/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */


%{
	#include <cstdio>
	#include <iomanip>
	#include <sstream>
	#include "ScannerMicroBlaze.hpp"
	
	int line = 0;
	int column = 0;
	std::string currentSourceLine;
	
	/* Complain about unmatched characters */
	void unmatched(const std::string yytext) {
		std::ostringstream error;
		error << currentSourceLine << std::endl;
		error << std::setw(column) << "^" << std::endl;
		error << "Lexical Error at " << line << "." << column << ": " << "unmatched characters: " << yytext << std::endl;
		throw error.str();
	}
	
	/* Count the number of columns (zero indexing) */
	void count(const std::string yytext, const int lineno) {
		line = lineno;
		
		for (int i = 0; yytext[i] != '\0'; i++) {
			if (yytext[i] == '\n') {
				column = 0;
				currentSourceLine = "";
			} else if (yytext[i] == '\t') {
				const int columnDifference = 4 - (column % 4);
				column += columnDifference;
				for (int i = 0; i < columnDifference; ++i) {
					currentSourceLine += " ";					
				}
			} else {
				column++;
				currentSourceLine += yytext[i];
			}
		}
	}
%}

%option yylineno nodefault yyclass="ScannerMicroBlaze" noyywrap c++ prefix="microBlaze"

/* White space */
WS									[ \t\v\r\n\f]

/* Digit */
D									[0-9]

/* Letter */
L									[a-zA-Z_]

/* Hexadecimal */
H									[a-fA-F0-9]

/* Identifier */
IDENTIFIER							{L}({L}|{D})*

/* Constant */
CONSTANT							{H}+|-?{D}+

/* Program Counter */
PC									^[ ]*{CONSTANT}

/* Registers */
REGISTERS_GENERAL					r{D}+
REGISTERS_SPECIAL					r(pc|msr|ear|esr|fsr|slr|shr|btr|edr|pid|zpr|tlb(lo|hi|s?x)|(fsl|pvr)?{D}+)


/* Symbolic instructions */
CARRY_KEEP							(c|k)+
IMMEDIATE							i
DELAY								d
ABSOLUTE							a
LINK								l
COMPARISON							eq|ge|gt|le|lt|ne
FLOATING_COMPARISON					{COMPARISON}|un
STREAM_INTERFACE					t?n?e?c?a?
DYNAMIC								d
SIGNED								s
UNSIGNED							u
REVERSE								r
EXCLUSIVE							x
HIGH								h
PATTERN_TYPE						bf|eq|ne
RETURN_TYPE							bd|id|ed|sd
HALF								h
WORD								w
DATA_CACHE_WRITE_TYPE				flush|clear

BRANCH_CONDITIONAL					b{COMPARISON}{IMMEDIATE}?
BRANCH_CONDITIONAL_WITH_DELAY		{BRANCH_CONDITIONAL}{DELAY}
BRANCH_UNCONDITIONAL				br{ABSOLUTE}?{IMMEDIATE}?
BRANCH_UNCONDITIONAL_WITH_DELAY		br{ABSOLUTE}?{LINK}?{IMMEDIATE}?{DELAY}
BREAK								brk{IMMEDIATE}?
RETURN								rt{RETURN_TYPE}

LOGIC								(and|addn|bsrl|bsll){IMMEDIATE}?|x?or{IMMEDIATE}?|pcmp{PATTERN_TYPE}|clz|srl
ARITHMETIC_INTEGER					(add|rsub){IMMEDIATE}?{CARRY_KEEP}?|bsra{IMMEDIATE}?|sr(a|c)|(cmp|idiv){UNSIGNED}?|mul({HIGH}{SIGNED}?{UNSIGNED}?|{IMMEDIATE})?
ARITHMETIC_FLOAT					f(add|rsub|mul|div|cmp"."{FLOATING_COMPARISON}|lt|int|sqrt)

READ								{STREAM_INTERFACE}get{DYNAMIC}?|lb{UNSIGNED}({REVERSE}|{IMMEDIATE})?|l{HALF}{UNSIGNED}({REVERSE}|{IMMEDIATE})?|l{WORD}({REVERSE}|{IMMEDIATE}|{EXCLUSIVE})?
STORE								{STREAM_INTERFACE}put{DYNAMIC}?|imm|sb({REVERSE}|{IMMEDIATE})?|sext(16|8)|s{HALF}({REVERSE}|{IMMEDIATE})?|s{WORD}({REVERSE}|{IMMEDIATE}|{EXCLUSIVE})?|wdc("."{DATA_CACHE_WRITE_TYPE})?|wic
MOVE								mfs|msr(clr|set)|mts
MEMORY								mbar


/* Source code */
C_SOURCE								^-.*$


