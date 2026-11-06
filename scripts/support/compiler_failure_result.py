"""Private producer-owned failure transport; process supervision stays with caller."""
import argparse
from dataclasses import dataclass
import json
import os
from pathlib import Path
import secrets
import subprocess
import sys
import tempfile

DESCRIPTOR_ENV = '_PLEW_COMPILER_FAILURE_FD'
IDENTITY_ENV = '_PLEW_COMPILER_FAILURE_ID'
DOMAINS = frozenset({'source', 'input', 'tool', 'limit', 'internal', 'unclassified'})


def decode_record(data, identity):
    if not data:
        return None, 'missing'
    if len(data) > 1024:
        return None, 'oversized'
    fields = data.split(b'\n')
    if len(fields) != 4 or fields[0] != b'plew.compiler.failure.v1' or fields[3] != b'':
        return None, 'malformed'
    if fields[1] != identity.encode('ascii'):
        return None, 'wrong-invocation'
    try:
        domain = fields[2].decode('ascii')
    except UnicodeDecodeError:
        return None, 'malformed'
    if domain not in DOMAINS:
        return None, 'unknown-domain'
    return domain, 'complete'


@dataclass(frozen=True)
class CompilerResult:
    returncode: int
    invocation: str
    failure_domain: str | None
    channel: str
    stdout: bytes | str | None = None
    stderr: bytes | str | None = None

    @property
    def source_rejection(self):
        return self.returncode == 1 and self.channel == 'complete' and self.failure_domain == 'source'

    @property
    def implementation_limit(self):
        return self.returncode == 1 and self.channel == 'complete' and self.failure_domain == 'limit'

    def record(self):
        return {'schema': 1, 'invocation': self.invocation,
                'returncode': self.returncode, 'channel': self.channel,
                'failure_domain': self.failure_domain, 'source_rejection': self.source_rejection}


def run_compiler(command, *, env=None, **options):
    """Keep subprocess options/results; this function does not own watchdog policy.

    A new unlinked file/ID belongs to exactly this invocation. No old receipt or
    rendered diagnostic is input to classification. Nested process wrappers must
    preserve the explicit descriptor or be placed outside this invocation helper.
    """
    identity = secrets.token_hex(16)
    with tempfile.TemporaryFile() as channel:
        environment = dict(os.environ if env is None else env)
        environment.update({DESCRIPTOR_ENV: str(channel.fileno()), IDENTITY_ENV: identity})
        inherited = tuple(options.pop('pass_fds', ()))
        if options.get('check'):
            raise ValueError('compiler result classification requires check=False')
        process = subprocess.run(command, env=environment,
            pass_fds=(*inherited, channel.fileno()), **options)
        channel.seek(0)
        domain, state = decode_record(channel.read(1025), identity)
    return CompilerResult(process.returncode, identity, domain, state, process.stdout, process.stderr)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--result', type=Path)
    parser.add_argument('--require-source-rejection', action='store_true',
                        help='assert the private source-rejection postcondition')
    parser.add_argument('command', nargs=argparse.REMAINDER)
    args = parser.parse_args()
    command = args.command[1:] if args.command[:1] == ['--'] else args.command
    if not command:
        parser.error('a compiler command is required')
    try:
        result = run_compiler(command)
        if args.result:
            args.result.write_text(json.dumps(result.record(), indent=2) + '\n')
    except (OSError, ValueError) as error:
        print(f'compiler-result: {error}', file=sys.stderr)
        return 125
    code = result.returncode
    if args.require_source_rejection:
        if result.source_rejection:
            return 0
        if code == 0:
            return 1
    return code if code >= 0 else 128 - code


if __name__ == '__main__':
    raise SystemExit(main())
