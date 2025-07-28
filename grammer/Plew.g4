grammar Plew;

// enum, for in, while, array, comment, import, generics, match, lock, ??, ?, declare, cast, self, function@crate()

trait:
	TRAIT type (type_arguments where_clauses?)? BLOCK_OPEN (
		req_newline (type | type_alias)
	)* (req_newline value_declare)* (
		req_newline function_declare
	)* opt_newline BLOCK_CLOSE;

struct:
	access_modifier? STRUCT type (type_arguments where_clauses?)? BLOCK_OPEN (
		req_newline type_alias
	)* (req_newline field_access_modifier? value_declare)* opt_newline BLOCK_CLOSE;

impl:
	IMPL type type_arguments? (WITH type type_parameters?)? where_clauses? BLOCK_OPEN (
		req_newline type_alias
	)* (req_newline value VIA value)* (req_newline function)* opt_newline BLOCK_CLOSE;

type_alias: TYPE type ASSIGN type_use;
field_access_modifier: access_modifier ('(' GET ')')?;

function: function_declare block;
function_declare:
	access_modifier? (ASYNC | SPAWN)? FN function_name type_arguments? '(' declare_args? ')'
		return_type? where_clauses?;
return_type: '->' type_use;
declare_args:
	opt_newline declare_arg (',' opt_newline declare_arg)* ','? opt_newline;
declare_arg: value type_annotate;
block:
	BLOCK_OPEN opt_newline (
		(multiple_statements opt_newline)
		| (return_statement opt_newline)
		| (
			(multiple_statements req_newline)? return_statement opt_newline
		)
	)? BLOCK_CLOSE;

multiple_statements: statement (req_newline statement)*;
statement:
	expression
	| block
	| if_statement
	| value_declare
	| assign;
if_statement: if block (elif block)* (else block)?;
return_statement: RETURN expression;
value_declare:
	(SYNC | MUT)? VAL value (
		type_annotate
		| type_annotate? assign_right
	);
assign: value assign_right;
assign_right: ASSIGN expression;

expression:
	literal
	| value
	| expression ('.' opt_newline (value | function_call))+
	| function_call
	| block_expression
	| if_expression
	| AWAIT expression
	| expression '[' expression ']'
	| '(' expression ')';

if_expression:
	if block_expression (elif block_expression)* else block_expression;

block_expression:
	(ASYNC | SPAWN)? BLOCK_OPEN opt_newline (
		multiple_statements req_newline
	)? give_statement opt_newline;
give_statement: GIVE expression;

loop_expression:
	LOOP BLOCK_OPEN opt_newline multiple_loop_statements BLOCK_CLOSE;
multiple_loop_statements:
	loop_statement (req_newline loop_statement)*;
loop_statement: statement | break_statement;
break_statement: BREAK expression?;

or: or OR_OP opt_newline and | and;
and: and AND_OP opt_newline relational | relational;
relational: relational RELATIONAL_OP opt_newline add | add;
add: add ADD_OP opt_newline multiply | multiply;
multiply: multiply MUL_OP opt_newline unary | unary;
unary: UNARY_OP? expression;

function_call:
	function_name type_parameters? '(' call_args? ')';
call_args:
	opt_newline arg (',' opt_newline arg)* ','? opt_newline;
arg: expression;
function_name: SNAKE_CASE;

if: IF expression;
elif: ELIF expression;
else: ELSE;

access_modifier: EXT? PUB;

type_annotate: ':' type_use;
type_use: type type_parameters? ('.' type)*;
type: PASCAL_CASE;
value: SNAKE_CASE;

type_arguments: '[' type (',' type)* ']';
type_parameters: '[' type_use (',' type_use)* ']';

where_clauses:
	WHERE where_clause (',' opt_newline where_clause)*;
where_clause: type ('.' type)* ':' type_use;

literal:
	integer_literal
	| float_literal
	| string_literal
	| bool_literal;
integer_literal: DIGIT+;
float_literal: DIGIT+ '.' DIGIT+;
string_literal: '"' .*? '"';
bool_literal: 'true' | 'false';

req_newline: NEWLINE+;
opt_newline: NEWLINE*;

NEWLINE: '\n';
DIGIT: [0-9];
SNAKE_CASE: [a-z] [a-z0-9_]*;
PASCAL_CASE: [A-Z] [A-Za-z0-9]*;
PUB: 'pub';
EXT: 'ext';
GET: 'get';
TYPE: 'type';
VAL: 'val';
MUT: 'mut';
SYNC: 'sync';
ASYNC: 'async';
SPAWN: 'spawn';
AWAIT: 'await';
LOOP: 'loop';
BREAK: 'break';
GIVE: 'give';
RETURN: 'return';
WHERE: 'where';
STRUCT: 'struct';
IMPL: 'impl';
WITH: 'with';
VIA: 'via';
TRAIT: 'trait';
FN: 'fn';
IF: 'if';
ELIF: 'elif';
ELSE: 'else';
BLOCK_OPEN: '{';
BLOCK_CLOSE: '}';
ASSIGN: '=';
OR_OP: '||';
AND_OP: '&&';
RELATIONAL_OP: '==' | '!=' | '<' | '>' | '<=' | '>=';
ADD_OP: '+' | '-';
MUL_OP: '*' | '/';
UNARY_OP: '-' | '!';
WHITESPACE: [ \t]+ -> skip;
