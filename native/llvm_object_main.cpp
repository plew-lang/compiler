// Build-machine worker for the same backend API that the native CLI embeds.
// This executable is not a separate user distribution requirement.
#include "llvm_backend.h"
#include <llvm-c/IRReader.h>
#include <llvm/Support/CommandLine.h>
#include <cstdio>
#include <cstring>

int main(int argc, char **argv) {
  if (argc < 3 || argc > 5) {
    std::fprintf(stderr, "usage: llvm-object input.ll output.o [cpu] [--trace]\n");
    return 1;
  }
  bool trace = argc == 5 && std::strcmp(argv[4], "--trace") == 0;
  if (argc == 5 && !trace) {
    std::fprintf(stderr, "plew: unknown option: %s\n", argv[4]);
    return 1;
  }
  // The one-shot worker owns LLVM's process-global diagnostic settings.
  // Actual code-generation pass events are consumed by the existing watchdog.
  if (trace) {
    const char *arguments[] = {"plew", "-debug-pass=Executions"};
    llvm::cl::ParseCommandLineOptions(2, arguments);
  }
  LLVMContextRef context = LLVMContextCreate();
  LLVMMemoryBufferRef buffer = nullptr;
  LLVMModuleRef module = nullptr;
  char *error = nullptr;
  int result = 1;
  if (LLVMCreateMemoryBufferWithContentsOfFile(argv[1], &buffer, &error)) {
    std::fprintf(stderr, "plew: %s\n", error);
    LLVMDisposeMessage(error);
  } else if (LLVMParseIRInContext(context, buffer, &module, &error)) {
    // LLVMParseIRInContext consumes the input buffer, including on failure.
    std::fprintf(stderr, "plew: %s\n", error);
    LLVMDisposeMessage(error);
  } else {
    result = plew_llvm_emit_object(module, argv[2], argc >= 4 ? argv[3] : "",
                                  trace);
    LLVMDisposeModule(module);
  }
  LLVMContextDispose(context);
  return result;
}
