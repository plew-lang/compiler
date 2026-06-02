# 作業ログ（実装フェーズ）

> compact がいつ走っても復帰できるよう、**今やっていること・次にやること**をこまめに更新する。古い完了項目は git 履歴に任せて圧縮してよい（「なぜ」は design-decisions、「設計」は architecture へ）。

## 現在地（一言）

stage0（Rust）で **Plew 製のレキサとパーサ＋評価器が compile&run する**段階。サポート済み：型付き整数/Bool/String（`.bytes`/`==`）・Array（リテラル/添字/`count`/for-each/`append`/`arr[i]=x`・リーク参照セマンティクス）・struct・enum+match（文位置・if-chain）・if/else/while/for（range/array）・関数（相互再帰・プロトタイプ）・`break`/`continue`・**`inout` パラメータ**・**`as` 数値キャスト**・stdin/stdout I/O（`readStdin`/`write`）。codegen は型を依存順に出力（前方宣言＋トポロジカル）。`selfhost/lexer.pw`・`selfhost/calc.pw` が実証。**次：実 Plew サブセットの全トークン lexer → サブセット parser+C codegen を Plew で → ファイル/stdin で自分を食わせて self-host**。

### stage0 のメモリモデル（重要・spec とは別物）

stage0 は **throwaway（1 回コンパイルして終了）**。よって Array は **ヒープ確保＋リーク（free しない）＋参照セマンティクス**で実装する（ARC/CoW は未実装）。値意味論との差（エイリアス後変更の観測）は、**stage1 を「アリーナ＋index・単一所有」で書く規律**で回避する（Rust 版 stage0 と同じスタイル＝AST も `ExprId` 等で arena+index）。spec の CoW 値意味論は**セルフホスト後の Plew 製コンパイラで正しく実装**する。これは spec の言語意味論を変えるものではなく stage0 の実装戦略（委任範囲内）。

## 全体ロードマップ（第一目標＝Plew でコンパイラが書ける → 即セルフホスト）

1. ✅ プロジェクト立ち上げ（C#/ANTLR/LLVMSharp と g4 を破棄 → Rust `bootstrap/`、lib+bin、cargo）
2. ✅ **Lexer**（手書き・token 列・span・コメント・数値/文字列/演算子の maximal munch）＋テスト
3. 🔨 **Parser**（再帰下降・AST を arena+index で）
   - ✅ 式：literal/ident/unary/binary（優先順位14段・非結合・グルーピング・エラー回復）
   - ✅ postfix：call（ラベル付き引数・末尾カンマ）/field `.`/index `[]`（postfix > prefix を担保）
   - ✅ 文・宣言（最小）：`fn` 宣言（params・`~:`・`-> ret`）・block・`val`/`mut val`・`return`・式文・型（`Array[I32]` 等）
   - ✅ 制御フロー：`if`/`else`/`else if`（式として）・ブロック式・`give`（パース）。codegen は `if` を**文位置**で対応
   - ✅ ループ：`while`（文位置 codegen）＋代入 `=`／複合代入 `+= -= *= /= %= &= |= ^= <<= >>=`。合計ループが e2e で動作
   - ⏭ 式の続き：`as`（要・型パーサ）・`try`/`await`・JSX `<T .. />`・closure・`match`・`?.`・**値位置 if/give の codegen**（clang statement-expr）
   - ⏭ 他宣言：`struct`/`enum`/`impl`/`trait`/`import` …
