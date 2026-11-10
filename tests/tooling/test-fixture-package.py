"""Scratch packages retain dependency identity after moving their manifest."""
from pathlib import Path
import subprocess
import sys
import tempfile
import tomllib

helper = Path(__file__).resolve().parents[2] / 'scripts/support/fixture_package.py'
with tempfile.TemporaryDirectory() as directory:
    root = Path(directory)
    source = root / 'compiler'
    destination = source / 'tmp/gen_case'
    dependency = root / 'syntax'
    source.mkdir()
    dependency.mkdir()
    destination.mkdir(parents=True)
    lock = b'[[package]]\nname = "Syntax"\ncommit = "fixed"\n'
    (source / 'Plew.lock').write_bytes(lock)
    for manifest in [
        'name = "test"\n[dependencies]\nSyntax = { path = "../syntax" }\n',
        "name = 'test'\n[dependencies.Syntax]\npath = '../syntax'\n",
        'name = "test"\n[dependencies]\nSyntax = { git = "https://example.invalid/syntax", rev = "fixed" }\n',
    ]:
        (source / 'Plew.toml').write_text(manifest)
        subprocess.run([sys.executable, '-B', str(helper), str(source), str(destination)], check=True)
        before = tomllib.loads(manifest)
        after = tomllib.loads((destination / 'Plew.toml').read_text())
        spec = after['dependencies']['Syntax']
        if 'path' in spec:
            assert (destination / spec['path']).resolve() == dependency.resolve()
            assert spec['path'] == '../../../syntax'
        else:
            assert (destination / 'Plew.toml').read_text() == manifest
        assert (destination / 'Plew.lock').read_bytes() == lock
        assert (source / 'Plew.toml').read_text() == manifest
    (source / 'Plew.lock').unlink()
    subprocess.run([sys.executable, '-B', str(helper), str(source), str(destination)], check=True)
    assert not (destination / 'Plew.lock').exists(), 'stale lock retained'
    # Legal TOML outside this controlled copier's spelling must fail before
    # publishing either file, rather than silently changing dependency identity.
    (source / 'Plew.toml').write_text('[dependencies.Syntax]\n"path" = "../syntax"\n')
    (destination / 'Plew.toml').write_bytes(b'manifest sentinel')
    (destination / 'Plew.lock').write_bytes(b'lock sentinel')
    result = subprocess.run([sys.executable, '-B', str(helper), str(source), str(destination)], capture_output=True)
    assert result.returncode != 0 and b'unsupported fixture dependency spelling' in result.stderr
    assert (destination / 'Plew.toml').read_bytes() == b'manifest sentinel'
    assert (destination / 'Plew.lock').read_bytes() == b'lock sentinel'
print('PASS relocated fixture dependency paths and exact pins/locks')
