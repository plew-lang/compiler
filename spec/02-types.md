# 型システム

## プリミティブ型

- **整数リテラル**: `123`
- **浮動小数点リテラル**: `3.14`
- **真偽値**: `true`, `false`
- **文字列**: `"hello world"` （変数展開対応）

### 数値リテラル

記法は基本的に Rust と同様ですが、**型サフィックスは型名そのもの（PascalCase）**である点だけ異なります。

- **基数**: 10 進 `123`、16 進 `0xFF`、8 進 `0o17`、2 進 `0b1010`。
- **桁区切り**: 任意位置に `_` を挿入できます（`1_000_000`、`0xFF_FF`）。
- **指数（e 表記）**: `1.5e10`、`2e-9`、`1E3`。
- **型サフィックス**: 末尾に型名を付けて型を固定します。型名は PascalCase なので `10U32` / `255I64` / `3.14F64`（Rust の `10u32` 相当）。

```plew
val b: U32 = 0xFF_FF   // 注釈で確定（16 進 + 桁区切り）
val d = 0o17I32        // サフィックスで確定（8 進）
val f = 3.14F64        // サフィックスで確定
```

#### リテラルの型付け（多相・文脈で確定）

数値リテラルは**特定の型を持たず、組み込み数値型に対して多相**です（整数リテラルは `I8`…`I64`・`U8`…`U64`、小数リテラルは `F32`・`F64`）。実際の型は**文脈（代入先の注釈・引数型・戻り型・演算子の被演算子型）から一意に決まったもの**になります。

```plew
val x: U32 = 42        // 注釈 → U32
f(n: 42)               // f(n: U32) が 1 つだけ → U32
val y = count + 1      // 1 は count の型（Add の右オペランド）
```

**一意に定まらなければコンパイルエラー**で、明示を要求します。Rust の `i32` のような既定型は持ちません。

```plew
val z = 42             // エラー：文脈が無い → val z: I32 = 42 か val z = 42I32
// f(n: I32) と f(n: I64) の両方がある状況で f(n: 42) → エラー（曖昧）
```

`42.0` も同様に `F32`/`F64` に多相で文脈で確定します。ユーザー定義型はこの多相の対象外（明示構築が必要）。

#### 浮動小数の実行時セマンティクス（NaN / inf）

`F32`/`F64` の算術は IEEE-754 に従い、`0.0 / 0.0` や `sqrt(-1.0)`・`inf - inf` などは **NaN**（非数）を、`1.0 / 0.0` などは **inf**（無限大）を生成します。inf は全順序を壊さない（全要素より大／小、`inf == inf` は真）ので通常の値として扱えます。

NaN だけは別扱いで、Plew は **NaN を比較した時点で panic** します（`== != < <= > >=`、および `Eq`/`Ord` 由来の処理）。「`NaN != NaN` が真」のような静かな嘘を返さず、バグを比較箇所で大きく落とすためです（→ [型変換と演算子](07-operators.md)）。NaN 判定は `is_nan()` で明示的に行います。これにより `F32`/`F64` は全順序 `Ord`・全等価 `Eq` に正直に準拠できます。

## 文字列（String）

`String` は**不変**な UTF-8 文字列です。一度作った中身は変わらず、加工（連結・変換・部分取り出し等）は新しい `String` を返します。参照の値渡し＋GC のもとで安全に共有でき、`spawn` の immutable キャプチャ（→ [非同期処理](09-concurrency.md)）とも噛み合うため、文字列は不変としています。

### 表現と妥当性

内部表現をそのまま公開し、**常に妥当な UTF-8** を不変条件とします。

```plew
struct String {
    pub(get) val bytes: Array[U8]   // UTF-8 バイト列（常に妥当）
}
```

- `bytes` は `pub(get)`（読み取り公開・書き込みは内部）。`s.bytes` は**ゼロコピーの読み取り**で `count` は O(1)。可変が欲しければ `.clone()`。
- **任意バイトからの公開生成は持たない**（不変条件を破るため）。生成は文字列リテラルと、検証する失敗し得る factory（例 `String.from_bytes(bytes:) -> Result[String, Utf8Error]`、名称暫定）に限る。
- **入力を正規化しない**：来たバイトをそのまま保持する（下記の等価と整合）。

