#ifndef TOOLS_MUTEX_HPP
#define TOOLS_MUTEX_HPP
/*
 *  Tab.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <sstream>
#include <string>
#include <map>
#include <set>
#include <bitset>
#include <limits>

namespace tools {
	class Mutex {
		public:
			static void clear(void);
			
			static void setParCoresMask(std::map<std::string, std::map<std::string, int> > &parCoresPriority);
			
			static const std::map<std::string, unsigned int> getInformation(const std::string &threadScope);
			static const unsigned int getCoreCount(const std::string &threadScope);
			static const unsigned int getOffset(const std::string &threadScope);
			static const unsigned int getBaseMask(const std::string &threadScope);
			static const std::set<std::string> getThreadScopes(void);
			
			static const std::string toString(void);
			
		private:
			static const unsigned int maxCount;
			static unsigned int currentOffset;
			
			// map<threadScope, map<[coreCount, offset, baseMask], value> >
			static std::map<std::string, std::map<std::string, unsigned int> > parCoreInformation;
			
			static const std::string binaryFormat(const unsigned int value);
	};

}

#endif // TOOLS_MUTEX_HPP
