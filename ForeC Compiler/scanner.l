/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */


%{
	#include <cstdio>
	#include <iomanip>
	#include <sstream>
	#include "Scanner.hpp"
	
	#include "parser.tab.h"
	#define YY_USER_ACTION yylloc->begin.line = yylineno;

	void unmatched(const std::string yytext);
	void count(const std::string yytext, const int lineno);
	void comment(const std::string yytext);
	void isInTypedef(void);
	void isExpectingTypeName(int value);
	void isNotExpectingTypeName(const int increment);
	int checkType(const std::string typeName);
%}

%option yylineno nodefault yyclass="Scanner" noyywrap c++

/* White space */
WS								[ \t\v\r\n\f]

/* Digit */
D								[0-9]

/* Letter */
L								[a-zA-Z_]

/* Hexadecimal */
H								[a-fA-F0-9]

/* Decimal floating point */
E								[Ee][+-]?{D}+

/* Hexadecimal floating point */
P								[Pp][+-]?{D}+

/* Floating point specifier */
FS								(f|F|l|L)

/* Integer specifier */
IS								((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))					


%%


{} /* Preprocessor directives */
"#include".+														{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::Parser::token::INCLUDE); }
("#define"|"#undef"|"#ifdef"|"#ifndef"|"#endif")(\\.|\\\n|[^\n])*	{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::Parser::token::DEFINE); }


{} /* Comments */
"/*"([^\*]|\*[^/])*"*/"			{ count(yytext, yylineno); comment(yytext); }
"//"[^\n]*						{ count(yytext, yylineno); comment(yytext); }


{} /* C-keywords */
"auto"							{ count(yytext, yylineno); return(forec::loader::Parser::token::AUTO); }
"_Bool"							{ count(yytext, yylineno); isExpectingTypeName(1); return(forec::loader::Parser::token::BOOL); }
"break"							{ count(yytext, yylineno); return(forec::loader::Parser::token::BREAK); }
"case"							{ count(yytext, yylineno); return(forec::loader::Parser::token::CASE); }
"char"							{ count(yytext, yylineno); isExpectingTypeName(1); return(forec::loader::Parser::token::CHAR); }
"_Complex"						{ count(yytext, yylineno); isExpectingTypeName(1); return(forec::loader::Parser::token::COMPLEX); }
"const"							{ count(yytext, yylineno); return(forec::loader::Parser::token::CONST); }
"continue"						{ count(yytext, yylineno); return(forec::loader::Parser::token::CONTINUE); }
"default"						{ count(yytext, yylineno); return(forec::loader::Parser::token::DEFAULT); }
"do"							{ count(yytext, yylineno); return(forec::loader::Parser::token::DO); }
"double"						{ count(yytext, yylineno); isExpectingTypeName(1); return(forec::loader::Parser::token::DOUBLE); }
"else"							{ count(yytext, yylineno); return(forec::loader::Parser::token::ELSE); }
"enum"							{ count(yytext, yylineno); return(forec::loader::Parser::token::ENUM); }
"extern"						{ count(yytext, yylineno); return(forec::loader::Parser::token::EXTERN); }
"false"							{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::Parser::token::FALSE); }
"float"							{ count(yytext, yylineno); isExpectingTypeName(1); return(forec::loader::Parser::token::FLOAT); }
"for"							{ count(yytext, yylineno); return(forec::loader::Parser::token::FOR); }
"goto"							{ count(yytext, yylineno); return(forec::loader::Parser::token::GOTO); }
"if"							{ count(yytext, yylineno); return(forec::loader::Parser::token::IF); }
"_Imaginary"					{ count(yytext, yylineno); isExpectingTypeName(1); return(forec::loader::Parser::token::IMAGINARY); }
"inline"						{ count(yytext, yylineno); return(forec::loader::Parser::token::INLINE); }
"int"							{ count(yytext, yylineno); isExpectingTypeName(1); return(forec::loader::Parser::token::INT); }
"long"							{ count(yytext, yylineno); isExpectingTypeName(1); return(forec::loader::Parser::token::LONG); }
"register"						{ count(yytext, yylineno); return(forec::loader::Parser::token::REGISTER); }
"restrict"						{ count(yytext, yylineno); return(forec::loader::Parser::token::RESTRICT); }
"return"						{ count(yytext, yylineno); return(forec::loader::Parser::token::RETURN); }
"short"							{ count(yytext, yylineno); isExpectingTypeName(1); return(forec::loader::Parser::token::SHORT); }
"signed"						{ count(yytext, yylineno); isExpectingTypeName(1); return(forec::loader::Parser::token::SIGNED); }
"sizeof"						{ count(yytext, yylineno); return(forec::loader::Parser::token::SIZEOF); }
"static"						{ count(yytext, yylineno); return(forec::loader::Parser::token::STATIC); }
"struct"						{ count(yytext, yylineno); return(forec::loader::Parser::token::STRUCT); }
"switch"						{ count(yytext, yylineno); return(forec::loader::Parser::token::SWITCH); }
"true"							{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::Parser::token::TRUE); }
"typedef"						{ count(yytext, yylineno); isInTypedef(); return(forec::loader::Parser::token::TYPEDEF); }
"union"							{ count(yytext, yylineno); return(forec::loader::Parser::token::UNION); }
"unsigned"						{ count(yytext, yylineno); isExpectingTypeName(1); return(forec::loader::Parser::token::UNSIGNED); }
"void"							{ count(yytext, yylineno); isExpectingTypeName(1); return(forec::loader::Parser::token::VOID); }
"volatile"						{ count(yytext, yylineno); return(forec::loader::Parser::token::VOLATILE); }
"while"							{ count(yytext, yylineno); return(forec::loader::Parser::token::WHILE); }


