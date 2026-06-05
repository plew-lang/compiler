# メタプログラミングの実装アーキテクチャ

> spec の正典は [spec/04-execution/16-metaprogramming.md](../spec/04-execution/16-metaprogramming.md)。本書は**実装の段取り・実行系の具体・将来計画**（「どう作るか」）を置く。確定方針（**AST 入力/String 出力**・別ファイル add-only 出力・`@[...]` 含意 part・組み込みは当面特権）は spec を参照。

## 全体像

マクロは **注釈対象項の構文木（`AST`）を受け取り、生成 Plew ソースを `String` で返す `Derive` 実装の Plew コード**。専用コマンド（仮 `plew gen`）が derive を実行し、**読める Plew ソース `<Foo>.gen.pw` を生成**（コミット）。ビルドは生成済みを読むだけ。原本 `<Foo>.pw` は不変、取り込みは `@[...]` の存在でローダが自動。

- **入力＝AST（span 付き）／出力＝String** の非対称はエラーの出どころと一致：入力エラー（マクロが対象を拒否）は AST ノードの span（原本座標）でユーザー元ソースを指す／出力エラー（生成コードが通らない）は `<Foo>.gen.pw` の普通のコンパイルエラー。だから**出力に `quote` のような埋め込み構文は作らず**、普通の Plew 文字列＋既存補間 `"{…}"` で組む。
- **ディレクティブ引数＝マクロ struct のフィールド**：`@[Name(a: 32)]` ＝ `Name { a: 32 }` を構築して `.derive(input)`（`derive` はメソッド・self ＝設定）。

**`Derive` トレイト＝要求＋提供の 2 メソッド**（構文ライブラリ `@Std/Syntax` が提供）：
```plew
trait Derive { fn derive(input: DeclAst) -> String }              // 要求：ユーザー実装
impl Derive {                                                     // 提供（blanket）：変換＋委譲
  fn deriveFromSource(source~: String, start: U64, end: U64) -> String {
    return self.derive(input: parseItem(source: source, start: start, end: end))
  }
}
```
**ランナーは String↔String の版非依存な機械**：`@[Name(args)]` ごとにハーネス（`<Name args/>.deriveFromSource(...)` を `print` する `main`）を合成→**コンパイル&別プロセス実行**（マクロが固定依存する `@Std/Syntax` 版がリンク＝版固定が自然成立）→ stdout を `<Foo>.gen.pw` へ。AST 型・lexer/parser はハーネスが import する `@Std/Syntax` 側にあり、**ランナーは AST に一切触れない**。

リッチな AST は**最終形でコンパイラ外の共有パッケージに切り出す**（lexer+parser+AST を 1 つにし、コンパイラもマクロも同じ版に依存＝Rust の 2 パーサ問題を回避・AST 版違いのツラミ最小化）。パッケージ管理が無い現状は **`@Std/Syntax`（in-tree）が一時的にその役**。

## 理想形（最終状態）＝構文層を唯一の真実に

切り出すべき「コンパイラに必要なもの ∩ マクロに必要なもの」は、**構文層まるごと**＝レクサ＋完全な値ツリー AST＋パーサ＋アンパーサ。**切る線は「構文（form）vs 意味（meaning）」**で、これが必要十分の境界。

- **構文（form）＝何が書かれたか**：トークン・木の形・名前の綴り・書かれた型式・span。**ここが重なり**＝コアライブラリ `@Std/Syntax` に出す。
- **意味（meaning）＝それが何に解決したか**：名前解決・型推論/検査・トレイト準拠・単相化・ARC/CoW・codegen。**コンパイラ専用**＝コアに出さない。
- 判定基準：**「ソースを見ただけで決まるか（構文）／プログラム全体の解決が要るか（意味）」**。前者だけを出す。

**`@Std/Syntax`（コア）の中身（理想）**：

