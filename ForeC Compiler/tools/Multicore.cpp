/*
 *  Multicore.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Multicore.hpp"

namespace tools {
	const std::string Multicore::threadSuffix = "__thread";
	std::string Multicore::architecture;
	std::string Multicore::fileName;
	std::map<std::string, std::string> Multicore::allocations;
	std::set<std::string> Multicore::coreIds;
	std::map<std::string, std::map<std::string, int> > Multicore::parCoresPriority;

	void Multicore::clear(void) {
		Multicore::allocations.clear();
		Multicore::coreIds.clear();
		Multicore::parCoresPriority.clear();
	}

	void Multicore::setAllocations(const std::string &fileName) {
		std::ifstream inFile(fileName.c_str());
		if (!inFile.good()) {
			throw std::string("Multicore::setAllocations: Unable to open file \"" + fileName + "\".");
		}
		
		Multicore::fileName = fileName.substr(0, fileName.find(".foreh"));

		std::string coreId;
		std::string line;
		bool isArchitecture = false;
		while(std::getline(inFile, line)) {
			// Remove return carriage.
			if (line.find('\r') != std::string::npos) {
				line.erase(line.find('\r'));
			}

			if (line.empty()) {
				continue;
			}

			// Determine header and values.
			if (*line.rbegin() == ':') {
				line.erase(line.end() - 1);
				isArchitecture = line.compare("architecture") == 0;
				if (!isArchitecture) {
					coreId = line;
				}
			} else {
				if (isArchitecture) {
					Multicore::architecture = line;
				} else {
					Multicore::setAllocation(line, coreId);
				}
			}
		}
	}

	void Multicore::setAllocation(const std::string &threadId, const std::string &coreId) {
		Multicore::allocations[threadId] = coreId;
		Multicore::coreIds.insert(coreId);
	}

	void Multicore::automaticallyAllocate(const std::set<std::string> &threads) {

	}

	const std::map<std::string, std::string> Multicore::getAllocations(void) {
		return Multicore::allocations;
	}

	const std::set<std::string> Multicore::getAllocatedThreads(void) {
		std::set<std::string> threads;

		for (std::map<std::string, std::string>::iterator allocation = Multicore::allocations.begin(); allocation != Multicore::allocations.end(); ++allocation) {
			threads.insert(allocation->first);
		}

		return threads;
	}


	const std::string Multicore::getArchitecture(void) {
		if (Multicore::architecture.size() == 0) {
			throw std::string("Multicore::getArchitecture: Architecture is unspecified.");
		}
		return Multicore::architecture;
	}

	const bool Multicore::isArchitecture(const std::string &architecture) {
		return Multicore::architecture.compare(architecture) == 0;
	}


	void Multicore::setParCorePriority(const std::string &threadScope, const std::string &coreId, const bool isMaster) {
		if (threadScope.compare("main") != 0 && Multicore::parCoresPriority[threadScope].find(coreId) == Multicore::parCoresPriority[threadScope].end()) {
			if (isMaster) {
				// 'Decrease' priority of existing cores.
				for (std::map<std::string, int>::iterator core = Multicore::parCoresPriority[threadScope].begin(); core!= Multicore::parCoresPriority[threadScope].end(); ++core) {
					core->second++;
				}
				
				// Set priority to highest.
				Multicore::parCoresPriority[threadScope][coreId] = 0;
			} else {
				// Assign priority based on the number of existing cores.
				int size = Multicore::parCoresPriority[threadScope].size();
				Multicore::parCoresPriority[threadScope][coreId] = size;
			}
		}
	}

	const std::map<std::string, std::map<std::string, int> > Multicore::getParCoresPriority(void) {
		return Multicore::parCoresPriority;
	}

	const std::map<std::string, int> Multicore::getParCoresPriority(const std::string &threadScope) {
		return Multicore::parCoresPriority[threadScope];
	}

	const int Multicore::getParCorePriority(const std::string &threadScope, const std::string &coreId) {
		if (Multicore::parCoresPriority[threadScope].find(coreId) == Multicore::parCoresPriority[threadScope].end()) {
			throw std::string("Multicore::getParCorePriority: Could not find priority for core" + coreId + " in thread \"" + threadScope + "\".");
		}
		return Multicore::parCoresPriority[threadScope][coreId];
	}

	const std::string Multicore::getCoreId(const std::string &threadName) {
		std::map<std::string, std::string>::iterator coreIdFound = Multicore::allocations.find(threadName);
		if (coreIdFound == Multicore::allocations.end()) {
			throw std::string("Multicore::getCoreId: Could not find coreId for thread \"" + threadName + "\".");
		}

		return coreIdFound->second;
	}

	const std::string Multicore::getMasterCoreId() {
		// Master core of the system.
		return Multicore::getCoreId("main");
	}

	const bool Multicore::isMasterCoreId(const std::string &coreId) {
		return Multicore::getCoreId("main").compare(coreId) == 0;
	}

	const bool Multicore::isMasterCoreId(const std::string &threadScope, const std::string &coreId) {
		return Multicore::getCoreId(threadScope).compare(coreId) == 0;
	}

	const std::set<std::string> Multicore::getSlaveCoreIds(void) {
		// Slave cores of the system.
		std::set<std::string> slaveCoreIds;
		slaveCoreIds.insert(Multicore::coreIds.begin(), Multicore::coreIds.end());
		slaveCoreIds.erase(Multicore::getCoreId("main"));

		return slaveCoreIds;
	}

	const std::set<std::string> Multicore::getCoreIds(void) {
		return Multicore::coreIds;
	}

	const std::set<std::string> Multicore::getCoreIds(const std::vector<std::string> &threads) {
		std::set<std::string> coreIds;
		for (std::vector<std::string>::const_iterator thread = threads.begin(); thread != threads.end(); ++thread) {
			coreIds.insert(Multicore::getCoreId(*thread));
		}

		return coreIds;
	}


	const std::string Multicore::toString(void) {
		std::ostringstream output;

		output << "============================" << std::endl;
		output << "tools::Multicore::toString()" << std::endl;
		output << "============================" << std::endl;

		output << "Multicore architecture:" << std::endl;
		output << "-----------------------" << std::endl;
		output << '\t' << Multicore::architecture << std::endl;
		output << std::endl;

		output << "Multicore allocations:" << std::endl;
		output << "----------------------" << std::endl;
		output << "\tCore\tThread" << std::endl;
		output << "\t----\t------" << std::endl;
		for (std::map<std::string, std::string>::const_iterator allocation = Multicore::allocations.begin(); allocation != Multicore::allocations.end(); ++allocation) {
			output << '\t' << allocation->second << "\t\t" << allocation->first << Multicore::threadSuffix << std::endl;
		}
		output << std::endl;

		if (Multicore::parCoresPriority.size() > 0) {
			output << "Priority of cores for each par(...) in threads:" << std::endl;
			output << "-----------------------------------------------" << std::endl;
			for (std::map<std::string, std::map<std::string, int> >::const_iterator threadScope = Multicore::parCoresPriority.begin(); threadScope != Multicore::parCoresPriority.end(); ++threadScope) {

				output << '\t' << threadScope->first << ':' << std::endl;
				for (std::map<std::string, int>::const_iterator corePriority = threadScope->second.begin(); corePriority != threadScope->second.end(); ++corePriority) {
					output << "\t* core" << corePriority->first << '(' << corePriority->second << ')' << std::endl;
				}
				output << std::endl;
			}
			output << std::endl;
		}

		return output.str();
	}
	
	const std::string Multicore::toXml(const std::string &indent) {
		std::map<std::string, std::set<std::string> > allocationsByCore;
		
		for (std::map<std::string, std::string>::const_iterator allocation = Multicore::allocations.begin(); allocation != Multicore::allocations.end(); ++allocation) {
			allocationsByCore[allocation->second].insert(allocation->first);
		}

		std::ostringstream output;

		output << indent << "<!-- Header filename (Multicore.cpp::toXml). -->" << std::endl;
		output << indent << "<filename elf=\"" << Multicore::fileName << "\" />" << std::endl;
		output << indent << "<architecture model=\"" << Multicore::getArchitecture() << "\" />" << std::endl;

		output << indent << "<!-- Allocation of threads for each core (Multicore.cpp::toXml). -->" << std::endl;
		output << indent << "<allocations>" << std::endl;
		for (std::map<std::string, std::set<std::string> >::const_iterator coreId = allocationsByCore.begin(); coreId != allocationsByCore.end(); ++coreId) {
			output << indent << "\t<core id=\"" << coreId->first << "\">" << std::endl;
			for (std::set<std::string>::const_iterator threadId = coreId->second.begin(); threadId != coreId->second.end(); ++threadId) {
				output << indent << "\t\t<thread id=\"" << *threadId << "\" />" << std::endl;
			}
			output << indent << "\t</core>" << std::endl;
		}
		output << indent << "</allocations>" << std::endl;

		return output.str();
	}
}

