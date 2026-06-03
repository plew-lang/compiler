# 暫定実装と仕様からの意図的剥離（provisional / intentional deviations）

セルフホストを最短で通すため、現コンパイラは `SPEC.md`／`spec/*.md` から**意図的に**多くを省いている。ここはその一覧＝「これはバグでなく既知の暫定」を記録し、後で仕様準拠に寄せる作業の地図にする。各項は **仕様（正典）→ 現状（剥離）→ 理由/再訪時期**。**解消済みの剥離は git 履歴（タグ）に任せてここからは落とす**＝この文書は「いま剥離しているもの」だけを映す。

- 対象＝**正典コンパイラ `compiler/src/_.pw`**（Plew 製・今後の機能はここに additive）。使い捨ての Rust stage0 は self-host 後に退役・削除済（履歴記述に出る「stage0」は当時の throwaway を指す・タグ `stage0-final` で復旧可）。
- **重要な大前提**：観測挙動が仕様の意味から逸れている剥離（hidden *meaning*）と、裏でコストだけ払う剥離（hidden *cost*）は別物。前者（値意味論・オーバーフロー panic・ラベル等）はいずれ必ず埋める。後者（ARC/CoW を leak で代用等）は self-host 後に正しく実装する。

## 2 つのゴール（受理の健全性 ＋ ソース spec-validity）

- **受理の健全性（accepted ⟹ spec-valid）**：このコンパイラが*受理*するコードは spec でも valid。逆向きの不完全性（spec valid だが未実装で reject）は許容。直すべきは **「spec は reject するのに今 accept してしまう」＝hidden meaning** だけ。ランタイム挙動の誤り（hidden cost＝leak・float 未対応等）は対象外。
- **ソース spec-validity**：`compiler/src/*.pw` 自体が完全 spec 準拠コンパイラでもそのまま通る純 spec-valid な Plew であること。コンパイラは自分自身を受理するので、受理の健全性が完全ならソースも自動的に spec-valid＝両者は表裏。これらの enforce は plewc.pw 自身にも適用される（import 必須・全呼び出しラベル付き等）＝新機能の各サイクルで plewc.pw を spec-valid に保ちつつ不動点を維持（ADD→reseed→USE）。

主な受理健全性チェック（import-gating・ラベル検査・match 網羅・無損失 `as`・struct/array `==` 拒否・`val` 代入の可変性検査）は**実装済**。各々の残ギャップは下の該当テーマ節に記載。**唯一の未完チェック＝下記 S2**。

- ⏳ **S2 @Std I/O の実シグネチャ**：`print`/`write`/`writeByte`/`readStdin`/`readFile`/`argCount`/`argAt` は現状ハードコードの placeholder。完全コンパイラは実 `@Std` で解決する必要。`readFile`→`Result` 可謬化の前提（`Optional`/`Result`/`try`）は実装済なので技術的には可能で、残るは std モジュールが intrinsic を呼ぶ際の **import ゲート整合**（std 内部の intrinsic 使用許可）と **`print(整数)` の真シグネチャ決定**（std 領域・spec 表面ゆえ要相談）。
- ⚠️ **C 予約語と衝突する識別子**（`default`/`double` 等を変数/関数/フィールド名に使う）→ 名前マングリング未実装ゆえ生成 C が壊れる＝**受理健全性の既知の穴**（spec-valid を accept して壊れた C を吐く・hidden meaning）。コンパイラ自身は回避済・ユーザーコードで顕在化。直し：codegen で識別子を安全な C 名へマングル。

## メモリ・所有権（最大の剥離）

