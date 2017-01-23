/*
 *  CSourceLine.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 09/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "CSourceLine.hpp"

namespace forec {
	namespace cfg {
		
		// Initialise static variable
		int CSourceLine::globalCount = 0;
		
		CSourceLine::CSourceLine(const CSourceLine &original) : Node("CSourceLine", original.variant, this->globalCount++), source(original.source) {
								
		}
		
		CSourceLine::CSourceLine(const std::string &variant): Node("CSourceLine", variant, this->globalCount++) {
			
		}
		
		CSourceLine::CSourceLine(std::string &source, const std::string &variant): Node("CSourceLine", variant, this->globalCount++), source(source) {
			
		}
		
		const int CSourceLine::getCount(void) {
			return globalCount;
		}
		
		void CSourceLine::inlineFunctions(void) {
			// Nothing.
		}

		void CSourceLine::toXml(std::ostream &output) {
			output << tools::Tab::toString() << "<source type=\"c\">" << std::endl;
			output << tools::Tab::toString() << "\t<![CDATA[" << source << "]]>" << std::endl;
			output << tools::Tab::toString() << "</source>" << std::endl;
		}
		
		void CSourceLine::toUppaal(std::ostream &output) {
			// Nothing.
		}
		
		void CSourceLine::toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) {
			// Nothing.
		}

		void CSourceLine::prettyPrint(std::ostream &output) {
			output << source;
		}
		
	}
}