1. **レクサ** `bytes → [Token]`（Token = kind＋span〔＋text〕・Comp 非依存・純粋）。
2. **完全な値ツリー AST**（宣言・式・文・パターンの全語彙）。
   - 名前は**値**（String）＝arena インデックス/バイトオフセットでなくノード単体で読める自己完結ツリー。
   - 型は再帰 **`TypeExpr`**（head 名＋型引数＋関数型…）＝「書かれた型」。
   - **全ノードが span**（原本座標）＝診断にもマクロの入力エラーにも使う。
   - **解決済み情報を一切持たない**。今の AST は「書かれた綴り（span）」と「解決済み型（`ty: U64`）」を同じノードに混在させているが、理想では構文 AST は "書かれたまま" だけ。解決結果はコンパイラ側の別レイヤがノードに紐付ける。
3. **パーサ** `[Token] → AST`（純粋＝codegen 播種なし・意味的副作用なし・回復可能エラー・**base offset を取りスライスを原本座標で parse**＝マクロ入力エラーがユーザー元位置を指す）。
4. **アンパーサ `AST → source`**（往復を閉じる＝フォーマッタがタダで出る・`quote`/authoring 層の土台・String 出力は最下層の床として残しつつ上に AST 構築＋印字が乗る）。

**重ならない側（コアに出さない）**：コンパイラ専用＝名前解決・型検査・準拠・単相化・codegen・`Comp` 状態・型付き IR。マクロ専用＝各 derive の生成ロジック・`Derive` トレイト・`plew gen` ランナー。

**理想のパイプライン**：

```
source ─[共有レクサ]→ tokens ─[共有パーサ]→ 構文AST ─┬─[コンパイラ]→ 解決/型付きIR → codegen
                                                     └─[マクロ]→ 読む → 生成(String / AST→アンパーサ)
```

**1 AST 原則**：AST の語彙は両者で**完全に同一・完全**。違うのは**スコープ**（コンパイラ＝プログラム全体／マクロ＝注釈された 1 項）と**その後何をするか**（compile／generate）だけ。**「マクロ専用の縮小 AST」は作らない**＝作った瞬間に Rust の syn vs rustc（2 AST が drift）を再現する。1 つの AST を、コンパイラは全部読み、マクロはその 1 項分を読む。マクロは宣言だけに人為的に制限されず、欲しければ関数本体も既定値式もディレクティブ引数式も同じ木として読める（読むかは各マクロの自由）。

**理想の効能**：文法も AST も 1 本＝drift 構造的に不可能（self-host だからこそ達成・Rust が諦めた地点）／マクロが見るのはコンパイラが見た構文そのもの＝「唱えた通り」が構文層でも成立／span 全ノード＝診断もマクロ入力エラーも原本座標／parse＋unparse の往復＝フォーマッタ・`quote`・round-trip・将来の LSP/lint が全部この 1 パッケージの上／**構文/意味の分離そのものが、いま負債として残る「パーサが codegen 仕事をする」「型付き IR が無い」を境界として強制**（意味は構文 AST の上の別レイヤへ押し出される）。

> **`@Std/Syntax` の in-tree 配置は一時的 workaround**。パッケージ管理が無い現状で、外部共有パッケージの代わりに in-tree（std 内）に置くだけ。パッケージ管理導入後に外部共有パッケージへ昇格させる前提（コンパイラもマクロツールも同一版に依存）。

## 入力モデルの再考：TokenStream か AST か（境界が鍵）

spec/16 は **入力＝TokenStream（span 付き）＋ヘルパで TokenStream→AST 変換**。動機は (a) 安定境界（トークンは AST より版に強い）と (b) 汎用性（型宣言に限らず任意の項を渡せる）。だが**上の「共有 AST パッケージ」を最終形に据えると、(a) の根拠は消える**＝AST も単一の源で安定するので、トークンを安定緩衝材にする必要がなくなる。残る正当化は (b) 汎用性のみで、Plew は derive 中心（宣言/シグネチャに `@[...]`）なので汎用トークン入力の出番は稀。

