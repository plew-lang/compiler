// Manual ORC feasibility probe, not a production execution path.
#include "common.hpp"

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
