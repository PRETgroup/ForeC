/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#include <iostream>
#include <iomanip>
#include <ostream>
#include <cstring>
#include <time.h>
#include <sys/time.h>

#include "File.hpp"

#include "cfg/Root.hpp"
#include "cfg/AssemblyLine.hpp"

#include "maxplus/MaxPlus.hpp"
#include "maxplus/Reaction.hpp"

#include "reachability/Reachability.hpp"
#include "reachability/Reaction.hpp"

#include "tools/Link.hpp"
#include "tools/Costing.hpp"
#include "tools/Function.hpp"
#include "tools/Multicore.hpp"
#include "tools/ObjectDump.hpp"
#include "tools/Scheduler.hpp"
#include "tools/Shared.hpp"
#include "tools/Threading.hpp"

#include "tools/rapidxml.hpp"

const std::string version = "Version: 0.8 (5 October 2014)";
std::ofstream analysisFile;
std::ofstream traceFile;

namespace global {
	std::string architecture = "undefined";
	std::string analysisApproach = "undefined";
	int traceLevel = 0;
	bool ccfgOnly = false;
	bool uppaalOnly = false;
	bool merge = false;
	bool mergeBranches = false;
	bool mergeGlobalAccesses = false;
	bool withInterleaving = false;
}

void createObjectDump(const rapidxml::xml_node<> &information, const std::string &fileName);
void parseObjectDump(const std::string &fileName, forec::cfg::Root &cfgRoot);
void informationInput(const rapidxml::xml_node<> &information);

void linkNodes(forec::cfg::Root &cfgRoot);
void mergeNodes(forec::cfg::Root &cfgRoot);
void performMaxPlus(void);
void performReachability(void);

void outputCfg(const std::string &fileName, forec::cfg::Root &cfgRoot);
void outputUppaal(const std::string &fileName, forec::cfg::Root &cfgRoot);


