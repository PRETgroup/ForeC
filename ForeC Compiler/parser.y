/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */
 
%require "3.0"
%skeleton "lalr1.cc"
%defines
%locations
%error-verbose
%define api.namespace {forec::loader}
%define parser_class_name {Parser}
%parse-param {forec::loader::Scanner &scanner}
%parse-param {forec::ast::Node &rootNode}
%lex-param   {forec::loader::Scanner &scanner}

%code requires {
	#include <string>

	#include "ast/AbortStatement.hpp"
	#include "ast/AbstractDeclarator.hpp"
	#include "ast/ArgumentExpressionList.hpp"
	#include "ast/AssignmentExpression.hpp"
	#include "ast/AssignmentOperator.hpp"
	#include "ast/BinaryExpression.hpp"
	#include "ast/BlockItemList.hpp"
	#include "ast/CastExpression.hpp"
	#include "ast/CombineSpecifier.hpp"
	#include "ast/CompoundStatement.hpp"
	#include "ast/Declaration.hpp"
	#include "ast/DeclarationList.hpp"
	#include "ast/DeclarationSpecifiers.hpp"
	#include "ast/Declarator.hpp"
	#include "ast/Designation.hpp"
	#include "ast/Designator.hpp"
	#include "ast/DesignatorList.hpp"
	#include "ast/DirectAbstractDeclarator.hpp"
	#include "ast/DirectDeclarator.hpp"
	#include "ast/EnumSpecifier.hpp"
	#include "ast/Enumerator.hpp"
	#include "ast/EnumeratorList.hpp"
	#include "ast/Expression.hpp"
	#include "ast/ExpressionStatement.hpp"
	#include "ast/FunctionDefinition.hpp"
	#include "ast/FunctionSpecifier.hpp"
	#include "ast/IdentifierList.hpp"
	#include "ast/InitDeclaratorList.hpp"
	#include "ast/Initializer.hpp"
	#include "ast/InitializerList.hpp"
	#include "ast/IterationStatement.hpp"
	#include "ast/JumpStatement.hpp"
	#include "ast/LabeledStatement.hpp"
	#include "ast/Node.hpp"
	#include "ast/NodeList.hpp"
	#include "ast/ParStatement.hpp"
	#include "ast/ParameterDeclaration.hpp"
	#include "ast/ParameterList.hpp"
	#include "ast/ParameterTypeList.hpp"
	#include "ast/PauseStatement.hpp"
	#include "ast/Pointer.hpp"
	#include "ast/PostfixExpression.hpp"
	#include "ast/PreProcessorDirective.hpp"
	#include "ast/PrimaryExpression.hpp"
	#include "ast/Root.hpp"
	#include "ast/SelectionStatement.hpp"
	#include "ast/SpecifierQualifierList.hpp"
	#include "ast/StorageClassSpecifier.hpp"
	#include "ast/StructDeclaration.hpp"
	#include "ast/StructDeclarationList.hpp"
	#include "ast/StructDeclarator.hpp"
	#include "ast/StructDeclaratorList.hpp"
	#include "ast/StructUnionSpecifier.hpp"
	#include "ast/TernaryExpression.hpp"
	#include "ast/ThreadDefinition.hpp"
	#include "ast/TypeName.hpp"
	#include "ast/TypeQualifier.hpp"
	#include "ast/TypeQualifierList.hpp"
	#include "ast/TypeSpecifier.hpp"
	#include "ast/UnaryExpression.hpp"


	
	namespace forec {
		namespace loader {
			// Forward-declare the Scanner class; the Parser needs to be assigned a 
			// Scanner, but the Scanner can't be declared without the Parser
			class Scanner;
		}
	}
}

%union {
	forec::ast::Node *node;
	forec::ast::NodeList *nodeList;
	std::string *str;
}

%code {
	// Prototype for the yylex function
	static int yylex(forec::loader::Parser::semantic_type * yylval, forec::loader::Parser::location_type * yylloc, forec::loader::Scanner &scanner);
}

%token <str> INCLUDE DEFINE

%token <str> IDENTIFIER CONSTANT STRING_LITERAL 
%token SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN 
%token <str> TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER INLINE RESTRICT
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token BOOL COMPLEX IMAGINARY
%token STRUCT UNION ENUM ELLIPSIS
%token <str> TRUE FALSE

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token COMBINE WITH SHARED INPUT OUTPUT PAUSE PAR WEAK IMMEDIATE ABORT WHEN THREAD 
%token CS_NONE CS_START CS_END


%type <node>		preprocessor_directives
%type <node>		primary_expression postfix_expression
%type <nodeList>	argument_expression_list
%type <node>		unary_expression
%type <str>			unary_operator
%type <node>		cast_expression
%type <node>		multiplicative_expression additive_expression
%type <node>		shift_expression
%type <node>		relational_expression equality_expression
%type <node>		and_expression
%type <node>		exclusive_or_expression inclusive_or_expression
%type <node>		logical_and_expression logical_or_expression
%type <node>		conditional_expression
%type <node>		assignment_expression
%type <node>		assignment_operator
%type <nodeList>	expression
%type <node>		constant_expression