- **値意味論＋CoW** → ✅ **実装済**（非アトミック refcount＋copy-on-write）。`Array[T]`/struct は `rc` 付き（`{data,len,cap,long long* rc}`・NULL＝借り物〔`.bytes`/文字列リテラル〕）。束縛は **O(1) 共有＋retain**（`_share`/`Struct_share`）、変異点（`_set`/`_push` の `_unique`）で **rc>1 なら複製してから書く**＝値意味論を保ったまま遅延コピー。`Ref` 箱も同じ rc ヘッダで refcount 化（共有可変のまま）。解放＝scope 末・早期 exit（`return`/`break`/`continue`・`panic` は不走）・成長時の旧バッファで、配列要素/struct フィールドを再帰解放（深い `_copy` とセット）。**RC は非アトミック**（spawn 境界で実体化ゆえ・→ [design-decisions.md](design-decisions.md)）。全 fixpoint＋ASan（テスト＋自己コンパイル）で実証。残：`WeakRef`・循環回収・mono struct/enum の share/release（mono 局所 leak・安全）。spec/03。
- **`WeakRef` / 循環回収** → 無し（リークで代用）。
- **`unique`/`borrow`/`move`/`deinit`** → ✅ **実装済＋健全性ハードニング完了**（タグ `unique-deinit`/`unique-move`/`unique-checks`/`unique-nested`/`unique-ref-deinit`/`unique-loud-rejects`/`unique-cond-flow`/`unique-no-generic-args`/`unique-no-double-deinit`/`unique-give-guard`）。`unique struct`＋`deinit`（決定的破棄・型本体→フィールド宣言順・ネスト再帰・合成 `Type_deinit`）・`move`/`borrow` 前置＋引数モード・線形 move 追跡（`Local.moved`・use-after-move/bare コピー/bare 引数/伝染/モード必須を reject・`return` の per-exit 除外）・`Ref[unique]` の最後の解放で deinit 発火・`inout`/`inout fn` は正規動作。**unique 値が黙ってコピー/leak/二重 deinit する穴を全て塞いだ**（`Array[unique]`・generic 型引数・条件付き move・struct フィールド/`Ref`/`give` への place コピーを全て loud に reject）＝危険な unique パスは「正しく動く」か「loud に弾く」だけ。**追加機能も実装済**（タグ `unique-reassign`/`unique-move-fn`）＝`mut val` unique の**再代入**（旧値 deinit→新値 store・直線版）・**消費メソッド `move fn` self**（self 所有・全 exit で deinit・呼び出しでレシーバ moved 印・`borrow fn`＝`fn` 同義）。残（全て loud reject か N/A）：部分 move/return・条件付き move/消費（flow 解析 TODO）・分岐内 unique 再代入・value-position `give`・`local struct`（spawn 段）。spec/03。
- **`local` 型**（spawn を越えられない・`Ref` 持ちは必須）→ 無し。spawn/async 実装時に。spec/03,14。
- **`inout`** → 実装済（C ポインタ）。**単純変数・合成可変性（`base.field`・`a[i]`・`.append`/`inout fn` 受信側）の代入可変性検査あり**。残：**重なり inout 検査なし**（spec は同一場所への複数 inout を禁止・lint＋限定 panic）。spec/03。
- **place 越しの get-modify-set 脱糖**（`arr[i].field=x` 等） → 未実装（単純な代入のみ）。spec/03。

## 数値モデル

- **幅つき整数 `I8..U64`** → ✅ **厳密幅 stdint で実装**（各型が `int8_t…int64_t`/`uint16_t…uint64_t`・**U8 は `unsigned char`**＝`.bytes` バッファ共有のため・`Bool` だけ `long long`）。**overflow/0除算 panic**（`__builtin_*_overflow`・符号付き `INT_MIN/-1`・`x % -1`=0 で C UB 回避）・**リテラル文脈型付け**（範囲検査＋厳密 no-default・型サフィックス `5U64`・先頭 `-` 畳み込み）。残（rare な穴）：両オペランドが幅不明な式の算術（`(1+1)` 等リテラルのみ）と配列要素 `/= %=` の narrow-signed `INT_MIN/-1`。`wrapping*` メソッドは additive 予定。
- **浮動小数点 `F32/F64`** → **未実装**（NaN 比較 panic・float `assert` も float 待ち）。spec/02,12。

## レンジ（暫定）

- **`a..<b`/`a..=b` は第一級の値**（`HalfOpenRange`/`ClosedRange` 2 型・JSX 糖衣・要素 `Ord`・`Step` で反復） → **現状：`for` のヘッドでしか書けない**。`for val i in a..<b`/`a..=b` をその場で C の for ループに脱糖するだけ。レンジ型・値・`Step`/`Ord`・素の `..` は無い。spec/02,11。

