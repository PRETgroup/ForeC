/*
 *  CastExpression.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "CastExpression.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int CastExpression::globalCount = 0;

		CastExpression::CastExpression(Node &node, const std::string &variant) : Node("CastExpression", variant, this->globalCount++) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}


		void CastExpression::prepend(Node &node) {
			children.insert(children.begin(), &node);

			node.setParent((Node *)this);
		}

		int CastExpression::getCount(void) {
			return globalCount;
		}
		
		void CastExpression::prettyPrint(std::ostream &output) {
			if (children.size() > 1) {
				for (std::vector<Node *>::iterator i = children.begin(); i != children.end() - 1; ++i) {
					output << "(" << *(*i) << ")";
				}
			}
			output << *(*(children.end() - 1));
		}

	}
}
