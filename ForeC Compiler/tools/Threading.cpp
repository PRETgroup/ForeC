/*
 *  Threading.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Threading.hpp"

#include "../ast/ParStatement.hpp"
#include "../ast/ThreadDefinition.hpp"

namespace tools {
	const std::string Threading::suffix = "__thread";
	std::string Threading::currentName;
	std::set<std::string> Threading::used;
	std::set<std::string> Threading::declared;
	std::set<std::pair<std::string, forec::ast::ThreadDefinition *> > Threading::declarations;
	std::map<std::string, forec::ast::ParStatement *> Threading::enclosingParStatements;
	std::map<std::string, forec::ast::ParStatement *> Threading::parIdTable;
	std::map<std::string, std::vector<forec::ast::ParStatement *> > Threading::parStatements;

	void Threading::clear(void) {
		Threading::currentName = "global";
		Threading::used.clear();
		Threading::declared.clear();
		Threading::declarations.clear();
		Threading::enclosingParStatements.clear();
		Threading::parIdTable.clear();
		Threading::parStatements.clear();
	}

	void Threading::addDeclaration(const std::string &identifier) {
		Threading::declared.insert(identifier);
		Threading::declarations.insert(std::make_pair(identifier, (forec::ast::ThreadDefinition *)NULL));
	}

	void Threading::addDeclaration(const std::string &identifier, forec::ast::ThreadDefinition &declaration) {
		Threading::declared.insert(identifier);
		Threading::declarations.insert(std::make_pair(identifier, &declaration));
	}

	std::string Threading::addParStatement(forec::ast::ParStatement &parStatement) {
		Threading::parStatements[Threading::getCurrentName()].push_back(&parStatement);

		// par(...) lookup.
		Threading::parIdTable[parStatement.getId()] = &parStatement;

		// Save thread IDs that are referred to by par(...).
		std::vector<std::string> threadIds = parStatement.getThreadIds();
		Threading::used.insert(threadIds.begin(), threadIds.end());

		// par(...) reverse lookup.
		std::vector<std::string> threadsIds = parStatement.getThreadIds();
		for (std::vector<std::string>::const_iterator threadId = threadIds.begin(); threadId != threadIds.end(); ++threadId) {
			Threading::enclosingParStatements[*threadId] = &parStatement;
		}

		return Threading::getCurrentName();
	}

	const bool Threading::isThread(const std::string &identifier) {
		return Threading::declared.find(identifier) != Threading::declared.end();
	}

	forec::ast::ParStatement *Threading::lookupId(const std::string &parId) {
		return Threading::parIdTable[parId];
	}

	const std::set<std::string> Threading::getUnused(void) {
		// unused = declared - used.
		std::set<std::string> result;
		std::set_difference(Threading::declared.begin(), Threading::declared.end(), Threading::used.begin(), Threading::used.end(), std::inserter(result, result.end()));
		result.erase("main");
		return result;
	}

	const std::set<std::string> Threading::getDeclared(void) {
		return Threading::declared;
	}

	forec::ast::ThreadDefinition *Threading::getDeclaration(const std::string &identifier) {
		for (std::set<std::pair<std::string, forec::ast::ThreadDefinition *> >::iterator declaration = Threading::declarations.begin(); declaration != Threading::declarations.end(); ++declaration) {
			if (declaration->first.compare(identifier) == 0) {
				return declaration->second;
			}
		}
		
		throw std::string("Threading::getDeclaration: Could not find thread declaration for \"" + identifier + "\".");
	}
	
	const std::set<std::string> Threading::getReferenced(void) {
		std::set<std::string> references;

		for (std::map<std::string, std::vector<forec::ast::ParStatement *> >::iterator threadScope = Threading::parStatements.begin(); threadScope != Threading::parStatements.end(); ++ threadScope) {
			for (std::vector<forec::ast::ParStatement *>::iterator parInstance = threadScope->second.begin(); parInstance != threadScope->second.end(); ++parInstance) {
				std::vector<std::string> threadIds = (*parInstance)->getThreadIds();
				references.insert(threadIds.begin(), threadIds.end());
			}
		}

		return references;
	}

	const std::set<std::string> Threading::getUndeclared(void) {
		// undeclared = referenced - declared.
		std::set<std::string> result;
		std::set<std::string> references = Threading::getReferenced();
		std::set_difference(references.begin(), references.end(), declared.begin(), declared.end(), std::inserter(result, result.end()));
		return result;
	}

	const std::map<std::string, std::vector<forec::ast::ParStatement *> > Threading::getParStatements(void) {
		return Threading::parStatements;
	}

	const std::vector<forec::ast::ParStatement *> Threading::getParStatements(const std::string &threadScope) {
		return Threading::parStatements[threadScope];
	}

	const bool Threading::hasParStatements(const std::string &threadScope) {
		return Threading::parStatements[threadScope].size() > 0;
	}

	const std::string Threading::getEnclosingThreadScope(const std::string &threadId) {
		if (Threading::isUnused(threadId)) {
			std::cerr << std::endl << "!!  Threading::getEnclosingThreadScope: Thread \"" << threadId << "\" is declared but unused.";
			return "";
		}

		// Get the (immediate) parent thread of the current thread.
		for (std::map<std::string, std::vector<forec::ast::ParStatement *> >::const_iterator threadScope = Threading::parStatements.begin(); threadScope != Threading::parStatements.end(); ++threadScope) {
			for (std::vector<forec::ast::ParStatement *>::const_iterator parInstance = threadScope->second.begin(); parInstance != threadScope->second.end(); ++parInstance) {
				if ((*parInstance)->hasThreadId(threadId)) {
					return threadScope->first;
				}
			}
		}

		throw std::string("Threading::getEnclosingThreadScope: Could not find enclosing thread scope for thread \"" + threadId + "\".");
		return "";
	}

	forec::ast::ParStatement *Threading::getEnclosingParStatement(const std::string &threadId) {
		if (Threading::enclosingParStatements.find(threadId) != Threading::enclosingParStatements.end()) {
			return Threading::enclosingParStatements[threadId];
		}

		throw std::string("Threading::getEnclosingParStatement: Thread \"" + threadId + "\" does not appear in a par statement.");
	}

	const bool Threading::allDeclared(void) {
		return Threading::getUndeclared().size() == 0;
	}

	const bool Threading::isUnused(const std::string &threadId) {
		std::set<std::string> unused = Threading::getUnused();
		return unused.find(threadId) != unused.end();
	}

	void Threading::setCurrentName(const std::string &identifier) {
		Threading::currentName = identifier;
	}

	const std::string Threading::getCurrentName(void) {
		return Threading::currentName;
	}

	const std::string Threading::toString(void) {
		std::ostringstream output;

		output << "============================" << std::endl;
		output << "tools::Threading::toString()" << std::endl;
		output << "============================" << std::endl;

		output << "Threads declared:" << std::endl;
		output << "-----------------" << std::endl;
		for (std::set<std::string>::const_iterator declaration = Threading::declared.begin(); declaration != Threading::declared.end(); ++declaration) {
			output << "\t* " << *declaration << Threading::suffix << std::endl;
		}
		output << std::endl;

		output << "Threads unused:" << std::endl;
		output << "---------------" << std::endl;
		std::set<std::string> unused = Threading::getUnused();
		for (std::set<std::string>::const_iterator threadId = unused.begin(); threadId != unused.end(); ++threadId) {
			output << "\t* " << *threadId << Threading::suffix << std::endl;
		}
		output << std::endl;

		output << "par(...) statements:" << std::endl;
		output << "--------------------" << std::endl;
		for (std::map<std::string, std::vector<forec::ast::ParStatement *> >::iterator threadScope = Threading::parStatements.begin(); threadScope != Threading::parStatements.end(); ++threadScope) {

			output << "\tThread scope: " << threadScope->first << std::endl;
			for (std::vector<forec::ast::ParStatement *>::iterator parInstance = threadScope->second.begin(); parInstance != threadScope->second.end(); ++parInstance) {

				output << "\t\t" << (*parInstance)->getId() << ":" << std::endl;
				std::vector<std::string> threads = (*parInstance)->getThreadIds();
				for (std::vector<std::string>::iterator thread = threads.begin(); thread != threads.end(); ++thread) {
					output << "\t\t* " << *thread << Threading::suffix << std::endl;
				}
				output << std::endl;
			}
		}

		return output.str();
	}
}