%type <node>		declaration
%type <nodeList>	declaration_specifiers
%type <nodeList>	init_declarator_list
%type <node>		init_declarator
%type <node>		storage_class_specifier type_specifier
%type <node>		struct_or_union_specifier
%type <str>			struct_or_union
%type <nodeList>	struct_declaration_list
%type <node>		struct_declaration
%type <nodeList>	specifier_qualifier_list
%type <nodeList>	struct_declarator_list
%type <node>		struct_declarator
%type <node>		enum_specifier
%type <nodeList>	enumerator_list
%type <node>		enumerator
%type <node>		type_qualifier
%type <node>		combine_specifier
%type <node>		function_specifier

%type <node>		declarator direct_declarator
%type <node>		pointer
%type <nodeList>	type_qualifier_list
%type <node>		parameter_type_list
%type <nodeList>	parameter_list
%type <node>		parameter_declaration
%type <nodeList>	identifier_list
%type <node>		type_name
%type <node>		abstract_declarator direct_abstract_declarator

%type <node>		initializer initializer_list
%type <node>		designation
%type <nodeList>	designator_list
%type <node>		designator

%type <node>		statement
%type <node>		labeled_statement compound_statement
%type <nodeList>	block_item_list
%type <node>		block_item
%type <node>		expression_statement selection_statement iteration_statement jump_statement
%type <node>		pause_statement par_statement abort_statement

%type <node>		translation_unit
%type <node>		external_declaration
%type <node>		function_definition thread_definition
%type <nodeList>	declaration_list


%start translation_unit

%%

preprocessor_directives
	: INCLUDE												{ $$ = new forec::ast::PreProcessorDirective(*$1, "include"); }
	| DEFINE												{ $$ = new forec::ast::PreProcessorDirective(*$1, "define"); }
	;

primary_expression
	: IDENTIFIER											{ $$ = new forec::ast::PrimaryExpression(*$1, @1.begin.line, "identifier"); }
	| CONSTANT												{ $$ = new forec::ast::PrimaryExpression(*$1, "terminal"); }
	| STRING_LITERAL										{ $$ = new forec::ast::PrimaryExpression(*$1, "terminal"); }
	| TRUE													{ $$ = new forec::ast::PrimaryExpression(*$1, "terminal"); }
	| FALSE													{ $$ = new forec::ast::PrimaryExpression(*$1, "terminal"); }
	| '(' expression ')'									{ $$ = new forec::ast::PrimaryExpression(*$2, "expression"); }
	;

postfix_expression
	: primary_expression									{ $$ = $1; }
	| postfix_expression '[' expression ']'					{ $$ = new forec::ast::PostfixExpression(*$1, *$3, "index"); }
	| postfix_expression '(' ')'							{ $$ = new forec::ast::PostfixExpression(*$1, "function0"); }
	| postfix_expression '(' argument_expression_list ')'	{ $$ = new forec::ast::PostfixExpression(*$1, *$3, "function1"); }
	| postfix_expression '.' IDENTIFIER						{ $$ = new forec::ast::PostfixExpression(*$1, *(new forec::ast::PrimaryExpression(*$3, @3.begin.line, "identifier")), "member"); }
	| postfix_expression PTR_OP IDENTIFIER					{ $$ = new forec::ast::PostfixExpression(*$1, *(new forec::ast::PrimaryExpression(*$3, @3.begin.line, "identifier")), "pointer"); }
	| postfix_expression INC_OP								{ $$ = new forec::ast::PostfixExpression(*$1, "increment"); }
	| postfix_expression DEC_OP								{ $$ = new forec::ast::PostfixExpression(*$1, "decrement"); }
	| '(' type_name ')' '{' initializer_list '}'			{ $$ = new forec::ast::PostfixExpression(*$2, *$5, "cast0"); }
	| '(' type_name ')' '{' initializer_list ',' '}'		{ $$ = new forec::ast::PostfixExpression(*$2, *$5, "cast1"); }
	;

argument_expression_list
	: assignment_expression									{ $$ = new forec::ast::ArgumentExpressionList(*$1); }
	| argument_expression_list ',' assignment_expression	{ $$ = $1; $$->append(*$3); }
	;

unary_expression
	: postfix_expression									{ $$ = $1; }
	| INC_OP unary_expression								{ $$ = new forec::ast::UnaryExpression(*$2, "increment"); }
	| DEC_OP unary_expression								{ $$ = new forec::ast::UnaryExpression(*$2, "decrement"); }
	| unary_operator cast_expression						{ $$ = new forec::ast::UnaryExpression(*$1, *$2, "cast"); }
	| SIZEOF unary_expression								{ $$ = new forec::ast::UnaryExpression(*$2, "sizeof0"); }
	| SIZEOF '(' type_name ')'								{ $$ = new forec::ast::UnaryExpression(*$3, "sizeof1"); }
	;

