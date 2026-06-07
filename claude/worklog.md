# 作業ログ

> 現在地・次の一歩・運用メモ・再利用資産だけを置く。完了した「やった」は git（記述的タグ）へ。「なぜ・却下案」は [design-decisions.md](design-decisions.md)、パイプライン設計は [architecture.md](architecture.md)、spec からの意図的剥離・暫定は [provisional.md](provisional.md)、メタプロの段取りは [metaprogramming-architecture.md](metaprogramming-architecture.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で全パートを綴じる 1 モジュール）。自分自身を不動点までコンパイル。hidden-meaning（整数幅・match 網羅・ラベル・受理の健全性・値意味論/CoW・`unique`/`deinit`/move・generics・トレイト＋Eq/Ord＋derive＋関連型・クロージャ）は概ね解消。**残る剥離・暫定は [provisional.md](provisional.md) が正典**。

**構文解析は完全に `@Std/Syntax` の責務（A＝フロントエンド統合・完了）。** コンパイラとマクロは**唯一の共有パーサ**を通る＝ドリフトする文法に二重パーサなし。

- **`@Std/Syntax`（構文＝form）**：レクサ `Syntax/Lexer.pw`／値ツリー AST `Syntax/Ast.pw`＋`Syntax/Trees.pw`（String 名・全ノード原本座標 span）／パーサ `Syntax/Parser.pw`（宣言・トップレベル）＋`Syntax/ParseBody.pw`（式・文・パターン・ブロック）／出力ビルダ `Syntax/Build.pw`（`Src`）。入口は `parseProgramAst(p) -> Array[TopItemAst]`（プログラム全体）と `parseItem(source,start,end) -> TopItemAst`（マクロ用＝注釈対象 1 項）。
- **コンパイラ（意味＝meaning）**：`compiler/src/`＝`Loader`（パース駆動ローディング＋パス解決）・`Ast`（arena ノード＋`Comp`）・`Parser/Decl`（＝module-tag helper `markImport`/`recordExport`＋derive 合成 `synth*`。**宣言パーサは持たない**）・`Codegen/`〔Emit/Resolve/Ops/Check/Expr/Stmt/Decl/Mono/Array/Async/Gen/**Lower**〕。`Codegen/Lower.pw` が共有値ツリー（TopItemAst/DeclAst/ImplAst/…）を arena へ lower。
- **ローディングもパース駆動**：driver（`main`）が各ファイルを `c.bytes` に追記→`parseAndLowerFile`（共有パーサで parse＋lower）→返った木の `Import` ノード（import＋part）を辿って子ファイル探索（ハンドロールの事前スキャンなし）。残る I/O（読込・パス解決）と arena バイト配置・module tagging はコンパイラ側＝構文解析でない部分のみ。

完了した大物（詳細は git・記述的タグ）：async/await 段階 1-3（stackless SM）・コアライブラリ境界（`@Std` の `extern "plew-intrinsic"`）・**Array＝`RawBuffer` 床の Plew struct**（[array-struct-plan.md](array-struct-plan.md)）・可視性完全強制・Iterator/Iterable＋lazy map/filter・再帰値型 auto-boxing＋ARC・renovate Phase A（ARC 1 本化・Op enum・expect）＋Phase B B0-B2（型付き AST キャッシュ）・**メタプロ M0/M1**（マクロが実宣言を読んで生成・tag `metaprogramming-m1`）・**A＝フロントエンド統合**（全パース→共有 @Std/Syntax・パース駆動ローディング）・**マクロ入力 `TopItemAst`**（struct/enum/fn に加え **impl/trait** もマクロ対象）・**パターン/構築のフィールド実在検査**（`checkMatchBinds`/`checkMakeFieldExists`＝受理の健全性・旧 silent broken C を loud reject 化）。renovate vs rewrite の判断・負債の地図は [architecture.md](architecture.md)「負債監査の結論」、設計根拠は [design-decisions.md](design-decisions.md)、再利用機構は本書末尾「再利用資産・罠」。

## 既知バグ一括修正（in progress・2026-06-07 着手）

provisional.md に散在していた「ブロッカーなし・いつでも直せる」バグを棚卸しし、**一括で潰す**。各項＝症状／場所／直し／状態。完了したらこの節から落とし（git タグ＋provisional の該当行更新へ）、全完了でこの節ごと削除。compact 跨ぎの再開地図。

- **Bug1 C 予約語識別子マングル**〔hidden meaning〕：✅**済**。`writeSpan`（識別子出力の単一経路・型名は PascalCase で非該当）が C 予約語の span に `_` を付与（`isCKeyword`・content-based で def/use 一貫）。文字列リテラル内容だけ `writeSpanRaw`（非マングル）に分離（Emit.pw・Expr.pw Str）。test run/c_reserved_idents（default/const/void/switch/double/int の var/param/field/fn＋文字列保全）。
- **Bug2 曖昧無サフィックスリテラルが先頭 overload 選択**〔silent〕：✅**済**（`9ddfcdb`）。findFunc/findMethod/findAssoc が 2 つ目の type-match を検出し、無サフィックスリテラル引数が候補間で異なる整数パラメータ型へ写るとき loud reject（`overloadsAmbiguous`/`checkOverloadAmbiguity`・Resolve.pw）。test reject/overload_ambiguous_literal・run/overload_literal_suffix。
- **Bug3 メソッド値化 `val f = obj.method` を受理**〔should be loud〕：✅**済**（`b8d87ed`）。struct レシーバの `.name` 式（非呼び出し）が「フィールド無し・メソッド有り」なら loud reject（`typeHasMethodNamed`・Expr.pw Field 経路）。Expr.Method 呼び出しは無影響。test reject/method_value。
- **Bug4 free 関数のモジュール跨ぎ同名衝突**〔false positive＋C 名衝突＋誤ディスパッチ〕：✅**済**。別モジュールに同名 private free fn があると ①正しい呼びが誤 reject ②C シンボル `redefinition` ③誤ディスパッチ。直し＝(a) `findFunc` を **same-module 優先**（`typeMatchSame`/`firstLabelSame`・Resolve.pw＝誤 reject＋ディスパッチ解消）＋(b) `writeFnSelector` で **衝突する free 関数だけ**にモジュール識別子 `_m<id>` を付与（`freeFnSelectorCollides`/`sameFreeFnSelectorDecl`・Decl.pw＝C 衝突解消）。**全 free 関数に一律付与すると self-compile の dead-code 到達解析が揺れ fixpoint が壊れた**ため collision-gated に（コンパイラは同名衝突がない＝出力不変＝fixpoint 保持）。test part/samename。
- **Bug5 `;` 文区切りが的外れエラー**：✅**済**（`b6c9ab8`）。`parsePrimaryAst` の default 末端が未知トークンを 0-Int に黙って変えていた→`p.fail` で loud（`;` 専用メッセージ付き・ParseBody.pw）。reject/semicolon_separator が既存でカバー。
- **Bug6+7 文脈型が末端リテラルに伝播しない**：✅**済**。(6) Arrow place 代入右辺リテラル `r->v = 42`/`ys[0]->v = 42` は**既に動作**していた（provisional が陳腐化）＝リグレッションテスト run/arrow_store_literal を追加。(7) `for val i: I32 in 0..<5` はそもそも型注釈が**パースされず**「expected an expression」だった。直し＝for 束縛に `: Type` 注釈を追加（StmtAst.For に `varTy`/`hasVarTy`・Stmt.For に `varTyStart/varTyLen`・ParseBody/Lower/Check/Mono/Stmt 連携）＝注釈型で境界リテラルを型付け（`checkLitSpan`）＋loop var をその型で登録（注釈なしは境界の型をフォールバック＝`print(i)` も ground）。test run/for_var_type_annotation。
- **Bug8+9 `@[Ord]` 残ギャップ**：✅**済**。(8) `synthEnumOrd`（tag 辞書順→同 tag は payload を `synthOrdChainExpr` で lexicographic・nullary は Equal）。(9) `@[Ord]` 合成時に Eq witness も合成（同型の明示 `@[Eq]` があれば重複回避＝`hasEqDeriveFor`）。**ついでに発覚した既存バグも修正**＝派生 `eq`/`compare`（assoc fn）が **private フィールドを読めなかった**（`inAnonImplOf` が assoc fn を type の impl 内と見ていなかった）→ assoc fn（recvStart!=0）も impl 内扱いに拡張（`@[Eq]`/`@[Ord]` on private-field struct が動く）。場所＝Parser/Decl.pw・Resolve.pw。test run/derive_ord_enum・derive_ord_implies_eq。
- **Bug10+12 ＝ネスト generic 単相化（`Array[Gen[K,V]]`）**：✅**済**。根＝generic struct の field 型 `Array[Box[T]]`/`Array[Entry[K,V]]`（compound 要素が**外側の型パラメータ**を含む）が、instance 解決で要素を ground できず head 名（`Array_Box`）や template 名（`Array_Box_T`）を吐いていた。`genericFieldTypeInfo`/`substTypeInfo` は `Array[T]`（bare param 要素）だけ処理し `Array[Box[T]]`（compound 要素に param）を未処理＝`typeInfoOfRef(fd.ty)` へフォールバックして head 名になっていた。直し＝**統一ヘルパ `groundedArrayFieldInfo`**（要素を instance env〔params→instArgs〕で ground し、ground 後が compound なら `appendMangleSpan` で mangle 名・単純なら head 名を kind=3 TypeInfo として返す＝`ref` は触らない＝**consumer 波及ゼロ**）を `genericFieldTypeInfo`/`genericEnumFieldTypeInfo`/`substTypeInfo` の array 枝で使用。併せて **template の非 ground compound 要素は runtime/method を emit しない**（`skipArrayElem`＋`emitArrayMethods` に `tyRefIsGround(ae.fieldStart)` 判定追加）。これで `struct Map[K,V] { entries: Array[Entry[K,V]] }`＋メソッド（`put`/`at` が field の Array メソッドを呼ぶ）が完全に通る＝**dict-wip の平行配列/明示型引数の回避策が不要に**。test run/generic_array_compound_field・generic_array_box_field。
- **Bug11 ＝generic コンストラクタ型引数推論**：✅**済（JSX）**。型引数なし JSX `<Box v=7 />`/`<Map entries=[] count=0 />` が **let 束縛注釈**（`val b: Box[I64] = …`）と**関数/クロージャ戻り型**（`fn make() -> Box[I64] { return <Box …/> }`）から型引数を推論。直し＝lower 時に context 型を渡す `lowerExprWithCtx`（型引数なし Make の head が context 型 head と一致したら context の型引数を採用＝arena Make を最初から正しい `ty` で構築＝struct 配列 IndexSet 非対応を回避）＋戻り型 context 用に `Comp.lowerRetTy`（free fn/method/assoc/closure の本体 lower 中だけ set・save/restore）。多パラメータ可。test run/generic_ctor_infer。**残＝assoc 呼び出し位置の推論**（`Box.make(x: 7)` で戻り `Box[T]` の T を call site context から推論＝`Box_make_x_T` のまま）は別機構（assoc-call 型引数推論）で未着手＝明示型引数 `Box[I64].make(...)` も現状パース未対応なので回避は JSX 構築へ。Dictionary には JSX で十分。
- **Bug13 shadow キャプチャの C 名不一致**〔loud・低優先〕：F2 の shadow suffix が `emitCaptureInit` の enclosing 名出力に未配線。場所＝Expr.pw。状態＝未着手・低優先。
- **Bug14 パターン/構築フィールド名のエラー行が近似**：bind/MakeField 名が lower で再インターン＝原本 offset 無し。直し＝`BindAst`/`MakeFieldAst` に span 付与、lower で原本 offset 維持。場所＝Trees.pw/Lower.pw。状態＝未着手。

> Bug10+12 が直ったので **Dictionary を `Array[Entry[K,V]]` 一本で素直に書ける**（dict-wip の平行配列回避策は不要）。Dictionary land 自体は別タスク（下記 Dictionary 再開ガイド・Bug11 は land に必須でない＝明示型引数で回避可）。

## 次の一歩

A 完了で M1 の理想形（真の 1 AST）に到達・impl/trait もマクロ対象済。**Eq/Ord トレイト演算子配線＋`@[Eq]`/`@[Ord]` derive は実装済**（commit `d33e17e`/`a9e15f2`・[provisional.md](provisional.md)「Eq/Ord」節）。

向かう先＝**Hash → Dictionary（M2 dogfood の本丸）**。ユーザー決定＝**(B) generic Hasher 形**（`fn hash[H](hasher: inout H) where H: Hasher`・マップが算法を選べる Rust 厳密形）。**アルゴリズム＝SipHash-1-3（Rust と同じ・rotl＋wrappingAdd＋xor の U64 のみ＝乗算不要・`wrappingAdd` 実装済）**。

> **🔴 必須 TODO（忘れない）＝ランダムシード（RandomState 相当）**。Rust の `HashMap` は SipHash-1-3 ＋ **マップごとにランダムキー**（DoS 耐性）。Plew にはまだ RNG（`Random`）が無いので、**当面は固定キー（決定的）で SipHash を実装**し、**`Random`/RNG 着手後にマップごとのランダムシードへ差し替える**（アルゴリズム・トレイト形は不変・シード源を差すだけ＝additive）。固定キー間は DoS 耐性なし（コンパイラ内部マップには無害・反復順は spec 未規定なので契約は破れない）。**RNG が入ったら必ずランダムシード化すること。**

- **✅ 前提工事＝完了**：(B) が要求する「**メソッド固有型引数 `[H]`＋メソッド `where H: Trait` 境界＋トレイトディスパッチ越しの `inout H`**」は実装済（commit 後述・test `generic_method_bound_inout`）。`registerMethodInst` をプリミティブ受信者にも拡張（`u64.hash[H]` のインスタンスを登録）＋`collectFnInsts` の推移スキャンにレシーバ env を張り（derive struct の `self.field.hash(...)` が field の generic-method インスタンスを推移 discover）。自由関数 `where` 境界・名前付きメソッド呼びは既に動いていた（差はメソッド経路のみだった）。
- **(a) Hash/Dictionary**：
  1. **✅ `wrappingMul`/`wrappingAdd`/`wrappingSub`（整数全幅）**（commit `aabb800`・privileged codegen lowering・uint64_t で計算→受信者幅へ truncate・test `wrapping_arith`）。
  2. **✅ `Hash`/`Hasher` トレイト＋SipHash-1-3 Hasher（Prelude・固定シード）＋U64/String の `impl … as Hash`**（commit `d8eedb6`・test `hash_siphasher`）。同時に extern body-walk バグ修正。
  3. **✅ `@[Hash]` derive を dogfood（特権合成でなく実 `impl Hash as Derive`）**（commit `4167151`・@Std/Syntax・test gen `derivehash`）。前提として trait 提供 assoc fn 呼び（commit `31c6fe1`）＋derive モデル `Derive`(assoc)/`ParameterizedDerive`(instance)（commit `b90ed6e`）を実装。
  4. **🚧 `Dictionary[K,V]` lang item＝struct+メソッド+添字は land 済**（`79436b7`/添字 commit）。**残＝`[k:v]`/`[:]` リテラルのみ**（下記「Dictionary 残作業」＝再帰値型 boxing の罠で保留）。
  現行のコンパイラ特権合成（`synthStructEq` 等＝Eq/Ord）は据え置き（Hash が dogfood の先駆け・Eq/Ord 移行は後）。

## Dictionary 残作業（struct+メソッド+添字は land 済・残＝リテラルのみ）

**状態**：`Dictionary[K,V]` の struct＋メソッド＋**添字 `dict[k]`/`dict[k]=v`** は **land 済**。`Array[U64]` 等を持つ generic struct を Prelude に入れて顕在化した array-element 名解決バグ（真の Bug12）も修正済（`arrayElemNameForRef` が env 依存 `sameMangle` で template 要素 `T` を concrete に誤マッチ→非 ground エントリ skip で解消）。dict-wip ブランチは退役（古い・平行配列回避策含む・main が正本）。**構築は当面 `<Dictionary[K,V] keys=[] vals=[] hashes=[] buckets=[] count=0 />`〔private フィールド露出・可視性ゲート緩い〕＋添字/メソッド**で完動。

### Dictionary の設計（land 済）
- **全て Array 上に構築**（平行配列＝CoW/値意味論は Array から継承）。`compiler/std/Prelude.pw` 末尾：
  `struct Dictionary[K, V] { mut val keys: Array[K]  mut val vals: Array[V]  mut val hashes: Array[U64]  mut val buckets: Array[U64]  pub(get) mut val count: U64 }`
- **open addressing・線形プロービング**。`buckets[slot]` ＝ エントリindex+1（0=空）。`keys`/`vals`/`hashes` は密に append。空構築（全 `[]`）＋初回 insert で grow（cap 0→8）。負荷 0.75 で倍化 grow＋rehash。
- メソッド（`pub impl[K, V] Dictionary[K, V]`・1ブロック＝可視性集約）：`hashOf`/`grow`/`insert`/`find`/`contains`/`getOr`/`at`（欠落 panic＝`dict[k]` の脱糖先）。**`get(key)->Optional[V]` は当面なし**（Optional ambient 化後）。**シード固定**（上の 🔴 RNG TODO）。
- **添字（land 済）**：`dict[k]`→`.at(key:)`／`dict[k]=v`→`.insert(key:,value:)`。base 型が Dictionary のとき codegen が合成 Method ノードを emit（`isDictionaryType`／`synthDictMethod`・Expr.pw Index 枝＋Stmt.pw assign 枝・exprType Index は V を返す）。test run/dictionary_subscript。

### 残＝`[k:v]`/`[:]` リテラル（⚠ 再帰値型 boxing の罠で保留）
- **試行と撤回**：`ExprAst.DictLit(keys: Array[ExprAst], vals: Array[ExprAst])` を `Syntax/Trees.pw` に足し、`ParseBody.pw` の `Kind.LBracket` を dict 検出に拡張、arena `Expr.DictLit` ＋ `lowerDictLit`（context 型は Bug11 の `lowerExprWithCtx` 経由）＋ genExpr の C statement-expression（empty dict 構築＋各ペア insert）＋ exprType/scanExprInsts を実装＝**リテラル自体は動いた**（`["a":1,"b":2]`/`[:]`/unsuffixed 全 OK）。**だが `ExprAst.DictLit` を ExprAst enum に足した瞬間、配列 of compound（`[<P x=1/>]`/`[[1,2]]`）が全部 segfault**＝`lowerExpr(e: ExprAst)` が `e` を**値渡しでコピー**する際の `ExprAst_copy` が壊れた（`match e` のタグ読みで segfault＝コピー結果が garbage）。原因は **再帰値型 ExprAst に新バリアント（しかも `Array[ExprAst]` を 2 本持つ）を足すと auto-boxing/copy 解析が乱れる**（`markBoxedFields`／value-tree の copy 生成）。enum 末尾に置いても再現＝タグ順でなく**バリアント追加そのもの**がトリガ。**全リテラル変更を revert**（main は green 267→添字で 268）。
- **再開方針**：リテラル lower は arena 新バリアント不要にできる（添字と同じく codegen で synthesize）か、`markBoxedFields`/再帰値型 copy が「`Array[ExprAst]` を 2 本持つ新バリアント」で壊れる根因を先に潰す。最小再現＝`ExprAst` に `Foo(a: Array[ExprAst], b: Array[ExprAst])` を足すだけで `[<P x=1/>]` が落ちるはず（要確認）。**当面はリテラル無しでも `<Dictionary[..] .../>`＋`dict[k]=v` で実用可**。
- **注意**：デバッグは必ず `./dev-rebuild.sh`→`compiler/plewc` の1本で（`/tmp/plewcN` を作らない・U64 stderr は `eprintInt` が I64 のみ＝一時 `eprintU`/`eprintSpan`〔stringFromBytes 要 import〕を足して使い終えたら消す）。**dev-rebuild は前回ビルドの plewc を使うので、miscompile 疑いは `./bootstrap.sh`〔種から plewc0→現ソース〕で clean 検証する**。

### Array 干渉が直った後の残り（Dictionary 完成）
- **`[k:v]`/`[:]` リテラル**：`compiler/std/Syntax/ParseBody.pw` の `Kind.LBracket` 分岐（配列リテラル・~328行）を拡張＝`[` の後 `:`+`]` なら空 dict（`[:]`）、最初の式の後が `:` なら dict（`: value` を読み `, k: v` を繰り返す）、それ以外は配列。`ExprAst.DictLit { keys, vals, span }` を `Syntax/Trees.pw` に追加。**lower＝明示型引数で `<Dictionary[K,V] keys=[] vals=[] hashes=[] buckets=[] count=0 />`＋各ペアに insert** を合成（`[:]` の K,V は文脈注釈から）。
- **`dict[k]`**（Index・欠落 panic）→ `.at(key:)` へ脱糖／**`dict[k]=v`**（IndexSet）→ `.insert(key:, value:)` へ脱糖。Dictionary 添字の codegen。
- リテラルを使う run テストを追加（現状は明示構築 `<Dictionary[..] keys=[] .../>` で検証＝private フィールド構築が緩く通っている前提・リテラル lower はコンパイラ合成なので可視性を回避）。
- **(b) M3**：パッケージ管理導入後に `@Std/Syntax` を in-tree から外部共有パッケージへ昇格（コンパイラもマクロも同一版に依存）。
- **小さな additive（任意）**：パターン/構築のフィールド名エラー行が近似（bind/MakeField 名が lower で再インターン＝原本 offset を持たない）。`BindAst`/`MakeFieldAst` に span を持たせ lower で原本 offset を維持すれば行が正確になる。

実装の段取り・実行系の具体は [metaprogramming-architecture.md](metaprogramming-architecture.md)。

## 並行・後続（renovate の残り・ロードマップ）

- **Phase B 残り（要 supervised）**：checks（10 箇所の `exprType`）を typed-AST に統合＝3 重 walker 一本化／pre-fill パスで codegen を完全 pure-read／`exprType` 再導出を駆逐。per-function clear で grounded をキャッシュできたので**テンプレート型は不要**になった。
- **Phase C＝名前 interning**（`spansEqual`/`rangeEquals` 多数を整数比較に・`kwSpan` 系も剥がれる）。**interning＝マップ＝`Dictionary` がツール**なので、**Dictionary が来てから（M2 後）やるのが得**（先にやると手書きハッシュ表になる）。
- **重い D（後日・本物の refactor）**：legacy 型 triple `(start,len,isArray)+ref` の ref 一本化／derive 合成 ~280 行が `Parser/Decl.pw`（＝メタプロ dogfood で置換されるので触らない）。
- **横断 additive**：Iterator 拡充（reduce/take/zip 等）・演算子トレイト全配線（Eq/Ord 以外・需要駆動）・循環回収（Ref グラフ限定サイクルコレクタ）・async tail＋spawn（実スレッド `JoinHandle[T]`）・`any P` 存在型。詳細は [provisional.md](provisional.md)。
- **既知のバグ＝free 関数のモジュール跨ぎ同名衝突**（要修正）：別モジュールに同名の private free 関数があると、同モジュール内の正しい呼び出しが「別モジュールの関数を import せず使用」エラーで誤検出される（例：`@Std/Syntax` に private `digitByte` を足すと本体の同名 `digitByte` 呼びが壊れた→`srcDigitByte` に改名して回避）。期待＝free 関数解決は **same-module 優先**、他モジュールは import 済み名のみ候補。現状は loaded 全モジュールの同名を拾い非 import なら error。一般ユーザーも別モジュールに同名 private 関数を置くと踏む独立バグ（メタプロ/A とは無関係）。

## 再利用資産・罠（git で拾いにくい知見）

- **型付き AST キャッシュ**（現アーキ）：`typeOf(c, id)`＝codegen の型読み口（旧 `exprType` 再導出の代替）。ノード型を `Comp` の **4 並列 scalar 配列**にキャッシュ（self-host は **struct 配列 IndexSet 非対応**ゆえ・`arr[i]=v` の scalar IndexSet は可）。**body emission のエントリ（`genFunc`/`genClosure`/`genAsyncFunc`）で `clearExprTyCache`**＝env（Self/型 args/インスタンス）は 1 body の emission 中だけ一定なので、grounded 型をその間だけキャッシュ・関数境界で破棄（全文脈で安全・filled-id リストのみ reset で O(fills)）。`exprType` は今や `typeOf` 初回 touch／自身の再帰／pre-codegen checks からのみ到達。
- **共有パーサ→arena lower（A）**：共有 @Std/Syntax パーサが値ツリー（`TopItemAst`/`DeclAst`/`ImplAst`/`TraitAst`/`ExternAst`/`ImportAst`/`DirectiveAst`／式文は `ExprAst`/`StmtAst`…）を返し、`Codegen/Lower.pw` が arena（`Expr`/`Stmt`/`Func`/`StructDef`…）へ lower。**名前の offset 規律**＝`moduleOf` に効く名前（free fn 宣言名・call 名・extern fn 名・import/export 名）は**原本 offset 維持**（再インターン不可）、それ以外（struct/enum/field/型名・impl 系全部）は `internBytes` で再インターン（codegen は text 出力ゆえ byte 同一・moduleOf 不参加）。`lowerType` が `recordArrayElem` で `arrayElems` 種まき（旧パーサの codegen 仕事は lower 側へ）。**罠**：パース駆動ローディングで `c.bytes` はファイル源と再インターン名が交互配置になる（各ファイルを追記直後に lower）。writeSpan は text 出力・moduleOf は per-file レンジ参照ゆえ不動点・可視性とも安全（offset 値そのものに依存するロジックは無い）。
- **再帰値型 box**：`markBoxedFields`（`Mono.pw`・`Comp.boxedFields`＝field の `nameStart` キー）が循環を閉じる**ユーザー側フィールド**を box（`Array`/`RawBuffer`/`Ref`/`WeakRef` は cut・`Optional`/`Result` は透過して引数を辿る＝Optional 自体は box せず hardcoded `.data.Some.v` を温存）。`T*`・構築 `genBoxCell`（`curRetTy=fd.ty` で nested JSX を mangle 推論）・読み deref コピー・書き fresh box に repoint（共有セル不変＝値意味論）。box＝`plew_arc_alloc` rc セル・copy/share は retain・release は rc→0 で pointee 再帰 release＋free。**ARC 解放は配線済**だが残リークは print/String の既存ギャップのみ（box 由来 0）。終端なし循環 `struct A{a:A}` は構築不能だが通る（loud reject は将来）。
- **値意味論 ARC の在処**：concrete＝`emitFieldAction`（struct/enum 共有・unique-deinit 込み）、mono＝`emitMonoFieldAction`/`emitMonoModeDef`。**heap フィールド種を足すのはこの 2 dispatcher**。need 判定は `fieldNeedsCopy/Release`・`typeInfoNeedsCopy/Release`。
- **Iterator/generic 機構**：method-level 型パラメータ（`FnInst.recvInstRef`・`registerMethodInst`・mangle suffix は method-own tail のみ）・**demand-driven 単相化**（`providedRetReachable`＝`FilterIter[FilterIter…]` の無限型族を到達時のみ発行）・Self/Item 解決（`curSelfRef`/`curItemRef`＋`resolveTy`）・構造的型推論（`unifyTypeParam`）・impl レベル `where`（funcBounds へ畳む）。**罠**：型パラメータ名 vs 具体型名のグローバル衝突（ユーザー struct `B` と `MapIter[…,B]` の `B`）→ `isTypeParamName` は宣言済 struct/enum 名を具体型扱い。
- **演算子 opcode**：`op` フィールドは `kindCode(Kind)` の整数。`Ops.pw` の `opAdd()..opCoalesce()`（`kindCode(<Kind.X/>)`）が**単一の symbolic 源**（magic 数を codegen に漏らさない）。
- **gen モード（`plew gen`・M0）**：`plewc --gen <file>`＝通常コンパイルの変種。`Comp.genMode`/`genMainIdx`、合成は `Codegen/Gen.pw`（`synthGenMain`＝`@[Name]` ごとに `write(s: <Name/>.deriveFromSource(source:"",start:0,end:0))` を arena AST で組む・`isBuiltinDerive` で Eq/Ord 除外）。driver（`_.pw`）で **①argv `--gen` 検出→entry を argv[2] へ ②`@Std/Io` 強制ロード（harness の `write` 用）③ローダ auto-part 抑制 ④checks 後に `synthGenMain`（import hygiene を回避）⑤body emission で user `main` を skip**。ローダ＝パース木の `Directive` ノードで `@[...]` を検出し `<Foo>.gen.pw`（存在時のみ）を同一モジュール part に enqueue。**罠**：`Expr.Str` は span が引用符込み前提（codegen が `start+1`/`len-2`）＝0 長 span は U64 アンダーフロー panic→合成側で実 `""`（2 バイト）を intern して指す。gen 中は user 自身の `main` が生成物を使っても OK（skip されるので未定義参照でも落ちない）＝「同一モジュール derive」が自然成立。auto-part の loud-fail（gen 未実行で `.gen.pw` 欠落）は directive→マクロ分類が要るので将来。

## ビルド・テスト・機能追加手順

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust 不要）。`./bootstrap.sh --reseed` で種更新（→ `compiler/plewc.seed.c` を commit）。
- **メタプロ生成**：`./plew-gen.sh <file.pw> …`＝`plewc --gen <file> | clang | run > <file>.gen.pw`。`@[...]` 付きファイルに対し derive マクロを走らせ生成 part を吐く（コミットする・通常ビルドが auto-part）。
- **テスト**：`./test.sh`＝`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/part/`（複数ファイル）＋`tests/reject/*.pw`（plewc 非ゼロ＝受理の健全性）＋`tests/panic/*.pw`（compile+link 成功・実行は非ゼロ＋`.panic` stderr 部分一致）＋`tests/gen/*/`（`App.pw`＝マクロ＋`@[...]`／hermetic に gen→auto-part→実行→`App.out` 照合・`.gen.pw` は毎回 $TMP で再生成）＋`tests/genreject/`（`plewc --gen` が reject すべき入力）＋不動点。メモリは `ASAN=1 ./test.sh`。**⚠ macOS の ASan は leak 非対応**（`detect_leaks` 不可）＝UAF/二重free は ASan、リークは `MallocStackLogging=1 leaks --atExit -- <bin>` で検証。
- **機能追加＝ADD→reseed→USE**：新機能を plewc.pw の**ソースで使う**には ①`compiler/src/`（または `compiler/std/`）に足す（ADD）→ ②`--reseed` で種更新→ ③ソースで使う（USE）。「ソースが使う機能は常にひとつ前のコンパイラがサポート済み」を守れば不動点は壊れない。**codegen 出力変化・AST フィールド追加・新 preamble 行は reseed 2 回**、**codegen 出力を変えない検査追加は reseed 1 回**。
- **AST フィールド追加のコツ＝デフォルト値**：`val isPub: Bool = false` とデフォルトを付けると既存の構築点が省略でそのまま通る＝多数の構築点を改修せず済む（`<Comp .../>` リテラルも省略可）。
- **⚠ 落とし穴＝コンパイラは `@Std/Io`→`@Std/Core`／`@Std/Syntax`／`Prelude`（全プログラム自動ロード）を import** するので、これらも「コンパイラ自身がコンパイルするソース」。種がまだ受理しない構文/機能を足すと bootstrap が即壊れる＝**機能を先に種へ焼いてから std で使う**（ADD→reseed→USE）。表現スワップ等の大変更は seam（intrinsic 境界）で担保（→ array-struct-plan.md）。

## 運用メモ

- 動作する区切りで**記述的 git タグ**。コミットメッセージは英語＋`Co-Authored-By`。GPG 署名（`--no-gpg-sign` を使わない・たまに pinentry タイムアウト＝再実行で通る・コミットメッセージにバッククォートを書くと zsh がコマンド置換するので避ける／`-F` でファイル渡し）。
- 不要になった実装は削除し、必要なら git tag から復旧（例：`git checkout stage0-final -- bootstrap`）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。
- C 予約語（`double` 等）と衝突する Plew 識別子は生成 C が壊れる＝名前マングリング未実装（[provisional.md](provisional.md)）。
- LLVM 化は当面しない＝意味論が揃ってから並行バックエンドとして追加（C は捨てない）。
