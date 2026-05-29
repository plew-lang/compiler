# newtype（名目型）

既存の型と同じ表現・同じ実装を持ちながら、**型としては別物**として扱う名前付き型を `newtype` で宣言します。中身が同じ `String` でも `UserId` と `Email` を取り違えない、といった「プリミティブ強迫（primitive obsession）」の回避に使います。

```plew
newtype Meter = F64
newtype UserId = String
```

> Haskell の `newtype` と違い、Plew の `newtype` は**元の型の実装をそのまま引き継ぎ**、変換は `as` で行います（ラップ／アンラップ用のコンストラクタはありません）。

> underlying には[存在型](08-traits.md#トレイトを値の型として使う存在型-any) `any P` も置けます（`newtype Handler = any Drawable` など）。継承される表面は `any P` の制限付きメンバ集合（`Self` 入力メンバ・関連関数は呼べない）です。

## 実装の継承と Self 置換

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

継承された実装はコンパイラが合成するものです。**ユーザーが `newtype` に `impl` を書くことはできません**（[拡張](09-extensions.md) でも同様）。独自の振る舞いを足したい場合は構造体でラップします。

## 別の型としての扱いと as

`newtype` と元の型は別の型なので、代入・引数渡しには明示的な `as` キャストが必要です。両者は表現が同一なので、この `as` は**双方向・ゼロコストの再タグ**で必ず成功します（[From トレイト](../03-expressions/12-operators.md) による計算を伴う変換とは異なります）。

```plew
val d: Meter = 5.0 as Meter
val raw: F64 = d as F64
```

## 生成

`factory` は暗黙的に `Self` を返すため（[構造体と列挙型](05-structs-enums.md#インスタンス生成) 参照）、`newtype` は元の型の factory も継承します。したがって生成も他の型と同じく JSX 構文で行えます。[fallible factory](05-structs-enums.md#失敗し得るファクトリfallible-factory)（`optional`／`result[E]`）も継承され、`Self` 置換はラッパーの内側に効きます（`Result[Self, E]` → `Result[Brand, E]`・`Optional[Self]` → `Optional[Brand]`）。`From`／`TryFrom` も factory なので、`as` や `<Brand.convert from=… />` がそのまま使えます。

```plew
@[DefaultFactory(pub)]
struct Rgb { val code: I32 }

newtype Brand = Rgb

val c = <Brand code=255 />  // 継承した既定 factory（Self = Brand）
```

> トレイトの関連型や impl のメンバ型を表す `type X = Y` は別概念で、そちらは透過的な型束縛です（別型扱いも `as` も伴いません）。
