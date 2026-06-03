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
- **★値意味論＋CoW＋refcount 解放**＝非アトミック refcount（`rc` ポインタ・NULL＝借り物）で配列/struct/`Ref` を管理。束縛は O(1) 共有＋retain、変異点で rc>1 なら複製（copy-on-write）。解放は scope 末・早期 exit・成長時（再帰）。詳細は下のロードマップ item 4。
- **★`Ref[T]`（共有可変・refcount 化）**＝rc ヘッダ付きヒープ箱・`<Ref[T] value=e/>`・`r->field`・コピーで retain 共有・scope 末で release。
- **★`unique` 型＋`deinit`＋所有権**＝`unique struct`＋`deinit`（決定的破棄・型本体→フィールド宣言順・ネスト再帰）・`move`/`borrow` モード（前置＋引数）・線形 move 追跡（use-after-move/bare コピー/伝染/モード必須を reject）。詳細は下のロードマップ item 4b。
- **★クロージャ/関数値**＝関数型 `fn(...)->R`・関数を第一級値・非キャプチャのクロージャリテラル（ラムダリフティング）・高階関数。**ラベル抑制 `~:`**・**デフォルト引数 `name: T = expr`**。
- **値意味論・generics・クロージャを有効化したまま自己ホスト不動点維持**。生成 C は警告クリーン。**コンパイラ自身がメソッド/match 式で自己記述**（dogfood）。

## ★ ロードマップ（generics → コアライブラリ → ランタイム）

意味論の hidden-meaning は大半解消済み（整数幅・match・ラベル・診断・受理の健全性チェックリストは [provisional.md](provisional.md) で全項解消）。残りは大物が中心。**拠り所「意味は最優先・コストは裏で後回し可」**：leak ランタイムは hidden-cost ゆえ後回し可。

1. ✅ **generics 完了**。残 additive：generic free 関数（呼び出し位置推論＋明示 `id[I32](x)` の Go 式判別）・`map[U]`（メソッド own 型パラメータ＋推移的インスタンス化＝単相化中の発見を worklist で fixpoint）。
2. ✅ **コアライブラリ（純 Plew）大筋完了**（`@Std/Core`・`try`/`??`・`assert`）。残り：**可謬 I/O（`readFile`→`Result`）→ S2 を閉じる**（ただし std モジュールが intrinsic を使う際の import ゲート整合に注意）・ambient 化・`try` の From 変換・`?.`。
3. ✅ **値意味論＋CoW 完成**（item 4 の ARC とセット＝refcount＋copy-on-write＋解放）。
4. ✅ **コア ARC＋CoW 完成**（非アトミック refcount・配列/struct/`Ref`・fixpoint＋97テスト〔通常＋ASan〕＋ASan 自己コンパイルで実証）。
   - **RC は非アトミック**（atomic 不要）＝spawn 境界で値を実体化（deep copy）するので refcount バッファが2スレッドから同時に触られない。"ARC" は Automatic の意で Atomic ではない。前提＝**spawn 実装時に「境界で materialize」を必ず入れる**。→ [design-decisions.md](design-decisions.md)。
   - **機構**：`PlewArray`/struct/`Ref` 箱に inline `long long* rc`（先頭ヘッダ・**NULL＝借り物**〔`.bytes`/文字列リテラル〕で retain/release no-op）。束縛は **O(1) 共有＋retain**（`_share`/`Struct_share`/`plew_ref_share`）、**変異点で rc>1 なら複製**（`_set`/`_push` 先頭の `_unique`）＝CoW。解放＝**scope 末**（`emitScopeDrops`・`Local.owned`〔let=owned／param・for・match=borrow〕）・**早期 exit**（`return`〔値を temp 退避〕/`break`/`continue`〔`curLoopMark`〕・`panic` 不走）・**成長時**、配列要素/struct フィールドを**再帰解放**（深い `_copy` とセット）。
   - **検証法**：`ASAN=1 ./test.sh`（テストプログラムを ASan で）＋**ASan ビルドのコンパイラで自己コンパイル**（`compiler/plewc _.pw > p.c; clang -fsanitize=address p.c -o pa; ASAN_OPTIONS=detect_leaks=0 pa _.pw`＝UAF/double-free 検出）。値意味論は `cow_array`/`cow_struct`/`cow_nested`、Ref は `ref_box`/`ref_shared` で固定。
   - **残る ARC**：`WeakRef`＋`upgrade()`・循環回収（Bacon–Rajan・Ref グラフ限定・spec/14）・mono struct/enum の share/release（mono 局所 leak・安全）・bare `<Ref value=e/>` 型推論（明示 `[T]` 必須）。
