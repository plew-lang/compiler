# 暫定実装と仕様からの意図的剥離（provisional / intentional deviations）

現コンパイラ（正典＝`compiler/src/_.pw`・Plew 製）が `SPEC.md`／`spec/*.md` から**意図的に**省いている箇所の一覧＝「これはバグでなく既知の暫定」＝**残作業の地図**。各項は **仕様（正典）→ 現状（剥離）→ 理由/再訪**。**`✅` は完了（git タグ＝正典）で経緯参照のため一行に縮約**・**`✅` でない項が本書の本体＝残作業**。優先度・順序は [worklog.md](worklog.md)「🗺️ ロードマップ」。

- **2 つのゴール**：①**受理の健全性（accepted ⟹ spec-valid）**＝受理するコードは spec でも valid（逆向きの不完全性＝spec valid だが reject は許容）。直すべきは「spec は reject するのに今 accept」＝hidden meaning だけ。②**ソース spec-validity**＝`compiler/src/*.pw` 自体が純 spec-valid（コンパイラは自分を受理＝①が完全なら②も自動）。enforce は plewc.pw 自身にも適用（import 必須・全呼びラベル付き等・ADD→reseed→USE で不動点維持）。
- **hidden meaning（観測挙動が spec から逸れる）と hidden cost（裏でコストだけ）は別物**＝前者（値意味論・overflow panic・ラベル等）は必ず埋める／後者（ARC/CoW を leak で代用等）は正しく実装するが leak 状態でも観測挙動は正しい。
- ✅ **受理健全性の共有パス `Codegen/Verify.pw`（`verifyProgram`）＋型チェッカ `Codegen/Infer.pw`（TypeRef ベース）**＝emission 非依存で spec 不正を弾く。型チェッカは `inferType`（精密型 or 0=不明・untyped int は 0）＋`typesCompatible`（保守的・確定的不一致のみ reject）＝Bool↔整数・別 named 型・引数/return 型不一致・混合幅算術/比較・✅ **primitive numeric LHS の二項演算で RHS 型不一致**（`1I64 + true`／`1I64 < true`＝以前は両オペランド numeric のときだけ照合し片側 Bool を素通し→silent miscompile・`tcCheckBinop` の `rNum` ゲートを外し numeric LHS なら常に RHS を `l` と照合・test reject binop_int_bool）・generic 引数違い（`Optional[I64]≠Optional[String]`）・✅ **`&&`/`||` の非 Bool オペランド**（`1I64 && true`＝短絡制御フローは Bool 専用・以前未検査→silent miscompile・test reject logical_non_bool）・✅ **比較 `==`/`<` の cross-type**（`"a" == 1I64`＝Eq/Ord は同一型〔no Rhs〕ゆえ全型で operands 一致必須・以前は numeric LHS のみ照合・test reject compare_cross_type）・✅ **複合代入の型不一致**（`x: I64; x += true`/`x += "a"`＝binop と同じく numeric target は value 一致必須・`tcCheckCompoundAssign` の両側ゲートを外す・test reject compound_assign_bool）・✅ **`as` の Bool↔numeric**（`true as I64`/`1I64 as Bool`＝Bool は非 numeric ゆえ `as` 不可・`castOperandIsBool`＋target 判定・newtype↔underlying は不変・test reject cast_bool_to_int/cast_int_to_bool）・✅ **primitive-element 配列 append の型不一致**（`Array[I64].append(true)`＝`checkLitSpan` は bool リテラルを素通し→`tcCheckValue` を element 型に対し追加〔primitive element に限定〕・test reject append_wrong_elem）・✅ **dict literal/insert の K/V 不一致**（`["a": 1I64, "b": true]`／`d.insert(key:, value:)`＝generic-receiver の insert を K/V 直接照合〔checkMethodArgs に Dictionary 特例〕・test reject dict_literal_value_type）・✅ **int↔float 暗黙変換**（both-float のみ免除）・✅ **mixed int/float 比較**（`tcCheckBinop` 全 primitive-numeric ペア）・✅ **`any P` 非準拠 coercion**（`conformExists`・以前 runtime crash）・✅ **generic 呼びの bare-`T` 引数一貫性**（`tcCheckGenericArgConsistency`・free-fn＋method・以前 silent miscompile）を解消。✅ **value 引数 type-check**（call＝free-fn・method〔非 generic receiver〕の VALUE 引数を `tcCheckValue`・closure body 戻り型〔`verifyExpr` が closure を walk〕・closure-arg 戻り型・if/while 条件 Bool・void fn の値 return）。✅ **dict subscript キー型**（`d[5I64]` on `Dictionary[String,_]`＝以前 crash・`checkIndexKeyType` で Index 読み/書き両方を reject・test reject dict_key_type_mismatch）。**残 soundness follow-up**〔narrow・既知〕：**generic-receiver method の value 引数 grounding**〔`w.set(5I64)` on `W[String]`＝`substTypeInfo`/`mf.typeParams` が impl param `T` を ground し切らず素通し・試行は `fold[B]` 等 method-own type-param を持つ iterator を誤 reject→revert・method-own param 除外の grounding が要る〕・overloaded 呼びの引数・generic 引数の nested `Array[T]` 位置・codegen を tc の型へ移行〔任意・大〕。

