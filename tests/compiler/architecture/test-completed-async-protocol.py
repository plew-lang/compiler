#!/usr/bin/env python3
"""Async declaration, activation acquisition and resume consume completed lanes."""
from pathlib import Path
import argparse
import subprocess

root = Path(__file__).resolve().parents[3]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--revision')
args = parser.parse_args()

def read(path):
    if args.revision:
        result = subprocess.run(['git', '-C', str(root), 'show', args.revision + ':' + path],
                                capture_output=True, text=True)
        return result.stdout if result.returncode == 0 else ''
    file = root / path
    return file.read_text() if file.exists() else ''

physical = read('src/Backend/PhysicalSignature.pw')
assert 'LlvmValueConvention.AsyncEntry' in physical, 'async entry still has opaque Legacy parameters'
assert 'LlvmValueConvention.AsyncResume' in physical and 'Frame(bodyId:' in physical
entry = read('src/Backend/Llvm/Async.pw')
mid = read('src/Backend/Llvm/Mid.pw')
activation = read('src/Backend/Llvm/MidAsync.pw')
for family in ['AsyncEntry', 'AsyncResume']:
    assert 'LlvmLegacyConvention.' + family not in entry + activation, 'async producer/activation retains raw ' + family
assert 'asyncBodyValueAbi' in entry and 'asyncValueParameter' in entry
assert 'callAsyncEntryValueFunction' in mid and 'callAsyncResumeValueFunction' in entry
assert 'asyncValueParameter' in mid, 'Ready resume still reads a raw frame pointer'
assert 'preparedLegacyParameter' not in entry
assert 'asyncEntryTy' not in entry + mid, 'async entry retains a competing signature array'
assert 'LLVMFunctionType(self.ptrty, arrayCPtr(parameters)' not in activation, 'activation reclassifies its entry signature'
assert 'bodyResultTerm' in read('src/Backend/Llvm/AsyncAbi.pw'), 'Promise transport and body payload are conflated'
print('PASS completed async entry/frame/resume lanes and retired raw classification')
