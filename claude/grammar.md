# 文法（ANTLR4）

文法定義は `grammer/Plew.g4`（ANTLR4）。これがソース構文の**正典**。設計会話（`note/`）は記法が時系列で二転三転しているため、迷ったら必ず `Plew.g4` を優先する。

## パーサ生成

- C# 公式ランタイム（`Antlr4.Runtime.Standard`）向けにパーサを生成する。NuGet パッケージはまだ `.csproj` 未追加。
- `grammer/.gitignore` は `*.interp` / `*.tokens` / `.antlr` を無視する（ANTLR ツールや VS Code 拡張の生成物）。生成された Lexer/Parser はコミットしない方針。
- ローカルに `antlr4` CLI は未導入。ビルド時生成（`Antlr4` MSBuild ターゲット）か CLI 生成かは実装開始時に決める。

## ANTLR 固有の注意（`Plew.g4` で実際に踏んでいる罠）

- 文字クラス `[...]` 内に `{` / `}` は直接書けない → `{`（`{`）/ `}`（`}`）でエスケープ。文字列補間トークンで使用。
- `.` はデフォルトで改行にマッチしない。否定集合 `~["{]` は改行を含む。
- 改行が意味を持つ言語（`req_newline` / `opt_newline` で文・宣言を区切る）。`NEWLINE: '\n'` をスキップしていないので、AST builder は改行トークンの扱いに注意。
- 文字列補間: `string_literal` は `'"' (DOUBLE_STRING_CHAR | string_variable)* '"'`。`string_variable: '{' expression (':' STRING_FORMAT+)? '}'` で `{expr:format}` を Lexer/Parser レベルで分割している（単一トークンでは中の式を解析できないため）。

## 文法と SPEC の差分

`Plew.g4` は**後で作り直す前提**で当面いじらない。初期の構文選択（`#Ext`、`impl … as`、修飾子削除など）は文法が解決済みの正だが、**最近の設計判断は SPEC 側が正で、文法が追いついていない**領域が多い。

下表は「文法が将来支えるべき構文」と「現行文法の状態」だけを示す。**各決定の意味論・根拠は spec が正典**なので、リンク先を見ること（ここで再掲しない）。多くの決定は**型検査／解決／コード生成といった意味論層**の話で、そもそも文法に現れない（その旨だけ記す）。

凡例：**一致**＝文法が現行決定を既に表現／**仕様先行**＝文法が未追従で要拡張／**意味論層**＝文法非依存（型検査・解決・codegen で扱う）。

