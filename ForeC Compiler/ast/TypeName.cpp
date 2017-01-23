/*
 *  TypeName.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "TypeName.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int TypeName::globalCount = 0;

		TypeName::TypeName(Node &node, const std::string &variant) : Node("TypeName", variant, this->globalCount++) {
			children.push_back(&node);
			
			node.setParent((Node *)this);
		}

		TypeName::TypeName(Node &node0, Node &node1, const std::string &variant) : Node("TypeName", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);
			
			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		int TypeName::getCount(void) {
			return globalCount;
		}
		
		void TypeName::prettyPrint(std::ostream &output) {
			output << *children[0];
		
			if (children.size() == 2) {
				output << " " << *children[1];
			}
		}

	}
}
