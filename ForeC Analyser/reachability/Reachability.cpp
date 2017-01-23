/*
 *  Reachability.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 21/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Reachability.hpp"

#include "Reaction.hpp"

#include "../cfg/Node.hpp"

#include "../tools/Threading.hpp"

#include <iostream>
#include <sstream>

namespace global {
	extern int traceLevel;
}

namespace forec {
	namespace reachability {
		int Reachability::progressCounter;
		unsigned int Reachability::reactionsSeenCount;
		std::ofstream Reachability::outFile;
		std::vector<std::vector<Reaction *> > Reachability::trace;
		std::set<std::string> Reachability::visitedReactions;
		Reaction *Reachability::maximumReaction;
	
		void Reachability::clear(void) {
			Reachability::progressCounter = 0;
			Reachability::reactionsSeenCount = 0;
			Reachability::trace.clear();
			Reachability::visitedReactions.clear();
			Reachability::maximumReaction = NULL;
		}

		void Reachability::openOutFile(const std::string &fileName) {
			Reachability::outFile.open(fileName.c_str());
			Reachability::outFile << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>" << std::endl;
			Reachability::outFile << "<program>" << std::endl;
		}

		void Reachability::closeOutFile(void) {
			Reachability::outFile << "</program>" << std::endl;
			Reachability::outFile.close();
		}
		
		void Reachability::setStartingReaction(const std::string &threadId) {
			Reaction *startingReaction = new Reaction(threadId);
			std::vector<Reaction *> startingReactionSet;
			startingReactionSet.push_back(startingReaction);
			
			Reachability::trace.push_back(startingReactionSet);
			Reachability::visitedReactions.insert(startingReaction->getStateId());
			
			maximumReaction = startingReaction;
		}
		
		Reaction *Reachability::getStartingReaction(void) {
			std::vector<Reaction *> startingReactionSet = Reachability::trace.front();
			if (startingReactionSet.size() != 1) {
				throw std::string("reachability::Reachability::getStartingReaction: More than one starting reaction found.");
			}
			return startingReactionSet.front();
		}

		std::vector<Reaction *> Reachability::getCurrentReactions(void) {
			return Reachability::trace.back();
		}

		std::vector<Reaction *> Reachability::getActiveReactions(std::vector<Reaction *> reactions) {
			std::vector<Reaction *> activeReactions;

			for (std::vector<Reaction *>::iterator reaction = reactions.begin(); reaction != reactions.end(); ++reaction) {
				if ((*reaction)->getOverallState() != Reaction::terminated) {
					activeReactions.push_back(*reaction);
				}
			}

			return activeReactions;
		}

		std::vector<Reaction *> Reachability::getCurrentActiveReactions(void) {
			return Reachability::getActiveReactions(Reachability::getCurrentReactions());
		}
		
		const Reaction *Reachability::compute(void) {
			Reachability::reactionsSeenCount = 0;
			std::vector<Reaction *> currentActiveReactions = Reachability::getCurrentActiveReactions();

			// Continue to evolve the reactions while at least one reaction is active.
			while (!currentActiveReactions.empty()) {

				// Repeat while reactions have not paused or terminated.
				std::vector<Reaction *> finishedReactions;
				do {
					// Let the reaction evolve.
					// When a branch (or abort) occurs, an alternate reaction is appended to currentActiveReactions.
					enum Reaction::Execution reactionState = currentActiveReactions.front()->react(currentActiveReactions);

					if (reactionState == Reaction::reacted || reactionState == Reaction::terminated) {
						if (global::traceLevel == 1 || global::traceLevel == 3) {
							std::cout << currentActiveReactions.front()->toString() << std::endl;
						}
						
						// Remove the reaction.
						finishedReactions.push_back(currentActiveReactions.front());
						currentActiveReactions.erase(currentActiveReactions.begin());
					} else if (reactionState != Reaction::branch) {
						std::ostringstream error;
						error << "Reachability::compute: Invalid reaction state encountered:" << std::endl << currentActiveReactions.front()->toString();
						throw error.str();
					}

					if (Reachability::progressCounter++ > 499) {
						Reachability::progressCounter = 0;
						std::cout << '.';
						std::flush(std::cout);
					}
				} while (!currentActiveReactions.empty());

				// One evolution of each reaction completed.
				std::cout << '|';
				std::flush(std::cout);

						
				// Update the maximum reaction encountered.
				for (std::vector<Reaction *>::const_iterator finishedReaction = finishedReactions.begin(); finishedReaction != finishedReactions.end(); ++finishedReaction) {
					if (Reachability::maximumReaction->getReactionTime() < (*finishedReaction)->getReactionTime()) {
						Reachability::maximumReaction = *finishedReaction;
					}
				}

				if (global::traceLevel == 2 || global::traceLevel == 3) {
					Reachability::toXml(finishedReactions);
				}

				Reaction::incrementGlobalCount();
				Reachability::reactionsSeenCount += finishedReactions.size();
											
				// Create the next set of reactions to evolve.
				Reachability::trace.back() = finishedReactions;
				std::vector<Reaction *> nextActiveReactions = Reachability::getCurrentActiveReactions();
				std::vector<Reaction *> nextActiveReactionsCopy;
				for (std::vector<Reaction *>::iterator nextActiveReaction = nextActiveReactions.begin(); nextActiveReaction != nextActiveReactions.end(); ++nextActiveReaction) {
					Reaction *nextActiveReactionCopy = new Reaction(*(*nextActiveReaction), false, false);

					if (Reachability::visitedReactions.find(nextActiveReactionCopy->getStateId()) != Reachability::visitedReactions.end() && !nextActiveReactionCopy->isIterating()) {
						delete nextActiveReactionCopy;
					} else {
						nextActiveReactionsCopy.push_back(nextActiveReactionCopy);
						Reachability::visitedReactions.insert(nextActiveReactionCopy->getStateId());
					}
				}

				Reachability::trace.push_back(nextActiveReactionsCopy);
				currentActiveReactions = Reachability::getCurrentActiveReactions();
			}

			// All possible evolutions completed.
			return Reachability::maximumReaction;
		}

		Reaction *Reachability::getMaximumReaction(void) {
			return Reachability::maximumReaction;
		}

		const unsigned int Reachability::getMaximumReactionTime(void) {
			return Reachability::maximumReaction->getReactionTime();
		}
		
		const unsigned int Reachability::getReactionsSeenCount(void) {
			return Reachability::reactionsSeenCount;
		}

		void Reachability::toXml(std::vector<Reaction *> &reactionResults) {
			Reachability::outFile << "\t<reaction id=\"" << Reaction::getGlobalCount() << "\">" << std::endl;
			
			for (std::vector<Reaction *>::const_iterator reactionResult = reactionResults.begin(); reactionResult != reactionResults.end(); ++reactionResult) {
				Reachability::outFile << (*reactionResult)->toXml() << std::endl;
			}

			Reachability::outFile << "\t</reaction>" << std::endl;
		}
		
	}
}

