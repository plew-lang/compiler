#include <stdio.h>
#include <stdlib.h>
extern long long plew_argCount(void);
extern char *plew_argAt(long long);
extern void plew_rawbuf_drop(void *);
static void at_exit(void) {
    char *first = plew_argAt(1);
    char *second = plew_argAt(2);
    printf("exit argc=%lld: %s / %s\n", plew_argCount(), first, second);
    plew_rawbuf_drop(first);
    plew_rawbuf_drop(second);
}
void test_register_exit_arguments(void) { atexit(at_exit); }