/* Analysis annotations */
FOREC_STATEMENT_PAR_START				^\+{WS}*"// forec:statement:par:"{IDENTIFIER}":start"
FOREC_STATEMENT_PAR_END					^\+{WS}*"// forec:statement:par:"{IDENTIFIER}":end"
FOREC_STATEMENT_ABORT_START				^\+{WS}*"// forec:statement:abort:"{IDENTIFIER}":start"
FOREC_STATEMENT_ABORT_END				^\+{WS}*"// forec:statement:abort:"{IDENTIFIER}":end"
FOREC_STATEMENT_ABORT_SCOPE_END			^\+{WS}*"// forec:statement:abort:"{IDENTIFIER}":scope:end"
FOREC_STATEMENT_PAUSE_START				^\+{WS}*"// forec:statement:pause:"{IDENTIFIER}":start"
FOREC_STATEMENT_PAUSE_END				^\+{WS}*"// forec:statement:pause:"{IDENTIFIER}":end"

FOREC_SCHEDULER_COUNTER_START			^\+{WS}*"// forec:scheduler:counter:start"
FOREC_SCHEDULER_COUNTER_END				^\+{WS}*"// forec:scheduler:counter:end"

FOREC_SCHEDULER_BOOT_START				^\+{WS}*"// forec:scheduler:boot:start"
FOREC_SCHEDULER_BOOT_END				^\+{WS}*"// forec:scheduler:boot:end"
FOREC_SCHEDULER_REACTION_START_START	^\+{WS}*"// forec:scheduler:reactionStart:"{IDENTIFIER}":"(master|slave)":"{D}+":start"
FOREC_SCHEDULER_REACTION_START_END		^\+{WS}*"// forec:scheduler:reactionStart:"{IDENTIFIER}":"(master|slave)":"{D}+":end"
FOREC_SCHEDULER_REACTION_END_START		^\+{WS}*"// forec:scheduler:reactionEnd:"{IDENTIFIER}":"(master|slave)":"{D}+":start"
FOREC_SCHEDULER_REACTION_END_END		^\+{WS}*"// forec:scheduler:reactionEnd:"{IDENTIFIER}":"(master|slave)":"{D}+":end"
FOREC_SCHEDULER_PAR_HANDLER_START		^\+{WS}*"// forec:scheduler:parHandler:"{IDENTIFIER}":"(master|slave)":"{D}+":start"
FOREC_SCHEDULER_PAR_HANDLER_END			^\+{WS}*"// forec:scheduler:parHandler:"{IDENTIFIER}":"(master|slave)":"{D}+":end"
FOREC_SCHEDULER_ABORT_HANDLER_START		^\+{WS}*"// forec:scheduler:abortHandler:"{IDENTIFIER}":"{D}+":start"
FOREC_SCHEDULER_ABORT_HANDLER_END		^\+{WS}*"// forec:scheduler:abortHandler:"{IDENTIFIER}":"{D}+":end"

FOREC_SCHEDULER_THREAD_REMOVE_START		^\+{WS}*"// forec:scheduler:threadRemove:"{IDENTIFIER}":start"
FOREC_SCHEDULER_THREAD_REMOVE_END		^\+{WS}*"// forec:scheduler:threadRemove:"{IDENTIFIER}":end"
FOREC_SCHEDULER_ITERATION_END_START		^\+{WS}*"// forec:scheduler:iterationEnd:"{IDENTIFIER}":start"
FOREC_SCHEDULER_ITERATION_END_END		^\+{WS}*"// forec:scheduler:iterationEnd:"{IDENTIFIER}":end"

FOREC_THREAD_START						^\+{WS}*"// forec:thread:"{IDENTIFIER}":start"
FOREC_THREAD_END						^\+{WS}*"// forec:thread:"{IDENTIFIER}":end"

FOREC_ITERATION_BOUND					^\+{WS}*"// forec:iteration:"{IDENTIFIER}":bound:"{D}+":"{D}+

%%


{} /* Program Counters */
{PC}								{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::PC); }
"// "{CONSTANT}						{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::PC_1); }


{} /* Assembly instructions */
{BRANCH_CONDITIONAL}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::BRANCH_CONDITIONAL); }
{BRANCH_CONDITIONAL_WITH_DELAY}		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::BRANCH_CONDITIONAL_WITH_DELAY); }
{BRANCH_UNCONDITIONAL}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::BRANCH_UNCONDITIONAL); }
{BRANCH_UNCONDITIONAL_WITH_DELAY}	{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::BRANCH_UNCONDITIONAL_WITH_DELAY); }
{BREAK}								{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::BREAK); }
{RETURN}							{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::RETURN); }

{LOGIC}								{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::LOGIC); }
{ARITHMETIC_INTEGER}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::ARITHMETIC_INTEGER); }
{ARITHMETIC_FLOAT}					{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::ARITHMETIC_FLOAT); }

