#include "../../../native/llvm_backend.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>

static int unusedPrepare(uint64_t, uint64_t, LLVMModuleRef *, LLVMContextRef *) {
  return 1;
}

// Each call uses a fresh context. Named struct spellings must not establish ABI
// identity, and equally sized but differently structured payloads must differ.
static LLVMModuleRef declaration(PlewLlvmJit *jit, LLVMContextRef context,
                                 unsigned shape, bool second) {
  auto module = LLVMModuleCreateWithNameInContext("source-abi", context);
  auto triple = plew_llvm_jit_target_triple(jit);
  auto layout = plew_llvm_jit_data_layout(jit);
  LLVMSetTarget(module, triple);
  LLVMSetDataLayout(module, layout);
  LLVMDisposeMessage(triple);
  LLVMDisposeMessage(layout);
  auto integer = LLVMInt64TypeInContext(context);
  auto result = shape == 1 ? LLVMInt32TypeInContext(context) : integer;
  auto parameter = shape == 2 ? LLVMInt32TypeInContext(context) : integer;
  LLVMTypeRef payload = nullptr;
  if (shape >= 7) {
    parameter = LLVMPointerTypeInContext(context, 0);
    payload = LLVMStructCreateNamed(context, second ? "OtherName" : "FirstName");
    LLVMTypeRef fields[] = {shape == 8 ? LLVMInt32TypeInContext(context) : integer,
                            LLVMInt32TypeInContext(context)};
    LLVMStructSetBody(payload, fields, shape == 8 ? 2 : 1, shape == 9);
  }
  auto function = LLVMAddFunction(module, "entry", LLVMFunctionType(result, &parameter, 1, shape == 3));
  if (shape == 4) LLVMSetFunctionCallConv(function, 8); // fastcc
  if (shape == 5 || shape == 6) {
    const char *name = shape == 5 ? "signext" : "zeroext";
    auto kind = LLVMGetEnumAttributeKindForName(name, std::strlen(name));
    LLVMAddAttributeAtIndex(function, shape == 5 ? LLVMAttributeReturnIndex : 1,
                            LLVMCreateEnumAttribute(context, kind, 0));
  }
  if (shape == 12) {
    uint64_t lower = 0, upper = 10;
    auto kind = LLVMGetEnumAttributeKindForName("range", 5);
    LLVMAddAttributeAtIndex(function, LLVMAttributeReturnIndex,
                            LLVMCreateConstantRangeAttribute(context, kind, 64, &lower, &upper));
  }
  if (payload) {
    auto kind = LLVMGetEnumAttributeKindForName("byval", 5);
    LLVMAddAttributeAtIndex(function, 1, LLVMCreateTypeAttribute(context, kind, payload));
    if (shape == 10 || shape == 11) {
      auto alignment = LLVMGetEnumAttributeKindForName("align", 5);
      LLVMAddAttributeAtIndex(function, 1, LLVMCreateEnumAttribute(context, alignment, shape == 10 ? 8 : 16));
    }
  }
  auto identity = LLVMValueAsMetadata(LLVMConstInt(integer, 1, 0));
  LLVMGlobalSetMetadata(function, LLVMGetMDKindIDInContext(context, "plew.body", 9),
                        LLVMMDNodeInContext2(context, &identity, 1));
  return module;
}

static void check(unsigned firstShape, unsigned secondShape, bool accepted) {
  auto jit = plew_llvm_jit_create();
  if (!jit) std::abort();
  auto first = LLVMContextCreate();
  auto module = declaration(jit, first, firstShape, false);
  if (plew_llvm_jit_declarations(jit, module, first, unusedPrepare, 17)) std::abort();
  auto second = LLVMContextCreate();
  module = declaration(jit, second, secondShape, true);
  const auto actual = plew_llvm_jit_declarations(jit, module, second, unusedPrepare, 17) == 0;
  if (actual != accepted || (plew_llvm_jit_failed(jit) != 0) == accepted) {
    std::fprintf(stderr, "source ABI case %u/%u expected accepted=%d\n", firstShape, secondShape, accepted);
    std::exit(2);
  }
  plew_llvm_jit_destroy(jit);
}