**境界の整理（誰が何をするか）**：
- `TokenStream`／`AST` の**型はどこから**＝最終形では共有パッケージ。移行期は `@Std/Syntax`。
- **String→TokenStream を誰が**＝`plew gen` ランナー（注釈対象項のソーステキストを持つのはランナー）。共有パッケージの lexer を使う。
- ここで効くのが**「無駄説」**：ランナーはどのみち lex する。入力を TokenStream にすると**マクロ側が即 `parse(ts)→AST` を呼ぶだけ**で、*同じ parse を毎マクロで再実行*。一方ランナーが text→AST まで済ませて **AST を渡せば parse は 1 回・マクロは即構造を読む**。derive ではトークン段は冗長な中間表現。

**結論（確定）**：**入力＝AST**。境界＝String（ランナーは版非依存）、String→AST は `Derive` 提供メソッド `deriveFromSource` が担う（中間 dispatcher 層は不要）。Rust でも生 TokenStream 必須は `json!`/`html!`/`quote!` 等の**関数形/DSL マクロ**だけで、**derive は常に AST へ parse**＝Plew の derive 専用モデルには AST で十分。汎用トークンが要るマクロを将来入れるなら `derive(input: TokenStream)` を additive escape hatch に。spec/16 を AST 入力へ更新済み。

## 実装の段取り（パッケージ管理より前に動かす）

- **M0＝配管を端から端まで（自明マクロ）＝✅実装済**（tag `metaprogramming-m0`）。実装は当初案（plewc が別ハーネス `.pw` を合成→再 import）より一段クリーンに倒した：**`plewc --gen <file>` は通常コンパイルの変種**。対象ファイルの全モジュール木（part/import 込み）を普通にロード・パースし（マクロ struct と instantiate 済み `deriveFromSource` がそのまま scope に入る）、**ユーザー自身の `main` を抑制し、代わりに各 `@[Name]` について `write(s: <Name/>.deriveFromSource(...))` する harness `main` を合成**して C を出す。シェルランナー `plew-gen.sh` が `plewc --gen <file> | clang | run > <Foo>.gen.pw`（bootstrap/test と同じ orchestration・**新 intrinsic 不要**）。別ハーネスファイルの import 解決が要らず、同一モジュール derive も import 越し derive もローダが木を綴じるので一様に動く。実装の要点・罠は [worklog.md](worklog.md) 末尾「再利用資産・罠」の gen 項。
  - source の渡し方：M0 は `source: ""` 固定（`parseItem` stub）。**M1 で実ソースを渡す＝✅**：`source` ＝対象項の実テキスト（エスケープして string literal 埋め込み）、`start` ＝原本オフセット（span の base）、`end` ＝informational。`parseItem` は `source` を丸ごとレックスし base=start で原本座標 span を返す。
  - `@Std/Io` を gen モードで強制ロード（harness の `write` 用）。auto-part 抑制・user `main` skip は gen モードフラグ（`Comp.genMode`）で分岐。
