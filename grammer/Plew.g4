grammar Plew;

// enum, for in, while, array, comment, import, generics, match, lock, ??, ?, declare, factory

trait:
	TRAIT type (type_args_declare where_clauses?)? '{' (
		req_newline (type | type_alias)
	)* (req_newline assoc_field_declare)* (
		req_newline field_declare
	)* (req_newline constructor_declare)* (
		req_newline method_declare
	)* opt_newline '}';

struct:
	access_modifier? STRUCT type (
		type_args_declare where_clauses?
	)? '{' (req_newline type_alias)* (
		req_newline field_access_modifier? field_declare
	)* opt_newline '}';

assoc_field_declare: ASSOC field_declare;
field_declare: value_declare_head type_annotate;

impl:
	IMPL type type_args_declare? (WITH type type_args?)? where_clauses? '{' (
		req_newline type_alias
	)* (req_newline assoc_value) (
		req_newline value_declare_head VIA value
	)* (req_newline constructor)* (req_newline method)* opt_newline '}';

assoc_value:
	ASSOC value_declare_head type_annotate? assign_right;
type_alias: TYPE type '=' type_use;
field_access_modifier: access_modifier ('(' GET ')')?;

constructor: constructor_declare block;
constructor_declare:
	access_modifier? function_modifier? CONSTRUCT function_declare_tail;
method: method_declare block;
method_declare:
	access_modifier? method_modifier FN function_name function_declare_tail;
method_modifier:
	ASSOC function_modifier?
	| ASYNC MUT
	| MUT
	| function_modifier;
function: function_declare block;
function_declare:
	access_modifier? function_modifier? FN function_name function_declare_tail;
function_modifier: ASYNC | SPAWN;
function_declare_tail:
	type_args_declare? '(' args_declare? ')' return_type? where_clauses?;
return_type: '->' type_use;
args_declare:
	opt_newline arg_declare (',' opt_newline arg_declare)* ','? opt_newline;
arg_declare: INOUT? value type_annotate;
block:
	'{' opt_newline (
		(multiple_statements opt_newline)
		| (return_statement opt_newline)
		| (
			(multiple_statements req_newline)? return_statement opt_newline
		)
	)? '}';

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
	value_declare_head (
		type_annotate
		| type_annotate? assign_right
	);
value_declare_head: (SYNC | MUT)? VAL value;
assign: value assign_right;
assign_right: '=' expression;

expression:
	literal
	| value
	| expression ('.' opt_newline (value | function_call))+
	| function_call
	| construct
	| block_expression
	| if_expression
	| expression AS type_use
	| AWAIT expression
	| expression '[' expression ']'
	| '(' expression ')';

construct:
	'<' type_use opt_newline construct_args? (
		construct_children
		| '/>'
	);
construct_children:
	'>' (req_newline expression)* opt_newline '</' type '>';
construct_args: construct_arg (opt_newline construct_arg)*;
construct_arg: value '=' expression;

if_expression:
	if block_expression (elif block_expression)* else block_expression;

block_expression:
	(ASYNC | SPAWN)? '{' opt_newline (
		multiple_statements req_newline
	)? give_statement opt_newline;
give_statement: GIVE expression;

loop_expression:
	LOOP '{' opt_newline multiple_loop_statements '}';
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
OR_OP: '||';
AND_OP: '&&';
RELATIONAL_OP: '==' | '!=' | '<' | '>' | '<=' | '>=';
ADD_OP: '+' | '-';
MUL_OP: '*' | '/';
UNARY_OP: '-' | '!';
WHITESPACE: [ \t]+ -> skip;

function_call:
	function_name ('@' crate)? type_args? '(' call_args? ')';
call_args:
	opt_newline arg (',' opt_newline arg)* ','? opt_newline;
arg: expression;
function_name: SNAKE_CASE;

if: IF expression;
elif: ELIF expression;
else: ELSE;

access_modifier: EXT? PUB;

type_annotate: ':' type_use;
type_use: type type_args? ('.' type)*;
type: SELF_TYPE | PASCAL_CASE;
value: SELF | SNAKE_CASE;
crate: PASCAL_CASE;

type_args_declare: '[' type (',' type)* ']';
type_args: '[' type_use (',' type_use)* ']';

where_clauses:
	WHERE where_clause (',' opt_newline where_clause)*;
where_clause: type ('.' type)* type_annotate;

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
ASSOC: 'assoc';
IMPL: 'impl';
WITH: 'with';
VIA: 'via';
TRAIT: 'trait';
FN: 'fn';
CONSTRUCT: 'construct';
INOUT: 'inout';
IF: 'if';
ELIF: 'elif';
ELSE: 'else';
AS: 'as';
SELF: 'self';
SELF_TYPE: 'Self';
