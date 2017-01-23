/*
 *  StructDeclaratorList.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "StructDeclaratorList.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int StructDeclaratorList::globalCount = 0;

		StructDeclaratorList::StructDeclaratorList(Node &node, const std::string &variant) : NodeList(node, "StructDeclaratorList", variant, this->globalCount++) {
			node.setParent((Node *)this);		
		}

		int StructDeclaratorList::getCount(void) {
			return globalCount;
		}
		
	}
}
