#ifndef FOREC_AST_CAST_EXPRESSION_HPP
#define FOREC_AST_CAST_EXPRESSION_HPP

/*
 *  CastExpression.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class CastExpression : public Node {
			public:				
				CastExpression(Node &node, const std::string &variant = "none");
								
				void prepend(Node &node);
				
				static int getCount(void);

				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_CAST_EXPRESSION_HPP
