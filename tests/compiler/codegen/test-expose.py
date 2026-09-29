#!/usr/bin/env python3
"""Named C entries retain ordinary Plew bodies and external-only roots."""
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile
import shutil

root = Path(__file__).resolve().parents[3]
compiler = Path(os.environ.get('PLEWC', root / 'plewc')).absolute()
sys.path.insert(0, str(root / 'scripts/support'))
import llvm_link
config = os.environ.get("LLVM_CONFIG") or shutil.which("llvm-config") or "/opt/homebrew/opt/llvm/bin/llvm-config"

def run(*args):
    return subprocess.run(list(map(str, args)), check=True, capture_output=True, timeout=55)

fixture = root / 'tests/compiler/codegen/Expose.pw'
raw = run(compiler, '--require-mid', fixture).stdout
for name in ['exposedAdd', 'exposedFloat', 'exposedEmpty', 'exposedWrite', 'exposedSignedByte', 'exposedUnsignedShort', 'exposedBoolean']:
    assert re.search(rb'^define (?!internal)[^\n]*@' + name.encode() + rb'\(', raw, re.M), name
# Use the selected target's C compiler as an ABI reference: successful low-bit
# roundtrips alone do not prove the upper-register extension contract.
c_reference = run(llvm_link.selected_clang(config), '-S', '-emit-llvm', '-O0', fixture.with_suffix('.c'), '-o', '-').stdout
for imported, exposed in [('cSignedByte', 'exposedSignedByte'), ('cUnsignedShort', 'exposedUnsignedShort'), ('cBoolean', 'exposedBoolean')]:
    reference = re.search(rb'^define[^\n]*@' + imported.encode() + rb'\([^\n]*', c_reference, re.M)
    assert reference, imported
    expected = re.findall(rb'\b(?:signext|zeroext)\b', reference.group())
    for marker, name in [(b'define', exposed), (b'declare', imported), (b'call', imported)]:
        signature = re.search(rb'[^\n]*\b' + marker + rb'[^\n]*@' + name.encode() + rb'\([^\n]*', raw)
        assert signature, (marker, name)
        assert re.findall(rb'\b(?:signext|zeroext)\b', signature.group()) == expected, signature.group()
with tempfile.TemporaryDirectory(prefix='plew-expose-') as folder:
    directory = Path(folder)
    source = directory / 'source.ll'
    source.write_bytes(raw)
    runtime = directory / 'runtime.c'
    runtime.write_bytes(run(compiler, '--runtime').stdout)
    for level in ['-O0', '-O2']:
        executable = directory / ('test' + level)
        run(llvm_link.selected_clang(config), level, source, runtime, fixture.with_suffix('.c'), '-o', executable)
        assert run(executable).stdout == b''
for name in ['expose_labels', 'expose_duplicate', 'expose_generic', 'expose_method', 'expose_associated', 'expose_main']:
    source = root / 'tests/fixtures/reject' / (name + '.pw')
    result = subprocess.run([str(compiler), str(source)], capture_output=True, timeout=55)
    assert result.returncode != 0, name
    assert source.with_suffix('.err').read_bytes().strip() in result.stderr, result.stderr
print('PASS expose: C and Plew calls, external-only roots, integer/float/void/inout ABI, labels and name collisions')
