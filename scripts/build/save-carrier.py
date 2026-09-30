#!/usr/bin/env python3
"""Save a development compiler snapshot without cluttering the repository root."""
import argparse
import os
from pathlib import Path
import re
import shutil

ROOT = Path(__file__).resolve().parents[2]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('name', help='snapshot label, e.g. candidate or before-change')
    parser.add_argument('--source', type=Path, default=ROOT / 'bin/plewc')
    args = parser.parse_args()
    if not re.fullmatch(r'[A-Za-z0-9][A-Za-z0-9_-]*', args.name):
        parser.error('name must contain only letters, digits, underscores and hyphens')
    if not args.source.is_file() or not os.access(args.source, os.X_OK):
        parser.error('source must be an executable file')
    directory = ROOT / 'bin'
    directory.mkdir(parents=True, exist_ok=True)
    std = directory / 'std'
    if not std.exists() and not std.is_symlink():
        std.symlink_to('../std', target_is_directory=True)
    if std.resolve() != (ROOT / 'std').resolve():
        parser.error('snapshot directory has an unexpected std entry')
    target = directory / ('plewc-' + args.name)
    # Exclusive creation also rejects dangling symlinks and accidental overwrite.
    with target.open('xb') as output, args.source.open('rb') as source:
        shutil.copyfileobj(source, output)
    shutil.copystat(args.source, target)
    print(target)


if __name__ == '__main__':
    main()
