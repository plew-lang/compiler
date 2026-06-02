# 暫定実装と仕様からの意図的剥離（provisional / intentional deviations）

セルフホストを最短で通すため、現コンパイラは `SPEC.md`／`spec/*.md` から**意図的に**多くを省いている。ここはその一覧＝「これはバグでなく既知の暫定」を記録し、後で仕様準拠に寄せる作業の地図にする。各項は **仕様（正典）→ 現状（剥離）→ 理由/再訪時期**。

- 対象＝**正典コンパイラ `compiler/src/_.pw`**（Plew 製・今後の機能はここに additive）。使い捨ての Rust stage0 は self-host 後に退役・削除済（履歴記述に出る「stage0」は当時の throwaway を指す・タグ `stage0-final` で復旧可）。
- **重要な大前提**：観測挙動が仕様の意味から逸れている剥離（hidden *meaning*）と、裏でコストだけ払う剥離（hidden *cost*）は別物。前者（値意味論・オーバーフロー panic・ラベル等）はいずれ必ず埋める。後者（ARC/CoW を leak で代用等）は self-host 後に正しく実装する。

## 現在の目標：受理の健全性（意味上 Plew として正しい）

**目標＝このコンパイラが*受理*するコードは spec でも valid（完全な Plew コンパイラも通せる）。** 逆向きの不完全性（spec valid だが未実装で reject＝`<.LParen />`・トレイト・`Result`/`try` 等）は許容。直すべきは **「spec は reject するのに今 accept してしまう」＝hidden meaning** だけ。ランタイム挙動の誤り（hidden cost＝leak・int 幅・overflow 非 panic）はこの目標の対象外（後回し）。

**受理の健全性チェックリスト（spec が拒むのに今通る＝要修正）**：
1. ✅ ~~import なしで `print`/`write` 等が書ける~~ → **解消**。I/O ビルトインは ambient でなく `import @Std/Io with { … }`（print/write/writeByte/readStdin/readFile）・args は `@Std/Process with { argCount, argAt }` が必須。名前↔モジュールも検査（`@Std/Process with { print }` は print を有効化しない）。未 import の使用は `compileError` 診断（`plewc: error: …`＋非ゼロ終了）で reject。
2. ✅ ~~ラベル無視~~ → **部分解消**。ユーザー定義トップレベル関数の呼び出しは、各引数のラベル必須・宣言順・名前一致を検査（不一致は `compileError` 診断で reject）。残：ラベル抑制 `~:`・メソッド呼び出し・関数型同一性へのラベル反映・I/O ビルトインのラベル（暫定シグネチャゆえ非検査）は未対応。
3. ✅ ~~非網羅 match が通る~~ → **解消**。match は網羅必須（`_` ワイルドカード、または enum 全 variant の被覆を検査・非網羅は `compileError` 診断で reject）。残：到達不能アーム警告・ガード・ネストパターンは未対応（元々）。
4. **lossy な `as` が通る**（`300 as U8` を C キャストで silent truncate） → spec は `as`＝infallible 限定（縮小は `TryFrom`）。`as` を無損失に制限。
5. ✅ ~~struct の `==`~~ → **解消**。比較演算子（`== != < <= > >=`）を struct/array に適用＝`Eq`/`Ord` 無しなので `compileError` 診断で reject（従来は壊れた C を吐いて clang が偶発的に弾いていたのを明示エラーに）。残：enum/String の順序比較（`<` 等）は依然「壊れた C で偶発的 reject」＝ホールではないが未整理。
6. ✅ ~~不変束縛 `val` への代入が通る~~ → **部分解消**。単純変数への代入 `x = …`／`x OP= …` は、対象が `mut val` ローカル or `inout` 仮引数でなければ `compileError` 診断で reject（spec: `val` は不変・`mut val` のみ可変記憶域）。残：**フィールド/添字越しの変更**（`a.f = x`・`a[i] = x`）の合成可変性検査（束縛側 `mut` 要求）・不変配列への `.append` 等のメソッド経由変更は未検査（incremental・受理健全性は accepted⟹valid のみ要求するので未検査でも方向は崩れない）。

