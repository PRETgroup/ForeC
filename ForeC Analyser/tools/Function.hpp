#ifndef TOOLS_FUNCTION_HPP
#define TOOLS_FUNCTION_HPP
/*
 *  Function.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 10/11/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <string>
#include <map>
#include <set>
#include <vector>

#include "rapidxml.hpp"

namespace global {
	extern bool merge;
	extern bool mergeBranches;
}

namespace forec {
	namespace cfg {
		class Node;
	}
}

namespace tools {
	class Multicore;
}

namespace tools {
	class Function {
	
		public:
			enum State {
				executing,
				terminated,
				branch
			};

			struct Trace {
				std::vector<forec::cfg::Node *> programCounters;
				enum State state;
				Multicore *core;
			};

			static void clear(void);
					
			static void add(const std::string &functionId, std::vector<forec::cfg::Node *> &programCounters);
			static void matchGlobalMemoryAccess(forec::cfg::Node &node, int &globalMemoryMatch);
			
			static forec::cfg::Node *getStartingNode(const std::string &functionId);
			static void copy(const std::string &functionId, std::vector<forec::cfg::Node *> &functionNodes, const bool merge = global::merge, const bool mergeBranches = global::mergeBranches);

			static const unsigned int getLatency(Multicore &core, const std::string &functionId);
			static const enum State assemblyLine(struct Trace &trace, std::vector<struct Function::Trace> &traces, forec::cfg::Node &currentProgramCounter);

			static struct Trace copyTrace(const struct Trace &trace);
			static void copyProgramCounters(const std::string &functionId, std::vector<forec::cfg::Node *> &threadProgramCounters);
			
			static void toXml(std::ostream &output);
			static const std::string toString(void);
			
			
		private:
			static int nodesMerged;
		
			// map<functionId, programCounters>
			static std::map<std::string, std::vector<forec::cfg::Node *> > programCounters;

	};

}

#endif // TOOLS_FUNCTION_HPP
