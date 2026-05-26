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

## 変数宣言

```plew
val immutable_var: I32  // 不変変数
mut val mutable_var: String = "initial"  // 可変変数

// 不変変数を可変変数に代入するにはclone()が必要
val immutable_data = <SomeStruct field=42 />
mut val mutable_data = immutable_data.clone()
```

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

```plew
// 基本代入
variable = expression
variable += expression
variable -= expression
variable *= expression
variable /= expression

// タプルの構造化代入
(a, b, c) = some_tuple

// 構造体の構造化代入（先頭に型名を置く）
SomeStruct { field1: x, field2: y } = some_struct

// 複合的な構造化代入
(first, Person { name: person_name, age: person_age }) = complex_data
```
