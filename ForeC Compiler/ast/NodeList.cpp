/*
 *  NodeList.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "NodeList.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int NodeList::globalCount = 0;

		NodeList::NodeList(Node &node, const std::string &type, const std::string &variant, const int id) : Node(type, variant, id) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}


		void NodeList::prettyPrint(std::ostream &output) {
			if (children.size() > 0) {
				output << *children[0];
			
				if (children.size() > 1) {
					for (std::vector<Node *>::iterator i = children.begin() + 1; i != children.end(); ++i) {
						output << ", " << *(*i);
					}
				}
			}
		}

	}
}
