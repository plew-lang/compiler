# 関数とインスタンス生成

## 関数宣言

```plew
export async fn function_name[T, U](
    arg1: Type1,
    inout arg2: Type2,
    arg3: Type3 = default_value
) -> ReturnType where T: Trait1, U: Trait2 {
    // 関数本体
}
```

## 引数ラベル

全ての関数呼び出しは、各引数に**ラベル（= 引数名）が必須**です。関数・メソッド・関連関数だけでなく、**クロージャの呼び出しも同様**です。ラベルはパラメータ名と一致し、宣言順に並べます。

```plew
fn greet(name: String, greeting: String) -> String {
    return "{greeting}, {name}"
}

greet(name: "Alice", greeting: "Hello")  // ラベル必須・宣言順
```

引数を持たない呼び出しにはラベルはありません（`make_counter()` など）。クロージャ呼び出しでもラベルが必要なため、**関数型はラベルを保持します**（Swift と異なり、型からラベルは落ちません）。

## 無名関数（クロージャ）

名前を持たない関数リテラルを `fn` で記述します。第一級の値として、変数への代入・引数渡し・戻り値にできます。キャプチャや escape の意味論は **Swift のクロージャと同じ**です。

```plew
// fn(引数) -> 戻り値型 { 本体 }
val add = fn(a: I32, b: I32) -> I32 {
    return a + b
}
val sum = add(a: 1, b: 2)  // 3
```

関数型は `fn(ラベル: 引数型, ...) -> 戻り値型` で表します（ラベルを含みます）。

```plew
fn apply(f: fn(n: I32) -> I32, x: I32) -> I32 {
    return f(n: x)
}

val doubled = apply(f: fn(n: I32) -> I32 { return n * 2 }, x: 21)  // 42
```

### 型推論

関数型が文脈から判明している場合、引数・戻り値の型注釈を省略できます（Swift と同様）。

```plew
val f: fn(n: I32) -> I32 = fn(n) { return n * 2 }  // n: I32 は推論される
```

### 環境のキャプチャ

クロージャは外側のスコープの変数をキャプチャします。Plew は参照の値渡し + GC なので、キャプチャした参照は自動的に生存し続けます。

```plew
fn make_counter() -> fn() -> I32 {
    mut val count: I32 = 0
    return fn() -> I32 {
        count += 1
        return count
    }
}

val counter = make_counter()
counter()  // 1
counter()  // 2
```

- キャプチャした変数の可変性は、その変数自身の宣言（`val` / `mut val`）に従います。
- **`[weak self]` / `[unowned self]` のようなキャプチャリストや `@escaping` 注釈は存在しません。** GC が循環参照も回収するため、クロージャは常に自由に escape できます。
- ただし `spawn` ブロックのキャプチャは全て immutable に制限されます（[非同期処理とメモリ管理](06-concurrency.md) 参照）。

## メソッドと impl

```plew
impl MyType {
    // インスタンスメソッド
    pub async fn instance_method(arg: Type) -> ReturnType {
        // メソッド本体
    }
    
    // 可変メソッド
    pub async mut fn mutable_method(arg: Type) -> ReturnType {
        // 可変メソッド本体
    }

    // 関連関数（静的メソッド相当）
    pub assoc fn associated_function() -> ReturnType {
        // 関連関数本体
    }

    // 関連変数（静的変数相当）
    assoc val associated_value: Type = default_value
}
```

### メソッドのオーバーロード

同じ名前のメソッドを、引数で区別して複数定義できます（オーバーロード）。解決は**ラベルと引数の具体型**だけで行い、トレイト探索や import に依存しません。

**セレクタ** = メソッド名 ＋ 順序付きラベル集合。Plew は呼び出しにラベルを強制するので、**ラベル集合が違えば別メソッド**（型を見ずに区別）。

同一セレクタ内に複数の定義を置く条件：

- **型引数の形が一致**：型引数の個数と、それを使う引数位置が全オーバーロードで同じ。違反は、たとえ他で解決できても一律エラー。
- **具体位置でのみ区別**：全員で具体型な引数位置のうち、最低 1 つで型が異なる。
- **境界は区別に使わない**：`where T: TraitA` の違いだけでオーバーロードを分けられない（区別は具体型のみ。境界は選ばれたオーバーロードの型引数への制約として効く）。

