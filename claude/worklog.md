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

**コアライブラリ境界＝整理済**：`@Std/Io`・`Process`・`Async` は実 `.pw` の `extern "plew-intrinsic"` 宣言（名前 intercept 撤去・呼びは `plew_<name>`・ランタイム symbol camelCase）。lang item 型は **`extern "plew-intrinsic" { struct I32 … }`** で Core が宣言＝所有（Swift モデル・表現不変・コヒーレンス是正）。**`Format` トレイト＋全整数型＋Bool の impl を純 Plew で Core に実装済**（`stringFromBytes` intrinsic＋桁ロジック）。**🎉 `print` も純 Plew 化完了**＝`@Std/Io` の `print[T](value~: T) where T: Format`（Stmt.Print/parsePrint/impPrint/print 特別 codegen を全廃・裸 `print(42)` はサフィックス必須＝既定型なし spec 準拠）。これを通すため **generic free fn の monomorphization をハードニング**（scan 時 exprType を codegen 同等に：closure 呼び結果・`arr.count`→U64・generic メソッド戻り型置換・Bool リテラル・compound 配列要素 ref〔`arr[i]->f`〕・`typeInfoOfRef` の ref 保持〔`bb.v.v`〕・generic-enum/struct-destructure の match バインド型＝`scanAddArmBinds` は mono scan と bounds checker 共用で 4 caller 全部に scrut 型を渡す〔自己ビルド破壊の真因＝Check.pw の未更新 caller だった〕）。`checkImplOnBuiltin` は **トレイト準拠メンバ on primitive は許し inherent `impl I32 {fn foo}` は拒否維持**（Io→Core が全プログラムに extern struct を持ち込む帰結への是正）。機構は [design-decisions.md](design-decisions.md)「コアライブラリの境界」。**String/Array メソッド Plew 化＝進行中**：✅ **String メソッド**（`impl String { fn isEmpty() }` 等を `.bytes` 上の純 Plew で・`checkImplOnBuiltin` は primitive スカラのみ inherent 拒否・String/Array は所有 aggregate ゆえ許可・String レシーバの method dispatch を genExpr/exprType に追加）。✅ **配列 intrinsic 床**（`extern "plew-intrinsic" { fn arrayPush[T](a: inout Array[T], v: T) … arrayGet/arraySet/arrayLen }` を `PlewArray_<E>_<op>` へ lower＝`emitArrayIntrinsic`・要素型は第1引数 Array[T] から復元・Swift Builtin 相当の還元不能床・コンパイラのみで standalone 検証済）。**残＝Array メソッド本体の Plew 化（`impl[T] Array[T] { inout fn append(v: T) { arrayPush(a: inout self, v: v) } }`）**＝**generic メソッドの monomorphization を Array に拡張**が前提（`emitMonoMethods` は user struct/enum の `genInsts` でキー・Array は genInst でないので、Array[E]〔c.arrayElems〕を receiver instantiation 扱いして `Array_<E>_<method>` を emit・`arr.append()` の dispatch を今の append 決め打ちから findMethod 一般化へ）。相応に大きく bootstrap も繊細（Core はコンパイラ自身のソース）。`arr[i]` の Index トレイト脱糖も整理対象。

**方針確定＝「あるべき姿」へ（Level 2・Swift/Rust モデル）**：Array 専用の mono 経路を足す（hacky・Array が 1-off で残る）のではなく、**生メモリの小さな床を作り、Array を Core の struct ＋ Plew メソッドにする**。これで Dictionary/Set/String 内部/独自コレクションが全部同じ床の上に乗る。進め方は2段＝**(i) 生メモリ床（`RawBuffer[T]`＋intrinsic）を additive に足し standalone 検証→種に焼く**（Array はまだ旧のまま・安全）→ **(ii) Array を Core struct へ切替**（Core を触る flag-day・bootstrap 最注意）。

**(i) 生メモリ床＝✅実装済・standalone 検証済**（`tests/run/raw_buffer`・204緑・不動点）。`RawBuffer[T]` blessed 型（`Ref` 同様 C `Tc*`・data 前に `[cap][rc]` ヘッダ＝data[-1]=rc/data[-2]=cap）＋intrinsic `rawAlloc(cap, of)`/`rawLoad`/`rawStore`/`rawCap`/`rawIsUnique`（`emitRawIntrinsic` で inline・型非依存ランタイム `plew_rawbuf_*` はヘッダのみ操作・`sizeof(Tc)`/`b[i]` は呼び出し位置 inline＝要素型ごとのランタイム生成なし）。配線＝`isRawBufInst`＋`genCTypeOf`/`emitConcreteCType`/`exprType`(local の ref 保持) を Ref の隣に。generic extern は mono instance を作らない（`registerCallInst` が isExtern を skip）。**残＝RawBuffer の値意味論（コピーで share・破棄で release）は (ii) で配線**（床テストは leak で可・Array が使う段で必要）。**`rawAlloc` の `of` は型ウィットネス**（返り値文脈推論 (A) 実装まで・空コレクションは of 無しになるので (A) 必須）。

