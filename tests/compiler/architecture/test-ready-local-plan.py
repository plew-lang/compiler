#!/usr/bin/env python3
"""Ready retains ordinary/program local representation through allocation."""
from pathlib import Path
root=Path(__file__).resolve().parents[3]
text=(root/'src/Backend/Llvm/Mid.pw').read_text()
def method(name):
 start=text.index('    inout fn '+name+'(')
 end=text.find('\n    inout fn ',start+1)
 return text[start:end if end>=0 else len(text)]
admission=method('prepareCanonicalForLlvm')
assert 'prepareBodyLocalPlan(' in admission, 'Ready discards admitted local representation and binding plan'
binding=method('midPrepareCanonicalLocals')
assert 'preparedBodyLocal(' in binding, 'local allocation does not consume retained Ready representation'
assert 'bodyLocalAdmission' in method('genLlvmPreparedMidBody'), 'emission does not retain the Ready plan'
print('PASS normal/program Ready local plans reach final allocation/binding')

async_text=(root/'src/Backend/Llvm/MidAsync.pw').read_text()
start=async_text.index('    inout fn prepareMidAsyncFrame(')
end=async_text.find('\n    inout fn ',start+1)
assert 'midCanonicalLocalTy(' not in async_text[start:end], 'async admission reads a previous emission plan'
assert 'planned locals cannot use legacy emission overrides' in text
assert 'Ready canonical body is out of range' in text
print('PASS admission is independent from active emission plans and bypasses fail closed')
