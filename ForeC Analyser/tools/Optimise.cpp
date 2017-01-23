/*
 *  Optimise.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/12.
 *  Copyright 2012 Potential Publishers. All rights reserved.
 *
 */

#include "Optimise.hpp"

#include "../cfg/AssemblyLine.hpp"
#include "../cfg/Node.hpp"

#include <algorithm>

namespace tools {

	int Optimise::performMergeNodes(forec::cfg::Node &startNode, const bool mergeGlobalAccesses) {
		int nodesMerged = 0;
		std::set<forec::cfg::Node *> sourceNodes;
		std::set<forec::cfg::Node *> unsuitableSourceNodes;
		
		// Get the thread's starting node.
		sourceNodes.insert(&startNode);

		do {
			// Pick a source node to merge its descendants.
			forec::cfg::Node *sourceNode = *sourceNodes.begin();

			// Find child nodes to merge or use as a source node.
			std::set<forec::cfg::Node *> sourceNodesFound;
			std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > > destinationNodes = Optimise::getDestinationNodes(*sourceNode, sourceNodesFound, mergeGlobalAccesses);

			// Merge (source <--> destination).
			if (destinationNodes.empty()) {
				// No longer a suitable source node.
				unsuitableSourceNodes.insert(sourceNode);				
				sourceNodes.erase(sourceNode);
			} else {
				Optimise::mergeNodes(*sourceNode, destinationNodes);
			}
			
			// Add new source nodes = sourceNodesFound - unsuitableSourceNodes.
			std::set<forec::cfg::Node *> newSourceNodes;
			std::set_difference(sourceNodesFound.begin(), sourceNodesFound.end(), unsuitableSourceNodes.begin(), unsuitableSourceNodes.end(), std::inserter(newSourceNodes, newSourceNodes.end()));
			sourceNodes.insert(newSourceNodes.begin(), newSourceNodes.end());
			
			nodesMerged += destinationNodes.size();
		} while (!sourceNodes.empty());
		
		return nodesMerged;
	}

	std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > > Optimise::getDestinationNodes(forec::cfg::Node &sourceNode, std::set<forec::cfg::Node *> &sourceNodesFound, const bool mergeGlobalAccesses) {
		// Get the child nodes.
		std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > > destinationNodes = sourceNode.getNextNodes();
		
		// Check if the child node is suitable. If not, find a new source node.
		std::vector<std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > >::iterator> unsuitableDestinationNodes;
		for (std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > >::iterator destinationNode = destinationNodes.begin(); destinationNode != destinationNodes.end(); ++destinationNode) {

			// Only merge pure computation nodes (AssemblyLine and AbortStatement).
			if (destinationNode->first->hasIterationBound()) {
				// Retain the loop bound. This is an unsuitable destination node. Prepare to remove destination node.
				unsuitableDestinationNodes.push_back(destinationNode);
			} else if (&sourceNode == destinationNode->first) {
				// We have a loop without an iteration bound.
				if (destinationNode->first->isType("PauseStatement")) {
					// Delayed loop, but this is an unsuitable destination node. 
					// Prepare to remove the destination node.
					unsuitableDestinationNodes.push_back(destinationNode);
				} else {
					// Unbounded loop.
					std::ostringstream error;
					error << "Optimise::getDestinationNodes: Instantaneous loop found for:" << std::endl;
					destinationNode->first->toXml(error);
					throw error.str();
				}
			} else if (destinationNode->first->isType("AssemblyLine")) {
				forec::cfg::AssemblyLine *assemblyLine = (forec::cfg::AssemblyLine*)(destinationNode->first);
				
				 if (assemblyLine->isFunctionCall() && !assemblyLine->isInlinedFunctionCall()) {
					// Function call hasn't been inlined.
					// Prepare to remove destination node.
					unsuitableDestinationNodes.push_back(destinationNode);
				} else if (destinationNode->first->getNextNodes().empty()) {
					// End of the execution path.
					// Prepare to remove destination node.
					unsuitableDestinationNodes.push_back(destinationNode);
				} else if (((forec::cfg::AssemblyLine *)destinationNode->first)->getHasGlobalMemoryAccess()) {
					if (mergeGlobalAccesses) {
						// Update link latency with memory latency.
						const int memoryLatency = ((forec::cfg::AssemblyLine *)destinationNode->first)->getMemoryLatency(destinationNode->second.first, destinationNode->second.second);
						destinationNode->second.first += memoryLatency;
						destinationNode->second.second = false;
					} else {
						// Prepare to remove destination node.
						unsuitableDestinationNodes.push_back(destinationNode);
					}
				} else {
					const int memoryLatency = ((forec::cfg::AssemblyLine *)destinationNode->first)->getMemoryLatency(destinationNode->second.first, destinationNode->second.second);
					destinationNode->second.first += memoryLatency;
				}
			} else if (destinationNode->first->isType("AbortStatement") || destinationNode->first->isType("Start")) {
				// Nothing. This is a suitable destination node.
			} else {
				// Unsuitable destination node. Prepare to remove destination node.
				unsuitableDestinationNodes.push_back(destinationNode);
			}
		}

		// Remove the unsuitable destination nodes.
		for (std::vector<std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > >::iterator>::reverse_iterator destinationNode = unsuitableDestinationNodes.rbegin(); destinationNode != unsuitableDestinationNodes.rend(); ++destinationNode) {
			// Make the destination node a new source node.
			sourceNodesFound.insert((*destinationNode)->first);
			destinationNodes.erase(*destinationNode);
		}
		
		return destinationNodes;
	}