int main(const int argc, const char *argv[]) {
	std::string fileName;
	std::string sourceFileName;
	std::string informationFileName;
	std::string analysisFileName;


	std::cout << std::endl;
	std::cout << "ForeC Analyser" << std::endl;
	std::cout << version << std::endl;
	std::cout << "-------------------------------" << std::endl;
	for (int i = 0; i < argc; ++i) {
		std::cout << argv[i] << " ";
	}
	std::cout << std::endl;

	time_t rawtime;
	time (&rawtime);
	std::cout << "Started at: " << ctime(&rawtime);
	std::cout << "-------------------------------" << std::endl;

	// Check argument inputs.
	bool unexpectedArguments = false;
	for (int i = 1; i < argc; ++i) {
		// Check the options before checking the filenames.
		if (std::string(argv[i]).compare("-v") == 0) {
			std::cout << version << std::endl << std::endl;
			return EXIT_SUCCESS;
		} else if (std::string(argv[i]).substr(0,6).compare("-merge") == 0) {
			global::merge = true;
			
			std::string option = std::string(argv[i]).substr(6);
			if (option.compare("-b") == 0) {
				global::mergeBranches = true;
			} else if (option.compare("-g") == 0) {
				global::mergeGlobalAccesses = true;
			} else if (option.compare("-bg") == 0) {
				global::mergeBranches = true;
				global::mergeGlobalAccesses = true;
			}
		} else if (std::string(argv[i]).compare("-ccfg") == 0) {
			global::ccfgOnly = true;
		} else if (std::string(argv[i]).compare("-uppaal") == 0) {
			global::uppaalOnly = true;
		} else if (std::string(argv[i]).substr(0,8).compare("-maxplus") == 0 || std::string(argv[i]).compare("-reachability") == 0) {
			global::analysisApproach = std::string(argv[i]);
			if (global::analysisApproach.compare("-maxplus-i") == 0) {
				global::withInterleaving = true;
			}
		} else if (std::string(argv[i]).substr(0,2).compare("-t") == 0) {
			std::istringstream(std::string(argv[i]).substr(2)) >> global::traceLevel;
		} else {
			if (sourceFileName.empty()) {
				sourceFileName = std::string(argv[i]);
			} else if (informationFileName.empty()) {
				informationFileName = std::string(argv[i]);
			} else {
				unexpectedArguments = true;
			}
		}
	}

	if (unexpectedArguments || sourceFileName.empty() || informationFileName.empty() || global::analysisApproach.compare("undefined") == 0) {
		std::cerr << "Usage: foreca [-option] <SOURCE FILENAME> <INFORMATION FILENAME>" << std::endl
				  << "  Option can be -v (version)," << std::endl
				  << "  or -[merge, merge-b, merge-g, merge-bg] with" << std::endl
				  << "     -ccfg, or" << std::endl
				  << "     -uppaal, or" << std::endl
				  << "     -<reachability, maxplus, maxplus-i>" << std::endl
				  << "     -t[1, 2, 3 (trace)]" << std::endl << std::endl;
		return EXIT_FAILURE;
	}

	// Open analysis results file.
	analysisFile.open("analysis.txt");
	analysisFile << "ForeC Analyser" << std::endl;
	analysisFile << version << std::endl;
	analysisFile << "Analysis output" << std::endl;
	analysisFile << "-------------------------------" << std::endl << std::endl;

	// Output the chosen analysis options.
	if (global::ccfgOnly) {
		analysisFile << "CCFG output only" << std::endl;
	} else if (global::uppaalOnly) {
		analysisFile << "UPPAAL output only" << std::endl;
	} else {
		analysisFile << "Analysis approach: " << global::analysisApproach << std::endl;
		analysisFile << "Trace level: " << global::traceLevel << std::endl;
	}
	
	analysisFile << "Merge: " << (global::merge ? "Yes" : "No") << std::endl;
	analysisFile << "Merge branches: " << (global::mergeBranches ? "Yes" : "No") << std::endl;
	analysisFile << "Merge global memory accesses: " << (global::mergeGlobalAccesses ? "Yes" : "No") << std::endl;
	analysisFile << "MaxPlus with thread interleaving: " << (global::withInterleaving ? "Yes" : "No") << std::endl;
	analysisFile << std::endl;

	// Starting node for the reconstructed control flow graph.
	forec::cfg::Root cfgRoot;

	// Initialise tools
	forec::reachability::Reachability::clear();
	tools::Link::clear();
	tools::Function::clear();
	tools::Multicore::clear();
	tools::Scheduler::clear();
	tools::Threading::clear(global::traceLevel > 0);

	// Try and open the object and scheduling information files.
	try {		
		if (informationFileName.find(".xml") == std::string::npos) {
			throw std::string("ForeC compiler generated information xml-file expected but received \"" + informationFileName + "\" instead.");
		}
		
		// Read in the information file.
		std::ifstream inFile(informationFileName.c_str());
		if (!inFile.good()) {
			throw std::string("Unable to open the information file \"" + fileName + "\".");
		}

		std::ostringstream informationRaw;
		std::string line;
		while(std::getline(inFile, line)) {
			informationRaw <<line << std::endl;
		}

		char *informationString = new char[informationRaw.str().size() + 1];
		strcpy(informationString, informationRaw.str().c_str());

		rapidxml::xml_document<> doc;
		doc.parse<0>(informationString);
		rapidxml::xml_node<> *information = doc.first_node("information");

		informationInput(*information);
		
		// Clear architecture model.
		tools::Costing::clear();
		tools::Costing::readInstructionLatencies();
		tools::Costing::readMemoryLatencies();
		analysisFile << tools::Costing::toString();

		// Generate object dump file.
		if (sourceFileName.find(".c") != std::string::npos) {
			fileName = sourceFileName.substr(0, sourceFileName.find(".c"));
			createObjectDump(*information, fileName);
		} else if ((sourceFileName.find(".dump") != std::string::npos)) {		
			fileName = sourceFileName.substr(0, sourceFileName.find(".dump"));
			std::cout << "Skipping object dump creation." << std::endl;
			analysisFile << "Skipped object dump creation." << std::endl;
		} else {
			std::ostringstream error;
			error << "ForeC generated c-file or object dump file expected but received" << std::endl;
			error << "    \"" << sourceFileName << "\"" << std::endl;
			error << "instead.";
			throw error.str();
		}
		
		// Parse the object dump.
		parseObjectDump(fileName, cfgRoot);
		
		std::cout << std::endl;

		// Generate control-flow of the program.
		linkNodes(cfgRoot);
		mergeNodes(cfgRoot);
		
		std::cout << std::endl;
		
		// Output the intermediate format.
		outputCfg(fileName, cfgRoot);
		
		if (global::uppaalOnly) {
			// Output the UPPAAL xml.
			outputUppaal(fileName, cfgRoot);	
		}
		
		std::cout << std::endl;
		
		if (!global::ccfgOnly && !global::uppaalOnly) {
			// Perform the chosen timing analysis.
			std::cout << "Preparing to perform " << global::analysisApproach << std::endl;
			analysisFile << "Preparing to perform " << global::analysisApproach << std::endl;
			if (global::analysisApproach.compare("-reachability") == 0) {
				performReachability();
			} else if (global::analysisApproach.compare("-maxplus") == 0) {
				performMaxPlus();
			} else if (global::analysisApproach.compare("-maxplus-i") == 0) {
				performMaxPlus();
			} else {
				throw std::string("Unknown timing analysis approach chosen.");
			}
		}
	} catch (std::string error) {
		std::cerr << std::endl;
		std::cerr << "Error:" << std::endl << error << std::endl << std::endl;

		analysisFile << std::endl;
		analysisFile << "Error: " << std::endl << error << std::endl;
		analysisFile.close();

		return EXIT_FAILURE;
	}

	std::cout << std::endl;
	std::cout << "Analysis success" << std::endl;
	std::cout << std::endl;
	analysisFile.close();

	return EXIT_SUCCESS;
}

