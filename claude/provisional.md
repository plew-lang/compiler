# 暫定実装と仕様からの意図的剥離（provisional / intentional deviations）

セルフホストを最短で通すため、現コンパイラは `SPEC.md`／`spec/*.md` から**意図的に**多くを省いている。ここはその一覧＝「これはバグでなく既知の暫定」を記録し、後で仕様準拠に寄せる作業の地図にする。各項は **仕様（正典）→ 現状（剥離）→ 理由/再訪時期**。**解消済みの剥離は git 履歴（タグ）に任せてここからは落とす**＝この文書は「いま剥離しているもの」だけを映す。

- 対象＝**正典コンパイラ `compiler/src/_.pw`**（Plew 製・今後の機能はここに additive）。使い捨ての Rust stage0 は self-host 後に退役・削除済（履歴記述に出る「stage0」は当時の throwaway を指す・タグ `stage0-final` で復旧可）。
- **重要な大前提**：観測挙動が仕様の意味から逸れている剥離（hidden *meaning*）と、裏でコストだけ払う剥離（hidden *cost*）は別物。前者（値意味論・オーバーフロー panic・ラベル等）はいずれ必ず埋める。後者（ARC/CoW を leak で代用等）は self-host 後に正しく実装する。

## 2 つのゴール（受理の健全性 ＋ ソース spec-validity）

- **受理の健全性（accepted ⟹ spec-valid）**：このコンパイラが*受理*するコードは spec でも valid。逆向きの不完全性（spec valid だが未実装で reject）は許容。直すべきは **「spec は reject するのに今 accept してしまう」＝hidden meaning** だけ。ランタイム挙動の誤り（hidden cost＝leak・float 未対応等）は対象外。
- **ソース spec-validity**：`compiler/src/*.pw` 自体が完全 spec 準拠コンパイラでもそのまま通る純 spec-valid な Plew であること。コンパイラは自分自身を受理するので、受理の健全性が完全ならソースも自動的に spec-valid＝両者は表裏。これらの enforce は plewc.pw 自身にも適用される（import 必須・全呼び出しラベル付き等）＝新機能の各サイクルで plewc.pw を spec-valid に保ちつつ不動点を維持（ADD→reseed→USE）。

主な受理健全性チェック（import-gating・ラベル検査・match 網羅・無損失 `as`・struct/array `==` 拒否・`val` 代入の可変性検査）は**実装済**。各々の残ギャップは下の該当テーマ節に記載。**唯一の未完チェック＝下記 S2**。

- ✅ **S2 @Std I/O の実 .pw 化**：`write`/`writeByte`/`readStdin`/`readFile`/`readFileBytes`/`eprint`/`fileExists`（`@Std/Io`）・`argCount`/`argAt`/`exit`（`@Std/Process`）・`sleep`（`@Std/Async`）は実 `.pw` の **`extern "plew-intrinsic"` 宣言**になり、コンパイラの名前ハードコード intercept は撤去（呼びは `plew_<name>` へ・ランタイム symbol は camelCase 統一）。lang item 型は **`extern "plew-intrinsic" { struct I32 … struct String }`**（Core が宣言＝所有・表現は intrinsic のまま不変・コヒーレンス是正で `impl I32 as Format` 等が通る）。**`Format` トレイト＋全整数型＋Bool の `impl … as Format` を純 Plew で実装済**（`stringFromBytes` intrinsic＋桁ロジック・I8-32→I64／U8-32→U64 へ lossless 委譲）。**✅ `print` も純 Plew 化完了**＝`@Std/Io` の `print[T](value~: T) where T: Format`（`write(s: value.format(format: ""))`＋改行）。Stmt.Print/parsePrint/impPrint/print 特別 codegen を全廃。**裸 `print(42)` はサフィックス必須**（既定型なし spec/02・reject `print_bare_literal`）。これを通すため **generic free fn の monomorphization をハードニング**（scan 時 `exprType` を codegen 同等に）：closure 呼び結果→fn 戻り型・`arr.count`→U64・generic メソッド戻り型置換（`substTypeInfo`）・Bool リテラル→Bool・compound 配列要素の ref 保持（`arr[i]->field`）・`typeInfoOfRef` が compound の ref を保持（`bb.v.v`・Ref pointee）・generic-enum/struct-destructure の match バインド型（`scanAddArmBinds` は **mono scan と bounds checker 共用**で 4 caller 全部に scrut の TypeInfo を渡す＝**かつての自己ビルド破壊の真因は Check.pw の未更新 caller 2 つ**）。**`checkImplOnBuiltin`**：Io→Core が全プログラムに `extern struct I32` を持ち込む帰結に、**トレイト準拠メンバ on primitive は許し（Core の `impl I32 as Format`）inherent `impl I32 {fn foo}` は拒否維持**（`methodWitnessesAConformance` で判別・`impl_on_builtin` reject 存続）。境界機構は [design-decisions.md](design-decisions.md)「コアライブラリの境界」。**✅ `String`/`Array` メソッドの Plew 化＝達成**：String メソッド（`.bytes` 上）・生メモリ床 `RawBuffer`・Array generic メソッド（要素型ごと mono・`emitArrayMethods`）・ambient プレリュード（`std/Prelude.pw` 自動ロード）・`.append` 純 Plew 化。**✅ Array の表現も Plew struct 化＝達成**（`struct Array[T]{data:RawBuffer[T]; pub(get) mut val count: U64}`・C typedef は StructDef 由来＝`Array_E{E* data; uint64_t count}`・Swift モデル・`PlewArray`/`.len`→`Array_E`/`.count`・経緯は [array-struct-plan.md](array-struct-plan.md)）。`readFile`→`Result` 可謬化（前提は揃い済）。**未完の orphan 強制**＝ユーザが `impl I32 as MyTrait`（自前トレイト準拠）を書くと現状通る（module identity 待ちの provisional・inherent でないので上の判別を抜ける）。
- ⚠️ **C 予約語と衝突する識別子**（`default`/`double` 等を変数/関数/フィールド名に使う）→ 名前マングリング未実装ゆえ生成 C が壊れる＝**受理健全性の既知の穴**（spec-valid を accept して壊れた C を吐く・hidden meaning）。コンパイラ自身は回避済・ユーザーコードで顕在化。直し：codegen で識別子を安全な C 名へマングル。

