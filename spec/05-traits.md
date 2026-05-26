# トレイト

トレイトは、型が満たすべき**要求**（メソッド・フィールド・関連値・関連型）と、その上に組んだ**提供メソッド**を束ねる抽象です。型への準拠は `impl Type as Trait` で**明示的に宣言**し、各要求を `via`／本体で witness します（暗黙の準拠は起きません）。トレイトは[型引数](#トレイト名の-型引数と関連型束縛)（多重 conformance）と[関連型](#関連型associated-type)（出力）を持てます。

トレイトの宣言は型システムの[カスタム型](02-types.md)の一種で、`export trait Shape { … }` のように書きます。本章では定義・関連型・継承・準拠の意味論と、標準で提供されるトレイトのカタログをまとめます。

## トレイトの定義（要求と提供メソッド）

トレイトは型が満たすべき**要求**と、要求の上に組まれた**提供メソッド**を持てます。両者は**本体の有無**で区別します。

- **要求**（本体なし）: 各型が準拠時に `via`／本体で必ず witness する（後述「トレイト準拠と via」）。フィールド要求・メソッド要求・関連値要求がある。
- **提供メソッド**（本体あり）: トレイト側で一度だけ定義し、要求や他の提供メソッドの上に組む。全準拠型で共有され、**型ごとに上書きできない**。

```plew
trait Stepper {
    fn step() -> I32                 // 要求：本体なし。各型が実装する
    fn double_step() -> I32 {        // 提供メソッド：本体あり。step() の上に組む
        return self.step() + self.step()
    }
}
```

`step()` を実装した型は `double_step()` を自動で得ます（`it.step()` も `it.double_step()` も呼べる）。`.map().filter()` のようなメソッドチェーンはこの提供メソッドで成り立ちます。

- 提供メソッドは型の**オーバーロード集合**に加わる。同じセレクタ・同じ具体シグネチャの既存メンバや別トレイトの提供メソッドと衝突すればコンパイルエラー（引数型が違えばオーバーロードとして共存。同一シグネチャの別挙動が要るなら `#Ext`、[拡張](10-extensions.md)）。
- 準拠側の `impl Type as Trait` が witness するのは**要求だけ**。提供メソッドに別の本体を与えること（上書き）はできない。挙動を変えたい型は名前付き `extension` + `#Ext` で別メソッドにする。
- **上書き可能な既定は持たない**: トレイト作者は本体の有無で「抽象な要求（各型が埋める）」か「固定の提供メソッド（全型共有）」かを明示的に選ぶ。中間の「既定だが上書き可」は無い（Swift の protocol extension に伴う静的／動的ディスパッチの食い違いを避けるため）。

### 関連型（associated type）

トレイトは**関連型**を要求できます。`type Name` で宣言し、シグネチャ中ではベア名で参照します。準拠側の impl が具体型に束ねます（`type Name = ConcreteType`）。

```plew
trait Iterator {
    type Item                       // 関連型の要求
    fn next() -> Optional[Item]     // シグネチャ中はベアで参照
}

impl Counter as Iterator {
    type Item = I32                 // impl が具体型に束ねる
    fn next() -> Optional[I32] { /* ... */ }
}
```

- **型引数（多重 conformance）と関連型（出力）の使い分け**: 入力＝呼ぶ側が選び 1 型に複数 conformance あり得るものは**型引数**にする（`Add[Rhs]`：`Vec` は `Add[Vec]` と `Add[F64]` の両方に準拠できる）。出力＝impl が一意に決めるものは**関連型**（`type Output`・`Iterator.Item`）。1 つのトレイトが両方を持ってよい（`Add[Rhs] { type Output }`）。複数 conformance のメソッドは引数型で区別される**オーバーロード**になる（→ [メソッドのオーバーロード](04-functions.md)、[型変換と演算子](07-operators.md)）。
- 関連型は**型の名前空間**に属し、メソッド・フィールドのオーバーロード集合とは別。関連型名がメソッド名と衝突することはない。`type Name = …` の充足に `via` は使わない（直接束ねる）。
- **制約を付けられる**: `type Item: Display` のように要求側で制約を課せる。impl はその制約を満たす型で束ねる。ベア `type Item` は制約なし。
- **外部からの射影は `T.Item`**: 型変数経由で関連型を名指すときは `.` で射影する（値のメンバアクセスと同じ区切り）。

```plew
fn first[T](it: T) -> Optional[T.Item] where T: Iterator {   // T.Item で射影
    return it.next()
}
```

#### トレイト名の `[...]`（型引数と関連型束縛）

トレイト名のあとの `[...]` には、**位置型引数**（`Add[Vec]`）と**関連型束縛**（`Iterator[Item = Foo]`）を書けます（Rust の `Trait<Arg, Assoc = T>` と同形で、記号だけ `[]`）。両者は混在可。supertrait や `where` 句のトレイト制約で使えます。

```plew
fn sum[T](it: T) -> I32 where T: Iterator[Item = I32] { /* ... */ }   // 関連型を束縛
fn g[T](x: T) where T: Add[Vec] { /* ... */ }                          // 位置型引数で右オペランドを指定
```

### トレイトの継承（supertrait）

`trait Sub: Super` は、`Sub` への準拠に `Super` への準拠を要求します（`where T: Trait` と同じく `:` は制約）。複数指定は `trait Sub: A, B`。関連型の束縛も同じ記法で書けます（`trait FooIterator: Iterator[Item = Foo] {}`）。

```plew
trait BoundedStepper: Stepper {
    fn limit() -> I32                    // 要求
    fn capped_step() -> I32 {            // 提供メソッド：親 Stepper の step() を使える
        val s = self.step()
        if s > self.limit() { return self.limit() }
        return s
    }
}
```

- **継承は制約であって自動実装ではない**: `impl Type as BoundedStepper` を書くには、別途 `impl Type as Stepper` も存在しなければならない（無ければエラー）。親準拠が暗黙に生成されることはない（暗黙準拠を持たない方針の一貫）。
- `Sub` の提供メソッドは `self` 経由で `Super` の要求・提供メソッドを呼べる（継承で準拠が保証されるため）。
- ダイヤモンド継承で同名の**要求**が複数経路から来ても、同セレクタ・同シグネチャならオーバーロード集合の 1 つへ畳まれる（シグネチャ不一致はオーバーロードとして共存、または衝突ならエラー）。同一シグネチャの**提供メソッド**が別トレイトから来て衝突する場合はエラー → `#Ext` で解決。

## トレイト準拠と via

型のメソッド・フィールドはセレクタ（名前＋ラベル）ごとの**オーバーロード集合**を成します（→ [メソッドのオーバーロード](04-functions.md)）。同一シグネチャで別物を作ることはできません。トレイトへの準拠は `impl Type as Trait` で**明示的に宣言**し、その中で各要求を **`via` で実体メンバに束ねる**か、メソッドならその場で本体を定義します。**準拠は暗黙には成立しません** — 名前が一致するだけのメソッドが勝手に witness になる「うっかり準拠」は起きません。

```plew
trait Drawable {
    val width: I32         // フィールド要求
    fn draw() -> String    // メソッド要求
}

struct Sprite {
    val w: I32
}

impl Sprite {
    fn render() -> String { return "..." }  // 実体メソッド
}

impl Sprite as Drawable {
    val width: I32 via w               // 要求 width（型つき）を実体 w に束ねる
    fn draw() -> String via render     // 要求 draw（完全シグネチャ）を実体 render に束ねる
}
```

`via` の左辺は**常に要求の完全なシグネチャ**（メソッドは引数ラベル・型・戻り型、フィールドは型）を書きます。本体定義形（`fn draw() -> String { … }`）と対称で、トレイトを見なくても各行が何を満たすか分かり、同名要求が複数あっても一意に特定できます。

実体に対応するメソッドが無い要求は、impl 内でそのまま本体を定義します（新しい実体メソッドになります）。

```plew
impl Sprite as Drawable {
    val width: I32 via w
    fn draw() -> String { return "drawn" }  // 実体が無いのでここで定義（via 形と対称）
}
```

同名の要求が複数ある（要求がオーバーロードされている）トレイトも、左辺のシグネチャで一意に witness できます。

```plew
trait Writer {
    fn write(data: Bytes) -> Result[I32, Error]    // 同名・別シグネチャの要求
    fn write(data: String) -> Result[I32, Error]
}

impl File as Writer {
    fn write(data: Bytes) -> Result[I32, Error] via write_bytes
    fn write(data: String) -> Result[I32, Error] via write_text
}
```

### ルール

- **全要求を明示的に束ねる**: フィールド・メソッドを問わず、各要求は `via` で実体メンバを指すか、メソッドなら impl 内で本体を定義する。**`via` 左辺は常に完全なシグネチャ**（名前一致でも `val width: I32 via width` のように書き、省略しない）。空の `impl Type as Trait {}` は準拠失敗。
- **define-once**: 実体メソッドの**本体定義は一箇所のみ**（inherent な `impl Type {}` か、いずれか 1 つの trait impl）。他からは `via` で参照する。フィールドはストレージなので struct 宣言で定義し、trait impl からは `via` で束ねるだけ（trait impl はフィールドを新設しない）。
- **別名はベアでも呼べる**: `fn draw() -> String via render` のように要求名と実体名が違う場合、要求名（`draw`）も**ベアの呼び名として加わる**。`sprite.draw()` も `sprite.render()` も同じメソッドを指す（トレイト経由で呼べてベアで呼べないのは不自然、という方針）。別名が同セレクタ・同シグネチャの既存メンバと衝突すればコンパイルエラー（引数が違えばオーバーロードとして共存）。
- **シグネチャ一致**: `via` 先のシグネチャは要求と一致しなければならない。合わなければエラー（改名するか、`#Ext` 拡張に分離）。
- **1 メンバで複数トレイトを witness 可**: 同じ実体メソッドを複数の trait impl から `via` で束ねてよい。シグネチャが噛み合う限り、1 つの `Foo.bar` が複数トレイトの要求を同時に満たせる。
- **同名・同シグネチャで別挙動が必要なら拡張**: 引数型が違えばオーバーロードとして同居できるが、**同じシグネチャ**で別実装は作れない。本当に必要なら名前付き `extension` に置き、呼び出し位置の `#Ext` で明示する（[拡張](10-extensions.md)）。

## 標準トレイト

言語・コアライブラリが提供する主要トレイトの一覧です。演算子・変換まわりの詳細な意味論は [型変換と演算子](07-operators.md) を参照。

### 基本トレイト

- `Clone`: オブジェクトの複製
- `Hash`: ハッシュ値計算
- `Display`: 表示用フォーマット
- `Format`: 変数展開用フォーマット

> トレイトは**型引数を持てます**が、その有無は「両辺が別型になり得るか」で決まります（下記）。impl が一意に決める出力は関連型 `type Output`。複数 conformance のメソッドは引数型で区別される[オーバーロード](04-functions.md)になります。

### 変換トレイト

- `From[Source]`: 型変換。`x as T` は `T.from(x: x)` の糖衣で、`try` のエラー変換にも使う。1 つの型が複数ソースに準拠可（`From[I32]`・`From[String]` …）。例外として newtype と元型の `as` は From でなくゼロコスト再タグ（→ [型変換と演算子](07-operators.md)）。

### 演算子トレイト

演算子は対応トレイトのメソッドの糖衣です（`!` も含む）。**ただし論理結合子 `&&` / `||` は短絡する制御フローで、トレイトではありません**（`if` の糖衣 → [型変換と演算子](07-operators.md)）。型引数の有無は **両辺が別型になり得るか**で決まります：

- **算術（別型を結ぶ）— `[Rhs]` あり**：`Add[Rhs]`, `Sub[Rhs]`, `Mul[Rhs]`, `Div[Rhs]`。右オペランド型で複数 conformance 可（`Vector as Mul[Vector]` と `Mul[F64]`）。結果型は関連型 `type Output`。
- **等価・順序（同一型上の関係）— 型引数なし**：`Eq { fn eq(rhs: Self) -> Bool }`（`==`/`!=`。`!=` は `!(==)`。`@[Eq]` で derive）、`Ord: Eq { fn compare(rhs: Self) -> Ordering }`（`< <= > >=` は `compare` に展開）。右辺は常に `Self`（異種比較は対称・反射律を壊すので持たない）。`F32`/`F64` も準拠するが NaN 比較で panic。
- **単項 — `Not`**：論理否定 `!`（eager）。`type Output`。
- **添字 — `Index[Key]`**：`collection[key]`。`type Output`。

### オプショナル関連トレイト

- `Chain`: オプショナルチェーン（`receiver?.member`）。値か空かに分解する `chain()` と、再構築用の `from_value` / `empty` を持つ
- `Coalesce[Rhs]`: nil 合体演算子（`??`）。左辺が空のとき右辺へフォールバックする。`type Output`
