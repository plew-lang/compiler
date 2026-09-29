#include "llvm_backend.h"
#include "llvm_pipeline.h"

#include <llvm-c/Analysis.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/DynamicLibrary.h>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/ExecutionEngine/Orc/ExecutionUtils.h>
#include <llvm/ExecutionEngine/Orc/LazyReexports.h>
#include <llvm/ExecutionEngine/Orc/ThreadSafeModule.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Metadata.h>
#include <llvm/Support/Error.h>
#include <llvm-c/Error.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>
#include <llvm-c/Transforms/PassBuilder.h>
#include <cstdio>
#include <cstring>
#include <memory>
#include <cstdlib>
#include <string>
#include <llvm/ADT/DenseMap.h>

#if defined(__has_feature)
#if __has_feature(address_sanitizer)
#define PLEW_JIT_LSAN 1
#endif
#endif
#if defined(__SANITIZE_ADDRESS__) && !defined(PLEW_JIT_LSAN)
#define PLEW_JIT_LSAN 1
#endif
#ifdef PLEW_JIT_LSAN
#include <sanitizer/lsan_interface.h>
#endif

struct PlewLlvmJit {
  // Destroy the engine (and its generators) before the trampoline owners.
  std::unique_ptr<llvm::orc::LazyCallThroughManager> calls;
  std::unique_ptr<llvm::orc::IndirectStubsManager> stubs;
  std::unique_ptr<llvm::orc::LLJIT> engine;
  llvm::orc::JITDylib *bodies = nullptr;
  llvm::orc::DefinitionGenerator *sourceBodies = nullptr;
  bool failed = false;
  bool preparing = false;
  uint64_t nextBody = 0;
  int mainParameters = -1;
  std::unordered_set<std::string> hostSymbols;
  struct SharedDefinition { uint64_t session, identity, bytes; };
  std::unordered_map<std::string, SharedDefinition> sharedDefinitions;
#ifdef PLEW_JIT_LSAN
  // JIT static storage lives in mapped memory, outside LSan's loader-discovered
  // globals. Register storage slots, never the objects they happen to contain.
  std::vector<std::pair<const void *, size_t>> roots;
  ~PlewLlvmJit() {
    for (const auto &root : roots)
      __lsan_unregister_root_region(root.first, root.second);
  }
#endif
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

extern "C" const unsigned char *plew_llvm_empty_name(void) {
  static const unsigned char empty[] = "";
  return empty;
}

extern "C" PlewLlvmJit *plew_llvm_jit_create(void) {
  if (LLVMInitializeNativeTarget() || LLVMInitializeNativeAsmPrinter()) {
    std::fprintf(stderr, "plew: native LLVM JIT target unavailable\n");
    return nullptr;
  }
  // The ORC platform needs process symbols for its own support, but source
  // modules must resolve only their declared imports, not compiler globals.
  auto engine = llvm::orc::LLJITBuilder()
      .setLinkProcessSymbolsByDefault(false)
      .setProcessSymbolsJITDylibSetup([](llvm::orc::LLJIT &engine)
          -> llvm::Expected<llvm::orc::JITDylibSP> {
        auto &process = engine.getExecutionSession().createBareJITDylib("plew.platform.process");
        auto search = llvm::orc::DynamicLibrarySearchGenerator::GetForCurrentProcess(
            engine.getDataLayout().getGlobalPrefix());
        if (!search) return search.takeError();
        process.addGenerator(std::move(*search));
        return llvm::orc::JITDylibSP(&process);
      }).setNumCompileThreads(0).create();
  if (!engine) {
    jitError(nullptr, engine.takeError());
    return nullptr;
  }
  auto jit = std::make_unique<PlewLlvmJit>();
  jit->engine = std::move(*engine);
  return jit.release();
}

extern "C" void plew_llvm_jit_destroy(PlewLlvmJit *jit) { delete jit; }
extern "C" int plew_llvm_jit_failed(const PlewLlvmJit *jit) {
  return !jit || jit->failed;
}

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
  jit->hostSymbols.insert(name);
  return 0;
}