4. ✅ **C コード生成（最小）** ＋ clang ドライバ ＝ walking skeleton（`print(int)`→printf）
5. 🔨 **型検査（最小）**＝双方向推論で数値リテラル型確定・Bool 条件・演算子型・呼び出し検査（`typeck.rs`）✅。残り＝struct/enum/String/Array へ拡張・codegen に型を通す
6. 🔨 `struct`/`enum`＋`match`
   - ✅ `struct`/`enum` 宣言のパース（フィールド vis/mut・generics `[T]`・variant payload・`export` 受理・`where` は未対応で loud）。typeck/codegen は当面スキップ（codegen は loud エラー）
   - ✅ JSX 構築 `<Type field=expr />`（ドット path で enum variant も・`/>` は 1 トークン `SlashGt`）
   - ✅ **struct 縦串**：`Ty::Struct`＋レジストリ、C struct typedef＋複合リテラル＋`.field`。`<Point x=3 y=4/>`→`p.x+p.y`=7
   - ✅ **enum + match 縦串**：`Ty::Enum`＋variant 構築（`<E.V .../>`）＋match（パターン束縛・網羅性検査）。codegen はタグ付き共用体＋switch（enum）/if-chain（int/Bool）。e2e で `Shape.Circle`→5、int match→20。**制約**：match は文位置のみ（値位置/`give` は未対応）、variant パターンは `E.V` 形（codegen）、variant フィールドのネストパターン未対応
   - ✅ **型を codegen に通す土台**：typeck が `CheckResult.expr_ty`（式 ID→型）を返し codegen が参照（print 書式の型ベース選択など）
   - ✅ **String（最小）**：型 `String`・文字列リテラル・`print(String)`。C 表現は `PlewString{const char* data; int64_t len}`（リテラル backed・ヒープ/ARC なし）。連結・可変・`bytes` 等は未実装
   - ✅ **値位置の `if`/ブロック**：GNU statement-expression＋三項で codegen（typeck は give 型を期待型から解決）。e2e で if→1、block→9
   - ✅ **`for val i in a..<b` レンジループ**：codegen は C counting loop。`0..<5`（両端リテラル）は spec 通り曖昧エラー＝型付き上限が必要（`0..<n`）。リテラル側を後で型付けし `0..<n` を曖昧にしない。配列反復・`for (k,v)` 分解は未対応
