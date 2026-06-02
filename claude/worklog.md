# 作業ログ

> 現在地・次の一歩・運用メモだけを置く。完了した「やった」は git 履歴へ（タグで辿れる）。「なぜ」は [design-decisions.md](design-decisions.md)、「パイプライン設計」は [architecture.md](architecture.md)、「spec からの意図的剥離」は [provisional.md](provisional.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で `Lexer`/`Ast`/`Parser`/`Codegen` を綴じ込む 1 モジュール）。自分自身を不動点までコンパイルする。

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust/cargo 不要）。`./bootstrap.sh --reseed` で種更新。
- **テスト**：`./test.sh`＝`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/part/`（複数ファイル）＋`tests/reject/*.pw`（plewc が非ゼロ終了で reject＝受理の健全性）＋不動点（Rust 非依存）。
- **サポート済の言語**（現状スナップショット・経緯は git/タグ）：型付き整数/Bool・String（リテラル/`.bytes`/`==`/エスケープ）・文字リテラル `'c'`・Array（リテラル/添字/`count`/`append`/`a[i]=x`/for-each）・struct と JSX 構築・enum＋match（**網羅検査**・**or パターン `A|B`**・rename/discard 束縛 `{f: val n}`/`{f: _}`・**値位置 `match` 式**）・enum `==`（全 nullary）・**可変性検査（place 単位＝単純変数＋`base.field` 合成＋`a[i]` 配列束縛＋`.append`/`inout fn` メソッド受信側）**・関数/**引数ラベル検査**/`inout`/再帰・**インヘレントメソッド `impl Type { fn / inout fn }`**・**`panic`**・`if`/`else`/`while`/`for`/`break`/`continue`・**値位置 `if` 式＋ブロック `give`**（`else` 必須・`else if` チェーン可）・演算子（算術・比較・論理・**ビット/シフト `& | ^ << >> ~`**・単項 `! - ~`・**`as`〔整数・無損失のみ＝縮小/符号変更/リテラル範囲外は reject〕**・複合代入 `+= … %=`・**ビット系複合代入 `&= |= ^= <<= >>=`**・**整数は厳密幅で格納〔stdint〕＋算術/除算オーバーフロー・0除算は panic＋リテラル文脈型付け〔既定型なし・文脈で確定・曖昧は reject・型サフィックス `5U64`〕**）・**`import @Std/{Io,Process} with {}`**（I/O は ambient でなく import 必須）・複数ファイル **`part ./Name`**・I/O ビルトイン（print/write/writeByte/readStdin/readFile(Bytes)/argCount/argAt）・診断 `compileError(At)`。軽量型追跡・配列単相化・preamble 自前出力・生成 C は警告クリーン。**コンパイラ自身がメソッド/match 式/or パターンで自己記述**（dogfood）。
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

### その他の候補（エピック後）

- **`import ./Foo`（名前空間束縛 `Foo.bar`）**。修飾名解決が要る（今は part で全部フラット同一スコープ）。part の provenance 穴の正攻法。
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
