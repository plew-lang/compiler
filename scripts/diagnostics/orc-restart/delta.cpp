// Backend-only experiment: extract annotated Plew functions, not source diffs.
#include "common.hpp"
#include "llvm/ExecutionEngine/JITLink/JITLinkMemoryManager.h"
#include "llvm/ExecutionEngine/Orc/ObjectLinkingLayer.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Support/JSON.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include <atomic>
#include <chrono>
#include <map>
#include <set>
#include <mach/mach.h>

using Clock = std::chrono::steady_clock;
static double ms(Clock::time_point start, Clock::time_point end) {
  return std::chrono::duration<double, std::milli>(end - start).count();
}
static uint64_t rss() {
  mach_task_basic_info_data_t info;
  mach_msg_type_number_t count = MACH_TASK_BASIC_INFO_COUNT;
  require(task_info(mach_task_self(), MACH_TASK_BASIC_INFO,
                   reinterpret_cast<task_info_t>(&info), &count) == KERN_SUCCESS,
          "cannot read resident memory");
  return info.resident_size;
}

// Delegate to LLVM's real allocator and count successful finalizations/frees.
// No fake resource-removal notifications: deallocation completion is observed.
class CountedMemory : public jitlink::JITLinkMemoryManager {
  std::unique_ptr<jitlink::InProcessMemoryManager> inner;
  class Flight : public InFlightAlloc {
    CountedMemory &owner;
    std::unique_ptr<InFlightAlloc> inner;
  public:
    Flight(CountedMemory &owner, std::unique_ptr<InFlightAlloc> inner)
        : owner(owner), inner(std::move(inner)) {}
    void abandon(OnAbandonedFunction done) override { inner->abandon(std::move(done)); }
    void finalize(OnFinalizedFunction done) override {
      inner->finalize([this, done = std::move(done)](Expected<FinalizedAlloc> value) mutable {
        if (value) { ++owner.live; ++owner.created; }
        done(std::move(value));
      });
    }
  };
public:
  std::atomic<int64_t> live{0}, created{0}, freed{0};
  CountedMemory() : inner(take(jitlink::InProcessMemoryManager::Create())) {}
  void allocate(const jitlink::JITLinkDylib *jd, jitlink::LinkGraph &graph,
                OnAllocatedFunction done) override {
    inner->allocate(jd, graph, [this, done = std::move(done)](AllocResult result) mutable {
      if (!result) { done(result.takeError()); return; }
      done(std::make_unique<Flight>(*this, std::move(*result)));
    });
  }
  void deallocate(std::vector<FinalizedAlloc> allocations, OnDeallocatedFunction done) override {
    auto count = allocations.size();
    inner->deallocate(std::move(allocations),
      [this, count, done = std::move(done)](Error error) mutable {
        if (!error) { live -= count; freed += count; }
        done(std::move(error));
      });
  }
};

static bool scalarSignature(Function &fn) {
  return fn.arg_size() == 1 && fn.getReturnType()->isIntegerTy(64) &&
         fn.getArg(0)->getType()->isIntegerTy(64);
}

