# 自走中に仮決めした判断の一覧

> ユーザーが長期離席中、「ランタイム完成まで止まらず実装」する制約下で、**判断に迷ったが続行のために仮決めした**項目の一覧。後でユーザーが見直す用。各項目＝**何を／なぜ仮決め／見直し方・代替案**。spec 表面に関わるものは特に要レビュー。確定済みの spec 剥離カタログは [provisional.md](provisional.md)、現在地は [worklog.md](worklog.md)。

## generics（G1〜G3）

- **generic free 関数・`map[U]` 系・推移的インスタンス化・クロージャは未実装**（generic メソッドはレシーバ型由来で実装済）。
  - なぜ仮決め：呼び出し位置の型引数推論（未型リテラルから不可）＋明示 `id[I32](x)` パース（Go 式判別）、メソッド独自型パラメータ、body 内生成インスタンスの推移発見、関数型/クロージャ ── いずれも大物で、コアライブラリの当面の必要（データ＋match＋レシーバ型メソッド）には不要。
  - 見直し方：コアライブラリが `map`/`flatMap` を要求した時点で着手（worklog の G3 残り設計参照）。

## エラー処理（try / ??）

- **`try` はエラー型一致を要求（`From` 変換なし）**。spec では `try` が `Err` 時に `<E from=f />`（From）でエラー型変換する。第一カットは未実装＝ソース `Result[T,E]` と関数戻り `Result[U,E']` の **E==E' 必須**（違うと生成 C が型不一致）。見直し：From トレイト実装後に変換挿入。
- **`?.`（オプショナルチェーン）未実装**。`??`・`match`・`try` でカバー。見直し：spec/13 の `?.` を後で。
- ✅ **`assert(x > 0)` / `assert(x > 0, message: "...")` 実装済（spec 忠実）**＝`@Std/Core` 純 Plew `fn assert(cond~: Bool, message: String = "assertion failed")`。**ラベル抑制 `~:`** と **デフォルト引数 `name: T = expr`** も実装。
- **デフォルト引数 v1 の限定（deferred）**：末尾省略のみ（spec の「ラベルで中間省略・省略組合せがセレクタ集合に合流」は未）。デフォルト式は呼び出し位置で genExpr（spec の「定義側スコープで評価・他引数/self 参照不可」は単純式では問題なし）。配列/struct のデフォルト（`= []` 等）は要素文脈が無く未対応＝単純値のみ。
- **`??`/`try` は `@Std/Core` の Optional/Result の形に密結合**（Some=tag0/field `v`、Ok=tag0/field `value`、Err=tag1/field `error` をハードコード）。lang-item ゆえ妥当だが、ユーザーが別形の Optional を定義しても `??` はこの形を仮定。見直し：lang-item を spec で固定 or コンパイラが Core のシンボルを参照。

## ランタイム：値意味論（CoW）

- **eager copy で観測可能な値意味論を実現**（拠り所：意味は正しく・コスト〔遅延 CoW・解放〕は裏で後回し可）。コピー挿入点＝`val/mut val` 配列束縛・配列代入・JSX 配列フィールド初期化（いずれもソースが place のとき `PlewArray_E_copy`）。String は不変ゆえ共有で正しい（コピー不要）。**メモリは leak のまま**（解放は後回し hidden cost）。
- **by-value 引数はコピーしない＝これは穴ではない**：spec で関数引数はイミュータブル（変更には `inout`）。変更不能ゆえ共有とコピーは観測同一。`inout` はポインタ（意図的共有）。よって引数コピー不要＝**eager copy を hot path に入れずに済み自己ホスト性能を保てる**（全引数を deep copy すると O(n)/call で壊滅する、を回避）。
- ✅ **観測可能な範囲は完成**＝plain 配列・struct（配列フィールド・再帰）・**generic struct/enum コンテナ**（`Box[Array]`/`Maybe[Array]`＝mono copy 関数）まで全部コピー。コピー挿入点＝配列/struct/generic-inst の let/代入/JSX フィールド/return（`genCopyValue` 統一）。by-value 引数はイミュータブルゆえ不要。match bind も generic enum で置換型。残るは leak（解放）と遅延コピーのみ＝refcount 版 hidden-cost 最適化（後段 ARC）。
- **完全＆高速な CoW（refcount＋スコープ解放）は大物 ARC として後段**。eager copy は「mutable 束縛は稀＆小さい」前提で安全だが、性能最適化（遅延コピー）と解放（leak 解消）は refcount 版でないと埋まらない。`inout` と CoW の相互作用（inflated refcount で inout が in-place 変更できなくなる問題）＝正確な解放が前提。

## クロージャ / 関数値（イベントループの土台）

- ✅ **関数型 `fn(label:T,...)->R`＋関数を第一級値**（C 関数ポインタ typedef・関数名は decay・間接呼び出し）と **非キャプチャのクロージャリテラル**（`fn(...)->R{body}`＝ラムダリフティングで `__closure<id>` に）を実装（`tests/run/{fn_value,closure_literal}`）。ラベルは型から落とし C は位置引数。
- **キャプチャ未実装（deferred・大物）**：外側ローカルを参照するクロージャ（`makeCounter` 等）は env が要る＝**環境構造体＋fat closure（{fn ptr, env ptr}）＋エスケープ解析でキャプチャ変数をヒープ化**。現状の bare 関数ポインタ表現を fat に変える必要＝関数型/呼び出し/全経路に波及。spec は参照キャプチャ（Swift 流・`mut val` は共有可変）。**`spawn { block }` はキャプチャ必須**ゆえイベントループの前提。
- これらにより `map`/高階関数の**自由関数版**（`mapI32(arr, f: fn(...))`）は今書ける。`Array.map[U]` は generic own 型パラメータ＋推移的インスタンス化が別途要る。

## 既知の別件（generics 以前からの仮決め・関連）

- **C 予約語と衝突する Plew 識別子**（`default`/`double` 等）は生成 C が壊れる＝名前マングリング未実装。コンパイラ自身は回避。ユーザーコードで顕在化する hidden-meaning 穴（acceptance soundness 対象）。見直し：codegen で識別子を安全な C 名にマングル。
- メモリは leak（free しない）＝CoW/ARC 未実装の hidden cost（[provisional.md](provisional.md)・拠り所上は後回し可）。

> 運用：以後この自走で仮決めするたびここへ追記する。確定したら該当項目を消す／provisional.md or spec へ移す。
