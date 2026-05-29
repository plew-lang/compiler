# コンパイラ アーキテクチャ

Plew コンパイラ（`PlewCompiler`）の実装方針。**現状はスキャフォールド段階**（`Program.cs` が Hello World のみ）であり、本書はこれから組み立てるパイプラインの設計を示す。

## ゴール

- **ターゲット: LLVM-IR**。生成した IR を `llc` → `clang`（あるいは LLVM API）でネイティブバイナリへ。WASM も将来ターゲット。
- **最終的にセルフホスティング**したい。パフォーマンスは二の次、開発しやすさが最優先（macOS で動けば十分）。
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
  │   5. @[...] 組み込みディレクティブ展開（Eq/Hash/Clone/… を AST 変換で合成）
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
- **ARC（参照カウント）**: 循環は `WeakRef` で断ち切る（循環コレクタの要否・方式はランタイム実装時に決定・未定）。単一スレッド + イベントループ前提＋spawn は値の送信のみなので、並行のメモリ安全性問題は最小。

## ビルド/実行

`dotnet build` / `dotnet run` で C# コンパイラ自体をビルド・実行する。ANTLR パーサ生成の手順は [grammar.md](grammar.md) を参照。サンプルプログラムは `examples/*.pw`。
