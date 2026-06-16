# コンパイラ アーキテクチャ

Plew コンパイラの実装方針。**🎉 セルフホスト達成済み**＝正典コンパイラは Plew 製のパッケージ `compiler/src/`（`Ir ← Frontend ← Backend ← entry` の一方向モジュール DAG＋共有 leaf〔Path/Ops/Diag〕・各 root が `Codegen/*`／`Backend/Llvm/*` を part で綴じる・自分を不動点までコンパイル）。**構文解析（レクサ・式/文/宣言/トップレベルパーサ）は共有 `@Std/Syntax` に統合済**（コンパイラもマクロも同一パーサ＝真の 1 AST＝A フロントエンド統合・[metaprogramming-architecture.md](metaprogramming-architecture.md)）＝本体は共有経路で parse→`Codegen/Lower.pw` で arena へ lower→`Backend/Llvm.pw` で LLVM IR→clang。本書はパイプライン設計と、**そこへ至るブートストラップの経緯**（使い捨て Rust stage0→退役）を残す。現在地・次の一歩は [worklog.md](worklog.md)。

## ゴールと第一目標

- **第一目標＝「Plew でコンパイラが書ける状態」**。そこへ達したら即座に **Plew によるセルフホスティング**へ移行する（最終ゴール）。
- **速度最優先**＝開発速度。ただし「バグりにくさ」「テストのしやすさ」のように間接的に開発速度へ寄与するものも速度に含める。**コンパイラ自体やビルド成果物の実行性能は最低限でよい**（設計の拠り所＝「意味は唱えた通り・難しい魔法は隠す」を優先・hidden cost は許容）。
- **第一目標時点では macOS（ローカル）でだけ動けばよい**。クロスや WASM は後。
- **メモリ管理は ARC**。既定は値意味論（CoW）で、opt-in の最小所有権（`unique`/`borrow`/`inout`/`move`・`Ref`/`WeakRef`）のみ（→ [language-semantics.md](language-semantics.md)、[design-decisions.md](design-decisions.md)）。

## 技術スタック

正典コンパイラ（`compiler/src/`・Plew 製）は **手書きレクサ + 再帰下降パーサ（共有 `@Std/Syntax`）→ LLVM バックエンド**（libLLVM-C を in-process で叩いてテキスト IR を吐く → clang・`compiler/plewc`）。かつて **C トランスパイル backend** を正典/オラクルとして併走させ、LLVM backend が C と完全機能同等（self-host 含む）に達した点が tag `llvm-c-parity`。その後 **C backend は退役・削除**（C 訳・C 生成コードは git 履歴／同タグに保存）＝いまは LLVM 単一 backend（WASM は LLVM 経由で後続）。下表は**使い捨て stage0（Rust・退役済み）**の技術選定で、骨格と「なぜ Rust だったか」の経緯。

| 役割 | stage0 の採用 | 備考 |
| --- | --- | --- |
| 実装言語 | **Rust**（退役済み・`git checkout stage0-final -- bootstrap` で復旧可） | lib + bin。`tests/` から内部を叩け TDD 容易。役割は stage1 を立ち上げることだけ |
| 字句・構文解析 | **手書き**（lexer + 再帰下降パーサ） | ANTLR は不採用。速度と挙動の完全な制御のため（stage1 も同じ） |
| コード生成 | **C へトランスパイル → `clang`** | LLVM バックエンドは self-host 後に Plew 側で追加済（C と同等）・WASM は LLVM 経由で後続 |
| ランタイム | **C**（基本型・I/O・配列） | 生成 C に preamble として埋め込み（stage1 は自前で出力） |

### 技術選定の経緯（なぜ巻き戻したか）

旧スタックは **C# / .NET 8 ＋ ANTLR4 ＋ LLVMSharp**（選定経緯は当初 `note/ChatGPT-言語選定の相談.md`＝TypeScript 有力 → LLVM バインディングが非公式ゆえ C#）。これを実装着手時に**技術選定ごと破棄**し、Rust ＋ C トランスパイルへ転換した。理由：