**(i) 当初設計メモ（参考・実装は上記で完了）**：
- **`RawBuffer[T]`＝新しい blessed 型**＝「参照カウント付き生バッファ」。値意味論は **`Ref` を鏡写し**（コピーで retain・破棄で release）＝既存の値意味論機構を再利用し CoW の retain/release がタダで正しくなる（新 Clone/Drop プロトコルは作らない＝値意味論の哲学を崩さない）。配線箇所は Ref と同じ＝判定 `isRefInst`（Mono.pw:67）の隣に `isRawBufInst`、`Ref→Tc*` lowering（Mono.pw:228 付近）、retain/release（Expr.pw:49,62〔`plew_ref_share`〕・Decl.pw:534・release 側）。
- **重要発見＝ランタイムは型非依存にできる**：`RawBuffer[T]` を `Ref` 同様 C の `Tc*` に落とし、ヘッダ `{long long rc; long long cap;}` を data の前に置く（`((Header*)p)[-1]`）。alloc/cap/isUnique/share/release は `void*`＋ヘッダ操作で全要素型共通（プリアンブルに数本）。要素ごとの差（`sizeof(Tc)`・`b[i]`）は呼び出し位置にインライン。**だから PlewArray 式の要素型ごとランタイム生成は不要**＝床は軽い。
- **intrinsic（`@Std/Core` 宣言・lowering は `emitArrayIntrinsic` 同様コンパイラ内）**：`rawAlloc[T](cap: U64) -> RawBuffer[T]`→`(Tc*)plew_rawbuf_alloc(sizeof(Tc), cap)`／`rawLoad[T](b: RawBuffer[T], i: U64) -> T`→`((b)[i])`／`rawStore[T](b: RawBuffer[T], i: U64, v: T)`→`((b)[i]=(v))`／`rawCap[T](b)->U64`→`plew_rawbuf_cap(b)`／`rawIsUnique[T](b)->Bool`→`plew_rawbuf_is_unique(b)`。要素型 Tc は load/store/cap/isUnique は第1引数 `RawBuffer[T]` の型引数から復元。
- **唯一の wrinkle＝`rawAlloc` の要素型**：RawBuffer 引数が無いので T を args から取れない。LHS 束縛型（`self.data: RawBuffer[I64] = rawAlloc(...)`）からの return-context 推論が要る（または呼び出し明示型引数 `rawAlloc[I64](...)` の対応）。実装時にここを最初に解く（return-context 推論の有無を確認）。
- **runtime プリアンブル**：`void* plew_rawbuf_alloc(long long elemSize, long long cap)`（malloc(header+elemSize*cap)・rc=1・cap 格納・data 返す）／`void* plew_rawbuf_share(void* p)`（rc++・`plew_ref_share` と同型）／`void plew_rawbuf_release(void* p)`（rc--・0 で free）／`long long plew_rawbuf_cap(void* p)`／`int plew_rawbuf_is_unique(void* p)`（rc==1）。
- **standalone テスト**：`mut val b: RawBuffer[I64] = rawAlloc(cap: 4U64); rawStore(b: b, i: 0U64, v: 99I64); print(rawLoad(b: b, i: 0U64))`→99・`rawCap`/`rawIsUnique` も。

**(ii-a) ✅実装済**（`tests/run/array_methods`・205緑・不動点）：`impl[T] Array[T] { fn … }` のユーザーメソッドが**純 Plew で動く**（要素型ごとに monomorphize＋名前で dispatch・Array 表現は PlewArray のまま）。「配列メソッド＝無条件 append」ハードコードは **append 以外を撤廃**（append 自身は移行 fallback として残置）。実装＝①`parseImpl`：`impl Array[T]` は受信子が array 型としてパースされ span が要素を指すので、メソッドを**頭名 "Array" で登録**（headTok）。②`emitArrayMethods`：`emitMonoMethods` と並行の専用パス＝`c.arrayElems`（要素型）でキー（Array は mono struct でないので genInsts に入れられない）・**型パラメータ要素（`Array[T]` の T）はスキップ**（自己参照 env＝genCElem 無限再帰を回避）。③`genExpr` Method：append 以外の配列メソッドを `Array_<E>_<selector>` へ dispatch。④`exprType`：Array メソッド内の self は array（kind 3・要素名）型・配列への Method 呼びは戻り値型 T を要素型に置換。

