#ifndef FOREC_REACHABILITY_REACTION_HPP
#define FOREC_REACHABILITY_REACTION_HPP
/*
 *  Reaction.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 21/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <set>
#include <map>
#include <vector>
#include <string>
#include <sstream>

namespace forec {
	namespace cfg {
		class IterationBound;
		class Node;
	}
}

namespace tools {
	class Multicore;
	class Threading;
}

namespace forec {
	namespace reachability {
		class Threading;
	}
}

namespace forec {
	namespace reachability {
		class Reaction {
	
			// Static
			public:
				static void incrementGlobalCount(void);
				static const int getGlobalCount(void);

				static void incrementGlobalSubCount(void);
				static const int getGlobalSubCount(void);
	
			
			private:
				static int globalCount;
				static int globalSubCount;

			// Dynamic
			public:
				enum Execution {
					reacting = 0,
					reacted,
					terminated,
				
					branch,			// Branch state only valid when reaching to the next reacting, reacted or terminated state.
				};

				struct ThreadTree {
					Threading *thread;
					
					// For the current reaction.
					bool justForked;
					bool justJoined;
				
					struct Aborts {
						std::map<std::string, bool> checked;
					} aborts;
				
					// pair<parId, vector<thread> >
					std::pair<std::string, std::vector<struct ThreadTree> > childThreads;
				};

				Reaction(const std::string &threadId);
				Reaction(Reaction &reaction, const bool isAlternate, const bool isAbortPar);
			
				const int getId(void) const;
				const int getSubId(void) const;
				const enum Execution getOverallState(void) const;
				const enum Execution getState(void);
				const enum Execution getState(const struct ThreadTree &threadTree);
				const std::string getStateId(void) const;
				const bool isIterating(void) const;
			
				void clearThreadWithAlternative(void);
				Threading *getThreadWithAlternative(void);

				const unsigned int getReactionTime(void) const;
			
				const enum Execution react(std::vector<Reaction *> &traces);
				const enum Execution react(std::vector<Reaction *> &traces, struct ThreadTree &threadTree);
			
				const std::string getExecutionTrace(const std::string &indent) const;

				const std::string toString(void) const;
				const std::string childThreadsToString(const struct ThreadTree &threadTree) const;

				const std::string toXml(void);
				const std::string childThreadsToXml(const struct ThreadTree &threadTree);


			private:
				struct ThreadTree threadTree;
			
				struct State {
					int id;
					int subId;
					std::ostringstream stringId;
					enum Execution execution;
				};
			
				struct State state;
			
				Threading *threadWithAlternative;
			
				// map<coreId, coreInformation>
				std::map<std::string, tools::Multicore *> cores;

				// vector<thread>
				std::vector<Threading *> threadsRemoved;
			
				// map<iterationBound, iterationCount>
				std::map<forec::cfg::IterationBound *, int> iterationCounts;
			
				void copyThreadTree(struct ThreadTree &threadTree, struct ThreadTree &threadTreeCopy, Threading &threadWithAlternative, const bool isAlternate, const bool isAbortPar);
			
				void takeTransition(std::pair<forec::cfg::Node *, std::pair<int, bool> > &nextProgramCounter, Threading &thread);
				Reaction *takeAlternateTransition(Reaction &originalReaction, std::pair<forec::cfg::Node *, std::pair<int, bool> > &nextProgramCounter, Threading &thread);
				const int getMemoryCost(std::pair<forec::cfg::Node *, std::pair<int, bool> > &nextProgramCounter, Threading &thread, std::map<std::string, tools::Multicore *> &cores);
				
				void checkIterationBound(forec::cfg::Node &currentProgramCounter, std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > > &nextProgramCounters, Threading &thread);
				const enum Execution abortPar(std::vector<Reaction *> &traces, struct ThreadTree &threadTree, const std::string &variant);
				const bool pauseStatement(Threading &thread, forec::cfg::Node &currentProgramCounter);
				const bool parStatement(struct ThreadTree &threadTree, forec::cfg::Node &currentProgramCounter);
				const bool threadRemove(Threading &thread, forec::cfg::Node &currentProgramCounter);
				void iterationEnd(Threading &thread, forec::cfg::Node &currentProgramCounter);
				
		};
	}
}

#endif // FOREC_REACHABILITY_REACTION_HPP