{} /* ForeC keywords */
"combine"						{ count(yytext, yylineno); return(forec::loader::Parser::token::COMBINE); }
"with"							{ count(yytext, yylineno); return(forec::loader::Parser::token::WITH); }
"shared"						{ count(yytext, yylineno); return(forec::loader::Parser::token::SHARED); }
"input"							{ count(yytext, yylineno); return(forec::loader::Parser::token::INPUT); }
"output"						{ count(yytext, yylineno); return(forec::loader::Parser::token::OUTPUT); }
"pause"							{ count(yytext, yylineno); return(forec::loader::Parser::token::PAUSE); }
"par"							{ count(yytext, yylineno); return(forec::loader::Parser::token::PAR); }
"weak"							{ count(yytext, yylineno); return(forec::loader::Parser::token::WEAK); }
"immediate"						{ count(yytext, yylineno); return(forec::loader::Parser::token::IMMEDIATE); }
"abort"							{ count(yytext, yylineno); return(forec::loader::Parser::token::ABORT); }
"when"							{ count(yytext, yylineno); return(forec::loader::Parser::token::WHEN); }
"thread"						{ count(yytext, yylineno); return(forec::loader::Parser::token::THREAD); }

"cs_none"						{ count(yytext, yylineno); return(forec::loader::Parser::token::CS_NONE); }
"cs_start"						{ count(yytext, yylineno); return(forec::loader::Parser::token::CS_START); }
"cs_end"						{ count(yytext, yylineno); return(forec::loader::Parser::token::CS_END); }


{} /* Identifiers and Type names */
{L}({L}|{D})*					{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(checkType(yytext)); }


{} /* Numbers */
0[xX]{H}+{IS}?					{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::Parser::token::CONSTANT); }
0{D}+{IS}?						{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::Parser::token::CONSTANT); }
{D}+{IS}?						{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::Parser::token::CONSTANT); }
L?'(\\.|[^\\'\n])+'				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::Parser::token::CONSTANT); /*'*/ }

