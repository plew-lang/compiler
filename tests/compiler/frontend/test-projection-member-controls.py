#!/usr/bin/env python3
"""Preserved projection namespaces and distinct missing-binding producers."""
from pathlib import Path
import argparse, hashlib, json, sys
ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'scripts/support'))
from compiler_failure_result import run_compiler
parser = argparse.ArgumentParser()
parser.add_argument('--carrier', required=True, type=Path)
parser.add_argument('--out', required=True, type=Path)
args = parser.parse_args()
carrier = args.carrier.resolve()
out = args.out.resolve()
out.mkdir(exist_ok=False)
positives = ['associated_binding_inherited_signature', 'assoc_type_projection_parameterized', 'assoc_type_projection_trait_args']
negatives = ['extern_signature_unrelated_conformance', 'extern_signature_wrong_trait_instance']
files = [ROOT/'tests/fixtures'/phase/(name+ext) for phase,names,exts in [('run',positives,['.pw','.out']), ('reject',negatives,['.pw'])] for name in names for ext in exts]
sha = lambda path: hashlib.sha256(path.read_bytes()).hexdigest()
inputs = {str(path):sha(path) for path in [carrier,Path(__file__),ROOT/'Plew.toml',ROOT/'Plew.lock',*files,*carrier.with_name('std').rglob('*.pw')]}
rows = []
for accepted,names,phase in [(True,positives,'run'),(False,negatives,'reject')]:
 for name in names:
  source = ROOT/'tests/fixtures'/phase/(name+'.pw')
  for mode,flags in [('check',['--check']),('aot',[]),('orc',['--run'])]:
   result = run_compiler([str(carrier),*flags,str(source)],capture_output=True,timeout=120,cwd=ROOT)
   passed = result.returncode == 0 if accepted else result.returncode == 1 and result.record()['failure_domain'] == 'unclassified' and b'associated-type projection names an associated type that is not bound by the selected conformance' in result.stderr
   if accepted and mode == 'orc':
    expected = source.with_suffix('.out').read_bytes()
    # Match the existing normal harness: .out.exact opts into trailing-newline equality.
    exact = source.with_suffix('.out.exact').exists()
    passed = passed and (result.stdout == expected if exact else result.stdout.rstrip(b'\n') == expected.rstrip(b'\n'))
   (out/(name+'-'+mode+'.stderr')).write_bytes(result.stderr)
   rows.append(dict(name=name,mode=mode,pass_=passed,**result.record()))
unchanged = all(sha(Path(path)) == value for path,value in inputs.items())
(out/'result.json').write_text(json.dumps(dict(inputs=inputs,inputs_unchanged=unchanged,cases=rows),indent=2)+'\n')
print(dict(cases=len(rows),passed=sum(row['pass_'] for row in rows),inputs_unchanged=unchanged))
sys.exit(not unchanged or not all(row['pass_'] for row in rows))
