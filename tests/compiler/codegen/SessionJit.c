#include <stdint.h>
extern void plew_set_args(int, char **);
uint64_t plew_test_args_address(void) { return (uintptr_t)&plew_set_args; }
int plew_test_call_main(uint64_t address) {
  return ((int (*)(int, char **))(uintptr_t)address)(0, 0);
}
