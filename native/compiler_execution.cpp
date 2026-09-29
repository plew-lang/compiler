// The execution boundary scopes argv in the one shared runtime instance.
#include "llvm_backend.h"
#include <climits>
#include <vector>
extern "C" char **plew_exchange_args(int, char **, int *);
extern "C" int plew_compiler_jit_main(PlewLlvmJit *jit, uint64_t count, char **values) {
  if (count > INT_MAX) return 1;
  std::vector<char *> arguments;
  for (uint64_t index = 0; index < count; ++index) arguments.push_back(values[index]);
  arguments.push_back(nullptr);
  int previousCount = 0;
  char **previous = plew_exchange_args(static_cast<int>(count), arguments.data(), &previousCount);
  int result = plew_llvm_jit_call_main(jit, static_cast<int>(count), arguments.data());
  int ignored = 0;
  plew_exchange_args(previousCount, previous, &ignored);
  return result;
}
