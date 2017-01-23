/*
 *  StructDeclarator.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "StructDeclarator.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int StructDeclarator::globalCount = 0;

		StructDeclarator::StructDeclarator(Node &node, const std::string &variant) : Node("StructDeclarator", variant, this->globalCount++) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}

		StructDeclarator::StructDeclarator(Node &node0, Node &node1, const std::string &variant) : Node("StructDeclarator", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		int StructDeclarator::getCount(void) {
			return globalCount;
		}
	
		
		void StructDeclarator::prettyPrint(std::ostream &output) {
			if (variant.compare("constantExpression") == 0) {
				output << ": " << *children[0];
			} else if (variant.compare("full") == 0) {
				output << *children[0] << " : " << *children[1];
			}
		}

	}
}
