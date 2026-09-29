#include "../../../native/llvm_backend.h"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <thread>
#include <unordered_map>

struct State {
  int calls[5] = {};
  PlewLlvmJit *jit = nullptr;
  std::thread::id thread = std::this_thread::get_id();
  bool fail = false;
};
static std::unordered_map<uint64_t, State *> sessions;
static int prepare(uint64_t session, uint64_t body, LLVMModuleRef *out,
                   LLVMContextRef *context) {
  auto found = sessions.find(session);
  assert(found != sessions.end());
  auto &state = *found->second;
  assert(state.thread == std::this_thread::get_id());
  assert(body < 4 && ++state.calls[body] == 1);
  *context = LLVMContextCreate();
  *out = LLVMModuleCreateWithNameInContext("requested", *context);
  if (state.fail) return 1; // Failure still transfers allocated handles.
  if (body == 3) {
    auto real = LLVMDoubleTypeInContext(*context);
    LLVMTypeRef arguments[10];
    for (auto &argument : arguments) argument = real;
    auto signature = LLVMFunctionType(real, arguments, 10, 0);
    auto function = LLVMAddFunction(*out, "floating", signature);
    auto builder = LLVMCreateBuilderInContext(*context);
    LLVMPositionBuilderAtEnd(builder, LLVMAppendBasicBlockInContext(*context, function, "entry"));
    LLVMBuildRet(builder, LLVMBuildFAdd(builder, LLVMGetParam(function, 0), LLVMGetParam(function, 9), ""));
    LLVMDisposeBuilder(builder);
    return 0;
  }
  auto integer = LLVMInt64TypeInContext(*context);
  auto signature = LLVMFunctionType(integer, &integer, 1, 0);
  const char *names[] = {"first", "second", "identity"};
  auto function = LLVMAddFunction(*out, names[body], signature);
  auto builder = LLVMCreateBuilderInContext(*context);
  LLVMPositionBuilderAtEnd(builder, LLVMAppendBasicBlockInContext(*context, function, "entry"));
  auto argument = LLVMGetParam(function, 0);
  if (body == 0) {
    assert(plew_llvm_jit_defer(state.jit, "second", 1, prepare, session) == 0);
    auto second = LLVMAddFunction(*out, "second", signature);
    LLVMBuildRet(builder, LLVMBuildCall2(builder, signature, second, &argument, 1, ""));
  } else if (body == 1) {
    LLVMBuildRet(builder, LLVMBuildAdd(builder, argument, LLVMConstInt(integer, 1, 0), ""));
  } else {
    LLVMBuildRet(builder, LLVMBuildPtrToInt(builder, function, integer, ""));
  }
  LLVMDisposeBuilder(builder);
  return 0;
}
int main(int argc, char **argv) {
  State state;
  constexpr uint64_t session = UINT64_C(0xf000000100000003);
  sessions.emplace(session, &state);
  state.fail = argc > 1 && std::strcmp(argv[1], "fail") == 0;
  auto jit = plew_llvm_jit_create();
  assert(jit);
  state.jit = jit;
  assert(plew_llvm_jit_defer(jit, "first", 0, prepare, session) == 0);
  assert(plew_llvm_jit_defer(jit, "unused", 4, prepare, session) == 0);
  assert(plew_llvm_jit_defer(jit, "identity", 2, prepare, session) == 0);
  assert(plew_llvm_jit_defer(jit, "floating", 3, prepare, session) == 0);
  auto address = plew_llvm_jit_lookup(jit, "first");
  auto identity = plew_llvm_jit_lookup(jit, "identity");
  assert(address && identity && state.calls[0] == 0 && state.calls[1] == 0 && state.calls[2] == 0);
  auto first = reinterpret_cast<uint64_t (*)(uint64_t)>(address);
  assert(first(41) == 42);
  assert(first(72) == 73 && state.calls[0] == 1 && state.calls[1] == 1 && state.calls[2] == 0);
  auto self = reinterpret_cast<uint64_t (*)(uint64_t)>(identity);
  assert(self(0) == identity && self(0) == identity && state.calls[2] == 1);
  assert(plew_llvm_jit_lookup(jit, "first") == address);
  auto floating = reinterpret_cast<double (*)(double,double,double,double,double,double,double,double,double,double)>(plew_llvm_jit_lookup(jit, "floating"));
  assert(state.calls[3] == 0);
  assert(floating(1.25,2,3,4,5,6,7,8,9,10.5) == 11.75);
  assert(floating(2.25,2,3,4,5,6,7,8,9,20.5) == 22.75 && state.calls[3] == 1);
  assert(!plew_llvm_jit_failed(jit));
  plew_llvm_jit_destroy(jit);
  sessions.erase(session);
}
