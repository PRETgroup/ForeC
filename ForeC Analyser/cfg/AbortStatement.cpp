/*
 *  AbortStatement.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 11/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "AbortStatement.hpp"

#include "AssemblyLine.hpp"

namespace forec {
	namespace cfg {
		
		// Initialise static variable
		int AbortStatement::globalCount = 0;

		AbortStatement::AbortStatement(const std::string &information, const std::string &variant) : Node("AbortStatement", variant, this->globalCount++) {
			AbortStatement::initialise(information);
		}
		
		AbortStatement::AbortStatement(const std::string &information, Node &node, const std::string &variant) : Node("AbortStatement", variant, this->globalCount++) {
			children.push_back(&node);
			node.setParent((Node *)this);

			AbortStatement::initialise(information);
		}
		
		void AbortStatement::initialise(const std::string &information) {
			idString = information;
			idString.erase(0, idString.rfind("abort"));
			idString = idString.substr(0, idString.find(":"));
			
			std::string identifier = idString;

			if (identifier.find("Strong") != std::string::npos) {
				strength = "strong";
				identifier.erase(identifier.begin(), identifier.begin() + std::string("Strong").length());
			} else if (identifier.find("Weak") != std::string::npos) {
				strength = "weak";
				identifier.erase(identifier.begin(), identifier.begin() + std::string("Weak").length());
			}
			
			std::istringstream input(identifier);
			input >> std::dec >> idNumber;
		}

		const int AbortStatement::getCount(void) {
			return globalCount;
		}
		
		const std::string AbortStatement::getIdentifier(void) {
			return idString;
		}
		
		const int AbortStatement::getIdNumber(void) {
			return idNumber;
		}

		const unsigned int AbortStatement::getProgramCounter(void) {
			if (isVariant("scopeEnd")) {
				return 0;
			}
		
			AssemblyLine *firstAssemblyLine = (AssemblyLine *)findFirst("AssemblyLine", "none");
			if (firstAssemblyLine == NULL) {
				return -1;
			}
			
			return firstAssemblyLine->getProgramCounter();
		}

		const int AbortStatement::getLatency(void) {
			if (isVariant("scopeEnd")) {
				return 0;
			}
			
			const std::vector<Node *> assemblyLines = children[0]->findAll("AssemblyLine", "none");
			
			if (assemblyLines.empty()) {
				return 0;
			}
			
			int latency = 0;
			bool needAlignment = true;
			for (std::vector<Node *>::const_iterator assemblyLine = assemblyLines.begin(); assemblyLine != assemblyLines.end(); ++assemblyLine) {
				latency += ((AssemblyLine *)*assemblyLine)->getLatency(true, needAlignment, latency);
				needAlignment &= !((AssemblyLine *)*assemblyLine)->getHasGlobalMemoryAccess();
			}
			
			return latency;			
		}

		void AbortStatement::linkNodes(void) {
			if (tools::Link::hasPrevious()) {
				Node *previousNode = tools::Link::getPrevious();
				addPreviousNode(*previousNode);
				previousNode->addNextNode(*this, AbortStatement::getLatency());
			}
			
			if (isVariant("statement")) {
				tools::Link::addUnresolvedAbortDestination(getIdentifier(), *this);
			}
			
			tools::Link::setPrevious(*this);
		}

		void AbortStatement::resolveDestinations(void) {
			if (isVariant("scopeEnd")) {
				tools::Link::resolveAbortDestinations(getIdentifier(), *this, getLatency());
			} else {
				const int firstProgramCounter = getProgramCounter();
				if (firstProgramCounter != -1) {
					tools::Link::resolveBranchDestinations(firstProgramCounter, *this, getLatency());
				}
			}
		}
		
		void AbortStatement::inlineFunctions(void) {
			// Nothing.
		}
		
		void AbortStatement::toXml(std::ostream &output) {
			output << tools::Tab::toString() << "<forec type=\"statement\" id=\"" << getId() << "\">" << std::endl;
			tools::Tab::indent();
			output << tools::Tab::toString() << "<abort id=\"" << getIdNumber() << "\"";
			
			if (isVariant("scopeEnd")) {
				output << " variant=\"scopeEnd\" />" << std::endl;
			} else {
				output << " />" << std::endl;
			}

			for (std::vector<Node *>::iterator i = previousNodes.begin(); i != previousNodes.end(); ++i) {
				output << tools::Tab::toString() << "<previous node=\"" << (*i)->getId() << "\" />" << std::endl;
			}
			
			for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
				output << tools::Tab::toString() << "<next node=\"" << i->first->getId() << "\" latency=\"" << i->second.first << "\" />" << std::endl;
			}

			tools::Tab::dedent();
			output << tools::Tab::toString() << "</forec>" << std::endl;
		}

		void AbortStatement::toUppaal(std::ostream &output) {
			// Nothing.
		}
		
		void AbortStatement::toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) {
			y += 64;
			
			// TODO: location id may be wrong (scopeEnd).
			locations << tools::Tab::toString() << "<location id=\"" << getId() << "\" x=\"" << x << "\" y=\"" << y << "\" color=\"#0000FF\">" << std::endl;
			tools::Tab::indent();
			locations << tools::Tab::toString() << "<name x=\"" << (x - 56) << "\" y=\"" << (y + 8) << "\">" << getId() << "</name>" << std::endl;
			tools::Tab::dedent();
			locations << tools::Tab::toString() << "</location>" << std::endl;

			// Edges.
			int offset = 0;
			for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
				if (i == nextNodes.begin()) {
					transitions << tools::Tab::toString() << "<transition>" << std::endl;
				} else {
					transitions << tools::Tab::toString() << "<transition color=\"#0000FF\">" << std::endl;
				}
				
				tools::Tab::indent();
				transitions << tools::Tab::toString() << "<source ref=\"" << getId() << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<target ref=\"" << i->first->getId() << "\" />" << std::endl;
				if (offset != 0) {
					transitions << tools::Tab::toString() << "<nail x=\"" << (x - offset) << "\" y=\"" << y << "\" />" << std::endl;
				}
				// TODO: Add guard, synchronisation, or assignment labels.
				// TODO: For abort/scheduling/tick/computing the execution time.
				tools::Tab::dedent();
				
				transitions << tools::Tab::toString() << "</transition>" << std::endl;
				
				offset += 32;
			}
		}
		
		void AbortStatement::prettyPrint(std::ostream &output) {
			output << getIdentifier();
			
			if (isVariant("scopeEnd")) {
				output << "ScopeEnd";
			}
		}
		
	}
}

