/*
 *  Enumerator.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Enumerator.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int Enumerator::globalCount = 0;
		
		Enumerator::Enumerator(Node &node0, Node &node1, const std::string &variant) : Node("Enumerator", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		int Enumerator::getCount(void) {
			return globalCount;
		}
		
		void Enumerator::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			children[1]->updateSymbolTable("variable", true, true);
			children[0]->updateSymbolTable(type, false, false);
		}
		
		void Enumerator::prettyPrint(std::ostream &output) {
			output << *children[0] << " = " << *children[1];
		}

	}
}
