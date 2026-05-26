# Plew プログラミング言語仕様書

Plew は現代的なシステムプログラミング言語で、型安全性、非同期プログラミング、パターンマッチング、独自の拡張システムを重視して設計されています。シングルプロセス・シングルスレッドを基本とし、JavaScript ライクな非同期処理とガベージコレクションによるメモリ管理を採用しています。

本仕様書はトピックごとに `spec/` 配下へ分割されています。

## 目次

1. [概要・基本構文](spec/01-overview.md) — 概要、命名規則、キーワード、コメント
2. [型システム](spec/02-types.md) — プリミティブ型、文字列展開、複合型、構造体／列挙型／トレイト、フィールド統一原則、Optional／Result、newtype（名目型）、ジェネリクス、where 句
3. [変数と値の管理](spec/03-values.md) — 参照の値渡しと inout、変数宣言、構造化代入
4. [関数とインスタンス生成](spec/04-functions.md) — 関数宣言、引数ラベル、無名関数（クロージャ）、メソッドと impl、via、factory／インスタンス生成
5. [制御構造](spec/05-control-flow.md) — ブロックと give、条件分岐、パターンマッチング、ループ、ガード
6. [非同期処理とメモリ管理](spec/06-concurrency.md) — async/await、spawn、GC
7. [エラーハンドリング](spec/07-error-handling.md) — try 式
8. [型変換と演算子](spec/08-operators.md) — From トレイト、演算子システム、オプショナルチェーン（Chain）、nil 合体（Coalesce）
9. [拡張システム](spec/09-extensions.md) — extension、`#` による拡張適用
10. [モジュールシステム](spec/10-modules.md) — import、export、extern
11. [標準トレイト](spec/11-traits.md) — 基本／変換／演算子トレイト
12. [メタプログラミング](spec/12-metaprogramming.md) — `@[...]` 組み込みディレクティブ、ユーザー定義メタプログラミング（方針転換中）
13. [サンプルコード](spec/13-examples.md)

---

この仕様書は Plew プログラミング言語の現在の設計を反映しています。
