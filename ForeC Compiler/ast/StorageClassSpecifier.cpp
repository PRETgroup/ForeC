/*
 *  StorageClassSpecifier.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "StorageClassSpecifier.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int StorageClassSpecifier::globalCount = 0;

		StorageClassSpecifier::StorageClassSpecifier(const std::string &variant) : Node("StorageClassSpecifier", variant, this->globalCount++) {
			
		}

		int StorageClassSpecifier::getCount(void) {
			return globalCount;
		}
		
		void StorageClassSpecifier::prettyPrint(std::ostream &output) {
			output << variant;
		}

	}
}
