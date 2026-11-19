#!/usr/bin/env python3
"""Keep process input at the CLI edge rather than in embeddable analysis."""
from pathlib import Path
import re

def declaration(text, marker):
    """Select this declaration, independent of the next method's name/order."""
    matches = list(re.finditer(r'^\s*' + re.escape(marker), text, re.M))
    assert len(matches) == 1, f'expected one declaration: {marker}'
    start = matches[0].start()
    position, parentheses, depth = start, 0, 0
    quote, comment = False, 0
    while position < len(text):
        char = text[position]
        pair = text[position:position + 2]
        if quote:
            if char == '\\':
                position += 2
                continue
            if char == '"':
                quote = False
        elif comment:
            if pair == '/*':
                comment += 1
                position += 2
                continue
            if pair == '*/':
                comment -= 1
                position += 2
                continue
        elif pair == '//':
            end = text.find('\n', position)
            position = len(text) if end < 0 else end
            continue
        elif pair == '/*':
            comment = 1
            position += 2
            continue
        elif char == '"':
            quote = True
        elif char == '(':
            parentheses += 1
        elif char == ')':
            parentheses -= 1
        elif char == '{' and (depth or parentheses == 0):
            depth += 1
        elif char == '}' and depth:
            depth -= 1
            if depth == 0:
                return text[start:position + 1]
        position += 1
    raise AssertionError(f'unclosed declaration: {marker}')

root = Path(__file__).resolve().parents[3]
frontend = (root / 'src/Frontend.pw').read_text()
driver = (root / 'src/FrontendDriver.pw').read_text()
analysis = frontend
assert not re.search(r'\b(?:argCount|readStdin|computeStdRoot)\(', analysis)
assert 'argAt(entryArgIdx)' not in analysis
assert 'FrontendInput.File(path:' in analysis
assert 'FrontendInput.Text(text:' in analysis
assert 'sources.stdRoot' in analysis
entry = declaration(frontend, 'pub fn analyzeFrontend(')
assert '-> Result[(), CompileDiagnostic]' in entry
assert 'c.errorAt(' not in frontend and 'exit(' not in frontend
assert 'match analysis {' in driver and 'emitCompilerFailure(diagnostic: diagnostic)' in driver
assert 'return <FrontendRequest input=input sources=configuredSourceAccess(sources: sources)' in driver
assert 'pub fn configuredSourceAccess(sources: SourceAccess) -> SourceAccess' in driver
assert 'analyzeFrontend(c: inout c, input: request.input, sources: request.sources, options: request.options)' in driver
compiler = (root / 'src/Compiler.pw').read_text()
assert 'CheckedProgram.check(input: request.input, sources: request.sources, options: request.options)' in compiler
checked = (root / 'src/CheckedProgram.pw').read_text()
checking = declaration(checked, 'assoc fn check(')
assert checking.index('CompilerSession.open(') < checking.index('checkCompilerSession(session: move session)')
opening = declaration(checked, 'assoc fn open(')
assert opening.index('openFrontendForRequests(') < opening.index('<CompilerSessionResult.Success')
completion = declaration(checked, 'pub fn checkCompilerSession(')
assert completion.index('completeFrontendDeclarations(') < completion.index('prepareDeclarationProgramWithRequests(') < completion.index('<ProgramCheckResult.Success')
assert 'session=move state' in completion
assert 'openFrontendForRequests(' not in completion  # complete the same snapshot
session = declaration(checked, 'pub unique struct CompilerSession {')
assert 'pub val ' not in session and 'pub mut val ' not in session
assert 'mut val session: CompilerSession' in checked
checking = opening + checking + completion
for forbidden in ('finalizeFrontendExecutables(', 'LLVMContextCreate(', 'lowerRequestedLlvm(', 'lowerGlobalStorageLlvm(', 'argCount(', 'readStdin(', 'exit(', 'emitDiagnostic(', 'emitCompilerFailure('):
    assert forbidden not in checking, f'whole-target check crosses its boundary: {forbidden}'
source_open = declaration(frontend, 'pub fn openFrontendForRequests(')
assert 'c: inout Comp' not in source_open and 'mut val c = <Comp />' in source_open
assert 'origin: <FrontendDeclarationOrigin.SourceAdmission />' in source_open
# Sessions now also own explicit backend requests. Static check/open must not
# execute them; importing their result types is not code generation.
assert 'use ./Backend' not in frontend
body_lowering = declaration(checked, 'inout fn lowerBody(')
storage_lowering = declaration(checked, 'inout fn lowerGlobalStorage(')
# Internal calls retain the raw cause until the owning public exit interprets it.
assert body_lowering.index('self.prepareBodyAccessRaw(') < body_lowering.index('lowerRequestedLlvm(')
assert storage_lowering.index('self.prepareInitializersRaw(') < storage_lowering.index('lowerGlobalStorageLlvm(')
for method, raw in [('prepareBodyAccess', 'prepareBodyAccessRaw'), ('prepareInitializers', 'prepareInitializersRaw')]:
    wrapper = declaration(checked, 'inout fn ' + method + '(')
    assert 'self.' + raw + '(' in wrapper and 'self.ownedResult(' in wrapper
assert 'self.ownedFailure(' in body_lowering and 'self.ownedFailure(' in storage_lowering
assert checked.count('lowerRequestedLlvm(') == body_lowering.count('lowerRequestedLlvm(') == 1
assert checked.count('lowerGlobalStorageLlvm(') == storage_lowering.count('lowerGlobalStorageLlvm(') == 1
assert 'pub mut val compiler' not in declaration(checked, 'pub unique struct CheckedProgram {')
assert 'readStdin()' in driver and 'computeStdRoot(arg0:' in driver
print('PASS explicit frontend inputs and CLI ownership')
