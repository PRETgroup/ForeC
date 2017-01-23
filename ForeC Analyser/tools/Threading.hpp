#ifndef TOOLS_THREADING_HPP
#define TOOLS_THREADING_HPP
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

#include "rapidxml.hpp"

namespace forec {
	namespace cfg {
		class Node;
	}
}

namespace tools {
	class Threading {
	
		public:
			enum State {
				reacting = 0,
				reacted,
				terminated,
			
				branch,			// Branch state only valid when reaching to the next reacting, reacted or terminated state.
			};
				
			static void clear(const bool debugging);
		
			static void loadInformation(const rapidxml::xml_node<> &information);
			static void loadThreadGraphRecursive(rapidxml::xml_node<> *node, std::set<std::string> &encounteredParIds);

			static const std::set<std::string> getAllThreadIds(void);
			static const std::vector<std::string> getThreadIds(const std::string &parId);
			static const std::string getEnclosingThreadId(const std::string &parId);
			static const std::vector<std::string> getParIds(const std::string &threadId);
			static const std::string getEnclosingParId(const std::string &threadId);
			
			static const int getParIndex(const std::string &coreId, const std::string &threadScope, const std::string &parId);
			static const int getParIndexesSize(const std::string &coreId, const std::string &threadScope);
			static const int getNumberOfHandlers(const std::string &coreId, const std::string &threadScope, const std::string &parId);
						
			static const bool hasPar(const std::string &threadId);
			static const bool isNested(const std::string &parId);

			static const std::vector<std::pair<std::string, enum State> > getAllocatedThreads(const std::string &parId, const std::string &coreId);
			static const bool parCoreTerminated(const std::string &parId, const std::string &coreId);
							
			static const std::vector<std::string> getAborts(const std::string &parId, const std::string &variant);
			
			static void addStartingNode(const std::string &threadId, forec::cfg::Node &startNode);
			static void setStartingNode(const std::string &threadId, forec::cfg::Node &startNode);
			static forec::cfg::Node *getStartingNode(const std::string &threadId);

			static const std::string staticToString(void);
			
			static bool debugging;
			
			// map<parId, map<coreId, vector<pair<threadId, state> > > >
			static std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, enum State> > > > parCores;

		private:
			// map<parId, threadIdList>
			static std::map<std::string, std::vector<std::string> > parIds;
			
			// map<coreId, map<threadScope, map<parId, pair<index, numberOfHandlers> > > >
			static std::map<std::string, std::map<std::string, std::map<std::string, std::pair<int, int> > > > parIndexes;
			
			// map<threadId, parIdList>
			static std::map<std::string, std::vector<std::string> > threadIds;
			
			// map<parId, threadId>
			static std::map<std::string, std::string> enclosingThreadIds;
			
			// map<threadId, enclosingParId>
			static std::map<std::string, std::string> enclosingParIds;
			
			// map<parId, map<[strong, weak], vector<abortId> > >
			static std::map<std::string, std::map<std::string, std::vector<std::string> > > abortIds;
						
			// map<threadId, startingNode>
			static std::map<std::string, forec::cfg::Node *> startingNodes;
	};

}

#endif // TOOLS_THREADING_HPP
