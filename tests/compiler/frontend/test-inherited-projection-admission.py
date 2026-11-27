#!/usr/bin/env python3
"""Associated-member check/JIT controls; --native-backend also links and runs AOT."""
from pathlib import Path
import argparse, hashlib, json, sys, subprocess
ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT/'scripts/support'))
from compiler_failure_result import run_compiler
parser=argparse.ArgumentParser()
parser.add_argument('--carrier',required=True,type=Path)
parser.add_argument('--out',required=True,type=Path)
parser.add_argument('--native-backend',type=Path,help='fixed backend archive for actual native AOT execution')
args=parser.parse_args()
carrier=args.carrier.resolve();out=args.out.resolve();out.mkdir(exist_ok=False)
base='trait Parent { type Output }\ntrait Child: Parent {}\nstruct P {}\nimpl P as Parent { type Output = I64 }\nimpl P as Child {}\n'
param='trait Parent[A] { type Output }\ntrait Child[B]: Parent[Array[B]] {}\nstruct P {}\nimpl P as Parent[Array[I64]] { type Output = I64 }\nimpl P as Child[I64] {}\n'
cases={"Direct": (True, 'fn main() {}\n')}
for name,projection in [('Parent','T#Parent.Output'),('Child','T#Child.Output'),('Short','T.Output')]:
 cases[name]=(True,base+'fn project[T](value: T, item: '+projection+') -> '+projection+' where T: Child { return item }\nfn main() { print(project(value: <P />, item: 7I64)) }\n')
for name,projection in [('ParentArguments','T#Parent[Array[I64]].Output'),('ChildArguments','T#Child[I64].Output'),('ShortArguments','T.Output')]:
 cases[name]=(True,param+'fn project[T](value: T, item: '+projection+') -> '+projection+' where T: Child[I64] { return item }\nfn main() { print(project(value: <P />, item: 7I64)) }\n')
ambiguous='trait First { type Output }\ntrait Second { type Output }\ntrait Both: First + Second {}\n'
for name,projection in [('AmbiguousChild','T#Both.Output'),('AmbiguousShort','T.Output')]:
 cases[name]=(False,ambiguous+'fn project[T](value: T, item: '+projection+') where T: Both {}\nfn main() {}\n')
cases['EqualOutputs']=(False,ambiguous+'struct P {}\nimpl P as First { type Output = I64 }\nimpl P as Second { type Output = I64 }\nimpl P as Both {}\nfn project(item: P#Both.Output) {}\nfn main() {}\n')
cases['AmbiguousDirectRoots']=(False,'trait First { type Output }\ntrait Second { type Output }\nfn project[T](value: T, item: T.Output) where T: First + Second {}\nfn main() {}\n')
cases['NoChildProof']=(False,'trait Parent { type Output }\ntrait Child: Parent {}\nfn project[T](value: T, item: T#Child.Output) where T: Parent {}\nfn main() {}\n')
errors={'NoChildProof': b'requires a conformance'}
arity='trait Parent[A, B] { type Output }\ntrait Child[C]: Parent[C, Array[C]] {}\nstruct P {}\nimpl P as Parent[I64, Array[I64]] { type Output = I64 }\nimpl P as Child[I64] {}\n'
for name,projection in [('ParentArity','T#Parent[I64, Array[I64]].Output'),('ChildArity','T#Child[I64].Output')]:
 cases[name]=(True,arity+'fn project[T](value: T, item: '+projection+') -> '+projection+' where T: Child[I64] { return item }\nfn main() { print(project(value: <P />, item: 7I64)) }\n')
