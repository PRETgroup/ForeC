/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */
 
#ifndef SCANNER_MICROBLAZE_HPP
#define SCANNER_MICROBLAZE_HPP

// Only include FlexLexer.h if it hasn't been already included
#if ! defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer microBlazeFlexLexer
#include <FlexLexer.h>
#endif

// Override the interface for yylex since we namespaced it
#undef YY_DECL
#define YY_DECL int forec::loader::ScannerMicroBlaze::yylex()

// Include Bison for types / tokens
#include "ParserMicroBlaze.tab.h"


namespace forec {
	namespace loader {
		class ScannerMicroBlaze : public yyFlexLexer {
			public:
				// constructor accepts the input and output streams
				// 0 means std equivilant (stdin, stdout)
				ScannerMicroBlaze(std::istream * in = 0, std::ostream * out = 0) : yyFlexLexer(in, out) { }

				// overloaded version of yylex - we need a pointer to yylval and yylloc
				inline int yylex(ParserMicroBlaze::semantic_type * lval);
		
			private:
				// Scanning function created by Flex; make this private to force usage
				// of the overloaded method so we can get a pointer to Bison's yylval
				int yylex();
			
				// point to yylval (provided by Bison in overloaded yylex)
				ParserMicroBlaze::semantic_type * yylval;
				
				// block default constructor
				ScannerMicroBlaze();
				// block default copy constructor
				ScannerMicroBlaze(ScannerMicroBlaze const &rhs);
				// block default assignment operator
				ScannerMicroBlaze &operator=(ScannerMicroBlaze const &rhs);
		};
		
		// all our overloaded version does is save yylval to member variables
		// and invoke the generated scanner
		int ScannerMicroBlaze::yylex(ParserMicroBlaze::semantic_type * lval) {
			yylval = lval;
			return yylex();
		}

	}
}

#endif // SCANNER_MICROBLAZE_HPP
