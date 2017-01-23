/*
 *  SpecifierQualifierList.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "SpecifierQualifierList.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int SpecifierQualifierList::globalCount = 0;

		SpecifierQualifierList::SpecifierQualifierList(Node &node, const std::string &variant) : NodeList(node, "SpecifierQualifierList", variant, this->globalCount++) {
			node.setParent((Node *)this);
		}

		int SpecifierQualifierList::getCount(void) {
			return globalCount;
		}
		
		void SpecifierQualifierList::prettyPrint(std::ostream &output) {
			output << *children[0];
			
			if (children.size() > 1) {
				for (std::vector<Node *>::iterator i = children.begin() + 1; i != children.end(); ++i) {
					output << " " << *(*i);
				}
			}
		}
		
	}
}