| 項目（→ spec） | 文法が支えるべき構文 | 現行文法の状態 |
| --- | --- | --- |
| 拡張の区切り（[09](../spec/02-type-system/09-extensions.md)） | `('#' \| '#!') type_use` | 一致 |
| 拡張ビューの型扱い（[09](../spec/02-type-system/09-extensions.md)） | （型細別・暗黙キャストなし・コンテナ非伝播） | 意味論層 |
| トレイト実装（[07](../spec/02-type-system/07-methods-impl.md)） | `impl Type AS type_use` | 一致 |
| 並行性修飾子（[14](../spec/04-execution/14-concurrency.md)） | `sync`/`shared`/`atomic` は不採用＝`MUT? VAL` のみ | 一致（削除済み） |
| 可視性（[05](../spec/02-type-system/05-structs-enums.md)） | `export` + `pub`/`pub(get)` | 一致 |
| 冪乗 `**`（[12](../spec/03-expressions/12-operators.md)） | 不採用（`pow` で代替） | 一致（未実装） |
| `lazy` | 専用構文なし（`<Lazy />` 構造体） | 一致（未実装） |
| force-unwrap（[13](../spec/03-expressions/13-error-handling.md)） | 無し（`UNARY_POSTFIX_OP` `!` は遺物・削除予定） | 要削除 |
| 数値リテラル（[02](../spec/01-basics/02-basic-types.md)） | `0x`/`0o`/`0b`・`_`・e 表記・型サフィックス `10U32` | 仕様先行（`DIGIT+` のみ・型付けは意味論層） |
| メソッドのオーバーロード（[07](../spec/02-type-system/07-methods-impl.md)） | impl 内に同名 `method` 複数（解決規則は意味論層） | 仕様先行 |
| デフォルト引数（[04](../spec/01-basics/04-functions.md)） | `arg_declare` に `= 式`（`inout` には付けない） | 仕様先行（`arg_declare` は `INOUT? value type_annotate` で既定値構文なし・毎回評価/自己完結/セレクタ生成は意味論層） |
| ジェネリクスの型パラメータ（[06](../spec/02-type-system/06-generics.md)） | `[...]` は名前のみ・制約は `where`（インライン `[T: Trait]` なし） | 仕様先行（制約は意味論層） |
| impl の型パラメータ（[06](../spec/02-type-system/06-generics.md)） | `impl[T] Type …` の前置宣言 | 仕様先行（前置なし） |
| モジュール/`part`/`_.pw`（[15](../spec/04-execution/15-modules.md)） | `part`・ディレクトリ `_.pw`・エントリ `src/_.pw` | 仕様先行（`import` のみ） |
| 再エクスポート（[15](../spec/04-execution/15-modules.md)） | `export <path> with {…}` / `with *` | 仕様先行 |
| トレイト準拠 `via`（[08](../spec/02-type-system/08-traits.md)） | 各要求を `via 完全シグネチャ` で束ねる | 仕様先行（`impl as` のみ） |
| 派生メソッド・トレイト主語 impl・`default_extension`（[08](../spec/02-type-system/08-traits.md), [09](../spec/02-type-system/09-extensions.md)） | `extension`/`impl` がトレイト名を主語に取る／型本体の `default_extension #Ext` | 一部一致（`trait_body` は本体なしのみ＝一致）／残りは仕様先行 |
| 存在型 `any P`（[08](../spec/02-type-system/08-traits.md)） | `type_use` の `any` プレフィクス | 仕様先行（存在型・動的ディスパッチは意味論/codegen 層） |
| トレイト継承 supertrait（[08](../spec/02-type-system/08-traits.md)） | `trait Sub: A + B` | 仕様先行（supertrait 句なし） |
| 関連型の宣言（[08](../spec/02-type-system/08-traits.md)） | `type Item`（ベア可）/ `type Item: 制約` | 仕様先行（束縛必須・ベア不可） |
| 関連型の束縛（[08](../spec/02-type-system/08-traits.md)） | `Trait[Arg, Assoc = Foo]`（位置＋名前付き混在） | 仕様先行（`type_args` は位置のみ） |
| 関連型の射影（[08](../spec/02-type-system/08-traits.md)） | `T.Item`（`.` 連結） | 一致（要 AST 解釈） |
| トレイトの型引数（[08](../spec/02-type-system/08-traits.md)） | `Add[Rhs]` 等（`type_args_declare?`） | 一致 |
| 変換トレイト・`as`（[12](../spec/03-expressions/12-operators.md)） | `AS type_use`（`From` factory 対応付け・`as` は infallible 固定は意味論層） | 一致 |
| 失敗し得るファクトリ（[05](../spec/02-type-system/05-structs-enums.md)） | `factory` の前置修飾 `optional` / `result '[' type_use ']'`（戻りラッパーは意味論層） | 仕様先行（`factory` 宣言に修飾語なし・`optional`/`result` は文脈依存キーワードで要追加） |
| `TryFrom`・可謬変換（[12](../spec/03-expressions/12-operators.md)） | `result[E] factory convert(from: ...)`（`as` 糖衣なし＝呼びは JSX `<T.convert from=.../>`）／`From` は無名 `factory(from: ...)`（`x as T` 糖衣） | 仕様先行（trait 要求の factory・fallible factory に依存） |
| トレイトの factory 要求（[08](../spec/02-type-system/08-traits.md)） | `trait_body` に本体なし `factory`（fallible 含む）を要求として書ける | 仕様先行（`trait_body` は本体なしメソッド/フィールド等のみ・factory 要求は要追加） |
| 等価・順序（[12](../spec/03-expressions/12-operators.md)） | 比較トークン（`Eq`/`Ord` 対応付けは意味論層） | 仕様先行 |
| 論理結合子 `&&`/`||`（[12](../spec/03-expressions/12-operators.md)） | トークンあり（短絡＝制御フローは codegen 層） | 仕様先行 |
| 演算子の優先順位・結合性（[12](../spec/03-expressions/12-operators.md)） | 14 段（後置 ＞ 前置/`try`/`await` ＞ `as` ＞ `*/%` ＞ `+-` ＞ `<<>>` ＞ `&` ＞ `^` ＞ `\|` ＞ `??` ＞ 比較[非結合] ＞ `&&` ＞ `\|\|` ＞ レンジ[非結合]） | 仕様先行（現行ラダーは `??` 最下位・`%`/`as`/レンジ/ビットを欠き・比較は左結合） |
| ビット演算子（[12](../spec/03-expressions/12-operators.md)） | `& \| ^ << >> ~`（`BitAnd`/`BitOr`/`BitXor`/`Shl`/`Shr`/`BitNot`） | 仕様先行（トークン・規則なし） |
| 単項 `!` と `~`（[12](../spec/03-expressions/12-operators.md)） | `!`＝Bool 専用 Not／`~`＝整数 BitNot（別演算子） | 仕様先行（`UNARY_PREFIX_OP` は `-`/`!` のみ・`~` なし） |
| 複合代入演算子（[12](../spec/03-expressions/12-operators.md)） | `ASSIGN_OP` に `%=` ＋ビット系 `&= ^= \|= <<= >>=`（脱糖 `a OP= b`⟺`a = a OP b`・専用トレイトなし） | 仕様先行（現行 `ASSIGN_OP` は `= += -= *= /=` のみ・`%=`/ビット系を欠く） |
| 場所（place）越しの変更（[03](../spec/01-basics/03-values.md)） | 代入左辺・`inout` レシーバ/引数は place（`mut val` 根＋フィールド/添字パス）。`arr[i].field=x`・`arr[i].inout_method()`・`a.b[i].c=x` | 意味論層（get-modify-set 脱糖・in-place 最適化・重なり inout 検査＝静的エラー/lint/限定ランタイム panic はすべて型検査・codegen 層） |
| 条件チェーン（[11](../spec/03-expressions/11-control-flow.md)） | `if`/`elif`/`while`/`guard` 条件に `PAT = expr` の `&&` 連結 | 仕様先行（単一式想定・要拡張） |
| 浮動小数 NaN（[12](../spec/03-expressions/12-operators.md)） | （比較で panic・算術は IEEE） | 意味論層（実行時） |
| 整数オーバーフロー/0 除算（[12](../spec/03-expressions/12-operators.md)） | （全ビルドで panic） | 意味論層（codegen） |
| `panic` 文（[11](../spec/03-expressions/11-control-flow.md)） | `panic "msg"` キーワード（発散する文） | 仕様先行（トークン/規則なし） |
| match アーム右辺（[11](../spec/03-expressions/11-control-flow.md)） | ベア式 `=> expr`／ブロック／発散ブロック | 仕様先行（要確認） |
| ローカル再宣言（[03](../spec/01-basics/03-values.md)） | 同名 `val`（名前解決は意味論層） | 一致（意味論層） |
| 文字列・配列の型意味論（[02](../spec/01-basics/02-basic-types.md)） | （不変・UTF-8 妥当・`bytes` 公開・整数添字なし・配列添字/`count`/レンジ要素は `U64` 固定 等） | 意味論層（型検査/codegen） |
| 文字列補間・複数行（[02](../spec/01-basics/02-basic-types.md)） | 補間 `{式}`・深さ 0 の `:` 境界・`{{`/`}}`・行末 `\` 継続 | 仕様先行（単一 `{`/`:`・エスケープ/継続なし） |
| ラベル付きタプル（[02](../spec/01-basics/02-basic-types.md)） | `(x: I32)` 型／`(x: 1)` 生成／`.x`／`(val x)=e` 分解 | 仕様先行（位置タプル `(e, e)`） |
| 辞書・集合型（[02](../spec/01-basics/02-basic-types.md)） | `Dictionary[K, V]` リテラル `[k: v]`/`[:]`（`K: Hash`・`dict[k]->V` 欠落 panic）・`Set[E]` | 一致（`dictionary_literal` あり）／型名・`Hash` 境界・lang item 化・`Set` は意味論層 |
| 変数束縛 `val`/bare・punning（[03](../spec/01-basics/03-values.md)） | `val`＝新規・bare＝既存／`for val i`／punning | 仕様先行 |
| ワイルドカード `_`（[11](../spec/03-expressions/11-control-flow.md)） | 一般パターンの葉（破棄・パターン位置ならどこでも・値式不可） | 仕様先行（現行は `match_case` の `'_'` 特例のみ＝ネスト/分解での `_`・統一パターン規則は未整備） |
| 全フィールド明示・`..` なし（[11](../spec/03-expressions/11-control-flow.md)） | 分解パターンは全フィールド列挙（束縛 or `_`）・残り無視 `..` を持たない | 意味論層（フィールド網羅検査）＋仕様先行（`enum_assign_left` は enum 限定で構造体/レコード分解の規則なし） |
| レンジ構文（[02](../spec/01-basics/02-basic-types.md)） | `a..<b`/`a..=b`（素の `..` なし） | 仕様先行（範囲リテラルなし・型/糖衣は意味論層） |

## `examples/main.pw` について

このサンプルは `sync val` と `b.lock()` を使っており、**現行文法でも現行モデルでも無効**な旧設計の構文（Plew は `Mutex`/`sync val` を持たず、spawn は値の送信のみ）。新しいサンプルを書くときは現行文法・現行モデルに従うこと。

## 文法の細かい未整備（致命的でない）

会話末で指摘済み: `@[...]` ディレクティブ内の空行・末尾カンマ、`match_case` 前の `opt_newline`、`where_clauses` の末尾カンマなど書き味レベルの穴。実装を進めつつ調整する。
