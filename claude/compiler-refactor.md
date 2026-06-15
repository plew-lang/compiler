# コンパイラ構造リファクタ（god-object 解体＋モジュール分割）

正典コンパイラ `compiler/src/` を「現実装の理想像」までリファクタする計画。**なぜ・到達点・マイルストーン・未検証リスク**を残す（進捗の「やった」は git）。現在地は [worklog.md](worklog.md)。

> **現在地（tag）**：M0〜M3（`Comp` god-struct 83→**11 フィールド**・巨大ファイル全分割）＋**M5（scoped resolution＋循環検出）完了**。**M4（モジュール昇格）に着手＝M4-1 完了：IR をデータモジュール `Ir.pw` へ昇格**（旧 `Ast.pw`＝コンパイラ自身の IR 語彙＋共有 `Comp` 算術。パーサ AST = `@Std/Syntax` の `*Ast` とは別物なので名前も是正）。全 IR 型を `export`、passes が cross-module 構築する leaf/decl struct＋`Comp` に pub `factory` を付与、interner サービス（`intern`/`spansEqual` を export・`internHash`/`internGrow` は内部）を `Comp.pushType` の循環回避のため Ir へ同梱。root `_.pw` は `part ./Ast`→`import ./Ir with { … }`。**これがコンパイラ初の cross-module 共有可変 `Comp`**（M0 probe が struct 変異＋enum variant 構築の両方を実証済）。**M4 の主目的は part 撲滅＝モジュール構造を [spec/15](../spec/04-execution/15-modules.md) 準拠に**（91 part の単一モジュール解消）。残り＝**M4-2（逆依存を断ち Backend 独立モジュール化）→ M4-3（Frontend モジュール化）**。型回復統一（typed IR）は part 撲滅に不要と判明し**後段の任意トラックへ退避**（下記）。M5 で resolver を **flat global＋ヒューリスティック＋post-hoc gate** から **scoped resolution** へ移行済：`nameVisibleFrom`（同モジュール定義 or imported+exported）を選択の唯一の基準にし、自由関数（`findFunc`）・型/トレイト（`checkTypeVisibility`）の双方をスコープ化、`detectImportCycles` で DAG を強制（[spec/15 循環依存](../spec/04-execution/15-modules.md#循環依存モジュールグラフは-dag)）。**gate は作らず構造的に解消**（当初計画通り）。M5 は単一モジュールのまま緑を保ったまま完了＝M4 の前提インフラが整った。新カテゴリ `tests/partreject/`（多ファイル reject）追加。

## 診断（何が問題か）

`compiler/src/_.pw` は root が ~18 個の `part` を羅列して 1 つの巨大モジュールを組む形。だが **`part` の羅列は症状**で、原因は2つ：

1. **`Comp`（`Ast.pw:694`・83 フィールドの god-struct）** にコンパイラ全体の状態が集約され、全パスが `c: inout Comp` を取る**自由関数の集まり**として `Comp` を変異させる。`part` は「impl がどうしても肥大するときの抜け道」だが、ここでは「単一の `Comp` を全パスが触る」ことが抜け道を module 規模で常用させている。
2. **ファイルが巨大**：`Backend/Llvm.pw` 11,635 行を筆頭に、Check 3,139／Resolve 2,539／Mono 2,479／Lower 2,088／Verify 1,941／Ast 1,010。人間が一目で「どこに何があるか」を把握できる上限（≈300、最大 500 行）を大きく超える。

### コンパイラというドメインの正しいモデル

「全部入りの god-object」は**コンパイラの正しい形ではない**。`Comp` の 83 フィールドを実際に分類すると 3 層に割れる：

| 層 | 例 | 件数 | 評価 |
|---|---|---|---|
| **(a) 共有 IR/arena** | `bytes`/`exprs`/`stmts`/`funcs`/`structs`/`enums`/`types`/`traits`/`conforms`/`globals`… | ~18 | 中央集約が正解（全フェーズが読む唯一のデータ） |
| **(b) 共有サービス/派生表** | 名前 interner（`intern*`）・型キャッシュ（`exprTy*`）・mono ワークリスト（`genInsts`/`fnInsts`/`captures`）・可視性表（`exports`/`imports`/`moduleRanges`） | ~25 | 中央集約が正解（interner/キャッシュは共有サービス） |
| **(c) パス専用の一時カーソル状態** | `curRetTy`/`locals`/`tmp`/`curTypeParams`/`curRecvInstRef`/`curSelfRef`/`curAsync`/`asyncState`/`verifyMovedIdx`/`curWitnessed`… | **~40** | **god-object の臭い**＝per-pass に置くべき |

**83 の約半分が「パス専用の一時状態」**で、グローバルに置かれているのが問題の本体。これは実在コンパイラの定石「**共有コア＋パス専用コンテキスト**」に反する：rustc は `TyCtxt`（共有）と `FnCtxt`/`FunctionCx`（per-fn）、clang は `ASTContext`／`CodeGenFunction`、LLVM は `Module`（共有）と `IRBuilder`（カーソル）を分ける。この `Comp` は LLVM でいう `Module` と `IRBuilder` を 1 つに溶かした状態。**god-object はコンパイラの本質でなく、フェーズ分離の不在**（[architecture.md](architecture.md)「根① 型付き IR が無い」）という設計負債の症状。

### IR 型は分割できる（DAG・循環なし）

arena ノード（`Expr`/`Stmt`/`Func`/`StructDef`…）の相互参照は**すべて U64 index**（`Binary(lhs: U64, rhs: U64)` 等）で、型として埋め込むのは小さな leaf 型（`Arg`/`Bind`/`MakeField`/`Param`/`MatchArm`）だけ。それらは U64＋span のみを持ち `Expr`/`Stmt` を型として参照し返さない。**型グラフは循環のない DAG** ＝ `Expr`/`Stmt`/`Func` を子モジュールに `export` して `import` できる（`@Std/Syntax` が `ExprAst` 等を export している前例どおり）。

## 到達点（理想像）

**設計原則＝「構造で表現できることをコメントや並び順で代用しない」**（40 フィールドをコメントで仕切るのは負け）。判定基準：

- どのファイルも **≤500 行（理想 ≤300）**。
- どの構造体もフィールドが一目で把握できる粒度（目安 **≤15**）。
- `Comp` は**純粋な共有 IR**で、パス一時状態を持たない。
- 「1 モジュール = 1 主構造体＋少数のヘルパ」に可能な限り寄せる（コンパイラは共有 IR＋パス群ゆえ完全達成は不能＝共有コアは正当に大きい・[worklog](worklog.md) の方針）。

目標レイアウト：

```
compiler/
  Ir/                      ← データモデル（共有コア・凝集データ）
    Tree.pw   Decl.pw   Type.pw      ノード語彙（Expr/Stmt・Func/Struct・TypeRef…）
    Comp.pw                          Comp＝下の子オブジェクトを束ねる薄い composite
    Arena.pw  Interner.pw  TypeCache.pw  MonoWork.pw  ModuleTable.pw  DeclTables.pw  (a)(b) を分割
  Frontend/                ← パス群（import Ir・各々が自前の *Ctx を持つ）
    Lower/ Resolve/ Check/ Infer/ Mono/ Verify/ …（各 ≤500 行・一時状態は LowerCtx/CheckCtx/VerifyCtx へ＝(c)）
  Backend/                 ← モジュール（主構造体 LlvmCtx・import Ir）
    _.pw  Types.pw  Expr.pw  Call.pw  Stmt.pw  GenericStruct.pw  Closure.pw  Any.pw  Async.pw  Runtime.pw …
  Driver.pw  Loader.pw
```

a/b は「結合のため」でなく**可読性のため**カテゴリ別子構造体に分け、c は**パス別コンテキスト**へ抽出する（前者は god-object の正当な共有部分を整理、後者が god-object を実際に解消）。

引数名・ラベルはこの機会に [spec/04 の規約](../spec/01-basics/04-functions.md#引数名とラベルの指針規約) に揃える（`c`→`comp`・`st`→`ctx`、通すコンテキストは `~:` 省略）。

## マイルストーン

順序は**安全性（不動点を毎ステップ緑に保つ）優先**。鍵は「**構造改造はまず単一モジュール内で完結させ（intra-module＝未検証パスを踏まない）、モジュール昇格は最後**」。

| M | 内容 | 跨ぐ可変状態 | リスク | 主眼 |
|---|---|---|---|---|
| **M0** | **probe**：cross-module `inout` 変異が動くか tmp で検証＋分割規律（毎段 dev-rebuild→test→reseed→不動点→tag）確立 | — | 低 | M4 の前提を先に確定 |
| **M1** | **巨大ファイルを part 分割**（Llvm 11.6k→~20、Check/Resolve/Mono/Lower/Verify/Ast も ≤500・std の >500 も）。構造・意味は不変＝観測出力不変で不動点が守る | 不要 | 低 | 可読性・即効・以降を扱いやすく |
| **M2** | **`Comp` の (a)+(b) をカテゴリ別子構造体へ解体**（Arena/Interner/TypeCache/MonoWork/ModuleTable/DeclTables）。`c.exprs`→`c.arena.exprs` 等の機械的書換・**1 カテゴリ 1 コミット**で緑維持 | 不要（intra-module） | 中 | god-object の (a)(b) 側を構造化 |
| **M3** | **(c) パス一時状態を per-pass コンテキストへ抽出**（VerifyCtx→ParseScratch→LowerCtx→**CodegenCtx** の順＝小→大）。署名 `(c: inout Comp,…)`→`(…, ctx: inout CodegenCtx,…)` を threading | 不要（intra-module） | 高（最大 churn） | **god-object を実際に解消** |
| **M5** | **scoped resolution＋循環検出**（M4 の前提・**M4 より先**）：名前解決をスコープ化＋import グラフ DFS で循環 reject。gate は作らず構造的に解消 | 不要（単一モジュールのまま） | 中 | resolver を理想化・spec 準拠化 |
| **M4** | **モジュール昇格**（M0＋M5 が通れば）：Backend を独立モジュール化＋Ir をデータモジュール群へ＋パスをモジュールへ。「1 モジュール 1 主構造体」「巨大 part 羅列」を解消 | 必要 | 中（M0 次第） | 理想像の完成 |

各 M 内も増分（1 ファイル/1 カテゴリ/1 パスごと commit＋tag）。M3 完了時点で god-object は消え、**実施順は M3→M5→M4**：M5（resolver の scoped 化）を単一モジュールのまま終え、M4 で「分割した境界を scoped resolution が検査する」が噛み合う。

### M4 の主目的＝モジュール構造を spec/15 ベストプラクティスへ（part 撲滅）

**決定（再優先）**：M4 の主目的は `compiler/src/` を [spec/15 ベストプラクティス](../spec/04-execution/15-modules.md) に沿わせる＝**巨大単一モジュール（91 part）の解消**。spec/15:207 は「既定は `import`、`part` を選ぶのは①[無名 impl の配置](../spec/04-execution/15-modules.md#無名-impl-の配置)が型/トレイトの定義モジュールを要求 ②相互再帰などで DAG に切れない（＝論理的に1モジュール）ときだけ。『関連が近い／大きい』は part の理由にならない」と定める。現状は 91 part が単一モジュールにぶら下がり大半が「関連／大きい」理由＝違反。これを `import` 層へ切り、`part` は spec が許す箇所（相互再帰核・無名 impl）だけに絞る。

**前提＝モジュールグラフは DAG**（spec/15＋M5 の循環検出が強制）。今 part を事実上「正当化」しているのは **Backend↔Frontend の循環**：
- Backend → Frontend：`findFunc`/`resolvedCallee`/`typeOf`/`spansEqual`/`structIndexByName`/`moduleOf` 等を呼ぶ（**正しい向き**＝Backend は Frontend の解析結果を消費）。
- Frontend → Backend：Backend 定義の**誤配置クエリ** `enumIdxByName`/`findTraitIdxByName`/`methodInEntryModule` を Check/Verify が呼ぶ（**逆向き**＝循環の原因・裏取り済）。

∴ **循環を断つ＝逆向きを消す**：この3関数（純粋クエリで Backend にある必然なし）を正しい層（Frontend/Ir）へ戻す pure-move。これで **Ir ← Frontend ← Backend** の一方向 DAG になり、最大塊 Backend（11.6k 行）を独立モジュールへ切れる。**型回復の二重実装（typed IR）は part 撲滅に不要**＝Backend→Frontend の型回復呼び（`typeOf` 等）は一方向で循環を作らない。

**自然に綺麗になる副産物**：層を切ると「どの関数がどの層に属すべきか」が構造で強制され、誤配置（逆依存・Backend に紛れた純粋クエリ）が炙り出され是正される。

#### マイルストーン（モジュール昇格）

| M | 内容 | 状態 |
|---|---|---|
| **M4-1** | IR をデータモジュール `Ir.pw` へ昇格（`Expr`/`Stmt`/`Comp`/interner…）。初の cross-module 共有可変 `Comp`。 | 完了・tag `refactor-m4-1` |
| **M4-2** | 逆依存3関数を Backend→Frontend/Ir へ戻し循環を断つ → **Backend を独立モジュール化**（`import Ir` ＋ Frontend の export 結果）。 | 次 |
| **M4-3** | **Frontend をモジュール化**（root＝Driver/Loader/main が `import`）。内部で DAG に切れる層は更に `import`、相互再帰核は spec/15 が許す `part` のまま残す（目標は「part ゼロ」でなく「spec が正当化する part だけ」）。 | 後 |

各段 dev-rebuild→test→reseed→不動点→tag。M5 の循環検出が「分割境界が DAG か」を実際に検査する。

#### 努力目標（後で言語制約化）：part 内は `impl` のみ

**方針（ユーザー・enforcement は後）**：part のベストプラクティスを構造で強制するため、最終的に **part に書けるのは `impl` だけ**にする（自由関数・型・top-level val を part に置けない）。コンパイラをまずその状態へ寄せ、達成後に言語制約として実装する。
- **狙い**：spec/15 の part 正当理由①（無名 impl の配置）に part 用途を縛り、「関連が近い/大きいから part」の濫用を言語レベルで不能にする。
- **含意（理由②＝相互再帰モジュール）**：自由関数を part 分割できなくなるので、(a) モジュール root に置く（巨大化）か (b) **メソッド化**（`fn f(c: inout Comp,…)` → `impl Comp { fn f(…) }`）して impl として分割。本コンパイラは解析がほぼ `fn(c: inout Comp,…)`＝実質 Comp メソッドゆえ (b) が機械的に可能。
- **再評価する緊張**：メソッド化で Comp の API 面が再増殖（M2/M3 の状態削減とは別軸だが意識）／どの型のメソッドでもない純ユーティリティ（`spansEqual` 的）はモジュール root 行き。到達後に enforcement の是非・緩和（part-local private 自由関数を許すか等）を判断。
- **段取り上の位置**：まず import 層化（Ir/Frontend/Backend/entry）を緑に。その後段に「各モジュールの part を impl のみへ寄せるメソッド化フェーズ」が乗る（長い裾・北極星）。

**済んだ予備作業**＝`findFunc` の解決を単一チョークポイント `resolvedCallee`（exprId キー永続 memo `TypeCache.callee`）へ集約済（13 site 中 12・tag `refactor-m4-b1` 他）。下記 typed IR トラックの一部だが、Backend の findFunc 呼びを memo 読みに替えて結合を薄くする副次効果もある。

### 別トラック（後段・任意）：型回復統一＝typed IR（根①）

> ⚠ **これは M4（part 撲滅）の critical path ではない**。Backend の独立は逆依存3関数の除去だけで足り、型回復の二重実装は Backend→Frontend の一方向呼びゆえ循環を作らない。typed IR は「根① 型付き IR が無い」（[architecture.md](architecture.md)）への独立した品質改善として後段で任意に行う。view-aware オーバーロード解決が backend に残る唯一の「決定」で、その前計算はこのトラックに blocked。以下は実コード精査で確定した知見（着手時の土台）。

- **二重実装**：`exprType(c,id)->TypeInfo`（フロント・`Resolve/ExprType.pw`・33+ arm・全式）と `exprTypeRef(c,st,id)->TypeRef index`（backend・`Backend/Llvm/GenericStruct.pw:138`・6 arm・place 式のみ）が「この式の型は？」を別実装で答える。クロス呼びは `valueKind`→`typeOf`（kind だけ委譲）の1本のみ＝**一方向（循環でない）**。
- **表現ギャップ**：`TypeInfo`（lossy＝kind/nameStart/nameLen/ref／**stage 1 で `viewExtId` 追加済**）vs `TypeRef`（完全）。view-aware が backend に残るのは TypeInfo が view を落とすから。
- **局所型の二重管理（linchpin）**：フロント `c.cur.locals[].ty`（テンプレ型）vs backend `st.locTypeRef[]`（**grounded 型**・emission 中に `groundTypeRef` で構築）。
- **制約（裏取り済）**：①フロントの型付けは lazy・非網羅で generic 本体はインスタンス依存（毎回再導出）⇒「全式を1回記録」は不可。②**grounding は backend の正当な仕事**（インスタンス固有・前計算不可）。
- **あるべき形**：消すべきは (a) 回復ロジックの二重実装 (b) lossy 表現。grounding は残す。局所型は **(B) backend が `c.cur.locals` を可変保持は却下**（意味の再導出）。正しくは「**テンプレ型を単一ロジックで出し backend はそれを ground して読む**」。
- **段取り**：1.表現統一（TypeRef view 込み・stage 1 着手済＝`TypeInfo.viewExtId`）→ 2.局所テンプレ型の単一出所（linchpin・最難関）→ 3.backend `exprTypeRef` を統一回復＋grounding に置換 → 4.view-aware が薄い reader に落ち前計算化。

## scoped resolution への移行（M5・resolver の理想化）

**決定**：循環 import 禁止（[spec/15 循環依存](../spec/04-execution/15-modules.md#循環依存モジュールグラフは-dag)）を機に、resolver を移行する。**gate（型参照 gate・関数 gate）は使い捨てなので作らない** ── scoped resolution で構造的に解消する。

### 今のモデルの病理（実装が示す事実）
- 全 struct/func は単一プール `c.arena.structs`/`c.arena.funcs`。モジュール容れ物なし。
- `findFunc`（Resolve/Module.pw:123）＝全 funcs を線形走査し、**同モジュール優先ヒューリスティック**で別モジュールの同名 private を退ける（コメントが「これが無いと spurious reject」と自認）。
- 可視性は **post-hoc gate**：`checkImports`（import 文の名が export 済か）＋`checkUseVisibility`（cross-module 関数呼びが import 済か）。Driver.pw:291-292 で実行。
- **型参照は素通し**（"Types stay ambient"・Check/Visibility.pw:52）＝spec 逸脱の穴。
- これらは「全部見える前提を後から矯正する3絆創膏」。

### 理想像
> モジュール＝スコープ。スコープ = 自モジュール宣言 ∪ import で持ち込んだ依存の export 名 ∪ lang-item 型。名前解決＝**スコープ内候補のみ**考慮。

帰結：型 gate 不要（未 import 型はそもそも解決されない）／同モジュール優先ヒューリスティック不要（別モジュール非 import は候補にすら入らない）／`checkUseVisibility` 不要（解決に内包）。3 絆創膏→1 原理。

### 実装方針
- **新コンテナは作らない**。中央述語 **`nameVisibleFrom(comp, useMod, candMod, candStart, candLen) -> Bool`** を全「ソース名→宣言」解決に **FILTER** として適用＝arena 線形走査の現スタイルに整合（スコープの実体＝述語）。
- **可視判定**：`candMod == useMod` ∥ ambient 型（`isAmbientInLang`＝`@Std/Lang` の export 面）∥（candName が useMod の `c.modules.imports` に在り、かつ candName が `c.modules.exports` に在る）。namespace/alias 経由も `markImport`（Parser/Decl.pw:467）で `imports` に登録済 → 同じ述語で効く。**型の namespace 参照（型位置の `P.Foo`）は現状未処理＝要実装**。
- **適用箇所**：
  - free fn＝`findFunc` の候補ループに `nameVisibleFrom` を入れ、**同モジュール優先ヒューリスティックを削除**（in-scope 候補のみ残す）。
  - 型名＝**チョークポイント散在**（~22 ファイルが `c.arena.structs` 直走査・集約は `structIndexByName` Decl.pw:471 のみ）。ソース由来の型名解決（型注釈・TypeRef 検査・構築ヘッド・match パターン型）に述語を適用。当面は **書かれた TypeRef を走査して in-scope を検査する小パス**（findFunc が関数に埋めるのと同じ「スコープ内に解決するか」を型側でも行う＝gate ではなく scoped resolution の型側）。理想は全型ルックアップを scope-aware な単一チョークポイントへ寄せること（散在解消は付随リファクタ）。
  - トップレベル global（`val`/`mut val`）名も同様。
- **対象外（import スコープ非依存）**：メソッド・assoc fn・演算子・トレイト impl の dispatch は型＋有効 `#Ext` だけで決まる（spec/09）＝モジュールスコープに掛けない。
- **Core ambient 維持**：`@Std/Core` は force-load 済 ambient（Optional/Result/演算子 witness/range/`for`）＝スコープ常駐扱い。`assert` は従来どおり import gate（spec）。
- **削除**：`checkUseVisibility`・`findFunc` の same-module 優先ヒューリスティック・型 ambient 素通し。**保持**：`checkImports`（import 文自体の検証＝「import した名が未 export」を良い診断で出す・解決とは別の入口検証）。

### 循環検出（DAG 強制・独立の小追加）
`c.modules.imports`（`fieldStart`=importing module id）＝import 辺。これを辺集合に **DFS で循環検出 → コンパイルエラー**（輪のモジュール列を診断）。scoped resolution とは独立だが spec/15 の確定事項なので同時に入れる。

### 順序・ブートストラップ安全
- コンパイラは**現状 1 モジュール（全 part）** ＝内部参照は全て same-module＝scoped 化しても**挙動不変・緑のまま**。
- cross-module scoping を実際に exercise するのは **compiler↔@Std 境界**（`_.pw` の import 群）＝型 scoping ON で「std 型を使うが未 import」が compiler 自身に出れば import 群へ追補（**健全な churn**・spec 準拠化）。これが scoped resolution の実テスト。
- 段取り（各段 dev-rebuild→test→reseed→不動点→commit）：
  1. `nameVisibleFrom` 追加＋free fn を scoped 化（ヒューリスティック削除）。
  2. 型名解決を scoped 化（書かれた TypeRef の in-scope 検査）＋compiler/std 自身の未 import を追補。
  3. `checkUseVisibility` 削除（内包確認）。
  4. import 循環検出（DFS）追加。
  5. reject テスト追加：①未 import 型参照 ②未 import 関数呼び ③循環 import。
- **その後 M4（モジュール分割）が本当に検査される**＝M5 が M4 の前提インフラ。

**実装で判明した罠（M5 完了済）**：①**型注釈スパンは再 intern**（Phase D・ソース offset でない）ので `moduleOf(型スパン)` は使えない ── use-site module は**包含 decl の実 offset**（func `nameStart`・struct/enum `defOffset`）から、型の定義モジュールも `defOffset` から取る。②`NewtypeDef` に `defOffset` を追加（StructDef/EnumDef と同型）＝cross-module newtype が解決。③型パラメータは**包含 decl の `typeParams`** と照合して skip（グローバル `isTypeParamName` は単一大文字 struct `P` 等で破れる ── `FilterIter[I,P,E]`）。④循環検出は import 名→`definingModuleOfName` で module 辺を作り DFS color。⑤backend は `array[i].field` チェーン読みを未対応 ── 中間値をローカル束縛して回避。

### M5 後続：型可視性をチョークポイント検査へ根治（siteOffset モデル）

**問題**：上記の罠①③に引きずられ、当初の `checkTypeVisibility` は**型注釈サイトを手で列挙**（func の param/ret・struct/enum field）していた。これは**列挙漏れが構造的に起こる**（local `val x: T`／newtype underlying／trait 要求シグネチャ／式中の `as`・明示型引数・closure sig が素通り）。罠①の本質は「`lowerType` が `TypeAst.span`（実ソース offset）を捨て、`internBytes(name)` の再 intern スパンに差し替えている」こと ── これが defOffset proxy と手列挙の両方を強いていた**設計の誤り**。

**根治**：`TypeRef` に `siteOffset`（実ソース offset）を持たせ、唯一のチョークポイント `lowerType` で `t.span.start` を刻む。`checkTypeVisibility` は **`c.arena.types` を一様走査**する単一パスにする。プログラム中の**あらゆる書かれた型**（param/field/local/newtype/trait req/`as`/明示型引数/将来の新文法）は必ず `lowerType` を通るので、**サイト列挙漏れが原理的に起こらない**（チョークポイント検査）。
- **合成 TypeRef の除外**＝`siteOffset` の既定は 0。`lowerType` の通常 push（名前付き型）でのみ `t.span.start` を刻み、record-struct push やその他の合成 `pushType` 呼び出しは 0（=skip）のまま。offset 0 は実注釈には決して現れない（注釈は decl 内部にあり offset 0 は entry ファイル先頭）。`StructDef.defOffset != 0` 慣習と同じ。
- **型パラメータ skip**＝`lowerType` で head が in-scope 型パラメータなら `siteOffset=0`。スコープは `c.cur.typeParams`（cursor の generic 置換環＝意味的に正しい住処）を**lowering 中も**設定して供給する。各 decl-lowering 関数（struct/enum/func/method/impl/trait req）で save/restore、`lowerTopItem` で `[]` リセット（staleness 防止のセーフティネット）。
- **検査の単純化**＝型パラメータは事前 skip 済なので、`checkTypeName` から `typeParams`／`nameInTypeParams`／`isTypeParamName` を落とせる。`Self`・関連型は「グローバル decl が無い」で自然に skip。`checkTypeArgs`（配列だけ head に要素を持つ特例の再帰 walk）は不要化＝args も各々 arena の TypeRef なので同じ一様走査が拾う。
- **副産物**＝エラー行が decl 名でなく**注釈そのもの**を指す（正直な provenance）。式中の型注釈（`as`・明示型引数・closure sig）も新たに被覆（従来は素通り）。
- **検証**＝コンパイラ自身が generics の塊なので、型パラメータ scope の配線漏れ・衝突は self-host で露見する（fixpoint が実テスト）。残る理論的偽陽性は「型パラメータ名が実在の型名と衝突」のみ＝稀・loud・リネームで回避（単一大文字 struct 衝突と同根）。

**チョークポイント化が炙り出した健全な churn**（従来は未 walk ゆえ素通りしていた・移行で顕在化＝正しい挙動）：
- **ambient ＝ `@Std/Lang` の export 面**（`isAmbientInLang`・旧 `isLangItemTypeName` 名リストと旧 `preludeModule` de-facto-ambient はともに廃止）＝Lang が宣言/再エクスポートする型だけが import 不要。`@Std/Core`/`@Std/Hash` は force-load されるが ambient ではない（型名の名指しに import 要・`SipHasher.new()` 等は `import @Std/Hash` 必須）。`@Std/Prelude` は撤去。
- **alias を型位置で解決**＝`import M with { Real as Alias }` の `Alias` を型注釈に書く use を `realTypeNameInModule`（use-site module scope）で real 名へ解決してから可視性判定（imports/exports は real 名 keyed）。従来 alias は param 位置に現れず未検証だった。
- **トレイト関連型を impl の skip scope へ**＝`pub impl Iterator { fn map(...) -> ...[Item] }` 等、提供メソッドが書く関連型 `Item` は binder。`lowerImpl` が実装/拡張するトレイトの `assocTypes` を `appendTraitAssocTypes` で skip scope に積む（`lowerMethodMember` はそれ＋メソッド own `[U]` を継ぐ）。ユーザが `struct Item` を定義した時のみ衝突として顕在化＝関連型 scope の必要性を示す実例。

### M2 の前提：ネスト place 変異（backend 機能・解決済）

`c.exprs`→`c.arena.exprs` は **読み取りは元から動くが、変異（`c.arena.exprs.append`／`c.arena.exprs[i]=v`／`inout c.arena.exprs`／ネスト scalar field 代入）は backend が未対応だった**（lvalue ポインタ計算が一段＝local/直下フィールド止まり）。`placePtrStrict`（再帰的 lvalue ポインタ＝Ident／ネスト Field を GEP／array Index 要素）を入れ、`placePtrOf`・`arrStoragePtr`・index/field 代入をそれ経由にして解決（generic ネスト place は従来どおり未対応）。**M2 はこの backend 拡張が前提**。

### M3 の形：per-pass コンテキスト引数 vs `Comp` 上の子構造体

(c) の ~36 カーソル状態の追い出しには2案。**(i) per-pass コンテキストを別引数で threading**（`(c: inout Comp, ctx: inout CodegenCtx,…)`）＝アーキ的に純（スコープ付き寿命・god-object を真に解消）だが**全パスの全関数に引数追加＋呼び出し書換で最大 churn**。**(ii) `Comp` 上の子構造体に grouping**（`c.cur.retTy` 等＝M2 と同じ機械的書換）＝可読性（フィールド数）は解決するが共有可変のまま（god-object の臭いは残る）。ユーザーの主訴は**フィールド数の把握困難**で、(ii) はそれを M2 と同じ手法で解く（フェーズ別の小さな cursor 群＝ParseScratch／CodegenCursor 等に分けると各々が grok 可能）。(i) のアーキ純度は別目標。**どちらを採るかは着手前に確認**。

## 未検証リスク（M0 で先に潰す）

**モジュール昇格（M4）は `Comp`（＋arena 型）を `pub` フィールド付きで `export` し、別モジュールの関数が `inout Comp` で跨いで変異することを要求する。これは現コンパイラで前例ゼロの未検証パス**（std 側はパーサが値ツリーを返すだけで、跨ぐ共有可変状態が一切ない）。

- **M0 probe**：小さな 2 モジュール（A が `export struct S { pub mut val … }` ＋ pub factory、B が `fn bump(s: inout S)` で変異、main が構築→呼出→印字）で、(1) pub フィールドの cross-module `inout` 変異、(2) ネスト子構造体フィールドの変異、(3) pub メソッド経由の変異、を検証。既存の cross-module import 構文は `import ./Name with { … }`（`tests/part/crossimport` 参照）。
- **M0 が NG なら M3 で止めても価値は大半得られる**（小ファイル＋カテゴリ化コア＋per-pass コンテキスト）。その場合は「cross-module 変異を有効化」を別タスクに切り出す。

なお **型定義のモジュール化**（Expr/Stmt を子モジュールへ）は変異を跨がない（型は不変な定義＝import して match するのは tested path）ので、M4 の中でも先行して安全に踏める。

## リファクタの心構え：legacy workaround を現代の Plew へ

コンパイラは Plew の文法がまだ貧弱だった頃から育っているので、**今の言語機能なら素直に書ける箇所を、当時の回りくどい workaround のまま**抱えている。リファクタは「コードを移動するだけ」ではなく、**触る箇所すべてで『今の Plew でもっと良く書けないか』を能動的に問う**。

> ⚠ **周囲の（古い）書き方に引きずられない。** LLM は周辺コードのスタイルを模倣しがちだが、ここでは周辺こそが負債。各片について「これは workaround か？ 今の機能で直せるか？」を**毎回・強く**問う。

典型パターン（非網羅・見たら直す）：

- `if foo { } else { BODY }`（空の then）→ `if !foo { BODY }`（worklog「コード整理 TODO」の既知項）。
- Optional を手で `match` → `?.`（Chain）・`unwrapOr`・`if`/`while`-let・`guard`。
- フラグ変数＋後段 `if` → `guard`／早期 `return` でネスト削減。
- 多値返却を `inout` out-param や「並列スカラ配列＋第二の戻り値もどき」で代用（例：`curWhereTraits` ＝ "a second return value without a tuple type"）→ ラベル付きレコード `(a:, b:)` 返却。
- 値位置の `if`/`match` を一時変数＋代入で代用 → `give` 値ブロック・value-position match。
- 文字列の手組み連結 → 補間 `"{x}"`。
- enum/primitive のディスパッチを自由関数で代用 → メソッド（今は enum/primitive メソッドが動く）。
- `assoc fn` を生成に流用 → named/fallible factory。
- 引数名・ラベルは [spec/04 規約](../spec/01-basics/04-functions.md#引数名とラベルの指針規約)・factory 名は [spec/05 規約](../spec/02-type-system/05-structs-enums.md#ファクトリ名の指針規約) に揃える。

**ただし「今は直せない workaround」と「今なら直せる workaround」を見分ける**：一部の並列スカラ配列は**まだ存在しない機能**の代用（例：`exprTy*` の 4 並列配列＝「struct-array の `IndexSet` が self-host サブセットに無い」ため）。**機能がまだ無いものは無理に直さない**。問うのは「今の機能で直せるか？」で、直せる箇所だけ直す。

**安全規律**：これらは**意味を変えない idiomatic 書き換え**だが純粋な move ではない。だから **pure move のコミットと idiomatic rewrite のコミットは可能なら分ける**（不動点が割れたとき bisect しやすい）。各書き換えは test＋不動点で守る。意味論を変える整理だけは仰ぐ（[CLAUDE.md](../CLAUDE.md) 方針）。
