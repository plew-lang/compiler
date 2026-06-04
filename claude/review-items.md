# 確認事項メモ（未解決・あとで対応／確認したい項目）

> 「作業を止めずに進めるが、**あとで対応・判断したい**」未解決項目を溜める場所。
> - **バグ修正の現況（解決済み含む）**は [worklog.md](worklog.md) 冒頭の「バグ調査カタログ」を正典とする（F 番号はそちら）。
> - 区分：「① 要ユーザー判断」「② 据え置き（理由あり）」「③ 残・順次対応可」。
> - **解決したら該当項目を消す**（このファイルは未解決だけを映す）。

## ① 要ユーザー判断（言語仕様に触れる）

- 現在なし。直近の決定（String リテラル単相・struct フィールドはカンマ不採用/改行区切り・enum バリアントの record 形式移行）は spec と [design-decisions.md](design-decisions.md) に反映済み。

## ② 据え置き（理由あり・大物 or 設計）

- **F11〔中・据え置き：構造化要素型 refactor〕複合要素型の配列**：`Array[Array[T]]`・`Array[Ref[T]]`・`Array[Box[T]]` 等、要素が複合型だと要素型マングルが内側型を解決できず頭名（`Array`/`Ref`/…）を literal 出力（`PlewArray_Ref`＝unknown type）。配列の**要素型を名前 span（`c.arrayElems`）で持つ設計**に根ざし、マングル/ランタイム（copy/release の ARC）/要素 C 型/単相化探索の全経路を**構造化要素型へ拡張**する必要＝規模ゆえ別タスク。`Array[Ref[T]]` は spec 推奨パターンなので価値は高い。
- **F12〔中・据え置き：整数リテラル符号モデル〕U64 リテラル ∈ [2^63, 2^64-1] で plewc がクラッシュ**：`tokenValue` が値を I64 で蓄積（`v*10+digit`）し I64 範囲超過でコンパイラ自身の overflow check が panic。直すには値表現を U64 化（`Expr.Int.value` U64・lexer 蓄積 U64・符号なし codegen・範囲検査・**負リテラル `-128` 畳み込みとの両立に符号フラグ**）＝整数リテラルの符号モデルに波及。影響はユーザーの巨大 U64 リテラルのみ（稀）。
- **演算子トレイト（Eq/Ord 以外）/ `@[Ord]` on enum / 曖昧な untyped-literal オーバーロード**：トレイト体系の大物・需要駆動。[provisional.md](provisional.md) のロードマップで管理。

## ③ 残（順次対応可・小〜中）

- **F4 残：for / guard の struct 分解**：`for Person { val name } in people`・`guard S { val x } = …`（spec/11）。match の struct 分解は実装済（`run/struct_pattern`）。for/guard のヘッダ分解は別 codegen で未対応。
- **F14 残：default 式の literal 型検査**：generic/非 generic とも、フィールド既定値式（`val n: I32 = 0`）の literal が field 型に対して型検査されていない（codegen は通る）。検査を足すと健全性が上がる。
- **closure が shadow された local をキャプチャ〔極小・稀・loud〕**：F2 の shadow 用 C 名 suffix（`cnum`）が `emitCaptureInit`（enclosing 名を素の writeSpan で出す）に未配線。shadow 変数をキャプチャする極端ケースのみ C 名不一致になり得る（壊れても clang エラー＝loud・silent でない）。well-tested な closure コードへの回帰リスクに見合わず低優先。
- **N4b〔小・ほぼ by-design〕for ループ変数の型注釈が範囲境界へ伝播しない**：`for val i: I32 in 0..<5` は境界リテラルに型文脈が伝わらず「no type from context」。回避＝境界に suffix（`0..<5I32`）。設計上「範囲境界リテラルは型必須」（for.pw 明記）なので非バグ寄りだが、ループ変数注釈を context に使う改善余地。
