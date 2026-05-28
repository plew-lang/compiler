# 変数と値の管理

## 参照の値渡しと inout

Plew では全ての値の受け渡しは参照の値渡しで行われます。

```plew
fn immutable_function(param: MyStruct) {
    // param は不変 - フィールドの変更や可変メソッドの呼び出し不可
    param.some_field = new_value  // エラー
    param.mutate()  // エラー
}

fn mutable_function(inout param: MyStruct) {
    // param は可変 - フィールドの変更や可変メソッドの呼び出し可能
    param.some_field = new_value  // OK
    param.mutate()  // OK
}
```

`inout` 引数には、**呼び出し側でも `&` を付けて**「この呼び出しで変更され得る」ことを明示します（暗黙に書き換わらない）。`&` は `mut` な束縛にしか付けられません。

```plew
mut val account = <Account balance=0 />
mutable_function(param: &account)   // & 必須。account はこの後 変更され得る
```

## 変数宣言

```plew
val immutable_var: I32 = 0               // 不変変数（初期化必須）
mut val mutable_var: String = "initial"  // 可変変数

// 不変変数を可変変数に代入するにはclone()が必要
val immutable_data = <SomeStruct field=42 />
mut val mutable_data = immutable_data.clone()
```

- **宣言時に必ず初期化します**（未初期化宣言は持ちません）。分岐で初期値を決めたいときは式ブロックを使います：`val x: I32 = if flag { give 1 } else { give 2 }`。

### 再宣言（shadowing）

同名の `val`/`mut val` を**再宣言できます**（Rust と同じ・無制限）。再宣言は代入ではなく**新しい束縛**で、型も可変性も変えてよく、それ以降 `name` は**レキシカルに直近の宣言**を指します。外側スコープの名前を内側で覆う（shadowing）こともできます。

```plew
val config = load()                 // Optional[Config]
guard Optional.Some { value: val config } = config { panic "missing" }
// 以降 config は Config（元の Optional は退役）

val raw = read()                    // Bytes
val raw = parse(data: raw)          // ParsedData（同名で変換・型が変わる）
```

- **代入 `x = e` とは別物**：代入は既存の `mut` 束縛を同じ型で書き換える。再宣言 `val x = e` は新しい束縛を作る（`mut` 不要・型変更可）。
- `guard`/`match`/`if` のパターン束縛が同名で値を絞り込めるのは、この一般規則の帰結であって特別扱いではない（「絞り込みのときだけ同名可」という線引きは設けない）。
- 再宣言で覆って一度も読まれない前の束縛は、未使用束縛として診断（lint）で拾える（Rust 同様）。

## 代入と構造化代入

代入 `x = e` は既存の `mut` 束縛を書き換えます。分解では各要素を **`val name`（新しい束縛）** か **bare `name`（既存へ代入・要 `mut`）** で書き分け、混在もできます（`val`＝新規・bare＝既存は[再宣言](#再宣言shadowing)と同じ区別）。

```plew
// 基本代入（既存の mut 束縛）
variable = expression
variable += expression          // -=, *=, /= も同様

// ラベル付きタプルの分解（フィールド名で対応）
(val x, val y) = point          // x, y を新規宣言
(x, val y) = point              // x は既存へ代入（要 mut）・y は新規

// 構造体の分解（先頭に型名 → ブロックと曖昧にならない）
SomeStruct { val field1, val field2 } = some_struct       // punning（同名束縛）
SomeStruct { field1: val a, field2: val b } = some_struct // 別名

// 入れ子（不要フィールドは _ で破棄。全フィールドの明示が要る）
(name: val n, info: Person { name: _, val age }) = record
```

- 分解は**フィールド名で対応**します（位置ではない）。`(val x, val y)` は record の `x`/`y` を束縛し、書く順序は問いません。
- 文頭の `(` はラベル付きタプルの分解、型名始まりは構造体の分解、`{` 始まりは[ブロック](../03-expressions/11-control-flow.md)で、互いに曖昧になりません。
- **全フィールドを明示**します（束縛するか `_` で破棄）。未記載フィールドの暗黙無視も、残りを捨てる `..` もありません＝フィールド追加時に既存の分解がエラーになり取りこぼしを防ぎます。`_` は値を捨てる破棄パターンで `val` 不要、パターン位置ならどこでも書けます（詳細は → [パターンマッチング](../03-expressions/11-control-flow.md)）。
