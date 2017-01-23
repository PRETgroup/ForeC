/*
 *  PreProcessorDirective.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "PreProcessorDirective.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int PreProcessorDirective::globalCount = 0;

		PreProcessorDirective::PreProcessorDirective(const std::string &directive, const std::string &variant) : Node("PreProcessorDirective", variant, this->globalCount++), directive(directive) {
			
		}


		int PreProcessorDirective::getCount(void) {
			return globalCount;
		}
		
		void PreProcessorDirective::prettyPrint(std::ostream &output) {
			output << directive;
		}

	}
}
