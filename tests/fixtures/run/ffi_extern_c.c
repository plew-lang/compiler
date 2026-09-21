// Companion foreign C library for ffi_extern_c.pw (linked by test.sh). Opaque
// handle behind a void* — ABI-identical to the Plew-side `typedef void* ModuleRef`.
#include <stdlib.h>
#include <string.h>
typedef struct { char* name; } Mod;
void* moduleCreate(unsigned char* name) {
    Mod* m = (Mod*)malloc(sizeof(Mod));
    m->name = strdup((const char*)name);
    return m;
}
unsigned char* moduleName(void* mod) { return (unsigned char*)((Mod*)mod)->name; }
void moduleDispose(void* mod) { Mod* m = (Mod*)mod; free(m->name); free(m); }
