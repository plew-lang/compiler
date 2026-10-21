/* Exercise the actual emitted runtime with a bounded allocator and panic trap.
 * Production panic still aborts; only this internal harness substitutes it. */
#include <assert.h>
#include <setjmp.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
static jmp_buf failure;
static int fail_next, allocations;
static void* bounded_malloc(size_t bytes) {
    allocations++;
    if (fail_next) { fail_next=0; return NULL; }
    assert(bytes<4096); /* No edge case may request a huge real allocation. */
    return malloc(bytes);
}
__attribute__((noreturn)) static void trapped_abort(void) { longjmp(failure,1); }
#define malloc bounded_malloc
#define abort trapped_abort
#include "runtime.c"
#undef malloc
#undef abort
#define PANICS(expression) do { if (!setjmp(failure)) { (void)(expression); fputs("missing expected panic\n",stderr); exit(1); } } while(0)
int main(void) {
    int before=allocations;
    PANICS(plew_rawbuf_alloc(8,1ULL<<61));
    PANICS(plew_rawbuf_alloc(1,ULLONG_MAX));
    PANICS(plew_rawbuf_alloc(1,PTRDIFF_MAX));
    PANICS(plew_rawbuf_alloc(ULLONG_MAX,2));
    assert(allocations==before);
    void* empty=plew_rawbuf_alloc(0,LLONG_MAX);
    assert(plew_rawbuf_count(empty)==0 && plew_rawbuf_cap(empty)==LLONG_MAX);
    /* Zero-sized slots can have huge logical counts without real storage. */
    plew_rawbuf_set_count(empty,LLONG_MAX);
    PANICS(plew_arr_prepare(empty,0,1,1));
    assert(plew_rawbuf_count(empty)==LLONG_MAX);
    plew_rawbuf_drop(empty);
    assert(plew_buffer_growth(0,LLONG_MAX/2+1,LLONG_MAX/2+2)==LLONG_MAX/2+2);
    unsigned long long limit=plew_buffer_capacity_limit(8);
    assert(plew_buffer_growth(8,limit/2+1,limit/2+2)==limit/2+2);
    assert(plew_buffer_growth(8,0,1)==8);
    for (int shared=0;shared<=1;shared++) {
        long long* original=plew_rawbuf_alloc(sizeof(long long),1);
        original[0]=42;
        plew_rawbuf_set_count(original,1);
        if(shared) plew_rawbuf_retain(original);
        long long owners=((long long*)original)[-1];
        before=allocations;
        PANICS(plew_arr_prepare(original,sizeof(long long),ULLONG_MAX,0));
        assert(allocations==before);
        assert(original[0]==42 && plew_rawbuf_count(original)==1 && plew_rawbuf_cap(original)==1 && original[-1]==owners);
        fail_next=1;
        PANICS(plew_arr_prepare(original,sizeof(long long),1,1));
        assert(original[0]==42 && plew_rawbuf_count(original)==1 && plew_rawbuf_cap(original)==1 && original[-1]==owners);
        if(shared) {
            fail_next=1;
            PANICS(plew_arr_prepare(original,sizeof(long long),0,0));
            assert(original[-1]==owners && original[0]==42);
        }
        void* prepared=plew_arr_prepare(original,sizeof(long long),1,1);
        assert(plew_rawbuf_count(prepared)==1 && plew_rawbuf_cap(prepared)>=2 && ((long long*)prepared)[0]==42);
        if(shared) { assert(original[-1]==1 && original[0]==42); plew_rawbuf_drop(original); }
        plew_rawbuf_drop(prepared);
    }
    void* reserved=plew_rawbuf_alloc(8,32);
    plew_rawbuf_set_count(reserved,1);
    ((long long*)reserved)[0]=7;
    plew_rawbuf_retain(reserved);
    void* private=plew_arr_prepare(reserved,8,0,0);
    assert(plew_rawbuf_cap(private)>=32 && ((long long*)private)[0]==7);
    assert(plew_rawbuf_count(reserved)==1 && ((long long*)reserved)[-1]==1);
    plew_rawbuf_drop(private);
    plew_rawbuf_drop(reserved);
    fail_next=1;
    PANICS(plew_rawbuf_alloc(8,1));
    puts("PASS runtime Buffer capacity and transactional failure");
}