## メモリ・所有権

- ✅ **値意味論＋CoW＋ARC 解放**（非アトミック refcount・`Array[T]` は `RawBuffer` 床の Plew struct・束縛は O(1) 共有＋retain・変異点で複製・scope/早期 exit で再帰解放・ASan clean）。残：`WeakRef`・**循環回収**〔スコープ外〕・mono struct/enum の share/release〔mono 局所 leak・安全〕。spec/03。
- ✅ **`unique`/`borrow`/`move`/`deinit`＋健全性ハードニング**（決定的破棄・bare コピー/伝染を loud reject・`Ref[unique]` の最後の解放で deinit・`mut val` unique 再代入・`move fn` self）。**残（soundness 穴）＝use-after-move 未検出**〔`take(move u); take(move u)` を accept＝`u` を move 後に再使用しても reject されない・backend は moved-out local を deinit から除外するだけで front-end の線形追跡なし・heap 持ち unique では意味的に不正〔現状クラッシュはしないが二重 move〕・**flow-sensitive な linear move 解析が要る**＝conditional/partial move も含め未実装・naive な追跡はコンパイラ自身の多用する `move` を誤 reject する危険〕。残（N/A）：部分 move/return・条件付き move/消費。spec/03。
- **`local` 型**（spawn を越えられない）→ 無し。spawn 段で。spec/03,14。
- ✅ **`inout`＋合成可変性検査**（単純変数・`base.field`・`a[i]`・`.append`/`inout fn`）。spec/03。
- **重なる `inout`**（1 呼びで複数 inout が同じ場所）→ ✅ **ケース①構文同一を loud reject**（arg×arg/self×arg・`exprSyntaxEq`・test overlapping_inout*）。**残＝ケース②③＝部分/添字重なり**（`a.merge(inout a.field)`・`arr[i],arr[j]` の distinct 証明）＝spec 通り lint＋限定ランタイム panic は将来。spec/03。
- ✅ **place 越し get-modify-set 脱糖**（`arr[i].field = x`＝`tryArrayElemFieldAssign`・Arrow place 代入の右辺リテラル型付け・✅ compound 要素 `arr[i].field OP= x`・✅ `arr[i].inoutMethod()`）。spec/03。

## 数値モデル

- ✅ **幅つき整数 `I8..U64`**（厳密幅 stdint・U8=`unsigned char`〔.bytes 共有〕・**overflow/0除算 panic**〔intrinsic 床〕・リテラル文脈型付け＋厳密 no-default＋U64 magnitude モデル・幅不明な式の算術は loud error・`wrapping*` メソッドは additive 予定）。
- ✅ **浮動小数 `F32/F64`（実用上完成）**＝リテラル/local/関数引数戻り/`Array[F64]`/struct フィールド/算術〔fadd 等〕/比較〔ordered fcmp＋**NaN panic**〕/print〔Format〕/int→float `as`・✅ **int↔float 暗黙変換を loud reject**〔`val x:F64=nI64`・`I64=3.5`＝以前 silent miscompile・`typesCompatible` の float 免除を both-float に絞った・test reject float_int_no_implicit/float_literal_to_int〕・✅ **無型 int リテラルの float context `val x: F64 = 5` / `1.5 + 2` / `-3` / `Array[F64]=[1,2.5]` / `takesF(x: 7)` / `10 / 4`**〔checkLitTi が float→eKind 2＝既存「非 int は skip」・`floatCtxCode`〔9=F64/10=F32〕を exprIntCtx へ・`intCtxKw` が F64/F32 を返し typeOf が float を復元・backend Int 枝が float type のとき uitofp で double emit・`checkArithNoCtx` が float sibling を検出・`valueKind` の Int 枝が float context のとき 4〔両オペランド無型の `10/4` も float binop へ〕・test run float_int_literal_ctx〕。**残**：**float→int `as`**〔TryFrom〕・**真の F32**〔当面 double〕・`%` は整数限定で reject〔spec 通り〕。spec/02,12。
- ✅ **整数リテラル基数＋桁区切り**（`0x`/`0o`/`0b`＋`_`・float `_` も・test int_literal_bases）。spec/02。

