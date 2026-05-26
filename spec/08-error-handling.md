# エラーハンドリング

## try 式 - Rust の?演算子相当

`try`は特別なエラーハンドリングではなく、Result 型の早期リターンのシンタックスシュガーです。

```plew
fn parse_and_process(input: String) -> Result[I32, String] {
    val number: I32 = try parse_int(text: input)  // エラー時は早期リターン
    val processed = number * 2
    return <Result.Ok value=processed />
}

// エラー型の変換（From トレイト実装時）
fn complex_operation() -> Result[Data, GeneralError] {
    val result1: Result[I32, ParseError] = try_parse()
    val value = try result1  // ParseError → GeneralError に自動変換
    // 処理続行
}
```

`try` は、`expr` のエラー型 `F` が関数の戻りエラー型 `E` と違う場合、Err 時に `E.from(x: f)` を挿入して変換します（Rust の `?`＝`From::from` と同じ）。ターゲット `E` は関数シグネチャから既知なので、`GeneralError` が複数のソースエラーから変換可能（`From[ParseError]`・`From[IoError]` …）でも、ソース型でオーバーロード解決されます（→ [型変換と From トレイト](07-operators.md)）。`E == F` のときは変換不要でそのまま伝播します。

```plew
impl GeneralError as From[ParseError] {
    assoc fn from(x: ParseError) -> GeneralError { /* ... */ }
}
impl GeneralError as From[IoError] {
    assoc fn from(x: IoError) -> GeneralError { /* ... */ }
}
```

集約エラー enum（各ソースエラーを variant で保持する型）では、こうした variant ラップの `From` 実装を**メタプログラミングで自動生成**でき、手書きは不要です（Rust の `thiserror` 相当）。`try` 側の機構は単一の `From` のまま、boilerplate だけを生成で消します（→ [メタプログラミング](12-metaprogramming.md)）。

## force-unwrap は持たない

`Optional` / `Result` から中身を強制的に取り出す**後置演算子（`!` のような force-unwrap）は提供しません**。取り出しは `Optional` / `Result` の `unwrap` メソッドで行いますが、空・エラー時に実行時エラーとなるため**基本的に非推奨**です。通常は `match` / `guard` / `?.` / `??` / `try` で分岐・伝播してください。

```plew
val v = maybe_value.unwrap()  // 空なら実行時エラー。基本は使わない
```
