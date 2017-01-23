/*
 *  Mutex.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Mutex.hpp"

namespace tools {
	const unsigned int Mutex::maxCount = 32;
	unsigned int Mutex::currentOffset;
	std::map<std::string, std::map<std::string, unsigned int> > Mutex::parCoreInformation;

	void Mutex::clear(void) {
		Mutex::currentOffset = Mutex::maxCount;
		Mutex::parCoreInformation.clear();
	}
	
	void Mutex::setParCoresMask(std::map<std::string, std::map<std::string, int> > &parCoresPriority) {
		for (std::map<std::string, std::map<std::string, int> >::iterator threadScope = parCoresPriority.begin(); threadScope != parCoresPriority.end(); ++threadScope) {
			// Number of participating cores within a thread.
			Mutex::parCoreInformation[threadScope->first]["coreCount"] = threadScope->second.size();

			if (Mutex::currentOffset < 1) {
				throw std::string("Mutex::setParCoresMask: Not enough mutex positions available.");
			}

			// Starting bit position for a new mutex.
			Mutex::currentOffset -= 1;
			Mutex::parCoreInformation[threadScope->first]["offset"] = Mutex::currentOffset;
			
			// Indicate bits reserved for the mutex
			Mutex::parCoreInformation[threadScope->first]["baseMask"] = 1 << Mutex::parCoreInformation[threadScope->first]["offset"];
		}
	}


	const std::map<std::string, unsigned int> Mutex::getInformation(const std::string &threadScope) {
		return Mutex::parCoreInformation[threadScope];
	}


	const unsigned int Mutex::getCoreCount(const std::string &threadScope) {
		return Mutex::parCoreInformation[threadScope]["coreCount"];
	}

	const unsigned int Mutex::getOffset(const std::string &threadScope) {
		return Mutex::parCoreInformation[threadScope]["offset"];
	}

	const unsigned int Mutex::getBaseMask(const std::string &threadScope) {
		return Mutex::parCoreInformation[threadScope]["baseMask"];
	}
			
	const std::set<std::string> Mutex::getThreadScopes(void) {
		std::set<std::string> threadScopes;
		for (std::map<std::string, std::map<std::string, unsigned int> >::iterator threadScope = Mutex::parCoreInformation.begin(); threadScope != Mutex::parCoreInformation.end(); ++threadScope) {
			threadScopes.insert(threadScope->first);
		}
		return threadScopes;
	}
	
	const std::string Mutex::toString(void) {
		std::ostringstream output;
		
		output << "========================" << std::endl;
		output << "tools::Mutex::toString()" << std::endl;
		output << "========================" << std::endl;
		
		
		output << "Mutex information:" << std::endl;
		output << "------------------" << std::endl;
		for (std::map<std::string, std::map<std::string, unsigned int> >::iterator threadScope = Mutex::parCoreInformation.begin(); threadScope != Mutex::parCoreInformation.end(); ++threadScope) {
			output << "\tThread " << threadScope->first << ':' << std::endl;
			
			for (std::map<std::string, unsigned int>::const_iterator information = threadScope->second.begin(); information != threadScope->second.end(); ++information) {
				output << "\t\t";
				output.width(10);
				output << std::left << information->first << ':';
				if (information->first.compare("coreCount") == 0 || information->first.compare("offset") == 0) {
					output << information->second << std::endl;
				} else {
					output << Mutex::binaryFormat(information->second) << std::endl;
				}
			}
			
			output << std::endl;
		}
		
		return output.str();
	}


	const std::string Mutex::binaryFormat(const unsigned int value) {		
		const std::bitset<std::numeric_limits<unsigned int>::digits> binary(value);
		return binary.to_string();
	}

}
