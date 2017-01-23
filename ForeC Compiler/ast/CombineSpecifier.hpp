#ifndef FOREC_AST_COMBINE_SPECIFIER_HPP
#define FOREC_AST_COMBINE_SPECIFIER_HPP

/*
 *  CombineSpecifier.hpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 27/05/13.
 *  Copyright 2013 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class CombineSpecifier : public Node {
			public:
				CombineSpecifier(const std::string &terminal, const std::string &variant = "none");

				static int getCount(void);
				
				const std::string getTerminal(void) const;

				void updateSymbolTable(const std::string &type = "none", const bool isUsage = false, const bool isRead = false);

				void prettyPrint(std::ostream &output);

			protected:
				static int globalCount;
				
				const std::string terminal;

		};
	}
}
		
#endif // FOREC_AST_COMBINE_SPECIFIER_HPP