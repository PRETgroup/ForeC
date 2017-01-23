/*
 *  DeclarationList.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "DeclarationList.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int DeclarationList::globalCount = 0;

		DeclarationList::DeclarationList(Node &node, const std::string &variant) : NodeList(node, "DeclarationList", variant, this->globalCount++) {
			node.setParent((Node *)this);
		}

		int DeclarationList::getCount(void) {
			return globalCount;
		}
	
		
		void DeclarationList::prettyPrint(std::ostream &output) {
			output << *children[0];
			
			if (children.size() > 1) {
				for (std::vector<Node *>::iterator i = children.begin() + 1; i != children.end(); ++i) {
					output << " " << *(*i);
				}
			}
		}

	}
}
