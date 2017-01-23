/*
 *  Thread.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 11/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Thread.hpp"

#include "AssemblyLine.hpp"
#include "Start.hpp"

#include "../reachability/Reachability.hpp"

#include "../tools/Optimise.hpp"
#include "../tools/Threading.hpp"
#include "../tools/Uppaal.hpp"

#include <algorithm>

namespace global {
	extern bool merge;
}

namespace forec {
	namespace cfg {
		
		// Initialise static variable
		int Thread::globalCount = 0;
		
		Thread::Thread(const std::string &information, Node &node, const std::string &variant) : Node("Thread", variant, this->globalCount++) {
			children.push_back(&node);
			node.setParent((Node *)this);
	
			identifier = information;
			identifier.erase(0, identifier.find("thread"));
			identifier.erase(0, std::string("thread:").length());
			identifier = identifier.substr(0, identifier.find(":"));

			Start *startNode = new Start(getProgramCounter());
			startNode->setParent((Node *)this);
			children.insert(children.begin(), startNode);
			
			tools::Threading::addStartingNode(identifier, *startNode);
		}
		
		const int Thread::getCount(void) {
			return globalCount;
		}

		const std::string Thread::getIdentifier(void) {
			return identifier;
		}
		
		const unsigned int Thread::getProgramCounter(void) {
			AssemblyLine *firstAssemblyLine = (AssemblyLine *)findFirst("AssemblyLine", "none");
			if (firstAssemblyLine == NULL) {
				return -1;
			}
			
			return firstAssemblyLine->getProgramCounter();
		}
		
		void Thread::linkNodes(void) {
			tools::Link::resetPrevious();
			
			tools::Link::setForecStatementEntry(true);
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->linkNodes();
			}
			tools::Link::setForecStatementEntry(false);
			
			tools::Link::resetPrevious();
		}
		
		const int Thread::mergeNodes(const bool mergeGlobalAccesses) {
			if (global::merge) {
				Node *startNode = findFirst("Start", "none");
				return tools::Optimise::performMergeNodes(*startNode, mergeGlobalAccesses);
			}
			
			return 0;
		}
		
		void Thread::mergeBranches(void) {
			tools::Optimise::mergeBranches(children, true);
		}
		
		void Thread::toXml(std::ostream &output) {
			output << tools::Tab::toString() << "<thread id=\"" << identifier << "\">" << std::endl;
			tools::Tab::indent();
			
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->toXml(output);
			}
			
			tools::Tab::dedent();
			output << tools::Tab::toString() << "</thread>" << std::endl;
		}
		
		void Thread::toUppaal(std::ostream &output) {
			tools::Uppaal::enterThreadScope(identifier);
		
			output << std::endl;
			output << tools::Tab::toString() << "<template>" << std::endl;
			
			tools::Tab::indent();
			output << tools::Tab::toString() << "<name>" << identifier << "</name>" << std::endl;
			output << tools::Tab::toString() << "<declaration>" << std::endl;
			
			tools::Tab::indent();
			output << "// Thread local declarations for the model." << std::endl;
			
			tools::Tab::dedent();
			output << tools::Tab::toString() << "</declaration>" << std::endl;
			output << std::endl;
			
			// <location>
			// <transition>
			int x = 0;
			int y = 0;
			std::ostringstream locations;
			std::ostringstream transitions;
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->toUppaal(x, y, locations, transitions);
			}
			
			output << locations.str() << std::endl;
			output << tools::Tab::toString() << "<init ref=\"" << findFirst("Start", "none")->getId() << "\"/>" << std::endl;
			output << std::endl;
			
			if (identifier.compare("main") != 0) {
				// Link the threadRemove to Start node.
				transitions << tools::Tab::toString() << "<transition>" << std::endl;
				
				tools::Tab::indent();
				transitions << tools::Tab::toString() << "<source ref=\"" << findFirst("Scheduler", "threadRemove")->getId() << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<target ref=\"" << findFirst("Start", "none")->getId() << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<nail x=\"" << (x - 200) << "\" y=\"" << y << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<nail x=\"" << (x - 200) << "\" y=\"0\" />" << std::endl;
				tools::Tab::dedent();
				
				transitions << tools::Tab::toString() << "</transition>" << std::endl;
			}
			output << transitions.str();
			
			tools::Tab::dedent();
			output << tools::Tab::toString() << "</template>" << std::endl;
			
			tools::Uppaal::leaveThreadScope(identifier);
		}
		
		void Thread::toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) {
			// Nothing.
		}
		
		void Thread::prettyPrint(std::ostream &output) {
			output << "thread " << identifier << " {" << std::endl;
			output << *children[0] << std::endl;
			output << *children[1];
			output << '}';
		}
		
	}
}

