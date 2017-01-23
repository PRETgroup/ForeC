/*
 *  MaxPlus.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "MaxPlus.hpp"

#include "Reaction.hpp"
#include "Threading.hpp"

#include "../tools/Costing.hpp"
#include "../tools/Multicore.hpp"
#include "../tools/Scheduler.hpp"
#include "../tools/Threading.hpp"

#include <iostream>
#include <set>

namespace forec {
	namespace maxplus {
		int MaxPlus::progressCounter = 0;
		std::string MaxPlus::mainThreadId;
		std::string MaxPlus::executionTrace;
		std::map<std::string, std::set<std::string> > MaxPlus::visitedReactions;
		std::map<std::string, unsigned int> MaxPlus::reactionsSeenCount;
		std::map<std::string, Reaction *> MaxPlus::maximumReaction;
		std::set<std::string> MaxPlus::threadIds;
		std::map<std::string, std::vector<std::vector<Reaction *> > > MaxPlus::trace;
		
		void MaxPlus::clear(void) {
			MaxPlus::progressCounter = 0;
			MaxPlus::visitedReactions.clear();
			MaxPlus::reactionsSeenCount.clear();
			MaxPlus::maximumReaction.clear();
			MaxPlus::threadIds.clear();
			MaxPlus::trace.clear();
		}
		
		void MaxPlus::setMainThreadId(const std::string &mainThreadId) {
			MaxPlus::mainThreadId = mainThreadId;
		}
		
		void MaxPlus::setThreads(void) {
			MaxPlus::threadIds = tools::Threading::getAllThreadIds();
		}
		
		const std::map<std::string, unsigned int> MaxPlus::getReactionsSeenCount(void) {
			return MaxPlus::reactionsSeenCount;
		}
		
		Reaction *MaxPlus::getMaximumReaction(const std::string &threadId) {
			return MaxPlus::maximumReaction[threadId];
		}
		
		std::vector<Reaction *> MaxPlus::getCurrentReactions(const std::string &threadId) {
			return MaxPlus::trace[threadId].back();
		}

		std::vector<Reaction *> MaxPlus::getActiveReactions(std::vector<Reaction *> reactions) {
			std::vector<Reaction *> activeReactions;
			
			for (std::vector<Reaction *>::iterator reaction = reactions.begin(); reaction != reactions.end(); ++reaction) {
				if ((*reaction)->getState() != Reaction::terminated) {
					activeReactions.push_back(*reaction);
				}
			}

			return activeReactions;
		}

		std::vector<Reaction *> MaxPlus::getCurrentActiveReactions(const std::string &threadId) {
			return MaxPlus::getActiveReactions(MaxPlus::getCurrentReactions(threadId));
		}
		
		void MaxPlus::computeEachThread(void) {
			for (std::set<std::string>::iterator threadId = MaxPlus::threadIds.begin(); threadId != MaxPlus::threadIds.end(); ++threadId) {
				Reaction *startingReaction = new Reaction(*threadId);
				std::vector<Reaction *> startingReactionSet;
				startingReactionSet.push_back(startingReaction);
			
				MaxPlus::trace[*threadId].push_back(startingReactionSet);
				MaxPlus::visitedReactions[*threadId].insert(startingReaction->getStateId());
				MaxPlus::maximumReaction[*threadId] = startingReaction;
			
				std::vector<Reaction *> currentActiveReactions = MaxPlus::getCurrentActiveReactions(*threadId);

				// Continue to evolve the reactions while at least one reaction is active.
				while (!currentActiveReactions.empty()) {
					// Repeat while reactions have not paused or terminated.
					std::vector<Reaction *> finishedReactions;
			
					do {
						// Let the reaction evolve.
						// When a branch (or abort) occurs, an alternate reaction is appended to currentActiveReactions.
						enum Reaction::Execution reactionState = currentActiveReactions.front()->react(currentActiveReactions);

						if (reactionState == Reaction::reacted || reactionState == Reaction::terminated) {
							// Remove the reaction.
							finishedReactions.push_back(currentActiveReactions.front());
							currentActiveReactions.erase(currentActiveReactions.begin());
						} else if (reactionState != Reaction::branch) {
							std::ostringstream error;
							error << "MaxPLus::compute: Invalid reaction state encountered:" << std::endl << currentActiveReactions.front()->toString();
							throw error.str();
						}

						if (MaxPlus::progressCounter++ > 99) {
							MaxPlus::progressCounter = 0;
							std::cout << '.';
							std::flush(std::cout);
						}
					} while (!currentActiveReactions.empty());
				
					// One evolution of each reaction completed.
					std::cout << '|';
					std::flush(std::cout);

					// Update the maximum reaction encountered.
					for (std::vector<Reaction *>::const_iterator finishedReaction = finishedReactions.begin(); finishedReaction != finishedReactions.end(); ++finishedReaction) {
						if (MaxPlus::maximumReaction[*threadId]->getReactionTime() < (*finishedReaction)->getReactionTime()) {
							MaxPlus::maximumReaction[*threadId] = *finishedReaction;
						}
					}

					Reaction::incrementGlobalCount();
					MaxPlus::reactionsSeenCount[*threadId] += finishedReactions.size();
				
					// Create the next set of reactions to evolve.
					MaxPlus::trace[*threadId].back() = finishedReactions;
					std::vector<Reaction *> nextActiveReactions = MaxPlus::getCurrentActiveReactions(*threadId);
					std::vector<Reaction *> nextActiveReactionsCopy;
					for (std::vector<Reaction *>::iterator nextActiveReaction = nextActiveReactions.begin(); nextActiveReaction != nextActiveReactions.end(); ++nextActiveReaction) {
						Reaction *nextActiveReactionCopy = new Reaction(*(*nextActiveReaction), false);

						if (visitedReactions[*threadId].find(nextActiveReactionCopy->getStateId()) != visitedReactions[*threadId].end() && !nextActiveReactionCopy->isIterating()) {
							delete nextActiveReactionCopy;
						} else {
							nextActiveReactionsCopy.push_back(nextActiveReactionCopy);
							visitedReactions[*threadId].insert(nextActiveReactionCopy->getStateId());
						}
					}

					MaxPlus::trace[*threadId].push_back(nextActiveReactionsCopy);
					currentActiveReactions = MaxPlus::getCurrentActiveReactions(*threadId);
				}
			}
		}
		
		const unsigned int MaxPlus::compute(const bool withInterleaving) {
			MaxPlus::computeEachThread();
			
			if (MaxPlus::maximumReaction.find("main") == MaxPlus::maximumReaction.end()) {
				throw std::string("MaxPlus::compute: threadId \"main\" not found.");
			}
			
			unsigned int maxReactionTime = 0;
			if (withInterleaving) {
				// Create core contexts.
				std::map<std::string, tools::Multicore *> cores;
				std::set<std::string> allCoreIds = tools::Multicore::getAllCoreIds();
				for (std::set<std::string>::const_iterator coreId = allCoreIds.begin(); coreId != allCoreIds.end(); ++coreId) {
					cores[*coreId] = new tools::Multicore(*coreId, tools::Costing::getBusCycle());
					cores[*coreId]->addEvent("Reaction Start");
				}
				
				// Compute with consideration for thread interleaving on cores.
				MaxPlus::computeWithInterleaving(mainThreadId, cores);
				maxReactionTime = cores[tools::Multicore::getAllocatedCore(mainThreadId)]->getElapsedTime();

				std::ostringstream output;
				if (!cores.empty()) {
					for (std::map<std::string, tools::Multicore *>::const_iterator core = cores.begin(); core != cores.end(); ++core) {
						output << core->second->getExecutionTrace("") << std::endl;
					}

					MaxPlus::executionTrace = output.str();
				}
			} else {
				maxReactionTime = MaxPlus::computeWithoutInterleaving();
			}			
			return maxReactionTime;
		}
		
		void MaxPlus::computeWithInterleaving(const std::string &threadId, std::map<std::string, tools::Multicore *> &cores) {
			// Add thread latency.
			const std::string coreId = tools::Multicore::getAllocatedCore(threadId);
			cores[coreId]->addEvent(threadId);
			cores[coreId]->incrementElapsedTime(MaxPlus::maximumReaction[threadId]->getReactionTime());
			
			if (tools::Threading::hasPar(threadId)) {
				// Create temporary core contexts to compare execution costs.
				std::map<std::string, tools::Multicore *> coresCopy0;
				std::map<std::string, tools::Multicore *> coresCopy1;
				for (std::map<std::string, tools::Multicore *>::const_iterator core = cores.begin(); core != cores.end(); ++core) {
					coresCopy0[core->first] = new tools::Multicore(core->first, 0);
					coresCopy1[core->first] = new tools::Multicore(core->first, 0);
				}
					
				std::vector<std::string> parIds = tools::Threading::getParIds(threadId);
				for (std::vector<std::string>::const_iterator parId = parIds.begin(); parId != parIds.end(); ++parId) {
					cores[coreId]->addEvent(threadId + " Par" + *parId + " statement");
					cores[coreId]->addEvent("Context switch");
					
					// Add max(parPresent, parAbsent) cost.
					getCopy(cores, coresCopy0, coresCopy1);
					tools::Scheduler::resolveParPresent(coresCopy0, coreId, threadId, *parId);
					tools::Scheduler::resolveParAbsent(coresCopy1, coreId, threadId);
					MaxPlus::setMax(cores, coresCopy0, coresCopy1);
				
					// Strong abort cost.
					const std::vector<std::string> enclosingStrongAborts = tools::Threading::getAborts(*parId, "strong");
					const int maxStrongAbortCount = enclosingStrongAborts.size() ;
					if (maxStrongAbortCount > 0) {
						// Add max(abortTaken, abortNotTaken) cost.
						getCopy(cores, coresCopy0, coresCopy1);
						tools::Scheduler::resolveAbortTaken(coresCopy0, *parId, maxStrongAbortCount - 1, "strong");
						tools::Scheduler::resolveAbortsNotTaken(coresCopy1, *parId, maxStrongAbortCount, "strong");
						MaxPlus::setMax(cores, coresCopy0, coresCopy1);
					}
				
					// Add the reactionStart cost.
					tools::Scheduler::reactionStart(cores, *parId);

					// Add the latency of the child threads.
					std::vector<std::string> chilThreadIds = tools::Threading::getThreadIds(*parId);
					for (std::vector<std::string>::const_iterator chilThreadId = chilThreadIds.begin(); chilThreadId != chilThreadIds.end(); ++chilThreadId) {
						MaxPlus::computeWithInterleaving(*chilThreadId, cores);
					}
					
					// Weak abort cost.
					const std::vector<std::string> enclosingWeakAborts = tools::Threading::getAborts(*parId, "weak");
					const int maxWeakAbortCount = enclosingWeakAborts.size();
					if (maxWeakAbortCount > 0) {
						getCopy(cores, coresCopy0, coresCopy1);
						tools::Scheduler::resolveAbortTaken(coresCopy0, *parId, maxWeakAbortCount - 1, "weak");
						tools::Scheduler::resolveAbortsNotTaken(coresCopy1, *parId, maxWeakAbortCount, "weak");
						MaxPlus::setMax(cores, coresCopy0, coresCopy1);
					}
				
					// Add the reactionEnd cost.
					tools::Scheduler::resolveJoin(cores, coreId, *parId, threadId);
					
					// Add parent thread cost between each par(...).
					cores[coreId]->incrementElapsedTime(MaxPlus::maximumReaction[threadId]->getReactionTime());
				}

				// Add parAbsent cost.
				tools::Scheduler::resolveParAbsent(cores, coreId, threadId);
			}
			
			if (threadId.compare("main") != 0) {
				Threading::setThreadState(coreId, threadId, tools::Threading::terminated);
			}
		}
		
		void MaxPlus::getCopy(std::map<std::string, tools::Multicore *> &cores, std::map<std::string, tools::Multicore *> &coresCopy0, std::map<std::string, tools::Multicore *> &coresCopy1) {
			for (std::map<std::string, tools::Multicore *>::iterator core = cores.begin(); core != cores.end(); ++core) {
				coresCopy0[core->first]->setElapsedTime(core->second->getElapsedTime());
				coresCopy1[core->first]->setElapsedTime(core->second->getElapsedTime());
				
				coresCopy0[core->first]->setNextStartingElapsedTime(core->second->getNextStartingElapsedTime());
				coresCopy1[core->first]->setNextStartingElapsedTime(core->second->getNextStartingElapsedTime());
			}
		}
		
		void MaxPlus::setMax(std::map<std::string, tools::Multicore *> &cores, std::map<std::string, tools::Multicore *> &coresCopy0, std::map<std::string, tools::Multicore *> &coresCopy1) {
			for (std::map<std::string, tools::Multicore *>::iterator core = cores.begin(); core != cores.end(); ++core) {
				// Elapsed times.
				if (core->second->getElapsedTime() < coresCopy0[core->first]->getElapsedTime()) {
					core->second->setElapsedTime(coresCopy0[core->first]->getElapsedTime());
				}
				
				if (core->second->getElapsedTime() < coresCopy0[core->first]->getElapsedTime()) {
					core->second->setElapsedTime(coresCopy0[core->first]->getElapsedTime());
				}
				
				// Next starting elapsed times.
				if (core->second->getNextStartingElapsedTime() < coresCopy1[core->first]->getNextStartingElapsedTime()) {
					core->second->setNextStartingElapsedTime(coresCopy1[core->first]->getNextStartingElapsedTime());
				}
				
				if (core->second->getNextStartingElapsedTime() < coresCopy1[core->first]->getNextStartingElapsedTime()) {
					core->second->setNextStartingElapsedTime(coresCopy1[core->first]->getNextStartingElapsedTime());
				}
			}
		}
		
		const unsigned int MaxPlus::computeWithoutInterleaving(void) {
			unsigned int maxReactionTime = 0;
			
			// Sum up the reaction times of the threads.
			for (std::map<std::string, Reaction *>::iterator thread = MaxPlus::maximumReaction.begin(); thread != MaxPlus::maximumReaction.end(); ++thread) {
				maxReactionTime += thread->second->getReactionTime();
			}
			
			// Get all the par(...)s.
			std::vector<std::string> parIds;
			for (std::set<std::string>::iterator threadId = MaxPlus::threadIds.begin(); threadId != MaxPlus::threadIds.end(); ++threadId) {
				if (tools::Threading::hasPar(*threadId)) {
					std::vector<std::string> containingParIds = tools::Threading::getParIds(*threadId);
 					parIds.insert(parIds.begin(), containingParIds.begin(), containingParIds.end());
 				}
			}

			for (std::vector<std::string>::const_iterator parId = parIds.begin(); parId != parIds.end(); ++parId) {
				const std::string threadScope = tools::Threading::getEnclosingThreadId(*parId);
				const std::string masterCoreId = tools::Multicore::getAllocatedCore(threadScope);

				const std::vector<std::string> enclosingStrongAborts = tools::Threading::getAborts(*parId, "strong");
				const std::vector<std::string> enclosingWeakAborts = tools::Threading::getAborts(*parId, "weak");
				const int maxStrongAbortCount = enclosingStrongAborts.size() ;
				const int maxWeakAbortCount = enclosingWeakAborts.size();

				// Add the reactionStart and reactionEnd costs for each par(...).
				maxReactionTime += tools::Scheduler::staticLatency("reactionStart", "", "", *parId, "", -1, "", -1);
				maxReactionTime += tools::Scheduler::staticLatency("reactionEnd", masterCoreId, "", *parId, threadScope, -1, "", -1);
				
				if (maxStrongAbortCount > 0) {
					// Add max(abortTaken, abortNotTaken) costs for each par(...).
					const int strongAbortLatency0 = tools::Scheduler::staticLatency("resolveAbortTaken", "", "", *parId, "", -1, "strong", maxStrongAbortCount - 1);
					const int strongAbortLatency1 = tools::Scheduler::staticLatency("resolveAbortsNotTaken", "", "", *parId, "", maxStrongAbortCount, "strong", -1);
					if (strongAbortLatency0 > strongAbortLatency1) {
						maxReactionTime += strongAbortLatency0;
					} else {
						maxReactionTime += strongAbortLatency1;
					}
				}

				if (maxWeakAbortCount > 0) {
					// Add max(abortTaken, abortNotTaken) costs for each par(...).
					const int weakAbortLatency0 = tools::Scheduler::staticLatency("resolveAbortTaken", "", "", *parId, "", -1, "weak", maxWeakAbortCount - 1);
					const int weakAbortLatency1 = tools::Scheduler::staticLatency("resolveAbortsNotTaken", "", "", *parId, "", maxWeakAbortCount, "weak", -1);
					if (weakAbortLatency0 > weakAbortLatency1) {
						maxReactionTime += weakAbortLatency0;
					} else {
						maxReactionTime += weakAbortLatency1;
					}
				}

				// Add max(parPresent, parAbsent) costs for each par(...).
				const int resolveParLatency0 = tools::Scheduler::staticLatency("resolveParPresent", masterCoreId, threadScope, *parId, "", -1, "", -1);
				const int resolveParLatency1 = tools::Scheduler::staticLatency("resolveParAbsent", masterCoreId, threadScope, "", "", -1, "", -1);
				if (resolveParLatency0 > resolveParLatency1) {
					maxReactionTime += resolveParLatency0;
				} else {
					maxReactionTime += resolveParLatency1;
				}

				// Add the resolveJoin costs for each par(...).
				maxReactionTime += tools::Scheduler::staticLatency("resolveJoin", masterCoreId, "", *parId, threadScope, -1, "", -1);
			}
			
			return maxReactionTime;
		}
		
		const std::string MaxPlus::getExecutionTrace(void) {
			return MaxPlus::executionTrace;
		}
	}
}

