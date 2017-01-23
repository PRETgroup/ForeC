#ifndef FOREC_AST_STRUCT_DECLARATOR_LIST_HPP
#define FOREC_AST_STRUCT_DECLARATOR_LIST_HPP

/*
 *  StructDeclaratorList.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "NodeList.hpp"

namespace forec {
	namespace ast {
		class StructDeclaratorList : public NodeList {
			public:				
				StructDeclaratorList(Node &node, const std::string &variant = "none");

				static int getCount(void);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_STRUCT_DECLARATOR_LIST_HPP
