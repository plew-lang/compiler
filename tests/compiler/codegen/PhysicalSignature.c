#include <llvm-c/Core.h>
#include <llvm-c/TargetMachine.h>
#include "../../../native/llvm_backend.h"
#include <assert.h>

LLVMModuleRef plew_test_signature_module(LLVMContextRef context) {
    LLVMModuleRef module = LLVMModuleCreateWithNameInContext("signature-test", context);
    char *triple = LLVMGetDefaultTargetTriple();
    char *layout = plew_llvm_native_data_layout("generic");
    assert(triple && *triple && layout && *layout);
    LLVMSetTarget(module, triple);
    LLVMSetDataLayout(module, layout);
    LLVMDisposeMessage(triple);
    LLVMDisposeMessage(layout);
    return module;
}
LLVMModuleRef plew_test_signature_blank_module(LLVMContextRef context) {
    return LLVMModuleCreateWithNameInContext("targetless", context);
}
LLVMTypeRef plew_test_signature_type(LLVMContextRef context, unsigned kind) {
    LLVMTypeRef scalar = LLVMInt64TypeInContext(context);
    switch (kind) {
        case 0: return LLVMVoidTypeInContext(context);
        case 1: return scalar;
        case 2: return LLVMStructTypeInContext(context, 0, 0, 0);
        case 3: return LLVMStructTypeInContext(context, &scalar, 1, 0);
        case 4: return LLVMPointerTypeInContext(context, 0);
        case 5: return LLVMStructCreateNamed(context, "incomplete");
        default: assert(0); return 0;
    }
}
void plew_test_signature_change_layout(LLVMModuleRef module) {
    LLVMSetDataLayout(module, "e-p:64:64-i64:64-n32:64-S128");
}
