/*
 *  Start.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 09/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Start.hpp"

#include "../tools/Function.hpp"

namespace forec {
	namespace cfg {
		
		// Initialise static variable
		int Start::globalCount = 0;
		
		Start::Start(const unsigned int programCounter, const std::string &variant): Node("Start", variant, this->globalCount++), programCounter(programCounter) {

		}
		
		const int Start::getCount(void) {
			return globalCount;
		}

		const unsigned int Start::getProgramCounter(void) {
			return programCounter;
		}

		const int Start::getInstructionLatency(void) {
			return 0;
		}
		
		void Start::linkNodes(void) {
			tools::Link::setForecStatementEntry(false);
			tools::Link::setPrevious(*this);
		}

		void Start::inlineFunctions(void) {
			// Nothing.
		}

		void Start::toXml(std::ostream &output) {
			output << tools::Tab::toString() << "<source type=\"start\" id=\"" << getId() << "\">" << std::endl;
			tools::Tab::indent();
			
			for (std::vector<Node *>::iterator i = previousNodes.begin(); i != previousNodes.end(); ++i) {
				output << tools::Tab::toString() << "<previous node=\"" << (*i)->getId() << "\" />" << std::endl;
			}
			
			for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
				output << tools::Tab::toString() << "<next node=\"" << i->first->getId() << "\" latency=\"" << i->second.first << "\" />" << std::endl;
			}
			
			tools::Tab::dedent();
			output << tools::Tab::toString() << "</source>" << std::endl;		
		}

		void Start::toUppaal(std::ostream &output) {
			// Nothing.
		}
		
		void Start::toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) {
			locations << tools::Tab::toString() << "<location id=\"" << getId() << "\" x=\"" << x << "\" y=\"" << y << "\" color=\"#FFFFFF\">" << std::endl;
			tools::Tab::indent();
			locations << tools::Tab::toString() << "<name x=\"" << (x - 56) << "\" y=\"" << (y + 8) << "\">Start</name>" << std::endl;
			tools::Tab::dedent();
			locations << tools::Tab::toString() << "</location>" << std::endl;
			
			// Edges.
			int offset = 0;
			for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
				// TODO: If the transition is an abort, then change the edge colour.
				transitions << tools::Tab::toString() << "<transition>" << std::endl;
				
				tools::Tab::indent();
				transitions << tools::Tab::toString() << "<source ref=\"" << getId() << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<target ref=\"" << i->first->getId() << "\" />" << std::endl;
				if (offset != 0) {
					transitions << tools::Tab::toString() << "<nail x=\"" << (x + offset) << "\" y=\"" << y << "\" />" << std::endl;
				}
				// TODO: Add guard, synchronisation, or assignment labels.
				// TODO: For abort/scheduling/tick/computing the execution time.
				tools::Tab::dedent();
				
				transitions << tools::Tab::toString() << "</transition>" << std::endl;
				
				offset -= 8;
			}
		}

		void Start::prettyPrint(std::ostream &output) {
			output << "Start node";
		}
		
	}
}

