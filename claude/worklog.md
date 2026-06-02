# 作業ログ（実装フェーズ）

> compact がいつ走っても復帰できるよう、**今やっていること・次にやること**をこまめに更新する。古い完了項目は git 履歴に任せて圧縮してよい（「なぜ」は design-decisions、「設計」は architecture へ）。

## 🎉 セルフホスト達成（2026-06-02）

**第一目標達成＝Plew で書かれたコンパイラが自分自身をコンパイルできる（不動点）。** `selfhost/plewc.pw`（Plew 製コンパイラ）を stage0 でビルド→`plewc`、`plewc` が plewc.pw を C 化（`c1`）→clang で `plewc1`、`plewc1` が plewc.pw を C 化（`c2`）、**`c1 == c2`（完全一致）**。`plewc1` は実プログラム（算術/struct/enum/array/string）も正しくコンパイル＝動く自己ホスト型コンパイラ。e2e `selfhost_plewc_reaches_fixpoint` で恒常検証。stage0（Rust）はこれで throwaway 化＝以降の機能追加は Plew 側（plewc.pw）で additive に。

**post-self-host フェーズ（1→4 順）**：
1. ✅ **真の自己ビルド**＝`plewc plewc.pw`（ファイル引数）。stage0＋plewc.pw 両方に I/O ビルトイン追加＝`readFile(path)→String`・`argCount()→U64`・`argAt(i)→String`（C ランタイム＝`plew_read_file`/`plew_arg_count`/`plew_arg_at`・main を `int main(int argc, char** argv)` 化し argc/argv をグローバルへ）。plewc.pw の main は引数あれば `readFile(argAt(1))`・無ければ `readStdin()`。`plewc plewc.pw > c` → clang → `sb1`、`sb1 plewc.pw` で不動点も確認。
2. ✅ **生成 C の警告クリーン化**（plewc.pw の codegen のみ修正＝stage0 不問・不動点維持）。`-Wall -Wextra` で 4 種ゼロ化＝①`-Wparentheses-equality`（`if ((a==b))`）→`genCond`（条件位置の最上位 binary は外側括弧を省く）②`-Wunused-variable`（match 束縛）→束縛直後に `(void)name;`③`-Wunused-function`（要素型ごとの未使用配列ランタイム・I/O ヘルパー）→生成 static ヘルパーに `__attribute__((unused))`④`-Wreturn-type`（wildcard 無しの網羅 match で C が fall-through と誤認）→`else { __builtin_unreachable(); }`。回帰ガード＝不動点 e2e の c1 コンパイルを `-Wall -Wextra -Werror` に。
3. 🔨 言語機能を plewc.pw 側で拡張（post-self-host は Plew 側で additive）。
   - ✅ **`for` ループ**（`Stmt.For`）＝`for val i in a..<b`/`a..=b`（range・inclusive で `<=`）と `for val x in arr`（配列を index で走査）。codegen は C for ループへ脱糖（range＝`for(long long var=lo; var </<= __feN; var++)`・array＝`{ PlewArray_E __faN = arr; for(...) { E var = PlewArray_E_get(__faN, __fiN); ... } }`）。ループ変数を locals に登録（range＝scalar・array＝要素型）。**plewc.pw 自身の driver で dogfood**（本体出力ループを `for val j in 0..<c.funcs.count` に）→ stage0 が新 plewc.pw をビルド・self-built が不動点維持・警告クリーン（e2e `selfhost_plewc_compiles_for_loops`）。
   - ✅ **String `==`/`!=`**（型指向＝`exprType(lhs)` が String なら `PlewString_eq(...)`／`!=` は `!`・`isStringEq` ヘルパー・`genCond` も String eq を genExpr 経由に）＋ **`a[i] = v` index-set**（`Stmt.Assign` の target が `Expr.Index` なら `PlewArray_E_set(&base, i, v)`・複合 `a[i] OP= v` は `set(.., get(..) OP v)`＝`assignToBinStr`）。e2e `selfhost_plewc_compiles_string_eq_and_index_set`（1,1,40,13）・不動点維持・警告クリーン。
   - ✅ **enum `==`/`!=`（暫定・variant 同一性）**＝タグ比較に脱糖（variant 構築は tag index リテラル・他は `(expr).tag`）。**全 nullary enum 限定で許可**（`curKind == <Kind.LParen />` は正しい）・**payload 持ち enum の `==` は loud エラー**（未宣言識別子 `__plew_enum_eq_requires_Eq_derive` を出し C コンパイル失敗＝沈黙バグ回避）。本筋は `@[Eq]` derive で構造的 Eq（→ provisional.md）。variant 値は JSX 一本化を維持（bare `Foo.Bar` 不採用・「どちらでも書ける」回避）。型省略 JSX `<.LParen />` は未決（surface 追加）。
   - ⏭ 候補（次）：受理の健全性（下記の現在目標）／値位置 `if`/`match`／トレイト等。
