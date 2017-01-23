/*
 *  Expression.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Expression.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int Expression::globalCount = 0;

		Expression::Expression(Node &node, const std::string &variant) : NodeList(node, "Expression", variant, this->globalCount++) {
			node.setParent((Node *)this);
		}

		int Expression::getCount(void) {
			return globalCount;
		}
		
	}
}
