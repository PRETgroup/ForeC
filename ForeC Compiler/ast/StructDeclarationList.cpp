/*
 *  StructDeclarationList.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "StructDeclarationList.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int StructDeclarationList::globalCount = 0;

		StructDeclarationList::StructDeclarationList(Node &node, const std::string &variant) : NodeList(node, "StructDeclarationList", variant, this->globalCount++) {
			node.setParent((Node *)this);		
		}

		int StructDeclarationList::getCount(void) {
			return globalCount;
		}
		
		
	
		void StructDeclarationList::prettyPrint(std::ostream &output) {
			output << tools::Tab::toString() << *children[0];
			
			if (children.size() > 1) {
				for (std::vector<Node *>::iterator i = children.begin() + 1; i != children.end(); ++i) {
					output << std::endl << tools::Tab::toString() << *(*i);
				}
			}
		}

	}
}
