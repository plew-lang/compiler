---
id: com-ctl6
status: in_progress
deps: []
links: []
created: 2026-11-26T00:16:03Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-yeua
tags: [frontend, diagnostics, verification]
---
# Retain root-only use refusals through source-loading consumers



## Contract and finite scope

Current fixed ff4 normal235 negative failures include exactly four with the
root-only use diagnostic: partreject/{part_use_selective,part_pub_use_nested,
generated_part_use,part_use_namespace_alias}. The completed caf022 receipts
record intended rejection but Unclassified transport. Loader.pw's actual part
import branch at load/lower is the candidate producer, not message grouping as
admission authority. Preserve the root-only rule, module-wide part bindings,
public status/message and generated-part behavior.

com-w4c2 owns and closed the rule/migration; do not reopen its semantics or
reimplement module lookup. This child owns only this demonstrated refusal's
source origin through actual load/admission/cache/session/CLI consumers.
Other loader errors, all259 failures, gen's separate consumer com-k4c9, other
API narrowing and new macro exceptions are excluded.

## Investigation before implementation

Trace the actual root/part/generated source file registration, parsed import
identity/role/span, fresh source-input parsing versus Raw structural entries, error restoration,
failed construction/cache and final owner/adapter. Select the smallest retained
producer-owned proof using existing source-input contracts. Editable Comp flags,
public spans/AST, origin enum or same text alone must not grant Source. Identify
and remove competing interpretation, not add another source checker.

## Scenarios and completion

- Freeze the four real fixtures on adopted ff4 across check/AOT/ORC; keep exact
  status/message and distinguish generated-part preparation demand.
- Root selective/namespace/pub imports and legitimate parts remain valid;
  generated input does not gain an implicit exception or change lookup.
- Actual refusal creation and retained final consumer. Raw/foreign AST/directive
  and invalid structural range queries never gain Source. Root source input
  permits use; actual parsed part input refuses it. A new source-byte parser
  invocation is an owned source operation, not a semantic request borrowing a
  foreign session; add no artificial session-token API. Cover failed open result
  retention at its real boundary; no live session/body cache exists after a
  pre-Lower open failure.
- Preserve Input/Tool/Internal/Limit distinctions; unrelated loader failures and
  same-text injected helper failure cannot acquire this source origin.
- Native meaningful RED/GREEN, fresh CLI/controls, applicable regression/formal
  <=7.5s, independent guarantee review, evidence publication and bounded cleanup.
  Parent com-yeua and phase3 remain open until their own full gates.

## Starting evidence

met-un2r is closed at20a7b325; product e27ce3e5, formalG2/7.361221s and full
caf022 baseline259/3313 fixed-source cases. Saved development carrier
bin/carriers/ff4a21a5861e/plewc has identical frozen std. Full failure receipts
and root-use cases are in the type-visibility-refusals whole reconciliation.
The stderr histogram is only a hint; no complete producer audit of259 is claimed.


## Executed RED and selected design

Fixed ff4 reproduces all4 cases in check/AOT/ORC: correct diagnostic/status1,
actual channel Unclassified. Three root/shared-part positives pass9 modes with
expected ORC output. Inputs including frozen std, Syntax and fixture files are
unchanged. CLI result: root-use-refusal-cli-red-v1.

Actual route: loadFrontendDeclarations reads one source String, appends its
bytes, registers the file and parseFileSyntax constructs Lexer/P from those
bytes. The parser's own syntax-error contract is already Source. Immediately
following parse, loader-local rootSeen/moduleId determines part membership;
generated siblings enter that same work queue. checkPartSyntaxOnly is a public
Raw SyntaxSlice validator and cannot acquire Source merely from current Comp
state. Published recursively reaches the underlying Import node. No session is
returned when CompilerSession.open fails here; do not invent lazy-body retries.

Independently reviewed approach: private source-input operation owns append,
file registration, fresh parse and part-rule check for that same source String
and loader-local Root/Part target. It does not accept an external SyntaxSlice,
fileStart or report for promotion. Shared structural core consumes immutable
syntax/root/item values, returns a typed rule verdict, and remains the one
checker. Public structural APIs map it to their Raw reports. The fresh source
operation creates Source only for its actual RootOnlyUse verdict; other part
reports and unrelated Source/Input/Tool/Internal/Limit branches retain their
existing domains. No body/type seal, permanent SyntaxFile snapshot or event
ledger is needed. Private target data is from the load graph, not an editable
Comp flag or Source-admission enum.

com-qt11 retains broader parser/structural API capability narrowing. The new
pure structural core naturally removes Comp from that decision; this child does
not close its remaining entry/diagnostic responsibilities. Direct opaque node
readers still require valid IDs; broader reader hardening remains with that API
owner. New structural slice range checks must fail Internal rather than panic or
Source, and have their own native RED before repair.


Native REDs are executed on frozen inputs: the actual Source-input open failure
still has Unclassified domain; an empty-store SyntaxSlice(count1) panics with
index-out-of-bounds. Both compiled/linked successfully, so these are target
failures, not test setup. [RED evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/root-use-refusals/red.json).

## Implemented boundary and current verification

Private parseLoadedSource now owns source bytes, delimiter append, derived base,
file registration, fresh parse and part admission. PartSyntaxCheck is the shared
immutable structural decision; Raw public adapters retain Unclassified reports.
Only its fresh RootOnlyUse verdict creates Source. Other part item failures keep
their domain; invalid Raw ranges return Internal without indexing.

Native producer, session-open failure retention, Raw/foreign/direct-item and
same-text non-Source controls pass. An unrelated partfreefn remains Unclassified.
Bounds RED panic is replaced by Internal. Service RED was an actual domain
assertion after successful compile/link; the first GREEN setup syntax error is
not counted as a RED. [Native evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/root-use-refusals/native.json).

Independent implementation review found no must-fix. It checked delimiter, file
range, rootSeen and pendingRoots. Rejected part now fails before local
pendingRoots append; the local array never escapes on failure. Its parse-done
trace is consequently absent, while registered source/syntax prefix is unchanged.
No extra parse, AST snapshot or event ledger was introduced. Fresh compiler CLI,
whole reconciliation and formal performance remain required; task stays open.
