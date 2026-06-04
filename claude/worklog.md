# 作業ログ

> 現在地・次の一歩・運用メモだけを置く。完了した「やった」は git 履歴へ（記述的タグで辿れる）。「なぜ」は [design-decisions.md](design-decisions.md)、「パイプライン設計」は [architecture.md](architecture.md)、「spec からの意図的剥離・暫定の仮決め」は [provisional.md](provisional.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で全パートを綴じ込む 1 モジュール＝`Loader`・`Lexer`・`Ast`・`Parser/`〔Expr/Stmt/Decl〕・`Codegen/`〔Emit/Resolve/Ops/Check/Expr/Stmt/Decl/Mono/Array/Async〕）。自分自身を不動点までコンパイルする。意味論の hidden-meaning（整数幅・match 網羅・ラベル・診断・受理の健全性・値意味論/CoW・`unique`/`deinit`/move・generics・トレイト step1＋Eq/Ord＋derive・クロージャ）は概ね解消済み。**残る剥離・暫定は [provisional.md](provisional.md) が正典**。

- ✅ **イベントループ（async/await）段階 1-3**（spec/14・方式 B＝stackless ステートマシン・native-C・`Codegen/Async.pw`）。`async fn`（free）/`await`/`Promise[T]`/`sleep`（`@Std/Async`）が動く（if/while/enum-match 内・複数中断点可）。**残 tail（additive・クリーン reject）**：await-in-`for`・struct-destructure match・式中 await・async メソッド・generic async・String/struct 値の `Promise`・frame/Promise の ARC（当面リーク）。方式の根拠は [design-decisions.md](design-decisions.md)「async fn のローワリング」。
- ✅ **コアライブラリ境界＝整理済**：`@Std/Io`・`Process`・`Async` は実 `.pw` の `extern "plew-intrinsic"` 宣言（呼びは `plew_<name>`）。lang item 型は `extern "plew-intrinsic" { struct I32 … }` で Core が宣言＝所有（Swift モデル・コヒーレンス是正）。`Format` トレイト＋全整数/Bool の impl・**`print` も純 Plew**（`@Std/Io` の `print[T](value~: T) where T: Format`・裸 `print(42)` はサフィックス必須＝既定型なし）。これを通すため generic free fn の monomorphization をハードニング（scan 時 exprType を codegen 同等に）。機構は [design-decisions.md](design-decisions.md)「コアライブラリの境界」。
- ✅ **Array メソッドの Plew 化（あるべき姿 Level 2 への道）**：①**生メモリ床 `RawBuffer[T]`**（`Ref` 同様 C `Tc*`＋`[cap][rc]` ヘッダ・intrinsic `rawAlloc/Load/Store/Cap/IsUnique`・型非依存ランタイム `plew_rawbuf_*`・`tests/run/raw_buffer`）。②**Array generic メソッド**（`impl[T] Array[T] { fn … }` が要素型ごと mono＋名前 dispatch・`emitArrayMethods`・`tests/run/array_methods`）。③**プレリュード `std/Prelude.pw`**（loader が全プログラムに自動ロード＝ambient な Array メソッドの置き場・import 不要で `xs.get/set/append`・`tests/run/prelude_array`）。④**`.append` を純 Plew 化**（`impl Array { append }` へ dispatch・push ハードコードは不在時 fallback のみ）。

## ✅ 完了＝Array を `struct Array[T] { data: RawBuffer[T]; pub(get) mut val count: U64 }` に（branch `array-struct`）

**あるべき姿 達成＝Array の表現が Plew struct に**（Swift モデル・`PlewArray_<E>` 撤去・C typedef は StructDef 由来）。経緯・設計の核心は [array-struct-plan.md](array-struct-plan.md)。**設計の核心＝段階 flip**（bootstrap seam＝intrinsic 境界）。**(A) 返り値文脈推論は不要だった**（リテラルはコンパイラ lowering で E 既知）→ 別 additive に降格。

進捗（すべて完了）：
- ✅ **step 1＝RawBuffer の値意味論**（struct フィールドの RawBuffer は share-on-bind／deep copy は owner の CoW メソッドで lazy）。
- ✅ **core 検証**（`tests/run/raw_struct_cow`）：`struct{data:RawBuffer; count}＋push(grow+CoW)＋at` が end-to-end 正しい。
- ✅ **`pub(get)` フィールド構文の解析**（consume-and-record・visibility 未強制ゆえ観測同一・I2 で強制）。
- ✅ **A0＝dormant ガード**（`isGenericInst(Array)=false` 固定＝struct 定義があってもビルトイン扱い・二重生成回避）。
- ✅ **Flip1a＝ビルトイン Array を RawBuffer 床へ**（tag `array-rawbuffer-floor`）：`PlewArray_<E>` の C 表現を `{data; len; cap; rc}`→`{data; len}`（cap/rc はバッファヘッダ）・ランタイムを `plew_rawbuf_*` で再実装（要素別 deep copy/release 維持）・struct array-field share も配列ランタイム経由・**`String.bytes` は独立 owned `Array[U8]` をコピー生成**（借用ビュー廃止＝値意味論が要求）。Array はまだビルトイン＝これが struct `Array[T]{data:RawBuffer; count}` と同じ C 形状。208 緑（ASan 含む）＋不動点。
- ✅ **Flip1b＝Array を Plew struct へ昇格**（tag `array-plew-struct`）：Prelude の `struct Array[T] { data: RawBuffer[T]; pub(get) mut val count: U64 }` が C typedef を供給（`struct Array_E { E* data; uint64_t count; }`＝emitMonoForward/emitMonoStruct 由来・hand-written typedef 廃止）。A0 ガード除去で `Array[E]` が genInst 化。名前を `PlewArray_E`/`.len`→`Array_E`/`.count` に統一。**配列を値で持つ nominal struct のため Array genInst body を nominal body より前に出力**（ポインタベースゆえ前方宣言で足る）。封じ込めのため**リテラル/添字/for/値意味論/メソッドは kind-3 経路のまま**（exprType は配列ローカル/配列戻り値を genInst でなく kind-3 と報告）。`Array[U8]` のみ hand-written 維持（ファイルパス/String.bytes が無条件に要る・narrow guard で genInst 外）。208 緑（ASan 含む）＋不動点。
- ✅ **あるべき姿 達成**：append/get/set は**既に純 Plew メソッド**（Prelude の `impl[T] Array[T]`）で、floor＝`arrayPush/Get/Set/Len`（Swift の Builtin 相当・deep-copy-aware ランタイムへの正当な境界）を呼ぶ。Swift の Array と同型＝「Plew struct ＋ floor 上の薄い純 Plew メソッド」。**Flip2（methods の raw floor 直接化）は不要**：配列の値意味論（CoW make-unique の要素別 deep copy/release）は型を知るコンパイラ生成ランタイムが必須で、raw floor（型消去・shallow）では `Array[TypeRef]` 等の struct 要素が別名化バグになる。floor intrinsics がその境界を正しく担う。

残ギャップ（別途・additive）：将来 Dictionary/Set 向けに **コレクション値意味論の一般化**（要素別 deep copy/release を `RawBuffer` 上の任意コレクションで再利用可能に）。今は配列専用ランタイム（`Array_E_copy/share/release/unique`）。

## ロードマップ（残りの大物・前向きのみ）

1. ✅ **Array struct 化＝完了**（上記・`array-struct`→main）。次の収穫＝**コレクション値意味論の一般化**（配列専用ランタイムを `RawBuffer` 上の任意コレクションへ＝Dictionary/Set の前提）。
2. 🔲 **関連型＋Iterator/Iterable**（`for` 脱糖の正式化・提供メソッド map/filter…）。署名は core-lib。
3. 🔲 **Hash/Hasher → Dictionary（`[k:v]` lang item）/Set**（要：コレクション値意味論の一般化）。
4. 🔲 **イベントループ tail＋spawn**（実スレッド・`JoinHandle[T]`・closure 残ギャップ）。
5. 🔲 **`any P` 存在型**（型消去・動的ディスパッチ・トレイトの最後）。
6. 🔲 **メタプログラミング**（`Derive`・コード生成・spec 上も最後）。

横断 additive：演算子トレイト全配線（Eq/Ord 以外・需要駆動）・I2（import の with ゲート＝可視性検査・今は全フラット）・循環回収（Ref グラフ限定サイクルコレクタ）。詳細は [provisional.md](provisional.md)。

## ビルド・テスト・機能追加手順

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust 不要）。`./bootstrap.sh --reseed` で種更新（→ `compiler/plewc.seed.c` を commit）。
- **テスト**：`./test.sh`＝`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/part/`（複数ファイル）＋`tests/reject/*.pw`（plewc 非ゼロ＝受理の健全性）＋`tests/panic/*.pw`（compile+link 成功・実行は非ゼロ＋`.panic` stderr 部分一致）＋不動点。メモリは `ASAN=1 ./test.sh` ＋ ASan ビルドで自己コンパイル（UAF/double-free）。
- **機能追加＝ADD→reseed→USE**：新機能を plewc.pw の**ソースで使う**には ①`compiler/src/` の codegen に足す（ADD）→ ②`--reseed` で種更新→ ③ソースで使う（USE）。「ソースが使う機能は常にひとつ前のコンパイラがサポート済み」を守れば不動点は壊れない。**新 preamble 行・codegen 出力変化・AST フィールド追加は reseed 2 回**（1 回目で挙動を種に焼き、2 回目で一致）。
- **⚠ 落とし穴＝コンパイラは `@Std/Io`→`@Std/Core` を import**するので、Core/Io/Process/**Prelude**（全プログラム自動ロード）も「コンパイラ自身がコンパイルするソース」。**そこに「種がまだ受理しない構文/機能」を足すと bootstrap が即壊れる**。回避＝**機能を先に種へ焼いてから Core/Prelude で使う**（コンパイラ側の許可だけ先に `--reseed`→中身を足して `--reseed`）。`--reseed` も古い種で plewc0 を作るので順を破ると詰む。

## 運用メモ

- 動作する区切りで**記述的 git タグ**（バージョン番号はまだ）。コミットメッセージは英語＋`Co-Authored-By`。GPG 署名（`--no-gpg-sign` を使わない）。
- **不要になった実装は削除し、必要なら git tag から復旧**（例：`git checkout stage0-final -- bootstrap`）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。
- C 予約語（`double` 等）と衝突する Plew 識別子は生成 C が壊れる＝名前マングリング未実装（コンパイラ自身は回避・ユーザーコードで顕在化＝[provisional.md](provisional.md)）。
- LLVM 化は当面しない＝意味論が揃ってから並行バックエンドとして追加（C は捨てない）。