## 文字列

- `String`＝不変・UTF-8 妥当・`==` バイト等価な **CoW 値型** → **現状：`{const char* data; long long len}`・不変・byte-`==`**（不変と byte-eq は spec 通り・不変ゆえ共有で観測的に正しい）。残：**UTF-8 妥当性チェックなし**・**連結なし**・**`scalars`/`graphemes`/`Ord`/substring/`Slice` なし**・解放なし（leak）。`.bytes`（`Array[U8]`・O(1) 共有ビュー）は spec 通り。spec/02。
- **文字列リテラルのエスケープ**：内容を C へ **verbatim 透過**（`\n`/`\"`/`\\`/`\t` 等 C と共通のものだけ動く）。Plew 固有エスケープは未対応。

## 配列・辞書・集合・タプル

- `Array[T]`：✅ **値意味論＋CoW＋解放を実装**（上述メモリ節）。添字 `U64`・範囲外 panic は spec 通り。`[E; N]`/const generics/`Slice`/部分文字列は **spec 自体が当面保留**。
- **`Dictionary[K,V]`（lang item・`[k:v]` リテラル）／`Set[E]`** → **未実装**（Hash が要る大物）。
- **ラベル付き無名レコード `(x: I32, y: I32)`** → 未実装（struct のみ）。

## 型システム：ジェネリクス・トレイト・拡張

- **ジェネリクス `[T]`／`[T,U]`** → ✅ **実装済（タグ `generics-data`/`generics-methods`）**：struct/enum/fn/`impl[T]` の型パラメータ・単相化（`Box_I32`）・generic struct/enum（`Optional`/`Result` 含む）・generic メソッド（レシーバ型由来）。残 additive：generic free 関数の呼び出し位置推論＋明示 `id[I32](x)`・メソッド own 型パラメータ `map[U]`＋推移的インスタンス化・`where` 制約（traits 待ち）・関連型。
- **トレイト（`via` 準拠・提供メソッド・`any P` 存在型・blanket・継承）** → **全て未実装**（大物）。
- **演算子→トレイト脱糖**（`+`↔`Add` 等） → 無し。**演算子は数値/String にハードコード**（対象演算子も subset・下記）。
- **拡張 `#Ext`／`defaultExtension`／`A#P` ビュー／無名 impl コヒーレンス** → 全て未実装。
- **`newtype`** → 未実装。

## 関数・呼び出し