### 等価

`==` は**バイト等価**（`bytes` の要素ごとの一致）。正準等価（"café" の合成形 ≡ 分解形）は暗黙には行わず、必要なら明示的に正規化してから比較します（正規化 API は未決）。→ [等価（Eq）](07-operators.md)。

### 要素の見方（バイト／スカラ／書記素）

「1 文字」を一つに固定せず、**ビューを明示選択**します。型がコストを語ります：

- `bytes`（`Array[U8]`）— ランダムアクセス可・`count` は O(1)。
- `scalars()` — Unicode スカラのイテレータ（`count()` は O(n)）。
- `graphemes()` — 書記素クラスタ（人間が 1 文字と感じる単位。結合文字・絵文字列を割らない）のイテレータ（`count()` は O(n)）。

ランダムアクセスできるのは `bytes` だけで、復号を要する `scalars`/`graphemes` はイテレータ。**String への整数添字 `s[i]` は持たない**（可変長 UTF-8 で O(1) 添字は嘘になる。生バイトは `s.bytes[i]`）。長さ専用メソッド（`*_count()`）も設けません（配列の `count`＝O(1)、イテレータの `count()`＝O(n) で自明だから）。

### 構築（ビルダ）

不変文字列の効率的な構築は伸長可能な**ビルダ**で行い、確定時に不変 `String` に封じます（素朴な逐次連結 `s = s + …` の O(n²) を避ける）。ビルダの型名・API は未決。

### 当面持たないもの（将来 additive）

- **部分文字列（substring）API** — 必要時に**コピーで新しい `String`** を作る形で追加する（retention・エイリアスのない footgun フリー版）。当座の抽出は `scalars()`/`graphemes()` 反復＋ビルダ。
- **ゼロコピーのビュー型 `Slice[U8]` と、それを用いたゼロコピー部分文字列／FFI** — 後から追加する。導入時には `bytes` の型がビュー型へ寄る可能性がある（1.0 前なので許容）。

### 変数展開

文字列内で `{expression}` による変数展開が可能です。Format トレイトを実装している型で利用できます。

```plew
val name = "Alice"
val age: I32 = 30
val message = "Hello, {name}! You are {age} years old."
val formatted = "Pi is approximately {pi:.2}"  // フォーマット指定
```

```plew
trait Format {
    fn format(format: String) -> String
}
```

## 複合型

### 配列

```plew
[1, 2, 3, 4]
[expression1, expression2, ...]
```

`Array[T]` は**動的・伸長可能・連続**なコレクション（`Vec<T>` / `List<T>` 相当）。要素は連続配置され、プリミティブ／値型は**ボックス化せず格納**します（Java `int[]`・C# 配列モデル。`Array[U8]` や WASM ゼロコピーの前提）。

- **唯一の配列型**。長さが型に乗る固定長配列 `[E; N]`（const generics）は持たない＝長さは常に実行時。型レベルの長さ安全が要る局所は名前付きフィールドの struct か実行時不変条件で代替する（需要が固まれば const generics は後付けで非破壊に足せる）。
- **添字 `arr[i]` は `Index[I32] -> T`**（要素の値を返す。→ [型変換と演算子](07-operators.md)）。`count` は O(1)。
- **部分ビュー（スライス）は当面持たない**。部分配列はコピーで作る。ゼロコピーのビュー型（`Slice[T]` / Span 相当）と、それを使った FFI ゼロコピーは、必要になった時点で additive に追加する（FFI 型マッピングは [モジュール](11-modules.md) で未策定）。

### 辞書

```plew
[key1: value1, key2: value2]
[:]  // 空の辞書
```

### タプル

```plew
(value1, value2, value3)
```

タプルは**異種・位置指向**で、アクセスは分解（`(a, b) = t`）やパターンで行います。**整数添字 `t[i]` は持たない**（異種なので戻り型が定まらず、同種限定の `Index` は arity ごとの手書きになるため）。同種・列指向のものは `Array[T]` を使います。

### レンジ（HalfOpenRange / ClosedRange）

