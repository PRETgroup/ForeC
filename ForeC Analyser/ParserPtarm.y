/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */
 
%require "3.6"
%skeleton "lalr1.cc"
%defines
%locations
%define parse.error verbose
%define api.prefix {ptarm}
%define api.namespace {forec::loader}
%define api.parser.class {ParserPtarm}
%parse-param {forec::loader::ScannerPtarm &scanner}
%parse-param {forec::cfg::Node &rootNode}
%lex-param   {forec::loader::ScannerPtarm &scanner}

%code requires {
	#include <string>

	#include "cfg/AbortStatement.hpp"
	#include "cfg/AssemblyInstruction.hpp"
	#include "cfg/AssemblyLine.hpp"
	#include "cfg/Body.hpp"
	#include "cfg/CSourceLine.hpp"
	#include "cfg/IterationBound.hpp"
	#include "cfg/Label.hpp"
	#include "cfg/Node.hpp"
	#include "cfg/NodeList.hpp"
	#include "cfg/Operand.hpp"
	#include "cfg/OperandList.hpp"
	#include "cfg/ParStatement.hpp"
	#include "cfg/PauseStatement.hpp"
	#include "cfg/Root.hpp"
	#include "cfg/Scheduler.hpp"
	#include "cfg/Thread.hpp"

	
	namespace forec {
		namespace loader {
			// Forward-declare the Scanner class; the Parser needs to be assigned a 
			// Scanner, but the Scanner can't be declared without the Parser
			class ScannerPtarm;
		}
	}
}

%union {
	forec::cfg::Node *node;
	forec::cfg::NodeList *nodeList;
	std::string *str;
}

%code {
	// Prototype for the yylex function
	static int yylex(forec::loader::ParserPtarm::semantic_type * yylval, forec::loader::ParserPtarm::location_type * yylloc, forec::loader::ScannerPtarm &scanner);
}

%token <str> REGISTERS_GENERAL REGISTERS_SPECIAL 
%token <str> COPROCESSOR_REGISTERS
%token <str> CONSTANT SHIFTED_OPERAND PC PC_1

%token <str> BRANCH_CONDITIONAL BRANCH_UNCONDITIONAL INTERRUPT
%token <str> LOGIC ARITHMETIC_INTEGER
%token <str> COPROCESSOR READ STORE MOVE

%token <str> LABEL

%token <str> C_SOURCE DATA

%token <str> FOREC_STATEMENT_PAR_START FOREC_STATEMENT_PAR_END FOREC_STATEMENT_ABORT_START FOREC_STATEMENT_ABORT_END
%token <str> FOREC_STATEMENT_ABORT_SCOPE_END FOREC_STATEMENT_PAUSE_START FOREC_STATEMENT_PAUSE_END

%token <str> FOREC_SCHEDULER_COUNTER_START FOREC_SCHEDULER_COUNTER_END
%token <str> FOREC_SCHEDULER_BOOT_START FOREC_SCHEDULER_BOOT_END FOREC_SCHEDULER_REACTION_START_START
%token <str> FOREC_SCHEDULER_REACTION_START_END FOREC_SCHEDULER_REACTION_END_START FOREC_SCHEDULER_REACTION_END_END
%token <str> FOREC_SCHEDULER_PAR_HANDLER_START FOREC_SCHEDULER_PAR_HANDLER_END FOREC_SCHEDULER_ABORT_HANDLER_START
%token <str> FOREC_SCHEDULER_ABORT_HANDLER_END
%token <str> FOREC_SCHEDULER_THREAD_REMOVE_START FOREC_SCHEDULER_THREAD_REMOVE_END
%token <str> FOREC_SCHEDULER_ITERATION_END_START FOREC_SCHEDULER_ITERATION_END_END
%token <str> FOREC_ITERATION_BOUND

%token <str> FOREC_THREAD_START FOREC_THREAD_END

%type <node>		operand
%type <nodeList>	operand_list
%type <node>		assembly_instruction
%type <node>		alt_assembly_line
%type <node>		assembly_line
%type <node>		label
%type <node>		c_source_line
%type <node>		iteration_bound
%type <node>		mixed_source
%type <node>		abort_statement
%type <node>		abort_scope_end
%type <node>		par_statement
%type <node>		pause_statement
%type <node>		forec_statement
%type <node>		forec_scheduler
%type <node>		body_item
%type <nodeList>	body

%type <node>		thread
%type <node>		fragment
%type <node>		translation_unit

