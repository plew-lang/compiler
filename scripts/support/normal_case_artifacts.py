"""Own one normal case's scratch and publish its result before retirement."""
import hashlib
import json
import os
from pathlib import Path
import shutil
import stat
import sys
import tempfile


def publish(path, record):
    temporary = None
    try:
        with tempfile.NamedTemporaryFile(mode='w', dir=path.parent, prefix=path.name + '.',
                                         suffix='.tmp', delete=False) as stream:
            temporary = Path(stream.name)
            json.dump(record, stream, sort_keys=True)
            stream.write('\n')
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temporary, path)
        descriptor = os.open(path.parent, os.O_RDONLY)
        try:
            os.fsync(descriptor)
        finally:
            os.close(descriptor)
    finally:
        if temporary is not None:
            temporary.unlink(missing_ok=True)


def begin(parent, phase, source):
    parent = Path(parent).absolute()
    parent.mkdir(parents=True, exist_ok=True)
    directory = Path(tempfile.mkdtemp(prefix=phase + '-', dir=parent))
    identity = directory.stat()
    label = source.parent.name if phase in ('part', 'partreject') else source.stem
    if phase != 'run':
        label = phase + '/' + label
    record = dict(schema='plew-normal-case-v1', phase=phase, case=label,
                  source=str(source.absolute()), compiler=os.environ.get('PLEWC'),
                  source_sha256=hashlib.sha256(source.read_bytes()).hexdigest() if source.is_file() else None,
                  directory=str(directory), identity=[identity.st_dev, identity.st_ino],
                  status='pending', result=None, retired=False)
    publish(Path(str(directory) + '.json'), record)
    return directory


def finish(directory, result):
    directory = Path(directory).absolute()
    receipt = Path(str(directory) + '.json')
    record = json.loads(receipt.read_text())
    identity = directory.lstat()
    if (record.get('schema') != 'plew-normal-case-v1' or record.get('directory') != str(directory)
            or record.get('identity') != [identity.st_dev, identity.st_ino]
            or not stat.S_ISDIR(identity.st_mode) or record.get('status') != 'pending'):
        raise ValueError('normal case scratch ownership changed')
    artifacts = []
    for root, dirs, files in os.walk(directory, followlinks=False):
        for name in files:
            path = Path(root) / name
            value = path.lstat()
            if stat.S_ISREG(value.st_mode):
                artifacts.append(dict(path=str(path.relative_to(directory)), bytes=value.st_size,
                                      allocated_bytes=value.st_blocks * 512))
    passed = result == 'PASS ' + record['case']
    record.update(status='pass' if passed else 'fail', result=result, artifacts=artifacts,
                  artifact_bytes=sum(x['bytes'] for x in artifacts),
                  allocated_bytes=sum(x['allocated_bytes'] for x in artifacts))
    # This fsynced receipt is outside the payload. Never retire first and rely
    # on a later stdout line or a successful process exit to preserve the result.
    publish(receipt, record)
    if passed:
        shutil.rmtree(directory)
        record['retired'] = True
        publish(receipt, record)
    else:
        print(f'plewc: retained case artifacts: {directory}', file=sys.stderr)


if __name__ == '__main__':
    try:
        if len(sys.argv) == 4 and sys.argv[1] == 'begin':
            parent = os.environ.get('_PLEW_NORMAL_CASE_ROOT') or Path(__file__).resolve().parents[2] / 'tmp/normal-cases'
            print(begin(parent, sys.argv[2], Path(sys.argv[3])))
        elif len(sys.argv) == 4 and sys.argv[1] == 'finish':
            finish(Path(sys.argv[2]), sys.argv[3])
        else:
            raise ValueError('usage: normal_case_artifacts.py begin PHASE SOURCE | finish DIRECTORY RESULT')
    except (OSError, ValueError, KeyError) as error:
        print(f'plewc: normal case artifact error: {error}', file=sys.stderr)
        sys.exit(1)
