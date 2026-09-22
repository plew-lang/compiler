#!/usr/bin/env python3
"""Focused normal and genuine LLVM ASan regression checks; manual diagnostic."""
from pathlib import Path
import argparse, json, os, subprocess, sys, hashlib
ROOT=Path(__file__).resolve().parents[3]
sys.path.insert(0,str(ROOT/'scripts/support'))
import clang_environment

def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--out',type=Path,required=True);p.add_argument('--compiler',type=Path,default=ROOT/'plewc');a=p.parse_args()
 out=a.out.resolve();out.mkdir(parents=True,exist_ok=False);compiler=a.compiler.resolve();clang_environment.apply();env=dict(os.environ,ASAN_OPTIONS='detect_leaks=1:abort_on_error=0:exitcode=86',PYTHONDONTWRITEBYTECODE='1');rows=[]
 def run(name,args):
  with (out/(name+'.out')).open('wb') as o,(out/(name+'.err')).open('wb') as e:r=subprocess.run([sys.executable,ROOT/'scripts/support/watch-command.py','--',*args],cwd=ROOT,env=env,stdout=o,stderr=e)
  rows.append({'step':name,'exit':r.returncode});return r.returncode
 def required(name,args):
  if run(name,args):raise RuntimeError(f'{name} failed; see {out}')
 cases=['ref_parameter_receiver_lifetime','ref_arc_deinit','ref_reassign_arc','ref_arrow_field_bind_arc','ref_arrow_method','ref_arrow_chain','closure_write_capture','mid_deref_projection_schema']
 inputs=[compiler,Path(__file__),ROOT/'tests/fixtures/run/ref_parameter_receiver_lifetime.pw',ROOT/'tests/fixtures/run/ref_parameter_receiver_lifetime.out'];inputs += [ROOT/'tests/fixtures/run'/(case+suffix) for case in cases for suffix in ['.pw','.out']]
 inputs += sorted((ROOT/'std').rglob('*.pw')) + sorted((ROOT/'scripts/support').glob('*.py'))
 hashes={str(x):hashlib.sha256(x.read_bytes()).hexdigest() for x in inputs}
 required('runtime',[compiler,'--runtime'])
 for case in cases:
  fixture=ROOT/'tests/fixtures/run'/(case+'.pw');expected=fixture.with_suffix('.out').read_text().strip()
  for sanitized in [False,True]:
   name=case+('-asan' if sanitized else '-normal');clang='/opt/homebrew/opt/llvm@22/bin/clang' if sanitized else '/opt/homebrew/opt/llvm/bin/clang'
   required(name+'-compile',[compiler,*(['--asan'] if sanitized else ['--trace-phases']),fixture])
   ll=out/(name+'-compile.out')
   if sanitized:
    required(name+'-instrument',['/opt/homebrew/opt/llvm@22/bin/opt','-passes=asan',ll,'-o',out/(name+'.bc')]);ll=out/(name+'.bc')
   required(name+'-link',[clang,'-w',*(['-fsanitize=address'] if sanitized else ['-O2']),'-x','ir',ll,'-x','c',out/'runtime.out','-o',out/name])
   status=run(name+'-run',[out/name]);actual=(out/(name+'-run.out')).read_text().strip()
   if status or actual!=expected:raise RuntimeError(f'{name}: exit={status}, stdout={actual!r}, expected={expected!r}; see {out}')
  print(f'passed normal+ASan {case}',flush=True)
 assert all(hashlib.sha256(Path(k).read_bytes()).hexdigest()==v for k,v in hashes.items())
 (out/'results.json').write_text(json.dumps({'inputs':hashes,'inputs_unchanged':True,'cases':cases,'steps':rows},indent=2)+'\n')
if __name__=='__main__':main()
