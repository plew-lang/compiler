# CLAUDE.md

このリポジトリで作業する Claude Code（および将来の貢献者）向けのガイド。**常に意識すべき核**だけをここに置き、必要時に参照する詳細は子ドキュメント（`claude/*.md`・`spec/*.md`）へ寄せている。

## プロジェクト概要

**Plew**（**P**rogramming **L**anguage for **E**veryday **W**izard のバクロニム）のコンパイラを Plew 自身で実装する（🎉 セルフホスト達成済・LLVM 単一 backend）。根幹の設計思想＝**迷ったときの最終的な拠り所**：

> **唱えた通りに発現する。仕組みは問わない。** ── 意味（何をして・どこから来たか）は唱えた通りに発現し、仕組み（どう実現するか）は丸ごと引き受ける。観測挙動が唱えた意味から逸れない限り、裏では好きなだけ動いてよい。

二軸で運用する。**(1) 意味は唱えた通り（透明）**：意味を決める層（字句解析・名前解決・型解決・オーバーロード/トレイト解決・変換）でコンパイラは勝手をしない＝**補完はする／忖度はしない／曖昧はエラー**。**(2) 発現は隠蔽してよい（コストは裏）**：最適化・コード生成・ARC・CoW・スケジューリング・確保といった「人間に難しすぎる魔法」は自由に隠す。**hidden cost は可・hidden meaning/behavior/provenance は不可**。求めるのは「簡単さ（言語が代わりにやる）」ではなく**掌握"感"・正直さ・一貫性**（書いた通りに意味し動いて見えること）。

**ターゲット**＝「複雑な状態を持つクライアントアプリ」主軸に、モノレポでサーバも同一言語で書く**フルスタックのアプリケーション言語**（一次ビーチヘッド＝WASM ウェブ）。**値意味論（CoW）＋ARC＋シングルスレッド + イベントループ（JavaScript ライク）**を採り、資源など必要なときだけ opt-in の最小所有権（`unique`/`borrow`/`inout`/`move`・`Ref`/`WeakRef`）。性能は二の次（拠り所優先）。

現状・到達点・ロードマップは [worklog.md](claude/worklog.md)、アーキ設計・経緯・リポジトリ構成は [architecture.md](claude/architecture.md)、spec からの残ギャップは [provisional.md](claude/provisional.md)。

## ドキュメント（どこに何があるか）

実装に着手する前に、関連する詳細ドキュメントを必ず読むこと：

- **[SPEC.md](SPEC.md)／`spec/*.md`** — 言語仕様の**正典**（構文・意味論）。
- **[claude/language-semantics.md](claude/language-semantics.md)** — spec 意味論の実装者向けダイジェスト＝**章をまたぐ背骨＋間違えやすい罠＋spec 索引**。**他言語と直感が違う領域（値・所有権／トレイト・拡張／可視性・モジュール／演算子・変換／文字列・配列／並行／エラー／メタプロ）は、設計/実装の前にここ＋spec を必ず読む**（地図はここ）。
- **[claude/worklog.md](claude/worklog.md)** — 現在地・次の一歩・ロードマップ・**再利用知見（罠）**・**ビルド/テスト/機能追加手順**（compact 復帰用にこまめ更新）。
- **[claude/architecture.md](claude/architecture.md)** — パイプライン設計・技術スタック・ブートストラップ経緯・**リポジトリ構成**・開発ワークフロー。
- **[claude/design-decisions.md](claude/design-decisions.md)** — 各判断の**根拠・却下案・経緯・未決事項**（「なぜ」専門）。**実装前に未決を確認**。
- **[claude/provisional.md](claude/provisional.md)** — spec から意図的に剥離している箇所のカタログ＝残作業の地図。
- **[claude/metaprogramming-architecture.md](claude/metaprogramming-architecture.md)** — メタプロ（`plew gen`・共有 `@Std/Syntax`・`Derive`）の段取り・実行系。
- **[claude/compiler-refactor.md](claude/compiler-refactor.md)** — コンパイラ構造リファクタの計画（`Comp` god-object 解体・巨大ファイル/モジュール分割）。
- **[claude/grammar.md](claude/grammar.md)** — 構文 × spec 索引。
- **`note/*.md`** — 設計の元になった ChatGPT 会話ログ（一次資料・記法は変遷あり・矛盾したら spec 優先）。

### claude/ の編集方針

spec を**再掲せずリンク**し役割で書き分ける。**残す**＝設計判断の根拠・却下案・経緯・未決。**消す**＝完了した作業メモ・純粋な作業ログ（git が記録）。**文脈非依存に書く**（「前回／今セッション」等の会話自己参照を使わない・各エントリ単体で意味が通るよう）。**重複を避け**、決定したら spec（正典）＋claude 双方を即同期し grep で陳腐化を点検。

## 実装上の最重要原則

1. **正典は `SPEC.md`／`spec/*.md`**。構文解析は手書き再帰下降パーサ＝共有 `@Std/Syntax`（旧 ANTLR `Plew.g4` は破棄済）。`note/` と矛盾したら spec 優先。
2. **全制約の根＝値意味論 + CoW + ARC + opt-in 所有権**。代入・受け渡しは独立コピー（CoW で遅延）・共有可変は `Ref` のみ・メモリは ARC（循環は `WeakRef`）。`val` の不変性が信頼でき・`deinit` で資源を決定的に解放でき、並行性は「借用は async/spawn 境界を越えず・spawn は move/copy のみ・`Ref` は spawn 不可」で**実質 race-free・`Mutex` 不要**。詳細は [language-semantics.md](claude/language-semantics.md)＋spec/03,14。
3. **他言語と異なる領域は実装前に spec＋[language-semantics.md](claude/language-semantics.md) を必ず読む**（罠・背骨の地図はそこ）。**メタプロ**は骨格確定（入力 AST／出力 String・別コマンド `plew gen` が `<Foo>.gen.pw` 生成）＝段取りは [metaprogramming-architecture.md](claude/metaprogramming-architecture.md)＋spec/16。**設計の未決**は [design-decisions.md](claude/design-decisions.md) で確認（言語の大物はほぼ決着・残るは実装/コアライブラリ寄り＝チャネル/FFI/数値トレイト署名/テストランナー等）。

