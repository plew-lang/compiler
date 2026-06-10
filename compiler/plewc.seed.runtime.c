#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
void plew_exit(long long code){ exit((int)code); }
void plew_write_raw(const char* d, long long n){ fwrite(d,1,(size_t)n,stdout); }
void plew_eprint_raw(const char* d, long long n){ fwrite(d,1,(size_t)n,stderr); }
__attribute__((noreturn)) void plew_panic_raw(const char* d, long long n){ fputs("panic: ",stderr); fwrite(d,1,(size_t)n,stderr); fputc('\n',stderr); exit(1); }
void plew_print_str(const char* d, long long n){ fwrite(d,1,(size_t)n,stdout); fputc('\n',stdout); }
void plew_print_i64(long long v){ printf("%lld\n", v); }
void plew_print_f64(double v){ printf("%g\n", v); }
void plew_print_u64(unsigned long long v){ printf("%llu\n", v); }
void plew_print_bool(long long v){ fputs(v?"1":"0",stdout); fputc('\n',stdout); }
long long plew_str_eq(const char* a, long long na, const char* b, long long nb){ if(na!=nb) return 0; for(long long i=0;i<na;i++) if(a[i]!=b[i]) return 0; return 1; }
typedef struct { char* d; long long n; } PlewStrR;
PlewStrR plew_f64_to_str(double v){ char* buf=(char*)malloc(32); int n=snprintf(buf,32,"%g",v); PlewStrR s; s.d=buf; s.n=(long long)n; return s; }
void plew_f64_nan_check(double a, double b){ if(a!=a || b!=b) plew_panic_raw("NaN comparison",14); }
PlewStrR plew_readStdin(void){ size_t cap=4096,len=0; char* buf=(char*)malloc(cap); int ch; while((ch=getchar())!=EOF){ if(len+1>=cap){cap*=2;buf=(char*)realloc(buf,cap);} buf[len++]=(char)ch; } PlewStrR s; s.d=buf; s.n=(long long)len; return s; }
unsigned char* plew_cString(char* d, long long n){ unsigned char* b=(unsigned char*)malloc((size_t)n+1); if(n) memcpy(b,d,(size_t)n); b[n]=0; return b; }
PlewStrR plew_stringFromCString(unsigned char* p){ PlewStrR s; if(!p){ s.d=(char*)""; s.n=0; return s; } size_t n=strlen((const char*)p); char* b=(char*)malloc(n+1); memcpy(b,p,n); b[n]=0; s.d=b; s.n=(long long)n; return s; }
void* plew_rawbuf_alloc(long long elemSize, long long cap){ long long* h=(long long*)malloc(2*sizeof(long long)+(size_t)(elemSize*cap)); h[0]=cap; h[1]=1; return (void*)(h+2); }
long long plew_rawbuf_cap(void* p){ return p?((long long*)p)[-2]:0; }
void* plew_arr_grow(void* data, long long elemSize, long long count){ long long cap=plew_rawbuf_cap(data); if(count<cap) return data; long long nc=cap<8?8:cap*2; void* nd=plew_rawbuf_alloc(elemSize,nc); if(count) memcpy(nd,data,(size_t)(elemSize*count)); return nd; }
void* plew_arr_copy(void* data, long long elemSize, long long count){ void* nd=plew_rawbuf_alloc(elemSize,count<1?1:count); if(count) memcpy(nd,data,(size_t)(elemSize*count)); return nd; }
void plew_rawbuf_retain(void* p){ if(p) ((long long*)p)[-1]++; }
long long plew_rawbuf_release(void* p){ if(!p) return 0; return --((long long*)p)[-1]; }
void plew_bounds(long long i, long long n){ if(i<0||i>=n){ fputs("panic: index out of bounds\n",stderr); exit(1); } }
int8_t plew_i8Add(int8_t a, int8_t b){ int8_t r; if(__builtin_add_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
int8_t plew_i8Sub(int8_t a, int8_t b){ int8_t r; if(__builtin_sub_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
int8_t plew_i8Mul(int8_t a, int8_t b){ int8_t r; if(__builtin_mul_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
int8_t plew_i8Div(int8_t a, int8_t b){ if(b==0) plew_panic_raw("division by zero",16); if(b==-1 && a==INT8_MIN) plew_panic_raw("integer overflow",16); return a/b; }
int8_t plew_i8Rem(int8_t a, int8_t b){ if(b==0) plew_panic_raw("remainder by zero",17); if(b==-1) return 0; return a%b; }
int8_t plew_i8Neg(int8_t a){ int8_t r; if(__builtin_sub_overflow((int8_t)0,a,&r)) plew_panic_raw("integer overflow",16); return r; }
int16_t plew_i16Add(int16_t a, int16_t b){ int16_t r; if(__builtin_add_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
int16_t plew_i16Sub(int16_t a, int16_t b){ int16_t r; if(__builtin_sub_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
int16_t plew_i16Mul(int16_t a, int16_t b){ int16_t r; if(__builtin_mul_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
int16_t plew_i16Div(int16_t a, int16_t b){ if(b==0) plew_panic_raw("division by zero",16); if(b==-1 && a==INT16_MIN) plew_panic_raw("integer overflow",16); return a/b; }
int16_t plew_i16Rem(int16_t a, int16_t b){ if(b==0) plew_panic_raw("remainder by zero",17); if(b==-1) return 0; return a%b; }
int16_t plew_i16Neg(int16_t a){ int16_t r; if(__builtin_sub_overflow((int16_t)0,a,&r)) plew_panic_raw("integer overflow",16); return r; }
int32_t plew_i32Add(int32_t a, int32_t b){ int32_t r; if(__builtin_add_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
int32_t plew_i32Sub(int32_t a, int32_t b){ int32_t r; if(__builtin_sub_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
int32_t plew_i32Mul(int32_t a, int32_t b){ int32_t r; if(__builtin_mul_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
int32_t plew_i32Div(int32_t a, int32_t b){ if(b==0) plew_panic_raw("division by zero",16); if(b==-1 && a==INT32_MIN) plew_panic_raw("integer overflow",16); return a/b; }
int32_t plew_i32Rem(int32_t a, int32_t b){ if(b==0) plew_panic_raw("remainder by zero",17); if(b==-1) return 0; return a%b; }
int32_t plew_i32Neg(int32_t a){ int32_t r; if(__builtin_sub_overflow((int32_t)0,a,&r)) plew_panic_raw("integer overflow",16); return r; }
int64_t plew_i64Add(int64_t a, int64_t b){ int64_t r; if(__builtin_add_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
int64_t plew_i64Sub(int64_t a, int64_t b){ int64_t r; if(__builtin_sub_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
int64_t plew_i64Mul(int64_t a, int64_t b){ int64_t r; if(__builtin_mul_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
int64_t plew_i64Div(int64_t a, int64_t b){ if(b==0) plew_panic_raw("division by zero",16); if(b==-1 && a==INT64_MIN) plew_panic_raw("integer overflow",16); return a/b; }
int64_t plew_i64Rem(int64_t a, int64_t b){ if(b==0) plew_panic_raw("remainder by zero",17); if(b==-1) return 0; return a%b; }
int64_t plew_i64Neg(int64_t a){ int64_t r; if(__builtin_sub_overflow((int64_t)0,a,&r)) plew_panic_raw("integer overflow",16); return r; }
unsigned char plew_u8Add(unsigned char a, unsigned char b){ unsigned char r; if(__builtin_add_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
unsigned char plew_u8Sub(unsigned char a, unsigned char b){ unsigned char r; if(__builtin_sub_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
unsigned char plew_u8Mul(unsigned char a, unsigned char b){ unsigned char r; if(__builtin_mul_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
unsigned char plew_u8Div(unsigned char a, unsigned char b){ if(b==0) plew_panic_raw("division by zero",16); return a/b; }
unsigned char plew_u8Rem(unsigned char a, unsigned char b){ if(b==0) plew_panic_raw("remainder by zero",17); return a%b; }
uint16_t plew_u16Add(uint16_t a, uint16_t b){ uint16_t r; if(__builtin_add_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
uint16_t plew_u16Sub(uint16_t a, uint16_t b){ uint16_t r; if(__builtin_sub_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
uint16_t plew_u16Mul(uint16_t a, uint16_t b){ uint16_t r; if(__builtin_mul_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
uint16_t plew_u16Div(uint16_t a, uint16_t b){ if(b==0) plew_panic_raw("division by zero",16); return a/b; }
uint16_t plew_u16Rem(uint16_t a, uint16_t b){ if(b==0) plew_panic_raw("remainder by zero",17); return a%b; }
uint32_t plew_u32Add(uint32_t a, uint32_t b){ uint32_t r; if(__builtin_add_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
uint32_t plew_u32Sub(uint32_t a, uint32_t b){ uint32_t r; if(__builtin_sub_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
uint32_t plew_u32Mul(uint32_t a, uint32_t b){ uint32_t r; if(__builtin_mul_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
uint32_t plew_u32Div(uint32_t a, uint32_t b){ if(b==0) plew_panic_raw("division by zero",16); return a/b; }
uint32_t plew_u32Rem(uint32_t a, uint32_t b){ if(b==0) plew_panic_raw("remainder by zero",17); return a%b; }
uint64_t plew_u64Add(uint64_t a, uint64_t b){ uint64_t r; if(__builtin_add_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
uint64_t plew_u64Sub(uint64_t a, uint64_t b){ uint64_t r; if(__builtin_sub_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
uint64_t plew_u64Mul(uint64_t a, uint64_t b){ uint64_t r; if(__builtin_mul_overflow(a,b,&r)) plew_panic_raw("integer overflow",16); return r; }
uint64_t plew_u64Div(uint64_t a, uint64_t b){ if(b==0) plew_panic_raw("division by zero",16); return a/b; }
uint64_t plew_u64Rem(uint64_t a, uint64_t b){ if(b==0) plew_panic_raw("remainder by zero",17); return a%b; }
static int plew_argc = 0; static char** plew_argv = 0;
void plew_set_args(int argc, char** argv){ plew_argc = argc; plew_argv = argv; }
long long plew_argCount(void){ return (long long)plew_argc; }
PlewStrR plew_argAt(long long i){ PlewStrR s; if(i<0||i>=plew_argc){ s.d=(char*)""; s.n=0; return s; } s.d=plew_argv[i]; s.n=(long long)strlen(plew_argv[i]); return s; }
void plew_writeByte(unsigned char b){ putchar((int)b); }
static PlewStrR plew_readPath(const char* path){ FILE* f=fopen(path,"rb"); PlewStrR s; if(!f){ s.d=(char*)""; s.n=0; return s; } fseek(f,0,SEEK_END); long sz=ftell(f); fseek(f,0,SEEK_SET); char* buf=(char*)malloc((size_t)sz+1); size_t n=fread(buf,1,(size_t)sz,f); fclose(f); buf[n]=0; s.d=buf; s.n=(long long)n; return s; }
PlewStrR plew_readFile(char* d, long long n){ char* p=(char*)malloc((size_t)n+1); if(n) memcpy(p,d,(size_t)n); p[n]=0; PlewStrR r=plew_readPath(p); free(p); return r; }
PlewStrR plew_readFileBytes(char* d, long long n){ return plew_readFile(d,n); }
long long plew_fileExists(char* d, long long n){ char* p=(char*)malloc((size_t)n+1); if(n) memcpy(p,d,(size_t)n); p[n]=0; FILE* f=fopen(p,"rb"); free(p); if(f){ fclose(f); return 1; } return 0; }
typedef struct PlewPromise PlewPromise;
typedef void (*PlewResumeFn)(void*);
struct PlewPromise { int done; long long value; PlewResumeFn k; void* kframe; };
typedef struct { PlewResumeFn fn; void* arg; } PlewTask;
static PlewTask* plew_ready = 0; static long long plew_ready_len = 0, plew_ready_cap = 0, plew_ready_head = 0;
static void plew_enqueue(PlewResumeFn fn, void* arg) { if (plew_ready_len == plew_ready_cap) { plew_ready_cap = plew_ready_cap ? plew_ready_cap * 2 : 16; plew_ready = (PlewTask*)realloc(plew_ready, (size_t)plew_ready_cap * sizeof(PlewTask)); } plew_ready[plew_ready_len].fn = fn; plew_ready[plew_ready_len].arg = arg; plew_ready_len++; }
static int plew_dequeue(PlewTask* out) { if (plew_ready_head >= plew_ready_len) { plew_ready_head = 0; plew_ready_len = 0; return 0; } *out = plew_ready[plew_ready_head++]; return 1; }
typedef struct { long long deadline; PlewPromise* p; } PlewTimer;
static PlewTimer* plew_timers = 0; static long long plew_timers_len = 0, plew_timers_cap = 0; static long long plew_vnow = 0;
void* plew_frame_alloc(long long sz) { return malloc((size_t)sz); }
void plew_frame_free(void* p) { free(p); }
PlewPromise* plew_promise_new(void) { PlewPromise* p = (PlewPromise*)malloc(sizeof(PlewPromise)); p->done = 0; p->value = 0; p->k = 0; p->kframe = 0; return p; }
void plew_promise_resolve(PlewPromise* p, long long v) { p->done = 1; p->value = v; if (p->k) { PlewResumeFn k = p->k; void* f = p->kframe; p->k = 0; plew_enqueue(k, f); } }
static void plew_timer_add(long long delay, PlewPromise* p) { if (plew_timers_len == plew_timers_cap) { plew_timers_cap = plew_timers_cap ? plew_timers_cap * 2 : 8; plew_timers = (PlewTimer*)realloc(plew_timers, (size_t)plew_timers_cap * sizeof(PlewTimer)); } plew_timers[plew_timers_len].deadline = plew_vnow + delay; plew_timers[plew_timers_len].p = p; plew_timers_len++; }
PlewPromise* plew_sleep(long long ms) { PlewPromise* p = plew_promise_new(); plew_timer_add(ms, p); return p; }
void plew_loop_run(void) { PlewTask t; while (1) { while (plew_dequeue(&t)) { t.fn(t.arg); } if (plew_timers_len == 0) break; long long bi = -1, bd = 0; for (long long i = 0; i < plew_timers_len; i++) { if (bi < 0 || plew_timers[i].deadline < bd) { bi = i; bd = plew_timers[i].deadline; } } PlewPromise* p = plew_timers[bi].p; plew_vnow = plew_timers[bi].deadline; plew_timers[bi] = plew_timers[--plew_timers_len]; plew_promise_resolve(p, 0); } }
