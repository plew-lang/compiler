# Plew プログラミング言語仕様書

## 概要

Plew は現代的なシステムプログラミング言語で、型安全性、非同期プログラミング、パターンマッチング、独自の拡張システムを重視して設計されています。シングルプロセス・シングルスレッドを基本とし、JavaScript ライクな非同期処理とガベージコレクションによるメモリ管理を採用しています。

## 基本構文

### 命名規則

- **型名**: PascalCase（例: `MyType`, `String`）
- **変数名・関数名**: snake_case（例: `my_variable`, `calculate_sum`）

### キーワード

```
export, pub, get, type, val, mut, async, spawn, await, loop, break, continue,
give, return, where, enum, struct, assoc, extension, impl, via, trait, fn,
construct, inout, guard, while, for, in, if, elif, else, match, as, self,
Self, extern, import, with, try
```

## 型システム

### プリミティブ型

- **整数リテラル**: `123`
- **浮動小数点リテラル**: `3.14`
- **真偽値**: `true`, `false`
- **文字列**: `"hello world"` （変数展開対応）

### 文字列の変数展開

文字列内で`{expression}`による変数展開が可能です。Format トレイトを実装している型で利用できます。

```plew
val name = "Alice"
val age = 30
val message = "Hello, {name}! You are {age} years old."
val formatted = "Pi is approximately {pi:.2}"  // フォーマット指定
```

```plew
trait Format {
    fn format(format: String) -> String
}
```

### 複合型

#### 配列

```plew
[1, 2, 3, 4]
[expression1, expression2, ...]
```

#### 辞書

```plew
[key1: value1, key2: value2]
[:]  // 空の辞書
```

#### タプル

```plew
(value1, value2, value3)
```

### カスタム型

#### 構造体

```plew
@[default_constructor(pub), eq, hash, clone]  // ディレクティブ（オプション）
export struct MyStruct[T] where T: SomeTrait {
    pub val field1: String
    pub(get) val readonly_field: I32  // getter付きpublicフィールド
    mut val field2: T
}
```

**構造体ディレクティブ**: 詳細は今後決定予定

#### 列挙型

```plew
@[all, eq, hash]  // ディレクティブ（オプション）
export enum Color[T] where T: Display {
    Red { val intensity: Float }
    Green
    Blue
}
```

**列挙型ディレクティブ**: 詳細は今後決定予定

#### トレイト

```plew
export trait Drawable[T] where T: Clone {
    type Output: Display  // 関連型

    val required_field: I32  // フィールド要求

    assoc fn create() -> Self  // 関連関数
    fn draw() -> Output    // インスタンスメソッド
    mut fn rotate(angle: Float)  // 可変メソッド
}
```

### ジェネリクス

基本的に Rust と同様に不変（invariant）です。

```plew
struct Container[T] {
    val value: T
}

fn process[T](container: Container[T]) where T: Display {
    // 処理
}
```

### Where 句

型制約の表現に使用します。`:` （トレイト境界）と `=` （型等価）の両方をサポートします。

```plew
// トレイト境界
fn func[T](param: T) where T: Clone + Display {
    // 処理
}

// 型等価制約
impl MyStruct[T] as SomeTrait where T = I32 {
    // T が I32 の場合のみ実装
}
```

## 変数と値の管理

### 参照の値渡しと inout

Plew では全ての値の受け渡しは参照の値渡しで行われます。

```plew
fn immutable_function(param: MyStruct) {
    // param は不変 - フィールドの変更や可変メソッドの呼び出し不可
    param.some_field = new_value  // エラー
    param.mutate()  // エラー
}

fn mutable_function(inout param: MyStruct) {
    // param は可変 - フィールドの変更や可変メソッドの呼び出し可能
    param.some_field = new_value  // OK
    param.mutate()  // OK
}
```

### 変数宣言

```plew
val immutable_var: I32  // 不変変数
mut val mutable_var: String = "initial"  // 可変変数

// 不変変数を可変変数に代入するにはclone()が必要
val immutable_data = <SomeStruct field=42 />
mut val mutable_data = immutable_data.clone()
```

### 代入と構造化代入

