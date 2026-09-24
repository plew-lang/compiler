"""Controlled source edits with the same observable revision oracle."""
def variant(template, revision, scenario, functions, expression_shape):
    kind = ['layout', 'signature', 'generic', 'module'][revision % 4] if scenario == 'mixed' else 'body'
    modules = {}
    if kind == 'layout':
        fields = '\n'.join(f'pub val padding{i}: I64' for i in range(revision % 3 + 1))
        arguments = ' '.join(f'padding{i}={i}I64' for i in range(revision % 3 + 1))
        declarations = (f'struct Revision {{ pub val number: I64\n{fields}\n}}\n'
                        'pub impl Revision { factory }\n'
                        f'fn revised(input: I64) -> I64 {{ val item = <Revision number=input {arguments} /> return item.number }}\n')
        expression = f'revised(input: {revision}I64)'
    elif kind == 'signature':
        if revision % 8 == 1:
            declarations = 'fn revised(input: I64) -> I64 { return input }\n'
            expression = f'revised(input: {revision}I64)'
        else:
            declarations = 'fn revised(input: I64, offset: I64) -> I64 { return input + offset }\n'
            expression = f'revised(input: {revision}I64, offset: 0I64)'
    elif kind == 'generic':
        extra = 'pub val extra: I64\n' if revision % 8 == 2 else ''
        argument = 'extra=11I64' if extra else ''
        declarations = ('struct Revision[T] { pub val number: T\n'+extra+'}\n'
                        'pub impl Revision[T] { factory }\n'
                        'fn unbox[T](box: Revision[T]) -> T { return box.number }\n'
                        f'fn revised(input: I64) -> I64 {{ val box: Revision[I64] = <Revision[I64] number=input {argument} /> return unbox(box: box) }}\n')
        expression = f'revised(input: {revision}I64)'
    elif kind == 'module':
        modules['Changes.pw'] = f'export fn revised() -> I64 {{ return {revision}I64 }}\n'
        declarations = 'import ./Changes with { revised }\n'
        expression = 'revised()'
    else:
        declarations = ''
        expression = f'{revision}I64'
    if functions:
        declarations += '\n'.join(f'fn extra{i}(input: I64) -> I64 {{ return input }}' for i in range(functions))+'\n'
        if expression_shape == 'deep':
            expression += ''.join(f' + extra{i}(input: 0I64)' for i in range(functions))
        else:
            statements = '\n'.join(f'total += extra{i}(input: input)' for i in range(functions))
            declarations += 'fn bulk(input: I64) -> I64 { mut val total = 0I64\n' + statements + '\nreturn total\n}\n'
            expression += ' + bulk(input: 0I64)'
    return declarations + template.replace('input + 7000000I64', 'input + 7000000I64 + '+expression), modules, kind