```plew
impl A {
    fn f[T](a: I16, b: T) {}
    fn f[T: TraitA](a: I32, b: T) {}   // 具体位置 a で区別、b は全員 T
    fn f[T: TraitB](a: I64, b: T) {}
    fn f[T, U](b: T, c: U) {}          // ラベルが (b, c) → 別セレクタ＝別メソッド
}

// 禁止：同セレクタ f(n:) で n が generic vs 具体
// fn f[T](n: T) {}
// fn f(n: I32) {}
```

- すべてのオーバーロードはその型のモジュール内（無名 impl）に集まるので、**衝突検出はモジュール単体のビルドで完結**する（Rust のようなグローバルコヒーレンスは不要）。拡張（`#Ext`）のメソッドはベア解決に参加しないので別扱い。
- 解決：ラベルでセレクタを確定 → 具体位置の型で 1 つ選ぶ → 型引数位置は推論＋境界チェック。重なり得るジェネリック impl は保守的に拒否し、specialization（最特化選択）は行わない。
- リテラル引数は文脈（このオーバーロード集合）で型が一意に定まらなければエラー（→ [数値リテラル](02-types.md)）。

## メンバの可視性

フィールド・メソッドの可視性は**型のカプセル化だけ**を制御し、モジュール/パッケージ境界とは独立です（境界は [モジュール](10-modules.md) の `export` / 再エクスポートが担当）。段階は **2 つだけ**で、`pub(crate)` のような中間段は持ちません。

- **`pub`** — その型を参照できるコードからメンバが見える。
- **`pub(get)`** — 読み取りは `pub`、書き込みは型の内部のみ（外部からは不変）。
- **修飾なし（非公開）** — **その型の無名 impl の中からのみ**見える。同一モジュールの非 impl コード・他の型・名前付き拡張（`#Ext`、自型・他型を問わず）・外部パッケージ、いずれからも見えない。

```plew
struct Account {
    pub val id: I32             // どこからでも見える
    pub(get) val balance: I32   // 読み取り公開・書き込みは内部のみ
    val secret_key: String      // 無名 impl の中だけ
}

impl Account {                  // 無名 impl → secret_key が見える
    pub mut fn rotate_key() { self.secret_key = generate() }
}

extension Audit {
    impl Account {              // 拡張 → pub / pub(get) のみ
        fn report() -> I32 { return self.balance }  // OK
        // fn leak() -> String { return self.secret_key }  // エラー: 非公開
    }
}
```

非公開メンバを見られるのが**無名 impl だけ**なので、外部型を拡張しても作者が隠した内部には触れられず、`pub` のカプセル化が型レベルで保たれます。兄弟モジュールがメンバを使いたい場合は `pub` にする（＝外部にも見える）か、密結合なコードを型のモジュールに `part` で同居させて無名 impl から触れます。

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

- 提供メソッドは型の**オーバーロード集合**に加わる。同じセレクタ・同じ具体シグネチャの既存メンバや別トレイトの提供メソッドと衝突すればコンパイルエラー（引数型が違えばオーバーロードとして共存。同一シグネチャの別挙動が要るなら `#Ext`、[拡張](09-extensions.md)）。
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

- **型引数（多重 conformance）と関連型（出力）の使い分け**: 入力＝呼ぶ側が選び 1 型に複数 conformance あり得るものは**型引数**にする（`Add[Rhs]`：`Vec` は `Add[Vec]` と `Add[F64]` の両方に準拠できる）。出力＝impl が一意に決めるものは**関連型**（`type Output`・`Iterator.Item`）。1 つのトレイトが両方を持ってよい（`Add[Rhs] { type Output }`）。複数 conformance のメソッドは引数型で区別される**オーバーロード**になる（→ 「メソッドのオーバーロード」、[型変換と演算子](08-operators.md)）。
- 関連型は**型の名前空間**に属し、メソッド・フィールドのオーバーロード集合とは別。関連型名がメソッド名と衝突することはない。`type Name = …` の充足に `via` は使わない（直接束ねる）。
- **境界を付けられる**: `type Item: Display` のように要求側で境界を課せる。impl はその境界を満たす型で束ねる。ベア `type Item` は境界なし。
- **外部からの射影は `T.Item`**: 型変数経由で関連型を名指すときは `.` で射影する（値のメンバアクセスと同じ区切り）。

```plew
fn first[T: Iterator](it: T) -> Optional[T.Item] {   // T.Item で射影
    return it.next()
}
```

#### トレイト名の `[...]`（型引数と関連型束縛）