```plew
// 基本代入
variable = expression
variable += expression
variable -= expression
variable *= expression
variable /= expression

// タプルの構造化代入
(a, b, c) = some_tuple

// 構造体の構造化代入
[field1: x, field2: y] = some_struct

// 複合的な構造化代入
(first, [name: person_name, age: person_age]) = complex_data
```

## 関数

### 関数宣言

```plew
export async fn function_name[T, U](
    arg1: Type1,
    inout arg2: Type2,
    arg3: Type3 = default_value
) -> ReturnType where T: Trait1, U: Trait2 {
    // 関数本体
}
```

### メソッドと impl

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

### via によるフィールドエイリアス

トレイトにフィールドを定義し、実装時に既存フィールドをエイリアスとして使用できます。

```plew
trait HasPosition {
    val x: I32
    val y: I32
}

struct Point {
    val coordinate_x: I32
    val coordinate_y: I32
}

impl Point as HasPosition {
    val x via coordinate_x  // coordinate_x を x として公開
    val y via coordinate_y  // coordinate_y を y として公開
}
```

## 構造体のインスタンス作成（construct 構文）

全ての構造体は**JSX ライクな構文でのみ**インスタンス化できます。

```plew
struct Person {
    val name: String
    val age: I32
}

// インスタンス作成
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

## 制御構造

### ブロック式と give 文

ブロックを式として評価するには`give`文が必要です。

```plew
val result = {
    val temp = calculate_something()
    give temp * 2  // ブロックの戻り値
}

// エラー: give がないブロックは式として評価不可
val invalid = { 42 }  // コンパイルエラー
```

### 条件分岐

```plew
val result = if condition {
    give "true case"
} elif another_condition {
    give "elif case"
} else {
    give "else case"
}
```

### パターンマッチング

```plew
val result = match expression {
    42 => { give "the answer" }
    Color.Red(val intensity) => { give "red with intensity {intensity}" }
    (val x, val y) => { give "tuple with x={x}, y={y}" }
    _ => { give "default case" }
}
```

### ループ

```plew
// 無限ループ（式として使用可能）
val result = loop {
    val data = get_data()
    if data.is_valid() { 
        break data.process()  // ループの戻り値
    }
    if should_retry() { continue }
    break Error.Failed  // エラー時の戻り値
}

// While ループ
while condition {
    // 処理
}

// For ループ（構造化代入対応）
for (key, value) in dictionary {
    // 処理
}

for [name: person_name, age: person_age] in people {
    // 処理
}
```

### ガード文

条件が満たされない場合に早期リターンやブロック脱出を行います。列挙型のunwrapと変数代入も可能です。

```plew
// 基本的な条件チェック
guard user.is_authenticated() && user.has_permission("read") {
    return Error.Unauthorized
}
// ここに到達するのは guard 条件が true の場合のみ

// 列挙型のunwrapと変数代入
guard Result.Ok(val value) = some_result {
    return Error.Failed
}
// ここでは value が使用可能

// 複数の条件を組み合わせ
guard Option.Some(val data) = maybe_data && data.is_valid() {
    return Error.Invalid
}
// ここでは data が使用可能
```

## 非同期プログラミング

Plew は JavaScript と同様のシングルプロセス・シングルスレッド + イベントループモデルを採用しています。

### 基本的な非同期処理

```plew
async fn fetch_data(url: String) -> Promise[Result[Data, Error]] {
    val response = await http_request(url)
    val data = await response.json()
    Promise.resolve(Result.Ok(data))
}

async fn main() {
    val data = await fetch_data("https://api.example.com/data")
    print("Received: {data}")
}
```

### spawn によるマルチプロセス実行

```plew
fn heavy_computation() {
    spawn {
        // この処理は別プロセスで実行される
        val result = expensive_calculation()

        // spawn 内でキャプチャした変数は不変として扱われる
        // （元が可変変数でも spawn 内では不変）
    }
}
```

## エラーハンドリング

### try 式 - Rust の?演算子相当

`try`は特別なエラーハンドリングではなく、Result 型の早期リターンのシンタックスシュガーです。

```plew
fn parse_and_process(input: String) -> Result[I32, String] {
    val number: I32 = try parse_int(input)  // エラー時は早期リターン
    val processed = number * 2
    Result.Ok(processed)
}