void informationInput(const rapidxml::xml_node<> &information) {
	std::cout << "Parsing information ... ";
	
	tools::Multicore::loadInformation(information);
	analysisFile << "Architecture: " << global::architecture << std::endl << std::endl;
	analysisFile << tools::Multicore::staticToString();

	tools::Threading::loadInformation(information);
	analysisFile << tools::Threading::staticToString();

	tools::Shared::loadInformation(information);
	analysisFile << tools::Shared::toString();
	
	tools::Costing::setCoreCount(tools::Multicore::getAllCoreIds().size());
	
	std::cout << "done" << std::endl;
}

void createObjectDump(const rapidxml::xml_node<> &information, const std::string &fileName) {
	std::cout << "Creating object dump ... ";
	
	std::ostringstream elfFileName;
	elfFileName << information.first_node("filename")->first_attribute("elf")->value() << ".elf";
	tools::ObjectDump::make(fileName + ".c", fileName + "_expanded.c", elfFileName.str(), fileName + ".dump");

	analysisFile << "ForeC generated file: " << fileName << ".c" << std::endl;
	analysisFile << "ForeC generated file after macro expansion: " << fileName << "_expanded.c" << std::endl;
	analysisFile << "Compiled ELF: " << elfFileName.str() << std::endl;
	analysisFile << "Generated dump file: " << fileName << ".dump" << std::endl;
	
	std::cout << "done" << std::endl;
	std::cout << "Compiled ELF: " << elfFileName.str() << std::endl;
}

void parseObjectDump(const std::string &fileName, forec::cfg::Root &cfgRoot) {
	std::cout << "Parsing object dump ... ";

	forec::File::read(fileName + ".dump", global::architecture, cfgRoot);
	cfgRoot.addLastFunction();
	analysisFile << "Parsed object dump: " << fileName << ".dump" << std::endl << std::endl;
	
	analysisFile << tools::Function::toString();

	std::cout << "done" << std::endl;
}

