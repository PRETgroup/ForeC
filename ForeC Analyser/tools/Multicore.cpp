/*
 *  Multicore.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 21/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Multicore.hpp"

#include <string.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iomanip>

namespace global {
	extern std::string architecture;
}

namespace tools {
	const std::string Multicore::threadSuffix = "__thread";
	std::map<std::string, std::set<std::string> > Multicore::allocatedThreads;			
	std::map<std::string, std::string> Multicore::allocatedCores;
	std::map<std::string, std::set<std::string> > Multicore::allocatedParCores;		
	std::map<std::string, std::set<std::string> > Multicore::activeParCores;
	std::set<std::string> Multicore::allCoreIds;

	void Multicore::clear(void) {
		Multicore::allocatedThreads.clear();
		Multicore::allocatedCores.clear();
		Multicore::activeParCores.clear();
		Multicore::allCoreIds.clear();
	}
	
	void Multicore::loadInformation(const rapidxml::xml_node<> &information) {
		// Get the architecture model.
		global::architecture = information.first_node("architecture")->first_attribute("model")->value();
		if (global::architecture.compare("microblaze") != 0 && global::architecture.compare("ptarm") != 0) {
			throw std::string("Multicore::loadInformation: Unsupported architecture: " + global::architecture);
		}
	
		// Get the thread-to-core allocations
		rapidxml::xml_node<> *allocations = information.first_node("allocations");
		for (rapidxml::xml_node<> *core = allocations->first_node("core"); core; core = core->next_sibling("core")) {
			rapidxml::xml_attribute<> *coreId = core->first_attribute("id");

			Multicore::allCoreIds.insert(coreId->value());
			
			for (rapidxml::xml_node<> *thread = core->first_node("thread"); thread; thread = thread->next_sibling("thread")) {
				rapidxml::xml_attribute<> *threadId = thread->first_attribute("id");
				Multicore::allocatedThreads[coreId->value()].insert(threadId->value());
				Multicore::allocatedCores[threadId->value()] = coreId->value();
			}
		}

		// Get the core allocations for each par(...)
		rapidxml::xml_node<> *allocatedParCoresNode = information.first_node("allocatedParCores");
		for (rapidxml::xml_node<> *par = allocatedParCoresNode->first_node("par"); par; par = par->next_sibling("par")) {
			rapidxml::xml_attribute<> *parId = par->first_attribute("id");
			
			for (rapidxml::xml_node<> *core = par->first_node("core"); core; core = core->next_sibling("core")) {
				rapidxml::xml_attribute<> *coreId = core->first_attribute("id");
				Multicore::allocatedParCores[parId->value()].insert(coreId->value());
			}
		}

		// Get the active cores for each par(...)
		rapidxml::xml_node<> *activeParCoresNode = information.first_node("activeParCores");
		for (rapidxml::xml_node<> *thread = activeParCoresNode->first_node("thread"); thread; thread = thread->next_sibling("thread")) {
			rapidxml::xml_attribute<> *threadId = thread->first_attribute("id");
			
			for (rapidxml::xml_node<> *core = thread->first_node("core"); core; core = core->next_sibling("core")) {
				rapidxml::xml_attribute<> *coreId = core->first_attribute("id");
				Multicore::activeParCores[threadId->value()].insert(coreId->value());
			}
		}
	}
	
	const std::string Multicore::getAllocatedCore(const std::string &threadId) {
		return Multicore::allocatedCores[threadId];
	}
	
	const std::set<std::string> Multicore::getAllocatedThreads(const std::string &coreId) {
		return Multicore::allocatedThreads[coreId];
	}

	const std::set<std::string> Multicore::getAllocatedParCores(const std::string &parId) {
		if (Multicore::allocatedParCores.find(parId) == Multicore::allocatedParCores.end()) {
			throw std::string("Multicore::getAllocatedParCores: Par \"" + parId + "\" has no allocated cores.");
		}

		return Multicore::allocatedParCores[parId];
	}

	const std::set<std::string> Multicore::getActiveParCores(const std::string &threadId) {
		if (Multicore::activeParCores.find(threadId) == Multicore::activeParCores.end()) {
			throw std::string("Multicore::getActiveParCores: Thread \"" + threadId + "\" has no par(...).");
		}
		
		return Multicore::activeParCores[threadId];
	}

	const std::set<std::string> Multicore::getAllCoreIds(void) {
		return Multicore::allCoreIds;
	}
	
	
	const std::string Multicore::staticToString(void) {
		std::ostringstream output;
		
		output << "============================" << std::endl;
		output << "tools::Multicore::toString()" << std::endl;
		output << "============================" << std::endl;
		
		if (!Multicore::allocatedThreads.empty()) {
			output << "Cores with thread allocation:" << std::endl;
			output << "-----------------------------" << std::endl;
			
			for (std::map<std::string, std::set<std::string> >::const_iterator coreId = Multicore::allocatedThreads.begin(); coreId != Multicore::allocatedThreads.end(); ++coreId) {
				
				output << "\tcoreId" << coreId->first << ':' << std::endl;
				for (std::set<std::string>::const_iterator threadId = coreId->second.begin(); threadId != coreId->second.end(); ++threadId) {
					output << "\t* " << *threadId << "__thread" << std::endl;
				}
				output << std::endl;
			}
			output << std::endl;
		}

		if (!Multicore::allocatedCores.empty()) {
			output << "Threads with core allocation:" << std::endl;
			output << "-----------------------------" << std::endl;

			for (std::map<std::string, std::string>::const_iterator threadId = Multicore::allocatedCores.begin(); threadId != Multicore::allocatedCores.end(); ++threadId) {
				output << '\t' << threadId->first << "__thread: core" << threadId->second << std::endl; 
			}
			output << std::endl;
		}
		
		if (!Multicore::activeParCores.empty()) {
			output << "Threads with active cores:" << std::endl;
			output << "--------------------------" << std::endl;
				
				for (std::map<std::string, std::set<std::string> >::const_iterator threadScope = Multicore::activeParCores.begin(); threadScope != Multicore::activeParCores.end(); ++threadScope) {
					
					output << "\t" << threadScope->first << "__thread:" << std::endl;
					for (std::set<std::string>::const_iterator coreId = threadScope->second.begin(); coreId != threadScope->second.end(); ++coreId) {
						output << "\t* core" << *coreId << std::endl;
					}
					output << std::endl;
				}
			output << std::endl;
		}
		
		return output.str();
	}
	
	// Dynamic
	Multicore::Multicore(const std::string &id, const unsigned int elapsedTime) : id(id) {
		state = Multicore::executing;
		this->elapsedTime = elapsedTime;
		nextStartingElapsedTime = 0;
		executionTrace.clear();
	}
	
	// Copy constructor.
	Multicore::Multicore(const Multicore &core) : id(core.id) {
		state = core.state;
		elapsedTime = core.elapsedTime;
		nextStartingElapsedTime = core.nextStartingElapsedTime;
		
		executionTrace.clear();
		for (std::vector<std::pair<int, std::string> >::const_iterator trace = core.executionTrace.begin(); trace != core.executionTrace.end(); ++trace) {
			executionTrace.push_back(std::pair<int, std::string>(trace->first, trace->second));
		}
	}

	const std::string Multicore::getId(void) {
		return id;
	}
	
	void Multicore::resetElapsedTime(void) {
		elapsedTime = 0;
	}
	
	void Multicore::setElapsedTime(const unsigned int newElapsedTime) {
		elapsedTime = newElapsedTime;
	}
	const unsigned int Multicore::getElapsedTime(void) {
		return elapsedTime;
	}
	
	void Multicore::incrementElapsedTime(const unsigned int increment) {
		elapsedTime += increment;
	}
	
	void Multicore::setNextStartingElapsedTime(const unsigned int elapsedTime) {
		nextStartingElapsedTime = elapsedTime;
	}
	
	const unsigned int Multicore::getNextStartingElapsedTime(void) {
		return nextStartingElapsedTime;
	}

	void Multicore::setState(enum Multicore::State state) {
		this->state = state;
	}
	
	const enum Multicore::State Multicore::getState(void) {
		return state;
	}
	
	void Multicore::addEvent(const std::string eventName) {
		if (executionTrace.empty()) {
			executionTrace.push_back(std::pair<int, std::string>(elapsedTime, eventName));
		} else {
			if (executionTrace.back().second.compare(eventName) != 0) {
				executionTrace.push_back(std::pair<int, std::string>(elapsedTime, eventName));
			}
		}
	}
	
	const std::string Multicore::getExecutionTrace(const std::string &indent) {
		std::ostringstream output;
		
		output << indent << "Core ID: " << id << std::endl;
		for (std::vector<std::pair<int, std::string> >::const_iterator trace = executionTrace.begin(); trace != executionTrace.end(); ++trace) {
			output << indent << "* " << std::setw(6) << trace->first << " " << trace->second << std::endl;
		}
		
		return output.str();
	}

	const std::string Multicore::toString(const std::string &indent) {
		std::ostringstream output;

		output << indent << "Core ID: " << id << std::endl;
		output << indent << "* Elapsed time: " << elapsedTime << std::endl;
		output << indent << "* State: ";
		if (state == Multicore::executing) {
			output << "executing";
		} else if (state == Multicore::executed) {
			output << "executed";
		} else {
			std::ostringstream error;
			error << "Multicore::toString: Unknown state: " << state;
			throw error.str();
		}

		output << std::endl;

		return output.str();
	}
	
}

