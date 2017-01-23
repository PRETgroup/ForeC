/*
 *  Condition.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 8/04/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Condition.hpp"

#include "Threading.hpp"

#include "../ast/IterationStatement.hpp"
#include "../ast/SelectionStatement.hpp"
#include "../ast/ParStatement.hpp"

namespace tools {
	std::string Condition::selectionBranch;
	std::vector<forec::ast::IterationStatement *> Condition::iterationScopeName;
	std::vector<std::pair<forec::ast::SelectionStatement *, std::string> > Condition::selectionScopeName;
	std::map<std::string, forec::ast::IterationStatement *> Condition::iterationIdTable;
	std::map<std::string, forec::ast::SelectionStatement *> Condition::selectionIdTable;
	std::map<std::string, std::map<forec::ast::ParStatement *, forec::ast::IterationStatement *> > Condition::iterationParStatements;
	std::map<std::string, std::map<forec::ast::ParStatement *, std::pair<forec::ast::SelectionStatement *, std::string> > > Condition::selectionParStatements;

	void Condition::clear(void) {
		Condition::iterationScopeName.clear();
		Condition::selectionScopeName.clear();
		Condition::iterationIdTable.clear();
		Condition::selectionIdTable.clear();
		Condition::iterationParStatements.clear();
		Condition::selectionParStatements.clear();
	}

	const bool Condition::enterScope(forec::ast::IterationStatement &iterationStatement) {
		// Add iteration scope.
		Condition::iterationScopeName.push_back(&iterationStatement);
		
		// Iteration lookup.
		Condition::iterationIdTable[iterationStatement.getId()] = &iterationStatement;

		return Condition::iterationScopeName.size() == 1;
	}

	void Condition::enterScope(forec::ast::SelectionStatement &selectionStatement) {
		// Add selection scope.
		std::pair<forec::ast::SelectionStatement *, std::string> scopeName;
		scopeName.first = &selectionStatement;
		scopeName.second = "";
		Condition::selectionScopeName.push_back(scopeName);
		
		// Selection lookup.
		Condition::selectionIdTable[selectionStatement.getId()] = &selectionStatement;
	}

	void Condition::leaveScope(const std::string &type) {
		// Remove iteration or selection scope.
		if (type.compare("IterationStatement") == 0) {
			Condition::iterationScopeName.pop_back();
		} else if (type.compare("SelectionStatement") == 0) {
			Condition::selectionScopeName.pop_back();
		}
	}

	void Condition::setSelectionBranch(const std::string &branch) {
		// Set current branch.
		Condition::selectionBranch = branch;
		Condition::selectionScopeName.back().second = branch;
	}

	void Condition::addParStatement(forec::ast::ParStatement &parStatement) {
		if (Condition::iterationScopeName.size() > 0) {
			Condition::iterationParStatements[Threading::getCurrentName()][&parStatement] = Condition::iterationScopeName.back();
		}

		if (Condition::selectionScopeName.size() > 0) {
			Condition::selectionParStatements[Threading::getCurrentName()][&parStatement] = Condition::selectionScopeName.back();
		}
	}

	const std::vector<forec::ast::IterationStatement *> Condition::getCurrentIterations(void) {
		return Condition::iterationScopeName;
	}

	const std::vector<std::pair<forec::ast::SelectionStatement *, std::string> > Condition::getCurrentSelections(void) {
		return Condition::selectionScopeName;
	}

	const forec::ast::IterationStatement *Condition::lookupIterationId(const std::string &iterationId) {
		return Condition::iterationIdTable[iterationId];
	}

	const forec::ast::SelectionStatement *Condition::lookupSelectionId(const std::string &selectionId) {
		return Condition::selectionIdTable[selectionId];
	}

	const std::set<forec::ast::ParStatement *> Condition::getParStatements(const std::string &threadScope, const std::string &type, const std::string &id) {
		// Retrieve par(...)s within a thread's iteration or selection scopes.
		std::set<forec::ast::ParStatement *> parStatements;
		if (type.compare("IterationStatement") == 0) {
			for (std::map<forec::ast::ParStatement *, forec::ast::IterationStatement *>::iterator par = Condition::iterationParStatements[threadScope].begin(); par != Condition::iterationParStatements[threadScope].end(); ++par) {
				if (par->second->getId().compare(id) == 0) {
					parStatements.insert(par->first);
				}
			}
		} else if (type.compare("SelectionStatement") == 0) {
			for (std::map<forec::ast::ParStatement *, std::pair<forec::ast::SelectionStatement *, std::string> >::iterator par = Condition::selectionParStatements[threadScope].begin(); par != Condition::selectionParStatements[threadScope].end(); ++par) {
				if (par->second.first->getId().compare(id) == 0) {
					parStatements.insert(par->first);
				}
			}
		}

		return parStatements;
	}

	const std::set<forec::ast::ParStatement *> Condition::getParStatements(const std::string &threadScope, const std::string &type, const std::string &branch, const std::string &id) {
		// Retrieve par(...)s within a thread's selection scopes.
		std::set<forec::ast::ParStatement *> parStatements;
		for (std::map<forec::ast::ParStatement *, std::pair<forec::ast::SelectionStatement *, std::string> >::iterator par = Condition::selectionParStatements[threadScope].begin(); par != Condition::selectionParStatements[threadScope].end(); ++par) {
			if (par->second.first->getId().compare(id) == 0) {
				if (par->second.second.compare(branch) == 0) {
					parStatements.insert(par->first);
				}
			}
		}

		return parStatements;
	}

	bool Condition::hasParStatements(const std::string &threadScope, const std::string &type, const std::string &id) {
		return Condition::getParStatements(threadScope, type, id).size() > 0;
	}

	const std::map<std::string, std::map<forec::ast::ParStatement *, forec::ast::IterationStatement *> > Condition::getIterations(void) {
		return Condition::iterationParStatements;
	}

	const forec::ast::IterationStatement *Condition::getIterations(const std::string &threadScope, forec::ast::ParStatement &parStatement) {
		if (Condition::iterationParStatements.find(threadScope) != Condition::iterationParStatements.end()) {
			if (Condition::iterationParStatements[threadScope].find(&parStatement) != Condition::iterationParStatements[threadScope].end()) {
				return Condition::iterationParStatements[threadScope][&parStatement];
			}
		}

		return NULL;
	}

	const std::map<std::string, std::map<forec::ast::ParStatement *, std::pair<forec::ast::SelectionStatement *, std::string> > > Condition::getSelections(void) {
		return Condition::selectionParStatements;
	}

	const std::pair<forec::ast::SelectionStatement *, std::string> Condition::getSelections(const std::string &threadScope, forec::ast::ParStatement &parStatement) {
		if (Condition::selectionParStatements.find(threadScope) != Condition::selectionParStatements.end()) {
			if (Condition::selectionParStatements[threadScope].find(&parStatement) != Condition::selectionParStatements[threadScope].end()) {
				return Condition::selectionParStatements[threadScope][&parStatement];
			}
		}

		return std::pair<forec::ast::SelectionStatement *, std::string>(NULL, NULL);
	}

	const bool Condition::inIterationScope(const std::string &threadScope, forec::ast::ParStatement *parStatement) {
		return Condition::getIterations(threadScope, *parStatement) != NULL;
	}

	const std::string Condition::toString(void) {
		std::ostringstream output;

		output << "============================" << std::endl;
		output << "tools::Condition::toString()" << std::endl;
		output << "============================" << std::endl;

		if (!Condition::iterationParStatements.empty()) {
			output << "Iterations statements:" << std::endl;
			output << "----------------------" << std::endl;
			for (std::map<std::string, std::map<forec::ast::ParStatement *, forec::ast::IterationStatement *> >::const_iterator threadScope = Condition::iterationParStatements.begin(); threadScope != Condition::iterationParStatements.end(); ++threadScope) {
				output << "\tThread scope: " << threadScope->first << "__thread" << std::endl;

				for (std::map<forec::ast::ParStatement *, forec::ast::IterationStatement *>::const_iterator parInstance = threadScope->second.begin(); parInstance != threadScope->second.end(); ++parInstance) {
					output << "\t\t" << parInstance->first->getId() << ':' << std::endl;
					output << "\t\t* " << parInstance->second->getVariant() << '_' << parInstance->second->getIdNumber();
				
					if (parInstance->second->getWillPause()) {
						output << " (pauses)";
					}
					output << std::endl << std::endl;
				}
			}
		}

		if (!Condition::selectionParStatements.empty()) {
			output << "Selections statements:" << std::endl;
			output << "----------------------" << std::endl;
			for (std::map<std::string, std::map<forec::ast::ParStatement *, std::pair<forec::ast::SelectionStatement *, std::string> > >::const_iterator threadScope = Condition::selectionParStatements.begin(); threadScope != Condition::selectionParStatements.end(); ++threadScope) {
				output << "\tThread scope: " << threadScope->first << "__thread" << std::endl;

				for (std::map<forec::ast::ParStatement *, std::pair<forec::ast::SelectionStatement *, std::string> >::const_iterator parInstance = threadScope->second.begin(); parInstance != threadScope->second.end(); ++parInstance) {
					output << "\t\t" << parInstance->first->getId() << ':' << std::endl;
					output << "\t\t* " << parInstance->second.second << '_'<< parInstance->second.first->getVariant() << parInstance->second.first->getIdNumber() << std::endl << std::endl;
				}
			}
		}

		return output.str();
	}


}
