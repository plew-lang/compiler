# コンパイラ アーキテクチャ

Plew コンパイラ（`PlewCompiler`）の実装方針。**現状はスキャフォールド段階**（`Program.cs` が Hello World のみ）であり、本書はこれから組み立てるパイプラインの設計を示す。

## ゴール

- **ターゲット: LLVM-IR**。生成した IR を `llc` → `clang`（あるいは LLVM API）でネイティブバイナリへ。WASM も将来ターゲット。
- **最終的にセルフホスティング**したい。パフォーマンスは二の次（設計の拠り所＝「意味は唱えた通り・難しい魔法は隠す」を優先・hidden cost は許容）。macOS で動けば十分。
- **メモリ管理は ARC（参照カウント）**。既定は値意味論（CoW）で、opt-in の最小所有権（`unique`/`borrow`/`inout`/`move`・`Ref`/`WeakRef`）のみ。全面的な所有権・ライフタイムは不採用（→ [language-semantics.md](language-semantics.md)、[design-decisions.md](design-decisions.md)）。

## 技術スタック

| 役割 | 採用 | 備考 |
| --- | --- | --- |
| 実装言語 | C# / .NET 8 | `PlewCompiler.csproj`。SDK は 10 系だが `TargetFramework` は `net8.0` |
| 字句・構文解析 | ANTLR4（C# 公式ランタイム） | 文法は `grammer/Plew.g4`。→ [grammar.md](grammar.md) |
| コード生成 | LLVMSharp（予定） | LLVM C API の .NET バインディング。LLVM 本体バージョンとの同期に注意 |

選定の経緯は `note/ChatGPT-言語選定の相談.md` を参照（TypeScript が当初有力だったが LLVM バインディングが非公式・断片的なため C# + LLVMSharp に決定）。

> いずれの NuGet パッケージ（`Antlr4.Runtime.Standard`, `LLVMSharp` / `libLLVM`）もまだ `.csproj` に追加されていない。最初の実装ステップで追加する。

## コンパイルパイプライン（設計）

```
.pw ソース
  │  ANTLR4 Lexer/Parser（Plew.g4 から生成）
  ▼
Parse Tree（ANTLR）
  │  AST builder（Visitor で自前 AST へ変換）
  ▼
AST
  │  セマンティック解析
  │   1. 名前解決（モジュール / import / スコープ）
  │   2. 型推論・型検査（ジェネリクス、where 句）
  │   3. trait/impl 解決・拡張解決（#Extension）
  │   4. 並行性検査（spawn キャプチャの immutable 化）
  │   5. @[...] 組み込みディレクティブ展開（Eq/Hash/Encode/… を AST 変換で合成）
  ▼
型付き AST / IR（中間表現）
  │  LLVMSharp で LLVM-IR を構築
  ▼
LLVM-IR
  │  llc → clang（ネイティブ） / WASM バックエンド
  ▼
実行バイナリ
```

### 各フェーズの実装メモ

