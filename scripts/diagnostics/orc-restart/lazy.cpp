// Stage-zero ORC probe: machine-code laziness and an executor failure boundary.
// Deliberately not a source-lazy Plew implementation or a production host ABI.
#include "common.hpp"
#include "llvm/AsmParser/Parser.h"
#include <map>
#include <string>
#include <unistd.h>

static std::map<std::string, unsigned> compiled;
[[noreturn]] static void failedCall() {
  const char message[] = "lazy-call-failed\n";
  (void)!write(STDERR_FILENO, message, sizeof(message) - 1);
  _exit(70); // Never return an invented value to a JIT caller or unwind its stack.
}

int main(int argc, char **argv) {
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  auto jit = take(LLLazyJITBuilder()
      .setLazyCompileFailureAddr(ExecutorAddr::fromPtr(&failedCall)).create());
  jit->getIRTransformLayer().setTransform(
      [](ThreadSafeModule module, MaterializationResponsibility &)
          -> Expected<ThreadSafeModule> {
        module.withModuleDo([](Module &m) {
          verify(m);
          for (const auto &function : m)
            if (!function.isDeclaration()) ++compiled[function.getName().str()];
        });
        return std::move(module);
      });
  ThreadSafeContext context(std::make_unique<LLVMContext>());
  SMDiagnostic diagnostic;
  auto module = parseAssemblyString(R"(
    define i64 @even(i64 %n) {
      %done = icmp eq i64 %n, 0
      br i1 %done, label %yes, label %recur
    yes: ret i64 1
    recur:
      %next = sub i64 %n, 1
      %result = call i64 @odd(i64 %next)
      ret i64 %result
    }
    define i64 @odd(i64 %n) {
      %done = icmp eq i64 %n, 0
      br i1 %done, label %no, label %recur
    no: ret i64 0
    recur:
      %next = sub i64 %n, 1
      %result = call i64 @even(i64 %next)
      ret i64 %result
    }
    define i64 @callback(ptr %context) {
      %value = load i64, ptr %context
      ret i64 %value
    }
    define i64 @invoke(ptr %code, ptr %context) {
      %value = call i64 %code(ptr %context)
      ret i64 %value
    }
    define i64 @unused() { ret i64 99 }
    declare i64 @unavailable_symbol()
    define i64 @broken() {
      %value = call i64 @unavailable_symbol()
      ret i64 %value
    }
    define void @spin() {
      br label %loop
    loop: br label %loop
    }
  )", diagnostic, *context.getContext());
  if (!module) { diagnostic.print(argv[0], errs()); return 1; }
  module->setDataLayout(jit->getDataLayout());
  module->setTargetTriple(jit->getTargetTriple().str());
  check(jit->addLazyIRModule(ThreadSafeModule(std::move(module), context)));
  std::string mode = argc > 1 ? argv[1] : "success";
  if (mode == "failure") { take(jit->lookup("broken")).toPtr<long (*)()>()(); return 1; }
  if (mode == "spin") { take(jit->lookup("spin")).toPtr<void (*)()>()(); return 1; }
  require(compiled.empty(), "registration compiled bodies");
  auto even = take(jit->lookup("even")).toPtr<long (*)(long)>();
  require(compiled.empty(), "lookup compiled body instead of returning a lazy stub");
  require(even(8) == 1 && even(9) == 0, "mutual recursion");
  require(compiled["even"] == 1 && compiled["odd"] == 1, "recursive bodies must compile once");
  auto callback = take(jit->lookup("callback")).toPtr<long (*)(void *)>();
  auto invoke = take(jit->lookup("invoke")).toPtr<long (*)(long (*)(void *), void *)>();
  require(compiled["callback"] == 0 && compiled["invoke"] == 0, "callback lookup compiled bodies");
  long value = 42;
  require(invoke(callback, &value) == 42 && invoke(callback, &value) == 42, "callback ABI");
  require(compiled["callback"] == 1 && compiled["invoke"] == 1, "callback bodies must compile once");
  require(compiled["unused"] == 0 && compiled["broken"] == 0 && compiled["spin"] == 0,
          "unrequested independent body compiled");
  outs() << "PASS lazy lookup, recursion, callback and one-time materialization\n";
  return 0;
}
