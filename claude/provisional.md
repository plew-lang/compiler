# 暫定実装と仕様からの意図的剥離（provisional / intentional deviations）

現コンパイラ（正典＝`compiler/src/_.pw`・Plew 製）が `SPEC.md`／`spec/*.md` から**意図的に**省いている箇所の一覧＝「これはバグでなく既知の暫定」＝**残作業の地図**。各項は **仕様（正典）→ 現状（剥離）→ 理由/再訪**。**`✅` は完了（git タグ＝正典）で経緯参照のため一行に縮約**・**`✅` でない項が本書の本体＝残作業**。優先度・順序は [worklog.md](worklog.md)「🗺️ ロードマップ」。

- **2 つのゴール**：①**受理の健全性（accepted ⟹ spec-valid）**＝受理するコードは spec でも valid（逆向きの不完全性＝spec valid だが reject は許容）。直すべきは「spec は reject するのに今 accept」＝hidden meaning だけ。②**ソース spec-validity**＝`compiler/src/*.pw` 自体が純 spec-valid（コンパイラは自分を受理＝①が完全なら②も自動）。enforce は plewc.pw 自身にも適用（import 必須・全呼びラベル付き等・ADD→reseed→USE で不動点維持）。
- **hidden meaning（観測挙動が spec から逸れる）と hidden cost（裏でコストだけ）は別物**＝前者（値意味論・overflow panic・ラベル等）は必ず埋める／後者（ARC/CoW を leak で代用等）は正しく実装するが leak 状態でも観測挙動は正しい。
- ✅ **受理健全性の共有パス `Codegen/Verify.pw`（`verifyProgram`）＋型チェッカ `Codegen/Infer.pw`（TypeRef ベース）**＝emission 非依存で spec 不正を弾く。`inferType`（精密型 or 0=不明）＋`typesCompatible`（保守的・確定的不一致のみ reject）が広範な型混同を解消（Bool↔整数・別 named 型・引数/return 不一致・混合幅算術/比較・generic 引数違い・primitive binop の RHS 型・`&&`/`||` の非 Bool・比較の cross-type・複合代入の型・`as` の Bool↔numeric・int↔float 暗黙変換・配列 append/dict K-V・range 両端・field/default arg・void 結果の値使用・`any P` メソッド結果型・generic/provided 本体 abstract 検査〔Rust 流・entry-module gate〕・generic-receiver value 引数 grounding）。**残 follow-up**〔narrow・任意〕：overloaded 呼びの引数・generic 引数の nested `Array[T]` 位置・codegen を tc の型へ移行〔大〕。

## メモリ・所有権

- ✅ **値意味論＋CoW＋ARC 解放**（非アトミック refcount・`Array[T]` は `RawBuffer` 床の Plew struct・束縛は O(1) 共有＋retain・変異点で複製・scope/早期 exit で再帰解放・ASan clean）。残：`WeakRef`・**循環回収**〔スコープ外〕・mono struct/enum の share/release〔mono 局所 leak・安全〕。spec/03。
- ✅ **`unique`/`borrow`/`move`/`deinit`＋健全性ハードニング**（決定的破棄・bare コピー/伝染を loud reject・`Ref[unique]` の最後の解放で deinit・`mut val` unique 再代入・`move fn` self・`deinit` は unique 型のみ・use-after-move 線形追跡）。残（spec 通り将来）：部分 move/field move〔unsupported〕・条件付き move〔禁止のまま〕。spec/03。
- **`local` 型**（spawn を越えられない）→ **無し**。spawn 段で。spec/03,14。
- ✅ **`inout`＋合成可変性検査**（単純変数・`base.field`・`a[i]`・`.append`/`inout fn`・call-site `inout` キーワード一致・`inout` 引数は mutable place 必須）。spec/03。
- **重なる `inout`**（1 呼びで複数 inout が同じ場所）→ ✅ **ケース①構文同一を loud reject**（`exprSyntaxEq`）。**残＝ケース②③＝部分/添字重なり**（`a.merge(inout a.field)`・`arr[i],arr[j]` の distinct 証明）＝spec 通り lint＋限定ランタイム panic は将来。spec/03。
- ✅ **place 越し get-modify-set 脱糖**（`arr[i].field = x`・compound 要素 `arr[i].field OP= x`・`arr[i].inoutMethod()`）。spec/03。

