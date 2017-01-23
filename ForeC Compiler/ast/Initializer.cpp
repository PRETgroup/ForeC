/*
 *  Initializer.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Initializer.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int Initializer::globalCount = 0;

		Initializer::Initializer(Node &node, const std::string &variant) : Node("Initializer", variant, this->globalCount++) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}
		
		
		int Initializer::getCount(void) {
			return globalCount;
		}
		
		void Initializer::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			children[0]->updateSymbolTable("variable", true, true);
		}
		
		void Initializer::prettyPrint(std::ostream &output) {
			if (variant.compare("initializerList0") == 0) {
				output << "{" << *children[0] << "}";
			} else if (variant.compare("initializerList1") == 0) {
				output << "{" << *children[0] << ", }";
			}

		}

	}
}
