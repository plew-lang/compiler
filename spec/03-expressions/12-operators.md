# 型変換と演算子

## 型キャストと From トレイト

`x as T` キャストは、ターゲット型 `T` の `From[Source]` 実装を呼ぶシンタックスシュガーです（`x as T` ⟺ `T.from(x: x)`）。**唯一の例外は [`newtype`](../02-type-system/10-newtype.md) と元の型の間の `as`** で、これは `From` 実装ではなく表現が同一な型どうしのゼロコストな再タグ（構造的に必ず成功）として処理されます。

```plew
trait From[Source] {
    assoc fn from(x: Source) -> Self
}

impl I64 as From[I32] {
    assoc fn from(x: I32) -> I64 {
        // I32 から I64 への変換実装
    }
}
impl I64 as From[I16] {                  // 別ソースは別 conformance
    assoc fn from(x: I16) -> I64 { /* ... */ }
}

val x: I32 = 10
val y: I64 = x as I64  // I64.from(x: x) と同等
```

ターゲット型は `as T` の `T`（や `try` の関数戻り型）で常に明示的に決まるので、`from(x:)` は**ソース引数の型でオーバーロード解決**されます（→ [メソッドのオーバーロード](../02-type-system/07-methods-impl.md)）。これにより 1 つの型が複数ソースから変換可能（`I64` は `From[I32]` と `From[I16]` の両方に準拠）になります。`try` のエラー変換も同じ `From` を使います（→ [エラーハンドリング](13-error-handling.md)）。

**暗黙変換は持ちません。** 型変換は常に明示の `as`（数値の幅変更 `I32→I64` 等も `x as I64` と書く）。例外は `try` のエラー変換（`From` を暗黙挿入）と数値リテラルの多相だけ。これによりオーバーロード解決は「ラベル＋具体型の完全一致（リテラルは互換候補に絞り一意か否か）」に保たれ、変換ランク付けの曖昧さが生じません。

## 演算子システム

全ての演算子は、対応するトレイトのメソッド呼び出しのシンタックスシュガーです。**演算子は、オペランドの型に対応するトレイトが実装されている場合にのみ呼び出せます。** 未実装の型に演算子を適用するとコンパイルエラーになります（これは二項演算子・単項演算子・添字アクセスすべてに共通します）。なお **`&&` / `||` は例外**で、短絡評価する制御フロー糖衣でありトレイトではありません（後述「論理結合子」）。

```plew
trait Add[Rhs] {
    type Output
    fn add(rhs: Rhs) -> Output
}

struct Vector {
    val x: F64
    val y: F64
}

impl Vector as Add[Vector] {
    type Output = Vector

    fn add(rhs: Vector) -> Vector {
        return <Vector x=(self.x + rhs.x) y=(self.y + rhs.y) />
    }
}

val v1 = <Vector x=1.0 y=2.0 />
val v2 = <Vector x=3.0 y=4.0 />
val result = v1 + v2  // v1.add(rhs: v2) と同等
```

### 演算子のオーバーロード（右オペランド型ごとの conformance）

演算子は対応トレイトのメソッドの糖衣です（`a + b` ⟺ `a.add(rhs: b)`）。トレイトは右オペランド型を型引数に持つので（`Add[Rhs]`）、**1 つの型が複数の右オペランド型に準拠**でき、`add` は引数型で区別される[オーバーロード](../02-type-system/07-methods-impl.md)として解決されます。

```plew
// Vector * Vector
impl Vector as Mul[Vector] {
    type Output = Vector
    fn mul(rhs: Vector) -> Vector { /* 要素ごとの積など */ }
}
// Vector * F64（スカラー倍）
impl Vector as Mul[F64] {
    type Output = Vector
    fn mul(rhs: F64) -> Vector { /* スカラー倍 */ }
}

val a = <Vector x=1.0 y=1.0 />
val b = a * <Vector x=2.0 y=2.0 />   // Mul[Vector]
val c = a * 2.0                       // Mul[F64]
```

