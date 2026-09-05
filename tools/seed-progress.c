// Diagnostic seed bridge. No Plew values cross this observation boundary.
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

void plew_seed_generic_progress(uint64_t completed, uint64_t total) {
    static time_t started, reported;
    static uint64_t previous;
    time_t now = time(NULL);
    if (!started) started = now;
    if (completed == 0 || completed == total ||
        (completed != previous && now - reported >= 1)) {
        fprintf(stderr, "[seed-progress] generic-body-check completed=%" PRIu64
                "/%" PRIu64 " elapsed=%lds\n", completed, total,
                (long)(now - started));
        fflush(stderr);
        reported = now;
        previous = completed;
    }
}
