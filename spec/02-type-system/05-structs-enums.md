# 構造体と列挙型

## 構造体

```plew
@[DefaultFactory(pub), Eq, Hash]  // ディレクティブ（オプション）
export struct MyStruct[T] where T: SomeTrait {
    pub val field1: String
    pub(get) val readonly_field: I32  // getter付きpublicフィールド
    mut val field2: T
}
```

`pub` / `pub(get)` / 非公開（修飾なし）のメンバ可視性は本章末の[メンバの可視性](#メンバの可視性)を参照。非公開メンバは型の無名 impl からのみ見えます。

型本体には `default_extension #Ext1#Ext2` を書けます。これはこの型のベア表面に**既定で載せる拡張**の宣言です（列挙は型レベルの `Type#A#B` と同じ `#` 連結）。`impl`（実装）ではなく型の宣言なので型本体に置きます。意味論・衝突規則・剥がし方は [拡張のデフォルト拡張](09-extensions.md#デフォルト拡張default_extension) を参照。列挙型でも同様に書けます。

```plew
struct Counter {
    mut val n: I32
    default_extension #StepperExt   // counter.double_step() がベアで呼べる
}
```

**構造体ディレクティブ**: 詳細は今後決定予定（[メタプログラミング](../04-execution/16-metaprogramming.md) 参照）

## 列挙型

```plew
@[All, Eq, Hash]  // ディレクティブ（オプション）
export enum Color[T] where T: Format {
    Red { val intensity: F64 }
    Green
    Blue
}
```

**列挙型ディレクティブ**: 詳細は今後決定予定（[メタプログラミング](../04-execution/16-metaprogramming.md) 参照）

## フィールドの統一原則

構造体と列挙型バリアントは、どちらも**名前付きフィールド**のみを持ちます。位置指向の無名ペイロード（`Some(T)` のようなもの）は書けません。そのため、宣言・生成・分解の3つで両者は同じ構文に従います。

| | 構造体 | 列挙型バリアント |
| --- | --- | --- |
| 宣言 | `struct S { val field: T }` | `enum E { V { val field: T } }` |
| 生成 | `<S field=expr />` | `<E.V field=expr />` |
| 分解 | `S { field: val binding }` | `E.V { field: val binding }` |

- 生成は JSX ライク構文のみ（下記 [インスタンス生成](#インスタンス生成) 参照）。
- 分解は必ず**型名を先頭に置く**ため、`{` 始まりのブロックと曖昧になりません（[制御構造](../03-expressions/11-control-flow.md) 参照）。

## 標準の Optional / Result

オプショナル値とエラーは特別な構文ではなく、通常の列挙型として定義されます。

```plew
@[All, Eq]
export enum Optional[T] {
    Some { val value: T }
    None
}

@[All, Eq]
export enum Result[T, E] {
    Ok { val value: T }
    Err { val error: E }
}
```

```plew
val some = <Optional.Some value=42 />
val none = <Optional.None />

match maybe_value {
    Optional.Some { value: val v } => v
    Optional.None                  => 0
}
```

オプショナルチェーン（`?.`）・nil 合体（`??`）は、それぞれ `Chain` / `Coalesce` トレイトの実装によって有効になります（[型変換と演算子](../03-expressions/12-operators.md) 参照）。

> トレイトもカスタム型の一種ですが、要求・関連型・継承・準拠と `via` の意味論は独立章の[トレイト](08-traits.md)にまとめています。

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

**子要素の対応づけ（Plew で最も暗黙的な箇所）**：`<Tag>…子…</Tag>` の子要素は、フィールド名がちょうど **`children`** のフィールドへ渡されます（属性で `children=…` と書くのと等価）。`children` の型は、子要素の並び（イテレータ）から構築できることを宣言するトレイト（暫定 `FromIterator[T]`・名称未決）に準拠していなければなりません。

`@[DefaultFactory(pub)]` ディレクティブで、フィールドをそのまま受け取る既定の factory の公開範囲を制御できます。

### factory

カスタムの生成ロジックは `impl` 内に `factory` で定義します（`impl` は [メソッドと impl](07-methods-impl.md)）。古典的なコンストラクタと違い `self` を初期化するのではなく、**完成したインスタンスを `return` で返します**（＝ファクトリ）。`return` は必須で、キャッシュ済みの値など `<Type … />` 以外を返してもかまいません。

- 無名 `factory(...)` → `<Type … />` で呼び出す。ラベル集合が異なれば複数定義（[オーバーロード](07-methods-impl.md)）できる。
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

factory の戻り型は常に暗黙の `Self` です。本体での `<Type field=… />`（全フィールド指定）はフィールド初期化（＝ `Self` の生成）を指し、自分自身を再帰呼び出ししません。この `Self` 規約により、[`newtype`](10-newtype.md) は元の型の factory をそのまま継承して JSX 構文で生成できます。

### 列挙型バリアントの生成

列挙型のバリアントも同じ構文で生成します。`Enum.Variant` を型として指定し、フィールドを持たないバリアントは要素なしで生成します。

```plew
val some = <Optional.Some value=42 />
val none = <Optional.None />
val ok   = <Result.Ok value=data />
val err  = <Result.Err error=parse_error />
```

enum にも snake_case の名前付き factory を定義できます（PascalCase のバリアント名と衝突しません）。

## メンバの可視性

フィールド・メソッドの可視性は**型のカプセル化だけ**を制御し、モジュール/パッケージ境界とは独立です（境界は [モジュール](../04-execution/15-modules.md) の `export` / 再エクスポートが担当）。段階は **2 つだけ**で、`pub(crate)` のような中間段は持ちません。

- **`pub`** — その型を参照できるコードからメンバが見える。
- **`pub(get)`** — 読み取りは `pub`、書き込みは型の内部のみ（外部からは不変）。
- **修飾なし（非公開）** — **その型の無名 impl の中からのみ**見える。同一モジュールの非 impl コード・他の型・名前付き拡張（`#Ext`、自型・他型を問わず）・外部パッケージ、いずれからも見えない。

```plew
struct Account {
    pub val id: I32             // どこからでも見える
    pub(get) val balance: I32   // 読み取り公開・書き込みは内部のみ
    mut val secret_key: String  // 無名 impl の中だけ
}

impl Account {                  // 無名 impl → secret_key が見える
    pub inout fn rotate_key() { self.secret_key = generate() }
}

extension Audit {
    impl Account {              // 拡張 → pub / pub(get) のみ
        fn report() -> I32 { return self.balance }  // OK
        // fn leak() -> String { return self.secret_key }  // エラー: 非公開
    }
}
```

非公開メンバを見られるのが**無名 impl だけ**なので、外部型を拡張しても作者が隠した内部には触れられず、`pub` のカプセル化が型レベルで保たれます。兄弟モジュールがメンバを使いたい場合は `pub` にする（＝外部にも見える）か、密結合なコードを型のモジュールに `part` で同居させて無名 impl から触れます。