`a * b` は `b` の型で `Mul[…]` の conformance を選びます。**同じ右オペランド型に複数の conformance は書けません**（同セレクタ・同シグネチャで衝突）。blanket なジェネリック impl（`Mul[T] where T: Scalar`）と具体 impl（`Mul[F64]`）の併存も不可（引数位置が generic vs 具体で混在＝オーバーロードの形不一致。specialization は無し）。

> 型引数 `[Rhs]` を持つのは **両辺が別型になり得る演算**（算術・添字・nil 合体・変換）です。**等価・順序は同一型上の関係なので型引数を持ちません**（次節）。

## 等価（Eq トレイト）

`==` / `!=` は `Eq` トレイトの糖衣です。等価は**同一型上の同値関係**（反射・対称・推移）なので、`Eq` は**型引数を持たず**右辺は常に `Self` です。異種比較 `impl A as Eq[B]`（A≠B）は対称律（`B as Eq[A]` が無いと壊れる）・反射律を型で保証できないため持ちません。幅の違う数値などは明示 `as` で型を揃えてから比較します。

```plew
trait Eq {
    fn eq(rhs: Self) -> Bool
}

val same = a == b   // a.eq(rhs: b)
val diff = a != b   // !(a == b)
```

`@[Eq]` ディレクティブはフィールドごとの `impl T as Eq` を合成します（→ [メタプログラミング](../04-execution/16-metaprogramming.md)）。

## 順序（Ord トレイト）

`< <= > >=` は `Ord` トレイトの糖衣です。`Ord` も同一型上の**全順序**なので型引数を持たず（`Ord: Eq`）、比較結果を `Ordering` で返します。4 つの演算子はすべて `compare` に展開されます。

```plew
enum Ordering { Less; Equal; Greater }

trait Ord: Eq {
    fn compare(rhs: Self) -> Ordering
}

a < b    // match a.compare(rhs: b) { Less => true,     _ => false }
a <= b   // match a.compare(rhs: b) { Greater => false, _ => true }
a > b    // match a.compare(rhs: b) { Greater => true,  _ => false }
a >= b   // match a.compare(rhs: b) { Less => false,    _ => true }
```

`F32`/`F64` も `Ord`・`Eq` に準拠しますが、**NaN を比較すると panic** します（IEEE の「NaN はどの値とも順序が付かない」を静かな `false` で返さず落とす）。NaN 判定は `is_nan()`。算術自体は IEEE 据え置きで NaN/inf を生成します（→ [基本型](../01-basics/02-basic-types.md)）。

## 論理結合子（`&&` / `||`）

`&&` / `||` は**短絡評価する制御フロー**で、`if` の糖衣です（演算子トレイトではありません）。両オペランドは `Bool` 限定で、オーバーロードできません。

```plew
a && b   // ≡ if a { give b } else { give false }
a || b   // ≡ if a { give true } else { give b }
```

右オペランドは左の結果次第で評価されません（`b` は `a` が真のときだけ走る）。これは「**右辺は左辺が成り立つときだけ安全に評価したい**」ガード（範囲チェック後の添字、存在確認後のアクセス等）を 1 式で書くためで、`while i < n && p(arr[i])` のようなループ条件で特に効きます。`if` の糖衣として定義されるので、非評価は隠れた魔法ではなく明示的な意味です。

> 前置 `!`（`Not`）は eager（必ずオペランドを評価する値演算）なのでトレイトのままです。ビット演算が必要なら `&` / `|` を `BitAnd` / `BitOr` トレイト（eager）として別途用意します（現状は未提供）。

> **条件位置での `&&`**：`if`/`elif`/`while`/`guard` の条件では、`&&` は Bool 節に加えて反証可能束縛 `PATTERN = expr` も連結します（[条件チェーン](11-control-flow.md)）。値レベルの短絡と同じ概念ですが脱糖は別物で、`||` は束縛節を連結できません。

## 単項演算子

前置演算子も二項演算子と同様にトレイトベースで、対応するトレイトが実装されている場合にのみ呼び出せます。

前置 `!`（論理否定）は`Not`トレイトのシンタックスシュガーです。