## メモリ・所有権（最大の剥離）

- **値意味論＋CoW** → ✅ **実装済**（非アトミック refcount＋copy-on-write）。`Array[T]` は `RawBuffer` 床の Plew struct（`{E* data; uint64_t count}`・cap/CoW refcount はバッファの `[cap][rc]` ヘッダ＝`plew_rawbuf_*`）。束縛は **O(1) 共有＋retain**（`Array_E_share`/`Struct_share`）、変異点（`Array_E_set`/`_push` の `_unique`）で **shared なら複製してから書く**＝値意味論を保ったまま遅延コピー。`Ref` 箱も同じ rc ヘッダで refcount 化（共有可変のまま）。解放＝scope 末・早期 exit（`return`/`break`/`continue`・`panic` は不走）・成長時の旧バッファで、配列要素/struct フィールドを再帰解放（深い `_copy` とセット）。**RC は非アトミック**（spawn 境界で実体化ゆえ・→ [design-decisions.md](design-decisions.md)）。全 fixpoint＋ASan（テスト＋自己コンパイル）で実証。残：`WeakRef`・循環回収・mono struct/enum の share/release（mono 局所 leak・安全）。spec/03。
- **`WeakRef` / 循環回収** → 無し（リークで代用）。
- **`unique`/`borrow`/`move`/`deinit`** → ✅ **実装済＋健全性ハードニング完了**（タグ `unique-deinit`/`unique-move`/`unique-checks`/`unique-nested`/`unique-ref-deinit`/`unique-loud-rejects`/`unique-cond-flow`/`unique-no-generic-args`/`unique-no-double-deinit`/`unique-give-guard`）。`unique struct`＋`deinit`（決定的破棄・型本体→フィールド宣言順・ネスト再帰・合成 `Type_deinit`）・`move`/`borrow` 前置＋引数モード・線形 move 追跡（`Local.moved`・use-after-move/bare コピー/bare 引数/伝染/モード必須を reject・`return` の per-exit 除外）・`Ref[unique]` の最後の解放で deinit 発火・`inout`/`inout fn` は正規動作。**unique 値が黙ってコピー/leak/二重 deinit する穴を全て塞いだ**（`Array[unique]`・generic 型引数・条件付き move・struct フィールド/`Ref`/`give` への place コピーを全て loud に reject）＝危険な unique パスは「正しく動く」か「loud に弾く」だけ。**追加機能も実装済**（タグ `unique-reassign`/`unique-move-fn`）＝`mut val` unique の**再代入**（旧値 deinit→新値 store・直線版）・**消費メソッド `move fn` self**（self 所有・全 exit で deinit・呼び出しでレシーバ moved 印・`borrow fn`＝`fn` 同義）。残（全て loud reject か N/A）：部分 move/return・条件付き move/消費（flow 解析 TODO）・分岐内 unique 再代入・value-position `give`・`local struct`（spawn 段）。spec/03。
- **`local` 型**（spawn を越えられない・`Ref` 持ちは必須）→ 無し。spawn/async 実装時に。spec/03,14。
- **`inout`** → 実装済（C ポインタ）。**単純変数・合成可変性（`base.field`・`a[i]`・`.append`/`inout fn` 受信側）の代入可変性検査あり**。残：**重なり inout 検査なし**（spec は同一場所への複数 inout を禁止・lint＋限定 panic）。spec/03。
- **place 越しの get-modify-set 脱糖**（`arr[i].field=x` 等） → **部分実装**：`arr[i].field = x`（`tryArrayElemFieldAssign`＝get-modify-set 脱糖）は動く。残：compound 要素は loud-reject・`arr[i].inoutMethod()`（inout メソッド経由）未対応・**Arrow place 代入の右辺リテラル型付け**（`ys[0]->v = 42` の `42` が「no type from context」＝pointee フィールド型の文脈が渡らない・`42I32`/変数で回避可・`a.b = lit` 通常 field は動くが `ref->field = lit` が未対応）。spec/03。

