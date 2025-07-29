grammar Sandbox;

expression: coalesce;
coalesce: coalesce COALESCE_OP or | or;
or: or OR_OP and | and;
and: and AND_OP relational | relational;
relational: relational RELATIONAL_OP add | add;
add: add ADD_OP multiply | multiply;
multiply: multiply MUL_OP unary_prefix | unary_prefix;
unary_prefix: UNARY_PREFIX_OP? unary_postfix;
unary_postfix: primary UNARY_POSTFIX_OP?;
COALESCE_OP: '??';
OR_OP: '||';
AND_OP: '&&';
RELATIONAL_OP: '==' | '!=' | '<' | '>' | '<=' | '>=';
ADD_OP: '+' | '-';
MUL_OP: '*' | '/';
UNARY_PREFIX_OP: '-' | '!';
UNARY_POSTFIX_OP: '?';

primary: literal | '(' expression ')';

literal:
	integer_literal
	| float_literal
	| string_literal
	| bool_literal;
integer_literal: DIGIT+;
float_literal: DIGIT+ '.' DIGIT+;
string_literal: '"' .*? '"';
bool_literal: 'true' | 'false';

DIGIT: [0-9];
