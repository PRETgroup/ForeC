#ifndef FOREC_AST_PAR_STATEMENT_HPP
#define FOREC_AST_PAR_STATEMENT_HPP

/*
 *  ParStatement.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class PrimaryExpression;
	}
	
	namespace tarot {
		class Node;
	}
}

namespace forec {
	namespace ast {
		class ParStatement : public Node {
			public:				
				ParStatement(Node &node, const std::string &variant = "none");

				const std::string getId(void) const;

				static int getCount(void);
	
				const std::string getThreadScope(void) const;
				const std::vector<std::string> getThreadIds(void) const;
				const bool hasThreadId(const std::string &threadId) const;
				
				void updateSymbolTable(const std::string &type = "none", const bool isUsage = false, const bool isRead = false);
				
				std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > > pullUpIndirectParallelVariables(void);
				void pullDownIndirectParallelVariables(std::set<PrimaryExpression *> &definedVariables);
				
				void createTarot(const std::string &threadScope, tarot::Node &tarotNode);
				
				const Node::Instantaneous willPause(const bool requireBothBranches);
				
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				std::string threadScope;
				std::vector<std::string> threadIds;
				
		};
	}
}

#endif // FOREC_AST_PAR_STATEMENT_HPP
