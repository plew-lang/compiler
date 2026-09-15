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
