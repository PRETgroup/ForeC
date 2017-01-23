/*
 *  Threading.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 29/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Threading.hpp"

#include "../tools/Multicore.hpp"

#include "../cfg/Node.hpp"
#include "../cfg/AssemblyLine.hpp"
#include "../cfg/AbortStatement.hpp"
#include "../cfg/Label.hpp"
#include "../cfg/ParStatement.hpp"
#include "../cfg/PauseStatement.hpp"
#include "../cfg/Scheduler.hpp"
#include "../cfg/Start.hpp"
#include "../cfg/Thread.hpp"
#include "../cfg/IterationBound.hpp"

#include <fstream>
#include <sstream>
#include <string.h>

namespace forec {
	namespace reachability {
	
		// Static
		void Threading::resetThreadStates(const std::string &parId, const enum tools::Threading::State state) {
			if (tools::Threading::parCores.find(parId) == tools::Threading::parCores.end()) {
				throw std::string("Threading::resetThreadStates: par" + parId + " not found.");
			}
		
			for (std::map<std::string, std::vector<std::pair<std::string, enum tools::Threading::State> > >::iterator coreId = tools::Threading::parCores[parId].begin(); coreId != tools::Threading::parCores[parId].end(); ++coreId) {
				for(std::vector<std::pair<std::string, enum tools::Threading::State> >::iterator thread = coreId->second.begin(); thread != coreId->second.end(); ++thread) {
					thread->second = state;
				}
			}
		}
	
		void Threading::setThreadState(const std::string &coreId, const std::string &threadId, const enum tools::Threading::State state) {
			const std::string enclosingParId = tools::Threading::getEnclosingParId(threadId);
	
			if (tools::Threading::parCores.find(enclosingParId) == tools::Threading::parCores.end()) {
				throw std::string("Threading::setThreadState: enclosing par" + enclosingParId + " of thread \"" + threadId + "\" not found.");
			}
		
			if (tools::Threading::parCores[enclosingParId].find(coreId) == tools::Threading::parCores[enclosingParId].end()) {
				throw std::string("Threading::setThreadState: coreId \"" + coreId + "\" not found.");
			}
		
			for (std::vector<std::pair<std::string, enum tools::Threading::State> >::iterator thread = tools::Threading::parCores[enclosingParId][coreId].begin(); thread != tools::Threading::parCores[enclosingParId][coreId].end(); ++thread) {
				if (thread->first.compare(threadId) == 0) {
					thread->second = state;
				}
			}
		}

		// Dynamic
		Threading::Threading(const std::string &threadId) : id(threadId), coreId(tools::Multicore::getAllocatedCore(threadId)) {
			state = tools::Threading::reacting;
			alternateProgramCounter = NULL;
			programCounters.clear();
			programCounters.push_back(tools::Threading::getStartingNode(threadId));
		}
	
		// Copy constructor
		Threading::Threading(Threading &thread, const bool isLeaf, const bool isAlternate) : id(thread.id), coreId(thread.coreId) {
			alternateProgramCounter = NULL;
			programCounters.clear();

			if (isAlternate) {
				// Copy the complete history of program counters.
				programCounters.insert(programCounters.begin(), thread.programCounters.begin(), thread.programCounters.end());
			
				// Check if this is the thread that has branched or aborted.
				if (thread.alternateProgramCounter != NULL) {
					// Add the alternate program counter.
					if (programCounters.size() < 2 || tools::Threading::debugging) {
						programCounters.push_back(thread.alternateProgramCounter);
					} else {
						programCounters.back() = thread.alternateProgramCounter;
					}
				}
		
				state = thread.state;
			} else {
				programCounters.push_back(thread.programCounters.back());
				state = tools::Threading::reacting;
				thread.state = tools::Threading::reacting;
				thread.alternateProgramCounter = NULL;
			}
		}
	
		const std::string Threading::getId(void) {
			return id;
		}

		const std::string Threading::getCoreId(void) {
			return coreId;
		}
	
		void Threading::setState(enum tools::Threading::State state) {
			this->state = state;
		}
	
		const enum tools::Threading::State Threading::getState(void) {
			return state;
		}
	
		void Threading::addAlternateProgramCounter(forec::cfg::Node &alternateProgramCounter) {
			this->alternateProgramCounter = &alternateProgramCounter;
		}

		void Threading::clearAlternateProgramCounter(void) {
			this->alternateProgramCounter = NULL;
		}

		void Threading::advanceProgramCounter(forec::cfg::Node &nextProgramCounter) {
			if (programCounters.empty()) {
				std::ostringstream error;
				error << "Threading::advanceProgramCounter: No starting program counter for thread " << id << '.' << std::endl;
				throw error.str();
			} else if (programCounters.size() == 1 || tools::Threading::debugging) {
				programCounters.push_back(&nextProgramCounter);
			} else {
				programCounters.back() = &nextProgramCounter;
			}
		}

		std::vector<forec::cfg::Node *> *Threading::getProgramCounters(void) {
			return &programCounters;
		}
	
		forec::cfg::Node *Threading::getCurrentProgramCounter(void) {
			if (programCounters.empty()) {
				std::ostringstream error;
				error << "Threading::getCurrentProgramCounter: No program counter for thread " << id << '.' << std::endl;
				throw error.str();
			}
			
			return programCounters.back();
		}

		const unsigned int Threading::getCurrentAddress(void) {
			forec::cfg::Node *currentProgramCounter = Threading::getCurrentProgramCounter();
		
			unsigned int currentAddress = -1;
			if (currentProgramCounter->isType("Start")) {
				currentAddress = ((forec::cfg::Start *)currentProgramCounter)->getProgramCounter();
			} else if (currentProgramCounter->isType("AssemblyLine")) {
				currentAddress = ((forec::cfg::AssemblyLine *)currentProgramCounter)->getProgramCounter();
			} else if (currentProgramCounter->isType("AbortStatement")) {
				currentAddress = ((forec::cfg::AbortStatement *)currentProgramCounter)->getProgramCounter();
			} else if (currentProgramCounter->isType("PauseStatement")) {
				currentAddress = ((forec::cfg::PauseStatement *)currentProgramCounter)->getProgramCounter();
			} else if (currentProgramCounter->isType("ParStatement")) {
				currentAddress = ((forec::cfg::ParStatement *)currentProgramCounter)->getProgramCounter();
			} else if (currentProgramCounter->isType("Scheduler")) {
				currentAddress = ((forec::cfg::Scheduler *)currentProgramCounter)->getProgramCounter();
			} else if (currentProgramCounter->isType("IterationBound")) {
				currentAddress = 0;
			} else {
				std::ostringstream error;
				error << "Threading::getCurrentAddress: Unknown type of programCounter: " << currentProgramCounter->getType() << std::endl
					  << *currentProgramCounter;
				throw error.str();
			}
		
			return currentAddress;
		}
	
		const std::string Threading::toString(const std::string &indent) {
			std::ostringstream output;

			output << indent << "\t* Thread: " << id << " (";
			switch (state) {
				case (tools::Threading::reacting):		output << "reacting";
														break;

				case (tools::Threading::reacted):		output << "reacted";
														break;
									
				case (tools::Threading::terminated):	output << "terminated";
														break;

				case (tools::Threading::branch):		output << "branch";
														break;
											
				default:								output << "unspecified";
														break;
			}
			output << ')' << std::endl;

			output << indent << "\t  ProgramCounters:";
			for (std::vector<forec::cfg::Node *>::const_iterator programCounter = programCounters.begin(); programCounter != programCounters.end(); ++programCounter) {
				if ((*programCounter)->isType("Start")) {
					output << "Start";
				} else if ((*programCounter)->isType("AssemblyLine")) {
					output << " 0x" << std::hex << ((forec::cfg::AssemblyLine *)*programCounter)->getProgramCounter();
				} else if ((*programCounter)->isType("AbortStatement")) {
					output << " abort(" << "0x" << std::hex << ((forec::cfg::AbortStatement *)*programCounter)->getProgramCounter() << ')';
				} else if ((*programCounter)->isType("PauseStatement")) {
					output << " pause(" << "0x" << std::hex << ((forec::cfg::PauseStatement *)*programCounter)->getProgramCounter() << ')';
				} else if ((*programCounter)->isType("ParStatement")) {
					output << " par(" << "0x" << std::hex << ((forec::cfg::ParStatement *)*programCounter)->getProgramCounter() << ')';
				} else if ((*programCounter)->isType("Scheduler")) {
					output << " scheduler(" << "0x" << std::hex << ((forec::cfg::Scheduler *)*programCounter)->getProgramCounter() << ')';
				} else if ((*programCounter)->isType("Label")) {
					output << " label(" << ((forec::cfg::Label *)*programCounter)->getId() << ')';
				} else if ((*programCounter)->isType("IterationBound")) {
					output << " bound" ;
				} else {
					throw std::string("Threading::toString: Unknown type of programCounter: " + (*programCounter)->getType());
				} 
			}
			output << std::dec << std::endl;

			return output.str();
		}
	}
}
