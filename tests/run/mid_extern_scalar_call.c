#include <stdint.h>

static int64_t sequence;
int32_t externalSigned(int32_t value) { return value; }
uint32_t externalUnsigned(uint32_t value) { return value; }
double externalFloat(double value) { return value * 2.0; }
void externalRecord(int64_t value) { sequence = sequence * 10 + value; }
int64_t externalSequence(void) { return sequence; }
int64_t externalPair(int64_t first, int64_t second) {
    return first * 10 + second;
}