→ **大前提**：これらの enforce は plewc.pw 自身にも適用される（plewc.pw も import 必須・全呼び出しラベル付き等になっている）。stage0 退役＋C 種ブートストラップ済なので、新機能を追加する各サイクルで plewc.pw 自身も spec-valid に保ちながら不動点を維持する（ADD→reseed→USE）。

## メモリ・所有権（最大の剥離）

- **値意味論＋CoW** → **現状：参照セマンティクス＋リーク**。`Array[T]` は `{T* data; len; cap}` でヒープ確保し **free しない**（append の旧バッファもリーク）。代入・受け渡しは C の構造体コピー（ポインタ共有）＝**エイリアス後の変更が観測できてしまう**＝spec の値意味論と逆。回避は「stage1 を arena+index・単一所有で書く規律」のみ。spec/03。
- **ARC / `WeakRef` / 循環回収** → 無し（リークで代用）。
- **`unique`/`local`/`borrow`/`move`/`Ref`/`WeakRef`/`deinit`** → 無し。すべてコピー可能・by-value。`borrow`/`move` は stage0 がコピー可能型でエラーにする（spec 通り）が、そもそも unique 型が無い。
- **`inout`** → 実装済（C ポインタ）。ただし **重なり inout 検査なし**（spec は同一場所への複数 inout を禁止・lint＋限定 panic）。**単純変数への代入は可変性検査あり**（`val` 不変・`mut val`/`inout` のみ代入可＝受理健全性 #6）が、フィールド/添字越しの合成可変性は未検査。spec/03。
- **place 越しの get-modify-set 脱糖**（`arr[i].field=x` 等） → 未実装（単純な代入のみ）。spec/03。

## 数値モデル

- **幅つき整数 `I8..U64`・`F32/F64`** → **現状：全整数 `long long`（int64_t）**。幅の区別なし・符号なし演算の意味なし・**浮動小数点は一切なし**。spec/02。
- **0 除算は常に panic** → **実装済（binary `/`・`%`）**：`a / b`・`a % b` は `plew_div`/`plew_mod`（preamble・除数 0 で `plew_panic`→exit(1)）に脱糖。`%` は C 切り捨て＝剰余は被除数の符号（spec 通り）。残：複合代入 `/=`/`%=`（簡易・配列 place 経由とも）は今は生 `/`/`%`＝未チェック（hidden cost＝後回し・soundness 対象外）。
- **オーバーフロー panic**・**NaN 比較で panic**・`assert` 常時 ON → **未実装**（C の UB / wraparound / crash 任せ）。オーバーフロー検査は幅つき整数（要 TypeInfo への幅保持）に依存ゆえ整数幅エピックと同時。`wrapping*` メソッドも無し。spec/12。
- **数値リテラルは多相・既定型なし・曖昧はエラー** → stage0 は実装（双方向推論）。ただし `print` の引数だけ I64 にフォールバック（stage0 の便宜）。stage1 はリテラルを素朴に long long 化（曖昧検査は stage0 が既に弾く前提）。
- **U8**：配列要素のときだけ `unsigned char`（`.bytes` の char バッファ共有のため）・スカラ U8 は long long。

## レンジ（暫定）

- **`a..<b`/`a..=b` は第一級の値**（`HalfOpenRange`/`ClosedRange` 2 型・JSX 糖衣・要素 `Ord`・`Step` プロトコルで反復） → **現状：`for` のヘッドでしか書けない**。`for val i in a..<b`/`a..=b` を **その場で C の for ループに脱糖**するだけ。レンジ型・レンジ値・`Step`/`Ord`・素の `..` は無い。要素は long long 固定。spec/02,11。

## 文字列

