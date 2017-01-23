#ifndef FOREC_AST_UNARY_EXPRESSION_HPP
#define FOREC_AST_UNARY_EXPRESSION_HPP

/*
 *  UnaryExpression.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class UnaryExpression : public Node {
			public:				
				UnaryExpression(Node &node, const std::string &variant = "none");
				UnaryExpression(const std::string unaryOperator, Node &node, const std::string &variant = "none");
		
				static int getCount(void);
								
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				const std::string unaryOperator;
		};
	}
}

#endif // FOREC_AST_UNARY_EXPRESSION_HPP
