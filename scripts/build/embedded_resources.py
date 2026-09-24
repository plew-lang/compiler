"""Generate immutable source/runtime resources for the distribution binary."""
import hashlib
import json
from pathlib import Path


def literal(value):
    if '\0' in value:
        raise ValueError('embedded source contains a NUL byte')
    return json.dumps(value, ensure_ascii=False)


def generate(root, destination, runtime, recipe, source_inputs, notices):
    sources = [(path.relative_to(root / 'std').as_posix(), path.read_bytes().decode('utf-8'))
               for path in sorted((root / 'std').rglob('*.pw'))]
    if not sources:
        raise ValueError('no standard sources to embed')
    identity = hashlib.sha256(json.dumps(source_inputs, sort_keys=True).encode()).hexdigest()[:16]
    lines = ['#include "resources.h"', 'namespace {',
             'struct Source { const char *path; const char *text; };',
             'const Source sources[] = {']
    for path, source in sources:
        lines.append('{' + literal('plew:std/' + path) + ',' + literal(source) + '},')
    lines.extend(['};', 'const unsigned char runtime[] = {'])
    data = Path(runtime).read_bytes()
    for start in range(0, len(data), 32):
        lines.append(','.join(str(byte) for byte in data[start:start + 32]) + ',')
    lines.extend(['};', '}', 'extern "C" {',
                  'uint64_t plew_embedded_source_count() { return sizeof(sources)/sizeof(Source); }',
                  'const char *plew_embedded_source_path(uint64_t i) { return i < plew_embedded_source_count() ? sources[i].path : ""; }',
                  'const char *plew_embedded_source_text(uint64_t i) { return i < plew_embedded_source_count() ? sources[i].text : ""; }',
                  'const unsigned char *plew_embedded_runtime_data() { return runtime; }',
                  'size_t plew_embedded_runtime_size() { return sizeof(runtime); }',
                  'const char *plew_distribution_version() { return ' + literal('dev-' + identity) + '; }',
                  'const char *plew_distribution_cpu() { return ' + literal(recipe['target_cpu']) + '; }',
                  'const char *plew_distribution_minimum_macos() { return ' + literal(recipe['minimum_macos']) + '; }',
                  'const char *plew_distribution_licenses() { return ' + literal(notices) + '; }',
                  '}'])
    Path(destination).write_text('\n'.join(lines) + '\n')
