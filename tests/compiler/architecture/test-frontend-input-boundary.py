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
assert 'analyzeFrontend(c: inout c, input: input, sources: configuredSources' in driver
assert 'readStdin()' in driver and 'computeStdRoot(arg0:' in driver
print('PASS explicit frontend inputs and CLI ownership')
