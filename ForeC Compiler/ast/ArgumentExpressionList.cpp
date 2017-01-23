/*
 *  ArgumentExpressionList.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "ArgumentExpressionList.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int ArgumentExpressionList::globalCount = 0;

		ArgumentExpressionList::ArgumentExpressionList(Node &node, const std::string &variant) : NodeList(node, "ArgumentExpressionList", variant, this->globalCount++) {
			node.setParent((Node *)this);
		}
		
		int ArgumentExpressionList::getCount(void) {
			return globalCount;
		}
		
	}
}
