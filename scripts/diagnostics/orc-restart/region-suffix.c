#undef malloc
#undef calloc
#undef realloc
#undef free
#undef plew_loop_run
void plew_loop_run(void) {}
long long probe_pending(void) { return plew_timers_len + plew_ready_len - plew_ready_head; }
// Called only after the host has disabled entry and no native stack is running.
// The entire runtime dylib is closed next; these pointers must never be reused.
void probe_reset_state(void) {
  if (plew_access_head) abort();
  plew_ready = NULL; plew_ready_len = plew_ready_cap = plew_ready_head = 0;
  plew_timers = NULL; plew_timers_len = plew_timers_cap = plew_vnow = 0;
  plew_argc = 0; plew_argv = NULL; plew_last_exit = 0;
}