%start translation_unit

%%

// C statements
operand
	: REGISTERS_GENERAL					{ $$ = new forec::cfg::Operand(*$1, "generalRegister"); }
	| REGISTERS_SPECIAL					{ $$ = new forec::cfg::Operand(*$1, "specialRegister"); }
	| COPROCESSOR_REGISTERS				{ $$ = new forec::cfg::Operand(*$1, "coprocessorRegister"); }
	| CONSTANT							{ $$ = new forec::cfg::Operand(*$1, "constant"); }
	| SHIFTED_OPERAND					{ $$ = new forec::cfg::Operand(*$1, "shiftedOperand"); }
	| '[' operand ']'					{ $$ = new forec::cfg::Operand(*$2, "address1"); }
	| '[' operand ',' operand ']'		{ $$ = new forec::cfg::Operand(*$2, *$4, "address2"); }
	;

operand_list
	: operand							{ $$ = new forec::cfg::OperandList(*$1); }
	| operand '!'						{ $$ = new forec::cfg::OperandList(*$1); }
	| operand '^'						{ $$ = new forec::cfg::OperandList(*$1); }
	| '{' operand_list '}'				{ $$ = new forec::cfg::OperandList(*$2, "registerList"); }
	| operand_list ',' operand			{ $$ = $1; $$->append(*$3); }
	| operand_list ',' operand '!'		{ $$ = $1; $$->append(*$3); }
	| operand_list ',' operand '^'		{ $$ = $1; $$->append(*$3); }
	| operand_list ',' '{' operand '}'	{ $$ = $1; $$->append(*$4); }
	;

assembly_instruction
	: BRANCH_CONDITIONAL				{ $$ = new forec::cfg::AssemblyInstruction(*$1, "branchConditional"); }
	| BRANCH_UNCONDITIONAL				{ $$ = new forec::cfg::AssemblyInstruction(*$1, "branchUnconditional"); }
	| INTERRUPT							{ $$ = new forec::cfg::AssemblyInstruction(*$1, "interrupt"); }
	| LOGIC								{ $$ = new forec::cfg::AssemblyInstruction(*$1, "logic"); }
	| ARITHMETIC_INTEGER				{ $$ = new forec::cfg::AssemblyInstruction(*$1, "arithmeticInteger"); }
	| READ								{ $$ = new forec::cfg::AssemblyInstruction(*$1, "read"); }
	| STORE								{ $$ = new forec::cfg::AssemblyInstruction(*$1, "store"); }
	| MOVE								{ $$ = new forec::cfg::AssemblyInstruction(*$1, "move"); }
	| COPROCESSOR						{ $$ = new forec::cfg::AssemblyInstruction(*$1, "coprocessor"); }
	| DATA								{ $$ = new forec::cfg::AssemblyInstruction(*$1, "data"); }
	;

alt_assembly_line
	: ';' '(' assembly_instruction operand_list ')'					{ /* Do nothing */ }
	;

assembly_line
	: PC ':' CONSTANT assembly_instruction operand_list								{ $$ = new forec::cfg::AssemblyLine(*$1, *$3, *$4, *$5); }
	| PC ':' CONSTANT assembly_instruction alt_assembly_line						{ $$ = new forec::cfg::AssemblyLine(*$1, *$3, *$4, *(new forec::cfg::OperandList(*(new forec::cfg::Operand(""))))); }
	| PC ':' CONSTANT assembly_instruction operand_list alt_assembly_line			{ $$ = new forec::cfg::AssemblyLine(*$1, *$3, *$4, *$5); }
	| PC ':' CONSTANT assembly_instruction operand_list '<' LABEL '>'				{ $$ = new forec::cfg::AssemblyLine(*$1, *$3, *$4, *$5, "; " + ((forec::cfg::Operand *)(((forec::cfg::OperandList *)$5)->getOperands()[0]))->getValue(), *$7); }
	| PC ':' CONSTANT assembly_instruction operand_list PC_1						{ $$ = new forec::cfg::AssemblyLine(*$1, *$3, *$4, *$5, *$6); }
	| PC ':' CONSTANT assembly_instruction operand_list PC_1 '<' LABEL '>'			{ $$ = new forec::cfg::AssemblyLine(*$1, *$3, *$4, *$5, *$6, *$8); }
	;

label
	: PC '<' LABEL '>' ':'				{ $$ = new forec::cfg::Label(*$1, *$3); }
	;
	
