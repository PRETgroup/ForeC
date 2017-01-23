/*
 *  LabeledStatement.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "LabeledStatement.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int LabeledStatement::globalCount = 0;


		LabeledStatement::LabeledStatement(Node &node, const std::string &variant) : Node("LabeledStatement", variant, this->globalCount++) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}

		LabeledStatement::LabeledStatement(Node &node0, Node &node1, const std::string &variant) : Node("LabeledStatement", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		int LabeledStatement::getCount(void) {
			return globalCount;
		}
		
		void LabeledStatement::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			if (isVariant("label")) {
				children[0]->updateSymbolTable("label");
				children[1]->updateSymbolTable();
			} else if (isVariant("case")) {
				children[1]->updateSymbolTable();
			} else if (isVariant("default")) {
				children[0]->updateSymbolTable();
			}
		}

		void LabeledStatement::prettyPrint(std::ostream &output) {
			if (variant.compare("label") == 0) {
				output << std::endl;
				tools::Tab::dedent();
				output << tools::Tab::toString() << *children[0] << ":" << std::endl;
				tools::Tab::indent();
				output << tools::Tab::toString() << *children[1];
			} else if (variant.compare("case") == 0) {
				output << std::endl;
				tools::Tab::dedent();
				output << tools::Tab::toString() << "case " << *children[0] << ":" << std::endl;
				tools::Tab::indent();
				output << tools::Tab::toString() << *children[1];
			} else if (variant.compare("default") == 0) {
				output << std::endl;
				tools::Tab::dedent();
				output << tools::Tab::toString() << "default:" << std::endl;
				tools::Tab::indent();
				output << tools::Tab::toString() << *children[0];
			}
		}

	}
}