static void checkMissingIdentity(bool main) {
  auto jit = plew_llvm_jit_create();
  if (!jit) std::abort();
  auto first = LLVMContextCreate();
  auto module = declaration(jit, first, 0, false);
  if (main) {
    LLVMTypeRef parameters[] = {LLVMInt32TypeInContext(first), LLVMPointerTypeInContext(first, 0)};
    auto function = LLVMAddFunction(module, "main", LLVMFunctionType(parameters[0], parameters, 2, 0));
    auto identity = LLVMValueAsMetadata(LLVMConstInt(LLVMInt64TypeInContext(first), 2, 0));
    LLVMGlobalSetMetadata(function, LLVMGetMDKindIDInContext(first, "plew.body", 9), LLVMMDNodeInContext2(first, &identity, 1));
  }
  if (plew_llvm_jit_declarations(jit, module, first, unusedPrepare, 17)) std::abort();
  auto second = LLVMContextCreate();
  module = declaration(jit, second, 0, true);
  if (main) {
    LLVMAddFunction(module, "main", LLVMFunctionType(LLVMInt32TypeInContext(second), nullptr, 0, 0));
  } else {
    LLVMGlobalEraseMetadata(LLVMGetNamedFunction(module, "entry"), LLVMGetMDKindIDInContext(second, "plew.body", 9));
  }
  if (!plew_llvm_jit_declarations(jit, module, second, unusedPrepare, 17) || !plew_llvm_jit_failed(jit)) {
    std::fputs("source declaration lost required identity\n", stderr);
    std::exit(2);
  }
  plew_llvm_jit_destroy(jit);
}

static PlewLlvmJit *activeJit;
static unsigned preparedShape;
static bool eraseIdentity;
static unsigned dependencyMode;
static void dependency(LLVMModuleRef module, LLVMContextRef context, bool prepared) {
  auto integer = LLVMInt64TypeInContext(context);
  auto result = prepared ? LLVMInt32TypeInContext(context) : integer;
  auto function = LLVMAddFunction(module, "dependency", LLVMFunctionType(result, nullptr, 0, 0));
  if (!prepared || dependencyMode == 1) {
    auto identity = LLVMValueAsMetadata(LLVMConstInt(integer, 2, 0));
    LLVMGlobalSetMetadata(function, LLVMGetMDKindIDInContext(context, "plew.body", 9), LLVMMDNodeInContext2(context, &identity, 1));
  } else if (dependencyMode == 3) {
    LLVMGlobalSetMetadata(function, LLVMGetMDKindIDInContext(context, "plew.host", 9), LLVMMDNodeInContext2(context, nullptr, 0));
  }
}
static int prepareEntry(uint64_t, uint64_t, LLVMModuleRef *module, LLVMContextRef *context) {
  *context = LLVMContextCreate();
  *module = declaration(activeJit, *context, preparedShape, true);
  auto function = LLVMGetNamedFunction(*module, "entry");
  auto builder = LLVMCreateBuilderInContext(*context);
  LLVMPositionBuilderAtEnd(builder, LLVMAppendBasicBlockInContext(*context, function, "entry"));
  LLVMBuildRet(builder, LLVMGetParam(function, 0));
  LLVMDisposeBuilder(builder);
  if (eraseIdentity)
    LLVMGlobalEraseMetadata(function, LLVMGetMDKindIDInContext(*context, "plew.body", 9));
  if (dependencyMode) dependency(*module, *context, true);
  return 0;
}

int main(int argc, char **argv) {
  if (argc > 1) {
    preparedShape = std::strcmp(argv[1], "--requested-bad") == 0 ? 6 : 0;
    eraseIdentity = std::strcmp(argv[1], "--requested-missing-identity") == 0;
    dependencyMode = std::strcmp(argv[1], "--requested-dependency-bad") == 0 ? 1
                   : std::strcmp(argv[1], "--requested-dependency-missing-identity") == 0 ? 2
                   : std::strcmp(argv[1], "--requested-dependency-host") == 0 ? 3 : 0;
    activeJit = plew_llvm_jit_create();
    if (!activeJit) std::abort();
    auto context = LLVMContextCreate();
    auto module = declaration(activeJit, context, 0, false);
    if (dependencyMode) dependency(module, context, false);
    if (plew_llvm_jit_declarations(activeJit, module, context, prepareEntry, 17)) std::abort();
    auto address = plew_llvm_jit_lookup(activeJit, "entry");
    if (!address) std::abort();
    auto call = reinterpret_cast<uint64_t (*)(uint64_t)>(static_cast<uintptr_t>(address));
    if (call(9) != 9 || plew_llvm_jit_failed(activeJit)) std::abort();
    plew_llvm_jit_destroy(activeJit);
    std::puts("ok");
    return 0;
  }
  check(0, 0, true);
  for (unsigned shape = 1; shape <= 6; ++shape) check(0, shape, false);
  check(7, 7, true);
  check(7, 8, false); // same byte size, distinct byval type structure
  check(7, 9, false); // packedness
  check(10, 10, true);
  check(10, 11, false); // numeric parameter attribute payload
  checkMissingIdentity(false);
  checkMissingIdentity(true); // must not silently change the saved main arity
  auto jit = plew_llvm_jit_create();
  if (!jit) std::abort();
  auto context = LLVMContextCreate();
  auto module = declaration(jit, context, 12, false);
  if (!plew_llvm_jit_declarations(jit, module, context, unusedPrepare, 17) || !plew_llvm_jit_failed(jit)) std::abort();
  plew_llvm_jit_destroy(jit); // unimplemented range payloads must not compare by kind only
  std::puts("ok");
}
