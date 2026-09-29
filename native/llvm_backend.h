#ifndef PLEW_LLVM_BACKEND_H
#define PLEW_LLVM_BACKEND_H

#include <llvm-c/Core.h>
#include <stdint.h>

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

// Single-threaded native execution session. It owns code, not a second Plew
// runtime. Hosts explicitly supply symbols from the existing runtime instance.
// Immutable empty instruction name, borrowed for the process lifetime.
const unsigned char *plew_llvm_empty_name(void);
typedef struct PlewLlvmJit PlewLlvmJit;
PlewLlvmJit *plew_llvm_jit_create(void);
void plew_llvm_jit_destroy(PlewLlvmJit *jit);
int plew_llvm_jit_failed(const PlewLlvmJit *jit);
int plew_llvm_jit_define(PlewLlvmJit *jit, const char *name,
                         uint64_t address, int callable);
// Always consumes both handles, including on failure. They must be a matching
// module/context pair owned exclusively by the caller before this call.
int plew_llvm_jit_add(PlewLlvmJit *jit, LLVMModuleRef module,
                      LLVMContextRef context);
// The callback and the session identified by its integer ID live until JIT destruction. Called synchronously
// on first execution, never on registration/address lookup. It must not execute
// application code or perform symbol lookup. It returns a freshly owned pair;
// the bridge consumes any non-null outputs even when the callback fails.
typedef int (*PlewLlvmPrepareBody)(uint64_t session, uint64_t body,
                                  LLVMModuleRef *module, LLVMContextRef *context);
int plew_llvm_jit_defer(PlewLlvmJit *jit, const char *name, uint64_t body,
                        PlewLlvmPrepareBody prepare, uint64_t session);
// Returns zero on failure. Any failure makes this session terminal.
uint64_t plew_llvm_jit_lookup(PlewLlvmJit *jit, const char *name);

#ifdef __cplusplus
}
#endif
#endif
