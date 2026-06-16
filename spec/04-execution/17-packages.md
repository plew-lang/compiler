# パッケージ

パッケージは **TOML マニフェスト `Plew.toml`** を持つディレクトリです。`src/` 以下にソースを置き、依存・公開面・ネイティブ依存を宣言します。中央レジストリは持たず、依存は **git リポジトリ／ローカルパス**で解決します（Go modules / SwiftPM と同じ分散思想）。モジュール・`import`・`public` の意味論は [モジュールシステム](15-modules.md)、本章はその上の**パッケージ単位の配布・依存・ビルド**を定めます。

## マニフェスト（`Plew.toml`）

最低限は **4 項目**だけです：

```toml
name = "Http"             # パッケージ名（PascalCase・@Http 参照のデフォルト束縛名）
plew = "0.3"              # 要求する最低 Plew バージョン
public = ["_", "Server"]  # 公開モジュール（既定 ["_"]・→ モジュール章「パッケージ」）

[dependencies]            # 依存（下記）
```

- **version / license / repository / description は持ちません**。それぞれ唯一の真実源を参照します ── version は **git tag**、license は `LICENSE` ファイル、repository は git remote、description は `README`。マニフェストに重複させない（単一真実源・DRY）。
- `name` は**グローバル一意 ID ではなく、消費側が `@Http` で参照するデフォルトの束縛名**です。パッケージの同一性の基礎は依存指定の git URL（衝突は消費側のローカル名で解決 → [モジュール章](15-modules.md#依存とローカル名)）。
- `public` の意味論（公開モジュール・既定 `["_"]`・封印 `[]`）は → [モジュール章「パッケージ」](15-modules.md#公開モジュールと外部到達)。

## 依存（`dependencies`）

依存は **git リポジトリ URL の配列**です。最低限は URL のみ：

```toml
dependencies = [
    "https://github.com/foo/http.git",                          # これだけで可
    { git = "https://github.com/bar/json.git", version = "3" }, # 制約する時だけ table
    { git = "https://github.com/x/db.git",    rev = "abc123ef" },# commit 固定
    { git = "https://github.com/x/edge.git",  branch = "main" }, # branch 追跡
    { path = "../local-lib" },                                  # ローカルパス
    { git = "https://github.com/y/z.git",     as = "MyZ" },     # 束縛名を rename
]
```

- **束縛名は依存先マニフェストの `name` から自動**で決まります（`@Http` 等）。衝突する時だけ `as` で rename します。これにより**消費側は URL だけ書けば束縛名もバージョンも要りません**。
- 指定は `git` に対して `version` / `tag` / `rev` / `branch` の**いずれか 1 つ**、または `path` 単独です。複数併記はエラー（曖昧はエラー）。
- **`.git` は省略しません**（git リポジトリ URL を明示）。**短縮形は持ちません** ── レジストリ前提の裸バージョン（`"3" だけ`）も、ホスト短縮（`foo/http`）も無し。URL/path が常に可視で出どころが分かること（provenance）を優先します。

### バージョン指定（桁数モデル）

git tag を semver として解釈します。**書いた桁が固定・書かない桁は最新**という桁数モデルです（`^`/`~`/`=` 演算子は使いません）：

| 指定 | 解決される範囲 | 意味 |
|---|---|---|
| なし | 制約なし | メジャーも自動更新（最新追従） |
| `"3"` | `>=3.0.0, <4.0.0` | メジャー固定・マイナー以下を更新 |
| `"3.2"` | `>=3.2.0, <3.3.0` | マイナー固定・パッチを更新 |
| `"3.2.1"` | `=3.2.1` | 完全固定 |

- tag に **`v` は付けません**（`1.2.0`・semver 仕様に忠実。git tag 慣習の `v1.2.0` 対応は当面なし・将来 additive 可）。
- **0.x を特別扱いしません**：`"0"` は 0.x 全体追従（破壊的変更の取り込みは自己責任）、`"0.3"` はマイナー固定（`>=0.3.0, <0.4.0`）。
- **下限と範囲を独立に指定する形（`>=3.2.5, <3.3.0` 等）は持ちません**（桁数モデルのみ・必要になれば将来 additive）。

## 依存解決

- **制約内の最新を選びます**（newest-compatible）。最新を取りに行くので、再現性は下記のロックファイルで固定します。
- **複数バージョン共存**：同じメジャー範囲の複数要求は**最新 1 つに統合**します。**メジャー違いの要求は両方を共存ビルド**します（A が `B v1`・C が `B v2` を要求しても両立＝依存地獄の回避）。ただし：
  - **`@Std`・言語アイテム・コアトレイトは単一版必須**です（`Array`/`Eq` 等が複数版あると型システムが壊れる）。
  - **異なるバージョンの同名型を API 境界で晒すと別型として扱われ、コンパイルエラー**になります（hidden にしない）。共存が安全なのは、型・トレイトを境界で晒さないライブラリです。
- **間接依存は import できません（phantom dependency の禁止）**：パッケージ内のコードが `import @Name` できるのは、**自身の `dependencies` に書いた直接依存と `@Std` のみ**です。推移依存はビルドには使われますが import できません（依存先が `export` で再公開した面を経由する場合を除く）。`dependencies` に無い `@Name` の import はコンパイルエラーです。

## ロックファイル（`Plew.lock`）

- 解決結果（**git URL + 確定 commit + content hash**）を固定し、再現ビルドを保証します。
- **ライブラリ・アプリともコミット推奨**です。ただし **lock が効くのはトップレベル（ビルド対象）のみ** ── 依存ライブラリ同梱の lock は**無視**され、利用側は依存の**制約（マニフェスト）だけ**を見て自分のグラフを再解決し、自分の lock を書きます。
- バージョンの更新は **`update` コマンドで明示的に**行います（ビルドが暗黙に上げることはしない）。

## 配布とビルド（ソース配布＋消費側ビルド＋キャッシュ）

- 配布物は **Plew ソース**です（precompiled lib のリンクは一次手段にしない）。
- ビルドは**消費側の `plewc` が fetch 済みソースから whole-program** で行います。
- 速度は **content-addressed なビルドキャッシュ**（`source hash × compiler version × target × flags` でキー）で回収します（hidden cost は可・hidden meaning は不可）。
- 実行可能ビルドのエントリ選択は → [モジュール章「ビルド」](15-modules.md#ビルド)。

## ネイティブ依存（C / Rust / system ライブラリ）

ネイティブ依存は **`Plew.toml` の宣言一本**で表します。**ビルドスクリプト（`build.rs`/`build.zig` 的な任意コード）は持ちません** ── ビルド時に第三者コードが走らない（Go 流のサプライチェーン姿勢）。Plew 本体が宣言を読んで、祝福した既知ツール（clang/cargo）を決まった作法で実行します。

```toml
[native.sqlite]
c = { sources = ["native/sqlite3.c"], include = ["native/"] }
link = "static"

[native.mycrypto]
rust = { crate = "rust/mycrypto", features = ["std"] }
link = "static"

[native.llvm]
pkg-config = "llvm"          # system ライブラリのリンク

[native.mycrypto.target.wasm32]
unsupported = true           # ターゲット別の上書き／封印
```

- **C/C++・Rust・pkg-config を祝福**（名指しサポート）します。これ以外のネイティブ依存（cmake の巨大プロジェクト・Go 等）は **プリビルドバンドル**（最終手段・検証不可とターゲットマトリクスは作者責任）で取り込みます。
- **任意コマンド実行を持たない**ことで、Plew が起動するのは clang/cargo だけと分かり、サンドボックスのポリシーが書けます（任意コマンドのサンドボックスは原理的に困難＝SwiftPM も自動ビルドから締め出している）。
- **C は実行が決定的・ネット不要・隔離容易**です。**Rust は cargo がネット（依存解決）と crate 側の `build.rs`（任意コード）を内包**するため：
  - **fetch（ネット・content hash 検証）と build（`cargo --offline`・隔離可能）を分離**します。
  - crate 側 `build.rs` の信頼は Rust エコシステムに委ねます（Plew は cargo プロセスを OS レベルで包むところまで）。
  - 消費側に Rust ツールチェーンが要ります。**`Plew.lock` に「この依存は cargo ビルド＝ビルド時にホストでコード実行」を記録**し、初回はユーザー承認を求めます（provenance）。
- 言語側の `extern(c)` 構文（型マッピング・`CPtr`・`repr(c)`）は → [モジュール章「外部コード統合」](15-modules.md#外部コード統合externc-ffi)。本章はその**リンク／ビルドの宣言**を担います。

## 越境メタプログラミング

依存が公開する `Derive` を消費側の型に当てる場合も `.gen.pw` コミットモデル（生成は当てる型を持つ**消費側**で起き `.gen.pw` を消費側にコミット・`@Std/Syntax` は各 derive の依存版で隔離実行・derive はホスト実行）を使います。複数バージョン共存と String 境界で両立します。→ [メタプログラミング](16-metaprogramming.md)。