unary_operator
	: '&'													{ $$ = new std::string("&"); }
	| '*'													{ $$ = new std::string("*"); }
	| '+'													{ $$ = new std::string("+"); }
	| '-'													{ $$ = new std::string("-"); }
	| '~'													{ $$ = new std::string("~"); }
	| '!'													{ $$ = new std::string("!"); }
	;

cast_expression
	: unary_expression										{ $$ = new forec::ast::CastExpression(*$1); }
	| '(' type_name ')' cast_expression						{ $$ = $4; $$->prepend(*$2); }
	;

multiplicative_expression
	: cast_expression										{ $$ = new forec::ast::BinaryExpression(*$1, "cast"); }
	| multiplicative_expression '*' cast_expression			{ $$ = new forec::ast::BinaryExpression(*$1, *$3, "*"); }
	| multiplicative_expression '/' cast_expression			{ $$ = new forec::ast::BinaryExpression(*$1, *$3, "/"); }
	| multiplicative_expression '%' cast_expression			{ $$ = new forec::ast::BinaryExpression(*$1, *$3, "%"); }
	;

additive_expression
	: multiplicative_expression								{ $$ = new forec::ast::BinaryExpression(*$1, "multiplicative"); }
	| additive_expression '+' multiplicative_expression		{ $$ = new forec::ast::BinaryExpression(*$1, *$3, " + "); }
	| additive_expression '-' multiplicative_expression		{ $$ = new forec::ast::BinaryExpression(*$1, *$3, " - "); }
	;

shift_expression
	: additive_expression									{ $$ = new forec::ast::BinaryExpression(*$1, "additive"); }
	| shift_expression LEFT_OP additive_expression			{ $$ = new forec::ast::BinaryExpression(*$1, *$3, " << "); }
	| shift_expression RIGHT_OP additive_expression			{ $$ = new forec::ast::BinaryExpression(*$1, *$3, " >> "); }
	;

relational_expression
	: shift_expression										{ $$ = new forec::ast::BinaryExpression(*$1, "shift"); }
	| relational_expression '<' shift_expression			{ $$ = new forec::ast::BinaryExpression(*$1, *$3, " < "); }
	| relational_expression '>' shift_expression			{ $$ = new forec::ast::BinaryExpression(*$1, *$3, " > "); }
	| relational_expression LE_OP shift_expression			{ $$ = new forec::ast::BinaryExpression(*$1, *$3, " <= "); }
	| relational_expression GE_OP shift_expression			{ $$ = new forec::ast::BinaryExpression(*$1, *$3, " >= "); }
	;

equality_expression
	: relational_expression									{ $$ = new forec::ast::BinaryExpression(*$1, "relational"); }
	| equality_expression EQ_OP relational_expression		{ $$ = new forec::ast::BinaryExpression(*$1, *$3, " == "); }
	| equality_expression NE_OP relational_expression		{ $$ = new forec::ast::BinaryExpression(*$1, *$3, " != "); }
	;

and_expression
	: equality_expression									{ $$ = new forec::ast::BinaryExpression(*$1, "equality"); }
	| and_expression '&' equality_expression				{ $$ = new forec::ast::BinaryExpression(*$1, *$3, " & "); }
	;

exclusive_or_expression
	: and_expression										{ $$ = new forec::ast::BinaryExpression(*$1, "and"); }
	| exclusive_or_expression '^' and_expression			{ $$ = new forec::ast::BinaryExpression(*$1, *$3, " ^ "); }
	;

inclusive_or_expression
	: exclusive_or_expression								{ $$ = new forec::ast::BinaryExpression(*$1, "exclusiveOr"); }
	| inclusive_or_expression '|' exclusive_or_expression	{ $$ = new forec::ast::BinaryExpression(*$1, *$3, " | "); }
	;

logical_and_expression
	: inclusive_or_expression								{ $$ = new forec::ast::BinaryExpression(*$1, "inclusiveOr"); }
	| logical_and_expression AND_OP inclusive_or_expression	{ $$ = new forec::ast::BinaryExpression(*$1, *$3, " && "); }
	;

logical_or_expression
	: logical_and_expression								{ $$ = new forec::ast::BinaryExpression(*$1, "logicalAnd"); }
	| logical_or_expression OR_OP logical_and_expression	{ $$ = new forec::ast::BinaryExpression(*$1, *$3, " || "); }
	;

conditional_expression
	: logical_or_expression												{ $$ = new forec::ast::TernaryExpression(*$1, "logicalOr"); }
	| logical_or_expression '?' expression ':' conditional_expression	{ $$ = new forec::ast::TernaryExpression(*$1, *$3, *$5); }
	;

