# コンパイラ アーキテクチャ

Plew コンパイラの実装方針。**🎉 セルフホスト達成済み**＝正典コンパイラは Plew 製のパッケージ `compiler/src/`（root `_.pw` が `part` で全パート〔Loader/Ast/`Parser/Decl`/`Codegen/`〕を綴じ込む 1 モジュール・part はサブディレクトリ可・自分を不動点までコンパイル）。**構文解析（レクサ・式/文/宣言/トップレベルパーサ）は共有 `@Std/Syntax` に統合済**（コンパイラもマクロも同一パーサ＝真の 1 AST＝A フロントエンド統合・[metaprogramming-architecture.md](metaprogramming-architecture.md)）＝本体は共有経路で parse→`Codegen/Lower.pw` で arena へ lower→C→clang。本書はパイプライン設計と、**そこへ至るブートストラップの経緯**（使い捨て Rust stage0→退役）を残す。現在地・次の一歩は [worklog.md](worklog.md)。

## ゴールと第一目標

- **第一目標＝「Plew でコンパイラが書ける状態」**。そこへ達したら即座に **Plew によるセルフホスティング**へ移行する（最終ゴール）。
- **速度最優先**＝開発速度。ただし「バグりにくさ」「テストのしやすさ」のように間接的に開発速度へ寄与するものも速度に含める。**コンパイラ自体やビルド成果物の実行性能は最低限でよい**（設計の拠り所＝「意味は唱えた通り・難しい魔法は隠す」を優先・hidden cost は許容）。
- **第一目標時点では macOS（ローカル）でだけ動けばよい**。クロスや WASM は後。
- **メモリ管理は ARC**。既定は値意味論（CoW）で、opt-in の最小所有権（`unique`/`borrow`/`inout`/`move`・`Ref`/`WeakRef`）のみ（→ [language-semantics.md](language-semantics.md)、[design-decisions.md](design-decisions.md)）。

## 技術スタック

正典コンパイラ（`compiler/src/`・Plew 製）は **手書きレクサ + 再帰下降パーサ（共有 `@Std/Syntax`）→ 2 バックエンド**＝C トランスパイル → clang（`compiler/plewc`）と LLVM（libLLVM-C → `compiler/plewc-llvm`）。**LLVM バックエンドは C と完全機能同等＝達成済**（self-host 含む・tag `llvm-c-parity`・WASM は LLVM 経由で後続）。下表は**使い捨て stage0（Rust・退役済み）**の技術選定で、骨格と「なぜ Rust だったか」の経緯。

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
- **stage0 は C トランスパイルを選んだ**：LLVM-IR は SSA・phi・明示型・手動メモリ操作で、テキスト手書きか C++ バインディング格闘になる。C は局所変数・制御構文・struct・関数呼び出しがそのまま使え最適化は clang 任せ、ARC ランタイムも C ヘッダ1枚。多くの言語が C 経由でブートストラップした実績（「仕組みは問わない」＝C は隠れた機構）。self-host 後、LLVM バックエンドを Plew 側で **libLLVM-C（安定 C API）経由・in-process** で追加し C と同等に到達（textual `.ll` 先行は不採用＝SSA 構築ロジックが共通ゆえ作り捨てになる・経緯は [design-decisions.md](design-decisions.md)「LLVM バックエンド」）。C はオラクル/種として併存。

## ブートストラップ戦略（達成済み・経緯）

辿った道：**stage0（Rust・使い捨て）が Plew サブセットを C に落とす → そのサブセットだけで stage1（`compiler/src/_.pw`）を書く → stage0 でコンパイル → 自分自身をコンパイルできて不動点＝セルフホスト達成 → stage0 を退役**。いまは stage0 不要で、stage1 の C 訳（種 `compiler/plewc.seed.c`）から `./bootstrap.sh` で自己ブートストラップする。以降の機能（LLVM/WASM バックエンド・循環回収・所有権検査・トレイト等）は Plew 側（stage1）で additive に育てる。現コンパイラが spec から意図的に省いている範囲は [provisional.md](provisional.md)。

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
  │   3. trait/impl 解決（step 1＋Eq/Ord＋derive）※ 実装済 / 拡張解決（#Extension）※ 未実装
  │   4. 受理健全性検査（emission 非依存パス `verifyProgram`）※ 実装済
  │   5. 並行性検査（spawn キャプチャ）※ async/await 段は実装済 / spawn 段は未実装
  ▼
型付き AST（共有 `runFrontend`）
  │  ├─ C コード生成 → clang        （compiler/plewc）
  │  └─ LLVM IR 生成（libLLVM-C）→ clang  （compiler/plewc-llvm）
  ▼
