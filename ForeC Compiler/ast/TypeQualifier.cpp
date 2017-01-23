/*
 *  TypeQualifier.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "TypeQualifier.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int TypeQualifier::globalCount = 0;

		TypeQualifier::TypeQualifier(const std::string &variant) : Node("TypeQualifier", variant, this->globalCount++) {

		}

		int TypeQualifier::getCount(void) {
			return globalCount;
		}

		void TypeQualifier::prettyPrint(std::ostream &output) {
			if (isVariant("shared")  ||isVariant("input") || isVariant("output")) {
				output << "/* " << variant << " */";
			} else {
				output << variant;
			}
		}

	}
}
