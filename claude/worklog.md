# 作業ログ

> 現在地・**ロードマップ**・運用メモ・**git で拾いにくい再利用知見（罠）**だけを置く。完了した「やった」は git（記述的タグ・コミット）へ。「なぜ・却下案」は [design-decisions.md](design-decisions.md)、パイプライン設計は [architecture.md](architecture.md)、spec からの意図的剥離・暫定（＝残作業の正典地図）は [provisional.md](provisional.md)、メタプロの段取りは [metaprogramming-architecture.md](metaprogramming-architecture.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み・LLVM 単一 backend（C backend 退役・削除済み）。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で全パートを綴じる 1 モジュール）。自分自身を不動点までコンパイル。構文解析は完全に共有 `@Std/Syntax` の責務（コンパイラとマクロが唯一の共有パーサを通る＝真の 1 AST）。`compiler/src/` 本体は共有パーサで parse→`Codegen/Lower.pw` で arena へ lower するだけ。

- **バイナリ 1 本**：`compiler/plewc`（root `_.pw`＝フロントエンド part 群＋`Backend/Llvm`・libLLVM-C をリンク）。`main`＝`runFrontend()`（共有フロントエンド `Codegen/Driver.pw`・`Comp` を返す）→ `emitLlvm()`。
- **受理健全性は emission 非依存の共有パス `Codegen/Verify.pw`**（`verifyProgram`）＝全 non-generic・non-async 関数を walk し spec 不正を弾く。**型は `Codegen/Infer.pw`（TypeRef ベース型チェッカ）**＝`inferType`（精密型 or 0=不明）＋`typesCompatible`（保守的・確定的不一致のみ reject）。
- **self-host**：`./bootstrap.sh`（IR 種 `compiler/plewc.seed.ll`＋`.seed.runtime.c`→clang＋libLLVM→plewc0→自己コンパイル→IR 不動点）。`--reseed` で種更新（→ 種＋追跡バイナリ `compiler/plewc` を commit）。
- **グリーン**：`./test.sh`（run306/panic14/reject282/part＋不動点・fail=0）／`./test-gen.sh`（gen11）。

**実装済みの主要能力の正典地図は [provisional.md](provisional.md)**（spec 章ごとに「✅＝完了／✅でない＝残作業」を列挙）。ここでは再掲しない。大物の経緯は git タグ。

## 🎯 ゴール＝「3 大機能を除く spec 完全準拠」

**並行 spawn・循環回収・パッケージ管理（M3）の 3 つを意図的に後回しにし、それ以外で Plew が完全に仕様通り動く状態を目指す。** 残作業の正典地図は [provisional.md](provisional.md)（＝現コンパイラが spec から意図的に剥離している箇所のカタログ・`✅` でない項が残作業）＝**この 3 つ以外の剥離をすべて潰す**のがゴール。完了の目安＝provisional.md が（3 大機能・spec-future を除いて）すべて `✅` になり、spec 由来の reject/run テストが網羅される。

**スコープ外（このゴールに含めない）**：
- **3 大機能**＝spawn（spec/14）・循環回収（design-decisions）・パッケージ管理（M3）。
- **spec 自身が additive/将来送りにしている項**＝固定長配列 `[E; N]`・const generics・`Slice`・部分文字列・`USize`/`ISize`。

**ツール要件（達成済）**＝任意パスのバイナリ単体で `plew build`/`plew gen` が動く（ⓐ＝relocatable driver＋`compiler/plewc`＋clang・symlink 解決）。真の単一バイナリ ⓑ（plewc が clang を内部 spawn・LLVM 直接オブジェクト出力）は additive な将来 upgrade（要ユーザー確認）。

## 🗺️ ロードマップ（残作業のみ・soundness 優先）

進め方＝[provisional.md](provisional.md)（残作業の正典カタログ・`✅` でない項が残作業）を走査し各剥離を green 増分で潰す→区切りごとに commit＋push＋本ログ更新。優先＝**soundness（spec-invalid を accept しない）** ＞ **hidden meaning（spec-valid を reject／silent 逸脱）** ＞ **hidden cost（leak）**。

### A. soundness（spec-invalid を accept する穴）＝🎉 完了

generic/provided 本体 abstract 検査・use-after-move・generic-receiver grounding・factory 公開ゲート (a)・closure/fn 型ラベル・inout place・array↔scalar・default 自己完結・deinit on unique・重複 trait-req/type-param・bare return ほか、contained な穴は尽きた（~130 probe）。詳細は provisional.md の各 `✅` と git。**設計判断で残したいもの**＝generic 本体検査は **Rust 流（宣言時 bound-aware）＋entry-module gate**で確定＝[generic-abstract-checker.md](generic-abstract-checker.md)（「template を型パラメータ-aware で全 verify」案は false-reject と soundness 緩めをトレードするだけで✗と実証）。

残る soundness は spec が将来送りの 1 件のみ：**重なる inout ②③**（部分/添字重なり＝`a.merge(inout a.field)`・`arr[i],arr[j]` の distinct 証明）＝spec 通り lint＋限定ランタイム panic（ケース①構文同一は実装済）。

### B. hidden meaning（spec-valid を reject／silent 逸脱）＝**実質的に完了**

hidden-meaning 穴は概ね閉じた（ユーザー確認済）。閉じたもの＝match クラスタ（literal pattern・式位置 panic/return・capture-binding・if-let/while-let/guard）・assoc val・global 前方参照・import クラスタ（namespace `Io.print`・path/name/type-value alias・dir module 解決）・演算子トレイト全配線（O1-O8・built-in 算術完全削除・Index/IndexSet・`??`→`unwrapOr`）・一般 Chain `?.`（ネスト含む）・Pow/pow・From/TryFrom（user 型＋整数⇄整数・float→signed/unsigned の数値 matrix＝`@[IntTryFrom]` derive で dogfood 生成）・String 連結＋UTF-8 妥当性・newtype 継承（int/非 int/struct/trait/unique/factory＝spec/10 完全準拠）・factory 機構（named/fallible）・トレイト間準拠 `impl B as A`（spec/08,09 完全＝ベア所有者・拡張第三者・多経路 `#` 選択・連鎖×衝突 viewRoot・境界越し view-aware mono・純加算ビューモデル・ビュー妥当性強制）。各々の経緯は git＋provisional.md の該当 `✅`。

**残は additive/見送り**：
- **Pow の float**（`F64 as Pow[F64]`・超越 intrinsic）＝float 後に additive。
- **複合添字 `a[k] += v`** の一般化（一部済）。
- **Iterator の sum/zip**＝ユーザー判断で見送り（additive・numeric tower〔Zero atom〕設計は未決のまま保留・associated-type bound `Iterator[Item=T]`＋`T.zero()` は動くと確認済）。`enumerate` は ✅（generic record 基盤込み）。
- **import パス正当性の厳密検査**＝今は「ロード済み export 集合に在るか」近似。reject-hardening（hidden-meaning でない）。

### C. hidden cost（leak・観測挙動は正しい・最後）

- **backend 全体の ARC drop**＝array/String/any box・closure 一時・Ref pointee 深い release・mono struct/enum の share/release を scope-exit で。観測挙動不変ゆえテストしにくい＝`leaks`/ASan で検証。**3 大機能の循環回収（要ユーザー確認）が次の主戦場候補**。

### コード整理 TODO（純リファクタ・観測挙動不変）

- **冗長な `if a == b { } else { BODY }` → `if a != b { BODY }`**：self-host 初期の書き癖で empty-then-else 形が compiler/src・std に散在（`!=` は使えるのに）。一括修正（同種の `if a { } else { BODY }` も対象）。要 dev-rebuild＋test＋不動点。

### 横断＝根治 refactor（複数項の根・任意）

- **型パラメータ判定のスコープ化**＝`isTypeParamName` のグローバル名照合が根。これを直すと (i) 単一大文字 struct 名が std メソッド型パラメータ（`fold[B]` の `B`/`F`/…）と衝突して generic 引数に使えない問題、(ii) 型パラメータ名衝突〔現状 crash→reject で回避〕が解消。name-based でなく**スコープ付き param 同一性**へ。〔generic-receiver grounding は本 refactor 無しで解決済ゆえ優先度は下がった〕

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
- **newtype = 別型・underlying 表現**：`Comp.newtypes` テーブル。`llvmScalarTy`/`binWitnessType`/`cmpOperandType` が newtype→underlying 解決（演算子は**両オペランド同一 newtype のときだけ**＝sound・result 型は operand newtype のまま＝Self 置換が自動）。`knownNamedTypeId` が distinct id（型区別）。非 int underlying のメソッド継承は `typeOf` 両用問題で codegen 専用解決点の個別配線が要る（実装済＝`kindFromTySpan`/`primLangItemRecvName` 経由）。

### 値意味論・ARC・再帰値型

- **再帰値型 box**：`markBoxedFields`（`Mono.pw`・`Comp.boxedFields`＝field の `nameStart` キー）が循環を閉じるユーザー側フィールドを box（`Array`/`RawBuffer`/`Ref`/`WeakRef` は cut・`Optional`/`Result` は透過）。box＝`plew_arc_alloc` rc セル。
- **⚠ `Array[Enum]` の要素 deep copy/release**：`arrayElemNeedsDeep`＝`structNeedsCopy` **OR** `enumNeedsCopy`。enum 要素を取りこぼすと heap 持ち variant の `Array[Enum]`（`Array[ExprAst]` 等）が leak＋UAF。**新しく heap を持つ要素種を Array に入れるときは必ずここ**。
- **⚠ by-value 引数のローカルはコピーされず格納されうる**：ヒープ持ち値型の名前付きローカルを by-value で `append` 等に渡すと CoW コピーされず浅く格納→scope 末 release で dangling。**`xs.append(parseFoo())` と一時値で渡す**（根治＝by-value 引数 place の CoW コピー未対応）。
- **値意味論 ARC の在処**：concrete＝`emitFieldAction`、mono＝`emitMonoFieldAction`/`emitMonoModeDef`。**heap フィールド種を足すのはこの 2 dispatcher**。
- **give-block 脱糖**：値位置ブロック＝arena `IfExpr(cond=Int(1,isBool), thenBlk, elseBlk)`（C statement-expression）を合成し then で `mut val __t=…; …; give move __t`、else は dead だが型のため同型値を give。**所有権**＝`give move __t`（deep copy なし移譲・素の `give __t` は shallow＋ブロック末 release で UAF）。

### generic・Iterator 機構

- **generic struct field の array 単相化**：`Array[Box[T]]`/`Array[Entry[K,V]]` は `groundedArrayFieldInfo`（array 枝が要素を instance env で ground）＝`ref` 不変で波及ゼロ。template の非 ground compound 要素は runtime/method を emit しない。**罠**：型パラメータ名 vs 具体型名のグローバル衝突（ユーザー struct `B` と `MapIter[…,B]` の `B`）→ `isTypeParamName` は宣言済 struct/enum 名を具体型扱い。
- **Iterator/generic 機構**：method-level 型パラメータ（`FnInst.recvInstRef`・mangle は method-own tail のみ）・demand-driven 単相化（`providedRetReachable`）・Self/Item 解決（`curSelfRef`/`curItemRef`）・構造的型推論（`unifyTypeParam`）・推移的インスタンス探索（`scanGenInstMethodBodies`）。
- **Iterator 終端/adapter 機構**：終端 `count`/`fold[B]`/`first`/`reduce`/`collect`/`any`/`all`＝`pub impl Iterator` の provided method・lazy adapter（`MapIter`/`FilterIter`/`TakeIter`/`SkipIter`/`EnumerateIter`）受信で動く。**鍵**＝(1) **own-args sidecar** `st.genMethOwn`（gen-method slot を (mfi,instRef,ownArgs) でキー化・`fold[B]` の method-own B を `methodOwnArgs`/`inferFnArgs` で推論）。(2) **`resolveTy` last-match**（own param が conformer の同名 param を正しく shadow）。(3) **provided method の署名計算で Self/Item env**（`setSelfItemEnv`・戻り `Optional[Item]` を ground）＋`llvmFnRetTy` の grounding を `curItemRef`/`curSelfRef` でも発火。(4) 新 adapter は std struct＋`as Iterator`＋`adapterCallResultInst` の名前マッピング 1 行（generic 自動でない）。罠＝非スカラ accumulator の `fold` は collided env ゆえ loud reject（数値は OK）。
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
- **gen モード（`plew gen`）**：fn emission で `c.genMode` 時は `genMainIdx`（合成 harness main）だけを main 扱い。**entry モジュール（module 0）の derive のみ処理**＝`synthGenMain` の `moduleOf(declStart)!=0` skip（std file を gen 時に force-load @Std/Core と二重収集するのを防ぐ）。
- **検証配置の罠**：種ビルド binary は **std の 1 つ上**に置く（`computeStdRoot`＝binary dir＋`std/`）。

### 受理検査の共有パス（`Codegen/Verify.pw`／型チェッカ `Codegen/Infer.pw`）

- **検査は emitter のローカル表 `c.locals` に依存**ゆえ、独立 verify パスでも genFunc 同等に再構築必須（self 環境/curRet/param locals＋ブロックスコープ＋Let/For/Match-arm で `addLocal`）。
- **演算子witness 検査は `hasCompareWitness`/`hasBinTraitWitness` ガードを先に**（`binTraitNeedsTrait` はスカラ算術に常に true＝「witness 必須」の意・単独で呼ぶと valid 算術を誤 reject）。
- **match-arm bind は scrut の型で generic grounding**（`genericFieldTypeInfo`/`genericEnumFieldTypeInfo`）。
- **move 解析は分岐入口で `c.curBranchBase=scopeMark()`**（conditional-move 検出）。
- **verify は型回復後（`buildExprTyTable` の後＝runFrontend 末尾）で呼ぶ**。**async fn は除外しない**（`verifyFunc` が async も walk・返り値は Promise[T]→T を unwrap）。
- **型チェッカ（Infer.pw）の `knownNamedTypeId` が型同一性の根**＝struct/enum/newtype に distinct id、`extern(c)`/float/`any P`/untyped int は判定せず（保守的）。newtype の型区別はここ。
- **ビュー妥当性（`checkViewValid`）は非ジェネリック entry-module body のみ walk**＝レシーバ concrete（strip `#!Ext` と型不明は conservative skip）。トレイト `#P` は `typeConformsTo`、拡張 `#A` は `extAppliesToType`（extId+recvId 照合・newtype underlying 委譲）で妥当性照合。

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
