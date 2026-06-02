# 作業ログ

> 現在地・次の一歩・運用メモだけを置く。完了した「やった」は git 履歴へ（タグで辿れる）。「なぜ」は [design-decisions.md](design-decisions.md)、「パイプライン設計」は [architecture.md](architecture.md)、「spec からの意図的剥離」は [provisional.md](provisional.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝`compiler/src/_.pw`（Plew 製・自分自身を不動点までコンパイルする）。

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust/cargo 不要）。`./bootstrap.sh --reseed` で種更新。
- **テスト**：`./test.sh`＝`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/reject/*.pw`（コンパイル失敗を確認＝受理の健全性）＋不動点（Rust 非依存）。
- **コンパイラがサポート済の言語**：型付き整数/Bool・String（リテラル/`.bytes`/`==`/エスケープ）・Array（リテラル/添字/`count`/`append`/`a[i]=x`/for-each）・struct/JSX 構築/フィールド・enum+match（網羅前提・タグ if-chain）・enum `==`（全 nullary 限定）・関数/引数/`inout`/再帰・`if`/`else`/`while`/`for`（range/array）・`break`/`continue`・`as`（数値）・**`import @Std/Io`・`@Std/Process` の `with { }` 選択 import**（I/O ビルトインは ambient でなく import 必須＝下記 enforce）・I/O ビルトイン（`print`/`write`/`writeByte`/`readStdin`/`readFile`/`argCount`/`argAt`）。軽量型追跡 `exprType`・配列単相化・I/O ランタイム preamble を自前出力。生成 C は警告クリーン（`-Wall -Wextra -Werror`）。
- **足場（履歴）**：`examples/{lexer,parser,emit,calc}.pw` は self-host 途上の小コンパイラ。
- **spec からの意図的剥離**（値意味論/CoW・整数幅・ラベル・トレイト・モジュール等）は [provisional.md](provisional.md) に集約。

## 現在の目標：受理の健全性（意味上 Plew として正しい）

**このコンパイラが*受理*するコードを spec でも valid にする**（完全な Plew コンパイラも通せる）。spec が reject するのに今 accept してしまう所＝hidden meaning を潰す。逆向きの不完全性（valid だが未実装で reject＝`<.LParen />`・トレイト等）は許容。hidden cost（leak・int 幅・overflow 非 panic）は対象外（後回し）。

要修正リスト＝[provisional.md](provisional.md)「受理の健全性チェックリスト」：① ✅ **import なしで `print`**（`@Std/Io`・`@Std/Process` import 必須・名前↔モジュール検査）② ✅ **ラベル無視**（ユーザー関数呼び出しは有無/名前/宣言順/arg 数を検査）③ ✅ **非網羅 match**（`_` or 全 variant 被覆を検査）④ ⏸ lossy `as`（**整数幅実装に依存＝保留**）⑤ ✅ **struct `==`**（比較演算子を struct/array に適用＝`Eq`/`Ord` 無しで reject）。いずれも不一致は **`compileError(msg)` ビルトイン**で `plewc: error: …` を stderr に出し非ゼロ終了（旧 sentinel 方式＝未宣言 C 識別子で clang を落とす、を置換）。

**④が整数幅に依存して保留**：現状は `as` を数値↔数値の素の C キャストにしており `300 as U8` が silent truncate する。spec は `as`＝infallible 固定（無損失のみ・縮小は `TryFrom`）。だが現コンパイラは整数幅を区別せず全部 `long long` なので**損失性が判定できない**＝幅つき整数（hidden cost 側の大物）の実装と一体。受理の健全性は①②③⑤で当面の hidden-meaning を概ね潰した。

**開発を楽にする機能フェーズ（受理の健全性は一区切り）**：

- ✅ **複数ファイル `part ./Name`**（相対・兄弟ファイル）。root の `part` directive を走査→兄弟 `.pw` を readFileBytes で読みバイト連結→1 buffer として lex/parse（単一アリーナ・単一 C 出力ゆえ全部入り）。`tests/part/` で回帰。残：`_.pw` ディレクトリ・`../`・`/` ルート・ネスト part 追従。

- ✅ **コンパイラ本体を分割**。`compiler/src/_.pw`（約3100行）→ root `_.pw`（234行・import＋part＋driver＋main）＋`Lexer.pw`/`Ast.pw`/`Parser.pw`/`Codegen.pw`。ブートストラップは root を渡すだけ（part 追従はコンパイラがやる）＝`part` のブートストラップ実地テストにもなっている。bootstrap.sh/test.sh は無変更。

- ✅ **真の診断経路＋行番号**。`compileError(msg)`／`compileErrorAt(line, msg)` ビルトイン（stderr へ `plewc: error: [line N: ]…`＋`exit(1)`）。受理健全性の全チェック（import/ラベル/match/struct==/enum==）を sentinel から置換し、`lineOf(offset)`＋`exprOffset(id)`＋`Stmt.Print.offset` で行番号を付与（assembled buffer 越しでも正しい）。`test.sh` の reject は plewc の終了コードで判定。compileError* はコンパイラ内部の ambient プリミティブ（import gate しない）。

- ✅ **文字リテラル `'c'`**（spec/02「文字リテラル」＋design-decisions に決定記録）。単一スカラ→コードポイントの多相数値リテラル（`'/'`→47・`'あ'`→12354・エンコーディング非依存）。エスケープは文字列と共通。複数スカラ（国旗 `'🇯🇵'`）・複数書記素（`'ab'`）は `Grapheme` 型未策定ゆえ reject（spec valid だが未実装）。lexer に `Kind.Char`、parser に `charValue`（UTF-8 をビット演算なしの算術で復号＝`%64`/`*64`）。**ドッグフード**：`isDigit`/`isAlpha` を `b >= '0'` 等に書き換え（同じ整数に lower）。残：マジックナンバーは lexer 本体（句読点 dispatch・`b == 47` 等）にまだ多数＝追って char literal 化できる（同値 lower ゆえ不動点安全）。

**次の一歩の候補**（やりやすい順で自走）：
- lexer 残りのマジックナンバーを char literal 化（低リスク・読みやすさ向上・同値 lower で不動点安全）。
- `import ./Foo`（名前空間束縛・`Foo.bar`）＝修飾名解決が要る。今は全部フラット同一スコープ。
- 整数幅（`I8..U64`/`F*`）＝hidden cost の大物。これが入ると④ lossy `as`・overflow panic も片付く（`'あ' を U8` の溢れ検査もここで効く）。
- 値意味論/CoW・トレイト/ジェネリクスは更に大物（後）。

> import 機構の現状＝**`with { }` 選択 import のみ**で、認識するのは I/O ビルトイン（`@Std/Io`＝print/write/writeByte/readStdin/readFile・`@Std/Process`＝argCount/argAt）だけ。名前空間 import（`Io.print`）・実モジュール解決・複数ファイル・`export`/`part`・`/`/`./` ルートは未実装（単一ファイルのまま）。enforce は `compileError(msg)`＝`plewc: error: …` を stderr に出し非ゼロ終了（受理健全性チェック共通の経路）。

## 機能を plewc.pw に足す手順（ADD→reseed→USE）

plewc.pw が暗黙に依存するのは閉じた一式だけ＝**I/O ビルトイン**（`print`/`write`/`writeByte`/`readStdin`/`readFile`/`argCount`/`argAt`）＋**C ランタイム preamble**（`PlewString`・`PlewArray_<T>`＋配列ランタイム・I/O 本体）で、これは **plewc.pw 自身の codegen が出力**する＝出力 C は自己完結。

- 新機能を plewc.pw の**ソースで使う**には：①`compiler/src/_.pw` の codegen に機能を足す（**ADD**）→ ②`./bootstrap.sh --reseed` で種更新（→ `compiler/plewc.seed.c` を commit）→ ③ソースで使う（**USE**）。「ソースが使う機能は常にひとつ前のコンパイラがサポート済み」を守れば不動点は壊れない。
- 暗黙ビルトイン → 実 `@Std`/`extern` への将来移行も同じ **ADD→USE→REMOVE**（受理を先に足す・ソース移行・旧挙動の除去は最後）。各段で不動点を保つので flag day にならない。`print`/`write` は本来 `@Std`＋`Format` で、魔法ビルトインはその代用。

## メモリモデル（hidden cost の暫定・重要）

Array は **ヒープ確保＋リーク（free しない）＋参照セマンティクス**で実装（spec の CoW 値意味論/ARC は未実装）。エイリアス後変更が観測できてしまう差は、**plewc.pw を「アリーナ＋index・単一所有」で書く規律**で回避している。正しい CoW/ARC は後で（hidden cost＝受理の健全性の対象外）。詳細は [provisional.md](provisional.md)。

## 運用メモ

- 動作する区切りで**記述的 git タグ**（`self-host`/`stage0-retired` 等・バージョン番号はまだ）。コミットメッセージは英語。
- **不要になった実装は削除し、必要なら git tag から復旧**（例：`git checkout stage0-final -- bootstrap`）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。メモは repo 内（外部 memory は使わない）。
- LLVM 化は当面しない＝意味論が揃ってから（import/トレイト/所有権の後）、性能 or 直 WASM が要る時に並行バックエンドとして追加（C は捨てない）。
