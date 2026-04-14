# 言語選定の相談

**User:**   
**Created:** 8/7/2025 0:02:31  
**Updated:** 8/7/2025 0:38:20  
**Exported:** 4/14/2026 22:58:55  
**Link:** [https://chatgpt.com/c/68936e86-65dc-832b-b789-91f38b0871d5](https://chatgpt.com/c/68936e86-65dc-832b-b789-91f38b0871d5)  

## Prompt:
2025/8/7 0:02:28

ANTLR4とLLVM-IRを使って自作言語のコンパイラを作りたいんですが、どの言語で進めるか悩んでいます。
ANTLR4とLLVM-IR双方についてライブラリを使う必要があると思うので、以下の条件に基づいてどの言語のどのライブラリを使うのが良いか、お勧めしてください。
- 最終的にはセルフホスティングしたいので、パフォーマンスは二の次
- 開発のしやすさが最優先
- 可能な限り公式がサポートしている
- メンテナンスがよくされている

## Response:
2025/8/7 0:02:31

以下の点を教えていただけますか？

1.  開発のしやすさにおいて重視しているポイントは何ですか？（例：エディタ支援、型システム、ドキュメント、コミュニティの厚さなど）
2.  対象プラットフォームはどこですか？（例：Linux専用、Windows対応が必要、WebAssemblyターゲットなど）
3.  現時点で候補にしている言語（あるいは避けたい言語）があれば教えてください。

これらがわかると、開発効率やライブラリ整備状況に基づいた具体的な提案がしやすくなります。

## Prompt:
2025/8/7 0:05:33

エディタ支援はもちろん必要ですが、型等についてはキツすぎないほうが良いです。例えばRustは本番コンパイラを作るなら良いですが、雑に作っていくならキツすぎます。
対象プラットフォームは、macで動けば十分です。
今の所TypeScriptが有力ですが、良さそうなLLVM-IRに書き出すためのライブラリがなさげなので悩んでいるところです。

## Response:
2025/8/7 0:05:35

了解しました。TypeScriptを第一候補としつつ、ANTLR4とLLVM-IRに対応した開発のしやすい言語・ライブラリの組み合わせについて調査します。特に次の条件に重点を置いて調べます。

*   ANTLR4およびLLVM-IRのライブラリが存在する
*   開発体験が良好（エディタ支援、柔軟な型、活発なメンテナンス）
*   パフォーマンスは重視しない
*   macOSで動作すればよい
*   公式または事実上の標準ライブラリが存在

調査結果をまとめてご報告します。少々お待ちください。

Research completed in 9m· 14 件の情報源· 73 件の検索

Best Stacks for an ANTLR4 + LLVM-IR Compiler
============================================

To build a custom language compiler with ANTLR4 and LLVM-IR, we compare several language+library stacks that meet the requirements. The key criteria are:

*   **ANTLR4 support:** Official or well-maintained runtime for the language.
*   **LLVM-IR generation:** Availability of a library (preferably official or widely used) to construct LLVM IR.
*   **Ease of development:** Strong IDE/editor support, a flexible (not overly strict) type system, good documentation/community.
*   **Platform compatibility:** Must work reliably on macOS.
*   **Library maintenance:** Preference for officially supported or actively maintained libraries.

Below is an overview of candidate stacks and how they measure up:

| **Stack (Language + IR Library)** | **ANTLR4 Support** | **LLVM IR Generation Library** | **Library Status & Notes** |
| --- | --- | --- | --- |
| **Python** (with **llvmlite**) | Yes – official Python3 runtime[github.com](https://github.com/antlr/antlr4#:~:text=ANTLR%204%20supports%2010%20target,not%20strictly%20follow%20semver%20semantics) | **llvmlite** (lightweight binding)[github.com](https://github.com/numba/llvmlite#:~:text=A%20Lightweight%20LLVM%20Python%20Binding,for%20Writing%20JIT%20Compilers) | Actively maintained (LLVM 15+ support)[github.com](https://github.com/numba/llvmlite#:~:text=llvmlite%20has%20been%20tested%20with,to%20work%20with%20greater%20versions); stable C API usage for low churn[github.com](https://github.com/numba/llvmlite#:~:text=,compiler%20requirements%20and%20C%2B%2B%2011). |
| **C# (.NET)** (with **LLVMSharp**) | Yes – official C# runtime[github.com](https://github.com/antlr/antlr4#:~:text=ANTLR%204%20supports%2010%20target,not%20strictly%20follow%20semver%20semantics) | **LLVMSharp** (.NET LLVM C API)[github.com](https://github.com/dotnet/LLVMSharp#:~:text=LLVMSharp) | .NET Foundation project; covers full C API (enough for a compiler)[github.com](https://github.com/dotnet/LLVMSharp#:~:text=Features). Updates can lag LLVM releases[davidelettieri.it](https://davidelettieri.it/2025/02/15/kaleidoscope-tutorial-llvmsharp-18#:~:text=difficulties). |
| **Go** (with **llir/llvm**) | Yes – official Go runtime[github.com](https://github.com/antlr/antlr4#:~:text=ANTLR%204%20supports%2010%20target,not%20strictly%20follow%20semver%20semantics) | **llir/llvm** (pure Go IR library)[blog.gopheracademy.com](https://blog.gopheracademy.com/advent-2018/llvm-ir-and-go/#:~:text=The%20two%20main%20libraries%20for,LLVM%20IR%20in%20Go%20are) | Well-maintained community library; pure Go (no LLVM build needed)[blog.gopheracademy.com](https://blog.gopheracademy.com/advent-2018/llvm-ir-and-go/#:~:text=The%20two%20main%20libraries%20for,LLVM%20IR%20in%20Go%20are). Official Cgo bindings also available for full API. |
| **Swift** (with **Swift-LLVM** bindings) | Yes – official Swift runtime[github.com](https://github.com/antlr/antlr4#:~:text=ANTLR%204%20supports%2010%20target,not%20strictly%20follow%20semver%20semantics) | **Swift-LLVM** (Swift/C++ interop)[github.com](https://github.com/swiftlang/swift-llvm-bindings#:~:text=Swift%20Bindings%20for%20LLVM) | Official (part of Swift project); uses Swift–C++ interop to call LLVM API[github.com](https://github.com/swiftlang/swift-llvm-bindings#:~:text=Swift%20Bindings%20for%20LLVM%20is,for%20a%20C%20bridging%20layer). Work-in-progress (requires Swift 5.9+, cutting-edge). |
| **TypeScript** (with Node **llvm-bindings**) | Yes – official TS runtime[github.com](https://github.com/antlr/antlr4#:~:text=ANTLR%204%20supports%2010%20target,not%20strictly%20follow%20semver%20semantics) | **llvm-bindings** (Node addon)[dev.to](https://dev.to/apsarasx/use-llvm-by-javascripttypescript-27c3#:~:text=But,Not%20everyone%20likes%20C) | Community-driven (not official). Requires LLVM installed; API coverage on-demand (incomplete)[dev.to](https://dev.to/apsarasx/use-llvm-by-javascripttypescript-27c3#:~:text=%60llvm,bindings). |

Below, we discuss each stack in detail with its pros and cons:

Python + ANTLR4 + llvmlite
--------------------------

Python offers maximum ease of development with dynamic typing and an extensive ecosystem. ANTLR4 has an official Python3 target runtime[github.com](https://github.com/antlr/antlr4#:~:text=ANTLR%204%20supports%2010%20target,not%20strictly%20follow%20semver%20semantics), making it straightforward to generate a parser. For LLVM IR generation, **llvmlite** is a well-documented, lightweight binding maintained by the Numba project[github.com](https://github.com/numba/llvmlite#:~:text=A%20Lightweight%20LLVM%20Python%20Binding,for%20Writing%20JIT%20Compilers). It provides a pure Python IR builder decoupled from LLVM’s unstable C++ APIs, instead relying on the stable C API and emitting textual IR under the hood[github.com](https://github.com/numba/llvmlite#:~:text=,compiler%20requirements%20and%20C%2B%2B%2011). This design yields better error messages and low maintenance when upgrading LLVM[github.com](https://github.com/numba/llvmlite#:~:text=,compiler%20requirements%20and%20C%2B%2B%2011).

*   **Pros:** Very quick development cycle (no compile step), flexible dynamic typing, and simple syntax. Excellent IDE support (e.g. PyCharm, VSCode) and huge community. The llvmlite library is stable and makes IR building easier by using LLVM’s C API and text IR internally for robustness[news.ycombinator.com](https://news.ycombinator.com/item?id=25539797#:~:text=tijsvd%20%20%2061%20,next%20%5B%E2%80%93)[github.com](https://github.com/numba/llvmlite#:~:text=,compiler%20requirements%20and%20C%2B%2B%2011). Python’s wealth of libraries and documentation can accelerate prototyping.
*   **Cons:** Execution performance is lower (Python is interpreted), though performance is not the priority here. The compiler built in Python will be slower and use more memory than one in a compiled language. Deployment of a Python-based tool may require managing Python environments on the target macOS system. However, the extra overhead of llvmlite’s IR text round-trip is negligible if performance isn’t critical[news.ycombinator.com](https://news.ycombinator.com/item?id=25539797#:~:text=tijsvd%20%20%2061%20,next%20%5B%E2%80%93).

C# (.NET) + ANTLR4 + LLVMSharp
------------------------------

C# is a statically-typed language with a rich development environment (Visual Studio, Rider, etc.) and a large community. ANTLR4 provides an official C# runtime[github.com](https://github.com/antlr/antlr4#:~:text=ANTLR%204%20supports%2010%20target,not%20strictly%20follow%20semver%20semantics) that is well-maintained. For LLVM integration, **LLVMSharp** offers .NET bindings to LLVM. LLVMSharp is a .NET Standard library auto-generated from LLVM’s C headers (via ClangSharp)[github.com](https://github.com/dotnet/LLVMSharp#:~:text=LLVMSharp). It exposes almost the entire LLVM C API, which is sufficient to implement a full compiler[github.com](https://github.com/dotnet/LLVMSharp#:~:text=Features). This means you can create IR, optimize, and even JIT using the same calls as the C API (e.g., `LLVM.ModuleCreateWithName` becomes `LLVM.ModuleCreateWithName` in C#)[github.com](https://github.com/dotnet/LLVMSharp#:~:text=Features).

*   **Pros:** Modern C# has good type inference (`var`), garbage collection, and optional dynamic features, making the type system more flexible than C/C++ while still catching errors at compile time. The tooling on macOS is strong with VS Code (using OmniSharp) or Visual Studio for Mac. The LLVMSharp library is backed by the .NET Foundation and covers all stable LLVM C API functions, ensuring comprehensive functionality for IR generation and manipulation[github.com](https://github.com/dotnet/LLVMSharp#:~:text=Features). Performance of the compiler (if needed) will be high since C# is JIT-compiled. Documentation and community for C# are extensive, and resources like the Kaleidoscope tutorial have been ported to C# using LLVMSharp[davidelettieri.it](https://davidelettieri.it/2025/02/15/kaleidoscope-tutorial-llvmsharp-18#:~:text=A%20few%20years%20ago%20I,I%20encountered%20a%20few%20difficulties).
*   **Cons:** As a compiled language, the edit-compile-run cycle is slower than Python’s. The static type system is stricter than Python/TS (though easier than C++). LLVMSharp, while maintained, has lagged behind the very latest LLVM releases at times[davidelettieri.it](https://davidelettieri.it/2025/02/15/kaleidoscope-tutorial-llvmsharp-18#:~:text=difficulties) – you might need to use a slightly older LLVM version or nightly builds for cutting-edge features. Also, using LLVMSharp requires adding the native LLVM library (e.g., via NuGet `libLLVM` package) on your system[github.com](https://github.com/dotnet/LLVMSharp#:~:text=A%20nuget%20package%20for%20the,org%2Fpackages%2Fllvmsharp), which is an extra setup step. Overall, the development experience is not as instant as Python’s, but still developer-friendly by compiled language standards.

Go + ANTLR4 + llir/llvm
-----------------------

Go is designed for simplicity and fast compilation, which can be beneficial for compiler development. ANTLR4 supports Go with an official runtime target[github.com](https://github.com/antlr/antlr4#:~:text=ANTLR%204%20supports%2010%20target,not%20strictly%20follow%20semver%20semantics), allowing you to generate a parser in pure Go. For LLVM integration, the **llir/llvm** library is a popular choice. It is a pure Go library for constructing and manipulating LLVM IR without needing the actual LLVM binaries[blog.gopheracademy.com](https://blog.gopheracademy.com/advent-2018/llvm-ir-and-go/#:~:text=The%20two%20main%20libraries%20for,LLVM%20IR%20in%20Go%20are). The library can parse and produce LLVM IR text, which you can then pass to LLVM tools (like `llc` or `clang`) to generate machine code. (Go also has official LLVM bindings via Cgo for the full API, but those require linking to LLVM binaries and increase complexity[blog.gopheracademy.com](https://blog.gopheracademy.com/advent-2018/llvm-ir-and-go/#:~:text=The%20two%20main%20libraries%20for,LLVM%20IR%20in%20Go%20are).)

*   **Pros:** Go’s syntax and type system are simple and not overly verbose. It lacks complex type features, making it “not overly strict” in usage – there’s no manual memory management and most variables can be type-inferred or use straightforward types. The development experience is streamlined: fast compilation and easy cross-compiling, with good editor support (gopls in VSCode, GoLand, etc.). The `llir/llvm` library is actively developed and idiomatic in Go, letting you generate IR in a high-level way[blog.gopheracademy.com](https://blog.gopheracademy.com/advent-2018/llvm-ir-and-go/#:~:text=The%20two%20main%20libraries%20for,LLVM%20IR%20in%20Go%20are). Because it’s pure Go, you avoid dealing with C++ interoperability or compiling LLVM itself, which aligns with ease-of-development. Go’s community, while not as large as Python’s, is strong and the language has been used in several compiler projects (e.g. TinyGo, and various toy languages).
*   **Cons:** The Go ecosystem for compiler development is smaller than that of Python/Java, so there are fewer high-level examples for using ANTLR4 + LLVM together (though resources do exist[github.com](https://github.com/llir#:~:text=llir%20,llir%2Firutil%27s%20past%20year%20of)). If you need advanced LLVM features (e.g. JIT execution, custom optimization passes in-process), the pure Go approach might be limiting – you may have to emit IR to text and invoke external LLVM tools, which is a slower, multi-step compilation process. Also, Go’s static typing, while simple, means you have to compile for every change (though compile times are very fast). In summary, Go offers a nice balance of performance and simplicity, with the trade-off of a slightly less mature ecosystem for LLVM integration compared to Python or C#.

Swift + ANTLR4 + Swift-LLVM Bindings
------------------------------------

Swift, Apple’s modern language, is another candidate especially since the target is macOS. ANTLR4 officially supports Swift as a target[github.com](https://github.com/antlr/antlr4#:~:text=ANTLR%204%20supports%2010%20target,not%20strictly%20follow%20semver%20semantics), so you can generate a Swift parser. For LLVM IR, Swift now has **Swift-LLVM** bindings as part of the Swift project. These bindings leverage Swift’s new C++ interoperability to call the LLVM C++ APIs directly from Swift[github.com](https://github.com/swiftlang/swift-llvm-bindings#:~:text=Swift%20Bindings%20for%20LLVM). This is an **official** effort by Apple to make LLVM more accessible in Swift, meaning it’s likely to be well-maintained in the long term. Using these, one could programmatically create IR and invoke LLVM passes or the JIT just as in C++.

*   **Pros:** Swift offers strong type safety with a more concise syntax than Java or C#. Its type system has type inference and optionals, which help avoid many errors without excessive verbosity. Developer experience on macOS is excellent – Xcode and VSCode both support Swift, and you get features like interactive playgrounds for quick experimentation. The Swift-LLVM bindings are _officially_ part of Swift, indicating a high level of support; they aim to remove the need for C bridging and let Swift call LLVM APIs natively[github.com](https://github.com/swiftlang/swift-llvm-bindings#:~:text=Swift%20Bindings%20for%20LLVM). This provides power similar to writing the compiler in C++, but with Swift’s safer and more comfortable language features. Community support for Swift is huge in general, and there is growing interest in using Swift for systems programming and compiler development (Apple itself is beginning to use these bindings in their tooling).
*   **Cons:** The Swift-LLVM bindings are **very new** and still evolving. They require the latest Swift (5.9 or above) and an LLVM build on your system[github.com](https://github.com/swiftlang/swift-llvm-bindings#:~:text=Trying%20it%20out). Setting them up involves building a Swift package with CMake and linking to LLVM, which is more complex than using a higher-level library. As a work-in-progress, the API might change as Swift’s C++ interop matures[github.com](https://github.com/swiftlang/swift-llvm-bindings#:~:text=Swift%20Bindings%20for%20LLVM%20is,for%20a%20C%20bridging%20layer), so expect some churn or limited documentation. Additionally, Swift’s strict type safety (while generally a positive) means less flexibility than a dynamic language – you’ll need to model the AST/IR with proper types. Swift is also less commonly used for custom compilers (compared to Python or C#), so community examples are fewer. In short, Swift is a forward-looking choice that could pay off with a high-quality, safe compiler, but it may involve more initial setup and learning due to its newness in this domain.

TypeScript + ANTLR4 + LLVM Bindings (Node)
------------------------------------------

TypeScript was initially a leading candidate due to its familiar syntax and flexible typing. ANTLR4 does have a TypeScript target (essentially using the JavaScript runtime)[github.com](https://github.com/antlr/antlr4#:~:text=ANTLR%204%20supports%2010%20target,not%20strictly%20follow%20semver%20semantics), which allows writing the parser in TS. However, generating LLVM IR from TypeScript requires using a Node.js native addon. One such library is **llvm-bindings** on NPM, which wraps the LLVM C++ API for use in Node/TS[dev.to](https://dev.to/apsarasx/use-llvm-by-javascripttypescript-27c3#:~:text=But,Not%20everyone%20likes%20C). This approach has been demonstrated (for example, by the Langium project to compile to LLVM IR in a TS toolchain[typefox.io](https://www.typefox.io/blog/langium-llvm/#:~:text=At%20this%20juncture%2C%20we%20find,of%20a%20LLVM%20binding%20library)), and it lets you construct IR in TypeScript similar to how you would in C++ (by calling into the LLVM libraries).

*   **Pros:** TypeScript provides a comfortable middle-ground between dynamic and static typing – you can catch errors at compile-time but still have the flexibility of JavaScript when needed. The developer tooling is excellent (VS Code has first-class TS support). If you already know TypeScript well, leveraging it means less context switching. The **llvm-bindings** library (and similar projects like _llvm-node_) enable using LLVM’s capabilities; the usage is quite straightforward for basic IR building (e.g., creating a context, module, IR builder in TS)[dev.to](https://dev.to/apsarasx/use-llvm-by-javascripttypescript-27c3#:~:text=Then%2C%20new%20a%20,IR%20Builder)[dev.to](https://dev.to/apsarasx/use-llvm-by-javascripttypescript-27c3#:~:text=Then%2C%20build%20objects%20related%20to,function%20signatures). Being able to stay in the Node ecosystem could make integration with other JS tools or packaging easier.
*   **Cons:** The LLVM bindings for Node are **not officially maintained by the LLVM project**. They are community efforts and can be incomplete or lag behind new LLVM features. In fact, the author of `llvm-bindings` notes that it’s under development and new APIs are added on demand when requested[dev.to](https://dev.to/apsarasx/use-llvm-by-javascripttypescript-27c3#:~:text=%60llvm,bindings). Relying on such a library might mean you encounter missing functionality and have to request or implement updates yourself. Additionally, using this stack adds a dependency on native code: you must have LLVM installed on macOS and match the Node addon to the correct LLVM version[dev.to](https://dev.to/apsarasx/use-llvm-by-javascripttypescript-27c3#:~:text=But,Not%20everyone%20likes%20C)[dev.to](https://dev.to/apsarasx/use-llvm-by-javascripttypescript-27c3#:~:text=First%2C%20you%20need%20to%20install,bindings), which can complicate setup. Performance-wise, you also introduce overhead crossing between JavaScript and C++ in the binding. In summary, while TypeScript meets the ease-of-development criterion, the lack of a robust, official LLVM-IR library is a significant drawback that could slow development and maintenance.

Conclusion and Trade-offs
-------------------------

Each stack offers a different balance between ease, power, and maturity:

*   **Python + llvmlite** is arguably the easiest path for initial development. It maximizes productivity and has very stable tooling for ANTLR4 and IR generation[github.com](https://github.com/numba/llvmlite#:~:text=,compiler%20requirements%20and%20C%2B%2B%2011). The trade-off is lower performance and the need to ship a Python runtime, but for a first compiler version (especially one intended to be eventually self-hosted), this is often acceptable[news.ycombinator.com](https://news.ycombinator.com/item?id=25539797#:~:text=tijsvd%20%20%2061%20,next%20%5B%E2%80%93).
*   **C# + LLVMSharp** provides a solid middle ground: a comfortable typed language with excellent tooling and a fairly complete, officially backed LLVM library[github.com](https://github.com/dotnet/LLVMSharp#:~:text=Features). You sacrifice some of the rapid scripting agility of Python, but gain in execution speed and type safety. Watch out for library version mismatches with LLVM, though[davidelettieri.it](https://davidelettieri.it/2025/02/15/kaleidoscope-tutorial-llvmsharp-18#:~:text=difficulties).
*   **Go + llir/llvm** appeals if you prefer a simple, efficient language. It compiles to a self-contained binary (great for macOS deployment) and avoids complex build setups by using a pure-Go IR library[blog.gopheracademy.com](https://blog.gopheracademy.com/advent-2018/llvm-ir-and-go/#:~:text=The%20two%20main%20libraries%20for,LLVM%20IR%20in%20Go%20are). The development experience is smooth, but you might need to fall back on external LLVM tools for the final codegen step, which adds an extra phase to your build process.
*   **Swift + Swift-LLVM** is an intriguing choice for macOS-centric development. It aligns well with Apple’s technologies and promises first-class LLVM API access in a safer language[github.com](https://github.com/swiftlang/swift-llvm-bindings#:~:text=Swift%20Bindings%20for%20LLVM). This could future-proof your compiler and even make self-hosting on macOS more natural. The downside is the current immaturity of the bindings – it’s best if you’re comfortable dealing with evolving tools and potentially contributing fixes.
*   **TypeScript + llvm-bindings** lets you stick with a language you know and love, but the lack of an officially maintained IR library is a serious limitation. It can certainly work (others have done it), but you may spend more time fighting build issues or waiting on binding updates, which undermines the “ease of development” goal.

In conclusion, if **development ease** is the top priority, **Python with ANTLR4 and llvmlite** is a highly effective choice – it has official support and a proven, easy-to-use IR library[github.com](https://github.com/antlr/antlr4#:~:text=ANTLR%204%20supports%2010%20target,not%20strictly%20follow%20semver%20semantics)[github.com](https://github.com/numba/llvmlite#:~:text=,compiler%20requirements%20and%20C%2B%2B%2011). For a more **structured, compiled** approach without too much complexity, **C# with LLVMSharp** is a strong contender, given its comprehensive library support and tooling[github.com](https://github.com/dotnet/LLVMSharp#:~:text=Features). **Go** is also a good option for ease and simplicity, especially if you prefer a minimalist language, though its LLVM story is less “official” (balanced by the simplicity of llir). **Swift** might be worth it if you’re an Apple ecosystem enthusiast willing to ride the cutting edge.

Each of these stacks can fulfill the project requirements; the “best” ultimately depends on your familiarity and long-term plans. Many language creators prototype in a high-level environment (like Python) for ease, then later rewrite in a faster language (or the new language itself) once the design solidifies. Given the criteria and current library support, **Python/llvmlite** and **C#/LLVMSharp** stand out as the most well-rounded stacks, with **Go** close behind – all three have official ANTLR4 runtimes and well-maintained LLVM integration, minimizing risk as you build your compiler. The trade-offs above should help you choose the stack that best aligns with your comfort and the needs of your custom language project.

**Sources:**

*   ANTLR4 official targets (C++, C#, Python, Go, Swift, TypeScript, etc.)[github.com](https://github.com/antlr/antlr4#:~:text=ANTLR%204%20supports%2010%20target,not%20strictly%20follow%20semver%20semantics)
*   llvmlite design and benefits (Python LLVM IR binding)[github.com](https://github.com/numba/llvmlite#:~:text=,compiler%20requirements%20and%20C%2B%2B%2011)[news.ycombinator.com](https://news.ycombinator.com/item?id=25539797#:~:text=tijsvd%20%20%2061%20,next%20%5B%E2%80%93)
*   LLVMSharp (.NET) features and status[github.com](https://github.com/dotnet/LLVMSharp#:~:text=Features)[davidelettieri.it](https://davidelettieri.it/2025/02/15/kaleidoscope-tutorial-llvmsharp-18#:~:text=difficulties)
*   Go LLVM libraries (official vs pure Go)[blog.gopheracademy.com](https://blog.gopheracademy.com/advent-2018/llvm-ir-and-go/#:~:text=The%20two%20main%20libraries%20for,LLVM%20IR%20in%20Go%20are)
*   Swift LLVM bindings announcement (Swift project)[github.com](https://github.com/swiftlang/swift-llvm-bindings#:~:text=Swift%20Bindings%20for%20LLVM)
*   TypeScript LLVM bindings usage and limitations[dev.to](https://dev.to/apsarasx/use-llvm-by-javascripttypescript-27c3#:~:text=But,Not%20everyone%20likes%20C)[dev.to](https://dev.to/apsarasx/use-llvm-by-javascripttypescript-27c3#:~:text=%60llvm,bindings)

## Prompt:
2025/8/7 0:37:25

日本語でまとめ直してもらってもいいですか？

## Response:
2025/8/7 0:37:27

以下、日本語でまとめ直した内容です。条件をすべて踏まえた上で、開発のしやすさを最優先にして検討しました。

* * *

🔧 目的
-----

ANTLR4 + LLVM-IR を使って自作言語のコンパイラを開発する上で、最も開発しやすく、メンテナンス性の高い言語とライブラリの組み合わせを選定します。

### 条件

*   パフォーマンスは重視しない（セルフホスティング前提）
*   開発しやすさ（エディタ支援・柔軟な型など）を最優先
*   macOS 上で動けばよい
*   できれば公式サポート、または事実上の標準ライブラリがあるもの
*   TypeScript には注目しているが LLVM ライブラリが弱い

* * *

✅ おすすめの言語 + ライブラリ構成（上位3選）
-------------------------

| 言語 | ANTLR4対応 | LLVM IR生成 | 総合評価（開発のしやすさ） |
| --- | --- | --- | --- |
| **Python** | ✅ 公式ランタイムあり | ✅ `llvmlite`（安定・軽量） | ⭐⭐⭐⭐⭐ 非常に開発しやすい |
| **C# (.NET)** | ✅ 公式ランタイムあり | ✅ `LLVMSharp`（網羅的） | ⭐⭐⭐⭐ 型はあるが柔軟で IDE 強力 |
| **Go** | ✅ 公式ランタイムあり | ✅ `llir/llvm`（純Go） | ⭐⭐⭐ IDE支援も十分で実装も簡潔 |

* * *

各言語の特徴とトレードオフ
-------------

### 🐍 Python + ANTLR4 + llvmlite

*   **利点**
    *   開発効率が非常に高い。型が緩く試行錯誤しやすい。
    *   `llvmlite`はLLVM C APIを使った安定したIR生成ライブラリ。
    *   エディタ支援（VSCode, PyCharm）も非常に充実。
    *   文法がシンプルでAST/IRの記述も自然。
*   **欠点**
    *   コンパイラの実行速度は遅め。
    *   最終的にセルフホストするならリライトが必要。

> **初心者〜中級者のプロトタイピングに最適。まずはこれで構文や中間表現を固めるのが王道。**

* * *

### 💠 C# + ANTLR4 + LLVMSharp

*   **利点**
    *   `LLVMSharp`はLLVM C APIにかなり忠実。C++と同様の制御が可能。
    *   型があるが、モダンC#は柔軟（`var`, `dynamic` など）。
    *   Visual Studio や Rider のエディタ支援は最強クラス。
*   **欠点**
    *   LLVM本体のバージョンとの同期が少し面倒（NuGetのDLL等）。
    *   Pythonに比べると試行錯誤には向かない。

> **本格的に構造化されたコンパイラを作る際の候補。型が必要な段階で有力。**

* * *

### 🟡 Go + ANTLR4 + llir/llvm

*   **利点**
    *   `llir/llvm` は純Goで完結。LLVMをビルドせずにIR生成できる。
    *   Goの型は単純なので扱いやすい。実装が素直。
    *   ビルドが速く、ツールとしての配布もしやすい。
*   **欠点**
    *   JITや最適化など、高度なLLVM機能は使いにくい。
    *   LLVMへの依存はやや外部的（IR生成して別途LLVMツールでコード生成）。

> **手軽に1ファイルで動く開発環境を作りたい人向け。セットアップがとにかく楽。**

* * *

🟦 その他の候補
---------

### 🟠 TypeScript + ANTLR4 + llvm-bindings（Node.js）

*   **利点**
    *   JS/TSは試行錯誤しやすく、VSCodeとの相性抜群。
    *   既存のコード資産やパーサーツールが活かせる。
*   **欠点**
    *   LLVMバインディングが非公式かつ断片的（`llvm-bindings`, `llvm-node`）。
    *   ネイティブAdd-onの扱いが面倒。依存解決も不安定。

> **TSに強いこだわりがあるなら選択肢になるが、LLVMまわりの安定性に難あり。あまり推奨できない。**

* * *

### 🍎 Swift + ANTLR4 + Swift-LLVM（Swift C++ interop）

*   **利点**
    *   Apple公式。将来的には最も安全なLLVM統合方法になり得る。
    *   macOSと親和性が高く、Xcodeでの開発体験も◎。
*   **欠点**
    *   非常に新しい。Swift5.9+が必須、情報が少ない。
    *   LLVM C++ APIを直に叩く構成のため、難易度は高め。

> **macOS中心、かつ最先端を攻めたい方向け。今はまだ時期尚早な面も。**

* * *

結論
--

開発のしやすさを最優先にするなら、以下の順でおすすめします：

1.  **Python + ANTLR4 + llvmlite**  
     最も手軽。プロトタイプ・学習用途・初期設計に最適。
2.  **C# + ANTLR4 + LLVMSharp**  
     本格的に構造化された開発をしたいなら最有力。IDE体験が非常に良い。
3.  **Go + ANTLR4 + llir/llvm**  
     セットアップが簡単で軽量な環境が作れる。IR生成に特化するなら◎。

TypeScript は現状の LLVM サポートが弱く、今回の目的には厳しいです。どうしても TypeScript を使いたい場合は「IR だけは別プロセスで生成する」などの割り切りが必要です。

* * *

必要ならそれぞれのサンプルコードや開発環境のセットアップ手順も提示できます。どれで進めるか決まったら教えてください。



---
Powered by [ChatGPT Exporter](https://www.chatgptexporter.com)