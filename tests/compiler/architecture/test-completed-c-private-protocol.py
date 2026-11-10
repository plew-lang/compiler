#!/usr/bin/env python3
"""C conversion must join the ordinary typed private Body protocol."""
from pathlib import Path
import argparse
import subprocess
root = Path(__file__).resolve().parents[3]
parser = argparse.ArgumentParser()
parser.add_argument('--revision')
args = parser.parse_args()
def source(name):
    if args.revision:
        return subprocess.check_output(['git', '-C', str(root), 'show', args.revision + ':' + name], text=True)
    return (root / name).read_text()
entry = source('src/Backend/Llvm/ProvidedFns.pw')
start = entry.index('    inout fn emitExposedEntry(')
end = entry.index('\n    inout fn ', start + 1)
entry = entry[start:end]
assert 'callBodyValueFunction(' in entry, 'converted C values still bypass typed Body inputs'
assert 'Array[LlvmValueInput]' in entry and 'LlvmParameterRole.Ordinary' in entry
assert 'semanticType=prepared.parameterTypes[index]' in entry
assert 'argumentValueMode(passing: prepared.parameterPassings[index])' in entry
for conversion in ['scalarFromC(', 'prepareCInout(', 'completeCInouts(', 'scalarToC(', 'attachCIntegerExtension(']:
    assert conversion in entry, 'C conversion/attribute path lost: ' + conversion
assert 'callLegacyValueFunction(' not in entry
for name in ['src/Backend.pw', 'src/Backend/Llvm/ValueAbi.pw', 'src/Backend/Llvm/ProvidedFns.pw']:
    text = source(name)
    assert 'LlvmBodyCompatibility' not in text and 'bodyAdapter' not in text, 'raw Body compatibility authority remains'
print('PASS C conversion joins typed private Body inputs; no raw Body permission')
