#ifndef FOREC_REACHABILITY_REACHABILITY_HPP
#define FOREC_REACHABILITY_REACHABILITY_HPP
/*
 *  Reachability.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 21/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <vector>
#include <set>
#include <string>
#include <fstream>

namespace forec {
	namespace reachability {
		class Reaction;
	}
}

namespace forec {
	namespace cfg {
		class Node;
	}
}

namespace forec {
	namespace reachability {
		class Reachability {
			public:
				static void clear(void);
				static void openOutFile(const std::string &fileName);
				static void closeOutFile(void);
				
				static void setStartingReaction(const std::string &threadId);
				static Reaction *getStartingReaction(void);
				static std::vector<Reaction *> getCurrentReactions(void);
				static std::vector<Reaction *> getActiveReactions(std::vector<Reaction *> reactions);
				static std::vector<Reaction *> getCurrentActiveReactions(void);
				
				static const Reaction *compute(void);

				static Reaction *getMaximumReaction(void);
				static const unsigned int getMaximumReactionTime(void);
				static const unsigned int getReactionsSeenCount(void);

				static void toXml(std::vector<Reaction *> &reactionResults);
				
				
			private:
				static int progressCounter;
				static unsigned int reactionsSeenCount;
				static std::ofstream outFile;

				static Reaction *maximumReaction;
				
				// Each outer element is one evolution.
				// vector<vector<reactions> >
				static std::vector<std::vector<Reaction *> > trace;
				
				static std::set<std::string> visitedReactions;
		};
	}
}


#endif // FOREC_REACHABILITY_REACHABILITY_HPP
