#!/usr/bin/env python3
"""Check the bounded Closure/EnvironmentDrop admission-to-consumer handoff.

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
closures = source('src/Backend/Llvm/Closures.pw')
assert 'enum LlvmLocalBinding' in backend, 'Ready closure admission discards explicit parameter/environment-to-local bindings'
assert 'Closure(abiId:' in backend and 'EnvironmentDrop(abiId:' in backend, 'Ready lacks distinct closure/environment-drop entry identities'
assert 'environmentType:' in backend and 'binding: LlvmLocalBinding' in backend, 'Ready loses admitted environment layout or local binding rows'
prepare = method(mid, 'prepareBodyLocalPlan')
assert 'prepareClosureLocalBindings(' in prepare, 'Ready does not retain admitted closure bindings'
local = method(mid, 'midPrepareCanonicalLocals')
assert 'LlvmLocalBinding.Parameter(' in local and 'LlvmLocalBinding.Environment(' in local, 'final local binding does not consume retained rows'
for name in ('emitClosures', 'emitClosureEnvironmentDrops'):
    emit = method(closures, name)
    assert 'abiParameterStart:' not in emit and 'abiParameterValues:' not in emit and 'closureBodyId:' not in emit, name + ' still supplies raw binding overrides'
    assert 'closureEnvTy(' not in emit and 'captureSlotTy(' not in emit, name + ' reconstructs retained environment representation'
    assert 'Array[LLVMValueRef]' not in emit, name + ' still expands untyped input vectors'
emit = method(mid, 'genLlvmPreparedMidBody')
assert 'bindMidClosureCaptures(' not in emit, 'emission still revalidates semantic capture correspondence'
print('PASS retained Closure/EnvironmentDrop plans reach final typed local bindings')
