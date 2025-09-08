grammar Plew;

program: (program_component req_newline)* EOF;

program_component:
	import_statement
	| extern
	| extension
	| trait
	| enum
	| struct
	| impl
	| type_alias
	| function
	| value_declare;

import_statement:
	IMPORT import_source ((AS type) | import_with)?;
import_with:
	WITH '{' opt_newline import_with_component (
		',' opt_newline import_with_component
	)* opt_newline '}';
import_with_component: (type (AS type)?) | (value (AS value)?);
import_source:
	package_name
	| path_component ( '/' path_component)*;
path_component: '.' | '..' | type;
package_name: '@' type;

extern:
	EXTERN string_literal '{' (
		req_newline (function_declare | value_declare)
	)* opt_newline '}';

extension:
	EXPORT? EXTENSION type (type_args_declare where_clauses?)? '{' opt_newline extension_body (
		req_newline extension_body
	)* opt_newline '}';
extension_body: impl;

trait:
	EXPORT? TRAIT type (type_args_declare where_clauses?)? '{' trait_bodies? '}';
trait_bodies:
	opt_newline trait_body (req_newline trait_body)* opt_newline;
trait_body:
	TYPE type type_annotate
	| type_alias
	| assoc_field_declare
	| field_declare
	| constructor_declare
	| method_declare;

enum: (enum_directives req_newline)? EXPORT? ENUM type (
		type_args_declare where_clauses?
	)? '{' enum_bodies? '}';
enum_bodies:
	opt_newline enum_body (req_newline enum_body)* opt_newline;
enum_body: type_alias | enum_variant_declare;
enum_variant_declare:
	enum_variant ('{' enum_variant_declare_bodies '}')?;
enum_variant_declare_bodies:
	opt_newline enum_variant_declare_body (
		req_newline enum_variant_declare_body
	)* opt_newline;
enum_variant_declare_body: field_access_modifier? field_declare;
enum_directives:
	'@[' opt_newline enum_directive (
		',' opt_newline enum_directive
	)* opt_newline ']';
enum_directive: 'all' | common_directive;

struct:
	(struct_directives req_newline)? EXPORT? STRUCT type (
		type_args_declare where_clauses?
	)? '{' struct_bodies? '}';
struct_bodies:
	opt_newline struct_body (req_newline struct_body)* opt_newline;
struct_body: type_alias | field_access_modifier? field_declare;
struct_directives:
	'@[' opt_newline struct_directive (
		',' opt_newline struct_directive
	)* opt_newline ']';
struct_directive:
	'default_constructor(' PUB ')'
	| common_directive;

common_directive: 'eq' | 'hash' | 'clone' | 'decode' | 'encode';

assoc_field_declare: ASSOC field_declare;
field_declare: value_declare_head type_annotate;

impl:
	IMPL type type_args_declare? (AS type_use type_args?)? where_clauses? '{' (
		req_newline type_alias
	)* (req_newline assoc_value) (
		req_newline value_declare_head VIA value
	)* (req_newline constructor)* (req_newline method)* opt_newline '}';

assoc_value:
	ASSOC value_declare_head type_annotate? '=' expression;
type_alias: TYPE type '=' type_use;
field_access_modifier: PUB ('(' GET ')')?;

constructor: constructor_declare block;
constructor_declare:
	PUB? block_modifier? CONSTRUCT function_declare_tail;
method: method_declare block;
method_declare:
	PUB? method_modifier FN function_name function_declare_tail;
method_modifier:
	ASSOC block_modifier?
	| ASYNC MUT
	| MUT
	| block_modifier;
function: function_declare block;
function_declare:
	EXPORT? block_modifier? FN function_name function_declare_tail;
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
	| guard
	| while
	| CONTINUE;
return_statement: RETURN expression?;
break_statement: BREAK expression?;
give_statement: GIVE expression;
value_declare: value_declare_head type_annotate;
assign: assign_left ASSIGN_OP expression;
assign_left:
	assign_left_with_declare
	| assign_left_without_declare;
assign_left_with_declare:
	value_declare_head type_annotate?
	| tuple_assign_left_with_declare
	| struct_assign_left_with_declare;
tuple_assign_left_with_declare:
	'(' opt_newline assign_left_with_declare (
		',' opt_newline assign_left_with_declare
	)* opt_newline ')';
struct_assign_left_with_declare:
	'[' opt_newline struct_assign_left_entry_with_declare (
		',' opt_newline struct_assign_left_entry_with_declare
	)* opt_newline ']';
