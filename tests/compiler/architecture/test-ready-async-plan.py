#!/usr/bin/env python3
"""Check the bounded async activation admission-to-consumer handoff.

--revision permits the exact baseline structural RED without building it.
"""
import argparse
from pathlib import Path
import subprocess

root = Path(__file__).resolve().parents[3]
parser = argparse.ArgumentParser()
parser.add_argument('--revision')
args = parser.parse_args()
def source(path):
    if args.revision:
        return subprocess.check_output(['git', '-C', str(root), 'show', args.revision + ':' + path], text=True)
    return (root / path).read_text()
def method(text, name):
    start = text.index('    inout fn ' + name + '(')
    end = text.find('\n    inout fn ', start + 1)
    return text[start:end if end >= 0 else len(text)]
backend = source('src/Backend.pw')
mid = source('src/Backend/Llvm/Mid.pw')
async_mid = source('src/Backend/Llvm/MidAsync.pw')
async_entry = source('src/Backend/Llvm/Async.pw')
assert 'AsyncResume(activationId:' in backend, 'Ready async admission discards activation-local frame storage and entry input mappings'
assert 'FrameField(field:' in backend, 'Ready lacks retained frame-to-local storage selection'
assert 'admitMidAsyncActivation(' in async_mid, 'async activation bypasses common physical admission'
ready = backend[backend.index('enum MidLlvmPrepared'):backend.index('// Local representation')]
assert 'abiParameterCount:' not in ready, 'Ready retains obsolete raw parameter count'
for token in ('abiParameterValues', 'abiParameterStart', 'localsPrepared', 'closureBodyId:'):
    assert token not in method(mid, 'genLlvmPreparedMidBody'), 'common emitter retains raw binding override ' + token
local = method(mid, 'midPrepareCanonicalLocals')
assert 'FrameField(' in local and 'preparedBodyLocal(' in local, 'final local allocation does not consume retained frame fields'
assert 'storage: Array[LLVMValueRef]' not in local and 'initializeParameters' not in local, 'local preparation retains raw storage bypass'
resume = method(async_mid, 'genLlvmMidAsyncResume')
assert 'localSlots' not in async_mid and 'localSlots' not in async_entry, 'async frame still transports owning slot arrays'
assert 'MidLlvmPrepared.Ready canonical=' not in resume, 'resume fabricates unadmitted Ready'
assert 'genLlvmPreparedMidBody(' in resume, 'resume bypasses common Ready consumer'
assert 'legacyValueParameter(' not in method(async_entry, 'genLlvmAsyncFunc'), 'async entry reconstructs raw input bindings'
print('PASS retained async activation inputs/storage reach common Ready consumer')

inputs = backend[backend.index('struct LlvmAsyncActivationInput'):backend.index('struct LlvmAsyncActivation {')]
assert 'semanticType:' not in inputs, 'async input duplicates the local semantic type authority'
assert 'typeRef: local.semanticType' in method(async_entry, 'genLlvmAsyncFunc'), 'async ARC does not consume retained local type'
assert 'midCanonicalLocalTy(' not in method(async_mid, 'admitMidAsyncActivation'), 'async admission reads ambient emission state'
assert 'lowerMidLocalType(' not in method(async_mid, 'genLlvmMidAsyncResume'), 'resume re-lowers admitted local types'
assert 'LlvmBodyLocalAdmission.Legacy' not in mid, 'Ready retains an unchecked local fallback'

assert 'lane.semanticType != rows[index].semanticType' in method(async_mid, 'admitMidAsyncActivation'), 'async admission loses completed semantic lane correspondence'
assert 'LLVMFunctionType(self.ptrty, arrayCPtr(parameters)' not in method(async_mid, 'admitMidAsyncActivation'), 'async admission reconstructs a competing physical signature'

assert 'asyncBody:' not in method(mid, 'genLlvmPreparedMidBody').split('->', 1)[0], 'common emitter accepts external async-mode override'

assert 'declaration.isBorrowed' in method(async_mid, 'admitMidAsyncActivation'), 'owned async inputs accept borrowed local aliases'
assert 'fn midCanonicalLocalTy(body:' in mid, 'retained local type reader still accepts semantic context or mutation authority'