## レンジ

- **`a..<b`/`a..=b` は第一級の値**（`HalfOpenRange`/`ClosedRange`・`Step` で反復）→ **現状：`for` ヘッドでしか書けない**（その場で C for ループに脱糖・レンジ型/値/`Step`/素の `..` は無い）。ループ変数型注釈は実装済（`for val i: I32 in 0..<5`）。✅ **両端の型一致**（`0I64..<5I32`＝幅混在を reject＝`checkLitSpan` は suffixed literal を自身の suffix でしか検査しないため `tcCheckValue` を var 型・両端に追加・test reject range_bound_width）。spec/02,11。

## 文字列

- `String`＝不変・UTF-8 妥当・`==` バイト等価な CoW 値型 → **現状：`{ptr,len}`・不変・byte-`==`**（不変と byte-eq は spec 通り）。残：**UTF-8 妥当性チェックなし**・**連結なし**・**`scalars`/`graphemes`/`Ord`/substring/`Slice` なし**・解放なし〔leak〕。`.bytes`（`Array[U8]` O(1) ビュー）は spec 通り。spec/02。
- ✅ **文字列リテラルのエスケープ**：`strDecodeBytes`/`escByte` が `\n`/`\t`/`\r`/`\0`＋`\\`/`\"`/`\'` を decode 済。✅ **`\u{XXXX}` Unicode エスケープ**（`café`＝`\u{e9}`・絵文字＝`\u{1F600}`）＝`appendUtf8`/`hexDigitVal` が UTF-8 1-4 byte に encode・U64→U8 truncation は `truncU8` intrinsic〔Core の `extern "plew-intrinsic"`＋genLlvmCall intercept で `coerceInt`→i8・bitCastU64 と同形〕。chicken-and-egg は ADD（intercept のみ）→reseed→USE→reseed の2段 reseed で解消（intercept を先に seed へ焼く）。test run unicode_escape。spec/02。

## 配列・辞書・集合・タプル

- ✅ **`Array[T]`（値意味論＋CoW＋解放・添字 U64・範囲外 panic・複合要素 `Array[Ref[T]]`/`Array[Box[T]]`/`Array[Array[T]]`・generic struct/関数での単相化）**。残る小 hidden-cost ARC 残留〔no UAF〕：fresh-temp append の box 1 つ leak・heap 持ち Ref pointee の深い release・ネスト配列 inner-array 要素 ARC。`[E;N]`/const generics/`Slice`/部分文字列は **spec 自身が保留**〔スコープ外〕。
- ✅ **`Dictionary[K,V]`（lang item・`[k:v]`/`[:]`・SipHash-1-3・`get`/`dict[k]` 欠落 panic・複合添字 `d[k]+=v`・per-process ランダムシード〔DoS 耐性〕・キー型 `U8..U64`/`I8..I64`〔`bitCastU64`〕/String・String 値）**。残＝**`Bool` キー**〔Bool primitive メソッドディスパッチ未対応＝低価値〕。**`Set[E]`** → **未実装**（非 lang item・import 要・前提＝construction-field 推論は✅／generic assoc fn が未＝`Set[E].empty()` が「assoc fn not emittable」＝generic method declare-on-demand の assoc 版が要る・回避＝注釈ローカル＋JSX 構築）。
- ✅ **ラベル付き無名レコード `(x: I32, y: I32)`**（型注釈/リテラル/`.field`/多値返却/フィールド順独立〔canonical ソート＝構造的同一性〕/関数跨ぎ同一性/record param/value-semantics コピー/struct・enum payload/合成 struct 機構〔`ensureRecordStruct`〕/**分解 `(val x, val y) = p`**/**punning `(x, y)`**/**for 分解 `for (val x, val y) in xs`**/**construction-field & call-arg context**〔dict/record/`()` literal が field/param 型から推論〕/for-over-array element 追跡/✅ **method への record literal context**〔`methodArgType`・method 名+label が一意のとき param 型採用・test method_record_arg〕/✅ **nested record literal**〔record-of-records の inner literal context＝record branch が canonical 名を `lowerMakeFields` に渡す・test nested_record_literal〕）。**残**：(c) **inline `()` の generic field 構築**〔`<Result.Ok value=()/>`＝generic owner で field 型が param ゆえ grounding されず・変数経由で✅〕・(d) **canonical 名の full-type 厳密化**〔`recordTypeKey` は head＋arg-head のみ〕・(e) **無注釈 destructure-assign の nested record**〔`(val a,val b)=(a:(x:1),...)` ＝context なし inner literal〕。✅ **generic-enum/struct 構築の call/method 引数 context**〔`take(o: <Optional.Some v=5I64/>)`＝`genArgValue`→`st.expectedTy`・test generic_enum_ctor_arg・残＝無型 int payload `v=5` は check-side gap〕。spec/02。