7. 🔨 **次の本丸**：
   - ✅ **型レジストリを codegen に公開**：typeck が `CheckResult.table: TypeTable`（struct/enum 名 id→名、`Array[T]` 要素型の interning）を返し、codegen が `Ty→C名`（`ty_c_name`/`mangle`）を解決。
   - ✅ **Array（単相化・読み取り中心）**：`[..]` リテラル／`arr[i]`（範囲外 panic）／`arr.count`（U64）／`for val x in arr`。C 表現＝`PlewArray_<mangle>{T* data; len; cap}`＋per-type ランタイム（`_new`/`_get`）。要素型ごとに単相化（プリミティブ/struct/enum/ネスト配列可）。メモリはリーク（上記メモリモデル）。
   - ✅ **Array 変更操作**：`arr.append(x)`（伸長・cap<4→4→倍々で realloc・旧バッファはリーク）／`arr[i] = x`・`arr[i] OP= x`（IndexSet・範囲外 panic）。メソッド呼び出しの土台＝typeck `check_method`（レシーバ型でディスパッチ・現状 Array の `append` のみ＝`print` 同様の stage0 ビルトイン）／codegen `emit_array_method`・`emit_index_set`（receiver は addressable lvalue 前提・`_push`/`_set` ランタイム）。空 `[]` から成長可。**制約**：append/index-set は base が C lvalue のときのみ（Ident/field）。
   - ✅ **String バイトアクセス＋等価**：`s.bytes`（spec 通り `Array[U8]`・O(1)・バッファ共有＝stage0 の参照セマンティクス配列で表現）／`String` の `==`/`!=`（バイト等価＝`PlewString_eq`）。これで Plew 製レキサが「ソースを `source.bytes` で走査・キーワードを `==` 照合」できる土台ができた。**未**：substring（owned コピー）・連結・`Ord`・scalars/graphemes。
   - ✅ **`break`/`continue`**（文）。**enum match を C switch→tag の if-chain に変換**＝match アーム内の `break`/`continue` が（switch でなく）ループを正しく対象にする。clang は `-w`（生成 C は警告クリーンを目指さない）。
   - ✅ **複合機能スモークテスト通過**：enum トークン種＋struct トークン＋`Array[Tok]`＋enum 返す関数＋`while` で `src.bytes` 走査＋`append`＋`match`（block アーム）＝ミニレキサが compile&run。**match アームに文を置くには block `=> { … }` が必要**（spec 通り＝アームは式）。
   - ⏭ import 機構／値位置 `match`／codegen の整数幅反映／名前解決の本格化。
   - ✅ **stage1 レキサ素描が compile&run**（`selfhost/lexer.pw`）：整数/識別子/キーワード/単一文字記号を tokenize、arena 風 `Array[Tok]`（source を (start,len) で参照＝文字列materializeなし）。キーワード照合は純 Plew バイト比較（`rangeEquals`・substring 不要）。`"val x = 12 + foo * (3)"`→10 トークンの種別列を検証（e2e `selfhost_lexer_sketch_builds_and_runs`）。**substring 無しでレキサが書けることを実証**。
   - ✅ **`inout` パラメータ**（spec/03）：宣言 `x: inout T`／呼び出し `f(x: inout a)`（両側明示・引数は place）。codegen は C ポインタ＝callee 内で `(*p)`・呼び出しで `&(place)`。struct フィールド変更も配列 append も関数越しに伝播（パーサのカーソル状態 threading が書ける）。`borrow`/`move` はコピー可能型でエラー（spec 決定）。**未**：`mut` 束縛の検査（inout 引数が `val` でも今は通す）・重なり inout 検査・`inout fn`（メソッド self）。
   - ✅ **パーサ素描が compile&run**（`selfhost/calc.pw`）：算術式パーサ＋評価器。`inout p: Parser` でカーソル相互再帰・arena+index AST（`Array[Expr]`・U64 index＝`as` 回避）・enum payload・再帰 eval。`"2 + 3 * (4 + 5) - 1"`→28（e2e `selfhost_calc_parser_builds_and_runs`）。**パーサ・フェーズの言語要件を実証**。
   - ✅ **codegen の型順序対応**：構造体がArrayを含む／Arrayの要素が構造体、の循環を「①全 nominal の前方宣言 `typedef struct N N;`／②Array typedef（要素はポインタ＝前方宣言で足る）／③構造体/enum 本体を依存順（by-value 含有でトポロジカル）／④Array ランタイム（要素を値で扱う＝本体後）」で解決。関数は**プロトタイプ**を本体前に出して相互再帰可。
   - 📝 **パーサ素描で判明した言語の罠（spec 通りだが書き手が嵌まる）**：①フィールド名に `val` 不可（キーワード衝突）②enum variant フィールドも `val name: T`（`val` 必須）③match のフィールド punning は `{ val name }`（`val` 前置・bare `{ name }` は variant パターン扱い）④`as` キャスト未実装＝index 型は `count` と同じ `U64` で統一して回避。
   - ✅ **`as` 数値キャスト**（spec/12）：`*` より強く prefix より弱い・左結合・stage0 は numeric↔numeric のみ・C キャスト。`3 as I64`（裸リテラル source）は曖昧エラーのまま＝`as` は default を供給しない（no-default 原則と整合）。
   - ✅ **stdin/stdout I/O**（stage0 ビルトイン・`@Std` の fiction）：`readStdin() -> String`（全 stdin）・`write(s: String)`（生・改行なし）。stage1 を stdin→stdout フィルタにでき、codegen 断片を逐次 `write` できる（文字列連結不要）＝真の self-host への足場。
   - ✅ **実 Plew サブセットの全トークン lexer**（`selfhost/lexer.pw`・stdin→トークン種別列）：整数/文字列リテラル・識別子/19 キーワード・行コメント・改行（collapsed）・全区切り＋多文字演算子（`-> => /> == != <= >= += -= *= /= %= ..< ..= && ||`）。`Lexer{bytes,pos,toks}` を `inout` で持ち回り `Array[Tok]` 構築。`fn add(a: I64, b: I64) -> I64 { return a + b }` を正しく tokenize（e2e `selfhost_lexer_tokenizes_a_function`・stdin パイプ）。**Go 流 newline 抑制も実装済み**（`()`/`[]` 内は継続・文を終えられるトークンの後だけ Newline・`{` 後は出さない＝stage0 と一致）。**未**：文字列エスケープ・Float リテラル・`~:`/ビット演算子。
   - ⏭ 次：このトークン列を食う**サブセット parser を Plew で**（arena+index AST・`inout p`）→ C codegen を Plew で（`write` 断片出力）。名前解決は線形スキャン。self-host は `plewc-stage1 < x.pw > x.c`。**ファイル I/O**（自分自身を読む＝真の self-host に必須・現状ハードコード文字列）と **`Dictionary` or 線形スキャン**（名前解決）はその先。AST 再帰は arena+index（`ExprId`=U32 包み）で回避予定。
   - ⏭ import 機構／値位置 `match`／codegen 整数幅は必要になった時点で。
