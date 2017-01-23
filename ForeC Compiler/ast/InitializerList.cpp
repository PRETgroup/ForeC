/*
 *  InitializerList.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "InitializerList.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int InitializerList::globalCount = 0;


		InitializerList::InitializerList(Node &node0, Node &node1, const std::string &variant) : Node("InitializerList", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		InitializerList::InitializerList(Node &node0, Node &node1, Node &node2, const std::string &variant) : Node("InitializerList", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);
			children.push_back(&node2);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
			node2.setParent((Node *)this);
		}

		int InitializerList::getCount(void) {
			return globalCount;
		}

		void InitializerList::prettyPrint(std::ostream &output) {
			if (variant.compare("designation") == 0) {
				output << *children[0] << " " << *children[1];
			} else if (variant.compare("initializer") == 0) {
				output << *children[0] << ", " << *children[1];
			} else if (variant.compare("designationInitalizer") == 0) {
				output << *children[0] << ", " << *children[1] << " " << *children[2];
			}
		}

	}
}