- **引数ラベルは必須・宣言順・関数型の同一性の一部** → **部分実装**。ユーザー定義トップレベル関数・メソッドの呼び出しはラベル検査（`hasLabel`＋宣言順で param 名一致・arg 数一致・不一致は `compileError` 診断で reject）。C 出力自体はラベルを落とし位置引数。✅ **ラベル抑制 `~:`**（位置引数・`Param.noLabel`）・**デフォルト引数 `name: T = expr`**（末尾省略のみ）は実装済。✅ **オーバーロード完成**（タグ `overload-mangle`/`overloading`）＝C 名をセレクタ（名前＋各パラメータの ラベル＋型頭）でマングル（`writeFnSelector`）し、`findFunc`/`findMethod` がラベル＋引数型で解決（arity／label／type の3軸・自由関数もメソッドも・`exprType` も解決経由で戻り型を選ぶ・単一名は first-label に fallback で従来通り）。残：**I/O ビルトイン**（暫定シグネチャゆえ非検査）・**関数型同一性へのラベル反映**・オーバーロードした関数値（fn-value は first-by-name）・デフォルト引数の中間省略/配列・struct デフォルト。spec/04,07。
- **インヘレントメソッド `impl Type { fn m(...) }`** → **実装済（subset）**。`fn`（by-value self）/`inout fn`（self 可変・C ポインタ）の 2 モード・`recv.m(label: arg)`・ラベル検査・C へ `Type_m(self, …)` マングル（`self` 暗黙）。✅ **引数型オーバーロード**（セレクタ＝名前＋ラベル＋型・タグ `overloading`）・✅ **`move fn`／`borrow fn` self**（消費／借用メソッド）実装済。残：トレイト/拡張のメソッド・一時値レシーバへの `inout`。spec/07。
- **クロージャ／関数値** → ✅ **実装済（不変値キャプチャ＋スカラー mut 参照キャプチャ）**：関数型 `fn(...)->R` は一律 **fat closure `PlewClosure{fn,env,rc,drop}`**（C 関数ポインタ単体から移行・呼び出し ABI は `R fn(void* env, params...)`・bare 関数値はサンク `<sel>__thunk` 経由・呼び出し位置で `.fn` を具体署名へキャスト）。クロージャリテラル＝`__closure<id>(void* __env, ...)`・高階関数。**キャプチャ**：(1)**不変（`val`）の値キャプチャ**＝スカラー（整数/Bool）・String・array・Ref・plain struct（env 構造体 `__closure_env<id>` に格納・ヒープ所有は retain〔share〕して格納＝エスケープ後も生存・`val` 不変ゆえ値キャプチャ＝参照キャプチャと観測同一＝spec 準拠）。(2)**`mut val` の参照キャプチャ＝スカラーのみ**（**箱化**＝外側ローカルを `T*` のヒープ ARC セルにし〔`plew_arc_alloc`〕・env は `plew_ref_share` で retain したポインタを保持・読み書きは両側 deref で**共有**＝`makeCounter` が動く・Swift 流）。body は `((__closure_env<id>*)__env)->name`、boxed は `(*…->name)`。**未対応は loud reject**（silent な意味逸脱を出さない）：**`mut val` 非スカラー**（array/struct/String の参照キャプチャ）・`unique`/generic 実体化/enum/関数値のキャプチャ・**ネスト closure**・**val capture への代入**。**hidden cost**＝env・retain したヒープ・箱化セルは現状解放せず leak（double-free/UAF 無し・`plew_closure_share/release` 配備済）。メソッド値は spec で禁止（spec 通り未対応）。**次（B2b-2）**＝leak 解消＝**env drop（閉包 release 配線）＋閉包ライフタイム/move 追跡（エスケープした閉包は factory が release しない）**。観測挙動は不変でコスト（メモリ回収）だけ埋める additive。**B2b-3**＝`mut val` 非スカラー箱化・`mut val` 参照キャプチャ閉包の `local` マーク（spawn 不可・spec/14）。
- **`;` 文区切り** → ⚠️ **既存の未対応（クロージャ無関係）**：Plew は文を改行区切りにし、`;` を文区切りとして使えない。`a; b` を書くと `;` 位置に value 0 の合成 Int ノードができ「integer literal has no type from context」という的外れエラーで落ちる（通常関数本体でも同様）。本来は構文エラーで loud に弾くべき＝パーサ堅牢化の TODO。

## enum 等価（暫定）

- **`Eq`/`Ord` トレイト＋`@[Eq]` derive（メタプロで構造的等価を生成・Rust 流）** → **現状：enum `==`/`!=` を「タグ（variant）比較」に直接脱糖**（variant 構築オペランドは tag index リテラル・それ以外は `(expr).tag`）。**全 nullary な enum だけ許可**（構造的 Eq と完全一致で正しい）・**payload 持ち enum の `==` は hidden meaning を避けるため `compileError` で reject**（タグだけ見て payload 無視の沈黙バグにしない）。`@[Eq]` 実装で構造的 Eq に置換予定。struct の `==` は未対応。spec/08,12,16。
- 補足：variant 値は **JSX 必須**（`<Kind.LParen />`・bare 不採用＝「生成は常に JSX」を維持）。型省略 JSX `<.LParen />`（文脈推論）は surface 追加の未決。

## 制御フロー・match

