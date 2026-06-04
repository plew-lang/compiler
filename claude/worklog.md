# 作業ログ

> 現在地・次の一歩・運用メモだけを置く。完了した「やった」は git 履歴へ（記述的タグで辿れる）。「なぜ」は [design-decisions.md](design-decisions.md)、「パイプライン設計」は [architecture.md](architecture.md)、「spec からの意図的剥離・暫定の仮決め」は [provisional.md](provisional.md)。

## 現在地

🎉 **セルフホスト達成・stage0（Rust）退役済み。** 正典コンパイラ＝Plew パッケージ `compiler/src/`（root `_.pw` が `part` で全パートを綴じ込む 1 モジュール＝`Loader`・`Lexer`・`Ast`・`Parser/`〔Expr/Stmt/Decl〕・`Codegen/`〔Emit/Resolve/Ops/Check/Expr/Stmt/Decl/Mono/Array〕・part はサブディレクトリ可）。自分自身を不動点までコンパイルする。

意味論の hidden-meaning（整数幅・match 網羅・ラベル・診断・受理の健全性チェック・値意味論/CoW・`unique`/`deinit`/move・generics・トレイト step 1＋Eq/Ord＋derive・クロージャ）は概ね解消済み。**残っている剥離（実装済/未実装の現況）はすべて [provisional.md](provisional.md) が正典**（このログには個別バグ/完了項目を溜めない）。

## 次の一歩＝イベントループ（async/await/Promise・最大の残）

**方式は B＝stackless ステートマシン**（Node/V8 と同じ・colored async）に確定。**native-C 先行**で意味論（suspend/resume・drain 順・ARC across await）を固め、その後 WASM（Asyncify/JSPI）。**A＝スタックフルは却下**（Node を範とすると終着点が B・A は async fn ローワリング〔難所〕を作り直す中継ぎになる）。根拠・却下案は [design-decisions.md](design-decisions.md)「async fn のローワリング」。

土台は揃っている：関数値＝fat closure＋leak-free キャプチャ（不変値＋スカラー `mut val` 参照）・ARC・generics（`Promise[T]` 用）・`try`/`Result`/`Optional`。タスク＝`()->()` 閉包/フレームで表現でき `any` 不要。

増分の切り方（最小サブセットから additive に）：
1. `async fn`/`await`/`Promise[T]` の言語表面（lexer→parser→型）＋**単一中断点**のステートマシン化（await をまたぐ live local だけフレーム構造体へ昇格・`await` で `state=N`／フレーム退避／PENDING return・resume は `switch(state)`）。
2. イベントループ（タスクキュー＋drain）＋ `async fn main`＋ タイマ 1 本（`sleep(ms)` 相当）＝**最小マイルストン**（遅延 2 タスクが期日順に発火するゴールデンテスト）。
3. await-in-loop / await-in-branch / await-in-match / 複数中断点へ拡張。
4. `spawn`＝実スレッド（pthread・境界で CoW 値を eager 実体化・`Ref` は越えられない）・`JoinHandle[T]`/`join()->Promise[T]`。ここで closure の残ギャップ（`mut val` 非スカラー箱化・`mut val` 参照キャプチャ閉包の `local` マーク）を回収（単一スレッド async では Ref 可ゆえ async 段では不要）。

## ロードマップ（残りの大物・前向きのみ）

1. 🔄 **イベントループ**（上記・最大・着手対象）。
2. 🔲 **関連型＋Iterator/Iterable**（`for` 脱糖の正式化・`where T: Iterator` の `it.next()->Optional[T.Item]`・提供メソッド map/filter…）。署名は core-lib。
3. 🔲 **Hash/Hasher → Dictionary（`[k:v]` lang item）/Set**（Hash 後）。
4. 🔲 **`any P` 存在型**（トレイトの重い尻尾＝最後・型消去・動的ディスパッチ）。
5. 🔲 **メタプログラミング**（`Derive`・コード生成・spec 上も最後）。

横断 additive：演算子トレイト全配線（Eq/Ord 以外・需要駆動）・I2（import の with ゲート＝可視性検査・今は全フラット）・S2（@Std I/O の実シグネチャ）・循環回収（Ref グラフ限定サイクルコレクタ）。詳細は [provisional.md](provisional.md)。

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
