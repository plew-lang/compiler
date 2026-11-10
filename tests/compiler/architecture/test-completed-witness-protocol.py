#!/usr/bin/env python3
"""Public existential endpoints connect declaration/call/Ready without raw reconstruction."""
from pathlib import Path
import argparse,subprocess
root=Path(__file__).resolve().parents[3]
parser=argparse.ArgumentParser();parser.add_argument('--revision');args=parser.parse_args()
def read(path):
 return subprocess.check_output(['git','-C',str(root),'show',args.revision+':'+path],text=True) if args.revision else (root/path).read_text()
def method(text,name):
 start=text.index('fn '+name+'(');brace=text.index('{',start);depth=1;end=brace+1
 while depth:
  depth+=(text[end]=='{')-(text[end]=='}');end+=1
 return text[start:end]
any=read('src/Backend/Llvm/Any.pw');mid=read('src/Backend/Llvm/Mid.pw');abi=read('src/Backend/Llvm/ValueAbi.pw')
call=method(mid,'midCanonicalEmitExistentialCall');decl=method(any,'buildAnyThunk');bind=method(mid,'midPrepareCanonicalLocals')
assert 'callWitnessValueFunction' in call,'witness call still reconstructs raw per-call ABI'
assert 'callLegacyValueFunction' not in call and 'LLVMFunctionType' not in call
assert 'LLVMBuildGEP2' not in call,'typed fat consumer owns vtable slot extraction'
assert 'witnessTemplateForMember' in decl and 'witnessBodyValueAbi' in decl
assert 'declareLegacyBodyFunction' not in decl and 'LLVMFunctionType' not in decl
assert 'witnessBodyParameter' in bind,'Ready witness inputs must consume completed descriptor'
for name in ['callLegacyValueFunction','legacyValueParameter','preparedLegacyParameter']:
 assert 'LlvmValueConvention.Witness' in method(abi,name),name+' must reject completed witness bypass'
for name in ['witnessTemplateForCall','witnessTemplateForMember']:
 body=method(any,name)
 assert body.index('cachedWitnessValueAbi')<body.index('Array['),'cache hit must precede vector materialization'
 assert 'existentialRequirementSignature(' not in body,'backend cannot re-resolve public signature'
print('PASS completed public witness endpoint declaration/call/Ready and no raw reclassification')
