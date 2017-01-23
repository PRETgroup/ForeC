#ifndef FOREC_MAXPLUS_REACTION_HPP
#define FOREC_MAXPLUS_REACTION_HPP
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
	namespace maxplus {
		class Threading;
	}
}

namespace forec {
	namespace maxplus {
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
				
				Reaction(const std::string &threadId);
				Reaction(Reaction &reaction, const bool isAlternate);
			
				const int getId(void) const;
				const int getSubId(void) const;
				const enum Execution getState(void);
				const std::string getStateId(void) const;
				const bool isIterating(void) const;
			
				void clearThreadWithAlternative(void);
				Threading *getThreadWithAlternative(void);

				const unsigned int getReactionTime(void) const;
			
				const enum Execution react(std::vector<Reaction *> &traces);
				
				const std::string toString(void) const;

			private:
				struct State {
					int id;
					int subId;
					std::ostringstream stringId;
					enum Execution execution;
				};
			
				struct State state;
				Threading *thread;
				Threading *threadWithAlternative;
			
				// map<coreId, coreInformation>
				tools::Multicore *core;
			
				// map<iterationBound, iterationCount>
				std::map<forec::cfg::IterationBound *, int> iterationCounts;
			
				void takeTransition(std::pair<forec::cfg::Node *, std::pair<int, bool> > &nextProgramCounter, Threading &thread);
				Reaction *takeAlternateTransition(Reaction &originalReaction, std::pair<forec::cfg::Node *, std::pair<int, bool> > &nextProgramCounter, Threading &thread);
				const int getMemoryCost(std::pair<forec::cfg::Node *, std::pair<int, bool> > &nextProgramCounter, Threading &thread, tools::Multicore &core);
				
				void checkIterationBound(forec::cfg::Node &currentProgramCounter, std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > > &nextProgramCounters, Threading &thread);
				const bool pauseStatement(Threading &thread, forec::cfg::Node &currentProgramCounter);
				const bool threadRemove(Threading &thread, forec::cfg::Node &currentProgramCounter);
				void iterationEnd(Threading &thread, forec::cfg::Node &currentProgramCounter);
				
		};
	}
}

#endif // FOREC_MAXPLUS_REACTION_HPP

