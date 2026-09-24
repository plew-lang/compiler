// Shared diagnostic helpers. No Plew language semantics are implemented here.
#pragma once
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/ExecutionUtils.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include <cstdlib>
using namespace llvm;
using namespace llvm::orc;
static void check(Error error) {
  if (error) {
    logAllUnhandledErrors(std::move(error), errs(), "orc-probe: ");
    std::exit(1);
  }
}
template <class T> static T take(Expected<T> value) {
  if (!value) check(value.takeError());
  return std::move(*value);
}
static void require(bool condition, const char *message) {
  if (!condition) { errs() << "orc-probe: " << message << '\n'; std::exit(1); }
}
static void verify(Module &module) {
  require(!verifyModule(module, &errs()), "invalid LLVM module");
}
static void optimize(Module &module, TargetMachine &target, StringRef pipeline) {
  verify(module);
  if (pipeline == "none") return;
  LoopAnalysisManager loops;
  FunctionAnalysisManager functions;
  CGSCCAnalysisManager calls;
  ModuleAnalysisManager modules;
  PassBuilder builder(&target);
  builder.registerModuleAnalyses(modules);
  builder.registerCGSCCAnalyses(calls);
  builder.registerFunctionAnalyses(functions);
  builder.registerLoopAnalyses(loops);
  builder.crossRegisterProxies(loops, functions, calls, modules);
  ModulePassManager passes;
  check(builder.parsePassPipeline(passes, pipeline));
  passes.run(module, modules);
  verify(module);
}

static void instrumentForSanitizer(Module &module) {
#ifdef ORC_PROBE_ASAN
  for (auto &function : module)
    if (!function.isDeclaration()) function.addFnAttr(Attribute::SanitizeAddress);
  auto builder = take(JITTargetMachineBuilder::detectHost());
  auto target = take(builder.createTargetMachine());
  optimize(module, *target, "asan");
  require(module.getFunction("__asan_report_load8") || module.getFunction("__asan_report_load1"),
          "ASan instrumentation missing");
#endif
}