7. ⏭ → stage1（Plew でコンパイラ）に必要な分が揃い次第セルフホスト
6. **stage1**：Plew サブセットでコンパイラを書く → stage0 で compile → 自己 compile＝**セルフホスト達成**
7. 以降 LLVM/WASM・循環回収・所有権検査などを Plew 側で additive に

詳細・省略する機能の一覧は [architecture.md](architecture.md)「ブートストラップ戦略」を参照。

## 次の一歩（パーサ着手時の段取り案）

- AST ノード定義（arena 前提）。まず**式 → 文 → 宣言**の順で最小から。
- パーサの骨格（トークンカーソル・エラー回復方針）＋最初のテスト（整数リテラル/二項演算の優先順位）。
- 構文の全体像と優先順位は [grammar.md](grammar.md)（構文リファレンス＝spec 索引）と spec/12（演算子 14 段）を参照。

## 戦略メモ

- **walking skeleton 優先**：パーサを作り切る前に「`fn main` の小さなプログラム → C 生成 → clang → 実行」の縦串を通す（C トランスパイル＋clang 連携を早期検証・動く成果物）。マイルストン `first-c-output`。
- 残りの順序：lexer 改行 ✅ → 文/ブロック/`fn`宣言 → 最小 C codegen + clang ドライバ → 縦串。その後に式の続き（`as`/match/JSX 等）と他宣言を肉付け。

## 既知の暫定ギャップ

- ✅ **数値リテラルの型確定**：型検査（`typeck.rs`）で双方向推論を実装し、`val x = 6*7`（曖昧）を loud に拒否・注釈で解決・条件は Bool 強制・演算子型不一致も検出。テストで担保（tests/typeck.rs）。
- **`print` は暫定の組み込み**：本来は **import 必須**（ambient でない・`import @Std/...`・正確なパスは stdlib 設計時）で、シグネチャは **`print[T](~value: T) where T: Format`**（Format 準拠なら何でも）。stage0 は import 機構・トレイト・String 未実装のため、print を数値専用の組み込み（型検査で I64 pin・codegen は printf 直結）として暫定扱い。stdlib 整備時に置換。
- **codegen は依然 `int64_t` 前提**：型検査は I32/U64/F64 等を区別するが、codegen は全整数を int64_t で出す（幅が違う型は未対応）。型を codegen に通す＝次段。
- オーバーフロー panic・`as`・NaN 比較 panic 等の数値実行時意味論は未実装（codegen 素朴）。

## 直近の決定・注意（揮発しやすい文脈）

- **文の区切り＝改行（Go 流自動終端・Swift 流の括弧内継続）を採用・確定**（ユーザー追認済・spec/01「文の区切り」に反映）。詳細・根拠は design-decisions.md「文の区切り＝改行」。

- **タグ運用**：動作する区切りで記述的タグ（`lexer-working` 済予定）。バージョン番号はまだ使わない。
- **メモは repo 内**（CLAUDE.md / claude/）に。外部 memory は使わない。
- **判断に迷ったら突き進まず仰ぐ**。不要ファイルは容赦なく消してよい。
- `grammar.md` は ANTLR 機構の記述が陳腐化（g4 破棄済）。転用予定＝下半分の「構文 × spec」表はパーサ実装チェックリストとして残す。