int main(int argc, char **argv) {
  if (argc != 7) {
    errs() << "usage: delta INPUT.ll RUNTIME.dylib PIPELINE|none COUNT RUNS OUTPUT.json\n";
    return 2;
  }
  int count = std::atoi(argv[4]), runs = std::atoi(argv[5]);
  require(count > 0 && count <= 100 && runs >= 2, "invalid count/runs");
  constexpr int64_t marker = 7000000;
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  std::string error;
  require(!sys::DynamicLibrary::LoadLibraryPermanently(argv[2], &error), error.c_str());
  auto cold = Clock::now();
  auto builder = take(JITTargetMachineBuilder::detectHost());
  builder.setCodeGenOptLevel(StringRef(argv[3]) == "none" ? CodeGenOptLevel::None
                                                         : CodeGenOptLevel::Default);
  auto target = take(builder.createTargetMachine());
  CountedMemory memory;
  auto jit = take(LLJITBuilder().setJITTargetMachineBuilder(builder)
    .setObjectLinkingLayerCreator([&](ExecutionSession &session, const Triple &)
      -> Expected<std::unique_ptr<ObjectLayer>> {
        return std::make_unique<ObjectLinkingLayer>(session, memory);
      }).create());
  jit->getMainJITDylib().addGenerator(take(DynamicLibrarySearchGenerator::GetForCurrentProcess(
      jit->getDataLayout().getGlobalPrefix())));
  auto initDone = Clock::now();
  ThreadSafeContext context(std::make_unique<LLVMContext>());
  auto &ctx = *context.getContext();
  SMDiagnostic diagnostic;
  auto original = parseIRFile(argv[1], diagnostic, ctx);
  if (!original) { diagnostic.print(argv[0], errs()); return 1; }
  original->setDataLayout(jit->getDataLayout());
  original->setTargetTriple(jit->getTargetTriple().str());
  std::map<int64_t, std::string> selected;
  for (auto &fn : *original) {
    for (auto &inst : instructions(fn)) {
      for (auto &operand : inst.operands()) {
        auto *number = dyn_cast<ConstantInt>(operand);
        if (number && number->getBitWidth() == 64 &&
            number->getSExtValue() >= marker && number->getSExtValue() < marker + count) {
          auto value = number->getSExtValue();
          require(scalarSignature(fn), "selected function must have i64(i64) signature");
          require(!selected.count(value) || selected[value] == fn.getName(), "ambiguous marker");
          selected[value] = fn.getName().str();
        }
      }
    }
  }
  require(selected.size() == static_cast<size_t>(count), "marker/function count mismatch");
  std::set<std::string> names;
  for (auto &item : selected) names.insert(item.second);
  require(names.size() == static_cast<size_t>(count), "multiple markers in one function");
  std::string rootName;
  for (auto &fn : *original) {
    if (!scalarSignature(fn) || names.count(fn.getName().str())) continue;
    std::set<std::string> callees;
    for (auto &inst : instructions(fn))
      if (auto *call = dyn_cast<CallBase>(&inst))
        if (auto *callee = call->getCalledFunction())
          if (names.count(callee->getName().str())) callees.insert(callee->getName().str());
    if (callees.size() == names.size()) {
      require(rootName.empty(), "ambiguous persistent caller");
      rootName = fn.getName().str();
    }
  }
  require(!rootName.empty(), "persistent caller not found");
  // This controlled extraction exports backing globals/helpers to the base.
  // It does not infer a production incremental-compilation boundary.
  for (auto &fn : *original)
    if (!fn.isDeclaration()) fn.setLinkage(GlobalValue::ExternalLinkage);
  unsigned globalIndex = 0;
  for (auto &global : original->globals()) {
    if (!global.hasName()) global.setName("orc_backing_" + std::to_string(globalIndex++));
    if (global.hasInitializer()) global.setLinkage(GlobalValue::ExternalLinkage);
  }
  ValueToValueMapTy baseMap, patchMap;
  auto base = CloneModule(*original, baseMap, [&](const GlobalValue *value) {
    return !names.count(value->getName().str());
  });
  auto patch = CloneModule(*original, patchMap, [&](const GlobalValue *value) {
    return names.count(value->getName().str()) != 0;
  });
  std::vector<std::string> slotNames;
  for (auto &name : names) {
    auto slotName = "orc_slot_" + name;
    auto *slot = new GlobalVariable(*base, PointerType::getUnqual(ctx), false,
      GlobalValue::ExternalLinkage, ConstantPointerNull::get(PointerType::getUnqual(ctx)), slotName);
    slotNames.push_back(slotName);
    auto *fn = base->getFunction(name);
    std::vector<CallBase *> calls;
    for (auto *user : fn->users()) {
      auto *call = dyn_cast<CallBase>(user);
      require(call && call->getCalledFunction() == fn, "unsupported address escape in probe");
      calls.push_back(call);
    }
    require(!calls.empty(), "no persistent call site");
    for (auto *call : calls) {
      IRBuilder<> ir(call);
      call->setCalledOperand(ir.CreateLoad(PointerType::getUnqual(ctx), slot));
    }
    fn->eraseFromParent();
  }
  verify(*base); verify(*patch);
  std::string patchIR;
  raw_string_ostream patchStream(patchIR);
  patch->print(patchStream, nullptr);
  optimize(*base, *target, argv[3]);
  check(jit->addIRModule(ThreadSafeModule(std::move(base), context)));
  auto persistent = take(jit->lookup(rootName)).toPtr<int64_t (*)(int64_t)>();
  std::vector<void **> slots;
  for (auto &name : slotNames) slots.push_back(take(jit->lookup(name)).toPtr<void **>());
  auto baseDone = Clock::now();
  const auto baseAllocations = memory.live.load();
  ResourceTrackerSP previous;
  std::vector<std::string> previousNames;
  std::error_code sampleError;
  std::string samplePath = std::string(argv[6]) + ".samples.jsonl";
  raw_fd_ostream sampleOutput(samplePath, sampleError);
  require(!sampleError, "cannot open samples output");
  for (int iteration = 0; iteration < runs; ++iteration) {
    auto start = Clock::now();
    // Fresh context per update: do not retain every generation's LLVM types.
    ThreadSafeContext updateContext(std::make_unique<LLVMContext>());
    auto update = parseIR(MemoryBufferRef(patchIR, "patch"), diagnostic, *updateContext.getContext());
    require(bool(update), "cannot parse patch");
    int replacements = 0;
    for (auto &name : names) {
      auto *fn = update->getFunction(name);
      require(fn && !fn->isDeclaration(), "missing patch body");
      for (auto &inst : instructions(*fn))
        for (unsigned index = 0; index < inst.getNumOperands(); ++index) {
          auto *number = dyn_cast<ConstantInt>(inst.getOperand(index));
          if (number && number->getBitWidth() == 64 && selected.count(number->getSExtValue())) {
            inst.setOperand(index, ConstantInt::get(number->getType(),
              number->getSExtValue() + (iteration + 1) * 1000));
            ++replacements;
          }
        }
    }
    require(replacements == count, "unexpected number of marker uses");
    std::vector<std::string> generationNames;
    for (auto &name : names) {
      auto newName = name + "_generation_" + std::to_string(iteration);
      update->getFunction(name)->setName(newName);
      generationNames.push_back(newName);
    }
    auto parsed = Clock::now();
    optimize(*update, *target, argv[3]);
    auto optimized = Clock::now();
    auto tracker = jit->getMainJITDylib().createResourceTracker();
    check(jit->addIRModule(tracker, ThreadSafeModule(std::move(update), updateContext)));
    auto registered = Clock::now();
    std::vector<void *> addresses;
    for (auto &name : generationNames) addresses.push_back(take(jit->lookup(name)).toPtr<void *>());
    auto linked = Clock::now();
    // Single-threaded, quiescent boundary; no live old stack/frame/callback.
    for (size_t index = 0; index < slots.size(); ++index) *slots[index] = addresses[index];
    auto value = persistent(42);
    auto executed = Clock::now();
    const int64_t expected = count * (marker + (iteration + 1) * 1000 + 42) + count * (count - 1) / 2;
    require(value == expected, "stale/wrong result from persistent caller");
    if (previous) {
      check(previous->remove());
      for (auto &name : previousNames) {
        auto absent = jit->lookup(name);
        require(!absent, "removed symbol remains visible");
        consumeError(absent.takeError());
      }
    }
    jit->getExecutionSession().getSymbolStringPool()->clearDeadEntries();
    auto removed = Clock::now();
    require(memory.live == baseAllocations + 1, "live JIT allocations grew");
    sampleOutput << formatv("{0}", json::Value(json::Object{
      {"iteration", iteration}, {"functions", count}, {"value", value},
      {"parse_patch_ms", ms(start, parsed)}, {"optimize_verify_ms", ms(parsed, optimized)},
      {"register_ms", ms(optimized, registered)}, {"codegen_link_lookup_ms", ms(registered, linked)},
      {"publish_first_call_ms", ms(linked, executed)}, {"remove_check_ms", ms(executed, removed)},
      {"total_ms", ms(start, removed)}, {"rss_bytes", static_cast<int64_t>(rss())},
      {"live_jit_allocations", memory.live.load()}, {"freed_jit_allocations", memory.freed.load()}})) << '\n';
    sampleOutput.flush();
    previous = std::move(tracker);
    previousNames = std::move(generationNames);
    if (iteration % 25 == 0 || iteration + 1 == runs)
      errs() << "[orc-delta] completed " << iteration + 1 << '/' << runs << '\n';
  }
  for (auto *slot : slots) *slot = nullptr;
  check(previous->remove());
  require(memory.live == baseAllocations, "last patch allocation not released");
  json::Object report{{"jit_initialization_ms", ms(cold, initDone)},
    {"base_preparation_ms", ms(initDone, baseDone)}, {"pipeline", argv[3]},
    {"functions", count}, {"runs", runs}, {"persistent_caller", rootName},
    {"base_jit_allocations", baseAllocations}, {"final_jit_allocations", memory.live.load()},
    {"generated_jit_allocations", memory.created.load()}, {"freed_jit_allocations", memory.freed.load()},
    {"patch_ir_bytes", static_cast<int64_t>(patchIR.size())}, {"samples_path", samplePath}};
  std::error_code ioError;
  raw_fd_ostream output(argv[6], ioError);
  require(!ioError, "cannot open output");
  output << formatv("{0:2}", json::Value(std::move(report))) << '\n';
  return 0;
}
