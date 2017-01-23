/*
 *  AssignmentExpression.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "AssignmentExpression.hpp"

#include "PrimaryExpression.hpp"

#include "../tools/Query.hpp"
#include "../tools/SymbolTable.hpp"
#include "../tools/Tab.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int AssignmentExpression::globalCount = 0;

		AssignmentExpression::AssignmentExpression(Node &node, const std::string &variant) : Node("AssignmentExpression", variant, this->globalCount++) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}

		AssignmentExpression::AssignmentExpression(Node &node0, Node &node1, Node &node2, const std::string &variant) : Node("AssignmentExpression", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);
			children.push_back(&node2);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
			node2.setParent((Node *)this);
		}

		int AssignmentExpression::getCount(void) {
			return globalCount;
		}

		void AssignmentExpression::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			if (children.size() > 1) {
				children[2]->updateSymbolTable("variable", true, true);
				children[0]->updateSymbolTable("variable", true, false);
			} else {
				children[0]->updateSymbolTable("variable", true, true);
			}
		}

		void AssignmentExpression::prettyPrint(std::ostream &output) {
			output << *children[0];
			if (children.size() == 3) {
				output << " " << *children[1] << " " << *children[2];
				
				// Update the modified status if the lhs is a shared variable.
				std::vector<Node *> identifiersFound = tools::Query::retrieveAll(*children[0], "PrimaryExpression", "identifier");
				if (!identifiersFound.empty()) {
					PrimaryExpression *identifier = (PrimaryExpression *)identifiersFound[0];
					if (identifier->getDeclaration() != NULL) {
						if (identifier->getDeclaration()->getType().compare("shared") == 0) {
							const std::map<forec::ast::PrimaryExpression *, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > indirectParallelThreadUseDef = tools::SymbolTable::getIndirectParallelThread(true, true, identifier->getScope());
							const tools::SymbolTable::UpdateType updateType = indirectParallelThreadUseDef.find(identifier->getDeclaration())->second.first;
							if (updateType == tools::SymbolTable::intermediate) {
								output << ';' << std::endl;
								output << tools::Tab::toString() << identifier->getSharedSymbolString() << ".status = FOREC_SHARED_MODIFIED";
							}
						}
					}
				}
			}
		}

	}
}