## 数値モデル

- **幅つき整数 `I8..U64`** → ✅ **厳密幅 stdint で実装**（各型が `int8_t…int64_t`/`uint16_t…uint64_t`・**U8 は `unsigned char`**＝`.bytes` バッファ共有のため・`Bool` だけ `long long`）。**overflow/0除算 panic**（`__builtin_*_overflow`・符号付き `INT_MIN/-1`・`x % -1`=0 で C UB 回避）・**リテラル文脈型付け**（範囲検査＋厳密 no-default・型サフィックス `5U64`・先頭 `-` 畳み込み）。**リテラルは U64 magnitude モデル**＝全 U64 範囲 [0, 2^64-1] が valid（codegen は >2^63-1 に `ULL`）・2^64-1 超過は lexer で clean なコンパイルエラー・負は Unary `-`＋符号で範囲検査。残（rare な穴）：両オペランドが幅不明な式の算術（`(1+1)` 等リテラルのみ）と配列要素 `/= %=` の narrow-signed `INT_MIN/-1`。`wrapping*` メソッドは additive 予定。
- **浮動小数点 `F32/F64`** → **未実装**（NaN 比較 panic・float `assert` も float 待ち）。spec/02,12。

## レンジ（暫定）

- **`a..<b`/`a..=b` は第一級の値**（`HalfOpenRange`/`ClosedRange` 2 型・JSX 糖衣・要素 `Ord`・`Step` で反復） → **現状：`for` のヘッドでしか書けない**。`for val i in a..<b`/`a..=b` をその場で C の for ループに脱糖するだけ。レンジ型・値・`Step`/`Ord`・素の `..` は無い。**小・ほぼ by-design**：`for val i: I32 in 0..<5` のループ変数型注釈が範囲境界リテラルへ伝播せず「no type from context」（境界に suffix `0..<5I32` で回避・設計上「範囲境界リテラルは型必須」だが注釈を context に使う改善余地）。spec/02,11。

## 文字列

- `String`＝不変・UTF-8 妥当・`==` バイト等価な **CoW 値型** → **現状：`{const char* data; long long len}`・不変・byte-`==`**（不変と byte-eq は spec 通り・不変ゆえ共有で観測的に正しい）。残：**UTF-8 妥当性チェックなし**・**連結なし**・**`scalars`/`graphemes`/`Ord`/substring/`Slice` なし**・解放なし（leak）。`.bytes`（`Array[U8]`・O(1) 共有ビュー）は spec 通り。spec/02。
- **文字列リテラルのエスケープ**：内容を C へ **verbatim 透過**（`\n`/`\"`/`\\`/`\t` 等 C と共通のものだけ動く）。Plew 固有エスケープは未対応。

## 配列・辞書・集合・タプル

- `Array[T]`：✅ **値意味論＋CoW＋解放を実装**（上述メモリ節）。添字 `U64`・範囲外 panic は spec 通り。**複合要素型も実装済**＝`Array[Ref[T]]`/`Array[Box[T]]`/`Array[Array[T]]`（ネスト）＋配列リテラル要素 append＋`Array[T]` の generic struct/関数での単相化（複合要素にマングル名 span を与え C 型/ARC は要素 ref から復元）。**残る小・hidden-cost ARC 残留（no UAF）**：fresh-temp append（`xs.append(<Ref…/>)`）が box を 1 つ leak（temp 所有権が transfer でなく retain）・heap 持ち Ref pointee の深い release（`Array[Ref[StructWithHeap]]` の pointee の配列/Ref フィールドが leak）・ネスト配列 `Array[Array[T]]` の inner-array 要素 ARC（ビットコピー＝leak）。`[E; N]`/const generics/`Slice`/部分文字列は **spec 自体が当面保留**。
- **`Dictionary[K,V]`（lang item・`[k:v]` リテラル）／`Set[E]`** → **未実装**（Hash が要る大物）。
- **ラベル付き無名レコード `(x: I32, y: I32)`** → 未実装（struct のみ）。

## 型システム：ジェネリクス・トレイト・拡張

