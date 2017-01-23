#ifndef FOREC_REACHABILITY_THREADING_HPP
#define FOREC_REACHABILITY_THREADING_HPP
/*
 *  Threading.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 29/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>

#include "../tools/Threading.hpp"

namespace forec {
	namespace cfg {
		class Node;
	}
}

namespace forec {
	namespace reachability {
		class Threading {
	
			// Static
			public:
				static void resetThreadStates(const std::string &parId, const enum tools::Threading::State state);
				static void setThreadState(const std::string &coreId, const std::string &threadId, const enum tools::Threading::State state);

			// Dynamic
			public:
				Threading(const std::string &threadId);
				Threading(Threading &thread, const bool isLeaf, const bool isAlternate);
			
				const std::string getId(void);
				const std::string getCoreId(void);
			
				void setState(enum tools::Threading::State state);
				const enum tools::Threading::State getState(void);
			
				void addAlternateProgramCounter(forec::cfg::Node &alternateProgramCounter);
				void clearAlternateProgramCounter(void);
			
				void advanceProgramCounter(forec::cfg::Node &nextProgramCounter);

				std::vector<forec::cfg::Node *> *getProgramCounters(void);
				forec::cfg::Node *getCurrentProgramCounter(void);
			
				const unsigned int getCurrentAddress(void);
			
				const std::string toString(const std::string &indent = "");
			
			private:	
				const std::string id;
				const std::string coreId;
				enum tools::Threading::State state;
				forec::cfg::Node *alternateProgramCounter;
			
				// vector<programCounter>
				// First element should be the continuation point of the thread.
				std::vector<forec::cfg::Node *> programCounters;
				
		};
	}
}

#endif // FOREC_REACHABILITY_THREADING_HPP