- **`match` 網羅性をコンパイル時検査** → **実装済**（`_` ワイルドカード or enum 全 variant 被覆・非網羅は `compileError` で reject・網羅 match は末尾 `__builtin_unreachable()`）。パターンは `E.V { val f }` 一段＋`_`＋**rename `{ field: val name }`・discard `{ field: _ }`**＋**or パターン `A | B | …`**（全フィールド束縛必須・選択肢間の束縛名集合不一致はパース時 reject・異名フィールドを rename で共通束縛に揃える payload-or 可）。残：束縛名一致だが**型が食い違う**選択肢は C エラー fallback（クリーン診断でない）・**ガード・ネストパターン無し**・到達不能アーム警告無し。spec/11。
- **値位置の `match`／`if`** → **実装済**（`return match …`／`val x = match …`／`val x = if c { … give a } else { give b }`・ネスト/`else if` 可・C statement-expression 脱糖・`if` 式は `else` 必須）。残：`match` 式の結果型がバインド依存だと誤推論し得る／`give` 値が配列リテラルのときの型付けは未対応。spec/11。
- **`panic`（発散文）** → **実装済**（`panic <msg>`→noreturn `plew_panic`・stderr `panic: <msg>`＋`exit(1)`・unwind なし・`deinit` 非走行）。配列範囲外 panic は個別ランタイムで exit。残：式位置の `panic` は文のみ。

## 演算子（subset）

- **対応**：`+ - * / %`・比較 `== != < <= > >=`・論理 `&& ||`（C 短絡）・**ビット/シフト `& | ^ << >> ~`**・単項 `! - ~`・代入 `=`・複合 `+= -= *= /= %=`＋**ビット系 `&= |= ^= <<= >>=`**（純粋脱糖）・**`??`（Coalesce・Optional）**。
- **未対応**：`pow`/`**`・`Neg`/`Not`/各種演算子トレイト・`as` 以外の数値変換。
- **優先順位**：`??` を含め 10 段（低→高：`|| < && < 比較 < ?? < | < ^ < & < シフト < +- < */%`・`??` 右結合）。spec の 14 段とビット/算術/論理/比較/`??` の相対順序は一致。未対応段（`as` の位置・レンジ）と比較/レンジの非結合は未強制。spec/12。
- **`as`**：**数値↔数値の C キャストのみ**（無損失検査済＝source 幅を `TypeInfo` で復元し narrowing は reject・式幅も伝播）。残：`From`/`TryFrom`（`as` の全域変換脱糖・`try` の From 変換＝現状 `try` はソース/関数戻りの **エラー型一致 `E==E'` を要求**・違うと C 型不一致）・`?.`（オプショナルチェーン）は未実装。spec/12,13。
- **`??`/`try` は `@Std/Core` の Optional/Result の tag/field レイアウトをハードコード前提**（Some=tag0/`v`・Ok=tag0/`value`・Err=tag1/`error`）。lang-item ゆえ妥当だが、ユーザーが別形の Optional/Result を定義しても `??`/`try` はこの形を仮定。見直し：lang-item を spec で固定 or コンパイラが Core のシンボルを参照（ambient 化〔上記 import 節〕とセットで整理）。

## 可視性・モジュール・import

