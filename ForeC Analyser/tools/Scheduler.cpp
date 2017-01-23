/*
 *  Scheduler.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 20/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Scheduler.hpp"

#include "Costing.hpp"
#include "Shared.hpp"
#include "Threading.hpp"
#include "Multicore.hpp"

#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>

namespace tools {
	void Scheduler::clear(void) {

	}

	const unsigned int Scheduler::staticLatency(const std::string &type, const std::string &masterCoreId, const std::string &threadId, const std::string &parId, const std::string &threadScope, const int numberOfChecks, const std::string &variant, const int index) {
		Multicore *core = new Multicore("-1", 0);
		Scheduler::staticLatency(type, *core, masterCoreId, threadId, parId, threadScope, numberOfChecks, variant, index);
		return core->getElapsedTime();
	}
	
	void Scheduler::staticLatency(const std::string &type, Multicore &core, const std::string &masterCoreId, const std::string &threadId, const std::string &parId, const std::string &threadScope, const int numberOfChecks, const std::string &variant, const int index) {
		std::map<std::string, Multicore *> cores;

		// Create cores.
		std::set<std::string> allCoreIds = tools::Multicore::getAllCoreIds();
		for (std::set<std::string>::const_iterator coreId = allCoreIds.begin(); coreId != allCoreIds.end(); ++coreId) {
			cores[*coreId] = new Multicore(*coreId, core.getElapsedTime());
		}
		
		// Get the elapsed time.
		if (type.compare("resolveParAbsent") == 0) {
			Scheduler::resolveParAbsent(cores, masterCoreId, threadId);
		} else if (type.compare("resolveParPresent") == 0) {
			Scheduler::resolveParPresent(cores, masterCoreId, threadId, parId);
		} else if (type.compare("resolveThreadTerminate") == 0) {
			Scheduler::resolveThreadTerminate(cores, masterCoreId, threadId);
		} else if (type.compare("reactionStart") == 0) {
			Scheduler::reactionStart(cores, parId);
		} else if (type.compare("reactionEnd") == 0) {
			Scheduler::reactionEnd(cores, masterCoreId, parId, threadScope);
		} else if (type.compare("resolveJoin") == 0) {
			Scheduler::resolveJoin(cores, masterCoreId, parId, threadScope);
		} else if (type.compare("iterationEnd") == 0) {
			Scheduler::iterationEnd(cores, masterCoreId, threadId);
		} else if (type.compare("resolveAbortsNotTaken") == 0) {
			Scheduler::resolveAbortsNotTaken(cores, parId, numberOfChecks, variant);
		} else if (type.compare("resolveAbortTaken") == 0) {
			Scheduler::resolveAbortTaken(cores, parId, index, variant);
		} else {
			std::ostringstream error;
			error << "Scheduler::getStaticLatency: Unknown scheduling type: " << type << '.' << std::endl;
			throw error.str();
		}
		
		// Update the maximum elapsed time for the original core.
		for (std::set<std::string>::const_iterator coreId = allCoreIds.begin(); coreId != allCoreIds.end(); ++coreId) {
			if (core.getElapsedTime() < cores[*coreId]->getElapsedTime()) {
				core.setElapsedTime(cores[*coreId]->getElapsedTime());
			}
			
			if (core.getNextStartingElapsedTime() < cores[*coreId]->getNextStartingElapsedTime()) {
				core.setNextStartingElapsedTime(cores[*coreId]->getNextStartingElapsedTime());
			}
		}
	}

	// If the thread does not contain a par(...) then this should have no effect.
	// Set core elapsed times to be at least as long as the master core's.
	void Scheduler::resolveParAbsent(std::map<std::string, Multicore *> &cores, const std::string &masterCoreId, const std::string &threadId) {
		if (threadId.compare("main") != 0 && Threading::hasPar(threadId)) {
			// Nested thread.
			std::set<std::string> activeParCores = Multicore::getActiveParCores(threadId);
			activeParCores.erase(masterCoreId);
		
			// Master
			cores[masterCoreId]->addEvent("send(" + threadId + ", fork, null) start");
			addCost(*cores[masterCoreId], "1 gl 4");

			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				// Slave 
				cores[*activeParCore]->addEvent("get(" + threadId + ", fork) start");
				addCost(*cores[*activeParCore], "2 ls 3 ll 3");
	
				// Slave mutex
				if (cores[*activeParCore]->getElapsedTime() < cores[masterCoreId]->getElapsedTime()) {
					cores[*activeParCore]->setElapsedTime(cores[masterCoreId]->getElapsedTime());
				}
	
				// Slave receive and scheduling cost
				addCost(*cores[*activeParCore], "5 ls ll 2 gl 1");
				addCost(*cores[*activeParCore], "ll ll ls 8");
				cores[*activeParCore]->addEvent("get(" + threadId + ", fork) end");
				cores[*activeParCore]->addEvent("Context switch");
			}

			// Master scheduling cost
			addCost(*cores[masterCoreId], "ll ll ls 8");
			cores[masterCoreId]->addEvent("send(" + threadId + ", fork, null) end");
			cores[masterCoreId]->addEvent("Context switch");
		}
	}

	// Set core elapsed times to be at least as long as the master core's.
	void Scheduler::resolveParPresent(std::map<std::string, Multicore *> &cores, const std::string &masterCoreId, const std::string &threadId, const std::string &parId) {
		std::set<std::string> activeParCores = Multicore::getActiveParCores(threadId);
		activeParCores.erase(masterCoreId);
		
		if (threadId.compare("main") == 0) {
			// Master send.
			cores[masterCoreId]->addEvent("send(" + threadId + ", fork, " + parId + ") start");
			addCost(*cores[masterCoreId], "2 gs 2 gs");
			
			// Thread main scope.
			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				// Slave mutex.
				cores[*activeParCore]->addEvent("get(" + threadId + ", fork) start");
				addCost(*cores[*activeParCore], "1 gl 3");
				if (cores[*activeParCore]->getElapsedTime() < cores[masterCoreId]->getElapsedTime()) {
					cores[*activeParCore]->setElapsedTime(cores[masterCoreId]->getElapsedTime());
				}
	
				// Slave receive cost.
				addCost(*cores[*activeParCore], "4 gl 2 gl ls");
			
				// Slave schedule cost.
				if (Threading::getAllocatedThreads(parId, *activeParCore).size() != 0) {
					// Right par(...).
					addCost(*cores[*activeParCore], "ll 3", Threading::getParIndex(*activeParCore, threadId, parId));
					addCost(*cores[*activeParCore], "ll 2");
					addCost(*cores[*activeParCore], "1 ls", Threading::getNumberOfHandlers(*activeParCore, threadId, parId)*3);
					addCost(*cores[*activeParCore], "2 gs 1 gl 1 gs 3");
				}
				cores[*activeParCore]->addEvent("get(" + threadId + ", fork) end");
				cores[*activeParCore]->addEvent("Context switch");
			}
			
			// Master schedule cost.
			addCost(*cores[masterCoreId], "1 ls", Threading::getNumberOfHandlers(masterCoreId, threadId, parId)*3);
			addCost(*cores[masterCoreId], "2 gs 2 gs 1 gl 1 gs 3");
			cores[masterCoreId]->addEvent("send(" + threadId + ", fork, " + parId + ") end");
			cores[masterCoreId]->addEvent("Context switch");
		} else {
			// The par(...) is nested.

			// Master mutex.
			cores[masterCoreId]->addEvent("send(" + threadId + ", fork, " + parId + ") start");
			addCost(*cores[masterCoreId], "1 gl 6");

			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				// Slave 
				cores[*activeParCore]->addEvent("get(" + threadId + ", fork) start");
				addCost(*cores[*activeParCore], "2 ls 3 ll 3");
	
				// Slave mutex
				if (cores[*activeParCore]->getElapsedTime() < cores[masterCoreId]->getElapsedTime()) {
					cores[*activeParCore]->setElapsedTime(cores[masterCoreId]->getElapsedTime());
				}
				
				addCost(*cores[*activeParCore], "5 ls ll 2 gl 4 gl ls");
				
				// Slave receive and schedule cost.
				if (Threading::getAllocatedThreads(parId, *activeParCore).size() == 0) {
					// Wrong par(...).
					addCost(*cores[*activeParCore], "ll 4", Threading::getParIndexesSize(*activeParCore, threadId) + 2);
					addCost(*cores[*activeParCore], "1 gl 1 gs 1 ls");
				} else {
					// Right par(...).
					addCost(*cores[*activeParCore], "ll 4", Threading::getParIndex(*activeParCore, threadId, parId));
					addCost(*cores[*activeParCore], "ll 2");
					addCost(*cores[*activeParCore], "1 ls", Threading::getNumberOfHandlers(*activeParCore, threadId, parId)*3 - 2);
					addCost(*cores[*activeParCore], "ll 1 ls ll ls ll ls ll 1 ls 2 gs 1 gl 1 gs 3");
				}	
				cores[*activeParCore]->addEvent("get(" + threadId + ", fork) end");		
				cores[*activeParCore]->addEvent("Context switch");					
			}

			// Master scheduling cost
			addCost(*cores[masterCoreId], "1 gl ls");
			addCost(*cores[masterCoreId], "ll 4", Threading::getParIndex(masterCoreId, threadId, parId)*3);
			addCost(*cores[masterCoreId], "ll 2");
			addCost(*cores[masterCoreId], "1 ls", Threading::getNumberOfHandlers(masterCoreId, threadId, parId)*3 - 2);
			addCost(*cores[masterCoreId], "ll 1 ls ll ls ll ls ll 1 ls 2 gs 1 gl 1 gs 3");
			cores[masterCoreId]->addEvent("send(" + threadId + ", fork, " + parId + ") end");
			cores[masterCoreId]->addEvent("Context switch");
		}
	}
	
	// When a thread with a par(...) terminates. parId = -3
	// Set core elapsed times to be at least as long as the master core's.
	void Scheduler::resolveThreadTerminate(std::map<std::string, Multicore *> &cores, const std::string &masterCoreId, const std::string &threadId) {
		if (threadId.compare("main") != 0) {
			// Nested thread.
			if (Threading::hasPar(threadId)) {
				std::set<std::string> activeParCores = Multicore::getActiveParCores(threadId);
				activeParCores.erase(masterCoreId);
			
				// Remove handler
				cores[masterCoreId]->addEvent("send(" + threadId + ", fork, no more) start");
				addCost(*cores[masterCoreId], "2 gs", 3);
				addCost(*cores[masterCoreId], "3");

				// Master mutex
				addCost(*cores[masterCoreId], "1 gl 6");

				for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
					// Slave 
					cores[*activeParCore]->addEvent("get(" + threadId + ", fork) start");
					addCost(*cores[*activeParCore], "2 ls 3 ll 3");
	
					// Slave mutex
					if (cores[*activeParCore]->getElapsedTime() < cores[masterCoreId]->getElapsedTime()) {
						cores[*activeParCore]->setElapsedTime(cores[masterCoreId]->getElapsedTime());
					}
				
					// Slave receive, schedule and send cost.
					addCost(*cores[*activeParCore], "5 ls ll 2 gl 4 gl ls");
					addCost(*cores[*activeParCore], "ll 4", Threading::getParIndexesSize(*activeParCore, threadId) + 1);
					addCost(*cores[*activeParCore], "ll 2");
					addCost(*cores[*activeParCore], "1 gl 2 gs", 2);
					addCost(*cores[*activeParCore], "1 gl 1 gs 2 gs");
				}

				// Master receive cost
				addCost(*cores[masterCoreId], "1 gl ls");
				addCost(*cores[masterCoreId], "ll 4", Threading::getParIndexesSize(masterCoreId, threadId) + 1);
				addCost(*cores[masterCoreId], "ll 2");
				addCost(*cores[masterCoreId], "1 gl 2 gs", 2);

				for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
					// Master max
					if (cores[masterCoreId]->getElapsedTime() < cores[*activeParCore]->getElapsedTime()) {
						cores[masterCoreId]->setElapsedTime(cores[*activeParCore]->getElapsedTime());
						addCost(*cores[masterCoreId], "3");
					}
					addCost(*cores[masterCoreId], "1 gl 2");
				}
				addCost(*cores[masterCoreId], "1 gs 2 gs");
				addCost(*cores[masterCoreId], "2 gs", activeParCores.size());
				addCost(*cores[masterCoreId], "1 gl 2 gs");
					  
				for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
					// Slave receive cost
					if (cores[*activeParCore]->getElapsedTime() < cores[masterCoreId]->getElapsedTime()) {
						cores[*activeParCore]->setElapsedTime(cores[masterCoreId]->getElapsedTime());
					}

					addCost(*cores[*activeParCore], "4 gl 1 gl 2");
					addCost(*cores[*activeParCore], "ll ll ls", 2);
					addCost(*cores[*activeParCore], "ll ll ls 8");
					cores[*activeParCore]->addEvent("get(" + threadId + ", fork) end");
					cores[*activeParCore]->addEvent("Context switch");
				}

				addCost(*cores[masterCoreId], "ll ll ls", 2);
				addCost(*cores[masterCoreId], "1 gl ls 8");
				cores[masterCoreId]->addEvent("send(" + threadId + ", fork, no more) end");
				cores[masterCoreId]->addEvent("Context switch");
			}
			
			addCost(*cores[masterCoreId], "1 gl 2 gs");
			addCost(*cores[masterCoreId], "ll ll ls", 3);
			addCost(*cores[masterCoreId], "8");
		}
		
		cores[masterCoreId]->addEvent(threadId + " Terminated");
	}
	
	// Thread demarcating the start of a par(...)'s child threads.
	void Scheduler::reactionStart(std::map<std::string, Multicore *> &cores, const std::string &parId) {
		std::set<std::string> allocatedParCores = Multicore::getAllocatedParCores(parId);
		
		for (std::set<std::string>::const_iterator allocatedParCore = allocatedParCores.begin(); allocatedParCore != allocatedParCores.end(); ++allocatedParCore) {
			cores[*allocatedParCore]->addEvent("Par" + parId + " reference start");
			addCost(*cores[*allocatedParCore], "ll ll ls 8");
			cores[*allocatedParCore]->addEvent("Par" + parId + " reference end");
			cores[*allocatedParCore]->addEvent("Context switch");
		}
	}

	// par(...) has reacted.
	// Set all cores to the maximum elapsed times.
	void Scheduler::reactionEnd(std::map<std::string, Multicore *> &cores, const std::string &masterCoreId, const std::string &parId, const std::string &threadScope) {
		std::set<std::string> activeParCores = Multicore::getActiveParCores(threadScope);
		activeParCores.erase(masterCoreId);

		if (threadScope.compare("main") == 0) {
			// Thread main scope.
			cores[masterCoreId]->addEvent("get(" + threadScope + ", join) start");
			addCost(*cores[masterCoreId], "1 gl 1");		
			if (Threading::parCoreTerminated(parId, masterCoreId)) {
				addCost(*cores[masterCoreId], "4 gs");
			} else {
				addCost(*cores[masterCoreId], "2 gs 3");
			}
			
			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				const bool parCoreTerminated = Threading::parCoreTerminated(parId, *activeParCore);

				// Slave send cost
				cores[*activeParCore]->addEvent("send(" + threadScope + ", " + (parCoreTerminated ? "terminated" : "paused") + ") start");
				addCost(*cores[*activeParCore], "1 gl 1");
				
				if (parCoreTerminated) {
					addCost(*cores[*activeParCore], "3 gl ls 1 ls 2 gs");
				} else {
					addCost(*cores[*activeParCore], "2 gs");
				}
				cores[*activeParCore]->addEvent("send(" + threadScope + ", " + (parCoreTerminated ? "terminated" : "paused") + ") end");
				cores[*activeParCore]->addEvent("Context switch");

				// Master max receive cost.
				if (cores[masterCoreId]->getElapsedTime() < cores[*activeParCore]->getElapsedTime()) {
					cores[masterCoreId]->setElapsedTime(cores[*activeParCore]->getElapsedTime());
					addCost(*cores[masterCoreId], "4");
				}
				addCost(*cores[masterCoreId], "1 gl 2");
			}
			
			// Master.
			addCost(*cores[masterCoreId], "3");
			
			// Master combine cost.
			combineCost(*cores[masterCoreId], threadScope, parId);
			
			// Master check termination.
			addCost(*cores[masterCoreId], "1 gl 2", activeParCores.size() + 1);
			addCost(*cores[masterCoreId], "2");

			// Reset slave core states.
			addCost(*cores[masterCoreId], "2 gs", activeParCores.size());
			cores[masterCoreId]->addEvent("get(" + threadScope + ", join) end");
			cores[masterCoreId]->addEvent("Context switch");
			
			// Set the next starting elapsed time for all the cores.	
			unsigned int masterCost = 0;
			addCost(masterCost, "1 gl 2 gs");
			
			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				// Slave receive cost
				unsigned int slaveCost = masterCost;
				addCost(slaveCost, "4 gl 1 gl 3 gl 2 gs");

				if (Threading::parCoreTerminated(parId, *activeParCore)) {
					addCost(slaveCost, "1 gl 3 gl ll 2");
				}
				
				addCost(slaveCost, "ll ll ls 8");
				cores[*activeParCore]->setNextStartingElapsedTime(slaveCost);
			}
			
			addCost(masterCost, "ll ll ls 8");
			cores[masterCoreId]->setNextStartingElapsedTime(masterCost);
		} else {
			// Nested par(...).
			cores[masterCoreId]->addEvent("get(" + threadScope + ", join) start");
			addCost(*cores[masterCoreId], "1 gl 1");
			if (Threading::parCoreTerminated(parId, masterCoreId)) {
				addCost(*cores[masterCoreId], "4 gs");
			} else {
				addCost(*cores[masterCoreId], "2 gs 3");
			}
			
			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				const bool parCoreTerminated = Threading::parCoreTerminated(parId, *activeParCore);

				// Slave send cost
				cores[*activeParCore]->addEvent("send(" + threadScope + ", " + (parCoreTerminated ? "terminated" : "paused") + ") start");
				addCost(*cores[*activeParCore], "1 gl 1");

				if (parCoreTerminated) {
					addCost(*cores[*activeParCore], "3 gl ls 1 ls 2 gs");
				} else {
					addCost(*cores[*activeParCore], "2 gs");
				}

				// Master max receive cost.
				if (cores[masterCoreId]->getElapsedTime() < cores[*activeParCore]->getElapsedTime()) {
					cores[masterCoreId]->setElapsedTime(cores[*activeParCore]->getElapsedTime());
					addCost(*cores[masterCoreId], "4");
				}
				addCost(*cores[masterCoreId], "1 gl 2");
			}

			// Master combine cost.
			combineCost(*cores[masterCoreId], threadScope, parId);
			
			// Master check termination.
			addCost(*cores[masterCoreId], "1 gl 2", activeParCores.size() + 1);
			addCost(*cores[masterCoreId], "2");

			// Reset slave core states.
			addCost(*cores[masterCoreId], "2 gs", activeParCores.size());
			addCost(*cores[masterCoreId], "1 gl 2 gs");

			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				const bool parCoreTerminated = Threading::parCoreTerminated(parId, *activeParCore);

				// Slave receive cost.
				if (cores[*activeParCore]->getElapsedTime() < cores[masterCoreId]->getElapsedTime()) {
					cores[*activeParCore]->setElapsedTime(cores[masterCoreId]->getElapsedTime());
				}
				
				addCost(*cores[*activeParCore], "4 gl 1 gl 3 gl 2 gs");
				
				if (parCoreTerminated) {
					addCost(*cores[*activeParCore], "1 gl 3 gl ll 2");
				}
				
				addCost(*cores[*activeParCore], "ll ll ls 8");
				cores[*activeParCore]->addEvent("send(" + threadScope + ", " + (parCoreTerminated ? "terminated" : "paused") + ") end");
				cores[*activeParCore]->addEvent("Context switch");
			}
			
			addCost(*cores[masterCoreId], "ll ll ls 8");
			cores[masterCoreId]->addEvent("get(" + threadScope + ", join) end");
			cores[masterCoreId]->addEvent("Context switch");
		}
	}

	// par(...) has terminated.
	// Set the elapsed time of the master core to the longest elapsed time of its slave cores.
	// Also, consider the resolution time.
	void Scheduler::resolveJoin(std::map<std::string, Multicore *> &cores, const std::string &masterCoreId, const std::string &parId, const std::string &threadScope) {
		std::set<std::string> activeParCores = Multicore::getActiveParCores(threadScope);
		activeParCores.erase(masterCoreId);

		if (threadScope.compare("main") == 0) {
			// Thread main scope.
			cores[masterCoreId]->addEvent("get(" + threadScope + ", join) start");
			addCost(*cores[masterCoreId], "1 gl 5 gs");

			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				// Slave send cost
				cores[*activeParCore]->addEvent("send(" + threadScope + ", terminated) start");
				addCost(*cores[*activeParCore], "1 gl 4 gl ls 1 ls 2 gs");

				// Master max receive cost.
				if (cores[masterCoreId]->getElapsedTime() < cores[*activeParCore]->getElapsedTime()) {
					cores[masterCoreId]->setElapsedTime(cores[*activeParCore]->getElapsedTime());
					addCost(*cores[masterCoreId], "4");
				}
				addCost(*cores[masterCoreId], "1 gl 2");
			}

			// Master.
			addCost(*cores[masterCoreId], "3");

			// Master combine cost.
			combineCost(*cores[masterCoreId], threadScope, parId);

			// Master check termination.
			addCost(*cores[masterCoreId], "1 gl 2", activeParCores.size() + 1);
			addCost(*cores[masterCoreId], "1 gs 2 gs");
			addCost(*cores[masterCoreId], "2 gs", activeParCores.size());
			addCost(*cores[masterCoreId], "1 gl 2 gs");
			
			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				// Slave receive cost.
				if (cores[*activeParCore]->getElapsedTime() < cores[masterCoreId]->getElapsedTime()) {
					cores[*activeParCore]->setElapsedTime(cores[masterCoreId]->getElapsedTime());
				}
				
				addCost(*cores[*activeParCore], "4 gl 1 gl 3 gl 2 gs 1 gl 3 gl ll 4");
				cores[*activeParCore]->addEvent("send(" + threadScope + ", terminated) end");
				cores[*activeParCore]->addEvent("Context switch");
			}
			
			addCost(*cores[masterCoreId], "1 gl ls 8");
			cores[masterCoreId]->addEvent("get(" + threadScope + ", join) end");
			cores[masterCoreId]->addEvent("Context switch");
		} else {
			// Nested par(...).
			cores[masterCoreId]->addEvent("get(" + threadScope + ", join) start");
			addCost(*cores[masterCoreId], "1 gl 5 gs");
			
			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				// Slave send cost
				cores[*activeParCore]->addEvent("send(" + threadScope + ", terminated) start");
				addCost(*cores[*activeParCore], "1 gl 4 gl ls 1 ls 2 gs");
			
				// Master max receive cost.
				if (cores[masterCoreId]->getElapsedTime() < cores[*activeParCore]->getElapsedTime()) {
					cores[masterCoreId]->setElapsedTime(cores[*activeParCore]->getElapsedTime());
					addCost(*cores[masterCoreId], "4");
				}
				addCost(*cores[masterCoreId], "1 gl 2");
			}

			// Master.
			addCost(*cores[masterCoreId], "3");

			// Master combine cost.
			combineCost(*cores[masterCoreId], threadScope, parId);
			
			// Master check termination.
			addCost(*cores[masterCoreId], "1 gl 2", activeParCores.size() + 1);
			addCost(*cores[masterCoreId], "4 gs 2 gs");
			addCost(*cores[masterCoreId], "2 gs", activeParCores.size());
			addCost(*cores[masterCoreId], "1 gl 2 gs");

			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				// Slave receive cost
				if (cores[*activeParCore]->getElapsedTime() < cores[masterCoreId]->getElapsedTime()) {
					cores[*activeParCore]->setElapsedTime(cores[masterCoreId]->getElapsedTime());
				}
				
				addCost(*cores[*activeParCore], "4 gl 1 gl 3 gl 2 gs 1 gl 3 gl ll 4 ll 1 ls ll ls ll ls ll 1 ls 3");
				cores[*activeParCore]->addEvent("send(" + threadScope + ", terminated) end");
				cores[*activeParCore]->addEvent("Context switch");
			}
			
			addCost(*cores[masterCoreId], "ll 1 ls ll ls 1 ls 1 ls ll ls ll 1 ls 1 gl ls 8");
			cores[masterCoreId]->addEvent("get(" + threadScope + ", join) end");
			cores[masterCoreId]->addEvent("Context switch");
		}
	}

	// par(...) is in a loop. parId = -2
	// Set all cores to the maximum elapsed times.
	void Scheduler::iterationEnd(std::map<std::string, Multicore *> &cores, const std::string &masterCoreId, const std::string &threadId) {
		std::set<std::string> activeParCores = Multicore::getActiveParCores(threadId);
		activeParCores.erase(masterCoreId);

		if (threadId.compare("main") == 0) {
			// Thread main scope.
			cores[masterCoreId]->addEvent("send(" + threadId + ", iteration) start");
			addCost(*cores[masterCoreId], "2 gs 2 gs");
			
			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				// Slave.
				cores[*activeParCore]->addEvent("get(" + threadId + ", iteration) start");
				addCost(*cores[*activeParCore], "1 gl 3");
	
				// Slave max.
				if (cores[*activeParCore]->getElapsedTime() < cores[masterCoreId]->getElapsedTime()) {
					cores[*activeParCore]->setElapsedTime(cores[masterCoreId]->getElapsedTime());
				}
				
				// Slave receive, schedule and send cost.
				addCost(*cores[*activeParCore], "4 gl 2 gl ls");
				addCost(*cores[*activeParCore], "ll 3", Threading::getParIndexesSize(*activeParCore, threadId));
				addCost(*cores[*activeParCore], "1 gl 1 gs 2 gs");
			}

			// Master receive cost.
			addCost(*cores[masterCoreId], "2 gs 4 gl 2");
			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				// Master max receive cost.
				if (cores[masterCoreId]->getElapsedTime() < cores[*activeParCore]->getElapsedTime()) {
					cores[masterCoreId]->setElapsedTime(cores[*activeParCore]->getElapsedTime());
					addCost(*cores[masterCoreId], "4");
				}
				addCost(*cores[masterCoreId], "1 gl 2");
			}
			addCost(*cores[masterCoreId], "1 gs 2 gs");
			addCost(*cores[masterCoreId], "2 gs", activeParCores.size());
			addCost(*cores[masterCoreId], "1 gl 2 gs");
			
			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				// Slave receive cost.
				if (cores[*activeParCore]->getElapsedTime() < cores[masterCoreId]->getElapsedTime()) {
					cores[*activeParCore]->setElapsedTime(cores[masterCoreId]->getElapsedTime());
				}
				addCost(*cores[*activeParCore], "4 gl 1 gl 3 gl 2 gs 1 gl 4");
				cores[*activeParCore]->addEvent("get(" + threadId + ", iteration) end");
				cores[*activeParCore]->addEvent("Context switch");
			}
			
			addCost(*cores[masterCoreId], "1 gl ls ll 8");
			cores[masterCoreId]->addEvent("send(" + threadId + ", iteration) end");
			cores[masterCoreId]->addEvent("Context switch");
		} else {
			// Nested thread.
			
			// Master mutex
			cores[masterCoreId]->addEvent("send(" + threadId + ", iteration) start");
			addCost(*cores[masterCoreId], "2 gs", 3);
			addCost(*cores[masterCoreId], "4 gl 6");

			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				// Slave 
				cores[*activeParCore]->addEvent("get(" + threadId + ", iteration) start");
				addCost(*cores[*activeParCore], "2 ls 3 ll 3");
	
				// Slave max
				if (cores[*activeParCore]->getElapsedTime() < cores[masterCoreId]->getElapsedTime()) {
					cores[*activeParCore]->setElapsedTime(cores[masterCoreId]->getElapsedTime());
				}
				
				// Slave receive, schedule and send cost.
				addCost(*cores[*activeParCore], "5 ls ll 2 gl 4 gl ls");
				addCost(*cores[*activeParCore], "ll 4", Threading::getParIndexesSize(*activeParCore, threadId));
				addCost(*cores[*activeParCore], "ll 3 gl 1 gs 2 gs");
			}

			// Master receive cost
			addCost(*cores[masterCoreId], "1 gl ls");
			addCost(*cores[masterCoreId], "ll 4", Threading::getParIndexesSize(masterCoreId, threadId));
			addCost(*cores[masterCoreId], "ll 2");
			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				// Master max receive cost.
				if (cores[masterCoreId]->getElapsedTime() < cores[*activeParCore]->getElapsedTime()) {
					cores[masterCoreId]->setElapsedTime(cores[*activeParCore]->getElapsedTime());
					addCost(*cores[masterCoreId], "3");
				}
				addCost(*cores[masterCoreId], "1 gl 2");
			}
			addCost(*cores[masterCoreId], "1 gs 2 gs 3");
			addCost(*cores[masterCoreId], "2 gs", activeParCores.size());
			addCost(*cores[masterCoreId], "1 gl 2 gs");
				  
			for (std::set<std::string>::const_iterator activeParCore = activeParCores.begin(); activeParCore != activeParCores.end(); ++activeParCore) {
				// Slave receive cost
				if (cores[*activeParCore]->getElapsedTime() < cores[masterCoreId]->getElapsedTime()) {
					cores[*activeParCore]->setElapsedTime(cores[masterCoreId]->getElapsedTime());
				}
				
				addCost(*cores[*activeParCore], "4 gl 1 gl 5");
				cores[*activeParCore]->addEvent("get(" + threadId + ", iteration) end");
				cores[*activeParCore]->addEvent("Context switch");
			}
			
			addCost(*cores[masterCoreId], "1 gl ls 8");
			cores[masterCoreId]->addEvent("send(" + threadId + ", iteration) end");
			cores[masterCoreId]->addEvent("Context switch");
		}
	}

	// TODO: Calculate the real cost of evaluating the condition.
	void Scheduler::resolveAbortsNotTaken(std::map<std::string, Multicore *> &cores, const std::string &parId, const int numberOfChecks, const std::string &variant) {
		std::set<std::string> allocatedParCores = Multicore::getAllocatedParCores(parId);
		
		for (std::set<std::string>::const_iterator allocatedParCore = allocatedParCores.begin(); allocatedParCore != allocatedParCores.end(); ++allocatedParCore) {
			// Cost of checking
			cores[*allocatedParCore]->addEvent("Check " + variant + " aborts start");
			addCost(*cores[*allocatedParCore], "1 gl 3 ll ll ls 8", numberOfChecks);
			cores[*allocatedParCore]->addEvent("Check " + variant + " aborts end");
			cores[*allocatedParCore]->addEvent("Context switch");
		}
	}
	
	// TODO: Calculate the real cost of evaluating the condition.
	void Scheduler::resolveAbortTaken(std::map<std::string, Multicore *> &cores, const std::string &parId, const int index, const std::string &variant) {
		std::set<std::string> allocatedParCores = Multicore::getAllocatedParCores(parId);
		
		for (std::set<std::string>::const_iterator allocatedParCore = allocatedParCores.begin(); allocatedParCore != allocatedParCores.end(); ++allocatedParCore) {
			// Cost of checking
			cores[*allocatedParCore]->addEvent("Check " + variant + " aborts taken start");
			addCost(*cores[*allocatedParCore], "1 gl 3 ll ll ls 8", index);
			addCost(*cores[*allocatedParCore], "1 gl 2 gs 3");
			cores[*allocatedParCore]->addEvent("Check " + variant + " aborts taken end");
			cores[*allocatedParCore]->addEvent("Context switch");
		}
	}
	
	void Scheduler::addCost(Multicore &core, const std::string &costs, const int repetition) {
		std::istringstream costsBuffer(costs);
		std::istream_iterator<std::string> start(costsBuffer);
		std::istream_iterator<std::string> end;
		std::vector<std::string> costTokens(start, end);
		
		for (int i = 0; i < repetition; ++i) {
			for (std::vector<std::string>::const_iterator cost = costTokens.begin(); cost != costTokens.end(); ++cost) {
				if (std::string::npos != cost->find_first_of("0123456789")){
					// Instruction cost in clock cycles.
					unsigned int value;
					std::istringstream input(*cost);
					input >> std::dec >> value;
					core.incrementElapsedTime(value);
				} else {
					// Memory access cost.
					core.incrementElapsedTime(1);
					core.incrementElapsedTime(Costing::getAccessLatency((*cost)[0] == 'g', core.getElapsedTime(), (*cost)[1]));
				}
			}
		}
	}
	
	void Scheduler::addCost(unsigned int &core, const std::string &costs, const int repetition) {
		std::istringstream costsBuffer(costs);
		std::istream_iterator<std::string> start(costsBuffer);
		std::istream_iterator<std::string> end;
		std::vector<std::string> costTokens(start, end);
		
		for (int i = 0; i < repetition; ++i) {
			for (std::vector<std::string>::const_iterator cost = costTokens.begin(); cost != costTokens.end(); ++cost) {
				if (std::string::npos != cost->find_first_of("0123456789")){
					// Instruction cost in clock cycles.
					unsigned int value;
					std::istringstream input(*cost);
					input >> std::dec >> value;
					core += value;
				} else {
					// Memory access cost.
					core += 1;
					core += Costing::getAccessLatency((*cost)[0] == 'g', core, (*cost)[1]);
				}
			}
		}
	}
	
	// Combine cost.
	void Scheduler::combineCost(Multicore &masterCore, const std::string &threadScope, const std::string &parId) {
		const std::vector<std::pair<std::string, std::pair<int, std::string> > > variablesToCombine = Shared::getVariablesToCombine(threadScope, parId);

		if (Shared::getParIndexesSize(threadScope)) {
			addCost(masterCore, "1 gl ls");

			// Only par(...)s that need to be combined are checked.
			if (!variablesToCombine.empty()) {
				addCost(masterCore, "ll 4", Shared::getParIndex(threadScope, parId));
				addCost(masterCore, "ll 2");
			
				// Combine in shared variable declaration order.
				for (std::vector<std::pair<std::string, std::pair<int, std::string> > >::const_iterator variable = variablesToCombine.begin(); variable != variablesToCombine.end(); ++variable) {
					if (variable->second.first == 1) {
						addCost(masterCore, "1 gl 4 gs 1 gl 1 gs 2 gs");
					} else {
						addCost(masterCore, "ls");
						addCost(masterCore, "1 gl 4 gs ll 8 ls ll 1 ls", variable->second.first);
						addCost(masterCore, "ll 1 ll ll 1 gs 2 gs 4 ls 3");
					
						for (int i = 0; i < variable->second.first - 1; ++i) {
							addCost(masterCore, "ll ll 4 ll 6 ll 6");
							masterCore.setElapsedTime(Shared::combineLatency(masterCore, variable->second.second));
							addCost(masterCore, "2 gs ll 1 ls");
						}
						addCost(masterCore, "ll ll 2");
					}
				}
			} else {
				addCost(masterCore, "ll 4", Shared::getParIndexesSize(threadScope));
			}
		}
	}

	const unsigned int Scheduler::getMaxElapsedTime(std::map<std::string, Multicore *> &cores, std::set<std::string> coreIds) {
		unsigned int maxElapsedTime = 0;
		for (std::set<std::string>::const_iterator coreId = coreIds.begin(); coreId != coreIds.end(); ++coreId) {
			if (maxElapsedTime < cores[*coreId]->getElapsedTime()) {
				maxElapsedTime = cores[*coreId]->getElapsedTime();
			}
		}

		return maxElapsedTime;
	}
			
	const std::string Scheduler::toString(void) {
		std::ostringstream output;
	
		return output.str();
	}

}
