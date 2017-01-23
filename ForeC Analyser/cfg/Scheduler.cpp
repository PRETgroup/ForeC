/*
 *  Scheduler.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 11/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Scheduler.hpp"

#include "AssemblyLine.hpp"

namespace forec {
	namespace cfg {
		
		// Initialise static variable
		int Scheduler::globalCount = 0;
		
		Scheduler::Scheduler(const std::string &information, Node &node, const std::string &variant) : Node("Scheduler", variant, this->globalCount++) {
			children.push_back(&node);
			node.setParent((Node *)this);
		}
		
		const int Scheduler::getCount(void) {
			return globalCount;
		}

		const unsigned int Scheduler::getProgramCounter(void) {
			AssemblyLine *firstAssemblyLine = (AssemblyLine *)findFirst("AssemblyLine", "none");
			if (firstAssemblyLine == NULL) {
				return -1;
			}
			
			return firstAssemblyLine->getProgramCounter();
		}
		
		const int Scheduler::getLatency() {
			if (isVariant("threadRemove")) {
				return 0;
			}
			
			if (isVariant("iterationEnd")) {
				return 0;
				/*
				int latency = 0;
				for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
					const std::vector<Node *> assemblyLines = (*i)->findAll("AssemblyLine", "none");
			
					bool needAlignment = true;
					for (std::vector<Node *>::const_iterator assemblyLine = assemblyLines.begin(); assemblyLine != assemblyLines.end(); ++assemblyLine) {
						latency += ((AssemblyLine *)*assemblyLine)->getLatency(true, needAlignment, latency);
						needAlignment &= !((AssemblyLine *)*assemblyLine)->getHasGlobalMemoryAccess();
					}
				}
				
				// Include latency for computed goto.
				latency += 5;
				return latency;
				*/
			} else {
				throw std::string("Scheduler::getLatency: Requested undefined latency for " + getVariant());
			}
			
			return 0;			
		}
		
		void Scheduler::linkNodes(void) {
			if (isVariant("threadRemove") || isVariant("iterationEnd") || isVariant("counter")) {
				if (tools::Link::hasPrevious() && !isVariant("counter")) {
					Node *previousNode = tools::Link::getPrevious();
					addPreviousNode(*previousNode);
					previousNode->addNextNode(*this, Scheduler::getLatency());
				}
				
				if (!isVariant("counter")) {
					tools::Link::setPrevious(*this);
				}
			}
		}
		
		void Scheduler::resolveDestinations(void) {
			if (isVariant("threadRemove") || isVariant("iterationEnd")) {
				const int firstProgramCounter = getProgramCounter();
				if (firstProgramCounter != -1) {
					tools::Link::resolveBranchDestinations(firstProgramCounter, *this, getLatency());
				}
			} else {
				for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
					(*i)->resolveDestinations();
				}
			}
		}
		
		void Scheduler::inlineFunctions(void) {
			// Nothing.
		}
		
		void Scheduler::toXml(std::ostream &output) {
			output << tools::Tab::toString() << "<forec type=\"scheduler\" id=\"" << getId() << "\">" << std::endl;
			tools::Tab::indent();
			output << tools::Tab::toString() << "<" << getVariant() << " />" << std::endl;			

			for (std::vector<Node *>::iterator i = previousNodes.begin(); i != previousNodes.end(); ++i) {
				output << tools::Tab::toString() << "<previous node=\"" << (*i)->getId() << "\" />" << std::endl;
			}
			
			for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
				output << tools::Tab::toString() << "<next node=\"" << i->first->getId() << "\" latency=\"" << i->second.first << "\" />" << std::endl;
			}
			
			tools::Tab::dedent();
			output << tools::Tab::toString() << "</forec>" << std::endl;
		}
		
		void Scheduler::toUppaal(std::ostream &output) {
			// Nothing.
		}
		
		void Scheduler::toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) {
			if (isVariant("threadRemove") || isVariant("iterationEnd")) {
				y += 64; 
				
				locations << tools::Tab::toString() << "<location id=\"" << getId() << "\" x=\"" << x << "\" y=\"" << y << "\" color=\"#5FC514\">" << std::endl;
				tools::Tab::indent();
				locations << tools::Tab::toString() << "<name x=\"" << (x - 56) << "\" y=\"" << (y + 8) << "\">" << getVariant() << "</name>" << std::endl;
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
		}
		
		void Scheduler::prettyPrint(std::ostream &output) {
			output << "Scheduler " << getVariant() << " node";
		}
		
	}
}