4b. ✅ **`unique` 型＋`deinit`＋move 所有権 完成**（タグ `unique-deinit`/`unique-move`/`unique-checks`/`unique-nested`）。`unique struct`＋`deinit { }`（struct 本体／`impl` 両形・合成 `Type_deinit(Type self)`＋`c.deinits`）。**move 意味論**＝`move`/`borrow` 前置（`Expr.Move`・`try` と同位）＋`move T`/`borrow T` 引数モード・線形 move 追跡（`Local.moved` を rebuild で立て・moved は解放せず・use-after-move エラー・unique の bare コピー/bare 引数はエラー＝`move`/`borrow`/`inout` 必須・`move T` 引数は callee 所有〔関数末で `emitScopeDrops(0)`〕・unique place の `return` は暗黙 move）。**deinit 発火**＝所有 local の scope 末/早期 exit で `Type_deinit`→`Type_release`（型本体→フィールド宣言順・再帰）。**伝染チェック**＝unique フィールドを持つ struct は `unique` 必須・copyable に `borrow`/`move` 不可・unique 引数はモード必須。**ネスト deinit**＝`structNeedsRelease`（unique フィールド含む）で `_release` を出し、各 unique フィールドの `deinit`+`release` を宣言順に再帰（deinit proto を前出し）。検証＝`unique_deinit`/`unique_move`/`unique_nested`（ASan clean）＋reject 群。
   - **健全性ハードニング 完了**（タグ `unique-ref-deinit`/`unique-loud-rejects`/`unique-cond-flow`/`unique-no-generic-args`/`unique-no-double-deinit`/`unique-give-guard`）＝**unique 値が黙ってコピー/leak/二重 deinit する穴を全て塞ぐ**（拠り所「意味は唱えた通り」＝silent な意味喪失を排除）。実装：(1)**`Ref[unique]` の deinit を最後の解放で発火**（`emitRefRelease` が pointee の `Type_deinit`→`Type_release`・spec 推奨の「unique を共有/格納するなら `Ref` 包み」が動く）。(2)**`Array[unique]` を reject**（`c.arrayElems` 走査・`Array[Ref[unique]]` は可）。(3)**unique を generic 型引数に不可**（`c.types` 全走査・`Box[File]`/`Optional[File]`/`Result[File,E]` 不可・`Ref` 除外）。(4)**条件付き return の発散修正**＝`emitScopeDrops(exclIdx)` で「この exit だけ除外」（move を永続化しない・`if c { return a } return b` が各パスで未返却側を deinit）。(5)**条件付き move を reject**＝`curBranchBase`（if/while/for/match body 入口の locals 高水位）より外の local の `move` を拒否（永続 moved が不走パスで deinit を飛ばすため）。(6)**unique reassignment を reject**（旧値 deinit 不走＋RHS place コピー）。(7)**struct フィールド/`Ref`/`give` への unique place コピーを reject**（`checkMakeFields`＋`Stmt.Give`・`move`/fresh のみ可）。(8)**`move fn`/`borrow fn` self の silent swallow を reject**。⇒ **危険な unique パスは「正しく動く」か「loud に弾く」だけ＝silent な二重 deinit/leak は無い**。`inout`（param＋`inout fn`）は正規に動作（`unique_inout`）。
   - **追加機能 完了**（タグ `unique-reassign`/`unique-move-fn`）＝(B)**deinit-on-reassign**＝`mut val` unique の再代入は旧値を `Type_deinit`→`Type_release` してから新値（move/fresh）を store（各値ちょうど1回 deinit・直線版・`unique_reassign`）。(A)**消費メソッド `move fn` self**＝self を所有し全 exit（return＋fall-through）で `emitSelfDeinit`・呼び出し位置でレシーバを moved 印（`Func.selfMove`／`c.curSelfMove`）・`borrow fn` は `fn` の同義語として受理。ガード＝`move fn` 呼び出しはレシーバが「所有 local」必須（borrow／field／element／分岐外は reject）・`move self`／`return self` は reject（`unique_move_fn`）。
   - **残る unique（全て loud reject か N/A・silent な穴は無し）**：field/element の部分 move／部分 return／`move fn` 経由の部分消費（reject＝部分 move 追跡 TODO）・条件付き move/消費（reject＝flow 解析 TODO）・分岐内 unique 再代入（curBranchBase で RHS move が止まる・直線のみ）・value-position `give` の unique（reject TODO）・`local struct`（spawn 境界・async 段で）・クロージャの unique キャプチャ（クロージャ未キャプチャゆえ N/A）・モジュール直下 unique val（プロセス終端 leak・安全）。
