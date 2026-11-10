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

LLVMValueRef plew_test_signature_function(LLVMModuleRef module, LLVMTypeRef aggregate) {
    LLVMContextRef context = LLVMGetModuleContext(module);
    LLVMTypeRef parameters[] = { LLVMPointerTypeInContext(context, 0), LLVMInt64TypeInContext(context), LLVMPointerTypeInContext(context, 0) };
    LLVMValueRef function = LLVMAddFunction(module, "typed-input", LLVMFunctionType(LLVMVoidTypeInContext(context), parameters, 3, 0));
    unsigned byval = LLVMGetEnumAttributeKindForName("byval", 5);
    LLVMAddAttributeAtIndex(function, 1, LLVMCreateTypeAttribute(context, byval, aggregate));
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);
    LLVMPositionBuilderAtEnd(builder, LLVMAppendBasicBlockInContext(context, function, "entry"));
    LLVMBuildRetVoid(builder);
    LLVMDisposeBuilder(builder);
    return function;
}
LLVMValueRef plew_test_signature_value(LLVMValueRef function, LLVMTypeRef type, unsigned kind) {
    if (kind < 3) return LLVMGetParam(function, kind);
    if (kind == 3) return LLVMGetUndef(type);
    LLVMContextRef context = LLVMGetTypeContext(type);
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);
    LLVMBasicBlockRef block = LLVMGetEntryBasicBlock(function);
    LLVMPositionBuilderBefore(builder, LLVMGetFirstInstruction(block));
    LLVMValueRef value = LLVMBuildAlloca(builder, type, "home");
    LLVMDisposeBuilder(builder);
    return value;
}
LLVMValueRef plew_test_signature_constant(LLVMModuleRef module, unsigned kind) {
    LLVMContextRef context = LLVMGetModuleContext(module);
    LLVMTypeRef scalar = LLVMInt64TypeInContext(context);
    LLVMValueRef global = LLVMAddGlobal(module, scalar, "provenance-global");
    LLVMSetInitializer(global, LLVMConstInt(scalar, 0, 0));
    if (kind == 0) return global;
    LLVMValueRef offset = LLVMConstInt(scalar, 1, 0);
    LLVMValueRef expression = LLVMConstGEP2(scalar, global, &offset, 1);
    if (kind == 1) return expression;
    return LLVMConstStructInContext(context, &expression, 1, 0);
}

LLVMValueRef plew_test_signature_byref_function(LLVMModuleRef module, LLVMTypeRef aggregate, unsigned long long alignment) {
    LLVMContextRef context = LLVMGetModuleContext(module);
    LLVMTypeRef pointer = LLVMPointerTypeInContext(context, 0);
    LLVMValueRef function = LLVMAddFunction(module, "guaranteed-input", LLVMFunctionType(LLVMVoidTypeInContext(context), &pointer, 1, 0));
    LLVMAddAttributeAtIndex(function, 1, LLVMCreateTypeAttribute(context, LLVMGetEnumAttributeKindForName("byref", 5), aggregate));
    LLVMAddAttributeAtIndex(function, 1, LLVMCreateEnumAttribute(context, LLVMGetEnumAttributeKindForName("align", 5), alignment));
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);
    LLVMPositionBuilderAtEnd(builder, LLVMAppendBasicBlockInContext(context, function, "entry"));
    LLVMBuildRetVoid(builder);
    LLVMDisposeBuilder(builder);
    return function;
}

void plew_test_projected_homes(void) {
    LLVMContextRef context = LLVMContextCreate();
    LLVMModuleRef module = plew_test_signature_module(context);
    LLVMTypeRef integer = LLVMInt64TypeInContext(context);
    LLVMTypeRef pairFields[] = { integer, integer };
    LLVMTypeRef pair = LLVMStructTypeInContext(context, pairFields, 2, 0);
    LLVMTypeRef fields[] = { pair, pair };
    LLVMTypeRef holder = LLVMStructTypeInContext(context, fields, 2, 0);
    LLVMValueRef function = LLVMAddFunction(module, "projection-controls", LLVMFunctionType(LLVMVoidTypeInContext(context), 0, 0, 0));
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);
    LLVMPositionBuilderAtEnd(builder, LLVMAppendBasicBlockInContext(context, function, "entry"));
    LLVMValueRef root = LLVMBuildAlloca(builder, holder, "root");
    LLVMSetAlignment(root, 8);
    LLVMValueRef other = LLVMBuildAlloca(builder, holder, "other");
    LLVMValueRef field = LLVMBuildStructGEP2(builder, holder, root, 1, "field");
    LLVMValueRef nested = LLVMBuildStructGEP2(builder, pair, field, 0, "nested");
    const uint64_t indices[] = { 1, 0 };
    const uint64_t wrong[] = { 0, 0 };
    assert(plew_llvm_home_type_matches(field, pair));
    assert(plew_llvm_home_alignment(field) == 8);
    assert(plew_llvm_projected_home_matches(field, root, holder, indices, 1, pair));
    assert(plew_llvm_projected_home_matches(nested, root, holder, indices, 2, integer));
    assert(!plew_llvm_projected_home_matches(nested, other, holder, indices, 2, integer));
    assert(!plew_llvm_projected_home_matches(nested, root, holder, wrong, 2, integer));
    assert(!plew_llvm_projected_home_matches(nested, root, holder, indices, 1, integer));
    assert(!plew_llvm_projected_home_matches(nested, root, pair, indices, 2, integer));
    assert(!plew_llvm_projected_home_matches(nested, root, holder, indices, 2, pair));
    LLVMValueRef offset = LLVMConstInt(integer, 1, 0);
    LLVMValueRef stepped = LLVMBuildGEP2(builder, holder, root, &offset, 1, "stepped");
    assert(!plew_llvm_home_type_matches(stepped, holder));
    LLVMSetAlignment(root, 1);
    assert(plew_llvm_home_alignment(field) == 1);
    LLVMBuildRetVoid(builder);
    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);
    LLVMContextDispose(context);
}
