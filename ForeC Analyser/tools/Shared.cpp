/*
 *  Shared.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 15/04/12.
 *  Copyright 2012 Potential Publishers. All rights reserved.
 *
 */

#include "Shared.hpp"

#include "Function.hpp"
#include "Multicore.hpp"

#include <fstream>
#include <sstream>
#include <string.h>

namespace tools {
	std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, std::pair<int, std::string> > > > > Shared::variablesToCombine;
	std::map<std::string, std::map<std::string, int> > Shared::parIndexes;
	
	void Shared::clear(void) {
		Shared::variablesToCombine.clear();
		Shared::parIndexes.clear();
	}

	void Shared::loadInformation(const rapidxml::xml_node<> &information) {
		// Get shared variables.
		rapidxml::xml_node<> *shared = information.first_node("shared");
		for (rapidxml::xml_node<> *threadScope = shared->first_node("threadScope"); threadScope; threadScope = threadScope->next_sibling("threadScope")) {		
			rapidxml::xml_attribute<> *threadId = threadScope->first_attribute("id");
			
			int index = 0;
			for (rapidxml::xml_node<> *par = threadScope->first_node("par"); par; par = par->next_sibling("par")) {
				rapidxml::xml_attribute<> *parId = par->first_attribute("id");
			
				for (rapidxml::xml_node<> *variable = par->first_node("variable"); variable; variable = variable->next_sibling("variable")) {
					rapidxml::xml_attribute<> *variableId = variable->first_attribute("id");
					rapidxml::xml_attribute<> *defines = variable->first_attribute("defines");
					rapidxml::xml_attribute<> *combine = variable->first_attribute("combine");
					
					int definesValue;
					std::istringstream input(defines->value());
					input >> std::dec >> definesValue;
					std::pair<std::string, std::pair<int, std::string> > variableInfo(variableId->value(), std::pair<int, std::string>(definesValue, ""));
					if (combine != NULL) {
						variableInfo.second.second = combine->value();
					}
					
					Shared::variablesToCombine[threadId->value()][parId->value()].push_back(variableInfo);
				}
				
				parIndexes[threadId->value()][parId->value()] = index;
				index++;
			}
		}
	}
	
	const std::vector<std::pair<std::string, std::pair<int, std::string> > > Shared::getVariablesToCombine(const std::string &threadScope, const std::string &parId) {
		if (Shared::variablesToCombine.find(threadScope) != Shared::variablesToCombine.end()) {
			if (Shared::variablesToCombine[threadScope].find(parId) != Shared::variablesToCombine[threadScope].end()) {
				return Shared::variablesToCombine[threadScope][parId];
			}
		}
		
		return std::vector<std::pair<std::string, std::pair<int, std::string> > >();
	}

	const int Shared::getParIndex(const std::string &threadScope, const std::string &parId) {
		if (Shared::parIndexes.find(threadScope) == Shared::parIndexes.end()) {
			throw std::string("Shared::getParIndex: threadScope \"" + threadScope + "\" not found.");
		}
		
		if (Shared::parIndexes[threadScope].find(parId) == Shared::parIndexes[threadScope].end()) {
			throw std::string("Shared::getParIndex: parId \"" + parId + "\" not found.");
		}
		
		return Shared::parIndexes[threadScope][parId];
	}
	
	const int Shared::getParIndexesSize(const std::string &threadScope) {
		if (Shared::parIndexes.find(threadScope) == Shared::parIndexes.end()) {
			return 0;
		}
		
		return parIndexes[threadScope].size();
	}

	const unsigned int Shared::combineLatency(Multicore &core, const std::string &function) {
		return Function::getLatency(core, function);
	}

	const std::string Shared::toString(void) {
		std::ostringstream output;

		output << "=========================" << std::endl;
		output << "tools::Shared::toString()" << std::endl;
		output << "=========================" << std::endl;

		if (!Shared::variablesToCombine.empty()) {
			output << "Shared variables usage:" << std::endl;
			output << "-----------------------" << std::endl;
			
			for (std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, std::pair<int, std::string> > > > >::const_iterator threadScope = Shared::variablesToCombine.begin(); threadScope != Shared::variablesToCombine.end(); ++threadScope) {
				output << "\tThread scope: " << threadScope->first << "__thread" << std::endl;
				
				for (std::map<std::string, std::vector<std::pair<std::string, std::pair<int, std::string> > > >::const_iterator parId = threadScope->second.begin(); parId != threadScope->second.end(); ++parId) {
					output << "\t\tpar" << parId->first << ':' << std::endl;
				
					for (std::vector<std::pair<std::string, std::pair<int, std::string> > >::const_iterator variable = parId->second.begin(); variable != parId->second.end(); ++variable) {
						output << "\t\t* " << variable->first << " (defines = " << variable->second.first;
						if (variable->second.second.compare("") != 0) {
							output << ", combine = " << variable->second.second;
						}
						output << ')' << std::endl;
					}
					output << std::endl;
				}
			}
		}
		
		if (!Shared::parIndexes.empty()) {
			output << "Threads with par(...) indexes:" << std::endl;
			output << "------------------------------" << std::endl;
			
			for (std::map<std::string, std::map<std::string, int> >::const_iterator threadScope = Shared::parIndexes.begin(); threadScope != parIndexes.end(); ++threadScope) {
				output << "\tThread scope: " << threadScope->first << "__thread" << std::endl;
				
				for (std::map<std::string, int>::const_iterator parId = threadScope->second.begin(); parId != threadScope->second.end(); ++parId) {
					output << "\t " << parId->second << " par" << parId->first << std::endl;
				}
				output << std::endl;
			}
			output << std::endl;
		}

		return output.str();
	}

}

