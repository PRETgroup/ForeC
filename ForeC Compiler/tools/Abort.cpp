/*
 *  Abort.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Abort.hpp"

#include "Threading.hpp"

#include "../ast/AbortStatement.hpp"
#include "../ast/ParStatement.hpp"


namespace tools {
	std::vector<forec::ast::AbortStatement *> Abort::scopeName;
	std::map<std::string, forec::ast::AbortStatement *> Abort::abortIdTable;
	std::map<std::string, std::map<forec::ast::ParStatement *, std::vector<forec::ast::AbortStatement *> > > Abort::parStatements;

	void Abort::clear(void) {
		Abort::scopeName.clear();
		Abort::abortIdTable.clear();
		Abort::parStatements.clear();
	}

	void Abort::enterScope(forec::ast::AbortStatement &abortStatement) {
		// Add abort scope.
		Abort::scopeName.push_back(&abortStatement);
		
		// Abort lookup.
		Abort::abortIdTable[abortStatement.getId()] = &abortStatement;
	}

	void Abort::leaveScope(void) {
		// Remove abort scope.
		Abort::scopeName.pop_back();
	}

	void Abort::addParStatement(forec::ast::ParStatement &parStatement) {
		// Add abort scopes to par(...).
		if (Abort::scopeName.size() > 0) {
			Abort::parStatements[Threading::getCurrentName()][&parStatement] = Abort::scopeName;
		}
	}

	const std::vector<forec::ast::AbortStatement *> Abort::getCurrentAborts(void) {
		return Abort::scopeName;
	}

	const forec::ast::AbortStatement *Abort::lookupId(const std::string &abortId) {
		return Abort::abortIdTable[abortId];
	}

	const std::string Abort::getVariant(const std::string &abortId) {
		return Abort::abortIdTable[abortId]->getVariant();
	}

	const std::set<forec::ast::ParStatement *> Abort::getParStatements(const std::string &threadScope) {
		// Retrieve par(...)s within a thread's abort scopes.
		std::set<forec::ast::ParStatement *> parStatements;
		std::map<forec::ast::ParStatement *, std::vector<forec::ast::AbortStatement *> > aborts = Abort::getAborts(threadScope);
		for (std::map<forec::ast::ParStatement *, std::vector<forec::ast::AbortStatement *> >::iterator par = aborts.begin(); par != aborts.end(); ++par) {
			parStatements.insert(par->first);
		}

		return parStatements;
	}


	const std::map<std::string, std::map<forec::ast::ParStatement *, std::vector<forec::ast::AbortStatement *> > > Abort::getAborts(void) {
		return Abort::parStatements;
	}

	const std::map<forec::ast::ParStatement *, std::vector<forec::ast::AbortStatement *> > Abort::getAborts(const std::string &threadScope) {
		if (Abort::parStatements.find(threadScope) != Abort::parStatements.end()) {
			return Abort::parStatements[threadScope];
		}

		return std::map<forec::ast::ParStatement *, std::vector<forec::ast::AbortStatement *> >();
	}

	const std::vector<forec::ast::AbortStatement *> Abort::getAborts(const std::string &threadScope, forec::ast::ParStatement &parStatement) {
		std::map<forec::ast::ParStatement *, std::vector<forec::ast::AbortStatement *> > aborts = Abort::getAborts(threadScope);
		if (aborts.find(&parStatement) != aborts.end()) {
			return aborts[&parStatement];
		}

		return std::vector<forec::ast::AbortStatement *>();
	}


	const std::string Abort::toString(void) {
		std::ostringstream output;

		output << "========================" << std::endl;
		output << "tools::Abort::toString()" << std::endl;
		output << "========================" << std::endl;

		if (!Abort::parStatements.empty()) {
			output << "Abort statements:" << std::endl;
			output << "-----------------" << std::endl;
			for (std::map<std::string, std::map<forec::ast::ParStatement *, std::vector<forec::ast::AbortStatement *> > >::const_iterator threadScope = Abort::parStatements.begin(); threadScope != Abort::parStatements.end(); ++threadScope) {
				output << "\tThread scope: " << threadScope->first << "__thread" << std::endl;

				for (std::map<forec::ast::ParStatement *, std::vector<forec::ast::AbortStatement *> >::const_iterator parInstance = threadScope->second.begin(); parInstance != threadScope->second.end(); ++parInstance) {
					output << "\t\t" << parInstance->first->getId() << ":" << std::endl;

					for (std::vector<forec::ast::AbortStatement *>::const_iterator abort = parInstance->second.begin(); abort != parInstance->second.end(); ++abort) {
						output << "\t\t* " << (*abort)->getId() << " " << (*abort)->getVariant() << std::endl;
					}

					output << std::endl;
				}
			}
			output << std::endl;
		}

		return output.str();
	}

	const std::string Abort::outputXml(const std::string &indent) {
		std::ostringstream output;
		
		output << indent << "<!-- Aborts around each par(...) (Abort.cpp::outputXml). -->" << std::endl;
		output << indent << "<aborts>" << std::endl;
		for (std::map<std::string, std::map<forec::ast::ParStatement *, std::vector<forec::ast::AbortStatement *> > >::const_iterator threadScope = Abort::parStatements.begin(); threadScope != Abort::parStatements.end(); ++threadScope) {
			for (std::map<forec::ast::ParStatement *, std::vector<forec::ast::AbortStatement *> >::const_iterator parInstance = threadScope->second.begin(); parInstance != threadScope->second.end(); ++parInstance) {
				std::string parNumber = parInstance->first->getId();
				parNumber.replace(parNumber.find("par"), std::string("par").length(), "");
				output << indent << "\t<par id=\"" << parNumber << "\">" << std::endl;
			
				for (std::vector<forec::ast::AbortStatement *>::const_iterator abort = parInstance->second.begin(); abort != parInstance->second.end(); ++abort) {
					output << indent << "\t\t<abort id=\"" << (*abort)->getId() << "\" variant=\"" << (*abort)->getVariant() << "\" />" << std::endl;
				}
				
				output << indent <<"\t</par>" << std::endl;
			}
		}
		output << indent << "</aborts>" << std::endl;
		
		return output.str();
	}
	
}