## 型システム：ジェネリクス・トレイト・拡張

- ✅ **再帰値型**（`struct A { child: Optional[A] }`＝field-level auto-boxing＋CoW ARC・観測挙動も解放も正しい・5000 ノード 0 leaks）。✅ **generic 再帰値型 `Node[T]{next:Optional[Node[T]]}`・`enum Tree[T]{Branch(l:Tree[T],r:Tree[T])}` も完全動作**〔構築・match・field access end-to-end・test recursive_generic：linked list/tree〕＝5 link（markBoxedFields generic guard 除去／boxed-field 構築型 ground／`registerGenStructBodies` で instance layout box／`bindMatchPayload` の structIdx を `genStructSlot`／boxed-field read を base env で ground）。✅ **相互再帰 generic 値型**〔`Ping[T]`↔`Pong[T]`＝`nameReachesOwner` を `genericStructIndex` でも引き相互サイクルを box・test recursive_generic〕。残〔minor〕：終端なし循環（住人なし＝構築不能・将来 loud reject）。spec/03。⚠ **単一大文字 struct 名は std メソッド型パラメータ（`fold[B]`/`map[B]` の `B`/`F`/`E`/`P`/`I`/`T`/`U`/`K`/`V`）と衝突＝`isTypeParamName` グローバル照合で「not ground」化し generic 引数に使えず clean error〔回避＝リネーム・根治＝スコープ化〕。
- ✅ **ジェネリクス `[T]`/`[T,U]`**（単相化・generic struct/enum/fn/`impl[T]`・`where T: Trait` 制約＋メソッド own 型パラメータ＋推移的インスタンス化・`inout H` をトレイトディスパッチ越し・関連型 `type Item`・ネスト generic 単相化〔`groundedArrayFieldInfo`〕・generic コンストラクタ JSX 型引数推論・aggregate 内 generic-inst フィールド by value）。残 additive：**generic free 関数の明示型引数 `id[I32](x)`**〔推論は動く〕・**assoc 呼出位置の型推論**〔`Box.make(x:7)` の戻り T〕・generic 抽象 `T::Item`〔concrete では不要〕。spec/06,08。
- ✅ **トレイト（ユーザー定義・準拠・提供メソッド・bound 越しディスパッチ・継承 `trait Sub: Super`・`where T: Trait[Args]`・blanket impl・`any P` 存在型）**。**残る剥離**：(1) **トレイト引数 aware の多重 conformance 区別**＝bound パイプラインが型引数を表現せず `where T: Into[I64]` ≡ `where T: Into`〔arity 照合・引数 aware は将来〕。(2) **blanket の限界**＝bound 必須・subject param が self 以外で出る `fn convert() -> T` の T→具体置換なし・primitive/無準拠型は未対象。spec/08。
- ✅ **演算子→トレイト脱糖（O1-O8）**（ユーザー型＋プリミティブの算術/ビット/単項/比較が witness 脱糖・built-in 算術完全削除・Index/IndexSet・Chain `?.`〔Optional 具体〕・`??`→`unwrapOr`）。残＝**一般 Chain トレイト**・**`Pow`/`**`**〔float 後〕・**`Output != Self`**。spec/12。
- ✅ **拡張 `#Ext`（struct レシーバで完備）**（値/型ビュー・`defaultExtension`・`#P` 源選択・self-view/`#!Ext`/スタック `#A#B`・明示ビュー強制4面・view-aware オーバーロード・トレイト主語 impl・外部型コヒーレンス）。**残る剥離**：(a) **コンテナ不変性 `Array[P]`≠`Array[P#Ext]`**〔exotic・保留〕・(b) **型レベル chained `Type#A#B`**〔param に2 view・値レベルは可〕。〔enum/primitive ext レシーバは enum/primitive メソッドディスパッチ実装で自動解消＝済〕。spec/09。
- **`newtype`（spec/10）** → **int underlying 完備（sound）**：別型・underlying 表現・`as` ゼロコスト再タグ・**型区別**〔`knownNamedTypeId` distinct id＝`val x: I64 = meter` を reject〕・**算術/比較演算子継承**〔両同一 newtype のみ underlying witness 解決＝sound・result は operand newtype＝Self 置換自動・`Meter + I64`/`Meter == I64` は reject〕。test newtype_basics・reject newtype_mix/newtype_arith_mix。**残（follow-up）**＝(a) **メソッド/フィールド継承＋非 int underlying**〔`userId.bytes`〔UserId=String〕＝`localStructIdxFor`/`kindFromTySpan`/`exprStructIdx`/非 int `as` を newtype→underlying 解決・ただし `typeOf` は型チェッカ distinction と両用ゆえ codegen 専用解決点の個別配線が要る・2026-06-11 試行で field access 落ち→revert〕・(b) **unique/deinit 自動継承**・(c) **factory 継承**・(d) **`export newtype`**〔現状 recordExport せず〕。foundation は sound（受理は spec-valid のみ）。