assignment_expression
	: conditional_expression											{ $$ = new forec::ast::AssignmentExpression(*$1, "conditional"); }
	| unary_expression assignment_operator assignment_expression		{ $$ = new forec::ast::AssignmentExpression(*$1, *$2, *$3); }
	;

assignment_operator
	: '='													{ $$ = new forec::ast::AssignmentOperator("="); }
	| MUL_ASSIGN											{ $$ = new forec::ast::AssignmentOperator("*="); }
	| DIV_ASSIGN											{ $$ = new forec::ast::AssignmentOperator("/="); }
	| MOD_ASSIGN											{ $$ = new forec::ast::AssignmentOperator("%="); }
	| ADD_ASSIGN											{ $$ = new forec::ast::AssignmentOperator("+="); }
	| SUB_ASSIGN											{ $$ = new forec::ast::AssignmentOperator("-="); }
	| LEFT_ASSIGN											{ $$ = new forec::ast::AssignmentOperator("<<="); }
	| RIGHT_ASSIGN											{ $$ = new forec::ast::AssignmentOperator(">>="); }
	| AND_ASSIGN											{ $$ = new forec::ast::AssignmentOperator("&="); }
	| XOR_ASSIGN											{ $$ = new forec::ast::AssignmentOperator("^="); }
	| OR_ASSIGN												{ $$ = new forec::ast::AssignmentOperator("|="); }
	;

expression
	: assignment_expression									{ $$ = new forec::ast::Expression(*$1); }
	| expression ',' assignment_expression					{ $$ = $1; $$->append(*$3); }
	;

constant_expression
	: conditional_expression								{ $$ = $1; }
	;





declaration
	: declaration_specifiers ';'							{ $$ = new forec::ast::Declaration(*$1, "declaration"); }
	| declaration_specifiers init_declarator_list ';'		{ $$ = new forec::ast::Declaration(*$1, *$2, "initDeclaration"); }
	| THREAD init_declarator_list ';'						{ $$ = new forec::ast::Declaration(*$2, "threadDeclaration"); }
	;

declaration_specifiers
	: storage_class_specifier								{ $$ = new forec::ast::DeclarationSpecifiers(*$1, "storageClassSpecifier"); }
	| storage_class_specifier declaration_specifiers		{ $$ = $2; $2->prepend(*$1); }
	| type_specifier										{ $$ = new forec::ast::DeclarationSpecifiers(*$1, "typeSpecifier"); }
	| type_specifier declaration_specifiers					{ $$ = $2; $2->prepend(*$1); }
	| type_qualifier										{ $$ = new forec::ast::DeclarationSpecifiers(*$1, "typeQualifier"); }
	| type_qualifier declaration_specifiers					{ $$ = $2; $2->prepend(*$1); }
	| function_specifier									{ $$ = new forec::ast::DeclarationSpecifiers(*$1, "functionSpecifier"); }
	| function_specifier declaration_specifiers				{ $$ = $2; $2->prepend(*$1); }
	;

init_declarator_list
	: init_declarator										{ $$ = new forec::ast::InitDeclaratorList(*$1); }
	| init_declarator_list ',' init_declarator				{ $$ = $1; $1->append(*$3); }
	;

init_declarator
	: declarator											{ $$ = new forec::ast::BinaryExpression(*$1, "declarator"); }
	| declarator combine_specifier							{ $$ = new forec::ast::BinaryExpression(*$1, *$2, "declarator"); }
	| declarator '=' initializer							{ $$ = new forec::ast::BinaryExpression(*(new forec::ast::BinaryExpression(*$1, "declarator")), *$3, " = "); }
	| declarator '=' initializer combine_specifier			{ $$ = new forec::ast::BinaryExpression(*(new forec::ast::BinaryExpression(*$1, "declarator")), *$3, *$4, " = "); }
	;

storage_class_specifier
	: TYPEDEF												{ $$ = new forec::ast::StorageClassSpecifier("typedef"); }
	| EXTERN												{ $$ = new forec::ast::StorageClassSpecifier("extern"); }
	| STATIC												{ $$ = new forec::ast::StorageClassSpecifier("static"); }
	| AUTO													{ $$ = new forec::ast::StorageClassSpecifier("auto"); }
	| REGISTER												{ $$ = new forec::ast::StorageClassSpecifier("register"); }
	;

