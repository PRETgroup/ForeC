/*
 *  Pointer.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Pointer.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int Pointer::globalCount = 0;

		Pointer::Pointer(const std::string &variant) : Node("Pointer", variant, this->globalCount++) {

		}

		Pointer::Pointer(Node &node, const std::string &variant) : Node("Pointer", variant, this->globalCount++) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}

		Pointer::Pointer(Node &node0, Node &node1, const std::string &variant) : Node("Pointer", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		int Pointer::getCount(void) {
			return globalCount;
		}
		
		void Pointer::prettyPrint(std::ostream &output) {
			output << "*";
			if (children.size() > 0) {
				output << *children[0];
			}

			if (children.size() == 2) {
				output << " " << *children[1];
			}
		}

	}
}
