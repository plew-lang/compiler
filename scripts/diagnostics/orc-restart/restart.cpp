// Persistent diagnostic host. Commands arrive only after explicit restart.
#include "common.hpp"
#include "llvm/IR/InstIterator.h"
#include <dlfcn.h>
#include <iostream>
#include <sstream>
#include <optional>

int main(int argc, char **argv) {
  require(argc == 2, "usage: restart RUNTIME.dylib");
  InitializeNativeTarget(); InitializeNativeTargetAsmPrinter();
  void *library = dlopen(argv[1], RTLD_NOW | RTLD_LOCAL);
  require(library, "runtime load failed");
  auto allocations = reinterpret_cast<long long (*)()>(dlsym(library, "probe_allocations"));
  auto pending = reinterpret_cast<long long (*)()>(dlsym(library, "probe_pending"));
  auto reset = reinterpret_cast<void (*)()>(dlsym(library, "probe_reset_state"));
  auto destroy = reinterpret_cast<long long (*)()>(dlsym(library, "probe_destroy_region"));
  require(allocations && pending && reset && destroy, "missing runtime interface");
  auto jit = take(LLJITBuilder().create());
  JITDylib *active = nullptr;
  uint64_t serial = 0, activeToken = 0;
  int64_t (*callback)(int64_t) = nullptr;
  auto dispatch = [&](uint64_t token, int64_t payload) -> std::optional<int64_t> {
    if (!callback || token != activeToken) return std::nullopt;
    return callback(payload);
  };
  auto dispose = [&]() {
    callback = nullptr;
    if (!active) return;
    check(jit->deinitialize(*active));
    reset(); destroy();
    require(allocations() == 0 && pending() == 0, "region not empty");
    check(jit->getExecutionSession().removeJITDylib(*active)); active = nullptr;
    jit->getExecutionSession().getSymbolStringPool()->clearDeadEntries();
  };
  std::cout << "HOST_READY\n" << std::flush;
  std::string line;
  while (std::getline(std::cin, line)) {
    std::istringstream request(line);
    std::string command, path; int64_t revision = 0;
    request >> command;
    if (command == "QUIT") break;
    if (command == "PING") {
      auto result = dispatch(activeToken, 20);
      if (result) std::cout << "PONG " << *result << '\n';
      else std::cout << "INACTIVE\n";
      std::cout << std::flush; continue;
    }
    require(command == "LOAD" || command == "FAIL_READY", "unknown command");
    request >> path >> revision;
    require(!path.empty(), "missing IR path");
    ThreadSafeContext context(std::make_unique<LLVMContext>());
    SMDiagnostic diagnostic;
    auto module = parseIRFile(path, diagnostic, *context.getContext());
    if (!module || verifyModule(*module, &errs())) {
      std::cout << "REJECTED\n" << std::flush; continue;
    }
    require(!module->getNamedGlobal("llvm.global_ctors"), "probe does not support native constructors");
    module->setDataLayout(jit->getDataLayout());
    module->setTargetTriple(jit->getTargetTriple().str());
    std::string eventName;
    for (auto &function : *module)
      for (auto &instruction : instructions(function))
        for (auto &operand : instruction.operands())
          if (auto *value = dyn_cast<ConstantInt>(operand))
            if (value->getBitWidth() == 64 && value->getSExtValue() == 7000000) {
              require(eventName.empty() || eventName == function.getName(), "ambiguous event");
              require(function.arg_size() == 1 && function.getReturnType()->isIntegerTy(64)
                && function.getArg(0)->getType()->isIntegerTy(64), "invalid event signature");
              eventName = function.getName().str();
            }
    require(!eventName.empty(), "event marker absent");
    module->getFunction(eventName)->setLinkage(GlobalValue::ExternalLinkage);
    auto created = jit->createJITDylib("candidate_" + std::to_string(++serial));
    if (!created) check(created.takeError());
    auto &candidate = *created;
    candidate.addGenerator(std::make_unique<DynamicLibrarySearchGenerator>(
      sys::DynamicLibrary(library), jit->getDataLayout().getGlobalPrefix()));
    candidate.addGenerator(take(DynamicLibrarySearchGenerator::GetForCurrentProcess(
      jit->getDataLayout().getGlobalPrefix())));
    check(jit->addIRModule(candidate, ThreadSafeModule(std::move(module), context)));
    auto mainAddress = jit->lookup(candidate, "main");
    if (!mainAddress) {
      consumeError(mainAddress.takeError());
      check(jit->getExecutionSession().removeJITDylib(candidate));
      std::cout << "REJECTED\n" << std::flush; continue;
    }
    auto eventAddress = jit->lookup(candidate, eventName);
    if (!eventAddress) {
      consumeError(eventAddress.takeError());
      check(jit->getExecutionSession().removeJITDylib(candidate));
      std::cout << "REJECTED\n" << std::flush; continue;
    }
    // Candidate code is fully materialized without executing app initializers.
    uint64_t oldToken = activeToken;
    dispose(); active = &candidate; activeToken = serial;
    check(jit->initialize(candidate));
    auto entry = mainAddress->toPtr<int (*)(int, char **)>();
    char program[] = "restart-probe"; char *args[] = {program, nullptr};
    require(entry(1, args) == 0, "main failed");
    require(pending() > 0 && allocations() > 0, "no suspended state");
    // Model a host readiness failure after initialization, not panic recovery.
    if (command == "FAIL_READY") {
      dispose(); std::cout << "INIT_FAILED\n" << std::flush; continue;
    }
    callback = eventAddress->toPtr<int64_t (*)(int64_t)>();
    require(!dispatch(oldToken, 20), "old event entered new generation");
    auto result = dispatch(activeToken, 20);
    require(result && *result == 7000023 + revision, "new source not reflected");
    std::cout << "READY " << *result << '\n' << std::flush;
    errs() << "[restart] ready generation " << serial << '\n';
  }
  dispose();
  require(dlclose(library) == 0, "runtime close failed");
  std::cout << "STOPPED\n" << std::flush;
}
