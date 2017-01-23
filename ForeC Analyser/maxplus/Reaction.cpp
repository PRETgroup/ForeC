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
#include "../tools/Function.hpp"
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
#include "../cfg/Start.hpp"

namespace global {
	extern bool merge;
	extern bool mergeSequential;
	extern bool mergeGlobalAccesses;
}

namespace forec {
	namespace maxplus {
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
		
		// Dynamic
		Reaction::Reaction(const std::string &threadId) {
			this->state.id = globalCount;
			this->state.subId = globalSubCount;
	
			thread = new Threading(threadId);

			state.stringId << std::hex << thread->getCurrentAddress() << '_';
			state.execution = Reaction::reacting;
			threadWithAlternative = NULL;
			core = new tools::Multicore("-1", tools::Costing::getBusCycle());
			core->addEvent("Reaction Start");
			iterationCounts.clear();
		}

		// Copy constructor
		Reaction::Reaction(Reaction &reaction, const bool isAlternate) {
			this->state.id = globalCount;
			this->threadWithAlternative = NULL;
			
			thread = new Threading(*reaction.thread, isAlternate);
		
			if (isAlternate) {
				// Alternate reaction for a branch
				Reaction::incrementGlobalSubCount();
				this->state.subId = Reaction::getGlobalSubCount();
				this->state.stringId << reaction.getStateId();
				this->state.execution = reaction.getState();
				this->core = new tools::Multicore(*reaction.core);
			} else {
				// New evolution of a reaction
				this->state.subId = reaction.state.subId;
				this->state.stringId << std::hex << thread->getCurrentAddress() << '_';
				this->state.execution = Reaction::reacting;
				this->core = new tools::Multicore("-1", reaction.core->getNextStartingElapsedTime() + tools::Costing::getBusCycle());
				this->core->addEvent("Reaction Start");
			}

			iterationCounts.clear();
			for (std::map<forec::cfg::IterationBound *, int>::const_iterator bound = reaction.iterationCounts.begin(); bound != reaction.iterationCounts.end(); ++bound) {
				iterationCounts[bound->first] = bound->second;
			}
		}

		const int Reaction::getId(void) const {
			return this->state.id;
		}

		const int Reaction::getSubId(void) const {
			return this->state.subId;
		}

		const enum Reaction::Execution Reaction::getState(void) {
			return this->state.execution;
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
			return this->core->getElapsedTime();
		}

		const enum Reaction::Execution Reaction::react(std::vector<Reaction *> &traces) {
			// While the thread has not reached the reacted or terminated state.
			while (thread->getState() != tools::Threading::reacted && thread->getState() != tools::Threading::terminated) {
				core->addEvent(thread->getId());
		
				// Branching thread reached again (resume the traversal).
				this->state.execution = Reaction::reacting;
			
				// Get the current program counter.
				forec::cfg::Node *currentProgramCounter = thread->getCurrentProgramCounter();
				
				//-----------------------------------------------------------------------------------						
				// If the current node is a pause, then pause the thread. Ignore if this is a new reaction.
				if (Reaction::pauseStatement(*thread, *currentProgramCounter)) {
					this->state.execution = Reaction::reacted;
					return this->state.execution;
				}
				
				// If the current node is the last node of the thread (thread termination).
				if (Reaction::threadRemove(*thread, *currentProgramCounter)) {
					this->state.execution = Reaction::terminated;
					return this->state.execution;
				}
				
				// Check if an iteration end is encountered.
				Reaction::iterationEnd(*thread, *currentProgramCounter);
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
					Reaction::checkIterationBound(*currentProgramCounter, nextProgramCounters, *thread);
					
					if (nextProgramCounters.size() > 1) {
						this->threadWithAlternative = thread;
						this->state.execution = Reaction::branch;
						thread->setState(tools::Threading::branch);
						
						for (std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > >::iterator nextProgramCounter = nextProgramCounters.begin() + 1; nextProgramCounter != nextProgramCounters.end(); ++nextProgramCounter) {
							// Take alternate transition.
							traces.push_back(Reaction::takeAlternateTransition(*this, *nextProgramCounter, *thread));
						}
						
						this->clearThreadWithAlternative();
					}
					
					// Take the first transition.
					Reaction::takeTransition(nextProgramCounters.front(), *thread);
					
					if (nextProgramCounters.size() > 1) {
						this->state.execution = Reaction::branch;
						return this->state.execution;
					} else {
						thread->setState(tools::Threading::reacting);
					}
				}
			}
		
