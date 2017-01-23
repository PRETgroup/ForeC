/*
 *  Threading.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 29/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Threading.hpp"

#include "Multicore.hpp"

#include "../cfg/Node.hpp"
#include "../cfg/Start.hpp"
#include "../cfg/Thread.hpp"

#include <fstream>
#include <sstream>
#include <string.h>

namespace tools {
	bool Threading::debugging;
	std::map<std::string, std::vector<std::string> > Threading::parIds;
	std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, enum Threading::State> > > > Threading::parCores;
	std::map<std::string, std::vector<std::string> > Threading::threadIds;
	std::map<std::string, std::map<std::string, std::map<std::string, std::pair<int, int> > > > Threading::parIndexes;
	std::map<std::string, std::string> Threading::enclosingThreadIds;
	std::map<std::string, std::string> Threading::enclosingParIds;
	std::map<std::string, std::map<std::string, std::vector<std::string> > > Threading::abortIds;
	std::map<std::string, forec::cfg::Node *> Threading::startingNodes;
	
	void Threading::clear(const bool debugging) {
		Threading::debugging = debugging;
		Threading::parIds.clear();
		Threading::parCores.clear();
		Threading::parIndexes.clear();
		Threading::threadIds.clear();
		Threading::enclosingThreadIds.clear();
		Threading::enclosingParIds.clear();
		Threading::abortIds.clear();
		Threading::startingNodes.clear();
	}

	void Threading::loadInformation(const rapidxml::xml_node<> &information) {
		// Get aborts around each par(...).
		rapidxml::xml_node<> *aborts = information.first_node("aborts");
		for (rapidxml::xml_node<> *par = aborts->first_node("par"); par; par = par->next_sibling("par")) {
			rapidxml::xml_attribute<> *parId = par->first_attribute("id");
			
			for (rapidxml::xml_node<> *abort = par->first_node("abort"); abort; abort = abort->next_sibling("abort")) {
				rapidxml::xml_attribute<> *abortId = abort->first_attribute("id");
				rapidxml::xml_attribute<> *abortVariant = abort->first_attribute("variant");
				
				Threading::abortIds[parId->value()][abortVariant->value()].push_back(abortId->value());
			}
		}
		
		// Get the par(...) indexes for each core.
		rapidxml::xml_node<> *parIndexes = information.first_node("parIndexes");
		for (rapidxml::xml_node<> *core = parIndexes->first_node("core"); core; core = core->next_sibling("core")) {
			rapidxml::xml_attribute<> *coreId = core->first_attribute("id");
			
			for (rapidxml::xml_node<> *thread = core->first_node("threadScope"); thread; thread = thread->next_sibling("threadScope")) {
				rapidxml::xml_attribute<> *threadScope = thread->first_attribute("id");
				
				int index = 0;
				for (rapidxml::xml_node<> *par = thread->first_node("par"); par; par = par->next_sibling("par")) {
					rapidxml::xml_attribute<> *parId = par->first_attribute("id");
					Threading::parIndexes[coreId->value()][threadScope->value()][parId->value()].first = index;

					rapidxml::xml_attribute<> *number = par->first_attribute("handlers");
					int numberOfHandlers;
					std::istringstream numberString(number->value());
					numberString >> numberOfHandlers;
					Threading::parIndexes[coreId->value()][threadScope->value()][parId->value()].second = numberOfHandlers;
					
					index++;
				}
			}
		}
		
		// XML of thread graph is a recursive nesting of thread and par nodes.
		// Root node is a thread node.
		std::set<std::string> encounteredParIds;
		rapidxml::xml_node<> *tarotNode = information.first_node("tarot");
		for (rapidxml::xml_node<> *thread = tarotNode->first_node("thread"); thread; thread = thread->next_sibling("thread")) {
			rapidxml::xml_attribute<> *threadId = thread->first_attribute("id");
			
			// Nested par node
			for (rapidxml::xml_node<> *parNested = thread->first_node("par"); parNested; parNested = parNested->next_sibling("par")) {
				rapidxml::xml_attribute<> *parNestedId = parNested->first_attribute("id");
				
				Threading::threadIds[threadId->value()].push_back(parNestedId->value());
				Threading::enclosingThreadIds[parNestedId->value()] = threadId->value();
				Threading::loadThreadGraphRecursive(parNested, encounteredParIds);
			}
		}
	}
	
	void Threading::loadThreadGraphRecursive(rapidxml::xml_node<> *par, std::set<std::string> &encounteredParIds) {
		rapidxml::xml_attribute<> *parId = par->first_attribute("id");
		if (encounteredParIds.find(parId->value()) == encounteredParIds.end()) {
			encounteredParIds.insert(parId->value());
			
			// Thread nodes.
			for (rapidxml::xml_node<> *thread = par->first_node("thread"); thread; thread = thread->next_sibling("thread")) {
				rapidxml::xml_attribute<> *threadId = thread->first_attribute("id");
			
				Threading::parIds[parId->value()].push_back(threadId->value());
				Threading::enclosingParIds[threadId->value()] = parId->value();
			
				std::pair<std::string, enum Threading::State> childState(threadId->value(), Threading::reacting);
				Threading::parCores[parId->value()][Multicore::getAllocatedCore(threadId->value())].push_back(childState);
			
				// Nested par nodes.
				for (rapidxml::xml_node<> *parNested = thread->first_node("par"); parNested; parNested = parNested->next_sibling("par")) {
					rapidxml::xml_attribute<> *parNestedId = parNested->first_attribute("id");
				
					Threading::threadIds[threadId->value()].push_back(parNestedId->value());
					Threading::enclosingThreadIds[parNestedId->value()] = threadId->value();
					Threading::loadThreadGraphRecursive(parNested, encounteredParIds);
				}
			
				if (encounteredParIds.find(parId->value()) == encounteredParIds.end()) {

				}
			}
		}
	}
	
	const std::set<std::string> Threading::getAllThreadIds(void) {
		std::set<std::string> allThreadIds;
		for (std::map<std::string, forec::cfg::Node *>::const_iterator threadId = Threading::startingNodes.begin(); threadId != Threading::startingNodes.end(); ++threadId) {
			allThreadIds.insert(threadId->first);
		}
		
		return allThreadIds;
	}
	
	const std::vector<std::string> Threading::getThreadIds(const std::string &parId) {
		if (Threading::parIds.find(parId) == Threading::parIds.end()) {
			throw std::string("Threading::getThreadIds: parId \"" + parId + "\" not found.");
		}
		
		return Threading::parIds[parId];
	}
	
	const std::vector<std::string> Threading::getParIds(const std::string &threadId) {
		if (Threading::threadIds.find(threadId) == Threading::threadIds.end()) {
			throw std::string("Threading::getParId: threadId \"" + threadId + "\" not found.");
		}
		
		return Threading::threadIds[threadId];
	}
	
	const std::string Threading::getEnclosingThreadId(const std::string &parId) {
		if (Threading::enclosingThreadIds.find(parId) == Threading::enclosingThreadIds.end()) {
			throw std::string("Threading::getEnclosingThreadId: parId \"" + parId + "\" not found.");
		}
		
		return Threading::enclosingThreadIds[parId];
	}
	
	const std::string Threading::getEnclosingParId(const std::string &threadId) {
		if (Threading::enclosingParIds.find(threadId) == Threading::enclosingParIds.end()) {
			throw std::string("Threading::getEnclosingParId: threadId \"" + threadId + "\" not found.");
		}
		
		return Threading::enclosingParIds[threadId];
	}

	const int Threading::getParIndex(const std::string &coreId, const std::string &threadScope, const std::string &parId) {
		return Threading::parIndexes[coreId][threadScope][parId].first;
	}
	
	const int Threading::getParIndexesSize(const std::string &coreId, const std::string &threadScope) {
		return Threading::parIndexes[coreId][threadScope].size();
	}
	
	const int Threading::getNumberOfHandlers(const std::string &coreId, const std::string &threadScope, const std::string &parId) {
		if (Threading::parIndexes.find(coreId) == Threading::parIndexes.end()) {
			throw std::string("Threading::getNumberOfHandlers: coreId \"" + coreId + "\" not found.");
		}
		
		if (Threading::parIndexes[coreId].find(threadScope) == Threading::parIndexes[coreId].end()) {
			throw std::string("Threading::getNumberOfHandlers: threadScope \"" + threadScope + "\" not found.");
		}
		
		if (Threading::parIndexes[coreId][threadScope].find(parId) == Threading::parIndexes[coreId][threadScope].end()) {
			throw std::string("Threading::getNumberOfHandlers: parId \"" + parId + "\" not found (core " + coreId + ", threadScope " + threadScope + ").");
		}
		
		return Threading::parIndexes[coreId][threadScope][parId].second;
	}
	

	const bool Threading::hasPar(const std::string &threadId) {
		return Threading::threadIds.find(threadId) != Threading::threadIds.end();
	}

	const bool Threading::isNested(const std::string &parId) {
		std::vector<std::string> mainParIds = Threading::getParIds("main");
		for (std::vector<std::string>::const_iterator mainParId = mainParIds.begin(); mainParId != mainParIds.end(); ++mainParId) {
			if (mainParId->compare(parId) == 0) {
				return false;
			}
		}
		
		return true;
	}	
	
		const std::vector<std::pair<std::string, enum tools::Threading::State> > Threading::getAllocatedThreads(const std::string &parId, const std::string &coreId) {
			if (Threading::parCores.find(parId) == Threading::parCores.end()) {
				throw std::string("Threading::getAllocatedThreads: parId \"" + parId + "\" not found.");
			}
		
			if (Threading::parCores[parId].find(coreId) == Threading::parCores[parId].end()) {
				return std::vector<std::pair<std::string, enum tools::Threading::State> >();
			}
		
			return Threading::parCores[parId][coreId];
		}
	
	const bool Threading::parCoreTerminated(const std::string &parId, const std::string &coreId) {
		const std::vector<std::pair<std::string, enum Threading::State> > childThreads = Threading::getAllocatedThreads(parId, coreId);
	
		for(std::vector<std::pair<std::string, enum tools::Threading::State> >::const_iterator thread = childThreads.begin(); thread != childThreads.end(); ++thread) {
			if (thread->second != Threading::terminated) {
				return false;
			}
		}
	
		return true;
	}

	const std::vector<std::string> Threading::getAborts(const std::string &parId, const std::string &variant) {
		if (Threading::abortIds.find(parId) == Threading::abortIds.end()) {
			return std::vector<std::string>();
		}
		
		if (Threading::abortIds[parId].find(variant) == Threading::abortIds[parId].end()) {
			return std::vector<std::string>();
		}
		
		return Threading::abortIds[parId][variant];
	}

	void Threading::addStartingNode(const std::string &threadId, forec::cfg::Node &startNode) {
		Threading::setStartingNode(threadId, startNode);
	}
	
	void Threading::setStartingNode(const std::string &threadId, forec::cfg::Node &startNode) {
		Threading::startingNodes[threadId] = &startNode;
	}
	
	forec::cfg::Node *Threading::getStartingNode(const std::string &threadId) {
		if (Threading::startingNodes.find(threadId) == Threading::startingNodes.end()) {
			throw std::string("Threading::getThread: Could not find thread " + threadId);
		}

		return Threading::startingNodes[threadId];
	}

	const std::string Threading::staticToString(void) {
		std::ostringstream output;

		output << "============================" << std::endl;
		output << "tools::Threading::toString()" << std::endl;
		output << "============================" << std::endl;

		if (!Threading::parIndexes.empty()) {
			output << "Cores with par(...) indexes for each parent thread:" << std::endl;
			output << "---------------------------------------------------" << std::endl;
			
			for (std::map<std::string, std::map<std::string, std::map<std::string, std::pair<int, int> > > >::const_iterator coreId = Threading::parIndexes.begin(); coreId != Threading::parIndexes.end(); ++coreId) {
				output << "\tcoreId" << coreId->first << ':' << std::endl;
				
				for (std::map<std::string, std::map<std::string, std::pair<int, int> > >::const_iterator threadScope = coreId->second.begin(); threadScope != coreId->second.end(); ++threadScope) {
					output << "\t* " << threadScope->first << "__thread:" << std::endl;
					
					for (std::map<std::string, std::pair<int, int> >::const_iterator parId = threadScope->second.begin(); parId != threadScope->second.end(); ++parId) {
						output << "\t " << parId->second.first << " par" << parId->first << " (" << parId->second.second << ')' << std::endl;
					}
				}
				output << std::endl;
			}
			output << std::endl;
		}

		if (!Threading::startingNodes.empty()) {
			output << "Thread starting address:" << std::endl;
			output << "------------------------" << std::endl;

			for (std::map<std::string, forec::cfg::Node *>::const_iterator startingNode = Threading::startingNodes.begin(); startingNode != Threading::startingNodes.end(); ++startingNode) {
				output << '\t' << startingNode->first << ": 0x" << std::hex << ((forec::cfg::Start *)(startingNode->second))->getProgramCounter() << std::endl;
			}
			
			output << std::endl;
		}

		if (!Threading::parIds.empty()) {
			output << "Threads in each par(...):" << std::endl;
			output << "-------------------------" << std::endl;
		
			for (std::map<std::string, std::vector<std::string> >::const_iterator parId = Threading::parIds.begin(); parId != Threading::parIds.end(); ++parId) {
				output << "\tpar" << parId->first << ':' << std::endl;

				for (std::vector<std::string>::const_iterator threadId = parId->second.begin(); threadId != parId->second.end(); ++threadId) {
					output << "\t *" << *threadId << "__thread" << std::endl;
				}

				output << std::endl;
			}
		}

		if (!Threading::parCores.empty()) {
			output << "Allocation of threads for each core:" << std::endl;
			output << "------------------------------------" << std::endl;
		
			for (std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, enum State> > > >::const_iterator parCore = Threading::parCores.begin(); parCore != Threading::parCores.end(); ++parCore) {
				output << "\tpar" << parCore->first << ':' << std::endl;

				for (std::map<std::string, std::vector<std::pair<std::string, enum State> > >::const_iterator coreId = parCore->second.begin(); coreId != parCore->second.end(); ++coreId) {
					output << "\t *core" << coreId->first << std::endl;

					for (std::vector<std::pair<std::string, enum State> >::const_iterator threadId = coreId->second.begin(); threadId != coreId->second.end(); ++threadId) {
						output << "\t  *" << threadId->first << "__thread (" << threadId->second << ')' << std::endl;
					}
				}

				output << std::endl;
			}
		}

		if (!Threading::threadIds.empty()) {
			output << "par(...)s in each thread:" << std::endl;
			output << "-------------------------" << std::endl;
		
			for (std::map<std::string, std::vector<std::string> >::const_iterator threadId = Threading::threadIds.begin(); threadId != Threading::threadIds.end(); ++threadId) {
				output << '\t' << threadId->first << "__thread:" << std::endl;

				for (std::vector<std::string>::const_iterator parId = threadId->second.begin(); parId != threadId->second.end(); ++parId) {
					output << "\t *par" << *parId << std::endl;
				}

				output << std::endl;
			}
		}

		if (!Threading::enclosingThreadIds.empty()) {
			output << "Thread enclosing each par(...):" << std::endl;
			output << "-------------------------------" << std::endl;
		
			for (std::map<std::string, std::string>::const_iterator parId = Threading::enclosingThreadIds.begin(); parId != Threading::enclosingThreadIds.end(); ++parId) {
				output << "\tpar" << parId->first << ": " << parId->second << "__thread" << std::endl;
			}
			
			output << std::endl;
		}

		if (!Threading::enclosingParIds.empty()) {
			output << "par(...) enclosing each thread:" << std::endl;
			output << "-------------------------------" << std::endl;
		
			for (std::map<std::string, std::string>::const_iterator threadId = Threading::enclosingParIds.begin(); threadId != Threading::enclosingParIds.end(); ++threadId) {
				output << '\t' << threadId->first << "__thread: par" << threadId->second << std::endl;
			}
			
			output << std::endl;
		}

		if (!Threading::abortIds.empty()) {
			output << "Aborts around each par(...):" << std::endl;
			output << "----------------------------" << std::endl;
		
			for (std::map<std::string, std::map<std::string, std::vector<std::string> > >::const_iterator parId = Threading::abortIds.begin(); parId != Threading::abortIds.end(); ++parId) {
				output << "\tpar" << parId->first << ':' << std::endl;
				
				for (std::map<std::string, std::vector<std::string> >::const_iterator variant = parId->second.begin(); variant != parId->second.end(); ++variant) {
					output << "\t\t" << variant->first << ':' << std::endl;
					
					for (std::vector<std::string>::const_iterator abortId = variant->second.begin(); abortId != variant->second.end(); ++abortId) {
						output << "\t\t* " << (*abortId) << std::endl;
					}
				}
				
				output << std::endl;
			}
			
			output << std::endl;
		}

		return output.str();
	}
}
