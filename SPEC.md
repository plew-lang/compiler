# Plew プログラミング言語仕様書

Plew は現代的なシステムプログラミング言語で、型安全性、非同期プログラミング、パターンマッチング、独自の拡張システムを重視して設計されています。シングルプロセス・シングルスレッドを基本とし、JavaScript ライクな非同期処理とガベージコレクションによるメモリ管理を採用しています。

本仕様書はトピック別に分割し、論理依存順に **4 部**へまとめて `spec/` 配下に置いています。

## 目次

### 第Ⅰ部 言語の基礎

1. [概要・基本構文](spec/01-basics/01-overview.md) — 概要、命名規則、キーワード、コメント
2. [基本型](spec/01-basics/02-basic-types.md) — プリミティブ型、数値リテラル、文字列（不変・UTF-8・変数展開）、複合型（配列／辞書／ラベル付きタプル／レンジ）
3. [変数と値の管理](spec/01-basics/03-values.md) — 参照の値渡しと inout、変数宣言、再宣言（shadowing）、構造化代入
4. [関数](spec/01-basics/04-functions.md) — 関数宣言、引数ラベル、無名関数（クロージャ）

### 第Ⅱ部 型システム

5. [構造体と列挙型](spec/02-type-system/05-structs-enums.md) — 構造体／列挙型の宣言、フィールド統一原則、Optional／Result、インスタンス生成（JSX／factory）、メンバの可視性
6. [ジェネリクス](spec/02-type-system/06-generics.md) — 型パラメータ、impl[T]、where 句
7. [メソッドと impl](spec/02-type-system/07-methods-impl.md) — impl、メソッド、関連関数／関連値、メソッドのオーバーロード、無名 impl のコヒーレンス
8. [トレイト](spec/02-type-system/08-traits.md) — 定義（要求・提供メソッド）、関連型、継承（supertrait）、準拠と via、標準トレイト
9. [拡張システム](spec/02-type-system/09-extensions.md) — extension、`#` による拡張適用、orphan rule
10. [newtype（名目型）](spec/02-type-system/10-newtype.md) — 実装の継承と Self 置換、as による再タグ

### 第Ⅲ部 式・制御・エラー

11. [制御構造](spec/03-expressions/11-control-flow.md) — ブロックと give、条件分岐、条件チェーン（束縛つき条件）、パターンマッチング、ループ、ガード、panic
12. [型変換と演算子](spec/03-expressions/12-operators.md) — From トレイト、演算子システム、等価／順序（Eq／Ord）、論理結合子（&&／||）、オプショナルチェーン（Chain）、nil 合体（Coalesce）
13. [エラーハンドリング](spec/03-expressions/13-error-handling.md) — try 式

### 第Ⅳ部 実行モデルとツール

14. [非同期処理とメモリ管理](spec/04-execution/14-concurrency.md) — async/await、spawn、チャネル、GC
15. [モジュールシステム](spec/04-execution/15-modules.md) — import、export、part、パッケージ、extern
16. [メタプログラミング](spec/04-execution/16-metaprogramming.md) — `@[...]` 組み込みディレクティブ、ユーザー定義メタプログラミング（方針転換中）

### 付録

17. [サンプルコード](spec/05-appendix/17-examples.md)

---

この仕様書は Plew プログラミング言語の現在の設計を反映しています。
