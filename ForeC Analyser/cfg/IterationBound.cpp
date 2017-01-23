/*
 *  IterationBound.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 14/05/12.
 *  Copyright 2012 Potential Publishers. All rights reserved.
 *
 */

#include "IterationBound.hpp"

#include "AssemblyLine.hpp"

namespace forec {
	namespace cfg {
		
		// Initialise static variable
		int IterationBound::globalCount = 0;
		
		IterationBound::IterationBound(const std::string &information, const std::string &variant) : Node("IterationBound", variant, this->globalCount++) {		
			std::string informationCopy = information;
			informationCopy.erase(0, informationCopy.find("iteration"));
			informationCopy.erase(0, std::string("iteration:").length());
			informationCopy = informationCopy.substr(0, informationCopy.find(":"));
			identifier = informationCopy;
			
			informationCopy = information;
			informationCopy.erase(0, informationCopy.find("bound"));
			informationCopy.erase(0, std::string("bound:").length());
			const std::string lowerBoundCopy = informationCopy.substr(0, informationCopy.find(":"));
			const std::string upperBoundCopy = informationCopy.substr(informationCopy.find(":") + 1);
			
			std::istringstream input(lowerBoundCopy);
			input >> lowerBound;
			input.clear();
			input.str(upperBoundCopy);
			input >> upperBound;
		}
		
		const int IterationBound::getCount(void) {
			return globalCount;
		}

		const std::string IterationBound::getIdentifier(void) const {
			return identifier;
		}

		const int IterationBound::getLowerBound(void) const {
			return lowerBound;
		}

		const int IterationBound::getUpperBound(void) const {
			return upperBound;
		}

		void IterationBound::linkNodes(void) {
			if (tools::Link::hasPrevious()) {
				Node *previousNode = tools::Link::getPrevious();
				addPreviousNode(*previousNode);
				previousNode->addNextNode(*this, 0);
				previousNode->setIterationBound(*this);
			}
			
			tools::Link::setForecStatementEntry(false);
			tools::Link::setPrevious(*this);			
		}

		void IterationBound::inlineFunctions(void) {
			// Nothing.
		}

		void IterationBound::toXml(std::ostream &output) {
			output << tools::Tab::toString() << "<forec type=\"iteration\" id=\"" << getId() << "\">" << std::endl;
			tools::Tab::indent();
			
			output << tools::Tab::toString() << "<bound id=\"" << getIdentifier() << "\" >" << std::endl;
			tools::Tab::indent();
			
			output << tools::Tab::toString() << "<lower>" << getLowerBound() << "</lower>" << std::endl;
			
			output << tools::Tab::toString() << "<upper>" << getUpperBound() << "</upper>" << std::endl;
			
			tools::Tab::dedent();
			output << tools::Tab::toString() << "</bound>" << std::endl;

			for (std::vector<Node *>::iterator i = previousNodes.begin(); i != previousNodes.end(); ++i) {
				output << tools::Tab::toString() << "<previous node=\"" << (*i)->getId() << "\" />" << std::endl;
			}
			
			for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
				output << tools::Tab::toString() << "<next node=\"" << i->first->getId() << "\" latency=\"" << i->second.first << "\" />" << std::endl;
			}

			tools::Tab::dedent();
			output << tools::Tab::toString() << "</forec>" << std::endl;
		}
		
		void IterationBound::toUppaal(std::ostream &output) {
			// Nothing.
		}
		
		void IterationBound::toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) {
			y += 64;
			
			locations << tools::Tab::toString() << "<location id=\"" << getId() << "\" x=\"" << x << "\" y=\"" << y << "\" color=\"#0000FF\">" << std::endl;
			tools::Tab::indent();
			locations << tools::Tab::toString() << "<name x=\"" << (x - 56) << "\" y=\"" << (y + 8) << "\">" << getId() << "</name>" << std::endl;
			tools::Tab::dedent();
			locations << tools::Tab::toString() << "</location>" << std::endl;
			
			// Edges.
			int offset = 0;
			for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
				transitions << tools::Tab::toString() << "<transition>" << std::endl;
				
				tools::Tab::indent();
				transitions << tools::Tab::toString() << "<source ref=\"" << getId() << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<target ref=\"" << i->first->getId() << "\" />" << std::endl;
				if (offset != 0) {
					transitions << tools::Tab::toString() << "<nail x=\"" << (x + offset) << "\" y=\"" << y << "\" />" << std::endl;
				}
				// TODO: Guard determining which edge to take.
				// TODO: Assignment to update the iteration count.
			//	transitions << tools::Tab::toString() << "<bound id=\"" << getIdentifier() << "\" >" << std::endl;
			//	transitions << tools::Tab::toString() << "<lower>" << getLowerBound() << std::endl;
			//	transitions << tools::Tab::toString() << "</lower>" << "<upper>" << getUpperBound() << "</upper>" << std::endl;
			//	transitions << tools::Tab::toString() << "</bound>" << std::endl;
				tools::Tab::dedent();
				
				transitions << tools::Tab::toString() << "</transition>" << std::endl;
				
				offset -= 8;
			}
		}
		
		void IterationBound::prettyPrint(std::ostream &output) {
			output << "Iteration bound for " << getIdentifier() << " is (" << getLowerBound() << ", " << getUpperBound() << ')' << std::endl;
		}
		
	}
}

