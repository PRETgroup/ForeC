/*
 *  AssemblyLine.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 08/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "AssemblyLine.hpp"

#include "AssemblyInstruction.hpp"
#include "Operand.hpp"
#include "OperandList.hpp"

#include "../tools/Costing.hpp"
#include "../tools/Function.hpp"

namespace global {
	extern std::string architecture;
}

namespace forec {
	namespace cfg {
		
		// Initialise static variable
		int AssemblyLine::globalCount = 0;
		
		// Duplicating a function body.
		AssemblyLine::AssemblyLine(const AssemblyLine &original)
								  : Node("AssemblyLine", original.variant, this->globalCount++), programCounter(original.programCounter), 
								    opcode(original.opcode), instruction(original.instruction), operandList(original.operandList), 
								    hexValue(original.hexValue), label(original.label) {
			this->programCounterValue = original.programCounterValue;

			delaySlot = NULL;
			isDelaySlot = false;
			inlined = false;

			hasGlobalMemoryAccess = original.hasGlobalMemoryAccess;
		}

		AssemblyLine::AssemblyLine(const std::string &programCounter, const std::string &opcode, Node &instruction, Node &operandList, const std::string &hexValue, const std::string &label, const std::string &variant)
								  : Node("AssemblyLine", variant, this->globalCount++), programCounter(programCounter), opcode(opcode), instruction(&instruction), operandList(&operandList), hexValue(hexValue), label(label) {
			instruction.setParent((Node *)this);
			operandList.setParent((Node *)this);
			
			std::istringstream input(programCounter);
			input >> std::hex >> programCounterValue;

			delaySlot = NULL;
			isDelaySlot = false;
			inlined = false;
			
			if (global::architecture.compare("microblaze") == 0) {
				if (AssemblyLine::getHasMemoryAccess()) {
					if (label.find("rodata") == std::string::npos) {
						// Global variable not in local data memory.
						std::vector<Node *> operands = ((OperandList *)&operandList)->getOperands();
						hasGlobalMemoryAccess = tools::Costing::isGlobalMemoryAccess(((Operand *)operands[1])->getValue());
					} else {
						hasGlobalMemoryAccess = false;
					}
				} else {
					hasGlobalMemoryAccess = false;
				}
			}
		}
		
		AssemblyInstruction *AssemblyLine::getInstruction(void) {
			return (AssemblyInstruction *)instruction;
		}
		
		const unsigned int AssemblyLine::getProgramCounter(void) {
			return programCounterValue;
		}
		
		const unsigned int AssemblyLine::getDestinationAddress(void) {
			if (hexValue.compare("") == 0) {
				return -1;
			}

			unsigned int destinationAddress = 0;
			if (global::architecture.compare("microblaze") == 0) {
				std::istringstream input(hexValue.substr(3));	// Remove the leading "// "
				input >> std::hex >> destinationAddress;
			} else if (global::architecture.compare("ptarm") == 0) {
				// First operand
				std::istringstream input(hexValue.substr(2));	// Remove the leading "; "
				input >> std::hex >> destinationAddress;				
			}
			return destinationAddress;
		}
		
		const int AssemblyLine::getInstructionLatency(void) {
			AssemblyInstruction *instruction = AssemblyLine::getInstruction();
			return instruction->getLatency();
		}
		
		// Merging and reachability
		const int AssemblyLine::getMemoryLatency(const int elapsedTime, const bool needAlignment) {
			AssemblyInstruction *instruction = AssemblyLine::getInstruction();
			const std::string instructionName = instruction->getInstruction();
			int latency = 0;

			if (global::architecture.compare("microblaze") == 0) {
				// If memory access.
				const char accessType = instructionName[0];
				if (accessType == 'l' || (accessType == 's' && instructionName[1] != 'e' && instructionName[1] != 'r')) {
					std::vector<Node *> operands = ((OperandList *)operandList)->getOperands();

					if (operands.size() != 3) {
						std::ostringstream output;
						output << "AssemblyLine::getMemoryLatency: Expecting three operands but got " << operands.size() << " instead." << std::endl;
						output << "\t" << *this;
						throw std::string(output.str());
					}
					
					if (needAlignment) {
						// Account for the worst-case bus latency.
						latency = tools::Costing::getMaxAccessLatency(hasGlobalMemoryAccess, accessType);
					} else {
						// Already accounted for the worst-case bus latency.
						latency = tools::Costing::getAccessLatency(hasGlobalMemoryAccess, elapsedTime, accessType);
					}
				}
			} else if (global::architecture.compare("ptarm") == 0) {
				// If memory access.
				char accessType = instructionName[0];
				if (accessType == 'l' || (accessType == 's' && instructionName[1] == 't') || instructionName.compare("swp") == 0
					|| instructionName.compare("swpb") == 0 || instructionName.compare("pop") == 0 || instructionName.compare("push") == 0) {
					
					if (instructionName.compare("swp") == 0 || instructionName.compare("swpb") == 0 || instructionName.compare("pop") == 0){
						accessType = 'l';
					} else if (instructionName.compare("push") == 0) {
						accessType = 's';
					}
					
					if (needAlignment) {
						// Account for the worst-case bus latency.
						latency = tools::Costing::getMaxAccessLatency(hasGlobalMemoryAccess, accessType);
					} else {
						// Already accounted for the worst-case bus latency.
						latency = tools::Costing::getAccessLatency(hasGlobalMemoryAccess, elapsedTime, accessType);
					}
				}
			}

			return latency;
		}
	
		// Compute instruction and memory latency. (ForeC statements and schedulers).
		const int AssemblyLine::getLatency(const bool mergeGlobalAccesses, const bool needAlignment, const int mergedLatency) {
			AssemblyInstruction *instruction = AssemblyLine::getInstruction();
			const std::string instructionName = instruction->getInstruction();
			int latency = instruction->getLatency();

			if (global::architecture.compare("microblaze") == 0) {
				if (mergeGlobalAccesses) {
					// If memory access, then the bus time has to be added.
					const char accessType = instructionName[0];
					if (accessType == 'l' || (accessType == 's' && instructionName[1] != 'e' && instructionName[1] != 'r')) {
						std::vector<Node *> operands = ((OperandList *)operandList)->getOperands();

						if (operands.size() != 3) {
							std::ostringstream output;
							output << "AssemblyLine::getLatency: Expecting three operands but got " << operands.size() << " instead." << std::endl;
							output << "\t" << *this;
							throw std::string(output.str());
						}

						if (needAlignment) {
							// Account for the worst-case bus latency.
							latency += tools::Costing::getMaxAccessLatency(hasGlobalMemoryAccess, accessType);
						} else {
							// Already accounted for the worst-case bus latency at the start of execution.
							latency += tools::Costing::getAccessLatency(hasGlobalMemoryAccess, mergedLatency + latency, accessType);
						}
					}
				}
			} else if (global::architecture.compare("ptarm") == 0) {
				if (mergeGlobalAccesses) {
					// If memory access, then the bus time has to be added.
					char accessType = instructionName[0];
					if (accessType == 'l' || (accessType == 's' && instructionName[1] == 't') || instructionName.compare("swp") == 0
						|| instructionName.compare("swpb") == 0 || instructionName.compare("pop") == 0 || instructionName.compare("push") == 0) {
						
						if (instructionName.compare("swp") == 0 || instructionName.compare("swpb") == 0 || instructionName.compare("pop") == 0){
							accessType = 'l';
						} else if (instructionName.compare("push") == 0) {
							accessType = 's';
						}
						
						if (needAlignment) {
							// Account for the worst-case bus latency.
							latency += tools::Costing::getMaxAccessLatency(hasGlobalMemoryAccess, accessType);
						} else {
							// Already accounted for the worst-case bus latency at the start of execution.
							latency += tools::Costing::getAccessLatency(hasGlobalMemoryAccess, mergedLatency + latency, accessType);
						}
					}
				}

			}
			
			return latency;
		}

		const bool AssemblyLine::getHasMemoryAccess(void) {
			AssemblyInstruction *instruction = AssemblyLine::getInstruction();
			const std::string instructionName = instruction->getInstruction();
			
			if (global::architecture.compare("microblaze") == 0) {
				// If memory access.
				const char accessType = instructionName[0];
				if (accessType == 'l' || (accessType == 's' && instructionName[1] != 'e' && instructionName[1] != 'r')) {
					return true;
				}
			} else if (global::architecture.compare("ptarm") == 0) {
				// If memory access.
				const char accessType = instructionName[0];
				if (accessType == 'l' || (accessType == 's' && instructionName[1] == 't') || instructionName.compare("swp") == 0
					|| instructionName.compare("swpb") == 0 || instructionName.compare("pop") == 0 || instructionName.compare("push") == 0) {
					return true;
				}
			}
			
			return false;
		}

		const bool AssemblyLine::getHasGlobalMemoryAccess(void) {
			return hasGlobalMemoryAccess;
		}
		
		void AssemblyLine::setHasGlobalMemoryAccess(const bool hasGlobalMemoryAccess) {
			this->hasGlobalMemoryAccess = hasGlobalMemoryAccess;
		}
		
		const std::string AssemblyLine::getLabel(void) {
			return label;
		}
		
		Node *AssemblyLine::getOperandList(void) {
			return operandList;
		}
		
		const bool AssemblyLine::isBranching(void) {
			return ((AssemblyInstruction *)instruction)->isBranching();
		}

		const bool AssemblyLine::isBranchingWithDelay(void) {
			return ((AssemblyInstruction *)instruction)->isBranchingWithDelay();
		}

		const bool AssemblyLine::isBranchingWithoutDelay(void) {
			return ((AssemblyInstruction *)instruction)->isBranchingWithoutDelay();
		}

		const bool AssemblyLine::isConditionalBranching(void) {
			return ((AssemblyInstruction *)instruction)->isConditionalBranching();
		}

		const bool AssemblyLine::isUnconditionalBranching(void) {
			return ((AssemblyInstruction *)instruction)->isUnconditionalBranching();
		}

		const bool AssemblyLine::isConditionalBranchingWithDelay(void) {
			return ((AssemblyInstruction *)instruction)->isConditionalBranchingWithDelay();
		}
		
		const bool AssemblyLine::isConditionalBranchingWithoutDelay(void) {
			return ((AssemblyInstruction *)instruction)->isConditionalBranchingWithoutDelay();
		}
		
		const bool AssemblyLine::isUnconditionalBranchingWithDelay(void) {
			return ((AssemblyInstruction *)instruction)->isUnconditionalBranchingWithDelay();
		}
		
		const bool AssemblyLine::isUnconditionalBranchingWithoutDelay(void) {
			return ((AssemblyInstruction *)instruction)->isUnconditionalBranchingWithoutDelay();
		}

		const bool AssemblyLine::isFunctionCall(void) {
			return ((AssemblyInstruction *)instruction)->isFunctionCall();
		}
		
		const bool AssemblyLine::isInlinedFunctionCall(void) {
			return inlined;
		}
		
		const bool AssemblyLine::isFunctionReturn(void) {
			return ((AssemblyInstruction *)instruction)->isFunctionReturn();
		}
		
		const int AssemblyLine::getCount(void) {
			return globalCount;
		}
		
		void AssemblyLine::linkNodes(void) {
			// MicroBlaze has delays after certain branches. Ptarm does not have delays.
			if (global::architecture.compare("microblaze") == 0) {
				if (tools::Link::hasPrevious() && !tools::Link::isForecStatementEntry()) {
					Node *previousNode = tools::Link::getPrevious();
					addPreviousNode(*previousNode);
					
					// Determine previous node type to handle the delay slot.
					if (previousNode->isType("AssemblyLine")) {
						AssemblyLine *previousAssemblyLine = (AssemblyLine *)previousNode;
						
						if (previousAssemblyLine->isBranching() || previousAssemblyLine->isFunctionReturn()) {
							if (previousAssemblyLine->isBranchingWithDelay() || previousAssemblyLine->isFunctionReturn()) {
								// Delay instruction.
								if (previousAssemblyLine->getDelaySlot() == NULL) {
									previousAssemblyLine->setDelaySlot(*this);
									this->setIsDelaySlot(true);
								} else if (previousAssemblyLine->isConditionalBranching() || previousAssemblyLine->isFunctionCall()) {
									// No longer the delay slot because it has already been set.
									previousAssemblyLine->addNextNode(*this, AssemblyLine::getInstructionLatency());
								}
							} else {
								// In computation.
								previousAssemblyLine->addNextNode(*this, AssemblyLine::getInstructionLatency());
							}
						} else {
							// Previous was computation.
							previousAssemblyLine->addNextNode(*this, AssemblyLine::getInstructionLatency());
						}
					} else {
						previousNode->addNextNode(*this, AssemblyLine::getInstructionLatency());
					}
				}
				
				tools::Link::setForecStatementEntry(false);

				if (isBranching() && !isFunctionCall()) {
					tools::Link::addUnresolvedBranchDestination(getDestinationAddress(), *this);
				}

				// Update globalPrevious
				if (isBranching()) {
					if (isUnconditionalBranchingWithoutDelay()) {
						// No instruction will follow in sequence.
						tools::Link::resetPrevious();
					} else {
						// Delay slot or computation instruction will follow in sequence.
						tools::Link::setPrevious(*this);
					}
				} else if (tools::Link::hasPrevious()) {
					// Handle the delay slot.
					Node *previousNode = tools::Link::getPrevious();
					
					// Determine previous node type.
					if (previousNode->isType("AssemblyLine")) {
						AssemblyLine *previousAssemblyLine = (AssemblyLine *)previousNode;
						if (previousAssemblyLine->isUnconditionalBranchingWithDelay() || previousAssemblyLine->isFunctionReturn()) {
							// Delay slot.
							if (previousAssemblyLine->isFunctionCall()) {
								if (previousAssemblyLine->getDelaySlot() != this) {
									tools::Link::setPrevious(*this);
								}
							} else {
								// Control-flow path does not continue sequentially past this delay slot.
								tools::Link::resetPrevious();
							}
						} else if (previousAssemblyLine->isConditionalBranchingWithDelay()) {
							if (previousAssemblyLine->getDelaySlot() == this)  {
								// In delay slot.
								// Keep the globalPrevious as it is.
							} else {
								tools::Link::setPrevious(*this);
							}
						} else {
							// Previous node was computation.
							tools::Link::setPrevious(*this);
						}
					} else {
						// AbortStatement, ParStatement, PauseStatement
						tools::Link::setPrevious(*this);
					}
				} else {
					// Computation
					tools::Link::setPrevious(*this);
				}
			} else {
				if (tools::Link::hasPrevious() && !tools::Link::isForecStatementEntry()) {
					Node *previousNode = tools::Link::getPrevious();
					addPreviousNode(*previousNode);
					
					previousNode->addNextNode(*this, AssemblyLine::getInstructionLatency());
				}
				
				tools::Link::setForecStatementEntry(false);
				
				if (isBranching() && !isFunctionCall()) {
					tools::Link::addUnresolvedBranchDestination(getDestinationAddress(), *this);
				}
				
				// Update globalPrevious
				if (isFunctionCall()) {
					// Computation instruction will follow in sequence.
					tools::Link::setPrevious(*this);
				} else if (isFunctionReturn() || isUnconditionalBranching()) {
					// No instruction will follow in sequence.
					tools::Link::resetPrevious();
				} else {
					// Computation
					tools::Link::setPrevious(*this);
				}
			}
		}

		void AssemblyLine::resolveDestinations(void) {
			tools::Link::resolveBranchDestinations(getProgramCounter(), *this, getInstructionLatency());
		}
		
		void AssemblyLine::setDelaySlot(AssemblyLine &currentLine) {
			delaySlot = &currentLine;
		}

		Node* AssemblyLine::getDelaySlot(void) {
			return delaySlot;
		}
		
		void AssemblyLine::setIsDelaySlot(const bool isDelaySlot) {
			this->isDelaySlot = isDelaySlot;
		}
		
		const bool AssemblyLine::getIsDelaySlot(void) {
			return isDelaySlot;
		}

		void AssemblyLine::setInlined(const bool inlined) {
			this->inlined = inlined;
		}
		
		void AssemblyLine::inlineFunctions(void) {
			// Nothing.
		}

		void AssemblyLine::toXml(std::ostream &output) {
			output << tools::Tab::toString() << "<source type=\"assembly\" id=\"" << getId() << "\">" << std::endl;
			tools::Tab::indent();
			
			if (AssemblyLine::getHasMemoryAccess()) {
				output << tools::Tab::toString() << "<memoryAccess type=\"" << (AssemblyLine::getHasGlobalMemoryAccess() ? "global" : "local") << "\" />" << std::endl;
			}
			
			if (isDelaySlot) {
				output << tools::Tab::toString() << "<delaySlot />" << std::endl;
			}
			
			output << tools::Tab::toString() << "<programCounter>" << std::endl;
			output << tools::Tab::toString() << "\t" << std::hex << getProgramCounter() << std::dec << std::endl;
			output << tools::Tab::toString() << "</programCounter>" << std::endl;

			output << tools::Tab::toString() << "<opcode>" << std::endl;
			output << tools::Tab::toString() << "\t" << opcode << std::endl;
			output << tools::Tab::toString() << "</opcode>" << std::endl;
			
			instruction->toXml(output);
			operandList->toXml(output);
			
			if (delaySlot != NULL) {
				output << tools::Tab::toString() << "<delay node=\">" << delaySlot->getId() << "\" />" << std::endl;
			}
			
			for (std::vector<Node *>::iterator i = previousNodes.begin(); i != previousNodes.end(); ++i) {
				output << tools::Tab::toString() << "<previous node=\"" << (*i)->getId() << "\" />" << std::endl;
			}
			
			for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
				output << tools::Tab::toString() << "<next node=\"" << i->first->getId() << "\" latency=\"" << i->second.first << "\" />" << std::endl;
			}
			
			tools::Tab::dedent();
			output << tools::Tab::toString() << "</source>" << std::endl;
		}

		void AssemblyLine::toUppaal(std::ostream &output) {
			// Nothing.
		}
		
		void AssemblyLine::toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) {
			y += 64;
			
			locations << tools::Tab::toString() << "<location id=\"" << getId() << "\" x=\"" << x << "\" y=\"" << y << "\" color=\"#FFFFFF\">" << std::endl;
			tools::Tab::indent();
			locations << tools::Tab::toString() << "<name x=\"" << (x - 56) << "\" y=\"" << (y + 8) << "\">" << getId() << "</name>" << std::endl;
			tools::Tab::dedent();
			locations << tools::Tab::toString() << "</location>" << std::endl;
			
			// Edges.
			int offset = 0;
			for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
				transitions << tools::Tab::toString() << "<transition>" << std::endl;
				
				tools::Tab::indent();
				transitions << tools::Tab::toString() << "<source ref=\"" << getId() << "\" />" << std::endl;
				transitions << tools::Tab::toString() << "<target ref=\"" << i->first->getId() << "\" />" << std::endl;
				if (offset != 0) {
					transitions << tools::Tab::toString() << "<nail x=\"" << (x + offset) << "\" y=\"" << y << "\" />" << std::endl;
				}
				// TODO: Add guard, synchronisation, or assignment labels.
				// TODO: For abort/scheduling/tick/computing the execution time.
				tools::Tab::dedent();
				
				transitions << tools::Tab::toString() << "</transition>" << std::endl;
				
				offset -= 8;
			}
		}

		void AssemblyLine::prettyPrint(std::ostream &output) {
			output << "0x" << std::hex << getProgramCounter() << std::dec << ": " << *instruction << " " << *operandList;
			
			if (hexValue.compare("") != 0) {
				output << " // 0x" << std::hex << getDestinationAddress() << std::dec;
			}
			
			if (label.compare("") != 0) {
				output << " " << label;
			}

			output << " (" << getLatency(true, false, 0) << ')';
		}
		
	}
}