- **M1＝構文層を共有コアへ切り出し＝コア機能✅実装済**（tag `metaprogramming-m1`）。**マクロが対象宣言の実構造を読んで生成できる**：`@Std/Syntax` に共有レクサ（`Syntax/Lexer.pw`・コンパイラ本体も import＝レクサ 1 本）＋クリーン値ツリー AST（`Syntax/Ast.pw`＝Span/TypeAst/FieldAst/VariantAst/ParamAst/DeclAst〔タグ付き struct・DeclKind〕）＋宣言パーサ（`Syntax/Parser.pw`＝`parseItem`・struct/enum/fn シグネチャ＋型式）＋出力ビルダ（`Syntax/Build.pw`＝`Src`）。`parseItem` 本物化＝ハーネスが対象項の実ソースをエスケープ埋め込み（`internSourceLiteral`）＋原本オフセット（`DeriveReq.declStart/declEnd`）を base に渡す。**ディレクティブ引数 `@[Name(label: expr)]`** も実装（`parseDirectiveArgs`・`DeriveReq.args`・synthGenMain が `<Name label=expr/>` 構築）。gen テスト＝fieldnames/directiveargs/enumvariants/deriveshow（最後は `pub impl T as Show` 生成＝実用 derive）。
  - **残（M1 の理想完成）**：①**本体フロントエンドの共有パーサ統合**（共有パーサ→tree→lower→arena・旧 `parseProgram/parseStruct/Enum/Func` 退役＝真の 1 AST・重複パーサ解消・不動点 byte 同一性が重い）＝**未着手**。②**構文層の式・文・パターン**（関数本体を木で surface）。現状はマクロ前進優先で **1→2→3〔宣言〕→5** を先に通した（parseItem は arena 独立なので本体無改修でマクロが動く）。**arena→`DeclAst` 変換のショートカットは採らない**（1 AST 原則）。**やらない＝重なりの外**：codegen を型付き IR 化し arena を消す負債根 #1（境界の下・マクロ不可視・別件）。確定手順は [worklog.md](worklog.md)「M1 の進め方」、暫定判断はローカル review-items。
  - **authoring 層（ハイライト対応テンプレート/quote）は future・additive**。コアは String 出力のまま。
- **M2＝コアライブラリのマクロを dogfood**：`Eq`/`Hash` をこの機構で書く。現行のコンパイラ特権合成（`synthStructEq` 等）から段階移行（特権版を残したまま並行→検証→差し替え）。`Hash` が出れば `Dictionary`（`[k:v]`）に接続。
- **M3＝パッケージ管理導入後に切り出し**：`@Std/Syntax`（lexer+parser+AST）を独立した**外部共有パッケージ**へ昇格。コンパイラもマクロツールも同一パッケージ版に依存する構成へ。

> 当初の理想順は「ライブラリ切り出し → その上に機構」だったが、入れ物（パッケージ管理）が無いので**機構を in-tree（`@Std/Syntax`）で先に作り、外部切り出しは最後**に倒した。各段階で実利（コンパイラが綺麗になる／Dictionary が進む）が出る。**重い D（legacy 型 triple／パーサの codegen 仕事）と Phase C（名前 interning）はこの後**＝Dictionary が来てから interning を綺麗にやる順。

> 当初の理想順は「ライブラリ切り出し → その上に機構」だったが、入れ物（パッケージ管理）が無いので**機構を in-tree で先に作り、切り出しは最後**に倒した。各段階で実利（コンパイラが綺麗になる／Dictionary が進む）が出る。

## 実行系の具体（M0）

- マクロは「要求 `fn derive(input: DeclAst) -> String` を持つ `Derive` 実装」を含む通常の Plew パッケージ（`@Std/Syntax` に依存）。
- `plew gen` の 1 ファイル分の処理：
  1. ソースをロード（`part`/`import` 解決）し、`@[Name(args)]` 付き対象項を集める。**gen 中は `.gen.pw` の auto-part 取り込みを抑制**（これから作るので）。
  2. 各 `(対象項, Name(args))` について、`Name { args }` を構築し**提供メソッド `.deriveFromSource(source, start, end)`** を呼ぶ `main` を合成（＝String→AST 変換＋ユーザー `derive` 委譲は `@Std/Syntax` 内で起きる）。`source` の渡し方（stdin/原本ファイル/リテラル）は最も楽な形で。プロセス境界は**テキスト**（ランナーは AST/TokenStream 型に触れない＝版非依存）。
  3. それをコンパイル（.pw→C→bin）し、サブプロセス実行。複数 derive は出力を連結。
  4. `<Foo>.pw` 由来の生成片を `<Foo>.gen.pw` に書き出す（既存があれば上書き＝生成物は決定的）。
- ローダ側（ビルド時）：`<Foo>.pw` に `@[...]` を見たら `<Foo>.gen.pw` を同モジュールの part として自動ロード（無ければ「`plew gen` を走らせよ」と loud に失敗）。
- マクロが入力を拒否する場合は AST ノードの span（**原本座標**）で**対象項の元位置**を指す（出力エラーは別＝`.gen.pw` の再コンパイルが指す）。

