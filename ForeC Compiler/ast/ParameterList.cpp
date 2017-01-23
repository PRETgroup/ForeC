/*
 *  ParameterList.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "ParameterList.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int ParameterList::globalCount = 0;

		ParameterList::ParameterList(Node &node, const std::string &variant) : NodeList(node, "ParameterList", variant, this->globalCount++) {
			node.setParent((Node *)this);
		}

		int ParameterList::getCount(void) {
			return globalCount;
		}
		
	}
}
