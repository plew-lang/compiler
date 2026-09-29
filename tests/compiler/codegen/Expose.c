#include <stdint.h>
extern int64_t exposedAdd(int64_t, int64_t);
extern double exposedFloat(double);
extern void exposedEmpty(void);
extern void exposedWrite(int64_t *);
int32_t exerciseExposed(void) {
    exposedEmpty();
    int64_t result = 0;
    exposedWrite(&result);
    if (result != 42) return 3;
    if (exposedAdd(-9, 51) != 42) return 1;
    if (exposedFloat(1.25) != 2.5) return 2;
    return 0;
}