type_specifier
	: VOID													{ $$ = new forec::ast::TypeSpecifier("void"); }
	| CHAR													{ $$ = new forec::ast::TypeSpecifier("char"); }
	| SHORT													{ $$ = new forec::ast::TypeSpecifier("short"); }
	| INT													{ $$ = new forec::ast::TypeSpecifier("int"); }
	| LONG													{ $$ = new forec::ast::TypeSpecifier("long"); }
	| FLOAT													{ $$ = new forec::ast::TypeSpecifier("float"); }
	| DOUBLE												{ $$ = new forec::ast::TypeSpecifier("double"); }
	| SIGNED												{ $$ = new forec::ast::TypeSpecifier("signed"); }
	| UNSIGNED												{ $$ = new forec::ast::TypeSpecifier("unsigned"); }
	| BOOL													{ $$ = new forec::ast::TypeSpecifier("_Bool"); }
	| COMPLEX												{ $$ = new forec::ast::TypeSpecifier("_Complex"); }
	| IMAGINARY												{ $$ = new forec::ast::TypeSpecifier("_Imaginary"); }
	| struct_or_union_specifier								{ $$ = $1; }
	| enum_specifier										{ $$ = $1; }
	| TYPE_NAME												{ $$ = new forec::ast::TypeSpecifier(*(new forec::ast::PrimaryExpression(*$1, @1.begin.line, "identifier")), "typedef"); }
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'	{ $$ = new forec::ast::StructUnionSpecifier(*$1, *(new forec::ast::PrimaryExpression(*$2, @2.begin.line, "identifier")), *$4, "definition"); }
	| struct_or_union '{' struct_declaration_list '}'				{ $$ = new forec::ast::StructUnionSpecifier(*$1, *$3, "anonymous"); }
	| struct_or_union IDENTIFIER									{ $$ = new forec::ast::StructUnionSpecifier(*$1, *(new forec::ast::PrimaryExpression(*$2, @2.begin.line, "identifier")), "declaration"); }
	;

struct_or_union
	: STRUCT												{ $$ = new std::string("struct"); }
	| UNION													{ $$ = new std::string("union"); }
	;

struct_declaration_list
	: struct_declaration									{ $$ = new forec::ast::StructDeclarationList(*$1); }
	| struct_declaration_list struct_declaration			{ $$ = $1; $$->append(*$2); }
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'	{ $$ = new forec::ast::StructDeclaration(*$1, *$2); }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list				{ $$ = $2; $2->prepend(*$1); }
	| type_specifier										{ $$ = new forec::ast::SpecifierQualifierList(*$1, "typeSpecifier"); }
	| type_qualifier specifier_qualifier_list				{ $$ = $2; $2->prepend(*$1); }
	| type_qualifier										{ $$ = new forec::ast::SpecifierQualifierList(*$1, "typeQualifier"); }
	;

struct_declarator_list
	: struct_declarator										{ $$ = new forec::ast::StructDeclaratorList(*$1); }
	| struct_declarator_list ',' struct_declarator			{ $$ = $1; $$->append(*$3); }
	;

struct_declarator
	: declarator											{ $$ = $1; }
	| ':' constant_expression								{ $$ = new forec::ast::StructDeclarator(*$2, "constantExpression"); }
	| declarator ':' constant_expression					{ $$ = new forec::ast::StructDeclarator(*$1, *$3, "full"); }
	;

enum_specifier
	: ENUM '{' enumerator_list '}'							{ $$ = new forec::ast::EnumSpecifier(*$3, "anonymous0"); }
	| ENUM IDENTIFIER '{' enumerator_list '}'				{ $$ = new forec::ast::EnumSpecifier(*(new forec::ast::PrimaryExpression(*$2, @2.begin.line, "identifier")), *$4, "definition0"); }
	| ENUM '{' enumerator_list ',' '}'						{ $$ = new forec::ast::EnumSpecifier(*$3, "anonymous1"); }
	| ENUM IDENTIFIER '{' enumerator_list ',' '}'			{ $$ = new forec::ast::EnumSpecifier(*(new forec::ast::PrimaryExpression(*$2, @2.begin.line, "identifier")), *$4, "definition1"); }
	| ENUM IDENTIFIER										{ $$ = new forec::ast::EnumSpecifier(*(new forec::ast::PrimaryExpression(*$2, @2.begin.line, "identifier")), "declaration"); }
	;

enumerator_list
	: enumerator											{ $$ = new forec::ast::EnumeratorList(*$1); }
	| enumerator_list ',' enumerator						{ $$ = $1; $$->append(*$3); }
	;

enumerator
	: IDENTIFIER											{ $$ = new forec::ast::PrimaryExpression(*$1, @1.begin.line, "identifier"); }
	| IDENTIFIER '=' constant_expression					{ $$ = new forec::ast::Enumerator(*(new forec::ast::PrimaryExpression(*$1, @1.begin.line, "identifier")), *$3); }
	;

type_qualifier
	: CONST													{ $$ = new forec::ast::TypeQualifier("const"); }
	| RESTRICT												{ $$ = new forec::ast::TypeQualifier("restrict"); }
	| VOLATILE												{ $$ = new forec::ast::TypeQualifier("volatile"); }
	| INPUT													{ $$ = new forec::ast::TypeQualifier("input"); }
	| OUTPUT												{ $$ = new forec::ast::TypeQualifier("output"); }
	| SHARED												{ $$ = new forec::ast::TypeQualifier("shared"); }
	;

combine_specifier
	: COMBINE WITH IDENTIFIER								{ $$ = new forec::ast::CombineSpecifier(*$3); }
	;

