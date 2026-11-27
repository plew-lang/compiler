#!/usr/bin/env python3
"""Adopted inherited associated-member selection: end-to-end RED/controls."""
from pathlib import Path
import argparse, hashlib, json, sys
ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT/'scripts/support'))
from compiler_failure_result import run_compiler
parser=argparse.ArgumentParser()
parser.add_argument('--carrier',required=True,type=Path)
parser.add_argument('--out',required=True,type=Path)
args=parser.parse_args()
carrier=args.carrier.resolve();out=args.out.resolve();out.mkdir(exist_ok=False)
base='trait Parent { type Output }\ntrait Child: Parent {}\nstruct P {}\nimpl P as Parent { type Output = I64 }\nimpl P as Child {}\n'
param='trait Parent[A] { type Output }\ntrait Child[B]: Parent[Array[B]] {}\nstruct P {}\nimpl P as Parent[Array[I64]] { type Output = I64 }\nimpl P as Child[I64] {}\n'
cases={}
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
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
inputs={str(p):sha(p) for p in [carrier,Path(__file__),ROOT/'Plew.toml',ROOT/'Plew.lock',*carrier.with_name('std').rglob('*.pw')]}
rows=[]
for name,(accepted,body) in cases.items():
 directory=out/name;directory.mkdir();source=directory/'Main.pw';source.write_text('use @Std/Io only { print }\n'+body);inputs[str(source)]=sha(source)
 for mode,flags in [('check',['--check']),('aot',[]),('orc',['--run'])]:
  result=run_compiler([str(carrier),*flags,str(source)],capture_output=True,timeout=120,cwd=ROOT)
  (directory/(mode+'.stdout')).write_bytes(result.stdout);(directory/(mode+'.stderr')).write_bytes(result.stderr)
  passed=(result.returncode==0 and (mode!='orc' or result.stdout==b'7\n')) if accepted else (result.returncode==1 and result.record()['failure_domain']=='source' and errors.get(name,b'ambiguous') in result.stderr)
  rows.append(dict(case=name,mode=mode,expected_accept=accepted,pass_=passed,**result.record(),stderr=result.stderr.decode()))
unchanged=all(sha(Path(p))==v for p,v in inputs.items())
(out/'result.json').write_text(json.dumps(dict(inputs=inputs,inputs_unchanged=unchanged,cases=rows),indent=2)+'\n')
print(dict(cases=len(rows),passed=sum(x['pass_'] for x in rows),inputs_unchanged=unchanged,failed_cases=sorted({x['case'] for x in rows if not x['pass_']})))
sys.exit(not unchanged or not all(x['pass_'] for x in rows))
