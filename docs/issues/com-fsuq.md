---
id: com-fsuq
status: open
deps: []
links: []
created: 2026-10-27T18:40:48Z
type: bug
priority: 1
assignee: Koji Murata
tags: [verification, tooling]
---
# Reject non-source failures in negative-test result classification

Prevent normal reject and partreject workers from reporting PASS for non-source compiler failures.

Confirmed audit evidence: evidence/test-audit/rejection-classification.json (meta) executes the actual worker bodies extracted from tests/harness/test.sh, with production supervisors and fixed compiler doubles. Without .err, silent exit 1 and a plewc internal-error diagnostic plus exit 1 both publish PASS for both phases. With a reason companion, unrelated text fails in the measured controls. No real compiler miscompile/rejection or individual wrong expectation is claimed.

Guarantee: a negative source test passes only for the intended class of compiler rejection; signals, timeout, silent non-source failures and internal failures must not be counted as success. Preserve valid source rejection, diagnostic substring checks, expected program panic semantics, worker aggregation/progress and source inputs.

Before changing code, independently inspect diagnostic/runner contracts and history. Add controlled-double RED cases that exercise the production worker, with/without companions, proper diagnostics, no diagnostic, internal failure, ordinary wrong exit and signal. Avoid an independent copy of worker classification. Find the responsible shared classification boundary rather than weakening expectations or filtering the offending inputs. If internal failure cannot be reliably distinguished by the available result contract, document the required diagnostic/exit boundary and seek an unresolved design decision instead of assuming a regex is sound.

Excluded: adding .err to all 427 cases, correcting each fixture expectation, compiler semantics changes, suite reduction, weakening sanitizer/watchdog checks, or claims about all other runner phases. Those audits remain with com-e713/com-5zvv.

Acceptance: discriminating RED/GREEN controls plus affected production worker/runner checks; independent review of actual failure paths and source-result contract. Repair execution is separate from audit work; this issue has no dependency on audit closure and does not become an audit completion prerequisite.

Found by com-ouh2; source baseline tests/harness/test.sh SHA is in the evidence snapshot.