function_specifier
	: INLINE												{ $$ = new forec::ast::FunctionSpecifier("inline"); }
	;




declarator
	: pointer direct_declarator								{ $$ = new forec::ast::Declarator(*$1, *$2); }
	| direct_declarator										{ $$ = $1; }
	;


direct_declarator
	: IDENTIFIER																	{ $$ = new forec::ast::DirectDeclarator(*(new forec::ast::PrimaryExpression(*$1, @1.begin.line, "identifier")), "identifier"); }
	| '(' declarator ')'															{ $$ = new forec::ast::DirectDeclarator(*$2, "cast"); }
	| direct_declarator '[' type_qualifier_list assignment_expression ']'			{ $$ = new forec::ast::DirectDeclarator(*$1, *$3, *$4, "array0"); }
	| direct_declarator '[' type_qualifier_list ']'									{ $$ = new forec::ast::DirectDeclarator(*$1, *$3, "array1"); }
	| direct_declarator '[' assignment_expression ']'								{ $$ = new forec::ast::DirectDeclarator(*$1, *$3, "array2"); }
	| direct_declarator '[' STATIC type_qualifier_list assignment_expression ']'	{ $$ = new forec::ast::DirectDeclarator(*$1, *$4, *$5, "array3"); }
	| direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'	{ $$ = new forec::ast::DirectDeclarator(*$1, *$3, *$5, "array4"); }
	| direct_declarator '[' type_qualifier_list '*' ']'								{ $$ = new forec::ast::DirectDeclarator(*$1, *$3, "array5"); }
	| direct_declarator '[' '*' ']'													{ $$ = new forec::ast::DirectDeclarator(*$1, "array6"); }
	| direct_declarator '[' ']'														{ $$ = new forec::ast::DirectDeclarator(*$1, "array7"); }
	| direct_declarator '(' parameter_type_list ')'									{ $$ = new forec::ast::DirectDeclarator(*$1, *$3, "function0"); }
	| direct_declarator '(' identifier_list ')'										{ $$ = new forec::ast::DirectDeclarator(*$1, *$3, "function1"); }
	| direct_declarator '(' ')'														{ $$ = new forec::ast::DirectDeclarator(*$1, "function2"); }
	;

pointer
	: '*'													{ $$ = new forec::ast::Pointer("asterisk"); }
	| '*' type_qualifier_list								{ $$ = new forec::ast::Pointer(*$2, "typeQualifier"); }
	| '*' pointer											{ $$ = new forec::ast::Pointer(*$2, "pointer"); }
	| '*' type_qualifier_list pointer						{ $$ = new forec::ast::Pointer(*$2, *$3, "typeQualifierPointer"); }
	;

type_qualifier_list
	: type_qualifier										{ $$ = new forec::ast::TypeQualifierList(*$1); }
	| type_qualifier_list type_qualifier					{ $$ = $1; $$->append(*$2); }
	;


parameter_type_list
	: parameter_list										{ $$ = $1; }
	| parameter_list ',' ELLIPSIS							{ $$ = new forec::ast::ParameterTypeList(*$1, "unbounded"); }
	;

parameter_list
	: parameter_declaration									{ $$ = new forec::ast::ParameterList(*$1); }
	| parameter_list ',' parameter_declaration				{ $$ = $1; $$->append(*$3); }
	;

parameter_declaration
	: declaration_specifiers declarator						{ $$ = new forec::ast::ParameterDeclaration(*$1, *$2); }
	| declaration_specifiers abstract_declarator			{ $$ = new forec::ast::ParameterDeclaration(*$1, *$2); }
	| declaration_specifiers								{ $$ = $1; }
	;

identifier_list
	: IDENTIFIER											{ $$ = new forec::ast::IdentifierList(*(new forec::ast::PrimaryExpression(*$1, @1.begin.line, "identifier"))); }
	| identifier_list ',' IDENTIFIER						{ $$ = $1; $$->append(*(new forec::ast::PrimaryExpression(*$3, @3.begin.line, "identifier"))); }
	;

type_name
	: specifier_qualifier_list								{ $$ = new forec::ast::TypeName(*$1); }
	| specifier_qualifier_list abstract_declarator			{ $$ = new forec::ast::TypeName(*$1, *$2); }
	;

