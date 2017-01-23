#ifndef TOOLS_MULTICORE_HPP
#define TOOLS_MULTICORE_HPP
/*
 *  Multicore.hpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <set>

namespace tools {
	class Multicore {
		public:
			static void clear(void);

			static void setAllocations(const std::string &fileName);
			static void setAllocation(const std::string &threadId, const std::string &coreId);
			static void automaticallyAllocate(const std::set<std::string> &threads);
			static const std::map<std::string, std::string> getAllocations(void);

			static const std::string getArchitecture(void);
			static const bool isArchitecture(const std::string &architecture);

			static void setParCorePriority(const std::string &threadScope, const std::string &coreId, const bool isMaster);
			static const std::map<std::string, std::map<std::string, int> > getParCoresPriority(void);
			static const std::map<std::string, int> getParCoresPriority(const std::string &threadScope);
			static const int getParCorePriority(const std::string &threadScope, const std::string &coreId);

			static const std::set<std::string> getAllocatedThreads(void);
			static const std::string getCoreId(const std::string &threadName);
			static const std::string getMasterCoreId(void);
			static const bool isMasterCoreId(const std::string &coreId);
			static const bool isMasterCoreId(const std::string &threadScope, const std::string &coreId);
			static const std::set<std::string> getSlaveCoreIds(void);
			static const std::set<std::string> getCoreIds(void);
			static const std::set<std::string> getCoreIds(const std::vector<std::string> &threads);

			static const std::string toString(void);
			static const std::string toXml(const std::string &indent);


		private:
			static const std::string threadSuffix;
			static std::string architecture;
			static std::string fileName;

			// map<threadId, coreId>
			static std::map<std::string, std::string> allocations;

			// set<coreId>
			static std::set<std::string> coreIds;

			// map<threadScope, map<coreId, priority> >
			static std::map<std::string, std::map<std::string, int> > parCoresPriority;
	};

}

#endif // TOOLS_MULTICORE_HPP