## 数値モデル

- ✅ **幅つき整数 `I8..U64`**（厳密幅 stdint・overflow/0除算 panic・リテラル文脈型付け＋厳密 no-default＋U64 magnitude モデル・幅不明な式の算術は loud error・`wrapping*` メソッドは additive 予定）。
- ✅ **浮動小数 `F32/F64`（実用上完成）**＝リテラル/local/関数引数戻り/`Array[F64]`/struct フィールド/算術/比較〔ordered fcmp＋NaN panic〕/print/int→float `as`・int↔float 暗黙変換を loud reject・無型 int リテラルの float context・float→int/unsigned `TryFrom[F64]`〔0 方向切り捨て・NaN/inf/範囲外 Err〕。**残**：**真の F32**〔当面 double〕・`%` は整数限定で reject〔spec 通り〕。spec/02,12。
- ✅ **整数リテラル基数＋桁区切り**（`0x`/`0o`/`0b`＋`_`・float `_` も）。spec/02。

## レンジ

- **`a..<b`/`a..=b` は第一級の値**（`HalfOpenRange`/`ClosedRange`・`Step` で反復）→ **現状：`for` ヘッドでしか書けない**（その場で C for ループに脱糖・レンジ型/値/`Step`/素の `..` は無い）。ループ変数型注釈は実装済（`for val i: I32 in 0..<5`）。✅ 両端の型一致検査。spec/02,11。

## 文字列

- `String`＝不変・UTF-8 妥当・`==` バイト等価な CoW 値型 → **現状：`{ptr,len}`・不変・byte-`==`**（不変と byte-eq は spec 通り）。✅ 連結 `+`〔`impl String as Add[String]`〕・✅ UTF-8 妥当性チェック〔安全な公開コンストラクタ `<String.checked source=bytes/>`→`Result[String, Utf8Error]`・unchecked 床は `stringFromBytesUnchecked`〕。**残：`scalars`/`graphemes`/`Ord`/substring/`Slice` なし**・解放なし〔leak〕。`.bytes`（`Array[U8]` O(1) ビュー）は spec 通り。spec/02。
- ✅ **文字列リテラルのエスケープ**：`\n`/`\t`/`\r`/`\0`＋`\\`/`\"`/`\'`・`\u{XXXX}` Unicode エスケープ〔UTF-8 1-4 byte encode・無効コードポイント/サロゲートは loud reject〕。spec/02。

## 配列・辞書・集合・タプル