ネイティブバイナリ（mac）＝両 backend 同一観測挙動
```

### 各フェーズの実装メモ（意味論＝言語非依存の契約）

以下は「コンパイラがどう振る舞うべきか」の意味論メモ。多くは実装済（型検査・trait step 1・ARC・クロージャ・async/await・受理健全性検査・両 backend）、残る未実装は拡張解決（#Extension）・並行 spawn で、これから実装するときの索引として残す。

- **フロントエンド（実体＝A 後）**: 上図の「Token 列→手書き Parser→arena AST」は、実装では**共有 `@Std/Syntax` パーサが値ツリー（`TopItemAst`/`DeclAst`/`ExprAst`…・String 名・原本座標 span）を返し、`Codegen/Lower.pw` が arena（index 参照ノード）へ lower** する 2 段（コンパイラもマクロも同一パーサ＝[metaprogramming-architecture.md](metaprogramming-architecture.md)）。ローディングもパース駆動＝ファイルを parse して木の `import`/`part` ノードを辿る（事前スキャンなし）。`@[...]` ディレクティブは木の `Directive` ノードで、ユーザー定義メタプロはビルドと独立した別コマンド（`plew gen`）で別ファイル `<Foo>.gen.pw` へコード生成→ローダが auto-part。→ [design-decisions.md](design-decisions.md) / [spec/16](../spec/04-execution/16-metaprogramming.md)。
- **拡張解決（最重要）**: メソッド/演算子のバインドは「呼び出し位置の `#Extension` 指定」だけで決定論的に決め、import スコープに依存させない。無名（デフォルト）`impl` はそのまま発動、`extension Name { impl … }` は `#Name` 明示時のみ。一意に定まらなければエラー。→ [language-semantics.md](language-semantics.md)。
- **並行性検査**: `spawn { … }` のキャプチャはコピー可能のみ、`unique` を渡すなら `spawn fn` の `move` 引数。**借用は async/spawn 境界を越えず、`Ref`/`local` 型は spawn を越えられない**（推移的に `Ref`-free＝`local` でないことを検査）→ スレッド間に共有可変が無く実質 race-free（Mutex 不要）。戻りは `join() -> Promise[T]` ハンドル。
  - **codegen の責務（CoW × spawn）**: CoW 値は内部バッファを**非 atomic** refcount で共有するので、**spawn 境界を越えるコピー可能値には eager な実体化（ディープコピー）を挿入**（async 境界では遅延のまま）。これで非 atomic count を 2 スレッドから触られず全面 atomic ARC を避ける → [spec/14](../spec/04-execution/14-concurrency.md#cow-値は-spawn-境界で実体化するeager-copy)。
  - **クロージャ変換（capture）**: 通常の閉包は外側変数を**参照キャプチャ**（`mut val` は可変・共有・永続）。**脱出する閉包のキャプチャ変数はヒープへ昇格（box 化）**。`mut val` 参照キャプチャした閉包は共有可変ストレージを持つ＝`local` 扱いで spawn 不可。→ [spec/04 環境のキャプチャ](../spec/01-basics/04-functions.md#環境のキャプチャ)。
- **async/await ローワリング（方式 B＝stackless ステートマシン・実装済・C/LLVM 両 backend）**: `async fn` を**状態機械**に変換する（Node/V8・Rust・C# と同じ・colored async）。`await` をまたいで生きる local だけを**ヒープのフレーム構造体のフィールド**へ昇格し（またがない local は通常の C スタック変数のまま）、`await p` は `state=N`／フレーム退避／PENDING return、resume は `switch(state)` で再突入。`async fn f()` はフレームを確保し `Promise[T]` を返す。**スタックフル（方式 A＝コルーチン/ucontext）は却下**：観測挙動は colored 前提で A/B 同一だが、Node を範とすると終着点は B（軽量大量タスク・WASM 直行）で、A は async fn ローワリング〔難所〕を作り直す中継ぎになる。native-C 先行（意味論を固める）→ WASM（Asyncify/JSPI）。**なぜ B**＝[design-decisions.md](design-decisions.md)「async fn のローワリング」。
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

## ビルド／開発ワークフロー

- **ビルド**：`./bootstrap.sh`（C 種→clang→自己コンパイル→不動点検証・Rust 不要）。**テスト**：`./test.sh`（`.pw` ゴールデン＋reject＋不動点）。**コンパイラ実行**：`compiler/plewc foo.pw | clang -x c -`。手順詳細は [worklog.md](worklog.md)（ADD→reseed→USE）。
- **テスト先行**：機能は `tests/run`（ゴールデン）／`tests/reject`（受理の健全性）で守る。
- `grammer/Plew.g4` は破棄済み（手書きパーサ）。正典は `SPEC.md`／`spec/*.md`。

> commit/push のタイミング・タグ命名・worklog 更新・「迷ったら仰ぐ／不要ファイルは消してよい」などの**プロセス方針は `CLAUDE.md`「作業の進め方・ユーザーについて」が住所**（ここでは再掲しない）。実装の現在地・次の一歩は [worklog.md](worklog.md)。
