/*
 *  PostfixExpression.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "PostfixExpression.hpp"

#include "FunctionDefinition.hpp"
#include "PrimaryExpression.hpp"

#include "../tools/Function.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int PostfixExpression::globalCount = 0;

		PostfixExpression::PostfixExpression(Node &node, const std::string &variant) : Node("PostfixExpression", variant, this->globalCount++) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}

		PostfixExpression::PostfixExpression(Node &node0, Node &node1, const std::string &variant) : Node("PostfixExpression", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		int PostfixExpression::getCount(void) {
			return globalCount;
		}

		void PostfixExpression::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			if (isVariant("member") || isVariant("pointer")) {
				children[0]->updateSymbolTable(type, isUsage, isRead);
			} else if (isVariant("function0")) {
				children[0]->updateSymbolTable("function", isUsage, isRead);
			} else if (isVariant("function1")) {
				children[0]->updateSymbolTable("function", isUsage, isRead);
				children[1]->updateSymbolTable("variable", true, true);
			} else {
				for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
					(*i)->updateSymbolTable(type, isUsage, isRead);
				}
			}
		}

		const Node::Instantaneous PostfixExpression::willPause(const bool requireBothBranches) {
			instantaneous.pauses = false;
			instantaneous.breaks = false;
			instantaneous.continues = false;
			instantaneous.returns = false;
			
			if (isVariant("function0") || isVariant("function1")) {
				const std::string name = ((PrimaryExpression *)children[0])->getTerminal();
				try {
					FunctionDefinition *function = tools::Function::getDeclaration(name);
					const struct Node::Instantaneous result = function->willPause(requireBothBranches);
					instantaneous.pauses = result.pauses;
				} catch (std::string error) {
					if (error.find("Function::getDeclaration:") != std::string::npos){
						std::cout << std::endl << "!!  PostfixExpression::willPause: Assuming \"" << name << "\"() terminates instantly.";
					} else {
						throw error;
					}
				}
			}
			
			return instantaneous;
		}

		void PostfixExpression::prettyPrint(std::ostream &output) {
			if (isVariant("index")) {
				output << *children[0] << "[" << *children[1] << "]";
			} else if (isVariant("function0")) {
				output << *children[0] << "()";
			} else if (isVariant("function1")) {
				output << *children[0] << "(" << *children[1] << ")";
			} else if (isVariant("member")) {
				output << *children[0] << "." << *children[1];
			} else if (isVariant("pointer")) {
				output << *children[0] << "->" << *children[1];
			} else if (isVariant("increment")) {
				output << *children[0] << "++";
			} else if (isVariant("decrement")) {
				output << *children[0] << "--";
			} else if (isVariant("cast0")) {
				output << "(" << *children[0] << ") {" << *children[1] << "}";
			} else if (isVariant("cast1")) {
				output << "(" << *children[0] << ") {" << *children[1] << ", }";
			}
		}

	}
}