abstract_declarator
	: pointer												{ $$ = $1; }
	| direct_abstract_declarator							{ $$ = $1; }
	| pointer direct_abstract_declarator					{ $$ = new forec::ast::AbstractDeclarator(*$1, *$2); }
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'								{ $$ = new forec::ast::DirectAbstractDeclarator(*$2, "cast"); }
	| '[' ']'													{ $$ = new forec::ast::DirectAbstractDeclarator("index0"); }
	| '[' assignment_expression ']'								{ $$ = new forec::ast::DirectAbstractDeclarator(*$2, "index1"); }
	| direct_abstract_declarator '[' ']'						{ $$ = new forec::ast::DirectAbstractDeclarator(*$1, "array0"); }
	| direct_abstract_declarator '[' assignment_expression ']'	{ $$ = new forec::ast::DirectAbstractDeclarator(*$1, *$3, "array1"); }
	| '[' '*' ']'												{ $$ = new forec::ast::DirectAbstractDeclarator("array2"); }
	| direct_abstract_declarator '[' '*' ']'					{ $$ = new forec::ast::DirectAbstractDeclarator(*$1, "index2"); }
	| '(' ')'													{ $$ = new forec::ast::DirectAbstractDeclarator("function0"); }
	| '(' parameter_type_list ')'								{ $$ = new forec::ast::DirectAbstractDeclarator(*$2, "function1"); }
	| direct_abstract_declarator '(' ')'						{ $$ = new forec::ast::DirectAbstractDeclarator(*$1, "function2"); }
	| direct_abstract_declarator '(' parameter_type_list ')'	{ $$ = new forec::ast::DirectAbstractDeclarator(*$1, *$3, "function3"); }
	;

initializer
	: assignment_expression									{ $$ = $1; }
	| '{' initializer_list '}'								{ $$ = new forec::ast::Initializer(*$2, "initializerList0"); }
	| '{' initializer_list ',' '}'							{ $$ = new forec::ast::Initializer(*$2, "initializerList1"); }
	;

initializer_list
	: initializer											{ $$ = $1; }
	| designation initializer								{ $$ = new forec::ast::InitializerList(*$1, *$2, "designation"); }
	| initializer_list ',' initializer						{ $$ = new forec::ast::InitializerList(*$1, *$3, "initializer"); }
	| initializer_list ',' designation initializer			{ $$ = new forec::ast::InitializerList(*$1, *$3, *$4, "designationInitalizer"); }
	;

designation
	: designator_list '='									{ $$ = new forec::ast::Designation(*$1); }
	;

designator_list
	: designator											{ $$ = new forec::ast::DesignatorList(*$1); }
	| designator_list designator							{ $$ = $1; $$->append(*$2); }
	;

designator
	: '[' constant_expression ']'							{ $$ = new forec::ast::Designator(*$2, "index"); }
	| '.' IDENTIFIER										{ $$ = new forec::ast::Designator(*(new forec::ast::PrimaryExpression(*$2, @2.begin.line, "identifier")), "member"); }
	;

statement
	: labeled_statement										{ $$ = $1; }
	| compound_statement									{ $$ = $1; }
	| expression_statement									{ $$ = $1; }
	| selection_statement									{ $$ = $1; }
	| iteration_statement									{ $$ = $1; }
	| jump_statement										{ $$ = $1; }
	| pause_statement										{ $$ = $1; }
	| par_statement											{ $$ = $1; }
	| abort_statement										{ $$ = $1; }
	;

labeled_statement
	: IDENTIFIER ':' statement								{ $$ = new forec::ast::LabeledStatement(*(new forec::ast::PrimaryExpression(*$1, @1.begin.line, "identifier")), *$3, "label"); }
	| CASE constant_expression ':' statement				{ $$ = new forec::ast::LabeledStatement(*$2, *$4, "case"); }
	| DEFAULT ':' statement									{ $$ = new forec::ast::LabeledStatement(*$3, "default"); }
	;

compound_statement
	: '{' '}'												{ $$ = new forec::ast::CompoundStatement(); }
	| '{' block_item_list '}'								{ $$ = new forec::ast::CompoundStatement(*$2); }
	;

block_item_list
	: block_item											{ $$ = new forec::ast::BlockItemList(*$1); }
	| block_item_list block_item							{ $$ = $1; $$->append(*$2); }
	;

block_item
	: declaration											{ $$ = $1; }
	| statement												{ $$ = $1; }
	| preprocessor_directives								{ $$ = $1; }
	;

expression_statement
	: ';'													{ $$ = new forec::ast::ExpressionStatement(); }	
	| expression ';'										{ $$ = new forec::ast::ExpressionStatement(*$1); }
	;

selection_statement
	: IF '(' expression ')' statement						{ $$ = new forec::ast::SelectionStatement(*$3, *$5, "if"); }
	| IF '(' expression ')' statement ELSE statement		{ $$ = new forec::ast::SelectionStatement(*$3, *$5, *$7, "ifElse"); }
	| SWITCH '(' expression ')' statement					{ $$ = new forec::ast::SelectionStatement(*$3, *$5, "switch"); }
	;

