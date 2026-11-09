#!/usr/bin/env python3
"""Normal declaration sites consume the common completed-signature planner."""
from pathlib import Path

root = Path(__file__).resolve().parents[3]
for path, name in [('ProvidedFns.pw', 'declareGenFns'),
                   ('GenMethods.pw', 'declareOneGenMethod')]:
    text = (root / 'src/Backend/Llvm' / path).read_text()
    start = text.index('    inout fn ' + name + '(')
    end = text.find('\n    inout fn ', start + 1)
    body = text[start:end if end >= 0 else len(text)]
    assert 'LLVMFunctionType(' not in body, (
        name + ' independently constructs a raw signature, losing logical lane roles')
    assert 'bodyParameterLlvmTy(' not in body, (
        name + ' duplicates parameter layout outside the shared signature owner')
print('PASS normal declarations consume the physical signature owner')
