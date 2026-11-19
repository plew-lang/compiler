// The producer borrows its module: successful and failed output must leave it
// alive, native-targeted and disposable exactly once by the caller.
#include "../../../native/llvm_backend.h"
#include <llvm-c/Analysis.h>
#include <llvm-c/TargetMachine.h>
#include <cstdio>
#include <cstring>
#include <string>

int main(int argc, char **argv) {
  if (argc != 2) return 2;
  LLVMContextRef context = LLVMContextCreate();
  LLVMModuleRef module = LLVMModuleCreateWithNameInContext("borrowed", context);
  auto type = LLVMFunctionType(LLVMInt32TypeInContext(context), nullptr, 0, 0);
  auto function = LLVMAddFunction(module, "main", type);
  auto block = LLVMAppendBasicBlockInContext(context, function, "entry");
  auto builder = LLVMCreateBuilderInContext(context);
  LLVMPositionBuilderAtEnd(builder, block);
  LLVMBuildRet(builder, LLVMConstInt(LLVMInt32TypeInContext(context), 0, 0));
  LLVMDisposeBuilder(builder);
  char *native = LLVMGetDefaultTargetTriple();
  const std::string directory(argv[1]);
  bool valid = true;
  auto alive = [&] {
    char *error = nullptr;
    bool result = LLVMVerifyModule(module, LLVMReturnStatusAction, &error) == 0 &&
        LLVMGetFirstFunction(module) == function && std::strcmp(LLVMGetTarget(module), native) == 0;
    LLVMDisposeMessage(error);
    return result;
  };
  valid = plew_llvm_emit_thinlto_object(module, (directory + "/lifetime-thin.o").c_str(), "", 0) == 0 && alive();
  valid = valid && plew_llvm_emit_object(module, (directory + "/lifetime-machine.o").c_str(), "", 0) == 0 && alive();
  valid = valid && plew_llvm_emit_thinlto_object(module, (directory + "/missing/lifetime.o").c_str(), "", 0) != 0 && alive();
  LLVMDisposeMessage(native);
  LLVMDisposeModule(module);
  LLVMContextDispose(context);
  if (!valid) return 1;
  std::puts("PASS borrowed module remains live");
  return 0;
}
