#ifndef TOOLS_OBJECT_DUMP_HPP
#define TOOLS_OBJECT_DUMP_HPP
/*
 *  ObjectDump.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 14/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <string>

namespace tools {
	class ObjectDump {
		public:
			static void make(const std::string &sourceName, const std::string &expandedName, const std::string &elfName, const std::string &dumpName);
			static void makeMicroBlaze(const std::string &sourceName, const std::string &expandedName, const std::string &elfName, const std::string &dumpName);
			static void makePtarm(const std::string &sourceName, const std::string &expandedName, const std::string &elfName, const std::string &dumpName);
			
	};

}

#endif // TOOLS_OBJECT_DUMP_HPP
