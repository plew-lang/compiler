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

## 🔄 着手中＝コンパイラ負債監査の結論：RENOVATE（rewrite せず段階改修）

**監査済（2026-06-05・5 サブシステム並行精査）。結論＝全領域 RENOVATE 一致**（rewrite は不採用）。「表現力が貧弱な時代の設計」由来の負債は実在するが**局所的・legible・増分修正可**、意味論は正しく高価な資産。詳細根拠は本節に集約（design-decisions の「なぜ rewrite しないか」も兼ねる）。

- **根① 型付き IR が無い**（最大）：型は codegen 中に `exprType` が AST を歩いて都度復元（74 箇所・未対応は scalar 落ち `Resolve.pw:1014,1502`）。帰結＝emission 順序が正しさの前提・3 パス＋codegen が別々に再導出・復元外れで健全性チェック黙過・**単相化が codegen 全体のモード化**（149 touchpoints・発見 walk が束縛ロジックを ~300 行二重実装）。
- **根② 名前がソースバイトオフセット**（symbol table 無し）：`spansEqual`/`rangeEquals` 259 箇所・`kwSpan` がソース全検索＋偽コメント植え（`_.pw:151`）・`appendMangle` がソース buffer に書込み・Loader が全ファイル 1 buffer 連結（モジュール隔離なし）。
- **集中重複③ ARC 4 重複**（struct/enum×concrete/mono・分類カスケード ~6 回再実装・mono-struct share/release 欠落＝leak）。**enum の `mode` 引数版が正解形**。**局所④** 演算子 opcode が手番 magic 整数（`kindCode`・`op==57` 素マッチ）→`Op` enum 化で解消。**局所⑤** パーサが codegen 仕事（mangle 書込み・arrayElems 種まき・型 triple/ref 二重表現）／derive 合成 ~280 行がパーサ内／tolerant パース（無ければ黙って進む＝受理健全性を損なう・`expect()` 不在）／最初のエラーで `exit(1)` 回復なし。
- **綺麗な所（honesty）**：意味論は全て正しい＝ARC scope-drop・async stackless SM（UAF 対策/仮想時計/loud reject）・checked 算術・RawBuffer 床・需要駆動単相化＋combinator 到達性ゲート・再帰 boxing 解析・パターン/優先順位パース。不動点 self-host が稼働・ドキュメント規律が高い＝**読める負債**ゆえ renovate が効く。
- **renovation が届かない唯一＝ソース連結モジュールモデル**（Loader＋`*Start/*Len` span 規約）。分割/incremental compile はここを触らないと不可だが Loader に隔離・**分割コンパイルが要るまで後回し**。
- **なぜ rewrite でなく renovate**：①高価で正しい意味論（`unique-*` 等の長いエッジケース蓄積）を捨てて踏み直すことになる（Joel 典型）②不動点の安全網を長期間失う（renovate は各ステップ緑）③2 つの根は再帰値型が動く今だからこそ増分で剥がせる。
- **ロードマップ**（メタプロと合流）：
  - **Phase A✅（クイックウィン・完了）**：①**ARC エミッタ 1 本化**＝`emitFieldAction`（concrete struct/enum 共有・unique-deinit 込み）＋`emitMonoFieldAction`/`emitMonoModeDef`（mono struct/enum 共有）に集約。旧 `emitStruct{Copy,Share,Release}Def`・`emitMono{Struct,Enum}Copy*`・`emitMonoEnumMode*` を削除。**mono-struct の share/release を新設＝documented leak を解消**（`monoStructNeedsRelease`＋driver＋scope-drop 配線）。「heap フィールド種を足す＝2 dispatcher を触るだけ」に。②**演算子 magic 数を named helper 化**＝`opAdd()..opCoalesce()`（`Ops.pw`・`kindCode(<Kind.X/>)` が単一の源）で `op == 57` 等を全置換。③**`expect()` パーサヘルパ**＝tolerant な「無ければ黙って進む」を mandatory トークンで loud reject に（`)`/`=`/`]` を変換・reject テスト 3 本追加・残サイトは additive）。**全部 behavior-preserving＋不動点維持・suite 236/0**。
  - **Phase B🔄（最大レバレッジ）＝型付き AST**（着手中）。根①（codegen 中の `exprType` 都度復元）を「読む」へ反転。
    - **B0✅＝kwSpan ハック除去**：型名のソース全検索＋偽コメントを `buildKwCache`（既知オフセットへ 1 回並べ O(1)）に。
    - **B1✅＝`typeOf` キャッシュ seam**：`typeOf(c,id)` を導入し codegen 出力地点（Expr/Stmt/Ops の 32 箇所）を移行。ノード型を `Comp` の **4 並列 scalar 配列**にキャッシュ（self-host は struct 配列 IndexSet 非対応ゆえ）。**`typeCacheable()`＝純粋 free function 文脈のみキャッシュ**（型パラメータ/recv/Self/Item/recvInstRef 全部無し）＝env 非依存＋本体 1 回 emit。**メソッド/generic/provided 本体は除外**（provided trait メソッドは 1 body を準拠型ごとに emit＝Self で型が変わる）→ 初版で全メソッド文脈をキャッシュし trait_provided/trait_where が壊れたのを gate で修正。behavior-preserving・236/0（output＋ASan）・不動点。
    - **B 次の一歩**：①free-fn キャッシュを **pre-fill パス**化（codegen を pure-read に）→ ②generic 本体を**テンプレート型 TypeRef** で持ち読み出し時 ground（案B）→ ③`exprType` 再導出駆逐。
    - **設計メモ**：案A（名前解決パス）は**挟まない**＝B が内包（型付けにスコープ解決が要る）・A 単体は消費者が無く検証弱／B はノード型を codegen が読む＝不動点で検証可。スコープ走査の codegen 一致が唯一の難所。
  - **Phase C**：名前 interning（`spansEqual` 一掃）・`MonoEnv` 明示パラメータ化 → **`@Std/Syntax` 値ツリー AST＝この型付き AST**としてマクロへ公開（＝メタプロ土台に合流）。
  - **deferred**：分割コンパイル（Loader 連結モデル）。