- **Rust を選ぶ**：①網羅 `match`＋強い型で AST/型検査の巨大な分岐がバグりにくく、`cargo test` で TDD しやすい（＝間接的な開発速度）。②所有権・トレイトが Plew の `unique`/`borrow`/`move`・trait 体系に近く、**stage1 を Plew で書き直すとき設計がほぼそのまま移植できる**（最重要の「セルフホストの脚」を加速）。③コンパイラエラーが親切で、人手を介さず自走で自己修正しやすい。
  - **却下案**：OCaml（ADT＋パターンマッチは最速だが Plew への移植性・ツール・自走補正で劣る）。Go（ADT/網羅が弱く AST コードが冗長）。TypeScript（反復は速いが型健全性・移植性が弱い）。
  - **既知の摩擦と対策**：Rust は素朴なポインタ相互参照（型グラフ・親参照）で借用検査と戦う。これは **arena ＋ index（`NodeId(u32)` 等の整数ハンドルで参照）**で回避する（rustc/rust-analyzer の定石。キャッシュ効率・安定 ID という副産物つき）。この方式は Plew の arena 設計にも移植できる。
- **stage0 は C トランスパイルを選んだ**：LLVM-IR は SSA・phi・明示型・手動メモリ操作で、テキスト手書きか C++ バインディング格闘になる。C は局所変数・制御構文・struct・関数呼び出しがそのまま使え最適化は clang 任せ、ARC ランタイムも C ヘッダ1枚。多くの言語が C 経由でブートストラップした実績（「仕組みは問わない」＝C は隠れた機構）。self-host 後、LLVM バックエンドを Plew 側で **libLLVM-C（安定 C API）経由・in-process** で追加し C と同等に到達（textual `.ll` 先行は不採用＝SSA 構築ロジックが共通ゆえ作り捨てになる・経緯は [design-decisions.md](design-decisions.md)「LLVM バックエンド」）。**C backend は完全同等（tag `llvm-c-parity`）まではオラクル/種として併走したのち退役・削除**し、LLVM 一本化した。ブートストラップ種も C 訳から LLVM IR 訳（`compiler/plewc.seed.ll`）へ移行＝libLLVM がビルド必須依存に。

## ブートストラップ戦略（達成済み・経緯）

辿った道：**stage0（Rust・使い捨て）が Plew サブセットを C に落とす → そのサブセットだけで stage1（`compiler/src/_.pw`）を書く → stage0 でコンパイル → 自分自身をコンパイルできて不動点＝セルフホスト達成 → stage0 を退役**。いまは stage0 不要で、stage1 の LLVM IR 訳（種 `compiler/plewc.seed.ll`＋随伴ランタイム `compiler/plewc.seed.runtime.c`）から `./bootstrap.sh`（clang＋libLLVM）で自己ブートストラップする（C 訳の種からの clang 単独ブートストラップは C backend 退役で終了）。以降の機能（WASM バックエンド・循環回収・所有権検査・トレイト等）は Plew 側（stage1）で additive に育てる。現コンパイラが spec から意図的に省いている範囲は [provisional.md](provisional.md)。

> arena＋index で AST を組み共有可変（`Ref`/`WeakRef`）を使わない規律、CoW をベタコピー（リーク）で代用する素朴化など、ブートストラップ用の素朴化は両 stage で設計が揃うよう選んだ。詳細・現状の剥離一覧は [provisional.md](provisional.md)。

## コンパイルパイプライン（設計）

```
.pw ソース
  │  手書き Lexer（→ token 列）
  ▼
Token 列
  │  手書き再帰下降 Parser
  ▼
AST（arena 確保・index 参照）
  │  セマンティック解析
  │   1. 名前解決（モジュール / import / スコープ）
  │   2. 型推論・型検査（ジェネリクス、where 句）※ 実装済
  │   3. trait/impl 解決（継承・where bound・トレイト間準拠 `impl B as A`・Eq/Ord・derive）／拡張解決（`#Ext` view・源選択・defaultExtension）※ ともに実装済（struct レシーバ）
  │   4. 受理健全性検査（emission 非依存パス `verifyProgram`）※ 実装済
  │   5. 並行性検査（spawn キャプチャ）※ async/await 段は実装済 / spawn 段は未実装
  ▼
型付き AST（共有 `runFrontend`）
  │  └─ LLVM IR 生成（libLLVM-C・in-process）→ テキスト IR → clang  （compiler/plewc）
  ▼
