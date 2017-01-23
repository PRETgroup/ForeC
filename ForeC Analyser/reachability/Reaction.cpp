/*
 *  Reaction.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 21/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Reaction.hpp"
#include "Threading.hpp"

#include "../tools/Costing.hpp"
#include "../tools/Link.hpp"
#include "../tools/Multicore.hpp"
#include "../tools/Scheduler.hpp"
#include "../tools/Threading.hpp"

#include "../cfg/Node.hpp"
#include "../cfg/AssemblyLine.hpp"
#include "../cfg/AbortStatement.hpp"
#include "../cfg/IterationBound.hpp"
#include "../cfg/ParStatement.hpp"
#include "../cfg/PauseStatement.hpp"
#include "../cfg/Scheduler.hpp"

namespace global {
	extern bool merge;
	extern bool mergeGlobalAccesses;
}

namespace forec {
	namespace reachability {
		int Reaction::globalCount = 1;
		int Reaction::globalSubCount = 1;

		void Reaction::incrementGlobalCount(void) {
			Reaction::globalCount++;
		}

		const int Reaction::getGlobalCount(void) {
			return Reaction::globalCount;
		}

		void Reaction::incrementGlobalSubCount(void) {
			Reaction::globalSubCount++;
		}

		const int Reaction::getGlobalSubCount(void) {
			return Reaction::globalSubCount;
		}

		Reaction::Reaction(const std::string &threadId) {
			this->state.id = globalCount;
			this->state.subId = globalSubCount;
	
			threadTree.thread = new Threading(threadId);
		
			threadTree.justForked = false;
			threadTree.justJoined = false;
			threadTree.aborts.checked["strong"] = false;
			threadTree.aborts.checked["weak"] = false;
		
			threadTree.childThreads.first = "";
			threadTree.childThreads.second.clear();
			threadsRemoved.clear();
		
			state.stringId << std::hex << threadTree.thread->getCurrentAddress() << '_';
			state.execution = Reaction::reacting;
			threadWithAlternative = NULL;

			std::set<std::string> allCoreIds = tools::Multicore::getAllCoreIds();
			for (std::set<std::string>::const_iterator coreId = allCoreIds.begin(); coreId != allCoreIds.end(); ++coreId) {
				if (allCoreIds.size() == 1) {
					cores[*coreId] = new tools::Multicore(*coreId, 0);
				} else {
					cores[*coreId] = new tools::Multicore(*coreId, tools::Costing::getBusCycle());
				}
				cores[*coreId]->addEvent("Reaction Start");
			}
		
			iterationCounts.clear();
		}

		// Copy constructor
		Reaction::Reaction(Reaction &reaction, const bool isAlternate, const bool isAbortPar) {
			this->state.id = globalCount;
			this->threadWithAlternative = NULL;
		
			if (isAlternate) {
				// Alternate reaction for a branch
				Reaction::incrementGlobalSubCount();
				this->state.subId = Reaction::getGlobalSubCount();
				this->state.stringId << reaction.getStateId();
				this->state.execution = reaction.getOverallState();

				for (std::map<std::string, tools::Multicore *>::const_iterator core = reaction.cores.begin(); core != reaction.cores.end(); ++core) {
					this->cores[core->first] = new tools::Multicore(*core->second);
				}
			
				// Retain the history of removed threads.
				threadsRemoved.insert(threadsRemoved.begin(), reaction.threadsRemoved.begin(), reaction.threadsRemoved.end());
			} else {
				// New evolution of a reaction
				this->state.subId = reaction.state.subId;
				this->state.execution = Reaction::reacting;
			
				for (std::map<std::string, tools::Multicore *>::const_iterator core = reaction.cores.begin(); core != reaction.cores.end(); ++core) {
					this->cores[core->first] = new tools::Multicore(core->first, core->second->getNextStartingElapsedTime());
					this->cores[core->first]->addEvent("Reaction Start");
				}
			}

			Reaction::copyThreadTree(reaction.threadTree, this->threadTree, *reaction.threadWithAlternative, isAlternate, isAbortPar);

			iterationCounts.clear();
			for (std::map<forec::cfg::IterationBound *, int>::const_iterator bound = reaction.iterationCounts.begin(); bound != reaction.iterationCounts.end(); ++bound) {
				iterationCounts[bound->first] = bound->second;
			}
		}

		void Reaction::copyThreadTree(struct Reaction::ThreadTree &threadTree, struct Reaction::ThreadTree &threadTreeCopy, Threading &threadWithAlternative, const bool isAlternate, const bool isAbortPar) {
			if (threadTree.thread->getState() != tools::Threading::terminated || isAlternate) {
				// Make a copy of the Threading object.
				threadTreeCopy.thread = new Threading(*threadTree.thread, threadTree.childThreads.second.empty(), isAlternate);
			
				if (!isAlternate) {
					// New evolution of a reaction.
					threadTree.justForked = false;
					threadTree.justJoined = false;
					threadTree.aborts.checked["strong"] = false;
					threadTree.aborts.checked["weak"] = false;
				
					if (threadTree.childThreads.second.empty()) {
						// Leaf
						this->state.stringId << std::hex << threadTreeCopy.thread->getCurrentAddress() << '_';
					}
				}
			
				threadTreeCopy.justForked = threadTree.justForked;
				threadTreeCopy.justJoined = threadTree.justJoined;
				threadTreeCopy.aborts.checked["strong"] = threadTree.aborts.checked["strong"];
				threadTreeCopy.aborts.checked["weak"] = threadTree.aborts.checked["weak"];
				threadTreeCopy.childThreads.first = threadTree.childThreads.first;
				threadTreeCopy.childThreads.second.clear();
			
				// Stop copying if an enclosing abort is taken.
				if (!(isAbortPar && &threadWithAlternative == threadTree.thread)) {
					// Copy the par(...) child threads.
					for (std::vector<struct Reaction::ThreadTree>::iterator childThread = threadTree.childThreads.second.begin(); childThread != threadTree.childThreads.second.end(); ++childThread) {
						struct Reaction::ThreadTree childThreadTreeCopy;
						Reaction::copyThreadTree(*childThread, childThreadTreeCopy, threadWithAlternative, isAlternate, isAbortPar);
						threadTreeCopy.childThreads.second.push_back(childThreadTreeCopy);
					}
				}

			}
		}

		const int Reaction::getId(void) const {
			return this->state.id;
		}

		const int Reaction::getSubId(void) const {
			return this->state.subId;
		}

		const enum Reaction::Execution Reaction::getOverallState(void) const {
			return this->state.execution;
		}

		// If at least one thread is reacting, branching or aborting, then the reaction is Reaction::reacting or Reaction::branch.
		// If all threads have terminated, then the reaction is Reaction::terminated.
		// If some threads are either reacted or terminated, then the reaction is Reaction::reacted.
		const enum Reaction::Execution Reaction::getState(void) {
			this->state.execution = getState(this->threadTree);
			return this->state.execution;
		}
	
		const enum Reaction::Execution Reaction::getState(const struct Reaction::ThreadTree &threadTree) {
			if (threadTree.childThreads.second.empty()) {
				// Leaf node
				if (threadTree.thread->getState() == tools::Threading::reacting) {
					return Reaction::reacting;
				} else if (threadTree.thread->getState() == tools::Threading::reacted) {
					return Reaction::reacted;
				} else if (threadTree.thread->getState() == tools::Threading::branch) {
					return Reaction::branch;
				} else if (threadTree.thread->getState() == tools::Threading::terminated) {
					return Reaction::terminated;
				}
			} else {
				// Fork node
				bool allTerminated = true;
			
				for (std::vector<struct Reaction::ThreadTree>::const_iterator childThread = threadTree.childThreads.second.begin(); childThread != threadTree.childThreads.second.end(); ++childThread) {
					enum Reaction::Execution childThreadState = Reaction::getState(*childThread);
				
					if (childThreadState == Reaction::reacting) {
						return Reaction::reacting;
					} else if (childThreadState == Reaction::branch) {
						return Reaction::branch;
					}
				
					allTerminated &= (childThreadState == Reaction::terminated);
				}
			
				if (allTerminated) {
					return Reaction::terminated;
				} else {
					return Reaction::reacted;
				}
			}

			throw std::string("Reaction::getState: Could not determine the correct state for " + threadTree.thread->getId() + ".");
			return Reaction::reacted;
		}

		const std::string Reaction::getStateId(void) const {
			return this->state.stringId.str();
		}
	
		const bool Reaction::isIterating(void) const {
			return !(this->iterationCounts.empty());
		}
	
		void Reaction::clearThreadWithAlternative(void) {
			this->threadWithAlternative = NULL;
		}

		Threading *Reaction::getThreadWithAlternative(void) {
			return this->threadWithAlternative;
		}

		const unsigned int Reaction::getReactionTime(void) const {
			return this->cores.find(threadTree.thread->getCoreId())->second->getElapsedTime();
		}

		const enum Reaction::Execution Reaction::react(std::vector<Reaction *> &traces) {
			this->state.execution = react(traces, this->threadTree);
			return this->state.execution;
		}
		
		const enum Reaction::Execution Reaction::react(std::vector<Reaction *> &traces, struct Reaction::ThreadTree &threadTree) {
			bool hasForked = false;
			bool hasJoined = false;

			// While threads are created or terminated.
			do {
				hasForked = false;
				hasJoined = false;

				if (threadTree.childThreads.second.empty()) {
					// CFG Leaf node

					// While the thread has not reached the reacted or terminated state.
					while (threadTree.thread->getState() != tools::Threading::reacted && threadTree.thread->getState() != tools::Threading::terminated) {
						cores[threadTree.thread->getCoreId()]->addEvent(threadTree.thread->getId());
					
						// Branching thread reached again (resume the traversal).
						this->state.execution = Reaction::reacting;
					
						// Get the current program counter.
						forec::cfg::Node *currentProgramCounter = threadTree.thread->getCurrentProgramCounter();
						
						//-----------------------------------------------------------------------------------
						// If the current node is a par statement, then add the child threads. Ignore if returning from a join.
						if (Reaction::parStatement(threadTree, *currentProgramCounter)) {
							hasForked = true;
							break;
						}
						
						// If the current node is a pause, then pause the thread. Ignore if this is a new reaction.
						if (Reaction::pauseStatement(*threadTree.thread, *currentProgramCounter)) {
							return Reaction::reacted;
						}
						
						// If the current node is the last node of the thread (thread termination).
						if (Reaction::threadRemove(*threadTree.thread, *currentProgramCounter)) {
							return Reaction::terminated;
						}
						
						// Check if an iteration end is encountered.
						Reaction::iterationEnd(*threadTree.thread, *currentProgramCounter);
						//-----------------------------------------------------------------------------------
						
						// Get the next program counters (transitions). Take the next transitions.
						std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > > nextProgramCounters = currentProgramCounter->getNextNodes();
						if (nextProgramCounters.empty()) {
							// Unexpected dead end
							std::ostringstream error;
							error << "Reaction::react: No next program counters found for " << currentProgramCounter->getId() << '.' << std::endl;
							throw error.str();
						} else {
							// Check for an iteration bound.
							Reaction::checkIterationBound(*currentProgramCounter, nextProgramCounters, *threadTree.thread);
							
							if (nextProgramCounters.size() > 1) {
								this->threadWithAlternative = threadTree.thread;
								this->state.execution = Reaction::branch;
								threadTree.thread->setState(tools::Threading::branch);
								
								for (std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > >::iterator nextProgramCounter = nextProgramCounters.begin() + 1; nextProgramCounter != nextProgramCounters.end(); ++nextProgramCounter) {
									// Take alternate transition.
									traces.push_back(Reaction::takeAlternateTransition(*this, *nextProgramCounter, *threadTree.thread));
								}
								
								this->clearThreadWithAlternative();
							}
							
							// Take the first transition.
							Reaction::takeTransition(nextProgramCounters.front(), *threadTree.thread);
							
							if (nextProgramCounters.size() > 1) {
								return Reaction::branch;
							} else {
								threadTree.thread->setState(tools::Threading::reacting);
							}
						}
					}
				} else {
					// CFG fork node
				
					// Don't add the scheduling costs when resuming from an immediate par(...) or branch (or abort).
					if (!(threadTree.justForked || this->state.execution == Reaction::branch)) {
						tools::Scheduler::reactionStart(cores, threadTree.childThreads.first);

						// Check for strong abort conditions.
						const enum Reaction::Execution result = Reaction::abortPar(traces, threadTree, "strong");

						if (result == Reaction::branch) {
							// Allow alternate reactions to be traversed.
							return Reaction::branch;
						}
					}
				
					// Propagate the state of its child threads rather than its own.
					enum Reaction::Execution childThreadResult = Reaction::reacting;
					std::vector<std::vector<struct Reaction::ThreadTree>::iterator> terminatedChildThreads;
					for (std::vector<struct Reaction::ThreadTree>::iterator childThread = threadTree.childThreads.second.begin(); childThread != threadTree.childThreads.second.end(); ++childThread) {
						if (childThread->thread->getState() == tools::Threading::terminated) {
							// A(n alternate) branched reaction copies the terminated threads.
							terminatedChildThreads.push_back(childThread);
							childThreadResult = Reaction::terminated;
						} else {
							childThreadResult = react(traces, *childThread);

							if (childThreadResult == Reaction::reacting) {
								throw std::string("Reaction::react: Child thread returned with \"reacting\" status");
							} else if (childThreadResult == Reaction::branch) {
								// Stop the iteration to allow the removal of terminated threads before returning childThreadResult.
								break;
							} else if (childThreadResult == Reaction::terminated) {		
								terminatedChildThreads.push_back(childThread);
							}
						}
					}
				
					// Remove the terminated child threads.
					for (std::vector<std::vector<struct Reaction::ThreadTree>::iterator>::iterator terminatedChildThread = terminatedChildThreads.begin(); terminatedChildThread != terminatedChildThreads.end(); ++terminatedChildThread) {
						threadsRemoved.push_back((*terminatedChildThread)->thread);
					}
				
					for (std::vector<std::vector<struct Reaction::ThreadTree>::iterator>::reverse_iterator terminatedChildThread = terminatedChildThreads.rbegin(); terminatedChildThread != terminatedChildThreads.rend(); ++terminatedChildThread) {
						threadTree.childThreads.second.erase(*terminatedChildThread);
					}

					if (childThreadResult == Reaction::branch) {
						return childThreadResult;
					}
				
					if (threadTree.childThreads.second.empty()) {
						// par(...) has terminated.

						hasJoined = true;
						threadTree.justForked = false;
						threadTree.justJoined = true;
					
						// Check for weak abort conditions (redundant but part of the implementation).
						const enum Reaction::Execution result = Reaction::abortPar(traces, threadTree, "weak");
						
						// Set the elapsed time of the master core to the longest elapsed time of its slave cores.
						tools::Scheduler::resolveJoin(cores, threadTree.thread->getCoreId(), threadTree.childThreads.first, threadTree.thread->getId());

						// Clear par(...) id.
						threadTree.childThreads.first = "";
						
						if (result == Reaction::branch) {
							// Allow alternate reactions to be traversed.
							return Reaction::branch;
						}
					} else {
						// par(...) has reacted.
						
						// If not resuming after an alternate reaction (branch or weak abort).
						if (!(this->state.execution == Reaction::branch || (this->state.execution == Reaction::branch && threadTree.aborts.checked["weak"] == true))) {
							// Check for weak abort conditions.
							const enum Reaction::Execution result = Reaction::abortPar(traces, threadTree, "weak");
							
							// Set the allocated cores to the maximum elapsed times.
							tools::Scheduler::reactionEnd(cores, threadTree.thread->getCoreId(), threadTree.childThreads.first, threadTree.thread->getId());
								
							if (result == Reaction::branch) {
								// Allow alternate reactions to be traversed.
								return Reaction::branch;
							}
						}
					}
				}
			} while (hasForked || hasJoined);
		
			return Reaction::reacted;
		}
		
		void Reaction::takeTransition(std::pair<forec::cfg::Node *, std::pair<int, bool> > &nextProgramCounter, Threading &thread) {
			// Update the thread's program counter.
			thread.advanceProgramCounter(*nextProgramCounter.first);

			// Add the latency of the transition.
			cores[thread.getCoreId()]->incrementElapsedTime(nextProgramCounter.second.first);

			// Add any memory latency.
			cores[thread.getCoreId()]->incrementElapsedTime(Reaction::getMemoryCost(nextProgramCounter, thread, cores));
		}

		Reaction *Reaction::takeAlternateTransition(Reaction &originalReaction, std::pair<forec::cfg::Node *, std::pair<int, bool> > &nextProgramCounter, Threading &thread) {
			// Prepare to take the alternate edge.
			thread.addAlternateProgramCounter(*nextProgramCounter.first);

			// Create a new reaction.
			Reaction *alternateReaction = new Reaction(originalReaction, true, false);
			thread.clearAlternateProgramCounter();
			
			// Add the latency of the transition.
			alternateReaction->cores[thread.getCoreId()]->incrementElapsedTime(nextProgramCounter.second.first);
			
			// Add any memory latency.
			alternateReaction->cores[thread.getCoreId()]->incrementElapsedTime(Reaction::getMemoryCost(nextProgramCounter, thread, alternateReaction->cores));
			
			return alternateReaction;
		}
		
		const enum Reaction::Execution Reaction::abortPar(std::vector<Reaction *> &traces, struct Reaction::ThreadTree &threadTree, const std::string &variant) {
			std::vector<std::string> aborts = tools::Threading::getAborts(threadTree.childThreads.first, variant);
			if (!aborts.empty() && !threadTree.aborts.checked[variant]) {
				threadTree.aborts.checked[variant] = true;
			
				this->threadWithAlternative = threadTree.thread;
				this->state.execution = Reaction::branch;
				threadTree.thread->setState(tools::Threading::branch);
				
				// Create alternate reactions and add abort checking costs.
				int index = 0;
				for (std::vector<std::string>::const_iterator abort = aborts.begin(); abort != aborts.end(); ++abort) {
					// Prepare to take one of the aborts.
					threadTree.thread->addAlternateProgramCounter(*tools::Link::getAbortScopeEndNode(*abort));
					
					// Create a new reaction. Aborted child threads are not copied.
					Reaction *alternateReaction = new Reaction(*this, true, true);
					threadTree.thread->clearAlternateProgramCounter();
					
					// Increment the cores' elapsed time.
					tools::Scheduler::resolveAbortTaken(alternateReaction->cores, threadTree.childThreads.first, index, variant);
					tools::Scheduler::resolveJoin(alternateReaction->cores, threadTree.thread->getCoreId(), threadTree.childThreads.first, threadTree.thread->getId());
					traces.push_back(alternateReaction);

					index++;
				}

				this->clearThreadWithAlternative();

				// Add abort checking costs for the original reaction.
				tools::Scheduler::resolveAbortsNotTaken(this->cores, threadTree.childThreads.first, aborts.size(), variant);
			}
		
			return this->state.execution;
		}
		
		const int Reaction::getMemoryCost(std::pair<forec::cfg::Node *, std::pair<int, bool> > &nextProgramCounter, Threading &thread, std::map<std::string, tools::Multicore *> &cores) {
			if (nextProgramCounter.first->isType("AssemblyLine")) {
				forec::cfg::AssemblyLine *assemblyLine = (forec::cfg::AssemblyLine *)nextProgramCounter.first;
				
				if (global::mergeGlobalAccesses) {
					// Global and local memory access costs have been computed.
					return 0;
				} else {
					if (!global::merge || assemblyLine->getHasGlobalMemoryAccess()) {
						// Global or local memory access costs have not been computed.
						return assemblyLine->getMemoryLatency(cores[thread.getCoreId()]->getElapsedTime(), false);
					} else {
						// Only local memory access cost has been computed.
						return 0;
					}
				}
			}
			
			return 0;
		}
		
		void Reaction::checkIterationBound(forec::cfg::Node &currentProgramCounter, std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > > &nextProgramCounters, Threading &thread) {
			if (currentProgramCounter.hasIterationBound()) {
				forec::cfg::IterationBound *iterationBound = (forec::cfg::IterationBound *)(currentProgramCounter.getIterationBound());
				
				if (iterationCounts.find(iterationBound) == iterationCounts.end()) {
					// First iteration.
					iterationCounts[iterationBound] = 0;
				} else {
					iterationCounts[iterationBound]++;
				}

				if (iterationCounts[iterationBound] == iterationBound->getUpperBound()) {
					// Bound has been reached. Take the exit path.
					nextProgramCounters = iterationBound->getNextNodes();

					// Remove the iteration count.
					iterationCounts.erase(iterationBound);
				} else if (iterationCounts[iterationBound] < iterationBound->getLowerBound()) {
					// Do not explore exit path by removing the exit path.
					for (std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > >::iterator node = nextProgramCounters.begin(); node != nextProgramCounters.end(); ++node) {
						if (node->first == iterationBound) {
							nextProgramCounters.erase(node);
							break;
						}
					}
					
					if (global::mergeGlobalAccesses) {
						// Add a global memory access alignment cost because the loop resumes from a different alignment to the first iteration.
						cores[thread.getCoreId()]->incrementElapsedTime(tools::Costing::getMaxAccessLatency(true, 'l'));
					}
				}
			}
		}
		
		const bool Reaction::pauseStatement(Threading &thread, forec::cfg::Node &currentProgramCounter) {
			if (currentProgramCounter.isType("PauseStatement") && thread.getProgramCounters()->size() > 1) {
				// Not at the start of a reaction.
				thread.setState(tools::Threading::reacted);

				cores[thread.getCoreId()]->addEvent(thread.getId() + " Paused");
				cores[thread.getCoreId()]->addEvent("Context switch");

				// Set core elapsed times to be at least as long as the master core's.
				// If the thread does not contain a par(...) then this should have no effect.
				tools::Scheduler::resolveParAbsent(cores, thread.getCoreId(), thread.getId());
				
				return true;
			}
			
			return false;
		}
		
		const bool Reaction::parStatement(struct Reaction::ThreadTree &threadTree, forec::cfg::Node &currentProgramCounter) {
			if (currentProgramCounter.isType("ParStatement") && !threadTree.justJoined) {
				const std::string parId = ((forec::cfg::ParStatement *)&currentProgramCounter)->getId();
				const std::vector<std::string> threadIds = tools::Threading::getThreadIds(parId);

				threadTree.justForked = true;
				threadTree.justJoined = false;
				threadTree.aborts.checked["strong"] = false;
				threadTree.aborts.checked["weak"] = false;

				// Add child threads
				threadTree.childThreads.first = parId;	
				for (std::vector<std::string>::const_iterator threadId = threadIds.begin(); threadId != threadIds.end(); ++threadId) {
					struct Reaction::ThreadTree newChildThreadTree;
					newChildThreadTree.thread = new Threading(*threadId);
					newChildThreadTree.justForked = false;
					newChildThreadTree.justJoined = false;
					newChildThreadTree.aborts.checked["strong"] = false;
					newChildThreadTree.aborts.checked["weak"] = false;
					threadTree.childThreads.second.push_back(newChildThreadTree);	
				}

				if (threadTree.thread->getId().compare("main") != 0) {
					cores[threadTree.thread->getCoreId()]->addEvent(threadTree.thread->getId() + " Par" + parId + " statement");
					cores[threadTree.thread->getCoreId()]->addEvent("Context switch");
				}
			
				// Add parent thread to the history of removed threads.
				threadsRemoved.push_back(threadTree.thread);

				// Set core elapsed times to be at least as long as the master core's.
				Threading::resetThreadStates(parId, tools::Threading::reacting);
				tools::Scheduler::resolveParPresent(cores, threadTree.thread->getCoreId(), threadTree.thread->getId(), parId);
				
				return true;
			}
			
			// No longer at a par(...).
			threadTree.justJoined = false;
			return false;
		}

		const bool Reaction::threadRemove(Threading &thread, forec::cfg::Node &currentProgramCounter) {
			if (currentProgramCounter.isType("Scheduler") && currentProgramCounter.isVariant("threadRemove")) {
				// Terminate the current thread.
				thread.setState(tools::Threading::terminated);

				if (thread.getId().compare("main") != 0) {
					Threading::setThreadState(thread.getCoreId(), thread.getId(), tools::Threading::terminated);
				}
				tools::Scheduler::resolveThreadTerminate(cores, thread.getCoreId(), thread.getId());

				return true;
			}

			return false;
		}

		void Reaction::iterationEnd(Threading &thread, forec::cfg::Node &currentProgramCounter) {
			if (currentProgramCounter.isType("Scheduler") && currentProgramCounter.isVariant("iterationEnd")) {
				// Parent thread reaches the end of an iteration.
				// Set all cores to the maximum elapsed times.
				tools::Scheduler::iterationEnd(cores, thread.getCoreId(), thread.getId());
			}

			if (global::mergeGlobalAccesses) {
				// Add a global memory access alignment cost because the loop resumes from a different alignment to the first iteration.
				cores[thread.getCoreId()]->incrementElapsedTime(tools::Costing::getMaxAccessLatency(true, 'l'));
			}
		}
		
		const std::string Reaction::getExecutionTrace(const std::string &indent) const {
			std::ostringstream output;
			for (std::map<std::string, tools::Multicore *>::const_iterator core = cores.begin(); core != cores.end(); ++core) {
				output << core->second->getExecutionTrace(indent) << std::endl;
			}
		
			return output.str();
		}

		const std::string Reaction::toString(void) const {
			std::ostringstream output;

			output << "Reaction " << getId() << '.' << getSubId() << ": " << getStateId() << std::endl;

			for (std::vector<Threading *>::const_iterator thread = threadsRemoved.begin(); thread != threadsRemoved.end(); ++thread) {
				output << "\tHistory level: " << (thread - threadsRemoved.end()) << std::endl;
				output << (*thread)->toString();
			}

			output << "\tHistory level: 0" << std::endl;
			output << Reaction::childThreadsToString(threadTree);

			if (!cores.empty()) {
				output << std::endl;
				for (std::map<std::string, tools::Multicore *>::const_iterator core = cores.begin(); core != cores.end(); ++core) {
					output << core->second->toString("\t");
				}
			}
		
			return output.str();
		}
	
		const std::string Reaction::childThreadsToString(const struct Reaction::ThreadTree &threadTree) const {
			std::ostringstream output;
		
			if (threadTree.childThreads.second.empty()) {
				output << threadTree.thread->toString();
			} else {
				for (std::vector<struct Reaction::ThreadTree>::const_iterator childThread = threadTree.childThreads.second.begin(); childThread != threadTree.childThreads.second.end(); ++childThread) {
					output << Reaction::childThreadsToString(*childThread);
				}
			}
		
			return output.str();
		}

		const std::string Reaction::toXml(void) {
			std::ostringstream output;

			output << "\t\t<trace id=\"" << getSubId() << "\" state=\"" << getStateId() << "\">" << std::endl;

			for (std::vector<Threading *>::const_iterator thread = threadsRemoved.begin(); thread != threadsRemoved.end(); ++thread) {
				output << "\t\t\tHistory level: " << (thread - threadsRemoved.end()) << std::endl;
				output << (*thread)->toString("\t\t");
			}

			output << "\t\t\tHistory level: 0" << std::endl;
			output << Reaction::childThreadsToXml(threadTree);

			if (!cores.empty()) {
				output << std::endl;
				for (std::map<std::string, tools::Multicore *>::const_iterator core = cores.begin(); core != cores.end(); ++core) {
					output << core->second->toString("\t\t\t");
				}
			}
		
			output << std::endl;
			output << getExecutionTrace("\t\t\t") << std::endl;

			output << "\t\t</trace>";
		
			return output.str();
		}
	
		const std::string Reaction::childThreadsToXml(const struct ThreadTree &threadTree) {
			std::ostringstream output;
		
			if (threadTree.childThreads.second.empty()) {
				output << threadTree.thread->toString("\t\t");
			} else {
				for (std::vector<struct Reaction::ThreadTree>::const_iterator childThread = threadTree.childThreads.second.begin(); childThread != threadTree.childThreads.second.end(); ++childThread) {
					output << Reaction::childThreadsToXml(*childThread);
				}
			}
		
			return output.str();
		}
			
	}
}

