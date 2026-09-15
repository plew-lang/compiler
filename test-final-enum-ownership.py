#!/usr/bin/env python3
"""Prevent enum ARC from recovering payload facts from declarations or ambient binders."""
from pathlib import Path
import re

source = (Path(__file__).resolve().parent / 'src/Backend/Llvm/Enums.pw').read_text()
for name in ('enumNeedsDeinit', 'emitEnumOwnership', 'emitEnumReleaseWitnessBodies'):
    match = re.search(r'    inout fn ' + name + r'\([^\n]+\{\n(.*?)(?=\n    inout fn |\Z)', source, re.S)
    assert match, f'missing ownership entry: {name}'
    body = match.group(1)
    for forbidden in ('arcNeedsRelease(', 'arcFieldTy(', 'fieldIsBoxed(', 'enumVariantAt(', 'setEnumEnv(', 'groundTypeRef(', 'findOrAddTypeRef('):
        assert forbidden not in body, f'{name} re-resolves payload facts through {forbidden}'
print('PASS enum ownership consumes frozen payload facts')

arrays = (Path(__file__).resolve().parent / 'src/Backend/Llvm/Arrays.pw').read_text()
for name in ('emitRetainWitnessWalk', 'emitRetainWitnessBodies'):
    match = re.search(r'    inout fn ' + name + r'\([^\n]+\{\n(.*?)(?=\n    inout fn |\Z)', arrays, re.S)
    assert match, f'missing struct ownership entry: {name}'
    for forbidden in ('arcNeedsRelease(', 'arcFieldTy(', 'fieldIsBoxed(', 'structAt(', 'setStructEnv(', 'groundTypeRef('):
        assert forbidden not in match.group(1), f'{name} re-resolves ownership through {forbidden}'
for retired in ('deepCopyStructValue', 'deepCopyEnumRef', 'deepCopyEnumValue', 'copyArrayValue', 'copyWitSlot', 'enumCopyWitSlot'):
    assert retired not in source + arrays, f'retired eager-copy path returned: {retired}'
print('PASS struct copies share frozen retain contracts')

for name in ('valueArc',):
    match = re.search(r'    inout fn ' + name + r'\([^\n]+\{\n(.*?)(?=\n    inout fn |\Z)', arrays, re.S)
    assert match, f'missing ownership entry: {name}'
    for forbidden in ('arcClassOfRef(', 'setStructEnv(', 'groundTypeRef('):
        assert forbidden not in match.group(1), f'{name} reopens ownership through {forbidden}'
print('PASS value ARC consumes finalized classification')
