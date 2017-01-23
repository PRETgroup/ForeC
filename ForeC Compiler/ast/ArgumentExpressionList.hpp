#ifndef FOREC_AST_ARGUMENT_EXPRESSION_LIST_HPP
#define FOREC_AST_ARGUMENT_EXPRESSION_LIST_HPP

/*
 *  ArgumentExpressionList.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "NodeList.hpp"

namespace forec {
	namespace ast {
		class ArgumentExpressionList : public NodeList {
			public:				
				ArgumentExpressionList(Node &node, const std::string &variant = "none");
			
				static int getCount(void);
			
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_ARGUMENT_EXPRESSION_LIST_HPP
