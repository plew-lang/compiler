# 確認事項メモ（未解決・あとで対応／確認したい項目）

> 「作業を止めずに進めるが、**あとで対応・判断したい**」未解決項目を溜める場所。
> - **バグ修正の現況（解決済み含む）**は [worklog.md](worklog.md) 冒頭の「バグ調査カタログ」を正典とする（F 番号はそちら）。
> - 区分：「① 要ユーザー判断（言語仕様に触れる）」「② 判断不要・据え置いた実装」。
> - **解決したら該当項目を消す**（このファイルは未解決だけを映す）。

## ① 要ユーザー判断（言語仕様に触れる）

- 現在なし。直近の決定（String リテラル単相・struct フィールドはカンマ不採用/改行区切り・enum バリアントの record 形式移行）は spec と [design-decisions.md](design-decisions.md) に反映済み。

## ② 判断不要・据え置いた実装（メモのみ・順次対応可）

- **F3 トップレベル変数（`val`/`mut val` をモジュール直下）**：`parseProgram` が未対応で黙殺＝"undeclared identifier"。実装には spec/15 の初期化順（全トップレベル/assoc val → main）の配線が要る（feature 規模）。まず最低限 **loud-reject**（未対応と明示）に倒すのが安全な中間段。
- **F4 struct 分解パターン `P { val x, val y }`**（match/for/guard）：spec/11 正典。現状 enum バリアント分解（record 形式 `E.V(...)`）のみ対応で、非 enum struct パターン（`{ }`）は catch-all 誤診断で落ちる。`parsePattern` が型名後に `.` 無しでも variant を読む点の修正＋ match codegen に struct（タグ無し・`_m.field` 直読み・irrefutable 単一アーム）経路の追加が要る。
- **F11〔中・重要〕複合要素型の配列**：要素型が**複合型**（`Array[Array[T]]`・`Array[Ref[T]]`・`Array[Box[T]]` 等の generic/Ref/array）だと要素型マングルが内側型を解決できず、要素型名に頭名（`Array`/`Ref`/…）を literal 出力（`PlewArray_Ref`・`Ref* data`＝unknown type）。**`Array[Ref[T]]` は spec 推奨の「unique 要素は Ref 包み」「共有要素」パターンなので重要度高**（matrix／list-of-list／shared 要素配列で顕在化）。`recordArrayElem`／要素型マングル（`wPA`/`genCElem` 系）が要素の structured type を解決して `PlewArray_Ref_Cell` 等に正しくマングルするよう拡張が要る。
- **F12〔中〕U64 リテラル ∈ [2^63, 2^64-1] で plewc がクラッシュ**：`18446744073709551615U64` 等で「panic: integer overflow」。リテラル値が `Expr.Int.value: I64` に蓄積され、`tokenValue` の digit 蓄積（`value*10+digit`）が I64 範囲を超え、コンパイラ自身の overflow check が panic。修正＝値表現を U64 化（lexer 蓄積 U64・`Expr.Int.value` U64・codegen の符号なし出力・範囲検査と負リテラル畳み込みの符号配慮）＝**整数リテラルの符号モデルに波及**。コンパイラ自身は該当リテラルを使わずビルド可＝影響はユーザーの巨大 U64 リテラルのみ（edge）。
- **F10 残：配列要素越しの変更の未対応分**：`arr[i].field = x`（plain `=`）は実装済（`tryArrayElemFieldAssign`）。残り＝(a) `arr[i].field OP= v`（compound）＝現状 loud-reject 済（`reject/array_elem_field_compound`）→ checked arith 付き get-modify-set の実装。(b) `arr[i].inoutMethod()`＝メソッド呼び codegen が `&(get(...))`＝rvalue アドレスで不正 C＝**まだ loud-reject すらしていない**（要対応）。(c) 多段 `a.b[i].c = x`・heap フィールド値の ARC 整合は未検証。
- **F14 残：generic struct のフィールド既定値**：非 generic struct の `val x: T = expr` は実装済（`FieldDef.hasDefault`＋`Expr.Make` 挿入）。残り＝generic struct は `Expr.Make` の `if generic {}` で default 挿入をスキップ（未対応）・default 式の literal 型検査は未（codegen は通る）。
- **F8〔小〕裸の no-field enum variant 値**：`Color.Green`（`<Color.Green/>` でない）が `Color.Green` をそのまま C 出力＝不正。構築は常に JSX なので loud-reject すべき（`use <Type.Variant /> to construct`）。
- **F15〔小〕ビルトインメソッド名と同名のユーザー自由関数が誤コンパイル**：`fn count(...)` のような、配列等のビルトインプロパティ/メソッド名（`count` 等）と同名のトップレベル関数を呼ぶと call codegen が特別扱いして誤った C を出す（`count(...)` が `.count` 系の脱糖に巻き込まれる疑い）。要 loud-reject か名前空間分離。edge だが silent 誤コンパイル。
- **F6 `;` 文区切り・catch-all 誤診断**：`;` を文区切りに使うと value-0 Int 合成で「no type from context」誤診断（本来は構文エラー）。加えて「integer literal has no type from context」が多くの未対応経路の包括誤診断になっており、診断の精度向上余地が大きい。
- **未解決識別子の raw 出力〔小〕**：未定義の識別子（例：メソッド内で `self.` を忘れた裸のフィールド名 `n`）が解決失敗時にそのまま C へ出力され clang エラーになる。Plew レベルで「unknown identifier」を loud-reject すべき（catch-all 誤診断の改善とセット）。
- **gap #2 `.bytes` 等の field チェーン後置型**：`s.bytes`（String→Array[U8]）の exprType が scalar に落ちるため、`val bs = s.bytes`（注釈なし）の推論不可・`s.bytes.count` も `.count` が `.len` に脱糖されず PlewArray_U8 に直当てで不可（注釈や直 local なら可）。F1/F11 と同根の name-span/exprType 問題。
- **Ref 構築のリテラル型付け**：`<Ref[I32] value=7/>` が**注釈ありでも** `value=7` のリテラルを Ref[I32] の T から型付けできず落ちる（`value=7I32` の suffix が要る）。JSX フィールド型からの literal 文脈型付けの穴。
- **closure が shadow された local をキャプチャ〔極小・稀〕**：F2 の cnum（shadow 用 C 名 suffix）は capture-init 経路（enclosing 名を素の writeSpan で出す）に未配線。shadow 変数をキャプチャする極端ケースのみ C 名不一致になり得る（壊れても loud）。
- **N4b〔小〕for ループ変数の型注釈が範囲境界へ伝播しない**：`for val i: I32 in 0..<5` は注釈 I32 があっても境界リテラルに型文脈が伝わらず「no type from context」。回避＝境界に suffix（`0..<5I32`）。設計上「範囲境界リテラルは型必須」（for.pw に明記）なので非バグだが、ループ変数注釈を context に使う改善余地。
- **演算子トレイト（Eq/Ord 以外）未配線**・**曖昧な untyped-literal オーバーロード**・**`@[Ord]` on enum 未対応**：[provisional.md](provisional.md) 記載の既知の需要駆動項目。
