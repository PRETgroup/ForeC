/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#include <iostream>
#include <ostream>
#include <cstring>
#include <unistd.h>
#include <algorithm>

#include "File.hpp"

#include "tarot/Tarot.hpp"

#include "tools/Function.hpp"
#include "tools/Query.hpp"
#include "tools/Multicore.hpp"
#include "tools/Threading.hpp"
#include "tools/Template.hpp"
#include "tools/Abort.hpp"
#include "tools/Condition.hpp"
#include "tools/Mutex.hpp"
#include "tools/SymbolTable.hpp"
#include "tools/Tab.hpp"


const std::string version = "Version: 0.99 (5 October 2014)";
std::ofstream debugFile;

namespace global {
	int debugLevel = 0;
	bool checkLoops = false;
	unsigned long minReactionTime = 0;
}

void programInput(const std::string &sourceFileName, forec::ast::Root &astRoot);
void threadAllocationInput(const std::string &headerFileName);

void updateSymbolTable(forec::ast::Root &astRoot);
void checkThreads(void);
void checkInstantaneousLoops(forec::ast::Root &astRoot);

void createTarot(forec::ast::Root &astRoot);
void createThreadScheduling(void);
void createMutexes(void);

void takeOutThreadLocalDeclarations(forec::ast::Root &astRoot);
void insertThreads(forec::ast::Root &astRoot);

void output(const std::string &fileName, forec::ast::Root &astRoot);

