# Generic 本体の abstract checker（Rust 流・宣言時 bound-aware 型検査）

**決定（2026-06-12・Koji）**：generic 関数/メソッド/trait provided-method の本体は、**宣言時に一度だけ abstract に型検査する**（Rust 流）。C++ template 流（instantiate されたぶんだけ検査・dead は無検査）は採らない。型パラメータ `T` は **不透明な型**として扱い、`T` に対してできる操作は **`where T: Trait` bound が提供する capability のみ**。bound が正当化しない操作（メソッド・演算子・比較）は **instance ではなく定義地点でエラー**にする。

> なぜ：Plew の拠り所「意味は唱えた通り（透明）／曖昧はエラー」に沿う。dead な generic でも本体の型エラーを宣言時に loud に弾く＝C++ template の「使うまでエラーが出ない」ergonomics を避ける。単相化（codegen）は従来どおりで、これと独立（Rust も abstract 検査＋単相化を両立）。

## per-instance 方式を採らない理由（実証済み）

per-instance（インスタンスを置換 env で検査）は **instantiate されないものを一切検査しない**のが原理的限界（dead generic の concrete エラーが漏れる）。また 2026-06-12 の診断で、template を「型パラメータを lenient に通す」方式で verify すると **false-reject と soundness 緩めをトレードするだけ**（5 regression）と確認済み。よって **bound から capability を導く abstract checker** が唯一の筋。詳細は [worklog.md](worklog.md) A 節。

## 既存インフラ（#9 eager generic type-checker＝土台は実装済み）

`Codegen/Check.pw` に既に部分実装があり、設計意図も Rust 流で一致している：

- **`checkGenericBodies(c)`**（Driver から呼ぶ）＝全 generic 本体（`typeParams.count>0` 且つ非 extern）を walk。`curCheckFn`＝検査中の関数 index、params を locals に投入、`checkBoundsBlock` を回す。
- **`checkBoundsExpr/Stmt/Block`**＝本体を walk して bound 検査。
- **`isTypeParamOf(c, fnIdx, start, len)`**＝**関数スコープの**型パラメータ判定（global な `isTypeParamName` ではない・スコープ化済み）。
- **`boundProvidesMethod(c, fnIdx, tpStart, tpLen, name, args)`**＝型パラメータの bound 群（`c.funcBounds`）が当該メンバを提供するか。`traitProvidesMember`（**supertrait 継承込み**・要求 reqs＋provided method の両方）で解決。
- **`boundHasTraitNamed(c, fnIdx, tpStart, tpLen, traitName)`**＝当該型パラメータに特定 trait の bound があるか。
- bound 格納＝**`FuncBound`**（`fnIdx`/`paramNameId`/`traitNameId`…）を `c.funcBounds`。impl-level `where` も各メソッドの funcBounds へ畳み込み済み。
- 関連型束縛＝`AssocBinding`（`type Item = X`）／`assocBindingSpan` で解決。
- instance 側の bound 適合（call-site の `where` 違反）＝`checkFnBounds`/`checkMethodBounds`（**既に reject 済み**＝「制約を満たさない型で呼ぶ」は別経路で弾く）。

### 既にできている検査
- 型パラメータ値への**メソッド呼び** `x.m()` → bound が `m` を提供しなければ reject。
- 型パラメータ値への**比較 `== != < <= > >=`** → `Eq`/`Ord` bound 必須。

## 残ギャップ（完成に必要・確認済み 2026-06-12）

1. **比較以外の演算子に bound 要求が無い**（`a + b` は `Add`、`-a` は `Neg`、`a & b` は `BitAnd`、`a << b` は `Shl`、`!a` は `Not`、`~a` は `BitNot` …）→ いま全部 ACCEPTED。
2. **型パラメータの strict な型同一性が無い**＝`typesCompatible` が型パラメータを `knownNamedTypeId→0` で lenient に通すため、**`T ≠ I64` を検出できない**：`fn f[T](a:T)->I64 { return a }` が ACCEPTED。`val y: I64 = a`（a:T）も同様。`T = T` は OK・`T ≠ U`（別の型パラメータ）は reject・`T` と concrete は reject、を**スコープ付きで**入れる必要。
3. **concrete 部分の full type-check が generic 本体に走っていない**＝`checkGenericBodies` は `checkBoundsBlock`(bound 検査)だけで、`verifyFunc` 相当（return 型・literal-context・tcCheckValue・missing-return…）を回していない。`val y: I64 = true`（concrete）等が漏れる余地。
4. **関連型 `T::Item` は未対応**（チェーン呼びの receiver が型パラメータの結果＝unchecked に degrade／コメント明記）。
5. **field access on T**（`x.field`）＝型パラメータには field 無し→ reject すべき（現状未）。

## 段階プラン（各段は green 増分・self-host 緑維持）

> ⚠ コンパイラ自身が generic を多用。`typesCompatible` を型パラメータに strict 化すると自分の source を誤 reject → 自己再ビルド不能になり得る。各段で `./dev-rebuild.sh`→ダメなら `./bootstrap.sh`（種から）で切り分け。strict 化は**スコープ付き**（`curCheckFn` の型パラメータに限る）で、非 generic / per-instance の lenient 挙動を壊さないこと。

