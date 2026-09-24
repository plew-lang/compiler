// A lifecycle probe: whole application generations, no live external callbacks.
#include "common.hpp"
#include <dlfcn.h>
int main(int argc, char **argv) {
  require(argc == 4, "usage: region APP.ll RUNTIME.dylib RUNS");
  InitializeNativeTarget(); InitializeNativeTargetAsmPrinter();
  auto jit = take(LLJITBuilder().create());
  int runs = std::atoi(argv[3]); require(runs > 0, "invalid runs");
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
    check(jit->addIRModule(generation, ThreadSafeModule(std::move(module), context)));
    check(jit->initialize(generation));
    auto entry = take(jit->lookup(generation, "main")).toPtr<int (*)(int, char **)>();
    char program[] = "region-probe"; char *args[] = {program, nullptr};
    require(entry(1, args) == 0, "application failed");
    require(pending() > 0 && allocations() > 0, "no suspended owned state");
    // No further entry or dispatch is allowed after this boundary.
    check(jit->deinitialize(generation));
    reset();
    auto reclaimed = destroy();
    require(reclaimed > 0 && allocations() == 0, "region was not reclaimed");
    check(jit->getExecutionSession().removeJITDylib(generation));
    require(dlclose(library) == 0, "runtime close failed");
    jit->getExecutionSession().getSymbolStringPool()->clearDeadEntries();
    errs() << "[region] completed " << iteration + 1 << '/' << runs
           << " reclaimed=" << reclaimed << '\n';
  }
}
