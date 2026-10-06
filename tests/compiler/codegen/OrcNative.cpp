#include "../../../native/llvm_backend.h"
#include <cassert>
#include <cstdint>
#include <cstring>

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

static void checkMemoryIntrinsics() {
  auto jit = plew_llvm_jit_create();
  assert(jit);
  auto context = LLVMContextCreate();
  auto module = LLVMModuleCreateWithNameInContext("memory", context);
  auto pointer = LLVMPointerTypeInContext(context, 0);
  LLVMTypeRef parameters[] = {pointer, pointer, LLVMInt64TypeInContext(context)};
  auto signature = LLVMFunctionType(LLVMVoidTypeInContext(context), parameters, 3, 0);
  auto function = LLVMAddFunction(module, "copyMoveClear", signature);
  auto builder = LLVMCreateBuilderInContext(context);
  LLVMPositionBuilderAtEnd(builder, LLVMAppendBasicBlockInContext(context, function, "entry"));
  auto destination = LLVMGetParam(function, 0);
  auto source = LLVMGetParam(function, 1);
  auto size = LLVMGetParam(function, 2);
  LLVMBuildMemCpy(builder, destination, 1, source, 1, size);
  LLVMBuildMemSet(builder, source, LLVMConstInt(LLVMInt8TypeInContext(context), 0, 0), size, 1);
  LLVMBuildMemMove(builder, source, 1, destination, 1, size);
  LLVMBuildRetVoid(builder);
  LLVMDisposeBuilder(builder);
  // The input IR contains intrinsics, not explicit libc imports.
  assert(!LLVMGetNamedFunction(module, "memcpy"));
  assert(!LLVMGetNamedFunction(module, "memmove"));
  assert(!LLVMGetNamedFunction(module, "memset"));
  assert(plew_llvm_jit_add(jit, module, context) == 0);
  auto address = plew_llvm_jit_lookup(jit, "copyMoveClear");
  assert(address);
  auto execute = reinterpret_cast<void (*)(void *, void *, uint64_t)>(static_cast<uintptr_t>(address));
  unsigned char sourceBytes[513], destinationBytes[513];
  for (unsigned i = 0; i < sizeof(sourceBytes); ++i) sourceBytes[i] = i % 251;
  execute(destinationBytes, sourceBytes, sizeof(sourceBytes));
  for (unsigned i = 0; i < sizeof(sourceBytes); ++i) {
    assert(sourceBytes[i] == i % 251);
    assert(destinationBytes[i] == i % 251);
  }
  // Runtime support does not make unrelated process symbols available.
  assert(plew_llvm_jit_lookup(jit, "hostBump") == 0);
  plew_llvm_jit_destroy(jit);
}

int main() {
  checkMemoryIntrinsics();
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
