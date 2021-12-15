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
%define api.prefix {microBlaze}
%define api.namespace {forec::loader}
%define api.parser.class {ParserMicroBlaze}
%parse-param {forec::loader::ScannerMicroBlaze &scanner}
%parse-param {forec::cfg::Node &rootNode}
%lex-param   {forec::loader::ScannerMicroBlaze &scanner}

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
			class ScannerMicroBlaze;
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
	static int yylex(forec::loader::ParserMicroBlaze::semantic_type * yylval, forec::loader::ParserMicroBlaze::location_type * yylloc, forec::loader::ScannerMicroBlaze &scanner);
}

%token <str> REGISTERS_GENERAL REGISTERS_SPECIAL 
%token <str> CONSTANT PC PC_1

%token <str> BRANCH_CONDITIONAL BRANCH_CONDITIONAL_WITH_DELAY BRANCH_UNCONDITIONAL BRANCH_UNCONDITIONAL_WITH_DELAY
%token <str> BREAK RETURN
%token <str> LOGIC ARITHMETIC_INTEGER ARITHMETIC_FLOAT
%token <str> READ STORE MOVE MEMORY

%token <str> LABEL

%token <str> C_SOURCE

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
	| CONSTANT							{ $$ = new forec::cfg::Operand(*$1, "constant"); }
	;

operand_list
	: operand							{ $$ = new forec::cfg::OperandList(*$1); }
	| operand_list ',' operand			{ $$ = $1; $$->append(*$3); }
	;

assembly_instruction
	: BRANCH_CONDITIONAL				{ $$ = new forec::cfg::AssemblyInstruction(*$1, "branchConditional"); }
	| BRANCH_CONDITIONAL_WITH_DELAY		{ $$ = new forec::cfg::AssemblyInstruction(*$1, "branchConditionalWithDelay"); }
	| BRANCH_UNCONDITIONAL				{ $$ = new forec::cfg::AssemblyInstruction(*$1, "branchUnconditional"); }
	| BRANCH_UNCONDITIONAL_WITH_DELAY	{ $$ = new forec::cfg::AssemblyInstruction(*$1, "branchUnconditionalWithDelay"); }
	| BREAK								{ $$ = new forec::cfg::AssemblyInstruction(*$1, "break"); }
	| RETURN							{ $$ = new forec::cfg::AssemblyInstruction(*$1, "return"); }
	| LOGIC								{ $$ = new forec::cfg::AssemblyInstruction(*$1, "logic"); }
	| ARITHMETIC_INTEGER				{ $$ = new forec::cfg::AssemblyInstruction(*$1, "arithmeticInteger"); }
	| ARITHMETIC_FLOAT					{ $$ = new forec::cfg::AssemblyInstruction(*$1, "arithmeticFloat"); }
	| READ								{ $$ = new forec::cfg::AssemblyInstruction(*$1, "read"); }
	| STORE								{ $$ = new forec::cfg::AssemblyInstruction(*$1, "store"); }
	| MOVE								{ $$ = new forec::cfg::AssemblyInstruction(*$1, "move"); }
	| MEMORY							{ $$ = new forec::cfg::AssemblyInstruction(*$1, "memory"); }
	;

assembly_line
	: PC ':' CONSTANT assembly_instruction operand_list							{ $$ = new forec::cfg::AssemblyLine(*$1, *$3, *$4, *$5); }
	| PC ':' CONSTANT assembly_instruction operand_list PC_1					{ $$ = new forec::cfg::AssemblyLine(*$1, *$3, *$4, *$5, *$6); }
	| PC ':' CONSTANT assembly_instruction operand_list PC_1 '<' LABEL '>'		{ $$ = new forec::cfg::AssemblyLine(*$1, *$3, *$4, *$5, *$6, *$8); }
	;

label
	: PC '<' LABEL '>' ':'				{ $$ = new forec::cfg::Label(*$1, *$3); }
	;
	
c_source_line
	: C_SOURCE							{ $$ = new forec::cfg::CSourceLine(*$1); }
	| PC ':' CONSTANT operand_list		{ if ($3->compare("80000001") != 0) {	/* Special MicroBlaze instruction to terminate the simulation. */
											unsigned int pcValue;
											std::istringstream pc(*$1);
											pc >> std::hex >> pcValue;
											std::ostringstream error;
											error << "Parser Error at program counter 0x" << std::hex << pcValue << ": Missing asm instruction" << std::endl;
											throw error.str();
										  }; $$ = new forec::cfg::CSourceLine("80000001 r0, r0, r0"); 
										}
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
#include "ScannerMicroBlaze.hpp"
static int yylex(forec::loader::ParserMicroBlaze::semantic_type * yylval, forec::loader::ParserMicroBlaze::location_type * yylloc, forec::loader::ScannerMicroBlaze &scanner) {
	return scanner.yylex(yylval);
}

