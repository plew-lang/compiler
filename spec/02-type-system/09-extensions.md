# 拡張システム

Plew の特徴的な機能として、値に対して動的に拡張を適用できるシステムがあります。拡張は値自体を変更するのではなく、その値の型に対して一時的に機能を追加する仕組みです。

## 拡張で追加できる機能

拡張では以下の要素を追加できます：

- **メソッド** - インスタンスメソッドや可変メソッド
- **関連値** - 関連定数や関連変数（`assoc val`）
- **型エイリアス** - 型の別名定義
- **factory** - 新しいインスタンス生成（factory）
- **viaフィールドエイリアス** - 既存フィールドの別名

`impl` の**主語は型でもトレイトでもよい**：`impl Type { … }` は型に、`impl Trait { … }` はそのトレイトの全準拠型に（派生メソッド）、`impl B as A { … }` はトレイト `B` の全準拠型を別トレイト `A` へ準拠させる（トレイト間準拠）。トレイトを主語にする `impl` は**拡張の中だけ**に書けます（ベアでは書けない。→ [拡張はトレイトも対象にできる](#拡張はトレイトも対象にできる派生メソッドトレイト間準拠)）。1 つの拡張に複数の `impl` を束ねられ（型・トレイト混在可）、**拡張の名前からは中身を推定できません**（後述の à la carte 適用）。

## 拡張の定義と使用

```plew
struct Person {
    val name: String
    val age: I32
}

extension GreetingExtension {
    impl Person {
        // メソッドの追加
        fn greet() -> String {
            return "Hello, I'm {self.name}"
        }
        
        // 関連値の追加
        assoc val default_greeting: String = "Hi there!"
        
        // 型エイリアスの追加
        type NameType = String
    }
}

extension FormalExtension {
    impl Person {
        fn greet() -> String {  // 同名メソッドでも拡張が違えばOK
            return "Good day, my name is {self.name}"
        }

        fn introduce() -> String {
            return "Allow me to introduce myself: {self.name}"
        }
        
        // factory の追加（→ <Person.formal_person name=… />）
        factory formal_person(name: String) {
            return <Person name=name age=0 />
        }
    }
}

// トレイト実装の追加例
extension MathExtension {
    impl Person as Add[Person] {
        type Output = Person
        
        fn add(rhs: Person) -> Person {
            return <Person name="{self.name} & {rhs.name}" age=(self.age + rhs.age) />
        }
    }
    
    // 複数の型を同一拡張内で拡張可能
    impl String {
        fn shout() -> String {
            return "{self}!"
        }
    }
}

fn example() {
    val person = <Person name="Alice" age=25 />

    // 拡張を明示的に適用してメソッド呼び出し
    val greeting1 = person#GreetingExtension.greet()
    val greeting2 = person#FormalExtension.greet()
    
    // 関連値へのアクセス
    val default = Person#GreetingExtension.default_greeting
    
    // 拡張でトレイト実装を追加した場合の演算子使用
    val combined = person#MathExtension + <Person name="Bob" age=30 />
    
    // 拡張なしではメソッド呼び出し不可
    person.greet()  // エラー: greet メソッドは定義されていない
}
```

## 拡張の制約

### 同名メソッドと `#Ext` による曖昧化

拡張は**対象型の既存メソッドと同名のメソッドを定義できます**（旧仕様の「同名禁止」は撤廃）。これは引数ベースのオーバーロードではなく、`#Ext` による明示的なシャドーイングです。

- **ベア `value.foo()` は常に型自身（無名 impl）の `foo`** に解決される。拡張のメソッドはベア解決に参加しない。
- **`value#Ext.foo()` は `Ext` の `foo`**。`#Ext` ビューでは拡張側が同名の型メンバをシャドーする（明示適用したから拡張が優先）。
- 複数拡張を同時適用して同名が衝突する場合はコンパイルエラー（後述「拡張の型システム統合」。明示が対称で解決不能なため）。

外部型を自分のトレイトに準拠させる際、トレイトの要求名が型の既存メソッドと衝突しても（シグネチャ不一致で `via` 束縛できなくても）拡張内で定義でき、`#Ext` で区別できます ── これを禁止すると当該準拠が不可能になるため、同名追加を許容します。トレイト準拠は `via` で実体メンバに束ねます（[トレイト準拠と via](08-traits.md) 参照）。なお拡張の impl からは対象型の **`pub` / `pub(get)` メンバのみ**見えます（非公開は無名 impl 専用 → [メンバの可視性](05-structs-enums.md#メンバの可視性)）。

```plew
struct MyStruct {}

impl MyStruct {
    fn process() -> I32 { return 1 }           // 型自身のメソッド
}

extension Alt {
    impl MyStruct {
        fn process() -> String { return "x" }  // OK: 同名でも #Ext で区別
    }
}

val a = value.process()       // 型自身（-> I32）
val b = value#Alt.process()   // Alt のもの（-> String）
```

### 拡張メソッド内の `self` の型

`extension Bar { impl Foo { … } }` の中では、`self` の型は **`Foo#Bar`**（対象型 + その拡張）です。本体は一度だけ型検査されるので `self` は固定型でなければならず、拡張 `Bar` が定義時に知っているのは **対象型 `Foo` と自分自身 `Bar` だけ**だからです。呼び出し側がさらに別の拡張を効かせていても（`v: Foo#Bar#A` で `v.m()` を呼ぶ）、`m` の本体内では `self` はあくまで `Foo#Bar` で、**呼び出し側の `#A` は本体からは見えません**（見えるとモジュラに型検査できなくなる）。

この帰結として、`#Bar` ビューでは拡張が元メソッドをシャドーするため：

```plew
impl Foo {
    fn m() {}                 // 元メソッド
}

extension Bar {
    impl Foo {
        fn m() {              // self: Foo#Bar
            self.m()          // ← 拡張メソッドの再帰（#Bar ビューで Bar が元を隠す）
            self#!Bar.m()     // ← 元メソッド（#!Bar で Foo に戻す。"super" 相当）
            // self#A.foo()   // ← 別拡張 A の再利用は #A を明示スタック
        }
    }
}
```

- **`self.m()` は再帰**であって「元メソッド呼び出し」ではない。元（シャドーされた本体）へ到達する唯一の経路は **`self#!Bar.m()`**。
- 可視性は**字句的**で `self` の型に依らない。拡張 impl 内にいる限り対象型の `pub` / `pub(get)` メンバしか見えず、`self#!Bar` は解決先を変えるだけで可視性は広げない（`self#!Bar.m()` が元に届くのは元が公開メンバのときだけ）。

## 拡張の型システム統合

```plew
fn handle_formal_person(person: Person#FormalExtension) {
    // 拡張適用済みの型として受け取り
    person.greet()      // OK: FormalExtension.greet
    person.introduce()  // OK: FormalExtension.introduce
}

fn convert_extensions(person: Person#GreetingExtension) {
    // 同名メソッドを持つ拡張を同時適用しようとするとコンパイルエラー
    // val conflicted: Person#GreetingExtension#FormalExtension  // エラー: greet メソッドが衝突

    // 拡張を外して別の拡張を適用
    val formal_only = person#!GreetingExtension#FormalExtension
    formal_only.greet()  // OK: FormalExtension.greet のみ

    // 拡張の付け替え
    val with_greeting = formal_only#!FormalExtension#GreetingExtension
    with_greeting.greet()  // OK: GreetingExtension.greet
}
```

### 拡張ビューの変更は明示（暗黙キャストなし）

`A#P` は値の表現を変えない**ゼロコストのビュー**です（C 的には `A` と同一の構造体で、実行時フットプリントを持ちません）。`a#P.m()` は「`P` が `A` 用に定義したメソッド `m` を `a` を self に直接呼ぶ」に落ち、`#P` は「どのメソッド／witness を解決に使うか」を選ぶマーカにすぎません。

一方で**型検査の上では `A#P` は `A` の型細別**として扱い、ジェネリック引数にも流れ、**不変（invariant）に扱います**。帰結は次の 3 点です。

**ビューの変更は常に明示** ── `A`／`A#P`／`A#Q` の間に暗黙キャストはありません。別のビューが欲しければ呼び出し位置で `#`／`#!` を書きます。値が黙って効く拡張を変えることはありません（Plew が他でも暗黙変換を持たない方針の一貫）。

```plew
fn f(a: Person#FormalExtension) { a.introduce() }
val p = <Person name="Alice" age=25 />   // p: Person

f(p)                   // エラー：Person は Person#FormalExtension ではない
f(p#FormalExtension)   // OK：呼び出し位置で Formal ビューを明示
```

**コンテナには伝播しない（不変）** ── `Array[A]` と `Array[A#P]`、`Array[A#Ext1]` と `Array[A#Ext2]` は別の型で、暗黙キャストできません。スカラの再ビューは安全でも、コンテナは impl に依存する**内部不変条件**を抱えるためです。たとえば外部型 `A` に別のハッシュを与える `#Ext1`/`#Ext2` で `HashSet[A#Ext1]`（Ext1 のハッシュで配置済み）を `HashSet[A#Ext2]` として読めてしまうと、全ルックアップが空振りする**サイレントな論理バグ**になります。ジェネリクス一般と同じく不変に倒し、付け替えたいときは明示的に組み直します（`HashSet.from(…)` など）。なお[トレイト制約](08-traits.md)の充足のためにコンパイラが拡張を推論することもありません（`f(x#Ext)` と明示する＝[orphan rule](#外部型への実装は拡張でorphan-rule) の想定された使い方）。

**拡張違いはそのままオーバーロードになる** ── 暗黙キャストが無いので `A` と `A#P` は exact 一致で曖昧なく解決でき、`fn f(a: A)` と `fn f(a: A#P)` は別[オーバーロード](07-methods-impl.md#メソッドのオーバーロード)として共存します（呼び出し側が `#` の有無で選ぶ）。型が `default_extension #P` を宣言している場合は `A ≡ A#P` なので両者は同一定義＝重複エラーです。

## 継承・ネストは持たない

拡張は**継承もネストもできません**（`extension B: A` のような「A を引き継ぐ B」も、拡張の入れ子も無し）。理由は拡張の核である「**呼び出し位置の `#Ext` だけで定義場所が一意に分かる**」を保つため。継承・ネストは「`value#B.foo()` の `foo` が B 由来か取り込んだ A 由来か」を不透明にし、これを壊します。

代わりに：

- **別の拡張のメンバを再利用**したいときは、`self#A.foo()` と**明示修飾**して呼ぶ（暗黙の取り込みはしない）。
- **複数の拡張を同時に効かせたい**ときは、呼び出し位置で `value#A#B` と**スタック**する（同名衝突はエラー）。

> 複数の拡張を 1 つの名前にまとめる別名（`alias Web = Json + Http` のような bundling）は将来あり得るが、現状は持たない。導入は後付けで非破壊にできる（禁止はあくまで安全側のデフォルト）。

## 外部型への実装は拡張で（orphan rule）

無名 impl（`impl Type …`）を書けるのは **その型を自分のモジュールで定義している場合だけ**です（コヒーレンスのため。Rust の「型 or トレイト所有」より厳格な**型所有**版。配置できるモジュールの詳細は [モジュール](../04-execution/15-modules.md) の「無名 impl の配置」参照）。**外部型（他モジュール定義）への実装は、トレイトの所有を問わず、すべて名前付き拡張で行います** ── 外部トレイトはもちろん、**自分のトレイトを外部型に実装する場合も拡張が必要**です（無名だと呼び出しで結局 `#` 修飾が要り「実質拡張」になるため、経路を `#Ext` 一本に統一）。

```plew
extension Ext {
    impl ImportedStruct as ImportedTrait {
        // ImportedTrait の各要求を via で束ねる / 本体定義する
    }
}
```

Rust がこれを一律禁止するのは大域コヒーレンス（唯一の impl 保証）のためですが、Plew が許せるのは解決方法が違うからです：

- 拡張の impl は**無名ではない**ため暗黙ディスパッチには乗らず、呼び出し位置で `#Ext` を明示した時だけ発動する。
- `#Ext` は**型の一部**（`ImportedStruct#Ext`）なので、ジェネリックにも決定論的に流れる。`fn f[T](x: T) where T: ImportedTrait` は `f(x: v#Ext)` のように、拡張適用済みの型を渡して呼ぶ。
- **素の `ImportedStruct` は `ImportedTrait` を満たさない**。使用箇所で `#Ext` を適用して `ImportedStruct#Ext` にする必要がある。
- 同じ実装を別々の拡張が与えても `ImportedStruct#Ext1` と `ImportedStruct#Ext2` は**別の型**となり、`Array[ImportedStruct#Ext1]` などはコンテナごと型レベルで区別される（非コヒーレンスを「禁止」ではなく「型による区別」で防ぐ）。

### 制限

- トレイトの要求がメソッド・関連値・factory・`via` で満たせる場合は完全に実装できるが、**フィールド要求は外部型に新設できない**ため、外部 struct が該当フィールドを既に持ち `via` で束ねられる時だけ満たせる。
- 空の `impl … as … {}` が成立するのは要求ゼロのマーカートレイトのみ。要求があれば本体（`via`／定義）が必要（[トレイト準拠と via](08-traits.md) 参照）。

## 拡張はトレイトも対象にできる（派生メソッド・トレイト間準拠）

拡張内の `impl` は**トレイトを主語**にできます。これがトレイトの[派生メソッド](08-traits.md)の置き場であり、blanket 的な「あるトレイトの全準拠型を別トレイトへ準拠させる」仕組みでもあります。

```plew
extension IterExt {
    impl Iterator {                  // 派生メソッド：self は Self: Iterator
        fn map[F](f: F) -> Map[Self, F] { /* self.next() の上に組む */ }
        fn filter[F](f: F) -> Filter[Self, F] { /* … */ }
    }
}

extension ToStr {
    impl Format as ToString {        // トレイト間準拠：self は Self: Format
        fn to_string() -> String { return self.format(format: "") }
    }
}
```

- **`impl Trait { … }`（派生メソッド）**：`self` は `Self: Trait`。要求や同拡張内の他メソッドを呼べる。本体はトレイトのインターフェースに対して一度だけ型検査される。
- **`impl B as A { … }`（トレイト間準拠）**：`B` の全準拠型を `A` へ準拠させる。`self` は `Self: B`。`A` の要求を `B` の語彙で実装する。`#Ext` 適用済み（または `default_extension` 済み）の B 型だけが `A` を満たすので、`fn g[T](x: T) where T: A` には `g(x#Ext)` で渡す（[外部型への実装](#外部型への実装は拡張でorphan-rule)の `f(x: v#Ext)` と同じ流れ）。
- **頭なし Self の blanket は禁止**：`impl[T] T { … }` や `impl[T] T as A where T: B { … }`（Self が型構築子を持たないベア型変数）は書けません。型所有が錨を下ろせず、型のベアメソッド一覧をローカルに列挙できなくなるためです。「B の全準拠型を A へ」は上記 `impl B as A`（主語＝トレイト）で表現します。

### 拡張は名前付きバンドル（à la carte 適用）

1 つの拡張は**任意の `impl` を束ねた名前付きバンドル**にすぎず、名前から中身は決まりません。`value#P` は「P の中で value の型が**資格を持つ部分だけ**を活性化する」à la carte 適用です。

```plew
extension P {
    impl B {}        // B 準拠型に効く部分
    impl C {}        // C 準拠型に効く部分
}
```

- `T#P` という型は**何の準拠も主張しません**。`#P` はあくまで「P のビューを開く」だけで、その中の `impl Iterator { fn map }` が `T` に**適用される**ことは別問題です。`it.map()` を呼ぶには `it#IterExt` で拡張ビューを開き、かつ `where T: Iterator` で `impl Iterator` 部が適用されることを保証する必要があります（直交する 2 条件で、両方必要）。

```plew
fn process[T](it: T#IterExt) where T: Iterator {   // where は T#IterExt から含意されない＝省略不可
    it.map(f).filter(g)                            // 本体はベア。map の戻り値は default を持つ具体型なので鎖は流れる
}
```

## デフォルト拡張（`default_extension`）

型は、自分のベア表面に**既定で載せる拡張**を宣言できます。構文は型本体の `default_extension`（→ [構造体と列挙型](05-structs-enums.md)）で、列挙は型レベルの `Type#A#B` と同じく `#` 連結です。

```plew
struct Array[T] {
    default_extension #IterExt#FooExt
}

val arr = [1U32]      // Array
arr.map(f)            // OK：既定で #IterExt が載っている
arr#!IterExt.map()    // エラー：#!IterExt で剥がすと map は無い
```

- **宣言できるのは型の作者だけ**：`default_extension` は型本体に書く＝型を所有するモジュールのみ。外部モジュールが他人の型のベア表面を勝手に変えることはできない（変えたければ使用箇所で `#Ext`）。
- **ベア解決への参加**：既定拡張のメソッドは、その型のベアなオーバーロード集合に加わる（非デフォルトの拡張はベア解決に参加せず `#Ext` 必須）。`value#!Ext` で個別に剥がせ、`value#Ext` は常に届く。既定集合は `#`／`#!` チェーンの起点になる（`Array` ≡ `Array#IterExt#FooExt`）。
- **衝突＝宣言地点でエラー**：型自身のメソッドや別の既定拡張と**同セレクタ・同シグネチャ**で衝突したら、`default_extension` 宣言地点でコンパイルエラー（引数型が違えばオーバーロードとして共存）。型の作者が「片方だけ既定にし、他方は `#Ext` で明示」と curate して解決する。
- **à la carte**：既定拡張も適用は à la carte（型が資格を持つ部分だけが載る）。型が何の資格も持たない拡張を既定指定しても無意味なので診断対象。
- **ジェネリックには流れない**：境界 `T: Trait` は要求しか運ばず、`T` の既定拡張は不明。境界型変数に派生メソッドを使うときは `x#Ext`（または引数型 `x: T#Ext`）と明示する（上記「à la carte 適用」参照）。
