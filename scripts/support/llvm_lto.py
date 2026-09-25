"""Darwin ThinLTO build settings, shared by LLVM and standalone packaging."""
from pathlib import Path
import subprocess


def settings(config, jobs):
    if jobs < 1:
        raise ValueError('ThinLTO jobs must be positive')
    def query(option):
        return Path(subprocess.check_output([config, option], text=True).strip())
    library = query('--libdir') / 'libLTO.dylib'
    archiver = query('--bindir') / 'llvm-libtool-darwin'
    for path in (library, archiver):
        if not path.is_file():
            raise ValueError(f'ThinLTO build tool is unavailable: {path}')
    if ',' in str(library):
        raise ValueError('Darwin linker options cannot encode a comma in the libLTO path')
    return {
        'library': str(library), 'archiver': str(archiver), 'jobs': jobs,
        'flags': ['-flto=thin', f'-Wl,-lto_library,{library}',
                  '-Wl,-mllvm,-O3', f'-Wl,-mllvm,-threads={jobs}',
                  '-Wl,-mllvm,-debug-pass=Executions'],
    }