- `String`＝不変・UTF-8 妥当・`==` バイト等価な **CoW 値型** → **現状：`{const char* data; long long len}`・不変・byte-`==`**（不変と byte-eq は spec 通り）。ただし **CoW なし**（stage0 のリーク/参照）・**UTF-8 妥当性チェックなし**・**連結なし**・**`scalars`/`graphemes`/`Ord`/substring/`Slice` なし**。`.bytes`（`Array[U8]`・O(1) 共有ビュー）は spec 通り。spec/02。
- **文字列リテラルのエスケープ**：内容を C へ **verbatim 透過**（`\n`/`\"`/`\\`/`\t` 等 C と共通のものだけ正しく動く）。decoded length だけ自前計算。Plew 固有エスケープは未対応。

## 配列・辞書・集合・タプル

- `Array[T]`：上記メモリ項参照（参照＋リーク・CoW 無し）。添字 `U64`・範囲外 panic は spec 通り。`[E; N]`/const generics/`Slice`/部分文字列は **spec 自体が当面保留**。
- **`Dictionary[K,V]`（lang item・`[k:v]` リテラル）／`Set[E]`** → **未実装**。
- **ラベル付き無名レコード `(x: I32, y: I32)`** → 未実装（struct のみ）。

## 型システム：ジェネリクス・トレイト・拡張

- **ジェネリクス `[T]`／`where` 制約／関連型** → **全て未実装**（具体型のみ）。
- **トレイト（`via` 準拠・提供メソッド・`any P` 存在型・blanket・継承）** → **全て未実装**。
- **演算子→トレイト脱糖**（`+`↔`Add` 等） → 無し。**演算子は数値/String にハードコード**。対象演算子も subset（下記）。
- **拡張 `#Ext`／`defaultExtension`／`A#P` ビュー／無名 impl コヒーレンス** → 全て未実装。
- **`newtype`** → 未実装。

## 関数・呼び出し

- **引数ラベルは必須・宣言順・関数型の同一性の一部** → **部分実装**。ユーザー定義トップレベル関数の呼び出しはラベルを検査（各引数 `hasLabel`＋宣言順で param 名と一致・arg 数一致・不一致は `compileError` 診断で reject）。C 出力自体は依然ラベルを落とし位置引数。**ユーザーメソッド呼び出しもラベル検査あり**（`recv.m(label: arg)`・引数数＋ラベル一致）。未対応：ラベル抑制 `~:`・**I/O ビルトイン**（`write(s:)`/`argAt(…)` 等は暫定シグネチャゆえ generic パス手前で個別処理＝非検査）・ラベルによるオーバーロード・関数型同一性へのラベル反映。spec/04。
- **インヘレントメソッド `impl Type { fn m(...) }`** → **実装済（subset）**。`fn`（by-value self）/`inout fn`（self を可変・C ポインタ）の 2 モード・呼び出し `recv.m(label: arg)`・ラベル検査あり・C へは `Type_m(self, …)` にマングル（`inout fn` は `&recv`）。`self` は暗黙（明示トークン無し＝codegen が現在レシーバを覚えて `self` 識別子を特別扱い）。**未対応**：引数型オーバーロード（セレクタ＝名前＋ラベル）・`move fn` self・トレイト/拡張のメソッド・メソッドの一時値レシーバへの `inout`（lvalue 前提）。**自由関数は名前一意**（同名不可）。配列の `append` は型ベースのビルトイン経路。
- **デフォルト引数（呼び出しごと再評価・定義側スコープ）** → 未実装。
- **クロージャ／メソッド値** → 未実装（spec はメソッド値を禁止＝こちらは spec 通り）。

## enum 等価（暫定）

