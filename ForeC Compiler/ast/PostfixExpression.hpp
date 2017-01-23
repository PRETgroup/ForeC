#ifndef FOREC_AST_POSTFIX_EXPRESSION_HPP
#define FOREC_AST_POSTFIX_EXPRESSION_HPP

/*
 *  PostfixExpression.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class PostfixExpression : public Node {
			public:				
				PostfixExpression(Node &node, const std::string &variant = "none");
				PostfixExpression(Node &node0, Node &node1, const std::string &variant = "none");
								
				static int getCount(void);

				void updateSymbolTable(const std::string &type = "none", const bool isUsage = false, const bool isRead = false);
				
				const Node::Instantaneous willPause(const bool requireBothBranches);

				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				const std::string identifier;
		};
	}
}

#endif // FOREC_AST_POSTFIX_EXPRESSION_HPP
