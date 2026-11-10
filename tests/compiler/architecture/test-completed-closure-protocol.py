#!/usr/bin/env python3
"""Completed closure signatures reach declaration, call and binding without raw ABI recovery."""
import argparse
import subprocess
from pathlib import Path
root = Path(__file__).resolve().parents[3]
parser = argparse.ArgumentParser()
parser.add_argument('--revision')
options = parser.parse_args()
def source(path):
    if options.revision:
        return subprocess.check_output(['git', '-C', str(root), 'show', options.revision + ':' + path], text=True)
    return (root / path).read_text()
abi = source('src/Backend/Llvm/ValueAbi.pw')
closures = source('src/Backend/Llvm/Closures.pw')
mid = source('src/Backend/Llvm/Mid.pw')

def method(text, name):
    marker = 'fn ' + name + '('
    start = text.index(marker)
    # balanced braces (all methods here use simple balanced diagnostic strings).
    brace = text.index('{', start)
    depth = 1
    end = brace + 1
    while depth:
        depth += (text[end] == '{') - (text[end] == '}')
        end += 1
    return text[start:end]

call = method(mid, 'midCanonicalEmitClosureCall')
assert 'callClosureValueFunction' in call, 'closure indirect call must consume completed descriptor'
assert 'callLegacyValueFunction' not in call, 'ordinary closure call must not reclassify a raw signature'
assert 'LLVMFunctionType' not in call, 'call site must not reconstruct the signature'
assert 'closureValueAbi' in method(closures, 'declareClosure'), 'declaration uses completed callable template'
assert 'closureBodyParameter' in method(mid, 'midPrepareCanonicalLocals'), 'Ready ordinary/environment binding consumes completed descriptor'
assert 'closureValueAbis.getOr' in method(abi, 'closureValueAbi'), 'one physical plan per finalized type within scope'
callee = method(abi, 'callClosureValueFunction')
assert 'validateCallableInputs' in callee and 'validateInput' in callee
assert callee.count('LLVMBuildExtractValue') == 2, 'function/env must be extracted together after fat closure admission'
for name in ['preparedLegacyParameter']:
    assert 'LlvmValueConvention.Closure' in method(abi, name), name + ' must reject completed closure raw bypass'
print('PASS completed closure declaration/call/binding ownership and no raw reclassification')

for name in ['callLegacyValueFunction','legacyValueParameter']:
 assert 'fn '+name+'(' not in abi, name+' raw bypass must be absent'
