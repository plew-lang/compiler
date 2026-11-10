#ifndef PLEW_LLVM_PROGRESS_H
#define PLEW_LLVM_PROGRESS_H

#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Pass.h>
#include <chrono>
#include <cstdint>
#include <cstdio>

namespace plew {
namespace native {

// Only actual callback/checkpoint execution advances this counter. There is no
// timer thread: a silent long operation must still trip the external watchdog.
class LlvmProgress {
  bool enabled;
  const char *stage = nullptr;
  uint64_t completed = 0;
  std::chrono::steady_clock::time_point started, reported;

public:
  explicit LlvmProgress(bool enabled) : enabled(enabled) {}
  bool active() const { return enabled; }
  void begin(const char *name) {
    stage = name;
    completed = 0;
    started = reported = std::chrono::steady_clock::now();
    if (enabled)
      std::fprintf(stderr, "[trace-phase] llvm:%s completed=0 start\n", stage);
  }
  void checkpoint() {
    if (!enabled) return;
    ++completed;
    auto now = std::chrono::steady_clock::now();
    if (now - reported >= std::chrono::seconds(1)) {
      std::fprintf(stderr, "[trace-phase] llvm:%s completed=%llu\n", stage,
                   static_cast<unsigned long long>(completed));
      reported = now;
    }
  }
  void finish() {
    if (enabled)
      std::fprintf(stderr, "[trace-phase] llvm:%s completed=%llu done seconds=%.6f\n",
                   stage, static_cast<unsigned long long>(completed),
                   std::chrono::duration<double>(std::chrono::steady_clock::now() - started).count());
  }
};

class FunctionCheckpoint final : public llvm::FunctionPass {
  LlvmProgress &progress;
public:
  inline static char ID = 0;
  explicit FunctionCheckpoint(LlvmProgress &progress)
      : FunctionPass(ID), progress(progress) {}
  bool runOnFunction(llvm::Function &) override {
    progress.checkpoint();
    return false;
  }
  llvm::StringRef getPassName() const override { return "Plew progress checkpoint"; }
  void getAnalysisUsage(llvm::AnalysisUsage &usage) const override {
    usage.setPreservesAll();
  }
};

class ModuleCheckpoint final : public llvm::ModulePass {
  LlvmProgress &progress;
public:
  inline static char ID = 0;
  explicit ModuleCheckpoint(LlvmProgress &progress)
      : ModulePass(ID), progress(progress) {}
  bool runOnModule(llvm::Module &) override {
    progress.checkpoint();
    return false;
  }
  llvm::StringRef getPassName() const override { return "Plew module progress checkpoint"; }
  void getAnalysisUsage(llvm::AnalysisUsage &usage) const override {
    usage.setPreservesAll();
  }
};

// Legacy codegen exposes no after-pass callback. Observe its original function
// and non-immutable module boundaries without changing IR or requiring machine
// analyses. A checkpoint can follow a skipped/redundant pass; it is not an exact
// count of LLVM transformations. MachineFunctionPass derives from FunctionPass.
class ObjectPassManager final : public llvm::legacy::PassManager {
  LlvmProgress &progress;
public:
  explicit ObjectPassManager(LlvmProgress &progress) : progress(progress) {}
  void add(llvm::Pass *pass) override {
    // add() can delete a redundant pass immediately. Never inspect it afterward.
    bool function = pass->getPassKind() == llvm::PT_Function;
    bool module = pass->getPassKind() == llvm::PT_Module && !pass->getAsImmutablePass();
    llvm::legacy::PassManager::add(pass);
    if (!progress.active()) return;
    if (function) llvm::legacy::PassManager::add(new FunctionCheckpoint(progress));
    else if (module) llvm::legacy::PassManager::add(new ModuleCheckpoint(progress));
  }
};

} // namespace native
} // namespace plew
#endif
