/*
 *  DesignatorList.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "DesignatorList.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int DesignatorList::globalCount = 0;

		DesignatorList::DesignatorList(Node &node, const std::string &variant) : NodeList(node, "DesignatorList", variant, this->globalCount++) {
			node.setParent((Node *)this);	
		}

		int DesignatorList::getCount(void) {
			return globalCount;
		}
		
		void DesignatorList::prettyPrint(std::ostream &output) {
			output << *children[0];

			if (children.size() > 1) {
				for (std::vector<Node *>::iterator i = children.begin() + 1; i != children.end(); ++i) {
					output << " " << *(*i);
				}
			}
		}

	}
}
