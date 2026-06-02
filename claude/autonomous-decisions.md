# 自走中に仮決めした判断の一覧

> ユーザーが長期離席中、「ランタイム完成まで止まらず実装」する制約下で、**判断に迷ったが続行のために仮決めした**項目の一覧。後でユーザーが見直す用。各項目＝**何を／なぜ仮決め／見直し方・代替案**。spec 表面に関わるものは特に要レビュー。確定済みの spec 剥離カタログは [provisional.md](provisional.md)、現在地は [worklog.md](worklog.md)。

## generics（G1〜G3）

- **コアライブラリの設置位置＝`compiler/std/`**。`@Std/X` を `dirname(argv[0]) + "std/" + X + ".pw"` で解決（`compiler/plewc` 起動なら `compiler/std/X.pw`）。
  - なぜ仮決め：実体位置に確たる根拠なし。env var／インストール時展開／バイナリ埋め込み等いろいろあり得る。
  - ユーザー確認済の方針（2026-06-03）：**実態位置はどうでもよい**。プログラマ目線で「どこかからインポートできてる」(Rust 風)で OK、最終的にインストール時に適当な場所へ展開。**とりあえず動けば何でも可**。→ 現状の `compiler/std/` 解決で確定扱い（再配置は後で自由）。
- **`Optional`/`Result` は ambient でなく明示 `import @Std/Core` を要求**（spec では ambient＝import 不要）。
  - なぜ仮決め：auto-prelude（常時ロード）は既存テストの自前 `enum Optional` と衝突し、prelude 自己ロード回避等の複雑さがある。明示 import が安全で衝突なし。
  - 見直し方：spec 準拠にするなら `@Std/Core` を prelude として自動ロードし ambient 化（要：自己ロード回避＋名前衝突の扱い）。**acceptance soundness は壊さない**（valid を reject するだけ＝incompleteness）。spec 整合の宿題。
- **generic free 関数・`map[U]` 系・推移的インスタンス化・クロージャは未実装**（generic メソッドはレシーバ型由来で実装済）。
  - なぜ仮決め：呼び出し位置の型引数推論（未型リテラルから不可）＋明示 `id[I32](x)` パース（Go 式判別）、メソッド独自型パラメータ、body 内生成インスタンスの推移発見、関数型/クロージャ ── いずれも大物で、コアライブラリの当面の必要（データ＋match＋レシーバ型メソッド）には不要。
  - 見直し方：コアライブラリが `map`/`flatMap` を要求した時点で着手（worklog の G3 残り設計参照）。

## エラー処理（try / ??）

- **`try` はエラー型一致を要求（`From` 変換なし）**。spec では `try` が `Err` 時に `<E from=f />`（From）でエラー型変換する。第一カットは未実装＝ソース `Result[T,E]` と関数戻り `Result[U,E']` の **E==E' 必須**（違うと生成 C が型不一致）。見直し：From トレイト実装後に変換挿入。
- **`?.`（オプショナルチェーン）未実装**。`??`・`match`・`try` でカバー。見直し：spec/13 の `?.` を後で。
- **`??`/`try` は `@Std/Core` の Optional/Result の形に密結合**（Some=tag0/field `v`、Ok=tag0/field `value`、Err=tag1/field `error` をハードコード）。lang-item ゆえ妥当だが、ユーザーが別形の Optional を定義しても `??` はこの形を仮定。見直し：lang-item を spec で固定 or コンパイラが Core のシンボルを参照。

## ランタイム：値意味論（CoW）

- **eager copy で観測可能な値意味論を実現**（拠り所：意味は正しく・コスト〔遅延 CoW・解放〕は裏で後回し可）。コピー挿入点＝`val/mut val` 配列束縛・配列代入・JSX 配列フィールド初期化（いずれもソースが place のとき `PlewArray_E_copy`）。String は不変ゆえ共有で正しい（コピー不要）。**メモリは leak のまま**（解放は後回し hidden cost）。
- **by-value 引数はコピーしない＝これは穴ではない**：spec で関数引数はイミュータブル（変更には `inout`）。変更不能ゆえ共有とコピーは観測同一。`inout` はポインタ（意図的共有）。よって引数コピー不要＝**eager copy を hot path に入れずに済み自己ホスト性能を保てる**（全引数を deep copy すると O(n)/call で壊滅する、を回避）。
- ✅ **観測可能な穴は解消済**：①struct コピー時の配列フィールド（`structNeedsCopy`＋`Name_copy` 再帰）②place 配列/struct の return（return 地点でコピー）も実装。**コピー挿入点＝配列 let/代入/JSX フィールド・mutable struct let/代入・return（配列/struct）**。by-value 引数はイミュータブルゆえ不要。残るは深いエッジ（generic-inst/enum フィールド内の配列の深いコピー＝mono struct/enum の copy 関数は未＝`Optional[Array[I32]]` 等のコンテナ内配列）。
- **完全＆高速な CoW（refcount＋スコープ解放）は大物 ARC として後段**。eager copy は「mutable 束縛は稀＆小さい」前提で安全だが、性能最適化（遅延コピー）と解放（leak 解消）は refcount 版でないと埋まらない。`inout` と CoW の相互作用（inflated refcount で inout が in-place 変更できなくなる問題）＝正確な解放が前提。

## 既知の別件（generics 以前からの仮決め・関連）

- **C 予約語と衝突する Plew 識別子**（`default`/`double` 等）は生成 C が壊れる＝名前マングリング未実装。コンパイラ自身は回避。ユーザーコードで顕在化する hidden-meaning 穴（acceptance soundness 対象）。見直し：codegen で識別子を安全な C 名にマングル。
- メモリは leak（free しない）＝CoW/ARC 未実装の hidden cost（[provisional.md](provisional.md)・拠り所上は後回し可）。

> 運用：以後この自走で仮決めするたびここへ追記する。確定したら該当項目を消す／provisional.md or spec へ移す。
