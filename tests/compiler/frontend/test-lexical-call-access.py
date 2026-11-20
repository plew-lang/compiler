#!/usr/bin/env python3
"""Manual source-recording probe; inspect private access facts without shipping a test API."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tomllib

ROOT = Path(__file__).resolve().parents[3]
HOOK = '''
pub impl Comp {
    inout fn testArgumentAccessCount(function: U64, expression: U64) -> Result[U64, CompileDiagnostic] {
        val site = try self.templateCallSiteKey(fnIdx: function, exprId: expression)
        mut val count = 0U64
        for use in self.accessUses.getOr(key: site.lookupHash(), fallback: []) {
            if self.sameCallSiteKey(a: use.parent, b: site) && use.role == 2U64 && use.argIndex == 0U64 { count += 1U64 }
        }
        return <Result.Ok value=count />
    }
}
'''
PROBE = '''use ../../../src/Frontend only { Comp, FrontendInput, analyzeFrontendForRequests }
use ../../../src/SourceAccess only { SourceAccess }
use ../../../src/Ir only { Expr }
use @Std/Process only { argAt }
use @Std/Io only { print }
fn main() {
    mut val compiler = <Comp />
    match analyzeFrontendForRequests(c: inout compiler, input: <FrontendInput.File path=argAt(1I64) />, sources: <SourceAccess />) { Result.Ok(value: _) => {} Result.Err(error: val diagnostic) => { panic(diagnostic.message()) } }
    val name = compiler.internBytes(s: "apply")
    val function = compiler.arena.firstFunctionNamed(nameId: name.nameId)
    match compiler.prepareLexicalBody(fnIdx: function) { Result.Ok(value: _) => {} Result.Err(error: val diagnostic) => { panic(diagnostic.message()) } }
    mut val checked = false
    for index in 0U64..<compiler.arena.exprs.count() {
        match compiler.arena.exprs[index] {
            Expr.Call(nameStart: val start, nameLen: val len, args: _) => {
                val name = "action".bytes()
                mut val matches = len == name.count()
                if matches { for offset in 0U64..<len { if compiler.arena.bytes[start + offset] != name[offset] { matches = false } } }
                if matches {
                    val count = compiler.testArgumentAccessCount(function: function, expression: index).unwrap()
                    if count != 1U64 { panic("dynamic argument access provenance was lost") }
                    checked = true
                }
            }
            _ => {}
        }
    }
    if !checked { panic("probe did not reach the dynamic call") }
    print("argument access preserved")
}
'''

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--compiler', required=True, type=Path)
    parser.add_argument('--out', required=True, type=Path)
    args = parser.parse_args()
    out = args.out.resolve(); out.mkdir(parents=True, exist_ok=False)
    carrier = args.compiler.resolve()
    sys.path.insert(0, str(ROOT/'scripts/support'))
    import clang_environment
    clang_environment.apply()
    watch = [sys.executable, '-B', str(ROOT/'scripts/support/watch-command.py'), '--']
    trace = [sys.executable, '-B', str(ROOT/'scripts/support/trace-command.py')]
    fixture = ROOT/'tests/compiler/frontend/fixtures/LexicalCallBinding/InoutIndex.pw'
    inputs = [carrier, Path(__file__), fixture, ROOT/'Plew.toml', ROOT/'Plew.lock', *sorted((ROOT/'src').rglob('*.pw')), *sorted((ROOT/'std').rglob('*.pw')), *sorted((carrier.parent/'std').rglob('*.pw')), ROOT/'scripts/support/trace-command.py', ROOT/'scripts/support/watch-command.py']
    def hashes(): return {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in inputs}
    frozen = hashes(); results = []
    runtime = out/'runtime.c'
    with runtime.open('wb') as stream:
        subprocess.run([*watch, str(carrier), '--runtime'], stdout=stream, check=True)
    manifest = (ROOT/'Plew.toml').read_text()
    dependency = tomllib.loads(manifest)['dependencies']['Plew/Syntax']
    syntax = (ROOT/dependency['path']).resolve() if isinstance(dependency, dict) and 'path' in dependency else None
    for label in ['retained', 'omitted-control']:
        folder = out/label; folder.mkdir()
        shutil.copytree(ROOT/'src', folder/'src')
        (folder/'std').symlink_to(ROOT/'std', target_is_directory=True)
        selected_manifest = manifest
        if syntax:
            selected_manifest = re.sub(r'(?m)^"Plew/Syntax"\s*=.*$', '"Plew/Syntax" = { path = '+json.dumps(os.path.relpath(syntax, folder))+' }', manifest)
        (folder/'Plew.toml').write_text(selected_manifest)
        shutil.copy2(ROOT/'Plew.lock', folder/'Plew.lock')
        frontend = folder/'src/Frontend.pw'; frontend.write_text(frontend.read_text()+HOOK)
        if label == 'omitted-control':
            path = folder/'src/Codegen/Resolve/Record.pw'; text = path.read_text()
            line = '        try self.recordArgumentAccessUses(parentExpr: exprId, callee: self.arena.functionCount(), args: args)\n'
            assert text.count(line) == 1
            path.write_text(text.replace(line, '', 1))
        probe = folder/'tests/compiler/frontend/AccessProbe.pw'; probe.parent.mkdir(parents=True); probe.write_text(PROBE)
        obj = folder/'probe.o'
        with (folder/'compile.stderr').open('wb') as log:
            subprocess.run([*trace, str(folder/'compile.log'), '--', str(carrier), '--emit-object', str(obj), '--trace-phases', str(probe)], cwd=ROOT, stderr=log, check=True)
        program = folder/'probe'
        subprocess.run([*watch, '/usr/bin/clang', '-O1', str(obj), str(runtime), '-o', str(program)], check=True)
        run = subprocess.run([*watch, str(program), str(fixture)], cwd=ROOT, capture_output=True, timeout=60)
        (folder/'stdout').write_bytes(run.stdout); (folder/'stderr').write_bytes(run.stderr)
        if label == 'retained':
            assert (run.returncode, run.stdout, run.stderr) == (0, b'argument access preserved\n', b''), run
        else:
            assert run.returncode != 0 and b'panic: dynamic argument access provenance was lost' in run.stderr, run
        results.append({'case': label, 'status': run.returncode, 'expected': True})
    assert hashes() == frozen, 'probe product inputs changed'
    (out/'result.json').write_text(json.dumps({'inputs': frozen, 'cases': results, 'scope': 'Source-recording access metadata only; no function-value inout Mid/LLVM success claim'}, indent=2)+'\n')
    print('PASS lexical call argument access; omitted-record control detected')

if __name__ == '__main__':
    main()
