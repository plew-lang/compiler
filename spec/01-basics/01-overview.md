# 概要・基本構文

## 概要

Plew は現代的なシステムプログラミング言語で、型安全性、非同期プログラミング、パターンマッチング、独自の拡張システムを重視して設計されています。シングルプロセス・シングルスレッドを基本とし、JavaScript ライクな非同期処理とガベージコレクションによるメモリ管理を採用しています。

## 命名規則

- **型名**: PascalCase（例: `MyType`, `String`）
- **変数名・関数名**: snake_case（例: `my_variable`, `calculate_sum`）

## キーワード

```
export, pub, get, type, val, mut, async, spawn, await, loop, break, continue,
give, return, panic, where, enum, struct, newtype, assoc, extension, impl, via, trait, fn,
factory, inout, guard, while, for, in, if, elif, else, match, as, self,
Self, extern, import, part, with, try, true, false
```

`true` / `false` は真偽値リテラルです。

## コメント

```plew
// 行コメント

/*
 * ブロックコメント
 * 複数行にわたって記述可能
 */
```
