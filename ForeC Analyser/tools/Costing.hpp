#ifndef TOOLS_COSTING_HPP
#define TOOLS_COSTING_HPP
/*
 *  Costing.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <string>
#include <map>

namespace tools {
	class Costing {
		public:
			static void clear(void);

			static void setCoreCount(const int count);
			
			static void readInstructionLatencies(void);
			static const int getInstructionLatency(const std::string &instruction);

			static void readMemoryLatencies(void);
			static const int getMemoryLatency(const char accessType);
			static const int getMaxAccessLatency(const bool isGlobalMemoryAccess, const char accessType);
			static const int getAccessLatency(const bool isGlobalMemoryAccess, const int elapsedTime, const char accessType);
			static const int getBusCycle(void);
			static const bool isGlobalMemoryAccess(const std::string &operand1);
	
			static const std::string toString(void);
			
		private:
			static const std::string instructionFilePath;
			static const std::string memoryFilePath;
			
			static std::map<std::string, int> instructionLatencies;
			static std::map<std::string, int> memoryLatencies;

			static int coreCount;
	};

}

#endif // TOOLS_COSTING_HPP
