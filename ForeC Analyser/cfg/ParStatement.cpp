/*
 *  ParStatement.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 11/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "ParStatement.hpp"

#include "AssemblyLine.hpp"

#include "../tools/Threading.hpp"
#include "../tools/Uppaal.hpp"

namespace forec {
	namespace cfg {
		
		// Initialise static variable
		int ParStatement::globalCount = 0;
		
		ParStatement::ParStatement(const std::string &information, Node &node, const std::string &variant) : Node("ParStatement", variant, this->globalCount++) {
			children.push_back(&node);
			node.setParent((Node *)this);

			id = information;
			id.erase(0, id.rfind("par"));
			id = id.substr(0, id.find(":"));
			id.erase(0, sizeof("par") - 1);
		}
		
		const int ParStatement::getCount(void) {
			return globalCount;
		}

		const std::string ParStatement::getId(void) {
			return id;
		}

		const unsigned int ParStatement::getProgramCounter(void) {
			AssemblyLine *firstAssemblyLine = (AssemblyLine *)findFirst("AssemblyLine", "none");
			if (firstAssemblyLine == NULL) {
				return -1;
			}
			
			return firstAssemblyLine->getProgramCounter();
		}
		
		const int ParStatement::getLatency(void) {
			const std::vector<Node *> assemblyLines = children[0]->findAll("AssemblyLine", "none");
			
			if (assemblyLines.empty() || tools::Threading::getEnclosingThreadId(getId()).compare("main") == 0) {
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
		
		void ParStatement::linkNodes(void) {
			if (tools::Link::hasPrevious()) {
				Node *previousNode = tools::Link::getPrevious();
				addPreviousNode(*previousNode);
				previousNode->addNextNode(*this, ParStatement::getLatency());
			}

			tools::Link::setPrevious(*this);
		}
		
		void ParStatement::resolveDestinations(void) {
			const int firstProgramCounter = getProgramCounter();
			if (firstProgramCounter != -1) {
				tools::Link::resolveBranchDestinations(firstProgramCounter, *this, getLatency());
			}
		}
		
		void ParStatement::inlineFunctions(void) {
			// Nothing.
		}
		
		void ParStatement::toXml(std::ostream &output) {
			output << tools::Tab::toString() << "<forec type=\"statement\" id=\"" << getId() << "\">" << std::endl;
			tools::Tab::indent();
			output << tools::Tab::toString() << "<par />" << std::endl;
			
			for (std::vector<Node *>::iterator i = previousNodes.begin(); i != previousNodes.end(); ++i) {
				output << tools::Tab::toString() << "<previous node=\"" << (*i)->getId() << "\" />" << std::endl;
			}
			
			for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
				output << tools::Tab::toString() << "<next node=\"" << i->first->getId() << "\" latency=\"" << i->second.first << "\" />" << std::endl;
			}
						
			tools::Tab::dedent();
			output << tools::Tab::toString() << "</forec>" << std::endl;			
		}
		
		void ParStatement::toUppaal(std::ostream &output) {
			// Nothing.
		}
		
		void ParStatement::toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) {
			int abortId = 0;
			
			y += 64;
			
			// <location>
			locations << tools::Tab::toString() << "<location id=\"ParStatement_none_" << getId() << "\" x=\"" << x << "\" y=\"" << y << "\" color=\"#0000FF\" />" << std::endl;
			y += 64;
						
			// Weak aborts.
			std::string previousLocation = "ParStatement_none_" + getId();
			const std::vector<std::string> weakAborts = tools::Threading::getAborts(getId(), "weak");	// Weak aborts in the thread body.
			for (std::vector<std::string>::const_iterator weakAbortScope = weakAborts.begin(); weakAbortScope != weakAborts.end(); ++weakAbortScope) {
				// <location>
				locations << tools::Tab::toString() << "<location id=\"" << *weakAbortScope << '_' << abortId << '_' << getId() << "\" x=\"" << x << "\" y=\"" << y << "\" color=\"#0000FF\">" << std::endl;
				tools::Tab::indent();
				locations << tools::Tab::toString() << "<name x=\"" << (x - 56) << "\" y=\"" << (y + 8) << "\">" << *weakAbortScope << '_' << abortId << '_' << getId() << "</name>" << std::endl;
				tools::Tab::dedent();
				locations << tools::Tab::toString() << "</location>" << std::endl;
				
				// <transition>
				// Abort condition true.
				transitions << tools::Tab::toString() << "<transition>" << std::endl;
				tools::Tab::indent();
				transitions << tools::Tab::toString() << "<source ref=\"" << previousLocation << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<target ref=\"" << *weakAbortScope << '_' << abortId << '_' << getId() << "\" />" << std::endl;
				// TODO: Add guard, synchronisation, or assignment labels.
				// TODO: For abort/scheduling/tick/computing the execution time.
				tools::Tab::dedent();
				transitions << tools::Tab::toString() << "</transition>" << std::endl;
				
				// Abort condition false.
				transitions << tools::Tab::toString() << "<transition>" << std::endl;
				tools::Tab::indent();
				transitions << tools::Tab::toString() << "<source ref=\"" << previousLocation << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<target ref=\"" << *weakAbortScope << '_' << abortId << '_' << getId() << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<nail x=\"" << (x - 32) << "\" y=\"" << y << "\" />" << std::endl;
				// TODO: Add guard, synchronisation, or assignment labels.
				// TODO: For abort/scheduling/tick/computing the execution time.
				tools::Tab::dedent();
				transitions << tools::Tab::toString() << "</transition>" << std::endl;
				
				std::ostringstream abortIdString;
				abortIdString << '_' << abortId << '_' << getId();
				previousLocation = *weakAbortScope + abortIdString.str();
				
				y += 64;
				abortId++;
			}
			
			// <location>
			// ParStatement.
			locations << tools::Tab::toString() << "<location id=\"par" << getId() << "\" x=\"" << x << "\" y=\"" << y << "\" color=\"#0000FF\">" << std::endl;
			tools::Tab::indent();
			locations << tools::Tab::toString() << "<name x=\"" << (x - 56) << "\" y=\"" << (y + 8) << "\">par" << getId() << "</name>" << std::endl;
			tools::Tab::dedent();
			locations << tools::Tab::toString() << "</location>" << std::endl;
			
			// <transition>
			transitions << tools::Tab::toString() << "<transition>" << std::endl;
			tools::Tab::indent();
			transitions << tools::Tab::toString() << "<source ref=\"" << previousLocation << "\" />" << std::endl;
			transitions << tools::Tab::toString() << "<target ref=\"par" << getId() << "\" />" << std::endl;
			// TODO: Add guard, synchronisation, or assignment labels.
			// TODO: For abort/scheduling/tick/computing the execution time.
			tools::Tab::dedent();
			transitions << tools::Tab::toString() << "</transition>" << std::endl;
			
			int offset = 0;
			for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
				transitions << tools::Tab::toString() << "<transition>" << std::endl;
				
				tools::Tab::indent();
				transitions << tools::Tab::toString() << "<source ref=\"par" << getId() << "\" />" << std::endl;
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
			
			// Enclosing strong aborts.
			if (tools::Uppaal::getThreadScope().compare("main") != 0) {
				const std::string enclosingParId = tools::Threading::getEnclosingParId(tools::Uppaal::getThreadScope());
				const std::vector<std::string> enclosingStrongAborts = tools::Threading::getAborts(enclosingParId, "strong");	// Strong aborts enclosing the parent par.
// TODO			
				offset = 32;
				for (std::vector<std::string>::const_iterator enclosingStrongAbortScope = enclosingStrongAborts.begin(); enclosingStrongAbortScope != enclosingStrongAborts.end(); ++enclosingStrongAbortScope) {
					// <transition>
					// Abort condition true.
					transitions << tools::Tab::toString() << "<transition>" << std::endl;
					tools::Tab::indent();
					transitions << tools::Tab::toString() << "<source ref=\"par" << getId() << "\" />" << std::endl;
					transitions << tools::Tab::toString() << "<target ref=\"" << tools::Threading::getStartingNode(tools::Uppaal::getThreadScope())->getId() << "\" />" << std::endl;
					transitions << tools::Tab::toString() << "<nail x=\"" << (x - offset) << "\" y=\"" << y << "\" />" << std::endl;
					transitions << tools::Tab::toString() << "<nail x=\"" << (x - offset) << "\" y=\"0\" />" << std::endl;
					// TODO: Add guard, synchronisation, or assignment labels.
					// TODO: For abort/scheduling/tick/computing the execution time.
					tools::Tab::dedent();
					transitions << tools::Tab::toString() << "</transition>" << std::endl;
					
					offset += 32;
				}
			}
			
			// <location>
			// Reaction end.
			offset = 128;
			locations << tools::Tab::toString() << "<location id=\"ReactionEnd_" << getId() << "\" x=\"" << (x + offset) << "\" y=\"" << y << "\" color=\"#0000FF\">" << std::endl;
			tools::Tab::indent();
			locations << tools::Tab::toString() << "<name x=\"" << (x + offset - 56) << "\" y=\"" << (y + 8) << "\">ReactionEnd_" << getId() << "</name>" << std::endl;
			tools::Tab::dedent();
			locations << tools::Tab::toString() << "</location>" << std::endl;
			
			// <transition>
			transitions << tools::Tab::toString() << "<transition>" << std::endl;
			tools::Tab::indent();
			transitions << tools::Tab::toString() << "<source ref=\"par" << getId() << "\" />" << std::endl;
			transitions << tools::Tab::toString() << "<target ref=\"ReactionEnd_" << getId() << "\" />" << std::endl;
			// TODO: Add guard, synchronisation, or assignment labels.
			// TODO: For abort/scheduling/tick/computing the execution time.
			tools::Tab::dedent();
			transitions << tools::Tab::toString() << "</transition>" << std::endl;
			
			// Strong aborts.
			const std::vector<std::string> strongAborts = tools::Threading::getAborts(getId(), "strong");	// Strong aborts in the thread body.
			offset += 128;
			previousLocation = "ReactionEnd_" + getId();
			for (std::vector<std::string>::const_iterator strongAbortScope = strongAborts.begin(); strongAbortScope != strongAborts.end(); ++strongAbortScope) {
				// <location>
				locations << tools::Tab::toString() << "<location id=\"" << *strongAbortScope << '_' << abortId << '_' << getId() << "\" x=\"" << (x + offset) << "\" y=\"" << y << "\" color=\"#0000FF\">" << std::endl;
				tools::Tab::indent();
				locations << tools::Tab::toString() << "<name x=\"" << (x + offset - 56) << "\" y=\"" << (y + 8) << "\">" << *strongAbortScope << '_' << abortId << '_' << getId() << "</name>" << std::endl;
				tools::Tab::dedent();
				locations << tools::Tab::toString() << "</location>" << std::endl;
				
				// <transition>
				// Abort condition true.
				transitions << tools::Tab::toString() << "<transition>" << std::endl;
				tools::Tab::indent();
				transitions << tools::Tab::toString() << "<source ref=\"" << previousLocation << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<target ref=\"" << *strongAbortScope << '_' << abortId << '_' << getId() << "\" />" << std::endl;
				// TODO: Add guard, synchronisation, or assignment labels.
				// TODO: For abort/scheduling/tick/computing the execution time.
				tools::Tab::dedent();
				transitions << tools::Tab::toString() << "</transition>" << std::endl;
				
				// Abort condition false.
				transitions << tools::Tab::toString() << "<transition>" << std::endl;
				tools::Tab::indent();
				transitions << tools::Tab::toString() << "<source ref=\"" << previousLocation << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<target ref=\"" << *strongAbortScope << '_' << abortId << '_' << getId() << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<nail x=\"" << (x + offset) << "\" y=\"" << (y - 32) << "\" />" << std::endl;
				// TODO: Add guard, synchronisation, or assignment labels.
				// TODO: For abort/scheduling/tick/computing the execution time.
				tools::Tab::dedent();
				transitions << tools::Tab::toString() << "</transition>" << std::endl;
				previousLocation = *strongAbortScope;
				
				std::ostringstream abortIdString;
				abortIdString << '_' << abortId << '_' << getId();
				previousLocation = *strongAbortScope + abortIdString.str();
				
				offset += 128;
				abortId++;
			}

			// Weak aborts.
			for (std::vector<std::string>::const_iterator weakAbortScope = weakAborts.begin(); weakAbortScope != weakAborts.end(); ++weakAbortScope) {
				// <location>
				locations << tools::Tab::toString() << "<location id=\"" << *weakAbortScope << '_' << abortId << '_' << getId() << "\" x=\"" << (x + offset) << "\" y=\"" << y << "\" color=\"#0000FF\">" << std::endl;
				tools::Tab::indent();
				locations << tools::Tab::toString() << "<name x=\"" << (x + offset- 56) << "\" y=\"" << (y + 8) << "\">" << *weakAbortScope << '_' << abortId << '_' << getId() << "</name>" << std::endl;
				tools::Tab::dedent();
				locations << tools::Tab::toString() << "</location>" << std::endl;
				
				// <transition>
				// Abort condition true.
				transitions << tools::Tab::toString() << "<transition>" << std::endl;
				tools::Tab::indent();
				transitions << tools::Tab::toString() << "<source ref=\"" << previousLocation << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<target ref=\"" << *weakAbortScope << '_' << abortId << '_' << getId() << "\" />" << std::endl;
				// TODO: Add guard, synchronisation, or assignment labels.
				// TODO: For abort/scheduling/tick/computing the execution time.
				tools::Tab::dedent();
				transitions << tools::Tab::toString() << "</transition>" << std::endl;
				
				// Abort condition false.
				transitions << tools::Tab::toString() << "<transition>" << std::endl;
				tools::Tab::indent();
				transitions << tools::Tab::toString() << "<source ref=\"" << previousLocation << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<target ref=\"" << *weakAbortScope << '_' << abortId << '_' << getId() << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<nail x=\"" << (x + offset) << "\" y=\"" << (y - 32) << "\" />" << std::endl;
				// TODO: Add guard, synchronisation, or assignment labels.
				// TODO: For abort/scheduling/tick/computing the execution time.
				tools::Tab::dedent();
				transitions << tools::Tab::toString() << "</transition>" << std::endl;
				previousLocation = *weakAbortScope;
				
				std::ostringstream abortIdString;
				abortIdString << '_' << abortId << '_' << getId();
				previousLocation = *weakAbortScope + abortIdString.str();
				
				offset += 128;
				abortId++;
			}
			
			// Back to the ParStatement.
			transitions << tools::Tab::toString() << "<transition>" << std::endl;
			tools::Tab::indent();
			transitions << tools::Tab::toString() << "<source ref=\"" << previousLocation << "\" />" << std::endl;
			transitions << tools::Tab::toString() << "<target ref=\"par" << getId() << "\" />" << std::endl;
			transitions << tools::Tab::toString() << "<nail x=\"" << (x + offset - 128 - 32) << "\" y=\"" << (y + 32) << "\" />" << std::endl;
			transitions << tools::Tab::toString() << "<nail x=\"" << (x + 32) << "\" y=\"" << (y + 32) << "\" />" << std::endl;
			// TODO: Add guard, synchronisation, or assignment labels.
			// TODO: For abort/scheduling/tick/computing the execution time.
			tools::Tab::dedent();
			transitions << tools::Tab::toString() << "</transition>" << std::endl;
			
			// <transition>
			// Strong aborts end.
			int yOffset = 32;
			for (std::vector<std::string>::const_iterator strongAbortScope = strongAborts.begin(); strongAbortScope != strongAborts.end(); ++strongAbortScope) {
				transitions << tools::Tab::toString() << "<transition>" << std::endl;
				tools::Tab::indent();
				transitions << tools::Tab::toString() << "<source ref=\"" << previousLocation << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<target ref=\"" << tools::Link::getAbortScopeEndNode(*strongAbortScope)->getId() << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<nail x=\"" << (x + offset - 128) << "\" y=\"" << (y + yOffset) << "\" />" << std::endl;
				// TODO: Add guard, synchronisation, or assignment labels.
				// TODO: For abort/scheduling/tick/computing the execution time.
				tools::Tab::dedent();
				transitions << tools::Tab::toString() << "</transition>" << std::endl;
				
				yOffset +=32;
			}
		}
		
		void ParStatement::prettyPrint(std::ostream &output) {
			output << "par";
		}
		
	}
}