**プレリュード機構＝✅実装済**（`std/Prelude.pw`・`tests/run/prelude_array`）：**ambient な Array メソッドの置き場**。loader が全プログラムに**自動ロード**（末尾 append＝ユーザー行番号を動かさない・`computeStdRoot`+"Prelude.pw"・無ければスキップ）。import 不要で `xs.get(i:…)`/`xs.set(i:…, value:…)`/`xs.append(v)` が使える（lang-item Array の一部）。中身＝配列 intrinsic 床（`arrayPush`/`Get`/`Set`/`Len` を `extern "plew-intrinsic"` 宣言）＋`impl[T] Array[T] { append, get, set }`。**ii-b の `struct Array` もここに置く**。

**`.append`＝✅純 Plew 化済**：`impl Array { inout fn append(value~: T) { arrayPush(a: inout self, v: value) } }` へ dispatch（要素型ごと mono）。push ハードコードは**プレリュード不在時の fallback のみ**残置（freshly-seeded 保険）。`genArrayUserMethod` に要素型引数ハンドリング（`argIsElementTyped`+`emitArrayElemValue`）を足し `m.append([1,2,3])`（ネスト配列）も動く。

**残＝`.count`/`arr[i]`**：どちらも**フィールド/添字構文**（`digits.count` 括弧なし・`m[i]`）で、メソッド化＝構文変更が要るので **ii-b（struct 化）でまとめて**扱う。append/get/set が Plew 化できたので ii-a の主目的（メソッドを Plew で書ける）は達成。

**⚠ ii-b の `count` は stored field（重要）**：**Plew は computed property を持たない**ので、`.count`（括弧なしフィールドアクセス）は `fn count()` メソッドにできない＝**`pub(get) mut val count: U64` の stored field 必須**。よって struct は：
```
struct Array[T] {
    data: RawBuffer[T]
    pub(get) mut val count: U64   // .count はこのフィールド読み出し
}
```
`pub(get)`＝外から読めるが書けるのは Array 自身のメソッドのみ（append が `count += 1`）。`mut val`＝可変記憶域。`xs.count` はこのフィールドアクセスに落ちる（メソッド呼びでない）。`len` という名前にすると `.count` が `.len` フィールドに化けるので**フィールド名は `count`**。

**(ii-b) 表現 swap（真の flag-day・最後）**：`struct Array[T] { data: RawBuffer[T]; len: U64 }` を Core に・`PlewArray_<E>` 撤去・`RawBuffer` 値意味論（コピー share・破棄 release）を Ref の各サイトに配線。

**(ii) 実装経路メモ（ii-a は実装済・以下は記録）**：
- `methodMatchesInst`（Mono.pw:845）は `inst.nameStart=="Array"`（recv "Array"）で**既に Array メソッドにマッチ**＝条件は揃っている。
- ただし `c.genInsts` に `Array[E]` を足すと mono **struct**（`emitMonoStructs`）も emit され `PlewArray_<E>` と衝突する。→ **専用パス `emitArrayMethods(proto)`** を新設（`c.arrayElems` × recv=="Array" のメソッドを `emitMonoMethod(method, arrayInstRef[E])` で emit・`_.pw` の `emitMonoMethods` の隣に proto/body 両方）。`emitMangle(Array[E])`＝`Array_<E>`・self 型は `emitConcreteCType(Array[E])`＝`PlewArray_<E>` なので genSignature はそのまま使える。
- **dispatch**：`genExpr` Method の `bt.kind==3`（Expr.pw:640）は**メソッド名を見ず無条件で append/push**。→ 名前が `append` 以外なら `findMethod(recvStart="Array"〔kwSpan で span〕, name, args)` で Array メソッドを引き、`Array_<E>_<selector>(selfInout? &recv : recv, args)` を emit（`.append`/`.count`/`[i]` のハードコードは移行中 fallback として残す）。
- **前提の小改修**：`c.arrayElems` は要素 ref（`fieldStart`）を **compound 型のみ**保存（simple `I64` は 0・名前のみ＝Mono.pw:444-459）。`Array[E]` ref 合成と env の `T→I64` 置換に要素 ref が要るので、**`fieldStart=re` を常時保存**へ（`arrayElemNameForRef` の `fieldStart!=0` ガードは sameMangle で正しく動くので安全のはず・要 reseed 検証）。`arrayInstRef(elemRef)`＝`Array[elemRef]` TypeRef を c.types に append（"Array" span は `kwSpan(c, "Array", 5)`）。
- **移行手順（ADD→reseed→USE で flag-day 回避）**：①`emitArrayMethods`＋dispatch を足す（append ハードコードは残す）→ reseed →②Core に `impl[T] Array[T] { fn first()… }` を Plew で書き standalone+self 検証 →③`.append` 等を Plew メソッド化しハードコード撤去 → reseed。各段で種が新ソースをコンパイルできる。
- **ii-b（表現 swap・真の flag-day）**：`struct Array[T] { data: RawBuffer[T]; len: U64 }` を Core に・`PlewArray_<E>` ランタイム撤去・`RawBuffer` の値意味論（コピー share・破棄 release）を Ref の各サイトに配線・リテラル/`[i]`/`.count` 振替。**Array はコンパイラ自身が全面利用**ゆえ最注意（種は旧 Array・新ソースは新 Array）。先に ii-a を固めてから。