namespace {
llvm::Expected<llvm::orc::ThreadSafeModule>
consumeModule(PlewLlvmJit *jit, LLVMModuleRef module, LLVMContextRef context) {
  auto ownedContext = std::unique_ptr<llvm::LLVMContext>(llvm::unwrap(context));
  auto ownedModule = std::unique_ptr<llvm::Module>(llvm::unwrap(module));
  if (!module || !context)
    return llvm::createStringError("missing module/context pair");
  llvm::orc::ThreadSafeModule owned(std::move(ownedModule), std::move(ownedContext));
  if (!jit || jit->failed)
    return llvm::createStringError("terminal JIT session");
  if (!verify(module))
    return llvm::createStringError("module verification failed");
  const auto &triple = jit->engine->getTargetTriple();
  const char *actual = LLVMGetTarget(module);
  if (*actual && llvm::Triple(actual) != triple)
    return llvm::createStringError("module target is not the native JIT target");
  LLVMSetTarget(module, triple.str().c_str());
  owned.withModuleDo([&](llvm::Module &value) {
    value.setDataLayout(jit->engine->getDataLayout());
  });
  return std::move(owned);
}

[[noreturn]] void lazyFailure() {
  // A trampoline cannot return an arbitrary result with the callee's ABI.
  // The run contract is terminal failure, without application unwinding.
  std::fputs("plew: lazy compilation failed\n", stderr);
  std::_Exit(1);
}

class SourceBodyGenerator final : public llvm::orc::DefinitionGenerator {
  struct Body {
    std::string name, implementation;
    uint64_t body;
    PlewLlvmPrepareBody prepare;
    uint64_t session;
    bool requested = false;
    bool emitted = false;
  };
  PlewLlvmJit &jit;
  llvm::DenseMap<llvm::orc::SymbolStringPtr, Body> bodies;
  llvm::DenseMap<llvm::orc::SymbolStringPtr, llvm::orc::SymbolStringPtr> publicBodies;
public:
  explicit SourceBodyGenerator(PlewLlvmJit &jit) : jit(jit) {}
  Body *find(llvm::StringRef name) {
    auto found = publicBodies.find(jit.engine->mangleAndIntern(name));
    return found == publicBodies.end() ? nullptr : &bodies.find(found->second)->second;
  }
  void add(std::string name, std::string implementation, uint64_t body,
           PlewLlvmPrepareBody prepare, uint64_t session) {
    auto symbol = jit.engine->mangleAndIntern(implementation);
    publicBodies.try_emplace(jit.engine->mangleAndIntern(name), symbol);
    bodies.try_emplace(symbol, Body{std::move(name), std::move(implementation),
                                   body, prepare, session});
  }
  llvm::Error tryToGenerate(llvm::orc::LookupState &, llvm::orc::LookupKind,
                           llvm::orc::JITDylib &destination,
                           llvm::orc::JITDylibLookupFlags,
                           const llvm::orc::SymbolLookupSet &symbols) override {
    for (const auto &entry : symbols) {
      auto found = bodies.find(entry.first);
      if (found == bodies.end() || found->second.emitted)
        continue;
      // Preparing a body may register more bodies and rehash the index.
      // Copy the descriptor before invoking the compiler callback.
      auto body = found->second;
      found->second.requested = true;
      if (auto error = generate(destination, body))
        return error;
    }
    return llvm::Error::success();
  }
private:
  llvm::Error generate(llvm::orc::JITDylib &destination, Body &descriptor) {
    const auto &name = descriptor.name;
    auto body = descriptor.body;
    auto prepare = descriptor.prepare;
    auto session = descriptor.session;
    auto &requested = descriptor.requested;
    if (requested || jit.failed || jit.preparing) {
      jit.failed = true;
      return llvm::createStringError("invalid recursive source preparation");
    }
    requested = true;
    jit.preparing = true;
    LLVMModuleRef module = nullptr;
    LLVMContextRef context = nullptr;
    int status = prepare(session, body, &module, &context);
    jit.preparing = false;
    auto owned = consumeModule(&jit, module, context);
    if (!owned) {
      jit.failed = true;
      return owned.takeError();
    }
    if (status != 0) {
      jit.failed = true;
      return llvm::createStringError("source body preparation failed");
    }
    auto error = owned->withModuleDo([&](llvm::Module &value) -> llvm::Error {
      auto *function = value.getFunction(name);
      if (!function || function->isDeclaration())
        return llvm::createStringError("prepared module lacks its requested body");
      // The frontend explicitly identifies immutable session-owned metadata.
      // Keep the first definition; later modules import that same address.
      for (auto &global : value.globals()) {
        auto *metadata = global.getMetadata("plew.shared");
        if (!metadata) continue;
        auto *identity = metadata->getNumOperands() == 1
            ? llvm::mdconst::dyn_extract<llvm::ConstantInt>(metadata->getOperand(0))
            : nullptr;
        if (!identity || identity->getBitWidth() != 64 || identity->isZero() ||
            !global.isConstant() || !global.hasExternalLinkage() || global.isDeclaration())
          return llvm::createStringError("invalid shared metadata definition");
        auto bytes = value.getDataLayout().getTypeAllocSize(global.getValueType()).getFixedValue();
        auto inserted = jit.sharedDefinitions.emplace(global.getName().str(),
            PlewLlvmJit::SharedDefinition{session, identity->getZExtValue(), bytes});
        if (!inserted.second) {
          const auto &existing = inserted.first->second;
          if (existing.session != session || existing.identity != identity->getZExtValue() || existing.bytes != bytes)
            return llvm::createStringError("conflicting shared metadata identity");
          global.setInitializer(nullptr);
        }
      }
      // Declarations carry frozen body identities. Register dependencies before
      // linking without preparing their source bodies or decoding symbol names.
      std::vector<llvm::Function *> definitions;
      for (auto &candidate : value) {
        auto *metadata = candidate.getMetadata("plew.body");
        if (!metadata) {
          if (candidate.isDeclaration() && !candidate.use_empty() &&
              !candidate.isIntrinsic() && candidate.getMetadata("plew.host")) {
            auto symbol = candidate.getName().str();
            if (!find(symbol) && jit.hostSymbols.find(symbol) == jit.hostSymbols.end()) {
              auto host = llvm::sys::DynamicLibrary::getPermanentLibrary(nullptr);
              void *address = host.isValid() ? host.getAddressOfSymbol(symbol.c_str()) : nullptr;
              if (!address)
                return llvm::createStringError("unresolved host import: " + symbol);
              if (plew_llvm_jit_define(&jit, symbol.c_str(),
                      llvm::orc::ExecutorAddr::fromPtr(address).getValue(), 1))
                return llvm::createStringError("host import registration failed: " + symbol);
              jit.hostSymbols.insert(symbol);
            }
          }
          continue;
        }
        auto *identity = metadata->getNumOperands() == 1
            ? llvm::mdconst::dyn_extract<llvm::ConstantInt>(metadata->getOperand(0))
            : nullptr;
        if (!identity || identity->getBitWidth() != 64 || identity->isZero())
          return llvm::createStringError("invalid source body identity");
        auto candidateBody = identity->getZExtValue();
        if (!candidate.isDeclaration() && candidateBody != body)
          return llvm::createStringError("prepared module defines another source body");
        if (plew_llvm_jit_defer(&jit, candidate.getName().str().c_str(),
                                candidateBody, prepare, session))
          return llvm::createStringError("source dependency registration failed");
        if (!candidate.isDeclaration())
          definitions.push_back(&candidate);
      }
      // Generic native clients may provide a single entry without metadata.
      if (!function->getMetadata("plew.body"))
        definitions.push_back(function);
      for (auto *definition : definitions) {
        auto originalName = definition->getName().str();
        auto *registered = find(originalName);
        if (!registered || registered->body != body || registered->emitted)
          return llvm::createStringError("inconsistent source body entry");
        // All addresses, including self references and sibling entry addresses,
        // remain canonical stubs. One callback defines every entry of this body.
        definition->setName(registered->implementation);
        auto *entry = llvm::Function::Create(definition->getFunctionType(),
            llvm::GlobalValue::ExternalLinkage, originalName, value);
        entry->setCallingConv(definition->getCallingConv());
        entry->setAttributes(definition->getAttributes());
        definition->replaceAllUsesWith(entry);
        registered->emitted = true;
      }
      return llvm::Error::success();
    });
    if (!error)
      error = jit.engine->addIRModule(destination, std::move(*owned));
    if (error)
      jit.failed = true;
    return error;
  }
};
} // namespace

