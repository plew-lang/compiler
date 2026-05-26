# 非同期処理とメモリ管理

Plew は JavaScript と同様の**シングルプロセス・シングルスレッド + イベントループ**モデルを基盤とします。重い処理を別スレッドで動かしたいときだけ `spawn` でスレッドを立ち上げます。

## 基本的な非同期処理

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

## spawn — スレッドの起動

`spawn { … }` は新しいスレッドを起動してブロックをそこで実行します。基盤と同じく**起動したスレッド自身もシングルスレッド + イベントループ**（Web Worker 的に、内部で `async`/`await` を使えます）。

```plew
val handle = spawn { give heavy_computation() }   // Thread[I32]（型名は暫定）
val result = await handle.join()                   // 完了を待って結果 I32 を得る

spawn { background_task() }                         // ハンドルを束縛しなければ detached
```

- **戻り値はハンドル構造体**：ブロックの結果型 `T` に対し **`join() -> Promise[T]`** を持つ構造体（暫定 `Thread[T]`）。`join()` は Promise を返し、`await` で結果を得る ── イベントループを素朴にブロックせず、待機中はループへ譲る（async/await と同じ機構でスレッド完了を観測する）。
- **`spawn` の主な用途は「重い処理の結果を別スレッドで計算して受け取る」**こと。その値の受け取りは `await handle.join()` が標準。継続的な値のストリームにはチャネルを使う。
- **detached**：ハンドルを束縛しなければ join できないだけで、スレッドはブロックを最後まで実行する（スレッド側から見て detached か否かは不可視）。結果 `T` は誰も `join()` しなければ捨てられる。ハンドルは**スレッドを所有しない**（未束縛/GC されてもスレッドは死なない）。**ランタイムは全スレッドの完了まで生存し**、その後プログラムを終了する（保留中の仕事を黙って切らない。JS のイベントループの自然な延長）。
- **キャプチャは全て immutable（例外なし）**：spawn ブロックが外側からキャプチャした値は、元が `mut` でも spawn 内では不変。**これがデータ競合を防ぐ唯一の保証**。チャネルの `Sender` も immutable にキャプチャされる ── 例外ではない。
- **やり取りは「共有」ではなく「送信」**（"share memory by communicating"）。可変状態を共有するのではなく、immutable な `Sender` の **`send`（immutable メソッド）**で値を送る（実際のバッファ操作はチャネル内部＝コアの責務で、公開インターフェースは immutable）。`Mutex` / `sync val` は標準で提供しません。

## チャネル

スレッド間で値を送るにはチャネルを使います。**具体的な型・構文はコアライブラリの実装で定めます**（言語コアの構文要素ではなく、ライブラリ API）。設計上の論点：

- 方針は複数 Sender だが、**Plew は所有権が無いので Rust のように「Receiver は単一所有」を強制できない** ── `Receiver` も参照の値渡しで複数箇所が持て、`receive()` も複数回呼べる。マルチコンシューマの意味論（競合 vs ファンアウト等）はコアライブラリ設計で詰める。
- `send` は immutable メソッド（上記）。`recv()` は `Result[T, ChannelClosed]` を返す方向。

## メモリ管理

Plew はガベージコレクションを採用しており、基本的にメモリ管理を気にする必要はありません。シングルプロセス・シングルスレッドのため、メモリ安全性の問題も最小限です。

ただし、`spawn`ブロック使用時のみ、キャプチャされた値の可変性制限により競合状態を防止しています。
