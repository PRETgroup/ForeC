/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */


%{
	#include <cstdio>
	#include <iomanip>
	#include <sstream>
	#include "ScannerPtarm.hpp"
	
	void unmatched(const std::string yytext);
	void count(const std::string yytext, const int lineno);
%}

%option yylineno nodefault yyclass="ScannerPtarm" noyywrap c++ prefix="ptarm"

/* White space */
WS									[ \t\v\r\n\f]

/* Digit */
D									[0-9]

/* Letter */
L									[a-zA-Z_]

/* Hexadecimal */
H									(0x)?[a-fA-F0-9]

/* Identifier */
IDENTIFIER							{L}({L}|{D})*

/* Constant */
CONSTANT							{H}+|-?{D}+

/* Shifted Operand */
SHIFTED_OPERAND						((asr|lsl|lsr)|r(or|rx)){WS}*"#"{CONSTANT}

/* Label */
LABEL								"."?{IDENTIFIER}("+"{CONSTANT})?

/* Program Counter */
PC									^[ ]*{CONSTANT}

/* Registers */
REGISTERS_GENERAL					r{D}+
REGISTERS_SPECIAL					pc|lr|fp|ip|sp|cpsr|spsr
COPROCESSOR_REGISTERS				cr{D}+

/* Symbolic instructions */
COND								eq|ne|cs|hs|cc|lo|mi|pl|vs|vc|hi|ls|ge|lt|gt|le|al
ADDRESSING_MODE4					(da|ia|db|ib)|(fa|fd|ea|ed)

BRANCH_UNCONDITIONAL				b(l)?
BRANCH_CONDITIONAL					{BRANCH_UNCONDITIONAL}{COND}?
INTERRUPT							swi{COND}?
ARITHMETIC_INTEGER					(ad(c|d)|rs(b|c)|sbc|sub|(s|u)?m(la|ul)l?){COND}?s?|asr{COND}?
LOGIC								(and|bic|eor|orr){COND}?s?|(cm(n|p)|teq|tst|ls(l|r)s?|neg|ror){COND}?
COPROCESSOR							cdp({COND}?|2)
READ								ld(c({COND}?|2)l?|m{COND}?{ADDRESSING_MODE4}|r{COND}?s?h?b?t?)|pop
MOVE								m(cr({COND}?|2)|sr{COND}?|ov{COND}?s?|r(c|s){COND}?|vn{COND}?s?)|swp{COND}?b?|nop
STORE								st(c({COND}?|2)l?|m{COND}?{ADDRESSING_MODE4}|r{COND}?b?t?h?)|push
DATA								"."word

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
{PC}								{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::PC); }
"; "{CONSTANT}						{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::PC_1); }


{} /* Assembly instructions */
{BRANCH_UNCONDITIONAL}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::BRANCH_UNCONDITIONAL); }
{BRANCH_CONDITIONAL}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::BRANCH_CONDITIONAL); }
{INTERRUPT}							{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::BRANCH_UNCONDITIONAL); }
{ARITHMETIC_INTEGER}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::ARITHMETIC_INTEGER); }
{LOGIC}								{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::LOGIC); }
{COPROCESSOR}						{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::COPROCESSOR); }
{READ}								{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::READ); }
{MOVE}								{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::MOVE); }
{STORE}								{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::STORE); }

{REGISTERS_GENERAL}					{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::REGISTERS_GENERAL); }
{REGISTERS_SPECIAL}					{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::REGISTERS_SPECIAL); }
{COPROCESSOR_REGISTERS}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::COPROCESSOR_REGISTERS); }
{SHIFTED_OPERAND}					{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::SHIFTED_OPERAND); }


{} /* Numbers */
{CONSTANT}							{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::CONSTANT); }
"#"{CONSTANT}						{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::CONSTANT); }


{} /* Characters */
":"									{ count(yytext, yylineno); return(':'); }
";"									{ count(yytext, yylineno); return(';'); }
","									{ count(yytext, yylineno); return(','); }
"/"									{ count(yytext, yylineno); return('/'); }
"#"									{ count(yytext, yylineno); return('#'); }
"!"									{ count(yytext, yylineno); return('!'); }
"^"									{ count(yytext, yylineno); return('^'); }

