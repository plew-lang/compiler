# コンパイラ構造リファクタ（god-object 解体＋モジュール分割）

正典コンパイラ `compiler/src/` を「現実装の理想像」までリファクタする計画。**なぜ・到達点・マイルストーン・未検証リスク**を残す（進捗の「やった」は git）。現在地は [worklog.md](worklog.md)。

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
| **M4** | **モジュール昇格**（M0 が通れば）：Backend を独立モジュール化＋Ir をデータモジュール群へ＋パスをモジュールへ。「1 モジュール 1 主構造体」「巨大 part 羅列」を解消 | 必要 | 中（M0 次第） | 理想像の完成 |

各 M 内も増分（1 ファイル/1 カテゴリ/1 パスごと commit＋tag）。M3 完了時点で god-object は消え、M4 は「綺麗になった塊をモジュール境界で切る」だけの仕事になる。

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