- **再帰値型 `struct A { child: Optional[A] }` / `enum B { P(child: B) Q }`** → **未実装（着手予定）**。現状は enum ペイロードをインライン展開するので C で incomplete type（無限サイズ）になり**コンパイル不可**。spec/拠り所では**有限であるべき**＝コンパイラが裏で間接化（enum ペイロードをヒープ box・ARC）する hidden cost（明示 `Box`/`Ref`/`indirect` は書かせない）。値意味論（コピーは独立・CoW）を box 越しでも保つのが実装の肝。連結リスト/木の基本機能であり、メタプロの値ツリー AST（`@Std/Syntax`）の前提。→ worklog「着手中」。
- **ジェネリクス `[T]`／`[T,U]`** → ✅ **実装済（タグ `generics-data`/`generics-methods`）**：struct/enum/fn/`impl[T]` の型パラメータ・単相化（`Box_I32`）・generic struct/enum（`Optional`/`Result` 含む）・generic メソッド（レシーバ型由来）。残 additive：generic free 関数の呼び出し位置推論＋明示 `id[I32](x)`・メソッド own 型パラメータ `map[U]`＋推移的インスタンス化・`where` 制約（traits 待ち）。**関連型 `type Item` は実装済**（trait 宣言＋impl 束縛＋適合検査での `Item` 置換照合・test `assoc_type`）＝残るは generic 抽象コードでの `T::Item` 解決（concrete では不要）。
- **トレイト（`via` 準拠・提供メソッド・`any P` 存在型・blanket・継承）** → **全て未実装**（大物）。
- **演算子→トレイト脱糖**（`+`↔`Add` 等） → 無し。**演算子は数値/String にハードコード**（対象演算子も subset・下記）。
- **拡張 `#Ext`／`defaultExtension`／`A#P` ビュー／無名 impl コヒーレンス** → 全て未実装。
- **`newtype`** → 未実装。

## 関数・呼び出し

- **引数ラベルは必須・宣言順・関数型の同一性の一部** → **部分実装**。ユーザー定義トップレベル関数・メソッドの呼び出しはラベル検査（`hasLabel`＋宣言順で param 名一致・arg 数一致・不一致は `compileError` 診断で reject）。C 出力自体はラベルを落とし位置引数。✅ **ラベル抑制 `~:`**（位置引数・`Param.noLabel`）・**デフォルト引数 `name: T = expr`**（末尾省略のみ）は実装済。✅ **オーバーロード完成**（タグ `overload-mangle`/`overloading`）＝C 名をセレクタ（名前＋各パラメータの ラベル＋型頭）でマングル（`writeFnSelector`）し、`findFunc`/`findMethod` がラベル＋引数型で解決（arity／label／type の3軸・自由関数もメソッドも・`exprType` も解決経由で戻り型を選ぶ・単一名は first-label に fallback で従来通り）。残：**I/O ビルトイン**（暫定シグネチャゆえ非検査）・**関数型同一性へのラベル反映**・オーバーロードした関数値（fn-value は first-by-name）・デフォルト引数の中間省略/配列・struct デフォルト。spec/04,07。
- **インヘレントメソッド `impl Type { fn m(...) }`** → **実装済（subset）**。`fn`（by-value self）/`inout fn`（self 可変・C ポインタ）の 2 モード・`recv.m(label: arg)`・ラベル検査・C へ `Type_m(self, …)` マングル（`self` 暗黙）。✅ **引数型オーバーロード**（セレクタ＝名前＋ラベル＋型・タグ `overloading`）・✅ **`move fn`／`borrow fn` self**（消費／借用メソッド）実装済。残：トレイト/拡張のメソッド・一時値レシーバへの `inout`。spec/07。
- **クロージャ／関数値** → ✅ **実装済（不変値キャプチャ＋スカラー mut 参照キャプチャ）**：関数型 `fn(...)->R` は一律 **fat closure `PlewClosure{fn,env,rc,drop}`**（C 関数ポインタ単体から移行・呼び出し ABI は `R fn(void* env, params...)`・bare 関数値はサンク `<sel>__thunk` 経由・呼び出し位置で `.fn` を具体署名へキャスト）。クロージャリテラル＝`__closure<id>(void* __env, ...)`・高階関数。**キャプチャ**：(1)**不変（`val`）の値キャプチャ**＝スカラー（整数/Bool）・String・array・Ref・plain struct（env 構造体 `__closure_env<id>` に格納・ヒープ所有は retain〔share〕して格納＝エスケープ後も生存・`val` 不変ゆえ値キャプチャ＝参照キャプチャと観測同一＝spec 準拠）。(2)**`mut val` の参照キャプチャ＝スカラーのみ**（**箱化**＝外側ローカルを `T*` のヒープ ARC セルにし〔`plew_arc_alloc`〕・env は `plew_ref_share` で retain したポインタを保持・読み書きは両側 deref で**共有**＝`makeCounter` が動く・Swift 流）。body は `((__closure_env<id>*)__env)->name`、boxed は `(*…->name)`。**未対応は loud reject**（silent な意味逸脱を出さない）：**`mut val` 非スカラー**（array/struct/String の参照キャプチャ）・`unique`/generic 実体化/enum/関数値のキャプチャ・**ネスト closure**・**val capture への代入**。**ライフタイム＝leak 解消済**（B2b-2）＝閉包は `PlewClosure.drop`＝`__closure_env<id>_release`（boxed セル/array/struct/Ref キャプチャを release）を持ち、所有 closure ローカルは scope 末で `plew_closure_release`、箱化セルは scope 末で `plew_arc_release`、閉包の bind/return は `plew_closure_share`（retain）＝rc 会計が均衡。**`makeCounter`・エスケープした array キャプチャとも macOS `leaks` で 0 leaks／double-free・UAF 無し**を確認。残る hidden cost＝**引数に直接渡す一時 capturing 閉包**（束縛されない＝env を明示 release しないので env ブロックが残り得る・小・テストでは未観測）・Ref キャプチャ pointee の残留。**小・稀・loud な穴**＝shadow された local をキャプチャすると C 名不一致になり得る（F2 の shadow 用 C 名 suffix `cnum` が `emitCaptureInit` の enclosing 名出力に未配線・壊れても clang エラー＝loud・silent でない・回帰リスクに見合わず低優先）。メソッド値は spec で禁止（spec 通り未対応）。**次（B2b-3）**＝`mut val` 非スカラー箱化・`mut val` 参照キャプチャ閉包の `local` マーク（spawn 不可・spec/14・`spawn { block }` 前提）。
- **`;` 文区切り** → ⚠️ **既存の未対応（クロージャ無関係）**：Plew は文を改行区切りにし、`;` を文区切りとして使えない。`a; b` を書くと `;` 位置に value 0 の合成 Int ノードができ「integer literal has no type from context」という的外れエラーで落ちる（通常関数本体でも同様）。本来は構文エラーで loud に弾くべき＝パーサ堅牢化の TODO。

