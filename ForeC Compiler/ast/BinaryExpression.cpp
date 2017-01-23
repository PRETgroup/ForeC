/*
 *  BinaryExpression.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "BinaryExpression.hpp"

#include "DeclarationSpecifiers.hpp"
#include "PrimaryExpression.hpp"

#include "../tools/Query.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int BinaryExpression::globalCount = 0;

		BinaryExpression::BinaryExpression(Node &node, const std::string &variant) : Node("BinaryExpression", variant, this->globalCount++) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}

		BinaryExpression::BinaryExpression(Node &node0, Node &node1, const std::string &variant) : Node("BinaryExpression", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		BinaryExpression::BinaryExpression(Node &node0, Node &node1, Node &node2, const std::string &variant) : Node("BinaryExpression", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);
			children.push_back(&node2);
			
			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
			node2.setParent((Node *)this);
		}

		int BinaryExpression::getCount(void) {
			return globalCount;
		}

		void BinaryExpression::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			if (has("CombineSpecifier", "none")) {
				// Associate the combine function with the identifiers.
				std::vector<Node *> identifiersFound = tools::Query::retrieveAll(*children[0], "PrimaryExpression", "identifier");
				for (std::vector<Node *>::iterator identifier = identifiersFound.begin(); identifier != identifiersFound.end(); ++identifier) {
					((PrimaryExpression *)*identifier)->setCombineSpecifier(*children.back());
				}
			}
			
			if (isVariant(" = ")) {
				children[0]->updateSymbolTable(type, isUsage, false);
				children[1]->updateSymbolTable(type, isUsage, true);
				if (children.size() == 3) {
					children[2]->updateSymbolTable(type, isUsage, isRead);
				}
			} else {
				for (std::vector<Node *>::reverse_iterator i = children.rbegin(); i != children.rend(); ++i) {
					(*i)->updateSymbolTable(type, isUsage, isRead);
				}
			}
		}

		void BinaryExpression::prettyPrint(std::ostream &output) {
			// Find the shared variable.
			bool isShared = false;
			std::vector<Node *> identifiersFound = tools::Query::retrieveAll(*children[0], "PrimaryExpression", "identifier");
			PrimaryExpression *identifier = NULL;
			if (!identifiersFound.empty()) {
				identifier = (PrimaryExpression *)identifiersFound[0];
				isShared = (identifier->getType().compare("shared") == 0);
			}
		
			output << *children[0];
			if (isVariant(" = ")) {
				if (isShared) {
					// Shared variables are initialised as special structs.
					output << variant;
					if (identifier->getScope().compare("global") != 0) {
						output << '(' << *(forec::ast::DeclarationSpecifiers *)identifier->getSpecifiers() << ')';
					}
					output << "{.value = " << *children[1] << ", .status = FOREC_SHARED_UNMODIFIED}";
					if (children.size() == 3) {
						output << ' ' << *children[2];
					}
				} else {
					if (children.size() > 1) {
						output << variant << *children[1];
					}
				}
			} else {
				if (children.size() > 1) {
					if (!isVariant("declarator")) {
						output << variant;
					} else {
						output << ' ';
					}
					output << *children[1];
				}
			}
		}

	}
}