fixtures={}
for name in ['Closure','Provided','Unused']:
 fixture=ROOT/'tests/compiler/frontend/fixtures/ProjectionMembers'/('Executable'+name+'.pw')
 fixtures[str(fixture)]=fixture
 cases[name]=(True,fixture.read_text().split('\n',1)[1])
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
inputs={str(p):sha(p) for p in [carrier,Path(__file__),ROOT/'Plew.toml',ROOT/'Plew.lock',*carrier.with_name('std').rglob('*.pw')]}
inputs.update({path:sha(p) for path,p in fixtures.items()})
backend=args.native_backend.resolve() if args.native_backend else None
runtime_object=out/'runtime.o'
if backend:
 import native_build,clang_environment
 clang_environment.apply()
 clang=Path('/opt/homebrew/opt/llvm@22/bin/clang')
 for p in [backend,clang,ROOT/'scripts/support/native_build.py',ROOT/'scripts/support/clang_environment.py',ROOT/'scripts/support/compiler_failure_result.py']:
  inputs[str(p)]=sha(p)
 runtime=run_compiler([str(carrier),'--runtime'],capture_output=True,timeout=120,cwd=ROOT)
 (out/'runtime.c').write_bytes(runtime.stdout);(out/'runtime.stderr').write_bytes(runtime.stderr)
 if runtime.returncode:raise RuntimeError('fixed carrier runtime generation failed')
 with (out/'runtime-clang.stderr').open('wb') as diagnostics:
  built=native_build.run([clang,'-O0','-w','-c',out/'runtime.c','-o',runtime_object],clang=True,trace_log=out/'runtime-clang.trace',stdout=subprocess.DEVNULL,stderr=diagnostics)
 if built.returncode:raise RuntimeError('runtime native compilation failed')
rows=[]
for name,(accepted,body) in cases.items():
 expected_output=b'' if name=='Direct' else b'7\n'
 directory=out/name;directory.mkdir();source=directory/'Main.pw';source.write_text('use @Std/Io only { print }\n'+body);inputs[str(source)]=sha(source)
 for mode,flags in [('check',['--check']),('aot',[]),('orc',['--run'])]:
  result=run_compiler([str(carrier),*flags,str(source)],capture_output=True,timeout=120,cwd=ROOT)
  (directory/(mode+'.stdout')).write_bytes(result.stdout);(directory/(mode+'.stderr')).write_bytes(result.stderr)
  passed=(result.returncode==0 and (mode!='orc' or result.stdout==expected_output)) if accepted else (result.returncode==1 and result.record()['failure_domain']=='source' and errors.get(name,b'ambiguous') in result.stderr)
  native={}
  if backend and mode=='aot' and accepted and result.returncode==0:
   executable=directory/'program'
   with (directory/'aot-link.stderr').open('wb') as diagnostics:
    linked=native_build.run([clang,'-O0','-w','-x','ir',directory/'aot.stdout','-x','none',runtime_object,backend,'-L/opt/homebrew/opt/llvm@22/lib','-lLLVM','-lc++','-Wl,-export_dynamic','-o',executable],clang=True,trace_log=directory/'aot-link.trace',stdout=subprocess.DEVNULL,stderr=diagnostics)
   native['link_status']=linked.returncode;passed=linked.returncode==0
   if passed:
    try:
     executed=subprocess.run([executable],capture_output=True,timeout=60,cwd=ROOT)
     (directory/'native.stdout').write_bytes(executed.stdout);(directory/'native.stderr').write_bytes(executed.stderr)
     native.update(status=executed.returncode,stdout=executed.stdout.decode(),stderr=executed.stderr.decode());passed=executed.returncode==0 and executed.stdout==expected_output and executed.stderr==b''
    except subprocess.TimeoutExpired:
     native['timeout']=True;passed=False
  rows.append(dict(case=name,mode=mode,expected_accept=accepted,expected_stdout=expected_output.decode(),pass_=passed,aot_native=native,**result.record(),stderr=result.stderr.decode()))
unchanged=all(sha(Path(p))==v for p,v in inputs.items())
(out/'result.json').write_text(json.dumps(dict(inputs=inputs,inputs_unchanged=unchanged,aot_execution=bool(backend),cases=rows),indent=2)+'\n')
print(dict(cases=len(rows),passed=sum(x['pass_'] for x in rows),inputs_unchanged=unchanged,failed_cases=sorted({x['case'] for x in rows if not x['pass_']})))
sys.exit(not unchanged or not all(x['pass_'] for x in rows))
