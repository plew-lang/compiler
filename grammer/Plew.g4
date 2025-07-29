grammar Plew;

// for in, while, comment, import, match, lazy, anonymous function, if let, enum access, assoc member access

extern:
	EXTERN string_literal '{' (req_newline function_declare)* (
		req_newline value_declare
	)* opt_newline '}';

trait:
	access_modifier? TRAIT type (
		type_args_declare where_clauses?
	)? '{' (req_newline (type | type_alias))* (
		req_newline assoc_field_declare
	)* (req_newline field_declare)* (
		req_newline constructor_declare
	)* (req_newline method_declare)* opt_newline '}';

struct:
	(struct_directives req_newline)? access_modifier? STRUCT type (
		type_args_declare where_clauses?
	)? '{' (req_newline type_alias)* (
		req_newline field_access_modifier? field_declare
	)* opt_newline '}';

struct_directives:
	struct_directive (req_newline struct_directive)*;
struct_directive: '@' struct_directive_name;
struct_directive_name:
	'default_constructor(' access_modifier ')'
	| 'field_key';

assoc_field_declare: ASSOC field_declare;
field_declare: value_declare_head type_annotate;

enum: (enum_directives req_newline)? access_modifier? ENUM type (
		type_args_declare where_clauses?
	)? '{' (req_newline type_alias)* (req_newline enum_case)* opt_newline '}';

enum_case:
	ENUM_CASE (
		'(' opt_newline type_use (',' opt_newline type_use)* opt_newline ')'
	)?;
ENUM_CASE: PASCAL_CASE;
enum_directives: enum_directive (req_newline enum_directive)*;
enum_directive: '@' enum_directive_name;
enum_directive_name: 'all';

extension: access_modifier? EXTENSION type FOR impl_body;
impl: IMPL impl_body;
impl_body:
	type type_args_declare? (AS type type_args?)? where_clauses? '{' (
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
	access_modifier? block_modifier? CONSTRUCT function_declare_tail;
method: method_declare block;
method_declare:
	access_modifier? method_modifier FN function_name function_declare_tail;
method_modifier:
	ASSOC block_modifier?
	| ASYNC MUT
	| MUT
	| block_modifier;
function: function_declare block;
function_declare:
	access_modifier? block_modifier? FN function_name function_declare_tail;
function_declare_tail:
	type_args_declare? '(' args_declare? ')' return_type? where_clauses?;
return_type: '->' type_use;
args_declare:
	opt_newline arg_declare (',' opt_newline arg_declare)* ','? opt_newline;
arg_declare: INOUT? value type_annotate;

statement:
	expression
	| value_declare
	| assign
	| return_statement
	| break_statement
	| give_statement
	| CONTINUE;
return_statement: RETURN expression?;
break_statement: BREAK expression?;
give_statement: GIVE expression;
value_declare:
	value_declare_head (
		type_annotate
		| type_annotate? assign_right
	);
value_declare_head: (SYNC | MUT)? VAL value;
assign: value assign_right;
assign_right: '=' expression;

expression: coalesce;
coalesce: coalesce COALESCE_OP opt_newline or | or;
or: or OR_OP opt_newline and | and;
and: and AND_OP opt_newline relational | relational;
relational: relational RELATIONAL_OP opt_newline add | add;
add: add ADD_OP opt_newline multiply | multiply;
multiply:
	multiply MUL_OP opt_newline unary_prefix
	| unary_prefix;
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

primary:
	literal
	| primary ('.' opt_newline (value | function_call))+
	| static_access
	| construct
	| block_expression
	| loop_expression
	| if_expression
	| lock_expression
	| primary AS type_use
	| AWAIT primary
	| primary '[' primary ']'
	| '(' expression ')';

static_access:
	(type_use '.' opt_newline)? (value | function_call);
function_call:
	function_name ('@' type ('.' type)*)? type_args? '(' call_args? ')';
call_args:
	opt_newline arg (',' opt_newline arg)* ','? opt_newline;
arg: (value ':')? expression;
function_name: SNAKE_CASE;

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
	block_modifier? if block (elif block)* else block;
if: IF expression;
elif: ELIF expression;
else: ELSE;

lock_expression:
	LOCK lock_value (',' opt_newline lock_value)* block;
lock_value: value | value '=' expression;

loop_expression: LOOP block;

block_expression: block_modifier? block;
block_modifier: ASYNC | SPAWN;
block:
	'{' opt_newline (
		statement (req_newline statement)* opt_newline
	)? '}';

access_modifier: EXPORT;

type_annotate: ':' type_use;
type_use: type type_args? ('.' type type_args?)*;
type: SELF_TYPE | PASCAL_CASE;
value: SELF | SNAKE_CASE;
crate: PASCAL_CASE;

type_args_declare: '[' type (',' type)* ']';
type_args: '[' type_use (',' type_use)* ']';

where_clauses:
	WHERE where_clause (',' opt_newline where_clause)*;
where_clause: type ('.' type)* type_annotate;

literal:
	closure_literal
	| array_literal
	| dictionary_literal
	| tuple_literal
	| integer_literal
	| float_literal
	| string_literal
	| bool_literal;
closure_literal: FN function_declare_tail;
array_literal:
	'[' (opt_newline expression (',' opt_newline expression)*)? opt_newline ']';
dictionary_literal:
	'[' opt_newline dictionary_entry (
		',' opt_newline dictionary_entry
	)* opt_newline ']'
	| '[:]';
tuple_literal:
	'(' opt_newline expression (',' opt_newline expression)+ opt_newline ')';
dictionary_entry: expression ':' expression;
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
EXPORT: 'export';
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
CONTINUE: 'continue';
GIVE: 'give';
RETURN: 'return';
WHERE: 'where';
ENUM: 'enum';
STRUCT: 'struct';
ASSOC: 'assoc';
EXTENSION: 'extension';
IMPL: 'impl';
VIA: 'via';
TRAIT: 'trait';
FN: 'fn';
CONSTRUCT: 'construct';
INOUT: 'inout';
IF: 'if';
ELIF: 'elif';
ELSE: 'else';
FOR: 'for';
LOCK: 'lock';
MATCH: 'match';
AS: 'as';
SELF: 'self';
SELF_TYPE: 'Self';
EXTERN: 'extern';

WHITESPACE: [ \t]+ -> skip;
