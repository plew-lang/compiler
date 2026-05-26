# 関数とメソッド

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
- ただし `spawn` ブロックのキャプチャは全て immutable に制限されます（[非同期処理とメモリ管理](09-concurrency.md) 参照）。

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

`impl` には `factory`（インスタンス生成）も書けます。生成は型の生成として [型システム](02-types.md) の「インスタンス生成」にまとめています。トレイト準拠の `impl Type as Trait` と `via` は [トレイト](05-traits.md) を参照。

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

フィールド・メソッドの可視性は**型のカプセル化だけ**を制御し、モジュール/パッケージ境界とは独立です（境界は [モジュール](11-modules.md) の `export` / 再エクスポートが担当）。段階は **2 つだけ**で、`pub(crate)` のような中間段は持ちません。

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
