#ifndef FOREC_AST_NODE_HPP
#define FOREC_AST_NODE_HPP

/*
 *  Node.hpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>

#include "../tools/SymbolTable.hpp"
#include "../tools/Tab.hpp"

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
		class Node {
			friend std::ostream &operator<<(std::ostream &output, Node &node);

			public:
				struct Instantaneous {
					bool found;
					
					bool pauses;
					bool breaks;
					bool continues;
					bool returns;
				};
			
				Node(const std::string &type, const std::string &variant, const int id);

				const std::string getId(void) const;
				const std::string getIdNumber(void) const;

				const bool isType(const std::string &type) const;
				const std::string getType(void) const;

				const bool isVariant(const std::string &variant) const;
				const std::string getVariant(void) const;

				void setParent(Node *node);
				Node *getParent(void) const;
				void takeOut(std::vector<Node *> &nodes);
				void remove(const Node *node);
				void replace(Node *oldNode, Node *newNode);

				static int getGlobalCount(void);

				virtual void append(Node &node);
				virtual void prepend(Node &node);

				virtual const bool has(const std::string &type, const std::string &variant);
				virtual std::vector<Node *> find(const std::string &type, const std::string &variant);
				virtual std::vector<Node *> findAll(const std::string &type, const std::string &variant);
				
				virtual const struct Instantaneous willPause(const bool requireBothBranches);

				virtual void updateSymbolTable(const std::string &type = "none", const bool isUsage = false, const bool isRead = false);
				virtual std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > > pullUpIndirectParallelVariables(void);
				virtual void pullDownIndirectParallelVariables(std::set<PrimaryExpression *> &definedVariables);
				
				virtual void createTarot(const std::string &threadScope);
				virtual void createTarot(const std::string &threadScope, tarot::Node &tarotNode);

				virtual void prettyPrint(std::ostream &output) = 0;
				virtual std::string *toString(void);


			protected:
				static int globalCount;
				const int id;
				const std::string type;
				const std::string variant;
				
				Instantaneous instantaneous;
				
				Node *parent;
				std::vector<Node *> children;
		};
	}
}

#endif // FOREC_AST_NODE_HPP