`a..<b`（**半開** `[a, b)`・`b` を含まない）と `a..=b`（**閉** `[a, b]`・`b` を含む）でレンジを作ります。**上端は常に `<`／`=` で明示**し、素の `..` は持ちません（「どちらが開区間か」を毎回思い出さずに済むよう。記号は境界条件 `i < b`／`i <= b` に対応）。

```plew
for i in 0..<n { … }   // 0, 1, …, n-1
for i in 0..=n { … }   // 0, 1, …, n
```

- 形ごとに別の **prelude 構造体**（`Array`/`Optional` 同様つねに在る）で、`a..<b` は `<HalfOpenRange start=a end=b />`、`a..=b` は `<ClosedRange start=a end=b />` の**固定シンタックスシュガー**です。レンジは固定 2 フィールド構造体（`{ start, end }`）なので、配列・辞書リテラル（可変アリティで JSX 不可＝本物の例外）と違い、**JSX 構築の例外ではなくその糖衣**（「構築は JSX」原則を破らない）。`..<`/`..=` は固定脱糖でユーザー型には定義できない（非トレイト・上書き不可）。
- **要素型は `Ord`**（`HalfOpenRange[T] where T: Ord` / `ClosedRange[T] where T: Ord`）。順序さえあれば**任意の型でレンジを作れ**（ユーザー定義の順序型でも `v1..<v2`）、`contains` も使えます。
- **反復は `T: Step` のときだけ**：整数系（`I8`…`U64`）は離散ステップの trait `Step`（`Step: Ord`・暫定名）を実装するので `for i in 0..<n` できる。`F64` は `Ord` だが `Step` 非実装なので、`HalfOpenRange[F64]` は `contains` 可・**反復不可**。＝Iterator は `where T: Step` の条件付き準拠。
- 優先度は算術より**緩い**（`0..<n+1` ＝ `0..<(n+1)`）。
- **片側レンジ（`a..` / `..<b` / `..`）と `step` は当面持たない**（片側は主にスライス用途なのでスライスと一緒に、`step` は将来イテレータの `.step_by(k)` で。いずれも additive）。上端の無いレンジは印が不要（印は具体的な上端にだけ付く）。
- イテレータ／反復プロトコル自体の設計と `Step` の正確な定義（successor・距離計算など）、`ClosedRange` 反復時の最大値での停止（イテレータ側の状態で扱い、構造体は素の `{ start, end }`）は別途（未決）。

## カスタム型

### 構造体

```plew
@[DefaultFactory(pub), Eq, Hash, Clone]  // ディレクティブ（オプション）
export struct MyStruct[T] where T: SomeTrait {
    pub val field1: String
    pub(get) val readonly_field: I32  // getter付きpublicフィールド
    mut val field2: T
}
```

`pub` / `pub(get)` / 非公開（修飾なし）のメンバ可視性は [関数とメソッド](04-functions.md) の「メンバの可視性」を参照。非公開メンバは型の無名 impl からのみ見えます。

**構造体ディレクティブ**: 詳細は今後決定予定（[メタプログラミング](12-metaprogramming.md) 参照）

### 列挙型

```plew
@[All, Eq, Hash]  // ディレクティブ（オプション）
export enum Color[T] where T: Display {
    Red { val intensity: F64 }
    Green
    Blue
}
```

**列挙型ディレクティブ**: 詳細は今後決定予定（[メタプログラミング](12-metaprogramming.md) 参照）

### フィールドの統一原則

構造体と列挙型バリアントは、どちらも**名前付きフィールド**のみを持ちます。位置・無名（タプル）フィールドは存在しません（`Some(T)` のような無名ペイロードは書けません）。そのため、宣言・生成・分解の3つで両者は同じ構文に従います。

| | 構造体 | 列挙型バリアント |
| --- | --- | --- |
| 宣言 | `struct S { val field: T }` | `enum E { V { val field: T } }` |
| 生成 | `<S field=expr />` | `<E.V field=expr />` |
| 分解 | `S { field: val binding }` | `E.V { field: val binding }` |

