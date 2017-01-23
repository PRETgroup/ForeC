/*
 *  Costing.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 10/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Costing.hpp"

#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>

namespace global {
	extern std::string architecture;
}

namespace tools {
	// Initialise static variables
	const std::string Costing::instructionFilePath = "tools/LatenciesInstruction_";
	const std::string Costing::memoryFilePath = "tools/LatenciesMemory_";
	
	std::map<std::string, int> Costing::instructionLatencies;
	std::map<std::string, int> Costing::memoryLatencies;

	int Costing::coreCount;

	void Costing::clear(void) {
		Costing::instructionLatencies.clear();
		Costing::memoryLatencies.clear();
	}

	void Costing::setCoreCount(const int count) {
		Costing::coreCount = count;
	}
	
	void Costing::readInstructionLatencies(void) {
		const std::string forecaPath = getenv("FOREC_ANALYSER_PATH");
		if (forecaPath.compare("") == 0) {
			throw std::string("Check your environment for FOREC_ANALYSER_PATH: \"" + forecaPath + "\"");
		}

		std::string filePath = forecaPath + Costing::instructionFilePath + global::architecture + ".txt";
		std::ifstream inFile(filePath.c_str());
		if (!inFile.good()) {
			throw std::string("Costing::readInstructionLatencies: Unable to open file \"" + filePath + "\".");
		}

		std::string instruction;
		int latency;
		
		while (!inFile.eof()) {
			inFile >> instruction >> latency;
			Costing::instructionLatencies[instruction] = latency;
		}
	}

	void Costing::readMemoryLatencies(void) {
		const std::string forecaPath = getenv("FOREC_ANALYSER_PATH");
		if (forecaPath.compare("") == 0) {
			throw std::string("Check your environment for FOREC_ANALYSER_PATH: \"" + forecaPath + "\"");
		}

		std::string filePath = forecaPath + Costing::memoryFilePath + global::architecture + ".txt";
		std::ifstream inFile(filePath.c_str());
		if (!inFile.good()) {
			throw std::string("Costing::readMemoryLatencies: Unable to open file \"" + filePath + "\".");
		}

		std::string parameter;
		int latency;
		
		while (!inFile.eof()) {
			inFile >> parameter >> latency;
			Costing::memoryLatencies[parameter] = latency;
		}
	}
	
	
	const int Costing::getInstructionLatency(const std::string &instruction) {
		if (Costing::instructionLatencies.find(instruction) != Costing::instructionLatencies.end()) {
			return Costing::instructionLatencies[instruction];
		}
		
		throw std::string("Costing::getInstructionLatency: Could not find instruction " + instruction);
	}

	const int Costing::getMemoryLatency(const char accessType) {
		if (accessType == 'l') {
			return Costing::memoryLatencies["globalLoad"];
		} else if (accessType == 's') {
			return Costing::memoryLatencies["globalStore"];
		} else {
			std::ostringstream output;
			output << "Costing::getMemoryLatency: Unrecognised access type: " << accessType;
			throw output.str();
		}
		
		return -1;
	}

	const int Costing::getMaxAccessLatency(const bool isGlobalMemoryAccess, const char accessType) {
		int latency = 0;
		
		if (global::architecture.compare("microblaze") == 0) {
			if (isGlobalMemoryAccess) {
				// Global memory
				if (Costing::coreCount == 1) {
					return Costing::getMemoryLatency(accessType);
				}
				
				const int cycleSize = Costing::coreCount * Costing::memoryLatencies["slot"];
				latency = cycleSize - Costing::memoryLatencies["slot"] + Costing::getMemoryLatency(accessType) - 1;
				latency += Costing::getMemoryLatency(accessType);
			} else {
				// Local memory
				latency = Costing::memoryLatencies["local"];
			}
		} else if (global::architecture.compare("ptarm") == 0) {
			if (isGlobalMemoryAccess) {
				// Global memory
				latency = Costing::getMemoryLatency(accessType);
			} else {
				// Local memory
				latency = Costing::memoryLatencies["local"];
			}
		}
		
		return latency;
	}


	const int Costing::getAccessLatency(const bool isGlobalMemoryAccess, const int elapsedTime, const char accessType) {
		int latency = 0;
		
		if (global::architecture.compare("microblaze") == 0) {
			if (isGlobalMemoryAccess) {
				// Global memory
				if (Costing::coreCount == 1) {
					return Costing::getMemoryLatency(accessType);
				}
				
				const int cycleSize = Costing::coreCount * Costing::memoryLatencies["slot"];
				const int remainder = (elapsedTime % cycleSize);
				
				// Assume the cores are given the first slot of the schedule.
				// This assumption has been made by assigning the worst-case bus latency to each core at the start of the reaction.
				if ((remainder + Costing::getMemoryLatency(accessType)) <= Costing::memoryLatencies["slot"]) {
					latency = Costing::getMemoryLatency(accessType);
				} else {
					latency = cycleSize - remainder + Costing::getMemoryLatency(accessType);
				}
			} else {
				// Local memory
				latency = Costing::memoryLatencies["local"];
			}
		} else if (global::architecture.compare("ptarm") == 0) {
			if (isGlobalMemoryAccess) {
				// Global memory
				latency = Costing::getMemoryLatency(accessType);
			} else {
				// Local memory
				latency = Costing::memoryLatencies["local"];
			}
		}
		
		return latency;
	}
	
	const int Costing::getBusCycle(void) {
		return Costing::coreCount * Costing::memoryLatencies["slot"];
	}

	const bool Costing::isGlobalMemoryAccess(const std::string &operand1) {
		return operand1.compare("r0") == 0;
	}

	const std::string Costing::toString(void) {
		std::ostringstream output;

		output << "====================================" << std::endl;
		output << "tools::Costing::toString()" << std::endl;
		output << "====================================" << std::endl;

		output << "Memory access costs:" << std::endl;
		output << "--------------------" << std::endl;
		for (std::map<std::string, int>::const_iterator parameter = Costing::memoryLatencies.begin(); parameter != Costing::memoryLatencies.end(); ++parameter) {
			output << "* " << parameter->first << ": " << parameter->second << std::endl;
		}
		output << std::endl;
		
		return output.str();
	}

}
