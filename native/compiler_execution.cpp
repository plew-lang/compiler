// The process execution owns argv for as long as its JIT code and globals.
#include "llvm_backend.h"
#include <climits>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>
extern "C" char **plew_exchange_args(int, char **, int *);

struct PlewProgramArguments {
  std::vector<std::string> strings;
  std::vector<char *> pointers;
  char **previous = nullptr;
  int previousCount = 0;
  bool installed = false;

  ~PlewProgramArguments() {
    if (installed) {
      int ignored = 0;
      plew_exchange_args(previousCount, previous, &ignored);
    }
  }
};

extern "C" PlewProgramArguments *plew_compiler_arguments_create(uint64_t count, char **values) {
  if (count > INT_MAX) return nullptr;
  try {
    auto arguments = std::make_unique<PlewProgramArguments>();
    arguments->strings.reserve(count);
    for (uint64_t index = 0; index < count; ++index) arguments->strings.emplace_back(values[index]);
    arguments->pointers.reserve(count + 1);
    for (auto &value : arguments->strings) arguments->pointers.push_back(value.data());
    arguments->pointers.push_back(nullptr);
    return arguments.release();
  } catch (...) {
    return nullptr;
  }
}

extern "C" void plew_compiler_arguments_destroy(PlewProgramArguments *arguments) {
  delete arguments;
}

extern "C" int plew_compiler_jit_main(PlewLlvmJit *jit, PlewProgramArguments *arguments) {
  if (!arguments || arguments->installed) {
    std::fputs("plew: invalid or already installed program arguments\n", stderr);
    return 1;
  }
  const int count = static_cast<int>(arguments->strings.size());
  arguments->previous = plew_exchange_args(count, arguments->pointers.data(), &arguments->previousCount);
  arguments->installed = true;
  // Returning from main does not end the process execution: native exit
  // callbacks still observe the application's code, globals and arguments.
  return plew_llvm_jit_call_main(jit, count, arguments->pointers.data());
}
