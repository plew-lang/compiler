# 作業ログ

> 現在地・次の一歩・運用メモだけを置く。完了した「やった」は git 履歴へ（タグで辿れる）。「なぜ」は [design-decisions.md](design-decisions.md)、「パイプライン設計」は [architecture.md](architecture.md)、「spec からの意図的剥離」は [provisional.md](provisional.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で `Lexer`/`Ast`/`Parser`/`Codegen` を綴じ込む 1 モジュール）。自分自身を不動点までコンパイルする。

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust/cargo 不要）。`./bootstrap.sh --reseed` で種更新。
- **テスト**：`./test.sh`＝`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/part/`（複数ファイル）＋`tests/reject/*.pw`（plewc が非ゼロ終了で reject＝受理の健全性）＋不動点（Rust 非依存）。
- **サポート済の言語**：型付き整数/Bool・String（リテラル/`.bytes`/`==`/エスケープ）・**文字リテラル `'c'`**（→コードポイント）・Array（リテラル/添字/`count`/`append`/`a[i]=x`/for-each）・struct/JSX 構築/フィールド・enum+match（**網羅検査あり**・タグ if-chain）・enum `==`（全 nullary 限定）・**`val`/`mut val` 可変性検査**（不変への単純代入は reject）・関数/引数/**ラベル検査**/`inout`/再帰・**インヘレントメソッド `impl Type { fn / inout fn }`**（`recv.m(label:)`・self 暗黙・ラベル検査・`Type_m` マングル＝コンパイラ自身も `lx.at(off:)` で dogfood 中）・`if`/`else`/`while`/`for`（range/array）・`break`/`continue`・`as`（数値）・**`import @Std/Io`・`@Std/Process` の `with {}` 選択 import**（I/O は ambient でなく import 必須）・**複数ファイル `part ./Name`**・I/O ビルトイン（`print`/`write`/`writeByte`/`readStdin`/`readFile`/`readFileBytes`/`argCount`/`argAt`）・診断 `compileError`/`compileErrorAt`。軽量型追跡・配列単相化・I/O ランタイム preamble を自前出力。生成 C は警告クリーン。
- **spec からの意図的剥離**（値意味論/CoW・整数幅・トレイト・モジュール詳細等）は [provisional.md](provisional.md) に集約。足場（履歴）`examples/{lexer,parser,emit,calc}.pw`。

## 受理の健全性（意味上 Plew として正しい）＝一区切り

「このコンパイラが*受理*するコードは spec でも valid」を目標に hidden meaning を潰す。チェックリスト（詳細 [provisional.md](provisional.md)）：① import なし `print` ② ラベル無視 ③ 非網羅 match ⑤ struct/array 比較 ⑥ 不変 `val` への代入（単純変数）＝**解消済**。④ lossy `as` のみ**保留**（整数幅の実装に依存）。違反はすべて `compileError*` 診断＝`plewc: error: [line N: ]…`＋非ゼロ終了で reject。

## 次の一歩の候補（やりやすい順で自走）

- **コンパイラ自身の自由関数 → メソッド化を段階的に進める**（`at(lx: inout lx, off:)`→`lx.at(off:)` は完了済。`cur`/`advance`/`peekKind` 等 `inout Comp`/`inout Lexer` を取るヘルパは `impl` メソッドへ移せる＝書き味向上）。各まとまりで ADD 不要・USE→reseed のみ。低リスク。
- **`import ./Foo`（名前空間束縛・`Foo.bar`）**。修飾名解決が要る（今は part で全部フラット同一スコープ）。
- **整数幅 `I8..U64`/`F32/F64`**＝hidden cost の大物。codegen 全体の `long long` 前提を幅つきに置換すると、④ lossy `as`・overflow/0除算 panic・`'あ' を U8` の溢れ検査までまとめて片付く。**複数セッション規模**。
- 値意味論/CoW・トレイト/ジェネリクスは更に大物（後）。

> import の現状＝**`with {}` 選択形のみ**・認識するのは I/O ビルトインだけ（`@Std/Io`＝print/write/writeByte/readStdin/readFile(+readFileBytes)・`@Std/Process`＝argCount/argAt）・名前↔モジュール検査あり。名前空間 import・実モジュール解決・`export`・`/`/`../` ルート・`_.pw` ディレクトリ・ネスト part 追従は未実装。

## 機能を plewc.pw に足す手順（ADD→reseed→USE）

新機能を plewc.pw の**ソースで使う**には：①`compiler/src/` の codegen に機能を足す（**ADD**）→ ②`./bootstrap.sh --reseed` で種更新（→ `compiler/plewc.seed.c` を commit）→ ③ソースで使う（**USE**）。「ソースが使う機能は常にひとつ前のコンパイラがサポート済み」を守れば不動点は壊れない。新しい preamble 行を足した直後は種が 1 世代遅れるので **reseed を 2 回**回す（1 回目で挙動を種に焼き、2 回目で種ファイルを一致させる）。暗黙ビルトイン → 実 `@Std`/`extern` への将来移行も同じ ADD→USE→REMOVE で flag day にならない。

## メモリモデル（hidden cost の暫定・重要）

Array は **ヒープ確保＋リーク（free しない）＋参照セマンティクス**で実装（spec の CoW 値意味論/ARC は未実装）。エイリアス後変更が観測できてしまう差は、**plewc.pw を「アリーナ＋index・単一所有」で書く規律**で回避している。正しい CoW/ARC は後で（hidden cost＝受理の健全性の対象外）。詳細は [provisional.md](provisional.md)。

## 運用メモ

- 動作する区切りで**記述的 git タグ**（`self-host`/`char-literals` 等・バージョン番号はまだ）。コミットメッセージは英語。
- **不要になった実装は削除し、必要なら git tag から復旧**（例：`git checkout stage0-final -- bootstrap`）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。メモは repo 内（外部 memory は使わない）。
- LLVM 化は当面しない＝意味論が揃ってから（import/トレイト/所有権の後）、性能 or 直 WASM が要る時に並行バックエンドとして追加（C は捨てない）。
