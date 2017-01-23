#ifndef FOREC_MAXPLUS_HPP
#define FOREC_MAXPLUS_HPP
/*
 *  MaxPlus.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <map>
#include <set>
#include <vector>
#include <string>

namespace tools {
	class Multicore;
}

namespace forec {
	namespace maxplus {
		class Reaction;
	}
}

namespace forec {
	namespace maxplus {
		class MaxPlus {
		
			public:
				static void clear(void);
				
				static void setMainThreadId(const std::string &mainThreadId);
				static void setThreads(void);
				
				static const std::map<std::string, unsigned int> getReactionsSeenCount(void);
				static Reaction *getMaximumReaction(const std::string &threadId);
				
				static std::vector<Reaction *> getCurrentReactions(const std::string &threadId);
				static std::vector<Reaction *> getActiveReactions(std::vector<Reaction *> reactions);
				static std::vector<Reaction *> getCurrentActiveReactions(const std::string &threadId);
				
				static void computeEachThread(void);
				static const unsigned int compute(const bool withInterleaving);
				static const unsigned int computeWithInterleaving(void);
				static void computeWithInterleaving(const std::string &threadId, std::map<std::string, tools::Multicore *> &cores);
				static void getCopy(std::map<std::string, tools::Multicore *> &cores, std::map<std::string, tools::Multicore *> &coresCopy0, std::map<std::string, tools::Multicore *> &coresCopy1);
				static void setMax(std::map<std::string, tools::Multicore *> &cores, std::map<std::string, tools::Multicore *> &coresCopy1, std::map<std::string, tools::Multicore *> &coresCopy2);
				static const unsigned int computeWithoutInterleaving(void);
				
				static const std::string getExecutionTrace(void);
				
			private:
				static int progressCounter;
				static std::string mainThreadId;
				static std::string executionTrace;
				
				// map<threadId, set<states> >
				static std::map<std::string, std::set<std::string> > visitedReactions;
				
				// map<threadId, count>
				static std::map<std::string, unsigned int> reactionsSeenCount;
				
				// map<threadId, Reaction>
				static std::map<std::string, Reaction *> maximumReaction;
				
				// set<threadId>
				static std::set<std::string> threadIds;
				
				// Each outer element is one evolution.
				// map<threadId, vector<vector<reactions> > >
				static std::map<std::string, std::vector<std::vector<Reaction *> > > trace;
		};
	}
}

#endif // FOREC_MAXPLUS_HPP