iteration_statement
	: WHILE '(' expression ')' statement											{ $$ = new forec::ast::IterationStatement(@1.begin.line, *$3, *$5, "while"); }
	| DO statement WHILE '(' expression ')' ';'										{ $$ = new forec::ast::IterationStatement(@1.begin.line, *$2, *$5, "doWhile"); }
	| FOR '(' expression_statement expression_statement ')' statement				{ $$ = new forec::ast::IterationStatement(@1.begin.line, *$3, *$4, *$6, "for0"); }
	| FOR '(' expression_statement expression_statement expression ')' statement	{ $$ = new forec::ast::IterationStatement(@1.begin.line, *$3, *$4, *$5, *$7, "for1"); }
	| FOR '(' declaration expression_statement ')' statement						{ $$ = new forec::ast::IterationStatement(@1.begin.line, *$3, *$4, *$6, "for2"); }
	| FOR '(' declaration expression_statement expression ')' statement				{ $$ = new forec::ast::IterationStatement(@1.begin.line, *$3, *$4, *$5, *$7, "for3"); }
	| WHILE '(' expression ')' '#' CONSTANT '#' CONSTANT statement											{ $$ = new forec::ast::IterationStatement(@1.begin.line, *$3, *$6, *$8, *$9, "while"); }
	| DO statement WHILE '(' expression ')' '#' CONSTANT '#' CONSTANT ';'									{ $$ = new forec::ast::IterationStatement(@1.begin.line, *$2, *$5, *$8, *$10, "doWhile"); }
	| FOR '(' expression_statement expression_statement ')' '#' CONSTANT '#' CONSTANT statement				{ $$ = new forec::ast::IterationStatement(@1.begin.line, *$3, *$4, *$7, *$9, *$10, "for0"); }
	| FOR '(' expression_statement expression_statement expression ')' '#' CONSTANT '#' CONSTANT statement	{ $$ = new forec::ast::IterationStatement(@1.begin.line, *$3, *$4, *$5, *$8, *$10, *$11, "for1"); }
	| FOR '(' declaration expression_statement ')' '#' CONSTANT '#' CONSTANT statement						{ $$ = new forec::ast::IterationStatement(@1.begin.line, *$3, *$4, *$7, *$9, *$10, "for2"); }
	| FOR '(' declaration expression_statement expression ')' '#' CONSTANT '#' CONSTANT statement			{ $$ = new forec::ast::IterationStatement(@1.begin.line, *$3, *$4, *$5, *$8, *$10, *$11, "for3"); }
	;


jump_statement
	: GOTO IDENTIFIER ';'									{ $$ = new forec::ast::JumpStatement(*(new forec::ast::PrimaryExpression(*$2, @2.begin.line, "identifier")), "goto"); }
	| CONTINUE ';'											{ $$ = new forec::ast::JumpStatement("continue"); }
	| BREAK ';'												{ $$ = new forec::ast::JumpStatement("break"); }
	| RETURN ';'											{ $$ = new forec::ast::JumpStatement("return"); }
	| RETURN expression ';'									{ $$ = new forec::ast::JumpStatement(*$2, "returnExpression"); }
	;

pause_statement
	: PAUSE ';'												{ $$ = new forec::ast::PauseStatement(); }
	;

par_statement
	: PAR '(' identifier_list ')' ';'						{ $$ = new forec::ast::ParStatement(*$3); }
	;
	
abort_statement
	: WEAK ABORT compound_statement WHEN '(' expression ')' ';'				{ $$ = new forec::ast::AbortStatement(*$3, *$6, "weakNonImmediate"); }
	| ABORT compound_statement WHEN '(' expression ')' ';'					{ $$ = new forec::ast::AbortStatement(*$2, *$5, "strongNonImmediate"); }
	| WEAK ABORT compound_statement WHEN IMMEDIATE '(' expression ')' ';'	{ $$ = new forec::ast::AbortStatement(*$3, *$7, "weakImmediate"); }
	| ABORT compound_statement WHEN IMMEDIATE '(' expression ')' ';'		{ $$ = new forec::ast::AbortStatement(*$2, *$6, "strongImmediate"); }
	;

translation_unit
	: external_declaration									{ rootNode.append(*$1); }
	| translation_unit external_declaration					{ rootNode.append(*$2); }
	;

external_declaration
	: preprocessor_directives								{ $$ = $1; }
	| function_definition									{ $$ = $1; }
	| thread_definition										{ $$ = $1; }
	| declaration											{ $$ = $1; }
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement	{ $$ = new forec::ast::FunctionDefinition(*$1, *$2, *$3, *$4); }
	| declaration_specifiers declarator compound_statement					{ $$ = new forec::ast::FunctionDefinition(*$1, *$2, *$3); }
	;

thread_definition
	: THREAD declarator compound_statement					{ $$ = new forec::ast::ThreadDefinition(*$2, *$3); }
	;

declaration_list
	: declaration											{ $$ = new forec::ast::DeclarationList(*$1); }
	| declaration_list declaration							{ $$ = $1; $$->append(*$2); }
	;

	
%%

// Now that we have the Parser declared, we can declare the Scanner and implement
// the yylex function
#include "Scanner.hpp"
static int yylex(forec::loader::Parser::semantic_type * yylval, forec::loader::Parser::location_type * yylloc, forec::loader::Scanner &scanner) {
	return scanner.yylex(yylval, yylloc);
}

