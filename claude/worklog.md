# 作業ログ

> 現在地・次の候補・運用メモ・**git で拾いにくい再利用知見（罠）**だけを置く。完了した「やった」は git（記述的タグ・コミット）へ。「なぜ・却下案」は [design-decisions.md](design-decisions.md)、パイプライン設計は [architecture.md](architecture.md)、spec からの意図的剥離・暫定は [provisional.md](provisional.md)、メタプロの段取りは [metaprogramming-architecture.md](metaprogramming-architecture.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で全パートを綴じる 1 モジュール）。自分自身を不動点までコンパイル。構文解析は完全に共有 `@Std/Syntax` の責務（コンパイラとマクロが唯一の共有パーサを通る＝真の 1 AST）。`compiler/src/` 本体は共有パーサで parse→`Codegen/Lower.pw` で arena へ lower するだけ（ローディングもパース駆動）。

🎉🎉 **LLVM 単一 backend（C backend 退役・削除済み）。** かつて LLVM が C と完全機能同等に達した点が tag `llvm-c-parity`。その後 C backend を退役し、LLVM 一本化した（C 訳・C 生成コードは git 履歴／同タグに保存）。
- **バイナリ 1 本**：`compiler/plewc`（root `_.pw`＝フロントエンド part 群＋`Backend/Llvm`・libLLVM-C をリンク）。`main`＝`runFrontend()`（共有フロントエンド `Codegen/Driver.pw`・`Comp` を返す）→ `emitLlvm()`。
- **受理健全性は emission 非依存の共有パス `Codegen/Verify.pw`**（`verifyProgram`）：全 non-generic・non-async 関数を walk し受理検査を実行＝C emitter なしでも spec 不正を弾く（旧 C emitter の inline 検査を factor out した唯一の置き場）。
- **self-host**：`./bootstrap.sh`（IR 種 `compiler/plewc.seed.ll`＋`.seed.runtime.c`→clang＋libLLVM→plewc0→自己コンパイル→IR 不動点）。`--reseed` で IR 種更新（→ 種＋追跡バイナリ `compiler/plewc` を commit）。
- **グリーン**：`./test.sh`（run203/panic11/reject109/part5/fail=0＋不動点）／`./test-gen.sh`（gen10/reject1）。
- **C backend 削除の段取り**（参考）：①C build 面の削除＋正典名リネーム（`_llvm.pw`→`_.pw`・`plewc-llvm`→`plewc`・`bootstrap-llvm.sh`→`bootstrap.sh`・種 `.ll`）②共有 Codegen に残る dead な C 生成関数（`emitC` 起点の到達不能クラスタ・genExpr/genStmt/genDecl/C ARC・mono・async・numeric runtime emitter 等 180 fn ~7250 行）をラベル考慮の到達可能性解析で剥がす（LLVM self-compile が undefined 参照で誤削除を loud に弾く＝安全網）。

完了した大物（詳細は git・記述的タグ）：async/await 段階 1-3（stackless SM・LLVM）・コアライブラリ境界（`@Std` の `extern "plew-intrinsic"`）・Array＝`RawBuffer` 床の Plew struct（[array-struct-plan.md](array-struct-plan.md)）・可視性完全強制・Iterator/Iterable＋lazy map/filter・再帰値型 auto-boxing＋ARC・renovate Phase A-D（ARC 1 本化・Op enum・型付き AST キャッシュ・名前/型 interning）・メタプロ M0/M1/M2（マクロが実宣言を読んで生成・Eq/Ord/Hash derive・Dictionary[K,V] lang item）・フロントエンド統合（全パース→共有 @Std/Syntax）・演算子トレイト配線（算術/ビット/単項/比較を witness 脱糖・built-in 算術完全削除・`??`→`unwrapOr`・Index/IndexSet・Chain `?.`）・**C backend 退役→LLVM 一本化**・**ユーザー定義トレイトのディスパッチ拡充**（継承 `trait Sub: Super` bound 越し・`where T: Trait[Args]`・blanket impl `impl[T] T as Trait`）・**拡張システム `#Ext`（spec/09）を struct レシーバで完備**（値/型ビュー `value#Ext`/`Type#Ext`・`defaultExtension`・`#P` 源選択・self-view/`#!Ext` super/スタック `#A#B`・明示ビュー強制4面〔call/let/return/代入〕・view-aware オーバーロード `f(a:P)`/`f(a:P#Ext)`・トレイト主語 `impl Trait`/`impl B as A`・外部型コヒーレンス）・**`any P` 存在型（spec/08）完成**（fat pointer `{data,vtable}`＋per-(具体型,トレイト) thunk vtable・動的ディスパッチ・全 value 位置＋`Array[any P]` 異種混在＋for-over-any-iter・トレイト型引数/関連型束縛 `any Add[I32,Output=I32]`/`any Iterator[Item=I32]`・Self 返り再消去・inout self・Self 入力 reject・形成全束縛検査・コピー値意味論〔copy thunk〕）・**ambient `@Std/Core`**（演算子/`Optional`/`Result`/`for`・range が import 不要＝起動時 force-load・`assert` は import gate 維持）・**トップレベル変数（spec/15）**（`val`/`mut val`＋`export`・`plew_init_globals` で宣言順に 1 回初期化→main 冒頭で呼ぶ・各本体エントリで `seedGlobals`/`seedGlobalLocals` し global を base local として再登録＝読み書き/型回復/演算子/可視性が local 機構で素通り・shadow/クロージャ捕捉除外/cross-module export 対応）。

## 🎯 次のゴール＝「3 大機能を除く spec 完全準拠」

**並行 spawn・循環回収・パッケージ管理（M3）の 3 つを意図的に後回しにし、それ以外で Plew が完全に仕様通り動く状態を目指す。** 残作業の地図は [provisional.md](provisional.md)（＝現コンパイラが spec から意図的に剥離している箇所のカタログ）＝**この 3 つ以外の剥離をすべて潰す**のがゴール。

**スコープ内（潰す）**＝以下＋provisional.md の各テーマ節で `✅` でない項目：
1. **🔴 enum/primitive のメソッドディスパッチ＝✅ 完了**（最大ブロッカー解消）：enum の inherent メソッド（`isPlainUserFn` が enum 受容・本体 self 束縛で enum recvRef〔match 復元〕・`genLlvmMethod` に enum dispatch〔by-value／inout=placePtrOf〕）・enum トレイト準拠メソッド・enum/primitive の `#Ext` 拡張メソッド（`genLlvmExtMethod` を struct→enum→primitive の受信型解決に一般化）・enum `defaultExtension`（enum 本体パーサ＋lowering で `defaultExts` 登録）。primitive local の tref も let で設定（`x#Ext.m()` 解決）。注：`pub impl I64 {}` 等の built-in 型 inherent メソッドは spec が正しく禁止（`#Ext`/トレイト準拠を使う）＝バグでない。tests run/{enum_method,enum_method_inout,enum_extension,primitive_extension,enum_trait}。
2. **既知バグ（下記）**＝import なしプログラムの誤 reject／I/O import gate（受理健全性の穴）。
3. **Self 入力 param の準拠**＝`fn eqTo(other: Self)` 手書き準拠が完全性検査で誤 reject（derive は無事）。
4. **Iterator 拡充**＝終端（reduce/fold/count/sum/collect/any/all/first）＋ adapter（take/zip/enumerate/skip）。
5. **RNG/`Random`**＝`Dictionary` のランダムシード含む。
6. **backend 全体の ARC drop**＝array/String/any box の scope-exit 解放（hidden cost の leak 解消）。
7. **トレイト/拡張の残小物**＝トレイト引数 aware の多重 conformance 区別・コンテナ不変性 `Array[P]`≠`Array[P#Ext]`・型レベル chained `Type#A#B`。
8. **FFI/数値の spec 項**＝provisional.md の未 `✅` 項（値意味論/CoW の残・整数幅・レンジ・ラベル等で剥離が残る箇所）。

**スコープ外（このゴールに含めない）**：
- **3 大機能**＝spawn（spec/14）・循環回収（design-decisions）・パッケージ管理（M3）。
- **spec 自身が additive/将来送りにしている項**＝固定長配列 `[E; N]`・const generics・`Slice`・部分文字列・`USize`/`ISize`（これらは「現 spec からの剥離」ではなく spec が将来に回しているので準拠対象外）。

**進め方**＝provisional.md を上から走査し、3 大機能・spec-future を除いて各剥離を 1 つずつ green 増分で潰す→各区切りで commit＋push＋本ログ更新。完了の目安＝provisional.md が（3 大機能・spec-future を除いて）すべて `✅` になり、spec 由来の reject/run テストが網羅される。

**ツール要件（ゴールの一部）**＝**任意のパスに配置したコンパイラバイナリ単体で `plew build ./Main.pw` と `plew gen ./Main.pw` が動く**こと。
- **現状**：`plew`（build）はパス非依存済（symlink 解決で隣の `compiler/plewc` を見つけ・std はバイナリ位置解決・生成物は libc のみ）だが**サブコマンドは `plew <file>`／`plew run`＝`build` 動詞が無い**。`plew gen` は別スクリプト `plew-gen.sh` で **`cd $(dirname $0)`＝リポジトリルート前提＋`llvm-config` 依存**ゆえ任意パスのバイナリ単体では動かない。
- **やること**：①`plew` に `build`/`gen` サブコマンドを統一（`plew build ./Main.pw`／`plew gen ./Main.pw`・既存の bare `plew <file>`/`run` は維持してよい）②`gen` を**パス非依存化**（`cd repo` を捨て build と同じ symlink 解決で plewc を見つける）＋**`llvm-config` 依存を外す**（gen harness も libc のみリンクで済むか確認＝build と同じ床に揃える）。`@[...]` 付きファイルの auto-part・`<Foo>.gen.pw` 出力規約は不変。
- **設計の分岐（未決）**：「バイナリ単体」を ⓐ relocatable な薄い driver スクリプト＋`compiler/plewc`＋clang で満たすか、ⓑ `plewc` 自身が `build`/`gen` を解釈し clang を内部 spawn する真の単一バイナリにするか（さらに進めれば LLVM 直接オブジェクト出力で clang 不要）。着手時に確認。

## 既知バグ（要修正）

- **🐞 import なしプログラムが「arithmetic operator needs Add/Sub/...」で誤 reject＋intercept される I/O 組込の import gate が無い**（受理健全性の穴・調査済）。詳細・直し方は [provisional.md](provisional.md)「可視性・モジュール・import」の該当項（prelude が自己完結でなく verify が未使用 prelude 関数の witness で落ちる／`print` 等は LLVM backend が呼び名 intercept で import を問わず emit）。当面の回避＝`import @Std/Io with { print }`。

## 次の候補（open・additive／要判断）

- **Iterator 拡充**：終端（reduce/fold/count/sum/collect/any/all/first）＋遅延 adapter（take/zip/enumerate/skip・`MapIter`/`FilterIter` をテンプレに）。demand-driven 単相化が動くので確立パターン沿い。
- **並行 additive**：`spawn`/`JoinHandle`/チャネル・spawn 境界の意味論強制（move/copy のみ越境・`Ref` は spawn 不可）・`local` 伝染解析（言語仕様の決定が出る・重い）。
- **ユーザー定義トレイト・拡張 `#Ext`（spec/08,09）＝実装済**（残ギャップは [provisional.md](provisional.md)「型システム：…拡張」がカタログ）。残る小物＝トレイト引数 aware の多重 conformance 区別・コンテナ不変性 `Array[P]`≠`Array[P#Ext]`・型レベル chained `Type#A#B`（値レベルは可）。**前提機能ブロック**＝enum/primitive/generic の ext レシーバと enum defaultExtension は**通常の enum inherent メソッドが backend 未対応**（「only on registered struct value」）・primitive は trait-only ゆえ＝enum/primitive メソッドディスパッチが入れば ext 経路は自動で乗る別件。
- **`any P` 存在型（spec/08）＝完成**（「完了した大物」参照）。**残り（backend 全体水準・任意）**＝box の **drop**（スコープ離脱で box を free しない＝backend 全体が array/String value 型を scope-exit で free しないのと同水準＝leak。直すには vtable に drop thunk＋any local の scope-exit release〔rc/`rawbufRelease`〕が要る・backend 全体の ARC 完成と一緒にやるべき別件）。**値意味論のコピーは完成**＝any→any コピーは copy thunk で deep、concrete→any boxing も `copyValueIfPlace` で deep（struct→struct コピーと同等・当初 shallow だったのを修正済）。**前提機能ブロックを 1 つ解消**＝平易メソッドの `-> Self` 未解決 SEGV を Step B で修正済（Self 環境を method emission で設定）。
- **循環回収**：Ref グラフ限定サイクルコレクタ（Bacon–Rajan trial deletion）。設計確定済（[design-decisions.md](design-decisions.md)）・優先度中。
- **M3＝パッケージ管理**導入後に `@Std/Syntax` を in-tree から外部共有パッケージへ昇格（コンパイラもマクロも同一版に依存）。
- **LLVM additive**：generic async・struct/String を載せた Promise 値・FFI 拡張（`repr(c) struct`・`CInt`/`CSize`・所有権ラッパ）・LLVM 直接オブジェクト出力（現 `LLVMPrintModuleToString`→clang）。
- **🔴 RandomState（忘れない）**：Rust の `HashMap` は SipHash-1-3 ＋ マップごとランダムキー（DoS 耐性）。Plew はまだ RNG が無く `Dictionary` は固定キー（決定的）で実装済。**`Random`/RNG 着手後にマップごとのランダムシードへ差し替える**（アルゴリズム・トレイト形は不変・シード源を差すだけ＝additive）。

## 再利用資産・罠（git で拾いにくい知見）

### フロントエンド・arena・型機構

- **型付き AST キャッシュ**：`typeOf(c, id)`＝codegen の型読み口。ノード型を `Comp` の **4 並列 scalar 配列**にキャッシュ（self-host は struct 配列 IndexSet 非対応ゆえ・`arr[i]=v` の scalar IndexSet は可）。**body emission のエントリ（`genFunc`/`genClosure`/`genAsyncFunc`）で `clearExprTyCache`**＝env（Self/型 args/インスタンス）は 1 body の emission 中だけ一定なので grounded 型をその間だけキャッシュ・関数境界で破棄（filled-id リストのみ reset で O(fills)）。**`buildExprTyTable` は slot を allocate するだけで充填はしない**（typeOf が emission 中に遅延充填）。
- **共有パーサ→arena lower**：共有 @Std/Syntax パーサが値ツリー（`TopItemAst`/`DeclAst`/`ImplAst`/…）を返し、`Codegen/Lower.pw` が arena（`Expr`/`Stmt`/`Func`/`StructDef`…）へ lower。**名前の offset 規律**＝`moduleOf` に効く名前（free fn 宣言名・call 名・extern fn 名・import/export 名）は**原本 offset 維持**（再インターン不可）、それ以外（struct/enum/field/型名・impl 系全部）は `internBytes` で再インターン（codegen は text 出力ゆえ byte 同一・moduleOf 不参加）。**罠**：パース駆動ローディングで `c.bytes` はファイル源と再インターン名が交互配置になる（writeSpan は text 出力・moduleOf は per-file レンジ参照ゆえ不動点・可視性とも安全）。
- **block 0 は dummy 予約**：`body` フィールド 0 は「無本体」sentinel（extern fn・trait 要求シグネチャ）。entry ファイルは ambient Prelude より先に lower されるので、予約しないと最初の関数本体が block 0 に来て無本体と誤判定される。`_.pw` の Comp 初期化で `c.blocks.append(<Block stmts=[] />)`。
- **名前/型 interning（Phase C＋D）**：`intern(c, start, len) -> U64`＝span の**内容**を 1-based id に写す（FNV-1a＋手書き open-addressing・衝突は `spansEqual` 解決）。**0 は返さない**＝`nameId`/`tyNameId` の既定 0 が「未設定」sentinel。**唯一の content-keyed テーブルを宣言名と型名が共有**（`TypeRef` の "Foo" id と `StructDef` "Foo" id が同一）。`TypeRef.nameId` の唯一の choke point＝`pushType`。**罠**：①構築点を 1 つでも漏らすと id=0 で converted スキャンが取りこぼす silent miscompile（特に「Bind を返すヘルパ」が raw `<Bind/>` リテラルで nameId を落とすと比較が `real==0` で恒偽）。**id を比較する operand は出所が internBytes/pushType/構築点 intern のいずれかか必ず確認**。②Local は動的（codegen 中に push）＝`addLocalCn` で intern。③スキャンは「クエリを 1 回 intern→ループは整数 ==」＝intern をループ外に hoist しないと無意味。
- **演算子 opcode**：`op` フィールドは `kindCode(Kind)` の整数。`Ops.pw` の `opAdd()..opShrAssign()`（`kindCode(<Kind.X/>)`）が単一の symbolic 源（magic 数を codegen に漏らさない）。
- **負リテラル畳み込みは lower で実装済**：`lowerExpr` が `Unary(Neg, IntLit)` を符号付き `Expr.Int`（`isNeg`・magnitude in `value`）へ畳む（precedence 解決後の lower で畳むので `-128.foo()` は real Neg のまま）。新リテラル種を足すなら `Expr.Int` の全 match/構築点に `isNeg` を通すこと。
- **⚠ ambient Core に「よくある名前」を入れると衝突**：①bare 呼び出しは assoc fn を拾わない＝`findFunc`/`firstFuncByName` の free-fn フィルタは `hasRecv` だけでなく `isAssoc` も skip（assoc は `Type.` 必須）。②conformance は型パラメータ arity も一致で照合（`checkConformances` は `nameId` かつ `typeParams.count == traitArgs.count`・同名異トレイトの共存は arity/形状で弾く）。
- **missing-return 検査**（`Codegen/Check.pw` `checkReturns`）：非 `()` 関数の本体が全経路で発散しなければ loud エラー。Plew は末尾式を暗黙 return しない（`give` はブロック式専用）ので必須。
- **⚠ オーバーロード解決は局所 struct 引数の型を front-end で見れない**：`findFunc`/`paramsTypesMatch` は `exprType`（front-end）に依存するが、局所変数は `c.locals` 非投入ゆえ struct 値の型が scalar に化け、**ラベルのみで照合→first-by-label を返す（順序依存）**。型/ビューで本当に選び分けるには backend 側で精緻化する（`exprStructIdx`/`exprViewExtId` は backend のみ完全＝拡張の view-aware オーバーロード `findFuncViewAware` がこの理由で backend 実装）。新たに「引数の型/属性でオーバーロードを分ける」機能は同じ壁に当たる。
- **拡張ビュー機構（spec/09）**：`#Ext` は**メソッド源セレクタ**＝`Func.extId`（拡張名 id）/`srcTraitId`（トレイト源・提供メソッド copy 用）でタグし、`findExtMethodById` が両対応で解決。値の view は arena `Expr.ExtView(recv, src, strip)`、型の view は `TypeRef.viewExtId`（`pushType` 保持・型同一性の一部）。**bare 解決から除外**＝`findMethod` が `extId != 0` を skip（`defaultExtension` は `isDefaultExt` で緩和）。**ext メソッドの self は `Recv#Ext` ビュー**（`beginFnBody` で recvRef に viewExtId 載せ＝`self.m()` 再帰）。`exprViewExtId`/`collectViewChain` が値/型/再ビュー/strip/スタックの view を集約＝method dispatch がこれで拡張優先解決。明示ビュー強制は `genArgValue`/`Stmt.Let`/`Stmt.Return`/`Stmt.Assign` の4面で `viewExtId` 突き合わせ。**罠**＝generic/拡張メソッドの呼びは**ラベル必須**（省略は的外れに「this call is not yet supported」で reject＝関数未解決の症状）。enum/primitive レシーバの ext は**通常の enum/primitive inherent メソッドが未対応**ゆえブロック（struct 限定）。
- **`any P` 存在型機構（spec/08・`Backend/Llvm.pw`）**：値＝fat pointer `st.anyTy`=`{ptr data, ptr vtable}`。`data`＝rawbuf セルに boxed した具体値・`vtable`＝`(具体 struct, トレイト, bindKey)` ごとの静的 global（`ensureAnyVtable`・slot 0＝copy thunk〔値意味論・`deepCopyStructValue`〕・slot 1+＝要求メソッド thunk）。**thunk が要る理由**＝具体型ごとに self の by-value サイズが違い vtable slot signature を統一できない＝thunk が「要求シグネチャ（Self 以外 concrete）」へ正規化（`buildAnyThunk`：load self→witness pf 呼び・inout 要求は self を ptr で渡す・`-> Self` 要求は結果を再 box）。**型束縛**＝`TypeRef.argLabels`（`[Item=T]` の named／positional）→`anyBindingEnv` が trait typeParams/assocTypes を `curTypeParams`/`curTypeArgs` に積み `groundTypeRef` で `Rhs`/`Item`/`Output`→concrete。**型復元 hook**（背骨）＝`refIsAny` で `paramLlvmTy`/`llvmFnRetTy`/`fieldLlvmTy`→anyTy・`exprTypeRef`/`valueKind`/`exprLlvmType` の Method/Field 枝が `anyMethodRetRef`（grounded 戻り・`-> Self` は anyRef）を返す・局所/param/フィールド/for-var の `locTypeRef` に any TypeRef を載せる。**coercion**＝concrete→any は `coerceToAnyIfNeeded`（box＋vtable）・any→any place は `copyAnyIfPlace`（copy thunk）＝両者を 6 store 面（let/arg/return/field/配列要素/assign）に hook。**罠**＝①vtable global は**先生成→cache→thunk 構築**順（`-> Self` re-erasure の自己再帰回避）②`Self` 解決はメソッド emission で `setSelfItemEnv` 必須＋`llvmFnRetTy`/`paramLlvmTy` の `curSelfRef` 分岐（平易メソッドの `-> Self` は元々 SEGV だった）③arena `Expr.Method` の match で args rename は `args: val x`（bare `val x` は非存在フィールド punning で self-compile を壊す）④形成検査 `checkAnyFormation`＝全 typeParams/assocTypes 束縛必須。

### 値意味論・ARC・再帰値型

- **再帰値型 box**：`markBoxedFields`（`Mono.pw`・`Comp.boxedFields`＝field の `nameStart` キー）が循環を閉じる**ユーザー側フィールド**を box（`Array`/`RawBuffer`/`Ref`/`WeakRef` は cut・`Optional`/`Result` は透過）。box＝`plew_arc_alloc` rc セル・copy/share は retain・release は rc→0 で pointee 再帰 release＋free。読み deref コピー・書き fresh box に repoint（共有セル不変＝値意味論）。
- **⚠ `Array[Enum]` の要素 deep copy/release**：`Array[E]` 要素を deep に copy/release するかは `Codegen/Array.pw` の `arrayElemNeedsDeep`＝`structNeedsCopy` **OR** `enumNeedsCopy`。enum 要素を取りこぼすと heap 持ち variant の `Array[Enum]`（`Array[ExprAst]` 等）が浅い要素管理になり leak＋UAF。**新しく heap を持つ要素種を Array に入れるときは必ずここを確認**。
- **⚠ by-value 引数のローカルはコピーされず格納されうる**：ヒープ持ち値型の名前付きローカルを by-value 引数として `append` 等に渡すと、call site で CoW コピーされず浅く格納され、scope 末の release で格納要素がダングリング。**`xs.append(parseFoo())` と一時値で渡す**（parse 結果を一旦ローカルに束ねてから push を避ける・根治＝by-value 引数 place の CoW コピーは未対応）。
- **値意味論 ARC の在処**：concrete＝`emitFieldAction`（struct/enum 共有・unique-deinit 込み）、mono＝`emitMonoFieldAction`/`emitMonoModeDef`。**heap フィールド種を足すのはこの 2 dispatcher**。need 判定は `fieldNeedsCopy/Release`・`typeInfoNeedsCopy/Release`。
- **give-block 脱糖（codegen で式を組む雛形）**：「empty 構築→副作用文の連打→値を yield」を式位置で出すには arena `IfExpr(cond=Int(1,isBool), thenBlk, elseBlk)`（値位置ブロック＝C statement-expression）を合成し、then で `mut val __t = …; …; give move __t`、else は dead だが型のため同型値を give（Dictionary リテラルの `lowerDictLit` がこの形）。**所有権**＝`give move __t` で deep copy なし移譲（素の `give __t` は shallow コピー＋ブロック末 release で UAF）。

### generic・Iterator 機構

- **generic struct field の array 単相化**：`Array[Box[T]]`/`Array[Entry[K,V]]` の field/変数 field は `groundedArrayFieldInfo`（`genericFieldTypeInfo`/`genericEnumFieldTypeInfo`/`substTypeInfo` の array 枝）で instance env 越しに ground＝`ref` 不変で波及ゼロ。template の非 ground compound 要素は runtime/method を emit しない。**罠**：型パラメータ名 vs 具体型名のグローバル衝突（ユーザー struct `B` と `MapIter[…,B]` の `B`）→ `isTypeParamName` は宣言済 struct/enum 名を具体型扱い。
- **Iterator/generic 機構**：method-level 型パラメータ（`FnInst.recvInstRef`・mangle suffix は method-own tail のみ）・demand-driven 単相化（`providedRetReachable`＝`FilterIter[FilterIter…]` の無限型族を到達時のみ発行）・Self/Item 解決（`curSelfRef`/`curItemRef`）・構造的型推論（`unifyTypeParam`）。generic-レシーバ・メソッド本体の推移的インスタンス探索＝`scanGenInstMethodBodies`。
- **generic 呼び出しの引数 T 推論には arg 型に名前 span が要る**：`inferFnArgs`→`tyRefOfInfo` は `nameLen==0` で 0 を返す。リテラル等の `typeOf` が名前なし TypeInfo を返すと T 未推論。`Expr.Str` は `stringTypeSpan` で "String" 名 span を付与済。新リテラル種を足すなら typeOf に名前 span を持たせること。

### LLVM backend（`Backend/Llvm.pw`・ヘッダ＋コメントに詳細）

- **ディスパッチ**：ユーザー関数/メソッドは合成名 `pf<idx>`＋index→キャッシュ `LLVMValueRef`（マングル不要・LLVM モジュールは自己完結）。`c.locals` 非投入なので env に locKind/locStructIdx を持たせて型判定（typeOf は局所に効かない）。
- **narrowing `as` 不在**ゆえ LLVM API の count/index/aggregate-index 系 U32 パラメータは**バインディングで U64 宣言**（LP64 で安全）。
- **match payload bind はフィールド名で punning**＝`val x` は「フィールド x を束縛」・別名は `field: val local`（`val fbase` で非存在フィールドを束縛しエラーになりやすい）。
- **aggregate（struct/enum/array）に icmp/extractvalue を非 aggregate へ誤適用すると LLVM builder が SEGV**＝必ず `LLVMGetTypeKind==10/exprIsArray` でガード。LLVMValueRef の null sentinel は kind 不可＝`LLVMIsNull` を使う。
- **array は `{ptr,i64}`** で element-size generic runtime（typed GEP・`LLVMSizeOf`）。配列リテラルは elemTy をリテラルからでなく**束縛/param の annotation から**取る（i64 デフォルト混入を防ぐ）。inout param/self は alloca せず**ポインタ param を locPtr 直結**。
- **メソッド emission をエントリモジュール限定にしないと std メソッド本体（未対応構文だらけ）を引き込んで死ぬ**（call-graph 到達可能性で必要な std だけ遅延 emit＝`ensureProvidedDeclared`/`ensureGenMethodDeclared`/`ensureFreeFnDeclared`）。primitive lang-item（I64/String 等）は extern struct として c.structs に居るので nested-struct 判定で extern を除外。
- **⚠ alloca は全て entry ブロックへ**（`beginFnBody`＝`entry`→`br body0`、`entryAlloca`＝entry の terminator 直前へ挿入して builder 復帰）。builder 位置で alloca を吐くと loop body 内で反復ごとに stack が積もり大入力 SEGV（clang は entry へ hoist するので C から来ると起きない罠）。
- **⚠ inline enum payload のサイズ**：`fieldWords` は enum 型フィールドを `1 + enumPayloadWords(eid)` words と数える（`{i64 tag,[maxWords] payload}`）。1 word と過小だと大 variant 構築で隣接破壊（heap 状態依存の miscompile）。
- **checked 算術床**：add/sub/mul/div/rem/neg は生 IR op でなく runtime helper `plew_<w><Op>`（i8-i64 符号別・本体は `__builtin_*_overflow`＋div-zero/INT_MIN ガード〔旧 C backend の `emitIntRuntime` と同形〕・external linkage）経由＝overflow/0除算で loud panic。`buildBinOpS` は wrapping 床として温存（`wrapping*` 専用）。
- **`extern(c)` 不透明ハンドル型**（`type LLVMTypeRef`＝`StructDef.isCExtern`）は `llvmScalarTy` でも `ptr` に落とす（i64 既定だと `LLVMTypeRef` を返す user 関数が `define i64`＋`ret ptr` で invalid IR・コンパイラ自身（`_.pw`）の self-compile で露呈）。
- **gen モード（`plew gen`）**：fn emission ループで `c.genMode` 時は `genMainIdx`（合成 harness main）だけを main 扱いし、ユーザー自身の dead main（マクロ生成関数を呼ぶ）を完全スキップ。
- **検証配置の罠**：種ビルド binary は **std の 1 つ上**に置く（`computeStdRoot`＝binary dir＋`std/`）。

### 受理検査の共有パス（`Codegen/Verify.pw`）

- **検査は emitter のローカル表 `c.locals` に依存**ゆえ、独立 verify パスでも genFunc 同等に再構築必須（self 環境/curRet/param locals＋ブロックスコープ `scopeMark`/`popLocals`＋Let/For/Match-arm で `addLocal`）。
- **演算子witness 検査は `hasCompareWitness`/`hasBinTraitWitness` ガードを先に**（`binTraitNeedsTrait` はスカラ算術に常に true＝「witness 必須」の意・単独で呼ぶと valid 算術を誤 reject）。
- **match-arm bind は scrut の型で generic grounding**（`genericFieldTypeInfo`/`genericEnumFieldTypeInfo`・`Box[I32]{val v}` の v を I32 にする）。
- **move 解析は分岐入口で `c.curBranchBase=scopeMark()`**（conditional-move 検出＝`localIndexByName < curBranchBase`）。
- **verify は型回復後（`buildExprTyTable` の後＝runFrontend 末尾）で呼ぶ**（演算子/visibility が型を要する）。**async fn は除外**（`return n` が Promise 中身型を返す＝verify の `retStart` 文脈と不整合になるため）。

## ビルド・テスト・機能追加手順

- **ビルド（self-host）**：`./bootstrap.sh`＝IR 種 `compiler/plewc.seed.ll`＋`compiler/plewc.seed.runtime.c`→clang＋libLLVM→`plewc0`→`_.pw` 自己コンパイル→IR 不動点 cmp（Rust 不要）。`./bootstrap.sh --reseed` で種更新（→ 種 `.ll`/`.runtime.c`＋追跡バイナリ `compiler/plewc` を commit）。編集中の高速反復は `./dev-rebuild.sh`（現 `compiler/plewc` が src を再コンパイルして自分をその場上書き）。**⚠ dev-rebuild は前回ビルドの plewc を使う**ので、miscompile を疑うときや verify の誤 reject で自己再ビルド不能なときは `./bootstrap.sh`（種から clean）で切り分け。**libLLVM がビルド必須依存**（IR 種は libLLVM の版に結合＝大改版で要 `--reseed`）。
- **テスト**：`./test.sh`（run/panic/reject/part＋不動点・メモリは `ASAN=1`〔macOS の ASan は leak 非対応〕）／`./test-gen.sh`（メタプロ gen/genreject）。reject は loud reject の SKIP マスクなし＝run/panic/part での reject も失敗扱い（単一 backend ゆえ skip 無し）。
- **メタプロ生成**：`./plew-gen.sh <file.pw>`＝`plewc --gen <file>`→clang＋libLLVM→run > `<file>.gen.pw`（`@[...]` 付きファイルに derive を走らせ生成 part を吐く・コミットする・通常ビルドが auto-part）。
- **機能追加＝ADD→reseed→USE**：新機能を plewc.pw の**ソースで使う**には ①`compiler/src/`（または `compiler/std/`）に足す→②`--reseed` で種更新→③ソースで使う。「ソースが使う機能は常にひとつ前のコンパイラがサポート済み」を守れば不動点は壊れない。**codegen 出力変化・AST フィールド追加・新 preamble 行は reseed 2 回**、**codegen 出力を変えない検査追加は reseed 1 回**。
- **AST フィールド追加のコツ**：`val isPub: Bool = false` とデフォルトを付けると既存の構築点が省略でそのまま通る。**arena Expr/AST バリアント追加**は exhaustive な `match` 全箇所（共有 `@Std/Syntax` の `ExprAst`/`StmtAst` は `Codegen/Lower.pw` の `lowerExpr`/`lowerStmt` が唯一の exhaustive match）にケース追加が要り、AST enum へのバリアント追加は codegen 出力変化＝reseed 2 回。
- **⚠ コンパイラは `@Std/Io`→`@Std/Core`／`@Std/Syntax`／`Prelude` を import** するので、これらも「コンパイラ自身がコンパイルするソース」。種がまだ受理しない構文を std で使うと bootstrap が即壊れる＝機能を先に種へ焼く。表現スワップ等の大変更は seam（intrinsic 境界）で担保（→ [array-struct-plan.md](array-struct-plan.md)）。

## 運用メモ

- 動作する区切りで**記述的 git タグ**。コミットメッセージは英語＋`Co-Authored-By`。GPG 署名（`--no-gpg-sign` を使わない・たまに pinentry タイムアウト＝再実行で通る／詰まったら手元で `echo test | gpg --clearsign` でパスフレーズをキャッシュ／コミットメッセージにバッククォートを書くと zsh がコマンド置換するので避ける・`-F` でファイル渡し）。
- scratch は repo 直下の `tmp/`（gitignore 済）に置く。直接コマンドに `rm` を書くと毎回確認が出るので、cleanup はテストスクリプトに内包して呼ぶ。
- 不要になった実装は削除し、必要なら git tag から復旧（例：`git checkout stage0-final -- bootstrap` で Rust stage0）。
- 言語表面の決定は spec（正典）＋claude/ に即同期し、grep で陳腐化を点検。
