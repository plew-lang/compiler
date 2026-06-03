# 作業ログ

> 現在地・次の一歩・運用メモだけを置く。完了した「やった」は git 履歴へ（タグで辿れる）。「なぜ」は [design-decisions.md](design-decisions.md)、「パイプライン設計」は [architecture.md](architecture.md)、「spec からの意図的剥離・暫定の仮決め」は [provisional.md](provisional.md)。

## 現在地

> **🐛 バグ調査カタログ（2026-06-04・能動プローブで発見・着手中）**：共通根＝**「`integer literal has no type from context`」が多くの未対応経路の catch-all 誤診断**で複数バグを覆い隠す。重大度順：
> - **F1〔大・✅修正済〕** 注釈なし `val x = expr` が String/Array/struct/関数戻り値/変数コピーで型推論せず `long long` を吐き壊れた C（`val b=a`/`val a=mk()` 全滅）。根因＝`Stmt.Let`（Codegen/Stmt.pw:376）が注釈なし時 `exprType(init)` を使わず空型→`long long` fallback。修正＝注釈なし（`tyLen==0 && !tyIsArray`）なら `exprType(init)` の TypeInfo（kind 0=scalar/1=String/2=struct·Ref·generic/3=array）を eff* 値へ写し注釈付き経路を再利用。String 裸リテラル（kind1 nameLen=0）は name span が無いので **loud-error**（注釈要求・silent 誤コンパイル排除）。テスト `run/let_infer`＋`reject/let_infer_bare_string`。残＝`val bs = s.bytes` は **gap #2（`.bytes` exprType 未対応）** で別件・Ref `value=` 内のリテラル型付けは別の小ギャップ（注釈ありでも `<Ref[I32] value=7/>` が落ちる）。
> - **F2〔大・✅修正済〕** 同一ブロック内シャドーイング `val x=1; val x=2` が C `redefinition`（ネストブロックは OK）。spec/03,11＝無制限 shadowing。修正＝`let` binding が live な同名 local を持つとき C 名に suffix `_s<n>`（`Local.cnum`・宣言/読み/scope drop の3点に writeLocalCName/writeNameCn で一致適用・for/match-bind/param は別 C ブロックゆえ cnum=0 のまま）。test `run/shadowing`。
> - **F3〔大・feature 規模〕** トップレベル変数 `val`/`mut val` を `parseProgram`（Parser/Decl.pw:988）が処理せず1トークンずつ黙殺＝"undeclared identifier"・エラーも出ない silent 剥離。spec/15 の init 順（全トップレベル/assoc val→main）が絡む。
> - **F4〔中〕** struct 分解パターン `P { val x, val y }`（spec/11:70,129 正典）が match/for で catch-all 誤診断で落ちる（enum バリアント分解は OK）。
> - **F5〔小・✅修正済〕** 存在しない入力ファイルで plewc が rc=0（preamble だけ吐く）。修正＝`main`（_.pw）で entry を `fileExists` 検証し `cannot open source file: <path>` で exit(1)。
> - **F6〔小・既知〕** `;` 文区切り誤診断・catch-all 誤診断全般。
> - **F7〔小・✅修正済〕** カンマ区切り struct フィールドが幻の空フィールド `long long ,;` を生成。修正＝`parseStruct` のフィールドループに `Kind.Comma` の loud-reject（spec はフィールド改行区切り）。test `reject/struct_comma_fields`。
> - **別の小ギャップ** Ref 構築 `<Ref[I32] value=7/>` の `value=` 内リテラルが Ref[I32] の T から型付けされず注釈ありでも落ちる（要 suffix）。
> - **F9〔中・✅修正済（未コミット）〕** bare-expr の match アーム（`=> expr`/`=> give v`）が statement 位置で壊れる＝`parseBlock` が後続アームを文として飲み込み最初のアームだけ登録→網羅判定が誤って非網羅に＋アーム欠落。修正＝`parseMatch` が `parseArmBody`（`{}` or 単一文をブロック化）を使う。test `run/match_bare_arm`。これで E1/E3/e1b/e1c 系の「網羅なのに非網羅」誤判定が解消。
> - **F10〔中・一部✅修正済（未コミット）〕** 配列要素越しの place 変更 `arr[i].field = x` が未実装で不正 C（`get(...).field = v`＝rvalue 代入）。修正＝`tryArrayElemFieldAssign` で get-modify-set 脱糖（plain `=`）。compound は loud-reject・inout メソッド経由（`arr[i].m()`）は未対応＝review-items 参照。
> - **F11〔中〕** ネスト配列 `Array[Array[T]]` が要素型に `Array` を literal 出力＝不正 C。→ review-items。
> - **F12〔中〕** U64 リテラル ∈ [2^63, 2^64-1] で plewc がクラッシュ（値を I64 蓄積→overflow panic）。整数リテラル符号モデルに波及＝GPG 回復後に。→ review-items。
> - **F13〔✅修正済〕** 配列型の関数デフォルト引数 `fn f(xs: Array[I32] = [])` の省略呼びが `f(0)`＝不正 C。修正＝default-fill で array param は genArrayValue。test `run/default_arg_array`。
> - **F16〔✅修正済〕** 配列リテラルを引数で渡すと `f(xs: [1,2,3])`→`f(0)`＝不正 C。修正＝提供引数ループで array param は genArrayValue。
> - **F15〔小〕** ビルトインメソッド名（`count` 等）と同名のユーザー自由関数呼びが誤コンパイル。→ review-items。
> - **F14〔中・重要・✅修正済（未コミット）〕** struct フィールド既定値 `val x: T = expr`（spec/05）が完全破損（`parseStruct` が `= expr` を消費せず phantom field）。修正＝`FieldDef.hasDefault/defaultVal`＋`Expr.Make` で省略フィールドへ default 挿入（`makeProvides`）。test `run/field_defaults`。残＝generic struct の field default 未対応・default 式の literal 型検査未。
> - 健全確認済（プローブで OK）：generic struct/method・closure（引数/高階/キャプチャ）・trait+where境界・provided method・Ref 共有変更・nested struct place 変更・`??`・mutual recursion・char リテラル・wildcard match・while break/continue・unique/move/deinit（決定的・use-after-move/bare-copy reject）・配列成長・struct 戻り値 inline・nested generic `Box[Box[T]]`。
> - **F8〔小〕** 裸の no-field enum variant 値 `Color.Green`（JSX `<Color.Green/>` でない）が不正な C（`Color.Green` をそのまま出力）を生成。コンパイラ自身は常に `<Kind.X/>` を使う＝裸は非サポート構文。loud-reject すべき（silent 剥離）。→ review-items。
> - 非バグ＝`print` の String 非対応は整数専用 placeholder shim（仕様面でない）。
> 推奨順＝F1→F2→F4→F3（F1/F2 は局所修正で広範な有効コードが通る）。**進捗：F1・F2・F5・F7 修正済み。残＝F3・F4・F6＋下記の据え置き群。**
> **あとでユーザーと確認したい項目（要判断／据え置き）は [review-items.md](review-items.md) に集約**（String 裸リテラル推論の loud-error 是非・カンマ区切りフィールド・F3/F4 実装・`.bytes` 型・Ref リテラル型付け 等）。

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で全パートを綴じ込む 1 モジュール＝`Loader`・`Lexer`・`Ast`・`Parser/`〔Expr/Stmt/Decl〕・`Codegen/`〔Emit/Resolve/Ops/Check/Expr/Stmt/Decl/Mono/Array〕・part はサブディレクトリ可）。自分自身を不動点までコンパイルする。

