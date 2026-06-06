# 作業ログ

> 現在地・次の一歩・運用メモ・再利用資産だけを置く。完了した「やった」は git（記述的タグ）へ。「なぜ・却下案」は [design-decisions.md](design-decisions.md)、パイプライン設計は [architecture.md](architecture.md)、spec からの意図的剥離・暫定は [provisional.md](provisional.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で全パートを綴じる 1 モジュール＝`Loader`・`Ast`・`Parser/`〔Stmt〔型パーサのみ〕/Decl〕・`Codegen/`〔Emit/Resolve/Ops/Check/Expr/Stmt/Decl/Mono/Array/Async/Gen/Lower〕）。**レクサと式・文パーサは `@Std/Syntax` に移し本体は共有経路で parse→`Codegen/Lower.pw` で arena へ lower**（メタプロと同一・ドリフトなし＝A Phase 1+2）。自分自身を不動点までコンパイル。hidden-meaning（整数幅・match 網羅・ラベル・受理の健全性・値意味論/CoW・`unique`/`deinit`/move・generics・トレイト＋Eq/Ord＋derive＋関連型・クロージャ）は概ね解消。**残る剥離・暫定は [provisional.md](provisional.md) が正典**。

完了した大物（詳細は git・記述的タグ）：async/await 段階 1-3（stackless SM）・コアライブラリ境界（`@Std` の `extern "plew-intrinsic"`）・**Array＝`RawBuffer` 床の Plew struct**（[array-struct-plan.md](array-struct-plan.md)）・可視性完全強制・**Iterator/Iterable＋lazy map/filter**・**再帰値型 auto-boxing＋ARC**・**コンパイラ renovate Phase A**（ARC 1 本化・Op enum・expect）・**Phase B B0-B2**（型付き AST キャッシュ）・**D quick-wins**（Loader 掃除・expect 仕上げ）。renovate vs rewrite の判断・負債の地図は [architecture.md](architecture.md)「負債監査の結論」、言語設計の根拠は [design-decisions.md](design-decisions.md)、再利用機構は本書末尾「再利用資産・罠」。

## A（フロントエンド統合）Phase 1+2 済・式文は完全 1 本化（2026-06-06）

**ユーザー指示＝A を進める。** Phase 1＝コミット済（244/244・不動点維持）：
1. **codegen の nominal body emit を依存順（トポロジカル）化**（`emitNominalBodiesTopo`／`Codegen/Decl.pw`）＝commit `ded0f4a`。実バグ修正（`enum E { A(s: Struct) }` が不完全型でコンパイル不可を解消）かつ A の土台（値ツリーを enum で書ける）。
2-4. **共有値ツリー＋ボディパーサ**＝commit `5a76a94`：`@Std/Syntax/Trees.pw`（`ExprAst`/`StmtAst`/`PatternAst`/`BlockAst` 等・enum・String 名・原本座標 Span）／`@Std/Syntax/ParseBody.pw`（式・文・パターン・ブロックを `Parser/Expr.pw`+`Stmt.pw` どおりミラー・`*Ast` 接尾辞で本体と衝突回避・`export parseExprAst`/`parseBlockAst`/`parseExprFrom`/`parseBlockFrom`）／`parseFuncDecl` が関数本体を実パース（`DeclAst.body: BlockAst`＝マクロが本体を読める）。単体検証済。

**Phase 2＝式・文の統一＋旧パーサ削除＝✅達成**（2026-06-06・245/245・不動点維持）。コンパイラ本体は**全ての式・文・パターン・本体・デフォルト式・ディレクティブ引数を共有 @Std/Syntax パーサで parse → `Codegen/Lower.pw` で arena へ lower**する。ドリフトの主因（演算子優先順位等の式・文文法）は完全に 1 本化。コミット列：
- `4c2793d`＝関数本体を共有経路に（`parseBlock` が `parseBlockAst`+`lowerBlock`・`Codegen/Lower.pw`＝`lowerExpr/Stmt/Block/Pattern/Type`・Call 名/文字列は原本 offset・他は再インターン）。共有 `parseType` に関数型 `fn(...)->R`、`P` にエラー記録（`hasErr`/`errOff`/`errMsg`+`fail`）追加＝missing `)`/`]`/`=`・非結合比較・multiscalar char を本体が報告。
- `55ec756`＝フィールド/引数デフォルト式・ディレクティブ引数も共有経路（`parseExprC`）。
- `0541bd8`＝**旧式・文パーサを削除**（`Parser/Expr.pw` 全削除・`Parser/Stmt.pw` は型パーサ〔parseTypeTok/parseTypeParams/recordArrayElem〕のみに・~700 行減）。

**A の残り＝宣言/トップレベルの統合（ユーザー判断＝やり切る・大物・別エフォート向き）**：コンパイラの `parseProgram`＋`Parser/Decl.pw`（parseStruct/Enum/Func/Impl/Trait/Extern/Import/Export/Directive）はまだ本体独自。マクロ用の共有宣言パーサ（`@Std/Syntax/Parser.pw`＝DeclAst）と二重。**式・文と違い綺麗な単一切替点がなく all-or-nothing**（`parseProgram` が多形へ分岐）。~2000 行規模。

**着手済（土台）**：
- ✅ 共有 DeclAst が**デフォルト式を捕捉**（`FieldAst/ParamAst.defaultVal: ExprAst`・commit `abf9758`）＝メンバワイズ factory の default に必要。
- ✅ **A-1＝struct/enum を共有パーサ＋lowerDecl へ統合・旧 parseStruct/parseEnum 退役**（245/245・不動点維持）。`DeclAst` に `nameSpan`/`hasDeinit`/`deinitBody` 追加（共有 parseStructDecl が deinit を実捕捉）。`Codegen/Lower.pw`＝`lowerDecl`/`lowerStructDecl`/`lowerEnumDecl`/`lowerFieldDef`/`lowerTypeParamNames`＋ブリッジ `parseDeclItem`（共有 `parseDecl` を本体トークン列で駆動→arena へ lower）。`parseProgram`/`parseExport` の struct/enum を routing。名前は再インターン（struct/enum 名は `moduleOf` に不参加＝型は ambient／export の fieldStart は never-read ゆえ byte 同一で安全）。診断移植＝enum brace payload・struct comma を `P.fail` で。
- ✅ **A-2＝free fn（`fn`/`async fn`/`export fn`）を共有パーサ＋lowerFuncDecl へ・旧 parseFunc 退役**（245/245・不動点維持）。`DeclAst` に `isAsync`/`whereParams`/`whereTraits` 追加（共有 parseFuncDecl が where 句を実捕捉）。`lowerFuncDecl`＝関数名は**原本 offset 維持**（`d.nameSpan`＝`moduleOf`→checkUseVisibility のため再インターン不可）・where→FuncBound（text 一致ゆえ再インターン安全）。`lowerParams` がデフォルト引数式を lower。診断移植＝inline trait 制約 `[T: Trait]`。
- **A-3（impl）着手中**：impl はディスパッチ点が 1 つ（`impl`/`pub impl`）ゆえ共有 impl パーサは**全機能を一度に**支える必要。不動点が要求＝pub impl・generic `impl[T]`・`as Trait`・impl-level where・inout/move/async fn・assoc fn・`type Item = B`。テストのみ＝via・deinit-in-impl・bare impl・borrow fn。impl 系の名前は全て `moduleOf` 不参加＝再インターン安全。**残り＝impl → trait/extern/import/export。**

**残り手順（各段 additive 緑→最後にスワップ）**：
1. **DeclAst を完全 fn シグネチャへ拡張**：`isAsync`/`isPub`/`isAssoc`/`recv`（レシーバ型・メソッド用）/`selfMode`（fn/inout fn/move fn）/`isExtern`/`where` 句。共有 `parseFuncDecl` でパース。マクロも完全 fn を読める（additive 価値）。
2. **新トップレベル値ツリー＋パーサ**：`ImplAst`（レシーバ＋generic params＋conformance〔`impl A as Trait`〕＋`via` alias＋メソッド〔DeclAst func〕＋isPub）／`TraitAst`（supertraits＋要求）／`ExternAst`（intrinsic 宣言列）／`ImportAst`/`ExportAst`/`PartAst`（パス＋with リスト）／directive（`@[...]`）。`parseProgramAst -> Array[TopItemAst]`。struct の `deinit` も共有側で。
3. **宣言 lower**（`Codegen/Lower.pw` 拡張）：DeclAst→StructDef/EnumDef/Func、Impl→メソッド（recv 付き Func）＋Conform＋MethodAlias、Trait→TraitDef、Extern→Func（isExtern）、Import/Export→`c.imports/exports`（**module tagging＝原本 offset で `moduleOf` を効かせる**）、Directive→`pendingDerives`/drainDerives。codegen 播種（`recordArrayElem`）は lowerType が既に実施。
4. **`parseProgram` を共有 parse+lower にスワップ**。**診断移植が要点**：`Parser/Decl.pw` の専用エラー（「struct フィールドはカンマでなく改行」「enum ペイロードは括弧」「inline trait 制約不可」等）を共有パーサの `P.fail` 機構へ全部移植（reject スイートが落として強制＝漏れは tests/reject が検出）。
5. **`Parser/Decl.pw` の parse 部退役**（derive 合成 ~280 行は codegen として残す）。完成で真の 1 AST。

**注意**：lower の module tagging と derive を間違えると cross-module 可視性/derive が壊れる（テストが概ね捕捉するが慎重に）。スワップは緑＋不動点でなければ revert。

**Phase 2 着手時にまとめて決める暫定判断（M1 自走中の宿題）**：
- **`DeclAst` を enum へ戻す**：現状はタグ付き struct（`kind: DeclKind` ＋未使用フィールド空）。当初は codegen バグ（enum が struct を値で持つと不完全型）回避のためだったが、そのバグは Phase 1 の topo emit（`ded0f4a`）で解消済＝技術的に `enum DeclAst { Struct(StructDecl) … }` へ戻せる。**戻すと gen テスト6件の macro API が churn**（`d.kind` の match → `match d`）するので、手順5 で値ツリーを整える際に一括で enum 化するのが筋（個別にやらない）。
- **共有パーサの現スコープ**：宣言＋本体（式/文/パターン）は実装済。**未対応＝トップレベルの impl/trait/extern/import/export/part のみ**（＝手順5 そのもの）。`parseFuncDecl` は body を実パース済だが、フィールド/引数のデフォルト式は依然 skip（presence フラグのみ）・`fn(...)->R` 型式は bare 名に潰している＝lower で本体と突き合わせる際に補完要否を判断。
- **`Src` 出力ビルダの API 形状**（`Src`/`newSrc`/`put(text~:)`/`putByte(b~:)`/`putInt(n~:)`/`finish()`）は additive で容易に変更可。マクロを実運用して不満が出たら改名/拡張。今は確定不要。

## 次の一歩＝M1 コア達成後の選択（M0・M1 コア済）

**M1 コア＝✅達成**（直下「M1 の現状」参照・tag `metaprogramming-m1`・244/244 緑）。次の大きな分岐は **(a) M1 の理想完成（本体フロントエンドを共有パーサへ統合＝真の 1 AST・重複パーサ退役）／(b) 構文層を式・文・パターンまで拡張（マクロが関数本体を読める）／(c) M2 dogfood（Eq/Hash をマクロ化→`Dictionary`）** の 3 つ。
- **(a) は不動点 byte 同一性の制約が重い**＝慎重な増分が要る（壊すと回復に時間）。
- **(c) は `Hash`/`Hasher` の署名が未策定（core-lib 送り・言語/ライブラリ判断）**＝着手前にユーザー確認向き。
- いずれも「順序の委任」を超える分岐なので、再開時にユーザーと方向を確認するのが安全。下記は M1 の入力モデル確定メモ（参考）。



**入力モデル確定＝AST 入力**（当初の TokenStream から変更）。正典＝[spec/04-execution/16-metaprogramming.md](../spec/04-execution/16-metaprogramming.md)、実行系の段取り＝[metaprogramming-architecture.md](metaprogramming-architecture.md)。要点：

- **`Derive` トレイト＝要求 `derive(input: AST) -> String`（ユーザー）＋提供 `deriveFromSource(source, span)`**（構文ライブラリが String→AST 変換＋委譲＝中間 dispatcher 層は不要）。
- **ランナー（`plew gen`）＝String↔String の版非依存な機械**：`@[Name(args)]` ごとにハーネス（`<Name args/>.deriveFromSource(...)` を `write` する `main`）を合成→compile→別プロセス run→stdout を `<Foo>.gen.pw` へ。**版固定はハーネスがリンクする固定 `@Std/Syntax` で自然成立**（ランナーは AST 型に触れない）。
- **構文ライブラリ＝当面 `@Std/Syntax`（in-tree）・最終形は外部共有パッケージ**（コンパイラもマクロも同一版に依存＝Rust の 2 パーサ/AST 版違い問題を回避）。生トークンは将来 escape hatch（関数形/DSL マクロを入れる時のみ）。
- 出力モデル：`<Foo>.gen.pw` コミット・原本不変・add-only、`@[...]` でローダ自動 part（gen 中は抑制）。

**M0＝済**（tag `metaprogramming-m0`）。`plewc --gen <file>` モード＋`@Std/Syntax`（最小）＋ローダ auto-part＋`plew-gen.sh`＋`tests/gen/`。自明マクロ（固定文字列を返す）が `@[Greet]`→harness→`Greet.deriveFromSource`→`App.gen.pw`→通常ビルドで auto-part→生成関数実行、まで端から端まで貫通。実装メモは末尾「再利用資産・罠」の gen 項。

**M1＝`@Std/Syntax` の本実装＝構文層を共有コアへ切り出し（射程確定済）。** 理想形の正典は [metaprogramming-architecture.md](metaprogramming-architecture.md)「理想形（最終状態）」。下は確定した進め方。

## M1 の現状（2026-06-06）＝マクロが実宣言を読める＝達成 🎉

**M1 のコア機能は完成**：`@[Name]` マクロが `derive(input: DeclAst)` で**対象宣言の実構造**（型名・フィールド名/型/可視性・enum バリアント/ペイロード・fn シグネチャ・ジェネリクス）を読んで生成できる。さらに**ディレクティブ引数 `@[Name(label: expr)]`** も実装＝マクロ struct のフィールドに渡り `self.label` で読める（`parseDirectiveArgs`・`DeriveReq.args`・synthGenMain が `<Name label=expr/>` 構築）。テスト `tests/gen/fieldnames`（`@[FieldList] struct Point{x,y,z}`→`"x,y,z,"`）と `tests/gen/directiveargs`（`@[Tagged(prefix:"hi",times:3)] struct Widget`→`"hi-hi-hi-Widget"`）が end-to-end で緑（240/240・不動点維持）。

**実装済（下の確定手順のうち）**：1（レクサ一本化＝`@Std/Syntax/Lexer.pw`・本体は import）／2（値ツリー AST＝`@Std/Syntax/Ast.pw`＝Span/TypeAst/FieldAst/VariantAst/ParamAst/DeclAst＋DeclKind）／3 の**宣言サブセット**（`@Std/Syntax/Parser.pw`＝struct/enum/fn シグネチャ＋型式）／5（parseItem 本物化＝ハーネスが対象項の実ソースをエスケープ埋め込み＋原本オフセットを base に渡す＝`DeriveReq.declStart/declEnd`・`internSourceLiteral`）。

**順序を組み替えた**：マクロ前進を最優先し **1→2→3(宣言)→5** を先に通した（手順4＝本体フロントエンド差し替えは未着手）。理由＝parseItem は arena と独立なので、本体フロントエンドを触らずにマクロが動く。最終到達点（1 AST・重複パーサ解消）は不変。

**残（M1 の理想完成まで）**：
- **手順4＝本体フロントエンド差し替え**（共有パーサ→tree→lower→arena・旧 `parseProgram/parseStruct/Enum/Func` 退役＝重複パーサ解消）。これで真の 1 AST。**未着手**（不動点 byte 同一性の制約が重い・別増分）。
- **手順3 の残り＝式・文・パターンツリー**（関数本体・デフォルト式を木で surface）。現状は本体/デフォルト式を skip（presence フラグのみ）。
- **暫定判断はローカル `<memory-dir>/review-items.md` に記録**（DeclAst をタグ付き struct にした件＝codegen の enum-holds-struct 依存順バグ回避／`unique`/`export` 修飾子が slice 外で isUnique が macro 視点で false／func 型式を bare 名に潰す 等）。

## M1 の進め方（確定手順・構文層の切り出し）

**狙い＝「文字列→AST（レクサ＋クリーン値ツリー＋パーサ）」をコンパイラとマクロの唯一の共有物にする。** 切る線＝**構文（form）vs 意味（meaning）**。`String→AST` こそが切り出しの本体で、`parseItem` はその共有パーサを「対象項のソーススライス＋base offset」で呼ぶ薄いラッパ（原本座標で木が返る）。コンパイラ自身も同じ共有パーサを使う＝*コピーでなく同一物*（1 AST 原則＝マクロ専用の縮小 AST は作らない＝syn/rustc drift 回避）。

**射程の確定（重要）**：
- **やる＝構文層まるごと**（lexer＋完全値ツリー AST〔宣言・式・文・パターン・`TypeExpr`、String 名・全ノード原本座標 span〕＋parser）。コンパイラ本体はこの共有パーサで**構文ツリーを得て、それを既存の `Comp` arena へ lower** する（＝従来の parse-into-arena を「共有 parse→tree → lower→arena」に置換）。**checks も codegen も無改修**（arena を読むまま＝不動点が守る）。パーサが今やっている codegen 播種（`recordArrayElem` 等）は **lower 側へ移す**＝パーサは純粋（tokens→tree）。
- **やらない＝重なりの外**：codegen を arena から型付き IR に作り替え arena を消す（負債根 #1）。これは**共有境界の下・マクロ不可視**で、メタプロにも境界の理想にも無益。境界の理想を達成した後に part 単位で増分（不動点が各 part を守る）＝今バンドルしない（青天井化を避ける）。lower→arena で当面 arena は残る＝**境界の理想は 1mm も損なわれない**（マクロは arena を見ない）。
- **Dictionary は後**：理想ツリーは String 名で自己完結。インターン化（負債根 #2 の完済・`spansEqual`/`rangeEquals` 259 箇所を整数比較）＝Phase C で Dictionary を道具に。**先行不要・直交**。
- **unparser（AST→source）は additive 後乗せ**（フォーマッタ/`quote`/round-trip の土台・derive は当面 String 出力なので M1 の機能には不要・ブロックしない）。

**手順（各ステップで不動点＋`./test.sh` 緑を維持・ADD→reseed→USE）**：
1. **レクサ一本化**：`compiler/src/Lexer.pw`（`Kind`/`Tok`/`lex`・Comp 非依存）を `@Std/Syntax` へ移設し、本体 `compiler/src/_.pw` も `import @Std/Syntax with { … }`。これでレクサが 1 本。⚠ 本体が `@Std/Syntax` を import する＝それが本体のブートストラップ・ソースに入る（seed が支える機能だけ使う）。
2. **クリーン値ツリー AST 型を `@Std/Syntax` に定義**（`Decl`/`Field`/`Variant`/`Param`/`TypeExpr`/`Expr`/`Stmt`/`Pattern`…・String 名・再帰〔auto-boxing 既に在り〕・全ノード span）。
3. **共有パーサ `tokens → tree`**（純粋・回復可能エラー・base offset 対応）。まず**宣言（struct/enum/fn シグネチャ＋TypeExpr）**を先行実装＝ここが M1 の機能マイルストン（マクロが型/フィールド/関数を読める）。式・文・パターンは続けて埋め構文層を完成。
4. **本体フロントエンドを差し替え**：`lex`（共有）→ `parse`（共有・tree）→ `lower(tree)→Comp`（新パス＝arena 充填＋codegen 播種をここへ）。`parseProgram`/`parseStruct/Enum/Func` を置換。checks/codegen は不変。
5. **`parseItem` を本物化**：対象項の実ソース slice＋base offset で共有パーサ→宣言ツリー。**ハーネスに実ソース slice を渡す**（M0 は `source: ""`・decl span 捕捉＝directive `@`〜閉じ `}`）。derive が実際に宣言を読んで生成＝M1 完了。
6. （additive）**unparser**＝AST→source。

**進捗の刻み方**：手順 1（レクサ）と 3（宣言パーサ）+4（lower）+5（parseItem）で「マクロが対象型を読める」M1 緑を取り、その後 3 の式・文・パターンで構文層を完成。auto-part の loud-fail（gen 未実行で `.gen.pw` 欠落）は directive→マクロ分類が要るので並行 additive。
- **M2**＝dogfood（特権 Eq/Ord をマクロ化→`@[Hash]`→`Dictionary`）→ **M3** パッケージ管理後に外部切り出し。

## 並行・後続（renovate の残り・ロードマップ）

- **Phase B 残り（要 supervised）**：checks（10 箇所の `exprType`）を typed-AST に統合＝3 重 walker 一本化／pre-fill パスで codegen を完全 pure-read／`exprType` 再導出を駆逐。per-function clear で grounded をキャッシュできたので**テンプレート型は不要**になった。
- **Phase C＝名前 interning**（`spansEqual`/`rangeEquals` 259 箇所を整数比較に・`kwSpan` 系も剥がれる）。**interning＝マップ＝`Dictionary` がツール**なので、**Dictionary が来てから（M2 後）やるのが得**（先にやると手書きハッシュ表になる）。
- **重い D（後日・本物の refactor）**：legacy 型 triple `(start,len,isArray)+ref` の ref 一本化／パーサが codegen 仕事（`appendMangleSpan` でソース buffer に mangle 書込み・`recordArrayElem` で `arrayElems` 種まき）を post-parse へ／derive 合成 ~280 行がパーサ内（＝メタプロ dogfood で置換されるので触らない）。
- **deferred＝分割コンパイル**（Loader のソース連結モデル＋`*Start/*Len` span 規約。renovation が届かない唯一・分割/incremental が要るまで後回し）。
- **横断 additive**：Iterator 拡充（reduce/take/zip 等）・演算子トレイト全配線（Eq/Ord 以外・需要駆動）・循環回収（Ref グラフ限定サイクルコレクタ）・async tail＋spawn（実スレッド `JoinHandle[T]`）・`any P` 存在型。詳細は [provisional.md](provisional.md)。
- **既知のバグ＝free 関数のモジュール跨ぎ同名衝突**（2026-06-06 発見・要修正）：別モジュールに同名の private free 関数があると、同モジュール内の正しい呼び出しが「別モジュールの関数を import せず使用」エラーで誤検出される（例：`@Std/Syntax` に private `digitByte` を足すと本体 `Parser/Decl.pw` の同名 `digitByte` 呼びが壊れた→`srcDigitByte` に改名して回避）。期待＝free 関数解決は **same-module 優先**、他モジュールは import 済み名のみ候補。現状は loaded 全モジュールの同名を拾い非 import なら error。一般ユーザーも別モジュールに同名 private 関数を置くと踏む独立バグ（メタプロ/A とは無関係）。

## 再利用資産・罠（git で拾いにくい知見）

- **型付き AST キャッシュ**（現アーキ）：`typeOf(c, id)`＝codegen の型読み口（旧 `exprType` 再導出の代替）。ノード型を `Comp` の **4 並列 scalar 配列**にキャッシュ（self-host は **struct 配列 IndexSet 非対応**ゆえ・`arr[i]=v` の scalar IndexSet は可）。**body emission のエントリ（`genFunc`/`genClosure`/`genAsyncFunc`）で `clearExprTyCache`**＝env（Self/型 args/インスタンス）は 1 body の emission 中だけ一定なので、grounded 型をその間だけキャッシュ・関数境界で破棄（全文脈で安全・filled-id リストのみ reset で O(fills)）。`exprType` は今や `typeOf` 初回 touch／自身の再帰／pre-codegen checks からのみ到達。
- **再帰値型 box**：`markBoxedFields`（`Mono.pw`・`Comp.boxedFields`＝field の `nameStart` キー）が循環を閉じる**ユーザー側フィールド**を box（`Array`/`RawBuffer`/`Ref`/`WeakRef` は cut・`Optional`/`Result` は透過して引数を辿る＝Optional 自体は box せず hardcoded `.data.Some.v` を温存）。`T*`・構築 `genBoxCell`（`curRetTy=fd.ty` で nested JSX を mangle 推論）・読み deref コピー・書き fresh box に repoint（共有セル不変＝値意味論）。box＝`plew_arc_alloc` rc セル・copy/share は retain・release は rc→0 で pointee 再帰 release＋free。**ARC 解放は配線済**だが残リークは print/String の既存ギャップのみ（box 由来 0）。終端なし循環 `struct A{a:A}` は構築不能だが通る（loud reject は将来）。
- **値意味論 ARC の在処**：concrete＝`emitFieldAction`（struct/enum 共有・unique-deinit 込み）、mono＝`emitMonoFieldAction`/`emitMonoModeDef`。**heap フィールド種を足すのはこの 2 dispatcher**。need 判定は `fieldNeedsCopy/Release`・`typeInfoNeedsCopy/Release`。
- **Iterator/generic 機構**：method-level 型パラメータ（`FnInst.recvInstRef`・`registerMethodInst`・mangle suffix は method-own tail のみ）・**demand-driven 単相化**（`providedRetReachable`＝`FilterIter[FilterIter…]` の無限型族を到達時のみ発行）・Self/Item 解決（`curSelfRef`/`curItemRef`＋`resolveTy`）・構造的型推論（`unifyTypeParam`）・impl レベル `where`（funcBounds へ畳む）。**罠**：型パラメータ名 vs 具体型名のグローバル衝突（ユーザー struct `B` と `MapIter[…,B]` の `B`）→ `isTypeParamName` は宣言済 struct/enum 名を具体型扱い。
- **演算子 opcode**：`op` フィールドは `kindCode(Kind)` の整数。`Ops.pw` の `opAdd()..opCoalesce()`（`kindCode(<Kind.X/>)`）が**単一の symbolic 源**（magic 数を codegen に漏らさない）。
- **gen モード（`plew gen`・M0）**：`plewc --gen <file>`＝通常コンパイルの変種。`Comp.genMode`/`genMainIdx`、合成は `Codegen/Gen.pw`（`synthGenMain`＝`@[Name]` ごとに `write(s: <Name/>.deriveFromSource(source:"",start:0,end:0))` を arena AST で組む・`isBuiltinDerive` で Eq/Ord 除外）。driver（`_.pw`）で **①argv `--gen` 検出→entry を argv[2] へ ②`@Std/Io` 強制ロード（harness の `write` 用）③ローダ auto-part 抑制 ④checks 後に `synthGenMain`（import hygiene を回避）⑤body emission で user `main` を skip**。ローダ＝`hasDirective`（`@`+`[` 隣接トークン）で `@[...]` を検出し `<Foo>.gen.pw`（存在時のみ）を同一モジュール part に enqueue。**罠**：`Expr.Str` は span が引用符込み前提（codegen が `start+1`/`len-2`）＝0 長 span は U64 アンダーフロー panic→合成側で実 `""`（2 バイト）を intern して指す。gen 中は user 自身の `main` が生成物を使っても OK（skip されるので未定義参照でも落ちない）＝「同一モジュール derive」が自然成立。auto-part の loud-fail（gen 未実行で `.gen.pw` 欠落）は directive→マクロ分類が要るので M1 以降。

## ビルド・テスト・機能追加手順

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust 不要）。`./bootstrap.sh --reseed` で種更新（→ `compiler/plewc.seed.c` を commit）。
- **メタプロ生成**：`./plew-gen.sh <file.pw> …`＝`plewc --gen <file> | clang | run > <file>.gen.pw`。`@[...]` 付きファイルに対し derive マクロを走らせ生成 part を吐く（コミットする・通常ビルドが auto-part）。
- **テスト**：`./test.sh`＝`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/part/`（複数ファイル）＋`tests/reject/*.pw`（plewc 非ゼロ＝受理の健全性）＋`tests/panic/*.pw`（compile+link 成功・実行は非ゼロ＋`.panic` stderr 部分一致）＋`tests/gen/*/`（`App.pw`＝マクロ＋`@[...]`／hermetic に gen→auto-part→実行→`App.out` 照合・`.gen.pw` は毎回 $TMP で再生成）＋不動点。メモリは `ASAN=1 ./test.sh`。**⚠ macOS の ASan は leak 非対応**（`detect_leaks` 不可）＝UAF/二重free は ASan、リークは `MallocStackLogging=1 leaks --atExit -- <bin>` で検証。
- **機能追加＝ADD→reseed→USE**：新機能を plewc.pw の**ソースで使う**には ①`compiler/src/` の codegen に足す（ADD）→ ②`--reseed` で種更新→ ③ソースで使う（USE）。「ソースが使う機能は常にひとつ前のコンパイラがサポート済み」を守れば不動点は壊れない。**codegen 出力変化・AST フィールド追加・新 preamble 行は reseed 2 回**、**codegen 出力を変えない検査追加は reseed 1 回**。
- **AST フィールド追加のコツ＝デフォルト値**：`val isPub: Bool = false` とデフォルトを付けると既存の構築点が省略でそのまま通る＝多数の構築点を改修せず済む（`<Comp .../>` リテラルも省略可）。
- **⚠ 落とし穴＝コンパイラは `@Std/Io`→`@Std/Core` を import** するので、Core/Io/Process/**Prelude**（全プログラム自動ロード）も「コンパイラ自身がコンパイルするソース」。種がまだ受理しない構文/機能を足すと bootstrap が即壊れる＝**機能を先に種へ焼いてから Core/Prelude で使う**（ADD→reseed→USE）。表現スワップ等の大変更は seam（intrinsic 境界）で担保（→ array-struct-plan.md）。

## 運用メモ

- 動作する区切りで**記述的 git タグ**。コミットメッセージは英語＋`Co-Authored-By`。GPG 署名（`--no-gpg-sign` を使わない・たまに pinentry タイムアウト＝再実行で通る）。
- 不要になった実装は削除し、必要なら git tag から復旧（例：`git checkout stage0-final -- bootstrap`）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。
- C 予約語（`double` 等）と衝突する Plew 識別子は生成 C が壊れる＝名前マングリング未実装（[provisional.md](provisional.md)）。
- LLVM 化は当面しない＝意味論が揃ってから並行バックエンドとして追加（C は捨てない）。