{READ}								{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::READ); }
{STORE}								{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::STORE); }
{MOVE}								{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::MOVE); }
{MEMORY}							{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::MEMORY); }

{REGISTERS_GENERAL}					{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::REGISTERS_GENERAL); }
{REGISTERS_SPECIAL}					{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::REGISTERS_SPECIAL); }


{} /* Numbers */
{CONSTANT}							{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::CONSTANT); }


{} /* Characters */
":"									{ count(yytext, yylineno); return(':'); }
","									{ count(yytext, yylineno); return(','); }
"<"									{ count(yytext, yylineno); return('<'); }
">"									{ count(yytext, yylineno); return('>'); }
"/"									{ count(yytext, yylineno); return('/'); }


{} /* Assembly label */
{IDENTIFIER}("."{CONSTANT})?			{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::LABEL); }


{} /* Source lines */
{C_SOURCE}								{ count(yytext, yylineno); yylval->str = new std::string(yytext); yylval->str->erase(yylval->str->begin()); return(forec::loader::ParserMicroBlaze::token::C_SOURCE); }


{} /* Analysis annotations */
{FOREC_STATEMENT_PAR_START}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_STATEMENT_PAR_START); }
{FOREC_STATEMENT_PAR_END}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_STATEMENT_PAR_END); }
{FOREC_STATEMENT_ABORT_START}			{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_STATEMENT_ABORT_START); }
{FOREC_STATEMENT_ABORT_END}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_STATEMENT_ABORT_END); }
{FOREC_STATEMENT_ABORT_SCOPE_END}		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_STATEMENT_ABORT_SCOPE_END); }
{FOREC_STATEMENT_PAUSE_START}			{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_STATEMENT_PAUSE_START); }
{FOREC_STATEMENT_PAUSE_END}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_STATEMENT_PAUSE_END); }

{FOREC_SCHEDULER_COUNTER_START}			{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_SCHEDULER_COUNTER_START); }
{FOREC_SCHEDULER_COUNTER_END}			{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_SCHEDULER_COUNTER_END); }


{FOREC_SCHEDULER_BOOT_START}			{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_SCHEDULER_BOOT_START); }
{FOREC_SCHEDULER_BOOT_END}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_SCHEDULER_BOOT_END); }
{FOREC_SCHEDULER_REACTION_START_START}	{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_SCHEDULER_REACTION_START_START); }
{FOREC_SCHEDULER_REACTION_START_END}	{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_SCHEDULER_REACTION_START_END); }
{FOREC_SCHEDULER_REACTION_END_START}	{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_SCHEDULER_REACTION_END_START); }
{FOREC_SCHEDULER_REACTION_END_END}		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_SCHEDULER_REACTION_END_END); }
{FOREC_SCHEDULER_PAR_HANDLER_START}		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_SCHEDULER_PAR_HANDLER_START); }
{FOREC_SCHEDULER_PAR_HANDLER_END}		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_SCHEDULER_PAR_HANDLER_END); }
{FOREC_SCHEDULER_ABORT_HANDLER_START}	{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_SCHEDULER_ABORT_HANDLER_START); }
{FOREC_SCHEDULER_ABORT_HANDLER_END}		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_SCHEDULER_ABORT_HANDLER_END); }

{FOREC_SCHEDULER_THREAD_REMOVE_START}	{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_SCHEDULER_THREAD_REMOVE_START); }
{FOREC_SCHEDULER_THREAD_REMOVE_END}		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_SCHEDULER_THREAD_REMOVE_END); }
{FOREC_SCHEDULER_ITERATION_END_START}	{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_SCHEDULER_ITERATION_END_START); }
{FOREC_SCHEDULER_ITERATION_END_END}		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_SCHEDULER_ITERATION_END_END); }

{FOREC_THREAD_START}					{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_THREAD_START); }
{FOREC_THREAD_END}						{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_THREAD_END); }

{FOREC_ITERATION_BOUND}					{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserMicroBlaze::token::FOREC_ITERATION_BOUND); }


{} /* Whitespace */
{WS}									{ count(yytext, yylineno); /* Ignore */ }

{} /* Unmatched */
.										{ count(yytext, yylineno); unmatched(yytext); /* Ignore */ }


%%

// Error function throws an exception (std::string) with the location and error message
void forec::loader::ParserMicroBlaze::error(const forec::loader::ParserMicroBlaze::location_type &loc, const std::string &msg) {
	std::ostringstream error;
	error << currentSourceLine << std::endl;
	error << std::setw(column) << "^" << std::endl;
	error << "Parser Error at " << line << "." << column << ": " << msg << std::endl;
	throw error.str();
}

