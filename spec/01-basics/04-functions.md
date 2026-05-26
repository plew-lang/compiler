# 関数

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
- ただし `spawn` ブロックのキャプチャは全て immutable に制限されます（[非同期処理とメモリ管理](../04-execution/14-concurrency.md) 参照）。
