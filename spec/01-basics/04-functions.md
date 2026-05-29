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

引数のモード（`borrow`／`inout`／`move`・copyable は既定で by-value）、`async fn`／`spawn fn`、型引数の能力マーカー（`allow_unique`／`no_local`）は [値・変数・所有権](03-values.md)・[非同期処理とメモリ管理](../04-execution/14-concurrency.md)・[ジェネリクス](../02-type-system/06-generics.md) を参照。

## 引数ラベル

全ての関数呼び出しは、各引数に**ラベル（= 引数名）が必須**です。関数・メソッド・関連関数だけでなく、**クロージャの呼び出しも同様**です。ラベルはパラメータ名と一致し、宣言順に並べます。

```plew
fn greet(name: String, greeting: String) -> String {
    return "{greeting}, {name}"
}

greet(name: "Alice", greeting: "Hello")  // ラベル必須・宣言順
```

引数を持たない呼び出しにはラベルはありません（`make_counter()` など）。クロージャ呼び出しでもラベルが必要なため、**関数型はラベルを保持します**（Swift と異なり、型からラベルは落ちません）。

## デフォルト引数

引数に `= 式` を付けると、その引数は呼び出しで省略できます。

```plew
fn greet(name: String, greeting: String = "Hello", loud: Bool = false) -> String { ... }

greet(name: "Alice")                   // greeting="Hello", loud=false
greet(name: "Alice", greeting: "Hi")   // loud=false
greet(name: "Alice", loud: true)       // greeting="Hello"（途中だけ省略）
```

- **評価は呼び出しごと**です。引数を省略した呼び出しのたびにデフォルト式を新しく評価します（定義時に一度だけ評価して共有する Python 流ではありません）。よって `items: Array[I32] = []` は呼び出しのたびに**新しい空配列**になり、ある呼び出しの破壊的変更が次の呼び出しへ漏れません（値意味論＋毎回評価の帰結＝Python の `def f(x=[])` の罠を踏まない）。`now()` のような副作用や確保を含む式も毎回実行されます（コンパイル時定数に限りません）。
- **評価スコープは関数を定義したモジュール**です（呼び出し側ではありません）。デフォルト式はシグネチャの一部なので、呼び出し側から見えない非公開の名前も参照できます。「省略＝呼び出し側にデフォルト式を貼り付ける」という解釈ではありません。
- **デフォルト式は他の引数も `self` も参照できません**。デフォルトはシグネチャ単体で評価できる自己完結な値であるべきで、引数の評価順への依存を持ち込まないためです（`fn f(a: I32, b: I32 = a + 1)` や メソッドの `= self.count` は不可）。既定に使いたい値はモジュールのトップレベル定義や型の `assoc` 値／関数で与えます。`self` 由来の既定が要るときはオーバーロードに分けます。
- **省略できる引数は末尾に限りません**。ラベルが位置を曖昧さなく指すため、`greet(name:, loud:)` のように途中のデフォルト引数だけを省く呼び出しも一意です。省略する引数の組み合わせは自由で、残りの引数は宣言順にラベル付きで並べます。
- **`inout` 引数はデフォルトを持てません**（書き戻し先の場所が必要で、値であるデフォルトとは相容れないため）。

### オーバーロードとの関係

デフォルト引数を持つ関数は、**省略した引数の組み合わせごとに呼び出しセレクタ（名前＋ラベル列）を増やします**。例えば `fn f(a: I32 = 0, b: I32)` はセレクタ `f(a:b:)` と `f(b:)` の両方で呼べます。

これらの派生セレクタは通常のオーバーロード集合に加わり、既存の解決規則（同一セレクタは具体位置の型で区別 → [メソッドと impl](../02-type-system/07-methods-impl.md)）に従います。**別途宣言した関数のセレクタと衝突して型で区別できなければコンパイルエラー**です（例：上の `f` に加えて同じ型の `fn f(b: I32)` を宣言すると `f(b:)` が二重）。「一意に定まらなければエラー」という Plew の方針どおりです。

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

クロージャは外側のスコープの変数をキャプチャします。**値意味論なので、copyable は[コピー（スナップショット）でキャプチャ](03-values.md#値意味論value-semantics)** ── 閉包外の変更は閉包に伝わらず、閉包内の変更も外へ漏れません。閉包と外で**同じ可変状態を共有**したいときは [`Ref`](03-values.md#ref--weakref共有可変) を明示的にキャプチャします（共有可変の唯一の手段）。

```plew
struct Counter { mut val n: I32 }

fn make_counter() -> fn() -> I32 {
    val c = <Ref value=<Counter n=0 /> />   // 共有可変カウンタ（Ref）
    return fn() -> I32 {
        c->n += 1                            // Ref をコピーキャプチャ＝同じ Counter を共有
        return c->n
    }
}

val counter = make_counter()
counter()  // 1
counter()  // 2
```

- **copyable のキャプチャはコピー**（独立スナップショット）。**`unique` 値はキャプチャできない**（閉包へ move する構文は当面なし）。共有可変は `Ref` を copy-capture し、ARC が生存を保つ（GC 非依存・`[weak self]`/`@escaping` 注釈は無い）。
- `Ref` で**循環**ができ得る構造（閉包を保持するオブジェクトをその `Ref` が指す等）は [`WeakRef`](03-values.md#ref--weakref共有可変) で断ち切る（旧「GC で循環ノーケア」は ARC では成り立たない）。
- **`spawn` ブロックのキャプチャは copyable のみ**（`unique`/`Ref`/`borrow` は不可。`unique` をスレッドへ渡すなら `spawn fn`）→ [非同期処理とメモリ管理](../04-execution/14-concurrency.md)。
