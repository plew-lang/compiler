# ジェネリクス

基本的に Rust と同様に不変（invariant）です。型パラメータは `[...]` で宣言します。

```plew
struct Container[T] {
    val value: T
}

fn process[T](container: Container[T]) where T: Display {
    // 処理
}
```

**型パラメータの `[...]` には名前だけを並べます**（`[T]`・`[T, U]`）。制約はインラインに書かず、すべて [`where` 句](#where-句)に集約します（`fn`・`struct`・`enum`・`trait`・`impl` で共通）。

## impl の型パラメータ

`impl` 自身が導入する型パラメータは、型名の前に **`impl[...]`** で宣言します（`fn f[...]` と同形）。`impl[T]` で束縛した名前を、self 型・トレイト・`where` の中で**使います**。

```plew
impl[T] Container[T] { /* … */ }                        // self が generic（inherent）
impl[T] Container[T] as Drawable where T: Display { }    // 条件付き準拠
impl[T] Vector as Mul[T] where T: Scalar { }             // T はトレイト引数だけに現れる
impl Container[I32] as SomeTrait { }                     // 具体インスタンス化（バインダなし）
impl Celsius { /* … */ }                                 // 非ジェネリックはブラケット不要
```

- `impl[T]`（束縛）と `Container[T]`（使用）を分けるので、`impl Container[I32]`（具体型に対する実装）と曖昧になりません。
- 型パラメータがトレイト引数・`where`・メソッドにしか現れない場合も、`impl[...]` が置き場になります（self 型のブラケットに頼らない）。

## Where 句

型パラメータへの制約を表現します。各述語は **`型: 制約`** の形です（`T: Clone + Display`、関連型射影への制約 `T.Item: Display` も書けます）。

```plew
fn func[T](param: T) where T: Clone + Display {
    // 処理
}
```

- **特定の具体型に対する実装は型の位置に直接書きます** — `impl MyStruct[I32] as SomeTrait { }`（`where T = I32` のような型等価述語は持ちません）。
- 関連型を特定の型に束ねるのは `where` の述語ではなく、**トレイト名の `[...]` 内の関連型束縛**です（`T: Iterator[Item = I32]`。→ [トレイト](08-traits.md)）。