```plew
trait Not {
    type Output
    fn not() -> Output
}

impl Bool as Not {
    type Output = Bool

    fn not() -> Bool {
        // 否定の実装
    }
}

val flag: Bool = true
val negated = !flag  // flag.not() と同等
```

## 添字アクセス

`collection[key]`の添字アクセスは`Index`トレイトのシンタックスシュガーです。`Index`を実装した型に対してのみ使用できます。

```plew
trait Index[Key] {
    type Output
    fn index(key: Key) -> Output
}

impl MyArray[T] as Index[I32] {
    type Output = T

    fn index(key: I32) -> T {
        // 要素取得の実装
    }
}

val array = <MyArray ... />
val first = array[0]  // array.index(key: 0) と同等
```

## オプショナルチェーン（Chain トレイト）

`?.` は「値を持つ／持たない」のいずれかに分岐する型へのメンバアクセスのシンタックスシュガーです。`Chain` トレイトを実装した型でのみ使用できます（Optional 専用ではなく、`Chain` を実装した任意の型で使えます）。

```plew
trait Chain {
    type Value
    fn chain() -> Optional[Value]              // 値か空かに分解する
    assoc fn from_value(value: Value) -> Self  // 値から再構築する
    assoc fn empty() -> Self                   // 空を再構築する
}
```

`receiver?.member` は次のように展開されます（`receiver: R` は `R: Chain`、式全体の結果型 `O` も `Chain` を実装する型）:

```plew
match receiver.chain() {
    Optional.Some { value: val v } => O.from_value(value: v.member)
    Optional.None                  => O.empty()
}
```

レシーバが空なら以降のアクセスは評価されず、式全体が空になります（短絡評価）。`chain()` が値を返したときだけメンバへアクセスし、結果を `from_value` で包み直します（`from_value` / `empty` は関連関数なので関数呼び出しで、生成する変数は内部で JSX 構文を使います）。

```plew
val name = user?.profile?.name
// user または profile が空なら name は空
// 両方とも値を持つ場合のみ name にアクセスする
```

Optional 自身への実装は、値か空かをそのまま返すだけです。

```plew
impl Optional[T] as Chain {
    type Value = T

    fn chain() -> Optional[T] {
        return self
    }

    assoc fn from_value(value: T) -> Optional[T] {
        return <Optional.Some value=value />
    }

    assoc fn empty() -> Optional[T] {
        return <Optional.None />
    }
}
```

> `chain()` の戻り値が空のケース（`Optional.None`）は付随する値を持たないため、`Result` のようにエラー情報を運ぶ型は `?.` の対象外です。エラーの早期リターンは [`try`](13-error-handling.md) を使います。

## Nil 合体演算子（Coalesce トレイト）

`??` は二項演算子で、左辺が空のときに右辺へフォールバックします。`Coalesce[Rhs]` トレイトのシンタックスシュガーです。

```plew
trait Coalesce[Rhs] {
    type Output
    fn coalesce(rhs: Rhs) -> Output
}

val result = a ?? b  // a.coalesce(rhs: b) と同等
```

Optional は右辺の型に応じて 2 つの実装を与えます（`coalesce(rhs:)` を右辺型でオーバーロード）。

```plew
// a ?? b （右辺も Optional ならフォールバック結果も Optional）
impl Optional[T] as Coalesce[Optional[T]] {
    type Output = Optional[T]

    fn coalesce(rhs: Optional[T]) -> Optional[T] {
        return match self {
            Optional.Some { value: val v } => <Optional.Some value=v />
            Optional.None                  => rhs
        }
    }
}

// a ?? b （右辺が非 Optional の既定値なら結果は T）
impl Optional[T] as Coalesce[T] {
    type Output = T

    fn coalesce(rhs: T) -> T {
        return match self {
            Optional.Some { value: val v } => v
            Optional.None                  => rhs
        }
    }
}
```

```plew
val port: I32 = config_port ?? 8080  // 右辺 I32 → Coalesce[I32] → 結果 I32
val merged: Optional[I32] = a ?? b   // 右辺 Optional → Coalesce[Optional[I32]] → 結果 Optional
```
