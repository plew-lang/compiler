# 作業ログ（実装フェーズ）

> compact がいつ走っても復帰できるよう、**今やっていること・次にやること**をこまめに更新する。古い完了項目は git 履歴に任せて圧縮してよい（「なぜ」は design-decisions、「設計」は architecture へ）。

## 現在地（一言）

stage0（Rust）で **Plew 製コンパイラ（`selfhost/plewc.pw`・v1）が Plew プログラムを C に変換し clang が通す**段階に到達。stage0 サポート済み：型付き整数/Bool/String（`.bytes`/`==`・リテラルのエスケープ `\n`/`\"`/`\\`）・Array（リテラル/添字/`count`/for-each/`append`/`arr[i]=x`・リーク参照セマンティクス）・struct・enum+match（文位置・if-chain）・if/else/while/for（range/array）・関数（相互再帰・プロトタイプ）・`break`/`continue`・**`inout` パラメータ**・**`as` 数値キャスト**・stdin/stdout I/O（`readStdin`/`write`/**`writeByte`**＝putchar・識別子スパン出力用）。codegen は型を依存順に出力（前方宣言＋トポロジカル）。**Plew 製コンパイラ v1（`selfhost/plewc.pw`）が compile&run**：単一トップレベル関数の本体を C `main` に変換＝`val`/`mut val`・代入（`= += -= *= /= %=`）・`if`/`else`/`else if`・`while`・`print`・式（優先順位付き precedence-climbing・単項・括弧・識別子スパン出力）。arena+index AST。stdin→C を stdout に。**v2 関数/引数/呼び出し/再帰・v3 struct/JSX/フィールド・v4 enum/match・v5 Array/String/ビルトイン**まで実装済（型注釈は実 C 型へ反映・軽量型追跡 `exprType`・配列単相化・String.bytes 共有ビュー・I/O ランタイム preamble を自前出力）。実証用 selfhost ファイル：`lexer.pw`（全トークン）・`parser.pw`（トークン列パーサ）・`emit.pw`（式→C ミニコンパイラ）・`calc.pw`（バイト列パーサ）。**残るは `inout` 引数のみ＝実装すれば `plewc < plewc.pw` で self-host 可能（最後の山）**。

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
   - 📝 **パーサ素描で判明した言語の罠**：①フィールド名に `val` 不可（キーワード衝突・spec 通り）②~~enum variant フィールドも `val` 必須~~ → **撤廃済**：variant フィールドは修飾子なし `name: Type`（`val`/`mut`/`pub` は意味を持たない＝design-decisions 参照）③match のフィールド punning は `{ val name }`（`val` 前置必須）。bare `{ name }` は **「フィールド `name` を束縛するなら `val name` と書く」と案内するエラー**を出し `val name` として回復する（(B) 実装済・サイレント誤動作ではない）④`as` キャスト＝実装済（index は `U64` 統一の必要なし）。
   - ✅ **`as` 数値キャスト**（spec/12）：`*` より強く prefix より弱い・左結合・stage0 は numeric↔numeric のみ・C キャスト。`3 as I64`（裸リテラル source）は曖昧エラーのまま＝`as` は default を供給しない（no-default 原則と整合）。
   - ✅ **stdin/stdout I/O**（stage0 ビルトイン・`@Std` の fiction）：`readStdin() -> String`（全 stdin）・`write(s: String)`（生・改行なし）。stage1 を stdin→stdout フィルタにでき、codegen 断片を逐次 `write` できる（文字列連結不要）＝真の self-host への足場。
   - ✅ **実 Plew サブセットの全トークン lexer**（`selfhost/lexer.pw`・stdin→トークン種別列）：整数/文字列リテラル・識別子/19 キーワード・行コメント・改行（collapsed）・全区切り＋多文字演算子（`-> => /> == != <= >= += -= *= /= %= ..< ..= && ||`）。`Lexer{bytes,pos,toks}` を `inout` で持ち回り `Array[Tok]` 構築。`fn add(a: I64, b: I64) -> I64 { return a + b }` を正しく tokenize（e2e `selfhost_lexer_tokenizes_a_function`・stdin パイプ）。**Go 流 newline 抑制も実装済み**（`()`/`[]` 内は継続・文を終えられるトークンの後だけ Newline・`{` 後は出さない＝stage0 と一致）。**未**：文字列エスケープ・Float リテラル・`~:`/ビット演算子。
   - ✅ **トークン列を食うパーサを Plew で**（`selfhost/parser.pw`）：lexer を同梱し `Array[Tok]` を消費＝トークンカーソル `inout p: Parser` を進め `match Tok.kind` でディスパッチ・Int リテラルの値を (start,len) スパンからソースバイト経由で復元（`tokenValue`）。式文法（`+ - * / %`・括弧・優先順位）を arena+index AST に。`"1 + 2 * 3 - 4 % 3"`→6（e2e `selfhost_token_parser_builds_and_runs`・stdin）。**バイトでなくトークン列を食う self-host パーサの形を実証**。
   - ✅ **C codegen を Plew で＝ミニコンパイラ**（`selfhost/emit.pw`）：式を読み（lex→tokens→AST）、計算する**完全な C プログラムを stdout に出力**（`write` で逐次・String 連結不要）。整数の十進化は桁ごとの digit リテラル（`"0".."9"`）を再帰 `write`（stage0 String は不変・連結不可ゆえ構築でなく選択）。完全括弧化した C 式を AST から出力。二段検証＝stage0 が emit.pw をビルド→実行で C 取得→clang で C をコンパイル→実行→28（e2e `selfhost_emit_compiles_a_c_program`）。**lex→parse→emit-C の縦串が Plew 側で end-to-end・stage0 文字列エスケープも動作確認**。
   - ✅ **`writeByte(b: U8)` stage0 ビルトイン**（putchar）：self-host コンパイラが識別子テキストをソーススパンから C へ書き出すのに必須（stage0 String は不変・substring なし）。typeck（U8 引数）＋codegen（putchar）に配線。
   - ✅ **Plew 製コンパイラ v1（`selfhost/plewc.pw`）が compile&run**：単一トップレベル関数の本体を C `main` に変換。lex→parse→emit-C を Plew で end-to-end。サポート＝`val`/`mut val`（型注釈はスキップ＝全 int64_t）・代入（`= += -= *= /= %=`）・`if`/`else`/`else if`・`while`・`print`・式（precedence-climbing：`|| && == != < <= > >= + - * / %`・単項 `- !`・括弧・整数/Bool/識別子）。arena+index AST（`enum Expr`/`enum Stmt`＋`struct Block`＝stmt id の `Array[U64]`・`struct Comp` が全 arena 保持＝`inout c` 持ち回り）。op は kindCode(I64) で保持（enum-in-enum 回避）。識別子は (start,len) スパンを `writeByte` でエコー。三段検証＝stage0 が plewc.pw をビルド→Plew プログラムを食わせ C 取得→clang→実行（sum-loop→10、e2e `selfhost_plewc_compiles_a_plew_program`）。
   - ✅ **plewc.pw v2＝複数関数＋引数＋ユーザー呼び出し**：トップレベル `fn` を順に読み（`parseProgram`/`parseFunc`）、by-value 引数 `name: Type`（型スキップ＝全 `long long`・ラベル=名前）、`Expr.Call`（ラベルは drop し位置引数で C 出力・enum payload に `Array[U64]` を載せられることを stage0 単体検証済）、戻り値型（`-> ret` 有=`long long`/無=`void`/`main`=`int main(void)`）、相互再帰用に**全非 main 関数の前方プロトタイプ**を先出し。`return` は関数種別（main/void/値）で出し分け（`curIsMain`/`curRetVoid` を codegen 中に設定）。`add`+`fib(10)` プログラム→7,55（e2e `selfhost_plewc_compiles_functions_and_calls`）。
   - ✅ **plewc.pw v3＝struct/JSX 構築/フィールドアクセス＋型注釈の C 型反映**：`struct Name { (val|mut val) f: T ... }`（修飾子は consume して無視）を `parseStruct`→`StructDef`/`FieldDef`。JSX `<Type f=e ... />`（`parseMake`→`Expr.Make`＋`MakeField` 配列）を C 複合リテラル `(Type){.f = e, ...}` に。postfix `.field`（`parsePostfix`→`Expr.Field`・チェーン可）。型注釈を実 C 型へ反映開始＝`genCType`：scalar（I8..U64/Bool）→`long long`・named（struct）→名前エコー（`Stmt.Let`/フィールド/構造体本体）。struct は前方 typedef を全部先出し→本体（source 順＝依存順前提・topological は後で）。enum の dotted `<E.V .../>` は consume するが未モデル（v4）。nested struct＋chained field プログラム→7,14（e2e `selfhost_plewc_compiles_structs`）。
   - ✅ **plewc.pw v4＝enum + match**：`enum Name { Variant [{ f: T, ... }] }`（variant フィールドは修飾子なし）を `parseEnum`→`EnumDef`/`Variant`。C はタグ付き共用体 `struct E { long long tag; union { struct {...} V; ... } data; }`（nullary variant は `char _u` ダミー）。JSX variant 構築 `<E.V f=e/>`→`(E){.tag=idx, .data.V={.f=e}}`（`Expr.Make` に `isEnum`/variant span 追加）。`match scrut { E.V { val f } => { ... } _ => {...} }`→`Stmt.Match`→**tag の if-chain**（フレッシュ temp `_mN`・wildcard=`else`）。**型推論不要**＝パターンが `Enum.Variant` を明示するので tag index（`variantIndex`）とフィールド型（`genBindType`）を enum 宣言から線形スキャンで解決。**引数/戻り値型も実 C 型へ**（`Param`/`Func` に型スパン・`genSignature` で `genCType`）。enum/struct とも前方 typedef を全部先出し→本体（plewc.pw の集約は全て Array＝ポインタ経由ゆえ本体順序非依存）。`area(Shape)` プログラム→75,24（e2e `selfhost_plewc_compiles_enums_and_match`）。match アームは block body 限定（plewc.pw が使う形・bare-expr arm は未対応）。
   - ✅ **plewc.pw v5＝Array + String + ビルトイン（最大の codegen 山）**：軽量な型追跡を導入＝`Local`（変数→型の環境・関数ごとにリセット＋引数登録・`val`/match束縛で追加）＋`exprType`（式の型を bottom-up 復元＝`TypeInfo` kind 0scalar/1String/2named/3array）。これで `c.bytes`（struct フィールド）と `kw.bytes`（String ビルトイン）を**型推論で区別**。型は `PType`（element 名＋isArray）で表現（`parseTypeTok` が `Array[E]`→element 捕捉）。**Array 単相化**：宣言から要素型名を収集（`arrayElems`・dedup）→`PlewArray_<E>` typedef＋ランタイム（`_new`/`_get` 範囲チェック/`_set`/`_push` 倍々・リーク）を要素ごとに生成（stage0 と同型）。`[]`/`[a,b]` リテラルは宣言型から要素を取り `genArrayLiteral`（空＝`_new()`・非空＝statement-expr で push）・`a[i]`＝`PlewArray_E_get`・`.append`＝`_push`（`Expr.Method`）・`.count`＝`.len`。**String**＝`PlewString{const char* data; long long len}`・リテラルは内容 verbatim＋decoded length（`strDecodedLen`）・`.bytes`＝`PlewArray_U8` で char バッファを O(1) 共有ビュー（U8 要素＝`unsigned char`・U8 配列は常時 emit＝span 不要のハードコード）。**ビルトイン**＝`write`→`plew_write`・`writeByte`→`putchar`・`readStdin`→`plew_read_stdin` を Call codegen で認識し、**ランタイム preamble（PlewString＋I/O 本体）を plewc 自身が出力**＝出力 C は自己完結（self-host 契約を満たす）。出力順＝preamble→nominal forward→array typedef→nominal body→array runtime→prototypes→bodies（stage0 と同じ依存順）。配列＋文字列プログラム→42,3（e2e `selfhost_plewc_compiles_arrays_and_strings`）。
   - ⏭ 次：**`inout` 引数（self-host 最後の山）**＝plewc.pw 自身が `inout c: Comp`/`inout lx: Lexer` を多用。codegen＝宣言側はポインタ引数（`T* p`）・本体で `p` の使用を `(*p)` に・呼び出し側 `f(x: inout a)` は `&(a)` を渡す。Param に inout フラグを持たせ、Ident codegen で inout 引数なら deref。これが通れば **`plewc < plewc.pw` で self-host**（不動点検証）。**ファイル I/O**（自分を読む）と struct の topological 順序（相互 by-value 参照時）はその過程で。
   - ⏭ import 機構／値位置 `match`／codegen 整数幅は必要になった時点で。
7. ⏭ → stage1（Plew でコンパイラ）に必要な分が揃い次第セルフホスト
6. **stage1**：Plew サブセットでコンパイラを書く → stage0 で compile → 自己 compile＝**セルフホスト達成**
7. 以降 LLVM/WASM・循環回収・所有権検査などを Plew 側で additive に

詳細・省略する機能の一覧は [architecture.md](architecture.md)「ブートストラップ戦略」を参照。

## 次の一歩（パーサ着手時の段取り案）

- AST ノード定義（arena 前提）。まず**式 → 文 → 宣言**の順で最小から。
- パーサの骨格（トークンカーソル・エラー回復方針）＋最初のテスト（整数リテラル/二項演算の優先順位）。
- 構文の全体像と優先順位は [grammar.md](grammar.md)（構文リファレンス＝spec 索引）と spec/12（演算子 14 段）を参照。

## self-host の契約（後戻り回避・重要）

stage0 が plewc.pw に**暗黙提供**しているのは閉じた小さな一式だけ＝**I/O ビルトイン4つ**（`print`/`write`/`writeByte`/`readStdin`）＋**C ランタイム preamble**（`PlewString`・`PlewArray_<T>`＋配列ランタイム・上記4関数の本体）。パース/型/codegen ロジックは全て plewc.pw 側（純 Plew）にあり、I/O はこれで飽和（これ以上ビルトインは要らない）。

**規律＝「plewc.pw が依存する stage0 の振る舞いは、必ず plewc.pw 自身の codegen にも実装する」**。そのリストに載るのは上記 I/O 4つ＋ランタイム preamble のみ。Array/String フェーズ（v5）で「stage1 の codegen が `write`→`plew_write` を出し、preamble に `PlewString`・配列ランタイム・I/O 本体を自前で吐く」ところまでやり切れば、stage1 の出力 C は自己完結し stage0 依存が消える。

**後戻りは silent には起きない**：self-host は不動点検証（`plewc < plewc.pw > a.c` → `clang a.c` → `plewc2 < plewc.pw > b.c`・`a.c == b.c`）で宣言する。取りこぼしがあれば出力 C が未定義参照でコンパイル失敗＝stage0 を捨てる前に即露見。よってビルトインの暗黙埋め込みは Rust への後戻りトラップにならない（stage0 は throwaway のまま）。

### 暗黙埋め込み → `extern`/`@Std` への将来移行（非破壊の段階分け＝ADD→USE→REMOVE）

self-host 後、暗黙埋め込み（ランタイム自動注入＋魔法ビルトイン）を実 `@Std`/`extern` に置換したくなる。これを**非破壊**にやる鉄則＝「新しい形を*使う*前にコンパイラに*受理*させる／旧挙動の除去は最後」。各コミットは「ひとつ前のコンパイラ」でビルドし不動点を保つ：
1. **ADD**：コンパイラに `extern`/import 宣言の**受理**を足す（自動注入は継続）。ソースは未変更→旧コンパイラで通る。
2. **USE**：plewc.pw の**ソース**に `extern`/import を足す（ステップ1のコンパイラが受理できるので通る・注入は冗長だが無害）。
3. **REMOVE**：コンパイラの自動注入を**やめ** extern＋別コンパイルの runtime.o リンクに切替（ステップ2のコンパイラがまだ注入するので新ソースを通せる）。
flag day（同時破壊）にならない理由＝ソースが使う機能は常に前バージョンがサポート済み。急ぐ必要なし（self-host を妨げない）。魔法ビルトインは import 機構＋最小 `@Std` ができるまでの代用で、言語表面には未露出（`print`/`write` は本来 `@Std`＋`Format`）。

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
