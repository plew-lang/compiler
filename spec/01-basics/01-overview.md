# 概要・基本構文

## 概要

Plew は現代的なシステムプログラミング言語で、型安全性、非同期プログラミング、パターンマッチング、独自の拡張システムを重視して設計されています。シングルプロセス・シングルスレッドを基本とし、JavaScript ライクな非同期処理を採用します。値は**コピー意味論（CoW）**、メモリは **ARC（参照カウント）** で管理し、必要なときだけ opt-in の所有権（`unique`/`local`・`Ref`/`WeakRef`）を使います（→ [値・変数・所有権](03-values.md)、[非同期処理とメモリ管理](../04-execution/14-concurrency.md)）。

## 命名規則

- **型名**: PascalCase（例: `MyType`, `String`）
- **変数名・関数名**: snake_case（例: `my_variable`, `calculate_sum`）

## キーワード

```
export, pub, get, type, val, mut, async, spawn, await, loop, break, continue,
give, return, panic, where, enum, struct, newtype, assoc, extension, impl, via, trait, fn,
factory, borrow, inout, move, unique, local, deinit, guard, while, for, in, if, elif, else,
match, as, self, Self, extern, import, part, with, try, true, false
```

`true` / `false` は真偽値リテラルです。`borrow`/`inout`/`move`（アクセスモード）・`unique`/`local`（型マーカー）・`deinit`・generics の `allow_unique`/`no_local` は [値・変数・所有権](03-values.md) を参照。`mut` は記憶域可変性（`mut val`）専用です。

**文脈依存キーワード**：`optional` / `result` は [fallible factory](../02-type-system/05-structs-enums.md#失敗し得るファクトリfallible-factory) の前置修飾（`optional factory …` / `result[E] factory …`）の位置でのみ予約語として働き、**それ以外では通常の識別子**です。`result` は頻出する変数名なので予約語にせず、`val result = compute()` などは従来どおり書けます。

## コメント

```plew
// 行コメント

/*
 * ブロックコメント
 * 複数行にわたって記述可能
 */
```
