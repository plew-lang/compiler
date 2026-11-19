#!/usr/bin/env python3
"""The ASan B worker must execute precise capture-limit controls and fail closed."""
from pathlib import Path
import json
import os
import shutil
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
PROFILE = Path('tests/compiler/frontend/test-closure-capture-limits.py')
assert str(PROFILE) in (ROOT / 'tests/harness/test.sh').read_text()
assert 'require-source-rejection' in (ROOT / 'tests/harness/case-phase.sh').read_text()

FAKE = r'''#!/usr/bin/env python3
import os,sys
from pathlib import Path
name=Path(sys.argv[-1]).stem
mode='check' if '--check' in sys.argv else ('orc' if '--run' in sys.argv else 'aot')
limits={'GenericStruct','FunctionValue','UnusedGenericStruct','UnusedFunctionValue','GenericSubstitution','FunctionSubstitution'}
if name in limits:
    if (name.startswith('Unused') and mode=='orc') or (name.endswith('Substitution') and mode=='check'):
        sys.exit(0)
    kind='generic struct' if 'Generic' in name else 'function-typed'
    message='closure capture of '+kind+' values is not implemented'
    domain=os.environ.get('CAPTURE_TEST_DOMAIN','limit')
    if os.environ.get('CAPTURE_TEST_SANITIZER'):
        message+='\nERROR: AddressSanitizer: controlled failure'
elif 'reject' in sys.argv[-1]:
    domain='source';message='controlled source rejection'
else:
    sys.exit(0)
fd=os.environ.get('_PLEW_COMPILER_FAILURE_FD')
if fd:
    record='plew.compiler.failure.v1\n'+os.environ['_PLEW_COMPILER_FAILURE_ID']+'\n'+domain+'\n'
    os.write(int(fd),record.encode())
sys.stderr.write('plewc: error: '+message+'\n')
sys.exit(1)
'''

for label,domain,sanitizer,expected in [('limit','limit',False,0),('source','source',False,1),('sanitizer','limit',True,1)]:
    with tempfile.TemporaryDirectory(prefix='capture-limit-registration-') as folder:
        root=Path(folder)
        for path in ['tests/harness/asan-compile-corpus.sh',str(PROFILE)]:
            target=root/path;target.parent.mkdir(parents=True,exist_ok=True);shutil.copy(ROOT/path,target)
        shutil.copytree(ROOT/'scripts/support',root/'scripts/support',ignore=shutil.ignore_patterns('__pycache__','vendor'))
        target=root/'tests/compiler/frontend/fixtures/ClosureCaptureLimits'
        shutil.copytree(ROOT/'tests/compiler/frontend/fixtures/ClosureCaptureLimits',target)
        for phase in ['run','reject','panic']:
            path=root/'tests/fixtures'/phase/'Control.pw';path.parent.mkdir(parents=True);path.write_text('fn main() {}\n')
        (root/'src').mkdir();(root/'src/_.pw').write_text('fn main() {}\n')
        (root/'Plew.toml').write_text('');(root/'Plew.lock').write_text('')
        compiler=root/'plewc_asan';compiler.write_text(FAKE);compiler.chmod(0o755)
        logs=root/'logs';logs.mkdir()
        env=os.environ|{'PLEW_TEST_JOBS':'1','TMP':str(logs),'PLEWC':str(root/'wrong-compiler'),
                        'CAPTURE_TEST_DOMAIN':domain,'CAPTURE_TEST_SANITIZER':'1' if sanitizer else ''}
        result=subprocess.run(['sh','tests/harness/asan-compile-corpus.sh'],cwd=root,env=env,capture_output=True,timeout=50)
        assert result.returncode==expected,(label,result.stdout,result.stderr)
        assert b'clean (3 files)' in result.stdout,(label,result.stdout)
        receipt=json.loads((logs/'capture-limits/result.json').read_text())
        assert receipt['compiler']==str(compiler.resolve()) and len(receipt['cases'])==18
        assert len(receipt['errors'])==(0 if expected==0 else 14),(label,receipt['errors'])
        if expected==0:
            assert b'PASS closure-capture-limits' in result.stdout
        else:
            assert b'FAIL closure-capture-limits' in result.stdout
print('PASS capture limit registration: real B worker selection, wrong Source and sanitizer failures')