## 関数・呼び出し

- ✅ **引数ラベル必須・宣言順・オーバーロード**（セレクタ＝名前＋ラベル＋型頭で C マングル・arity/label/type 解決・`~:` 抑制・デフォルト引数〔末尾省略〕）。残：**関数型同一性へのラベル反映**・**関数値の署名不一致が未検出（soundness 穴）**〔`val f: fn(x: String)->String = twice`〔twice=fn(I64)->I64〕を accept→garbage 呼び・`inferType`/`typeOf` が fn-value の型を kind 0 に潰すため照合不能・以前の fn-value 型検査試行は false-reject で revert＝fn 型の TypeRef 復元が要る〕・オーバーロードした関数値〔first-by-name〕・デフォルト引数の中間省略/配列・struct デフォルト・I/O ビルトイン非検査。spec/04,07。
- ✅ **インヘレントメソッド**（`fn`/`inout fn`/`move fn`/`borrow fn` self・引数型オーバーロード）。残：一時値レシーバへの `inout`。spec/07。
- ✅ **クロージャ／関数値**（fat closure `PlewClosure{fn,env,rc,drop}`・不変値キャプチャ＋スカラー `mut val` 参照キャプチャ〔箱化＝`makeCounter`〕・leak 解消〔0 leaks/UAF 無し〕）。**残（loud reject）**：`mut val` 非スカラー参照キャプチャ・`unique`/generic/enum/関数値キャプチャ・ネスト closure・val capture への代入。残 hidden cost：引数直渡し一時 capturing 閉包・Ref キャプチャ pointee。spec/04。

## 制御フロー・match

- ✅ **`match` 網羅性検査**（`_` or 全 variant・rename/discard/or パターン・全フィールド束縛必須・フィールド名実在検査・値位置 `match`/`if`〔`give`〕）。残：束縛名一致だが型食い違いは C エラー fallback・**ガード・ネストパターン無し**・到達不能アーム警告無し。spec/11。
- ✅ **構築/分解の全フィールド明示必須**（struct パターン・enum payload・`<S wrongfield=…/>` 実在検査・`for (val x, val y) in xs` の record 分解）。spec/05,11。
- **`for (val k, val v) in dict`** → dict 反復子待ち〔別機能〕。**`guard` 文** → 無し（`KwGuard`/`Stmt.Guard` 無・条件チェーン束縛は `if`/`while`/`guard` 横断の別 feature）。spec/11。
- ✅ **`panic`（発散文）**。残：**式位置の `panic`**（statement-match の arm `=> panic` は✅〔`parseArmBodyAst`→`parseStmtAst`〕／**value-match の arm `val x = match … { _ => panic }` は未**）。2026-06-12 試行＝parser は `parseExprArmBodyAst` で `panic`/brace block を受理できたが、**backend value-match は arm body を単一 give-expr 前提**（`lowerMatchArms` の isExpr 枝が `arm.body.stmts[0]` を Give と仮定し panic arm を `emptyExpr` に落とす＝silent miscompile・IR は arm を丸ごと drop）＝**直すには value-match arm を block-bodied 化〔IfExpr 値ブロックと同形〕＋ emitter が diverging arm を検出して PHI から除外**（`st.terminated` チェック）が要る＝backend rework。parser だけ入れると silent miscompile ゆえ revert。if-else 値ブロック `if c { give } else { panic }` は✅。