## 同一パッケージ/モジュール内 derive（Rust の別クレート制約は不要）

マクロを**その対象（`@[...]` を付けた型）と同一パッケージ・同一モジュール・同一ファイル**に同居させて使える。Rust と違って問題ない。

- **Rust が proc-macro を別クレートに強制する理由**＝マクロを「利用クレートのコンパイル中」に実行するから、先にプラグイン（dylib）としてコンパイル済みでないと鶏と卵になる。
- **Plew にはその構造が無い**＝マクロはビルド中に走らず、別フェーズ `plew gen` がコミット済み `.gen.pw` を吐くだけ・ビルドはそれを読むだけ。「マクロをその利用コードのコンパイルの一部として実行する」循環が発生しない。`plew gen` 時はマクロを普通の Plew プログラムとしてコンパイルして走らせるだけ（同居していても「同じパッケージのコードをコンパイルして実行する」以上の意味を持たない）。

**実装上の小細工は1つ**：`plew gen` がマクロを実行するためにソースをコンパイルするとき、**まだ生成していない `<Foo>.gen.pw` の auto-part 取り込みを抑制（欠落を許容）**する。理由＝取り込み（`@[...]` → `.gen.pw` を part）はビルド用ルールで、gen 中はその `.gen.pw` をこれから作るので無くて当然。そして**マクロ自身は生成物を使わない**（生成 `impl Foo as Eq` を使うのはアプリ側で derive ではない）ので、対象型の宣言＋マクロ定義は `.gen.pw` 無しで普通にコンパイルできる。

**病的エッジ（参考）**：マクロのロジック自身が、同じマクロで derive される impl に依存する場合（例：`MyDerive.derive` の中で `==` を使い、その型がまさに `@[MyDerive]` 由来）だけは本物の循環。稀なので、起きたら **loud に検出してエラー**にする（通常の「他の型のための impl を生成する derive」では起きない）。

## bootstrap への影響

- コアライブラリ（`@Std`）の derive をマクロ化すると、**コンパイラ自身がコンパイルするソース**に生成ファイルが混ざる。生成物はコミット済みなので bootstrap は走らせず読むだけ＝従来の ADD→reseed→USE と同じ規律で回る。
- 移行中は「特権合成（現行）」と「マクロ版（新）」を**同名ディレクティブで二重に持たない**よう注意（衝突）。特権版を残す間はマクロ版を別名で検証→差し替え時に特権版を削除。

## 未確定で実装前に詰める点

- **`@Std/Syntax` の `DeclAst` 具体形＝✅確定・実装済**（`Syntax/Ast.pw`）：`DeclAst`＝タグ付き struct（`kind: DeclKind`＋`name`/`typeParams`/`span`＋struct 用 `isUnique`/`fields`、enum 用 `variants`、fn 用 `params`/`hasRet`/`ret`）。`FieldAst`＝`name`/`ty: TypeAst`/`isMut`/`vis`/`hasDefault`、`VariantAst`＝`name`/`fields`、`ParamAst`＝`name`/`ty`/モード/`noLabel`、`TypeAst`＝`name`/`args: Array[TypeAst]`/`span`（原本座標）。enum-of-structs でなくタグ付き struct なのは codegen の依存順制約回避（ローカル review-items 参照）。
- `parseItem` の実装＝✅確定・実装済（`@Std/Syntax` 共有レクサ/パーサ・原本座標で木が返る）。
- 生成コマンド名・設定（どこに対象を書くか・対象ディレクトリ）・source の渡し方（最も楽な形で）。
- authoring 層（テンプレート/quote）の具体（future・additive・コアは String 出力のまま）。
- 生トークン escape hatch（関数形/DSL マクロを将来入れる場合のみ）。
- `#Extension` との関係（生成した `impl` を拡張として出すか）。