{D}+{E}{FS}?					{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::Parser::token::CONSTANT); }
{D}*"."{D}+({E})?{FS}?			{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::Parser::token::CONSTANT); }
{D}+"."{D}*({E})?{FS}?			{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::Parser::token::CONSTANT); }
0[xX]{H}+{P}{FS}?				{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::Parser::token::CONSTANT); }
0[xX]{H}*"."{H}+({P})?{FS}?		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::Parser::token::CONSTANT); }
0[xX]{H}+"."{H}*({P})?{FS}?		{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::Parser::token::CONSTANT); }


{} /* String */
L?\"(\\.|[^\\"\n])*\"			{ count(yytext, yylineno); yylval->str = new std::string(yytext); return(forec::loader::Parser::token::STRING_LITERAL); /*"*/ }


{} /* Operators */
"..."							{ count(yytext, yylineno); return(forec::loader::Parser::token::ELLIPSIS); }
">>="							{ count(yytext, yylineno); return(forec::loader::Parser::token::RIGHT_ASSIGN); }
"<<="							{ count(yytext, yylineno); return(forec::loader::Parser::token::LEFT_ASSIGN); }
"+="							{ count(yytext, yylineno); return(forec::loader::Parser::token::ADD_ASSIGN); }
"-="							{ count(yytext, yylineno); return(forec::loader::Parser::token::SUB_ASSIGN); }
"*="							{ count(yytext, yylineno); return(forec::loader::Parser::token::MUL_ASSIGN); }
"/="							{ count(yytext, yylineno); return(forec::loader::Parser::token::DIV_ASSIGN); }
"%="							{ count(yytext, yylineno); return(forec::loader::Parser::token::MOD_ASSIGN); }
"&="							{ count(yytext, yylineno); return(forec::loader::Parser::token::AND_ASSIGN); }
"^="							{ count(yytext, yylineno); return(forec::loader::Parser::token::XOR_ASSIGN); }
"|="							{ count(yytext, yylineno); return(forec::loader::Parser::token::OR_ASSIGN); }
">>"							{ count(yytext, yylineno); return(forec::loader::Parser::token::RIGHT_OP); }
"<<"							{ count(yytext, yylineno); return(forec::loader::Parser::token::LEFT_OP); }
"++"							{ count(yytext, yylineno); return(forec::loader::Parser::token::INC_OP); }
"--"							{ count(yytext, yylineno); return(forec::loader::Parser::token::DEC_OP); }
"->"							{ count(yytext, yylineno); return(forec::loader::Parser::token::PTR_OP); }
"&&"							{ count(yytext, yylineno); return(forec::loader::Parser::token::AND_OP); }
"||"							{ count(yytext, yylineno); return(forec::loader::Parser::token::OR_OP); }
"<="							{ count(yytext, yylineno); return(forec::loader::Parser::token::LE_OP); }
">="							{ count(yytext, yylineno); return(forec::loader::Parser::token::GE_OP); }
"=="							{ count(yytext, yylineno); return(forec::loader::Parser::token::EQ_OP); }
"!="							{ count(yytext, yylineno); return(forec::loader::Parser::token::NE_OP); }
";"								{ count(yytext, yylineno); return(';'); }
("{"|"<%")						{ count(yytext, yylineno); isNotExpectingTypeName(1); return('{'); }
("}"|"%>")						{ count(yytext, yylineno); isNotExpectingTypeName(-1); return('}'); }
","								{ count(yytext, yylineno); return(','); }
":"								{ count(yytext, yylineno); return(':'); }
"="								{ count(yytext, yylineno); return('='); }
"("								{ count(yytext, yylineno); return('('); }
")"								{ count(yytext, yylineno); return(')'); }
("["|"<:")						{ count(yytext, yylineno); return('['); }
("]"|":>")						{ count(yytext, yylineno); return(']'); }
"."								{ count(yytext, yylineno); return('.'); }
"&"								{ count(yytext, yylineno); return('&'); }
"!"								{ count(yytext, yylineno); return('!'); }
"~"								{ count(yytext, yylineno); return('~'); }
"-"								{ count(yytext, yylineno); return('-'); }
"+"								{ count(yytext, yylineno); return('+'); }
"*"								{ count(yytext, yylineno); return('*'); }
"/"								{ count(yytext, yylineno); return('/'); }
"%"								{ count(yytext, yylineno); return('%'); }
"<"								{ count(yytext, yylineno); return('<'); }
">"								{ count(yytext, yylineno); return('>'); }
"^"								{ count(yytext, yylineno); return('^'); }
"|"								{ count(yytext, yylineno); return('|'); }
"?"								{ count(yytext, yylineno); return('?'); }
"#"								{ count(yytext, yylineno); return('#'); }