## enum 等価（暫定）

- **`Eq`/`Ord` トレイト＋`@[Eq]` derive（メタプロで構造的等価を生成・Rust 流）** → **現状：enum `==`/`!=` を「タグ（variant）比較」に直接脱糖**（variant 構築オペランドは tag index リテラル・それ以外は `(expr).tag`）。**全 nullary な enum だけ許可**（構造的 Eq と完全一致で正しい）・**payload 持ち enum の `==` は hidden meaning を避けるため `compileError` で reject**（タグだけ見て payload 無視の沈黙バグにしない）。`@[Eq]` 実装で構造的 Eq に置換予定。struct の `==` は未対応。spec/08,12,16。
- 補足：variant 値は **JSX 必須**（`<Kind.LParen />`・bare 不採用＝「生成は常に JSX」を維持）。型省略 JSX `<.LParen />`（文脈推論）は surface 追加の未決。

## 制御フロー・match

- **`match` 網羅性をコンパイル時検査** → **実装済**（`_` ワイルドカード or enum 全 variant 被覆・非網羅は `compileError` で reject・網羅 match は末尾 `__builtin_unreachable()`）。パターンは `E.V(val f)` 一段＋`_`＋**rename `(field: val name)`・discard `(field: _)`**＋**or パターン `A | B | …`**（全フィールド束縛必須・選択肢間の束縛名集合不一致はパース時 reject・異名フィールドを rename で共通束縛に揃える payload-or 可）。残：束縛名一致だが**型が食い違う**選択肢は C エラー fallback（クリーン診断でない）・**ガード・ネストパターン無し**・到達不能アーム警告無し。spec/11。
- **値位置の `match`／`if`** → **実装済**（`return match …`／`val x = match …`／`val x = if c { … give a } else { give b }`・ネスト/`else if` 可・C statement-expression 脱糖・`if` 式は `else` 必須）。残：`match` 式の結果型がバインド依存だと誤推論し得る／`give` 値が配列リテラルのときの型付けは未対応。spec/11。
- **struct 分解パターン `S { val x, val y }`** → **実装済**（match＝`run/struct_pattern`・for ヘッダ＝`run/for_struct_destructure`＝要素 struct を各反復で分解・punning/rename/discard 可・パターン型不一致と range 反復は loud reject・heap フィールドは borrow＝ASan clean）。**残（未実装機能・非バグ）**：(a) **`for (val k, val v) in dict` の tuple/record 分解**＝dict 反復子か record 要素サポートが前提（別機能）。(b) **`guard` 文そのもの**＝`KwGuard`/`parseGuard`/`Stmt.Guard` が無く、`if`/`while` も refutable 束縛・条件チェーン未対応＝spec/11 の条件チェーン束縛は `if`/`while`/`guard` 横断の丸ごと別 feature。spec/11。
- **`panic`（発散文）** → **実装済**（`panic <msg>`→noreturn `plew_panic`・stderr `panic: <msg>`＋`exit(1)`・unwind なし・`deinit` 非走行）。配列範囲外 panic は個別ランタイムで exit。残：式位置の `panic` は文のみ。