- **`pub`/`export`／名前空間 import（`Io.print`）／`_.pw` ディレクトリ解決** → **未実装**。名前解決は（全ファイル連結後の）線形スキャン。
- **`part`／`import` のパスルート** → 部分実装。`part ./Name`（兄弟ファイル）・**`part ./Sub/Name`（サブディレクトリ part パス＝`Sub/Name.pw` に解決・コンパイラ自身が `part ./Codegen/Expr` 等で依存）**・`import @Std/Io with { … }`・`@Std/Process with { … }` の `with { }` 選択形をパース＆enforce（バイト列連結→単一アリーナ/単一 C 出力・スコープ共有/名前空間なしは spec 通り）。`@Std/X` は `dirname(argv[0])/std/X.pw` 解決＝**バイナリ横の `std/`**（リポジトリでは `compiler/plewc` 起動ゆえ `compiler/std/X.pw`・Core.pw が実在）。バイナリと std が隣り合う限りディレクトリ移動に強く**現運用（self-host/テスト）は無問題**。残る課題は**配布時のみ**＝`plewc` を PATH 経由の bare 名で起動すると argv[0] にディレクトリ接頭辞が無く stdRoot が cwd 相対に外れる→インストール先 or バイナリ埋め込みで std を置く設計はそこで詰める。認識する import 名は I/O ビルトインだけで**名前↔モジュール対応も検査**（誤モジュール import は無効）。enforce は `compileError`＝stderr `plewc: error: …`＋`exit(1)`。残：`_.pw` ディレクトリ・ネストした part（root の part のみ走査）・`../`/`/` ルートの完全対応・forest/循環検査・行番号。
- **lang item / ambient 型** → 概念なし（名前空間はフラット）。`print`/`write`/`writeByte`/`readStdin`/`readFile`/`argCount`/`argAt` は **import で gate される埋め込みビルトイン**（本来は `@Std`＋`Format` 等・`argCount`/`argAt` は `Process.args()` の暫定スタンドイン）。移行レシピは [worklog.md](worklog.md)。
- **`Optional`/`Result` が ambient でなく明示 `import @Std/Core` を要求**（spec ではこの 2 つは lang item＝import 不要）。**意図的に放置する既知の spec 違反**。理由と直し方：名前空間は今フラット（全ファイルを 1 `Comp` に連結・可視性ゲート I2 未実装）なので、「ambient」＝「ローダが起動時に無条件 load」・「import 必須」＝「import directive を見た時だけ load」の差でしかなく、中間（一部だけ ambient）を可視性で作れない。ambient 化の本体は Core を起動時に無条件 load するだけ（explicit `import @Std/Core` は `pathSeen` dedup で冪等に併存）だが、付随して **(1) `assert` の巻き込み**＝Core 丸ごと load すると spec で import 必須の `assert` も ambient 化するので **prelude ファイル分割**（lang item 型だけ無条件 load・`assert` は別 import モジュールへ）が要る、**(2) 既存テストの自前 `enum Optional` との重複定義**＝lang item は再定義不可なので重複エラーが spec 的に正しく、テスト移行が要る。これらを処理する気になったら着手（フラットモデルのままでも A=無条件 load＋ファイル分割で可能・本物の可視性 I2 は不要）。
- **エントリ `fn main`**：`int main(int argc, char** argv)` に固定脱糖（spec の `fn main`/`async fn main`・戻り `()|Result` とは別）。

## 構築・factory

- **JSX `<Type f=e/>`／`<E.V f=e/>`** → 対応。
- **`factory`／`optional`・`result factory`／フィールドデフォルト値／memberwise vs `pub factory`** → 未実装。全フィールドを名前付きで必須指定。

## 共有可変・並行性・メタプログラミング

- **`Ref[T]`（共有可変）** → ✅ **基本実装済**：rc ヘッダ付きヒープ箱・`<Ref[T] value=e/>`・`r->field`・コピーで retain 共有・scope 末で release（最後の解放で箱を free＋pointee の配列/struct を release・**`Ref[unique]` は pointee の `deinit`→`release` を発火**＝unique を共有/格納する正規パターンが動く）。残：`WeakRef`＋`upgrade()`・循環回収・bare `<Ref value=e/>` 型推論（明示 `[T]` 必須）。spec/03,14。
- **`async`/`await`/`spawn`/`Promise`/`JoinHandle`/チャネル** → **未実装**（イベントループ＝最大の残）。✅ 土台＝関数値＋非キャプチャクロージャは実装済（spawn にはキャプチャが要る）。
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
- **【pre-existing・broad】`val x = expr`（注釈なし）の型推論なし**＝generic 呼び出しの引数型推論も連鎖劣化（注釈必須）。
- **既知 deferred**：`any P`・関連型・トレイト型引数 `Add[Rhs]`・`#Ext`・`a#P.foo()` 源選択・明示型引数 `f[I32](x)`・`Self` 入力要求の witness 置換（hand-written のみ・derive は無事）。

**優先度（私見）**：演算子トレイト全配線は大物・需要駆動。残る silent 逸脱2件（曖昧リテラル・method 値化）は小だが実装にやや手間（呼出位置/scope 復元）。

---

**再訪の優先度（私見）**：観測挙動を歪める残りの剥離＝①トレイト/`where`/Dictionary ②クロージャキャプチャ→spawn→async。整数幅・match・ラベル・診断・値意味論・**CoW＋refcount 解放（配列/struct/Ref・非アトミック）**・generics・`Optional`/`Result`/`try`/`??`・**`unique`＋`deinit`＋move 所有権**は解消済。残る hidden cost＝循環回収（`WeakRef` 手動 or サイクルコレクタ）・mono 局所 leak・`Array[unique]`/部分 move。
