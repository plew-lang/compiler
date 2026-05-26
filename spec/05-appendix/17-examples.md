# サンプルコード

## 基本的な構造体と拡張

```plew
struct Calculator {
    mut val current: F64
}

extension BasicMath {
    impl Calculator {
        mut fn add(value: F64) {
            self.current += value
        }

        fn result() -> F64 {
            return self.current
        }
    }
}

extension AdvancedMath {
    impl Calculator {
        mut fn power(exponent: F64) {
            self.current = math_pow(base: self.current, exponent: exponent)
        }

        mut fn sqrt() {
            self.current = math_sqrt(value: self.current)
        }
    }
}

async fn main() {
    mut val calc = <Calculator current=0.0 />

    val basic_result = calc#BasicMath
        .add(value: 10.0)
        .add(value: 5.0)
        .result()  // 15.0

    val advanced_calc = calc#AdvancedMath
    advanced_calc.power(exponent: 2.0)  // 225.0
    advanced_calc.sqrt()                // 15.0

    print(message: "Final result: {advanced_calc.result()}")
}
```