{} /* Whitespace */
{WS}							{ count(yytext, yylineno); }


{} /* Unmatched */
.								{ count(yytext, yylineno); unmatched(yytext); }

%%
int inTypedef = 0;
int expectingTypeName = 0;
int typeCount = 0;
std::string typeNames[256];

int line = 0;
int column = 0;
std::string currentSourceLine;


// Error function throws an exception (std::string) with the location and error message
void forec::loader::Parser::error(const forec::loader::Parser::location_type &loc, const std::string &msg) {
	std::ostringstream error;
	error << currentSourceLine << std::endl;
	error << std::setw(column) << "^" << std::endl;
	error << "Parser Error at " << line << "." << column << ": " << msg << std::endl;
	throw error.str();
}

/* Complain about unmatched characters */
void unmatched(const std::string yytext) {
	std::ostringstream error;
	error << currentSourceLine << std::endl;
	error << std::setw(column) << "^" << std::endl;
	error << "Lexical Error at " << line << "." << column << ": " << "unmatched characters: " << yytext << std::endl;
	throw error.str();
}

void comment(const std::string yytext) {
//	std::cout << "#" << yytext << "#" << std::endl;
}

/* Count the number of columns (zero indexing) */
void count(const std::string yytext, const int lineno) {
	line = lineno;
	
	for (int i = 0; yytext[i] != '\0'; i++) {
		if (yytext[i] == '\n') {
			column = 0;
			currentSourceLine = "";
		} else if (yytext[i] == '\t') {
			column += 4 - (column % 4);
			currentSourceLine += "    ";
		} else {
			column++;
			currentSourceLine += yytext[i];
		}
	}
}

void isInTypedef(void) {
	inTypedef = 1;
	expectingTypeName = 2;
}

void isExpectingTypeName(int value) {
	if (inTypedef == 1) {
		expectingTypeName = value;
	}
}

void isNotExpectingTypeName(const int increment) {
	if (increment > 0) {
		inTypedef <<= 1;
	} else {
		inTypedef >>= 1;
		isExpectingTypeName(1);
	}
}

int checkType(const std::string typeName) {	
	if (inTypedef == 1) {
		if (expectingTypeName == 2) {
			expectingTypeName = 1;

			for (int i = 0; i < typeCount; i++) {
				if (typeName.compare(typeNames[i]) == 0) {
					return(forec::loader::Parser::token::TYPE_NAME);
				}
			}
		} else if (expectingTypeName == 1) {
			inTypedef = 0;
			expectingTypeName = 0;
			for (int i = 0; i < typeCount; i++) {
				if (typeName.compare(typeNames[i]) == 0) {
					std::ostringstream error;
					error << currentSourceLine << std::endl;
					error << std::setw(column) << "^" << std::endl;
					error << "Lexical Error at " << line << "." << column << ": " << "redefinition of typedef " << typeName << std::endl;
					throw error.str();
				}
			}

			typeNames[typeCount++] = typeName;
			return(forec::loader::Parser::token::TYPE_NAME);
		}
	} else {
		for (int i = 0; i < typeCount; i++) {
			if (typeName.compare(typeNames[i]) == 0) {
				return(forec::loader::Parser::token::TYPE_NAME);
			}
		}
	}

	return(forec::loader::Parser::token::IDENTIFIER);
}



