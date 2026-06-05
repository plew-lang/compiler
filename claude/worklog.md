# 作業ログ

> 現在地・次の一歩・運用メモだけを置く。完了した「やった」は git 履歴へ（記述的タグで辿れる）。「なぜ」は [design-decisions.md](design-decisions.md)、「パイプライン設計」は [architecture.md](architecture.md)、「spec からの意図的剥離・暫定の仮決め」は [provisional.md](provisional.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で全パートを綴じ込む 1 モジュール＝`Loader`・`Lexer`・`Ast`・`Parser/`〔Expr/Stmt/Decl〕・`Codegen/`〔Emit/Resolve/Ops/Check/Expr/Stmt/Decl/Mono/Array/Async〕）。自分自身を不動点までコンパイルする。意味論の hidden-meaning（整数幅・match 網羅・ラベル・診断・受理の健全性・値意味論/CoW・`unique`/`deinit`/move・generics・トレイト＋Eq/Ord＋derive＋関連型・クロージャ）は概ね解消済み。**残る剥離・暫定は [provisional.md](provisional.md) が正典**。

- ✅ **イベントループ（async/await）段階 1-3**（spec/14・方式 B＝stackless ステートマシン・`Codegen/Async.pw`）。`async fn`（free）/`await`/`Promise[T]`/`sleep`（`@Std/Async`）が動く。残 tail（additive）：await-in-`for`・式中 await・async メソッド・generic async・String/struct 値 Promise・frame/Promise の ARC。根拠は design-decisions「async fn のローワリング」。
- ✅ **コアライブラリ境界**：`@Std/Io`・`Process`・`Async` は実 `.pw` の `extern "plew-intrinsic"` 宣言。lang item 型は `extern { struct I32 … }` で Core が宣言＝所有。`Format` トレイト＋全整数/Bool impl・`print` も純 Plew。機構は design-decisions「コアライブラリの境界」。
- ✅ **Array＝`RawBuffer` 床の上の Plew struct**（tag `array-plew-struct`・経緯/設計は [array-struct-plan.md](array-struct-plan.md)）：`struct Array[T] { data: RawBuffer[T]; pub(get) mut val count }` が C typedef を供給（`Array_E { E* data; uint64_t count }`）。append/get/set は floor intrinsics（`arrayPush/Get/Set/Len`＝Swift の Builtin 相当・deep-copy-aware ランタイム）上の純 Plew メソッド＝Swift の Array と同型。封じ込めで literal/index/for/値意味論/メソッドは kind-3 経路維持・`Array[U8]` のみ hand-written。**残ギャップ＝コレクション値意味論の一般化**（配列専用 deep copy/release ランタイムを `RawBuffer` 上の任意コレクションへ＝Dictionary/Set の前提）。
- ✅ **可視性 `export`/`import with`/`pub impl`/`pub`/`pub(get)` を spec 通り完全強制**（tag `visibility-enforced`・根拠は design-decisions「メンバ可視性＝impl ブロック単位」＋[[visibility-before-stdlib-grows]]）：①**モジュール可視性**＝loader の module identity（`moduleOf(offset)`）・`checkImports`〔import した名前は export 必須〕・`checkUseVisibility`〔import せず cross-module 関数使用を拒否〕。②**メンバ可視性**＝**impl ブロック単位 `pub impl`**（per-method `pub fn` 廃止）・フィールド per-field `pub`/`pub(get)`・private＝無名 impl のみ・トレイト準拠も `pub impl A as P`＝公開/無修飾＝内部。コンパイラは pub 大掃除で spec 準拠化。

## 🔄 着手中＝Iterator/Iterable（反復プロトコル・[[next-iterator-iterable]]）

基盤の関連型から進める順（ユーザー判断＝ダックタイピング for を先に作る手戻りを避ける）。
- ✅ **step 1＝関連型 `type Item`**：trait 宣言（`TraitDef.assocTypes`・`type Item` をパース）・impl 束縛（`type Item = Concrete`→`AssocBinding`/`Comp.assocBindings`）・**適合検査が要求の `Item` を束縛で置換**してから witness とセレクタ照合（`firstOr(fallback: Item)`＋`type Item=I64`→`firstOr(fallback: I64)` にマッチ）。同型が別 Item で複数準拠可。test `assoc_type`。AST 追加は全てデフォルト値付き＝構築点無改修。
- ✅ **step 2＝Iterator/Iterable トレイトを std に**（`@Std/Core`：`Iterator{type Item; inout next()->Optional[Item]}` / `Iterable{type Item; type Iter; iterator()->Iter}`）。trait 要求に `inout fn` を解禁（`parseTrait` に `Kind.KwInout`・適合はセレクタ一致で self-mode 非検査）。`Iter: Iterator[Item=Item]` の境界は未強制（additive）。
- ✅ **step 3＝`for` を一般 Iterable 適合で脱糖**（`Codegen/Stmt.compileIterableFor`）：`et.kind != 3`（配列でない）の for は `iterator()`/`next()` をダックタイピングで解決し `{ Iter __it = Recv_iterator(e); while(1){ Opt __o = Iter_next(&__it); if(__o.tag!=0) break; Elem var = __o.data.Some.v; body } }` を直接 C で吐く。Item は `next()` の戻り `Optional[Item]` の型引数から復元（`iterableItemInfo`＝check/mono/codegen 共有）。配列/レンジは fast-path 維持。test `iter_custom`・reject `for_not_iterable`。**併せて enum JSX 構築の型推論**：`<Optional.Some v=… />`（明示 `[I64]` なし）を return 位置の `curRetTy`（同名 generic enum）から instantiation 推論し mangled `Optional_I64` を吐く（`Expr.Make` の enum 枝）。**現状＝具体型のみ**（generic iterable／iterator struct の ARC drop は step 4 以降）。
- ✅ **step 4a＝generic iterable 対応**（`for val x in box`／`Box[I64]: Iterable`・iterator struct も generic）：`compileIterableFor`＝`groundUnderInst` で iterator/Item 型を iterand の instantiation 越しに解決（`Box[I64].iterator()→BoxIter[I64]`・その `next()→Optional[I64]`）。`iterableItemInfo`（check/mono 共有）も同様に chain 解決。test `iter_generic`。**前提＝nested generic field mono (G2a) と generic struct メソッド戻り値の instantiation 発見**：(1) `groundTypeRef`＝アクティブ env でフィールド型 `Array[T]→Array[I64]` を ground 化（typedef 欠落を解消・test `generic_array_field`）、(2) `scanGenInstFields` が struct メソッドの ret/param も env 下で scan＝`iterator()` の戻り `BoxIter[I64]` を登録→連鎖で `Optional[I64]` まで。
- 🔲 **step 4b＝Array/Range を Iterable に**（＋ ArrayIterator 等の iterator struct）。配列/レンジ fast-path は観測挙動を Iterable と一致させたまま残す。
- 🔲 **step 5＝提供メソッド** map/filter/reduce（`impl Iterator { }`・additive・generic iterator が前提＝4a で解決済）。

## ロードマップ（残りの大物・前向きのみ）

1. ✅ **Array struct 化**。次の収穫＝コレクション値意味論の一般化。
2. ✅ **可視性強制**。
3. 🔄 **Iterator/Iterable**（上記・着手中＝step 1 関連型 済）。
4. 🔲 **Hash/Hasher → Dictionary（`[k:v]` lang item）/Set**（要：コレクション値意味論の一般化）。
5. 🔲 **イベントループ tail＋spawn**（実スレッド・`JoinHandle[T]`・closure 残ギャップ）。
6. 🔲 **`any P` 存在型**（型消去・動的ディスパッチ・トレイトの最後）。
7. 🔲 **メタプログラミング**（`Derive`・コード生成・spec 上も最後）。

横断 additive：演算子トレイト全配線（Eq/Ord 以外・需要駆動）・循環回収（Ref グラフ限定サイクルコレクタ）。詳細は [provisional.md](provisional.md)。

## ビルド・テスト・機能追加手順

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust 不要）。`./bootstrap.sh --reseed` で種更新（→ `compiler/plewc.seed.c` を commit）。
- **テスト**：`./test.sh`＝`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/part/`（複数ファイル）＋`tests/reject/*.pw`（plewc 非ゼロ＝受理の健全性）＋`tests/panic/*.pw`（compile+link 成功・実行は非ゼロ＋`.panic` stderr 部分一致）＋不動点。メモリは `ASAN=1 ./test.sh`。
- **機能追加＝ADD→reseed→USE**：新機能を plewc.pw の**ソースで使う**には ①`compiler/src/` の codegen に足す（ADD）→ ②`--reseed` で種更新→ ③ソースで使う（USE）。「ソースが使う機能は常にひとつ前のコンパイラがサポート済み」を守れば不動点は壊れない。**新 preamble 行・codegen 出力変化・AST フィールド追加は reseed 2 回**（1 回目で挙動を種に焼き、2 回目で一致）。**ただし可視性検査のように codegen 出力を変えない検査追加は reseed 1 回で不動点**。
- **AST フィールド追加のコツ＝デフォルト値**：`val isPub: Bool = false` のようにフィールドにデフォルトを付けると、既存の `<Func …/>` 等の構築点が省略でそのまま通る（field default 構築が動く）＝多数の構築点を改修せず済む。可視性・関連型の AST 拡張はこれで churn を回避した。
- **⚠ 落とし穴＝コンパイラは `@Std/Io`→`@Std/Core` を import**するので、Core/Io/Process/**Prelude**（全プログラム自動ロード）も「コンパイラ自身がコンパイルするソース」。**そこに「種がまだ受理しない構文/機能」を足すと bootstrap が即壊れる**。回避＝**機能を先に種へ焼いてから Core/Prelude で使う**（ADD→reseed→USE）。**表現スワップ等の大変更は「旧コンパイラが新ソースを正しくコンパイルできるか」を seam（intrinsic 境界）で担保**（→ array-struct-plan.md「Bootstrap seam」）。

## 運用メモ

- 動作する区切りで**記述的 git タグ**（バージョン番号はまだ）。コミットメッセージは英語＋`Co-Authored-By`。GPG 署名（`--no-gpg-sign` を使わない・たまに pinentry タイムアウト＝再実行で通る）。
- **不要になった実装は削除し、必要なら git tag から復旧**（例：`git checkout stage0-final -- bootstrap`）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。
- C 予約語（`double` 等）と衝突する Plew 識別子は生成 C が壊れる＝名前マングリング未実装（コンパイラ自身は回避・ユーザーコードで顕在化＝[provisional.md](provisional.md)）。
- LLVM 化は当面しない＝意味論が揃ってから並行バックエンドとして追加（C は捨てない）。
