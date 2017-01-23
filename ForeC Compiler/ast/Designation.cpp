/*
 *  Designation.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Designation.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int Designation::globalCount = 0;


		Designation::Designation(Node &node, const std::string &variant) : Node("Designation", variant, this->globalCount++) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}
		
		int Designation::getCount(void) {
			return globalCount;
		}
		

		void Designation::prettyPrint(std::ostream &output) {
			output << *children[0] << " =";
		}

	}
}
