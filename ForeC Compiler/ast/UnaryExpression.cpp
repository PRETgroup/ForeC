/*
 *  UnaryExpression.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "UnaryExpression.hpp"

#include "PrimaryExpression.hpp"

#include "../tools/Query.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int UnaryExpression::globalCount = 0;

		UnaryExpression::UnaryExpression(Node &node, const std::string &variant) : Node("UnaryExpression", variant, this->globalCount++) {
			children.push_back(&node);
			
			node.setParent((Node *)this);
		}

		UnaryExpression::UnaryExpression(const std::string unaryOperator, Node &node, const std::string &variant) : Node("UnaryExpression", variant, this->globalCount++), unaryOperator(unaryOperator) {
			children.push_back(&node);
			
			if (unaryOperator.compare("&") == 0) {
				std::vector<Node *> identifiersFound = tools::Query::retrieveAll(node, "PrimaryExpression", "identifier");
				for (std::vector<Node *>::iterator identifier = identifiersFound.begin(); identifier != identifiersFound.end(); ++identifier) {
					((PrimaryExpression *)*identifier)->setIsPointer(true);
				}
			}
			
			node.setParent((Node *)this);
		}

		int UnaryExpression::getCount(void) {
			return globalCount;
		}
		
		void UnaryExpression::prettyPrint(std::ostream &output) {
			if (isVariant("increment")) {
				output << "++" << *children[0];
			} else if (isVariant("decrement")) {
				output << "--" << *children[0];
			} else if (isVariant("cast")) {
				output << unaryOperator;
				if (unaryOperator.compare("*") == 0) {
					output << " ";
				}
				output << *children[0];
			} else if (isVariant("sizeof0")) {
				output << "sizeof " << *children[0];
			} else if (isVariant("sizeof1")) {
				output << "sizeof(" << *children[0] << ")";
			}
		}

	}
}
