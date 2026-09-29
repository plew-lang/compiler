// Product compiler adapter. The generic ORC bridge never owns Plew values.
#include "llvm_backend.h"
extern "C" int plew_compiler_prepare_body(uint64_t session, uint64_t body,
                                         LLVMModuleRef *module,
                                         LLVMContextRef *context);
extern "C" int plew_compiler_jit_defer(PlewLlvmJit *jit, const char *name,
                                      uint64_t body, uint64_t session) {
  return plew_llvm_jit_defer(jit, name, body, plew_compiler_prepare_body, session);
}
