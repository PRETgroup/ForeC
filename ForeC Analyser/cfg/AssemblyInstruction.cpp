/*
 *  AssemblyInstruction.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 08/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "AssemblyInstruction.hpp"
#include "AssemblyLine.hpp"
#include "Operand.hpp"
#include "OperandList.hpp"

#include "../tools/Costing.hpp"

namespace global {
	extern std::string architecture;
}

namespace forec {
	namespace cfg {
		
		// Initialise static variable
		int AssemblyInstruction::globalCount = 0;
		
		AssemblyInstruction::AssemblyInstruction(const std::string &instruction, const int latency, const std::string &variant) : Node("AssemblyInstruction", variant, this->globalCount++), instruction(instruction), latency(latency) {

		}
		
		AssemblyInstruction::AssemblyInstruction(const std::string &instruction, const std::string &variant) : Node("AssemblyInstruction", variant, this->globalCount++), instruction(instruction) {
			latency = tools::Costing::getInstructionLatency(instruction);
		}
		
		const int AssemblyInstruction::getCount(void) {
			return globalCount;
		}
		
		const std::string AssemblyInstruction::getInstruction(void) {
			return instruction;
		}
		
		const int AssemblyInstruction::getLatency(void) {
			return latency;
		}

		const bool AssemblyInstruction::isBranching(void) {
			return (isVariant("branchConditional") || isVariant("branchConditionalWithDelay") || isVariant("branchUnconditional") || isVariant("branchUnconditionalWithDelay"));
		}

		const bool AssemblyInstruction::isBranchingWithDelay(void) {
			return (isVariant("branchConditionalWithDelay") || isVariant("branchUnconditionalWithDelay"));
		}

		const bool AssemblyInstruction::isBranchingWithoutDelay(void) {
			return (isVariant("branchConditional") || isVariant("branchUnconditional"));
		}

		const bool AssemblyInstruction::isConditionalBranching(void) {
			return (isVariant("branchConditional") || isVariant("branchConditionalWithDelay"));
		}

		const bool AssemblyInstruction::isUnconditionalBranching(void) {
			return (isVariant("branchUnconditional") || isVariant("branchUnconditionalWithDelay"));
		}

		const bool AssemblyInstruction::isConditionalBranchingWithDelay(void) {
			return isVariant("branchConditionalWithDelay");
		}
		
		const bool AssemblyInstruction::isConditionalBranchingWithoutDelay(void) {
			return isVariant("branchConditional");
		}

		const bool AssemblyInstruction::isUnconditionalBranchingWithDelay(void) {
			return isVariant("branchUnconditionalWithDelay");
		}
		
		const bool AssemblyInstruction::isUnconditionalBranchingWithoutDelay(void) {
			return isVariant("branchUnconditional");
		}
		
		const bool AssemblyInstruction::isFunctionCall(void) {
			if (global::architecture.compare("microblaze") == 0) {
				return AssemblyInstruction::getInstruction().compare("brlid") == 0;
			} else if (global::architecture.compare("ptarm") == 0) {
				return AssemblyInstruction::getInstruction().compare("bl") == 0;
			}
			
			return false;
		}
		
		const bool AssemblyInstruction::isFunctionReturn(void) {
			if (global::architecture.compare("microblaze") == 0) {
				return AssemblyInstruction::getInstruction().compare("rtsd") == 0;
			} else if (global::architecture.compare("ptarm") == 0) {
				// pop {fp,pc} is used if the function can call another function.
				if (AssemblyInstruction::getInstruction().compare("pop") == 0) {
					const std::vector<Node *> operandList = ((OperandList *)(((AssemblyLine *)parent)->getOperandList()))->getOperands();
					const std::vector<Node *> nestedOperandList = ((OperandList *)((OperandList *)operandList[0]))->getOperands();

					const std::string operand = ((Operand *)nestedOperandList.back())->getValue();
					if (operand.compare("pc") == 0) {
						return true;
					}
				}
		
				// mov pc,lr is used if the function cannot call another function.
				if (AssemblyInstruction::getInstruction().compare("mov") == 0) {
					const std::vector<Node *> operandList = ((OperandList *)(((AssemblyLine *)parent)->getOperandList()))->getOperands();
					const std::string operand1 = ((Operand *)operandList[0])->getValue();
					const std::string operand2 = ((Operand *)operandList[1])->getValue();

					if (operand1.compare("pc") == 0 && operand2.compare("lr") == 0) {
						return true;
					}
				}
			}
			
			return false;
		}
		
		void AssemblyInstruction::inlineFunctions(void) {
			// Nothing.
		}
		
		void AssemblyInstruction::toXml(std::ostream &output) {
			output << tools::Tab::toString() << "<instruction latency=\"" << latency << "\">" << std::endl;
			output << tools::Tab::toString() << "\t" << instruction << std::endl;
			output << tools::Tab::toString() << "</instruction>" << std::endl;
		}
		
		void AssemblyInstruction::toUppaal(std::ostream &output) {
			// Nothing.
		}
		
		void AssemblyInstruction::toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) {
			// Nothing.
		}
		
		void AssemblyInstruction::prettyPrint(std::ostream &output) {
			output << instruction;
			if (isFunctionCall()) {
				output << " (call)";
			}
			if (isFunctionReturn()) {
				output << " (return)";
			}
		}
		
	}
}

