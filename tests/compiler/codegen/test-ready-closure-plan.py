#!/usr/bin/env python3
"""Exercise private Ready APIs in an unchanged source snapshot plus test main."""
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
root=Path(__file__).resolve().parents[3]
compiler=Path(os.environ.get('PLEWC',root/'bin/plewc')).absolute()
config=os.environ.get('LLVM_CONFIG','/opt/homebrew/opt/llvm/bin/llvm-config')
out=root/'tmp/value-abi/ready-closure-plan'
out.mkdir(parents=True,exist_ok=True)
(out/'summary.json').unlink(missing_ok=True)
snapshot=out/'source'
if snapshot.exists(): shutil.rmtree(snapshot)
shutil.copytree(root/'src',snapshot/'src')
original=(root/'src/Backend.pw').read_bytes()
test=(root/'tests/compiler/codegen/ReadyClosurePlanMain.pw').read_bytes()
entry=snapshot/'src/Backend.pw'
entry.write_bytes(original+b'\n'+test)
assert entry.read_bytes()[:len(original)]==original
manifest=(root/'Plew.toml').read_text()
def local(match):
 path=(root/match[1]).resolve()
 return 'path = '+json.dumps(os.path.relpath(path,snapshot))
manifest=re.sub(r'path\s*=\s*"([^"]+)"',local,manifest)
(snapshot/'Plew.toml').write_text(manifest)
if (root/'Plew.lock').exists(): shutil.copy2(root/'Plew.lock',snapshot/'Plew.lock')
def sha(path): return hashlib.sha256(path.read_bytes()).hexdigest()
inputs={str(p.relative_to(root)):sha(p) for p in snapshot.rglob('*') if p.is_file()}
(out/'inputs.json').write_text(json.dumps(inputs,indent=2)+'\n')
def stage(name,command):
 print('[trace-phase] ready-closure-private:'+name,file=sys.stderr,flush=True)
 with (out/(name+'.stdout')).open('wb') as stdout,(out/(name+'.stderr')).open('wb') as stderr:
  # Preserve stage diagnostics and forward real compiler/LLVM progress to the
  # enclosing standard watchdog; do not replace it with a heartbeat.
  process=subprocess.Popen(list(map(str,command)),stdout=stdout,stderr=subprocess.PIPE)
  for line in process.stderr:
   stderr.write(line)
   if b'[trace-phase]' in line or b'[trace-command ' in line:
    sys.stderr.buffer.write(line)
    sys.stderr.buffer.flush()
  status=process.wait()
  if status: raise subprocess.CalledProcessError(status,command)
sys.path.insert(0,str(root/'scripts/support'))
import llvm_link
stage('compile',[compiler,'--trace-phases',entry])
shutil.copy2(out/'compile.stdout',out/'harness.ll')
stage('runtime',[compiler,'--runtime'])
shutil.copy2(out/'runtime.stdout',out/'runtime.c')
libdir=Path(config).parent.parent/'lib'
if not (libdir/'libLLVM.dylib').exists():
 libdir=Path(subprocess.check_output([config,'--libdir'],text=True).strip())
stage('link',[sys.executable,root/'scripts/support/llvm_link.py','--compiler-backend','--config',config,'--log-prefix',out/'link','--llvm',out/'harness.ll','--runtime',out/'runtime.c','--output',out/'harness','--','-L'+str(libdir),'-lLLVM'])
stage('run',[out/'harness'])
assert (out/'run.stdout').read_bytes()==b'ok\n'
assert not (out/'run.stderr').read_bytes()
assert all(sha(root/p)==value for p,value in inputs.items()), 'snapshot inputs changed during validation'
(out/'summary.json').write_text(json.dumps({'status':'passed','source_inputs':len(inputs),'backend_prefix_unchanged':True,'backend_prefix_sha256':hashlib.sha256(original).hexdigest(),'test_main_sha256':hashlib.sha256(test).hexdigest(),'compiler':str(compiler),'compiler_sha256':sha(compiler),'scope':'real private Closure/EnvironmentDrop admission and binding, malformed semantic correspondence, actual value/cell local allocations, leading environment lane and legacy override rejection'},indent=2)+'\n')
print('PASS private closure Ready admission/binding guards and exact source snapshot')
