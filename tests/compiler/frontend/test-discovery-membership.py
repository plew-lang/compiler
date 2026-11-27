#!/usr/bin/env python3
"""Manual real-CLI membership controls; no fixture or canonical carrier mutation."""
from pathlib import Path
import argparse,hashlib,json,sys
ROOT=Path(__file__).resolve().parents[3]
sys.path.insert(0,str(ROOT/'scripts/support'))
from compiler_failure_result import run_compiler
parser=argparse.ArgumentParser();parser.add_argument('--carrier',type=Path,required=True);parser.add_argument('--out',type=Path,required=True);args=parser.parse_args()
carrier=args.carrier.resolve();out=args.out.resolve();out.mkdir(exist_ok=False)
owner='use @Std/Core only { Eq }\n@[Eq]\nstruct Item {}\n'
cases={
 'ExplicitTwice':(False,{'Main.pw':'part ./Shared\npart ./Shared\nfn main() {}\n','Shared.pw':''}),
 'ExplicitAndAuto':(False,{'Main.pw':'use @Std/Core only { Eq }\npart ./Main.gen\n@[Eq]\nstruct Item {}\nfn main() {}\n','Main.gen.pw':''}),
 'OwnerFirst':(False,{'Main.pw':'use ./Owner\nuse ./Consumer\nfn main() {}\n','Owner.pw':'part ./Shared\n','Consumer.pw':'use ./Shared\n','Shared.pw':''}),
 'ConsumerFirst':(False,{'Main.pw':'use ./Consumer\nuse ./Owner\nfn main() {}\n','Owner.pw':'part ./Shared\n','Consumer.pw':'use ./Shared\n','Shared.pw':''}),
 'AutoTargetsRoot':(False,{'Main.pw':'use ./Owner.gen\nuse ./Owner\nfn main() {}\n','Owner.pw':owner,'Owner.gen.pw':''}),
 'AutoTargetsOtherPart':(False,{'Main.pw':'use ./Other\nuse ./Owner\nfn main() {}\n','Other.pw':'part ./Owner.gen\n','Owner.pw':owner,'Owner.gen.pw':''}),
 'SameModuleDiamond':(False,{'Main.pw':'part ./A\npart ./B\nfn main() {}\n','A.pw':'part ./Shared\n','B.pw':'part ./Shared\n','Shared.pw':''}),
 'DifferentModuleDiamond':(False,{'Main.pw':'use ./A\nuse ./B\nfn main() {}\n','A.pw':'part ./Shared\n','B.pw':'part ./Shared\n','Shared.pw':''}),
 'PartCycle':(False,{'Main.pw':'part ./A\nfn main() {}\n','A.pw':'part ./Main\n'}),
 'RepeatedRootUse':(True,{'Main.pw':'use ./Owner\nuse ./Other\nfn main() {}\n','Owner.pw':'','Other.pw':'use ./Owner\n'}),
 'MultipleAnnotations':(True,{'Main.pw':'use @Std/Core only { Eq }\n@[Eq]\nstruct First {}\n@[Eq]\nstruct Second {}\nfn main() {}\n','Main.gen.pw':''}),
 'NestedPart':(True,{'Main.pw':'part ./A\nfn main() {}\n','A.pw':'part ./B\n','B.pw':''}),
}
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
inputs={str(p):sha(p) for p in [carrier,Path(__file__),ROOT/'Plew.toml',ROOT/'Plew.lock',*carrier.with_name('std').rglob('*.pw')]};rows=[]
for name,(accepted,files) in cases.items():
 directory=out/name;directory.mkdir()
 for filename,text in files.items():
  p=directory/filename;p.write_text(text);inputs[str(p)]=sha(p)
 for mode,flags in [('check',['--check']),('aot',[]),('orc',['--run'])]:
  result=run_compiler([str(carrier),*flags,str(directory/'Main.pw')],capture_output=True,timeout=60,cwd=ROOT)
  (directory/(mode+'.stdout')).write_bytes(result.stdout);(directory/(mode+'.stderr')).write_bytes(result.stderr)
  passed=(result.returncode==0 and (mode!='orc' or result.stdout==b'')) if accepted else (result.returncode==1 and result.record()['failure_domain']=='source' and b'already in the module graph' in result.stderr)
  rows.append({'case':name,'mode':mode,'expected_accept':accepted,'pass':passed,**result.record(),'stderr':result.stderr.decode()})
unchanged=all(sha(Path(p))==v for p,v in inputs.items());record={'cases':rows,'inputs':inputs,'inputs_unchanged':unchanged};(out/'result.json').write_text(json.dumps(record,indent=2)+'\n')
print({'cases':len(rows),'pass':sum(x['pass'] for x in rows),'fail':sum(not x['pass'] for x in rows),'inputs_unchanged':unchanged,'failed_cases':sorted({x['case'] for x in rows if not x['pass']})})
if not unchanged or not all(x['pass'] for x in rows):sys.exit(1)
