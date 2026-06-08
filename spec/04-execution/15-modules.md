# モジュールシステム

## モジュールとトップレベル

Plew のすべての定義は、いずれかのモジュール（**1 ファイル = 1 モジュール**、`.pw`）の**トップレベル**に属します。**ユーザーがグローバル（ambient）な定義 ── どこからでも `import` 無しに見える名前 ── を作る手段はありません**。他モジュールの名前を使うには必ず `import` し、出どころが常に辿れます（唯一 ambient なのは言語自身が提供する[言語アイテム](#言語アイテムは常にスコープにあるimport-不要)で、そこにユーザーは足せません）。

トップレベルに書けるもの：

- **型・トレイト・関数**（`struct` / `enum` / `trait` / `fn`）。型に属さない関数はトップレベル関数として書きます（インスタンス非依存の処理はこれで足ります。型名で呼びたいものは [`assoc fn`](../02-type-system/07-methods-impl.md)）。
- **トップレベル変数**：不変の `val`（定数）と可変の `mut val`。プロセス全体で生きるモジュールレベルの状態です。

```plew
val maxRetry: I32 = 3          // トップレベル定数
mut val requestCount = 0       // トップレベル可変変数
```

トップレベル可変変数も持てます。値意味論なので、[`spawn`](14-concurrency.md) はトップレベルのコピー可能な値を**コピー（スナップショット）でキャプチャ**し、spawn 外の状態を書き換えられません（`Ref` は spawn を越えられない）。よってスレッド間に共有可変が生まれず、ロックも不要です（→ [並行安全性](14-concurrency.md#並行安全性--実質-race-free)）。

### トップレベル初期化と実行順序

トップレベル `val`/`mut val`・`export val`・[`assoc val`](../02-type-system/07-methods-impl.md)（型の静的値）は、**プログラム起動時に eager に初期化**されます。`main` 本体が動き始める前に、すべて初期化済みであることが保証されます（Swift/Rust のような「初回アクセス時の遅延初期化」ではない ── いつ走るか読めない非直感を持ち込まない）。初期化子は const に限らず**任意の実行時式**を書けます（関数呼び出し・I/O・[JSX 生成](../02-type-system/05-structs-enums.md) など）。

**順序は依存順（force-on-read）**。静的な依存解析は持たず、各トップレベル値を「**memoize されたサンク**」として扱います。値には *未初期化 / 初期化中 / 初期化済み* の状態があり、起動時に全値を force します：

- 初期化済み → その値
- 未初期化 → 「初期化中」に印し、初期化子を実行。**その式が別のトップレベル値を読むと、その読み取りが相手を再帰的に force する** ── これだけで依存順が自動的に正しくなる（関数呼び出し越しの推移依存も、実行が辿るので静的解析不要）。
- 初期化中（への再入）→ **循環初期化。起動時に [`panic`](../03-expressions/11-control-flow.md#panic-と発散)**（関わった名前を診断に出す）。コンパイル時ではなく起動時のランタイムエラー。

値が「初期化済み」になって初めて値として読めるため、**半初期化状態は決して観測されません**（読めば必ず完全な値か、await か、循環 panic のいずれか）。

#### トップレベル await と並行初期化

**トップレベルはイベントループ上の async コンテキスト**です。したがって初期化子で [`await`](14-concurrency.md) でき、内部で [`spawn`](14-concurrency.md) してその `join()` を待つこともできます（config 取得・DB 接続・ウォームアップなどを起動時に書ける）。

起動は**全トップレベル値の force を並行に起動してから待ち合わせる**（`Promise.all` 相当）ため、**互いに依存しない非同期初期化子は待ち（I/O）が重なります**（単一スレッドなので並列計算ではなく待ちのオーバーラップ。真の並列計算は各初期化子内の `spawn`）。依存があるものは force-on-read の `await` で自動的に直列化されます。循環は async では「初期化中」への単純再入ではなく**待ち合わせの輪（デッドロック）**として検出し、起動時 panic にします。

> **同期プログラムは無税**：初期化子に `await` が一つも無ければ、起動は awaits ゼロで一気に走り切り、「`main` 前の同期初期化」と同じ挙動・同じ性能になります。async の仕組みは `await` を書いたときだけ起動します。

#### 順序保証の範囲（unspecified であって UB ではない）

Plew が**常に保証**するもの：①メモリ安全（半初期化を観測しない）②依存順（A が B を読むなら B は完全初期化後にのみ観測）③一回性（各値の初期化はちょうど 1 回）。

**保証しない**のは、互いに依存しない初期化子どうしの**副作用の相対順（interleave）**だけです。これは **unspecified（規定しない）であって undefined behavior（UB）ではありません** ── 各実行は妥当でメモリ安全で、特定順に依存できないだけ（JS の Promise スケジューリングや辞書の反復順と同じ性質）。I/O が絡まなければイベントループの FIFO で事実上 kickoff 順（宣言/import 順）に決まり、I/O 完了タイミングが絡むと前後し得ます。特定順が必要なら**明示的に依存を作る**（一方が他方を読む／`main` 内で順序付ける）こと ── スケジューリングに頼ってはいけません。

> モジュール跨ぎも force-on-read で自動順序化され、跨ぎ循環も起動時 panic で捕まります（`import` 循環の可否は初期化とは独立した別の規則）。

### 実行エントリ（`main`）

プログラムの命令的な開始点は **`fn main`** です。トップレベルは宣言と値初期化子（上記の依存グラフ）だけを置く場所で、**自由なトップレベル文は持ちません**（文の順序と force-on-read の初期化順が衝突しないように、命令的な開始点を `main` に分離する）。実行の段取りは **①全トップレベル/`assoc val` 初期化を完了 → ②`main` を呼ぶ** の 2 段です。

```plew
fn main() { … }                       // 同期
async fn main() { … }                 // await を使う（同期は無税の特殊ケース）
fn main() -> Result[(), AppError] {   // Result を返すと main 内で try が使える
    val cfg = try loadConfig()
    run(config: cfg)
    return <Result.Ok value=() />
}
```

- **`async` は任意**：`fn main` と `async fn main` の両方が valid。実行モデルは常にイベントループなので、同期 `main` は await ゼロの特殊ケース（[同期プログラムは無税](#トップレベル-await-と並行初期化)）。
- **戻り値は `()` か `Result[(), E]`**。`Result` を返すと **`main` 内で [`try`](../03-expressions/13-error-handling.md) が使え**、`Err` のときランタイムが**エラーを表示して非ゼロ終了**します（`Termination` 相当の lang トレイト経由）。明示的な終了コードは標準ライブラリの `Process.exit(code:)`（発散）。
- **引数・環境は `main` の仮引数では受け取らず、標準ライブラリ経由**で取ります（`import @Std/Process` して `Process.args() -> Array[String]`／`Process.env` 等）。`print`/`Random` と同じく「ambient なプロセス能力を import 越しに明示取得」する形に揃え、出どころを可視に保つ（`main` のシグネチャを単一にし、ランタイムが複数 main 形を魔法認識しなくて済む）。`Process` は lang item ではないので import が要る。
- **ランタイムの寿命**：`main` が返り、**かつイベントループが drain した**（保留タスク・タイマ・登録リスナ・未 join の [`spawn`](14-concurrency.md) スレッドがいずれも無い）ときにプロセスは終了します（Node/ブラウザと同じ）。よって UI アプリの `main` は「DOM にマウントして return」でよく、イベント待ちでループが生き続けます。CLI は仕事して return → ループ空 → 終了。サーバは listen して return → 接続待ちで生存。
- **`main` は実行可能ビルドのときだけ必須**。ライブラリ（他パッケージや JS から呼ぶ WASM）には `main` は不要で、export 面だけを晒します（→ [エクスポート](#エクスポート)）。

### 言語アイテムは常にスコープにある（import 不要）

「`import` 必須」の唯一の例外が**言語アイテム（lang item）**です。Plew はプリミティブ型を持たず `I32`/`String` も構造体ですが、**構文がその意味として参照する型は、`import` せずとも常にスコープにあります** ── キーワードと同格の「言語の語彙」だからです（`if` を `import` しないのと同じ）。**ambient なのは型だけで、トレイトは含めません**（理由は下記）。

- 数値型（`I8`…`U64`・`F32`/`F64`）・`Bool`・`String`・`Array`・`Dictionary`・`Optional`・`Result`・レンジ 2 型（`HalfOpenRange`/`ClosedRange`）・`Promise`・スレッドハンドル `JoinHandle`

これらは型注釈に `Optional[I32]`・`Array[T]`・`-> Promise[T]` と**名前を書く**から ambient である必要があり、`1`・`"x"`・`[1, 2]`・`[k: v]`・`a..<b` 等のリテラルが生む値の型でもあります。`()`（空の[ラベル付きタプル＝無名レコード](../01-basics/02-basic-types.md#ラベル付きタプル無名レコード)）は**構文そのもの**で名前を持つ言語アイテムではありません（`Unit` 型は存在しません）。

**トレイトは ambient に含めません。** `a + b`・`for`・`xs[i]`・`x?`・`a == b`・`xs.sort()` のように**トレイトに裏打ちされた機能を使う**とき、トレイト名は一度も解決されないからです：

- メソッド・演算子のバインドは「**レシーバの型 ＋ 有効な `#Ext`**」だけで決まり、import スコープに依存しません（→ [拡張](../02-type-system/09-extensions.md)）。
- 演算子・構文 → トレイトの対応（`+`↔`Add`、`for`↔`Iterable`/`Iterator`、`xs[i]`↔`Index`、`[k:v]` のキー境界↔`Hash` など）は**コンパイラ内部の固定脱糖表**で、名前空間の住人ではありません。`a + b` を書くモジュールが何も `import` していなくても動きます。

トレイト名を書く必要があるのは `where T: Add`・`any Iterator[Item=I32]`・`impl Add for MyVec` のように**自分でジェネリック/トレイト/impl を書く＝定義地点**だけで、そこでは他の名前と同じく `import` します（組み込みの演算子トレイトも標準ライブラリから `import`）。`xs.sort()` を**呼ぶ**側には波及しません ── `sort` 側の `where T: Ord` は定義地点に書いてあり、呼び出しは型に対して解決されるからです。

> なぜ型だけで足りるか：**使う側（use site）はディスパッチが型に対して起きるのでトレイト名を解決せず**、**名指す側（definition site）はジェネリック/impl を書く文脈なので `import` が自然**。よって「ambient ＝ 型のみ・トレイトは脱糖表＋名指し時 `import`」で sharp に閉じます。`From` が脱糖表にあるのに `import` で名指すのと、`TryFrom`（構文非参照）が普通の `import` なのは、ともに「名前空間に居るか」と「脱糖表に居るか」が独立だからです。

**固定された小さな一覧**で、**ここに無いものはすべて通常のライブラリ＝明示 `import` が要ります**（`Random`・`Set`・`print` などは `@Std/…` から import。`Set` はリテラルを持たず辞書 `Dictionary` と対照的で、構文が参照しない＝言語アイテムではない）。判定基準は「構文が参照するか」で sharp です。

> 言語アイテムは**言語が提供する唯一の ambient な名前**で、キーワードと同じくユーザーがこれに足したり別の ambient を作ったりはできません（自前定義は必ずモジュールスコープ）。出どころは「ローカル束縛 → ファイルの `import` → 言語アイテム」で常に辿れ、言語アイテム名はローカル再宣言（[shadowing](../01-basics/03-values.md#再宣言shadowing)）で覆えます。

## インポート

import のルートは **3 つ**で、**先頭の記号が出どころを表します**。bare 名（`import Foo`）は不可 ── 相対なのか外部なのか std なのかが記号で判らなくなるため、すべての import は `@`・`/`・`./`／`../` のいずれかで始まります。

| 記号 | 出どころ | 例 |
|---|---|---|
| `@…` | **自分の外**（標準ライブラリ or 外部依存） | `import @Std/Testing`, `import @Json` |
| `/…` | **自前・パッケージのルート起点**（絶対） | `import /Models/User`, `import /Utils` |
| `./` `../` | **自前・相対**（このファイルからの相対パス） | `import ./User`, `import ../Utils` |

`@` の直後の名前で std と外部を見分けます ── **`@Std` は標準ライブラリの予約名**（マニフェスト束縛不要・常に利用可）で、それ以外の `@Name` はマニフェストで束縛した外部依存（→ [パッケージ](#パッケージ)）。`/` は**自パッケージの `src/` ルートから**の絶対パス（→ [ルート起点の絶対パス](#ルート起点の絶対パス)）。`@` を「自分の外」、`/` を「自前・ルートから」、`./` を「自前・ここから」と読めば、行頭だけで provenance が確定します。

```plew
import @Std/Http                          // 標準ライブラリ（@Std は予約）
import @Json                              // 外部依存（マニフェストで束縛）
import @Json/Encode                       // 外部依存のサブモジュール
import /Models/User                       // 自パッケージの src/Models/User.pw（ルート起点）
import ./LocalModule                      // ローカルモジュール（このファイルから相対）
import ../ParentModule as Parent          // エイリアス付き
import ./Models with { User as Account }  // 選択的インポート
```

**サブパスは任意の深さ**で書けます（`@Std/Http/Server`・`@Dep/Foo/Bar`・`/Src/Components`）。`@…` でどのサブモジュールに到達できるかは**パッケージが公開宣言したものに限ります**（→ [公開モジュールと外部到達](#公開モジュールと外部到達)）。3 ルートとも解決規則は同一で、ディレクトリは `_.pw`（ルート）・サブパスは `/`（→ [ディレクトリパスの解決](#ディレクトリパスの解決_pw)）。

### ルート起点の絶対パス（`/`）

`/` は**自パッケージの `src/` ルート起点の絶対パス**です。`import /Models/User` は、どのファイルから書いても `src/Models/User.pw` を指します（`/` 単体はルート `src/_.pw`）。深いネストで `../../../` が積み上がるのを避けるための経路で、Rust の `crate::` に相当します。

- **リファクタ安定**。相対パス `../../` は *import する側*の位置をエンコードするので、どちらのファイルを動かしても壊れます。`/` は *ターゲットの同一性*（ルートからの位置）をエンコードするので、import する側を動かしても壊れません ── 出どころも `../../` より正直に固定されます（パッケージ公開パス `@A/Http` が実ファイルに一致するのと同じ Go 流の割り切りで、ターゲット側を動かせばパスは変わります）。
- **`public` ゲートは通らない**。`/` は自パッケージ内の参照なので、外部公開を絞る `public`（→ [公開モジュールと外部到達](#公開モジュールと外部到達)）とは無関係で、相対 `./`／`../` と同じく**自パッケージのどのモジュールにも届きます**。`/` と `./`／`../` の違いは「ルート絶対か・ファイル相対か」だけで、到達範囲は同じ。
- **運用指針**：**近接（兄弟・親子）は相対 `./`／`../`、遠隔・深いネストはルート絶対 `/`** を推奨します。両系統を持つのは Rust（`super::`／`crate::`）と同じで、近さに応じて読みやすい方を選べます。
- `import`／`export`／[`part`](#part--モジュールの分割) は経路文法を共有するので、`/` はいずれでも書けます（`part /Foo`・`export /Models with *`）。

### 束縛のされ方

- `import ./Foo` — モジュールを**名前空間 `Foo`**（パスの末尾要素）として束縛し、`Foo.Bar` でアクセス。`import @Std/Http` なら名前空間は `Http`。
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
import ./myModule       // ❌ エラー: camelCase は不可（パスは PascalCase）
import ./123Module       // ❌ エラー: 数字から始まる名前は不可
import ./kebab-case      // ❌ エラー: ハイフンは使用不可
```

## エクスポート

宣言に `export` を付けると、そのモジュールの公開物になります。

```plew
export struct PublicStruct { /* ... */ }
export fn publicFunction() { /* ... */ }
export trait PublicTrait { /* ... */ }
export val publicConst: I32 = 100   // トップレベル定数も公開できる
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

拡張を使わない無名の `impl T`／`impl T as Tr` は、**T を定義したモジュール**の中にしか書けません（コヒーレンスのため。Rust の「型 or トレイト所有」より厳格な**型所有**版）。**トレイト自身の提供メソッド `impl Trait { … }`** も同様に、**そのトレイトを定義したモジュール**の中にしか書けません（トレイト所有版・→ [トレイト](../02-type-system/08-traits.md)）。

- モジュール内（part ツリー内）ならどのファイルに置いてもよい。同一モジュールに同じ無名 impl が二重に現れればコンパイルエラー。
- **外部型（他モジュール定義）への実装は、トレイトの所有を問わず無名では書けず、[拡張](../02-type-system/09-extensions.md)（`#Ext`）を使う**（自分のトレイトを外部型に実装する場合も拡張）。
- モジュールを import すると、その型と**その無名 impl が一緒に**入る（impl だけを個別に import する手段は無い）。**どのメンバを外から触れるかは [メンバの可視性](../02-type-system/05-structs-enums.md#メンバの可視性)が決めます** ── impl ブロックは `pub impl` で公開・修飾なしで非公開、フィールドは `pub`/`pub(get)` で公開・修飾なしで非公開。`export` がモジュール境界（その型・関数・トレイトに到達できるか）を、`pub impl`/`pub` が型のカプセル化（到達した型のどのメンバを使えるか）を担う**直交した 2 軸**です。

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
- **`@Std` は予約名**で、標準ライブラリを指します。ローカル名に `Std` は使えず、マニフェストへの記述なしに常に `import @Std/…` できます（言語が公開集合を宣言済みのパッケージ＝唯一マニフェスト束縛不要の `@`）。

### 公開モジュールと外部到達

パッケージは**どのモジュールを外部に公開するか**をマニフェストの `public` で宣言します。**公開パスは実ファイルに一致**し（別名を付けない＝`@A/Http` ↔ パッケージ内 `Http.pw`）、宣言したものだけが外部から `import` できます。ソースは `lib/`・`bin/` のような分割をせず、すべて `src/` に置き、`public` のパスは `src/` 起点です。

```toml
name = "A"
public = ["_", "Http", "Json"]   # 実パス。_ はルート（src/_.pw）。既定は ["_"]
```

```plew
import @A           // ✅ ルート（src/_.pw）
import @A/Http      // ✅ public 宣言あり ↔ src/Http.pw（or src/Http/_.pw）
import @A/Internal  // ❌ public に無い＝内部実装（到達不可）
```

- **`_` はルートモジュール**（`src/_.pw`）。`public` の**既定値は `["_"]`** ── 単一モジュールパッケージは `public` を書かずに `import @A` だけで使えます（ceremony ゼロ・`@A/A` のような Dart 流の名前重複は起きない）。
- **`public = []` で何も公開しない**（内部／ツール専用パッケージ・封印）。`public = ["Http"]` なら**サブのみ公開**してルートを玄関にしない、も可。
- **公開パスは実ファイル**（rename しない）。「公開ファイルを動かす＝公開 API を変える」を正直に出す Go 流の割り切り。リファクタ安定のための別名公開（Node の `exports` 流）は将来 additive。
- **任意深さ可**：`public = ["Http/Server"]` で `@A/Http/Server` を公開。`public = ["Api/"]` のディレクトリ糖衣で subtree 一括公開できる（**既定は非公開**＝列挙外は内部実装）。
- **自前（`/`・`./`／`../`）とパッケージ `@…` は解決規則が同一**（`_.pw`＝ルート・`/`＝サブ）。違いは「外部パッケージのサブモジュールは `public` ゲートを通る」点だけ ── 所有境界での encapsulation を 1 段足したもの（ファイル→モジュールは [`part`](#part--モジュールの分割)、モジュール→モジュールは [`export`](#エクスポート)、プロジェクト→パッケージは `public`）。自パッケージ内の絶対パス `/` はこのゲートの内側なので `public` に縛られない（→ [ルート起点の絶対パス](#ルート起点の絶対パス)）。

### ビルド

**エントリは「ファイルを明示選択」＋「その中の `fn main` が開始点」**の 2 段で、プロジェクト全体から "the main" を自動探索したり `bin/` のような特別ディレクトリを設けたりはしません。実行可能ビルドは、名指ししたファイルが定義する [`main`](#実行エントリmain) をエントリにします：

```sh
plew build ./src/client.pw    # その file の fn main がエントリ（例：WASM 出力）
plew build ./src/server.pw    # 別エントリ＝別ターゲット（例：native 出力）
```

これにより**モノレポで複数エントリ**（クライアント／サーバ）が同じモデルモジュールを共有しつつ別々にビルドできます。`main` を持たないファイルはライブラリとしてビルドされ、`main` は不要です。

## テスト

テストは **`test` ブロック**で書きます。**関数ではありません** ── テストはプログラムとしての意味（戻り値・レシーバ）を持たず「走らせて検査する」だけなので、`fn` ではなく専用ブロックにします（Zig/D 流）。`test` は実行時の意味を持たない**宣言修飾的な語**で、`export`（リンケージを変えるが実行時意味ゼロ）と同類です。

```plew
test "parses an empty header" {
    val r = parseHeader(input~: "")
    expectEq(expected: <Header empty=true />, actual: r)
}
```

### 配置（モジュール直下／無名 impl 内）

`test` ブロックは**コンテナスコープの宣言**で、置ける場所は 2 つ。**テストに特権的な可視性は無く**、通常コードと同じ規則で「見たいものが見える位置」に置きます：

- **モジュール直下** ── 非 `export`（モジュール私的）の自由関数や公開 API を試験。
- **無名 `impl` の中** ── その型の**非 [`pub`](../02-type-system/05-structs-enums.md#メンバの可視性) メンバ**を白箱で試験（無名 impl だから非 pub が見える）。

`fn` の本体内には書けません。型の private を本体ファイルと分けて試験したいときは [`part`](#part--モジュールの分割) で**同一モジュールの別ファイル**に無名 impl を置けます（同一モジュールなので非 pub が見える）。

```plew
struct Parser { … }

impl Parser {
    test "backtracks on EOF" {
        val p = <Parser source="" />
        expectEq(expected: 0, actual: p.cursor)   // cursor が非 pub でも無名 impl 内なら見える
    }
}
```

### 発見と実行

- **発見はコンパイル対象に含まれる `test` ブロックの無条件全収集**。参照ベース（Zig の `refAllDecls` 流）にはせず、「**書いたテストは必ず走る**」を保証します（参照漏れで静かにスキップされる trap を避ける）。
- **production ビルドからは `test` ブロックごとリンク除外**。通常コードは test／production で 1 バイトも変わりません（Rust の `cfg(test)` のように通常コードを差し替えるビルドモードは持たない＝意味論を変えるビルドは無い・変えるのはエントリ／リンク対象だけ）。
- テストの失敗は**そのテストを失敗扱いにしてランナーは残りを続行**します（`assert` の [`panic`](../03-expressions/11-control-flow.md#panic-と発散)＝プロセス停止とは別の失敗チャネル。正確な機構はランナー設計の課題）。

### アサーション（`@Std/Testing`）

テスト用の表明は `@Std/Testing` から import する小さな関数族で、**実行時の [`assert`](../03-expressions/11-control-flow.md#assert--条件付き-panic) とは別物**です（`assert`＝本番コードの不変条件・panic／`expect*`＝テストの検査・ランナー続行）。

```plew
import @Std/Testing with { expect, expectEq, expectNe, expectApprox }
```

| 関数 | 検査 |
|---|---|
| `expect(ok: Bool)` | 真偽値 |
| `expectEq(expected:, actual:)` | 等価（`==`） |
| `expectNe(expected:, actual:)` | 非等価 |
| `expectApprox(expected:, actual:, tolerance:)` | 浮動小数の許容誤差内（NaN 比較は panic・厳密比較が脆いため固有理由あり） |

- **`expected:`/`actual:` はラベル必須**（[ラベルは宣言順固定](../01-basics/04-functions.md#引数ラベル)）。`assertEquals(expected, actual)` の引数逆転 footgun を、ラベル明示で防ぎます（値を取り違えると `expected: <計算結果>` という不自然な記述になり目に見える）。失敗診断は expected／actual の値を表示。
- **power-assert は採らない**。`assert(a == b)` の式を内省して両辺を表示する方式（pytest／Spock／Swift Testing）は診断が無料な一方「どの式まで分解されるか」が暗黙になるため、**対応範囲が関数リストで明示される** expect 族を選ぶ。
- **`expectError` は無い**。特定エラー値は `expectEq(expected: <Result.Error … />, actual: r)`、ペイロード無視の「エラーか」は `expect(r.isError)`、中身検査は [`match`](../03-expressions/11-control-flow.md#パターンマッチング) ── Plew は `==` を持つ値型エラーなので Zig の `expectError` 相当は畳まれる。
- **バリアントの「ケースのみ判定」は関数にできない**（Plew に第一級のバリアントタグは無く、ケース判別は常に `match` の領域）。Result／Optional は `isOk`/`isError`/`isSome`/`isNone` で bool 化でき `expect(…)` に乗る。パターンを取る `expectMatches` は将来 additive。

## 外部コード統合（`extern(c)` FFI）

> **状態 = 設計叩き台（点1 不透明ハンドル/ポインタ/共有 struct/ABI 記法・点2 数値対応・点3 文字列境界・点4 所有権規約・リンクまで一通り確定方向で記述／残るは下記「未決」）。** Plew の C-API バックエンド（libLLVM-C 等を叩く）の土台。ABI は当面 `c` のみ（`system`/WASM/`javascript` は後続）。
>
> **スコープ＝外部を「使う側」のみ（Plew が C を呼ぶ）。** Plew 関数を C へ「使わせる側」（export＝Plew→C 公開）は**未定**で本節に含めない（既存 `export` キーワードとの整合・呼出規約・マングリングを別途詰める必要があり、現状の LLVM 利用には不要なため）。

`extern(c)` 境界は **Plew の保証が切れる継ぎ目**です。境界の内側（値意味論・CoW・ARC・実質 race-free）はあくまで Plew が管理するメモリについての約束で、**外部 C 世界の確保・解放・別名・スレッド安全は Plew は一切引き受けません**（"hidden cost は可・hidden meaning は不可" の原則上、ここは唱えた通り＝**生で危険なものは生で危険**と見えるべき領域）。だから FFI は**床**として最小・正直に定義し、安全性は Plew 側で `unique`＋`deinit` を被せて作ります（`Array` が `RawBuffer` の上に・`String` が `bytes` の上に立つのと同じ構図）。

### ABI 選択子はクォートなしの bareword（`extern(c)`）

ABI は**コンパイラが定義する閉じた集合**（ユーザーが新 ABI を定義することはできない＝intrinsic 床と同じコンパイラ原始要素）なので、**文字列ではなく bareword** で書きます（import パスを直書きするのと同じ「本質的に文字列でない箇所はクォートなし」方針）。可読性のため**パレンで括る**：`extern(c)` / `repr(c)`。

- 未知の ABI（`extern(florble)` 等）は **Plew 層で即 `unknown ABI` エラー**（曖昧はエラー・補完はする/忖度はしない）。文字列にしても集合は閉じる（Rust も `extern "florble"` はエラー）ので、bareword で失うものはない。
- ABI 名にハイフンが要る場合（C の `C-unwind` 等）は camelCase で表す（`cUnwind`）。Plew の文脈キーワード（`inout`/`noLocal`/`defaultExtension`）と同じ綴り方針。
- コアライブラリの intrinsic 床も同じ記法＝**`extern(plewIntrinsic) { … }`**（旧 `extern "plew-intrinsic"` の bareword 化）。

### 役割（方向・レイアウト）× ABI の 2 軸

FFI は **役割キーワード × ABI 選択子**で表す。`extern` は「外部に実体がある（本体なし）」**だけ**を意味し、ローカル定義には使わない（"意味は唱えた通り"＝キーワードが定義場所を正直に告げる）。

| 役割 | 綴り | 定義場所 | 用途 |
|---|---|---|---|
| **import 関数／不透明型** | `extern(c) { fn … ; type … }` | **C 側**（本体なし） | C を呼ぶ・C の不透明型を受け取る |
| **共有 struct** | `repr(c) struct Foo { … }` | **Plew 側**（レイアウト記述） | C と同一レイアウトの値型（C 関数へ渡す） |

> Plew 関数を C へ**公開**する側（export＝Plew→C）はスコープ外（上記「状態」参照）。本節は **C を呼ぶ／C の型を受け取る側**だけを定める。

```plew
import @Std/Ffi with { CString }   // 文字列境界（点3）— 別途定義

extern(c) {
    // 不透明な外部型（C の `typedef struct … *LLVMModuleRef;` に 1:1）。
    type LLVMContextRef
    type LLVMModuleRef
    type LLVMBuilderRef
    type LLVMValueRef

    fn LLVMContextCreate() -> LLVMContextRef
    fn LLVMModuleCreateWithNameInContext(name: CString, ctx: LLVMContextRef) -> LLVMModuleRef
    fn LLVMDisposeModule(m: LLVMModuleRef)
    fn LLVMCreateBuilderInContext(ctx: LLVMContextRef) -> LLVMBuilderRef
    fn LLVMBuildAdd(b: LLVMBuilderRef, lhs: LLVMValueRef, rhs: LLVMValueRef, name: CString) -> LLVMValueRef
}
```

### 不透明な外部型 `type Name`

`extern(c)` ブロック内の **`type Name`**（本体なし）は**不透明な外部型**を宣言します。C 側の「不透明 struct へのポインタの typedef」（`LLVMModuleRef` 等）に 1:1 対応します。

- **不透明**：フィールドも factory もリテラルも無い。**Plew 側では構築・分解できず**、`extern` 関数の戻り値として受け取り、`extern` 関数へ渡すことだけができる。
- **型として別物**：`LLVMModuleRef` と `LLVMValueRef` は別の名前型で、暗黙変換が無いので**取り違えはコンパイルエラー**（C の `void*` 一枚で素通りする緩さを型で塞ぐ）。
- **コピー可能・word サイズ**：中身はポインタ 1 語でビットコピー複製（整数ディスクリプタ扱い）。**`borrow`/`move` は書けない**（コピー可能型の規則どおり・[03 値・所有権](../01-basics/03-values.md)）。`val a = m; val b = m` は**同じ外部オブジェクトへの別名**を生むが、それは外部世界の話で Plew の値意味論・ARC の対象外（別名は普通に起きる＝境界の正直さ）。
- **deinit は走らない**：Plew は外部寿命を知らないので、ハンドルが捨てられても**自動解放しない**（生のままなら**リークも二重解放も起こり得る**＝承知で使う床）。
- **C への射影は 1:1**：生成 C では Plew の型名をそのまま C 型名に使う。実体 `typedef` は include した C ヘッダ（`<llvm-c/Core.h>` 等）が供給。

### C ポインタ `CPtr[T]` / `CMutPtr[T]` / `COpaque`

中身を持つポインタ・配列・out 引数のための生ポインタ型。`RawBuffer`/`Ref` と同格の**コンパイラ組み込みプリミティブ**（属性魔法でなく型語彙）。C の `const` 有無を**読む権利／書く権利**として保つ（Plew の `borrow`/`inout`・shared/unique と同じ軸・bindgen で `.h` を 1:1 に写すため）。

| C | Plew | 意味 |
|---|---|---|
| `const T*` | **`CPtr[T]`**（無印＝安全側） | 読み取り専用ポインタ |
| `T*` | **`CMutPtr[T]`**（可変は明示） | 書き込み可能ポインタ |
| `void*` | **`COpaque`** | 無タグ生ポインタ（`const void*` は当面分けない） |

- **無印が読み取り専用**＝危険な方（可変）を長い名前で明示（`mut val` で可変を明示するのと同じ流儀）。
- `T` は数値・`repr(c)` struct・不透明ハンドル・別のポインタ（`LLVMValueRef *Args` → `CPtr[LLVMValueRef]`）いずれも可。
- 表層アプリコードは `CPtr` を見ない。触るのは `extern` ブロックと薄いグルー層だけ（Plew の「生ポインタ無し」は**表層**の約束で、床には `RawBuffer` 同様に在ってよい）。
- **生ポインタ/ハンドルは「null を取り得る」値**（raw pointer なので当然）。非 null を装う別型は持たず、**取り出しが `Optional`** になる（下記 NULL）。
- `Array[T]` の連続記憶を渡すときは床経由で基底ポインタを一時的に借りる（寿命は呼び出し中だけ・詳細は点3/4）。

### 共有 struct `repr(c) struct`

C とレイアウトを共有する struct は **`repr(c)`**（`extern` ではない＝Plew 側で定義する・外部と詐称しない）。`repr(c)` は「この struct のメモリ表現は **C ABI**」を意味するコンパイラ指示（属性 `@[...]` でなくキーワード＝メタプロは純粋 codegen のまま温存）。

```plew
repr(c) struct LLVMMCJITCompilerOptions {
    mut val OptLevel: U32 = 0
    mut val NoFramePointerElim: LLVMBool = 0
    mut val EnableFastISel: LLVMBool = 0
    mut val MCJMM: LLVMMCJITMemoryManagerRef = ...   // 不透明ハンドルでも可
}
```

- **意味**：C ABI レイアウト固定（宣言順・自然アラインメント・並べ替え/パッキング最適化を禁止）／POD（CoW・ARC 不介入）／フィールドは C 表現可能型のみ（プリミティブ・`CPtr`/`CMutPtr`/`COpaque`・不透明ハンドル・入れ子 `repr(c)`。`Array`/`String`/`Ref` は不可）。
- **フィールドアクセス・JSX 構築・既定値は通常の Plew 機構そのまま**（新構文は struct ヘッダの `repr(c)` 1 つだけ）：`mut val o = <LLVMMCJITCompilerOptions OptLevel=2 />` の残りは既定 0、`o.OptLevel = 3` は通常の場所代入。
- **`c` は C *言語*でなく C *ABI***（プラットフォーム標準の万能相互運用規約）。`repr(c)` の別レイアウトとして `repr(packed)`（詰め）等を後続 additive に足せる（property `stable` でなく contract で名付ける＝`packed` も「決定的」なので衝突しない）。
- **向きを持たない**：`repr(c) struct` は C ABI レイアウトの値型というだけなので、`extern(c)` 関数へ渡す引数に使える。将来 export 側を定めれば同じ定義がそちらにも乗る（共有 struct は方向非依存）。

ポインタ越しに渡す「`&opts`」は **`inout` で書ける**（`CPtr` を表に出さない）：

```plew
extern(c) {
    // C: LLVMCreateMCJITCompilerForModule(…, struct LLVM…Options *Opts, size_t, char **Err)
    fn LLVMCreateMCJITCompilerForModule(out: inout ExecutionEngineRef, m: LLVMModuleRef,
                                        opts: inout LLVMMCJITCompilerOptions, sz: USize,
                                        err: inout CMutPtr[U8]) -> LLVMBool
}
```

`inout LLVMMCJITCompilerOptions` を `Options*` に lower（`&tmp` 渡し＋呼出後コピーバック）＝Plew の場所モデルそのまま。`CPtr[Foo]` を直に握る必要があるのは「ポインタを保持する／配列にする」場合だけで、そのときは `CPtr[Foo].load() -> Optional[Foo]`（null→`None`＋struct コピーアウト・下記 NULL）／`CMutPtr[Foo].store(value:)`（書き戻し）。ポインタ越しのフィールド単位 lvalue（`ptr->x`）は当面持たない（場所モデルを生ポインタへ拡張する話＝必要時 additive）。

### NULL（生ポインタは可謬・取り出しが `Optional`）

C-API は失敗時に NULL を返す。`CPtr` 導入後は**「境界で NULL↔None に写す」専用機構は不要**：生ポインタ/ハンドルは**素直に「null を取り得る」値**とし、**raw から安全な値を取り出す操作が `Optional`** になる（null は取り出し点で一度だけ顕在化）。署名に `Optional` を書く境界変換も `isNull()` も持たない。

- **raw→raw の素通し**（extern 戻りを別 extern へそのまま渡す・グルー層）は**チェック不要**。null 込みで C へ転送できる（C の領分）。
- **null に触る操作は「raw→`Optional`」一つだけ**：`CPtr[T]`/ハンドルの **`.toOptional() -> Optional[Self]`**（null→`None`・非 null→`Some`）。Bool を返す `isNull()` のように null を持ったまま残さない＝null は変換で消える。
- **データの取り出し**：`CPtr[T].load() -> Optional[T]`（= `.toOptional()` ＋中身コピー・null 参照外しを取り出し点で型が塞ぐ）。既知非 null のホットパス用に `loadUnchecked() -> T`（escape hatch）。
- **ハンドルを安全型に包む**（pointee 無し＝load しない）：`.toOptional()` で弾いてから包む。

```plew
extern(c) {
    fn LLVMParseIRInContext(ctx: LLVMContextRef, buf: MemoryBufferRef) -> LLVMModuleRef  // 失敗時 null
}
// raw ハンドル → null を toOptional で弾き、Some だけ安全型へ昇格。
val mod: Optional[Module] = LLVMParseIRInContext(ctx: ctx, buf: buf)
    .toOptional()
    .map { (raw: LLVMModuleRef) in Module.adopt(raw~: raw) }   // adopt は非可謬 factory
```

**非 null 不変条件は「safe な皮（`unique` Wrapper）」が持つ**（bare ハンドルは持たない）＝危険は raw 床に、保証は安全層に、という Plew の床/皮分離と一貫。

### 安全な皮は Plew 側で被せる

生ハンドル/ポインタに RAII を付けるには、`unique` struct で包んで `deinit` に解放を書く ── 「外部資源を Plew の決定的破棄に乗せる」正典の形（[03](../01-basics/03-values.md) の `unique`/`deinit`）。

```plew
// 外部モジュールを所有する安全な値型。unique ＝コピー不可・move 専用なので
// 二重解放は型で排除され、スコープを抜けると deinit が確実に Dispose する。
unique struct Module {
    val raw: LLVMModuleRef
    deinit { LLVMDisposeModule(m: self.raw) }
}
pub impl Module {
    assoc fn create(name: CString, ctx: LLVMContextRef) -> Module {
        return <Module raw=LLVMModuleCreateWithNameInContext(name: name, ctx: ctx) />
    }
}
```

危険を `extern` ブロックと薄い皮に局所化すれば、利用側は通常の Plew 値として扱える。

### 点2: 数値型の対応

C 型 ↔ Plew 型は**2 階級**に分ける。

**(a) 固定幅 C 型 ↔ Plew 固定幅型（1:1・機械的）**：

| C | Plew | | C | Plew |
|---|---|---|---|---|
| `int8_t`/`uint8_t` | `I8`/`U8` | | `int64_t`/`uint64_t` | `I64`/`U64` |
| `int16_t`/`uint16_t` | `I16`/`U16` | | `float` | `F32` |
| `int32_t`/`uint32_t` | `I32`/`U32` | | `double` | `F64` |
| `_Bool`(C99) | `Bool` | | | |

**(b) プラットフォーム幅 C 型 → `@Std/Ffi` 専用型（別型・明示変換）**：`int`/`long`/`size_t` 等は**ターゲットで幅が変わる**。Plew は自前型の `全ターゲット同一意味論`（`I32` は常に 32bit）を守りたいので、これらは**境界専用の C-ABI 整数型**として持つ（Rust の `c_int`/`c_long`・Zig の `c_int`/`usize` と同じ）：

- `CInt`/`CUInt`（`int`/`unsigned`）・`CLong`/`CULong`（`long`）・`CShort`/`CUShort`・`CChar`（`char`・符号はプラットフォーム依存）・`CSize`（`size_t`）・`CPtrDiff`（`ptrdiff_t`）。
- **`USize`/`ISize`** ＝ポインタ幅（`size_t`/`intptr_t` 相当・既に FFI 着手時 additive と予告済み）。
- これらは**別の名前型**（暗黙変換なし）で、Plew 固定幅型との往来は**明示**：同幅以上は `as`（無損失・幅はターゲット既知）、狭めは `TryFrom`（可謬）。`全ターゲット同一意味論` は自前型側で保たれ、可変幅は C 境界だけに閉じる。
- **`LLVMBool`**（`typedef int LLVMBool`）は `CInt`＝幅が `Bool`（1byte）と違うので **Plew `Bool` ではない**。境界では `x != 0` で判定（typedef エイリアスは後続）。
- **外部由来 `NaN`**：C から返る `F64` が `NaN` でも特別扱いしない ── Plew の「`NaN` は比較で panic・算術は IEEE」がそのまま適用（foreign な `NaN` も単なる `NaN`）。

### 点3: 文字列境界

`String`（UTF-8・CoW・長さ前置・**非 NUL 終端**・不変）と C 文字列（`const char*`・NUL 終端・任意バイト）の往来。

**送る（Plew→C）**：NUL 終端バッファが要る。**`CString`＝所有する `unique` 値**（Plew String の UTF-8 コピー＋NUL を heap に持ち、`.ptr: CPtr[U8]` で渡す・`deinit` で解放）。寿命は **`CString` 値が生きている間**（レキシカルに明示）＝既存の `unique`/`deinit` だけで成立し新しい寿命機構は不要。

```plew
val cname: CString = CString.from(text~: "my.module")
val m = LLVMModuleCreateWithNameInContext(name: cname.ptr, ctx: ctx)  // 呼び出し中有効
// cname の deinit がスコープ末で解放
```

呼んで捨てるだけの定番には scoped 糖衣 `text.withCString { (p: CPtr[U8]) -> R in … }`（クロージャ内だけ有効＝寿命が構造的に閉じる）。

**受け取る（C→Plew）**：`String.fromCString(ptr: CPtr[U8]) -> Result[String, Utf8Error]` ── NUL まで strlen＋コピー＋**UTF-8 検証**（C バイトは妥当 UTF-8 と限らない＝可謬）。検証せず生バイトが要れば `bytesFromCString(ptr:) -> Array[U8]`。`CString`/変換は `@Std/Ffi` が所有。

### 点4: 所有権・寿命規約

境界を越えた値は **ARC 管理外**（Plew は foreign ポインタ/ハンドルを refcount しない）。**誰が `free` するかは C-API の契約**でコンパイラは推論できないので、**束縛の作者が型で encode** する：

- **C が「解放すべきポインタ」を返す** → `unique`＋`deinit` で disposer を呼ぶ（**Message パターン**：`LLVMPrintModuleToString` → `char*` を `LLVMDisposeMessage` で解放）。
- **C が借用/静的ポインタを返す** → 必要分をコピーアウト（`String.fromCString`）して解放しない。
- **所有を受け取る C へ渡す**（稀）→ `move` し、自分では解放しない。

**借用ポインタの寿命**（`CString.ptr`・`Array` バッファ基底など）は**所有 Plew 値が生きていて未変更の間だけ**有効。所有者の寿命を越えて C が保持する呼び出しに渡す＝dangling＝UB（Plew は寿命を静的に防げない＝unsafe 境界の責任）。**`CMutPtr` を Plew データへ向ける**のは **unique/`inout` 由来のときだけ**（共有 CoW から出すと書き込みが共有コピーを壊す＝const/mut が borrow/inout に対応する理由）。

### 外部 C ライブラリのリンク

- **Plew は自己完結 C を吐く**：`extern(c) { type/fn }`・`repr(c) struct` から **C のプロトタイプ/typedef/struct を Plew 自身が生成**する（宣言の正本は Plew 側＝bindgen が `.h` から写した extern 宣言をそのまま C へ再 emit）。ゆえに**外部ヘッダの `#include` は不要**で、必要なのは**リンクだけ**（Plew の extern 宣言と実体の ABI 一致は FFI 本来の前提＝宣言＝プロトタイプ）。
- **リンク＝ビルド/マニフェスト関心（ソース構文でない）**：`extern(c)` ブロックは純粋な宣言に保ち、リンクするライブラリと探索は**パッケージマニフェスト**でネイティブ依存として宣言（`pkg-config`/`llvm-config` で `-I`/`-L`/`-l` を解決）。`plewc` がビルドを駆動するとき clang にフラグを渡す。
- **当面（pipe-to-clang）**：現行ワークフローのまま手でフラグを渡す ──
  ```sh
  plewc app.pw | clang -x c - $(llvm-config --ldflags --libs core) -o app && ./app
  ```
  リンクは「clang に渡すフラグ」に過ぎず、`#include` 不要なので追加の include パスも基本不要。
- **C++ シムが要る場合**（libLLVM-C で足りず C++ API を使う時・rustc の `llvm-wrapper` と同型）：`extern "C"` を露出する `.cpp` を 1 枚書き、clang++ で別途コンパイルして libLLVM/libc++ とリンク。**Plew 側の言語機能は `extern(c)` のまま**（C++ には触れない）。シム source とコンパイル/リンク指定はマニフェストに列挙（後続）。

### 未決

- **リンクのマニフェスト・スキーマ**：ネイティブ依存のキー（`link`/`pkg-config`/探索コマンド）・C++ シムのビルド統合。**パッケージ管理（M3）と地続き**ゆえそこで確定。
- **プラットフォーム幅型の変換規則**：`as`（無損失）と `TryFrom`（可謬）の閾値の厳密化・`CSize`↔`USize`↔`U64` の関係。
- **ハンドルの等価**：ポインタ同一性で `Eq` を提供するか。当面は非提供で開始し additive 可。
- **spawn/local**：生ハンドル/ポインタを `local`（`Ref` 同様 spawn 不可・保守的）とするか、コピー可能な 1 語として spawn 越境を許す（正直に危険・race-free 保証は境界で切れると明記）か。
- **使わせる側（export＝Plew→C 公開）＝未定**：Plew 関数を C へ公開する綴り・マングル抑制・可視性（既存 `export` モジュール公開との整合）・呼出規約の既定。既存 `export` キーワードと紛らわしく要設計・libLLVM-C 利用には不要なので本節スコープ外。
- **型エイリアス**（`type FooRef = CPtr[FooOpaque]`）と **`repr(packed)`/`callconv` 軸**：当面は不透明 `type` と `repr(c)` のみ、両者は後続 additive。