int main(const int argc, const char *argv[]) {
	std::string fileName;
	std::string sourceFileName;
	std::string headerFileName;

	std::cout << std::endl;
	std::cout << "ForeC Compiler (multicore distribution)" << std::endl;
	std::cout << version << std::endl;
	std::cout << "---------------------------------------" << std::endl;
	for (int i = 0; i < argc; ++i) {
		std::cout << argv[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "---------------------------------------" << std::endl;

	// Check argument inputs.
	bool unexpectedArguments = false;
	for (int i = 1; i < argc; ++i) {
		// Check the options before checking the filenames.
		if (std::string(argv[i]).compare("-v") == 0) {
			std::cout << version << std::endl << std::endl;
			return EXIT_SUCCESS;
		} else if (std::string(argv[i]).compare("-i") == 0) {
			global::checkLoops = true;
		} else if (std::string(argv[i]).substr(0,2).compare("-d") == 0) {
			std::istringstream(std::string(argv[i]).substr(2)) >> global::debugLevel;
		} else if (std::string(argv[i]).substr(0,2).compare("-t") == 0) {
			std::istringstream(std::string(argv[i]).substr(2)) >> global::minReactionTime;
		} else {
			if (sourceFileName.empty()) {
				sourceFileName = std::string(argv[i]);
			} else if (headerFileName.empty()) {
				headerFileName = std::string(argv[i]);
			} else {
				unexpectedArguments = true;
			}
		}
	}
	
	if (unexpectedArguments || sourceFileName.empty() || headerFileName.empty()) {
		std::cerr << "Usage: forecc [-option] <SOURCE FILENAME> <HEADER FILENAME>" << std::endl
				  << "  Option can be -v (version), or -d<1, 2, 3> (debug)," << std::endl
				  << "  -i (check loops), or -t<clock cycles> (timing)" << std::endl;
		return EXIT_FAILURE;
	}

	// Open debug file.
	debugFile.open("debug.txt");
	debugFile << "ForeC Compiler (multicore distribution)" << std::endl;
	debugFile << version << std::endl;
	debugFile << "Debug output" << std::endl;
	debugFile << "---------------------------------------" << std::endl << std::endl;
	debugFile << "Debug level: " << global::debugLevel << std::endl;
	debugFile << "Check instantaneous loops: " << (global::checkLoops ? "true" : "false") << std::endl;
	debugFile << "Minimum reaction time: " << global::minReactionTime << " clock cycles" << std::endl;
	debugFile << "Source file name: " << sourceFileName << std::endl;
	debugFile << "Header file name: " << headerFileName << std::endl << std::endl;

	// Starting node for the abstract syntax tree
	forec::ast::Root astRoot;

	// Initialise tools
	forec::tarot::Tarot::clear();
	tools::SymbolTable::clear();
	tools::Threading::clear();
	tools::Multicore::clear();
	tools::Abort::clear();
	tools::Condition::clear();
	tools::Mutex::clear();

	// Try and open the ForeC source and header files
	try {
		fileName = sourceFileName.substr(0, sourceFileName.find(".forec"));
			
		programInput(sourceFileName, astRoot);
		threadAllocationInput(headerFileName);

		std::cout << std::endl;

		updateSymbolTable(astRoot);
		checkThreads();
		if (global::checkLoops) {
			checkInstantaneousLoops(astRoot);
		}
		
		std::cout << std::endl;

		createTarot(astRoot);
		createThreadScheduling();
		createMutexes();

		std::cout << std::endl;

		takeOutThreadLocalDeclarations(astRoot);
		insertThreads(astRoot);

		std::cout << std::endl;

		output(fileName, astRoot);
	} catch (std::string error) {
		std::cerr << std::endl;
		std::cerr << "Error:" << std::endl << error << std::endl << std::endl;

		debugFile << std::endl;
		debugFile << "Error: " << std::endl << error << std::endl;
		debugFile.close();

		return EXIT_FAILURE;
	}

	std::cout << std::endl;
	std::cout << "Compilation success" << std::endl;
	std::cout << std::endl;
	debugFile.close();
	return EXIT_SUCCESS;
}

void programInput(const std::string &sourceFileName, forec::ast::Root &astRoot) {
	std::cout << "Parsing input program ... ";

	if (sourceFileName.find(".forec") == std::string::npos) {
		throw std::string("ForeC filename extension expected but received \"" + sourceFileName + "\" instead.");
	}

	forec::File::read(sourceFileName, astRoot);
	
	std::cout << "done" << std::endl;
}

void threadAllocationInput(const std::string &headerFileName) {
	std::cout << "Parsing thread allocations ... ";


	tools::Multicore::setAllocations(headerFileName);

	debugFile << tools::Multicore::toString() << std::endl;
	std::cout << "done" << std::endl;
}


void updateSymbolTable(forec::ast::Root &astRoot) {
	std::cout << "Updating symbol table ... ";

	tools::SymbolTable::resetScope();
	astRoot.updateSymbolTable();
	std::cout << "done" << std::endl;
	
	std::cout << "Checking shared variables ... ";
	astRoot.pullUpIndirectParallelVariables();
	std::set<forec::ast::PrimaryExpression *> parDefinedVariables;
	astRoot.pullDownIndirectParallelVariables(parDefinedVariables);
	debugFile << tools::SymbolTable::toString();

	// Get all the shared variable declarations.
	std::set<forec::ast::PrimaryExpression *> sharedSpecified;
	const std::map<std::string, std::set<forec::ast::PrimaryExpression *> > sharedScopedDeclarations = tools::SymbolTable::getDeclarations("shared");
	for (std::map<std::string, std::set<forec::ast::PrimaryExpression *> >::const_iterator variable = sharedScopedDeclarations.begin(); variable != sharedScopedDeclarations.end(); ++variable) {
		sharedSpecified.insert(variable->second.begin(), variable->second.end());
	}
	
	// Get all variables used by multiple threads.
	std::set<forec::ast::PrimaryExpression *> sharedNeeded;
	const std::map<forec::ast::PrimaryExpression *, std::set<std::string> > sharedNeededMap = tools::SymbolTable::getUsesDefsMultiple(true, true, "", "variable");
	for (std::map<forec::ast::PrimaryExpression *, std::set<std::string> >::const_iterator variable = sharedNeededMap.begin(); variable != sharedNeededMap.end(); ++variable) {
		if (variable->second.size() > 1) {
			sharedNeeded.insert(variable->first);
		}
	}

	std::set<forec::ast::PrimaryExpression *> sharedUnspecified;
	// unspecified = needed - specified
	std::set_difference(sharedNeeded.begin(), sharedNeeded.end(), sharedSpecified.begin(), sharedSpecified.end(), std::inserter(sharedUnspecified, sharedUnspecified.end()));
	if (!sharedUnspecified.empty()) {
		std::ostringstream output;
		output << "* These variables need to be declared as shared variables:" << std::endl;
		for (std::set<forec::ast::PrimaryExpression *>::const_iterator variable = sharedUnspecified.begin(); variable != sharedUnspecified.end(); ++variable) {
			output << "  " << (*variable)->getTerminal() << " (line " << (*variable)->getLineNumber();
			const std::set<std::string> threads = sharedNeededMap.find(*variable)->second;
			for (std::set<std::string>::const_iterator thread = threads.begin(); thread != threads.end(); ++thread) {
				output << ", " << *thread;
			}
			output << ')' << std::endl;
		}
		
		throw output.str();
	}

	// Combine functions.
	const std::set<forec::ast::PrimaryExpression *> combineNeeded = tools::SymbolTable::getCombineNeeded();
	const std::set<forec::ast::PrimaryExpression *> combineSpecified = tools::SymbolTable::getCombineSpecified();
	
	std::set<forec::ast::PrimaryExpression *> combineUnspecified;
	// unspecified = needed - specified
	std::set_difference(combineNeeded.begin(), combineNeeded.end(), combineSpecified.begin(), combineSpecified.end(), std::inserter(combineUnspecified, combineUnspecified.end()));
	if (!combineUnspecified.empty()) {
		std::ostringstream output;
		output << "* These variables need a combine function:" << std::endl;
		for (std::set<forec::ast::PrimaryExpression *>::const_iterator symbol = combineUnspecified.begin(); symbol != combineUnspecified.end(); ++symbol) {
			output << "  " << (*symbol)->getTerminal() << " (line " << (*symbol)->getLineNumber() << ')' << std::endl;
		}
		
		throw output.str();
	} 
	
	std::set<forec::ast::PrimaryExpression *> combineUnneeded;
	// uneeded = specified - needed
	std::set_difference(combineSpecified.begin(), combineSpecified.end(), combineNeeded.begin(), combineNeeded.end(), std::inserter(combineUnneeded, combineUnneeded.end()));
	if (!combineUnneeded.empty()) {
		std::cout << std::endl << "* These variables do not need a combine function:" << std::endl;
		for (std::set<forec::ast::PrimaryExpression *>::const_iterator symbol = combineUnneeded.begin(); symbol != combineUnneeded.end(); ++symbol) {
			std::cout << "  " << (*symbol)->getTerminal() << " (line " << (*symbol)->getLineNumber() << ')' << std::endl;
		}
	}

	std::cout << "done" << std::endl;
	
	std::cout << "Checking combine specifiers ... ";
	std::set<std::string> combineSpecifers = tools::SymbolTable::getCombineSpecifiers();
	for (std::set<std::string>::const_iterator specifier = combineSpecifers.begin(); specifier != combineSpecifers.end(); ++specifier) {
		try {
			tools::Function::getDeclaration(*specifier);
		} catch (std::string error) {
			std::ostringstream output;
			output << "The combine specifier \"" << *specifier << "\" is undeclared.";
			throw output.str();
		}
	}

	std::cout << "done" << std::endl;
}

void checkThreads(void) {
	std::cout << "Checking threads ... ";

	// Check that all threads have been declared.
	if (!tools::Threading::allDeclared()) {
		std::ostringstream output;
		output << std::endl;

		const std::set<std::string> undeclaredThreads = tools::Threading::getUndeclared();
		for (std::set<std::string>::const_iterator thread = undeclaredThreads.begin(); thread != undeclaredThreads.end(); ++thread) {
			output << '\t' << *thread << std::endl;
		}

		throw std::string("The following referenced threads are undeclared:" + output.str());
	}

	// Check that all allocated threads have been declared
	std::set<std::string> threadsAllocated = tools::Multicore::getAllocatedThreads();
	std::set<std::string> threadsDeclared = tools::Threading::getDeclared();
	std::set<std::string> result;
	// undeclared = allocated - declared.
	std::set_difference(threadsAllocated.begin(), threadsAllocated.end(), threadsDeclared.begin(), threadsDeclared.end(), std::inserter(result, result.end()));
	if (result.size() > 0) {
		std::ostringstream output;
		output << std::endl;

		for (std::set<std::string>::const_iterator thread = result.begin(); thread != result.end(); ++thread) {
			output << '\t' << *thread << std::endl;
		}

		throw std::string("The following allocated threads are undeclared:" + output.str());
	}

	// Check that all declared threads have been allocated.
	result.clear();
	// unallocated = declared - allocated.
	std::set_difference(threadsDeclared.begin(), threadsDeclared.end(), threadsAllocated.begin(), threadsAllocated.end(), std::inserter(result, result.end()));
	if (result.size() > 0) {
		std::ostringstream output;
		output << std::endl;

		for (std::set<std::string>::const_iterator thread = result.begin(); thread != result.end(); ++thread) {
			output << '\t' << *thread << std::endl;
		}

		throw std::string("The following declared threads are unallocated:" + output.str());
	}

	debugFile << tools::Threading::toString();
	std::cout << "done" << std::endl;
}

void checkInstantaneousLoops(forec::ast::Root &astRoot) {
	std::cout << "Checking for instantaneous loops ...";
	
	astRoot.willPause(true);
	astRoot.willPause(false);
	
	std::cout << "done" << std::endl;
}

void createTarot(forec::ast::Root &astRoot) {
	std::cout << "Creating tarot ... ";

	astRoot.createTarot("");
	forec::tarot::Tarot::setCoreAllocations(tools::Multicore::getAllocations());
	forec::tarot::Tarot::linkParThreads();
	forec::tarot::Tarot::findThreadRecursion();
	forec::tarot::Tarot::splitByCoreId(tools::Multicore::getCoreIds());

	forec::tarot::Tarot::findNextPar();
	forec::tarot::Tarot::findNextParInReaction();
	forec::tarot::Tarot::findLastPar();
	std::cout << "done" << std::endl;
}

void createThreadScheduling(void) {
	std::cout << "Statically scheduling thread execution ... ";
	forec::tarot::Tarot::extractParInformation();
	forec::tarot::Tarot::flatten();

	debugFile << tools::Abort::toString();
	debugFile << tools::Condition::toString();
	debugFile << std::endl << forec::tarot::Tarot::toString();

	std::cout << "done" << std::endl;
}


void createMutexes(void) {
	std::cout << "Determining mutexes required ... ";

	std::map<std::string, std::map<std::string, int> > parCoresPriority = tools::Multicore::getParCoresPriority();
	tools::Mutex::setParCoresMask(parCoresPriority);

	debugFile << tools::Multicore::toString() << std::endl;
	debugFile << tools::Mutex::toString() << std::endl;

	std::cout << "done" << std::endl;
}

void takeOutThreadLocalDeclarations(forec::ast::Root &astRoot) {
	std::cout << "Taking out thread local declarations to the top thread and global scope ... ";

	// Find the threads and take out their declarations.
	std::set<std::string> threadIds = tools::Threading::getDeclared();
	threadIds.erase("main");
	for (std::set<std::string>::const_iterator threadId = threadIds.begin(); threadId != threadIds.end(); ++threadId) {
		tools::Threading::getDeclaration(*threadId)->takeOutDeclarations();
	}
	
	forec::ast::FunctionDefinition *mainFunction = tools::Function::getDeclaration("main");
	mainFunction->takeOutDeclarations();

	std::cout << "done" << std::endl;
}

void insertThreads(forec::ast::Root &astRoot) {
	std::cout << "Inserting threads into the main(...) function ... ";

	// Find the threads and take them out.
	std::vector<forec::ast::Node *> threads;
	std::set<std::string> threadIds = tools::Threading::getDeclared();
	threadIds.erase("main");
	for (std::set<std::string>::const_iterator threadId = threadIds.begin(); threadId != threadIds.end(); ++threadId) {
		tools::Threading::getDeclaration(*threadId)->takeOut(threads);
	}

	// Find the main() function and then assign the threads.
	forec::ast::FunctionDefinition *mainFunction = tools::Function::getDeclaration("main");
	mainFunction->setThreads(threads);

	std::cout << "done" << std::endl;
}

void output(const std::string &fileName, forec::ast::Root &astRoot) {
	tools::Template::readFiles();

	// Generate Graphviz file.
	std::ofstream tarotOutput((fileName + ".dot").c_str());
	std::cout << "Outputting tarot file: " << fileName << ".dot ... ";
	tarotOutput << forec::tarot::Tarot::toDot(fileName);
	tarotOutput.close();
	std::cout << "done" << std::endl;

	// Generate C-code.
	std::cout << "Outputting program file: " << fileName << ".c ... ";
	forec::File::write(fileName, astRoot);
	std::cout << "done" << std::endl;

	// Generate XML information
	std::ofstream xmlOutput(std::string("information.xml").c_str());
	xmlOutput << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>" << std::endl;
	xmlOutput << "<!-- Supplementary information generated for static analysis (Main.cpp::output). -->" << std::endl;
	xmlOutput << "<information>" << std::endl;
	std::cout << "Outputting XML information: information.xml ... ";
	xmlOutput << tools::Multicore::toXml("\t");
	xmlOutput << tools::Abort::outputXml("\t");
	xmlOutput << forec::tarot::Tarot::outputXml("\t");
	xmlOutput << tools::SymbolTable::outputXml("\t");
	xmlOutput << "</information>" << std::endl;
	xmlOutput.close();
	std::cout << "done" << std::endl;
}


