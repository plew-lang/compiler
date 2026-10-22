#include "../../../native/llvm_backend.h"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <string>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>

static int hostCalls;
extern "C" int64_t hostBump() { return ++hostCalls; }

static std::string nativeLayout() {
  char *triple = LLVMGetDefaultTargetTriple();
  LLVMTargetRef target = nullptr;
  char *error = nullptr;
  assert(LLVMGetTargetFromTriple(triple, &target, &error) == 0);
  auto machine = LLVMCreateTargetMachine(target, triple, "", "",
      LLVMCodeGenLevelDefault, LLVMRelocPIC, LLVMCodeModelDefault);
  assert(machine);
  auto layout = LLVMCreateTargetDataLayout(machine);
  char *text = LLVMCopyStringRepOfTargetData(layout);
  std::string result(text);
  LLVMDisposeMessage(text);
  LLVMDisposeTargetData(layout);
  LLVMDisposeTargetMachine(machine);
  LLVMDisposeMessage(triple);
  return result;
}

static LLVMModuleRef layoutModule(LLVMContextRef context, const char *layout) {
  auto module = LLVMModuleCreateWithNameInContext("layout", context);
  if (layout) LLVMSetDataLayout(module, layout);
  auto type = LLVMInt64TypeInContext(context);
  auto signature = LLVMFunctionType(type, nullptr, 0, 0);
  auto function = LLVMAddFunction(module, "layoutValue", signature);
  auto builder = LLVMCreateBuilderInContext(context);
  LLVMPositionBuilderAtEnd(builder, LLVMAppendBasicBlockInContext(context, function, "entry"));
  LLVMBuildRet(builder, LLVMConstInt(type, 7, 0));
  LLVMDisposeBuilder(builder);
  return module;
}

static LLVMModuleRef layoutDeclarationModule(LLVMContextRef context, const char *layout) {
  auto module = LLVMModuleCreateWithNameInContext("layout-declarations", context);
  if (layout) LLVMSetDataLayout(module, layout);
  auto integer = LLVMInt64TypeInContext(context);
  auto signature = LLVMFunctionType(integer, nullptr, 0, 0);
  auto function = LLVMAddFunction(module, "layoutDeclaration", signature);
  auto identity = LLVMValueAsMetadata(LLVMConstInt(integer, 1, 0));
  LLVMGlobalSetMetadata(function, LLVMGetMDKindIDInContext(context, "plew.body", 9),
                        LLVMMDNodeInContext2(context, &identity, 1));
  return module;
}

static int unusedPrepare(uint64_t, uint64_t, LLVMModuleRef *, LLVMContextRef *) {
  assert(false && "declaration registration and lookup must not prepare a body");
  return 1;
}

static void checkLayouts(const char *objectPath) {
  auto initializer = plew_llvm_jit_create();
  assert(initializer);
  plew_llvm_jit_destroy(initializer);
  const auto native = nativeLayout();
  for (const char *layout : {static_cast<const char *>(nullptr), native.c_str(), "e-p:32:32"}) {
    bool compatible = !layout || native == layout;
    auto context = LLVMContextCreate();
    auto module = layoutModule(context, layout);
    auto previous = std::fopen(objectPath, "wb");
    assert(previous);
    assert(std::fwrite("kept", 1, 4, previous) == 4);
    std::fclose(previous);
    assert((plew_llvm_emit_object(module, objectPath, "", 0) == 0) == compatible);
    if (!compatible) {
      // Object output borrows the pair and preserves both layout and output.
      assert(std::strcmp(LLVMGetDataLayoutStr(module), layout) == 0);
      char bytes[5] = {};
      auto file = std::fopen(objectPath, "rb");
      assert(file && std::fread(bytes, 1, 5, file) == 4);
      std::fclose(file);
      assert(std::strcmp(bytes, "kept") == 0);
    }
    LLVMDisposeModule(module);
    LLVMContextDispose(context);

    auto jit = plew_llvm_jit_create();
    assert(jit);
    context = LLVMContextCreate();
    module = layoutModule(context, layout);
    // Admission consumes both handles on success and failure; ASan/LSan checks cleanup.
    assert((plew_llvm_jit_add(jit, module, context) == 0) == compatible);
    assert(bool(plew_llvm_jit_failed(jit)) == !compatible);
    if (compatible) {
      auto address = plew_llvm_jit_lookup(jit, "layoutValue");
      assert(address);
      auto execute = reinterpret_cast<int64_t (*)()>(static_cast<uintptr_t>(address));
      assert(execute() == 7);
    } else {
      assert(plew_llvm_jit_lookup(jit, "layoutValue") == 0);
    }
    plew_llvm_jit_destroy(jit);

    jit = plew_llvm_jit_create();
    assert(jit);
    context = LLVMContextCreate();
    module = layoutDeclarationModule(context, layout);
    const char *label = !layout ? "absent" : compatible ? "matching" : "incompatible";
    std::fprintf(stderr, "CHECK declaration-layout %s\n", label);
    assert((plew_llvm_jit_declarations(jit, module, context, unusedPrepare, 0) == 0) == compatible);
    assert(bool(plew_llvm_jit_failed(jit)) == !compatible);
    assert(bool(plew_llvm_jit_lookup(jit, "layoutDeclaration")) == compatible);
    std::fprintf(stderr, "END declaration-layout %s\n", label);
    plew_llvm_jit_destroy(jit);
  }
  std::remove(objectPath);
}

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

int main(int argc, char **argv) {
  assert(argc == 2);
  checkLayouts(argv[1]);
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
