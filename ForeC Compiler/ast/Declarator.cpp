/*
 *  Declarator.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Declarator.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int Declarator::globalCount = 0;

		Declarator::Declarator(Node &node0, Node &node1, const std::string &variant) : Node("Declarator", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		int Declarator::getCount(void) {
			return globalCount;
		}
		

		void Declarator::prettyPrint(std::ostream &output) {
			output << *children[0];
			
			if (!children[0]->isVariant("asterisk")) {
				output << " ";
			}
			
			output << *children[1];
		}

	}
}
