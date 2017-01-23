#ifndef FOREC_AST_JUMP_STATEMENT_HPP
#define FOREC_AST_JUMP_STATEMENT_HPP

/*
 *  JumpStatement.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class JumpStatement : public Node {
			public:				
				JumpStatement(const std::string &variant = "none");
				JumpStatement(Node &node, const std::string &variant = "none");

				static int getCount(void);
				
				void updateSymbolTable(const std::string &type = "none", const bool isUsage = false, const bool isRead = false);
				
				const struct Node::Instantaneous willPause(const bool requireBothBranches);
				
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_JUMP_STATEMENT_HPP
