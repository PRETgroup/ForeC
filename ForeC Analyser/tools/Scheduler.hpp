#ifndef TOOLS_SCHEDULER_HPP
#define TOOLS_SCHEDULER_HPP
/*
 *  Scheduler.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 20/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <string>
#include <vector>
#include <map>
#include <set>

namespace tools {
	class Multicore;
}

namespace tools {
	class Scheduler {
		public:
			static void clear(void);
			
			static const unsigned int staticLatency(const std::string &type, const std::string &masterCoreId, const std::string &threadId, const std::string &parId, const std::string &threadScope, const int numberOfChecks, const std::string &variant, const int index);
			static void staticLatency(const std::string &type, Multicore &core, const std::string &masterCoreId, const std::string &threadId, const std::string &parId, const std::string &threadScope, const int numberOfChecks, const std::string &variant, const int index);
			
			static void resolveParAbsent(std::map<std::string, Multicore *> &cores, const std::string &masterCoreId, const std::string &threadId);
			static void resolveParPresent(std::map<std::string, Multicore *> &cores, const std::string &masterCoreId, const std::string &threadId, const std::string &parId);
			
			static void resolveThreadTerminate(std::map<std::string, Multicore *> &cores, const std::string &masterCoreId, const std::string &threadId);
			
			static void reactionStart(std::map<std::string, Multicore *> &cores, const std::string &parId);
			static void reactionEnd(std::map<std::string, Multicore *> &cores, const std::string &masterCoreId, const std::string &parId, const std::string &threadScope);
			static void resolveJoin(std::map<std::string, Multicore *> &cores, const std::string &masterCoreId, const std::string &parId, const std::string &threadScope);
			
			static void iterationEnd(std::map<std::string, Multicore *> &cores, const std::string &masterCoreId, const std::string &threadId);
			
			static void resolveAbortsNotTaken(std::map<std::string, Multicore *> &cores, const std::string &parId, const int numberOfChecks, const std::string &variant);
			static void resolveAbortTaken(std::map<std::string, Multicore *> &cores, const std::string &parId, const int index, const std::string &variant);
			
			static const std::string toString(void);
			
			
		private:
			static void addCost(Multicore &core, const std::string &costs, const int repetition = 1);
			static void addCost(unsigned int &core, const std::string &costs, const int repetition = 1);
			static void combineCost(Multicore &masterCore, const std::string &threadScope, const std::string &parId);
			static const unsigned int getMaxElapsedTime(std::map<std::string, Multicore *> &cores, std::set<std::string> coreIds);

			
	};

}

#endif // TOOLS_SCHEDULER_HPP
