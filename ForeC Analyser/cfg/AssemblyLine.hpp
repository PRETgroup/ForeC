#ifndef FOREC_CFG_ASSEMBLY_LINE_HPP
#define FOREC_CFG_ASSEMBLY_LINE_HPP

/*
 *  AssemblyLine.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 08/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace cfg {
		class AssemblyInstruction;
	}
}

namespace forec {
	namespace cfg {
		class AssemblyLine : public Node {
			public:
				AssemblyLine(const AssemblyLine &original);
				AssemblyLine(const std::string &programCounter, const std::string &opcode, Node &instruction, Node &operandList, const std::string &hexValue = "", const std::string &label = "", const std::string &variant = "none");
				
				AssemblyInstruction *getInstruction(void);
				const unsigned int getProgramCounter(void);
				const unsigned int getDestinationAddress(void);
				
				const int getInstructionLatency(void);
				const int getMemoryLatency(const int elapsedTime, const bool needAlignment);
				const int getLatency(const bool mergeGlobalAccesses, const bool needAlignment, const int mergedLatency);
				const bool getHasMemoryAccess(void);
				const bool getHasGlobalMemoryAccess(void);
				void setHasGlobalMemoryAccess(const bool hasGlobalMemoryAccess);
				
				const std::string getLabel(void);
				
				Node *getOperandList(void);

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
				const bool isInlinedFunctionCall(void);
				const bool isFunctionReturn(void);
				
				static const int getCount(void);
				
				void linkNodes(void);
				void resolveDestinations(void);
				
				void setDelaySlot(AssemblyLine &currentLine);
				Node* getDelaySlot(void);
				
				void setIsDelaySlot(const bool isDelaySlot);
				const bool getIsDelaySlot(void);
				
				void setResolvedMemoryLatency(const bool resolvedMemoryLatency);
				
				void setInlined(const bool inlined);
				void inlineFunctions(void);

				void toXml(std::ostream &output);
				void toUppaal(std::ostream &output);
				void toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions);
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				
				const std::string programCounter;
				unsigned int programCounterValue;
				const std::string opcode;
				Node *instruction;
				Node *operandList;
				const std::string hexValue;
				const std::string label;
				bool inlined;
				bool isDelaySlot;
				
				bool hasGlobalMemoryAccess;
				
				AssemblyLine *delaySlot;
		};
	}
}

#endif // FOREC_CFG_ASSEMBLY_LINE_HPP