struct_assign_left_entry_with_declare:
	expression ':' assign_left_with_declare;
assign_left_without_declare:
	value ('.' opt_newline value)*
	| extended_type_chain ( '.' opt_newline value)+
	| tuple_assign_left_without_declare
	| struct_assign_left_without_declare;
struct_assign_left_without_declare:
	'[' opt_newline struct_assign_left_entry_without_declare (
		',' opt_newline struct_assign_left_entry_without_declare
	)* opt_newline ']';
struct_assign_left_entry_without_declare:
	expression ':' assign_left_without_declare;
tuple_assign_left_without_declare:
	'(' opt_newline assign_left_without_declare (
		',' opt_newline assign_left_without_declare
	)* opt_newline ')';
value_declare_head: MUT? VAL value;
ASSIGN_OP: '=' | '+=' | '-=' | '*=' | '/=';
guard:
	GUARD enum_assign (AND_OP opt_newline enum_assign)* block;
while: WHILE condition block;
for: FOR assign_left_with_declare IN expression block;

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
UNARY_POSTFIX_OP: '!';

primary:
	literal
	| primary (member_access opt_newline (value | function_call))+
	| primary extension_use
	| static_access
	| construct
	| enum_construct
	| block_expression
	| loop_expression
	| if_expression
	| match_expression
	| primary AS type_use
	| AWAIT primary
	| TRY primary
	| primary '[' primary ']'
	| '(' expression ')';

static_access:
	(type_use '.' opt_newline)? (value | function_call);
function_call: function_name type_args? '(' call_args? ')';
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

enum_construct:
	type_use '.' opt_newline enum_variant (
		'(' opt_newline expression (',' opt_newline expression)* opt_newline ')'
	)?;

member_access: '?'* '.';

if_expression:
	if block_expression (elif block_expression)* else block_expression;
if: IF condition;
elif: ELIF condition;
else: ELSE;
condition:
	expression
	| (expression AND_OP opt_newline)? enum_assign (
		AND_OP opt_newline condition
	)?;
enum_assign: enum_assign_left '=' expression;

match_expression:
	MATCH expression '{' (
		req_newline match_case block_expression
	)* req_newline '}';
match_case: expression | enum_assign_left | '_';
enum_assign_left:
	type ('.' opt_newline type)* '.' enum_variant '(' assign_left_with_declare ')';

loop_expression: LOOP block;

block_expression: block_modifier? block;
block_modifier: ASYNC | SPAWN;
block:
	'{' opt_newline (
		statement (req_newline statement)* opt_newline
	)? '}';

type_annotate: ':' type_use;
type_use:
	extendend_type type_args? ('.' extendend_type type_args?)*;
extended_type_chain:
	extendend_type ('.' opt_newline extendend_type)*;
extendend_type: type extension_use?;
type: SELF_TYPE | PASCAL_CASE;
value: SELF | SNAKE_CASE;
enum_variant: PASCAL_CASE;

extension_use: (opt_newline ('#' | '#!') type_use)+;

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
bool_literal: 'true' | 'false';
string_literal: back_string_literal | double_string_literal;
back_string_literal:
	'`' (BACK_STRING_CHAR | string_variable)* '`';
BACK_STRING_CHAR: '\\' . | ~[`\u007B];
double_string_literal:
	'"' (DOUBLE_STRING_CHAR | string_variable)* '"';
DOUBLE_STRING_CHAR: '\\' . | ~["\u007B];
string_variable: '{' expression (':' STRING_FORMAT+)? '}';
STRING_FORMAT: '\\' . | ~[\u007D];

req_newline: NEWLINE+;
opt_newline: NEWLINE*;

NEWLINE: '\n';
DIGIT: [0-9];
SNAKE_CASE: [a-z] [a-z0-9_]*;
PASCAL_CASE: [A-Z] [A-Za-z0-9]*;
EXPORT: 'export';
PUB: 'pub';
GET: 'get';
TYPE: 'type';
VAL: 'val';
MUT: 'mut';
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
GUARD: 'guard';
WHILE: 'while';
FOR: 'for';
IN: 'in';
IF: 'if';
ELIF: 'elif';
ELSE: 'else';
MATCH: 'match';
AS: 'as';
SELF: 'self';
SELF_TYPE: 'Self';
EXTERN: 'extern';
IMPORT: 'import';
WITH: 'with';
TRY: 'try';

WHITESPACE: [ \t]+ -> skip;
LINE_COMMENT: '//' ~[\n]* -> skip;
BLOCK_COMMENT: '/*' .*? '*/' -> skip;
