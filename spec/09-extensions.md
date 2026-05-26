# 拡張システム

Plew の特徴的な機能として、値に対して動的に拡張を適用できるシステムがあります。拡張は値自体を変更するのではなく、その値の型に対して一時的に機能を追加する仕組みです。

## 拡張で追加できる機能

拡張では以下の要素を既存の型に追加できます：

- **メソッド** - インスタンスメソッドや可変メソッド
- **関連値** - 関連定数や関連変数（`assoc val`）
- **型エイリアス** - 型の別名定義
- **factory** - 新しいインスタンス生成（factory）
- **viaフィールドエイリアス** - 既存フィールドの別名

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

外部型を自分のトレイトに準拠させる際、トレイトの要求名が型の既存メソッドと衝突しても（シグネチャ不一致で `via` 束縛できなくても）拡張内で定義でき、`#Ext` で区別できます ── これを禁止すると当該準拠が不可能になるため、同名追加を許容します。トレイト準拠は `via` で実体メンバに束ねます（[トレイト準拠と via](11-traits.md) 参照）。なお拡張の impl からは対象型の **`pub` / `pub(get)` メンバのみ**見えます（非公開は無名 impl 専用 → [メンバの可視性](04-functions.md)）。

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

## 継承・ネストは持たない

拡張は**継承もネストもできません**（`extension B: A` のような「A を引き継ぐ B」も、拡張の入れ子も無し）。理由は拡張の核である「**呼び出し位置の `#Ext` だけで定義場所が一意に分かる**」を保つため。継承・ネストは「`value#B.foo()` の `foo` が B 由来か取り込んだ A 由来か」を不透明にし、これを壊します。

代わりに：

- **別の拡張のメンバを再利用**したいときは、`self#A.foo()` と**明示修飾**して呼ぶ（暗黙の取り込みはしない）。
- **複数の拡張を同時に効かせたい**ときは、呼び出し位置で `value#A#B` と**スタック**する（同名衝突はエラー）。

> 複数の拡張を 1 つの名前にまとめる別名（`alias Web = Json + Http` のような bundling）は将来あり得るが、現状は持たない。導入は後付けで非破壊にできる（禁止はあくまで安全側のデフォルト）。

## 外部型への実装は拡張で（orphan rule）

無名 impl（`impl Type …`）を書けるのは **その型を自分のモジュールで定義している場合だけ**です（コヒーレンスのため。Rust の「型 or トレイト所有」より厳格な**型所有**版。配置できるモジュールの詳細は [モジュール](10-modules.md) の「無名 impl の配置」参照）。**外部型（他モジュール定義）への実装は、トレイトの所有を問わず、すべて名前付き拡張で行います** ── 外部トレイトはもちろん、**自分のトレイトを外部型に実装する場合も拡張が必要**です（無名だと呼び出しで結局 `#` 修飾が要り「実質拡張」になるため、経路を `#Ext` 一本に統一）。

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
- 空の `impl … as … {}` が成立するのは要求ゼロのマーカートレイトのみ。要求があれば本体（`via`／定義）が必要（[トレイト準拠と via](11-traits.md) 参照）。
