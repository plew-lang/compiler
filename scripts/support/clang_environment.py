"""Make clang's implicit configuration independent of machine-local cfg files."""
import os
from pathlib import Path
import shlex
import subprocess
import sys


def settings(environment=None):
    environment = os.environ if environment is None else environment
    result = {'CLANG_NO_DEFAULT_CONFIG': '1'}
    sdk = environment.get('SDKROOT')
    if sys.platform == 'darwin' and not sdk:
        sdk = subprocess.check_output(['xcrun', '--sdk', 'macosx', '--show-sdk-path'], text=True).strip()
    if sdk:
        path = Path(sdk)
        if not path.is_absolute() or not path.is_dir():
            raise ValueError('SDKROOT must name an existing absolute SDK directory')
        result['SDKROOT'] = str(path.resolve())
    return result


def apply():
    selected = settings()
    os.environ.update(selected)
    return selected


if __name__ == '__main__':
    for key, value in settings().items():
        print('export ' + key + '=' + shlex.quote(value))
