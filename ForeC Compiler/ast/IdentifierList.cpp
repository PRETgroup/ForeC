/*
 *  IdentifierList.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "IdentifierList.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int IdentifierList::globalCount = 0;

		IdentifierList::IdentifierList(Node &node, const std::string &variant) : NodeList(node, "IdentifierList", variant, this->globalCount++) {
			node.setParent((Node *)this);
		}
		
		int IdentifierList::getCount(void) {
			return globalCount;
		}	
			
		void IdentifierList::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->updateSymbolTable(type, true, true);
			}
		}
		
	}
}
