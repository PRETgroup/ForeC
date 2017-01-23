/*
 *  Operand.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 08/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Operand.hpp"

namespace forec {
	namespace cfg {
		
		// Initialise static variable
		int Operand::globalCount = 0;
		
		Operand::Operand(const std::string &value, const std::string &variant) : Node("Operand", variant, this->globalCount++), value(value) {
			
		}

		Operand::Operand(const Node &operand1, const std::string &variant) : Node("Operand", variant, this->globalCount++), operand1(&operand1) {
			
		}

		Operand::Operand(const Node &operand1, const Node &operand2, const std::string &variant) : Node("Operand", variant, this->globalCount++), operand1(&operand1), operand2(&operand2) {
			
		}
		
		const int Operand::getCount(void) {
			return globalCount;
		}
		
		const std::string Operand::getValue(void) {
			if (isVariant("address1")) {
				return "[" + ((Operand *)operand1)->getValue() + "]";
			} else if (isVariant("address2")) {
				return "[" + ((Operand *)operand1)->getValue() + ", " + ((Operand *)operand2)->getValue() + "]";
			}
			
			return value;
		}
		
		void Operand::toXml(std::ostream &output) {
			output << tools::Tab::toString() << "<" << getVariant() << ">" << std::endl;
			output << tools::Tab::toString() << "\t" << getValue() << std::endl;
			output << tools::Tab::toString() << "</" << getVariant() << ">" << std::endl;
		}
		
		void Operand::toUppaal(std::ostream &output) {
			// Nothing.
		}
		
		void Operand::toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) {
			// Nothing.
		}
		
		void Operand::prettyPrint(std::ostream &output) {
			output << getValue();
		}
		
	}
}

