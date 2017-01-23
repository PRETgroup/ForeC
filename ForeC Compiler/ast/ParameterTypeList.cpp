/*
 *  ParameterTypeList.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "ParameterTypeList.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int ParameterTypeList::globalCount = 0;

		ParameterTypeList::ParameterTypeList(Node &node, const std::string &variant) : NodeList(node, "ParameterTypeList", variant, this->globalCount++) {
			node.setParent((Node *)this);	
		}

		int ParameterTypeList::getCount(void) {
			return globalCount;
		}
		
		void ParameterTypeList::prettyPrint(std::ostream &output) {
			output << *children[0] << ", ...";
		}

	}
}