// エラー型のキャスト（As トレイト実装時）
fn complex_operation() -> Result[Data, GeneralError] {
    val result1: Result[I32, ParseError] = try_parse()
    val value = try result1  // ParseError が GeneralError に自動キャスト
    // 処理続行
}
```

## 型キャストと As トレイト

`as`キャストは`As`トレイトのシンタックスシュガーです。

```plew
trait As[T] {
    fn as() -> T
}

impl I32 as As[I64] {
    fn as() -> I64 {
        // I32 から I64 への変換実装
    }
}

val x: I32 = 10
val y: I64 = x as I64  // x.as() と同等
```

## 演算子システム

全ての演算子は対応するトレイトの実装で動作します。

```plew
trait Add[T] {
    type Output
    fn add(self, other: T) -> Output
}

struct Vector {
    val x: Float
    val y: Float
}

impl Vector as Add[Vector] {
    type Output = Vector

    fn add(self, other: Vector) -> Vector {
        <Vector x=(self.x + other.x) y=(self.y + other.y) />
    }
}

val v1 = <Vector x=1.0 y=2.0 />
val v2 = <Vector x=3.0 y=4.0 />
val result = v1 + v2  // Vector.add() が呼ばれる
```

## 拡張システム

Plew の特徴的な機能として、値に対して動的に拡張を適用できるシステムがあります。拡張は値自体を変更するのではなく、その値の型に対して一時的に機能を追加する仕組みです。

### 拡張で追加できる機能

拡張では以下の要素を既存の型に追加できます：

- **メソッド** - インスタンスメソッドや可変メソッド
- **関連値** - 関連定数や関連変数（`assoc val`）
- **型エイリアス** - 型の別名定義
- **コンストラクタ** - 新しいコンストラクタ
- **viaフィールドエイリアス** - 既存フィールドの別名

### 拡張の定義と使用

```plew
struct Person {
    val name: String
    val age: I32
}

extension GreetingExtension {
    impl Person {
        // メソッドの追加
        fn greet() -> String {
            give "Hello, I'm {self.name}"
        }
        
        // 関連値の追加
        assoc val default_greeting: String = "Hi there!"
        
        // 型エイリアスの追加
        type NameType = String
    }
}

extension FormalExtension {
    impl Person {
        fn greet() -> String {  // 同名メソッドでも拡張が違えばOK
            give "Good day, my name is {self.name}"
        }

        fn introduce() -> String {
            give "Allow me to introduce myself: {self.name}"
        }
        
        // コンストラクタの追加
        construct formal_person(name: String) {
            <Person name=name age=0 />
        }
    }
}

// トレイト実装の追加例
extension MathExtension {
    impl Person as Add[Person] {
        type Output = Person
        
        fn add(other: Person) -> Person {
            <Person name="{self.name} & {other.name}" age=(self.age + other.age) />
        }
    }
    
    // 複数の型を同一拡張内で拡張可能
    impl String {
        fn shout() -> String {
            give "{self}!"
        }
    }
}

fn example() {
    val person = <Person name="Alice" age=25 />

    // 拡張を明示的に適用してメソッド呼び出し
    val greeting1 = person#GreetingExtension.greet()
    val greeting2 = person#FormalExtension.greet()
    
    // 関連値へのアクセス
    val default = Person#GreetingExtension.default_greeting
    
    // 拡張でトレイト実装を追加した場合の演算子使用
    val combined = person#MathExtension + <Person name="Bob" age=30 />
    
    // 拡張なしではメソッド呼び出し不可
    person.greet()  // エラー: greet メソッドは定義されていない
}
```

### 拡張の制約

#### 既存メソッドとの衝突

拡張では、対象の型に既に定義されているメソッドと同名のメソッドを追加することはできません（コンパイルエラー）。

```plew
struct MyStruct {}

impl MyStruct {
    fn existing_method() {}
}

extension ProblematicExtension {
    impl MyStruct {
        fn existing_method() {}  // エラー: 既存メソッドと衝突
    }
}
```

### 拡張の型システム統合

```plew
fn handle_formal_person(person: Person#FormalExtension) {
    // 拡張適用済みの型として受け取り
    person.greet()      // OK: FormalExtension.greet
    person.introduce()  // OK: FormalExtension.introduce
}

