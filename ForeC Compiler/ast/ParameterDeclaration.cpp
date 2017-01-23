/*
 *  ParameterDeclaration.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "ParameterDeclaration.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int ParameterDeclaration::globalCount = 0;


		ParameterDeclaration::ParameterDeclaration(Node &node0, Node &node1, const std::string &variant) : Node("ParameterDeclaration", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		int ParameterDeclaration::getCount(void) {
			return globalCount;
		}
		
		void ParameterDeclaration::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			children.front()->updateSymbolTable("typedef", true);
			
			if (children.size() > 1) {
				children[1]->updateSymbolTable("variable", isUsage, isRead);
			}
		}
		
		void ParameterDeclaration::prettyPrint(std::ostream &output) {
			output << *children[0] << " " << *children[1];
		}

	}
}
