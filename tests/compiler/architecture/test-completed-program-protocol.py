#!/usr/bin/env python3
"""Program entries and requested publication have explicit ABI authorities."""
from pathlib import Path
import argparse
import subprocess
root = Path(__file__).resolve().parents[3]
parser = argparse.ArgumentParser()
parser.add_argument('--revision')
args = parser.parse_args()
def source(name):
    if args.revision:
        result = subprocess.run(['git', '-C', str(root), 'show', args.revision + ':' + name], capture_output=True, text=True)
        return result.stdout if result.returncode == 0 else ''
    return (root / name).read_text()
program = source('src/Backend/Llvm/ProgramAbi.pw')
assert 'programValueAbi(' in program, 'program entries lack completed descriptors'
for name in ['declareProgramValueFunction(', 'programNativeAbi(', 'programValueParameter(']:
    assert name in program
entry = source('src/Backend/Llvm/Entry.pw')
async_entry = source('src/Backend/Llvm/Async.pw')
assert 'mainFunctionType(' not in entry + async_entry
assert 'declareProgramValueFunction(' in entry and 'declareProgramValueFunction(' in async_entry
assert 'programValueParameter(' in entry
mid = source('src/Backend/Llvm/Mid.pw')
assert 'local admission lacks a completed entry descriptor' in mid
assert 'mainFunctionType(' not in mid + source('src/Backend/Llvm/MidAsync.pw')
native = source('native/llvm_backend.cpp')
assert 'sourceAbiReceipt(' in native and 'registerSourceEntry(' in native
assert 'conflicting source entry ABI' in native
assert 'sourceBodyIdentity(' in native
exposed = source('src/Backend/Llvm/ProvidedFns.pw')
start = exposed.index('    inout fn emitExposedEntry(')
exposed = exposed[start:exposed.index('\n    inout fn ', start + 1)]
assert exposed.count('attachCIntegerExtension(') == 2
assert exposed.rindex('attachCIntegerExtension(') < exposed.index('match self.emission'), 'declaration-only C ABI omits integer attributes'
print('PASS completed program descriptors and checked requested ABI registration')