## 演算子・変換

- ✅ **対応**：算術 `+ - * / %`・比較 `== != < <= > >=`・論理 `&& ||`・ビット/シフト `& | ^ << >> ~`・単項 `! - ~`・代入＋複合〔ビット系含む〕・`Optional.unwrapOr`〔旧 `??`〕・添字 `[]`/`[]=`〔Index/IndexSet〕・Chain `?.`〔Optional 具体〕。
- **未対応**：`pow`/`**`〔`Pow[Exp]`・float 後〕・`?.` の一般トレイト化〔現 Optional 具体〕・**`as` 以外の数値変換 `From`/`TryFrom`**〔縮小/パース・`try` の異エラー型 From 変換＝現状 `try` は `E==E'` 一致要求〕・`Output != Self`。
- ✅ **`as`**＝数値↔数値の C キャスト〔無損失検査済・narrowing reject〕。
- ✅ **`try`**＝Result 早期 return〔Ok=tag0/`value`・Err=tag1/`error` レイアウト前提・非 Result〔特に Optional〕operand は loud reject〕。無注釈 `<Result.Ok value=…/>` 構築は return/call-arg context で**動作確認済**〔`genArgValue`→`st.expectedTy`〕。spec/12,13。
- ✅ **曖昧な無サフィックス整数リテラルのオーバーロードを loud reject**（`checkOverloadAmbiguity`/`overloadsAmbiguous`・free-fn＋method・test reject overload_ambiguous_literal）。✅ **`val f = obj.method`（メソッド値化）を loud reject**（`verifyFieldReadVis`＋`typeHasMethodNamed`・annotated/inferred 両 local）。
- ✅ **【bug】ユーザー struct/enum 名が lang-item 型パラメータ名と衝突＝クラッシュ→loud reject 化**（`struct V {…}` × `Dictionary[K,V]`・`instArgCollidesParamName`・test reject typeparam_name_collision）。根治（name-based でない型パラメータ同一性＝スコープ化）は将来・回避＝リネーム。

## 可視性・モジュール・import

- ✅ **可視性 `export`/`import with`/`pub impl`/`pub`/`pub(get)` 完全強制**（`moduleOf`＋`checkImports`／`checkUseVisibility`＋メンバ可視性）。**残・未実装**＝名前空間 import（`Io.print` 形・今は `with { }` 選択のみ）／`as` リネームの実束縛／`_.pw` ディレクトリ解決／パス正当性厳密検査〔今は「ロード済み export 集合に在るか」近似〕。spec/15。
- ✅ **`part`／`import` パスルート**（`part ./Name`/`./Sub/Name`・`@Std/X` は binary 横 `std/X.pw`・`with { }` 選択）。残：`_.pw` ディレクトリ・ネスト part・forest/循環検査・名前空間 import。配布時の bare 名起動の stdRoot は別途。spec/15。
- ✅ **ambient `@Std/Core`**（演算子 witness/`Optional`/`Result`/`for`/range が import 不要＝起動時 force-load・`assert` は import gate 維持）。✅ lang-item 型の**再定義を loud reject**〔`checkLangItemRedef`＋`defOffset`・test reject redefine_langitem〕。
- ✅ **トップレベル変数**（`val`/`mut val`＋`export`・`plew_init_globals`・各本体エントリで `seedGlobals`）。残〔小〕＝前方参照〔後発 global を先行 global の初期化子が読むと zero〕・`assoc val`（static）未実装。
- **エントリ `fn main`**：`int main(int argc, char** argv)` に固定脱糖（spec の戻り `()|Result` とは別）。

## 構築・factory

