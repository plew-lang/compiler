#!/usr/bin/env python3
"""Check the bounded Witness admission-to-consumer handoff.

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
witness = source('src/Backend/Llvm/Any.pw')
assert 'Witness(abiId:' in backend, 'Ready witness admission discards erased receiver and ordinary lane-to-local bindings'
assert 'ErasedReceiver(parameterIndex:' in backend, 'Ready lacks selected erased receiver conversion'
assert 'prepareWitnessLocalBindings(' in method(mid, 'prepareBodyLocalPlan'), 'Ready does not retain admitted witness bindings'
local = method(mid, 'midPrepareCanonicalLocals')
assert 'LlvmLocalBinding.ErasedReceiver(' in local and 'LlvmLocalBinding.Parameter(' in local, 'final local binding does not consume witness conversions'
emit = method(witness, 'emitExistentialWitnesses')
assert 'abiParameterValues:' not in emit and 'Array[LLVMValueRef]' not in emit, 'witness emission expands untyped input vectors'
assert 'legacyValueParameter(' not in emit and 'llvmLoad(' not in emit, 'witness emission reselects erased receiver adaptation'
print('PASS retained Witness receiver and ordinary bindings reach final local preparation')
