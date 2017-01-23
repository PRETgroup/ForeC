#ifndef TOOLS_LINK_HPP
#define TOOLS_LINK_HPP
/*
 *  Link.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 17/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <string>
#include <map>
#include <set>

namespace forec {
	namespace cfg {
		class Node;
	}
}

namespace tools {
	class Link {
		public:
			static void clear(void);
			static void resetPrevious(void);
			static void setPrevious(forec::cfg::Node &previousNode);
		
			static const bool hasPrevious(void);
			static forec::cfg::Node *getPrevious(void);

			static void setForecStatementEntry(const bool value);
			static const bool isForecStatementEntry(void);
			
			static void addUnresolvedBranchDestination(const unsigned int destinationAddress, forec::cfg::Node &sourceNode);
			static void resolveBranchDestinations(const unsigned int programCounter, forec::cfg::Node &destinationNode, const int latency);
			static const bool hasUnresolvedBranchDestinations(void);

			static void addUnresolvedAbortDestination(const std::string &abortId, forec::cfg::Node &sourceNode);
			static void resolveAbortDestinations(const std::string &abortId, forec::cfg::Node &destinationNode, const int latency);
			static const bool hasUnresolvedAbortDestinations(void);
			static forec::cfg::Node *getAbortScopeEndNode(const std::string &abortId);
			
			static const std::string toString(void);
			
			
		private:
			static forec::cfg::Node *globalPrevious;
			static bool forecStatementEntry;
			
			// map<abortId, destinationNode *>
			static std::map<std::string, forec::cfg::Node *> abortScopeEndNodes;

			// map<destinationAddress, set<sourceNode *> >
			static std::map<unsigned int, std::set<forec::cfg::Node *> > unresolvedBranchDestinations;

			// map<destinationAddress, set<sourceNode *> >
			static std::map<std::string, std::set<forec::cfg::Node *> > unresolvedAbortDestinations;
	};

}

#endif // TOOLS_LINK_HPP

