/*
 *  Link.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 17/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Link.hpp"

#include "../cfg/AssemblyLine.hpp"

namespace tools {
	// Initialise static variables
	forec::cfg::Node *Link::globalPrevious = NULL;
	bool Link::forecStatementEntry = false;
	std::map<std::string, forec::cfg::Node *> Link::abortScopeEndNodes;
	std::map<unsigned int, std::set<forec::cfg::Node *> > Link::unresolvedBranchDestinations;
	std::map<std::string, std::set<forec::cfg::Node *> > Link::unresolvedAbortDestinations;
	
	void Link::clear(void) {
		Link::abortScopeEndNodes.clear();
		Link::unresolvedBranchDestinations.clear();
		Link::unresolvedAbortDestinations.clear();
		Link::globalPrevious = NULL;
		Link::forecStatementEntry = false;
	}

	void Link::resetPrevious(void) {
		Link::globalPrevious = NULL;
	}
	
	void Link::setPrevious(forec::cfg::Node &previousNode) {
		Link::globalPrevious = &previousNode;
	}

	const bool Link::hasPrevious(void) {
		return Link::globalPrevious != NULL;
	}

	forec::cfg::Node *Link::getPrevious(void) {
		return Link::globalPrevious;
	}

	void Link::setForecStatementEntry(const bool value) {
		Link::forecStatementEntry = value;
	}

	const bool Link::isForecStatementEntry(void) {
		return Link::forecStatementEntry;
	}

	void Link::addUnresolvedBranchDestination(const unsigned int destinationAddress, forec::cfg::Node &sourceNode) {
		Link::unresolvedBranchDestinations[destinationAddress].insert(&sourceNode);
	}
	
	void Link::resolveBranchDestinations(const unsigned int programCounter, forec::cfg::Node &destinationNode, const int latency) {
		if (Link::unresolvedBranchDestinations.find(programCounter) != Link::unresolvedBranchDestinations.end()) {
			std::set<forec::cfg::Node *> sourceNodes = Link::unresolvedBranchDestinations[programCounter];
			for (std::set<forec::cfg::Node *>::iterator i = sourceNodes.begin(); i != sourceNodes.end(); ++i) {
				(*i)->addNextNode(destinationNode, latency);
				destinationNode.addPreviousNode(*(*i));
			}
			Link::unresolvedBranchDestinations.erase(Link::unresolvedBranchDestinations.find(programCounter));
		}
	}
	
	const bool Link::hasUnresolvedBranchDestinations(void) {
		return !Link::unresolvedBranchDestinations.empty();
	}

	void Link::addUnresolvedAbortDestination(const std::string &abortId, forec::cfg::Node &sourceNode) {
		Link::unresolvedAbortDestinations[abortId].insert(&sourceNode);
	}

	void Link::resolveAbortDestinations(const std::string &abortId, forec::cfg::Node &destinationNode, const int latency) {
		if (Link::unresolvedAbortDestinations.find(abortId) != Link::unresolvedAbortDestinations.end()) {
			std::set<forec::cfg::Node *> sourceNodes = Link::unresolvedAbortDestinations[abortId];
			for (std::set<forec::cfg::Node *>::iterator i = sourceNodes.begin(); i != sourceNodes.end(); ++i) {
				(*i)->addNextNode(destinationNode, latency);
				destinationNode.addPreviousNode(*(*i));
			}
			Link::unresolvedAbortDestinations.erase(Link::unresolvedAbortDestinations.find(abortId));
		}
		
		abortScopeEndNodes[abortId] = &destinationNode;
	}

	const bool Link::hasUnresolvedAbortDestinations(void) {
		return !Link::unresolvedAbortDestinations.empty();
	}
	
	forec::cfg::Node *Link::getAbortScopeEndNode(const std::string &abortId) {
		if (Link::abortScopeEndNodes.find(abortId) == Link::abortScopeEndNodes.end()) {
			throw std::string("Link::getAbortScopeEndNode: Could not find abort \"" + abortId + "\" scope end node.");
		}
		
		return Link::abortScopeEndNodes[abortId];
	}
	
	const std::string Link::toString(void) {
		std::ostringstream output;
		
		output << "=======================" << std::endl;
		output << "tools::Link::toString()" << std::endl;
		output << "=======================" << std::endl;

		if (!Link::abortScopeEndNodes.empty()) {
			output << "Abort pre-emption destination addresses:" << std::endl;
			output << "----------------------------------------" << std::endl;
			for (std::map<std::string, forec::cfg::Node *>::const_iterator abortId = Link::abortScopeEndNodes.begin(); abortId != Link::abortScopeEndNodes.end(); ++abortId) {
				output << "* " << *(abortId->second) << std::endl;
			}
			output << std::endl;
		}

		if (!Link::unresolvedBranchDestinations.empty()) {
			output << "Unresolved branch destination addresses:" << std::endl;
			output << "----------------------------------------" << std::endl;
			for (std::map<unsigned int, std::set<forec::cfg::Node *> >::const_iterator unresolvedDestination = Link::unresolvedBranchDestinations.begin(); unresolvedDestination != Link::unresolvedBranchDestinations.end(); ++unresolvedDestination) {
				output << "\tAddress: 0x" << std::hex << unresolvedDestination->first << ":" << std::endl;
				
				for (std::set<forec::cfg::Node *>::const_iterator sourceNode = unresolvedDestination->second.begin(); sourceNode != unresolvedDestination->second.end(); ++sourceNode) {
					output << "\t* " << *(*sourceNode) << std::endl;
				}
				output << std::endl;
			}
		}
		
		if (!Link::unresolvedAbortDestinations.empty()) {
			output << "Unresolved abort destination addresses:" << std::endl;
			output << "---------------------------------------" << std::endl;
			for (std::map<std::string, std::set<forec::cfg::Node *> >::const_iterator unresolvedDestination = Link::unresolvedAbortDestinations.begin(); unresolvedDestination != Link::unresolvedAbortDestinations.end(); ++unresolvedDestination) {

				output << "\tAbort ID: " << unresolvedDestination->first << ":" << std::endl;
				
				for (std::set<forec::cfg::Node *>::const_iterator sourceNode = unresolvedDestination->second.begin(); sourceNode != unresolvedDestination->second.end(); ++sourceNode) {
					output << "\t* " << *(*sourceNode) << std::endl;
				}
				output << std::endl;
			}
		}
		
		output << std::endl;

		return output.str();
	}
}