			this->state.execution = Reaction::reacted;
			return this->state.execution;
		}
		
		void Reaction::takeTransition(std::pair<forec::cfg::Node *, std::pair<int, bool> > &nextProgramCounter, Threading &thread) {
			// Update the thread's program counter.
			thread.advanceProgramCounter(*nextProgramCounter.first);
			
			// Add the latency of the transition.
			core->incrementElapsedTime(nextProgramCounter.second.first);
			
			// Add any memory latency.
			core->incrementElapsedTime(Reaction::getMemoryCost(nextProgramCounter, thread, *core));
		}

		Reaction *Reaction::takeAlternateTransition(Reaction &originalReaction, std::pair<forec::cfg::Node *, std::pair<int, bool> > &nextProgramCounter, Threading &thread) {
			// Prepare to take the alternate edge.
			thread.addAlternateProgramCounter(*nextProgramCounter.first);

			// Create a new reaction.
			Reaction *alternateReaction = new Reaction(originalReaction, true);
			thread.clearAlternateProgramCounter();
			
			// Add the latency of the transition.
			alternateReaction->core->incrementElapsedTime(nextProgramCounter.second.first);
			
			// Add any memory latency.
			alternateReaction->core->incrementElapsedTime(Reaction::getMemoryCost(nextProgramCounter, thread, *alternateReaction->core));
			
			return alternateReaction;
		}
		
		const int Reaction::getMemoryCost(std::pair<forec::cfg::Node *, std::pair<int, bool> > &nextProgramCounter, Threading &thread, tools::Multicore &core) {
			if (nextProgramCounter.first->isType("AssemblyLine")) {
				forec::cfg::AssemblyLine *assemblyLine = (forec::cfg::AssemblyLine *)nextProgramCounter.first;
				
				if (global::mergeGlobalAccesses) {
					// Global and local memory access costs have been computed.
					return 0;
				} else {
					if (!global::merge || assemblyLine->getHasGlobalMemoryAccess()) {
						// Global or local memory access costs have not been computed.
						return assemblyLine->getMemoryLatency(core.getElapsedTime(), false);
					} else {
						// Only local memory access cost already computed.
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
						core->incrementElapsedTime(tools::Costing::getMaxAccessLatency(true, 'l'));
					}
				}
			}
		}
		
		const bool Reaction::pauseStatement(Threading &thread, forec::cfg::Node &currentProgramCounter) {
			if (currentProgramCounter.isType("PauseStatement") && thread.getProgramCounters()->size() > 1) {
				// Not at the start of a reaction.
				thread.setState(tools::Threading::reacted);

				core->addEvent(thread.getId() + " Paused");
				core->addEvent("Context switch");
				
				return true;
			}
			
			return false;
		}

		const bool Reaction::threadRemove(Threading &thread, forec::cfg::Node &currentProgramCounter) {
			if (currentProgramCounter.isType("Scheduler") && currentProgramCounter.isVariant("threadRemove")) {
				// Terminate the current thread.
				thread.setState(tools::Threading::terminated);
				tools::Scheduler::staticLatency("resolveThreadTerminate", *core, thread.getCoreId(), thread.getId(), "", "", -1, "", -1);
				return true;
			}

			return false;
		}

		void Reaction::iterationEnd(Threading &thread, forec::cfg::Node &currentProgramCounter) {
			if (currentProgramCounter.isType("Scheduler") && currentProgramCounter.isVariant("iterationEnd")) {
				// Parent thread reaches the end of an iteration.
				// Set all cores to the maximum elapsed times.
				tools::Scheduler::staticLatency("iterationEnd", *core, thread.getCoreId(), thread.getId(), "", "", -1, "", -1);
			}

			if (global::mergeGlobalAccesses) {
				// Add a global memory access alignment cost because the loop resumes from a different alignment to the first iteration.
				core->incrementElapsedTime(tools::Costing::getMaxAccessLatency(true, 'l'));
			}
		}

		const std::string Reaction::toString(void) const {
			std::ostringstream output;

			output << "Reaction " << getId() << '.' << getSubId() << ": " << getStateId() << std::endl;

			thread->toString();
			core->toString("\t");
		
			return output.str();
		}	
	}
}