- 生成は JSX ライク構文のみ（下記 [インスタンス生成](#インスタンス生成) 参照）。
- 分解は必ず**型名を先頭に置く**ため、`{` 始まりのブロックと曖昧になりません（[制御構造](06-control-flow.md) 参照）。

### 標準の Optional / Result

オプショナル値とエラーは特別な構文ではなく、通常の列挙型として定義されます。

```plew
@[All, Eq, Clone]
export enum Optional[T] {
    Some { val value: T }
    None
}

@[All, Eq, Clone]
export enum Result[T, E] {
    Ok { val value: T }
    Err { val error: E }
}
```

```plew
val some = <Optional.Some value=42 />
val none = <Optional.None />

match maybe_value {
    Optional.Some { value: val v } => { give v }
    Optional.None                  => { give 0 }
}
```

オプショナルチェーン（`?.`）・nil 合体（`??`）は、それぞれ `Chain` / `Coalesce` トレイトの実装によって有効になります（[型変換と演算子](07-operators.md) 参照）。

### トレイト

```plew
export trait Shape {
    type Output: Display  // 関連型（制約つき）

    val required_field: I32  // フィールド要求

    assoc fn create() -> Self  // 関連関数
    fn draw() -> Output    // インスタンスメソッド
    mut fn rotate(angle: F64)  // 可変メソッド
}
```

トレイトはカスタム型の一種で、上のように要求（フィールド・メソッド・関連型・関連値）と提供メソッドを宣言します。定義・関連型・継承（supertrait）・準拠と `via` の意味論は独立章の [トレイト](05-traits.md) を参照。準拠時は各要求を `via` で実体メンバに明示的に束ね、`Foo.bar` は型ごとに一意で、暗黙の準拠は起きません。

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

カスタムの生成ロジックは `impl` 内に `factory` で定義します（`impl` は [関数とメソッド](04-functions.md)）。古典的なコンストラクタと違い `self` を初期化するのではなく、**完成したインスタンスを `return` で返します**（＝ファクトリ）。`return` は必須で、キャッシュ済みの値など `<Type … />` 以外を返してもかまいません。

- 無名 `factory(...)` → `<Type … />` で呼び出す。ラベル集合が異なれば複数定義（[オーバーロード](04-functions.md)）できる。
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

factory の戻り型は常に暗黙の `Self` です。本体での `<Type field=… />`（全フィールド指定）はフィールド初期化（＝ `Self` の生成）を指し、自分自身を再帰呼び出ししません。この `Self` 規約により、下記の [`newtype`](#newtype名目型) は元の型の factory をそのまま継承して JSX 構文で生成できます。

### 列挙型バリアントの生成

列挙型のバリアントも同じ構文で生成します。`Enum.Variant` を型として指定し、フィールドを持たないバリアントは要素なしで生成します。

```plew
val some = <Optional.Some value=42 />
val none = <Optional.None />
val ok   = <Result.Ok value=data />
val err  = <Result.Err error=parse_error />
```

enum にも snake_case の名前付き factory を定義できます（PascalCase のバリアント名と衝突しません）。

## newtype（名目型）

既存の型と同じ表現・同じ実装を持ちながら、**型としては別物**として扱う名前付き型を `newtype` で宣言します。中身が同じ `String` でも `UserId` と `Email` を取り違えない、といった「プリミティブ強迫（primitive obsession）」の回避に使います。

```plew
newtype Meter = F64
newtype UserId = String
```

> Haskell の `newtype` と違い、Plew の `newtype` は**元の型の実装をそのまま引き継ぎ**、変換は `as` で行います（ラップ／アンラップ用のコンストラクタはありません）。

### 実装の継承と Self 置換

`newtype` は元の型のすべての実装（メソッド・トレイト実装・演算子・factory）を自動的に継承します。継承の際、シグネチャ中の型は次のルールで読み替えられます。

- **`Self` と書かれた位置**は newtype 自身に置換される。
- **具体的な型名で書かれた位置**はそのまま据え置かれる。

これにより、「受け手と同じ種類」を意図した位置（`Self`）と「本当にその具体型」を意図した位置（型名）を、ライブラリ側が書き分けられます。

トレイト型引数（`Add[Rhs]` の `Rhs`）にも同じ `Self` 置換が効きます。型引数に `Self` と書いた位置は newtype 自身に、具体型名で書いた位置は据え置かれます。

```plew
// 標準ライブラリ側のイメージ
impl F64 as Add[Self] {        // 同種同士の加算
    type Output = Self
    fn add(rhs: Self) -> Self { ... }
}
impl F64 as Mul[F64] {         // スカラ倍（右オペランドは F64 据え置き）
    type Output = Self
    fn mul(rhs: F64) -> Self { ... }
}

newtype Meter = F64

meter + meter   // Add[Self] → 置換され add(rhs: Meter) -> Meter   ✅ Meter
meter * 2.0     // Mul[F64]（据え置き）→ mul(rhs: F64) -> Meter   ✅ Meter（2.0 はスカラのまま）
meter * meter   // ✗ Mul[Meter] は無い（rhs に F64 を要求）→ meter * (meter as F64)
```

継承された実装はコンパイラが合成するものです。**ユーザーが `newtype` に `impl` を書くことはできません**（[拡張](10-extensions.md) でも同様）。独自の振る舞いを足したい場合は構造体でラップします。

### 別の型としての扱いと as

`newtype` と元の型は別の型なので、代入・引数渡しには明示的な `as` キャストが必要です。両者は表現が同一なので、この `as` は**双方向・ゼロコストの再タグ**で必ず成功します（[From トレイト](07-operators.md) による計算を伴う変換とは異なります）。

```plew
val d: Meter = 5.0 as Meter
val raw: F64 = d as F64
```

### 生成

`factory` は暗黙的に `Self` を返すため（上記 [インスタンス生成](#インスタンス生成) 参照）、`newtype` は元の型の factory も継承します。したがって生成も他の型と同じく JSX 構文で行えます。

```plew
@[DefaultFactory(pub)]
struct Rgb { val code: I32 }

newtype Brand = Rgb

val c = <Brand code=255 />  // 継承した既定 factory（Self = Brand）
```

> トレイトの関連型や impl のメンバ型を表す `type X = Y` は別概念で、そちらは透過的な型束縛です（別型扱いも `as` も伴いません）。

## ジェネリクス

基本的に Rust と同様に不変（invariant）です。型パラメータは `[...]` で宣言します。

```plew
struct Container[T] {
    val value: T
}

fn process[T](container: Container[T]) where T: Display {
    // 処理
}
```

**型パラメータの `[...]` には名前だけを並べます**（`[T]`・`[T, U]`）。制約はインラインに書かず、すべて [`where` 句](#where-句)に集約します（`fn`・`struct`・`enum`・`trait`・`impl` で共通）。

### impl の型パラメータ

`impl` 自身が導入する型パラメータは、型名の前に **`impl[...]`** で宣言します（`fn f[...]` と同形）。`impl[T]` で束縛した名前を、self 型・トレイト・`where` の中で**使います**。

```plew
impl[T] Container[T] { /* … */ }                        // self が generic（inherent）
impl[T] Container[T] as Drawable where T: Display { }    // 条件付き準拠
impl[T] Vector as Mul[T] where T: Scalar { }             // T はトレイト引数だけに現れる
impl Container[I32] as SomeTrait { }                     // 具体インスタンス化（バインダなし）
impl Celsius { /* … */ }                                 // 非ジェネリックはブラケット不要
```

- `impl[T]`（束縛）と `Container[T]`（使用）を分けるので、`impl Container[I32]`（具体型に対する実装）と曖昧になりません。
- 型パラメータがトレイト引数・`where`・メソッドにしか現れない場合も、`impl[...]` が置き場になります（self 型のブラケットに頼らない）。

## Where 句

型パラメータへの制約を表現します。各述語は **`型: 制約`** の形です（`T: Clone + Display`、関連型射影への制約 `T.Item: Display` も書けます）。

```plew
fn func[T](param: T) where T: Clone + Display {
    // 処理
}
```

- **特定の具体型に対する実装は型の位置に直接書きます** — `impl MyStruct[I32] as SomeTrait { }`（`where T = I32` のような型等価述語は持ちません）。
- 関連型を特定の型に束ねるのは `where` の述語ではなく、**トレイト名の `[...]` 内の関連型束縛**です（`T: Iterator[Item = I32]`。→ [トレイト](05-traits.md)）。
