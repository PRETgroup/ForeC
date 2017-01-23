/*
 *  AssignmentOperator.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "AssignmentOperator.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int AssignmentOperator::globalCount = 0;

		AssignmentOperator::AssignmentOperator(const std::string &variant) : Node("AssignmentOperator", variant, this->globalCount++) {
			
		}

		int AssignmentOperator::getCount(void) {
			return globalCount;
		}
		

		void AssignmentOperator::prettyPrint(std::ostream &output) {
			output << variant;
		}

	}
}
