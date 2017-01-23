/*
 *  ExpressionStatement.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "ExpressionStatement.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int ExpressionStatement::globalCount = 0;


		ExpressionStatement::ExpressionStatement(const std::string &variant) : Node("ExpressionStatement", variant, this->globalCount++) {

		}

		ExpressionStatement::ExpressionStatement(Node &node, const std::string &variant) : Node("ExpressionStatement", variant, this->globalCount++) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}

		int ExpressionStatement::getCount(void) {
			return globalCount;
		}
		
		void ExpressionStatement::prettyPrint(std::ostream &output) {
			if (children.size() == 1) {
				output << *children[0];
			}
			
			output << ";";
		}

	}
}