extern "C" int plew_llvm_jit_add(PlewLlvmJit *jit, LLVMModuleRef module,
                                 LLVMContextRef context) {
  auto owned = consumeModule(jit, module, context);
  if (!owned)
    return jitError(jit, owned.takeError());
#ifdef PLEW_JIT_LSAN
  std::vector<std::pair<std::string, size_t>> globals;
  owned->withModuleDo([&](llvm::Module &input) {
    for (auto &global : input.globals()) {
      if (!global.isDeclaration() && !global.isConstant() &&
          global.hasExternalLinkage())
        globals.emplace_back(global.getName().str(),
            jit->engine->getDataLayout().getTypeAllocSize(global.getValueType()));
    }
  });
#endif
  if (auto error = jit->engine->addIRModule(std::move(*owned)))
    return jitError(jit, std::move(error));
#ifdef PLEW_JIT_LSAN
  for (const auto &global : globals) {
    auto address = jit->engine->lookup(global.first);
    if (!address) return jitError(jit, address.takeError());
    if (!global.second) continue;
    const void *storage = address->toPtr<const void *>();
    __lsan_register_root_region(storage, global.second);
    jit->roots.emplace_back(storage, global.second);
  }
#endif
  return 0;
}

extern "C" int plew_llvm_jit_defer(PlewLlvmJit *jit, const char *name,
                                   uint64_t body, PlewLlvmPrepareBody prepare,
                                   uint64_t session) {
  if (!jit || jit->failed)
    return 1;
  if (!name || !*name || !prepare)
    return jitError(jit, llvm::createStringError("invalid deferred body"));
  if (!jit->bodies) {
    auto bodies = jit->engine->createJITDylib("plew.bodies");
    if (!bodies)
      return jitError(jit, bodies.takeError());
    jit->bodies = &*bodies;
    jit->bodies->addToLinkOrder(jit->engine->getMainJITDylib());
    auto generator = std::make_unique<SourceBodyGenerator>(*jit);
    jit->sourceBodies = generator.get();
    jit->bodies->addGenerator(std::move(generator));
    auto calls = llvm::orc::createLocalLazyCallThroughManager(
        jit->engine->getTargetTriple(), jit->engine->getExecutionSession(),
        llvm::orc::ExecutorAddr::fromPtr(&lazyFailure));
    if (!calls)
      return jitError(jit, calls.takeError());
    jit->calls = std::move(*calls);
    jit->stubs = llvm::orc::createLocalIndirectStubsManagerBuilder(
        jit->engine->getTargetTriple())();
  }
  auto *existing = static_cast<SourceBodyGenerator *>(jit->sourceBodies)->find(name);
  if (existing) {
    if (existing->body == body && existing->prepare == prepare && existing->session == session)
      return 0;
    return jitError(jit, llvm::createStringError("conflicting source body identity"));
  }
  std::string implementation = "__plew_lazy_body." + std::to_string(jit->nextBody++);
  static_cast<SourceBodyGenerator *>(jit->sourceBodies)->add(
      name, implementation, body, prepare, session);
  llvm::orc::SymbolAliasMap aliases;
  aliases[jit->engine->mangleAndIntern(name)] = {
      jit->engine->mangleAndIntern(implementation),
      llvm::JITSymbolFlags::Exported | llvm::JITSymbolFlags::Callable};
  if (auto error = jit->engine->getMainJITDylib().define(llvm::orc::lazyReexports(
          *jit->calls, *jit->stubs, *jit->bodies, std::move(aliases))))
    return jitError(jit, std::move(error));
  return 0;
}

