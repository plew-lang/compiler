# 暫定実装と仕様からの意図的剥離（provisional / intentional deviations）

セルフホストを最短で通すため、現コンパイラは `SPEC.md`／`spec/*.md` から**意図的に**多くを省いている。ここはその一覧＝「これはバグでなく既知の暫定」を記録し、後で仕様準拠に寄せる作業の地図にする。各項は **仕様（正典）→ 現状（剥離）→ 理由/再訪時期**。

- 対象は 2 つ：**stage0**（Rust・`bootstrap/`・使い捨て・**凍結**＝もう機能追加しない）と **stage1**（`selfhost/plewc.pw`・Plew 製・**正典**＝今後の機能はこちらに additive）。差がある所だけ stage0/stage1 を明記、無ければ両方共通。
- **重要な大前提**：観測挙動が仕様の意味から逸れている剥離（hidden *meaning*）と、裏でコストだけ払う剥離（hidden *cost*）は別物。前者（値意味論・オーバーフロー panic・ラベル等）はいずれ必ず埋める。後者（ARC/CoW を leak で代用等）は self-host 後に正しく実装する。

## メモリ・所有権（最大の剥離）

- **値意味論＋CoW** → **現状：参照セマンティクス＋リーク**。`Array[T]` は `{T* data; len; cap}` でヒープ確保し **free しない**（append の旧バッファもリーク）。代入・受け渡しは C の構造体コピー（ポインタ共有）＝**エイリアス後の変更が観測できてしまう**＝spec の値意味論と逆。回避は「stage1 を arena+index・単一所有で書く規律」のみ。spec/03。
- **ARC / `WeakRef` / 循環回収** → 無し（リークで代用）。
- **`unique`/`local`/`borrow`/`move`/`Ref`/`WeakRef`/`deinit`** → 無し。すべてコピー可能・by-value。`borrow`/`move` は stage0 がコピー可能型でエラーにする（spec 通り）が、そもそも unique 型が無い。
- **`inout`** → 実装済（C ポインタ）。ただし **重なり inout 検査なし**（spec は同一場所への複数 inout を禁止・lint＋限定 panic）。`inout` の mut 束縛検査もなし。spec/03。
- **place 越しの get-modify-set 脱糖**（`arr[i].field=x` 等） → 未実装（単純な代入のみ）。spec/03。

## 数値モデル

- **幅つき整数 `I8..U64`・`F32/F64`** → **現状：全整数 `long long`（int64_t）**。幅の区別なし・符号なし演算の意味なし・**浮動小数点は一切なし**。spec/02。
- **オーバーフロー／0 除算は常に panic**・**NaN 比較で panic**・`assert` 常時 ON → **未実装**（C の UB / wraparound / crash 任せ）。`wrapping*` メソッドも無し。spec/12。
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

- **引数ラベルは必須・宣言順・関数型の同一性の一部** → **現状：ラベルはパースして捨てる**（位置引数で C 出力）。ラベル検査なし・ラベルによるオーバーロードなし・関数型にラベルは乗らない。`~:` ラベル抑制も未使用。spec/04。
- **メソッドの引数型オーバーロード**（セレクタ＝名前＋ラベル） → 無し。**関数は名前一意**（同名不可）。メソッドは `append` のみ stage1 ビルトイン。
- **デフォルト引数（呼び出しごと再評価・定義側スコープ）** → 未実装。
- **クロージャ／メソッド値** → 未実装（spec はメソッド値を禁止＝こちらは spec 通り）。

## enum 等価（暫定）

- **`Eq`/`Ord` トレイト＋`@[Eq]` derive（メタプロで構造的等価を生成・Rust 流）** → **現状：enum `==`/`!=` を「タグ（variant）比較」に直接脱糖**（variant 構築オペランドは tag index リテラル・それ以外は `(expr).tag`＝例 `(k).tag == 0`）。stage1 のみ（stage0 は凍結ゆえ未対応＝plewc.pw 自身はまだ match で判別）。**全 nullary な enum だけ許可**（＝`curKind == <Kind.LParen />` は構造的 Eq と完全一致で正しい）。**payload 持ち enum の `==` は hidden meaning を避けるため loud にエラー**＝plewc が未宣言識別子 `__plew_enum_eq_requires_Eq_derive` を出力し C コンパイルが失敗（タグだけ見て payload を無視する沈黙バグにしない）。`@[Eq]` 実装で構造的 Eq に置換予定。struct の `==` は未対応。spec/08,12,16。
- 補足：variant 値は **JSX 必須**（`<Kind.LParen />`）で確定（bare `Kind.LParen` は不採用＝「インスタンス生成は常に JSX」を維持・「どちらでも書ける」回避）。型省略 JSX `<.LParen />`（文脈推論）は surface 追加の未決。

## 制御フロー・match

- **`match` 網羅性をコンパイル時検査** → **現状：検査せず**（網羅と仮定し、wildcard 無しの末尾に `__builtin_unreachable()`）。spec/11。
- **match アーム**：stage1 は **文位置・block アームのみ**（`=> { … }`）。**ベア式アーム `=> v`・ガード・ネストパターン無し**（`E.V { val f }` 一段＋`_` のみ・全フィールド束縛必須は spec 通り）。
- **値位置の `if`/`match`/ブロック（`give`）** → stage0 は if/block を statement-expression で対応・**stage1 は未対応**（文位置のみ）。`give` は stage1 では非対応。spec/11。
- **`panic`（発散文）** → stage1 未実装（範囲外 panic 等はランタイム関数で個別に exit）。

## 演算子（subset）

- **対応**：`+ - * / %`・比較 `== != < <= > >=`・論理 `&& ||`（C 短絡）・単項 `! -`・代入 `=`・複合 `+= -= *= /= %=`。
- **未対応**：ビット演算/シフト `& | ^ << >> ~`・`??`（Coalesce）・`pow`/`**`・`Neg`/`Not`/各種演算子トレイト・`as` 以外の変換。
- **優先順位**：stage1 は **5 段に簡約**（`|| < && < 比較 < +- < */%`）。spec の **14 段**（`as`>`*/%`>`+-`>シフト>`&`>`^`>`|`>`??`>比較>`&&`>`||`>レンジ）とは別物。比較・レンジの非結合も未強制。spec/12。
- **`as`**：**数値↔数値の C キャストのみ**。spec は「`as` は infallible 固定＝`From` 経由の全域変換」。`From`/`TryFrom`/`try`/`Result`/`Optional`/`?.` は **全て未実装**。spec/12,13。

## 可視性・モジュール・import

- **`pub`/`export`／モジュール（1 ファイル 1 モジュール）／`part`／3 ルート import（`@…`/`/`/`./`）／`@Std`** → **全て未実装**。**単一ファイル**・名前解決は線形スキャン。
- **lang item / ambient 型** → 概念なし。`print`/`write`/`writeByte`/`readStdin`/`readFile`/`argCount`/`argAt` は **コンパイラ埋め込みビルトイン**（本来は `@Std`＋`Format` 等）。移行レシピは [worklog.md](worklog.md)「self-host の契約」。
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