## 演算子（subset）

- **対応**：`+ - * / %`・比較 `== != < <= > >=`・論理 `&& ||`（C 短絡）・**ビット/シフト `& | ^ << >> ~`**・単項 `! - ~`・代入 `=`・複合 `+= -= *= /= %=`＋**ビット系 `&= |= ^= <<= >>=`**（純粋脱糖）・**`??`（Coalesce・Optional）**。
- **未対応**：`pow`/`**`・`Neg`/`Not`/各種演算子トレイト・`as` 以外の数値変換。
- **優先順位**：`??` を含め 10 段（低→高：`|| < && < 比較 < ?? < | < ^ < & < シフト < +- < */%`・`??` 右結合）。spec の 14 段とビット/算術/論理/比較/`??` の相対順序は一致。未対応段（`as` の位置・レンジ）と比較/レンジの非結合は未強制。spec/12。
- **`as`**：**数値↔数値の C キャストのみ**（無損失検査済＝source 幅を `TypeInfo` で復元し narrowing は reject・式幅も伝播）。残：`From`/`TryFrom`（`as` の全域変換脱糖・`try` の From 変換＝現状 `try` はソース/関数戻りの **エラー型一致 `E==E'` を要求**・違うと C 型不一致）・`?.`（オプショナルチェーン）は未実装。spec/12,13。
- **`??`/`try` は `@Std/Core` の Optional/Result の tag/field レイアウトをハードコード前提**（Some=tag0/`v`・Ok=tag0/`value`・Err=tag1/`error`）。lang-item ゆえ妥当だが、ユーザーが別形の Optional/Result を定義しても `??`/`try` はこの形を仮定。見直し：lang-item を spec で固定 or コンパイラが Core のシンボルを参照（ambient 化〔上記 import 節〕とセットで整理）。

## 可視性・モジュール・import

- **可視性 `export`/`import with`/`pub impl`/`pub`/`pub(get)` → ✅ spec 通り完全強制**（tag `visibility-enforced`）：loader が module identity（`moduleOf(offset)`）を持ち、`checkImports`〔import した名前は export 必須〕・`checkUseVisibility`〔import せず cross-module 関数使用を拒否〕＋メンバ可視性（impl ブロック単位 `pub impl`・フィールド per-field `pub`/`pub(get)`・private＝無名 impl のみ・トレイト準拠 `pub impl A as P`）。名前解決自体は今も（連結後の）線形スキャンだが可視性ゲートで絞る。**残・未実装**＝名前空間 import（`Io.print` 形・今は `with { }` 選択のみ）／`as` リネームの実束縛（今はパース＆元名記録のみ）／`_.pw` ディレクトリ解決／パス正当性（import を正しいモジュールから取っているかの厳密検査・今は「ロード済み export 集合に在るか」近似）。
- **`part`／`import` のパスルート** → 部分実装。`part ./Name`（兄弟ファイル）・**`part ./Sub/Name`（サブディレクトリ part パス＝`Sub/Name.pw` に解決・コンパイラ自身が `part ./Codegen/Expr` 等で依存）**・`import @Std/Io with { … }`・`@Std/Process with { … }` の `with { }` 選択形をパース＆enforce（バイト列連結→単一アリーナ/単一 C 出力・スコープ共有/名前空間なしは spec 通り）。`@Std/X` は `dirname(argv[0])/std/X.pw` 解決＝**バイナリ横の `std/`**（リポジトリでは `compiler/plewc` 起動ゆえ `compiler/std/X.pw`・Core.pw が実在）。バイナリと std が隣り合う限りディレクトリ移動に強く**現運用（self-host/テスト）は無問題**。残る課題は**配布時のみ**＝`plewc` を PATH 経由の bare 名で起動すると argv[0] にディレクトリ接頭辞が無く stdRoot が cwd 相対に外れる→インストール先 or バイナリ埋め込みで std を置く設計はそこで詰める。**可視性は全面強制済**（上記「可視性」項・`checkImports`＋`checkUseVisibility`）＝`import @Std/Process with { print }` は print が Process 未 export（＝Io 未ロード）で reject・未 import の cross-module 使用も reject。残：`_.pw` ディレクトリ・ネストした part（root の part のみ走査）・forest/循環検査・名前空間 import（`Io.print`）。
- **lang item / ambient 型** → 概念なし（名前空間はフラット）・lang item は型名でコンパイラが役割解決（[design-decisions.md](design-decisions.md)「コアライブラリの境界」）。I/O 群は実 `.pw` の `extern "plew-intrinsic"` 宣言に移行済（上記 S2）＝埋め込みビルトインは **`print` のみ**残る（整形 std 整備後に純 Plew 化）。`argCount`/`argAt` は `Process.args()` の暫定スタンドイン。
- **`Optional`/`Result` が ambient でなく明示 `import @Std/Core` を要求**（spec ではこの 2 つは lang item＝import 不要）。**意図的に放置する既知の spec 違反**。理由と直し方：名前空間は今もフラット（全ファイルを 1 `Comp` に連結）で、「ambient」＝「ローダが起動時に無条件 load」・「import 必須」＝「import directive を見た時だけ load」の差。可視性ゲート（I2）は実装済だが、`Optional`/`Result` を ambient にするには **Core を起動時に無条件 load**（lang item 型と同様）すればよい。ambient 化の本体は Core を起動時に無条件 load するだけ（explicit `import @Std/Core` は `pathSeen` dedup で冪等に併存）だが、付随して **(1) `assert` の巻き込み**＝Core 丸ごと load すると spec で import 必須の `assert` も ambient 化するので **prelude ファイル分割**（lang item 型だけ無条件 load・`assert` は別 import モジュールへ）が要る、**(2) 既存テストの自前 `enum Optional` との重複定義**＝lang item は再定義不可なので重複エラーが spec 的に正しく、テスト移行が要る。これらを処理する気になったら着手（フラットモデルのままでも A=無条件 load＋ファイル分割で可能・本物の可視性 I2 は不要）。
- **エントリ `fn main`**：`int main(int argc, char** argv)` に固定脱糖（spec の `fn main`/`async fn main`・戻り `()|Result` とは別）。
- **トップレベル変数（モジュール直下 `val`/`mut val`）** → **未実装・意図的に放置**（2026-06-04 ユーザー判断）。spec/CLAUDE.md ではトップレベル変数（`val` 定数・`mut val` 可変）は在るが、`parseProgram` が `KwVal`/`KwMut` を処理せず 1 トークンずつ黙って読み飛ばす＝宣言が丸ごと消え、参照側は "undeclared identifier"（生成 C で未定義）になる。**現状は silent**（hidden meaning＝本来 loud-reject か実装が筋）だが当面放置。実装するなら spec/15 の初期化順（①全トップレベル/`assoc val` 初期化→②`main`）の配線が要る＝feature 規模。トップレベル**関数**は実装済（こちらは在る）。