	void Optimise::mergeNodes(forec::cfg::Node &sourceNode, std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > > &destinationNodes) {
		// source <--> destination <--> child.
		for (std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > >::iterator destinationNode = destinationNodes.begin(); destinationNode != destinationNodes.end(); ++destinationNode) {

			// Get links to the child nodes of the destination node.
			std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > > childNodes = destinationNode->first->getNextNodes();
			
			for (std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > >::iterator childNode = childNodes.begin(); childNode != childNodes.end(); ++childNode) {
				// Check for unbounded loops.
				if (!childNode->first->hasIterationBound() && childNode->first->isType("AssemblyLine")) {
					// source <--> destination <--> child
					//             (nextChild)         ^
					//                  ^______________|
					std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > > nextChildNodes = childNode->first->getNextNodes();
					for (std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > >::iterator nextChildNode = nextChildNodes.begin(); nextChildNode != nextChildNodes.end(); ++nextChildNode) {
						if (destinationNode->first == nextChildNode->first) {
							std::ostringstream error;
							error << "Optimise::mergeNodes: Instantaneous loop found for:" << std::endl;
							childNode->first->toXml(error);
							throw error.str();
						}
					}
				}

				// Create new links between source <--> child.
				const int latencyFromSourceToChild = destinationNode->second.first + childNode->second.first;
				sourceNode.addNextNode(*childNode->first, latencyFromSourceToChild, destinationNode->second.second);
				childNode->first->addPreviousNode(sourceNode);
			}
			
			// Remove the links between source <--> destination node.
			sourceNode.removeNextNode(*destinationNode->first);
			destinationNode->first->removePreviousNode(sourceNode);
		}
	}

	void Optimise::mergeBranches(std::vector<forec::cfg::Node *> &children, const bool recursiveMerge) {
		for (std::vector<forec::cfg::Node *>::iterator child = children.begin(); child != children.end(); ++child) {
			std::vector<std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > >::iterator> duplicates;
			
			// Get the links to the next nodes.
			std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > > nextNodes = (*child)->getNextNodes();
			
			// Sort the next nodes based on the destination and maximise their cost.
			std::map<forec::cfg::Node *, std::pair<int, bool> > sortedNextNodes;
			for (std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > >::const_iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
				if (sortedNextNodes.find(i->first) == sortedNextNodes.end()) {
					sortedNextNodes[i->first] = i->second;
				} else {
					// Save the maximum cost.
					if (sortedNextNodes[i->first].first < i->second.first) {
						sortedNextNodes[i->first] = i->second;
					}
				}
			}
			
			// Replace all links with just the maximum.
			for (std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > >::const_iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
				(*child)->removeNextNode(*i->first);
				i->first->removePreviousNode(*(*child));
			}
			
			for (std::map<forec::cfg::Node *, std::pair<int, bool> >::const_iterator nextNode = sortedNextNodes.begin(); nextNode != sortedNextNodes.end(); ++nextNode) {
				(*child)->addNextNode(*nextNode->first, nextNode->second.first, nextNode->second.second);
				nextNode->first->addPreviousNode(*(*child));
			}
			
			if (recursiveMerge) {
				(*child)->mergeBranches();
			}
		}
	}

	void Optimise::removeUnreachableNodes(std::vector<forec::cfg::Node *> &children) {
		std::vector<std::vector<forec::cfg::Node *>::iterator> removedChildren;
		
		do {
			removedChildren.clear();
			for (std::vector<forec::cfg::Node *>::iterator child = children.begin(); child != children.end(); ++child) {
				// Remove if there are no previous nodes.
				if ((*child)->getPreviousNodes().empty()) {
					// Get the child node's next nodes.
					std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > > nextNodes = (*child)->getNextNodes();
					for (std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > >::iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
						// Remove the link.
						i->first->removePreviousNode(*(*child));
						
						if (i->first->isType("AssemblyLine")) {
							forec::cfg::Node *delaySlot = ((forec::cfg::AssemblyLine *)i->first)->getDelaySlot();
							if (delaySlot != NULL) {
								// Remove the link to the delay instruction.
								delaySlot->removePreviousNode(*i->first);
							}
						}
					}
					
					removedChildren.push_back(child);
				}
			}
			
			// Remove the child nodes.
			for (std::vector<std::vector<forec::cfg::Node *>::iterator>::reverse_iterator child = removedChildren.rbegin(); child != removedChildren.rend(); ++child) {
				children.erase(*child);
			}
		} while (!removedChildren.empty());
	}
}