- **AST builder**: ANTLR の Parse Tree を直接歩くのではなく、自前の AST ノードに落としてから解析する。`@[...]` 組み込みディレクティブは AST ノードに属性リストとして保持し、専用フェーズで変換する。ユーザー定義メタプログラミングはこれとは別方式（ビルドと独立した別コマンドで別ファイルへコード生成）へ転換した。→ [design-decisions.md](design-decisions.md) / [spec/04-execution/16-metaprogramming.md](../spec/04-execution/16-metaprogramming.md)。
- **拡張解決（最重要）**: メソッド/演算子のバインドは「呼び出し位置の `#Extension` 指定」だけで決定論的に決める。import スコープに依存させない。無名（デフォルト）`impl` はそのまま発動、`extension Name { impl … }` は `#Name` で明示指定された時のみ発動。一意に定まらなければコンパイルエラー。詳細は [language-semantics.md](language-semantics.md)。
- **並行性検査**: `spawn { … }` のキャプチャはコピー可能のみ（コピー＝スナップショット）、`unique` を渡すなら `spawn fn` の `move` 引数。**借用は async/spawn 境界を越えず、`Ref`/`local` 型は spawn を越えられない**（推移的に `Ref`-free＝`local` でないことを検査）。よってスレッド間に共有可変が無く実質 race-free（Mutex 不要）。`spawn` の戻りは `join() -> Promise[T]` のハンドルで、ランタイムは全スレッド完了まで生存。
  - **codegen の責務（CoW × spawn）**: `Array`/`String`/`Dictionary` 等の CoW 値は内部バッファを**非 atomic** refcount で共有するので、**spawn 境界を越えるコピー可能値には eager な実体化（ディープコピー）を挿入**し、スレッド間でバッファ＝refcount を共有させない（async 境界では遅延のまま）。これで `Ref` だけでなく CoW バッファも非 atomic count を 2 スレッドから触られず、全面 atomic ARC を避けられる → [spec/14](../spec/04-execution/14-concurrency.md#cow-値は-spawn-境界で実体化するeager-copy)。
  - **クロージャ変換（capture）**: 通常の閉包は外側変数を**参照キャプチャ**（`mut val` は可変・共有・永続）。**脱出する閉包がキャプチャした変数はヒープへ昇格（box 化）**して閉包の生存に合わせる。`mut val` を参照キャプチャした閉包は**共有可変ストレージを持つ＝`local` 扱いで spawn 不可**（spawn 閉包は copy/move キャプチャのみ）。`val` キャプチャは読み取り専用。→ [spec/04 環境のキャプチャ](../spec/01-basics/04-functions.md#環境のキャプチャ)。
- **ARC（参照カウント）**: 循環は `WeakRef` で断ち切る。循環の自動回収は **Ref グラフ限定のサイクルコレクタ**（Bacon–Rajan・per-thread・idle 実行）を additive に足す方向で確定（v1 は手動 `WeakRef`＋dev 時リークレポータ・実装時に頻度/順序の細目を詰める → [design-decisions「循環回収」](design-decisions.md)）。単一スレッド + イベントループ前提（ターン間がセーフポイント）＋spawn は値の送信のみ（`Ref` は非 atomic・スレッドローカル）なので、並行のメモリ安全性問題もコレクタの並行協調も最小。
- **再帰的な値型の自動箱化（codegen）**: 自己参照する `struct`/`enum`（木・連結リスト・AST）はサイズが無限になるので、**コンパイラが再帰を検出し必要なフィールドを CoW ヒープセルで自動箱化**してレイアウトを有限化する（Array/String と同じ機構の再利用・`indirect` 等の修飾語なし・フィールド型と値意味論は書いた通り・間接箇所はコンパイラが選ぶ）。値意味論の再帰型は循環を作れないので `WeakRef` 不要 → [spec/05 再帰的な値型](../spec/02-type-system/05-structs-enums.md#再帰的な値型)。
- **トップレベル/`assoc val` 初期化（runtime）**: 起動時 **eager**（`main` 前に全完了）。各トップレベル値は **memoize されたサンク**（未初期化/初期化中/初期化済み）で、起動時に force-on-read で **依存順を自動算出**（静的依存解析なし）。**循環はコンパイル時でなく起動時の panic**（async ではデッドロック検出）。**トップレベルはイベントループ上の async コンテキスト**＝top-level await 可・並行起動（`Promise.all` 相当）。同期プログラム（await 皆無）は従来の同期 before-main と同挙動 → [spec/15 トップレベル初期化](../spec/04-execution/15-modules.md#トップレベル初期化と実行順序)。
- **実行エントリ／ランタイム寿命（runtime）**: 開始点は **`fn main`／`async fn main`**。実行は ①全トップレベル/`assoc val` 初期化 → ②`main` 呼び出し。戻り `Result[(), E]` の `Err` は表示して非ゼロ終了（`Termination` 相当の lang トレイト）。args/env は仮引数でなく stdlib `Process`（import 要）。**終了条件＝`main` 返却 ＋ イベントループ drain**（保留タスク・タイマ・登録リスナ・未 join の spawn スレッドが無い＝Node/ブラウザ流）。エントリ選択はビルド時のファイル明示＋その `main`（探索なし・複数エントリ可）→ [spec/15 実行エントリ](../spec/04-execution/15-modules.md#実行エントリmain)。
- **panic は abort（codegen）**: `panic` はスタックを巻き戻さず **trap 一発**でプロセス停止。**`deinit` は走らない**・unwind テーブル/landing pad を吐かない（Rust `panic="abort"` 相当）。`deinit` の決定的解放は正常終了パスのみ → [spec/11 panic と発散](../spec/03-expressions/11-control-flow.md#panic-と発散)。
- **引数ラベルのコード生成**: セレクタ＝名前＋順序付きラベル列。**ラベル抑制 `name~:`** は無ラベル位置（呼び出しは位置渡し・`factory` では不可）。関数型はラベルを型同一性に含む（サブタイプ/暗黙変換なし・無ラベル位置は裸の型）→ [spec/04](../spec/01-basics/04-functions.md#ラベルの抑制)。

## ビルド/実行

`dotnet build` / `dotnet run` で C# コンパイラ自体をビルド・実行する。ANTLR パーサ生成の手順は [grammar.md](grammar.md) を参照。サンプルプログラムは `examples/*.pw`。
