# 標準的なトレイトとその用途

## 基本トレイト

- `Clone`: オブジェクトの複製
- `Hash`: ハッシュ値計算
- `Display`: 表示用フォーマット
- `Format`: 変数展開用フォーマット

> トレイトは**型引数を持てます**が、その有無は「両辺が別型になり得るか」で決まります（下記）。impl が一意に決める出力は関連型 `type Output`。複数 conformance のメソッドは引数型で区別される[オーバーロード](04-functions.md)になります。

## 変換トレイト

- `From[Source]`: 型変換。`x as T` は `T.from(x: x)` の糖衣で、`try` のエラー変換にも使う。1 つの型が複数ソースに準拠可（`From[I32]`・`From[String]` …）。例外として newtype と元型の `as` は From でなくゼロコスト再タグ（→ [型変換と演算子](08-operators.md)）。

## 演算子トレイト

演算子は対応トレイトのメソッドの糖衣です（`!` も含む）。**ただし論理結合子 `&&` / `||` は短絡する制御フローで、トレイトではありません**（`if` の糖衣 → [型変換と演算子](08-operators.md)）。型引数の有無は **両辺が別型になり得るか**で決まります：

- **算術（別型を結ぶ）— `[Rhs]` あり**：`Add[Rhs]`, `Sub[Rhs]`, `Mul[Rhs]`, `Div[Rhs]`。右オペランド型で複数 conformance 可（`Vector as Mul[Vector]` と `Mul[F64]`）。結果型は関連型 `type Output`。
- **等価・順序（同一型上の関係）— 型引数なし**：`Eq { fn eq(rhs: Self) -> Bool }`（`==`/`!=`。`!=` は `!(==)`。`@[Eq]` で derive）、`Ord: Eq { fn compare(rhs: Self) -> Ordering }`（`< <= > >=` は `compare` に展開）。右辺は常に `Self`（異種比較は対称・反射律を壊すので持たない）。`F32`/`F64` も準拠するが NaN 比較で panic。
- **単項 — `Not`**：論理否定 `!`（eager）。`type Output`。
- **添字 — `Index[Key]`**：`collection[key]`。`type Output`。

## オプショナル関連トレイト

- `Chain`: オプショナルチェーン（`receiver?.member`）。値か空かに分解する `chain()` と、再構築用の `from_value` / `empty` を持つ
- `Coalesce[Rhs]`: nil 合体演算子（`??`）。左辺が空のとき右辺へフォールバックする。`type Output`
