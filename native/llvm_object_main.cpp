// Build-machine worker for the same backend API that the native CLI embeds.
// This executable is not a separate user distribution requirement.
#include "llvm_backend.h"
#include <llvm-c/IRReader.h>
#include <cstdio>
#include <cstring>

int main(int argc, char **argv) {
  if (argc < 3 || argc > 6) {
    std::fprintf(stderr, "usage: llvm-object input.ll output.o [cpu] [--trace] [--thinlto]\n");
    return 1;
  }
  bool trace = false;
  bool thinlto = false;
  for (int index = 4; index < argc; ++index) {
    if (std::strcmp(argv[index], "--trace") == 0 && !trace) trace = true;
    else if (std::strcmp(argv[index], "--thinlto") == 0 && !thinlto) thinlto = true;
    else {
      std::fprintf(stderr, "plew: unknown or repeated option: %s\n", argv[index]);
      return 1;
    }
  }
  plew_llvm_initialize_worker(trace);
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
    result = thinlto
        ? plew_llvm_emit_thinlto_object(module, argv[2], argc >= 4 ? argv[3] : "", trace)
        : plew_llvm_emit_object(module, argv[2], argc >= 4 ? argv[3] : "", trace);
    LLVMDisposeModule(module);
  }
  LLVMContextDispose(context);
  return result;
}
