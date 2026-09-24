// A lifecycle probe: whole application generations and host-routed events.
#include "common.hpp"
#include <dlfcn.h>
#include "llvm/IR/InstIterator.h"
#include <optional>

// The transport retains only a generation token and scalar payload, never a
// JIT address or a pointer into an application heap. Single host thread only.
struct EventGate {
  uint64_t generation = 0;
  int64_t (*callback)(int64_t) = nullptr;
  std::optional<int64_t> dispatch(uint64_t token, int64_t payload) {
    if (!callback || token != generation) return std::nullopt;
    return callback(payload);
  }
  void close() { callback = nullptr; }
};
int main(int argc, char **argv) {
  require(argc == 4, "usage: region APP.ll RUNTIME.dylib RUNS");
  InitializeNativeTarget(); InitializeNativeTargetAsmPrinter();
  auto jit = take(LLJITBuilder().create());
  int runs = std::atoi(argv[3]); require(runs > 0, "invalid runs");
  EventGate gate;
  for (int iteration = 0; iteration < runs; ++iteration) {
    void *library = dlopen(argv[2], RTLD_NOW | RTLD_LOCAL);
    require(library != nullptr, "cannot load runtime");
    auto allocations = reinterpret_cast<long long (*)()>(dlsym(library, "probe_allocations"));
    auto pending = reinterpret_cast<long long (*)()>(dlsym(library, "probe_pending"));
    auto reset = reinterpret_cast<void (*)()>(dlsym(library, "probe_reset_state"));
    auto destroy = reinterpret_cast<long long (*)()>(dlsym(library, "probe_destroy_region"));
    require(allocations && pending && destroy && reset, "missing region entry");
    require(allocations() == 0 && pending() == 0, "runtime was not fresh");
    auto created = jit->createJITDylib("generation_" + std::to_string(iteration));
    if (!created) check(created.takeError());
    auto &generation = *created;
    generation.addGenerator(std::make_unique<DynamicLibrarySearchGenerator>(
      sys::DynamicLibrary(library), jit->getDataLayout().getGlobalPrefix()));
    generation.addGenerator(take(DynamicLibrarySearchGenerator::GetForCurrentProcess(
      jit->getDataLayout().getGlobalPrefix())));
    ThreadSafeContext context(std::make_unique<LLVMContext>());
    SMDiagnostic diagnostic;
    auto module = parseIRFile(argv[1], diagnostic, *context.getContext());
    require(bool(module), "cannot parse app");
    module->setDataLayout(jit->getDataLayout());
    module->setTargetTriple(jit->getTargetTriple().str());
    verify(*module);
    std::string eventName;
    for (auto &function : *module)
      for (auto &instruction : instructions(function))
        for (auto &operand : instruction.operands())
          if (auto *value = dyn_cast<ConstantInt>(operand))
            if (value->getBitWidth() == 64 && value->getSExtValue() == 7000000) {
              require(eventName.empty() || eventName == function.getName(), "ambiguous event marker");
              require(function.arg_size() == 1 && function.getReturnType()->isIntegerTy(64)
                && function.getArg(0)->getType()->isIntegerTy(64), "invalid event signature");
              eventName = function.getName().str();
            }
    require(!eventName.empty(), "event function missing");
    module->getFunction(eventName)->setLinkage(GlobalValue::ExternalLinkage);
    check(jit->addIRModule(generation, ThreadSafeModule(std::move(module), context)));
    check(jit->initialize(generation));
    auto entry = take(jit->lookup(generation, "main")).toPtr<int (*)(int, char **)>();
    char program[] = "region-probe"; char *args[] = {program, nullptr};
    require(entry(1, args) == 0, "application failed");
    require(pending() > 0 && allocations() > 0, "no suspended owned state");
    gate.generation = static_cast<uint64_t>(iteration) + 1;
    gate.callback = take(jit->lookup(generation, eventName)).toPtr<int64_t (*)(int64_t)>();
    require(!gate.dispatch(gate.generation - 1, 20), "old notification entered new app");
    require(gate.dispatch(gate.generation, 20) == 7000023, "current notification did not run");
    if (iteration == 0) {
      // Candidate materialization must finish before invalidating the old app.
      auto candidateCreated = jit->createJITDylib("failed_candidate");
      if (!candidateCreated) check(candidateCreated.takeError());
      auto &candidate = *candidateCreated;
      ThreadSafeContext candidateContext(std::make_unique<LLVMContext>());
      SMDiagnostic candidateDiagnostic;
      auto broken = parseIR(MemoryBufferRef(
        "declare i64 @probe_missing_external()\n"
        "define i64 @candidate_entry() { %x = call i64 @probe_missing_external() ret i64 %x }\n",
        "failed-candidate"), candidateDiagnostic, *candidateContext.getContext());
      require(bool(broken), "candidate fixture did not parse");
      broken->setDataLayout(jit->getDataLayout());
      broken->setTargetTriple(jit->getTargetTriple().str());
      verify(*broken);
      check(jit->addIRModule(candidate, ThreadSafeModule(std::move(broken), candidateContext)));
      auto result = jit->lookup(candidate, "candidate_entry");
      require(!result, "unresolved candidate unexpectedly linked");
      consumeError(result.takeError());
      check(jit->getExecutionSession().removeJITDylib(candidate));
      require(pending() > 0, "candidate failure removed old pending work");
      require(gate.dispatch(gate.generation, 20) == 7000024,
              "old application stopped after candidate failure");
    }
    gate.close();
    require(!gate.dispatch(gate.generation, 20), "notification entered closing app");
    // No further entry or dispatch is allowed after this boundary.
    check(jit->deinitialize(generation));
    reset();
    auto reclaimed = destroy();
    require(reclaimed > 0 && allocations() == 0, "region was not reclaimed");
    check(jit->getExecutionSession().removeJITDylib(generation));
    require(!gate.dispatch(gate.generation, 20), "notification entered freed code");
    require(dlclose(library) == 0, "runtime close failed");
    jit->getExecutionSession().getSymbolStringPool()->clearDeadEntries();
    errs() << "[region] completed " << iteration + 1 << '/' << runs
           << " reclaimed=" << reclaimed << '\n';
  }
}
