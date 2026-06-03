# 確認事項メモ（あとでユーザーと確認したい項目）

> このファイルは「作業を止めずに進めるが、**あとでユーザーに確認・判断してもらった方がよい**」項目を溜める場所。
> - **進行中のバグ修正の現況**は [worklog.md](worklog.md) 冒頭の「バグ調査カタログ」を正典とする（F1…の番号はそちら）。
> - ここには「①要ユーザー判断（言語仕様に触れる・後戻りが重い）」「②判断不要だが据え置いた実装（メモだけ）」を分けて書く。
> - 解決したら該当項目を消す。

## ① 要ユーザー判断（言語仕様に触れる・確認したい）

- **（未決）F1 の String 裸リテラル推論を「loud-error」にした件**：`val s = "hi"`（注釈なし）は現状 `cannot infer the type of this binding; add a type annotation` で reject している。理由＝String の TypeInfo に PlewString を導く name span が無いため（合成 span の仕組みが無い）。
  - 選択肢：(a) 現状維持（注釈必須・明示的）／(b) `c.bytes` から "String" を走査して span を得て `val s = "hi"` を通す（やや hack・ソースに "String" が必ず現れる前提）／(c) Local に型 kind を直接持たせる小リファクタで根治。
  - 推奨：当面 (a)。`val s: String = "hi"` で回避でき、silent 誤コンパイルは無い。需要が出たら (c)。
  - **確認したいこと**：`val s = "hi"` を注釈必須にして良いか（それとも (b)/(c) で通したいか）。

- **（未決）struct/enum フィールド・variant フィールドの区切り**：spec/05 の例は**改行区切り**のみ。F7 でカンマ区切り struct フィールドを loud-reject にした（`struct P { val x: I32, val y: I32 }` → エラー）。
  - **確認したいこと**：カンマ区切りも許容したいか（friendlier だが spec に無い）。現状は spec 準拠で改行のみ・カンマ reject。enum variant フィールドの複数列挙の区切りも同様に要確認（現状コンパイラは単一フィールド variant しか使っていない）。

## ② 判断不要・据え置いた実装（メモのみ・順次対応可）

- **F3 トップレベル変数（`val`/`mut val` をモジュール直下）**：`parseProgram` が未対応で黙殺＝"undeclared identifier"。実装には spec/15 の初期化順（全トップレベル/assoc val → main）の配線が要る（feature 規模）。まず最低限 **loud-reject**（未対応と明示）に倒すのが安全な中間段。
- **F4 struct 分解パターン `P { val x, val y }`**（match/for/guard）：spec/11 正典。現状 enum バリアント分解のみ対応で、非 enum struct パターンは catch-all 誤診断で落ちる。`parsePattern` が型名後に `.` 無しでも variant を読む点の修正＋ match codegen に struct（タグ無し・`_m.field` 直読み・irrefutable 単一アーム）経路の追加が要る。
- **gap #2 `.bytes` 等の field チェーン後置型**：`s.bytes`（String→Array[U8]）の exprType が未対応で `val bs = s.bytes`（注釈なし）が推論できない（注釈ありなら可）。F1 とは別件。これも name span 問題（"U8"/"Array" の span）に当たる。
- **Ref 構築のリテラル型付け**：`<Ref[I32] value=7/>` が**注釈ありでも** `value=7` のリテラルを Ref[I32] の T から型付けできず落ちる（`value=7I32` の suffix が要る）。JSX フィールド型からの literal 文脈型付けの穴。
- **F6 `;` 文区切り・catch-all 誤診断**：`;` を文区切りに使うと value-0 Int 合成で「no type from context」誤診断（本来は構文エラー）。加えて「integer literal has no type from context」が多くの未対応経路の包括誤診断になっており、診断の精度向上余地が大きい。
- **closure が shadow された local をキャプチャ**：F2 の cnum は capture-init 経路（enclosing 名を素の writeSpan で出す）に未配線。shadow 変数をキャプチャする極端ケースのみ C 名不一致になり得る（稀・壊れても loud）。
- **演算子トレイト（Eq/Ord 以外）未配線**・**曖昧な untyped-literal オーバーロード**・**`@[Ord]` on enum 未対応**：provisional.md 記載の既知の需要駆動項目。
