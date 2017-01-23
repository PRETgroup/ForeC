#ifndef FOREC_AST_EXPRESSION_STATEMENT_HPP
#define FOREC_AST_EXPRESSION_STATEMENT_HPP

/*
 *  ExpressionStatement.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class ExpressionStatement : public Node {
			public:				
				ExpressionStatement(const std::string &variant = "none");
				ExpressionStatement(Node &node, const std::string &variant = "none");

				static int getCount(void);
						
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_EXPRESSION_STATEMENT_HPP
