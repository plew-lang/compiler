# 確認事項メモ（あとでユーザーと確認したい項目）

> このファイルは「作業を止めずに進めるが、**あとでユーザーに確認・判断してもらった方がよい**」項目を溜める場所。
> - **進行中のバグ修正の現況**は [worklog.md](worklog.md) 冒頭の「バグ調査カタログ」を正典とする（F1…の番号はそちら）。
> - ここには「①要ユーザー判断（言語仕様に触れる・後戻りが重い）」「②判断不要だが据え置いた実装（メモだけ）」を分けて書く。
> - 解決したら該当項目を消す。

## ① 要ユーザー判断（言語仕様に触れる・確認したい）

- **（決定済 2026-06-04）String リテラルは単相のまま確定**：数値リテラルを多相にした動機（自然な既定型が無い）が String には無く（`String` が唯一の正典型）、Plew は暗黙の literal 多相（Swift `ExpressibleByStringLiteral`）より明示構築（`<T from="…"/>`＝`From`）を好むため。将来「文字列リテラルから作る別型」（`StaticString`・`b"…"`→`Array[U8]`・Char）が要れば**別リテラル構文 or `From`** で解く（リテラル多相化はしない）。→ この決定に伴い **F1 の String 裸リテラル推論の loud-error は撤回し `val s = "…"` を素直に String 推論**するよう修正済（`stringTypeSpan` がソース中の "String" 6バイトを span として流用＝既存の名前ベース型機構に乗せる・"String" がソースに皆無の degenerate ケースのみ注釈要求の fallback）。test `run/let_infer_string`。

- **（未決）struct/enum フィールド・variant フィールドの区切り**：spec/05 の例は**改行区切り**のみ。F7 でカンマ区切り struct フィールドを loud-reject にした（`struct P { val x: I32, val y: I32 }` → エラー）。
  - **確認したいこと**：カンマ区切りも許容したいか（friendlier だが spec に無い）。現状は spec 準拠で改行のみ・カンマ reject。enum variant フィールドの複数列挙の区切りも同様に要確認（現状コンパイラは単一フィールド variant しか使っていない）。

## ② 判断不要・据え置いた実装（メモのみ・順次対応可）

