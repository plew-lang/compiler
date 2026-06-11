# 作業ログ

> 現在地・**ロードマップ**・運用メモ・**git で拾いにくい再利用知見（罠）**だけを置く。完了した「やった」は git（記述的タグ・コミット）へ。「なぜ・却下案」は [design-decisions.md](design-decisions.md)、パイプライン設計は [architecture.md](architecture.md)、spec からの意図的剥離・暫定（＝残作業の正典地図）は [provisional.md](provisional.md)、メタプロの段取りは [metaprogramming-architecture.md](metaprogramming-architecture.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み・LLVM 単一 backend（C backend 退役・削除済み）。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で全パートを綴じる 1 モジュール）。自分自身を不動点までコンパイル。構文解析は完全に共有 `@Std/Syntax` の責務（コンパイラとマクロが唯一の共有パーサを通る＝真の 1 AST）。`compiler/src/` 本体は共有パーサで parse→`Codegen/Lower.pw` で arena へ lower するだけ。

- **バイナリ 1 本**：`compiler/plewc`（root `_.pw`＝フロントエンド part 群＋`Backend/Llvm`・libLLVM-C をリンク）。`main`＝`runFrontend()`（共有フロントエンド `Codegen/Driver.pw`・`Comp` を返す）→ `emitLlvm()`。
- **受理健全性は emission 非依存の共有パス `Codegen/Verify.pw`**（`verifyProgram`）＝全 non-generic・non-async 関数を walk し spec 不正を弾く。**型は `Codegen/Infer.pw`（TypeRef ベース型チェッカ）**＝`inferType`（精密型 or 0=不明）＋`typesCompatible`（保守的・確定的不一致のみ reject）。
- **self-host**：`./bootstrap.sh`（IR 種 `compiler/plewc.seed.ll`＋`.seed.runtime.c`→clang＋libLLVM→plewc0→自己コンパイル→IR 不動点）。`--reseed` で種更新（→ 種＋追跡バイナリ `compiler/plewc` を commit）。
- **グリーン**：`./test.sh`（run248/panic12/reject185/part5/fail=0＋不動点）／`./test-gen.sh`（gen10/reject1）。

**実装済みの主要能力**（詳細は spec＋git タグ＋下記 provisional.md／罠。ここは索引のみ）：値意味論＋CoW＋ARC 解放・`unique`/`move`/`borrow`/`deinit`＋move 所有権検査・幅つき整数（overflow/0除算 panic・リテラル文脈型付け）・浮動小数 F32/F64（実用上完成）・**本物の型チェッカ**（型混同 garbage 穴解消）・受理健全性の広範なハードニング・ジェネリクス（単相化・`where` 制約・関連型・aggregate 内 generic-inst フィールド by value）・**ユーザー定義トレイト**（準拠・提供メソッド・bound 越し・継承・blanket・`any P` 存在型）・**演算子トレイト全配線**（算術/ビット/単項/比較・built-in 算術完全削除）・**拡張 `#Ext`**（struct 完備）・**enum/primitive メソッドディスパッチ**・**async/await 段階 1-3**（stackless SM・イベントループ）・コアライブラリ Plew 化（`@Std/Core`/`Io`/`Process`/`Async`/`Random`・Array＝RawBuffer 床の Plew struct）・ambient `@Std/Core`・**可視性完全強制**・トップレベル変数・メタプロ M0/M1/M2（derive・Dictionary lang item）・**無名レコード**（型/リテラル/`.field`/多値返却/punning/分解/for 分解/construction-field & call-arg context＋method-arg & nested record context）・**newtype**（int underlying 完備＝別型・`as`・算術/比較演算子継承）・**RNG**（`@Std/Random`＋Dictionary ランダムシード）・**整数リテラル基数**（`0x`/`0o`/`0b`＋桁区切り `_`）・**構築フィールドゲート (b)**（cross-module 非 pub フィールド reject）・**lang-item 再定義 reject**・**型パラメータ名衝突→crash 回避 clean reject**・**再帰 generic 値型**（self/mutual・struct/enum・construct/match/access end-to-end）・**型チェッカ soundness ハードニング**（int↔float 暗黙変換/比較 reject・`any P` 非準拠 reject・generic bare-`T` 引数一貫性・closure body 検査＋closure-arg 戻り型・call/method VALUE 引数 type-check・if/while 条件 Bool 必須・**primitive binop の RHS 型一致**〔`1I64+true`〕・**`&&`/`||` Bool オペランド**・**比較の cross-type**〔`"a"==1I64`〕・**複合代入の型一致**〔`x+=true`〕・**`as` の Bool↔numeric 拒否**・**配列 append / dict literal+insert の要素・K/V 型一致**）。

## 🎯 ゴール＝「3 大機能を除く spec 完全準拠」

**並行 spawn・循環回収・パッケージ管理（M3）の 3 つを意図的に後回しにし、それ以外で Plew が完全に仕様通り動く状態を目指す。** 残作業の正典地図は [provisional.md](provisional.md)（＝現コンパイラが spec から意図的に剥離している箇所のカタログ・`✅` でない項が残作業）＝**この 3 つ以外の剥離をすべて潰す**のがゴール。完了の目安＝provisional.md が（3 大機能・spec-future を除いて）すべて `✅` になり、spec 由来の reject/run テストが網羅される。

**スコープ外（このゴールに含めない）**：
- **3 大機能**＝spawn（spec/14）・循環回収（design-decisions）・パッケージ管理（M3）。
- **spec 自身が additive/将来送りにしている項**＝固定長配列 `[E; N]`・const generics・`Slice`・部分文字列・`USize`/`ISize`。

**ツール要件（達成済）**＝任意パスのバイナリ単体で `plew build`/`plew gen` が動く（ⓐ＝relocatable driver＋`compiler/plewc`＋clang・symlink 解決）。真の単一バイナリ ⓑ（plewc が clang を内部 spawn・LLVM 直接オブジェクト出力）は additive な将来 upgrade（要ユーザー確認）。

## 🗺️ ロードマップ（残作業のみ・soundness 優先）

進め方＝[provisional.md](provisional.md)（残作業の正典カタログ・`✅` でない項が残作業）を走査し各剥離を green 増分で潰す→区切りごとに commit＋push＋本ログ更新。優先＝**soundness（spec-invalid を accept しない）** ＞ **hidden meaning（spec-valid を reject／silent 逸脱）** ＞ **hidden cost（leak）**。完了済みは上の capability 索引＋ provisional の `✅`。**以下は残のみ。**

### A. soundness（spec-invalid を accept する穴＝最優先）

- **ファクトリ公開ゲート (a)（spec/05）**＝全 pub フィールドでも cross-module 構築は `pub impl Type { factory }` 明示要。`factory` 宣言機能と一括（現状は (b) フィールドゲート＝非 pub を弾く・のみで、全 pub 型は許容＝spec (a) より緩い）。
- **generic-receiver method の value 引数 grounding**＝`w.set(5I64)` on `W[String]` が silent miscompile（`substTypeInfo`/`mf.typeParams` が impl param `T` を ground し切らず素通し）。2 回試行とも失敗＝(1) method-own param を含めると `fold[B]` 等を誤 reject、(2) **owner struct/enum の typeParams で ground**（`ownerTypeParamsForRef`）してもコンパイラ自身の source を誤 reject〔`expected=I64 got=U64 from=Field:ref`〕＋ tmp/w.pw では grounding が走らず（recv=W の genericRecv は true だが substitution が String を返さず素通し）＝**name-based 同一性の interning 衝突／index 整合がここでも噛む＝下の「横断＝型パラメータ判定のスコープ化」を先に直さないと安全に潰せない**。共有のクラッシュ事例〔dict 添字キー〕は別経路で reject 済。
- **重なる inout ②③**（部分/添字重なり＝`a.merge(inout a.field)`・`arr[i],arr[j]` の distinct 証明）＝spec 通り lint＋限定ランタイム panic（将来・ケース①構文同一は実装済）。
- **use-after-move 未検出**＝`take(move u); take(move u)` を accept（move 後の再使用が reject されない・backend は moved-out local を deinit 除外するだけで front-end の線形追跡なし）。**flow-sensitive linear move 解析が要る**＝conditional/partial move 含め未実装・naive 追跡はコンパイラ自身の多用する `move` を誤 reject する危険（bare-copy/伝染/`move fn` self は実装済）。spec/03。

> 受理健全性は広く確認済（int/float/幅/sign/struct/Optional/enum payload・引数/代入/複合代入/比較/論理/return/配列要素〔ネスト含む〕/dict literal+insert K/V/append 要素/range 両端/field & default arg/if-while 条件 Bool/closure 戻り型/void 値使用/`as` の Bool↔numeric/単項 String/move/unique/可視性/overflow/missing-return/網羅性をすべて reject）。**残る既知の soundness 穴**＝use-after-move〔flow 解析要〕・fn-value 署名不一致〔fn 型 TypeRef 復元要〕・generic 型注釈の arity〔`Box[I64,String]` annot・低 harm〕・generic-receiver method の value 引数 grounding〔横断 refactor 連動〕。

### B. hidden meaning（spec-valid を reject／silent 逸脱）

- **`From`/`TryFrom`**（数値縮小・パース・`as` の全域変換脱糖・`try` の異エラー型 From 変換）・**float→int `as`**。〔✅ **mixed float context は完了**＝`1.5+2` / `F64=5` / `-3` / `Array[F64]` / call-arg / 両オペランド無型 `10/4`〕。
- **newtype 非 int underlying のメソッド/フィールド継承**（`userId.bytes`〔UserId=String〕＝codegen 専用解決点の個別配線・`typeOf` 両用問題ゆえ blanket 不可）＋ unique/deinit/factory 継承・`export newtype`。int underlying は完備。
- **一般 Chain トレイト `?.`**（現 Optional 具体）・**`Pow`/`**`**（float 後）・**`Output != Self`**。
- **無型 int generic-enum payload** `<Optional.Some v=5 />`（check-side literal-context・lowering 採用は std 破壊で revert・回避 `v=5I64`）。
- **Iterator 残**＝`sum`（Zero/数値タワー待ち）・`enumerate`／`zip` は backend ブロッカー：**`enumerate`**（Item＝合成レコード `(index:U64,value:E)`＝型パラメータ E をフィールドに持つレコードの**monomorphized iterator 文脈での構築/フィールドアクセス**が未対応＝`<…value=v/>` で「construction of this type not yet supported」・`pair.index` で「field access only on a registered struct」＝generic-record 登録が要る backend 仕事〔小 std add では済まない〕）・**`zip`**（第2要素型＝`J::Item`＝型パラメータの抽象関連型が必要＝`generic 抽象 T::Item` 未対応ゆえ表現不能）。
- **module/import 残**＝名前空間 import（`Io.print`）・`as` リネームの実束縛・`_.pw` ディレクトリ解決・パス正当性厳密検査。
- **トレイト/拡張小物**＝トレイト引数 aware の多重 conformance 区別・コンテナ不変性 `Array[P]`≠`Array[P#Ext]`・型レベル chained `Type#A#B`。
- **その他小**＝`assoc val`（static・parser 未）・generic assoc-fn emission（`Box.make(x:7)`/`Set[E].empty()`＝mono 必要・backend 大）・式位置 `panic`（文位置は✅）・`guard` 文（parser 未）・match ガード/ネストパターン・Bool dict キー（低価値）・global 前方参照。

### C. hidden cost（leak・観測挙動は正しい・最後）

- **backend 全体の ARC drop**＝array/String/any box・closure 一時・Ref pointee 深い release・mono struct/enum の share/release を scope-exit で。観測挙動不変ゆえテストしにくい＝`leaks`/ASan で検証。

### 横断＝根治 refactor（複数項の根）

- **型パラメータ判定のスコープ化**＝`isTypeParamName` のグローバル名照合が根。これを直すと (i) 単一大文字 struct 名が std メソッド型パラメータ（`fold[B]` の `B`/`F`/`E`/`P`/`I`/`T`/`U`/`K`/`V`）と衝突して generic 引数に使えない問題、(ii) 型パラメータ名衝突〔現状 crash→reject で回避〕、(iii) 上の generic-receiver method grounding の取りこぼし、が一括で解消。name-based でなく**スコープ付き param 同一性**へ。

### スコープ外（3 大機能・spec-future）

- **`spawn`/`JoinHandle`/チャネル**（async 安定後・実スレッド pthread・境界で CoW eager 実体化・`Ref` 不可・`local` 伝染解析・言語仕様判断あり・spec/14）。
- **循環回収**（Ref グラフ限定サイクルコレクタ・Bacon–Rajan trial deletion・設計は design-decisions 済）。
- **M3 パッケージ管理**（導入後に `@Std/Syntax` を in-tree→外部共有パッケージへ昇格）。
- **spec 自身が将来送り**＝固定長配列 `[E; N]`・const generics・`Slice`・部分文字列・`USize`/`ISize`。

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
