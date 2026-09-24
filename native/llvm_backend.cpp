#include "llvm_backend.h"
#include "llvm_pipeline.h"

#include <llvm-c/Analysis.h>
#include <llvm-c/Error.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>
#include <llvm-c/Transforms/PassBuilder.h>
#include <cstdio>
#include <cstring>
#include <memory>

namespace {
struct MessageDisposer {
  void operator()(char *message) const { LLVMDisposeMessage(message); }
};
using Message = std::unique_ptr<char, MessageDisposer>;

bool verify(LLVMModuleRef module) {
  char *error = nullptr;
  int failed = LLVMVerifyModule(module, LLVMReturnStatusAction, &error);
  Message message(error);
  if (failed)
    std::fprintf(stderr, "plew: invalid LLVM module: %s\n", error);
  return !failed;
}

bool optimize(LLVMModuleRef module, LLVMTargetMachineRef machine,
              const char *pipeline, LLVMPassBuilderOptionsRef options) {
  LLVMErrorRef error = LLVMRunPasses(module, pipeline, machine, options);
  if (!error)
    return true;
  char *message = LLVMGetErrorMessage(error);
  std::fprintf(stderr, "plew: LLVM optimization failed: %s\n", message);
  LLVMDisposeErrorMessage(message);
  return false;
}
} // namespace

extern "C" int plew_llvm_emit_object(LLVMModuleRef module, const char *output,
                                     const char *cpu, int trace) {
  if (LLVMInitializeNativeTarget() || LLVMInitializeNativeAsmPrinter()) {
    std::fprintf(stderr, "plew: native LLVM target unavailable\n");
    return 1;
  }
  Message triple(LLVMGetDefaultTargetTriple());
  const char *moduleTriple = LLVMGetTarget(module);
  if (moduleTriple[0] && std::strcmp(moduleTriple, triple.get()) != 0) {
    std::fprintf(stderr, "plew: object backend requires native triple %s, got %s\n",
                 triple.get(), moduleTriple);
    return 1;
  }
  LLVMTargetRef target = nullptr;
  char *error = nullptr;
  if (LLVMGetTargetFromTriple(triple.get(), &target, &error)) {
    Message message(error);
    std::fprintf(stderr, "plew: LLVM target unavailable: %s\n", error);
    return 1;
  }
  auto machine = std::unique_ptr<LLVMOpaqueTargetMachine,
                                decltype(&LLVMDisposeTargetMachine)>(
      LLVMCreateTargetMachine(target, triple.get(), cpu, "",
                              LLVMCodeGenLevelDefault, LLVMRelocPIC,
                              LLVMCodeModelDefault), LLVMDisposeTargetMachine);
  if (!machine) {
    std::fprintf(stderr, "plew: cannot create LLVM target machine\n");
    return 1;
  }
  LLVMSetTarget(module, triple.get());
  auto layout = LLVMCreateTargetDataLayout(machine.get());
  Message layoutText(LLVMCopyStringRepOfTargetData(layout));
  const char *moduleLayout = LLVMGetDataLayoutStr(module);
  if (moduleLayout[0] && std::strcmp(moduleLayout, layoutText.get()) != 0) {
    LLVMDisposeTargetData(layout);
    std::fprintf(stderr, "plew: incompatible LLVM data layout\n");
    return 1;
  }
  LLVMSetModuleDataLayout(module, layout);
  LLVMDisposeTargetData(layout);
  if (!verify(module))
    return 1;

  auto options = std::unique_ptr<LLVMOpaquePassBuilderOptions,
                                decltype(&LLVMDisposePassBuilderOptions)>(
      LLVMCreatePassBuilderOptions(), LLVMDisposePassBuilderOptions);
  LLVMPassBuilderOptionsSetDebugLogging(options.get(), trace != 0);
  // Preserve the two optimization stages in the development link path:
  // the shared opt pipeline followed by clang's O2 IR optimization.
  if (!optimize(module, machine.get(), PLEW_LLVM_PIPELINE, options.get()) ||
      !optimize(module, machine.get(), "default<O2>", options.get()) ||
      !verify(module))
    return 1;

  LLVMMemoryBufferRef buffer = nullptr;
  if (LLVMTargetMachineEmitToMemoryBuffer(machine.get(), module, LLVMObjectFile,
                                         &error, &buffer)) {
    Message message(error);
    std::fprintf(stderr, "plew: LLVM object generation failed: %s\n", error);
    return 1;
  }
  auto object = std::unique_ptr<LLVMOpaqueMemoryBuffer,
                               decltype(&LLVMDisposeMemoryBuffer)>(
      buffer, LLVMDisposeMemoryBuffer);
  FILE *file = std::fopen(output, "wb");
  if (!file) {
    std::perror(output);
    return 1;
  }
  size_t size = LLVMGetBufferSize(buffer);
  bool complete = std::fwrite(LLVMGetBufferStart(buffer), 1, size, file) == size;
  if (std::fclose(file) != 0)
    complete = false;
  if (!complete) {
    std::fprintf(stderr, "plew: cannot write object: %s\n", output);
    std::remove(output);
    return 1;
  }
  return 0;
}