>
> **次の一歩＝(3) 関連型＋Iterator/Iterable**（closure は (2) 完了＝必要十分）。**closure 完了**＝(2a) fat closure 表現＋不変値キャプチャ（スカラー＋array/Ref/struct/String）／(2b-1) スカラー `mut val` 参照キャプチャ（`makeCounter`）／(2b-2) **leak 解消**（env drop＋scope 末 closure/cell release＋bind/return share＝macOS `leaks` で 0 leaks 確認）。タグ `closures-stage-a`／`closures-capture-scalar`／`closures-capture-heap`／`closures-mut-capture`／`closures-leak-free`。残＝(2b-3) `mut val` 非スカラー箱化・`local` マーク（spawn 段）。トレイト/generics は step 1＋健全性監査＋ARC 修正まで完了。
>
> **closure キャプチャの現状と設計（着手用）**：関数値は一律 **fat closure `PlewClosure{fn,env,rc,drop}`**（旧ベア関数ポインタから移行・ABI `R fn(void* env, params...)`・bare 関数値はサンク `<sel>__thunk` 経由・呼び位置で `.fn` を具体署名へキャスト）。**実装済キャプチャ**：(1)不変 `val` の値キャプチャ＝スカラー/String/array/Ref/plain struct（env 構造体 `__closure_env<id>`・body は `((__closure_env<id>*)__env)->name`・ヒープ所有は env に retain〔share〕＝エスケープ後も生存・`val` 不変ゆえ値=参照キャプチャと観測同一＝spec 準拠）。(2)**スカラー `mut val` 参照キャプチャ＝箱化**（外側ローカルを `T*` ヒープ ARC セル化〔`plew_arc_alloc`〕・env は `plew_ref_share` で retain ポインタ保持・両側 deref で共有＝`makeCounter`・boxed は body で `(*…->name)`・`isBoxedLocalAt`/`isBoxedCaptureOf`）。**ライフタイム＝leak 解消済**＝`PlewClosure.drop`＝`__closure_env<id>_release`（emitClosureEnvDrop が boxed セル/array/Ref/struct キャプチャを release）・所有 closure ローカルは `emitScopeDrops` で `plew_closure_release`・箱化セルも scope 末 `plew_arc_release`・bind/return は `genCopyValue` の fn 型分岐で `plew_closure_share`（retain）＝rc 均衡（macOS `leaks` で 0 leaks 確認）。**未対応は loud reject**（`mut val` 非スカラー／`unique`・generic・enum・関数値／ネスト closure／val capture への代入）。残 hidden cost＝引数直渡しの一時 capturing 閉包（束縛されず env 残り得る・小）・Ref pointee 残留。**(2b-3)**＝`mut val` 非スカラー箱化・`mut val` 参照キャプチャ閉包の `local` マーク（spawn 不可・spec/14・`spawn { block }` 前提）。詳細は item 5（イベントループ）。
>
> **既存ギャップ（closure 無関係・着手中に発見）**：①`;` を文区切りに使えない（改行区切り言語・`;` は value 0 合成 Int で「no type from context」誤エラー＝本来は構文エラーで弾くべき・パーサ堅牢化）。②`s.bytes.count` 等の field チェーン後置 `.count`/添字は exprType 未対応。
>
> **完了済（このフェーズ）**：trait T1–T3・assoc fn・Eq/Ord 配線・`@[Eq]`(struct/enum)/`@[Ord]`(struct) derive・健全性ギャップ #1–#4/#6/#8/#9（eager generic 型検査＝C++ テンプレート脱却）・監査の沈黙逸脱群（インライン制約/supertrait/同セレクタ衝突/ambient impl/`move fn`-copyable を reject・primitive が Eq/Ord 境界を満たす・比較非結合）・**ARC バグ修正**（配列 `_push`/`_set` が struct 要素を `E_copy`＝deep 所有・`_copy`/`_release` と対称＝過剰解放/UAF 解消・ASan 自己コンパイル clean）。タグ `traits-t1`〜`arc-array-elem-fix`。**残ギャップは provisional.md**（演算子トレイト全配線〔大物・需要駆動〕・曖昧リテラル/method 値化〔小・clang 止まり〕・`@[Ord]` on enum・#7 明示型引数〔据え置き〕）。
>
> **順序＝(2) closures → 〔関連型＋Iterator〕→ Hash→Dictionary**。関連型は Iterator 着手時に #9 を拡張（`where T: Iterator` の `it.next()->Optional[T.Item]`）。`any P` 存在型は最終フェーズ。

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust 不要）。`./bootstrap.sh --reseed` で種更新。**preamble/codegen 出力/AST フィールド変更後は reseed を2回**。
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
- **★オーバーロード完成**（タグ `overload-mangle`/`overloading`）＝関数/メソッドを **名前＋ラベル＋引数型** のセレクタで解決。C 名は `writeFnSelector` でマングル（名前＋各 param の ラベル＋型頭・配列 `A` 接頭）。arity/label/type の3軸・自由関数もメソッドも。traits（`via`・多重 conformance）の土台。詳細は下のロードマップ item 6。
- **★traits step 1 完了**（タグ `traits-t1`/`traits-t2`/`generic-free-fn`/`traits-t3`/`assoc-fn`/`traits-eq-ord`）＝**T1** trait 宣言＋`impl Type as Trait`（body/`via` witness・findMethod redirect）＋完全性チェック（暗黙準拠なし）。**T2** 提供メソッド `impl Trait`（各 Conform 型へ recv=Type 複製）。**T3a** generic free 関数の**呼び出し位置単相化**（`FnInst`・スコープ復元木探索で引数型推論・`writeFnSelector` が free 関数のみ型引数解決・戻り型置換）。**T3b** `where T: Trait` 境界（`FuncBound`・`checkFnBounds` が非準拠を loud reject）。**assoc fn**＝`assoc fn name(...)`（静的・self 無し・`Type.name(args)`・`findAssoc`/`assocRecvName`）。**Eq/Ord 配線**＝`== != < <= > >=` をユーザー型の `eq`/`compare` witness へ脱糖（`hasCompareWitness`/`emitTraitCompare`・Ord は Ordering タグ）。`any P` 存在型は未（item 7・最終）。
- **★traits 健全性ギャップ修正＋eager generic 型検査＋derive**（タグ `traits-gaps-124`/`generic-transitive`/`eager-generic-check`/`traits-gap-3`/`traits-gap-8`/`derive-eq-struct`/`derive-eq-enum`/`derive-ord-struct`）＝#1 `via` 先存在検査・#2 未知トレイト準拠 reject・#3 完全性をセレクタ単位（名前＋引数型・オーバーロード要求区別）・#4 Eq/Ord は `as Eq/Ord` 準拠ゲート・#6 transitive 単相化・#8 generic メソッドのインスタンス時境界 conformance（`checkMethodBounds`）・**#9 eager generic 型検査**（`checkGenericBodies`＝テンプレート本体を `where` 境界に対し1回検査＝C++ テンプレート脱却）・**#5 derive**（`@[Eq]` struct/enum＋`@[Ord]` struct＝最小ビルトイン・derived `Conform` は検査免除・option B〔`Ordering` 注入せず宣言要求〕）。残＝#7（据え置き）・`@[Ord]` on enum（loud な未対応）。
- **値意味論・generics・クロージャを有効化したまま自己ホスト不動点維持**。生成 C は警告クリーン。**コンパイラ自身がメソッド/match 式で自己記述**（dogfood）。

