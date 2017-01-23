#ifndef FOREC_AST_ABORT_STATEMENT_HPP
#define FOREC_AST_ABORT_STATEMENT_HPP

/*
 *  AbortStatement.hpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */


#include "Node.hpp"

namespace forec {
	namespace tarot {
		class Node;
	}
}

namespace forec {
	namespace ast {
		class AbortStatement : public Node {
			public:
				AbortStatement(Node &node0, Node &node1, const std::string &variant = "none");

				const std::string getId(void) const;
				const std::string getCondition(const bool suppressCopySuffix);
				const std::string getThreadScope(void) const;

				static int getCount(void);

				void updateSymbolTable(const std::string &type, const bool isUsage = false, const bool isRead = false);
				void createTarot(const std::string &threadScope, tarot::Node &tarotNode);

				const struct Node::Instantaneous willPause(const bool requireBothBranches);

				void prettyPrint(std::ostream &output);


			protected:
				static int globalCount;
				std::string threadScope;
		};
	}
}

#endif // FOREC_AST_ABORT_STATEMENT_HPP
