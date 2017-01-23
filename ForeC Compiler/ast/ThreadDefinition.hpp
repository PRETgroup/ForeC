#ifndef FOREC_AST_THREAD_DEFINITION_HPP
#define FOREC_AST_THREAD_DEFINITION_HPP

/*
 *  ThreadDefinition.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class ThreadDefinition : public Node {
			public:				
				ThreadDefinition(Node &node0, Node &node1, const std::string &variant = "none");

				void takeOutDeclarations(void);

				const std::string getId(void) const;
				static int getCount(void);
				
				void updateSymbolTable(const std::string &type = "none", const bool isUsage = false, const bool isRead = false);
				void createTarot(const std::string &threadScope);
				
				const Node::Instantaneous willPause(const bool requireBothBranches);
				std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > > pullUpIndirectParallelVariables(void);
				void pullDownIndirectParallelVariables(std::set<PrimaryExpression *> &definedVariables);		
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				std::string identifier;
				std::vector<Node *> privateDeclarations;
			
		};
	}
}

#endif // FOREC_AST_THREAD_DEFINITION_HPP