## 構築・factory

- **JSX `<Type f=e/>`／`<E.V f=e/>`** → 対応。
- **`factory`／`optional`・`result factory`／フィールドデフォルト値／memberwise vs `pub factory`** → 未実装。全フィールドを名前付きで必須指定。

## 共有可変・並行性・メタプログラミング

- **`Ref[T]`（共有可変）** → ✅ **基本実装済**：rc ヘッダ付きヒープ箱・`<Ref[T] value=e/>`・`r->field`・コピーで retain 共有・scope 末で release（最後の解放で箱を free＋pointee の配列/struct を release・**`Ref[unique]` は pointee の `deinit`→`release` を発火**＝unique を共有/格納する正規パターンが動く）。残：`WeakRef`＋`upgrade()`・循環回収・bare `<Ref value=e/>` 型推論（明示 `[T]` 必須）。spec/03,14。
- **`async`/`await`/`Promise`/`sleep`／イベントループ** → ✅ **段階 1・2・3a 実装済**（方式 B＝stackless ステートマシン・native-C・`Codegen/Async.pw`）。`async fn`（free のみ）を **frame 構造体＋resume 関数＋entry 関数**へ下ろす：frame に全パラメータ＋全ローカルを hoist（await を跨ぐ値の退避）・`await e` は `__f->__sub` 退避→`__state=N`→未解決なら resume 継続を登録して return→`switch` ディスパッチが `goto __L<N>` で再入→`__f->__sub->value` 読み出し・entry は frame 確保＋params コピー＋`__self=plew_promise_new()`＋resume 1 回＋`__self` 返却。ランタイム（`hasAnyAsync` ガード＝非 async は出力 byte 不変）＝`PlewPromise{done,value,k,kframe}`＋ready キュー＋**仮想時計タイマ**（deadline 順発火＝決定的・実時間消費なし）＋`plew_loop_run`＋`sleep`（`@Std/Async` import ゲート）。`Promise[T]`→`PlewPromise*`（**値スロットは `long long` に型消去**）。`async fn main`→`int main`＋ループ drain。**if/while/（enum）match 内 await・複数中断点も可**（全ローカル＋match バインドを frame hoist＋goto ゆえ分岐/ループ/アームへ goto 再入が安全・ループ内 await は state 再利用）。frame field 名は **monotonic suffix `name_sN`**（collect/codegen が同一 DFS 順で採番）で兄弟アーム/分岐の同名バインド衝突を回避＝shadowing も透過。entry は `__self` をローカル退避してから resume（同期完了＝中断なしで frame が `free` されても UAF にならない）。テスト＝`tests/run/async_{basic,order,control,match}`・reject `async_await_midexpr`。**残る tail（additive・いずれもクリーンに reject）**：(1) **await-in-`for`**＝誘導変数（`__fa`/`__fi`/loop-var）の frame 化が要る（while で代替可・優先度低）。(2) **struct-destructure match**（enum match は可）。(3) **式中 await**（`await a + 1`）＝await を文へ持ち上げる正規化。(4) **async メソッド**（self の frame 化）。(5) **generic async**。(6) **String/struct を値に持つ `Promise`**（値スロット拡張）。(7) **frame/`__self`/`PlewPromise` の ARC**（当面リーク＝完了 frame は `free` するが `__self`・heap フィールドはリーク・小）。spec/14。
- **`spawn`/`JoinHandle`/チャネル** → **未実装**（async 安定後・実スレッド pthread・境界で CoW eager 実体化・`Ref` 不可）。残る closure ギャップ（`mut val` 非スカラー箱化・`mut val` 参照キャプチャ閉包の `local` マーク）は spawn 段で回収（単一スレッド async は Ref 可ゆえ async 段では不要）。spec/14。
- **メタプログラミング（`Derive`・コード生成）** → 未実装（spec 上も最後）。

