/*
 *  JumpStatement.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "JumpStatement.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int JumpStatement::globalCount = 0;

		JumpStatement::JumpStatement(const std::string &variant) : Node("JumpStatement", variant, this->globalCount++) {

		}

		JumpStatement::JumpStatement(Node &node, const std::string &variant) : Node("JumpStatement", variant, this->globalCount++) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}

		int JumpStatement::getCount(void) {
			return globalCount;
		}
		
		void JumpStatement::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			if (isVariant("goto")) {
				children[0]->updateSymbolTable("label", true, true);
			} else if (isVariant("returnExpression")) {
				children[0]->updateSymbolTable();
			}
		}

		const struct Node::Instantaneous JumpStatement::willPause(const bool requireBothBranches) {
			instantaneous.pauses = false;
			instantaneous.breaks = isVariant("break");
			instantaneous.continues = isVariant("continue");
			instantaneous.returns = isVariant("return");
			
			return instantaneous;
		}

		void JumpStatement::prettyPrint(std::ostream &output) {
			if (isVariant("goto")) {
				output << "goto " << *children[0];
			} else if (isVariant("continue")) {
				output << "continue";
			} else if (isVariant("break")) {
				output << "break";
			} else if (isVariant("return")) {
				output << "return";
			} else if (isVariant("returnExpression")) {
				output << "return " << *children[0];
			}
			
			output << ";";
		}

	}
}