5. 🔄 **イベントループ（async/await/spawn）**（最大・最後）。✅ 土台＝関数値＋非キャプチャクロージャ。残り：
   - **クロージャのキャプチャ**＝外側ローカル参照（`makeCounter`）。**env＋fat closure（{fn ptr, env ptr}）＋エスケープでキャプチャ変数をヒープ化**。現状の bare 関数ポインタ表現の根本変更で、関数型/呼び出し/全経路に波及（相互依存が強く incremental green が困難）＝**`spawn { block }` の前提**。spec は参照キャプチャ（Swift 流・`mut val` 共有可変）。
   - **spawn**＝pthread。境界で CoW 値は eager 実体化・`Ref` は越えられない（spec/14）。`JoinHandle[T]`/`join()→Promise[T]` は async 機構依存（blocking join に簡略化するなら言語表面の判断＝要確認）。
   - **async/await**＝状態機械変換 or コルーチン＝最難。`Promise[T]` 自動ラップ・`await` 展開・スケジューラ。spec 表面（Promise API）に密接。
6. ✅ **関数/メソッドのオーバーロード 完成**（タグ `overload-mangle`/`overloading`）＝traits の土台（セレクタ＝名前＋ラベル＋型のモデル・`via` 別名／多重 conformance／同名別シグ要求の前提）。C 名を `writeFnSelector`（名前＋各 param の ラベル＋型頭・配列は `A` 接頭）でマングルし、proto/def/呼び出し/関数値で同一に出力。`findFunc`/`findMethod` がラベル＋引数型で解決（arity/label/type の3軸・`exprType` も解決経由・単一名は first-label fallback で従来通り）。`overload` テスト。
7. 🔄 **traits → closures → Iterator/Dictionary**（現在進行・ユーザー合意の順）。**(1) traits コア＋Eq/Ord**（trait 宣言・`impl A as Trait`・`where T: Trait` 解決・提供メソッド・`via`）→ **(2) closure キャプチャ**（イベントループ第1段・Iterator コンビネータの前提）→ **(3) Iterator/Iterable＋Hash/Dictionary/Set**。`any P` 存在型は traits の重い尻尾＝最後。spec/08。**オーバーロード（item 6）は完了済の前提。**
- **イベントループ（async/await/spawn）**は最後の大物（上の item 5）。**Dictionary** の `[k:v]` リテラルは traits（Hash）後。**I2**（import の with ゲート＝定義のモジュール所属追跡＋可視性検査・今は全フラット）は多モジュール化が進む段で additive。

## 機能を plewc.pw に足す手順（ADD→reseed→USE）

新機能を plewc.pw の**ソースで使う**には：①`compiler/src/` の codegen に機能を足す（ADD）→ ②`./bootstrap.sh --reseed` で種更新（→ `compiler/plewc.seed.c` を commit）→ ③ソースで使う（USE）。「ソースが使う機能は常にひとつ前のコンパイラがサポート済み」を守れば不動点は壊れない。**新しい preamble 行や codegen 出力変化（genCElem 等）・AST フィールド追加を足したら reseed を 2 回**（1 回目で挙動を種に焼き、2 回目で種ファイルを一致させる）。暗黙ビルトイン→実 `@Std`/`extern` への移行も同じ ADD→USE→REMOVE で flag day にならない。

## メモリモデル

Array/struct/`Ref` は **非アトミック refcount＋copy-on-write**（inline rc ヘッダ・共有＋書込時複製）。解放は scope 末/早期 exit/成長時で再帰（leak 解消済）。残る hidden cost＝循環回収（`WeakRef` or サイクルコレクタ・未）・mono 局所 leak。詳細は [provisional.md](provisional.md)、根拠（非アトミック等）は [design-decisions.md](design-decisions.md)。

## 運用メモ

- 動作する区切りで**記述的 git タグ**（`generics-data`/`value-semantics-complete` 等・バージョン番号はまだ）。コミットメッセージは英語＋`Co-Authored-By`。GPG 署名（`--no-gpg-sign` を使わない）。
- **不要になった実装は削除し、必要なら git tag から復旧**（例：`git checkout stage0-final -- bootstrap`）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。
- C 予約語（`double` 等）と衝突する Plew 識別子は生成 C が壊れる＝名前マングリング未実装（コンパイラ自身は回避・ユーザーコードで顕在化）。
- LLVM 化は当面しない＝意味論が揃ってから（所有権・並行の後）、性能 or 直 WASM が要る時に並行バックエンドとして追加（C は捨てない）。