- ✅ **`Array[T]`（値意味論＋CoW＋解放・添字 U64・範囲外 panic・複合要素 `Array[Ref[T]]`/`Array[Box[T]]`/`Array[Array[T]]`・generic struct/関数での単相化・非リテラル配列値の要素型一致）**。残る小 hidden-cost ARC 残留〔no UAF〕：fresh-temp append の box 1 つ leak・heap 持ち Ref pointee の深い release・ネスト配列 inner-array 要素 ARC。`[E;N]`/const generics/`Slice`/部分文字列は **spec 自身が保留**〔スコープ外〕。
- ✅ **`Dictionary[K,V]`（lang item・`[k:v]`/`[:]`・SipHash-1-3・`get`/`dict[k]` 欠落 panic・複合添字 `d[k]+=v`・per-process ランダムシード・キー型 `U8..U64`/`I8..I64`/String/`Bool`/**ユーザー struct**〔`@[Hash]`/`@[Eq]` derive・2-phase gen〕・dict subscript キー型検査）**。**`Set[E]`** → **未実装**（非 lang item・import 要・前提＝construction-field 推論は✅／generic assoc fn が未＝`Set[E].empty()` が「assoc fn not emittable」＝generic method declare-on-demand の assoc 版が要る・回避＝注釈ローカル＋JSX 構築）。
- ✅ **ラベル付き無名レコード `(x: I32, y: I32)`**（型注釈/リテラル/`.field`/多値返却/フィールド順独立/関数跨ぎ同一性/record param/value-semantics コピー/struct・enum payload/合成 struct 機構/分解 `(val x, val y) = p`/punning/for 分解/construction-field & call-arg context/method への record literal context/nested record literal/generic-enum/struct 構築の call/method 引数 context）。**残**：(c) inline `()` の generic field 構築〔`<Result.Ok value=()/>`・変数経由で✅〕・(d) canonical 名の full-type 厳密化〔`recordTypeKey` は head＋arg-head のみ〕・(e) 無注釈 destructure-assign の nested record。spec/02。

## 型システム：ジェネリクス・トレイト・拡張

- ✅ **再帰値型**（`struct A { child: Optional[A] }`＝field-level auto-boxing＋CoW ARC・generic 再帰値型 `Node[T]`/`Tree[T]`・相互再帰 generic 値型 `Ping[T]`↔`Pong[T]`・5000 ノード 0 leaks）。残〔minor〕：終端なし循環（住人なし＝構築不能・将来 loud reject）。spec/03。⚠ **単一大文字 struct 名は std メソッド型パラメータ（`fold[B]`/`map[B]` の `B`/`F`/…）と衝突**＝`isTypeParamName` グローバル照合で clean error〔回避＝リネーム・根治＝スコープ化〕。
- ✅ **ジェネリクス `[T]`/`[T,U]`**（単相化・generic struct/enum/fn/`impl[T]`・`where T: Trait`＋メソッド own 型パラメータ＋推移的インスタンス化・`inout H` をトレイトディスパッチ越し・関連型 `type Item`・ネスト generic 単相化・generic コンストラクタ JSX 型引数推論・aggregate 内 generic-inst フィールド by value・generic 型注釈の arity 検査・型パラメータ名の重複 reject）。残 additive：**generic free 関数の明示型引数 `id[I32](x)`**〔推論は動く〕・**assoc 呼出位置の型推論**〔`Box.make(x:7)` の戻り T〕・generic 抽象 `T::Item`〔concrete では不要〕。spec/06,08。
- ✅ **トレイト（ユーザー定義・準拠・提供メソッド・bound 越しディスパッチ・継承 `trait Sub: Super`・`where T: Trait[Args]`・`any P` 存在型・準拠 witness の返り値型一致）**。✅ **トレイト間準拠 `impl B as A`（spec/08,09 完全実装）**＝主語トレイトの全準拠型を別トレイトへ準拠（ベア所有者は自動随伴／拡張内は view-gated／頭なし `impl[T] T as A` は reject）＋衝突 `#` 経路選択〔直接呼び＋境界越し view-aware mono〕＋連鎖（推移）＋連鎖×衝突〔viewRoot モデル〕＋純加算ビューモデル〔`#X` はタグを積み base 表面を隠さない〕＋ビュー妥当性強制〔トレイト `#P`＝準拠必須・拡張 `#A`＝impl 必須・非対称〕。**残る剥離**：**トレイト引数 aware の多重 conformance 区別**＝bound パイプラインが型引数を表現せず `where T: Into[I64]` ≡ `where T: Into`〔arity 照合・引数 aware は将来〕。spec/08,09。
- ✅ **演算子→トレイト脱糖（O1-O8）**（ユーザー型＋プリミティブの算術/ビット/単項/比較が witness 脱糖・built-in 算術完全削除・Index/IndexSet・一般 Chain `?.`〔Optional 専用でなく `Chain` トレイト脱糖・任意の value-or-empty 型・ネスト `a?.x?.y` 可〕・`??`→`unwrapOr`・`Pow`/`pow`〔整数 conformance・float pow は additive 未提供〕・`Output != Self`）。spec/12。
- ✅ **拡張 `#Ext`（struct レシーバで完備）**（値/型ビュー・`defaultExtension`・`#P` 源選択・self-view/`#!Ext`/スタック `#A#B`・明示ビュー強制・view-aware オーバーロード・トレイト主語 impl・外部型コヒーレンス・enum/primitive ext レシーバ）。**残る剥離**：(a) **コンテナ不変性 `Array[P]`≠`Array[P#Ext]`**〔exotic・保留〕・(b) **型レベル chained `Type#A#B`**〔param に2 view・値レベルは可〕。spec/09。
- ✅ **`newtype`（spec/10 完全準拠）** ＝別型・underlying 表現・`as` ゼロコスト再タグ・型区別・算術/比較演算子継承・メソッド/フィールド継承〔int/非 int/struct underlying〕・trait 準拠の自動継承・既定/named/fallible factory 継承・unique/deinit 自動継承・`export newtype`・user 定義 `impl` は reject〔継承のみ・振る舞い追加は struct ラップ〕。

## 関数・呼び出し

- ✅ **引数ラベル必須・宣言順・オーバーロード**（セレクタ＝名前＋ラベル＋型頭で C マングル・arity/label/type 解決・`~:` 抑制・デフォルト引数〔末尾省略〕・関数型同一性へのラベル反映・closure literal の param 名をラベルと一致必須・関数値の署名一致＋呼び出し引数型検査）。残：一般 `typesCompatible` での fn 型ラベル比較〔binding/return 位置・現状は closure literal arg のみ厳格〕・`~:` 抑制位置の厳密一致・I/O ビルトイン非検査。spec/04,07。
- ✅ **インヘレントメソッド**（`fn`/`inout fn`/`move fn`/`borrow fn` self・引数型オーバーロード）。残：一時値レシーバへの `inout`。spec/07。
- ✅ **クロージャ／関数値**（fat closure `PlewClosure{fn,env,rc,drop}`・不変値キャプチャ＋スカラー `mut val` 参照キャプチャ〔箱化＝`makeCounter`〕・leak 解消）。**残（loud reject）**：`mut val` 非スカラー参照キャプチャ・`unique`/generic/enum/関数値キャプチャ・ネスト closure・val capture への代入。残 hidden cost：引数直渡し一時 capturing 閉包・Ref キャプチャ pointee。spec/04。

## 制御フロー・match

- ✅ **`match` 網羅性検査**（`_` or 全 variant・rename/discard/or パターン・全フィールド束縛必須・フィールド名/variant 名実在検査・値位置 `match`/`if`〔`give`〕・リテラルパターン・capture-binding `val x =>`〔スカラ/リテラル match・enum-dispatch の capture は未対応で loud reject〕）。❌ **arm ガードは持たない**（spec/11＝網羅性を純粋に構造的に保つ意図的決定・parser が loud reject）。**ネストパターン無しは spec 通り**（パターンは意図的に単層＝`field: Point(...)` は clean error）。残：束縛名一致だが型食い違いは C エラー fallback・到達不能アーム警告無し。spec/11。
- ✅ **構築/分解の全フィールド明示必須**（struct パターン・enum payload・`<S wrongfield=…/>` 実在検査・`for (val x, val y) in xs` の record 分解）。spec/05,11。
- **`for (val k, val v) in dict`** → dict 反復子待ち〔別機能〕。✅ **条件チェーン／`guard`（spec/11）**＝if-let/while-let〔`PATTERN = expr [&& cond]`〕・`guard` 文〔rest を成功枝に包んで binding-escape〕・式位置 if-let・複数束縛/Bool 混在チェーン・Bool-first-then-binding・guard else 発散 enforce＝全部済〔**パーサで `match`/`if`/`while` へ脱糖・arena/backend 変更ゼロ**〕。spec/11。
- ✅ **`panic`（発散文）＋式位置の `panic`/`return`**（value-match arm を block-bodied 化・`MatchArm.isDiverge`・diverging branch を PHI から除外）。

## 演算子・変換

- ✅ **対応**：算術 `+ - * / %`・比較 `== != < <= > >=`・論理 `&& ||`・ビット/シフト `& | ^ << >> ~`・単項 `! - ~`・代入＋複合〔ビット系含む〕・`Optional.unwrapOr`〔旧 `??`〕・添字 `[]`/`[]=`〔Index/IndexSet〕・一般 Chain `?.`〔任意の value-or-empty 型・ネスト可〕・`pow`〔`Pow[Exp]`・float pow は additive〕。
- ✅ **factory 機構＋From/TryFrom（user 型）**＝named factory〔`<Type.name attrs/>`〕・fallible〔`optional`/`result[E] factory`→Optional/Result〕・From〔anonymous `factory(from: S)`＋`x as T`/`<T from=x/>` 脱糖〕・TryFrom〔`result[E] factory checked(source:)`＋`<T.checked source=…/>`〕・factory-as-trait-requirement〔trait が `factory` 要求を持てる＝キーストーン〕・`try` の異エラー型 From 変換。
- ✅ **TryFrom 数値 matrix 完成**＝primitive 整数 narrowing〔I8/I16/I32 from I64・range-check＋trunc・`RangeError`〕・unsigned narrowing〔U8/U16/U32 from U64〕・cross-sign〔I64↔U64・bit reinterpret〕・narrower-source＋cross-sign の sub-64bit 全ペア〔`@[IntTryFrom]` derive で dogfood 生成・deriver は完全 dumb で一様 body `<T.checked source=(source as I64)/>`・`Core.gen.pw` にコミット・**extern ブロックへの `@[...]` derive をサポート**〕・float→signed/unsigned〔`f64ToI64`/`f64ToU64` intrinsic〕・文字列→I64 パース〔`ParseError`〕。残は ISize/USize 等の将来幅のみ。
- ✅ **`as`**＝数値↔数値の C キャスト〔無損失検査済・narrowing reject〕。✅ **単項演算子の適用可能性**（`!`=Bool/`-`=signed int・float/`~`=int・String への `-`/`!`/`~` を reject）。残（低 harm）＝witness を持たない user struct/enum への単項〔clang が invalid IR を reject＝silent miscompile でない〕。
- ✅ **`try`**＝Result 早期 return〔非 Result〔特に Optional〕operand は loud reject・error 型一致検査〕。spec/12,13。
- ✅ **曖昧な無サフィックス整数リテラルのオーバーロードを loud reject**・✅ **`val f = obj.method`（メソッド値化）を loud reject**・✅ **ユーザー struct/enum 名が lang-item 型パラメータ名と衝突→loud reject 化**〔根治＝型パラメータ同一性のスコープ化は将来・回避＝リネーム〕。

## 可視性・モジュール・import

- ✅ **scoped resolution（可視性 `export`/`import with`/`pub impl`/`pub`/`pub(get)`）**：名前解決をスコープ化（`nameVisibleFrom`＝同モジュール定義 or imported+exported）。**自由関数**＝`findFunc` が in-scope 候補のみ選び `checkUseVisibility` が診断。**型/トレイト**＝`checkTypeVisibility` が**チョークポイント検査**＝全 `c.arena.types` を一様走査し、各 TypeRef の `siteOffset`（書かれた実ソース offset・`lowerType` が `TypeAst.span.start` を刻む）でモジュールを引いて gate。**あらゆる書かれた型注釈は唯一の `lowerType` を通る**ので、param/ret・struct/enum フィールド・**ローカル `val x: T`**・**newtype underlying**・**trait 要求シグネチャ**・`as`・明示型引数・closure sig・将来の新文法まで**サイト列挙漏れなく**被覆（ネスト generic 引数も各々 arena の TypeRef ＝同じ走査が拾う・特例不要）。`siteOffset 0`＝合成 TypeRef or 型パラメータ head（lowering 時に `c.cur.typeParams`＝型パラメータ＋トレイト関連型の scope と照合して skip）→ 走査から除外。エラー行は decl 名でなく**注釈そのもの**を指す。✅ **ambient ＝ `@Std/Lang` の export 面**（`isAmbientInLang`・ハードコード名リスト `isLangItemTypeName` は廃止＝マニフェストが唯一の真実）。`@Std/Lang` が**宣言**する型（`Optional`/`Result`/`Array`/`Dictionary`＋不透明合成 intrinsic `Promise`/`JoinHandle`/レンジ2型）か**再エクスポート**する型（プリミティブ＝`@Std/Core` で witness と同居定義＝型所有コヒーレンス・`export @Std/Core with { I8… }`）だけが ambient＝**spec/15 リストちょうど**。`isAmbientInLang`＝(1) struct/enum を `defOffset` のモジュール＝langModule か走査（user の `enum Optional` が Lang 所有を覆わず再定義 reject も成立）(2) 再エクスポート記録（`exports` の `fieldStart==langModule`）。`Ordering`/`Ref`/`WeakRef`/`RawBuffer`・全トレイト・`SipHasher` は Lang 面に無い＝import 必須（`Ordering`＝`<`/`>` は脱糖で `Bool` を返し `Ordering` 値を生む構文なし／`Ref`/`WeakRef`/`RawBuffer`＝汎用 factory で名指す祝福*表現*・専用リテラル無し＝`@Std/Core` 在住）。`extern` struct は `defOffset` に実ソース offset を持つ（旧 0＝コンパイラ全体が module 0 ゆえ偶然通っていた穴を根治）。✅ **再エクスポート実装**（`export <path> with { … }`・`ReExport` が `ImportAst` を保持・ローダがフォワード先をロード・`lowerReExport` が転送名を自モジュール export 面へ＝ローカル束縛なし）。**hashing は @Std/Hash へ分離**・**`@Std/Prelude` は廃止**（空の force-load を撤去・`@Std/Lang` が唯一の ambient モジュール）。✅ **alias を型位置で解決**（`Real as Alias`＝`realTypeNameInModule` が use-site module scope で real 名へ・imports/exports は real 名 keyed）。✅ **名前空間 import `Io.print`**・✅ **`_.pw` ディレクトリ解決**。✅ **循環 import 検出**＝`detectImportCycles`（import→定義モジュール辺を DFS color・back-edge を reject・[spec/15 循環依存](../spec/04-execution/15-modules.md#循環依存モジュールグラフは-dag)）。**残〔小〕**＝①パス正当性厳密検査〔「ロード済み export 集合に在るか」近似〕。②理論上の偽陽性＝型パラメータ/関連型名が実在の型名と衝突した稀ケース（loud・リネームで回避）。spec/15。
- ✅ **`part`／`import` パスルート**（`part ./Name`・`@Std/X` は binary 横 `std/X.pw`・`with { }` 選択・dir module・namespace import）。spec/15。
- ✅ **ambient マニフェスト `@Std/Lang`**（`Optional`/`Result`/`Array`/`Dictionary`＋合成 intrinsic を宣言・プリミティブを `@Std/Core` から再エクスポート＝import 不要。`@Std/Core` は起動時 force-load されるが ambient ではない＝演算子 `+`/`for`/range の USE は脱糖表ゆえ無 import で動く一方、トレイト名・`assert`・`Ordering`/`Ref` 等の**名指し**は import 必須）・✅ lang-item 型の**再定義を loud reject**（`isAmbientInLang`）。
- ✅ **トップレベル変数**（`val`/`mut val`＋`export`）・✅ **`assoc val`（static 定数 `Type.NAME`）**〔ゼロ引数 assoc fn への脱糖・残〔小〕＝`assoc mut val` 未対応〕・✅ **global 前方参照**〔依存順トポロジカルソート・循環 reject〕。
- **エントリ `fn main`**：`int main(int argc, char** argv)` に固定脱糖（spec の戻り `()|Result` とは別）。

## 構築・factory

- ✅ **JSX `<Type f=e/>`／`<E.V f=e/>`＋フィールドデフォルト値 `val x: T = expr`**・✅ **フィールド/引数デフォルト値の型一致**・✅ **デフォルト値の自己完結**〔他フィールド/他引数/`self` 参照を loud-reject・module-level global は許容〕。残 narrow＝block-bearing default〔`give`-block if/match〕の deep-walk は未対応〔exotic〕。
- ✅ **(b) フィールドゲート（spec/05）**＝cross-module 構築で非 `pub` フィールドを設定すると loud reject〔`StructDef.defOffset`＋`offsetIsLoaded`〕。**残＝(a) 公開ゲート**＝既定 memberwise factory は private・全 pub フィールドでも外部構築は `pub impl Type { factory }` 明示要〔現状は全 pub フィールド型の cross-module 構築を許容＝spec (a) より緩い・factory 着手時に拡張〕。メタプロ側ディレクティブ引数構築は (b) 強制済。

## 共有可変・並行性・メタプログラミング

- ✅ **`Ref[T]`（共有可変）**（rc 箱・`<Ref[T] value=e/>`・`r->field`・retain 共有・`Ref[unique]` の deinit 発火・`value` フィールド型検査）。残：`WeakRef`＋`upgrade()`・**循環回収**〔スコープ外〕・bare `<Ref value=e/>` 型推論〔明示 `[T]` 必須〕。spec/03,14。
- ✅ **`async`/`await`/`Promise`/`sleep`／イベントループ 段階 1・2・3a**（方式 B＝stackless ステートマシン・frame hoist＋goto 再入・仮想時計タイマ・`async fn main`・if/while/match 内 await・async 本体も受理健全性検査）。**残 tail（additive・クリーンに reject）**：await-in-`for`・struct-destructure match・式中 await・async メソッド・generic async・String/struct を値に持つ `Promise`・frame/`__self`/`PlewPromise` の ARC〔leak・小〕。spec/14。
- **`spawn`/`JoinHandle`/チャネル** → **未実装**〔スコープ外・async 安定後・実スレッド pthread・境界で CoW eager 実体化・`Ref` 不可〕。spec/14。
- ✅ **メタプログラミング M1＋A＋M2**（`plewc --gen`＋共有 `@Std/Syntax`＋auto-part・マクロ入力 `TopItemAst`〔impl/trait も〕・`@[Eq]`/`@[Ord]`/`@[Hash]` derive・Dictionary lang item）。**剥離**＝ディレクティブ引数のファクトリ可視性 (a) は未〔上記 factory ゲート連動〕。M3 で `@Std/Syntax` 外部化〔スコープ外〕。spec/16。

## 字句

- ✅ 改行自動終端＋括弧内継続〔spec 準拠〕・`//` 行コメント＋`/* … */` ネスト対応ブロックコメント・`;` 文区切りは loud reject。

---

**再訪の優先度**：観測挙動を歪める大物はほぼ解消済（hidden meaning は実質完了＝整数幅・match・ラベル・無損失 `as`・値意味論・CoW＋refcount 解放・generics・トレイト〔トレイト間準拠完全〕・`Optional`/`Result`/`try`・`unique`＋`deinit`・クロージャ・演算子トレイト全配線・async/await・無名レコード・newtype・From/TryFrom 数値 matrix・受理健全性の共有パス＋型チェッカ soundness ハードニング・LLVM 単一 backend）。**残る soundness 穴**＝重なる inout ②③のみ。**残る hidden meaning**＝Iterator〔sum/zip〕・generic assoc fn〔Set〕・Pow の float・import パス正当性厳密検査（additive/見送り）。〔scoped resolution＝型・関数のクロスモジュール可視性＋循環 import 検出は解消済〕**残る hidden cost**＝backend ARC drop。**横断＝型パラメータ判定のスコープ化**（残る用途は単一大文字 struct 名衝突等のみ）。詳細順序は [worklog.md](worklog.md)「🗺️ ロードマップ」。
