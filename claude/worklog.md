# 作業ログ

> 現在地・次の一歩・運用メモだけを置く。完了した「やった」は git 履歴へ（タグで辿れる）。「なぜ」は [design-decisions.md](design-decisions.md)、「パイプライン設計」は [architecture.md](architecture.md)、「spec からの意図的剥離」は [provisional.md](provisional.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で `Lexer`/`Ast`/`Parser`/`Codegen` を綴じ込む 1 モジュール）。自分自身を不動点までコンパイルする。

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust/cargo 不要）。`./bootstrap.sh --reseed` で種更新。
- **テスト**：`./test.sh`＝`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/part/`（複数ファイル）＋`tests/reject/*.pw`（plewc が非ゼロ終了で reject＝受理の健全性）＋不動点（Rust 非依存）。
- **サポート済の言語**（現状スナップショット・経緯は git/タグ）：型付き整数/Bool・String（リテラル/`.bytes`/`==`/エスケープ）・文字リテラル `'c'`・Array（リテラル/添字/`count`/`append`/`a[i]=x`/for-each）・struct と JSX 構築・enum＋match（**網羅検査**・**or パターン `A|B`**・rename/discard 束縛 `{f: val n}`/`{f: _}`・**値位置 `match` 式**）・enum `==`（全 nullary）・**可変性検査（place 単位＝単純変数＋`base.field` 合成＋`a[i]` 配列束縛＋`.append`/`inout fn` メソッド受信側）**・関数/**引数ラベル検査**/`inout`/再帰・**インヘレントメソッド `impl Type { fn / inout fn }`**・**`panic`**・`if`/`else`/`while`/`for`/`break`/`continue`・**値位置 `if` 式＋ブロック `give`**（`else` 必須・`else if` チェーン可）・演算子（算術・比較・論理・**ビット/シフト `& | ^ << >> ~`**・単項 `! - ~`・**`as`〔整数・無損失のみ＝縮小/符号変更/リテラル範囲外は reject〕**・複合代入 `+= … %=`・**ビット系複合代入 `&= |= ^= <<= >>=`**・**整数は厳密幅で格納〔stdint〕＋算術/除算オーバーフロー・0除算は panic＋リテラル文脈型付け〔既定型なし・文脈で確定・曖昧は reject・型サフィックス `5U64`〕**）・**モジュールローダ＝再帰＋dedup の worklist**（`part ./Name`・`import ./Name`・`import ./Sub/Name`・`import ../Name`・`import /Seg/Seg`〔`Plew.toml` 上方探索→`<root>/src` 起点・`crate::` 相当〕を解決・diamond 1 回・循環終了・名前は当面フラット〔with ゲート I2 未〕）・**`import @Std/{Io,Process} with {}`**（I/O は ambient でなく import 必須・print/write/writeByte/readStdin/readFile(Bytes)/argCount/argAt/eprint/exit/fileExists）・診断 `compileError(At)` は**普通の Plew 関数**（`eprint`/`exit` 経由・脱 ambient 済）。軽量型追跡・配列単相化・preamble 自前出力・生成 C は警告クリーン。**コンパイラ自身がメソッド/match 式/or パターンで自己記述**（dogfood）。
- **spec からの意図的剥離**（値意味論/CoW・整数幅・トレイト・モジュール詳細等）は [provisional.md](provisional.md) に集約。足場（履歴）`examples/{lexer,parser,emit,calc}.pw`。

## 受理の健全性（意味上 Plew として正しい）＝一区切り

「このコンパイラが*受理*するコードは spec でも valid」を目標に hidden meaning を潰す。チェックリスト（詳細 [provisional.md](provisional.md)）：① import なし `print` ② ラベル無視 ③ 非網羅 match ④ lossy `as`（無損失のみに制限・縮小/符号変更/リテラル範囲外を reject） ⑤ struct/array 比較 ⑥ 不変 place への代入（単純変数＋`base.field` 合成＋`a[i]`＋`.append`/`inout fn` 受信側）＝**全項解消済**。残る穴は限定的＝ラベル抑制/メソッドラベル（②残）・式幅が復元できない `as`（④残・式幅伝播は overflow と同時）・let-init リテラル範囲＝いずれも「accepted⟹valid」の方向では incremental。違反はすべて `compileError*` 診断＝`plewc: error: [line N: ]…`＋非ゼロ終了で reject。

## 次の一歩の候補（やりやすい順で自走）

### 整数幅エピック — Phase A/B/C/D ✅ 完了

**済（A+B+C）**：
- **A：式幅伝播** — `exprType` が算術/ビット二項（→左辺幅）・単項 `-`/`~`（→operand 幅）を伝播。`(a-b) as U8` が narrowing として reject される。
- **C：narrow storage** — `genCElem` が各整数型を厳密幅 stdint（`int8_t…int64_t`/`uint16_t…uint64_t`・U8 は `unsigned char`・Bool は long long）に。これで宣言幅で overflow 検査が成立。コンパイラ自身の値は小さい非負ゆえ挙動不変＝fixpoint 維持。
- **B：overflow/division panic** — 算術 `+ - *`（二項・複合代入・配列要素複合）と単項 `-` が `__builtin_*_overflow` で結果型幅に溢れたら `plew_panic("integer overflow")`。`/ %`・`/= %=` は width＆符号認識の inline 文（0除算 panic・signed `INT_MIN/-1` overflow panic・`x % -1`=0 で C UB 回避）、width 不明は zero+`INT64_MIN/-1` 検査済 `plew_div`/`plew_mod`。`tests/panic/` カテゴリを test.sh に追加（compile+link 成功・実行は非ゼロ＋stderr 部分一致）。
- 残る穴（rare・documented）：両オペランドが幅不明な式（`(1+1):U8` 等リテラルのみ）の算術文脈オーバーフロー、配列要素 `/= %=` の narrow-signed `INT_MIN/-1`。

**確定済の言語判断**（spec／design-decisions）：U64 添字/count/range・`as`無損失（符号変更/縮小は `TryFrom`）・overflow/0除算は常に panic・**リテラル既定型なし＋曖昧はエラー**・`assert`常時ON・`wrapping*` メソッド明示。

**Phase D1（リテラル文脈型付け・範囲検査）✅ 完了**。純粋検査パス `checkLitCtx`（C 出力不変）が文脈の整数型をリテラルへ伝播：let 注釈/代入先/引数(仮引数型)/戻り(戻り型)/配列要素/struct・enum フィールド/添字(U64)/比較・算術の型付き相手から型を降ろし、範囲外リテラルと**定数式オーバーフロー（`200+100:U8`）**を compile error。先頭 `-` はリテラルへ畳み込み（`-128:I8` 可）。`Expr.Int` に source offset を追加し診断行を正確化。`litFitsBits` を per-width 定数比較に（`1<<31` の C int 溢れバグ修正）。

**Phase D2（厳密 no-default＝context-free リテラルを曖昧エラー）✅ 完了**。spec の「初手は厳格（明示要求）」（02-basic-types.md）に合わせ、文脈型の無い整数リテラルは `compileError`（`val x = 1 + 1`・`for val i in 0..<5` 等を reject）。実装：
- **型サフィックス `5U64`/`1I32`**（parser）＝Int トークン直後（隣接・空白なし）の整数型名 Ident を suffix として取り込み `Expr.Int.tyStart/tyLen` に格納。`Expr.Int` に `isBool`（`true`/`false` 分離＝Bool は曖昧でない）も追加。
- **`exprIntTy`**＝sibling 推論用に span-free で整数型(bits,sgn)を復元：`arr.count`→U64・`arr[i]`→要素型・builtin `argCount()`→I64。これで `0..<arr.count` は suffix 不要（spec 通り）。
- `checkLitLeaf`：isBool→skip／suffix 有→suffix 型で範囲検査（曖昧でない）／eKind1→文脈幅で範囲検査／eKind0→**曖昧エラー**。
- 注意：`for` の本体が I64 演算なら範囲も `0..<5I64`（`tests/run/for.pw`）。suffix は型を与えるだけで storage は従来通り（無注釈 let は long-long＝widening の hidden cost のみ）。

> 着手手順は ADD→reseed→USE（下節）。各 Phase で不動点を緑に保ってから commit。新 preamble 行や **codegen 挙動変化（genCElem 等）を足したら reseed 2 回**（1 世代遅れる）。AST ノードへのフィールド追加（`Expr.Int` の offset 等）も出力が変わるので reseed 2 回。

### ★ 第一目標：コンパイラのソース自体を spec-valid に（完全 Plew コンパイラで通す）

整数幅エピック完了で、コア言語の使い方は spec-valid に到達。残るは**ソースが現コンパイラ固有の緩みに依存している箇所**（→ [provisional.md](provisional.md) 冒頭「ソース spec-validity チェックリスト」）：

- ✅ **S1 完了**：診断 `compileError`/`compileErrorAt` を**普通の Plew 関数**（Codegen.pw・`eprint`＋`exit`＋`digitStr` 由来の `eprintInt`）に。`@Std/Io` `eprint(text: String)`・`@Std/Process` `exit(code: I32)` を import-gate ビルトインとして追加し _.pw で import、codegen 特別扱いと dead な `plew_compile_error*` preamble を撤去。これで診断の ambient 依存は解消。
- **S2（大物・要 spec 決定）**：`@Std` I/O の実シグネチャ。特に `print(整数)` の可否＝print の真シグネチャと、`readFile`/`readFileBytes` の**可謬化＝`Optional`/`Result`/`try`（spec/13）エピック**。std 領域のシグネチャは spec 表面（core-lib 未決）ゆえユーザー確認が要る。

### ★ import / モジュール（本物のコアライブラリの土台）

manifest は **`Plew.toml`**（spec 暫定名・TOML・src 既定 `src/`・`/` は `<root>/src` 起点）。ネスト配列 `Array[Array[U8]]` は**使えない**（`PlewArray_Array` で要素型 `Array` 未定義）ので、パス一覧は flat バッファ＋`Array[Bind]`(span) で持つ。

- ✅ **I1a 完了**：モジュールローダ＝再帰＋dedup の worklist（`compiler/src/_.pw` の driver）。各ファイルの `part ./Name`・`import ./Name` を**そのファイルのディレクトリ相対**で解決し、distinct ファイルを 1 回だけ combined バッファへ。diamond は 1 回・循環は終了。コンパイラ自身の flat 同一 dir parts は同順同内容＝不動点維持。`tests/part/crossimport`。
- ✅ **I1b 完了**：パスを構造的に解決。`./Name`・`./Sub/Name`（サブディレクトリ）・`../Name`/`../../Name`（親相対・`../` ごとに importer dir を 1 段 strip）・`/Seg/Seg`（root 絶対＝`findSrcRoot` が entry から上方へ `Plew.toml` を探し `<root>/src` を起点に・**ネストした entry からでも src ルート解決**＝`crate::` 動作）。`fileExists` ビルトイン（`plew_file_exists`）で manifest を検出。manifest は位置のみ使用（中身未読・src 既定）。`@Std` は Dot/Slash 始まりでないので自然にスキップ。`tests/part/rootimport`（`Plew.toml`＋`src/`）。
- ⏳ **I2 with ゲーティング**（次・難所）：今は include したファイルの名前が全部フラットに見える。`import ./Foo with { bar }` で `bar` だけ可視・未 import 名はエラーに。要：各トップレベル定義の**モジュール所属**追跡＋各 import 文の許可名集合＋名前使用時の可視性検査（今は全フラット・所属情報なし）。
- 既知の別件：Plew 識別子が **C 予約語**（`double` 等）だと生成 C が壊れる＝名前マングリング未実装（コンパイラ自身は回避済・ユーザーコードで顕在化・S 系とは別の hidden-meaning 穴）。
- ⏳ **I3 @Std 実体化**：`@Std/X`→std ディレクトリ解決。純 Plew のもの（`Core` の `Optional`/`Result`）は generics 後。`@Std/Io`/`Process` は extern/FFI まではイントリンシック裏付けのまま。
- 後で additive：修飾名 `Foo.bar`・`export`・`public` マニフェスト・`_.pw` ディレクトリ代表。

### ★ 確定ロードマップ（generics → コアライブラリ → ランタイム）

意味論の hidden-meaning は大半解消済み（整数幅・match・ラベル・診断）。残りは小さく additive。**拠り所「意味は最優先・コストは裏で後回し可」に照らし、leak ランタイムは hidden-cost ゆえ後回しでよい**。大物は以下の順で（合意済み）：

1. **generics**（全ての門）＝型パラメータを struct/enum/fn に＋一般単相化（`Array[E]` 専用ハードコードを一般機構へ）。境界なし（trait 境界は traits と一緒に後段）。**`Ref[T]`/`Promise[T]`/`Optional[T]`/`Result[T,E]` が全部これに依存**。今の C トランスパイル上で完結でき、後の CoW は additive。
2. **本物のコアライブラリ（純 Plew）**＝`@Std/Core` に `Optional`/`Result` 等を generic enum で実装。要 **I3＝`@Std/X` の実ファイル解決**（ローダは I1 で完成済み・`@Std`→std ディレクトリの解決を足す）。**import の正しい dogfood＝真に独立したモジュール**。これで **`try`＋可謬 I/O（`readFile`→`Result`）** が書けて **S2（残る hidden-meaning）も閉じる**。
3. **CoW**（値意味論・核の de-risk・以後コードがアリーナ規律から解放）。traits 不要。
4. **ARC ＋ `Ref`/`WeakRef`**（共有可変＋循環回収・generics 必要）。
5. **イベントループ（async/await/spawn）**（最大・`Promise[T]` 依存・最後）。
- traits（`Eq`/`Ord`/`Iterator` ＋ `where` 境界）は generics 後・コアライブラリと並走で純 Plew 化。I2（モジュール可視性ゲート）は多モジュール化が進む段で additive に。

> **着手中＝generics**。まず既存の `Array[E]` 単相化機構（`PlewArray_<E>`・要素型名マングル・`Comp.arrayElems`）を一般 generic の土台に拡張する。

#### generics 実装の段取り（言語表面は spec/06 で確定済＝確認不要）

確定済の言語表面：型パラメータ `[T]`/`[T, U]`＋能力マーカー `noLocal`/`allowUnique`（v1 は `allowUnique` 不実装＝コピー可能型限定・`unique` は `Ref` 包み）、トレイト制約は `where`（traits エピックなので **v1 は境界なし**＝parse して無視 or 後回し）、use-site の型引数 `Name[TypeArgs]`（PascalCase＝型引数適用／camelCase＝添字＝Go 式判別）、推論＋明示 `f[I32](...)`。`impl[T] Type[T]`。

現状の型表現 `(start, len, isArray)` は `Array[E]` 専用ハードコードで `Name[Arg, ...]`（複数引数・ネスト）を表現できない。これが土台。**コンパイラ自身は generics を使わない（Array＋scalar＋非 generic named のみ）ので、新機構は既存 Array 経路と併存で additive に足せる＝低リスク**。

- **G1（土台・型表現）**：`TypeRef` アリーナ（`struct TypeRef { nameStart, nameLen: U64; args: Array[U64] }`・`Comp.types`）導入。`parseTypeTok` を `Name[Arg, ...]` 再帰パースに一般化（`Array[E]` は `TypeRef{Array,[E]}` に吸収）。型を運ぶ全箇所（`Param`/`FieldDef`/`Func.ret`/`Local`/`Stmt.Let`/`Expr.Cast`/`Comp.curRet`/`PType`）の `(tyStart,tyLen,isArray)` 三つ組を `ty: U64`（TypeRef index）へ。codegen の型出力（`genCTypeRef`/`genCElem`）を TypeRef 受けに。**挙動不変の純リファクタ**＝不動点＋全テストで検証。
- **G2（generic struct/enum＋単相化）**：struct/enum に `[T,U]` 型パラメータ。プログラム全 TypeRef から具体インスタンス化 `Name[ConcreteArgs]` を収集→型パラメータ置換でフィールド/バリアント型を実体化→ネスト発見の推移閉包→マングル名 `Name_Arg1_Arg2` で C struct/enum を 1 インスタンスずつ出力。JSX 構築 `<Box[I32] v=5 />`・`<Optional[I32].Some v=5 />`。
- **G3（generic 関数/メソッド）**：`fn f[T]`・呼び出しで型引数推論（引数型から）or 明示 `f[I32](...)`・`impl[T] Type[T]` メソッド。呼ばれたインスタンスを単相化。
- **G4（コアライブラリ接続）**：`Optional`/`Result` を実 generic enum 化（次エピックのコアライブラリで）。

ADT 注意：ネスト配列 `Array[Array[U8]]` は今壊れる（`PlewArray_Array`・要素型未定義）＝G1/G2 でネスト TypeRef を正しくマングルすれば解消見込み（要テスト）。AST フィールド形を変えるので **reseed 2 回**ルール適用。

進捗：✅ **G1 完了**（TypeRef アリーナ＋`ty`/`retTy`/`ref` フィールド・`parseTypeTok` 再帰パース・挙動不変）。✅ **G2 step1 完了**（struct/enum に `[T,U]` 型パラメータ・`typeParams` 保持）。✅ **G2 step2＝単相化インフラ完了**（`genInsts`・TypeRef sentinel index0・`genericStructIndex`/`isGenericInst`/`typeRefEq`/`emitMangle`/`emitConcreteCType`/`emitFieldCType`/`genCTypeOf`/`scanType`/`collectGenInsts`/`emitMonoForward`/`emitMonoStruct`・use-site C 型を `genCTypeOf` 経由に・driver で generic template skip＋mono 出力）。✅ **G2a 完了＝generic struct が end-to-end**（宣言・`<Box[I32] v=5/>` 構築・`b.v` フィールド read・多パラメータ `Pair[A,B]`・ネスト `Box[Box[I32]]`・関数引数/戻り値。Make に型引数パース＋`Expr.Make.ty`・`typeInfoOfRef`/`genericFieldTypeInfo`・checkMakeFields/Make emission が generic 分岐。`tests/run/generic_struct{,_multi,_fn}`）。

**次＝G2b（generic enum＝Optional/Result）**：mono enum body 出力（`genEnumDef` を mangled 名＋フィールド置換で）・構築 `<Optional[I32].Some v=5/>`（Make の isEnum 経路を mangled 名・variant 置換）・**match**。match の難所＝scrut の具体インスタンス化を知る必要＝**`TypeInfo` に `ref: U64` を足す**（`exprType(Ident)`＝local の `lo.ty`、`exprType(Make)`＝`ty` をセット）→ match codegen が scrut 型 ref から mangled enum 名で C temp 宣言・`genBindType`/`variantIndex` を mono enum に対応（bind フィールド型は型パラメータ置換）。`emitMonoEnum(c, instRef)` を `genEnumDef` の置換版で。collectGenInsts は struct/enum 両対応に拡張（`isGenericInst` を enum も含むよう一般化＝`genericDeclIndex`）。

**その後＝G3（generic 関数/メソッド）**：`fn f[T]`・呼び出しで型引数推論（引数型）or 明示 `f[I32](...)`・`impl[T] Type[T]` メソッド・呼ばれたインスタンスを単相化（関数も mangle）。

#### G2 単相化の設計（実装中・次の一歩）

**TypeRef の sentinel**：`ty`=0 を「型なし」にするため、parse 前に `c.types` 先頭へダミー TypeRef を 1 個 push（実型は index 1+）。`addLocal` の synthetic `ty:0` 等が誤って実型 0 を指さないように。

**スコープ（G2a＝generic struct 先行）**：型引数は scalar/String/非 generic named＋他の generic struct インスタンス化（ネスト可）に限定。**Array を型引数/ generic フィールド型に置くのは保留**（`PlewArray_<name>` マングルと衝突＝別途）。**generic フィールドが型パラメータを含む別 generic 適用（`Box[T]` の中の `Foo[T]`）も G2a では保留**＝フィールド型は「型パラメータそのもの or 具体型」のみ＝推移閉包不要に。enum（Optional/Result）は **G2b**。

**機構（Codegen.pw に追加予定）**：
- `genericStructIndex(c, nameStart, nameLen)→U64`：typeParams 付き struct の index（なければ count）。enum 版も。
- `typeRefEq(c, a, b)→Bool`：head span＋args 再帰比較（dedup 用・文字列バッファ不要）。
- インスタンス収集：**use site のみ**走査（G2 は generic 関数なし＝use site の args は常に具体）＝c.funcs の param.ty/retTy・非 generic struct/enum のフィールド ty・全 Stmt.Let.ty・Expr.Cast.ty・Expr.Make の型引数。generic struct head のものを `Comp.genInsts`（TypeRef index・`typeRefEq` で dedup）へ。**arg が generic inst なら先に再帰収集（post-order）**＝by-value ネストの定義順を満たす。
- `emitMangle(c, ref)`：`Box[I32]`→`Box_I32`、`I32`→`I32`（args を `_` 連結・再帰）。インスタンス struct 名＝generic inst の C 型名。
- `emitConcreteCType(c, ref)`：具体 TypeRef の C 型＝args 無→`genCElem`／generic inst→`emitMangle`。
- `emitFieldCType(c, fieldRef, params, args)`：フィールド型が型パラメータなら対応 arg の C 型（`emitConcreteCType(args[i])`）、でなければ `emitConcreteCType(fieldRef)`。
- `emitMonoStruct(c, instRef)`：`struct Box_I32 { <substituted field ctype> field; ... };`。
- use site の C 型出力ラッパ `genCTypeOf(c, tyRef, fallStart, fallLen, isArray)`：generic inst（非 Array・args 有・head が generic）なら `emitConcreteCType`、でなければ既存 `genCTypeRef`。Let(2234)/genSignature param/ret/genStructDef field/genEnumDef field の呼びを差し替え。
- `_.pw` の emission ループ：通常 struct/enum ループで **generic decl を skip**（テンプレート）→ genInsts の forward typedef＋body を出力（G2a は struct body のみ）。

**まだ要るもの（end-to-end テストに必須）**：Make の型引数 `<Box[I32] v=5/>` パース＋codegen（`(Box_I32){.v=5}`）・フィールドアクセス `b.v` の型回復（exprType が generic inst を返す）。これらが揃って初めて `tests/run` で検証可能。**G2b（enum）は match の scrut 型を mono 名に・genBindType の置換・variant tag も。**

### その他の候補（エピック後）
- 値意味論/CoW・トレイト/ジェネリクスは更に大物（後）。
- **メソッド化の続き（任意・ROI 逓減）**：残る `parseX(c: inout c)` 群も `impl` へ移せるが再帰的・多数でゲイン小＝後回し可。

> import の現状＝**`with {}` 選択形のみ**・認識するのは I/O ビルトインだけ（`@Std/Io`＝print/write/writeByte/readStdin/readFile(+readFileBytes)・`@Std/Process`＝argCount/argAt）・名前↔モジュール検査あり。名前空間 import・実モジュール解決・`export`・`/`/`../` ルート・`_.pw` ディレクトリ・ネスト part 追従は未実装。

## 機能を plewc.pw に足す手順（ADD→reseed→USE）

新機能を plewc.pw の**ソースで使う**には：①`compiler/src/` の codegen に機能を足す（**ADD**）→ ②`./bootstrap.sh --reseed` で種更新（→ `compiler/plewc.seed.c` を commit）→ ③ソースで使う（**USE**）。「ソースが使う機能は常にひとつ前のコンパイラがサポート済み」を守れば不動点は壊れない。新しい preamble 行を足した直後は種が 1 世代遅れるので **reseed を 2 回**回す（1 回目で挙動を種に焼き、2 回目で種ファイルを一致させる）。暗黙ビルトイン → 実 `@Std`/`extern` への将来移行も同じ ADD→USE→REMOVE で flag day にならない。

## メモリモデル（hidden cost の暫定・重要）

Array は **ヒープ確保＋リーク（free しない）＋参照セマンティクス**で実装（spec の CoW 値意味論/ARC は未実装）。エイリアス後変更が観測できてしまう差は、**plewc.pw を「アリーナ＋index・単一所有」で書く規律**で回避している。正しい CoW/ARC は後で（hidden cost＝受理の健全性の対象外）。詳細は [provisional.md](provisional.md)。

## 運用メモ

- 動作する区切りで**記述的 git タグ**（`self-host`/`char-literals` 等・バージョン番号はまだ）。コミットメッセージは英語。
- **不要になった実装は削除し、必要なら git tag から復旧**（例：`git checkout stage0-final -- bootstrap`）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。メモは repo 内（外部 memory は使わない）。
- LLVM 化は当面しない＝意味論が揃ってから（import/トレイト/所有権の後）、性能 or 直 WASM が要る時に並行バックエンドとして追加（C は捨てない）。
