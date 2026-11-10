---
id: met-xb46
status: closed
deps: []
links: []
created: 2026-11-10T15:51:41Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, tooling, performance]
---
# Compare lower machine-code optimization tiers for development compiler builds


## Finite investigation contract

Compare machine-code O1 and O0 against the retained host O2 object from
met-1hnl. Keep both normal IR pipelines, native CPU apple-m1, verification,
runtime and production native backend identical. Select the lower machine
level only after IR optimization. Diagnostic observer passes are unchanged.
No production defaults, seed, adopted carrier or main integration are in scope.

Questions/scenarios:
- Measure each lower-tier object worker, stages, object/binary size and link.
  The O2 build timing is the previous single-run reference, not a fresh median.
- Link all three objects with the same runtime and native support archive.
- Warm each resulting compiler and alternate five source-to-LLVM trials per
  tier on the same compiler source; require byte-identical raw LLVM and runtime.
- Compare a small valid and invalid source on all three candidate compilers;
  preserve expected stdout/exit/diagnostics, and exercise AOT/lazy execution.
- Retain input hashes, actual exits and independent neutral review. Report any
  untested scope; no full-suite, sanitizer, fixed-point or promotion claim.

This is a configuration experiment, not a bug repair; no artificial RED.
If a lower tier is useful, production-mode selection is a subsequent decision.

## Diagnostic scope adjustment after candidate failure

The default-stack O0 candidate crashed during the first warmup (exit139,
zero output); the original benchmark gate is failed, not a successful comparison.
The crash report places the fault in Stack Guard. Relinking the same O0 object
with a 32MB Mach-O main stack permits identical-LLVM self compilation (23.164s).
A process RLIMIT increase failed before compiler launch and is not a compiler
failure. Continue the planned five-run/smoke comparison with the explicitly
larger-stack O0 diagnostic candidate; O2/O1 keep default stacks. This cannot
qualify default O0 for adoption or silently change normal stack requirements.
The original link-o0 log was overwritten by the stack-control link; its original
command, exit and binary hash remain in build-steps.json, not its full old log.

## Outcome

Investigated; keep normal O2. O1 produces the exact same object as O2 on this
frozen module. O1 worker228.689s versus prior O2 reference227.832s shows no gain.
O0 worker103.440s (machine stage22.027s) is much faster, but the default-stack
candidate crashes. The same object linked with32MB stack succeeds. Five-run
same-source medians are O2 8.119858s, O1 8.210037s and O0-with32MB22.449695s.
All18 LLVM outputs and3 runtimes agree; normal check/AOT/lazy and expected reject
check pass on all three diagnostic candidates. The final39-step gate passes
with unchanged inputs. Default O0 failure is preserved, not counted as success.

[Evidence, scopes, failed controls and recipe](../../../evidence/machine-code-tiers/README.md).
No normal defaults/source, main/seed/adopted carrier changed. No full-suite,
sanitizer or formal new fixed-point certification. O0 stack-demand root cause
is not traced beyond the stack-guard failure and larger-stack successful control;
it is a limitation of this rejected optimization option, not a required repair.

Closure reason: investigated. Independent neutral review accepted the finite
comparison, recomputed all medians and checked source/runtime/golden assertions
and frozen-input receipts. Its limits are explicitly retained in the evidence.
[Final review](../../../evidence/machine-code-tiers/final-review.json).
