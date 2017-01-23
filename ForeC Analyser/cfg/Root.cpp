/*
 *  Root.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 04/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Root.hpp"

#include "Label.hpp"
#include "Thread.hpp"

#include "../tools/Function.hpp"

namespace forec {
	namespace cfg {

		// Initialise static variable
		int Root::globalCount = 0;

		Root::Root(const std::string &variant) : Node("Root", variant, this->globalCount++) {

		}
		
		void Root::append(Node &node) {
			// Only add if it is not a thread or function.
			if (node.isType("Label")) {
				// End the current function body.
				if (!lastLabel.empty()) {
					tools::Function::add(lastLabel, functionNodes);
				}
				
				// Begin new function body.
				functionNodes.clear();
				lastLabel = ((Label *)&node)->getId();
			} else if (node.isType("CSourceLine") || node.isType("AssemblyLine") || node.isType("IterationBound")) {
				// Add to the current function body.
				functionNodes.push_back(&node);
			} else {
				if (!lastLabel.empty()) {
					tools::Function::add(lastLabel, functionNodes);
				}
				
				functionNodes.clear();
				lastLabel.clear();

				children.push_back(&node);			
				node.setParent((Node *)this);
			}
		}
		
		void Root::addLastFunction(void) {
			tools::Function::add(lastLabel, functionNodes);
		}

		const int Root::getCount(void) {
			return globalCount;
		}
		
		const int Root::mergeNodes(const bool mergeGlobalAccesses) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				if((*i)->isType("Thread")) {
					(*i)->mergeNodes(mergeGlobalAccesses);
				}
			}
			
			return -1;
		}
		
		const int Root::mergeNodes(const bool mergeGlobalAccesses, std::map<std::string, int> &results) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				if((*i)->isType("Thread")) {
					results[((forec::cfg::Thread *)*i)->getIdentifier()] = (*i)->mergeNodes(mergeGlobalAccesses);
				}
			}
			
			return -1;
		}
		
		void Root::toXml(std::ostream &output) {
			output << tools::Tab::toString() << "<program>" << std::endl;
			tools::Tab::indent();
			
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->toXml(output);
			}
			
			tools::Tab::dedent();
			output << tools::Tab::toString() << "</program>" << std::endl;
		}

		void Root::toUppaal(std::ostream &output) {
			output << tools::Tab::toString() << "<nta>" << std::endl;
			tools::Tab::indent();
			
			// <declaration />
			output << tools::Tab::toString() << "<declaration>" << std::endl;
			output << "// Global declarations for the model." << std::endl;
			output << "broadcast chan tick;" << std::endl;
			output << tools::Tab::toString() << "</declaration>" << std::endl;

			// <template />
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->toUppaal(output);
			}
			
			// <system />
			output << std::endl;
			output << tools::Tab::toString() << "<system>" << std::endl;
			output << "// Place template instantiations here." << std::endl;
			output << std::endl;
			output << "// List one or more processes to be composed into a system." << std::endl;
			output << "system" << std::endl;
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				if((*i)->isType("Thread")) {
					output << '\t' << ((forec::cfg::Thread *)*i)->getIdentifier();
					if ((i + 1) != children.end()) {
						output << ",";
					} else {
						output << ";";
					}
					output << std::endl;
				}
			}
			output << tools::Tab::toString() << "</system>" << std::endl;
			
			tools::Tab::dedent();
			output << tools::Tab::toString() << "</nta>" << std::endl;
		}
		
		void Root::toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) {
			// Nothing.
		}
		
		void Root::prettyPrint(std::ostream &output) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				output << *(*i) << std::endl;
			}
		}

	}
}

