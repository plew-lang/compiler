#!/usr/bin/env python3
"""Validate lazy count emission in generated LLVM (no LLVM rewriting)."""
from pathlib import Path
import re,sys
llvm=Path(sys.argv[1]).read_text()
functions=re.findall(r'^define [^\n]+\{\n(.*?)^}',llvm,re.M|re.S)
cascades=0
for function in functions:
    blocks=re.findall(r'^([\w.]+):[^\n]*\n(.*?)(?=^[\w.]+:|\Z)',function,re.M|re.S)
    for name,body in blocks:
        if name.startswith('arrrel.free'):
            assert len(re.findall(r'call i64 @plew_rawbuf_count\(',body))==1, f'{name}: final-owner cascade must obtain its own count'
            cascades+=1
assert cascades>0,'input does not exercise element-owning buffer release'
print(f'PASS: {cascades} final-owner cascade blocks obtain their own count')