"<"									{ count(yytext, yylineno); return('<'); }
">"									{ count(yytext, yylineno); return('>'); }
"["									{ count(yytext, yylineno); return('['); }
"]"									{ count(yytext, yylineno); return(']'); }
"("									{ count(yytext, yylineno); return('('); }
")"									{ count(yytext, yylineno); return(')'); }
"{"									{ count(yytext, yylineno); return('{'); }
"}"									{ count(yytext, yylineno); return('}'); }


{} /* Source lines */
{C_SOURCE}							{ count(yytext, yylineno); yylval->str = new std::string(yytext); yylval->str->erase(yylval->str->begin()); return(forec::loader::ParserPtarm::token::C_SOURCE); }
{DATA}								{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::DATA); }


{} /* Assembly label */
{LABEL}								{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::LABEL); }


{} /* Analysis annotations */
{FOREC_STATEMENT_PAR_START}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_STATEMENT_PAR_START); }
{FOREC_STATEMENT_PAR_END}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_STATEMENT_PAR_END); }
{FOREC_STATEMENT_ABORT_START}			{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_STATEMENT_ABORT_START); }
{FOREC_STATEMENT_ABORT_END}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_STATEMENT_ABORT_END); }
{FOREC_STATEMENT_ABORT_SCOPE_END}		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_STATEMENT_ABORT_SCOPE_END); }
{FOREC_STATEMENT_PAUSE_START}			{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_STATEMENT_PAUSE_START); }
{FOREC_STATEMENT_PAUSE_END}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_STATEMENT_PAUSE_END); }

{FOREC_SCHEDULER_COUNTER_START}			{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_SCHEDULER_COUNTER_START); }
{FOREC_SCHEDULER_COUNTER_END}			{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_SCHEDULER_COUNTER_END); }


{FOREC_SCHEDULER_BOOT_START}			{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_SCHEDULER_BOOT_START); }
{FOREC_SCHEDULER_BOOT_END}				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_SCHEDULER_BOOT_END); }
{FOREC_SCHEDULER_REACTION_START_START}	{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_SCHEDULER_REACTION_START_START); }
{FOREC_SCHEDULER_REACTION_START_END}	{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_SCHEDULER_REACTION_START_END); }
{FOREC_SCHEDULER_REACTION_END_START}	{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_SCHEDULER_REACTION_END_START); }
{FOREC_SCHEDULER_REACTION_END_END}		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_SCHEDULER_REACTION_END_END); }
{FOREC_SCHEDULER_PAR_HANDLER_START}		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_SCHEDULER_PAR_HANDLER_START); }
{FOREC_SCHEDULER_PAR_HANDLER_END}		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_SCHEDULER_PAR_HANDLER_END); }
{FOREC_SCHEDULER_ABORT_HANDLER_START}	{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_SCHEDULER_ABORT_HANDLER_START); }
{FOREC_SCHEDULER_ABORT_HANDLER_END}		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_SCHEDULER_ABORT_HANDLER_END); }

{FOREC_SCHEDULER_THREAD_REMOVE_START}	{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_SCHEDULER_THREAD_REMOVE_START); }
{FOREC_SCHEDULER_THREAD_REMOVE_END}		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_SCHEDULER_THREAD_REMOVE_END); }
{FOREC_SCHEDULER_ITERATION_END_START}	{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_SCHEDULER_ITERATION_END_START); }
{FOREC_SCHEDULER_ITERATION_END_END}		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_SCHEDULER_ITERATION_END_END); }

{FOREC_THREAD_START}					{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_THREAD_START); }
{FOREC_THREAD_END}						{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_THREAD_END); }

{FOREC_ITERATION_BOUND}					{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::ParserPtarm::token::FOREC_ITERATION_BOUND); }


{} /* Whitespace */
{WS}									{ count(yytext, yylineno); /* Ignore */ }

{} /* Unmatched */
.										{ count(yytext, yylineno); unmatched(yytext); /* Ignore */ }


%%

// Declared in ScannerMicroBlaze.l
extern int line;
extern int column;
extern std::string currentSourceLine;

// Error function throws an exception (std::string) with the location and error message
void forec::loader::ParserPtarm::error(const forec::loader::ParserPtarm::location_type &loc, const std::string &msg) {
	std::ostringstream error;
	error << currentSourceLine << std::endl;
	error << std::setw(column) << "^" << std::endl;
	error << "Parser Error at " << line << "." << column << ": " << msg << std::endl;
	throw error.str();
}



