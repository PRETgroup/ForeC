#ifndef FOREC_AST_ITERATION_STATEMENT_HPP
#define FOREC_AST_ITERATION_STATEMENT_HPP

/*
 *  IterationStatement.hpp
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
		class IterationStatement : public Node {
			public:
				IterationStatement(const unsigned int lineNumber, Node &node0, Node &node1, const std::string &variant);
				IterationStatement(const unsigned int lineNumber, Node &node0, Node &node1, Node &node2, const std::string &variant);
				IterationStatement(const unsigned int lineNumber, Node &node0, Node &node1, Node &node2, Node &node3, const std::string &variant);

				// Bounded
				IterationStatement(const unsigned int lineNumber, Node &node0, const std::string &lowerBound, const std::string &upperBound, Node &node1, const std::string &variant);
				IterationStatement(const unsigned int lineNumber, Node &node0, Node &node1, const std::string &lowerBound, const std::string &upperBound, const std::string &variant);
				IterationStatement(const unsigned int lineNumber, Node &node0, Node &node1, const std::string &lowerBound, const std::string &upperBound, Node &node2, const std::string &variant);
				IterationStatement(const unsigned int lineNumber, Node &node0, Node &node1, Node &node2, const std::string &lowerBound, const std::string &upperBound, Node &node3, const std::string &variant);

				const std::string getId(void) const;
				const std::string getThreadScope(void) const;

				static int getCount(void);
				
				void updateSymbolTable(const std::string &type = "none", const bool isUsage = false, const bool isRead = false);
				void createTarot(const std::string &threadScope, tarot::Node &tarotNode);

				const Node::Instantaneous willPause(const bool requireBothBranches);
				void setWillPause(const bool pauses);
				const bool getWillPause(void);

				void prettyPrint(std::ostream &output);

			protected:
				static int globalCount;
				const unsigned int lineNumber;
				
				bool isRoot;
				std::string threadScope;
				std::string lowerBound;
				std::string upperBound;
		};
	}
}

#endif // FOREC_AST_ITERATION_STATEMENT_HPP
