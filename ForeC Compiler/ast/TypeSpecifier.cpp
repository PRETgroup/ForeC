/*
 *  TypeSpecifier.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "TypeSpecifier.hpp"
#include "PrimaryExpression.hpp"

#include "../tools/SymbolTable.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int TypeSpecifier::globalCount = 0;

		TypeSpecifier::TypeSpecifier(const std::string &variant) : Node("TypeSpecifier", variant, this->globalCount++) {

		}

		TypeSpecifier::TypeSpecifier(PrimaryExpression &terminal, const std::string &variant) : Node("TypeSpecifier", variant, this->globalCount++), terminal(&terminal) {

		}

		const int TypeSpecifier::getCount(void) {
			return globalCount;
		}
		
		void TypeSpecifier::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			if (isVariant("typedef")) {
//				std::cout << "TypeSpecifier: " << *terminal << ' ' << type << ' ' << isUsage << std::endl;
				terminal->updateSymbolTable(type, isUsage, isRead);
			}
		}
		
		void TypeSpecifier::prettyPrint(std::ostream &output) {
			if (isVariant("typedef")) {
				output << *terminal;
			} else {
				output << variant;
			}
		}

	}
}
