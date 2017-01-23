/*
 *  Designator.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Designator.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int Designator::globalCount = 0;


		Designator::Designator(Node &node, const std::string &variant) : Node("Designator", variant, this->globalCount++) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}
		
		int Designator::getCount(void) {
			return globalCount;
		}
		
		void Designator::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			if (isVariant("index")) {
				for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
					(*i)->updateSymbolTable(type, isUsage, isRead);
				}
			}
		}
		
		void Designator::prettyPrint(std::ostream &output) {
			if (variant.compare("index") == 0) {
				output << "[" << *children[0] << "]";
			} else if (variant.compare("member") == 0) {
				output << "." << *children[0];
			}
		}

	}
}
