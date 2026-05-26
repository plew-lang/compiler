# 制御構造

## ブロック式と give 文

ブロックを式として評価するには`give`文が必要です。

```plew
val result = {
    val temp = calculate_something()
    give temp * 2  // ブロックの戻り値
}

// エラー: give がないブロックは式として評価不可
val invalid = { 42 }  // コンパイルエラー
```

## 条件分岐

```plew
val result = if condition {
    give "true case"
} elif another_condition {
    give "elif case"
} else {
    give "else case"
}
```

## 条件チェーン（束縛つき条件）

`if`/`elif`/`while`/`guard` の条件は**条件チェーン**で、`&&` で連結した 1 つ以上の**節**からなります。各節は次のいずれか：

- **Bool 式** — 真なら成立。
- **反証可能束縛** `PATTERN = expr` — `expr` がパターンに一致すれば束縛して成立、しなければ不成立。

節は左→右に短絡評価され、ある節が不成立になった時点で残りは評価されず、チェーン全体が不成立になります。束縛節が導入した変数は、**後続の節とブロック本体**で有効です。

```plew
if Optional.Some { value: val flag } = optional && flag {
    // optional が Some で、かつ束縛した flag が真のときだけ実行
    // flag はここで使える
}

while Optional.Some { value: val line } = reader.next() && !line.is_empty() {
    process(line: line)
}
```

- 成立時に本体を実行するのが `if`/`elif`/`while`。**不成立時**に本体（発散必須）を実行するのが `guard`（下記）。
- **束縛節は `&&` でのみ連結できます**（`||` 不可）。`||` だと束縛が成立しない経路ができてスコープが壊れるためです。Bool 節の**内部**では `||` は自由に使えます（`if a && (b || c) { … }`）。
- 束縛の被検査式 `= expr` のあとの**トップレベル `&&`** が次の節を区切ります（被検査式自体に `&&` を含めたいなら括弧で囲む。ただし束縛の被検査式が Bool の連言になることは通常ありません）。Plew は[構造体生成が JSX 限定](../02-type-system/05-structs-enums.md)なので、本体の `{` と式を取り違える曖昧さは生じません。
- このヘッダの `&&` は[値レベルの `&&`](12-operators.md)（Bool 専用の短絡）と**同じ「短絡する連言」概念ですが、脱糖は別物**です（ヘッダの `&&` は束縛節も連結できる条件チェーン文法）。

## パターンマッチング

```plew
val result = match expression {
    42                                      => "the answer"
    Color.Red { intensity: val intensity }  => "red with intensity {intensity}"
    (val x, val y)                          => "record x={x}, y={y}"
    _                                       => "default case"
}
```

パターンの**束縛は `val`／`mut val` で明示**します（refutable な `match`/`if`/`while`/`guard` では、bare の名前は既存の値・リテラル・バリアントとの**マッチ**）。フィールド名と束縛名が同じなら **punning** で省略でき、`Color.Red { val intensity }` ≡ `Color.Red { intensity: val intensity }`、`(val x)` ≡ `(x: val x)` です。

アームの右辺は次の 3 形式：

- **ベア式** `=> expr` — その式の値をアームの結果にする。
- **ブロック** `=> { …; give x }` — 複数文のあと `give` で値を返す。
- **発散ブロック** `=> { … panic / return … }` — 値を生まず、任意の期待型と適合する（式全体の型は発散しないアームから決まる。後述「panic と発散」）。

## ループ

```plew
// 無限ループ（式として使用可能）
val result = loop {
    val data = get_data()
    if data.is_valid() { 
        break data.process()  // ループの戻り値
    }
    if should_retry() { continue }
    break <Error.Failed />  // エラー時の戻り値
}

// While ループ
while condition {
    // 処理
}

// For ループ（レンジ・分解対応。ループ変数は val で宣言）
for val i in 0..<n {
    // 0, 1, …, n-1（半開）。0..=n なら n まで含む
}

for (val key, val value) in dictionary {
    // 処理
}

for Person { val name, val age } in people {
    // 処理
}
```

- ループ変数は `val`／`mut val` で**新規宣言**します。bare 名にすると既存の `mut` 変数へ代入し、ループ後も生存します（`val`＝新規・bare＝既存。→ [値](../01-basics/03-values.md)）。
- **値を返せるのは `loop` だけ**：`loop { … break x }` は式として `x` を返します。`while`／`for` は値を持たず、`break` は**値なしの脱出のみ**（`break x` は不可）。ループ本体ブロックでは `give` も使えません（`give` は通常ブロックと `if`／`match` アーム専用）。ラベル付きループ・多重 `break` は持ちません。
- `for` が回すのは **`Iterable`**（`fn iterator() -> Iter` で毎回新しいカーソルを産む）で、`Array`・辞書・レンジ等が準拠します。実際に値を出すのは **`Iterator`**（`mut fn next() -> Optional[Item]` の消費カーソル）で、両者は別トレイト（コレクションは値意味論上「自分のカーソル」を持てず、多重走査もしたいため）。`Iterator` 自身も `Iterable`（自分を返す）なので iterator を直接 `for` できます。正確なシグネチャはイテレータ・プロトコル（未策定）で確定します。
- `for (val key, val value) in dict` は、辞書が要素 `(key: K, value: V)`（ラベル付きタプル）の `Iterator` を産み、それを分解しています。

## ガード文

条件が満たされない場合に早期リターンやブロック脱出を行います。条件は他の制御構文と同じ[条件チェーン](#条件チェーン束縛つき条件)（`&&` で Bool 節と反証可能束縛 `PATTERN = expr` を連結）で、束縛した変数は guard を抜けた後で使えます。

```plew
// 基本的な条件チェック
guard user.is_authenticated() && user.has_permission(name: "read") {
    return <Error.Unauthorized />
}
// ここに到達するのは guard 条件が true の場合のみ

// 列挙型のunwrapと変数代入
guard Result.Ok { value: val value } = some_result {
    return <Error.Failed />
}
// ここでは value が使用可能

// 複数の条件を組み合わせ
guard Optional.Some { value: val data } = maybe_data && data.is_valid() {
    return <Error.Invalid />
}
// ここでは data が使用可能
```

## panic と発散

`panic "メッセージ"` はプログラムを停止させる**文**です（`return`/`break` と同じく、その先へ進まない＝発散する制御フロー）。回復可能な失敗には使わず（それは `Result`/`try`）、**回復不能なバグ**を即座に・大きな声で落とすために使います。catch はできません。

```plew
guard Optional.Some { value: val config } = maybe_config {
    panic "config is missing"   // guard 本体は発散する必要がある → panic で満たす
}

val config = match maybe_config {
    Optional.Some { value: val v } => v
    Optional.None                  => { panic "config is missing" }  // 発散アーム
}
```

- メッセージは診断用の `String`（文字列展開可）。型付きの値は運ばない。
- **式ではない**ので、式の位置には置けない（`x ?? panic "..."` は不可 → `guard`/`match` を使う）。
- **発散規則**：全経路が `panic`/`return`/`break`/`continue` で抜けるブロックは値を生まないので `give` が不要で、`if`/`match` のアームなどで**任意の期待型と適合**する（式全体の型は発散しないアームから決まる）。
- `spawn` スレッド内の panic は**プロセス全体を停止**する。スレッド単位で扱いたい失敗は `Result` を返して `join()` 経由で受け取る（→ [非同期処理とメモリ管理](../04-execution/14-concurrency.md)）。
