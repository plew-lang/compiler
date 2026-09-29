#include "llvm_backend.h"
#include "llvm_pipeline.h"

#include <llvm-c/Analysis.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/ExecutionEngine/Orc/ThreadSafeModule.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/Error.h>
#include <llvm-c/Error.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>
#include <llvm-c/Transforms/PassBuilder.h>
#include <cstdio>
#include <cstring>
#include <memory>

struct PlewLlvmJit {
  std::unique_ptr<llvm::orc::LLJIT> engine;
  bool failed = false;
};

namespace {
struct MessageDisposer {
  void operator()(char *message) const { LLVMDisposeMessage(message); }
};
using Message = std::unique_ptr<char, MessageDisposer>;

int jitError(PlewLlvmJit *jit, llvm::Error error) {
  if (jit)
    jit->failed = true;
  std::fprintf(stderr, "plew: LLVM JIT failed: %s\n",
               llvm::toString(std::move(error)).c_str());
  return 1;
}

bool verify(LLVMModuleRef module) {
  char *error = nullptr;
  int failed = LLVMVerifyModule(module, LLVMReturnStatusAction, &error);
  Message message(error);
  if (failed)
    std::fprintf(stderr, "plew: invalid LLVM module: %s\n", error);
  return !failed;
}

bool optimize(LLVMModuleRef module, LLVMTargetMachineRef machine,
              const char *pipeline, LLVMPassBuilderOptionsRef options) {
  LLVMErrorRef error = LLVMRunPasses(module, pipeline, machine, options);
  if (!error)
    return true;
  char *message = LLVMGetErrorMessage(error);
  std::fprintf(stderr, "plew: LLVM optimization failed: %s\n", message);
  LLVMDisposeErrorMessage(message);
  return false;
}
} // namespace

extern "C" PlewLlvmJit *plew_llvm_jit_create(void) {
  if (LLVMInitializeNativeTarget() || LLVMInitializeNativeAsmPrinter()) {
    std::fprintf(stderr, "plew: native LLVM JIT target unavailable\n");
    return nullptr;
  }
  auto engine = llvm::orc::LLJITBuilder().setNumCompileThreads(0).create();
  if (!engine) {
    jitError(nullptr, engine.takeError());
    return nullptr;
  }
  auto jit = std::make_unique<PlewLlvmJit>();
  jit->engine = std::move(*engine);
  return jit.release();
}

extern "C" void plew_llvm_jit_destroy(PlewLlvmJit *jit) { delete jit; }

extern "C" int plew_llvm_jit_define(PlewLlvmJit *jit, const char *name,
                                    uint64_t address, int callable) {
  if (!jit || jit->failed)
    return 1;
  if (!name || !*name || !address)
    return jitError(jit, llvm::createStringError("invalid host symbol"));
  auto flags = llvm::JITSymbolFlags::Exported;
  if (callable)
    flags |= llvm::JITSymbolFlags::Callable;
  llvm::orc::SymbolMap symbols;
  symbols[jit->engine->mangleAndIntern(name)] =
      llvm::orc::ExecutorSymbolDef(llvm::orc::ExecutorAddr(address), flags);
  if (auto error = jit->engine->getMainJITDylib().define(
          llvm::orc::absoluteSymbols(std::move(symbols))))
    return jitError(jit, std::move(error));
  return 0;
}

extern "C" int plew_llvm_jit_add(PlewLlvmJit *jit, LLVMModuleRef module,
                                 LLVMContextRef context) {
  // Local ownership covers verification, terminal-session and add failures.
  auto ownedContext = std::unique_ptr<llvm::LLVMContext>(llvm::unwrap(context));
  auto ownedModule = std::unique_ptr<llvm::Module>(llvm::unwrap(module));
  if (!module || !context) {
    if (jit)
      jit->failed = true;
    return 1;
  }
  llvm::orc::ThreadSafeModule owned(std::move(ownedModule), std::move(ownedContext));
  if (!jit || jit->failed)
    return 1;
  if (!verify(module)) {
    jit->failed = true;
    return 1;
  }
  const auto &triple = jit->engine->getTargetTriple();
  const char *actual = LLVMGetTarget(module);
  if (*actual && llvm::Triple(actual) != triple)
    return jitError(jit, llvm::createStringError("module target is not the native JIT target"));
  LLVMSetTarget(module, triple.str().c_str());
  owned.withModuleDo([&](llvm::Module &value) {
    value.setDataLayout(jit->engine->getDataLayout());
  });
  if (auto error = jit->engine->addIRModule(std::move(owned)))
    return jitError(jit, std::move(error));
  return 0;
}