## ★ ロードマップ（generics → コアライブラリ → ランタイム）

意味論の hidden-meaning は大半解消済み（整数幅・match・ラベル・診断・受理の健全性チェックリストは [provisional.md](provisional.md) で全項解消）。残りは大物が中心。**拠り所「意味は最優先・コストは裏で後回し可」**：leak ランタイムは hidden-cost ゆえ後回し可。

1. ✅ **generics 完了**。✅ **generic free 関数も完了**（タグ `generic-free-fn`＝呼び出し位置で引数型から単相化・`FnInst`）。残 additive：明示 `id[I32](x)` の型引数指定（Go 式判別・今は推論のみ）・transitive 単相化（generic body 内からの generic 呼び出し＝worklist で fixpoint）・`map[U]`（メソッド own 型パラメータ）・generic 型引数の配列（`f[T]` に `Array[E]` を渡す）。
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
7. 🔄 **traits → closures → Iterator/Dictionary**（現在進行・ユーザー合意の順）。✅ **(1) traits コア＋Eq/Ord＋健全性ギャップ＋eager 型検査＋derive 完了**＝trait 宣言・`impl A as Trait`（body/`via`）・完全性チェック（セレクタ単位）・提供メソッド・`where T: Trait` 解決＋強制・generic free 関数単相化（transitive 含む）・assoc fn・Eq/Ord 演算子配線・**eager generic 型検査（#9・C++ テンプレート脱却）**・**`@[Eq]/@[Ord]` derive**（struct 全＋enum Eq）〔タグ `traits-t1`〜`derive-ord-struct`〕。残＝#7（明示型引数・据え置き）・`@[Ord]` on enum（loud な未対応）。→ 🔲 **(2) closure キャプチャ**（イベントループ第1段・Iterator コンビネータの前提＝外側ローカル参照キャプチャ・env＋fat closure・item 5 参照）→ **(3) 関連型＋Iterator/Iterable＋Hash/Dictionary/Set**（関連型で #9 を拡張）。`any P` 存在型は traits の重い尻尾＝最後。spec/08,12。
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