void linkNodes(forec::cfg::Root &cfgRoot) {
	std::cout << "Linking nodes together ... ";
	std::cout.flush();
	cfgRoot.linkNodes();
	cfgRoot.resolveDestinations();
	std::cout << "done" << std::endl;
	
	std::cout << "Inlining functions ... ";
	std::cout.flush();
	cfgRoot.inlineFunctions();
	std::cout << "done" << std::endl;
	
	if (tools::Link::hasUnresolvedBranchDestinations()) {
		analysisFile << std::endl << "Unresolved branch destinations exists" << std::endl << std::endl;
		std::cout << std::endl << "Warning: Unresolved branch destinations exists." << std::endl << std::endl;
	}
	
	if (tools::Link::hasUnresolvedAbortDestinations()) {
		analysisFile << std::endl << "Unresolved abort destinations exists." << std::endl << std::endl;
		std::cout << std::endl << "Warning: Unresolved abort destinations exists." << std::endl << std::endl;
	}

	analysisFile << tools::Link::toString();
}

void mergeNodes(forec::cfg::Root &cfgRoot) {
	if (global::merge) {
		std::cout << "Merging pure computation nodes together ... ";
		std::cout.flush();
		std::map<std::string, int> results;
		cfgRoot.mergeNodes(global::mergeGlobalAccesses, results);

		analysisFile << "==========" << std::endl;
		analysisFile << "mergeNodes" << std::endl;
		analysisFile << "==========" << std::endl;

		if (!results.empty()) {
			for (std::map<std::string, int>::const_iterator result = results.begin(); result != results.end(); ++result) {
				analysisFile << '\t' << result->first << ": " << result->second << std::endl;
			}
			analysisFile << std::endl;
		}
		std::cout << "done" << std::endl;

		std::cout << "Removing unreachable nodes ... ";
		cfgRoot.removeUnreachableNodes();
		std::cout << "done" << std::endl;

		if (global::mergeBranches) {
			std::cout << "Merging branches together ... ";

			cfgRoot.mergeBranches();
			std::cout << "done" << std::endl;
		}
	}
}

void outputCfg(const std::string &fileName, forec::cfg::Root &cfgRoot) {
	// Generate XML control-flow graph
	std::ostringstream xmlOutput;
	xmlOutput << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>" << std::endl;
	cfgRoot.toXml(xmlOutput);

	std::cout << "Outputting XML control-flow graph: " << fileName << ".xml ... ";
	forec::File::write(fileName + ".xml", xmlOutput);
	std::cout << "done" << std::endl;

	// Generate flat control-flow graph
	std::ostringstream txtOutput;
	txtOutput << cfgRoot;

	std::cout << "Outputting TXT control-flow graph: " << fileName << ".txt ... ";
	forec::File::write(fileName + ".txt", txtOutput);
	std::cout << "done" << std::endl;
}

void outputUppaal(const std::string &fileName, forec::cfg::Root &cfgRoot) {
	// Generate XML for UPPAAL
	std::ostringstream uppaalOutput;
	uppaalOutput << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>" << std::endl;
	cfgRoot.toUppaal(uppaalOutput);

	std::cout << "Outputting UPPAAL model: " << fileName << "_uppaal.xml ... ";
	forec::File::write(fileName + "_uppaal.xml", uppaalOutput);
	std::cout << "done" << std::endl;
}