fn convert_extensions(person: Person#GreetingExtension) {
    // 同名メソッドを持つ拡張を同時適用しようとするとコンパイルエラー
    // val conflicted: Person#GreetingExtension#FormalExtension  // エラー: greet メソッドが衝突

    // 拡張を外して別の拡張を適用
    val formal_only = person#!GreetingExtension#FormalExtension
    formal_only.greet()  // OK: FormalExtension.greet のみ

    // 拡張の付け替え
    val with_greeting = formal_only#!FormalExtension#GreetingExtension
    with_greeting.greet()  // OK: GreetingExtension.greet
}
```

## モジュールシステム

### インポート

```plew
import @ExternalPackage               // 外部パッケージ
import ./LocalModule                 // ローカルモジュール
import ../ParentModule as Parent     // エイリアス付きインポート
import SomeModule with { Type1, function1 as func1 }  // 選択的インポート

// パス表現
import ../../../Utils    // 相対パス
import ./Src/Components  // 相対パス
```

#### ファイル名・ディレクトリ名の制約

パスコンポーネント（ファイル名・ディレクトリ名）は以下の制約があります：

- **PascalCase** でなければならない（例: `MyModule`, `Utils`, `Components`）
- **`.`** （現在のディレクトリ）と **`..`** （親ディレクトリ）は例外として使用可能

```plew
import ./MyModule        // ✅ OK: PascalCase
import ../ParentModule   // ✅ OK: PascalCase  
import ./my_module       // ❌ エラー: snake_case は不可
import ./123Module       // ❌ エラー: 数字から始まる名前は不可
import ./kebab-case      // ❌ エラー: ハイフンは使用不可
```

### エクスポート

```plew
export struct PublicStruct { /* ... */ }
export fn public_function() { /* ... */ }
export trait PublicTrait { /* ... */ }
```

### 外部コード統合

```plew
extern "c" {
    fn malloc(size: usize) -> *mut u8
    fn free(ptr: *mut u8)
}

extern "javascript" {
    fn console_log(message: String)
    val window: JsWindow
}
```

## メモリ管理

Plew はガベージコレクションを採用しており、基本的にメモリ管理を気にする必要はありません。シングルプロセス・シングルスレッドのため、メモリ安全性の問題も最小限です。

ただし、`spawn`ブロック使用時のみ、キャプチャされた値の可変性制限により競合状態を防止しています。

## コメント

```plew
// 行コメント

/*
 * ブロックコメント
 * 複数行にわたって記述可能
 */
```

## 標準的なトレイトとその用途

### 基本トレイト

- `Clone`: オブジェクトの複製
- `Eq`: 等価比較
- `Hash`: ハッシュ値計算
- `Display`: 表示用フォーマット
- `Format`: 変数展開用フォーマット

### 変換トレイト

- `As[T]`: 型変換（`as` 演算子）

### 演算子トレイト

- `Add[T]`, `Sub[T]`, `Mul[T]`, `Div[T]`: 算術演算
- `And[T]`, `Or[T]`: 論理演算
- `Eq[T]`, `Ne[T]`, `Lt[T]`, `Le[T]`, `Gt[T]`, `Ge[T]`: 比較演算

## サンプルコード

### 基本的な構造体と拡張

```plew
struct Calculator {
    mut val current: Float
}

extension BasicMath {
    impl Calculator {
        mut fn add(value: Float) {
            self.current += value
        }

        fn result() -> Float {
            give self.current
        }
    }
}

extension AdvancedMath {
    impl Calculator {
        mut fn power(exponent: Float) {
            self.current = math_pow(self.current, exponent)
        }

        mut fn sqrt() {
            self.current = math_sqrt(self.current)
        }
    }
}

async fn main() {
    mut val calc = <Calculator current=0.0 />

    val basic_result = calc#BasicMath
        .add(10.0)
        .add(5.0)
        .result()  // 15.0

    val advanced_calc = calc#AdvancedMath
    advanced_calc.power(2.0)  // 225.0
    advanced_calc.sqrt()      // 15.0

    print("Final result: {advanced_calc.result()}")
}
```

この仕様書は Plew プログラミング言語の現在の設計を反映しています。
