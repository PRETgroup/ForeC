#ifndef FOREC_CFG_ASSEMBLY_INSTRUCTION_HPP
#define FOREC_CFG_ASSEMBLY_INSTRUCTION_HPP

/*
 *  AssemblyInstruction.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 08/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace cfg {
		class AssemblyInstruction : public Node {
			public:
				AssemblyInstruction(const std::string &instruction, const int latency, const std::string &variant = "none");
				AssemblyInstruction(const std::string &instruction, const std::string &variant = "none");
							
				static const int getCount(void);
				
				const std::string getInstruction(void);
				const int getLatency(void);
				
				const bool isBranching(void);
				const bool isBranchingWithDelay(void);
				const bool isBranchingWithoutDelay(void);
				const bool isConditionalBranching(void);
				const bool isUnconditionalBranching(void);
				const bool isConditionalBranchingWithDelay(void);
				const bool isConditionalBranchingWithoutDelay(void);
				const bool isUnconditionalBranchingWithDelay(void);
				const bool isUnconditionalBranchingWithoutDelay(void);

				const bool isFunctionCall(void);
				const bool isFunctionReturn(void);
				
				void inlineFunctions(void);
				
				void toXml(std::ostream &output);
				void toUppaal(std::ostream &output);
				void toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions);
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				
				const std::string instruction;
				int latency;
		};
	}
}

#endif // FOREC_CFG_ASSEMBLY_INSTRUCTION_HPP
