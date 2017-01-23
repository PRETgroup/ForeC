/*
 *  Body.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 08/10/10.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Body.hpp"

#include "AssemblyLine.hpp"
#include "Operand.hpp"
#include "OperandList.hpp"
#include "Start.hpp"

#include "../tools/Function.hpp"
#include "../tools/Optimise.hpp"

#include <iostream>

namespace global {
	extern std::string architecture;
}

namespace forec {
	namespace cfg {
		
		// Initialise static variable
		int Body::globalCount = 0;
		
		Body::Body(Node &node, const std::string &variant) : NodeList(node, "Body", variant, this->globalCount++) {
			node.setParent((Node *)this);
			globalMemoryMatch = 0;
			tools::Function::matchGlobalMemoryAccess(node, globalMemoryMatch);
		}
		
		int Body::getCount(void) {
			return globalCount;
		}
		
		void Body::append(Node &node) {
			children.push_back(&node);

			node.setParent(this);
			tools::Function::matchGlobalMemoryAccess(node, globalMemoryMatch);
		}
		
		void Body::inlineFunctions(void) {
			bool childrenChanged = false;
			do {
				childrenChanged = false;
				for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
					if ((*i)->isType("AssemblyLine")) {

						forec::cfg::AssemblyLine *assemblyLine = (forec::cfg::AssemblyLine*)(*i);
						if (assemblyLine->isFunctionCall() && !assemblyLine->isInlinedFunctionCall()) {
							if (global::architecture.compare("microblaze") == 0) {
								// At a function call that hasn't been inlined yet.
								// Get a copy of the called function and insert it after the function call and its delay slot.
								std::vector<forec::cfg::Node *> functionNodes;
								tools::Function::copy(assemblyLine->getLabel(), functionNodes);

								children.insert(i + 2, functionNodes.begin(), functionNodes.end());
								
								// Get the next node after returning from the function and remove the link to the function call.
								std::vector<std::pair<Node *, std::pair<int, bool> > > originalNextNodes = assemblyLine->getNextNodes();
								for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator originalNextNode = originalNextNodes.begin(); originalNextNode != originalNextNodes.end(); ++originalNextNode) {
									originalNextNode->first->removePreviousNode(*assemblyLine);
									assemblyLine->removeNextNode(*originalNextNode->first);
								}
								
								// Link the function call to the start of the function.
								for (std::vector<Node *>::const_iterator functionNode = functionNodes.begin(); functionNode != functionNodes.end(); ++functionNode) {
									if ((*functionNode)->isType("Start")) {
										assemblyLine->addNextNode(*(*functionNode), ((forec::cfg::Start *)*functionNode)->getInstructionLatency());
										(*functionNode)->addPreviousNode(*assemblyLine);
										break;
									}
								}
			
								// Link the return from function to the original next node after the function call.
								for (std::vector<Node *>::const_iterator functionNode = functionNodes.begin(); functionNode != functionNodes.end(); ++functionNode) {
									if ((*functionNode)->isType("AssemblyLine")) {
										forec::cfg::AssemblyLine *assemblyLineInFunction = (forec::cfg::AssemblyLine*)(*functionNode);
										if (assemblyLineInFunction->isFunctionReturn()) {
											for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator originalNextNode = originalNextNodes.begin(); originalNextNode != originalNextNodes.end(); ++originalNextNode) {
												// Link the function return and next node together.
												assemblyLineInFunction->addNextNode(*originalNextNode->first, originalNextNode->second.first);
												originalNextNode->first->addPreviousNode(*assemblyLineInFunction);
											}
										}
									}
								}

								childrenChanged = true;
								assemblyLine->setInlined(true);
								break;
							} else if (global::architecture.compare("ptarm") == 0) {
								// At a function call that hasn't been inlined yet.
								// Get a copy of the called function and insert it after the function call.
								std::vector<Node *> functionNodes;
								tools::Function::copy(assemblyLine->getLabel(), functionNodes);
								
								children.insert(i + 1, functionNodes.begin(), functionNodes.end());
								
								// Get the next node after returning from the function and remove the link to the function call.
								std::vector<std::pair<Node *, std::pair<int, bool> > > originalNextNodes = assemblyLine->getNextNodes();								
								for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator originalNextNode = originalNextNodes.begin(); originalNextNode != originalNextNodes.end(); ++originalNextNode) {
									originalNextNode->first->removePreviousNode(*assemblyLine);
									assemblyLine->removeNextNode(*originalNextNode->first);
								}
								
								// Link the function call to the start of the function.
								for (std::vector<Node *>::const_iterator functionNode = functionNodes.begin(); functionNode != functionNodes.end(); ++functionNode) {
									if ((*functionNode)->isType("Start")) {
										assemblyLine->addNextNode(*(*functionNode), ((forec::cfg::Start *)*functionNode)->getInstructionLatency());
										(*functionNode)->addPreviousNode(*assemblyLine);
										break;
									}
								}
								
								// Link the return from the function to the original next node after the function call.
								for (std::vector<Node *>::const_iterator functionNode = functionNodes.begin(); functionNode != functionNodes.end(); ++functionNode) {
									if ((*functionNode)->isType("AssemblyLine")) {
										forec::cfg::AssemblyLine *assemblyLineInFunction = (forec::cfg::AssemblyLine*)(*functionNode);
										if (assemblyLineInFunction->isFunctionReturn()) {
											for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator originalNextNode = originalNextNodes.begin(); originalNextNode != originalNextNodes.end(); ++originalNextNode) {
												// Link the function return and next node together.
												assemblyLineInFunction->addNextNode(*originalNextNode->first, originalNextNode->second.first);
												originalNextNode->first->addPreviousNode(*assemblyLineInFunction);
											}
										}
									}
								}
								
								childrenChanged = true;
								assemblyLine->setInlined(true);
								break;
							}
						}
					} else {
						(*i)->inlineFunctions();
					}
				}
			} while (childrenChanged);
		}
		
		
		void Body::removeUnreachableNodes(void) {
			tools::Optimise::removeUnreachableNodes(children);
		}
		
		void Body::mergeBranches(void) {
			tools::Optimise::mergeBranches(children, false);
		}
		
		void Body::toXml(std::ostream &output) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				if (!(*i)->isType("CSourceLine")) {
					(*i)->toXml(output);
				}
			}
		}
		
		void Body::toUppaal(std::ostream &output) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->toUppaal(output);
			}
		}
		
		void Body::toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->toUppaal(x, y, locations, transitions);
			}
		}

		void Body::prettyPrint(std::ostream &output) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				if (!(*i)->isType("CSourceLine")) {
					output << '\t' << *(*i) << std::endl;
				}
			}
		}
		
	}
}
