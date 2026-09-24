"""Resolve the actual source dependency closure for build/validation snapshots."""
from pathlib import Path
import re
import tomllib


def dependency_inputs(compiler, env, allow_missing=False):
    """Resolve the actual locked cache, not the adjacent Syntax checkout."""
    inputs = []
    pending = [compiler]
    seen = set()
    cache = Path(env.get('PLEW_CACHE', str(Path.home() / '.plew/cache')))
    while pending:
        directory = pending.pop().resolve()
        if directory in seen:
            continue
        seen.add(directory)
        manifest = directory / 'Plew.toml'
        if manifest.exists():
            values = tomllib.loads(manifest.read_text())
            def paths(value):
                if isinstance(value, dict):
                    if isinstance(value.get('path'), str):
                        yield (directory / value['path']).resolve()
                    for entry in value.values():
                        yield from paths(entry)
            for path in paths(values):
                if not path.is_dir():
                    raise ValueError(f'missing path dependency: {path}')
                inputs.append(path)
                pending.append(path)
        lock = directory / 'Plew.lock'
        if lock.exists():
            for package in tomllib.loads(lock.read_text()).get('package', []):
                if 'git' not in package:
                    continue
                safe = re.sub(r'[^A-Za-z0-9._-]', '_', package['git'])
                path = cache / 'src' / safe / package['commit']
                if not path.is_dir() and not allow_missing:
                    raise ValueError(f'locked dependency missing: {path}; run the resolver first')
                inputs.append(path)
                pending.append(path)
    return inputs


