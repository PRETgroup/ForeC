/*
 *  AbstractDeclarator.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "AbstractDeclarator.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int AbstractDeclarator::globalCount = 0;

		AbstractDeclarator::AbstractDeclarator(Node &node0, Node &node1, const std::string &variant) : Node("AbstractDeclarator", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		int AbstractDeclarator::getCount(void) {
			return globalCount;
		}
		
		void AbstractDeclarator::prettyPrint(std::ostream &output) {
			output << *children[0] << " " << *children[1];
		}

	}
}
