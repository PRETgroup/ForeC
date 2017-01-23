/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */
 
#ifndef SCANNER_PTARM_HPP
#define SCANNER_PTARM_HPP

// Only include FlexLexer.h if it hasn't been already included
#if ! defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer ptarmFlexLexer
#include <FlexLexer.h>
#endif

// Override the interface for yylex since we namespaced it
#undef YY_DECL
#define YY_DECL int forec::loader::ScannerPtarm::yylex()

// Include Bison for types / tokens
#include "ParserPtarm.tab.h"


namespace forec {
	namespace loader {
		class ScannerPtarm : public yyFlexLexer {
			public:
				// constructor accepts the input and output streams
				// 0 means std equivilant (stdin, stdout)
				ScannerPtarm(std::istream * in = 0, std::ostream * out = 0) : yyFlexLexer(in, out) { }

				// overloaded version of yylex - we need a pointer to yylval and yylloc
				inline int yylex(ParserPtarm::semantic_type * lval);
		
			private:
				// Scanning function created by Flex; make this private to force usage
				// of the overloaded method so we can get a pointer to Bison's yylval
				int yylex();
			
				// point to yylval (provided by Bison in overloaded yylex)
				ParserPtarm::semantic_type * yylval;
				
				// block default constructor
				ScannerPtarm();
				// block default copy constructor
				ScannerPtarm(ScannerPtarm const &rhs);
				// block default assignment operator
				ScannerPtarm &operator=(ScannerPtarm const &rhs);
		};
		
		// all our overloaded version does is save yylval to member variables
		// and invoke the generated scanner
		int ScannerPtarm::yylex(ParserPtarm::semantic_type * lval) {
			yylval = lval;
			return yylex();
		}

	}
}

#endif // SCANNER_PTARM_HPP

