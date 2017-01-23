/*
 *  InitDeclaratorList.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "InitDeclaratorList.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int InitDeclaratorList::globalCount = 0;

		InitDeclaratorList::InitDeclaratorList(Node &node, const std::string &variant) : NodeList(node, "InitDeclaratorList", variant, this->globalCount++) {
			node.setParent((Node *)this);
		}

		int InitDeclaratorList::getCount(void) {
			return globalCount;
		}
		
	}
}
