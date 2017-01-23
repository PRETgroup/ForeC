#ifndef FOREC_AST_TYPE_SPECIFIER_HPP
#define FOREC_AST_TYPE_SPECIFIER_HPP

/*
 *  TypeSpecifier.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class PrimaryExpression;
	}
}

namespace forec {
	namespace ast {
		class TypeSpecifier : public Node {
			public:				
				TypeSpecifier(const std::string &variant = "none");
				TypeSpecifier(PrimaryExpression &terminal, const std::string &variant);

				static const int getCount(void);
				
				void updateSymbolTable(const std::string &type = "none", const bool isUsage = false, const bool isRead = false);
				
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				PrimaryExpression *terminal;
		};
	}
}

#endif // FOREC_AST_TYPE_SPECIFIER_HPP
