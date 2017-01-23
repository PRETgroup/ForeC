#ifndef FOREC_AST_DECLARATION_SPECIFIERS_HPP
#define FOREC_AST_DECLARATION_SPECIFIERS_HPP

/*
 *  DeclarationSpecifiers.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "NodeList.hpp"

namespace forec {
	namespace ast {
		class DeclarationSpecifiers : public NodeList {
			public:				
				DeclarationSpecifiers(Node &node, const std::string &variant = "none");
				
				static int getCount(void);
				
				void setSharedIdentifier(Node &sharedIdentifier);
				void setSharedDirectDeclarator(const std::string &sharedDirectDeclarator);
				const std::string getSharedStruct(void) const;

				void updateSymbolTable(const std::string &type = "none", const bool isUsage = false, const bool isRead = false);

				void prettyPrint(std::ostream &output);
				
			protected:
				static int globalCount;
				
				Node *sharedIdentifier;
				std::string sharedDirectDeclarator;
				
		};
	}
}

#endif // FOREC_AST_DECLARATION_SPECIFIERS_HPP