- ✅ **JSX `<Type f=e/>`／`<E.V f=e/>`＋フィールドデフォルト値 `val x: T = expr`**。**未実装**＝`factory`（明示宣言）・`optional`・`result factory`（可謬構築）。
- ✅ **(b) フィールドゲート（spec/05）**＝cross-module 構築で非 `pub` フィールド（vis 0/1）を設定すると loud reject（`checkConstructVis`・同一モジュール構築は無制限・enum payload/record〔全 pub 合成 struct〕/extern lang-item/synthesize された dict literal フィールドは除外）。実装鍵＝**`StructDef.defOffset`**〔decl span start＝再インターンされた nameStart は module 0 ゆえ defining module 特定不可・これで `moduleOf` が正しい源モジュールを引く〕＋**`offsetIsLoaded`**〔real source span か合成 span かを判別＝dict の `keys`/… を skip〕＋`MakeField.offset`〔real source offset・nameStart でなくこちらで gate〕。test reject construct_private_field_crossmodule。**残＝(a) 公開ゲート**（既定 memberwise factory は private・全 pub フィールドでも外部構築は `pub impl Type { factory }` 明示要）＝`factory` 宣言機能と一括（factory 未実装ゆえ現状は全 pub フィールド型の cross-module 構築は許容＝spec (a) より緩い・factory 着手時に拡張）。メタプロ側ディレクティブ引数構築は (b) 強制済〔`checkDirectiveArgsPublic`〕。

## 共有可変・並行性・メタプログラミング

- ✅ **`Ref[T]`（共有可変）**（rc 箱・`<Ref[T] value=e/>`・`r->field`・retain 共有・`Ref[unique]` の deinit 発火）。残：`WeakRef`＋`upgrade()`・**循環回収**〔スコープ外〕・bare `<Ref value=e/>` 型推論〔明示 `[T]` 必須〕。spec/03,14。
- ✅ **`async`/`await`/`Promise`/`sleep`／イベントループ 段階 1・2・3a**（方式 B＝stackless ステートマシン・frame hoist＋goto 再入・仮想時計タイマ・`async fn main`・if/while/match 内 await）。**残 tail（additive・クリーンに reject）**：await-in-`for`・struct-destructure match・式中 await・async メソッド・generic async・String/struct を値に持つ `Promise`・frame/`__self`/`PlewPromise` の ARC〔leak・小〕。spec/14。
- **`spawn`/`JoinHandle`/チャネル** → **未実装**〔スコープ外・async 安定後・実スレッド pthread・境界で CoW eager 実体化・`Ref` 不可〕。spec/14。
- ✅ **メタプログラミング M1＋A＋M2**（`plewc --gen`＋共有 `@Std/Syntax`＋auto-part・マクロ入力 `TopItemAst`〔impl/trait も〕・`@[Eq]`/`@[Ord]`/`@[Hash]` derive・Dictionary lang item）。**剥離**＝ディレクティブ引数のファクトリ可視性 (a) は未〔上記 factory ゲート連動〕。M3 で `@Std/Syntax` 外部化〔スコープ外〕。spec/16。

## 字句

- ✅ 改行自動終端＋括弧内継続〔spec 準拠〕・`//` 行コメント＋`/* … */` ネスト対応ブロックコメント・`;` 文区切りは loud reject。

---

**再訪の優先度**：観測挙動を歪める大物はほぼ解消済（整数幅・match・ラベル・無損失 `as`・値意味論・CoW＋refcount 解放・generics・トレイト・`Optional`/`Result`/`try`・`unique`＋`deinit`・クロージャ・演算子トレイト全配線・async/await・無名レコード・newtype〔int〕・受理健全性の共有パス＋型チェッカ soundness ハードニング・**構築フィールドゲート (b)**・**再帰 generic 値型完全**・LLVM 単一 backend）。**残る soundness 穴**＝ファクトリ公開ゲート (a)〔factory 機能依存〕・generic-receiver method の value 引数 grounding・重なる inout ②③。残る hidden meaning＝newtype 非 int 継承・From/TryFrom・float→int `as`・mixed `1.5+2`/無型 int generic-enum payload・一般 Chain・Iterator〔sum/enumerate/zip〕・名前空間 import・`\u{}`・generic assoc fn〔Set〕。残る hidden cost＝backend ARC drop。**横断＝型パラメータ判定のスコープ化**（複数項の根）。詳細順序は [worklog.md](worklog.md)「🗺️ ロードマップ」。
