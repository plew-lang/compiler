# 非同期処理とメモリ管理

Plew は JavaScript と同様の**シングルプロセス・シングルスレッド + イベントループ**を基盤とします。重い処理を別スレッドで動かしたいときだけ `spawn` でスレッドを立てます。メモリは **ARC（参照カウント）** で管理し、破棄は決定的（[`deinit`](../01-basics/03-values.md#deinit)）、循環は [`WeakRef`](../01-basics/03-values.md#ref--weakref共有可変) で断ち切ります。

> **用語**：本書は **`unique`／`local` の 2 マーカーを基準**に記述します。**「`unique` でない」＝コピー可能**（他言語でいう *Copyable*）、**「`local` でない」＝spawn 境界を越えられる**（他言語でいう *Sendable*）。*Copyable*／*Sendable* は概念の言い換えにすぎず**キーワードではありません** ── コードも本文も `unique`／`local` とその否定で表します。

## 基本的な非同期処理（async / await）

```plew
async fn fetch_data(url: String) -> Promise[Result[Data, Error]] {
    val response = await http_request(url: url)
    val data = await response.json()
    return <Result.Ok value=data />   // async fn の戻り値は Promise に自動ラップ
}

async fn main() {
    val data = await fetch_data(url: "https://api.example.com/data")
    print(message: "Received: {data}")
}
```

- **戻り型は `Promise[T]` と明示して書き**、本体の `return e`（`e: T`）はコンパイラが `Promise[T]` に包みます（TypeScript と同じ）。`await` はその `Promise[T]` を `T` に開きます。
- 戻り型を省略した `async fn`（`main` など）は、値を返さない `Promise` を返します。
- **`async` は単一スレッド上の協調的中断**で、別スレッドは起きません。所有権・借用は同期コードと同じに効きます（`unique` 値を await を跨いで保持してもよい）。

### async メソッドと self

`async fn` のメソッドは **self を借用できません**（借用は async 境界を越えられない＝`inout fn` の async 版は不可）。よって：

- **非消費の async メソッドは self をコピー**する（Self がコピー可能なときのみ）。＝Self がコピー可能必須で、generic struct なら型引数もコピー可能（[`allow_unique` でない](../02-type-system/06-generics.md)）。
- **消費する async メソッドは `async move fn`**（self を move）。
- **await を跨いで self を可変共有したいオブジェクトは `Ref` 裏打ち**にする ── `ref->async_mutate()` は `Ref` 越しに self を触り、`Ref` は async 境界を越えられる（単一スレッドでメモリ安全・interleave は JS 同様の論理ハザード）。ステートフルな async オブジェクトは Ref 裏打ち＝JS のオブジェクトと同じ姿。

### unique 結果と `allow_unique`（v1 は不可・将来）

v1 では **`Promise[T]`/`Thread[T]` を含むコアの generic 型はすべてコピー可能な型に限定**（`allow_unique` 未導入）。帰結：

- async/spawn は **unique 結果を返せない**（`-> Promise[unique]` 不可）。返すのはコピー可能な値か `Ref`。async で unique を持ち回るなら **`Ref` 包み**（`Ref` は async を越えられる）。
- **unique を generic に入れるのは常に `Ref` 包み**（`Optional[Ref[File]]`・`Array[Ref[File]]`）。`Ref` はコピー可能なので通常のコピー可能なコレクションになり、`match`/peek/反復が普通に効く（move-out 専用 API も `take()` も不要）。
- by-value の unique を generic で扱う（`Optional[unique]`・`Promise[unique]`・`Array[unique]`）には **借用束縛＝ライフタイム**が要り（要素を取り出さず借用で覗く操作のため）、v1 の非 escape 借用では実装できない。**`allow_unique` は将来の additive**（保持系＝Optional/Promise が先・Array/Iterable は escaping borrow 導入後）。それまでは `Ref` 包みで代替。

## メモリ管理（ARC）

- **ARC（参照カウント）で管理**：スコープを抜けて最後の所有者／`Ref` が消えると**即座に**解放され、`deinit` が走る（決定的破棄＝ファイル・ソケット等の資源解放に使える）。
- **循環は `WeakRef` で**：参照カウントは循環を回収しないので、親子の逆リンク等は `WeakRef` で断ち切る。
- 値意味論なので、共有された可変状態は `Ref` 経由のみ生まれる（→ [値・変数・所有権](../01-basics/03-values.md)）。

## 境界を越えるもの（move / copy / Ref / 借用）

`async` と `spawn` は性質が違い、値が境界を越えられるかが変わります。

| 渡すもの | async（単一スレッド） | spawn（実スレッド） |
| --- | --- | --- |
| 値（コピー可能） | ○ コピー | ○ コピー（スナップショット） |
| `unique` 値 | ○ `move` | ○ `move`（所有を移す） |
| `Ref[T]` | ○（共有・メモリ安全） | ✗（共有可変＋非 atomic 参照カウント＝競合） |
| 借用 `borrow`/`inout` | ✗ | ✗ |

畳むと **2 つの規則**：

- **借用は同期専用 ── どの境界も越えない**。`async`/`spawn` 関数の引数に `borrow`/`inout` は使えません（指す先のライフタイムが境界をまたぐ複雑さ＝Rust の async 借用問題を避けるため）。越えたいときは **`move`（必要なら戻り値で返す round-trip）・コピー・`Ref`** を使う。
  - 帰結：`Promise.all([f(x: move a), f(x: move a)])` は **2 度目の `move a` が use-after-move でエラー**になり、並行な可変アクセスの footgun が単純な move 追跡で弾ける（借用ライフタイム追跡は不要）。
- **`Ref` は async は越えられるが spawn は越えられない**。async は単一スレッドなので共有してもメモリ安全（ただし await を跨ぐ interleave は JS 同様の**論理ハザード**＝プログラマ責任）。spawn は実スレッドで、`Ref` の共有は **データ競合＋非 atomic な参照カウント破壊**になるため不可。

## spawn — スレッドの起動

`spawn { … }` は新スレッドを起動してブロックをそこで実行します（起動したスレッド自身もシングルスレッド + イベントループ＝Web Worker 的に内部で `async`/`await` 可）。

```plew
val n = 100                                  // コピー可能
val handle = spawn { give heavy(input: n) }  // n は暗黙コピーでキャプチャ
val result = await handle.join()             // 完了を待って結果（Thread[T]・型名暫定）
spawn { background() }                        // 束縛しなければ detached
```

- **ベアの `spawn { }` のキャプチャはコピー可能のみ（暗黙コピー＝スナップショット）**。`borrow`/`inout`・`Ref`・`local` を触れば**コンパイルエラー**（経路を示す）。**`unique` のキャプチャもエラー**（ブロックへ move する構文は当面持たない＝additive）。
- **`unique` をスレッドへ渡すには `spawn fn`**（下記）の `move` 引数を使う。
- **戻りはハンドル構造体**：`join() -> Promise[T]` を持つ（暫定 `Thread[T]`）。`await handle.join()` で結果。**ランタイムは全スレッド完了まで生存**してから終了する（Go の「main 終了で goroutine kill」footgun を避ける）。
- **`spawn` 内 `panic` はプロセス全体を停止**する。スレッド単位で扱いたい失敗は `Result` を返して `join()` で受け取る。

### spawn fn — 引数で値を渡してスレッド起動

`unique` を含む値をスレッドへ明示的に渡すには、`async fn` と平行な宣言形 **`spawn fn`** を使う（キャプチャでなく**引数**で境界を越える）。

```plew
spawn fn worker(input: move Data) -> Thread[Report] {   // input を move でスレッドへ
    return analyze(input: input)                         // 戻り値は Thread に自動ラップ
}
val handle = worker(input: move data)                    // 呼び出しがスレッドを起動
val report = await handle.join()
```

- `spawn fn g(...) -> Thread[T]` は呼ぶとスレッドを起動しハンドルを返す（`async fn ... -> Promise[T]` と平行・本体の `return e` を `Thread[T]` に自動ラップ）。**宣言された fn はキャプチャを持たず引数だけ**＝何が境界を越えるか完全に明示。
- 引数は `move`（unique・所有移動）／copy（コピー可能）。`borrow`/`inout`・`Ref`/`local` は渡せない（境界規則どおり）。

## local（spawn を越えられない型）

**spawn 境界を越えられるのは `local` でない値だけ**です（「`local` でない」＝**推移的に `Ref` を含まない**）。

- **`local struct`**（→ [値・変数・所有権](../01-basics/03-values.md)）は `Ref`（や他の `local` 型）をフィールドに持つ型。`Ref` 自体も `local`。**`local` な値は spawn 境界を越えられない**。
- spawn のキャプチャ／チャネルで送る値は **`local` でないこと**。違反は**そのキャプチャ／送信地点でコンパイルエラー**（原因の `Ref` への経路を示す）。
- ジェネリックで spawn するときは `[no_local T]` で T を **`local` でないもの**に制約する（→ [ジェネリクス](../02-type-system/06-generics.md)）。
- async（単一スレッド）では `local`/`Ref` も自由＝この制約は **spawn 境界だけ**に効く。

## チャネル

スレッド間で値を送るにはチャネルを使います（「共有」ではなく「送信」＝*share memory by communicating*）。**具体的な型・API はコアライブラリ送り**ですが、モデルは確定しています：

- チャネルは**スレッド安全なプリミティブ**で、`Sender`/`Receiver` ハンドルは `local` でない（`Ref` と違い内部が atomic なので spawn を越えられる）。
- **送る値は `local` でないこと**（move/copy で渡る・`Ref` は送れない）。これで送信経由でもスレッド間に共有可変が生まれず race-free を保つ。
- 方針は**複数 Sender**。所有権で「Receiver は単一所有」を強制はしない（複数箇所が持て、`receive()` も複数回呼べる）。`receive() -> Result[T, ChannelClosed]` 方向。マルチコンシューマの意味論は core-lib 設計で詰める。

## 並行安全性 ── 実質 race-free

Plew は次を保証します：

- **スレッド間に共有可変状態が存在しない**：spawn は値の送信のみ（借用・`Ref` は越えない）。よって**データ競合が原理的に起きず、UB も無い**。`Mutex` / `sync val` も不要。
- **唯一の注意は async の interleave**：単一スレッドで 1 つの `Ref` を複数の async タスクが触ると、await を跨いで状態が割り込まれ得る（**メモリ安全だが論理ハザード**＝JS の共有オブジェクトと同じ・プログラマ責任）。
- どうしてもスレッド間で可変共有したい稀なケースは、atomic 参照カウントの thread-safe 共有型（Rust の `Arc`/`Mutex` 相当）を **additive** に後付けする想定。大半はチャネルで足りる。