extern "C" uint64_t plew_llvm_jit_lookup(PlewLlvmJit *jit, const char *name) {
  if (!jit || jit->failed)
    return 0;
  if (!name || !*name) {
    jitError(jit, llvm::createStringError("invalid lookup symbol"));
    return 0;
  }
  auto address = jit->engine->lookup(name);
  if (!address) {
    jitError(jit, address.takeError());
    return 0;
  }
  return address->getValue();
}

extern "C" void plew_llvm_initialize_worker(int trace) {
  if (trace) {
    const char *arguments[] = {"plew-object", "-debug-pass=Executions"};
    llvm::cl::ParseCommandLineOptions(2, arguments);
  }
}

extern "C" int plew_llvm_emit_object(LLVMModuleRef module, const char *output,
                                     const char *cpu, int trace) {
  if (LLVMInitializeNativeTarget() || LLVMInitializeNativeAsmPrinter()) {
    std::fprintf(stderr, "plew: native LLVM target unavailable\n");
    return 1;
  }
  Message triple(LLVMGetDefaultTargetTriple());
  const char *moduleTriple = LLVMGetTarget(module);
  if (moduleTriple[0] && std::strcmp(moduleTriple, triple.get()) != 0) {
    std::fprintf(stderr, "plew: object backend requires native triple %s, got %s\n",
                 triple.get(), moduleTriple);
    return 1;
  }
  LLVMTargetRef target = nullptr;
  char *error = nullptr;
  if (LLVMGetTargetFromTriple(triple.get(), &target, &error)) {
    Message message(error);
    std::fprintf(stderr, "plew: LLVM target unavailable: %s\n", error);
    return 1;
  }
  auto machine = std::unique_ptr<LLVMOpaqueTargetMachine,
                                decltype(&LLVMDisposeTargetMachine)>(
      LLVMCreateTargetMachine(target, triple.get(), cpu, "",
                              LLVMCodeGenLevelDefault, LLVMRelocPIC,
                              LLVMCodeModelDefault), LLVMDisposeTargetMachine);
  if (!machine) {
    std::fprintf(stderr, "plew: cannot create LLVM target machine\n");
    return 1;
  }
  LLVMSetTarget(module, triple.get());
  auto layout = LLVMCreateTargetDataLayout(machine.get());
  Message layoutText(LLVMCopyStringRepOfTargetData(layout));
  const char *moduleLayout = LLVMGetDataLayoutStr(module);
  if (moduleLayout[0] && std::strcmp(moduleLayout, layoutText.get()) != 0) {
    LLVMDisposeTargetData(layout);
    std::fprintf(stderr, "plew: incompatible LLVM data layout\n");
    return 1;
  }
  LLVMSetModuleDataLayout(module, layout);
  LLVMDisposeTargetData(layout);
  if (!verify(module))
    return 1;

  bool sanitize = false;
  auto sanitizeKind = LLVMGetEnumAttributeKindForName("sanitize_address", 16);
  for (auto function = LLVMGetFirstFunction(module); function;
       function = LLVMGetNextFunction(function)) {
    if (LLVMGetEnumAttributeAtIndex(function, LLVMAttributeFunctionIndex, sanitizeKind)) {
      sanitize = true;
      break;
    }
  }
  auto options = std::unique_ptr<LLVMOpaquePassBuilderOptions,
                                decltype(&LLVMDisposePassBuilderOptions)>(
      LLVMCreatePassBuilderOptions(), LLVMDisposePassBuilderOptions);
  LLVMPassBuilderOptionsSetDebugLogging(options.get(), trace != 0);
  // Preserve the two optimization stages in the development link path:
  // the shared opt pipeline followed by clang's O2 IR optimization.
  if (!optimize(module, machine.get(), PLEW_LLVM_PIPELINE, options.get()) ||
      !optimize(module, machine.get(), "default<O2>", options.get()) ||
      (sanitize && !optimize(module, machine.get(), "asan", options.get())) ||
      !verify(module))
    return 1;

  LLVMMemoryBufferRef buffer = nullptr;
  if (LLVMTargetMachineEmitToMemoryBuffer(machine.get(), module, LLVMObjectFile,
                                         &error, &buffer)) {
    Message message(error);
    std::fprintf(stderr, "plew: LLVM object generation failed: %s\n", error);
    return 1;
  }
  auto object = std::unique_ptr<LLVMOpaqueMemoryBuffer,
                               decltype(&LLVMDisposeMemoryBuffer)>(
      buffer, LLVMDisposeMemoryBuffer);
  FILE *file = std::fopen(output, "wb");
  if (!file) {
    std::perror(output);
    return 1;
  }
  size_t size = LLVMGetBufferSize(buffer);
  bool complete = std::fwrite(LLVMGetBufferStart(buffer), 1, size, file) == size;
  if (std::fclose(file) != 0)
    complete = false;
  if (!complete) {
    std::fprintf(stderr, "plew: cannot write object: %s\n", output);
    std::remove(output);
    return 1;
  }
  return 0;
}
