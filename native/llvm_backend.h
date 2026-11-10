#ifndef PLEW_LLVM_BACKEND_H
#define PLEW_LLVM_BACKEND_H

#include <llvm-c/Core.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// trace requests lightweight progress. PLEW_LLVM_TRACE=1 plus trace opts into
// process-global detailed LLVM diagnostics once in a one-shot worker.
void plew_llvm_initialize_worker(int trace);

// Borrow and optimize a module, then emit a native PIC object. The caller owns
// the module throughout. Failure prints a diagnostic and returns nonzero.
// Modules carrying sanitize_address are instrumented after optimization.
// cpu is an explicit target CPU, or an empty string for LLVM's generic CPU.
// trace reports bounded IR/codegen checkpoints, not per-pass debug text.
int plew_llvm_emit_object(LLVMModuleRef module, const char *output,
                          const char *cpu, int trace);

// Immutable target descriptions for representation planning. Returned strings
// are owned LLVM messages (LLVMDisposeMessage); empty means failure. Native
// layout uses exactly the object backend's CPU/features/target-machine policy.
char *plew_llvm_native_data_layout(const char *cpu);
// Context-local identity only, never a session/body or persistent cache key.
uint64_t plew_llvm_module_identity(LLVMModuleRef module);
uint64_t plew_llvm_context_identity(LLVMContextRef context);
int plew_llvm_function_matches(LLVMModuleRef module, LLVMValueRef function, LLVMTypeRef signature);
int plew_llvm_value_scope_matches(LLVMValueRef value, LLVMValueRef function);
int plew_llvm_home_type_matches(LLVMValueRef address, LLVMTypeRef type);
uint64_t plew_llvm_home_alignment(LLVMValueRef address);
int plew_llvm_projected_home_matches(LLVMValueRef address, LLVMValueRef root, LLVMTypeRef rootType,
                                    const uint64_t *indices, uint64_t count, LLVMTypeRef resultType);
int plew_llvm_guaranteed_parameter_matches(LLVMValueRef address, LLVMTypeRef type, uint64_t alignment);

// Single-threaded native execution session. It owns code, not a second Plew
// runtime. Hosts explicitly supply symbols from the existing runtime instance.
// Immutable empty instruction name, borrowed for the process lifetime.
const unsigned char *plew_llvm_empty_name(void);
typedef struct PlewLlvmJit PlewLlvmJit;
typedef struct PlewProgramArguments PlewProgramArguments;
PlewProgramArguments *plew_compiler_arguments_create(uint64_t count, char **values);
void plew_compiler_arguments_destroy(PlewProgramArguments *arguments);
int plew_compiler_jit_main(PlewLlvmJit *jit, PlewProgramArguments *arguments);
int plew_compiler_trace_run(void);

PlewLlvmJit *plew_llvm_jit_create(void);
char *plew_llvm_jit_target_triple(const PlewLlvmJit *jit);
char *plew_llvm_jit_data_layout(const PlewLlvmJit *jit);
// Per-instance diagnostic observation only; no JIT policy or LLVM flags change.
void plew_llvm_jit_set_trace(PlewLlvmJit *jit, int enabled);
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
// Consumes a signature-only module and publishes its explicit body entries.
int plew_llvm_jit_declarations(PlewLlvmJit *jit, LLVMModuleRef module,
                                LLVMContextRef context, PlewLlvmPrepareBody prepare,
                                uint64_t session);
int plew_llvm_jit_call_main(PlewLlvmJit *jit, int argc, char **argv);
// Returns zero on failure. Any failure makes this session terminal.
uint64_t plew_llvm_jit_lookup(PlewLlvmJit *jit, const char *name);

#ifdef __cplusplus
}
#endif
#endif
