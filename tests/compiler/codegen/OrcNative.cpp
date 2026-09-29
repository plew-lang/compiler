#include "../../../native/llvm_backend.h"
#include <cassert>
#include <cstdint>

static int hostCalls;
extern "C" int64_t hostBump() { return ++hostCalls; }

static void addStorage(PlewLlvmJit *jit) {
  auto context = LLVMContextCreate();
  auto module = LLVMModuleCreateWithNameInContext("storage", context);
  auto type = LLVMInt64TypeInContext(context);
  auto global = LLVMAddGlobal(module, type, "counter");
  LLVMSetInitializer(global, LLVMConstInt(type, 40, 0));
  assert(plew_llvm_jit_add(jit, module, context) == 0);
}

static void addNext(PlewLlvmJit *jit) {
  auto context = LLVMContextCreate();
  auto module = LLVMModuleCreateWithNameInContext("callee", context);
  auto type = LLVMInt64TypeInContext(context);
  auto signature = LLVMFunctionType(type, nullptr, 0, 0);
  auto host = LLVMAddFunction(module, "hostBump", signature);
  auto function = LLVMAddFunction(module, "next", signature);
  auto global = LLVMAddGlobal(module, type, "counter");
  auto builder = LLVMCreateBuilderInContext(context);
  LLVMPositionBuilderAtEnd(builder, LLVMAppendBasicBlockInContext(context, function, "entry"));
  LLVMBuildCall2(builder, signature, host, nullptr, 0, "");
  auto old = LLVMBuildLoad2(builder, type, global, "old");
  auto value = LLVMBuildAdd(builder, old, LLVMConstInt(type, 1, 0), "value");
  LLVMBuildStore(builder, value, global);
  LLVMBuildRet(builder, value);
  LLVMDisposeBuilder(builder);
  assert(plew_llvm_jit_add(jit, module, context) == 0);
}

static void addEntry(PlewLlvmJit *jit) {
  auto context = LLVMContextCreate();
  auto module = LLVMModuleCreateWithNameInContext("caller", context);
  auto signature = LLVMFunctionType(LLVMInt64TypeInContext(context), nullptr, 0, 0);
  auto next = LLVMAddFunction(module, "next", signature);
  auto function = LLVMAddFunction(module, "entry", signature);
  auto builder = LLVMCreateBuilderInContext(context);
  LLVMPositionBuilderAtEnd(builder, LLVMAppendBasicBlockInContext(context, function, "entry"));
  LLVMBuildCall2(builder, signature, next, nullptr, 0, "");
  LLVMBuildRet(builder, LLVMBuildCall2(builder, signature, next, nullptr, 0, "value"));
  LLVMDisposeBuilder(builder);
  assert(plew_llvm_jit_add(jit, module, context) == 0);
}

int main() {
  auto jit = plew_llvm_jit_create();
  assert(jit);
  assert(plew_llvm_jit_define(jit, "hostBump", reinterpret_cast<uintptr_t>(&hostBump), 1) == 0);
  addEntry(jit); // Definitions may arrive in either dependency order.
  addStorage(jit);
  addNext(jit);
  assert(hostCalls == 0);
  auto address = plew_llvm_jit_lookup(jit, "entry");
  assert(address && hostCalls == 0);
  auto entry = reinterpret_cast<int64_t (*)()>(static_cast<uintptr_t>(address));
  assert(entry() == 42 && hostCalls == 2);
  assert(entry() == 44 && hostCalls == 4);
  assert(plew_llvm_jit_lookup(jit, "entry") == address);
  assert(plew_llvm_jit_lookup(jit, "missing") == 0);
  assert(plew_llvm_jit_lookup(jit, "entry") == 0);
  auto context = LLVMContextCreate();
  auto module = LLVMModuleCreateWithNameInContext("rejected", context);
  assert(plew_llvm_jit_add(jit, module, context) != 0); // Still consumes both.
  plew_llvm_jit_destroy(jit);

  jit = plew_llvm_jit_create();
  assert(jit);
  assert(plew_llvm_jit_define(jit, "hostBump", reinterpret_cast<uintptr_t>(&hostBump), 1) == 0);
  assert(plew_llvm_jit_define(jit, "hostBump", reinterpret_cast<uintptr_t>(&hostBump), 1) != 0);
  assert(plew_llvm_jit_lookup(jit, "hostBump") == 0);
  plew_llvm_jit_destroy(jit);

  jit = plew_llvm_jit_create();
  assert(jit);
  context = LLVMContextCreate();
  module = LLVMModuleCreateWithNameInContext("invalid", context);
  auto signature = LLVMFunctionType(LLVMVoidTypeInContext(context), nullptr, 0, 0);
  auto broken = LLVMAddFunction(module, "broken", signature);
  LLVMAppendBasicBlockInContext(context, broken, "unterminated");
  assert(plew_llvm_jit_add(jit, module, context) != 0);
  assert(plew_llvm_jit_lookup(jit, "broken") == 0);
  plew_llvm_jit_destroy(jit);
}