c_source_line
	: C_SOURCE							{ $$ = new forec::cfg::CSourceLine(*$1); }
	;

iteration_bound
	: FOREC_ITERATION_BOUND				{ $$ = new forec::cfg::IterationBound(*$1); }
	;

mixed_source
	: assembly_line						{ $$ = $1; }
	| c_source_line						{ $$ = $1; }
	| iteration_bound					{ $$ = $1; }
	;


// ForeC statements
abort_statement
	: FOREC_STATEMENT_ABORT_START body FOREC_STATEMENT_ABORT_END	{ $$ = new forec::cfg::AbortStatement(*$1, *$2, "statement"); }
	;

abort_scope_end
	: FOREC_STATEMENT_ABORT_SCOPE_END								{ $$ = new forec::cfg::AbortStatement(*$1, "scopeEnd"); }
	;

par_statement
	: FOREC_STATEMENT_PAR_START body FOREC_STATEMENT_PAR_END		{ $$ = new forec::cfg::ParStatement(*$1, *$2); }
	;
	
pause_statement
	: FOREC_STATEMENT_PAUSE_START body FOREC_STATEMENT_PAUSE_END	{ $$ = new forec::cfg::PauseStatement(*$1, *$2); }
	;
	
forec_statement
	: pause_statement					{ $$ = $1; }
	| abort_statement					{ $$ = $1; }
	| abort_scope_end					{ $$ = $1; }
	| par_statement						{ $$ = $1; }
	;
	

// ForeC scheduling
forec_scheduler
	: FOREC_SCHEDULER_COUNTER_START body FOREC_SCHEDULER_COUNTER_END				{ $$ = new forec::cfg::Scheduler(*$1, *$2, "counter");}
	| FOREC_SCHEDULER_BOOT_START body FOREC_SCHEDULER_BOOT_END						{ $$ = new forec::cfg::Scheduler(*$1, *$2, "boot");}
	| FOREC_SCHEDULER_REACTION_START_START body FOREC_SCHEDULER_REACTION_START_END	{ $$ = new forec::cfg::Scheduler(*$1, *$2, "reactionStart");}
	| FOREC_SCHEDULER_REACTION_END_START body FOREC_SCHEDULER_REACTION_END_END		{ $$ = new forec::cfg::Scheduler(*$1, *$2, "reactionEnd");}
	| FOREC_SCHEDULER_PAR_HANDLER_START body FOREC_SCHEDULER_PAR_HANDLER_END		{ $$ = new forec::cfg::Scheduler(*$1, *$2, "parHandler");}
	| FOREC_SCHEDULER_ABORT_HANDLER_START body FOREC_SCHEDULER_ABORT_HANDLER_END	{ $$ = new forec::cfg::Scheduler(*$1, *$2, "abortHandler");}
	| FOREC_SCHEDULER_THREAD_REMOVE_START body FOREC_SCHEDULER_THREAD_REMOVE_END	{ $$ = new forec::cfg::Scheduler(*$1, *$2, "threadRemove");}
	| FOREC_SCHEDULER_ITERATION_END_START body FOREC_SCHEDULER_ITERATION_END_END	{ $$ = new forec::cfg::Scheduler(*$1, *$2, "iterationEnd");}
	;


// Thread body
body_item
	: mixed_source						{ $$ = $1; }
	| forec_statement					{ $$ = $1; }
	| forec_scheduler					{ $$ = $1; }
	;

body
	: body_item							{ $$ = new forec::cfg::Body(*$1); }
	| body body_item					{ $$ = $1; $$->append(*$2); }
	;


// Program
thread
	: FOREC_THREAD_START body FOREC_THREAD_END	{ $$ = new forec::cfg::Thread(*$1, *$2);}
	;


fragment
	: label								{ $$ = $1; }
	| mixed_source						{ $$ = $1; }
	| thread							{ $$ = $1; }
	| forec_scheduler					{ $$ = $1; }
	;
		
translation_unit
	: fragment							{ rootNode.append(*$1); }
	| translation_unit fragment			{ rootNode.append(*$2); }
	;
	
%%


// Now that we have the Parser declared, we can declare the Scanner and implement
// the yylex function
#include "ScannerPtarm.hpp"
static int yylex(forec::loader::ParserPtarm::semantic_type * yylval, forec::loader::ParserPtarm::location_type * yylloc, forec::loader::ScannerPtarm &scanner) {
	return scanner.yylex(yylval);
}