extern "C" int plew_llvm_jit_declarations(PlewLlvmJit *jit, LLVMModuleRef module,
                                          LLVMContextRef context,
                                          PlewLlvmPrepareBody prepare, uint64_t session) {
  auto owned = consumeModule(jit, module, context);
  if (!owned)
    return jitError(jit, owned.takeError());
  auto error = owned->withModuleDo([&](llvm::Module &value) -> llvm::Error {
    if (!value.global_empty())
      return llvm::createStringError("declaration module contains global storage");
    for (auto &function : value) {
      if (!function.isDeclaration())
        return llvm::createStringError("declaration module contains executable code");
      if (function.getName() == "main") {
        auto *type = function.getFunctionType();
        auto count = type->getNumParams();
        if (!type->getReturnType()->isIntegerTy(32) || type->isVarArg() ||
            (count != 0 && (count != 2 || !type->getParamType(0)->isIntegerTy(32) ||
                            !type->getParamType(1)->isPointerTy())))
          return llvm::createStringError("invalid process entry ABI");
        jit->mainParameters = static_cast<int>(count);
      }
      auto *metadata = function.getMetadata("plew.body");
      if (!metadata)
        continue;
      auto *identity = metadata->getNumOperands() == 1
          ? llvm::mdconst::dyn_extract<llvm::ConstantInt>(metadata->getOperand(0)) : nullptr;
      if (!identity || identity->getBitWidth() != 64 || identity->isZero())
        return llvm::createStringError("invalid entry body identity");
      if (plew_llvm_jit_defer(jit, function.getName().str().c_str(),
                              identity->getZExtValue(), prepare, session))
        return llvm::createStringError("entry registration failed");
    }
    return llvm::Error::success();
  });
  return error ? jitError(jit, std::move(error)) : 0;
}

extern "C" int plew_llvm_jit_call_main(PlewLlvmJit *jit, int argc, char **argv) {
  if (!jit || jit->mainParameters < 0) return 1;
  auto address = plew_llvm_jit_lookup(jit, "main");
  if (!address) return 1;
  if (jit->mainParameters == 0)
    return llvm::orc::ExecutorAddr(address).toPtr<int (*)()>()();
  return llvm::orc::ExecutorAddr(address).toPtr<int (*)(int, char **)>()(argc, argv);
}

extern "C" uint64_t plew_llvm_jit_lookup(PlewLlvmJit *jit, const char *name) {
  if (!jit || jit->failed)
    return 0;
  if (jit->preparing) {
    jitError(jit, llvm::createStringError("symbol lookup during source preparation"));
    return 0;
  }
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
