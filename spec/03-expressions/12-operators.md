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

**暗黙変換は持ちません。** 型変換は常に明示の `as`（数値の幅変更 `I32→I64` 等も `x as I64` と書く）。例外は `try` のエラー変換（`From` を暗黙挿入）と数値リテラルの多相だけ。これによりオーバーロード解決は「ラベル＋具体型の完全一致（リテラルは互換候補に絞り一意か否か）」に保たれ、変換ランク付けの曖昧さが生じません。なお[拡張ビューの変更](../02-type-system/09-extensions.md#拡張ビューの変更は明示暗黙キャストなし)（`A`↔`A#P`）は値の表現を変えない**ビューの再解釈**で型変換ではありませんが、これも暗黙には起きず常に `#`／`#!` を明示します。

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

算術二項演算子はそれぞれ対応トレイトの糖衣です（いずれも型引数 `[Rhs]` と `type Output` を持ち、右オペランド型でオーバーロードできます）。

| 演算子 | トレイト | 脱糖 |
| --- | --- | --- |
| `+` | `Add[Rhs]` | `a.add(rhs: b)` |
| `-` | `Sub[Rhs]` | `a.sub(rhs: b)` |
| `*` | `Mul[Rhs]` | `a.mul(rhs: b)` |
| `/` | `Div[Rhs]` | `a.div(rhs: b)` |
| `%` | `Rem[Rhs]` | `a.rem(rhs: b)` |

冪乗 `**` は持ちません（`pow` メソッドで代替）。二項ビット演算 `&` / `^` / `|` / `<<` / `>>` と単項 `~`（`BitAnd` / `BitXor` / `BitOr` / `Shl` / `Shr` / `BitNot`）は、**演算子としての採用は決定済みですが実装は後回し**で、優先順位スロットだけ予約しています（→ [優先順位と結合性](#優先順位と結合性)）。

> **`/`・`%` の実行時意味**（Rust/Go/Swift に合わせる）：
> - **整数の 0 除算**（`a / 0`・`a % 0`）は **panic**（回復不能なトラップ。静かな値を返さない）。
> - **整数剰余 `%` は被除数の符号に従う**（truncated 除算。`-7 % 3 == -1`）。
> - **`%`（`Rem`）は整数型のみ**：浮動小数は `Rem` を実装せず `1.5 % 0.5` は**コンパイルエラー**（剰余が要るときは名前付きメソッド。Go/Swift に合わせる ── float の `%` は罠が多いため非提供）。
> - **浮動小数の除算**は IEEE 据え置きで `1.0 / 0.0` は `inf`（panic しない。→ [基本型](../01-basics/02-basic-types.md#浮動小数の実行時セマンティクスnan--inf)）。
> - 整数オーバーフロー（`I32.MIN / -1` 等）も **panic**（→ [整数の実行時セマンティクス](../01-basics/02-basic-types.md#整数の実行時セマンティクスオーバーフロー)）。

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
enum Ordering {
    Less
    Equal
    Greater
}

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

> 前置 `!`（`Not`）は eager（必ずオペランドを評価する値演算）なので、短絡する `&&`/`||` と違いトレイトのままです（`Bool` 専用の論理否定）。整数のビット反転は**別演算子** `~`（`BitNot`）で、二項ビット演算 `& ^ | << >>` ともども採用は決定済み・実装は後回しです（→ [優先順位と結合性](#優先順位と結合性)）。

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

前置 `-`（符号反転）は `Neg` トレイトのシンタックスシュガーです（`-x` ⟺ `x.neg()`）。

```plew
trait Neg {
    type Output
    fn neg() -> Output
}

impl I32 as Neg {
    type Output = I32

    fn neg() -> I32 {
        // 符号反転の実装
    }
}

val n: I32 = 5
val m = -n  // n.neg() と同等
```

- 符号付き整数（`I8`…`I64`）と浮動小数（`F32`/`F64`）が `Neg` を実装します。
- **符号なし整数（`U8`…`U64`）は `Neg` を実装しない**ので、`-x`（`x: U32` 等）は**コンパイルエラー**です（「演算子は実装トレイトのある型でのみ」の一般則どおり。静かなラップ値を返しません）。
- 二項の `-`（減算）は別トレイト `Sub` で、前置か中置かは構文位置で区別します。

> **負の数値リテラル**は `Neg` ではありません。`-128` のように数値リテラル直前にある `-` は[リテラルの一部](../01-basics/02-basic-types.md#リテラルの型付け多相文脈で確定)として畳み込まれ、リテラル全体で型範囲を検査します（`-128` は `I8` の最小値として有効。`(128).neg()` 経由だと `128` が `I8` に収まらず溢れてしまう）。`Neg` は変数・式に対する実行時の符号反転に使います。

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

### 添字代入（IndexSet）

`collection[key] = value` の添字**代入**は `IndexSet` トレイトの糖衣です。Rust の `IndexMut` 相当ですが、Plew は参照・借用を持たない（可変な場所を返せない）ので、**可変参照ではなくセッターメソッド**にします。

```plew
trait IndexSet[Key] {
    type Value
    mut fn index_set(key: Key, value: Value)
}

impl MyArray[T] as IndexSet[I32] {
    type Value = T

    mut fn index_set(key: I32, value: T) {
        // 要素設定の実装
    }
}

mut val array = <MyArray ... />
array[0] = x  // array.index_set(key: 0, value: x) と同等
```

- 読み取り（`Index`）と代入（`IndexSet`）は**独立したトレイト**で、読み取り専用コレクションは `Index` だけを実装できます。
- `collection[key] += x` などの複合代入は、**読み取り（`Index`）＋演算＋代入（`IndexSet`）**に展開されるので、両方の実装が要ります。
- レシーバ自身を書き換えるので `index_set` は `mut fn`。`mut val` な束縛にしか使えません。

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

## 優先順位と結合性

演算子の結合の強さ（番号が小さいほど強く＝先に結合する）と結合性は次の通りです。**`as`・算術・ビット・比較・`&&`/`||` の相対順は Rust と一致**します。Plew 固有の差は ① `??`（Rust に無く Swift と同位置）、② 前置 `try`/`await`（Rust の後置 `?` と逆）、③ 代入は文なので優先順位に乗らない、④ 単項の顔ぶれ（`~` を分離・deref/borrow なし）の 4 点だけです。

| 強さ | 演算子 | 結合性 | 状態 |
| --- | --- | --- | --- |
| 1（最強） | 後置：メンバ `.`／オプショナルチェーン `?.`／添字 `[]`／呼び出し `f()`／構造体生成 `<T/>` | 左（連鎖） | 現行 |
| 2 | 前置：`-`(Neg)・`!`(Not)・`~`(BitNot)／前置キーワード `try`・`await` | 前置（右） | `~` は予約 |
| 3 | `as`（キャスト） | 左 | 現行 |
| 4 | `* / %`（Mul/Div/Rem） | 左 | 現行 |
| 5 | `+ -`（Add/Sub） | 左 | 現行 |
| 6 | `<< >>`（Shl/Shr） | 左 | **予約（未提供）** |
| 7 | `&`（BitAnd） | 左 | **予約（未提供）** |
| 8 | `^`（BitXor） | 左 | **予約（未提供）** |
| 9 | `\|`（BitOr） | 左 | **予約（未提供）** |
| 10 | `??`（Coalesce） | 右 | 現行 |
| 11 | `== != < <= > >=`（Eq/Ord） | **非結合** | 現行 |
| 12 | `&&` | 左 | 現行 |
| 13 | `\|\|` | 左 | 現行 |
| 14（最弱） | `..< ..=`（レンジ） | **非結合** | 現行 |

### `as` は算術より強い（Lv3）

Plew は暗黙の数値拡幅を持たない（`I32`→`I64` も `x as I64` と明示）ので、`a as I64 + b as I64` が `(a as I64) + (b as I64)` と読まれるために `as` は算術より強い必要があります。Rust も暗黙拡幅が無く、同じ位置・同じ理由です。

### 前置 `try`/`await` は後置チェーン全体に掛かる

`try`/`await` は前置で、**直後の後置チェーン全体**を取ります：`try a().b()` は `try (a().b())`（`a().b()` を評価してから `try`）。Rust の後置 `?`（`a()?.b()` ＝ `(a()?).b()`）とは逆なので、**チェーン途中で取り出すには括弧**を使います：`(try a()).b()`。`try`/`await` は二項演算子より強く（`try f() + 1` ＝ `(try f()) + 1`、`try f() as I64` ＝ `(try f()) as I64`）、後置より弱い位置にあります。`try` の意味論は [エラーハンドリング](13-error-handling.md) を参照。

### `??` は Swift と同位置（Lv10・右結合）

`??` は算術・ビット・`as` より弱く、比較・`&&`・`||`・レンジより強い位置で、右結合（`a ?? b ?? c` ＝ `a ?? (b ?? c)`）です。これにより `x ?? 0 == y` ＝ `(x ?? 0) == y` と素直に読めます（JS / C# は `??` を比較より弱くする流儀ですが、Swift・Kotlin は本表と同じく比較より強くします）。

> **注意**：`??` は算術より弱いので `count ?? 0 + 1` は `count ?? (0 + 1)` になります（Swift・Kotlin・JS・C# すべてに共通の挙動）。フォールバックを得てから演算する意図なら括弧を付けてください：`(count ?? 0) + 1`。

なお Swift はレンジを `??` より強く置きますが、Plew はレンジを最下位にした（下記）ので `a ?? b ..< c` ＝ `(a ?? b) ..< c` です（`(start ?? 0)..<end` のように読め、実害はありません）。

### 比較・等価は非結合（Lv11）

`a < b < c` や `a == b == c` は**構文エラー**です。後者は `Bool` も `Eq` を持つため、左結合だと `(a == b) == c` が静かに通って「3 つが等しい」と誤読されます。明示の括弧を要求します（Rust の "Require parentheses" と同じ）。

### ビット演算子は予約（採用決定・実装は未了）

`& | ^ << >> ~` は `BitAnd` / `BitOr` / `BitXor` / `Shl` / `Shr` / `BitNot` トレイトの糖衣として将来提供します（演算子としての採用は決定済み・実装のみ後回し）。位置は **Rust と同じ「シフト ＞ `&` ＞ `^` ＞ `|`、いずれも比較より強い」**。これにより C の有名な罠 `x & 1 == 0` ＝ `x & (1 == 0)` を避け、`(x & 1) == 0` と読めます。シフトは加算より弱い（C/Rust と同じく `1 << 2 + 3` ＝ `1 << 5`）。Plew はジェネリクスを `[...]` で書くので `>>` がジェネリクス閉じと衝突せず、単一トークンにできます。論理否定 `!`（`Not`・`Bool` 専用）とビット反転 `~`（`BitNot`・整数）は別演算子です（Rust は `!` が両用）。

### レンジは非結合・最下位（Lv14）

`a..<b..<c` は構文エラーです。端点には算術が先に結合するので `0..<n + 1` ＝ `0..<(n + 1)`。位置は Rust に合わせて最下位にしています（レンジは `for … in`・`[]`・括弧内でしか現れず、端点が複合式でも括弧不要なため、低く置いても害がありません）。

### 代入は文

`= += -= *= /=` は式ではなく文なので、優先順位に乗りません（`if x = y` 型の取り違え事故が起きません）。複合代入（`+=` 等）の脱糖規則は別途規定します。
