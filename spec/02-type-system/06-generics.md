# ジェネリクス

基本的に Rust と同様に不変（invariant）です。型パラメータは `[...]` で宣言します。

```plew
struct Container[T] {
    val value: T
}

fn process[T](container: Container[T]) where T: Format {
    // 処理
}
```

**型パラメータの `[...]` には名前だけを並べます**（`[T]`・`[T, U]`）。制約はインラインに書かず、すべて [`where` 句](#where-句)に集約します（`fn`・`struct`・`enum`・`trait`・`impl` で共通）。

## impl の型パラメータ

`impl` 自身が導入する型パラメータは、型名の前に **`impl[...]`** で宣言します（`fn f[...]` と同形）。`impl[T]` で束縛した名前を、self 型・トレイト・`where` の中で**使います**。

```plew
impl[T] Container[T] { /* … */ }                        // self が generic（inherent）
impl[T] Container[T] as Drawable where T: Format { }    // 条件付き準拠
impl[T] Vector as Mul[T] where T: Scalar { }             // T はトレイト引数だけに現れる
impl Container[I32] as SomeTrait { }                     // 具体インスタンス化（バインダなし）
impl Celsius { /* … */ }                                 // 非ジェネリックはブラケット不要
```

- `impl[T]`（束縛）と `Container[T]`（使用）を分けるので、`impl Container[I32]`（具体型に対する実装）と曖昧になりません。
- 型パラメータがトレイト引数・`where`・メソッドにしか現れない場合も、`impl[...]` が置き場になります（self 型のブラケットに頼らない）。

## 呼び出し位置での型引数の明示

通常は型引数を**推論**しますが、推論が効かないときは呼び出し位置でも `name[TypeArgs](args)` と明示できます。

```plew
val n = parse[I32](text: input)   // 型引数 I32 を明示
```

ブラケットの中身が**型なら型引数の適用、値なら[添字アクセス](../03-expressions/12-operators.md)**として解釈します（Go と同じ判別）。型は PascalCase・値（変数）は snake_case なので、`f[I32](…)`（型引数）と `arr[i]`（添字）は衝突しません。

## Where 句

型パラメータへの制約を表現します。各述語は **`型: 制約`** の形です（`T: Clone + Format`、関連型射影への制約 `T.Item: Format` も書けます）。

```plew
fn func[T](param: T) where T: Clone + Format {
    // 処理
}
```

- **特定の具体型に対する実装は型の位置に直接書きます** — `impl MyStruct[I32] as SomeTrait { }`（`where T = I32` のような型等価述語は持ちません）。
- 関連型を特定の型に束ねるのは `where` の述語ではなく、**トレイト名の `[...]` 内の関連型束縛**です（`T: Iterator[Item = I32]`。→ [トレイト](08-traits.md)）。
