// Manual scoped embedding probe: observation state is per object request, and
// verbose LLVM command-line initialization is safe to request more than once.
#include "llvm_backend.h"
#include <llvm-c/IRReader.h>
#include <cstdio>
#include <cstring>
#include <string>

int main(int argc, char **argv) {
  if (argc != 2) return 1;
  for (int i = 0; i != 2; ++i) {
    plew_llvm_initialize_worker(1);
    auto context = LLVMContextCreate();
    const char *ir = "define i32 @main() { ret i32 0 }";
    auto input = LLVMCreateMemoryBufferWithMemoryRangeCopy(ir, std::strlen(ir), "repeat");
    LLVMModuleRef module = nullptr;
    char *error = nullptr;
    if (LLVMParseIRInContext(context, input, &module, &error)) {
      std::fprintf(stderr, "%s\n", error);
      LLVMDisposeMessage(error);
      LLVMContextDispose(context);
      return 1;
    }
    std::string output = std::string(argv[1]) + "/repeat-" + std::to_string(i) + ".o";
    int status = plew_llvm_emit_object(module, output.c_str(), "", 1);
    LLVMDisposeModule(module);
    LLVMContextDispose(context);
    if (status) return status;
  }
  std::puts("PASS repeated native progress requests");
}