void performMaxPlus(void) {
	std::cout << "Performing maxplus ... ";
	std::flush(std::cout);
	
	const std::string mainThreadId = "main";
	forec::maxplus::MaxPlus::setMainThreadId(mainThreadId);
	forec::maxplus::MaxPlus::setThreads();

	struct timeval startTime, endTime;
	gettimeofday(&startTime, 0);
	
	const unsigned int maximumReaction = forec::maxplus::MaxPlus::compute(global::withInterleaving);

	gettimeofday(&endTime, 0);
	long seconds = endTime.tv_sec - startTime.tv_sec;
	int microseconds = endTime.tv_usec - startTime.tv_usec;
	if (microseconds < 0) {
		microseconds += 1000000;
		seconds--;
	}
	
	std::cout << "done" << std::endl;
	
	unsigned int totalReactionsSeenCount = 0;
	const std::map<std::string, unsigned int> reactionsSeenCounts = forec::maxplus::MaxPlus::getReactionsSeenCount();
	for (std::map<std::string, unsigned int>::const_iterator reactionsSeenCount = reactionsSeenCounts.begin(); reactionsSeenCount != reactionsSeenCounts.end(); ++reactionsSeenCount) {
		totalReactionsSeenCount += reactionsSeenCount->second;
	}
	
	analysisFile << "Number of cores: " << tools::Multicore::getAllCoreIds().size() << std::endl;
	analysisFile << "Analysis time required: " << seconds << '.' << std::setfill('0') << std::setw(6) << microseconds << " seconds" << std::endl;
	analysisFile << "Reactions evolved: " << (forec::maxplus::Reaction::getGlobalCount() - 1) << std::endl;
	analysisFile << "Reactions seen: " << totalReactionsSeenCount << std::endl;
	analysisFile << std::endl;
	analysisFile << "Maximum reaction found:" << std::endl;
	analysisFile << "-----------------------" << std::endl;
	analysisFile << maximumReaction << std::endl;
	analysisFile << forec::maxplus::MaxPlus::getExecutionTrace() << std::endl;

	std::cout << "Number of cores: " << tools::Multicore::getAllCoreIds().size() << std::endl;
	std::cout << "Analysis time required: " << seconds << '.' << std::setfill('0') << std::setw(6) << microseconds << " seconds" << std::endl;
	std::cout << "Reactions evolved: " << (forec::maxplus::Reaction::getGlobalCount() - 1) << std::endl;
	std::cout << "Reactions seen: " << totalReactionsSeenCount << std::endl;
	std::cout << "Maximum reaction time found: " << maximumReaction;
	if (global::architecture.compare("ptarm") == 0) {
		std::cout << " thread cycles" << std::endl;
	} else {
		std::cout << " clock cycles" << std::endl;		
	}
}

void performReachability(void) {
	std::cout << "Performing reachability ... ";
	std::flush(std::cout);

	const std::string startingThreadId = "main";
	forec::reachability::Reachability::setStartingReaction(startingThreadId);

	forec::reachability::Reachability::openOutFile("trace.xml");

	struct timeval startTime, endTime;
	gettimeofday(&startTime, 0);
	
	const forec::reachability::Reaction *maximumReaction = forec::reachability::Reachability::compute();

	gettimeofday(&endTime, 0);
	long seconds = endTime.tv_sec - startTime.tv_sec;
	int microseconds = endTime.tv_usec - startTime.tv_usec;
	if (microseconds < 0) {
		microseconds += 1000000;
		seconds--;
	}
	
	forec::reachability::Reachability::closeOutFile();

	std::cout << "done" << std::endl;
	
	analysisFile << "Number of cores: " << tools::Multicore::getAllCoreIds().size() << std::endl;
	analysisFile << "Analysis time required: " << seconds << '.' << std::setfill('0') << std::setw(6) << microseconds << " seconds" << std::endl;
	analysisFile << "Reactions evolved: " << (forec::reachability::Reaction::getGlobalCount() - 1) << std::endl;
	analysisFile << "Reactions seen: " << (forec::reachability::Reachability::getReactionsSeenCount()) << std::endl;
	analysisFile << std::endl;
	analysisFile << "Maximum reaction found:" << std::endl;
	analysisFile << "-----------------------" << std::endl;
	analysisFile << maximumReaction->toString() << std::endl;
	analysisFile << maximumReaction->getExecutionTrace("") << std::endl;

	std::cout << "Number of cores: " << tools::Multicore::getAllCoreIds().size() << std::endl;
	std::cout << "Analysis time required: " << seconds << '.' << std::setfill('0') << std::setw(6) << microseconds << " seconds" << std::endl;
	std::cout << "Reactions evolved: " << (forec::reachability::Reaction::getGlobalCount() - 1) << std::endl;
	std::cout << "Reactions seen: " << (forec::reachability::Reachability::getReactionsSeenCount()) << std::endl;
	std::cout << "Maximum reaction time found: " << maximumReaction->getReactionTime();
	if (global::architecture.compare("ptarm") == 0) {
		std::cout << " thread cycles" << std::endl;
	} else {
		std::cout << " clock cycles" << std::endl;
	}
}


