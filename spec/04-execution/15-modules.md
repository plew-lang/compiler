# モジュールシステム

## モジュールとトップレベル

Plew のすべての定義は、いずれかのモジュール（**1 ファイル = 1 モジュール**、`.pw`）の**トップレベル**に属します。モジュールの外に置く定義や、どこからでも見える**グローバル名前空間は存在しません** ── 他モジュールの名前を使うには必ず `import` し、出どころが常に辿れます。

トップレベルに書けるもの：

- **型・トレイト・関数**（`struct` / `enum` / `trait` / `fn`）。型に属さない関数はトップレベル関数として書きます（インスタンス非依存の処理はこれで足ります。型名で呼びたいものは [`assoc fn`](../02-type-system/07-methods-impl.md)）。
- **トップレベル変数**：不変の `val`（定数）と可変の `mut val`。プロセス全体で生きるモジュールレベルの状態です。

```plew
val MAX_RETRY: I32 = 3          // トップレベル定数
mut val request_count = 0       // トップレベル可変変数
```

トップレベル可変変数も持てます。[`spawn`](14-concurrency.md) ではキャプチャが不変になる（spawn 内から書き換え不可）ので spawn 外のコードはロック不要ですが、可変なトップレベル状態を spawn 間で共有して競合させるのは非推奨です（[メモリ管理と並行安全性](14-concurrency.md#メモリ管理と並行安全性)）。

## インポート

```plew
import @ExternalPackage               // 外部パッケージ
import ./LocalModule                 // ローカルモジュール
import ../ParentModule as Parent     // エイリアス付きインポート
import SomeModule with { Type1, function1 as func1 }  // 選択的インポート

// パス表現
import ../../../Utils    // 相対パス
import ./Src/Components  // 相対パス
```

### 束縛のされ方

- `import ./Foo` — モジュールを**名前空間 `Foo`** として束縛し、`Foo.Bar` でアクセス。
- `import ./Foo as F` — 名前空間を `F` に。
- `import ./Foo with { Bar, Baz as Q }` — 選択したものを**フラットに**現スコープへ（`as` で別名可）。
- `import ./Foo with *` — 公開物を**全てフラットに**取り込む。

### ファイル名・ディレクトリ名の制約

パスコンポーネント（ファイル名・ディレクトリ名）は以下の制約があります：

- **PascalCase** でなければならない（例: `MyModule`, `Utils`, `Components`）
- **`.`** （現在のディレクトリ）と **`..`** （親ディレクトリ）は例外として使用可能
- **`_`**（アンダースコア単体）も例外。ディレクトリの代表ファイル `_.pw` 専用に予約（下記「ディレクトリパスの解決」参照）

```plew
import ./MyModule        // ✅ OK: PascalCase
import ../ParentModule   // ✅ OK: PascalCase  
import ./my_module       // ❌ エラー: snake_case は不可
import ./123Module       // ❌ エラー: 数字から始まる名前は不可
import ./kebab-case      // ❌ エラー: ハイフンは使用不可
```

## エクスポート

宣言に `export` を付けると、そのモジュールの公開物になります。

```plew
export struct PublicStruct { /* ... */ }
export fn public_function() { /* ... */ }
export trait PublicTrait { /* ... */ }
export val PUBLIC_CONST: I32 = 100   // トップレベル定数も公開できる
```

### 再エクスポート

他モジュールのものを自モジュールの公開物として転送するには、`import` を付けずに `export <path>` と書きます。`import` と違い**ローカルには束縛しません**（純粋な転送）。同じものをローカルでも使いたいときは `import` 行を別に書きます。

```plew
export ./Models with { User, Post as Article }  // 選択して再エクスポート（別名可）
export @Json with { encode, decode }            // 外部パッケージのものも
export ./Models with *                          // 公開物を全てフラットに再エクスポート
export ./Models                                 // 名前空間 Models ごと再エクスポート
```

公開 API をまとめる「バレル」モジュールはこの再エクスポートで組み立てます。

## part — モジュールの分割

1 つのモジュールを複数ファイルに分割するには `part` を宣言します。`part ./File` は `File` を**このモジュールに綴じ込む**ことを意味します（別モジュールを*参照*する `import` とは別物です）。

```plew
// X.pw（モジュールのルート）
struct X { /* ... */ }

part ./ImplA
part ./ImplB
```

```plew
// ImplA.pw
part ./ImplC   // part はネストできる
part ./ImplD

impl X as SomeTrait { /* ... */ }
```

- **モジュール = ルート + 推移的な part 全体**。`X.pw` から `part` で辿れる全ファイル（`ImplA`〜`ImplD`）が 1 つのモジュールを成す。ネストは宣言の便宜で、membership はフラット（全員が同格の一員）。
- **片側宣言**。part される側（`ImplA` 等）には何も書かない。Dart の `part of` のような相互宣言は不要。
- **part 先は独立 import 不可**。`import ./ImplA` はエラー（モジュールのルート `X` を import する）。外部に見えるのはルートだけで、part ファイルはモジュールの内部実装。
- **forest 制約**。1 ファイルは高々 1 つの親にしか part されない（2 つの親から part されるとエラー）。循環は不可。
- **モジュール内はスコープ共有**。同一モジュールのファイルどうしは互いを `import` せずに参照できる（`ImplA.pw` は `struct X` をそのまま使える）。暗黙の可視性はこの「明示的に綴じたツリー」の内側だけに限定される。
- **外部依存の import はファイルごと**。共有スコープでも、別モジュールから持ち込む名前は各ファイルが自分で `import` する（ルートの import を子が暗黙継承しない）。外部由来の名前の出どころは常にそのファイルで見える。
- **ディレクトリは跨いでよい**。`part` は相対ファイルパスで、ディレクトリはモジュールの単位ではなく単なる整理。

### import の対象はモジュールのルート

`import ./X` はモジュール `X`（ルートファイル `X.pw`）を参照し、ツリー全体の `export` と、ツリー内に書かれた impl をまとめて取り込みます。

### ディレクトリパスの解決（`_.pw`）

`import` / `part` のパスがディレクトリを指すとき、そのディレクトリ内の `_.pw` に解決されます。`_.pw` は**ディレクトリ全体をモジュール化するものではなく**、ただの単一ファイルモジュールです。効果は「ディレクトリパスで `import` / `part` できる」というだけで、同じディレクトリの他のファイルとは無関係です。

```plew
import ./Models        // Models/_.pw に解決される
import ./Models/User   // Models/User.pw（こちらは別モジュール）
```

- 解決順：`X.pw`（ファイル）があればそれ。無く `X/` が `X/_.pw` を持てばそれ。両方あればエラー。`X/` に `_.pw` が無ければ `X/` は単なる整理用フォルダ（モジュールではない）。
- `Models/_.pw` と `Models/User.pw` は**別モジュール**。`_.pw` は隣接ファイルを取り込まない。`Models/_.pw` が `Models/User.pw` を自分のモジュールに含めたいなら、明示的に `part ./User` と書く。
- `part ./Models` も同様に `Models/_.pw` に解決される。
- **単一ファイル → ディレクトリ化で import パスが不変**：`Models.pw` を `Models/_.pw` に移すだけで `import ./Models` はそのまま。

### 無名 impl の配置

拡張を使わない無名の `impl T as Tr` は、**T を定義したモジュール**の中にしか書けません（コヒーレンスのため。Rust の「型 or トレイト所有」より厳格な**型所有**版）。

- モジュール内（part ツリー内）ならどのファイルに置いてもよい。同一モジュールに同じ無名 impl が二重に現れればコンパイルエラー。
- **外部型（他モジュール定義）への実装は、トレイトの所有を問わず無名では書けず、[拡張](../02-type-system/09-extensions.md)（`#Ext`）を使う**（自分のトレイトを外部型に実装する場合も拡張）。
- モジュールを import すると、その型と**その無名 impl が一緒に**入る（impl だけを個別に import する手段は無い）。

## パッケージ

パッケージは **TOML マニフェスト**（暫定名 `Plew.toml`）を持つディレクトリです。マニフェストに依存を記述し、依存は **git リポジトリ または ローカルパス**で指定します（中央レジストリは持たない＝ Go modules / SwiftPM と同じ分散思想）。

### 依存とローカル名

依存はマニフェストで**ローカル名**に束縛し、コードからはその名前で `import @Name` します。

```toml
# 暫定形式
[dependencies]
Json  = { git = "https://example.com/json.git", tag = "v1.2.0" }
Utils = { path = "../Utils" }
```

```plew
import @Json with { encode }
import @Utils
```

- ローカル名は消費側が決めるので、**上流パッケージの名前衝突はローカル名で解決**できる（同名の依存に別ローカル名を振る）。
- 推移依存で同一パッケージの複数バージョンが現れた場合は **共存を許す方針**（依存解決の詳細は別途）。

### 公開エントリと外部到達

- `import @Foo` は Foo パッケージの**公開エントリ**に解決される。デフォルトは **`src/_.pw`**、マニフェストで上書き可。
- 外部からは**エントリの公開物だけ**が見える（エントリが再エクスポートで組んだ公開面）。内部ファイルへの直接到達（`@Foo/Internal` 等）はできない（カプセル化）。
- ソースは `lib/` と `bin/` のような分割をせず、すべて `src/` に置く。

### ビルド

実行エントリの規約は持たない。ビルドするファイルを明示する：

```sh
plew build ./src/entry.pw
```

## 外部コード統合

```plew
extern "c" {
    fn malloc(size: usize) -> *mut u8
    fn free(ptr: *mut u8)
}

extern "javascript" {
    fn console_log(message: String)
    val window: JsWindow
}
```

> **FFI の型マッピングは未策定です。** 上の `usize` / `*mut u8` は C 側の型を模した説明用の表記で、Plew の型体系（PascalCase・生ポインタ無し）との対応 ── 数値型の対応、ポインタ／バッファの受け渡し、文字列の境界変換、外部由来の `NaN` 流入の扱いなど ── は実装フェーズで定めます。
