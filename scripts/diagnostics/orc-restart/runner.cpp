// Manual ORC feasibility probe, not a production execution path.
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/ExecutionUtils.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include <cstdlib>
#include <iostream>

using namespace llvm;
using namespace llvm::orc;

static void check(Error error) {
  if (error) {
    logAllUnhandledErrors(std::move(error), errs(), "orc-probe: ");
    std::exit(1);
  }
}
template <class T> static T take(Expected<T> value) {
  if (!value) check(value.takeError());
  return std::move(*value);
}
static void verify(Module &module) {
  if (verifyModule(module, &errs())) std::exit(1);
}
static void optimize(Module &module, TargetMachine &target, StringRef pipeline) {
  verify(module);
  if (pipeline == "none") return;
  LoopAnalysisManager loops;
  FunctionAnalysisManager functions;
  CGSCCAnalysisManager calls;
  ModuleAnalysisManager modules;
  PassBuilder builder(&target);
  builder.registerModuleAnalyses(modules);
  builder.registerCGSCCAnalyses(calls);
  builder.registerFunctionAnalyses(functions);
  builder.registerLoopAnalyses(loops);
  builder.crossRegisterProxies(loops, functions, calls, modules);
  ModulePassManager passes;
  check(builder.parsePassPipeline(passes, pipeline));
  passes.run(module, modules);
  verify(module);
}

int main(int argc, char **argv) {
  if (argc != 4) {
    errs() << "usage: orc-runner INPUT.ll RUNTIME.dylib PIPELINE|none\n";
    return 2;
  }
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  std::string error;
  if (sys::DynamicLibrary::LoadLibraryPermanently(argv[2], &error)) {
    errs() << error << '\n';
    return 1;
  }
  auto targetBuilder = take(JITTargetMachineBuilder::detectHost());
  targetBuilder.setCodeGenOptLevel(StringRef(argv[3]) == "none"
                                      ? CodeGenOptLevel::None
                                      : CodeGenOptLevel::Default);
  auto target = take(targetBuilder.createTargetMachine());
  auto jit = take(LLJITBuilder().setJITTargetMachineBuilder(targetBuilder).create());
  jit->getMainJITDylib().addGenerator(take(
      DynamicLibrarySearchGenerator::GetForCurrentProcess(
          jit->getDataLayout().getGlobalPrefix())));
  ThreadSafeContext context(std::make_unique<LLVMContext>());
  SMDiagnostic diagnostic;
  auto module = parseIRFile(argv[1], diagnostic, *context.getContext());
  if (!module) {
    diagnostic.print(argv[0], errs());
    return 1;
  }
  module->setDataLayout(jit->getDataLayout());
  module->setTargetTriple(jit->getTargetTriple().str());
  optimize(*module, *target, argv[3]);
  check(jit->addIRModule(ThreadSafeModule(std::move(module), context)));
  check(jit->initialize(jit->getMainJITDylib()));
  auto entry = take(jit->lookup("main")).toPtr<int (*)()>();
  int result = entry();
  check(jit->deinitialize(jit->getMainJITDylib()));
  return result;
}
