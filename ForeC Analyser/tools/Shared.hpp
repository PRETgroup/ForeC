#ifndef TOOLS_SHARED_HPP
#define TOOLS_SHARED_HPP
/*
 *  Tab.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 15/04/12.
 *  Copyright 2012 Potential Publishers. All rights reserved.
 *
 */

#include <string>
#include <map>
#include <vector>

#include "rapidxml.hpp"

namespace tools {
	class Multicore;
}

namespace tools {
	class Shared {

		public:
			static void clear(void);
			static void loadInformation(const rapidxml::xml_node<> &information);
			
			static const std::vector<std::pair<std::string, std::pair<int, std::string> > > getVariablesToCombine(const std::string &threadScope, const std::string &parId);
			static const int getParIndex(const std::string &threadScope, const std::string &parId);
			static const int getParIndexesSize(const std::string &threadScope);
			
			static const unsigned int combineLatency(Multicore &core, const std::string &function);
			
			static const std::string toString(void);
			
		private:
			// map<threadScope, map<parId, vector<pair<variableId, pair<defines, combine> > > > >
			static std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, std::pair<int, std::string> > > > > variablesToCombine;
			
			// map<threadScope, map<parId, index> >
			static std::map<std::string, std::map<std::string, int> > parIndexes;
	};

}

#endif // TOOLS_SHARED_HPP

