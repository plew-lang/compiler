# トレイト

トレイトは、型が満たすべき**要求**（メソッド・フィールド・関連値・関連型）を束ねる抽象です。トレイト本体には要求だけを書きます。要求の上に組む**派生メソッド**（`Iterator` の `map`/`filter` を `next` の上に作る類）は、トレイト本体ではなく**名前付き拡張**の `impl Trait` ブロックに置き、各型が `default_extension` で自分のベア表面に取り込みます（→ [拡張](09-extensions.md)）。型への準拠は `impl Type as Trait` で**明示的に宣言**し、各要求を `via`／本体で witness します（暗黙の準拠は起きません）。トレイトは[型引数](#トレイト名の-型引数と関連型束縛)（多重 conformance）と[関連型](#関連型associated-type)（出力）を持てます。

トレイトの宣言は型システムの[カスタム型](05-structs-enums.md)の一種で、`export trait Shape { … }` のように書きます。本章では定義・関連型・継承・準拠の意味論と、標準で提供されるトレイトのカタログをまとめます。

## トレイトの定義（要求）

トレイト本体には型が満たすべき**要求**だけを書きます（すべて本体なし）。フィールド要求・メソッド要求・関連値要求・関連型があり、各型は準拠時に `via`／本体で必ず witness します（後述「トレイト準拠と via」）。

要求の上に組む**派生メソッド**（要求だけを使って組み立てる共有メソッド。`Iterator` の `map`/`filter` を `next` の上に作る類）は、トレイト本体にもベアの `impl Trait` にも書きません。**名前付き拡張**の中に `impl Trait { … }` として置き、各型が `default_extension` で自分のベア表面に取り込みます（→ [拡張](09-extensions.md) の「拡張はトレイトも対象にできる」「デフォルト拡張」）。こうすることで「どの派生メソッドがこの型でベアに見えるか」を**型の作者が明示的に管理**でき、別トレイト由来の同名メソッドが暗黙に流れ込んで衝突する事故が起きません。

```plew
trait Stepper {
    fn step() -> I32                 // 要求：本体なし。各型が実装する
}

extension StepperExt {               // 派生メソッドは名前付き拡張に置く
    impl Stepper {
        fn double_step() -> I32 {    // self: Self: Stepper。要求 step() の上に組む
            return self.step() + self.step()
        }
    }
}

struct Counter {
    mut val n: I32
    default_extension #StepperExt    // Counter のベア表面に double_step を載せる
}
impl Counter as Stepper {
    fn step() -> I32 { return self.n }
}
// counter.step() も counter.double_step() も呼べる。`.map().filter()` チェーンも同じ仕組み
```

- **`impl Trait`（拡張内）の `self` は準拠型**（`Self: Trait`）。派生メソッドは `self` 経由で要求や同じ拡張内の他メソッドを呼べる。本体はトレイトのインターフェースに対して一度だけ型検査される。`impl Trait` を書けるのは拡張の中だけ（ベアの `impl Trait` は書けない）で、拡張なので外部トレイトも対象にできる。
- 派生メソッドは**自動では生えない**（拡張は opt-in）。各型が `default_extension #Ext` で取り込むか、使用箇所で `value#Ext.foo()` と明示する。ジェネリックコードでは境界 `T: Trait` は要求しか運ばないので、`value#Ext` を明示する（引数型を `x: T#Ext` にすれば本体はベアで書ける。`where T: Trait` は別途必要 → [拡張](09-extensions.md)）。
- 衝突は**型の `default_extension` 宣言地点**で検出する。デフォルトに載せた拡張のメソッドが、その型自身のメソッドや別のデフォルト拡張と同セレクタ・同シグネチャになればコンパイルエラー（引数型が違えばオーバーロードとして共存）。型の作者がデフォルト集合を curate して解決する。同一シグネチャの別挙動が要るならデフォルトに入れず `#Ext` で明示する。
- **上書き可能な既定は持たない**: 準拠側の `impl Type as Trait`（`as` あり）が witness するのは**要求だけ**。派生メソッドに別の本体を与えること（上書き）はできない。挙動を変えたい型は別の名前付き `extension` に分けて `#Ext` で選ぶ。中間の「既定だが上書き可」は無い（Swift の protocol extension に伴う静的／動的ディスパッチの食い違いを避けるため）。

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

- **型引数（多重 conformance）と関連型（出力）の使い分け**: 入力＝呼ぶ側が選び 1 型に複数 conformance あり得るものは**型引数**にする（`Add[Rhs]`：`Vec` は `Add[Vec]` と `Add[F64]` の両方に準拠できる）。出力＝impl が一意に決めるものは**関連型**（`type Output`・`Iterator.Item`）。1 つのトレイトが両方を持ってよい（`Add[Rhs] { type Output }`）。複数 conformance のメソッドは引数型で区別される**オーバーロード**になる（→ [メソッドのオーバーロード](07-methods-impl.md)、[型変換と演算子](../03-expressions/12-operators.md)）。
- 関連型は**型の名前空間**に属し、メソッド・フィールドのオーバーロード集合とは別。関連型名がメソッド名と衝突することはない。`type Name = …` の充足に `via` は使わない（直接束ねる）。
- **制約を付けられる**: `type Item: Format` のように要求側で制約を課せる。impl はその制約を満たす型で束ねる。ベア `type Item` は制約なし。
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

`trait Sub: Super` は、`Sub` への準拠に `Super` への準拠を要求します（`where T: Trait` と同じく `:` は制約）。複数指定は **`+`** で連結します（`trait Sub: A + B`）。`where T: A + B` と同じく、`+` は**同一の主語（ここでは `Self`）に制約を重ねる**意味で、別々の主語を並べる `,` とは役割が違います。関連型の束縛も同じ記法で書けます（`trait FooIterator: Iterator[Item = Foo] + Clone {}`）。

```plew
trait BoundedStepper: Stepper {
    fn limit() -> I32                    // 要求
}

extension BoundedExt {
    impl BoundedStepper {
        fn capped_step() -> I32 {        // 派生メソッド：親 Stepper の step() を使える
            val s = self.step()
            if s > self.limit() { return self.limit() }
            return s
        }
    }
}
```

- **継承は制約であって自動実装ではない**: `impl Type as BoundedStepper` を書くには、別途 `impl Type as Stepper` も存在しなければならない（無ければエラー）。親準拠が暗黙に生成されることはない（暗黙準拠を持たない方針の一貫）。
- `Sub` を対象にする拡張の派生メソッドは、`self` 経由で `Super` の要求を呼べる（継承で準拠が保証されるため）。
- ダイヤモンド継承で同名の**要求**が複数経路から来ても、同セレクタ・同シグネチャならオーバーロード集合の 1 つへ畳まれる（シグネチャ不一致はオーバーロードとして共存、または衝突ならエラー）。**派生メソッド**はトレイトに自動付随せず**型が `default_extension` で取り込む**ものなので、別経路由来の同名・同シグネチャ派生メソッドが衝突するのは「型が両方をデフォルトに含めたとき」だけで、**その型の `default_extension` 宣言地点**で報告される（→ [拡張](09-extensions.md)）。トレイト定義そのものが衝突を強制することはない。

## トレイト準拠と via

型のメソッド・フィールドはセレクタ（名前＋ラベル）ごとの**オーバーロード集合**を成します（→ [メソッドのオーバーロード](07-methods-impl.md)）。同一シグネチャで別物を作ることはできません。トレイトへの準拠は `impl Type as Trait` で**明示的に宣言**し、その中で各要求を **`via` で実体メンバに束ねる**か、メソッドならその場で本体を定義します。**準拠は暗黙には成立しません** — 名前が一致するだけのメソッドが勝手に witness になる「うっかり準拠」は起きません。

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
- **同名・同シグネチャで別挙動が必要なら拡張**: 引数型が違えばオーバーロードとして同居できるが、**同じシグネチャ**で別実装は作れない。本当に必要なら名前付き `extension` に置き、呼び出し位置の `#Ext` で明示する（[拡張](09-extensions.md)）。

## 標準トレイト

言語・コアライブラリが提供する主要トレイトです。**演算子・変換・Optional 系トレイトの意味論（シグネチャ・脱糖・型引数の有無・NaN の扱い）の正典は [型変換と演算子](../03-expressions/12-operators.md)** にあり、ここでは所在の一覧だけを示します。型引数を持つか関連型にするかの判断基準は[上記の使い分け](#関連型associated-type)（入力＝型引数で多重 conformance／出力＝関連型）に従います。

### 基本トレイト

演算子に対応しない純粋なトレイトで、本章が正典です。

- `Clone`: オブジェクトの複製
- `Hash`: ハッシュ値計算
- `Format`: 表示・変数展開用フォーマット（→ [文字列](../01-basics/02-basic-types.md)）

### 演算子・変換・Optional 系トレイト

各演算子は対応トレイトのメソッドの糖衣です。詳細な意味論は [型変換と演算子](../03-expressions/12-operators.md) 章を参照（一覧のみ）。

| 種別 | トレイト | 演算子・用途 |
| --- | --- | --- |
| 変換 | `From[Source]` | `x as T`（`try` のエラー変換も。newtype⇔元型の `as` だけは From でなくゼロコスト再タグ） |
| 算術 | `Add[Rhs]` / `Sub[Rhs]` / `Mul[Rhs]` / `Div[Rhs]` | `+ - * /`・結果型は `type Output` |
| 等価 | `Eq`（型引数なし・右辺 `Self`） | `== !=` |
| 順序 | `Ord: Eq`（型引数なし） | `< <= > >=` |
| 単項 | `Not` | 前置 `!`（eager） |
| 添字 | `Index[Key]` | `collection[key]` |
| Optional チェーン | `Chain` | `?.` |
| nil 合体 | `Coalesce[Rhs]` | `??` |

> **`&&` / `||` はトレイトではありません** — Bool 限定・オーバーロード不可の、短絡する制御フロー（`if` の糖衣）です（→ [論理結合子](../03-expressions/12-operators.md)）。
