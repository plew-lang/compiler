# 確認事項メモ（未解決・あとで対応／確認したい項目）

> 「作業を止めずに進めるが、**あとで対応・判断したい**」未解決項目を溜める場所。
> - **バグ修正の現況（解決済み含む）**は [worklog.md](worklog.md) 冒頭の「バグ調査カタログ」を正典とする（F 番号はそちら）。
> - 区分：「① 要ユーザー判断」「② 据え置き（理由あり）」「③ 残・順次対応可」。
> - **解決したら該当項目を消す**（このファイルは未解決だけを映す）。

## ① 要ユーザー判断（言語仕様に触れる）

- 現在なし。直近の決定（String リテラル単相・struct フィールドはカンマ不採用/改行区切り・enum バリアントの record 形式移行）は spec と [design-decisions.md](design-decisions.md) に反映済み。

## ② 据え置き（理由あり・大物 or 設計）

- **F11〔✅実装済（主要ケース）〕複合要素型の配列**：`Array[Ref[T]]`（spec 推奨）・`Array[Box[T]]`・`Array[Array[T]]`（ネスト）＋ (a) 配列リテラル要素 append ＋ (b) **Ref 要素 ARC**（retain/release・UAF 解消・ASan clean）＋ (c) `Array[T]` 単相化（generic struct・関数・単純/複合 T）が動作。仕組み＝複合要素にマングル名 span（`appendMangle`）、C 型/ARC は ref から復元、型パラメータ要素は `wPA`/`genCElem` が env 解決、Ref 要素は runtime で retain/release。test `run/array_compound_elem`・`array_nested`・`array_generic_field`・`array_generic_fn`・`array_ref_arc`。**残る精緻化（小・後回し可）**：
  - fresh-temp append（`xs.append(<Ref…/>)`）は box を1つ leak（temp の所有権が transfer でなく retain・hidden-cost 許容）。
  - heap 持ち Ref pointee の深い release（`Array[Ref[StructWithHeap]]` の pointee の配列/Ref フィールドが leak・no UAF）。
  - ネスト配列 `Array[Array[T]]` の inner-array 要素 ARC（現状ビットコピー＝leak・no UAF）。
- **Arrow-place 代入のリテラル型付け〔小・新規発見〕**：`ys[0]->v = 42`（Ref pointee フィールドへの代入）の `42` が「no type from context」＝Arrow place 代入の右辺リテラルに pointee フィールド型の文脈が渡らない（`42I32` or 変数で回避可）。`a.b = lit`（通常 field）は動くが `ref->field = lit`（Arrow）が未対応。
- **演算子トレイト（Eq/Ord 以外）/ `@[Ord]` on enum / 曖昧な untyped-literal オーバーロード**：トレイト体系の大物・需要駆動。[provisional.md](provisional.md) のロードマップで管理。

## ③ 残（順次対応可・小〜中）

- **F4 残：for の tuple 分解／`guard` 文**（struct 分解は✅実装済）：`for Person { val name } in people` は実装（`run/for_struct_destructure`・要素 struct を `parsePattern` で分解しフィールドを各反復で束縛・パターン型不一致と range 反復は loud reject）。**残**＝(a) `for (val k, val v) in dict` の tuple/record 分解＝dict 反復子か record 要素が要る（別機能）／(b) `guard` 文そのものが未実装（`KwGuard`/`parseGuard`/`Stmt.Guard` なし・`if`/`while` も refutable 束縛・条件チェーン未対応＝spec/11 の条件チェーン束縛は丸ごと別 feature）。いずれもバグでなく未実装機能。
- **closure が shadow された local をキャプチャ〔極小・稀・loud〕**：F2 の shadow 用 C 名 suffix（`cnum`）が `emitCaptureInit`（enclosing 名を素の writeSpan で出す）に未配線。shadow 変数をキャプチャする極端ケースのみ C 名不一致になり得る（壊れても clang エラー＝loud・silent でない）。well-tested な closure コードへの回帰リスクに見合わず低優先。
- **N4b〔小・ほぼ by-design〕for ループ変数の型注釈が範囲境界へ伝播しない**：`for val i: I32 in 0..<5` は境界リテラルに型文脈が伝わらず「no type from context」。回避＝境界に suffix（`0..<5I32`）。設計上「範囲境界リテラルは型必須」（for.pw 明記）なので非バグ寄りだが、ループ変数注釈を context に使う改善余地。
