#!/usr/bin/env python3
"""Manual common-preparation boundary probe; see this directory README."""
from pathlib import Path
import subprocess,sys,json,os
import argparse
parser=argparse.ArgumentParser(description="Verify semantic preparation without linking LLVM")
parser.add_argument('--compiler', type=Path, required=True)
parser.add_argument('--out', type=Path, required=True)
args=parser.parse_args()
c=Path(__file__).resolve().parents[3];out=args.out.resolve();out.mkdir(parents=True,exist_ok=False);carrier=args.compiler.absolute()
sys.path.insert(0,str(c/'scripts/support'));from clang_environment import apply
apply();watch=[sys.executable,'-B',str(c/'scripts/support/watch-command.py'),'--']
with (out/'compile.stderr').open('wb') as log:
 subprocess.run([sys.executable,'-B',str(c/'scripts/support/trace-command.py'),str(out/'compile.log'),'--',str(carrier),'--emit-object',str(out/'check.o'),'--trace-phases',str(Path(__file__).with_name('PreparedProgram.pw'))],cwd=c,stderr=log,check=True)
with (out/'runtime.c').open('wb') as f:subprocess.run([*watch,str(carrier),'--runtime'],stdout=f,check=True)
subprocess.run([*watch,'/usr/bin/clang','-O2',str(out/'check.o'),str(out/'runtime.c'),'-o',str(out/'check')],check=True)
(out/'std').symlink_to(c/'std',target_is_directory=True)
results=[]
for kind,name in [('run','cow_struct'),('run','async_match'),('run','closure_return_boundaries'),('reject','borrow_inout_argument'),('reject','receiver_read_inout_overlap'),('reject','receiver_read_inout_global')]:
 source=c/f'tests/fixtures/{kind}/{name}.pw'; expected=0 if kind=='run' else 1
 result=subprocess.run([*watch,str(out/'check'),str(source)],cwd=c,capture_output=True)
 assert result.returncode==expected,(name,result.stderr)
 if expected:
  reference=subprocess.run([*watch,str(carrier),str(source)],cwd=c,capture_output=True)
  assert result.stderr==reference.stderr,(name,result.stderr,reference.stderr)
 else:assert result.stdout==b'prepared\n',result.stdout
 results.append({'case':name,'exit':result.returncode});print('PASS',name,flush=True)
deps=subprocess.check_output(['/usr/bin/otool','-L',str(out/'check')],text=True)
assert 'LLVM' not in deps,deps
(out/'results.json').write_text(json.dumps({'status':'passed','cases':results,'dependencies':deps},indent=2))
