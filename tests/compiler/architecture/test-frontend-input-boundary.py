#!/usr/bin/env python3
"""Keep process input at the CLI edge rather than in embeddable analysis."""
from pathlib import Path
import re
root = Path(__file__).resolve().parents[3]
frontend = (root / 'src/Frontend.pw').read_text()
driver = (root / 'src/FrontendDriver.pw').read_text()
analysis = frontend.split('pub fn analyzeFrontend(', 1)[1]
assert not re.search(r'\b(?:argCount|readStdin|computeStdRoot)\(', analysis)
assert 'argAt(entryArgIdx)' not in analysis
assert 'FrontendInput.File(path:' in analysis
assert 'FrontendInput.Text(text:' in analysis
assert 'sources.stdRoot' in analysis
entry = analysis.split('// Whether the literal', 1)[0]
assert '-> Result[(), CompileDiagnostic]' in entry
assert 'c.errorAt(' not in entry and 'exit(' not in entry
assert 'match analysis {' in driver and 'emitDiagnostic(diagnostic: diagnostic)' in driver
assert 'return <FrontendRequest input=input sources=configuredSources' in driver
assert 'analyzeFrontend(c: inout c, input: request.input, sources: request.sources, options: request.options)' in driver
compiler = (root / 'src/Compiler.pw').read_text()
assert 'CheckedProgram.check(input: request.input, sources: request.sources, options: request.options)' in compiler
checked = (root / 'src/CheckedProgram.pw').read_text()
checking = checked.split('assoc fn check(', 1)[1].split('pub fn prepareCheckedProgram(', 1)[0]
assert checking.index('CompilerSession.open(') < checking.index('checkCompilerSession(session: move session)')
opening = checked.split('assoc fn open(', 1)[1].split('// Declaration IDs', 1)[0]
assert opening.index('analyzeFrontendForRequests(') < opening.index('<CompilerSessionResult.Success')
completion = checked.split('pub fn checkCompilerSession(', 1)[1].split('// Static success', 1)[0]
assert completion.index('completeFrontendDeclarations(') < completion.index('prepareDeclarationProgramWithRequests(') < completion.index('<ProgramCheckResult.Success')
assert 'session=move state' in completion
assert 'analyzeFrontendForRequests(' not in completion  # complete the same snapshot
session = checked.split('pub unique struct CompilerSession {', 1)[1].split('}', 1)[0]
assert 'pub val ' not in session and 'pub mut val ' not in session
assert 'mut val session: CompilerSession' in checked
checking = opening + checking
for forbidden in ('finalizeFrontendExecutables(', 'LLVMContextCreate(', 'argCount(', 'readStdin(', 'exit(', 'emitDiagnostic('):
    assert forbidden not in checking, f'whole-target check crosses its boundary: {forbidden}'
assert 'import ./Backend' not in checked
assert 'pub mut val compiler' not in checked.split('pub unique struct CheckedProgram {', 1)[1].split('}', 1)[0]
assert 'readStdin()' in driver and 'computeStdRoot(arg0:' in driver
print('PASS explicit frontend inputs and CLI ownership')
