#include "../../../native/llvm_backend.h"
#include <cassert>
#include <cstdio>
extern "C" int plew_compiler_jit_defer(PlewLlvmJit *, const char *, uint64_t, uint64_t);
extern "C" int plew_compiler_prepare_body(uint64_t, uint64_t, LLVMModuleRef *, LLVMContextRef *);
extern "C" int exerciseCompilerCallback(uint64_t session, uint64_t body) {
  auto *jit = plew_llvm_jit_create();
  assert(jit);
  char name[80];
  std::snprintf(name, sizeof(name), "plew.body.gf%llu", (unsigned long long)body);
  assert(plew_compiler_jit_defer(jit, name, body, session) == 0);
  auto address = plew_llvm_jit_lookup(jit, name);
  assert(address);
  auto target = reinterpret_cast<int64_t (*)(int64_t)>(address);
  assert(target(41) == 41);
  assert(target(72) == 72);
  assert(!plew_llvm_jit_failed(jit));
  plew_llvm_jit_destroy(jit);
  return 0;
}
extern "C" int rejectCompilerCallback(uint64_t session) {
  LLVMModuleRef module = nullptr;
  LLVMContextRef context = nullptr;
  assert(plew_compiler_prepare_body(session, 1, &module, &context) != 0);
  assert(!module && !context);
  return 0;
}