4. ✅ **stage1 正典化**（→ 5 で stage0 退役）：当初は `bootstrap.sh` で stage0 経由ブートストラップ＋不動点検証。CLAUDE.md を self-host 達成・**今後の機能は plewc.pw 側に Plew で additive**へ更新。
5. ✅ **stage0 退役（Rust 削除）＋Rust 非依存テスト**：
   - **C 種ブートストラップ**＝`selfhost/plewc.seed.c`（plewc.pw の C 訳・チェックイン・gitignore 例外）。`bootstrap.sh` を `clang 種→plewc0→plewc.pw 自己コンパイル→不動点 cmp(種, 再生成)` に書換（Rust/cargo 不要）。`./bootstrap.sh --reseed` で plewc.pw 変更時に種再生成。新機能を plewc.pw 自身で使う手順＝**ADD（stage1 codegen に足す）→reseed→USE**。
   - **`bootstrap/`（Rust stage0）を削除**（タグ `stage0-final` で復旧可＝`git checkout stage0-final -- bootstrap`）。**削除方針＝不要になった実装は消し、必要なら git tag から復旧**（ユーザー方針）。
   - **テストを Rust から `.pw` シェルハーネスへ移行**＝`test.sh`＋`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/reject/*.pw`（spec-invalid＝コンパイル失敗を確認＝受理の健全性）＋不動点。stage0 内部 API 依存の Rust テストは stage0 ごと退役。`./test.sh`→pass=11。
   - **LLVM 化の方針（決定）**：当面やらない。捨てるのは codegen バックエンド層（2〜3 割）のみで lexer/parser/型/import/トレイト機構は生き残る・C バックエンドは可読/移植性で残す価値あり。**意味論が一通り揃ってから（import/トレイト/所有権の後）、性能 or 直 WASM が要る時に並行バックエンドとして追加**。先回りの IR 構築は premature。

## 現在の目標：受理の健全性（意味上 Plew として正しい）

**このコンパイラが*受理*するコードは spec でも valid にする**（完全な Plew コンパイラも通せる）。spec が reject するのに今 accept してしまう所＝hidden meaning を潰す。逆向きの不完全性（valid だが未実装で reject＝`<.LParen />`・トレイト等）は許容。ランタイム挙動の誤り（hidden cost＝leak・int 幅・overflow 非 panic）は対象外（後回し）。要修正リストは [provisional.md](provisional.md)「受理の健全性チェックリスト」＝①**import なしで `print` が書ける**（最優先＝import/`@Std`/モジュール機構）②ラベル無視 ③非網羅 match ④lossy `as` ⑤struct `==`。**enforce は plewc.pw 自身にも及ぶ**ので ADD→reseed→USE で plewc.pw を spec-valid 化していく。実装が楽になるもの（import 等）は先に入れてよい。

## 現在地（一言）

