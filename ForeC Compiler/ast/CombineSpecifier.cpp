/*
 *  CombineSpecifier.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 27/05/13.
 *  Copyright 2013 Potential Publishers. All rights reserved.
 *
 */

#include "CombineSpecifier.hpp"

#include "../tools/SymbolTable.hpp"

namespace forec {
	namespace ast {
	
		// Initialise static variable
		int CombineSpecifier::globalCount = 0;
		
		CombineSpecifier::CombineSpecifier(const std::string &terminal, const std::string &variant) : Node("CombineSpecifier", variant, this->globalCount++), terminal(terminal) {
			
		}

		int CombineSpecifier::getCount(void) {
			return globalCount;
		}
		
		const std::string CombineSpecifier::getTerminal(void) const {
			return terminal;
		}

		void CombineSpecifier::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			tools::SymbolTable::addCombineSpecifier(this->getTerminal());
		}
		
		void CombineSpecifier::prettyPrint(std::ostream &output) {
			output << "/* combine with " << terminal << " */";
		}

	}
}