- **先日の Phase 0（box ARC）は依然有効**＝AST を再帰値型に載せる前提。**次の着手＝Phase A（ARC 1 本化から）**を推奨。

---

### （旧・参考）メタプロ基盤の前段：値ツリー AST 化（box ARC は上記 renovate に吸収）

ユーザーと方針合意（2026-06-05 セッション）。**マクロには AST を全部公開する**（関数本体まで＝手続き的マクロの将来も塞がない・「全公開のデメリットは本質的に無い、コストは refactor だけ」）。ただし**「全公開」と「codegen 全書き直し」は別物**＝以下の lowering shim で安全に到達する。

- **「源を1つ」＝二重パーサ（syn/rustc 問題）回避**：パーサも AST 型も **`@Std/Syntax` に一本化**し、コンパイラはそれを import。
- **codegen は温存**：`@Std/Syntax` の値ツリー →（lowering 一段）→ 既存 arena に落として、~8k 行の codegen を書き直さない。lowering は標準的な surface-AST→IR の一段で、二重パーサにはならない。後から構文ごとに lowering を削って**純粋な値ツリー codegen へ段階収束**できる（不動点を保ったまま・急がない）。
- **段取り（不動点を緑に保つ増分）**：
  - **Phase 0✅＝box の ARC 解放を配線（完了）**。box＝`plew_arc_alloc` の rc ヘッダ付きセル・copy/share は `plew_ref_share` で retain・書換えは fresh box に repoint(rc=1)・release は rc 減算→0 で pointee 再帰 release＋free。**enum（concrete＋mono）に copy/share/release を新設**＝struct 版を enum へミラー（`enumNeedsCopy/Release`・`monoEnumNeedsRelease`・`emitEnumModeDef`・`emitMonoEnumModeDef`・`typeInfoNeedsCopy/Release`・`fieldNeedsCopy/Release`）。mono enum release proto は struct defs より前に emit（struct release が boxed generic-enum 場の release を呼ぶため）。**構築は retain-on-place**＝`genExpr`→`genCopyValue`（場の値を埋め込むとき share・fresh 値は直接＝二重 release を防ぐ・`genCopyValue` に concrete-enum share を追加）。local scope 末 release を concrete/mono enum local へ拡張。**検証**＝5 再帰テスト output＋ASan clean・5000 ノードの build/copy/sum stress で **0 leaks**（macOS `leaks`・ASan は Darwin で leak 非対応ゆえ `leaks` 併用）・全 suite 233/0（output＋ASan）・不動点 OK（reseed 2 回）。残リークは print/String が ARC 未解放な既存ギャップのみ（box 由来は 0）。
  - **Phase 1＝`@Std/Syntax`**：Token/Span・TypeExpr・Decl（FnDecl 含む）・Expr・Stmt を再帰値型で全定義＋手書き lexer/parser を移植して値ツリーを吐く。
  - **Phase 2＝コンパイラが採用**：`lower(値ツリー)→arena` を足し既存 codegen 温存。**ここで「源1つ・両者が使う・関数本体まで公開」成立。**
  - **Phase 3＝マクロ＋`plew gen`** を実 AST 上に（使い捨て DeriveInput なし）。Eq/Hash dogfood→Dictionary。
  - **Phase 4（任意）＝lowering を構文ごとに削り**値ツリー直走り codegen へ収束。
- ⚠ **Phase 0 完了で一旦停止して方針相談**（ユーザー指示）。

> 旧メタプロ詳細（TokenStream 入力前提・spec/16）は上の方針で見直し予定：入力は span 付き構造化値ツリーになり生 TokenStream 再パースが不要化する見込み（@Std/Syntax を組んでから判断）。正典＝[spec/04-execution/16-metaprogramming.md](../spec/04-execution/16-metaprogramming.md)、計画＝[metaprogramming-architecture.md](metaprogramming-architecture.md)。

## ロードマップ（残りの大物・前向きのみ）

1. ✅ Array struct 化・✅ 可視性強制・✅ Iterator/Iterable＋lazy map/filter・✅ 再帰値型 auto-boxing。
2. 🔄 **メタプロ基盤＝値ツリー AST 化**（上記・Phase 0 box ARC 実装中→Phase 1-3 @Std/Syntax＋lowering＋マクロ）。
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
