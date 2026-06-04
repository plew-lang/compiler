# 確認事項メモ（未解決・あとで対応／確認したい項目）

> 「作業を止めずに進めるが、**あとで対応・判断したい**」未解決項目を溜める場所。
> - **バグ修正の現況（解決済み含む）**は [worklog.md](worklog.md) 冒頭の「バグ調査カタログ」を正典とする（F 番号はそちら）。
> - 区分：「① 要ユーザー判断」「② 据え置き（理由あり）」「③ 残・順次対応可」。
> - **解決したら該当項目を消す**（このファイルは未解決だけを映す）。

## ① 要ユーザー判断（言語仕様に触れる）

- 現在なし。直近の決定（String リテラル単相・struct フィールドはカンマ不採用/改行区切り・enum バリアントの record 形式移行）は spec と [design-decisions.md](design-decisions.md) に反映済み。

## ② 据え置き（理由あり・大物 or 設計）

- **F11〔大筋✅実装済・残は精緻化〕複合要素型の配列**：`Array[Ref[T]]`（spec 推奨の共有/unique 要素）・`Array[Box[T]]`（generic struct 要素）・`Array[Array[T]]`（ネスト・依存順序＋`m[i][j]`）が動作。仕組み＝複合要素にマングル名 span（`appendMangle` で `Ref_I32` を `c.bytes` 末尾に追記）を与え全経路で共有、C 型/ARC は `c.arrayElems` の ref から `genCElem`/runtime が復元（単純要素は頭名のまま＝出力不変・fixpoint 保持）。test `run/array_compound_elem`・`run/array_nested`。**残（精緻化）**：
  - (a) 配列リテラルを**要素として** append（`m.append([1,2,3])` for `Array[Array[I32]]`）が「no type from context」。`.append`/`.push` はビルトインで専用 codegen 経路を通り、要素型が配列のとき引数の内側リテラルを型付けしない（ユーザー関数の配列リテラル引数は F16 で対応済だがビルトインは未）。check/codegen で要素型が配列なら `checkLitArray`＋`genArrayValue` を使う。スカラー append（`xs.append(10)`）・変数 append（`m.append(row)`）は動く。
  - (b) **要素 ARC**：`Array[Ref[T]]` の Ref 箱は現状ビットコピー（retain/release せず）＝箱が leak（project の hidden-cost 許容方針内）。`xs.append(refVar)` 後に refVar を release する稀パターンでは UAF 余地あり＝runtime の要素 retain/release（push/set/copy/release）を ref のkind別に出す精緻化が要る。
  - (c)〔**F11 特有でなく既存の generics ギャップ**〕**`Array[T]`（型パラメータ要素）の単相化**：generic struct/関数の `Array[T]` フィールド/引数を具体型で実体化すると、配列ランタイムが要素名 "T" を literal 出力（`PlewArray_T`・`T* data`＝unknown）＝**単純 T=I32 でも落ちる**（worklog の「generic 型引数の配列」additive 項）。F11 は直接書いた `Array[Ref[Cell]]` を直したが、`Holder[Ref[Cell]]`（field が `Array[T]`）等は型引数越しでこのギャップに当たる。直し＝配列要素の型パラメータを `curTypeArgs` で解決し mangle 名へ substitute（複合 T も同時に通る）。
- **F12〔中・据え置き：整数リテラル符号モデル〕U64 リテラル ∈ [2^63, 2^64-1] で plewc がクラッシュ**：`tokenValue` が値を I64 で蓄積（`v*10+digit`）し I64 範囲超過でコンパイラ自身の overflow check が panic。直すには値表現を U64 化（`Expr.Int.value` U64・lexer 蓄積 U64・符号なし codegen・範囲検査・**負リテラル `-128` 畳み込みとの両立に符号フラグ**）＝整数リテラルの符号モデルに波及。影響はユーザーの巨大 U64 リテラルのみ（稀）。
- **演算子トレイト（Eq/Ord 以外）/ `@[Ord]` on enum / 曖昧な untyped-literal オーバーロード**：トレイト体系の大物・需要駆動。[provisional.md](provisional.md) のロードマップで管理。

## ③ 残（順次対応可・小〜中）

- **F4 残：for / guard の struct 分解**：`for Person { val name } in people`・`guard S { val x } = …`（spec/11）。match の struct 分解は実装済（`run/struct_pattern`）。for/guard のヘッダ分解は別 codegen で未対応。
- **F14 残：default 式の literal 型検査**：generic/非 generic とも、フィールド既定値式（`val n: I32 = 0`）の literal が field 型に対して型検査されていない（codegen は通る）。検査を足すと健全性が上がる。
- **closure が shadow された local をキャプチャ〔極小・稀・loud〕**：F2 の shadow 用 C 名 suffix（`cnum`）が `emitCaptureInit`（enclosing 名を素の writeSpan で出す）に未配線。shadow 変数をキャプチャする極端ケースのみ C 名不一致になり得る（壊れても clang エラー＝loud・silent でない）。well-tested な closure コードへの回帰リスクに見合わず低優先。
- **N4b〔小・ほぼ by-design〕for ループ変数の型注釈が範囲境界へ伝播しない**：`for val i: I32 in 0..<5` は境界リテラルに型文脈が伝わらず「no type from context」。回避＝境界に suffix（`0..<5I32`）。設計上「範囲境界リテラルは型必須」（for.pw 明記）なので非バグ寄りだが、ループ変数注釈を context に使う改善余地。