- **`Eq`/`Ord` トレイト＋`@[Eq]` derive（メタプロで構造的等価を生成・Rust 流）** → **現状：enum `==`/`!=` を「タグ（variant）比較」に直接脱糖**（variant 構築オペランドは tag index リテラル・それ以外は `(expr).tag`＝例 `(k).tag == 0`）。stage1 のみ（stage0 は凍結ゆえ未対応＝plewc.pw 自身はまだ match で判別）。**全 nullary な enum だけ許可**（＝`curKind == <Kind.LParen />` は構造的 Eq と完全一致で正しい）。**payload 持ち enum の `==` は hidden meaning を避けるため `compileError` 診断で reject**（タグだけ見て payload を無視する沈黙バグにしない）。`@[Eq]` 実装で構造的 Eq に置換予定。struct の `==` は未対応。spec/08,12,16。
- 補足：variant 値は **JSX 必須**（`<Kind.LParen />`）で確定（bare `Kind.LParen` は不採用＝「インスタンス生成は常に JSX」を維持・「どちらでも書ける」回避）。型省略 JSX `<.LParen />`（文脈推論）は surface 追加の未決。

## 制御フロー・match

- **`match` 網羅性をコンパイル時検査** → **実装済**。`_` ワイルドカード or enum 全 variant 被覆を検査（非網羅は `compileError` 診断で reject）。網羅な match（全 variant 列挙・wildcard 無し）は従来どおり末尾に `__builtin_unreachable()`。残：到達不能アーム警告・ガード・ネストパターン・`val x` 捕捉アームは未対応。spec/11。
- **match アーム**：文位置は **block アーム**（`=> { … }`）、**式位置は bare 式アーム**（`=> v`）。パターンは `E.V { val f }` 一段＋`_`＋**フィールド束縛の rename `{ field: val name }`・discard `{ field: _ }`**＋**or パターン `A | B | …`**（全フィールド束縛必須は spec 通り）。or パターンは「選択肢ごとに同一 body を共有するアームへ複製」で脱糖し、**選択肢間の束縛名集合の不一致はパース時にクリーン診断で reject**（`A { val r } | B { val s }`）。nullary・同名フィールド punning・**異名フィールドを rename で共通束縛に揃える payload-or**（`Circle { radius: val v } | Square { side: val v }`）すべて対応。残：束縛名は一致するが**型が食い違う**選択肢（`A{x:I64} | B{x:String}`）は C エラー fallback（クリーン診断でない）。**ガード・ネストパターン無し**。文位置の bare 式アーム・式位置の block(`give`)アームは未対応（位置ごとに片方）。
- **値位置の `match`／`if`** → **実装済**（`return match k { … => v }`／`val x = match …`／`val x = if c { … give a } else { give b }`／式中ネスト可・`else if` チェーン可）。どちらも C statement-expression に脱糖（`if` 式は各分岐が `give` で終わる block・**`else` 必須**＝値位置は必ず yield・結果型は then 分岐の `give` 式から推論）。`give` は文（`Stmt.Give`）で、囲う block-expr の結果テンポラリへ代入。残：`match` 式の結果型はバインド依存だと誤推論し得る／`give` の値が配列リテラルのときの型付けは未対応（既存配列変数なら可）。spec/11。
- **`panic`（発散文）** → **実装済**。`panic <msg>`（msg は String 式）→ noreturn な `plew_panic`（stderr に `panic: <msg>`＋`exit(1)`）。spec 通り回復不能・unwind なし・`deinit` 非走行（そもそも未実装）。残：spawn 内のプロセス停止は単一スレッドゆえ自明・式位置の `panic` は文のみ。配列範囲外 panic は従来通り個別ランタイムで exit（メッセージ別）。

## 演算子（subset）

- **対応**：`+ - * / %`・比較 `== != < <= > >=`・論理 `&& ||`（C 短絡）・**ビット/シフト `& | ^ << >> ~`**・単項 `! - ~`・代入 `=`・複合 `+= -= *= /= %=`・**ビット系複合代入 `&= |= ^= <<= >>=`**（純粋脱糖）。
- **未対応**：`??`（Coalesce）・`pow`/`**`・`Neg`/`Not`/各種演算子トレイト・`as` 以外の変換。
- **優先順位**：stage1 は **9 段**（低→高：`|| < && < 比較 < | < ^ < & < シフト < +- < */%`）。spec の **14 段**（`as`>`*/%`>`+-`>シフト>`&`>`^`>`|`>`??`>比較>`&&`>`||`>レンジ）と、ビット/算術/論理/比較の相対順序は一致。未対応段（`as` の位置・`??`・レンジ）と比較/レンジの非結合は未強制。spec/12。
- **`as`**：**数値↔数値の C キャストのみ**。spec は「`as` は infallible 固定＝`From` 経由の全域変換」。`From`/`TryFrom`/`try`/`Result`/`Optional`/`?.` は **全て未実装**。spec/12,13。

