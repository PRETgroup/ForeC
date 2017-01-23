/*
 *  StructDeclaration.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "StructDeclaration.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int StructDeclaration::globalCount = 0;

		StructDeclaration::StructDeclaration(Node &node0, Node &node1, const std::string &variant) : Node("StructDeclaration", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		int StructDeclaration::getCount(void) {
			return globalCount;
		}
		
		void StructDeclaration::prettyPrint(std::ostream &output) {
			output << *children[0] << " " << *children[1] << ";";
		}

	}
}
