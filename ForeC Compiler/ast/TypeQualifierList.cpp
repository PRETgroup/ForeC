/*
 *  TypeQualifierList.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "TypeQualifierList.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int TypeQualifierList::globalCount = 0;

		TypeQualifierList::TypeQualifierList(Node &node, const std::string &variant) : NodeList(node, "TypeQualifierList", variant, this->globalCount++) {
			node.setParent((Node *)this);		
		}

		int TypeQualifierList::getCount(void) {
			return globalCount;
		}
		
		void TypeQualifierList::prettyPrint(std::ostream &output) {
			output << *children[0];
			
			if (children.size() > 1) {
				for (std::vector<Node *>::iterator i = children.begin() + 1; i != children.end(); ++i) {
					output << " " << *(*i);
				}
			}
		}

	}
}
