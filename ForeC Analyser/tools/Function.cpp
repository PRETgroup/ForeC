/*
 *  Function.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 10/11/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Function.hpp"

#include "../cfg/Node.hpp"
#include "../cfg/Operand.hpp"
#include "../cfg/OperandList.hpp"
#include "../cfg/AssemblyInstruction.hpp"
#include "../cfg/AssemblyLine.hpp"
#include "../cfg/CSourceLine.hpp"
#include "../cfg/IterationBound.hpp"
#include "../cfg/Start.hpp"

#include "Multicore.hpp"
#include "Optimise.hpp"

#include <sstream>

namespace global {
	extern bool mergeGlobalAccesses;
}

namespace tools {
	int Function::nodesMerged;
	std::map<std::string, std::vector<forec::cfg::Node *> > Function::programCounters;
	
	void Function::clear(void) {
		Function::nodesMerged = 0;
		Function::programCounters.clear();
	}

	void Function::add(const std::string &functionId, std::vector<forec::cfg::Node *> &programCounters) {
		if (Function::programCounters.find(functionId) != Function::programCounters.end()) {
			throw std::string("Function::add: Function \"" + functionId + "\" has already been added.");
		}

		Function::programCounters[functionId] = programCounters;
		
		int globalMemoryMatch = 0;
		for (std::vector<forec::cfg::Node *>::iterator node = programCounters.begin(); node != programCounters.end(); ++node) {
			Function::matchGlobalMemoryAccess(*(*node), globalMemoryMatch);
		}
	}

	// Detect accesses to global memory when the base address has already been computed.
	void Function::matchGlobalMemoryAccess(forec::cfg::Node &node, int &globalMemoryMatch) {
		if (node.isType("AssemblyLine")) {
			forec::cfg::AssemblyLine *assemblyLine = (forec::cfg::AssemblyLine *)&node;
			const std::string instruction = assemblyLine->getInstruction()->getInstruction();
			
			// imm, (add*, (sw|lw)*)*
			bool retry = false;
			do {
				switch (globalMemoryMatch) {
					case (0):	if (instruction.compare("imm") == 0) {
									globalMemoryMatch = 1;
								} else {
									globalMemoryMatch = 0;
								}
								retry = false;
								break;
			
					case (1):	if (instruction.find("add") != std::string::npos) {
									// Try and match more adds.
								} else if (assemblyLine->getHasMemoryAccess()) {
									std::vector<forec::cfg::Node *> operands = ((forec::cfg::OperandList *)assemblyLine->getOperandList())->getOperands();
									if (((forec::cfg::Operand *)operands[2])->getValue().compare("0") == 0) {
										// Third operand is "0".
										assemblyLine->setHasGlobalMemoryAccess(true);

									}
								} else {
									globalMemoryMatch = 0;
									retry = true;
								}
								break;
							
					default:	globalMemoryMatch = 0;
								retry = false;
								break;
				}
			} while (retry);
		} else {
			globalMemoryMatch = 0;
		}
	}

	forec::cfg::Node *Function::getStartingNode(const std::string &functionId) {
		if (Function::programCounters.find(functionId) == Function::programCounters.end()) {
			throw std::string("Function::getStartingNode: Could not find functionId \"" + functionId + "\"");
		}
	
		return Function::programCounters[functionId].front();
	}
	
	void Function::copy(const std::string &functionId, std::vector<forec::cfg::Node *> &functionNodes, const bool merge, const bool mergeBranches) {
		if (Function::programCounters.find(functionId) == Function::programCounters.end()) {
			throw std::string("Function::get: Could not find functionId \"" + functionId + "\"");
		}
		
		// Make copy.
		std::vector<forec::cfg::Node *> functionNodesCopy = Function::programCounters[functionId];
		
		forec::cfg::Start *startNode = new forec::cfg::Start(-1);
		functionNodes.push_back(startNode);
			
		for (std::vector<forec::cfg::Node *>::iterator functionNode = functionNodesCopy.begin(); functionNode != functionNodesCopy.end(); ++functionNode) {
			if ((*functionNode)->isType("AssemblyLine")) {
				forec::cfg::AssemblyLine *node = new forec::cfg::AssemblyLine(*((forec::cfg::AssemblyLine *)*functionNode));
				functionNodes.push_back(node);
			} else if ((*functionNode)->isType("IterationBound")) {
				forec::cfg::IterationBound *node = new forec::cfg::IterationBound(*((forec::cfg::IterationBound *)*functionNode));
				functionNodes.push_back(node);
			}
		}
		
		// Link the nodes.
		for (std::vector<forec::cfg::Node *>::const_iterator programCounter = functionNodes.begin(); programCounter != functionNodes.end(); ++programCounter) {
			(*programCounter)->linkNodes();
		}
		
		// Resolve the destination nodes.
		for (std::vector<forec::cfg::Node *>::const_iterator programCounter = functionNodes.begin(); programCounter != functionNodes.end(); ++programCounter) {
			(*programCounter)->resolveDestinations();
		}

		// Merge nodes.
		if (merge) {
			Function::nodesMerged += Optimise::performMergeNodes(*functionNodes.front(), global::mergeGlobalAccesses);
			
			// Merge branches.
			if (mergeBranches) {
				Optimise::mergeBranches(functionNodes, false);
			}
		}
		
		// Remove unreachable nodes, excluding the start node.
		functionNodes.erase(functionNodes.begin());
		Optimise::removeUnreachableNodes(functionNodes);
		functionNodes.insert(functionNodes.begin(), startNode);
	}
	

	const unsigned int Function::getLatency(Multicore &core, const std::string &functionId) {
		// Copy the function.
		std::vector<forec::cfg::Node *> functionNodes;
		Function::copy(functionId, functionNodes, false, false);
		
		struct Function::Trace startingTrace;
		startingTrace.programCounters.push_back(functionNodes.front()->getNextNodes().front().first);
		startingTrace.state = Function::executing;
		startingTrace.core = new tools::Multicore(core.getId(), core.getElapsedTime());
		
		std::vector<struct Function::Trace> traces;
		traces.push_back(startingTrace);

		bool branchEncountered = false;
		bool terminateEncountered = false;

		// While branches are occuring.
		do {
			branchEncountered = false;
			terminateEncountered = false;

			// For each trace.
			for (std::vector<struct Function::Trace>::iterator trace = traces.begin(); trace != traces.end(); ++trace) {
				// While the trace has not terminated.
				while (trace->state != Function::terminated) {
					// Get the current program counter and its type.
					forec::cfg::Node *currentProgramCounter = trace->programCounters.back();

					// Perform the required action.
					if (currentProgramCounter->isType("AssemblyLine")) {
						// Typical assembly line from the original C-source code.
						const enum Function::State result = Function::assemblyLine(*trace, traces, *currentProgramCounter);

						if (result == Function::branch) {
							// Allow the alternate trace to be traversed.
							branchEncountered = true;
							break;
						} else if (result == Function::terminated) {
							// End the traversal.
							terminateEncountered = true;
							break;
						}
					} else if (currentProgramCounter->isType("Label")) {
						trace->programCounters.push_back(currentProgramCounter->getNextNodes().front().first);
					} else {
						throw std::string("Function::getLatency: " + functionId + ": Unknown type of programCounter: " + currentProgramCounter->getType());
					}
				}

				if (branchEncountered) {
					// Allow an alternate trace to be created and traversed.
					break;
				}
			}
		} while (branchEncountered);

		// Find the trace with the maximum latency.
		std::vector<struct Function::Trace>::const_iterator maximumTrace = traces.begin();
		for (std::vector<struct Function::Trace>::const_iterator trace = traces.begin(); trace != traces.end(); ++trace) {
			if (maximumTrace->core->getElapsedTime() < trace->core->getElapsedTime()) {
				maximumTrace = trace;
			}
		}
		
		return maximumTrace->core->getElapsedTime();
	}

	const enum Function::State Function::assemblyLine(struct Function::Trace &trace, std::vector<struct Function::Trace> &traces, forec::cfg::Node &currentProgramCounter) {
		forec::cfg::AssemblyLine *currentAssemblyLine = (forec::cfg::AssemblyLine *)&currentProgramCounter;
		
		if (currentAssemblyLine->isFunctionReturn()) {
			// End of the function;
			trace.state = Function::terminated;
			return Function::terminated;
		}
		
		std::vector<forec::cfg::Node *> nextProgramCounters;
		std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > > nextNodes = currentAssemblyLine->getNextNodes();
		for (std::vector<std::pair<forec::cfg::Node *, std::pair<int, bool> > >::iterator node = nextNodes.begin(); node != nextNodes.end(); ++node) {
			nextProgramCounters.push_back(node->first);
		}
		
		if (nextProgramCounters.empty()) {
			// Dead end
			std::ostringstream output;
			output << "Function::assemblyLine: No next program counters found for statement at 0x" << std::hex << currentAssemblyLine->getProgramCounter() << '.';
			throw output.str();
		} else if (nextProgramCounters.size() == 1) {
			trace.core->incrementElapsedTime(currentAssemblyLine->getLatency(global::mergeGlobalAccesses, false, trace.core->getElapsedTime()));
		
			// Sequential
			if (currentAssemblyLine->isFunctionCall()) {
				// Traverse the function.
				trace.core->setElapsedTime(Function::getLatency(*trace.core, currentAssemblyLine->getLabel()));
			//	Function::copyProgramCounters(currentAssemblyLine->getLabel(), trace.getProgramCounters());
				trace.programCounters.push_back(nextProgramCounters.front());
				trace.state = Function::executing;

			} else {
				// Computation.
				trace.programCounters.push_back(nextProgramCounters.front());
				trace.state = Function::executing;
			}
		} else {
			trace.core->incrementElapsedTime(currentAssemblyLine->getLatency(global::mergeGlobalAccesses, false, trace.core->getElapsedTime()));
			
			// Branching
			if (currentAssemblyLine->isConditionalBranching()) {
				// Set up the next program counters.
				trace.programCounters.push_back(nextProgramCounters[0]);
				trace.state = Function::branch;
				
				// Create alternate trace.
				struct Function::Trace alternateTrace = Function::copyTrace(trace);
				alternateTrace.programCounters.back() = nextProgramCounters[1];
				traces.push_back(alternateTrace);
				return Function::branch;
			} else {
				std::ostringstream output;
				output << "Function::react: Multiple next program counters found for non-conditional branching statement at 0x" << std::hex << currentAssemblyLine->getProgramCounter() << '.';
				throw output.str();
			}
		}
		
		return Function::executing;
	}

	struct Function::Trace Function::copyTrace(const struct Trace &trace) {
		struct Function::Trace copy;

		for (std::vector<forec::cfg::Node *>::const_iterator programCounter = trace.programCounters.begin(); programCounter != trace.programCounters.end(); ++programCounter) {
			copy.programCounters.push_back(*programCounter);
		}
		
		copy.state = trace.state;
		copy.core = new  tools::Multicore(trace.core->getId(), trace.core->getElapsedTime());
		
		return copy;
	}

	void Function::copyProgramCounters(const std::string &functionId, std::vector<forec::cfg::Node *> &threadProgramCounters) {
		if (Function::programCounters.find(functionId) == Function::programCounters.end()) {
			throw std::string("Function::copyProgramCounters: Could not find functionId \"" + functionId + "\"");
		}
		
		threadProgramCounters.insert(threadProgramCounters.end(), Function::programCounters[functionId].begin(), Function::programCounters[functionId].end());
	}

	void Function::toXml(std::ostream &output) {
		for (std::map<std::string, std::vector<forec::cfg::Node *> >::const_iterator functionId = Function::programCounters.begin(); functionId != Function::programCounters.end(); ++functionId) {
			output << Tab::toString() << "<function label=\"" << functionId->first << "\">" << std::endl;
			Tab::indent();
		
			for (std::vector<forec::cfg::Node *>::const_iterator programCounter = functionId->second.begin(); programCounter != functionId->second.end(); ++programCounter) {
				(*programCounter)->toXml(output);
			}
		
			Tab::dedent();
			output << Tab::toString() << "</function>" << std::endl;
		}
	}

	const std::string Function::toString(void) {
		std::ostringstream output;

		output << "===========================" << std::endl;
		output << "tools::Function::toString()" << std::endl;
		output << "===========================" << std::endl;

		if (!Function::programCounters.empty()) {
			output << "Function starting node:" << std::endl;
			output << "-----------------------" << std::endl;

			for (std::map<std::string, std::vector<forec::cfg::Node *> >::const_iterator functionId = Function::programCounters.begin(); functionId != Function::programCounters.end(); ++functionId) {
				output << '\t' << functionId->first;
				
				for (std::vector<forec::cfg::Node *>::const_iterator programCounter = functionId->second.begin(); programCounter != functionId->second.end(); ++programCounter) {
					if ((*programCounter)->getType().compare("AssemblyLine") == 0) {
						output << ": 0x" << std::hex << ((forec::cfg::AssemblyLine *)*programCounter)->getProgramCounter() << std::dec;
						break;
					}
				}
				
				output << std::endl;
			}

			output << std::endl;
		}

		return output.str();
	}

}
