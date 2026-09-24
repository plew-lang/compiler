#ifndef PLEW_LLVM_BACKEND_H
#define PLEW_LLVM_BACKEND_H

#include <llvm-c/Core.h>

#ifdef __cplusplus
extern "C" {
#endif

// Configure process-global LLVM diagnostics once in a one-shot worker.
void plew_llvm_initialize_worker(int trace);

// Borrow and optimize a module, then emit a native PIC object. The caller owns
// the module throughout. Failure prints a diagnostic and returns nonzero.
// Modules carrying sanitize_address are instrumented after optimization.
// cpu is an explicit target CPU, or an empty string for LLVM's generic CPU.
int plew_llvm_emit_object(LLVMModuleRef module, const char *output,
                          const char *cpu, int trace);

#ifdef __cplusplus
}
#endif
#endif
