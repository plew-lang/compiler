# 作業ログ

> 現在地・次の一歩・運用メモだけを置く。完了した「やった」は git 履歴へ（記述的タグで辿れる）。「なぜ」は [design-decisions.md](design-decisions.md)、「パイプライン設計」は [architecture.md](architecture.md)、「spec からの意図的剥離・暫定の仮決め」は [provisional.md](provisional.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で全パートを綴じ込む 1 モジュール＝`Loader`・`Lexer`・`Ast`・`Parser/`〔Expr/Stmt/Decl〕・`Codegen/`〔Emit/Resolve/Ops/Check/Expr/Stmt/Decl/Mono/Array/Async〕）。自分自身を不動点までコンパイルする。hidden-meaning（整数幅・match 網羅・ラベル・診断・受理の健全性・値意味論/CoW・`unique`/`deinit`/move・generics・トレイト＋Eq/Ord＋derive＋関連型・クロージャ）は概ね解消済み。**残る剥離・暫定は [provisional.md](provisional.md) が正典**。

完了した大物（詳細は git・記述的タグ）：
- ✅ **イベントループ（async/await）段階 1-3**（spec/14・stackless ステートマシン・`Codegen/Async.pw`）。残 tail は additive（await-in-`for`・式中 await・async メソッド・generic async・frame/Promise の ARC）。
- ✅ **コアライブラリ境界**：`@Std/{Io,Process,Async,Core}` の `extern "plew-intrinsic"`・lang item 型は Core 宣言・`print`/`Format` も純 Plew。
- ✅ **Array＝`RawBuffer` 床の上の Plew struct**（tag `array-plew-struct`・[array-struct-plan.md](array-struct-plan.md)）。残ギャップ＝コレクション値意味論の一般化（Dictionary/Set の前提）。
- ✅ **可視性 `export`/`import with`/`pub impl`/`pub`/`pub(get)` 完全強制**（tag `visibility-enforced`）。
- ✅ **Iterator/Iterable ＋ lazy コンビネータ完成**（下記）。
- ✅ **再帰値型の auto-boxing 完成**（下記）。

### ✅ Iterator/Iterable ＋ lazy map/filter（完了・[[lazy-iterators-direction]]）

反復プロトコル（`Iterator{type Item; inout next()->Optional[Item]}` / `Iterable`）＋ `for` 脱糖、lazy な `map`/`filter` を `@Std/Core` で提供。`for v in xs.map(f).filter(p)` が**任意の順で連鎖**でき、**複数行チェーン**（改行前 `.`）も可。test 群 `iter_*`/`generic_*`。途中で additive に積んだ再利用機構（＝今後も効く資産）：

- **クロージャ型 struct フィールド呼び出し**（`recv.f(args)`・`emitClosureFieldCall`）。
- **impl レベル `where`**（`impl[I] T[I] where I: Iterator`＝各メンバ funcBounds に畳む）。
- **構造的型推論**（`unifyTypeParam`）＝型変数が `fn(x:Item)->B` 等に埋まっていても取り出す。クロージャ型回復＝`closureFnTypeRef`。
- **method-level 型パラメータ**（`map[B]`）＝generic method を **(receiver inst, method-own 引数) ごとに単相化**（`FnInst.recvInstRef`・`registerMethodInst`・mangle suffix は method-own tail のみ）。
- **Self/Item 型解決**（`curSelfRef`/`curItemRef`＋`resolveTy`）。`Item` 解決は Iterator メソッド env 下のみ＝ユーザー型名 `Item` 不破壊。
- **demand-driven 単相化（＝理想）**：提供 self-returning は無限型族（`FilterIter[FilterIter[…]]`）。戻り adapter inst が到達可能なときだけ発行（`providedRetReachable`）。
- **nested generic field の ground 化**（`groundTypeRef`）・instantiation の env 越し解決（`groundUnderInst`）。
- **罠の知見**：型パラメータ名 vs 具体型名のグローバル衝突（ユーザー struct `B` と `MapIter[…,B]` の `B`）→ `isTypeParamName` は宣言済 struct/enum 名を具体型扱い。提供メソッドを generic 準拠型に載せるときテンプレート扱いで scan skip（ゴミ inst 防止）。

残 additive（Iterator）：`reduce`/`fold`/`take`/`enumerate`/`zip`・`String` 出力 map（`String: Format` 要）・Array/Range を Iterable に。

### ✅ 再帰値型の auto-boxing（完了・spec/03「再帰する値型」）

`enum List { Cons(head, tail: List) Nil }` / `struct Node { next: Optional[Node] }` が**有限で定義・構築・反復**できる。循環を閉じるフィールドだけをコンパイラが裏で `T*` にヒープ間接化する hidden cost（明示 `Box`/`indirect` なし）。値意味論は box 越しでも保つ（コピー独立）。

- **検出**＝`markBoxedFields`（`Mono.pw`・`Comp.boxedFields`＝field の `nameStart` キー）：concrete struct/enum の到達可能性ウォークで back-edge を閉じる**ユーザー型側フィールド**を box。`Array`/`RawBuffer`/`Ref`/`WeakRef` は cut（既に間接）・`Optional`/`Result` は透過して引数を辿る（だから Optional 自体は box せず＝hardcoded `.data.Some.v` を温存）。
- **codegen**＝そのフィールドだけ `T*`（`genStructDef`/`genEnumDef`）・構築は `genBoxCell`（`malloc`＋値コピー＋`curRetTy=fd.ty` で nested JSX を mangle 推論）・読みは deref コピー（`Expr.Field`／match payload bind の両所）・代入は **fresh box に repoint**（共有セルを in-place 変更しないので値意味論が成立）。
- **横断修正**：`fieldType` が generic-inst フィールドの `ref` を載せる（field の match が `Optional_Node` を復元）。`structNeedsCopy`/`structNeedsRelease`/`emitStruct{Copy,Share,Release}Def`/`typeIsTransitivelyUnique` は **boxed フィールドを skip**（plain 共有ポインタ＝managed copy/release 不要・かつ `struct A{a:A}` の無限再帰ウォークを断つ＝segfault 回避）。
- **残（additive）**：box セルの **ARC 解放未配線＝leak**（観測挙動は正しい・短命プロセスで無害）→ share=retain/release=deref-free の CoW box へ。**終端なし循環**（`struct A{a:A}`）は構築不能だがクラッシュせず通る＝loud reject は将来。
- テスト＝`rec_list`/`rec_struct_optional`/`rec_tree`/`rec_mutual`/`rec_value_semantics`。

## 🔄 次の大物＝メタプログラミング基盤（設計確定済）

正典＝spec/16、実装計画＝[metaprogramming-architecture.md](metaprogramming-architecture.md)。確定方針：
- マクロ＝`Derive` 実装 struct・**入力 `TokenStream`（span 付き・入力エラー用）／出力 `String`（生成ソース・出力エラーは `.gen.pw`）**・`quote` 等の埋め込み構文は作らず普通の Plew 文字列＋補間で組む。
- ディレクティブ引数＝マクロ struct のフィールド（`@[Name(a: 32)]`＝`Name{a:32}.derive(input)`）。
- 別コマンド `plew gen` で `<Foo>.gen.pw` 生成（コミット・**原本不変・add-only**）。取り込みは **`@[...]` の存在でローダ自動 part**（同一パッケージ derive 可・gen 中は auto-part 抑制）。
- リッチ AST＝**値ツリーを `@Std/Syntax` に切り出し**（型宣言だけ先・コンパイラもマクロも import・パッケージ管理不要・後でパッケージ化容易）。組み込み Eq/Ord/Hash は当面コンパイラ特権で将来 dogfood。
- **実装順**：①機構（`TokenStream`＋parse ヘルパ→値ツリー `DeriveInput`・span エラー関数）→ ②`plew gen` → ③コアライブラリ derive を dogfood（**Hash はここ**→Dictionary）→ ④パッケージ管理後にライブラリ昇格。

## ロードマップ（残りの大物・前向きのみ）

1. ✅ Array struct 化・✅ 可視性強制・✅ Iterator/Iterable＋lazy map/filter・✅ 再帰値型 auto-boxing。
2. 🔄 **メタプログラミング基盤**（設計確定・上記の実装順 ①→④）。値ツリー AST の前提（再帰型）は整った。
3. 🔲 **Hash/Hasher → Dictionary（`[k:v]` lang item）/Set**（メタプロ③で `@[Hash]` を出してから・要：コレクション値意味論の一般化）。
4. 🔲 **イベントループ tail＋spawn**（実スレッド・`JoinHandle[T]`・closure 残ギャップ）。
5. 🔲 **`any P` 存在型**（型消去・動的ディスパッチ・トレイトの最後）。

横断 additive：Iterator 拡充（reduce/take 等）・演算子トレイト全配線（Eq/Ord 以外・需要駆動）・循環回収（Ref グラフ限定サイクルコレクタ）。詳細は [provisional.md](provisional.md)。

## ビルド・テスト・機能追加手順

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust 不要）。`./bootstrap.sh --reseed` で種更新（→ `compiler/plewc.seed.c` を commit）。
- **テスト**：`./test.sh`＝`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/part/`（複数ファイル）＋`tests/reject/*.pw`（plewc 非ゼロ＝受理の健全性）＋`tests/panic/*.pw`（compile+link 成功・実行は非ゼロ＋`.panic` stderr 部分一致）＋不動点。メモリは `ASAN=1 ./test.sh`。
- **機能追加＝ADD→reseed→USE**：新機能を plewc.pw の**ソースで使う**には ①`compiler/src/` の codegen に足す（ADD）→ ②`--reseed` で種更新→ ③ソースで使う（USE）。「ソースが使う機能は常にひとつ前のコンパイラがサポート済み」を守れば不動点は壊れない。**新 preamble 行・codegen 出力変化・AST フィールド追加は reseed 2 回**、**codegen 出力を変えない検査追加は reseed 1 回**。
- **AST フィールド追加のコツ＝デフォルト値**：`val isPub: Bool = false` のようにフィールドにデフォルトを付けると既存の構築点が省略でそのまま通る＝多数の構築点を改修せず済む。
- **⚠ 落とし穴＝コンパイラは `@Std/Io`→`@Std/Core` を import**するので、Core/Io/Process/**Prelude**（全プログラム自動ロード）も「コンパイラ自身がコンパイルするソース」。種がまだ受理しない構文/機能を足すと bootstrap が即壊れる＝**機能を先に種へ焼いてから Core/Prelude で使う**（ADD→reseed→USE）。表現スワップ等の大変更は seam（intrinsic 境界）で担保（→ array-struct-plan.md）。

## 運用メモ

- 動作する区切りで**記述的 git タグ**。コミットメッセージは英語＋`Co-Authored-By`。GPG 署名（`--no-gpg-sign` を使わない・たまに pinentry タイムアウト＝再実行で通る）。
- 不要になった実装は削除し、必要なら git tag から復旧（例：`git checkout stage0-final -- bootstrap`）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。
- C 予約語（`double` 等）と衝突する Plew 識別子は生成 C が壊れる＝名前マングリング未実装（[provisional.md](provisional.md)）。
- LLVM 化は当面しない＝意味論が揃ってから並行バックエンドとして追加（C は捨てない）。
