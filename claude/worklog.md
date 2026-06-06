# 作業ログ

> 現在地・次の一歩・運用メモ・再利用資産だけを置く。完了した「やった」は git（記述的タグ）へ。「なぜ・却下案」は [design-decisions.md](design-decisions.md)、パイプライン設計は [architecture.md](architecture.md)、spec からの意図的剥離・暫定は [provisional.md](provisional.md)、メタプロの段取りは [metaprogramming-architecture.md](metaprogramming-architecture.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で全パートを綴じる 1 モジュール）。自分自身を不動点までコンパイル。hidden-meaning（整数幅・match 網羅・ラベル・受理の健全性・値意味論/CoW・`unique`/`deinit`/move・generics・トレイト＋Eq/Ord＋derive＋関連型・クロージャ）は概ね解消。**残る剥離・暫定は [provisional.md](provisional.md) が正典**。

**構文解析は完全に `@Std/Syntax` の責務（A＝フロントエンド統合・完了）。** コンパイラとマクロは**唯一の共有パーサ**を通る＝ドリフトする文法に二重パーサなし。

- **`@Std/Syntax`（構文＝form）**：レクサ `Syntax/Lexer.pw`／値ツリー AST `Syntax/Ast.pw`＋`Syntax/Trees.pw`（String 名・全ノード原本座標 span）／パーサ `Syntax/Parser.pw`（宣言・トップレベル）＋`Syntax/ParseBody.pw`（式・文・パターン・ブロック）／出力ビルダ `Syntax/Build.pw`（`Src`）。入口は `parseProgramAst(p) -> Array[TopItemAst]`（プログラム全体）と `parseItem(source,start,end) -> TopItemAst`（マクロ用＝注釈対象 1 項）。
- **コンパイラ（意味＝meaning）**：`compiler/src/`＝`Loader`（パース駆動ローディング＋パス解決）・`Ast`（arena ノード＋`Comp`）・`Parser/Decl`（＝module-tag helper `markImport`/`recordExport`＋derive 合成 `synth*`。**宣言パーサは持たない**）・`Codegen/`〔Emit/Resolve/Ops/Check/Expr/Stmt/Decl/Mono/Array/Async/Gen/**Lower**〕。`Codegen/Lower.pw` が共有値ツリー（TopItemAst/DeclAst/ImplAst/…）を arena へ lower。
- **ローディングもパース駆動**：driver（`main`）が各ファイルを `c.bytes` に追記→`parseAndLowerFile`（共有パーサで parse＋lower）→返った木の `Import` ノード（import＋part）を辿って子ファイル探索（ハンドロールの事前スキャンなし）。残る I/O（読込・パス解決）と arena バイト配置・module tagging はコンパイラ側＝構文解析でない部分のみ。

完了した大物（詳細は git・記述的タグ）：async/await 段階 1-3（stackless SM）・コアライブラリ境界（`@Std` の `extern "plew-intrinsic"`）・**Array＝`RawBuffer` 床の Plew struct**（[array-struct-plan.md](array-struct-plan.md)）・可視性完全強制・Iterator/Iterable＋lazy map/filter・再帰値型 auto-boxing＋ARC・renovate Phase A（ARC 1 本化・Op enum・expect）＋Phase B B0-B2（型付き AST キャッシュ）・**メタプロ M0/M1**（マクロが実宣言を読んで生成・tag `metaprogramming-m1`）・**A＝フロントエンド統合**（全パース→共有 @Std/Syntax・パース駆動ローディング）・**マクロ入力 `TopItemAst`**（struct/enum/fn に加え **impl/trait** もマクロ対象）・**パターン/構築のフィールド実在検査**（`checkMatchBinds`/`checkMakeFieldExists`＝受理の健全性・旧 silent broken C を loud reject 化）。renovate vs rewrite の判断・負債の地図は [architecture.md](architecture.md)「負債監査の結論」、設計根拠は [design-decisions.md](design-decisions.md)、再利用機構は本書末尾「再利用資産・罠」。

## 次の一歩

A 完了で M1 の理想形（真の 1 AST）に到達・impl/trait もマクロ対象済。**Eq/Ord トレイト演算子配線＋`@[Eq]`/`@[Ord]` derive は実装済**（commit `d33e17e`/`a9e15f2`・[provisional.md](provisional.md)「Eq/Ord」節）。

向かう先＝**Hash → Dictionary（M2 dogfood の本丸）**。ユーザー決定＝**(B) generic Hasher 形**（`fn hash[H](hasher: inout H) where H: Hasher`・マップが算法を選べる Rust 厳密形）。**アルゴリズム＝SipHash-1-3（Rust と同じ・rotl＋wrappingAdd＋xor の U64 のみ＝乗算不要・`wrappingAdd` 実装済）**。

> **🔴 必須 TODO（忘れない）＝ランダムシード（RandomState 相当）**。Rust の `HashMap` は SipHash-1-3 ＋ **マップごとにランダムキー**（DoS 耐性）。Plew にはまだ RNG（`Random`）が無いので、**当面は固定キー（決定的）で SipHash を実装**し、**`Random`/RNG 着手後にマップごとのランダムシードへ差し替える**（アルゴリズム・トレイト形は不変・シード源を差すだけ＝additive）。固定キー間は DoS 耐性なし（コンパイラ内部マップには無害・反復順は spec 未規定なので契約は破れない）。**RNG が入ったら必ずランダムシード化すること。**

- **✅ 前提工事＝完了**：(B) が要求する「**メソッド固有型引数 `[H]`＋メソッド `where H: Trait` 境界＋トレイトディスパッチ越しの `inout H`**」は実装済（commit 後述・test `generic_method_bound_inout`）。`registerMethodInst` をプリミティブ受信者にも拡張（`u64.hash[H]` のインスタンスを登録）＋`collectFnInsts` の推移スキャンにレシーバ env を張り（derive struct の `self.field.hash(...)` が field の generic-method インスタンスを推移 discover）。自由関数 `where` 境界・名前付きメソッド呼びは既に動いていた（差はメソッド経路のみだった）。
- **(a) Hash/Dictionary**：
  1. **✅ `wrappingMul`/`wrappingAdd`/`wrappingSub`（整数全幅）**（commit `aabb800`・privileged codegen lowering・uint64_t で計算→受信者幅へ truncate・test `wrapping_arith`）。
  2. **✅ `Hash`/`Hasher` トレイト＋SipHash-1-3 Hasher（Prelude・固定シード）＋U64/String の `impl … as Hash`**（commit `d8eedb6`・test `hash_siphasher`）。同時に extern body-walk バグ修正。
  3. **✅ `@[Hash]` derive を dogfood（特権合成でなく実 `impl Hash as Derive`）**（commit `4167151`・@Std/Syntax・test gen `derivehash`）。前提として trait 提供 assoc fn 呼び（commit `31c6fe1`）＋derive モデル `Derive`(assoc)/`ParameterizedDerive`(instance)（commit `b90ed6e`）を実装。
  4. **🚧 `Dictionary[K,V]` lang item＝WIP（branch `dict-wip` ＋ `/tmp/dict-wip.patch`）**。ランタイムは**単体で完動**：平行配列（`keys: Array[K]`/`vals: Array[V]`/`hashes: Array[U64]`＋open-addressing の `buckets: Array[U64]`）＋SipHash・insert/update/getOr/contains/count/grow を検証済。**ネスト generic（`Array[Entry[K,V]]`）は単相化されない**ので平行配列で回避、**generic コンストラクタの戻り型推論が無い**ので構築は明示型引数（リテラル lower が供給予定）。`collectFnInsts` に generic-レシーバ・メソッド本体の推移スキャン（`scanGenInstMethodBodies`）を足し `Dictionary.hashOf` 内の `key.hash[H]`→`String.hash[SipHasher]` を discover。**未マージの理由**：Dictionary を**常時ロードの Prelude に置くと `array_methods` が回帰**（`Array[K]`/`Array[V]` フィールド由来の `Array[concrete]` genInst が Array 専用 emit 経路と干渉し、ground されない `Array_T_get` を吐く）。**次にやる＝この Array×genInst 干渉の修正**（Array を genInst emit 経路から除外＝Array は emitArrayMethods 専用、を切り分ける）。その後 `[k:v]`/`[:]` リテラル（@Std/Syntax パーサ：先頭要素の後が `:` か否かで dict/array 判別・`[:]` は空 dict）＋`dict[k]`（Index・欠落 panic）/`dict[k]=v`（IndexSet）。`get -> Optional[V]` は Optional ambient 化後。
  現行のコンパイラ特権合成（`synthStructEq` 等＝Eq/Ord）は据え置き（Hash が dogfood の先駆け・Eq/Ord 移行は後）。
- **(b) M3**：パッケージ管理導入後に `@Std/Syntax` を in-tree から外部共有パッケージへ昇格（コンパイラもマクロも同一版に依存）。
- **小さな additive（任意）**：パターン/構築のフィールド名エラー行が近似（bind/MakeField 名が lower で再インターン＝原本 offset を持たない）。`BindAst`/`MakeFieldAst` に span を持たせ lower で原本 offset を維持すれば行が正確になる。

実装の段取り・実行系の具体は [metaprogramming-architecture.md](metaprogramming-architecture.md)。

## 並行・後続（renovate の残り・ロードマップ）

- **Phase B 残り（要 supervised）**：checks（10 箇所の `exprType`）を typed-AST に統合＝3 重 walker 一本化／pre-fill パスで codegen を完全 pure-read／`exprType` 再導出を駆逐。per-function clear で grounded をキャッシュできたので**テンプレート型は不要**になった。
- **Phase C＝名前 interning**（`spansEqual`/`rangeEquals` 多数を整数比較に・`kwSpan` 系も剥がれる）。**interning＝マップ＝`Dictionary` がツール**なので、**Dictionary が来てから（M2 後）やるのが得**（先にやると手書きハッシュ表になる）。
- **重い D（後日・本物の refactor）**：legacy 型 triple `(start,len,isArray)+ref` の ref 一本化／derive 合成 ~280 行が `Parser/Decl.pw`（＝メタプロ dogfood で置換されるので触らない）。
- **横断 additive**：Iterator 拡充（reduce/take/zip 等）・演算子トレイト全配線（Eq/Ord 以外・需要駆動）・循環回収（Ref グラフ限定サイクルコレクタ）・async tail＋spawn（実スレッド `JoinHandle[T]`）・`any P` 存在型。詳細は [provisional.md](provisional.md)。
- **既知のバグ＝free 関数のモジュール跨ぎ同名衝突**（要修正）：別モジュールに同名の private free 関数があると、同モジュール内の正しい呼び出しが「別モジュールの関数を import せず使用」エラーで誤検出される（例：`@Std/Syntax` に private `digitByte` を足すと本体の同名 `digitByte` 呼びが壊れた→`srcDigitByte` に改名して回避）。期待＝free 関数解決は **same-module 優先**、他モジュールは import 済み名のみ候補。現状は loaded 全モジュールの同名を拾い非 import なら error。一般ユーザーも別モジュールに同名 private 関数を置くと踏む独立バグ（メタプロ/A とは無関係）。

## 再利用資産・罠（git で拾いにくい知見）

- **型付き AST キャッシュ**（現アーキ）：`typeOf(c, id)`＝codegen の型読み口（旧 `exprType` 再導出の代替）。ノード型を `Comp` の **4 並列 scalar 配列**にキャッシュ（self-host は **struct 配列 IndexSet 非対応**ゆえ・`arr[i]=v` の scalar IndexSet は可）。**body emission のエントリ（`genFunc`/`genClosure`/`genAsyncFunc`）で `clearExprTyCache`**＝env（Self/型 args/インスタンス）は 1 body の emission 中だけ一定なので、grounded 型をその間だけキャッシュ・関数境界で破棄（全文脈で安全・filled-id リストのみ reset で O(fills)）。`exprType` は今や `typeOf` 初回 touch／自身の再帰／pre-codegen checks からのみ到達。
- **共有パーサ→arena lower（A）**：共有 @Std/Syntax パーサが値ツリー（`TopItemAst`/`DeclAst`/`ImplAst`/`TraitAst`/`ExternAst`/`ImportAst`/`DirectiveAst`／式文は `ExprAst`/`StmtAst`…）を返し、`Codegen/Lower.pw` が arena（`Expr`/`Stmt`/`Func`/`StructDef`…）へ lower。**名前の offset 規律**＝`moduleOf` に効く名前（free fn 宣言名・call 名・extern fn 名・import/export 名）は**原本 offset 維持**（再インターン不可）、それ以外（struct/enum/field/型名・impl 系全部）は `internBytes` で再インターン（codegen は text 出力ゆえ byte 同一・moduleOf 不参加）。`lowerType` が `recordArrayElem` で `arrayElems` 種まき（旧パーサの codegen 仕事は lower 側へ）。**罠**：パース駆動ローディングで `c.bytes` はファイル源と再インターン名が交互配置になる（各ファイルを追記直後に lower）。writeSpan は text 出力・moduleOf は per-file レンジ参照ゆえ不動点・可視性とも安全（offset 値そのものに依存するロジックは無い）。
- **再帰値型 box**：`markBoxedFields`（`Mono.pw`・`Comp.boxedFields`＝field の `nameStart` キー）が循環を閉じる**ユーザー側フィールド**を box（`Array`/`RawBuffer`/`Ref`/`WeakRef` は cut・`Optional`/`Result` は透過して引数を辿る＝Optional 自体は box せず hardcoded `.data.Some.v` を温存）。`T*`・構築 `genBoxCell`（`curRetTy=fd.ty` で nested JSX を mangle 推論）・読み deref コピー・書き fresh box に repoint（共有セル不変＝値意味論）。box＝`plew_arc_alloc` rc セル・copy/share は retain・release は rc→0 で pointee 再帰 release＋free。**ARC 解放は配線済**だが残リークは print/String の既存ギャップのみ（box 由来 0）。終端なし循環 `struct A{a:A}` は構築不能だが通る（loud reject は将来）。
- **値意味論 ARC の在処**：concrete＝`emitFieldAction`（struct/enum 共有・unique-deinit 込み）、mono＝`emitMonoFieldAction`/`emitMonoModeDef`。**heap フィールド種を足すのはこの 2 dispatcher**。need 判定は `fieldNeedsCopy/Release`・`typeInfoNeedsCopy/Release`。
- **Iterator/generic 機構**：method-level 型パラメータ（`FnInst.recvInstRef`・`registerMethodInst`・mangle suffix は method-own tail のみ）・**demand-driven 単相化**（`providedRetReachable`＝`FilterIter[FilterIter…]` の無限型族を到達時のみ発行）・Self/Item 解決（`curSelfRef`/`curItemRef`＋`resolveTy`）・構造的型推論（`unifyTypeParam`）・impl レベル `where`（funcBounds へ畳む）。**罠**：型パラメータ名 vs 具体型名のグローバル衝突（ユーザー struct `B` と `MapIter[…,B]` の `B`）→ `isTypeParamName` は宣言済 struct/enum 名を具体型扱い。
- **演算子 opcode**：`op` フィールドは `kindCode(Kind)` の整数。`Ops.pw` の `opAdd()..opCoalesce()`（`kindCode(<Kind.X/>)`）が**単一の symbolic 源**（magic 数を codegen に漏らさない）。
- **gen モード（`plew gen`・M0）**：`plewc --gen <file>`＝通常コンパイルの変種。`Comp.genMode`/`genMainIdx`、合成は `Codegen/Gen.pw`（`synthGenMain`＝`@[Name]` ごとに `write(s: <Name/>.deriveFromSource(source:"",start:0,end:0))` を arena AST で組む・`isBuiltinDerive` で Eq/Ord 除外）。driver（`_.pw`）で **①argv `--gen` 検出→entry を argv[2] へ ②`@Std/Io` 強制ロード（harness の `write` 用）③ローダ auto-part 抑制 ④checks 後に `synthGenMain`（import hygiene を回避）⑤body emission で user `main` を skip**。ローダ＝パース木の `Directive` ノードで `@[...]` を検出し `<Foo>.gen.pw`（存在時のみ）を同一モジュール part に enqueue。**罠**：`Expr.Str` は span が引用符込み前提（codegen が `start+1`/`len-2`）＝0 長 span は U64 アンダーフロー panic→合成側で実 `""`（2 バイト）を intern して指す。gen 中は user 自身の `main` が生成物を使っても OK（skip されるので未定義参照でも落ちない）＝「同一モジュール derive」が自然成立。auto-part の loud-fail（gen 未実行で `.gen.pw` 欠落）は directive→マクロ分類が要るので将来。

## ビルド・テスト・機能追加手順

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust 不要）。`./bootstrap.sh --reseed` で種更新（→ `compiler/plewc.seed.c` を commit）。
- **メタプロ生成**：`./plew-gen.sh <file.pw> …`＝`plewc --gen <file> | clang | run > <file>.gen.pw`。`@[...]` 付きファイルに対し derive マクロを走らせ生成 part を吐く（コミットする・通常ビルドが auto-part）。
- **テスト**：`./test.sh`＝`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/part/`（複数ファイル）＋`tests/reject/*.pw`（plewc 非ゼロ＝受理の健全性）＋`tests/panic/*.pw`（compile+link 成功・実行は非ゼロ＋`.panic` stderr 部分一致）＋`tests/gen/*/`（`App.pw`＝マクロ＋`@[...]`／hermetic に gen→auto-part→実行→`App.out` 照合・`.gen.pw` は毎回 $TMP で再生成）＋`tests/genreject/`（`plewc --gen` が reject すべき入力）＋不動点。メモリは `ASAN=1 ./test.sh`。**⚠ macOS の ASan は leak 非対応**（`detect_leaks` 不可）＝UAF/二重free は ASan、リークは `MallocStackLogging=1 leaks --atExit -- <bin>` で検証。
- **機能追加＝ADD→reseed→USE**：新機能を plewc.pw の**ソースで使う**には ①`compiler/src/`（または `compiler/std/`）に足す（ADD）→ ②`--reseed` で種更新→ ③ソースで使う（USE）。「ソースが使う機能は常にひとつ前のコンパイラがサポート済み」を守れば不動点は壊れない。**codegen 出力変化・AST フィールド追加・新 preamble 行は reseed 2 回**、**codegen 出力を変えない検査追加は reseed 1 回**。
- **AST フィールド追加のコツ＝デフォルト値**：`val isPub: Bool = false` とデフォルトを付けると既存の構築点が省略でそのまま通る＝多数の構築点を改修せず済む（`<Comp .../>` リテラルも省略可）。
- **⚠ 落とし穴＝コンパイラは `@Std/Io`→`@Std/Core`／`@Std/Syntax`／`Prelude`（全プログラム自動ロード）を import** するので、これらも「コンパイラ自身がコンパイルするソース」。種がまだ受理しない構文/機能を足すと bootstrap が即壊れる＝**機能を先に種へ焼いてから std で使う**（ADD→reseed→USE）。表現スワップ等の大変更は seam（intrinsic 境界）で担保（→ array-struct-plan.md）。

## 運用メモ

- 動作する区切りで**記述的 git タグ**。コミットメッセージは英語＋`Co-Authored-By`。GPG 署名（`--no-gpg-sign` を使わない・たまに pinentry タイムアウト＝再実行で通る・コミットメッセージにバッククォートを書くと zsh がコマンド置換するので避ける／`-F` でファイル渡し）。
- 不要になった実装は削除し、必要なら git tag から復旧（例：`git checkout stage0-final -- bootstrap`）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。
- C 予約語（`double` 等）と衝突する Plew 識別子は生成 C が壊れる＝名前マングリング未実装（[provisional.md](provisional.md)）。
- LLVM 化は当面しない＝意味論が揃ってから並行バックエンドとして追加（C は捨てない）。
