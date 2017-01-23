#ifndef TOOLS_OPTIMISE_HPP
#define TOOLS_OPTIMISE_HPP
/*
 *  Tab.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/12.
 *  Copyright 2012 Potential Publishers. All rights reserved.
 *
 */

#include <vector>
#include <set>

namespace forec {
	namespace cfg {
		class Node;
	}
}

namespace tools {
	class Optimise {
		public:
			static int performMergeNodes(forec::cfg::Node &startNode, const bool mergeGlobalAccesses);
			static std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > > getDestinationNodes(forec::cfg::Node &sourceNode, std::set<forec::cfg::Node *> &sourceNodesFound, const bool mergeGlobalAccesses);
			static void mergeNodes(forec::cfg::Node &source, std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > > &destinationNodes);

			static void mergeBranches(std::vector<forec::cfg::Node *> &children, const bool recusiveMerge);
			
			static void removeUnreachableNodes(std::vector<forec::cfg::Node *> &children);
		private:

	};

}

#endif // TOOLS_OPTIMISE_HPP