## コーディング規約（Plew 言語側）

- **casing**：型名・enum バリアント＝**PascalCase**／変数・関数・定数（`val`/`assoc val`）・引数ラベル・能力マーカー＝**camelCase**（SCREAMING_SNAKE 不使用）。import/part のパス成分（ファイル/ディレクトリ名）＝PascalCase（`.`/`..`/`_.pw` の `_` のみ例外）・拡張子 `.pw`。
- **生成は JSX/factory に集約**（構築点が可視）：`<Type field=expr />`／無名レコードは `(label: expr)`／ブロックを式にするには `give`。フィールド宣言時デフォルト値可。**既定 memberwise factory は not pub**（公開は `pub impl Type { factory }`）。失敗し得る生成は `optional factory`／`result[E] factory`。詳細は spec/05。
- **引数名・ラベル抑制の規約**（正典＝[spec/04「引数名とラベルの指針」](spec/01-basics/04-functions.md#引数名とラベルの指針規約)）：名前は値を表す**名詞**（一文字・暗号名・前置詞ラベル不可・短縮は `~:` 省略で／略語にしない）。ラベルが冗長なら `~:` で省略 ── ①主語（→ メソッドのレシーバ化／通すコンテキストは省略）②直接目的語（**サイン＝名前が `value`/`item` のように空っぽ**・付加部 `index`/`key` はラベル残す）③型同名エコー `f(account: Account)`。区別すべき同型の兄弟がいればラベル必須。`factory` は `~:` 不可。
- **ファクトリ名の規約**（正典＝[spec/05「ファクトリ名の指針」](spec/02-type-system/05-structs-enums.md#ファクトリ名の指針規約)）：factory 名は暗黙の「生成（create）」の**修飾語**＝結果/手段を表す**形容詞・名詞**（✗ 単独動詞・目的語なし動詞）・名前とラベルで重複しない・簡潔。

## 作業の進め方・ユーザーについて

これまでのセッションで分かった進め方。

- **判断を仰ぐときは「選択肢＋トレードオフ＋推奨（理由）」を簡潔に**。決定の含意を最後まで追い、他所に生じる矛盾・抜け（呼び出し側の整合・既存規則との衝突）を**先回りで指摘**する。ユーザーは納得すれば即決する。
- **実装の順序・段取りは全面委任**（どの機能から・増分の切り方は確認不要で自走）。一方で**言語表面の設計判断・後戻りが重い分岐（spec 未記載の構文/意味論）と大物アーキ判断（バックエンド方式・バイナリ構成・ブートストラップ戦略）は自走せず一旦止まって確認**する。明白に不要なファイルは消してよい。迷ったら突き進まず仰ぐ。
- **リファクタは随時・委任**：観測挙動（テスト・不動点）を変えない純リファクタは確認不要・意味論を変える整理だけ仰ぐ。**周囲の古い書き方に引きずられず、触る箇所すべてで「今の Plew でもっと良く書けないか」を毎回・強く問う**（例＝空 then の `if foo {} else { f() }`→`if !foo { f() }`・手 match の Optional→`?.`/`unwrapOr`/`guard`）。ただし「今は直せない workaround（まだ無い機能の代用）」は無理に直さない。詳細・watch-list は [compiler-refactor.md](claude/compiler-refactor.md)「リファクタの心構え」。
- **明示 > 暗黙・便利**（意味/出どころは明示・コスト/機構は隠す＝CoW/ARC を隠すことと矛盾しない）。冗長でも追跡可能を好み、ambient（Swift 的「どこからでも見える」）を嫌い provenance を重視。**単純 > 強力だが紛らわしい**（使いこなしにくい機能は切る・暗黙ルールは最小）。
- **主張は根拠で・誇張しない**。ユーザーは通説や私の主張を検証してくる。間違えたら素直に撤回・再評価し守りに入らない。避けられないトレードオフは欠点を隠さず明示する。
- **根本方針も再考し得る**：下流の歪み（演算子・変換の不自然さ等）が積もれば、一度決めた前提でも巻き戻す。決定の含意を追い「この方針だとここが歪む」を早めに可視化する。
- **決定したら即同期**：spec（正典）＋`claude/*.md` を更新し grep で陳腐化を点検（章の改番時は相対リンクも sed 一括）。大きな巻き戻しの後は spec を通し読みして齟齬を点検する。
- **commit & push はキリごとに**（大きな塊を溜めない）。コミットメッセージは**英語**で追える粒度。正常動作の区切りでは**記述的 git タグ**（例 `self-host`・`metaprogramming-m1`）。
- **作業ログをこまめに更新**（[worklog.md](claude/worklog.md)）。**メモはすべて repo 内（`CLAUDE.md`／`claude/`）に置き、外部 memory は使わない**。
- **コンパイラの分割は `import` 子モジュール（DAG）が既定**（境界を `import` で切れる塊＝module・過度な細分化は避ける）。**`part` は型の `impl` を定義モジュールに置くためだけ**（part 内は impl のみ・自由関数/型/top-level val は root か別モジュール・相互再帰は型の impl メソッド化で 1 モジュール内に収める・循環 import は常に回避可能＝設計誤り）→ [compiler-refactor.md](claude/compiler-refactor.md)。
- **日本語でやり取りする**。
