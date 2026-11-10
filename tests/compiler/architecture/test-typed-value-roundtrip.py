#!/usr/bin/env python3
"""Normal calls and bindings cannot use the untyped compatibility boundary."""
from pathlib import Path
import re
root=Path(__file__).resolve().parents[3]
text=(root/'src/Backend/Llvm/Mid.pw').read_text()
def method(name):
 start=text.index('    inout fn '+name+'(')
 end=text.find('\n    inout fn ',start+1)
 return text[start:end if end>=0 else len(text)]
call=method('midCanonicalEmitDirectCall')
for branch in ['else if useMethod', 'else { result']:
 line=next(line for line in call.splitlines() if branch in line)
 assert not re.search(r'call(?:Legacy)?ValueFunction\(',line), 'normal call bypasses logical-role typed inputs: '+line.strip()
assert 'callBodyValueFunction(' in call, 'normal call does not consume stored body descriptor'
binding=method('midPrepareCanonicalLocals')
assert 'normalBodyParameter(' in binding, 'normal binding does not consume typed Value/Home input'
print('PASS normal typed call/binding round trip has no raw compatibility fallback')

abi=(root/'src/Backend/Llvm/ValueAbi.pw').read_text()
assert 'fn callLegacyValueFunction(' not in abi
assert 'fn legacyValueParameter(' not in abi
assert 'normal body cannot use raw prepared binding' in abi
adapters=[]
for path in (root/'src/Backend/Llvm').glob('*.pw'):
 for line in path.read_text().splitlines():
  if 'bodyAdapter: <Optional.Some' in line:
   adapters.append(path.name)
assert not adapters, adapters
destruction=(root/'src/Backend/Llvm/StmtDeinit.pw').read_text()
assert 'callBodyValueFunction(' in destruction
assert 'LlvmBodyCompatibility.Destruction' not in destruction
print('PASS user deinit and C conversion consume typed Body inputs; no raw compatibility remains')

# Every normal-body publisher must carry the target signature receiver, even
# generated newtype/witness adapters whose source receiver is a different term.
publishers=[]
for path in (root/'src/Codegen/Mono').glob('*.pw'):
 for line in path.read_text().splitlines():
  if 'self.appendFinalCallee(' in line and 'calleeBodyId:' in line:
   assert 'receiverSignatureTypeRef: signature.receiverType' in line, str(path)
   publishers.append(path.name)
assert sorted(publishers)==['Call.pw','Call.pw','Newtype.pw'], publishers
print('PASS normal and generated publishers retain canonical receiver terms')
