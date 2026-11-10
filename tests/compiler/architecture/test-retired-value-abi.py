#!/usr/bin/env python3
"""Only the unsupported closure declaration may retain a legacy ABI."""
from pathlib import Path
import argparse, subprocess
root=Path(__file__).resolve().parents[3]
p=argparse.ArgumentParser();p.add_argument('--revision');a=p.parse_args()
def read(name):
 return subprocess.check_output(['git','-C',str(root),'show',a.revision+':'+name],text=True) if a.revision else (root/name).read_text()
abi=read('src/Backend/Llvm/ValueAbi.pw')
for name in ['callLegacyValueFunction','declareLegacyValueFunction','legacyValueParameter']:
 assert 'fn '+name+'(' not in abi, 'unused raw private ABI remains: '+name
assert 'family.key() != 1U64' in abi, 'legacy construction must reject every retired family'
assert 'legacy parameter requires the unsupported closure convention' in abi
physical=read('src/Backend/PhysicalSignature.pw')
assert 'only the unsupported closure may use a legacy signature' in physical
print('PASS unused raw private ABI APIs removed; legacy construction/binding limited to unsupported closure')