- ✅ **P1＝演算子の bound 要求（done）**：`checkBoundsExpr` の Binary/Unary を拡張。型パラメータ値への算術/ビット/シフト（`Add`/`Sub`/`Mul`/`Div`/`Rem`/`BitAnd`/`BitOr`/`BitXor`/`Shl`/`Shr`）・単項（`Neg`/`Not`/`BitNot`）は対応 bound 必須（`binOpTraitName`/`unOpTraitName`＋`boundHasTraitNamed`）。`typesCompatible` 不触＝安全。test reject generic_op_no_bound/generic_unary_no_bound。残＝`Pow`（float 後）・`&&`/`||`（Bool 要求＝trait でない・別途）。
- ✅ **P2＝strict 型パラメータ同一性（done）**：`typesCompatible` に `curCheckFn` の型パラメータ strict 判定を追加（`T`vs`T`＝spansEqual・`T`vs concrete/別パラメータ＝false）。`checkGenericTypeMatch` が `return`・注釈付き `val` を判定（`inferType`＋`typesCompatible`）。`return a`(T)→`->I64`・`val y:I64=a`・`return b:U`→`->T` を定義地点で reject。**entry-module gate**＝std/prelude は trusted で除外（`Array.get` の `return arrayGet(self,i)` で inferType が要素 `T` でなく `Array` を返す既知の癖を踏むため・`verifyProgram` と同じ gate）。test reject generic_return_typeparam/generic_assign_typeparam/generic_return_other_param。
- ✅ **P3＝concrete full-check の合流＋全位置（done）**：`checkGenericTypeMatch` を **return・注釈 let・call 引数・make フィールド・代入〔plain/compound〕・配列リテラル要素〔再帰〕・concrete-receiver メソッド引数・value 位置 if/match-give** へ拡張＝T 値が concrete 位置へ流れる全経路を定義地点で reject。さらに **concrete binop**〔`1I64+true`／`aT==5I64`〕を `tcCheckBinop` を generic 本体でも走らせて検出〔entry-module gate〕。missing-return は既に generic も検査済。test reject generic_arg/field/method_arg/if_give/assign_concrete/array_elem/concrete_binop_typeparam・run generic_abstract_valid〔valid generic が誤 reject されないことを固定〕。
- ✅ **P4＝field/index access on T を reject（done）**：`x.field`/`x.count` on T は「T は不透明・trait は field を宣言しない」で reject・`x[i]` on T は `where T: Index` 必須。test reject generic_field_on_typeparam/generic_index_no_bound。残＝関連型 `T::Item`〔additive・deferred〕。
- ✅ **trait provided-method 本体の検査（done）**：非 dead は準拠型へのコピーが `verifyProgram` で検査される〔既存〕。**dead〔準拠型ゼロ〕provided-method**も `checkGenericBodies` が entry-module の provided-method を walk して検査〔std の iterator combinators は trusted で除外〕。**Self を abstract 型扱い**＝`isSelfTypeInProvided`〔curCheckFn が provided-method で recv span と一致〕で：(1) `self.notAReq()` を `traitProvidesMember`〔reqs＋provided＋supertrait〕で reject・(2) Self strict 同一性〔`return self`→`->I64` reject〕を `typesCompatible` に追加・(3) `self.req()` の結果型を exprType が trait req の retType〔concrete prim/String〕で回復〔`return self.name()`〔String〕→`->I64` reject〕・(4) concrete エラー〔`return "s"`〕。test reject provided_method_dead_concrete/provided_self_not_requirement/provided_self_result_type・run provided_method_valid。**かつて「supertrait coherence bug」と誤認した件＝幻**：再現に使ったトレイト名 `Sub` が **Core の減算演算子トレイト `Sub[Rhs]` と名前衝突**していただけ（トレイト名は flat namespace・spec/08 で意図的に許容＝`trait_name_collision` 参照）。実害は `instantiateProvidedMethods` が provided method を **trait 名 id だけで**準拠にマッチさせ、0-ary ユーザー `Sub` の provided method を Core `Sub[Rhs]` に準拠する**全整数型へコピー**していたこと。**修正＝arity gate**：provided-method テンプレートに `provTraitArity`（impl 主語の型引数数＝`im.recvType.args.count`）を持たせ、`f.recvId == cf.traitId && f.provTraitArity == cf.traitArgs.count` でコピー（`resolveTraitDef` の name＋arity 主判別と同形）。test run trait_name_collision_provided・provided_method_subtrait。残：同名**かつ同 arity**の二トレイトが両方 provided method を持つ稀ケースは arity で割れない（structural witness まで要・現状未対応の narrow 限界＝既存 `trait_name_collision` も provided なしで回避）。
- **残小＝`val y: T = 5`（literal-context）**＝T が数値 bound を持たねば reject すべきだが inferType(5)=0 で lenient。`val y: T = <untyped literal>` を「T は不透明＝リテラルを受け取れない」で reject する narrow 追加。
- **既知の inferType 癖（要追跡）**＝abstract context で `arrayGet(self,i)` 等の要素型回復が `Array`（head 名）を返す。entry-module gate で回避中だが、user が同型の array-element 回復を書くと false-positive の余地→将来 inferType の element 回復を abstract-aware に直すのが根治。
- **既知の backend ギャップ（別件）**＝generic 関数が generic enum を構築して返す（`fn wrap[T](x:T)->Optional[T]{ return <Optional.Some v=x/> }`）は「construction of this enum not yet supported」＝checker でなく backend の単相化未対応。

## テスト方針

各段で reject テスト（`tests/reject/generic_*`）を足す：`generic_op_no_bound`（P1）・`generic_return_typeparam`（P2）・`generic_assign_typeparam`（P2）等。**valid な generic（bound 付き）が誤 reject されないこと**を run テスト or 既存テストで担保。