トレイト名のあとの `[...]` には、**位置型引数**（`Add[Vec]`）と**関連型束縛**（`Iterator[Item = Foo]`）を書けます（Rust の `Trait<Arg, Assoc = T>` と同形で、記号だけ `[]`）。両者は混在可。supertrait・`where`・引数境界のどこでも使えます。

```plew
fn sum[T: Iterator[Item = I32]](it: T) -> I32 { /* ... */ }   // 関連型を束縛
fn g[T: Add[Vec]](x: T) { /* ... */ }                          // 位置型引数で右オペランドを指定
```

### トレイトの継承（supertrait）

`trait Sub: Super` は、`Sub` への準拠に `Super` への準拠を要求します（`where T: Trait` と同じく `:` は境界）。複数指定は `trait Sub: A, B`。関連型の束縛も同じ記法で書けます（`trait FooIterator: Iterator[Item = Foo] {}`）。

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

型のメソッド・フィールドはセレクタ（名前＋ラベル）ごとの**オーバーロード集合**を成します（→ 「メソッドのオーバーロード」）。同一シグネチャで別物を作ることはできません。トレイトへの準拠は `impl Type as Trait` で**明示的に宣言**し、その中で各要求を **`via` で実体メンバに束ねる**か、メソッドならその場で本体を定義します。**準拠は暗黙には成立しません** — 名前が一致するだけのメソッドが勝手に witness になる「うっかり準拠」は起きません。

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

## インスタンス生成

全ての構造体および列挙型バリアントは**JSX ライクな構文でのみ**インスタンス化できます。位置引数による生成（`Color.Red(5)` のような形）はありません。

```plew
struct Person {
    val name: String
    val age: I32
}

// フィールド指定による生成
val person = <Person name="Alice" age=30 />

// 子要素を持つ構造体（UIコンポーネントなど）
struct Container {
    val title: String
    val children: Array[Widget]
}

val container = <Container title="Main">
    <Button text="OK" />
    <Label text="Hello World" />
</Container>
```

`@[DefaultFactory(pub)]` ディレクティブで、フィールドをそのまま受け取る既定の factory の公開範囲を制御できます。

### factory

カスタムの生成ロジックは `impl` 内に `factory` で定義します。古典的なコンストラクタと違い `self` を初期化するのではなく、**完成したインスタンスを `return` で返します**（＝ファクトリ）。`return` は必須で、キャッシュ済みの値など `<Type … />` 以外を返してもかまいません。

- 無名 `factory(...)` → `<Type … />` で呼び出す。ラベル集合が異なれば複数定義（オーバーロード）できる。
- 名前付き `factory name(...)` → `<Type.name … />` で呼び出す（列挙型バリアント生成と同じ形）。名前は snake_case。
- 属性ラベルは factory の引数ラベル（必ずしもフィールド名と一致しなくてよい）。呼び出し時はラベル必須。

引数なしや同一ラベル集合の生成は無名では1つしか作れないため、それらは**名前付き factory** にします。これにより `assoc fn` を生成用に流用せずに済み、生成が常に JSX で明示されます。

```plew
struct Celsius {
    val degree: F64
}

impl Celsius {
    // 名前付き factory → <Celsius.from_fahrenheit … />
    factory from_fahrenheit(fahrenheit: F64) {
        return <Celsius degree=((fahrenheit - 32.0) / 1.8) />
    }

    // 引数なしでも名前を付ければ何個でも定義できる
    factory zero() {
        return <Celsius degree=0.0 />
    }
}

val a = <Celsius degree=20.0 />                      // フィールド指定
val b = <Celsius.from_fahrenheit fahrenheit=68.0 />  // 名前付き factory
val z = <Celsius.zero />                             // 引数なし factory
```

factory の戻り型は常に暗黙の `Self` です。本体での `<Type field=… />`（全フィールド指定）はフィールド初期化（＝ `Self` の生成）を指し、自分自身を再帰呼び出ししません。この `Self` 規約により、[`newtype`](02-types.md) は元の型の factory をそのまま継承して JSX 構文で生成できます。

### 列挙型バリアントの生成

列挙型のバリアントも同じ構文で生成します。`Enum.Variant` を型として指定し、フィールドを持たないバリアントは要素なしで生成します。

```plew
val some = <Optional.Some value=42 />
val none = <Optional.None />
val ok   = <Result.Ok value=data />
val err  = <Result.Err error=parse_error />
```

enum にも snake_case の名前付き factory を定義できます（PascalCase のバリアント名と衝突しません）。
