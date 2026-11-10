"""Copy package metadata to scratch without changing dependency identity."""
import copy
import json
import os
from pathlib import Path
import re
import shutil
import sys
import tomllib


def copy_package(source, destination):
    source, destination = Path(source).resolve(), Path(destination).resolve()
    text = (source / 'Plew.toml').read_text()
    expected = copy.deepcopy(tomllib.loads(text))
    paths = []
    for dependency in expected.get('dependencies', {}).values():
        if isinstance(dependency, dict) and 'path' in dependency:
            path = os.path.relpath((source / dependency['path']).resolve(), destination)
            paths.append(path)
            dependency['path'] = path
    if paths:
        def relocate(match):
            value = tomllib.loads('path = ' + match['value'])['path']
            path = os.path.relpath((source / value).resolve(), destination)
            return match['prefix'] + json.dumps(path, ensure_ascii=False)
        text = re.sub(r'''(?P<prefix>\bpath\s*=\s*)(?P<value>"(?:[^"\\\n]|\\.)*"|'[^'\n]*')''', relocate, text)
        if tomllib.loads(text) != expected:
            raise ValueError('unsupported fixture dependency spelling; metadata not copied')
    destination.mkdir(parents=True, exist_ok=True)
    (destination / 'Plew.toml').write_text(text)
    lock = destination / 'Plew.lock'
    if (source / 'Plew.lock').exists():
        shutil.copy2(source / 'Plew.lock', lock)
    else:
        lock.unlink(missing_ok=True)


if __name__ == '__main__':
    copy_package(*sys.argv[1:])
