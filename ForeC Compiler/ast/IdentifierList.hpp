#ifndef FOREC_AST_IDENTIFIER_LIST_HPP
#define FOREC_AST_IDENTIFIER_LIST_HPP

/*
 *  IdentifierList.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "NodeList.hpp"

namespace forec {
	namespace ast {
		class IdentifierList : public NodeList {
			public:				
				IdentifierList(Node &node, const std::string &variant = "none");
			
				static int getCount(void);
				
				void updateSymbolTable(const std::string &type = "none", const bool isUsage = false, const bool isRead = false);
		
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_IDENTIFIER_LIST_HPP
