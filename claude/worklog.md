# 作業ログ

> 現在地・**ロードマップ**・運用メモ・**git で拾いにくい再利用知見（罠）**だけを置く。完了した「やった」は git（記述的タグ・コミット）へ。「なぜ・却下案」は [design-decisions.md](design-decisions.md)、パイプライン設計は [architecture.md](architecture.md)、spec からの意図的剥離・暫定（＝残作業の正典地図）は [provisional.md](provisional.md)、メタプロの段取りは [metaprogramming-architecture.md](metaprogramming-architecture.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み・LLVM 単一 backend（C backend 退役・削除済み）。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で全パートを綴じる 1 モジュール）。自分自身を不動点までコンパイル。構文解析は完全に共有 `@Std/Syntax` の責務（コンパイラとマクロが唯一の共有パーサを通る＝真の 1 AST）。`compiler/src/` 本体は共有パーサで parse→`Codegen/Lower.pw` で arena へ lower するだけ。

- **バイナリ 1 本**：`compiler/plewc`（root `_.pw`＝フロントエンド part 群＋`Backend/Llvm`・libLLVM-C をリンク）。`main`＝`runFrontend()`（共有フロントエンド `Codegen/Driver.pw`・`Comp` を返す）→ `emitLlvm()`。
- **受理健全性は emission 非依存の共有パス `Codegen/Verify.pw`**（`verifyProgram`）＝全 non-generic・non-async 関数を walk し spec 不正を弾く。**型は `Codegen/Infer.pw`（TypeRef ベース型チェッカ）**＝`inferType`（精密型 or 0=不明）＋`typesCompatible`（保守的・確定的不一致のみ reject）。
- **self-host**：`./bootstrap.sh`（IR 種 `compiler/plewc.seed.ll`＋`.seed.runtime.c`→clang＋libLLVM→plewc0→自己コンパイル→IR 不動点）。`--reseed` で種更新（→ 種＋追跡バイナリ `compiler/plewc` を commit）。
- **グリーン**：`./test.sh`（run246/panic12/reject173/part5/fail=0＋不動点）／`./test-gen.sh`（gen10/reject1）。

**実装済みの主要能力**（詳細は spec＋git タグ＋下記 provisional.md／罠。ここは索引のみ）：値意味論＋CoW＋ARC 解放・`unique`/`move`/`borrow`/`deinit`＋move 所有権検査・幅つき整数（overflow/0除算 panic・リテラル文脈型付け）・浮動小数 F32/F64（実用上完成）・**本物の型チェッカ**（型混同 garbage 穴解消）・受理健全性の広範なハードニング・ジェネリクス（単相化・`where` 制約・関連型・aggregate 内 generic-inst フィールド by value）・**ユーザー定義トレイト**（準拠・提供メソッド・bound 越し・継承・blanket・`any P` 存在型）・**演算子トレイト全配線**（算術/ビット/単項/比較・built-in 算術完全削除）・**拡張 `#Ext`**（struct 完備）・**enum/primitive メソッドディスパッチ**・**async/await 段階 1-3**（stackless SM・イベントループ）・コアライブラリ Plew 化（`@Std/Core`/`Io`/`Process`/`Async`/`Random`・Array＝RawBuffer 床の Plew struct）・ambient `@Std/Core`・**可視性完全強制**・トップレベル変数・メタプロ M0/M1/M2（derive・Dictionary lang item）・**無名レコード**（型/リテラル/`.field`/多値返却/punning/分解/for 分解/construction-field & call-arg context＋method-arg & nested record context）・**newtype**（int underlying 完備＝別型・`as`・算術/比較演算子継承）・**RNG**（`@Std/Random`＋Dictionary ランダムシード）・**整数リテラル基数**（`0x`/`0o`/`0b`＋桁区切り `_`）・**構築フィールドゲート (b)**（cross-module 非 pub フィールド reject）・**lang-item 再定義 reject**・**型パラメータ名衝突→crash 回避 clean reject**・**再帰 generic 値型**（self/mutual・struct/enum・construct/match/access end-to-end）。

## 🎯 ゴール＝「3 大機能を除く spec 完全準拠」

**並行 spawn・循環回収・パッケージ管理（M3）の 3 つを意図的に後回しにし、それ以外で Plew が完全に仕様通り動く状態を目指す。** 残作業の正典地図は [provisional.md](provisional.md)（＝現コンパイラが spec から意図的に剥離している箇所のカタログ・`✅` でない項が残作業）＝**この 3 つ以外の剥離をすべて潰す**のがゴール。完了の目安＝provisional.md が（3 大機能・spec-future を除いて）すべて `✅` になり、spec 由来の reject/run テストが網羅される。

**スコープ外（このゴールに含めない）**：
- **3 大機能**＝spawn（spec/14）・循環回収（design-decisions）・パッケージ管理（M3）。
- **spec 自身が additive/将来送りにしている項**＝固定長配列 `[E; N]`・const generics・`Slice`・部分文字列・`USize`/`ISize`。

**ツール要件（達成済）**＝任意パスのバイナリ単体で `plew build`/`plew gen` が動く（ⓐ＝relocatable driver＋`compiler/plewc`＋clang・symlink 解決）。真の単一バイナリ ⓑ（plewc が clang を内部 spawn・LLVM 直接オブジェクト出力）は additive な将来 upgrade（要ユーザー確認）。

## 🗺️ ロードマップ（残作業を soundness 優先で）

進め方＝provisional.md を走査し、3 大機能・spec-future を除いて各剥離を 1 つずつ green 増分で潰す→各区切りで commit＋push＋本ログ更新。**soundness（受理健全性＝spec-invalid を accept しない）を最優先**、次に hidden meaning の小逸脱、最後に hidden cost（leak）。

### A. soundness（spec-invalid を accept する穴＝最優先）

- ✅ **構築フィールドゲート (b)（spec/05）**＝cross-module で非 `pub` フィールド設定を loud reject（`checkConstructVis`＋`StructDef.defOffset`＋`offsetIsLoaded`・dict literal 等の synthesize 構築は除外）。**残＝公開ゲート (a)**（全 pub でも外部構築は `pub impl factory` 要）は `factory` 宣言機能と一括。
- ✅ **lang-item 型の再定義を loud reject**（`isLangItemTypeName`＋`checkLangItemRedef`・`StructDef`/`EnumDef.defOffset` で entry-module 判定・extern intrinsic は skip・test reject redefine_langitem）。
- ✅ **曖昧な無サフィックス整数リテラルのオーバーロードを loud reject**（`checkOverloadAmbiguity`/`overloadsAmbiguous`・free-fn＋method 両経路・test reject overload_ambiguous_literal）＝既存実装で網羅済。
- ✅ **int↔float 暗黙変換を loud reject**（`typesCompatible` の float 免除を both-float に絞り＝`val x:F64=nI64`/`I64=3.5`/`f(F64)` with I64 arg を reject・以前は silent miscompile・test reject float_int_no_implicit/float_literal_to_int）。
- ✅ **mixed int/float 比較を loud reject**（`tcCheckBinop` を全 primitive-numeric ペアに拡張＝`aI64 < bF64`・以前は silent mix・test reject compare_int_float）。
- ✅ **型パラメータ名衝突クラッシュ→clean reject**（`instArgCollidesParamName`・struct/enum・test reject typeparam_name_collision）。
- **重なる inout のケース②③**（部分/添字重なり＝`a.merge(inout a.field)`・`arr[i],arr[j]` の distinct 証明）＝spec 通り lint＋限定ランタイム panic（ケース①構文同一は実装済）。〔受理健全性は int/float/幅/sign/struct/Optional 引数・代入・比較・配列要素・dict 値・if 枝・return・move/unique/可視性/overflow/missing-return/網羅性すべて reject 確認済〕

### B. hidden meaning の小逸脱（spec-valid を reject／silent 逸脱）

- **newtype メソッド/フィールド継承＋非 int underlying**（`userId.bytes`〔UserId=String〕）＝broad な codegen 解決が要る（`localStructIdxFor`/`kindFromTySpan`/`exprStructIdx`/非 int `as` を newtype→underlying 解決・ただし `typeOf` は型チェッカ distinction と両用ゆえ blanket 解決不可＝codegen 専用解決点を個別配線）。int underlying は完備。newtype の残＝unique/deinit/factory 継承・`export newtype`。
- **`as` 以外の数値変換 `From`/`TryFrom`**（縮小・パース・`as` の全域変換脱糖・`try` の異エラー型 From 変換）・**float→int `as`**・**mixed `1.5 + 2`**（無型 int リテラル推論）。
- **一般 Chain トレイト `?.`**（現 Optional 具体）・**`Pow`/`**`**（float 後）・**`Output != Self`**。
- ✅ **method への record literal context**（`methodArgType`・test method_record_arg）・✅ **nested record literal**（record branch が canonical 名を `lowerMakeFields` へ・test nested_record_literal）。
- ✅ **generic-enum/struct 構築の call/method 引数 context**（`<Optional.Some v=5I64 />` を直接 arg 渡し＝`genArgValue` が generic-inst param の型を `st.expectedTy` にセット→backend の既存 fallback が ground・**backend-only ゆえ provider body を壊さない**・test generic_enum_ctor_arg）。**残＝無型 int payload** `v=5`（check-side literal-context・lowering 採用は std 破壊で revert 済・回避 `v=5I64`）。
- **`\u{XXXX}` Unicode エスケープ**＝U64→U8 truncation primitive が要る（`truncU8` を runtime `plew_*` シンボル化か、compiler の extern intrinsic 呼びが genLlvmCall intercept を通るか確認・provisional §文字列）。
- **Bool dict キー**＝Bool primitive メソッドディスパッチ（backend 未対応・低価値）。〔✅ method 値化 `val f = obj.method` は loud reject 済〕
- ✅ **recursive generic value type**（`Node[T]{next:Optional[Node[T]]}`・`Tree[T]`＝構築/match/field access end-to-end・test recursive_generic）＋ ✅ **generic struct の非 int param フィールド**（`L[String].v` を print＝`valueKind` の Field を base env で ground）。残〔follow-up・非クラッシュ〕＝相互再帰 generic（`A[T]`↔`B[T]`）。
- **トレイト/拡張の残小物**＝トレイト引数 aware の多重 conformance 区別・コンテナ不変性 `Array[P]`≠`Array[P#Ext]`・型レベル chained `Type#A#B`。
- **module/import 残**＝名前空間 import（`Io.print`）・`as` リネームの実束縛・`_.pw` ディレクトリ解決・パス正当性厳密検査。
- **Iterator 残**＝`sum`（Zero/数値タワー待ち）・`enumerate`（(index,item) ＝無名レコード活用で可になった・要実装）・`zip`（2 イテレータ）。
- ✅ **【bug】ユーザー struct/enum 名が lang-item 型パラメータ名と衝突＝クラッシュ→clean reject 化**（`instArgCollidesParamName`・test reject typeparam_name_collision）。根治（スコープ化した型パラメータ同一性）は将来・回避＝リネーム。
- **その他小（残）**＝`assoc val`（static・parser 未）・generic assoc-fn emission（`Box.make(x:7)`/`Set[E].empty()`＝mono 必要・backend 大）・式位置 `panic`（文位置は✅）・guard 文（parser 未）・match ガード/ネストパターン・namespace import `Io.print`（parser+解決）。〔✅ 済＝place 越し compound `arr[i].field OP= x`・`arr[i].inoutMethod()`・struct-in-struct 構築〕

### C. hidden cost（leak・観測挙動は正しい・最後）

- **backend 全体の ARC drop**＝array/String/any box・closure 一時・Ref pointee 深い release・mono struct/enum の share/release を scope-exit で。観測挙動不変ゆえテストしにくい＝`leaks`/ASan で検証。

### スコープ外（3 大機能・別途）

- **`spawn`/`JoinHandle`/チャネル**＝async 安定後・実スレッド pthread・境界で CoW eager 実体化・`Ref` 不可・spawn 境界の意味論強制・`local` 伝染解析（重い・言語仕様判断あり）。
- **循環回収**＝Ref グラフ限定サイクルコレクタ（Bacon–Rajan trial deletion・設計は design-decisions 済）。
- **M3 パッケージ管理**＝導入後に `@Std/Syntax` を in-tree→外部共有パッケージへ昇格。

## 既知バグ（要修正・上の B/A に再掲ありの実害バグ）

- ✅ lang-item 型パラメータ名衝突（`struct V` × `Dictionary[K,V]`）＝**クラッシュ→clean reject 化**（`instArgCollidesParamName`・test reject typeparam_name_collision）。根治（name-based でない型パラメータ同一性）は将来。回避＝該当型をリネーム。
- 無注釈 `<Result.Ok value=… />` 構築の return/call-arg context＝**動作確認済**（genArgValue が `st.expectedTy` を流す・generic_enum_ctor_arg／手元検証）。残懸念があれば再現を残す。

## 再利用資産・罠（git で拾いにくい知見）

### フロントエンド・arena・型機構

- **型付き AST キャッシュ**：`typeOf(c, id)`＝codegen の型読み口。ノード型を `Comp` の **4 並列 scalar 配列**にキャッシュ（self-host は struct 配列 IndexSet 非対応ゆえ）。**body emission のエントリ（`genFunc`/`genClosure`/`genAsyncFunc`）で `clearExprTyCache`**＝env（Self/型 args/インスタンス）は 1 body の emission 中だけ一定なので grounded 型をその間だけキャッシュ・関数境界で破棄。`buildExprTyTable` は slot を allocate するだけで充填はしない（typeOf が emission 中に遅延充填）。
- **共有パーサ→arena lower**：共有 @Std/Syntax パーサが値ツリー（`TopItemAst`/`DeclAst`/…）を返し、`Codegen/Lower.pw` が arena（`Expr`/`Stmt`/`Func`/`StructDef`…）へ lower。**名前の offset 規律**＝`moduleOf` に効く名前（free fn 宣言名・call 名・extern fn 名・import/export 名）は**原本 offset 維持**、それ以外（struct/enum/field/型名・impl 系全部）は `internBytes` で再インターン。
- **block 0 は dummy 予約**：`body` フィールド 0 は「無本体」sentinel。entry ファイルは ambient Prelude より先に lower されるので予約しないと最初の関数本体が block 0 に来て無本体と誤判定。
- **名前/型 interning（Phase C＋D）**：`intern(c, start, len) -> U64`＝span の**内容**を 1-based id に。**0 は返さない**＝`nameId`/`tyNameId` の既定 0 が「未設定」sentinel。唯一の content-keyed テーブルを宣言名と型名が共有。`TypeRef.nameId` の choke point＝`pushType`。**罠**：①構築点を 1 つ漏らすと id=0 で converted スキャンが取りこぼす silent miscompile（「Bind を返すヘルパ」が raw `<Bind/>` で nameId を落とすと比較が恒偽）。②Local は動的＝`addLocalCn` で intern。③スキャンは「クエリを 1 回 intern→ループは整数 ==」。
- **演算子 opcode**：`op` フィールドは `kindCode(Kind)` の整数。`Ops.pw` の `opAdd()..` が単一の symbolic 源。
- **負リテラル畳み込みは lower で実装済**：`lowerExpr` が `Unary(Neg, IntLit)` を符号付き `Expr.Int`（`isNeg`）へ畳む（precedence 解決後ゆえ `-128.foo()` は real Neg）。新リテラル種を足すなら `Expr.Int` の全 match/構築点に `isNeg` を通す。
- **⚠ ambient Core に「よくある名前」を入れると衝突**：①bare 呼びは assoc fn を拾わない（`findFunc` は `hasRecv`＋`isAssoc` も skip・assoc は `Type.` 必須）。②conformance は型パラメータ arity も一致で照合。
- **missing-return 検査**（`Check.pw checkReturns`）：非 `()` 関数の本体が全経路で発散しなければ loud エラー（末尾式の暗黙 return なし）。
- **⚠ オーバーロード解決は局所 struct 引数の型を front-end で見れない**：`findFunc`/`paramsTypesMatch` は `exprType`（front-end）依存だが、局所変数は `c.locals` 非投入ゆえ struct 値の型が scalar 化＝ラベルのみで照合→first-by-label（順序依存）。型/ビューで選び分けるには backend で精緻化（`findFuncViewAware`）。新たに「引数の型/属性でオーバーロードを分ける」機能は同じ壁。
- **無名レコード = 合成 struct**：`lowerType` が record TypeAst を canonical 名 `(n:key,...)`（ソート済フィールド・`recordTypeKey`＝head＋arg-head のみ）の合成 StructDef に変換し既存 struct 機構を再利用。**construction-field/call-arg context**＝`makeFieldType`（owner 型名＋variant＋isEnum で field 宣言型を引く・owner decl は body より source 順で先に登録済）／`callArgType`（非 generic free fn を名前+label で一意解決）が dict/record/`()` literal に context を与える。罠＝generic owner では field 型が param ゆえ無型 int は grounding されない。
- **newtype = 別型・underlying 表現**：`Comp.newtypes` テーブル。`llvmScalarTy`/`binWitnessType`/`cmpOperandType` が newtype→underlying 解決（演算子は**両オペランド同一 newtype のときだけ**＝sound・result 型は operand newtype のまま＝Self 置換が自動）。`knownNamedTypeId` が distinct id（型区別）。非 int underlying のメソッド継承は `typeOf` 両用問題で codegen 専用解決点の個別配線が要る（未）。

### 値意味論・ARC・再帰値型

- **再帰値型 box**：`markBoxedFields`（`Mono.pw`・`Comp.boxedFields`＝field の `nameStart` キー）が循環を閉じるユーザー側フィールドを box（`Array`/`RawBuffer`/`Ref`/`WeakRef` は cut・`Optional`/`Result` は透過）。box＝`plew_arc_alloc` rc セル。
- **⚠ `Array[Enum]` の要素 deep copy/release**：`arrayElemNeedsDeep`＝`structNeedsCopy` **OR** `enumNeedsCopy`。enum 要素を取りこぼすと heap 持ち variant の `Array[Enum]`（`Array[ExprAst]` 等）が leak＋UAF。**新しく heap を持つ要素種を Array に入れるときは必ずここ**。
- **⚠ by-value 引数のローカルはコピーされず格納されうる**：ヒープ持ち値型の名前付きローカルを by-value で `append` 等に渡すと CoW コピーされず浅く格納→scope 末 release で dangling。**`xs.append(parseFoo())` と一時値で渡す**（根治＝by-value 引数 place の CoW コピー未対応）。
- **値意味論 ARC の在処**：concrete＝`emitFieldAction`、mono＝`emitMonoFieldAction`/`emitMonoModeDef`。**heap フィールド種を足すのはこの 2 dispatcher**。
- **give-block 脱糖**：値位置ブロック＝arena `IfExpr(cond=Int(1,isBool), thenBlk, elseBlk)`（C statement-expression）を合成し then で `mut val __t=…; …; give move __t`、else は dead だが型のため同型値を give。**所有権**＝`give move __t`（deep copy なし移譲・素の `give __t` は shallow＋ブロック末 release で UAF）。

### generic・Iterator 機構

- **generic struct field の array 単相化**：`Array[Box[T]]`/`Array[Entry[K,V]]` は `groundedArrayFieldInfo`（array 枝が要素を instance env で ground）＝`ref` 不変で波及ゼロ。template の非 ground compound 要素は runtime/method を emit しない。**罠**：型パラメータ名 vs 具体型名のグローバル衝突（ユーザー struct `B` と `MapIter[…,B]` の `B`）→ `isTypeParamName` は宣言済 struct/enum 名を具体型扱い。
- **Iterator/generic 機構**：method-level 型パラメータ（`FnInst.recvInstRef`・mangle は method-own tail のみ）・demand-driven 単相化（`providedRetReachable`）・Self/Item 解決（`curSelfRef`/`curItemRef`）・構造的型推論（`unifyTypeParam`）・推移的インスタンス探索（`scanGenInstMethodBodies`）。
- **Iterator 終端/adapter 機構**：終端 `count`/`fold[B]`/`first`/`reduce`/`collect`/`any`/`all`＝`pub impl Iterator` の provided method・lazy adapter（`MapIter`/`FilterIter`/`TakeIter`/`SkipIter`）受信で動く。**鍵**＝(1) **own-args sidecar** `st.genMethOwn`（gen-method slot を (mfi,instRef,ownArgs) でキー化・`fold[B]` の method-own B を `methodOwnArgs`/`inferFnArgs` で推論）。(2) **`resolveTy` last-match**（own param が conformer の同名 param を正しく shadow）。(3) **provided method の署名計算で Self/Item env**（`setSelfItemEnv`・戻り `Optional[Item]` を ground）＋`llvmFnRetTy` の grounding を `curItemRef`/`curSelfRef` でも発火。(4) 新 adapter は std struct＋`as Iterator`＋`adapterCallResultInst` の名前マッピング 1 行（generic 自動でない）。罠＝非スカラ accumulator の `fold` は collided env ゆえ loud reject（数値は OK）。
- **generic 呼び出しの引数 T 推論には arg 型に名前 span が要る**：`inferFnArgs`→`tyRefOfInfo` は `nameLen==0` で 0。リテラル等の typeOf が名前なし TypeInfo を返すと T 未推論。`Expr.Str`/String(kind 1) は名前 span 付与済。

### LLVM backend（`Backend/Llvm.pw`・ヘッダ＋コメントに詳細）

- **ディスパッチ**：ユーザー関数/メソッドは合成名 `pf<idx>`／generic は `gm<mfi>_<instRef>`＋index→キャッシュ `LLVMValueRef`。`c.locals` 非投入なので env に locKind/locStructIdx/locTypeRef を持たせて型判定。
- **narrowing `as` 不在**ゆえ LLVM API の count/index/aggregate-index 系 U32 パラメータは**バインディングで U64 宣言**。
- **match payload bind はフィールド名で punning**＝`val x` は「フィールド x を束縛」・別名は `field: val local`（bare `val fbase` は非存在フィールド punning で self-compile を壊す）。
- **aggregate（struct/enum/array）に icmp/extractvalue を非 aggregate へ誤適用すると LLVM builder が SEGV**＝必ず `LLVMGetTypeKind==10/exprIsArray` でガード。null sentinel は `LLVMIsNull`。
- **array は `{ptr,i64}`** で element-size generic runtime。配列リテラルは elemTy を束縛/param の annotation から取る（i64 デフォルト混入を防ぐ）。inout param/self は alloca せず**ポインタ param を locPtr 直結**。
- **メソッド emission をエントリモジュール限定に**＝std メソッド本体（未対応構文だらけ）を引き込まないよう、call-graph 到達可能性で必要な std だけ遅延 emit（`ensureProvidedDeclared`/`ensureGenMethodDeclared`/`ensureFreeFnDeclared`）。primitive lang-item は extern struct ゆえ nested-struct 判定で extern を除外。
- **⚠ alloca は全て entry ブロックへ**（`entryAlloca`＝entry の terminator 直前へ挿入）。builder 位置で alloca を吐くと loop body で反復ごとに stack が積もり大入力 SEGV（clang は entry へ hoist するので C から来ると起きない罠）。
- **⚠ inline enum payload のサイズ**：`fieldWords` は enum 型フィールドを `1 + enumPayloadWords(eid)` words と数える。過小だと大 variant 構築で隣接破壊。
- **checked 算術床**：add/sub/mul/div/rem/neg は runtime helper `plew_<w><Op>`（i8-i64 符号別・`__builtin_*_overflow`＋ガード）経由＝overflow/0除算 loud panic。`buildBinOpS` は wrapping 床（`wrapping*` 専用）。
- **`extern(c)` 不透明ハンドル型**（`StructDef.isCExtern`）は `llvmScalarTy` でも `ptr` に落とす（i64 既定だと invalid IR）。
- **for-over-array の element 追跡**：`genLlvmForArray` がループ変数を element の struct index＋TypeRef で束縛（field access/method dispatch が効く）。**primitive 要素は `structRegSlot` ゲートで除外**（scalar を struct 誤認しない）。generic-instance 要素は `genStructSlot`。
- **gen モード（`plew gen`）**：fn emission で `c.genMode` 時は `genMainIdx`（合成 harness main）だけを main 扱い。
- **検証配置の罠**：種ビルド binary は **std の 1 つ上**に置く（`computeStdRoot`＝binary dir＋`std/`）。

### 受理検査の共有パス（`Codegen/Verify.pw`／型チェッカ `Codegen/Infer.pw`）

- **検査は emitter のローカル表 `c.locals` に依存**ゆえ、独立 verify パスでも genFunc 同等に再構築必須（self 環境/curRet/param locals＋ブロックスコープ＋Let/For/Match-arm で `addLocal`）。
- **演算子witness 検査は `hasCompareWitness`/`hasBinTraitWitness` ガードを先に**（`binTraitNeedsTrait` はスカラ算術に常に true＝「witness 必須」の意・単独で呼ぶと valid 算術を誤 reject）。
- **match-arm bind は scrut の型で generic grounding**（`genericFieldTypeInfo`/`genericEnumFieldTypeInfo`）。
- **move 解析は分岐入口で `c.curBranchBase=scopeMark()`**（conditional-move 検出）。
- **verify は型回復後（`buildExprTyTable` の後＝runFrontend 末尾）で呼ぶ**。**async fn は除外**（`return n` が Promise 中身型を返すため）。
- **型チェッカ（Infer.pw）の `knownNamedTypeId` が型同一性の根**＝struct/enum/newtype に distinct id、`extern(c)`/float/`any P`/untyped int は判定せず（保守的）。newtype の型区別はここ。

## ビルド・テスト・機能追加手順

- **ビルド（self-host）**：`./bootstrap.sh`＝IR 種→clang＋libLLVM→`plewc0`→`_.pw` 自己コンパイル→IR 不動点 cmp。`./bootstrap.sh --reseed` で種更新（→ 種 `.ll`/`.runtime.c`＋追跡バイナリ `compiler/plewc` を commit）。編集中の高速反復は `./dev-rebuild.sh`（現 `compiler/plewc` が src を再コンパイルして自分をその場上書き）。**⚠ dev-rebuild は前回ビルドの plewc を使う**ので、miscompile を疑うときや verify 誤 reject で自己再ビルド不能なときは `./bootstrap.sh`（種から clean）で切り分け。**libLLVM がビルド必須依存**（IR 種は版に結合＝大改版で要 `--reseed`）。
- **テスト**：`./test.sh`（run/panic/reject/part＋不動点・メモリは `ASAN=1`〔macOS の ASan は leak 非対応〕）／`./test-gen.sh`（メタプロ gen/genreject）。reject は SKIP マスクなし（単一 backend）。
- **メタプロ生成**：`./plew-gen.sh <file.pw>`＝`plewc --gen <file>`→clang→run > `<file>.gen.pw`（`@[...]` 付きファイルに derive を走らせ生成 part を吐く・コミット・通常ビルドが auto-part）。
- **機能追加＝ADD→reseed→USE**：新機能を plewc.pw の**ソースで使う**には ①`compiler/src/`（または `compiler/std/`）に足す→②`--reseed` で種更新→③ソースで使う。**codegen 出力変化・AST フィールド追加・新 preamble 行・intercept 追加は reseed 2 回**、**codegen 出力を変えない検査追加は reseed 1 回**。
- **AST フィールド追加のコツ**：`val isPub: Bool = false` とデフォルトを付けると既存の構築点が省略で通る。**arena Expr/AST バリアント追加**は exhaustive な `match` 全箇所（`ExprAst`/`StmtAst` は `Lower.pw` の `lowerExpr`/`lowerStmt`・`TopItemAst` は `lowerTopItem`/`lowerExportItem`＋`Syntax.pw` の derive matcher）にケース追加＝reseed 2 回。
- **⚠ コンパイラは `@Std/Io`→`@Std/Core`／`@Std/Syntax`／`Prelude` を import** するので、これらも「コンパイラ自身がコンパイルするソース」。種がまだ受理しない構文を std で使うと bootstrap が即壊れる＝機能を先に種へ焼く。
- **⚠ コンパイラ内で extern intrinsic を使う罠**：`extern "plew-intrinsic"` を **compiler 自身が呼ぶ**（std でなく）と、genLlvmCall の name-intercept を経ず undefined シンボルになり得た（`truncU8` で発生）。compiler が使う truncation 等は runtime `plew_*` シンボル化を検討。

## 運用メモ

- 動作する区切りで**記述的 git タグ**。コミットメッセージは英語＋`Co-Authored-By`。GPG 署名（`--no-gpg-sign` を使わない・pinentry タイムアウトは再実行で通る／詰まったら手元で `echo test | gpg --clearsign` でパスフレーズキャッシュ／**コミットメッセージにバッククォートや `<…/>` を書くと zsh がコマンド置換/リダイレクトで壊すので避ける・`-F` でファイル渡しか平文化**）。
- scratch は repo 直下の `tmp/`（gitignore 済）。直接コマンドに `rm` を書くと毎回確認が出るので cleanup はスクリプトに内包。
- 不要になった実装は削除し、必要なら git tag から復旧（例：`git checkout stage0-final -- bootstrap`）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。