**(ii) 旧メモ（表現 swap の最終像・参考）**：`struct Array[T] { mut val data: RawBuffer[T]; mut val len: U64 }`＋`impl[T] Array[T] { append/get/count/… }`（CoW＝変更系で `rawIsUnique` 見て共有なら複製）。リテラル `[..]`→`Array.new()`+append、`arr[i]`→Index、`.count`→メソッド に寄せ、専用ランタイム `PlewArray_<E>`＋決め打ちを撤去。**Array はコンパイラ自身が全面利用**ゆえ種は旧 Array・新ソースは新 Array＝flag-day。先に (i) を種へ焼いてから一気に切替。String の `bytes`（Array[U8]）も連動。

横断 additive：演算子トレイト全配線（Eq/Ord 以外・需要駆動）・I2（import の with ゲート＝可視性検査・今は全フラット）・循環回収（Ref グラフ限定サイクルコレクタ）。詳細は [provisional.md](provisional.md)。

## ビルド・テスト・機能追加手順

- **ビルド**：`./bootstrap.sh`＝C 種 `compiler/plewc.seed.c`→clang→`plewc0`→`compiler/src/_.pw` を自己コンパイル→不動点 cmp（Rust 不要）。`./bootstrap.sh --reseed` で種更新（→ `compiler/plewc.seed.c` を commit）。
- **テスト**：`./test.sh`＝`tests/run/*.pw`（`.out` 照合・任意 `.in`）＋`tests/part/`（複数ファイル）＋`tests/reject/*.pw`（plewc 非ゼロ終了＝受理の健全性）＋`tests/panic/*.pw`（compile+link 成功・実行は非ゼロ＋`.panic` stderr 部分一致）＋不動点。メモリは `ASAN=1 ./test.sh` ＋ ASan ビルドのコンパイラで自己コンパイル（`compiler/plewc _.pw > p.c; clang -fsanitize=address p.c -o pa; ASAN_OPTIONS=detect_leaks=0 pa _.pw`＝UAF/double-free）。
- **機能追加＝ADD→reseed→USE**：新機能を plewc.pw の**ソースで使う**には ①`compiler/src/` の codegen に足す（ADD）→ ②`./bootstrap.sh --reseed` で種更新→ ③ソースで使う（USE）。「ソースが使う機能は常にひとつ前のコンパイラがサポート済み」を守れば不動点は壊れない。**新しい preamble 行・codegen 出力変化・AST フィールド追加を足したら reseed を 2 回**（1 回目で挙動を種に焼き、2 回目で種ファイルを一致させる）。暗黙ビルトイン→実 `@Std`/`extern` 移行も同じ ADD→USE→REMOVE で flag day にしない。**重要な落とし穴＝コンパイラは `@Std/Io`→`@Std/Core` を import するので、Core/Io/Process の `.pw` も「コンパイラ自身がコンパイルするソース」の一部**。よって **Core に「種のコンパイラがまだ受理しない構文/機能」を足すと bootstrap が即壊れる**（例：`impl String {}` を Core に足したら、種のコンパイラが inherent-on-builtin を拒否して [2/3] で落ちた）。回避＝**機能を先に種へ焼いてから Core で使う**：①コンパイラ側の許可変更だけ入れ Core の新 .pw 機能は外したまま `--reseed`（種に許可を焼く）→②Core にその機能を足して新コンパイラで `--reseed`（USE）。`--reseed` 自体も古い種で plewc0 を作るので、この順を破ると `--reseed` ごと詰む。

## 運用メモ

- 動作する区切りで**記述的 git タグ**（`generics-data`/`value-semantics-complete` 等・バージョン番号はまだ）。コミットメッセージは英語＋`Co-Authored-By`。GPG 署名（`--no-gpg-sign` を使わない）。
- **不要になった実装は削除し、必要なら git tag から復旧**（例：`git checkout stage0-final -- bootstrap`）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。
- C 予約語（`double` 等）と衝突する Plew 識別子は生成 C が壊れる＝名前マングリング未実装（コンパイラ自身は回避・ユーザーコードで顕在化＝[provisional.md](provisional.md)）。
- LLVM 化は当面しない＝意味論が揃ってから（所有権・並行の後）、性能 or 直 WASM が要る時に並行バックエンドとして追加（C は捨てない）。