**セルフホスト達成済・stage0 退役済。** 正典コンパイラ＝`selfhost/plewc.pw`（Plew 製）。ビルドは C 種 `selfhost/plewc.seed.c` から（`./bootstrap.sh`・Rust 不要）、テストは `./test.sh`（Rust 非依存）。plewc.pw がサポート済の言語：型付き整数/Bool/String（リテラル/`.bytes`/`==`/エスケープ）・Array（リテラル/添字/`count`/`append`/`a[i]=x`/for-each・**リーク参照セマンティクス**＝CoW 未実装）・struct/JSX 構築/フィールド・enum+match（網羅前提・タグ if-chain）・enum `==`（全 nullary 限定）・関数/引数/`inout`/再帰・`if`/`else`/`while`/`for`（range/array）・`break`/`continue`・`as`（数値）・I/O ビルトイン（`print`/`write`/`writeByte`/`readStdin`/`readFile`/`argCount`/`argAt`＝**import なしの暫定**）。軽量型追跡 `exprType`・配列単相化・I/O ランタイム preamble を自前出力。生成 C は警告クリーン（`-Wall -Wextra -Werror`）。

**次の目標は上記「受理の健全性」**（import/`@Std` を筆頭に、spec が reject すべきものを reject する）。実証用の小コンパイラ `lexer.pw`/`parser.pw`/`emit.pw`/`calc.pw` は self-host 途上の足場（履歴的価値）。

### メモリモデル（重要・spec とは別物＝hidden cost の暫定）

現コンパイラは Array を **ヒープ確保＋リーク（free しない）＋参照セマンティクス**で実装（ARC/CoW 未実装）。spec の CoW 値意味論との差（エイリアス後変更の観測）は、**plewc.pw を「アリーナ＋index・単一所有」で書く規律**で回避している。spec の CoW/ARC は後で正しく実装する（hidden cost＝受理の健全性の対象外）。詳細は [provisional.md](provisional.md)。

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
   - ✅ **plewc.pw v6＝inout 引数＋`as`＋配列代入＝SELF-HOST 達成**：`inout` パラメータ（宣言側＝ポインタ `T* p`・本体の使用を `(*p)` に deref・呼び出し側 `f(x: inout a)`＝`&(a)`・`Param`/`Local` に isInout・呼び出し引数は `Arg{expr,isInout}`）。`as` キャスト（`Expr.Cast`・postfix で `as Type`・`((cty)(operand))`）。配列リテラルの**代入**（`c.locals = []`＝target 型が array なら `genArrayLiteral`）。**レキサに文字列エスケープ処理**（`\X` スキップ＝自分のソースの `"\""`/`"\n"` を正しく tokenize）。**enum 本体を struct 本体より先に出力**（`struct Tok` が `Kind`〔enum〕を値で含む唯一の by-value nominal 依存を解決・full topological は将来）。→ **`plewc < plewc.pw` の不動点が成立**（e2e `selfhost_plewc_reaches_fixpoint`）。
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

→ **仕様からの意図的剥離の網羅カタログは [provisional.md](provisional.md) に集約**（値意味論/CoW・整数幅・レンジ・ラベル・トレイト・モジュール等＝「バグでなく既知の暫定」）。ここには揮発しやすい個別メモだけ残す：

- ✅ **数値リテラルの型確定**：型検査（`typeck.rs`）で双方向推論を実装し、`val x = 6*7`（曖昧）を loud に拒否・注釈で解決・条件は Bool 強制・演算子型不一致も検出（tests/typeck.rs）。
- 大物（整数幅・値意味論・レンジ・ラベル・トレイト・`Result`/`try` 等）は provisional.md 参照。再訪は self-host 後に stage1 側で additive。

## 直近の決定・注意（揮発しやすい文脈）

- **文の区切り＝改行（Go 流自動終端・Swift 流の括弧内継続）を採用・確定**（ユーザー追認済・spec/01「文の区切り」に反映）。詳細・根拠は design-decisions.md「文の区切り＝改行」。

- **タグ運用**：動作する区切りで記述的タグ（`lexer-working` 済予定）。バージョン番号はまだ使わない。
- **メモは repo 内**（CLAUDE.md / claude/）に。外部 memory は使わない。
- **判断に迷ったら突き進まず仰ぐ**。不要ファイルは容赦なく消してよい。
- `grammar.md` は ANTLR 機構の記述が陳腐化（g4 破棄済）。転用予定＝下半分の「構文 × spec」表はパーサ実装チェックリストとして残す。