## 字句・文の区切り

- 改行自動終端＋括弧内継続は **spec 準拠**（剥離ではない）。残る剥離：コメントは `//` 行コメントのみ（**ブロックコメント未対応**）。

## トレイト/generics 監査の残課題（3エージェント＋実機確認・2026-06）

トレイト/generics を spec/06,07,08,12 と突き合わせた監査結果。**大半修正済**：
- **修正済**（タグ `audit-fixes-1`/`audit-fixes-2`）：primitive が built-in Eq/Ord 境界を満たす・比較演算子の非結合（`a==b==c` 構文エラー）・提供メソッド衝突を loud error・インライン制約 `[T: Trait]` reject・supertrait `trait Sub: Super` の強制・generic vs 具体の同セレクタ衝突 reject・ambient 型への impl reject・コピー可能型 `move fn` reject。
- **修正済 ARC**（タグ `arc-via-uaf`/`arc-array-elem-fix`）：`via`＋引数つき要求の誤拒否は**コンパイラ自身の ARC heap-use-after-free**だった＝根本は**配列 `_push`/`_set` が struct 要素の heap を deep-copy せず格納するのに `_copy`/`_release` は deep 所有**する非対称。`_push`/`_set` を `E_copy`（値意味論＝push は値をコピー）に直して解消。ASan ビルドのコンパイラ自己コンパイルも clean。

**残（未修正）**：
- **【missing・clang 止まり】Eq/Ord 以外の演算子トレイト未配線**：`Add/Sub/Mul/Div/Rem`・`Neg/Not/BitNot`・`Index/IndexSet`・`Coalesce`・`Pow`・`From/TryFrom` はユーザー型で脱糖されず生 C→clang で落ちる（Plew 診断なし）。eager checker も比較op(50-55)のみ境界チェック・算術 op 素通り。大物の残作業。
- **【silent 逸脱・小】曖昧な無サフィックス整数リテラルが先頭オーバーロードを選ぶ**（`k(a:I32)`/`k(a:U64)` に `k(a:5)`・呼出位置の曖昧検出が要る）・**`val f = obj.method`（メソッド値化）を受理**（scope 復元の型回復が要る・現状 clang 止まり）。
- **【missing・loud】`@[Ord]` on enum**・**`@[Ord]` は `@[Eq]` を含意しない**（`Ord: Eq`）。
- **既知 deferred**：`any P`・トレイト型引数 `Add[Rhs]`・`#Ext`・`a#P.foo()` 源選択・明示型引数 `f[I32](x)`・`Self` 入力要求の witness 置換（hand-written のみ・derive は無事）。**関連型 `type Item`＝基本実装済**（残＝generic 抽象 `T::Item` 解決）。

**優先度（私見）**：演算子トレイト全配線は大物・需要駆動。残る silent 逸脱2件（曖昧リテラル・method 値化）は小だが実装にやや手間（呼出位置/scope 復元）。

---

**再訪の優先度（私見）**：観測挙動を歪める残りの剥離＝①**イベントループ（async/await→spawn・方式 B）**＝最大の残 ②演算子トレイト全配線（Eq/Ord 以外・需要駆動）／関連型 Iterator ／Dictionary。整数幅・match・ラベル・診断・値意味論・**CoW＋refcount 解放（配列/struct/Ref・非アトミック）**・generics・`Optional`/`Result`/`try`/`??`・**`unique`＋`deinit`＋move 所有権**・**クロージャ（leak-free キャプチャ）**は解消済。残る hidden cost＝循環回収（`WeakRef` 手動 or サイクルコレクタ）・mono 局所 leak・`Array[unique]`/部分 move・F11 の ARC 残留。
