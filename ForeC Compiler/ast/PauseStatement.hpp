#ifndef FOREC_AST_PAUSE_STATEMENT_HPP
#define FOREC_AST_PAUSE_STATEMENT_HPP

/*
 *  PauseStatement.hpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class AbortStatement;
		class ParStatement;
		class PrimaryExpression;
	}

	namespace tarot {
		class Node;
	}	
}

namespace forec {
	namespace ast {
		class PauseStatement : public Node {
			public:
				PauseStatement(const std::string &variant = "none");

				const std::string getId(void) const;

				static int getCount(void);

				void updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead = false);
				void createTarot(const std::string &threadScope, tarot::Node &tarotNode);

				const Node::Instantaneous willPause(const bool requireBothBranches);

				void prettyPrint(std::ostream &output);


			protected:
				static int globalCount;
				std::string threadScope;
				std::vector<AbortStatement *> aborts;
		};
	}
}

#endif // FOREC_AST_PAUSE_STATEMENT_HPP