## 可視性・モジュール・import

- **`pub`/`export`／`/`・`../` ルート／名前空間 import（`Io.print`）／`_.pw` ディレクトリ解決** → **未実装**。名前解決は（全ファイル連結後の）線形スキャン。
- **`part ./Name`（部分実装）** → 同一モジュールの複数ファイル化に対応。root ファイルの `part ./Name` directive を走査し、`Name.pw`（兄弟ファイル）を readFileBytes で読んで**バイト列を連結**し、1 つの buffer として lex/parse（単一アリーナ・単一 C 出力モデルゆえ別コンパイルはせず全部入りにする）。スコープ共有・名前空間なしは spec 通り。残：`_.pw` ディレクトリ・`../`・`/` ルート・ネストした part（root の part のみ走査＝part 先の part は未追従）・forest/循環検査なし。パス構築は `readFileBytes(path: Array[U8])` ビルトイン（`@Std/Io` の `readFile` import で一緒に有効化される内部ヘルパ）。
- **import（部分実装）** → `import @Std/Io with { … }`・`import @Std/Process with { … }` の **`with { }` 選択形のみ**パース＆enforce。認識する名前は I/O ビルトインだけ（`@Std/Io`＝print/write/writeByte/readStdin/readFile・`@Std/Process`＝argCount/argAt）で、**名前↔モジュール対応も検査**（誤モジュール import はそのビルトインを有効化しない）。それ以外の import パス・名前はパースして無視（単一ファイルゆえ解決先が無い）。enforce は `compileError(msg)` ビルトイン＝stderr へ `plewc: error: …`＋`exit(1)`（受理健全性チェック共通・行番号は未）。
- **lang item / ambient 型** → 概念なし。`print`/`write`/`writeByte`/`readStdin`/`readFile`/`argCount`/`argAt` は **import で gate される埋め込みビルトイン**（本来は `@Std`＋`Format` 等で、名前自体も `argCount`/`argAt` 等は `Process.args()` の暫定スタンドイン）。移行レシピは [worklog.md](worklog.md)。
- **エントリ `fn main`**：`int main(int argc, char** argv)` に固定脱糖（spec の `fn main`/`async fn main`・戻り `()|Result` とは別）。

## 構築・factory

- **JSX `<Type f=e/>`／`<E.V f=e/>`** → 対応。
- **`factory`／`optional`・`result factory`／フィールドデフォルト値／memberwise vs `pub factory`** → 未実装。全フィールドを名前付きで必須指定。

## 並行性・メタプログラミング

- **`async`/`await`/`spawn`/`Promise`/`JoinHandle`/チャネル** → 全て未実装（コンパイラに不要）。
- **メタプログラミング（`Derive`・コード生成）** → 未実装（spec 上も最後）。

## 字句・文の区切り（ここは spec 通り）

- Go 流の改行自動終端＋括弧内継続＝**spec 準拠**（剥離ではない）。
- コメントは `//` 行コメントのみ（ブロックコメント未対応）。

---

**再訪の優先度（私見）**：観測挙動を歪める剥離＝①値意味論/CoW（最重要・ARC とセット）②整数幅＋オーバーフロー/0除算 panic ③ラベル必須＋検査 ④`Result`/`try`/`Optional` ⑤トレイト/ジェネリクス。これらは self-host 後に Plew 側（stage1）で additive に。hidden cost だけの剥離（leak→ARC 等）は性能要求が出てから。
