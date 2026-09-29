#include <stdint.h>
extern int64_t exposedAdd(int64_t, int64_t);
extern double exposedFloat(double);
extern void exposedEmpty(void);
extern void exposedWrite(int64_t *);
extern int8_t exposedSignedByte(int8_t);
extern uint16_t exposedUnsignedShort(uint16_t);
extern float exposedMutateSingle(float *);
float cMutateSingle(float *value) { float previous = *value; *value += 0.25f; return previous; }
extern float exposedSingle(float);
float cSingle(float value) { return value; }
extern _Bool exposedBoolean(_Bool);
int8_t cSignedByte(int8_t value) { return value; }
uint16_t cUnsignedShort(uint16_t value) { return value; }
_Bool cBoolean(_Bool value) { return value; }
int32_t exerciseExposed(void) {
    exposedEmpty();
    int64_t result = 0;
    exposedWrite(&result);
    if (result != 42) return 3;
    if (exposedAdd(-9, 51) != 42) return 1;
    if (exposedFloat(1.25) != 2.5) return 2;
    if (exposedSignedByte(INT8_MIN) != INT8_MIN || exposedSignedByte(INT8_MAX) != INT8_MAX) return 4;
    if (exposedUnsignedShort(UINT16_MAX) != UINT16_MAX) return 5;
    if (!exposedBoolean(1) || exposedBoolean(0)) return 6;
    if (exposedSingle(1.25f) != 1.25f || exposedSingle(-123.5f) != -123.5f) return 7;
    float single = 1.25f;
    if (exposedMutateSingle(&single) != 1.25f || single != 1.5f) return 8;
    return 0;
}
