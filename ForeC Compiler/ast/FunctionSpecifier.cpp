/*
 *  FunctionSpecifier.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "FunctionSpecifier.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int FunctionSpecifier::globalCount = 0;

		FunctionSpecifier::FunctionSpecifier(const std::string &variant) : Node("FunctionSpecifier", variant, this->globalCount++) {
			
		}

		int FunctionSpecifier::getCount(void) {
			return globalCount;
		}
		
		void FunctionSpecifier::prettyPrint(std::ostream &output) {
			output << variant;
		}

	}
}
