/*
 *  OperandList.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 08/10/10.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "OperandList.hpp"

namespace forec {
	namespace cfg {
		
		// Initialise static variable
		int OperandList::globalCount = 0;
		
		OperandList::OperandList(Node &node, const std::string &variant) : NodeList(node, "OperandList", variant, this->globalCount++) {
			node.setParent((Node *)this);		
		}
		
		int OperandList::getCount(void) {
			return globalCount;
		}

		std::vector<Node *> OperandList::getOperands(void) {
			return children;
		}
		
		void OperandList::inlineFunctions(void) {
			// Nothing.
		}
		
		void OperandList::toXml(std::ostream &output) {
			output << tools::Tab::toString() << "<operands>" << std::endl;
			tools::Tab::indent();	
						
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->toXml(output);
			}
				
			tools::Tab::dedent();
			output << tools::Tab::toString() << "</operands>" << std::endl;
		}

		void OperandList::toUppaal(std::ostream &output) {
			// Nothing.
		}
		
		void OperandList::toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) {
			// Nothing.
		}
		
	}
}
