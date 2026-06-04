# 作業ログ

> 現在地・次の一歩・運用メモだけを置く。完了した「やった」は git 履歴へ（記述的タグで辿れる）。「なぜ」は [design-decisions.md](design-decisions.md)、「パイプライン設計」は [architecture.md](architecture.md)、「spec からの意図的剥離・暫定の仮決め」は [provisional.md](provisional.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で全パートを綴じ込む 1 モジュール＝`Loader`・`Lexer`・`Ast`・`Parser/`〔Expr/Stmt/Decl〕・`Codegen/`〔Emit/Resolve/Ops/Check/Expr/Stmt/Decl/Mono/Array〕・part はサブディレクトリ可）。自分自身を不動点までコンパイルする。

意味論の hidden-meaning（整数幅・match 網羅・ラベル・診断・受理の健全性チェック・値意味論/CoW・`unique`/`deinit`/move・generics・トレイト step 1＋Eq/Ord＋derive・クロージャ）は概ね解消済み。**残っている剥離（実装済/未実装の現況）はすべて [provisional.md](provisional.md) が正典**（このログには個別バグ/完了項目を溜めない）。

**イベントループ（async/await）＝段階 1・2・3（match まで）実装済**（spec/14・方式 B＝stackless ステートマシン・native-C）。`async fn`（free）/`await`/`Promise[T]`/`sleep`（`@Std/Async`）が動く：frame 構造体＋resume＋entry へ下ろし、await で suspend/resume、イベントループ（ready キュー＋仮想時計タイマ）を drain。**await は if/while/（enum）match の中でも可・複数中断点可**（全ローカル＋match バインドを frame に hoist〔monotonic suffix `name_sN` で兄弟アーム衝突回避〕＋goto ディスパッチで再入）。entry は `__self` をローカル退避してから resume（同期完了で frame が free されても UAF にならない）。実装は `Codegen/Async.pw`。テスト＝`tests/run/async_{basic,order,control,match}`。**残る async の tail（additive・いずれもクリーンに reject）**：await-in-`for`（誘導変数 `__fa`/`__fi`/loop-var の frame 化が要る・while で代替可）・struct-destructure match・式中 await（`await a + 1`＝await を文へ持ち上げる正規化）・async メソッド（self の frame 化）・generic async・String/struct を値に持つ `Promise`（値スロットは当面 `long long`）・frame/`__self`/Promise の ARC（当面リーク）。次の自然な一歩は spawn（実スレッド）か await-in-for。

## 次の一歩＝イベントループ（async/await/Promise・段階 3 の tail と spawn）

**方式は B＝stackless ステートマシン**（Node/V8 と同じ・colored async）に確定。**native-C 先行**で意味論（suspend/resume・drain 順・ARC across await）を固め、その後 WASM（Asyncify/JSPI）。**A＝スタックフルは却下**（Node を範とすると終着点が B・A は async fn ローワリング〔難所〕を作り直す中継ぎになる）。根拠・却下案は [design-decisions.md](design-decisions.md)「async fn のローワリング」。

### C ローワリング設計（確定・実装中）

`async fn f(p…) -> Promise[T]` を **3 つの C 実体**へ下ろす（goto ベース stackless コルーチン＝protothread 流）：
1. **frame 構造体** `__af_<sel>`：`int __state` ＋ awaiting 中の sub-promise `PlewPromise* __sub` ＋ 自分が返す `PlewPromise* __self` ＋ **全パラメータ＋全ローカル**（await を跨ぐ値の退避ゆえ live 解析せず一律 hoist）。
2. **resume 関数** `void __af_<sel>_resume(void* __fp)`：先頭で `switch(__f->__state){case 0:break; case N: goto __L<N>; …}`。本体を素直に emit し、await 点だけ suspend/resume に展開。
3. **entry 関数** `PlewPromise* <sel>(p…)`：frame を `plew_arc_alloc`、state=0・params コピー・`__self=plew_promise_new()`、resume を 1 回呼び、`__self` を返す。

**ローカル参照の振り向け**：`c.curAsync` フラグ＋`writeLocalCName` を async 時に `__f->name` へ（1 箇所で読み書きの大半を回収）。宣言サイト（Let/for-var/binds）は async 時 `T name = init` を `__f->name = init`（型前置なし＝field は frame で宣言済み）に切替。

**await の制限（段階 1-2）**：await は**文頭位置限定**＝`val x = await e`／`await e`（破棄）／`return await e`。式中 await（`await a + 1`）は段階 3+ additive（reject）。await 展開：
```
__f->__sub = (e の Promise);  __f->__state = N;
if (!__f->__sub->done) { __f->__sub->k=resume; __f->__sub->kframe=__f; return; }
__L<N>: ;  __f->x = __f->__sub->value;   // val x = await e のとき
```
switch 先頭ディスパッチが `goto __L<N>` で再入。全ローカル hoist ゆえ if/while/for/match の中へ goto しても宣言跨ぎが無く C 的に安全＝**段階 3（await-in-loop/branch/match）も同じ goto 機構で自然に伸びる**。

**ランタイム（preamble）**：`PlewPromise{int done; long long value; PlewResumeFn k; void* kframe;}`（値スロットは当面 `long long`＝()／整数／Bool。String/struct 値の Promise は additive）＋ready キュー＋タイマ（deadline 配列）＋`plew_loop_run()`（ready→タイマ drain）＋`plew_sleep(ms)->PlewPromise*`。`async fn main` の `int main` は frame 確保→resume 1 回→`plew_loop_run()`→return 0。

**段階**：1. 言語表面＋単一中断点（着手）→ 2. ループ＋`async fn main`＋`sleep`＝最小マイルストン（遅延 2 タスクが期日順に発火）→ 3. await-in-loop/branch/match・複数中断点・式中 await。
4（当面スキップ）. `spawn`＝実スレッド（pthread・境界で CoW eager 実体化・`Ref` 不可）・`JoinHandle[T]`/`join()->Promise[T]`。closure 残ギャップ（`mut val` 非スカラー箱化・参照キャプチャ閉包の `local` マーク）回収。

## ロードマップ（残りの大物・前向きのみ）

1. 🔄 **イベントループ**（上記・最大・着手対象）。
2. 🔲 **関連型＋Iterator/Iterable**（`for` 脱糖の正式化・`where T: Iterator` の `it.next()->Optional[T.Item]`・提供メソッド map/filter…）。署名は core-lib。
3. 🔲 **Hash/Hasher → Dictionary（`[k:v]` lang item）/Set**（Hash 後）。
4. 🔲 **`any P` 存在型**（トレイトの重い尻尾＝最後・型消去・動的ディスパッチ）。
5. 🔲 **メタプログラミング**（`Derive`・コード生成・spec 上も最後）。

**コアライブラリ境界＝整理済**：`@Std/Io`・`Process`・`Async` は実 `.pw` の `extern "plew-intrinsic"` 宣言（名前 intercept 撤去・呼びは `plew_<name>`・ランタイム symbol camelCase）。lang item は名前ベース解決。残＝`print` のみビルトイン（整形 std 後に純 Plew 化）・`String`/`Array` メソッドの Plew 化（generic intrinsic 床が前提）。機構は [design-decisions.md](design-decisions.md)「コアライブラリの境界」。

横断 additive：演算子トレイト全配線（Eq/Ord 以外・需要駆動）・I2（import の with ゲート＝可視性検査・今は全フラット）・循環回収（Ref グラフ限定サイクルコレクタ）。詳細は [provisional.md](provisional.md)。

## ビルド・テスト・機能追加手順

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust 不要）。`./bootstrap.sh --reseed` で種更新（→ `compiler/plewc.seed.c` を commit）。
- **テスト**：`./test.sh`＝`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/part/`（複数ファイル）＋`tests/reject/*.pw`（plewc 非ゼロ終了＝受理の健全性）＋`tests/panic/*.pw`（compile+link 成功・実行は非ゼロ＋`.panic` stderr 部分一致）＋不動点。メモリは `ASAN=1 ./test.sh` ＋ ASan ビルドのコンパイラで自己コンパイル（`compiler/plewc _.pw > p.c; clang -fsanitize=address p.c -o pa; ASAN_OPTIONS=detect_leaks=0 pa _.pw`＝UAF/double-free）。
- **機能追加＝ADD→reseed→USE**：新機能を plewc.pw の**ソースで使う**には ①`compiler/src/` の codegen に足す（ADD）→ ②`./bootstrap.sh --reseed` で種更新→ ③ソースで使う（USE）。「ソースが使う機能は常にひとつ前のコンパイラがサポート済み」を守れば不動点は壊れない。**新しい preamble 行・codegen 出力変化・AST フィールド追加を足したら reseed を 2 回**（1 回目で挙動を種に焼き、2 回目で種ファイルを一致させる）。暗黙ビルトイン→実 `@Std`/`extern` 移行も同じ ADD→USE→REMOVE で flag day にしない。

## 運用メモ

- 動作する区切りで**記述的 git タグ**（`generics-data`/`value-semantics-complete` 等・バージョン番号はまだ）。コミットメッセージは英語＋`Co-Authored-By`。GPG 署名（`--no-gpg-sign` を使わない）。
- **不要になった実装は削除し、必要なら git tag から復旧**（例：`git checkout stage0-final -- bootstrap`）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。
- C 予約語（`double` 等）と衝突する Plew 識別子は生成 C が壊れる＝名前マングリング未実装（コンパイラ自身は回避・ユーザーコードで顕在化＝[provisional.md](provisional.md)）。
- LLVM 化は当面しない＝意味論が揃ってから（所有権・並行の後）、性能 or 直 WASM が要る時に並行バックエンドとして追加（C は捨てない）。
