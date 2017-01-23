/*
 *  Label.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 09/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Label.hpp"

#include "../tools/Function.hpp"

namespace forec {
	namespace cfg {
		
		// Initialise static variable
		int Label::globalCount = 0;
		
		Label::Label(const std::string &address, const std::string &label, const std::string &variant): Node("Label", variant, this->globalCount++), address(address), label(label) {

		}
		
		const int Label::getCount(void) {
			return globalCount;
		}

		const std::string Label::getId(void) {
			return label;
		}
		
		const int Label::getLatency(void) {
			return 0;			
		}

		const std::string Label::getAddress(void) {
			return address;
		}

		void Label::linkNodes(void) {
			tools::Link::setPrevious(*this);
		}

		void Label::inlineFunctions(void) {
			// Nothing.
		}

		void Label::toXml(std::ostream &output) {
			output << tools::Tab::toString() << "<source type=\"assembly\" id=\"" << getId() << "\">" << std::endl;
			tools::Tab::indent();
			
			output << tools::Tab::toString() << "<label address=\"" << address << "\">" << std::endl;
			output << tools::Tab::toString() << "\t" << label << std::endl;
			output << tools::Tab::toString() << "</label>" << std::endl;

			for (std::vector<Node *>::iterator i = previousNodes.begin(); i != previousNodes.end(); ++i) {
				output << tools::Tab::toString() << "<previous node=\"" << (*i)->getId() << "\" />" << std::endl;
			}
			
			for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
				output << tools::Tab::toString() << "<next node=\"" << i->first->getId() << "\" latency=\"" << i->second.first << "\" />" << std::endl;
			}
			
			tools::Tab::dedent();
			output << tools::Tab::toString() << "</source>" << std::endl;		
		}

		void Label::toUppaal(std::ostream &output) {
			// Nothing.
		}
		
		void Label::toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) {
			// Nothing.
		}

		void Label::prettyPrint(std::ostream &output) {
			output << address << " <" << label << ">:";
		}
		
	}
}