ネイティブバイナリ（mac）
```

### 各フェーズの実装メモ（意味論＝言語非依存の契約）

以下は「コンパイラがどう振る舞うべきか」の意味論メモ。多くは実装済（型検査・trait step 1・ARC・クロージャ・async/await・受理健全性検査・LLVM backend）、残る未実装は拡張解決（#Extension）・並行 spawn で、これから実装するときの索引として残す。

- **フロントエンド（実体＝A 後）**: 上図の「Token 列→手書き Parser→arena AST」は、実装では**共有 `@Std/Syntax` パーサが値ツリー（`TopItemAst`/`DeclAst`/`ExprAst`…・String 名・原本座標 span）を返し、`Codegen/Lower.pw` が arena（index 参照ノード）へ lower** する 2 段（コンパイラもマクロも同一パーサ＝[metaprogramming-architecture.md](metaprogramming-architecture.md)）。ローディングもパース駆動＝ファイルを parse して木の `import`/`part` ノードを辿る（事前スキャンなし）。`@[...]` ディレクティブは木の `Directive` ノードで、ユーザー定義メタプロはビルドと独立した別コマンド（`plew gen`）で別ファイル `<Foo>.gen.pw` へコード生成→ローダが auto-part。→ [design-decisions.md](design-decisions.md) / [spec/16](../spec/04-execution/16-metaprogramming.md)。
- **拡張解決（最重要）**: メソッド/演算子のバインドは「呼び出し位置の `#Extension` 指定」だけで決定論的に決め、import スコープに依存させない。無名（デフォルト）`impl` はそのまま発動、`extension Name { impl … }` は `#Name` 明示時のみ。一意に定まらなければエラー。→ [language-semantics.md](language-semantics.md)。
- **並行性検査**: `spawn { … }` のキャプチャはコピー可能のみ、`unique` を渡すなら `spawn fn` の `move` 引数。**借用は async/spawn 境界を越えず、`Ref`/`local` 型は spawn を越えられない**（推移的に `Ref`-free＝`local` でないことを検査）→ スレッド間に共有可変が無く実質 race-free（Mutex 不要）。戻りは `join() -> Promise[T]` ハンドル。
  - **codegen の責務（CoW × spawn）**: CoW 値は内部バッファを**非 atomic** refcount で共有するので、**spawn 境界を越えるコピー可能値には eager な実体化（ディープコピー）を挿入**（async 境界では遅延のまま）。これで非 atomic count を 2 スレッドから触られず全面 atomic ARC を避ける → [spec/14](../spec/04-execution/14-concurrency.md#cow-値は-spawn-境界で実体化するeager-copy)。
  - **クロージャ変換（capture）**: 通常の閉包は外側変数を**参照キャプチャ**（`mut val` は可変・共有・永続）。**脱出する閉包のキャプチャ変数はヒープへ昇格（box 化）**。`mut val` 参照キャプチャした閉包は共有可変ストレージを持つ＝`local` 扱いで spawn 不可。→ [spec/04 環境のキャプチャ](../spec/01-basics/04-functions.md#環境のキャプチャ)。
- **async/await ローワリング（方式 B＝stackless ステートマシン・実装済・LLVM backend）**: `async fn` を**状態機械**に変換する（Node/V8・Rust・C# と同じ・colored async）。`await` をまたいで生きる local だけを**ヒープのフレーム構造体のフィールド**へ昇格し（またがない local は通常のスタック変数のまま）、`await p` は `state=N`／フレーム退避／PENDING return、resume は state ディスパッチで再突入。`async fn f()` はフレームを確保し `Promise[T]` を返す。**スタックフル（方式 A＝コルーチン/ucontext）は却下**：観測挙動は colored 前提で A/B 同一だが、Node を範とすると終着点は B（軽量大量タスク・WASM 直行）で、A は async fn ローワリング〔難所〕を作り直す中継ぎになる。native-C 先行（意味論を固める）→ WASM（Asyncify/JSPI）。**なぜ B**＝[design-decisions.md](design-decisions.md)「async fn のローワリング」。
- **ARC**: 循環は `WeakRef`。自動回収は **Ref グラフ限定のサイクルコレクタ**（Bacon–Rajan・per-thread・idle）を additive に足す方向で確定。検出時は loud 報告＋メモリ回収＋**循環メンバの deinit は走らせない**（deinit の有無で分けない＝panic と対称の契約外脱出）→ [design-decisions「循環回収」](design-decisions.md)。
- **再帰的な値型の自動箱化（codegen）**: 自己参照 `struct`/`enum`（木・連結リスト・AST）は**コンパイラが再帰を検出し必要なフィールドを CoW ヒープセルで自動箱化**しレイアウトを有限化（`indirect` 等の修飾語なし）。値意味論の再帰型は循環を作れないので `WeakRef` 不要 → [spec/05 再帰的な値型](../spec/02-type-system/05-structs-enums.md#再帰的な値型)。
- **トップレベル/`assoc val` 初期化（runtime）**: 起動時 **eager**（`main` 前に全完了）。各値は **memoize サンク**で force-on-read で依存順を自動算出（静的依存解析なし）。**循環は起動時 panic**（async はデッドロック検出）。→ [spec/15 トップレベル初期化](../spec/04-execution/15-modules.md#トップレベル初期化と実行順序)。
- **実行エントリ／ランタイム寿命（runtime）**: 開始点は **`fn main`／`async fn main`**。①全トップレベル/`assoc val` 初期化 → ②`main`。戻り `Result[(), E]` の `Err` は表示して非ゼロ終了。args/env は stdlib `Process`（import 要）。**終了条件＝`main` 返却＋イベントループ drain** → [spec/15 実行エントリ](../spec/04-execution/15-modules.md#実行エントリmain)。
- **panic は abort（codegen）**: `panic` はスタックを巻き戻さず **trap 一発**でプロセス停止（C では `abort`/trap）。**`deinit` は走らない**・unwind テーブルを吐かない（Rust `panic="abort"` 相当）。決定的解放は正常終了パスのみ → [spec/11 panic と発散](../spec/03-expressions/11-control-flow.md#panic-と発散)。
- **引数ラベルのコード生成**: セレクタ＝名前＋順序付きラベル列。**ラベル抑制 `name~:`** は無ラベル位置。関数型はラベルを型同一性に含む（サブタイプ/暗黙変換なし）→ [spec/04](../spec/01-basics/04-functions.md#ラベルの抑制)。

## 負債監査の結論＝RENOVATE（rewrite しない）・コンパイラの実体

上のパイプライン図は**理想形**で、実体は乖離がある（「表現力が貧弱な時代の設計」由来）。コンパイラ全フェーズを監査した結論＝**段階的 renovate（rewrite しない）**。負債は実在するが**局所的・legible・増分修正可**で、意味論は正しく高価な資産（`unique-*` 等の長いエッジケース蓄積）。

- **根① 型付き IR が無い**（最大）：図の「型付き AST」は実在せず、**型は codegen 中に都度復元**していた（`exprType` が AST を歩く）。帰結＝emission 順序が正しさの前提・3 パス＋codegen が別々に再導出・**単相化が codegen 全体のモード**（ambient な `curTypeParams`/`curRecvInstRef`）。**Phase B で `typeOf` キャッシュへ反転**（body ごと 1 回計算して読む・per-function clear）＝主部は解消、残り（checks 統合・pre-fill・`exprType` 駆逐）は worklog。
- **根② 名前がソースバイトオフセット**（symbol table 無し）：Loader が全ファイルを 1 buffer（`c.bytes`）へ追記（パース駆動＝各ファイルを parse 直後に lower するのでソースと再インターン名が交互配置・モジュール隔離なし・可視性は `moduleRanges`〔per-file レンジ〕で後付け）。**Phase C＝名前 interning（宣言名）→ Phase D＝型 interning（型 span／型パラメータ）で解消**：宣言名・型名 span（`TypeRef.nameId`／`Param/Local/FieldDef.tyNameId`／`Bind.nameId`／`FuncBound.paramNameId/traitNameId`）を構築点で `intern`→id に持たせ、宣言名スキャン＋全型・型パラメータ照合を byte 比較から整数比較へ（src `spansEqual` 143→16・実装は worklog「名前/型 interning」）。残る 16 spansEqual は use-site 名（match-arm variant・capture・import・MakeField・arrayElem・curRecv・DeriveReq）＝型 triple の範囲外。`kwSpan`（byte を生む keyword span）と `rangeEquals`（span を keyword リテラルと比較）は据え置き＝短 keyword への byte 比較は既に安価で id 化に明確な利益が無い（評価済）。**重い D'（legacy 型 triple `(start,len,isArray)+ref` の構造的 ref 一本化）は別途未着手**。
- **なぜ rewrite でなく renovate**：①高価で正しい意味論を捨てて踏み直すことになる（Joel 典型）②**不動点の安全網**を長期間失う（renovate は各ステップ緑）③2 つの根は再帰値型が動く今だからこそ増分で剥がせる。
- **意味論は全て正しい（綺麗な所）**：ARC scope-drop・async stackless SM・checked 算術・RawBuffer 床・需要駆動単相化＋combinator 到達性ゲート・再帰 boxing 解析・パターン/優先順位パース。
- **renovation が届かない唯一＝ソース連結モジュールモデル**（Loader＋`*Start/*Len` span 規約）。分割/incremental compile はここを触らないと不可だが Loader に隔離・分割が要るまで後回し。

## リポジトリ構成

```
bootstrap.sh          LLVM IR 種からコンパイラをビルド＋IR 不動点検証（clang＋libLLVM・Rust 不要）
dev-rebuild.sh        編集後の高速 in-place 再ビルド（現 `compiler/plewc` が src を再コンパイル→上書き・不動点/種なし）
test.sh               テストスイート（run/panic/reject/part＋不動点）
test-gen.sh           メタプロ（gen/genreject）テスト
plew                  統一 CLI＝`plew build f.pw [-o out]`／`plew run f.pw`／`plew gen f.pw`（＋bare `plew f.pw`＝build 後方互換）。任意パスで動く＝std はバイナリ位置解決・生成物も gen harness も libc のみ（llvm-config 不要）・symlink 解決で隣の compiler/plewc を見つける・PATH に symlink 可
plew-gen.sh           `plew gen` への薄い委譲 wrapper（後方互換・メタプロ生成 `<file>.gen.pw`・spec/16）
tmp/                  ローカル実験の scratch（gitignore・cleanup はスクリプト内包）。コマンドに**直接 `rm` を書かない**（毎回確認プロンプトが出る）＝削除はスクリプトに内包して呼ぶ
tests/
  run/<name>.pw,.out  コンパイル&実行→stdout 照合（任意の .in を stdin に）
  reject/<name>.pw    spec-invalid＝コンパイル失敗すべきケース（受理の健全性）
  panic/<name>.pw     コンパイル&リンク成功・実行は非ゼロ＋`.panic` stderr 部分一致（overflow/0除算等）
  gen/<name>/App.pw   メタプロ（マクロ＋`@[...]`）→ gen→auto-part→実行→App.out 照合
compiler/             ★ 正典のコンパイラ＝Plew パッケージ（今後の機能はここに Plew で）
  src/                ★ コンパイラ＝3 層モジュール DAG（Ir ← Frontend ← Backend ← entry）＋共有 leaf
    _.pw              entry＝`./Frontend`・`./Backend` を import し `main` のみ（`runFrontend()→emitLlvm()`・libLLVM をリンク）
    Ir.pw             純データ leaf＝arena ノード型（Expr/Stmt/TypeRef…）＋`Comp`/`LlvmCtx` 等の状態型＋arena ヘルパ
    Frontend.pw       解析核（root）＝`impl Comp`・`runFrontend()`。`Loader`/`Parser/Decl`/`Codegen/*` を part で綴じる
    Backend.pw        LLVM エミッタ（root）＝`impl LlvmCtx`・`emitLlvm()`。`Backend/Llvm/*` を part で綴じる（libLLVM-C を呼ぶ唯一の層）
    Path.pw Ops.pw Diag.pw   Frontend・Backend 双方が import する純 leaf＝import パス計算／演算子オペコード（`opEq`/`opAdd`…）／診断＋十進整形
    Loader.pw         モジュールローダ（Frontend の part）＝パース駆動（各ファイルを parse→木の import/part ノードを辿る・dedup・パス解決・part=impl-only と missing/duplicate part を reject）
                      （レクサ・パーサは src になく `@Std/Syntax` に移設＝本体も共有経路で parse・メタプロと共有）
    Parser/Decl.pw    コンパイラ frontend driver＝module-tag helper（markImport/recordExport）＋derive 合成（synth*）。宣言パーサは持たない（共有 @Std/Syntax へ）
    Codegen/*         解析サブパス（Frontend の part 群）＝Resolve/Lower/Mono/Infer/Check/Verify/Emit/Decl/Expr/Stmt/Gen/Ops（Lower＝共有 AST→arena・Verify＝emission 非依存の受理検査パス `verifyProgram`・Infer＝TypeRef ベース型チェッカ・Emit＝共有 codegen ユーティリティ〔interning/span/型述語/行追跡〕・Gen＝`plewc --gen` の harness 合成）
    Backend/Llvm/*    LLVM IR エミッタ（Backend の part 群）＝機能別に分割（Stmt/Expr/Arith/Enums/Arrays/Closures/Async/Types… 等）
  std/                言語標準ライブラリ＝Lang/Core/Hash/Io/Process/Async/Ffi/Random/Syntax（Lang＝ambient マニフェスト＝import 不要面の唯一の正本〔`Optional`/`Result`/`Array`/`Dictionary`＋合成 intrinsic を宣言・プリミティブを Core から再エクスポート〕・Core＝import 必須の trait/プリミティブ定義＋witness／Hash＝`Hash`/`SipHasher`／Lang・Core・Hash・Syntax は起動時 force-load／Syntax＝メタプロ＆コンパイラ共有の構文層 `@Std/Syntax`＝`Syntax/`〔Lexer/Parser/Build〕）
  plewc.seed.ll       ブートストラップ種＝`_.pw` の LLVM IR（＋`plewc.seed.runtime.c`＝随伴ランタイム・チェックイン）
  (plewc / plewc0 / plewc.ll / plewc.runtime.c   ビルド生成物・gitignore。plewc バイナリ自体は追跡)
examples/             実証用 Plew プログラム（hello.pw＋self-host 途上の小コンパイラ群）
SPEC.md               言語仕様の目次（インデックス）
spec/<部>/NN-*.md     4 部サブディレクトリに分割した言語仕様本体
claude/*.md           本ガイドからリンクする実装ドキュメント
```

> **stage0（Rust 製・使い捨て）は self-host 達成後に退役・削除済み**（種ベースのブートストラップへ移行・Rust/cargo 不要）。Rust stage0 が要るときは `git checkout stage0-final -- bootstrap` で復旧（タグ `stage0-final`）。コンパイラの構造リファクタ（モジュール化・巨大ファイル分割・`Comp` god-object の解体）の到達点と残りは [compiler-refactor.md](compiler-refactor.md)。

## ビルド／開発ワークフロー

- **ビルド**：`./bootstrap.sh`（LLVM IR 種→clang＋libLLVM→自己コンパイル→IR 不動点検証・Rust 不要）。`--reseed` で種更新（→ 種＋追跡バイナリ `compiler/plewc` を commit）。編集中の高速反復は `./dev-rebuild.sh`。**テスト**：`./test.sh`（run/panic/reject/part＋不動点）／`./test-gen.sh`（メタプロ）。**コンパイラ実行**：`compiler/plewc foo.pw > foo.ll && clang foo.ll <runtime> $(llvm-config --ldflags) -o foo`（または統一 CLI `plew run foo.pw`）。手順詳細・罠は [worklog.md](worklog.md)「ビルド・テスト・機能追加手順」（ADD→reseed→USE・dev-rebuild の取り違え注意）。
- **テスト先行**：機能は `tests/run`（ゴールデン）／`tests/reject`（受理の健全性）で守る。
- **仕様書（`spec/`）は mdBook で閲覧**：設定 `book.toml`（`src = "spec"`）・目次 `spec/SUMMARY.md`・`mdbook serve --open` でライブリロード・`mdbook build`→`book/`（gitignore）。章の追加・改番時は `SUMMARY.md` も更新。
- `grammer/Plew.g4` は破棄済み（手書きパーサ）。正典は `SPEC.md`／`spec/*.md`。

> commit/push のタイミング・タグ命名・worklog 更新・「迷ったら仰ぐ／不要ファイルは消してよい」などの**プロセス方針は `CLAUDE.md`「作業の進め方・ユーザーについて」が住所**（ここでは再掲しない）。実装の現在地・次の一歩は [worklog.md](worklog.md)。
