/*
 *  TernaryExpression.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "TernaryExpression.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int TernaryExpression::globalCount = 0;

		TernaryExpression::TernaryExpression(Node &node, const std::string &variant) : Node("TernaryExpression", variant, this->globalCount++) {
			children.push_back(&node);
			
			node.setParent((Node *)this);
		}

		TernaryExpression::TernaryExpression(Node &node0, Node &node1, Node &node2, const std::string &variant) : Node("TernaryExpression", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);
			children.push_back(&node2);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
			node2.setParent((Node *)this);
		}

		int TernaryExpression::getCount(void) {
			return globalCount;
		}
		
		void TernaryExpression::prettyPrint(std::ostream &output) {
			output << *children[0];
			
			if (children.size() == 3) {
					output << " ? " << *children[1] << " : " << *children[2];
			}
		}

	}
}
