---
id: met-8mfk
status: closed
deps: []
links: []
created: 2026-11-10T14:08:21Z
type: task
priority: 2
assignee: Koji Murata
tags: [tooling, performance]
---
# Compact retained LLVM trace logs without changing supervision


## Guarantee and Completion

Compact only retained LLVM trace detail in process_watch traced mode; consume
all original progress and preserve existing deadline, worker events, exit/status
and process-group cancellation. Keep source phase events, unknown diagnostic
bytes (including partial/long lines), final counters and latest sampled LLVM
context. Full diagnostic logging remains explicit opt-in. Untraced watch stderr
is unchanged. No compiler/LLVM pass, semantic rule or60-second limit changes.

TDD scenarios: high-volume LLVM detail reduces stored bytes; full opt-in retains
exact raw stderr; fragmented/binary/unterminated/long diagnostic preservation;
progress-only stream remains alive past deadline, details/diagnostics cannot
hide a real stall; interruption/cancellation/exit propagation existing controls.
Use the real monitoring integration suite, real captured build-trace replay and
independent neutral review. No whole compiler rebuild or speedup claim required.

## Outcome

Resolved: traced logs now default to compact recognized LLVM detail; every
original line still drives the unchanged classifier/deadline. Source phases,
unknown and partial/binary/long diagnostics, final counters and latest sampled
context remain. Explicit PLEW_TRACE_LOG=full preserves exact raw logging and is
recorded by validation. Untraced supervision ignores that setting. No LLVM
passes/flags, source semantics,60-second limit or group recovery is changed.

Dense-log storage assertion has actual RED→GREEN. All40 meta monitoring tests
and10 unchanged real-LLVM measurement-tool cases pass. Captured standard build
trace replay preserves2,978,160 events while reducing364,706,567→666,265bytes.
Source/evidence independent review identified an untraced mode boundary and
finite tests, all addressed. Speed improvement was not measured or promised.

[Retained evidence and limits](../../../evidence/compact-trace-logging/README.md).
No full compiler rebuild, formal fixed point, whole-suite or promotion claim.
