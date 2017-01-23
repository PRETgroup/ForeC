/*
 *  PauseStatement.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 11/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "PauseStatement.hpp"

#include "AssemblyLine.hpp"

namespace forec {
	namespace cfg {
		
		// Initialise static variable
		int PauseStatement::globalCount = 0;
		
		PauseStatement::PauseStatement(const std::string &information, Node &node, const std::string &variant) : Node("PauseStatement", variant, this->globalCount++) {
			children.push_back(&node);
			node.setParent((Node *)this);
		}
		
		const int PauseStatement::getCount(void) {
			return globalCount;
		}

		const unsigned int PauseStatement::getProgramCounter(void) {
			AssemblyLine *firstAssemblyLine = (AssemblyLine *)findFirst("AssemblyLine", "none");
			if (firstAssemblyLine == NULL) {
				return -1;
			}
			
			return firstAssemblyLine->getProgramCounter();
		}
		
		const int PauseStatement::getLatency(void) {
			if (children.empty()) {
				// If pause is in thread main.
				return 0;
			}
		
			const std::vector<Node *> assemblyLines = children[0]->findAll("AssemblyLine", "none");
			int latency = 0;
			bool needAlignment = true;
			for (std::vector<Node *>::const_iterator assemblyLine = assemblyLines.begin(); assemblyLine != assemblyLines.end(); ++assemblyLine) {
				latency += ((AssemblyLine *)*assemblyLine)->getLatency(true, needAlignment, latency);
				needAlignment &= !((AssemblyLine *)*assemblyLine)->getHasGlobalMemoryAccess();
			}
				
			// Add latency for computed goto.
			latency += 5;
			
			return latency;			
		}
		
		void PauseStatement::linkNodes(void) {
			if (tools::Link::hasPrevious()) {
				Node *previousNode = tools::Link::getPrevious();
				addPreviousNode(*previousNode);
				previousNode->addNextNode(*this, PauseStatement::getLatency());
			}
			
		/*	tools::Link::setForecStatementEntry(true);
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->linkNodes();
			}
			tools::Link::setForecStatementEntry(false);
		*/
			tools::Link::setPrevious(*this);
		}
		
		void PauseStatement::resolveDestinations(void) {
			const int firstProgramCounter = getProgramCounter();
			if (firstProgramCounter != -1) {
				tools::Link::resolveBranchDestinations(firstProgramCounter, *this, getLatency());
			}
		}
		
		void PauseStatement::inlineFunctions(void) {
			// Nothing.
		}
		
		void PauseStatement::toXml(std::ostream &output) {
			output << tools::Tab::toString() << "<forec type=\"statement\" id=\"" << getId() << "\">" << std::endl;
			tools::Tab::indent();
			output << tools::Tab::toString() << "<pause />" << std::endl;

			for (std::vector<Node *>::iterator i = previousNodes.begin(); i != previousNodes.end(); ++i) {
				output << tools::Tab::toString() << "<previous node=\"" << (*i)->getId() << "\" />" << std::endl;
			}
			
			for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
				output << tools::Tab::toString() << "<next node=\"" << i->first->getId() << "\" latency=\"" << i->second.first << "\" />" << std::endl;
			}
					
			tools::Tab::dedent();
			output << tools::Tab::toString() << "</forec>" << std::endl;			
		}
		
		void PauseStatement::toUppaal(std::ostream &output) {
			// Nothing.
		}
		
		void PauseStatement::toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) {
			y += 64;
			
			locations << tools::Tab::toString() << "<location id=\"" << getId() << "\" x=\"" << x << "\" y=\"" << y << "\" color=\"#000000\">" << std::endl;
			tools::Tab::indent();
			locations << tools::Tab::toString() << "<name x=\"" << (x - 56) << "\" y=\"" << (y + 8) << "\">" << getId() << "</name>" << std::endl;
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
				transitions << tools::Tab::toString() << "<label kind=\"synchronisation\" x=\"" << x << "\" y=\"" << (y + 8) << "\">" << std::endl;
				tools::Tab::indent();
				transitions << tools::Tab::toString() << "tick?" << std::endl;
				tools::Tab::dedent();
				transitions << tools::Tab::toString() << "</label>" << std::endl;
				tools::Tab::dedent();
				
				transitions << tools::Tab::toString() << "</transition>" << std::endl;
				
				offset -= 8;
			}
			
			// TODO: Link to the start node for aborts that enclose the thread. 
			// TODO: Encode in the abort hierarchy (outer aborts have higher priority).	
		}
		
		void PauseStatement::prettyPrint(std::ostream &output) {
			output << "pause";
		}
		
	}
}

