# 作業ログ

> 現在地・次の一歩・運用メモ・再利用資産だけを置く。完了した「やった」は git（記述的タグ）へ。「なぜ・却下案」は [design-decisions.md](design-decisions.md)、パイプライン設計は [architecture.md](architecture.md)、spec からの意図的剥離・暫定は [provisional.md](provisional.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で全パートを綴じる 1 モジュール＝`Loader`・`Lexer`・`Ast`・`Parser/`〔Expr/Stmt/Decl〕・`Codegen/`〔Emit/Resolve/Ops/Check/Expr/Stmt/Decl/Mono/Array/Async〕）。自分自身を不動点までコンパイル。hidden-meaning（整数幅・match 網羅・ラベル・受理の健全性・値意味論/CoW・`unique`/`deinit`/move・generics・トレイト＋Eq/Ord＋derive＋関連型・クロージャ）は概ね解消。**残る剥離・暫定は [provisional.md](provisional.md) が正典**。

完了した大物（詳細は git・記述的タグ）：async/await 段階 1-3（stackless SM）・コアライブラリ境界（`@Std` の `extern "plew-intrinsic"`）・**Array＝`RawBuffer` 床の Plew struct**（[array-struct-plan.md](array-struct-plan.md)）・可視性完全強制・**Iterator/Iterable＋lazy map/filter**・**再帰値型 auto-boxing＋ARC**・**コンパイラ renovate Phase A**（ARC 1 本化・Op enum・expect）・**Phase B B0-B2**（型付き AST キャッシュ）・**D quick-wins**（Loader 掃除・expect 仕上げ）。renovate vs rewrite の判断・負債の地図は [architecture.md](architecture.md)「負債監査の結論」、言語設計の根拠は [design-decisions.md](design-decisions.md)、再利用機構は本書末尾「再利用資産・罠」。

## 次の一歩＝メタプログラミング M1（M0 は済）

**入力モデル確定＝AST 入力**（当初の TokenStream から変更）。正典＝[spec/04-execution/16-metaprogramming.md](../spec/04-execution/16-metaprogramming.md)、実行系の段取り＝[metaprogramming-architecture.md](metaprogramming-architecture.md)。要点：

- **`Derive` トレイト＝要求 `derive(input: AST) -> String`（ユーザー）＋提供 `deriveFromSource(source, span)`**（構文ライブラリが String→AST 変換＋委譲＝中間 dispatcher 層は不要）。
- **ランナー（`plew gen`）＝String↔String の版非依存な機械**：`@[Name(args)]` ごとにハーネス（`<Name args/>.deriveFromSource(...)` を `write` する `main`）を合成→compile→別プロセス run→stdout を `<Foo>.gen.pw` へ。**版固定はハーネスがリンクする固定 `@Std/Syntax` で自然成立**（ランナーは AST 型に触れない）。
- **構文ライブラリ＝当面 `@Std/Syntax`（in-tree）・最終形は外部共有パッケージ**（コンパイラもマクロも同一版に依存＝Rust の 2 パーサ/AST 版違い問題を回避）。生トークンは将来 escape hatch（関数形/DSL マクロを入れる時のみ）。
- 出力モデル：`<Foo>.gen.pw` コミット・原本不変・add-only、`@[...]` でローダ自動 part（gen 中は抑制）。

**M0＝済**（tag `metaprogramming-m0`）。`plewc --gen <file>` モード＋`@Std/Syntax`（最小）＋ローダ auto-part＋`plew-gen.sh`＋`tests/gen/`。自明マクロ（固定文字列を返す）が `@[Greet]`→harness→`Greet.deriveFromSource`→`App.gen.pw`→通常ビルドで auto-part→生成関数実行、まで端から端まで貫通。実装メモは末尾「再利用資産・罠」の gen 項。

- **M1**（次）＝`@Std/Syntax` の本実装＝**理想形＝構文層を唯一の真実に**（lexer＋完全値ツリー AST＋parser＋unparser・**構文 vs 意味で切る**・コンパイラとマクロが**同一の 1 AST**を共有〔syn/rustc drift を構造的に回避〕＝詳細は [metaprogramming-architecture.md](metaprogramming-architecture.md)「理想形（最終状態）」）。具体物は `DeclAst`/`TypeExpr`（String 名・再帰・全ノード原本座標 span・struct/enum/fn 網羅）と `parseItem`（base offset でスライスを原本座標 parse・stub を実装に）。M0 は `source: ""` 固定なので**対象項の実ソース slice をハーネスへ渡す**（decl span 捕捉＝directive `@`〜閉じ `}`）のも M1。**未決＝射程**：理想は式・文まで構文層まるごと共有だが、初手をどこまで（宣言レイヤ先行か一気か）／**コンパイラのレクサを `@Std/Syntax` に移して本体も import する一本化**（レクサは Comp 非依存で抽出可）は確定方向・パーサ/AST 全面共有は重い D の前倒しで射程判断中。**Dictionary は後**（理想ツリーは String 名で自己完結＝インターン化〔Phase C・Dictionary が道具〕は直交した後乗せ最適化・先行不要）。
- **M2**＝dogfood（特権 Eq/Ord をマクロ化→`@[Hash]`→`Dictionary`）→ **M3** パッケージ管理後に外部切り出し。

## 並行・後続（renovate の残り・ロードマップ）

- **Phase B 残り（要 supervised）**：checks（10 箇所の `exprType`）を typed-AST に統合＝3 重 walker 一本化／pre-fill パスで codegen を完全 pure-read／`exprType` 再導出を駆逐。per-function clear で grounded をキャッシュできたので**テンプレート型は不要**になった。
- **Phase C＝名前 interning**（`spansEqual`/`rangeEquals` 259 箇所を整数比較に・`kwSpan` 系も剥がれる）。**interning＝マップ＝`Dictionary` がツール**なので、**Dictionary が来てから（M2 後）やるのが得**（先にやると手書きハッシュ表になる）。
- **重い D（後日・本物の refactor）**：legacy 型 triple `(start,len,isArray)+ref` の ref 一本化／パーサが codegen 仕事（`appendMangleSpan` でソース buffer に mangle 書込み・`recordArrayElem` で `arrayElems` 種まき）を post-parse へ／derive 合成 ~280 行がパーサ内（＝メタプロ dogfood で置換されるので触らない）。
- **deferred＝分割コンパイル**（Loader のソース連結モデル＋`*Start/*Len` span 規約。renovation が届かない唯一・分割/incremental が要るまで後回し）。
- **横断 additive**：Iterator 拡充（reduce/take/zip 等）・演算子トレイト全配線（Eq/Ord 以外・需要駆動）・循環回収（Ref グラフ限定サイクルコレクタ）・async tail＋spawn（実スレッド `JoinHandle[T]`）・`any P` 存在型。詳細は [provisional.md](provisional.md)。

## 再利用資産・罠（git で拾いにくい知見）

- **型付き AST キャッシュ**（現アーキ）：`typeOf(c, id)`＝codegen の型読み口（旧 `exprType` 再導出の代替）。ノード型を `Comp` の **4 並列 scalar 配列**にキャッシュ（self-host は **struct 配列 IndexSet 非対応**ゆえ・`arr[i]=v` の scalar IndexSet は可）。**body emission のエントリ（`genFunc`/`genClosure`/`genAsyncFunc`）で `clearExprTyCache`**＝env（Self/型 args/インスタンス）は 1 body の emission 中だけ一定なので、grounded 型をその間だけキャッシュ・関数境界で破棄（全文脈で安全・filled-id リストのみ reset で O(fills)）。`exprType` は今や `typeOf` 初回 touch／自身の再帰／pre-codegen checks からのみ到達。
- **再帰値型 box**：`markBoxedFields`（`Mono.pw`・`Comp.boxedFields`＝field の `nameStart` キー）が循環を閉じる**ユーザー側フィールド**を box（`Array`/`RawBuffer`/`Ref`/`WeakRef` は cut・`Optional`/`Result` は透過して引数を辿る＝Optional 自体は box せず hardcoded `.data.Some.v` を温存）。`T*`・構築 `genBoxCell`（`curRetTy=fd.ty` で nested JSX を mangle 推論）・読み deref コピー・書き fresh box に repoint（共有セル不変＝値意味論）。box＝`plew_arc_alloc` rc セル・copy/share は retain・release は rc→0 で pointee 再帰 release＋free。**ARC 解放は配線済**だが残リークは print/String の既存ギャップのみ（box 由来 0）。終端なし循環 `struct A{a:A}` は構築不能だが通る（loud reject は将来）。
- **値意味論 ARC の在処**：concrete＝`emitFieldAction`（struct/enum 共有・unique-deinit 込み）、mono＝`emitMonoFieldAction`/`emitMonoModeDef`。**heap フィールド種を足すのはこの 2 dispatcher**。need 判定は `fieldNeedsCopy/Release`・`typeInfoNeedsCopy/Release`。
- **Iterator/generic 機構**：method-level 型パラメータ（`FnInst.recvInstRef`・`registerMethodInst`・mangle suffix は method-own tail のみ）・**demand-driven 単相化**（`providedRetReachable`＝`FilterIter[FilterIter…]` の無限型族を到達時のみ発行）・Self/Item 解決（`curSelfRef`/`curItemRef`＋`resolveTy`）・構造的型推論（`unifyTypeParam`）・impl レベル `where`（funcBounds へ畳む）。**罠**：型パラメータ名 vs 具体型名のグローバル衝突（ユーザー struct `B` と `MapIter[…,B]` の `B`）→ `isTypeParamName` は宣言済 struct/enum 名を具体型扱い。
- **演算子 opcode**：`op` フィールドは `kindCode(Kind)` の整数。`Ops.pw` の `opAdd()..opCoalesce()`（`kindCode(<Kind.X/>)`）が**単一の symbolic 源**（magic 数を codegen に漏らさない）。
- **gen モード（`plew gen`・M0）**：`plewc --gen <file>`＝通常コンパイルの変種。`Comp.genMode`/`genMainIdx`、合成は `Codegen/Gen.pw`（`synthGenMain`＝`@[Name]` ごとに `write(s: <Name/>.deriveFromSource(source:"",start:0,end:0))` を arena AST で組む・`isBuiltinDerive` で Eq/Ord 除外）。driver（`_.pw`）で **①argv `--gen` 検出→entry を argv[2] へ ②`@Std/Io` 強制ロード（harness の `write` 用）③ローダ auto-part 抑制 ④checks 後に `synthGenMain`（import hygiene を回避）⑤body emission で user `main` を skip**。ローダ＝`hasDirective`（`@`+`[` 隣接トークン）で `@[...]` を検出し `<Foo>.gen.pw`（存在時のみ）を同一モジュール part に enqueue。**罠**：`Expr.Str` は span が引用符込み前提（codegen が `start+1`/`len-2`）＝0 長 span は U64 アンダーフロー panic→合成側で実 `""`（2 バイト）を intern して指す。gen 中は user 自身の `main` が生成物を使っても OK（skip されるので未定義参照でも落ちない）＝「同一モジュール derive」が自然成立。auto-part の loud-fail（gen 未実行で `.gen.pw` 欠落）は directive→マクロ分類が要るので M1 以降。

## ビルド・テスト・機能追加手順

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust 不要）。`./bootstrap.sh --reseed` で種更新（→ `compiler/plewc.seed.c` を commit）。
- **メタプロ生成**：`./plew-gen.sh <file.pw> …`＝`plewc --gen <file> | clang | run > <file>.gen.pw`。`@[...]` 付きファイルに対し derive マクロを走らせ生成 part を吐く（コミットする・通常ビルドが auto-part）。
- **テスト**：`./test.sh`＝`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/part/`（複数ファイル）＋`tests/reject/*.pw`（plewc 非ゼロ＝受理の健全性）＋`tests/panic/*.pw`（compile+link 成功・実行は非ゼロ＋`.panic` stderr 部分一致）＋`tests/gen/*/`（`App.pw`＝マクロ＋`@[...]`／hermetic に gen→auto-part→実行→`App.out` 照合・`.gen.pw` は毎回 $TMP で再生成）＋不動点。メモリは `ASAN=1 ./test.sh`。**⚠ macOS の ASan は leak 非対応**（`detect_leaks` 不可）＝UAF/二重free は ASan、リークは `MallocStackLogging=1 leaks --atExit -- <bin>` で検証。
- **機能追加＝ADD→reseed→USE**：新機能を plewc.pw の**ソースで使う**には ①`compiler/src/` の codegen に足す（ADD）→ ②`--reseed` で種更新→ ③ソースで使う（USE）。「ソースが使う機能は常にひとつ前のコンパイラがサポート済み」を守れば不動点は壊れない。**codegen 出力変化・AST フィールド追加・新 preamble 行は reseed 2 回**、**codegen 出力を変えない検査追加は reseed 1 回**。
- **AST フィールド追加のコツ＝デフォルト値**：`val isPub: Bool = false` とデフォルトを付けると既存の構築点が省略でそのまま通る＝多数の構築点を改修せず済む（`<Comp .../>` リテラルも省略可）。
- **⚠ 落とし穴＝コンパイラは `@Std/Io`→`@Std/Core` を import** するので、Core/Io/Process/**Prelude**（全プログラム自動ロード）も「コンパイラ自身がコンパイルするソース」。種がまだ受理しない構文/機能を足すと bootstrap が即壊れる＝**機能を先に種へ焼いてから Core/Prelude で使う**（ADD→reseed→USE）。表現スワップ等の大変更は seam（intrinsic 境界）で担保（→ array-struct-plan.md）。

## 運用メモ

- 動作する区切りで**記述的 git タグ**。コミットメッセージは英語＋`Co-Authored-By`。GPG 署名（`--no-gpg-sign` を使わない・たまに pinentry タイムアウト＝再実行で通る）。
- 不要になった実装は削除し、必要なら git tag から復旧（例：`git checkout stage0-final -- bootstrap`）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。
- C 予約語（`double` 等）と衝突する Plew 識別子は生成 C が壊れる＝名前マングリング未実装（[provisional.md](provisional.md)）。
- LLVM 化は当面しない＝意味論が揃ってから並行バックエンドとして追加（C は捨てない）。
