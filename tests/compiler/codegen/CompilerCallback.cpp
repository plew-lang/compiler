#include "../../../native/llvm_backend.h"
#include <cassert>
#include <cstdio>
extern "C" int plew_compiler_jit_defer(PlewLlvmJit *, const char *, uint64_t, uint64_t);
extern "C" int plew_compiler_prepare_body(uint64_t, uint64_t, LLVMModuleRef *, LLVMContextRef *);
extern "C" int exerciseCompilerCallback(uint64_t address) {
  assert(address);
  auto target = reinterpret_cast<int64_t (*)(int64_t)>(address);
  assert(target(41) == 42);
  assert(target(72) == 73);
  return 0;
}
extern "C" int rejectCompilerCallback(uint64_t session) {
  LLVMModuleRef module = nullptr;
  LLVMContextRef context = nullptr;
  assert(plew_compiler_prepare_body(session, 1, &module, &context) != 0);
  assert(!module && !context);
  return 0;
}
