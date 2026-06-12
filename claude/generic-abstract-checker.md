# Generic 本体の abstract checker（Rust 流・宣言時 bound-aware 型検査）

**決定（2026-06-12・Koji）／実装＝完了。** generic 関数・メソッド・trait provided-method の本体は、**宣言時に一度だけ abstract に型検査する**（Rust 流）。型パラメータ `T` は**不透明な型**で、`T` にできる操作は **`where T: Trait` bound が提供する capability のみ**。bound が正当化しない操作（メソッド・演算子・比較・field/index・concrete 位置への流入）は **instance ではなく定義地点でエラー**にする。

> なぜ：Plew の拠り所「意味は唱えた通り／曖昧はエラー」に沿う。dead な generic でも本体の型エラーを宣言時に loud に弾く＝C++ template の「使うまでエラーが出ない」を避ける。単相化（codegen）は従来どおりで独立（Rust も abstract 検査＋単相化を両立）。

## なぜ per-instance／template-全 verify を採らなかったか（実証済み・却下案）

- **per-instance**（インスタンスを置換 env で検査）は **instantiate されないものを一切検査しない**のが原理的限界（dead generic の concrete エラーが漏れる）。
- **template を「型パラメータを lenient に通す」全 verify** は **false-reject と soundness 緩めをトレードするだけ**。2026-06-12 の診断で `checkLitTi` に type-param skip を足して generic-function verify を有効化→**5 regression**（3 false-reject＋2 weakening＝type-param skip が広すぎ既存検査を緩めた）と確認し revert。
- よって **bound から capability を導く abstract checker** が唯一の筋。

## 採用した形（要点）

- 実装の中核＝`Codegen/Check.pw` の `checkGenericBodies`（Driver から）→ `checkBoundsExpr/Stmt/Block`。`isTypeParamOf(c, fnIdx, …)` は**関数スコープの**型パラメータ判定（global な `isTypeParamName` ではない）。bound は `c.funcBounds`（`FuncBound`）に格納し `boundProvidesMethod`/`traitProvidesMember`（supertrait＋provided method 込み）で解決。
- **entry-module gate が肝**：std/prelude の generic 本体は **trusted で除外**し、**user module 0 の generic body だけ厳格**に検査する。これで「コンパイラ自身が generic を多用」による false-reject（`Array.get` の `arrayGet(self,i)` を inferType が要素 `T` でなく `Array` と回復する癖など）を避けつつ user code を検査できる。`verifyProgram` と同じ gate。
- **trait provided-method**：非 dead は準拠型へのコピーを `verifyProgram` が検査。dead（準拠型ゼロ）も `checkGenericBodies` が entry-module の provided-method を walk。**`Self` を abstract 型扱い**＝`self.notAReq()` を `traitProvidesMember` で reject・`return self`→`->I64` 等の Self strict 同一性・`self.req()` の結果型回復。

## 残（additive・deferred）

- **関連型 `T::Item`**：型パラメータの結果に対するチェーン呼び（receiver が型パラメータの結果）は unchecked に degrade。abstract な `T::Item` 解決が要る（concrete では不要ゆえ低優先）。
