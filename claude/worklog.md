# 作業ログ

> 現在地・次の一歩・運用メモだけを置く。完了した「やった」は git 履歴へ（タグで辿れる）。「なぜ」は [design-decisions.md](design-decisions.md)、「パイプライン設計」は [architecture.md](architecture.md)、「spec からの意図的剥離・暫定の仮決め」は [provisional.md](provisional.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で全パートを綴じ込む 1 モジュール＝`Loader`・`Lexer`・`Ast`・`Parser/`〔Expr/Stmt/Decl〕・`Codegen/`〔Emit/Resolve/Ops/Check/Expr/Stmt/Decl/Mono/Array〕・part はサブディレクトリ可）。自分自身を不動点までコンパイルする。

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust 不要）。`./bootstrap.sh --reseed` で種更新。
- **テスト**：`./test.sh`＝`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/part/`（複数ファイル）＋`tests/reject/*.pw`（plewc 非ゼロ終了で reject＝受理の健全性）＋`tests/panic/*.pw`（compile+link 成功・実行は非ゼロ＋`.panic` stderr 部分一致）＋不動点。

### サポート済の言語（現状スナップショット・経緯は git/タグ）

- **基本**：型付き整数/Bool・String（リテラル/`.bytes`/`==`/エスケープ）・文字リテラル・Array（リテラル/添字/`count`/`append`/`a[i]=x`/for-each）・struct と JSX 構築・enum＋match（網羅検査・or パターン・rename/discard 束縛・値位置 `match` 式）・インヘレントメソッド・`panic`・`if`/`else`/`while`/`for`/`break`/`continue`・値位置 `if`＋`give`。
- **演算子/整数**：算術・比較・論理・ビット/シフト・単項・`as`（整数・無損失のみ）・複合代入。**整数は厳密幅 stdint で格納＋算術/除算オーバーフロー・0除算は panic＋リテラル文脈型付け**（既定型なし・曖昧は reject・型サフィックス `5U64`）。
- **可変性検査**（place 単位＝単純変数＋`base.field` 合成＋`a[i]`＋`.append`/`inout fn` 受信側）・**引数ラベル検査**。
- **モジュール**：再帰＋dedup ローダ（`part ./`・`import ./`・`./Sub/`・`../`・`/Seg`〔`Plew.toml` 上方探索→`<root>/src`〕・`@Std/X`→`dirname(argv[0])/std/X.pw`）・`import @Std/{Io,Process} with {}`（I/O は import 必須）。診断 `compileError(At)` は普通の Plew 関数（脱 ambient 済）。
- **★generics 完成**（タグ `generics-data`/`generics-methods`）：型パラメータ `[T,U]`（struct/enum/fn/`impl[T]`）・単相化（`Box_I32`）・generic struct（構築/フィールド/ネスト/多パラメータ）・generic enum（`Optional`/`Result`・match）・**generic メソッド**（レシーバ型由来の単相化・body 置換 env）。
- **★コアライブラリ**＝`@Std/Core`（`compiler/std/Core.pw`）に `Optional[T]`/`Result[T,E]`＋メソッド・`assert(cond~:, message:)`。**`try`/`??`** 実装。
- **★値意味論（観測的に完成・タグ `value-semantics-complete`）**＝eager copy で配列/struct/generic struct/enum コンテナを let/代入/JSX/return でコピー。String は不変で共有・by-value 引数はイミュータブルで不要。
- **★`Ref[T]`（共有可変）**＝ヒープ箱（C `T*`）・`<Ref[T] value=e/>`・`r->field`・コピーで共有。
- **★クロージャ/関数値**＝関数型 `fn(...)->R`・関数を第一級値・非キャプチャのクロージャリテラル（ラムダリフティング）・高階関数。**ラベル抑制 `~:`**・**デフォルト引数 `name: T = expr`**。
- **値意味論・generics・クロージャを有効化したまま自己ホスト不動点維持**。生成 C は警告クリーン。**コンパイラ自身がメソッド/match 式で自己記述**（dogfood）。

## ★ ロードマップ（generics → コアライブラリ → ランタイム）

意味論の hidden-meaning は大半解消済み（整数幅・match・ラベル・診断・受理の健全性チェックリストは [provisional.md](provisional.md) で全項解消）。残りは大物が中心。**拠り所「意味は最優先・コストは裏で後回し可」**：leak ランタイムは hidden-cost ゆえ後回し可。

1. ✅ **generics 完了**。残 additive：generic free 関数（呼び出し位置推論＋明示 `id[I32](x)` の Go 式判別）・`map[U]`（メソッド own 型パラメータ＋推移的インスタンス化＝単相化中の発見を worklist で fixpoint）。
2. ✅ **コアライブラリ（純 Plew）大筋完了**（`@Std/Core`・`try`/`??`・`assert`）。残り：**可謬 I/O（`readFile`→`Result`）→ S2 を閉じる**（ただし std モジュールが intrinsic を使う際の import ゲート整合に注意）・ambient 化・`try` の From 変換・`?.`。
3. ✅ **CoW（値意味論）＝観測可能な範囲は完成**。残り（deferred・hidden cost）：**正確な refcount＋スコープ解放を伴う完全 CoW（遅延コピー＋ leak 解消）＝ARC とセット**。`inout` と CoW の相互作用は正確な解放が前提。
4. 🔄 **ARC ＋ `Ref`/`WeakRef`**：✅ 基本 `Ref[T]`。✅ **スコープフレーム基盤**＝`genBlock`/`for`/`match` 入口で `scopeMark`→出口で `scopeExit`（`emitScopeDrops`〔今は no-op〕＋`popLocals`）。名前解決を真の lexical scope に厳格化（回帰テスト `scope_shadow`）。✅ **ASan ハーネス**（`ASAN=1 ./test.sh`・free 導入時の UAF/double-free を機械検証・leak 検出は free 後に `detect_leaks=1`）。
   - **RC は非アトミック**（atomic 不要）＝spawn 境界で値を実体化（deep copy）するので refcount バッファが2スレッドから同時に触られない＝バリア不要。"ARC" は Automatic（コンパイラ挿入）の意で Atomic ではない。前提＝**spawn 実装時に「境界で materialize」を必ず入れる**（破ると非アトミック前提が崩れる）。→ [design-decisions.md](design-decisions.md)。
   - ✅ **refcount 表現**＝`PlewArray` に `long long* rc`（所有＝バッファ先頭ヘッダを指す・**NULL＝借り物**〔`.bytes` ビュー・文字列リテラル静的〕で retain/release は no-op）。`plew_arc_alloc`〔rc=1〕/`retain`/`release`〔NULL安全〕。全構築点（`_new`/`_copy`/`_push`/`.bytes`）で rc 設定。
   - ✅ **成長時の旧バッファ解放**（`_push` realloc・追跡不要の安全 free・支配的 leak 解消）。✅ **scope 末の owned 配列 release**＝`Local.owned`（`let`=owned／param・for・match=borrow）→`emitScopeDrops` で owned 配列を `plew_arc_release`。配列 let は `genArrayValue` で常に一意所有ゆえ retain 不要。**ASan ビルドのコンパイラが自己コンパイルをクリーン完走**（UAF/double-free なし・122 release 発行）で実証。検証法＝`clang -fsanitize=address` で plewc.c をビルド→`compiler/src/_.pw` を食わせる。
   - **⚠️ 依存の発見＝CoW が先・struct release は後**：当初「再帰/struct release → 最後に CoW」と想定したが逆。**owned struct ローカルの release は CoW 流の束縛（共有時 retain）が前提**。理由＝immutable struct 束縛 `val f = c.funcs[i]` は **浅いビュー**（配列と違い `genArrayValue` でなく `genExpr`＝深いコピーしない）で arena の配列フィールドを alias するので、素朴に `Struct_release(f)` すると double-free（自己コンパイルがクラッシュ＝実証済み）。配列は常に一意所有ゆえ release 安全だが struct は共有する。→ **次は CoW（束縛を copy→share+retain に）を先に入れ、それから struct release が安全になる**。
   - ✅ **CoW（配列）完成**：`_share`（retain＋alias）/`_unique`（rc>1 なら複製してから変異）を runtime に・`_set`/`_push` 先頭で `_unique`＝**全変異が CoW**。`genArrayValue` の place 束縛を `_copy`→`_share`＝束縛は O(1) 共有・書込時のみ遅延複製。値意味論を `cow_array` テストで固定（`b=a; a[0]=99; a.append(4)` → a=[99,2,3,4]・b=[1,2,3]）。ASan コンパイラ自己コンパイルもクリーン（共有下で収支保持）。
   - ✅ **CoW（struct）完成**：`Struct_share`（heap フィールド retain）＋struct 束縛（`genStructValue`・`Stmt.Let` 非配列＝mutable/immutable 両方）を share に切替。これで **owned struct ローカル release を安全に再有効化**（`structLocalReleasable`＝具体〔非ジェネリック〕heap-struct 限定・前回 double-free クラッシュは share で解消）。struct フィールド経由の変異も `_set`/`_push` の `_unique` で CoW。値意味論を `cow_struct` テストで固定。ASan 自己コンパイルもクリーン（249 share／281 release・収支保持）。**＝CoW 完了（配列＋struct）**。
   - ✅ **再帰 release＋深い `_copy`**：配列 `_copy` が struct 要素を `<Elem>_copy`（深い）・`PlewArray_E_release` が struct 要素を再帰解放してから free（深いコピーと再帰解放はセット＝COW-split で要素が独立ゆえ double-free しない）。emitScopeDrops/Struct_release が `PlewArray_E_release` を呼ぶ。ドライバは struct copy/share/release **proto を array runtime より前**に（相互再帰）。入れ子値意味論を `cow_nested` で固定。`Array[Func]`→各 Func の params 等の入れ子 leak を解消。
   - ✅ **早期 exit release**：`return`（値を temp 退避→`emitScopeDrops(0)`→temp 返す）・`break`/`continue`（`c.curLoopMark`＝ループ本体入口 mark から release・nested は save/restore・`panic` は drop 不走）。
   - ✅ **`Ref` 箱の refcount 化**：`<Ref .../>` が `plew_arc_alloc`（inline rc ヘッダ・Ref 値はヘッダの先）で確保・pointee は genCopyValue で move/share・bind で `plew_ref_share` retain・owned Ref ローカルは scope 末で `emitRefRelease`（pointee が heap〔array/heap struct〕なら再帰解放してから箱 free）。Ref は共有可変のまま（エイリアス越しの書込が見える）。`ref_box` テスト（struct-with-array を箱に・共有箱を rc=0 で一度 free）で ASan 実証。
   - **✅ leak 仕上げ完了（値型＋Ref）**：配列・struct・入れ子・早期 exit・Ref の leak を全解消、CoW（共有＋書込時複製）稼働、すべて fixpoint＋97テスト（通常＋ASan）＋ASan 自己コンパイルで実証。残る ARC＝`deinit`（unique 型が前提・未実装）・`WeakRef`＋`upgrade()`・循環回収（Bacon–Rajan・Ref グラフ限定）・mono struct/enum の share/release（mono 局所は leak・安全）。**コア ARC＋CoW は完成。**
   - その先：`deinit`（unique・破棄順＝型本体→フィールド宣言順・unique 型自体が未実装）・`WeakRef`＋`upgrade()`・循環回収（Ref グラフ限定サイクルコレクタ・spec/14）・bare `<Ref value=e/>` 型推論（明示 `[T]` 必須）。
5. 🔄 **イベントループ（async/await/spawn）**（最大・最後）。✅ 土台＝関数値＋非キャプチャクロージャ。残り：
   - **クロージャのキャプチャ**＝外側ローカル参照（`makeCounter`）。**env＋fat closure（{fn ptr, env ptr}）＋エスケープでキャプチャ変数をヒープ化**。現状の bare 関数ポインタ表現の根本変更で、関数型/呼び出し/全経路に波及（相互依存が強く incremental green が困難）＝**`spawn { block }` の前提**。spec は参照キャプチャ（Swift 流・`mut val` 共有可変）。
   - **spawn**＝pthread。境界で CoW 値は eager 実体化・`Ref` は越えられない（spec/14）。`JoinHandle[T]`/`join()→Promise[T]` は async 機構依存（blocking join に簡略化するなら言語表面の判断＝要確認）。
   - **async/await**＝状態機械変換 or コルーチン＝最難。`Promise[T]` 自動ラップ・`await` 展開・スケジューラ。spec 表面（Promise API）に密接。
- **traits**（`Eq`/`Ord`/`Iterator`＋`where` 境界）・**Dictionary**（`[k:v]`・Hash）は別の大物（generics 後・コアライブラリと並走で純 Plew 化）。**I2**（import の with ゲート＝定義のモジュール所属追跡＋可視性検査・今は全フラット）は多モジュール化が進む段で additive。

## 機能を plewc.pw に足す手順（ADD→reseed→USE）

新機能を plewc.pw の**ソースで使う**には：①`compiler/src/` の codegen に機能を足す（ADD）→ ②`./bootstrap.sh --reseed` で種更新（→ `compiler/plewc.seed.c` を commit）→ ③ソースで使う（USE）。「ソースが使う機能は常にひとつ前のコンパイラがサポート済み」を守れば不動点は壊れない。**新しい preamble 行や codegen 出力変化（genCElem 等）・AST フィールド追加を足したら reseed を 2 回**（1 回目で挙動を種に焼き、2 回目で種ファイルを一致させる）。暗黙ビルトイン→実 `@Std`/`extern` への移行も同じ ADD→USE→REMOVE で flag day にならない。

## メモリモデル（hidden cost の暫定）

Array/`Ref` は **ヒープ確保＋リーク（free しない）**で実装（spec の遅延 CoW・ARC 解放/`deinit` は未）。値意味論は eager copy で**観測的には正しい**。正しい解放/遅延は後段 ARC（hidden cost＝受理の健全性の対象外）。詳細は [provisional.md](provisional.md)。

## 運用メモ

- 動作する区切りで**記述的 git タグ**（`generics-data`/`value-semantics-complete` 等・バージョン番号はまだ）。コミットメッセージは英語＋`Co-Authored-By`。GPG 署名（`--no-gpg-sign` を使わない）。
- **不要になった実装は削除し、必要なら git tag から復旧**（例：`git checkout stage0-final -- bootstrap`）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。
- C 予約語（`double` 等）と衝突する Plew 識別子は生成 C が壊れる＝名前マングリング未実装（コンパイラ自身は回避・ユーザーコードで顕在化）。
- LLVM 化は当面しない＝意味論が揃ってから（所有権・並行の後）、性能 or 直 WASM が要る時に並行バックエンドとして追加（C は捨てない）。
