# 作業ログ

> 現在地・次の一歩・運用メモだけを置く。完了した「やった」は git 履歴へ（タグで辿れる）。「なぜ」は [design-decisions.md](design-decisions.md)、「パイプライン設計」は [architecture.md](architecture.md)、「spec からの意図的剥離」は [provisional.md](provisional.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で `Lexer`/`Ast`/`Parser`/`Codegen` を綴じ込む 1 モジュール）。自分自身を不動点までコンパイルする。

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust/cargo 不要）。`./bootstrap.sh --reseed` で種更新。
- **テスト**：`./test.sh`＝`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/part/`（複数ファイル）＋`tests/reject/*.pw`（plewc が非ゼロ終了で reject＝受理の健全性）＋不動点（Rust 非依存）。
- **サポート済の言語**（現状スナップショット・経緯は git/タグ）：型付き整数/Bool・String（リテラル/`.bytes`/`==`/エスケープ）・文字リテラル `'c'`・Array（リテラル/添字/`count`/`append`/`a[i]=x`/for-each）・struct と JSX 構築・enum＋match（**網羅検査**・**or パターン `A|B`**・rename/discard 束縛 `{f: val n}`/`{f: _}`・**値位置 `match` 式**）・enum `==`（全 nullary）・**可変性検査（place 単位＝単純変数＋`base.field` 合成＋`a[i]` 配列束縛＋`.append`/`inout fn` メソッド受信側）**・関数/**引数ラベル検査**/`inout`/再帰・**インヘレントメソッド `impl Type { fn / inout fn }`**・**`panic`**・`if`/`else`/`while`/`for`/`break`/`continue`・**値位置 `if` 式＋ブロック `give`**（`else` 必須・`else if` チェーン可）・演算子（算術・比較・論理・**ビット/シフト `& | ^ << >> ~`**・単項 `! - ~`・**`as`〔整数・無損失のみ＝縮小/符号変更/リテラル範囲外は reject〕**・複合代入 `+= … %=`・**ビット系複合代入 `&= |= ^= <<= >>=`**）・**`import @Std/{Io,Process} with {}`**（I/O は ambient でなく import 必須）・複数ファイル **`part ./Name`**・I/O ビルトイン（print/write/writeByte/readStdin/readFile(Bytes)/argCount/argAt）・診断 `compileError(At)`。軽量型追跡・配列単相化・preamble 自前出力・生成 C は警告クリーン。**コンパイラ自身がメソッド/match 式/or パターンで自己記述**（dogfood）。
- **spec からの意図的剥離**（値意味論/CoW・整数幅・トレイト・モジュール詳細等）は [provisional.md](provisional.md) に集約。足場（履歴）`examples/{lexer,parser,emit,calc}.pw`。

## 受理の健全性（意味上 Plew として正しい）＝一区切り

「このコンパイラが*受理*するコードは spec でも valid」を目標に hidden meaning を潰す。チェックリスト（詳細 [provisional.md](provisional.md)）：① import なし `print` ② ラベル無視 ③ 非網羅 match ④ lossy `as`（無損失のみに制限・縮小/符号変更/リテラル範囲外を reject） ⑤ struct/array 比較 ⑥ 不変 place への代入（単純変数＋`base.field` 合成＋`a[i]`＋`.append`/`inout fn` 受信側）＝**全項解消済**。残る穴は限定的＝ラベル抑制/メソッドラベル（②残）・式幅が復元できない `as`（④残・式幅伝播は overflow と同時）・let-init リテラル範囲＝いずれも「accepted⟹valid」の方向では incremental。違反はすべて `compileError*` 診断＝`plewc: error: [line N: ]…`＋非ゼロ終了で reject。

## 次の一歩の候補（やりやすい順で自走）

### ★ 進行中エピック：整数幅をやり切る（次セッションの本線）

**済**：④ lossy `as`（無損失のみ）・0除算 panic。**方針＝意味先行**：`TypeInfo` がスカラ型名を保持（kind=0＋name）・C 型は 64bit 据え置き・コンパイラは U64 に揃え `as` 厳密無損失。**確定済の言語判断**（spec／design-decisions）：U64 添字/count/range・`as`無損失（符号変更/縮小は `TryFrom`）・overflow/0除算は常に panic・**リテラル既定型なし＋曖昧はエラー**・`assert`常時ON。

**残りを以下の順で**（A は小・先に commit／B が本丸／C は hidden cost で後回し可／D は別重量）：

- **Phase A：`exprType` に式の幅を伝播**（④ の残穴 `(a-b) as U8` を閉じる・小）。Binary 算術(56–60)/ビット(74–78)→ `exprType(lhs)`、比較(50–55)/論理(61,62)→ Bool(width-less)、シフトは lhs 型。Unary `-`/`~`→operand 型・`!`→Bool。`exprType(Binary)` の他利用（place 検査の base 等）は低リスクだが不動点で確認。これで `as` check の「source 不明→lenient」分岐が縮む。
- **Phase B：overflow panic**（hidden meaning の本丸）。幅つき型の算術で真の結果が型に収まらなければ panic。Phase A の結果幅が前提。**設計未決→着手時に方針提示**：①clang の `__builtin_*_overflow` を結果幅で使い溢れたら `plew_panic`（推奨・部品少）vs ②`plew_add_<T>` 等の (op×型) ランタイム関数（5op×8型＝冗長だが明示）。幅不明の式は検査不能＝skip（要 documented）。
- **Phase C：幅つき C ストレージ**（hidden cost・後回し可）。`genCElem`/`genTypeInfoCType` を `int8_t…uint64_t` に（今は long long）。**Cを入れるとC算術が幅で wrap する**ので、Bの溢れ検査は wrap 前（より広い型 or 組込みで真値）に走らせる必要＝B と密結合。配列要素/フィールド/ローカル/引数/戻りを一斉。最大の不動点リスク（U64→uint64_t はコンパイラの非負値に対し挙動不変ゆえ通るはず）。**64bit 据え置きでも「宣言幅で overflow 検査」は成立**するので、意味完全性（A+B+D）には C は必須でない＝C は独立の cost フォローアップに切れる。
- **Phase D：リテラル文脈型付け**（hidden meaning＋人間工学）。`val f: U8 = 300` の範囲検査・文脈（let 注釈/フィールド/引数/戻り/配列要素・`as` は済）からリテラル型を決める。**設計未決→着手時に方針提示**：完全な双方向 no-default 推論 vs 注釈必須-else-error の暫定。現状の「全部 long long・print は I64 fallback」を文脈駆動へ替える＝**現在 accept しているコードを reject し得る**ので慎重に。
- **推奨順＝A→B→D（意味完全）／C は別途 cost 対応**。A 着手が安全な第一手。

> 着手手順は ADD→reseed→USE（下節）。各 Phase で不動点を緑に保ってから commit。新 preamble 行（overflow ランタイム等）を足したら **reseed 2 回**。

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
