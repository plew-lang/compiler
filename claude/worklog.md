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
4. 🔨 **C コード生成（最小）** ＋ clang ドライバ ＝ walking skeleton ✅（整数前提・`print(int)`→printf・型検査なし）
5. 名前解決・型解決・trait/オーバーロード解決／codegen 汎用化／ARC ランタイム（C）
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

## 既知の暫定ギャップ（type 解決実装時に塞ぐ）

stage0 は**まだ型検査が一切無い**ため、Plew の意味論を強制していない箇所がある：

- **数値リテラルの型確定を強制していない**：`val x = 6 * 7`（注釈・確定文脈なし）は本来 spec 上**コンパイルエラー**（既定型なし）だが、今は codegen が全部 `int64_t` とみなして通す。→ 型解決を入れたら拒否し、テストで担保する。
- **`print(<int>)` は暫定の組み込み**（printf 直結）。本来の `print` は String を取る。文字列・stdlib 整備時に置換。
- 演算子の型・オーバーフロー panic・`as` 等の数値意味論も未実装（codegen は素朴）。

## 直近の決定・注意（揮発しやすい文脈）

- **文の区切り＝改行（Go 流自動終端・Swift 流の括弧内継続）を採用・確定**（ユーザー追認済・spec/01「文の区切り」に反映）。詳細・根拠は design-decisions.md「文の区切り＝改行」。

- **タグ運用**：動作する区切りで記述的タグ（`lexer-working` 済予定）。バージョン番号はまだ使わない。
- **メモは repo 内**（CLAUDE.md / claude/）に。外部 memory は使わない。
- **判断に迷ったら突き進まず仰ぐ**。不要ファイルは容赦なく消してよい。
- `grammar.md` は ANTLR 機構の記述が陳腐化（g4 破棄済）。転用予定＝下半分の「構文 × spec」表はパーサ実装チェックリストとして残す。
