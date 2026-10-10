"""Resolve the actual source dependency closure for build/validation snapshots."""
from pathlib import Path
import re
import tomllib


def dependency_inputs(compiler, env, allow_missing=False):
    """Resolve the actual locked cache, not the adjacent Syntax checkout."""
    inputs = []
    pending = [compiler]
    seen = set()
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
                path = locked_package_source(package, env)
                if not path.is_dir() and not allow_missing:
                    raise ValueError(f'locked dependency missing: {path}; run the resolver first')
                inputs.append(path)
                pending.append(path)
    return inputs



def locked_git_source(compiler, env, git):
    """Return the exact locked source root for one git dependency."""
    lock = tomllib.loads((compiler / 'Plew.lock').read_text())
    packages = [p for p in lock.get('package', []) if p.get('git') == git]
    if len(packages) != 1:
        raise ValueError(f'expected one locked dependency: {git}')
    path = locked_package_source(packages[0], env)
    if not path.is_dir():
        raise ValueError(f'locked dependency missing: {path}; run the resolver first')
    return path


def locked_package_source(package, env):
    cache = Path(env.get('PLEW_CACHE', str(Path.home() / '.plew/cache')))
    safe = re.sub(r'[^A-Za-z0-9._-]', '_', package['git'])
    path = cache / 'src' / safe / package['commit']
    return path


if __name__ == '__main__':
    import argparse
    import os
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--git', required=True)
    args = parser.parse_args()
    print(locked_git_source(Path.cwd(), os.environ, args.git))