- **F3 トップレベル変数（`val`/`mut val` をモジュール直下）**：`parseProgram` が未対応で黙殺＝"undeclared identifier"。実装には spec/15 の初期化順（全トップレベル/assoc val → main）の配線が要る（feature 規模）。まず最低限 **loud-reject**（未対応と明示）に倒すのが安全な中間段。
- **F4 struct 分解パターン `P { val x, val y }`**（match/for/guard）：spec/11 正典。現状 enum バリアント分解のみ対応で、非 enum struct パターンは catch-all 誤診断で落ちる。`parsePattern` が型名後に `.` 無しでも variant を読む点の修正＋ match codegen に struct（タグ無し・`_m.field` 直読み・irrefutable 単一アーム）経路の追加が要る。
- **gap #2 `.bytes` 等の field チェーン後置型**：`s.bytes`（String→Array[U8]）の exprType が未対応で `val bs = s.bytes`（注釈なし）が推論できない（注釈ありなら可）。F1 とは別件。これも name span 問題（"U8"/"Array" の span）に当たる。
- **Ref 構築のリテラル型付け**：`<Ref[I32] value=7/>` が**注釈ありでも** `value=7` のリテラルを Ref[I32] の T から型付けできず落ちる（`value=7I32` の suffix が要る）。JSX フィールド型からの literal 文脈型付けの穴。
- **F6 `;` 文区切り・catch-all 誤診断**：`;` を文区切りに使うと value-0 Int 合成で「no type from context」誤診断（本来は構文エラー）。加えて「integer literal has no type from context」が多くの未対応経路の包括誤診断になっており、診断の精度向上余地が大きい。
- **closure が shadow された local をキャプチャ**：F2 の cnum は capture-init 経路（enclosing 名を素の writeSpan で出す）に未配線。shadow 変数をキャプチャする極端ケースのみ C 名不一致になり得る（稀・壊れても loud）。
- **F10〔一部✅修正済（未コミット）〕配列要素越しの place 変更**：`arr[i].field = x`（plain `=`）は実装済＝`Stmt.Assign` の `tryArrayElemFieldAssign` が get-modify-set（`PlewArray_E_set(&arr, i, ({ E __ge = get(arr,i); __ge.field = v; __ge; }))`）に脱糖。フィールド/配列束縛の mut 検査は `placeIsMutable(target)`。test `run/array_elem_field_set`。**残（未対応・loud-reject 済 or 要追加）**：(a) `arr[i].field OP= v`（compound）＝loud-reject 済（`reject/array_elem_field_compound`）＝要実装（checked arith 付き get-modify-set）。(b) `arr[i].inoutMethod()`＝メソッド呼び codegen が `&(get(...))`＝rvalue アドレスで不正 C＝**まだ loud-reject すらしていない**（要対応）。(c) 多段 `a.b[i].c = x` や heap フィールド値の ARC 整合は未検証。
- **F8〔小・未着手〕裸の no-field enum variant 値**：`Color.Green`（`<Color.Green/>` でない）が `Color.Green` をそのまま C 出力＝不正。構築は常に JSX なので loud-reject すべき（`use <Type.Variant /> to construct`）。
- **未解決識別子の raw 出力〔小・未着手〕**：未定義の識別子（例：メソッド内で `self.` を忘れた裸のフィールド名 `n`）が解決失敗時にそのまま C へ出力され clang エラーになる。Plew レベルで「unknown identifier」を loud-reject すべき（catch-all 誤診断の改善とセット）。
- **F12〔中・未着手〕U64 リテラル ∈ [2^63, 2^64-1] で plewc がクラッシュ**：`18446744073709551615U64` 等で「panic: integer overflow」。リテラル値が `Expr.Int.value: I64` に蓄積され、`tokenValue` の digit 蓄積（`value*10+digit`）が I64 範囲を超え、コンパイラ自身の overflow check が panic。修正＝値表現を U64 化（lexer 蓄積 U64・`Expr.Int.value` U64・codegen の符号なし出力・範囲検査と負リテラル畳み込みの符号配慮）。**整数リテラルの符号モデルに波及＝チェックポイントを切れる状態（GPG 回復後）で慎重に。** コンパイラ自身は該当リテラルを使わずビルド可＝影響はユーザーの巨大 U64 リテラルのみ（edge）。
- **F11〔中・重要・未着手〕複合要素型の配列**：要素型が**複合型**（`Array[Array[T]]`・`Array[Ref[T]]`・`Array[Box[T]]` 等の generic/Ref/array）だと要素型マングルが内側型を解決できず、要素型名に頭名（`Array`/`Ref`/…）を literal 出力（`PlewArray_Ref`・`Ref* data`＝unknown type）。**`Array[Ref[T]]` は spec 推奨の「unique 要素は Ref 包み」「共有要素」パターンなので重要度高**（matrix／list-of-list／shared 要素配列で顕在化）。`recordArrayElem`／要素型マングル（`wPA`/`genCElem` 系）が要素の structured type を解決して `PlewArray_Ref_Cell` 等に正しくマングルするよう拡張が要る。
- **F14〔✅修正済（未コミット）〕struct フィールド既定値**：`struct Config { val timeout: I32 = 30 }`（spec/05 memberwise factory 既定引数糖衣）。修正＝(1) `parseStruct` が型の後の `Kind.Eq` で既定値式を parse し `FieldDef.hasDefault/defaultVal` に保持（AST 追加）／(2) `Expr.Make`（非 enum struct）が省略フィールドを `c.structs` の宣言から走査し、default 付きなら `.field = <default>` を挿入（`makeProvides` で省略判定・array 既定は genArrayValue で `[]` も可）。test `run/field_defaults`（scalar/partial/非スカラー `[]`）。残＝generic struct の field default は未対応（`if generic {}` でスキップ）・default 式の literal 型検査は未（codegen は通る）。
- **F13〔✅修正済（未コミット）〕配列型のデフォルト引数が `0` を生成**：`fn f(xs: Array[I32] = [])` の省略呼びが `f(0)`＝不正 C。修正＝`Expr.Call`／assoc-fn の default-fill ループで param が `tyIsArray` なら genArrayValue を使う（genExpr だと `[]` が 0）。test `run/default_arg_array`。残＝struct/Ref 型のデフォルト引数（genExpr が Make を扱うので動くはずだが未テスト）・generic param の array default。
- **F16〔✅修正済（未コミット）〕配列リテラルを引数で渡すと `0`**：`f(xs: [1,2,3])` が `f(0)`＝不正 C（提供引数ループが genExpr を使い、配列リテラルに要素型文脈が無い）。修正＝引数ループで対応 param が `tyIsArray` なら genArrayValue（要素型は param の tyStart/tyLen）。test `run/default_arg_array`（`tally(xs: [1,2,3])` 等）。
- **F15〔小・未着手〕ビルトインメソッド名と同名のユーザー自由関数が誤コンパイル**：`fn count(...)` のような、配列等のビルトインプロパティ/メソッド名（`count` 等）と同名のトップレベル関数を呼ぶと call codegen が特別扱いして誤った C を出す（`count(...)` が `.count` 系の脱糖に巻き込まれる疑い）。要 loud-reject か名前空間分離。edge だが silent 誤コンパイル。
- **N4b〔小〕for ループ変数の型注釈が範囲境界へ伝播しない**：`for val i: I32 in 0..<5` は注釈 I32 があっても境界リテラルに型文脈が伝わらず「no type from context」。回避＝境界に suffix（`0..<5I32`）。設計上「範囲境界リテラルは型必須」（for.pw に明記）なので非バグだが、ループ変数注釈を context に使う改善余地。
- **gap #2 再確認**：`s.bytes.count`（String.bytes→Array の `.count`）は `.bytes` の exprType が scalar に落ちるため `.count` が `.len` に脱糖されず PlewArray_U8 に直当て＝コンパイル不可（注釈や直 local なら可）。F1 と同根の name-span/exprType 問題。
- **演算子トレイト（Eq/Ord 以外）未配線**・**曖昧な untyped-literal オーバーロード**・**`@[Ord]` on enum 未対応**：provisional.md 記載の既知の需要駆動項目。
