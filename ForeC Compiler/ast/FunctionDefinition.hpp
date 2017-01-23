#ifndef FOREC_AST_FUNCTION_DEFINITION_HPP
#define FOREC_AST_FUNCTION_DEFINITION_HPP

/*
 *  FunctionDefinition.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class FunctionDefinition : public Node {
			public:				
				FunctionDefinition(Node &node0, Node &node1, Node &node2, const std::string &variant = "none");
				FunctionDefinition(Node &node0, Node &node1, Node &node2, Node &node3, const std::string &variant = "none");

				const std::string getIdentifier(void);
				
				void setThreads(std::vector<Node *> threads);
				void takeOutDeclarations(void);

				static int getCount(void);

				void updateSymbolTable(const std::string &type = "none", const bool isUsage = false, const bool isRead = false);
				void createTarot(const std::string &threadScope);
				
				const Node::Instantaneous willPause(const bool requireBothBranches);

				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				std::string identifier;
				std::vector<Node *> threads;
				std::vector<Node *> privateDeclarations;
				
		};
	}
}

#endif // FOREC_AST_FUNCTION_DEFINITION_HPP
