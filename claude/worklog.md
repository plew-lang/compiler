# 作業ログ

> 現在地・次の一歩・運用メモ・再利用資産だけを置く。完了した「やった」は git（記述的タグ）へ。「なぜ・却下案」は [design-decisions.md](design-decisions.md)、パイプライン設計は [architecture.md](architecture.md)、spec からの意図的剥離・暫定は [provisional.md](provisional.md)、メタプロの段取りは [metaprogramming-architecture.md](metaprogramming-architecture.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で全パートを綴じる 1 モジュール）。自分自身を不動点までコンパイル。hidden-meaning（整数幅・match 網羅・ラベル・受理の健全性・値意味論/CoW・`unique`/`deinit`/move・generics・トレイト＋Eq/Ord＋derive＋関連型・クロージャ）は概ね解消。**残る剥離・暫定は [provisional.md](provisional.md) が正典**。

**構文解析は完全に `@Std/Syntax` の責務（A＝フロントエンド統合・完了）。** コンパイラとマクロは**唯一の共有パーサ**を通る＝ドリフトする文法に二重パーサなし。

- **`@Std/Syntax`（構文＝form）**：レクサ `Syntax/Lexer.pw`／値ツリー AST `Syntax/Ast.pw`＋`Syntax/Trees.pw`（String 名・全ノード原本座標 span）／パーサ `Syntax/Parser.pw`（宣言・トップレベル）＋`Syntax/ParseBody.pw`（式・文・パターン・ブロック）／出力ビルダ `Syntax/Build.pw`（`Src`）。入口は `parseProgramAst(p) -> Array[TopItemAst]`（プログラム全体）と `parseItem(source,start,end) -> TopItemAst`（マクロ用＝注釈対象 1 項）。
- **コンパイラ（意味＝meaning）**：`compiler/src/`＝`Loader`（パース駆動ローディング＋パス解決）・`Ast`（arena ノード＋`Comp`）・`Parser/Decl`（＝module-tag helper `markImport`/`recordExport`＋derive 合成 `synth*`。**宣言パーサは持たない**）・`Codegen/`〔Emit/Resolve/Ops/Check/Expr/Stmt/Decl/Mono/Array/Async/Gen/**Lower**〕。`Codegen/Lower.pw` が共有値ツリー（TopItemAst/DeclAst/ImplAst/…）を arena へ lower。
- **ローディングもパース駆動**：driver（`main`）が各ファイルを `c.bytes` に追記→`parseAndLowerFile`（共有パーサで parse＋lower）→返った木の `Import` ノード（import＋part）を辿って子ファイル探索（ハンドロールの事前スキャンなし）。残る I/O（読込・パス解決）と arena バイト配置・module tagging はコンパイラ側＝構文解析でない部分のみ。

完了した大物（詳細は git・記述的タグ）：async/await 段階 1-3（stackless SM）・コアライブラリ境界（`@Std` の `extern "plew-intrinsic"`）・**Array＝`RawBuffer` 床の Plew struct**（[array-struct-plan.md](array-struct-plan.md)）・可視性完全強制・Iterator/Iterable＋lazy map/filter・再帰値型 auto-boxing＋ARC・renovate Phase A（ARC 1 本化・Op enum・expect）＋Phase B B0-B2（型付き AST キャッシュ）・**メタプロ M0/M1**（マクロが実宣言を読んで生成・tag `metaprogramming-m1`）・**A＝フロントエンド統合**（全パース→共有 @Std/Syntax・パース駆動ローディング）・**マクロ入力 `TopItemAst`**（struct/enum/fn に加え **impl/trait** もマクロ対象）・**パターン/構築のフィールド実在検査**（`checkMatchBinds`/`checkMakeFieldExists`＝受理の健全性）・**Eq/Ord トレイト＋`@[Eq]`/`@[Ord]` derive**・**Hash/Hasher＋SipHash-1-3＋`@[Hash]` dogfood**・**Dictionary[K,V] lang item（struct+メソッド+添字）**・ネスト generic 単相化（`Array[Gen[K,V]]`）・generic コンストラクタ型引数推論（JSX）・C 予約語マングル等の細バグ群。renovate vs rewrite の判断・負債の地図は [architecture.md](architecture.md)「負債監査の結論」、設計根拠は [design-decisions.md](design-decisions.md)、再利用機構は本書末尾「再利用資産・罠」。

## 次の一歩

**Hash → Dictionary（M2 dogfood）達成**：`Hash`/`Hasher` トレイト＋SipHash-1-3 Hasher＋`@[Hash]` derive dogfood、`Dictionary[K,V]` lang item（struct＋メソッド＋添字 `dict[k]`/`dict[k]=v`＋**リテラル `[k:v]`/`[:]`**）まで land 済（詳細＝下記「Dictionary」）。次の本線は並行 additive（下記ロードマップ）。**M3＝パッケージ管理導入後に `@Std/Syntax` を in-tree から外部共有パッケージへ昇格**（コンパイラもマクロも同一版に依存＝Rust の 2 パーサ版違い問題回避）。

> **🔴 必須 TODO（忘れない）＝ランダムシード（RandomState 相当）**。Rust の `HashMap` は SipHash-1-3 ＋ **マップごとにランダムキー**（DoS 耐性）。Plew にはまだ RNG（`Random`）が無いので、**当面は固定キー（決定的）で SipHash を実装**し、**`Random`/RNG 着手後にマップごとのランダムシードへ差し替える**（アルゴリズム・トレイト形は不変・シード源を差すだけ＝additive）。固定キー間は DoS 耐性なし（コンパイラ内部マップには無害・反復順は spec 未規定なので契約は破れない）。**RNG が入ったら必ずランダムシード化すること。**

## Dictionary[K,V]（lang item・struct+メソッド+添字は land 済）

**設計**：全て Array 上に構築（平行配列＝CoW/値意味論は Array から継承）。`compiler/std/Prelude.pw` 末尾＝`struct Dictionary[K,V] { mut val keys: Array[K]  mut val vals: Array[V]  mut val hashes: Array[U64]  mut val buckets: Array[U64]  pub(get) mut val count: U64 }`。open addressing・線形プロービング（`buckets[slot]`＝エントリ index+1・0=空／`keys`/`vals`/`hashes` 密 append／空構築〔全 `[]`〕＋初回 insert で grow cap0→8／負荷 0.75 で倍化 grow＋rehash）。メソッド（`pub impl[K,V]`・1 ブロック＝可視性集約）＝`hashOf`/`grow`/`insert`/`find`/`contains`/`getOr`/`at`（欠落 panic＝`dict[k]` の脱糖先）。`get(key)->Optional[V]` は Optional ambient 化後。シード固定（上の 🔴 RNG TODO）。**構築は当面 `<Dictionary[K,V] keys=[] vals=[] hashes=[] buckets=[] count=0 />`〔private フィールド露出・可視性ゲート緩い〕＋添字/メソッド**で完動。dict-wip ブランチは退役（古い・平行配列回避策含む・main が正本）。

**添字（land 済）**：`dict[k]`→`.at(key:)`／`dict[k]=v`→`.insert(key:,value:)`。base 型が Dictionary のとき codegen が合成 Method ノードを emit（`isDictionaryType`／`synthDictMethod`・Expr.pw Index 枝＋Stmt.pw assign 枝・exprType Index は V を返す）。test run/dictionary_subscript。

**リテラル `[k:v]`/`[:]`（land 済）**：パース＝`Kind.LBracket`（ParseBody.pw）で `[` 後が `:]` なら空 dict／最初の式の後が `:` なら dict（`, k: v` 反復）／他は配列。**最初の要素も一時値で `append`**（`val first = parseExprAst()` の名前付きローカルは避ける＝下記「by-value 引数の罠」）。AST＝`ExprAst.DictLit(keys, vals, span)`。lower（`Codegen/Lower.pw` の `lowerDictLit`/`synthEmptyDict`）＝give-block へ脱糖＝`if (1) { mut val __dl: Dictionary[K,V] = <empty>; __dl.insert(k,v)…; give move __dl } else { give <empty> }`（`move` で deep copy なしの所有権移譲＝return と同じ・else は dead だが値位置の型検査のため空 dict を give）。**K/V は binding/return context から**（`lowerExprWithCtx` の DictLit 枝＝annotated `let`/`return` のみ・要素推論なし＝空配列と同じく無 context はエラー）。`IfExpr` 値位置の結果型は `blockGiveType`（ブロックの `let` を peek 登録→give 式の型→pop）で give-of-block-local を正しく解決（既存の一般バグも改善）。test run/dictionary_literal。

**⚠ 真因は markBoxedFields でなく `Array[Enum]` の浅い要素 copy/release だった**（撤回済の旧診断＝「再帰値型へバリアント追加で boxing が壊れる」は誤り）。`ExprAst.DictLit` 追加で array-of-compound（`[<P x=1/>]`/`[[1,2]]`）が plewc 自身を crash させたのは、**コンパイラ自身が新パーサで `val first` 名前付きローカルを by-value で `append` に渡し（コピーされず浅く格納）→scope 末で `release(first)` し、格納済み要素がダングリング**したため（→「by-value 引数の罠」）。根因は別にあり＝`Array[E]` の要素 deep copy/release 判定 `structNeedsCopy` が **struct しか見ず enum を落とす**ので、heap 持ち variant を含む `Array[Enum]`（`Array[ExprAst]`/`Array[StmtAst]` 等）が浅い要素管理になり leak＋UAF（append したローカルを drop すると壊れる＝既存の潜在バグ）。修正＝`arrayElemNeedsDeep`（`structNeedsCopy` OR `enumNeedsCopy`）を `Codegen/Array.pw` の copy/release/set/push 4 箇所に配線（enum の `<Elem>_copy`/`_release` は既存）。test run/array_enum_arc（ORIGINAL では heap-use-after-free・修正後 ASan クリーン）。

## 残バグ（低優先・未着手）

- **Bug13 shadow キャプチャの C 名不一致**〔loud〕：F2 の shadow suffix が `emitCaptureInit` の enclosing 名出力に未配線（Expr.pw）。
- **Bug14 パターン/構築フィールド名のエラー行が近似**：bind/MakeField 名が lower で再インターン＝原本 offset 無し→`BindAst`/`MakeFieldAst` に span 付与、lower で原本 offset 維持（Trees.pw/Lower.pw）。
- **Bug15 非 void 関数で return せず末尾到達＝silent ゴミ**〔silent・既存・要言語判断〕：Plew は**末尾式を暗黙 return しない**設計（`fn f() -> U64 { 5U64 }` すらゴミ＝spec は `return` 明示・`give` はブロック式専用）。よって `fn f() -> T { match e { … => give v } }`（give アームの tail match）も値を返さず未初期化（`-Wreturn-type`）。これは「tail-match が返すべき」ではなく「**全経路 return せず関数末尾に達するのを loud なコンパイルエラーにすべき**」（拠り所＝silent ゴミは不可）。修正＝非 `()` 関数の本体が全経路で `return`/`panic`/発散で抜けることを検査（spec/11 の発散規則 L223＝panic/return/break/continue で抜けるブロックは値を生まない・に整合）。**制御フロー解析を要し言語表面の判断なので未着手＝ユーザー相談待ち**。
- **Bug16 `print(String)` が壊れる＝✅修正済**：原因 2 つ＝(1) **String が `Format` 非準拠**だった（`print[T] where T: Format` の境界違反＝`print(stringVar)`/struct field/match-bind が `does not conform to the trait required by where`）→ `compiler/std/Core.pw` に `pub impl String as Format { format → self }` 追加。(2) **文字列リテラル引数が generic の T を推論させない**（`Expr.Str` の typeOf が `kind=1 nameLen=0`＝名前なし→`tyRefOfInfo`=0→`print("hi")` が T 未推論で `print_value_T` 未定義を呼ぶ壊れた C）→ `Resolve.pw` で `Expr.Str` の typeOf に "String" 名 span を付与（`stringTypeSpan`）。enum/match/struct 無関係の `print` 一般バグだった。test run/print_string。

メタプロの段取り・実行系の具体は [metaprogramming-architecture.md](metaprogramming-architecture.md)。

## 並行・後続（renovate の残り・ロードマップ）

- **Phase B 残り（要 supervised）**：checks（10 箇所の `exprType`）を typed-AST に統合＝3 重 walker 一本化／pre-fill パスで codegen を完全 pure-read／`exprType` 再導出を駆逐。per-function clear で grounded をキャッシュできたので**テンプレート型は不要**になった。
- **Phase C＝名前 interning**（`spansEqual`/`rangeEquals` 多数を整数比較に・`kwSpan` 系も剥がれる）。**interning＝マップ＝`Dictionary` がツール**なので、**Dictionary が来た今（M2 後）やるのが得**（先にやると手書きハッシュ表になる）。
- **重い D（後日・本物の refactor）**：legacy 型 triple `(start,len,isArray)+ref` の ref 一本化／derive 合成 ~280 行が `Parser/Decl.pw`（＝メタプロ dogfood で置換されるので触らない）。
- **横断 additive**：Iterator 拡充（reduce/take/zip 等）・演算子トレイト全配線（Eq/Ord 以外・需要駆動）・循環回収（Ref グラフ限定サイクルコレクタ）・async tail＋spawn（実スレッド `JoinHandle[T]`）・`any P` 存在型。詳細は [provisional.md](provisional.md)。

## 再利用資産・罠（git で拾いにくい知見）

- **型付き AST キャッシュ**（現アーキ）：`typeOf(c, id)`＝codegen の型読み口（旧 `exprType` 再導出の代替）。ノード型を `Comp` の **4 並列 scalar 配列**にキャッシュ（self-host は **struct 配列 IndexSet 非対応**ゆえ・`arr[i]=v` の scalar IndexSet は可）。**body emission のエントリ（`genFunc`/`genClosure`/`genAsyncFunc`）で `clearExprTyCache`**＝env（Self/型 args/インスタンス）は 1 body の emission 中だけ一定なので、grounded 型をその間だけキャッシュ・関数境界で破棄（全文脈で安全・filled-id リストのみ reset で O(fills)）。`exprType` は今や `typeOf` 初回 touch／自身の再帰／pre-codegen checks からのみ到達。
- **共有パーサ→arena lower（A）**：共有 @Std/Syntax パーサが値ツリー（`TopItemAst`/`DeclAst`/`ImplAst`/`TraitAst`/`ExternAst`/`ImportAst`/`DirectiveAst`／式文は `ExprAst`/`StmtAst`…）を返し、`Codegen/Lower.pw` が arena（`Expr`/`Stmt`/`Func`/`StructDef`…）へ lower。**名前の offset 規律**＝`moduleOf` に効く名前（free fn 宣言名・call 名・extern fn 名・import/export 名）は**原本 offset 維持**（再インターン不可）、それ以外（struct/enum/field/型名・impl 系全部）は `internBytes` で再インターン（codegen は text 出力ゆえ byte 同一・moduleOf 不参加）。`lowerType` が `recordArrayElem` で `arrayElems` 種まき（旧パーサの codegen 仕事は lower 側へ）。**罠**：パース駆動ローディングで `c.bytes` はファイル源と再インターン名が交互配置になる（各ファイルを追記直後に lower）。writeSpan は text 出力・moduleOf は per-file レンジ参照ゆえ不動点・可視性とも安全（offset 値そのものに依存するロジックは無い）。
- **block 0 は dummy 予約**：`body` フィールド 0 は「無本体」sentinel（extern fn・trait 要求シグネチャ）。entry ファイルは ambient Prelude より先に lower されるので、予約しないと最初の関数本体が block 0 に来て無本体と誤判定される（`body != 0` で gate する body-walk 全部が誤 skip）。`_.pw` の Comp 初期化で `c.blocks.append(<Block stmts=[] />)`。
- **再帰値型 box**：`markBoxedFields`（`Mono.pw`・`Comp.boxedFields`＝field の `nameStart` キー）が循環を閉じる**ユーザー側フィールド**を box（`Array`/`RawBuffer`/`Ref`/`WeakRef` は cut・`Optional`/`Result` は透過して引数を辿る＝Optional 自体は box せず hardcoded `.data.Some.v` を温存）。`T*`・構築 `genBoxCell`（`curRetTy=fd.ty` で nested JSX を mangle 推論）・読み deref コピー・書き fresh box に repoint（共有セル不変＝値意味論）。box＝`plew_arc_alloc` rc セル・copy/share は retain・release は rc→0 で pointee 再帰 release＋free。**ARC 解放は配線済**だが残リークは print/String の既存ギャップのみ（box 由来 0）。終端なし循環 `struct A{a:A}` は構築不能だが通る（loud reject は将来）。（旧メモ「再帰値型へバリアント追加で auto-boxing/copy が壊れる」は**誤診断＝撤回**。実際の罠は次の 2 つ。）
- **⚠ `Array[Enum]` の要素 deep copy/release**（値意味論 ARC）：`Array[E]` の要素を deep に copy/release するかの判定は `Codegen/Array.pw` の `arrayElemNeedsDeep`＝`structNeedsCopy` **OR** `enumNeedsCopy`。元は `structNeedsCopy` だけ＝enum 要素を取りこぼし、heap 持ち variant の `Array[Enum]`（`Array[ExprAst]` 等）が**浅い要素管理**（buffer だけ copy/free・要素の `<E>_copy`/`_release` 不走）になり、leak＋（append したローカルを drop すると）UAF。**新しく heap を持つ要素種を Array に入れるときはここの判定を必ず確認**。
- **⚠ by-value 引数のローカルはコピーされず格納されうる**：ヒープ持ち値型の**名前付きローカル**を by-value 引数として `append` 等に渡すと、call site で CoW コピーされず**浅く格納**され、scope 末の `release(局所)` で格納要素がダングリングする（一時値 rvalue を渡せば所有権移譲で安全）。パーサ等で「parse 結果を一旦ローカルに束ねてから push」は避け、**`xs.append(parseFoo())` と一時値で渡す**。`Array[Enum]` を deep にした今は前者の罠も顕在化しにくいが、根治（by-value 引数 place の CoW コピー）は未対応＝当面は一時値で回避。
- **値意味論 ARC の在処**：concrete＝`emitFieldAction`（struct/enum 共有・unique-deinit 込み）、mono＝`emitMonoFieldAction`/`emitMonoModeDef`。**heap フィールド種を足すのはこの 2 dispatcher**。need 判定は `fieldNeedsCopy/Release`・`typeInfoNeedsCopy/Release`。
- **generic struct field の array 単相化**：`Array[Box[T]]`/`Array[Entry[K,V]]`（compound 要素が外側型パラメータを含む）の field/変数 field は `groundedArrayFieldInfo`（`genericFieldTypeInfo`/`genericEnumFieldTypeInfo`/`substTypeInfo` の array 枝）で instance env 越しに ground＝`ref` 不変で波及ゼロ。template の非 ground compound 要素は runtime/method を emit しない（`skipArrayElem`/`emitArrayMethods` の `tyRefIsGround`）。`arrayElemNameForRef` は env 依存 `sameMangle` で template `T` を concrete に誤マッチしうるので**非 ground エントリを skip**。
- **Iterator/generic 機構**：method-level 型パラメータ（`FnInst.recvInstRef`・`registerMethodInst`・mangle suffix は method-own tail のみ）・**demand-driven 単相化**（`providedRetReachable`＝`FilterIter[FilterIter…]` の無限型族を到達時のみ発行）・Self/Item 解決（`curSelfRef`/`curItemRef`＋`resolveTy`）・構造的型推論（`unifyTypeParam`）・impl レベル `where`（funcBounds へ畳む）。**generic-レシーバ・メソッド本体の推移的インスタンス探索**＝`scanGenInstMethodBodies`（各 genInst のメソッド本体を `emitMonoMethod` と同じ env で scan→nested fnInst 登録・Array レシーバはスキップ）＝`Dictionary[String,U64].hashOf` 内 `key.hash[H]`→`String.hash[SipHasher]` を discover。**罠**：型パラメータ名 vs 具体型名のグローバル衝突（ユーザー struct `B` と `MapIter[…,B]` の `B`）→ `isTypeParamName` は宣言済 struct/enum 名を具体型扱い。
- **generic コンストラクタ型引数推論（JSX）**：`lowerExprWithCtx`（lower 時に context 型を渡し、型引数なし Make の head が一致したら context 型引数を採用＝arena Make を最初から正しい `ty` で構築）＋`Comp.lowerRetTy`（戻り型 context・本体 lower 中だけ set）。
- **演算子 opcode**：`op` フィールドは `kindCode(Kind)` の整数。`Ops.pw` の `opAdd()..opCoalesce()`（`kindCode(<Kind.X/>)`）が**単一の symbolic 源**（magic 数を codegen に漏らさない）。
- **gen モード（`plew gen`・M0）**：`plewc --gen <file>`＝通常コンパイルの変種。`Comp.genMode`/`genMainIdx`、合成は `Codegen/Gen.pw`（`synthGenMain`＝`@[Name]` ごとに `write(s: <Name/>.deriveFromSource(source:"",start:0,end:0))` を arena AST で組む・`isBuiltinDerive` で Eq/Ord 除外）。driver（`_.pw`）で **①argv `--gen` 検出→entry を argv[2] へ ②`@Std/Io` 強制ロード（harness の `write` 用）③ローダ auto-part 抑制 ④checks 後に `synthGenMain`（import hygiene を回避）⑤body emission で user `main` を skip**。ローダ＝パース木の `Directive` ノードで `@[...]` を検出し `<Foo>.gen.pw`（存在時のみ）を同一モジュール part に enqueue。**罠**：`Expr.Str` は span が引用符込み前提（codegen が `start+1`/`len-2`）＝0 長 span は U64 アンダーフロー panic→合成側で実 `""`（2 バイト）を intern して指す。gen 中は user 自身の `main` が生成物を使っても OK（skip されるので未定義参照でも落ちない）＝「同一モジュール derive」が自然成立。auto-part の loud-fail（gen 未実行で `.gen.pw` 欠落）は directive→マクロ分類が要るので将来。

## ビルド・テスト・機能追加手順

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust 不要）。`./bootstrap.sh --reseed` で種更新（→ `compiler/plewc.seed.c` を commit）。編集中の高速反復は `./dev-rebuild.sh`（`compiler/plewc` をその場上書き）。**⚠ dev-rebuild は前回ビルドの plewc を使う**ので、miscompile を疑うときは `./bootstrap.sh`〔種から plewc0→現ソース〕で clean 検証する。
- **メタプロ生成**：`./plew-gen.sh <file.pw> …`＝`plewc --gen <file> | clang | run > <file>.gen.pw`。`@[...]` 付きファイルに対し derive マクロを走らせ生成 part を吐く（コミットする・通常ビルドが auto-part）。
- **テスト**：`./test.sh`＝`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/part/`（複数ファイル）＋`tests/reject/*.pw`（plewc 非ゼロ＝受理の健全性）＋`tests/panic/*.pw`（compile+link 成功・実行は非ゼロ＋`.panic` stderr 部分一致）＋`tests/gen/*/`（`App.pw`＝マクロ＋`@[...]`／hermetic に gen→auto-part→実行→`App.out` 照合・`.gen.pw` は毎回 $TMP で再生成）＋`tests/genreject/`（`plewc --gen` が reject すべき入力）＋不動点。メモリは `ASAN=1 ./test.sh`。**⚠ macOS の ASan は leak 非対応**（`detect_leaks` 不可）＝UAF/二重free は ASan、リークは `MallocStackLogging=1 leaks --atExit -- <bin>` で検証。
- **機能追加＝ADD→reseed→USE**：新機能を plewc.pw の**ソースで使う**には ①`compiler/src/`（または `compiler/std/`）に足す（ADD）→ ②`--reseed` で種更新→ ③ソースで使う（USE）。「ソースが使う機能は常にひとつ前のコンパイラがサポート済み」を守れば不動点は壊れない。**codegen 出力変化・AST フィールド追加・新 preamble 行は reseed 2 回**、**codegen 出力を変えない検査追加は reseed 1 回**。
- **AST フィールド追加のコツ＝デフォルト値**：`val isPub: Bool = false` とデフォルトを付けると既存の構築点が省略でそのまま通る＝多数の構築点を改修せず済む（`<Comp .../>` リテラルも省略可）。
- **⚠ 落とし穴＝コンパイラは `@Std/Io`→`@Std/Core`／`@Std/Syntax`／`Prelude`（全プログラム自動ロード）を import** するので、これらも「コンパイラ自身がコンパイルするソース」。種がまだ受理しない構文/機能を足すと bootstrap が即壊れる＝**機能を先に種へ焼いてから std で使う**（ADD→reseed→USE）。表現スワップ等の大変更は seam（intrinsic 境界）で担保（→ array-struct-plan.md）。
- **arena Expr/AST バリアント追加の罠**：①exhaustive な `match` 全箇所（Lower の `ExprAst`／genExpr・exprType・scanExprInsts 等の arena `Expr`）にケース追加が要る（コンパイル時に non-exhaustive で検出）。共有 `@Std/Syntax` の `ExprAst`/`StmtAst` は **`Codegen/Lower.pw` の `lowerExpr`/`lowerStmt` が唯一の exhaustive match**（パーサは構築のみ・Build.pw は body を slice 出力でノードを match しない）。②`@Std/Syntax` の AST enum にバリアントを足すのは codegen 出力変化＝**reseed 2 回**。

## 運用メモ

- 動作する区切りで**記述的 git タグ**。コミットメッセージは英語＋`Co-Authored-By`。GPG 署名（`--no-gpg-sign` を使わない・たまに pinentry タイムアウト＝再実行で通る／詰まったら手元で `echo test | gpg --clearsign` でパスフレーズをキャッシュ・コミットメッセージにバッククォートを書くと zsh がコマンド置換するので避ける／`-F` でファイル渡し）。
- 不要になった実装は削除し、必要なら git tag から復旧（例：`git checkout stage0-final -- bootstrap`）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。
- LLVM 化は当面しない＝意味論が揃ってから並行バックエンドとして追加（C は捨てない）。
