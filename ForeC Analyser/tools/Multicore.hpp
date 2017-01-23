#ifndef TOOLS_MULTICORE_HPP
#define TOOLS_MULTICORE_HPP
/*
 *  Multicore.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 21/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <string>
#include <vector>
#include <map>
#include <set>

#include "rapidxml.hpp"

namespace tools {
	class Multicore {
		public:
			static void clear(void);
			
			static void loadInformation(const rapidxml::xml_node<> &information);
			
			static const std::string getAllocatedCore(const std::string &threadId);
			static const std::string getAllocatedCores(const std::string &threadId);
			
			static const std::set<std::string> getAllocatedThreads(const std::string &coreId);
			static const std::set<std::string> getAllocatedParCores(const std::string &parId);
			static const std::set<std::string> getActiveParCores(const std::string &threadId);
			static const std::set<std::string> getAllCoreIds(void);
			
			static const std::string staticToString(void);
			
			
		private:		
			static const std::string threadSuffix;
		
			// map<coreId, set<threadId> >
			static std::map<std::string, std::set<std::string> > allocatedThreads;			

			// map<threadId, coreId >
			static std::map<std::string, std::string> allocatedCores;			

			// map<parId, set<coreId> >
			static std::map<std::string, std::set<std::string> > allocatedParCores;
			
			// map<threadId, set<coreId> >
			static std::map<std::string, std::set<std::string> > activeParCores;

			// set<coreId>
			static std::set<std::string> allCoreIds;

			
		// Dynamic
		public:
			enum State {
				executing,
				executed
			};
		
			Multicore(const std::string &id, const unsigned int elapsedTime = 0);
			Multicore(const Multicore &core);

			const std::string getId(void);

			void resetElapsedTime(void);
			void setElapsedTime(const unsigned int newElapsedTime);
			const unsigned int getElapsedTime(void);
			void incrementElapsedTime(const unsigned int increment);
			
			void setNextStartingElapsedTime(const unsigned int elapsedTime);
			const unsigned int getNextStartingElapsedTime(void);

			void setState(enum State state);
			const enum State getState(void);
			
			void addEvent(const std::string eventName);
			const std::string getExecutionTrace(const std::string &indent);

			const std::string toString(const std::string &indent = "");

			
		private:
			enum State state;
			const std::string id;
			
			unsigned int elapsedTime;
			unsigned int nextStartingElapsedTime;
			
			// vector<pair<elapsedTime, eventName> >
			std::vector<std::pair<int, std::string> > executionTrace;
	};
}


#endif // TOOLS_MULTICORE_HPP
