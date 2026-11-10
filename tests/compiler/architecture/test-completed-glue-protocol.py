#!/usr/bin/env python3
"""Ownership glue carries explicit operations through declaration, calls and binding."""
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
assert 'OwnershipGlue(operation:' in physical, 'ownership glue still has only opaque Legacy lanes'
glue = read('src/Backend/Llvm/OwnershipGlue.pw')
for name in ['glueValueAbi', 'declareGlueValueFunction', 'callGlueValueFunction',
             'glueValueParameter', 'callErasedGlueValueFunction']:
    assert 'fn ' + name + '(' in glue, name + ' must own the completed handoff'
for path in ['Any.pw', 'Closures.pw', 'Arrays.pw', 'Enums.pw', 'StmtDeinit.pw']:
    text = read('src/Backend/Llvm/' + path)
    for family in ['EnvironmentDrop', 'ExistentialCopy', 'ExistentialDrop',
                   'StructRetain', 'StructDrop', 'EnumRetain', 'EnumRelease']:
        assert 'LlvmLegacyConvention.' + family not in text, path + ' still uses raw ' + family
assert 'LlvmBodyCompatibility.Destruction' not in read('src/Backend/Llvm/StmtDeinit.pw'), 'user deinit still bypasses typed Body inputs'
assert 'glueValueParameter' in read('src/Backend/Llvm/Mid.pw'), 'Ready environment drop must decode completed glue'
print('PASS completed ownership glue operations, typed calls/bindings and retired raw families')
