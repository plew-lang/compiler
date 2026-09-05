#!/bin/zsh
# Run one foreground command while making long silent phases observable.
#
# This is intentionally a wrapper, not a success/failure adapter: stdout is
# untouched, stderr is mirrored verbatim, and this script returns the child's
# exact exit status.  It is the common fallback for external tools or compiler
# phases that have not yet gained an internal counter/heartbeat.

set -u

if (( $# == 0 )); then
  print -u2 "usage: ./progress.sh <command> [args...]"
  exit 64
fi

progress_log=$(mktemp -t plew-progress.XXXXXX)
progress_ticker_pid=""
cleanup_progress() {
  if [[ -n "$progress_ticker_pid" ]]; then
    kill "$progress_ticker_pid" 2>/dev/null || true
    wait "$progress_ticker_pid" 2>/dev/null || true
  fi
  rm -f "$progress_log"
}
trap cleanup_progress EXIT INT TERM

started_at=$(date +%s)
progress_ticker() {
  while true; do
    sleep 30
    now=$(date +%s)
    elapsed=$((now - started_at))
    last_line=$(tail -n 1 "$progress_log")
    if [[ -z "$last_line" ]]; then
      last_line="(no stderr phase reported yet)"
    fi
    print -u2 "[progress] elapsed=${elapsed}s last=${last_line}"
  done
}

progress_ticker &
progress_ticker_pid=$!

"$@" 2> >(tee "$progress_log" >&2)
child_exit=$?
exit "$child_exit"
