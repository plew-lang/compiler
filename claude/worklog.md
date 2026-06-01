# 作業ログ（実装フェーズ）

> compact がいつ走っても復帰できるよう、**今やっていること・次にやること**をこまめに更新する。古い完了項目は git 履歴に任せて圧縮してよい（「なぜ」は design-decisions、「設計」は architecture へ）。

## 現在地（一言）

stage0（Rust）：**walking skeleton 達成**（タグ `first-c-output`）＝`fn main(){ print(...) }` を source→C→clang→実行できる。lexer/式・文・宣言パーサ＋最小 C codegen＋clang ドライバ。次は**型検査の最小化と codegen の汎用化**、並行して**式・宣言の肉付け**（文字列・`if`/`match`・`struct`/`enum`・他宣言）。

## 全体ロードマップ（第一目標＝Plew でコンパイラが書ける → 即セルフホスト）

1. ✅ プロジェクト立ち上げ（C#/ANTLR/LLVMSharp と g4 を破棄 → Rust `bootstrap/`、lib+bin、cargo）
2. ✅ **Lexer**（手書き・token 列・span・コメント・数値/文字列/演算子の maximal munch）＋テスト
3. 🔨 **Parser**（再帰下降・AST を arena+index で）
   - ✅ 式：literal/ident/unary/binary（優先順位14段・非結合・グルーピング・エラー回復）
   - ✅ postfix：call（ラベル付き引数・末尾カンマ）/field `.`/index `[]`（postfix > prefix を担保）
   - ✅ 文・宣言（最小）：`fn` 宣言（params・`~:`・`-> ret`）・block・`val`/`mut val`・`return`・式文・型（`Array[I32]` 等）
   - ✅ 制御フロー：`if`/`else`/`else if`（式として）・ブロック式・`give`（パース）。codegen は `if` を**文位置**で対応
   - ✅ ループ：`while`（文位置 codegen）＋代入 `=`／複合代入 `+= -= *= /= %= &= |= ^= <<= >>=`。合計ループが e2e で動作
   - ⏭ 式の続き：`as`（要・型パーサ）・`try`/`await`・JSX `<T .. />`・closure・`match`・`?.`・**値位置 if/give の codegen**（clang statement-expr）
   - ⏭ 他宣言：`struct`/`enum`/`impl`/`trait`/`import` …
4. ✅ **C コード生成（最小）** ＋ clang ドライバ ＝ walking skeleton（`print(int)`→printf）
5. 🔨 **型検査（最小）**＝双方向推論で数値リテラル型確定・Bool 条件・演算子型・呼び出し検査（`typeck.rs`）✅。残り＝struct/enum/String/Array へ拡張・codegen に型を通す
6. 🔨 `struct`/`enum`＋`match`
   - ✅ `struct`/`enum` 宣言のパース（フィールド vis/mut・generics `[T]`・variant payload・`export` 受理・`where` は未対応で loud）。typeck/codegen は当面スキップ（codegen は loud エラー）
   - ⏭ `match`＋パターンのパース → struct 縦串（JSX 構築・field access・C struct）→ enum＋match の codegen（タグ付き共用体）
   - ⏭ `String`/`Array`＋ARC ランタイム（C）／名前解決の本格化
7. ⏭ → stage1（Plew でコンパイラ）に必要な分が揃い次第セルフホスト
6. **stage1**：Plew サブセットでコンパイラを書く → stage0 で compile → 自己 compile＝**セルフホスト達成**
7. 以降 LLVM/WASM・循環回収・所有権検査などを Plew 側で additive に

詳細・省略する機能の一覧は [architecture.md](architecture.md)「ブートストラップ戦略」を参照。

## 次の一歩（パーサ着手時の段取り案）

- AST ノード定義（arena 前提）。まず**式 → 文 → 宣言**の順で最小から。
- パーサの骨格（トークンカーソル・エラー回復方針）＋最初のテスト（整数リテラル/二項演算の優先順位）。
- 構文の全体像と優先順位は [grammar.md](grammar.md)（構文リファレンス＝spec 索引）と spec/12（演算子 14 段）を参照。

## 戦略メモ

- **walking skeleton 優先**：パーサを作り切る前に「`fn main` の小さなプログラム → C 生成 → clang → 実行」の縦串を通す（C トランスパイル＋clang 連携を早期検証・動く成果物）。マイルストン `first-c-output`。
- 残りの順序：lexer 改行 ✅ → 文/ブロック/`fn`宣言 → 最小 C codegen + clang ドライバ → 縦串。その後に式の続き（`as`/match/JSX 等）と他宣言を肉付け。

## 既知の暫定ギャップ

- ✅ **数値リテラルの型確定**：型検査（`typeck.rs`）で双方向推論を実装し、`val x = 6*7`（曖昧）を loud に拒否・注釈で解決・条件は Bool 強制・演算子型不一致も検出。テストで担保（tests/typeck.rs）。
- **`print(<int>)` は暫定の組み込み**：型検査では引数を I64 に pin、codegen は printf 直結。本来の `print` は String を取る。文字列・stdlib 整備時に置換。
- **codegen は依然 `int64_t` 前提**：型検査は I32/U64/F64 等を区別するが、codegen は全整数を int64_t で出す（幅が違う型は未対応）。型を codegen に通す＝次段。
- オーバーフロー panic・`as`・NaN 比較 panic 等の数値実行時意味論は未実装（codegen 素朴）。

## 直近の決定・注意（揮発しやすい文脈）

- **文の区切り＝改行（Go 流自動終端・Swift 流の括弧内継続）を採用・確定**（ユーザー追認済・spec/01「文の区切り」に反映）。詳細・根拠は design-decisions.md「文の区切り＝改行」。

- **タグ運用**：動作する区切りで記述的タグ（`lexer-working` 済予定）。バージョン番号はまだ使わない。
- **メモは repo 内**（CLAUDE.md / claude/）に。外部 memory は使わない。
- **判断に迷ったら突き進まず仰ぐ**。不要ファイルは容赦なく消してよい。
- `grammar.md` は ANTLR 機構の記述が陳腐化（g4 破棄済）。転用予定＝下半分の「構文 × spec」表はパーサ実装チェックリストとして残す。
