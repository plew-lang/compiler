# Plew プログラミング言語仕様書

Plew は現代的なシステムプログラミング言語で、型安全性、非同期プログラミング、パターンマッチング、独自の拡張システムを重視して設計されています。シングルプロセス・シングルスレッドを基本とし、JavaScript ライクな非同期処理とガベージコレクションによるメモリ管理を採用しています。

本仕様書はトピックごとに `spec/` 配下へ分割されています。

## 目次

1. [概要・基本構文](spec/01-overview.md) — 概要、命名規則、キーワード、コメント
2. [型システム](spec/02-types.md) — プリミティブ型、文字列（不変・UTF-8・変数展開）、複合型（配列／辞書／ラベル付きタプル／レンジ）、構造体／列挙型／トレイト、フィールド統一原則、Optional／Result、インスタンス生成（JSX／factory）、newtype（名目型）、ジェネリクス、where 句
3. [変数と値の管理](spec/03-values.md) — 参照の値渡しと inout、変数宣言、再宣言（shadowing）、構造化代入
4. [関数とメソッド](spec/04-functions.md) — 関数宣言、引数ラベル、無名関数（クロージャ）、メソッドと impl、メソッドのオーバーロード、メンバの可視性
5. [トレイト](spec/05-traits.md) — トレイトの定義（要求・提供メソッド）、関連型、継承（supertrait）、準拠と via、標準トレイト（基本／変換／演算子）
6. [制御構造](spec/06-control-flow.md) — ブロックと give、条件分岐、条件チェーン（束縛つき条件）、パターンマッチング、ループ、ガード、panic
7. [型変換と演算子](spec/07-operators.md) — From トレイト、演算子システム、等価／順序（Eq／Ord）、論理結合子（&&／||）、オプショナルチェーン（Chain）、nil 合体（Coalesce）
8. [エラーハンドリング](spec/08-error-handling.md) — try 式
9. [非同期処理とメモリ管理](spec/09-concurrency.md) — async/await、spawn、チャネル、GC
10. [拡張システム](spec/10-extensions.md) — extension、`#` による拡張適用
11. [モジュールシステム](spec/11-modules.md) — import、export、part、パッケージ、extern
12. [メタプログラミング](spec/12-metaprogramming.md) — `@[...]` 組み込みディレクティブ、ユーザー定義メタプログラミング（方針転換中）
13. [サンプルコード](spec/13-examples.md)

---

この仕様書は Plew プログラミング言語の現在の設計を反映しています。
