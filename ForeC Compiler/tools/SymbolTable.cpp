/*
 *  SymbolTable.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "SymbolTable.hpp"

#include "Threading.hpp"

#include "../ast/CombineSpecifier.hpp"
#include "../ast/ParStatement.hpp"
#include "../ast/PrimaryExpression.hpp"

namespace tools {
	std::string SymbolTable::scopeName;
	unsigned int SymbolTable::currentLevel;

	std::map<std::string, std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::string> > > SymbolTable::useDef;
	
	std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > > > > SymbolTable::indirectParallelVariablesPar;
	std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > > > > SymbolTable::indirectParallelVariablesThread;
		
	std::map<std::string, std::vector<std::vector<std::map<forec::ast::PrimaryExpression *, std::string > > > > SymbolTable::symbols;
	std::set<std::string> SymbolTable::combineSpecifiers;
	
	void SymbolTable::clear(void) {
		SymbolTable::useDef.clear();

		SymbolTable::indirectParallelVariablesPar.clear();
		SymbolTable::indirectParallelVariablesThread.clear();
				
		SymbolTable::symbols.clear();
		SymbolTable::combineSpecifiers.clear();

		SymbolTable::resetScope();

		// Enter scope of the program.
		SymbolTable::enterScope();
	}

	void SymbolTable::resetScope(void) {
		// Go back to the scope outside of the program.
		SymbolTable::scopeName = "global";
		SymbolTable::currentLevel = 0;
	}

	// Enter a new thread or function scope, or nested scope within a thread or function.
	void SymbolTable::enterScope(const std::string &scopeName) {
		if (scopeName.size() > 0) {
			SymbolTable::setScopeName(scopeName);
		}

		// Increment existing scope level.
		if (SymbolTable::symbols.find(SymbolTable::getScopeName()) == SymbolTable::symbols.end()) {
			// Entering the scope of a new thread or function.
			SymbolTable::symbols[SymbolTable::getScopeName()].push_back(std::vector<std::map<forec::ast::PrimaryExpression *, std::string > >());
			SymbolTable::symbols[SymbolTable::getScopeName()].back().push_back(std::map<forec::ast::PrimaryExpression *, std::string >());
		} else {
			// Entering a new scope within the the current thread or function.
			SymbolTable::currentLevel++;
			
			// Increase the scoping if not deep enough.
			if (SymbolTable::currentLevel > (SymbolTable::symbols[SymbolTable::getScopeName()].size() - 1)) {
				SymbolTable::symbols[SymbolTable::getScopeName()].push_back(std::vector<std::map<forec::ast::PrimaryExpression *, std::string > >());
			}

			// Increase the scope instance.
			SymbolTable::symbols[SymbolTable::getScopeName()][SymbolTable::currentLevel].push_back(std::map<forec::ast::PrimaryExpression *, std::string >());
		}
	}

	void SymbolTable::leaveScope(void) {
		if (SymbolTable::currentLevel == 0) {
			// If back at the scope of the program, reset.
			SymbolTable::resetScope();
		} else {
			SymbolTable::currentLevel--;
		}
	}

	// Scoping information.
	void SymbolTable::setScopeName(const std::string &name) {
		SymbolTable::scopeName = name;
	}

	const std::string SymbolTable::getScopeName(void) {
		return SymbolTable::scopeName;
	}

	const int SymbolTable::getInstance(const std::string &scopeName, const int currentLevel) {
		return SymbolTable::symbols[scopeName][currentLevel].size() - 1;
	}

	// Declarations
	// Add a symbol declaration.
	const std::string SymbolTable::addDeclaration(const std::string &type, forec::ast::PrimaryExpression &identifier) {
		// Check if the identifier has already been used in the current scope level.
		for (std::map<forec::ast::PrimaryExpression *, std::string >::const_iterator variable = SymbolTable::symbols[SymbolTable::getScopeName()][SymbolTable::currentLevel].back().begin(); variable != SymbolTable::symbols[SymbolTable::getScopeName()][SymbolTable::currentLevel].back().end(); ++variable) {
			if (identifier.getTerminal().compare(variable->first->getTerminal()) == 0) {
				throw std::string("SymbolTable::addDeclaration: " + type + " symbol \"" + identifier.getTerminal() + "\" already defined.");
			}
		}
		
		// Add symbol.
		SymbolTable::symbols[SymbolTable::getScopeName()][SymbolTable::currentLevel].back()[&identifier] = type;

		// Create the suffix.
		std::ostringstream suffix;
		if (type.compare("thread") == 0) {
			suffix << "__thread";
		} else if (type.compare("function") == 0 || type.compare("enumeration") == 0 || type.compare("extern") == 0) {
			// Do nothing. Function, enumeration, and external names are already unique.
		} else {
			suffix << "__" << SymbolTable::getScopeName() << '_' << SymbolTable::currentLevel << '_' << SymbolTable::getInstance();
		}
		
		return suffix.str();
	}

	// Find the symbol declaration.
	forec::ast::PrimaryExpression *SymbolTable::getDeclaration(const std::string &type, forec::ast::PrimaryExpression &identifier, const bool isRead, const bool isPointer) {
		// Set up the scopes to look through.
		std::vector<std::pair<std::string, std::vector<std::vector<std::map<forec::ast::PrimaryExpression *, std::string > > >::const_reverse_iterator> > startingScopes;
		startingScopes.push_back(std::pair<std::string, std::vector<std::vector<std::map<forec::ast::PrimaryExpression *, std::string > > >::const_reverse_iterator>());
		startingScopes.back().first = SymbolTable::getScopeName();
		startingScopes.back().second = SymbolTable::symbols[SymbolTable::getScopeName()].rend() - SymbolTable::currentLevel - 1;
		startingScopes.push_back(std::pair<std::string, std::vector<std::vector<std::map<forec::ast::PrimaryExpression *, std::string > > >::const_reverse_iterator>());
		startingScopes.back().first = "global";
		startingScopes.back().second = SymbolTable::symbols["global"].rbegin();

		// Go through the symbols in the current and "global" scope to find the closest variable declaration.
		for (std::vector<std::pair<std::string, std::vector<std::vector<std::map<forec::ast::PrimaryExpression *, std::string > > >::const_reverse_iterator> >::const_iterator startingScope = startingScopes.begin(); startingScope != startingScopes.end(); ++startingScope) {
			// Go up each nested scopes.
			for (std::vector<std::vector<std::map<forec::ast::PrimaryExpression *, std::string > > >::const_reverse_iterator scope = startingScope->second; scope != SymbolTable::symbols[startingScope->first].rend(); ++scope) {
				// Find the variable declaration.
				for (std::map<forec::ast::PrimaryExpression *, std::string >::const_iterator variable = scope->back().begin(); variable != scope->back().end(); ++variable) {
					if (identifier.getTerminal().compare(variable->first->getTerminal()) == 0) {
						if (SymbolTable::getScopeName().compare("global") != 0) {
							// Record the use or def of this declared symbol.
							if (isRead) {
								SymbolTable::useDef[SymbolTable::getScopeName()]["use"][variable->first] = variable->first->getType();
							}
							if (!isRead) {
								SymbolTable::useDef[SymbolTable::getScopeName()]["def"][variable->first] = variable->first->getType();
							}
						}
						
						return variable->first;
					}
				}
			}
		}

		if (type.compare("variable") == 0) {
			std::ostringstream output;
			output << "SymbolTable::getDeclaration: No declaration found for variable \"" << identifier.getTerminal() << "\" (line " << identifier.getLineNumber() << ").";
			throw output.str();
		} else {
			std::cerr << std::endl << "* SymbolTable::getDeclaration: " << type << " \"" << identifier.getTerminal() << "\" externally declared?";
		}
		
		return NULL;
	}

	// Find all symbol declarations of the same type.
	const std::map<std::string, std::set<forec::ast::PrimaryExpression *> > SymbolTable::getDeclarations(const std::string &type) {
		std::map<std::string, std::set<forec::ast::PrimaryExpression *> > declarations;
	
		// Go through the entire symbol table.
		for (std::map<std::string, std::vector<std::vector<std::map<forec::ast::PrimaryExpression *, std::string > > > >::const_iterator scopeName = SymbolTable::symbols.begin(); scopeName != SymbolTable::symbols.end(); ++scopeName) {
			for (std::vector<std::vector<std::map<forec::ast::PrimaryExpression *, std::string > > >::const_iterator scopeLevel = scopeName->second.begin(); scopeLevel != scopeName->second.end(); ++scopeLevel) {
				for (std::vector<std::map<forec::ast::PrimaryExpression *, std::string > >::const_iterator scopeInstance = scopeLevel->begin(); scopeInstance != scopeLevel->end(); ++scopeInstance) {
					for (std::map<forec::ast::PrimaryExpression *, std::string >::const_iterator variable = scopeInstance->begin(); variable != scopeInstance->end(); ++variable) {
						if (type.compare(variable->second) == 0) {
							declarations[scopeName->first].insert(variable->first);
						}
					}
				}
			}
		}

		return declarations;
	}

	// Find all symbol declarations of the same type in a given scope.
	const std::set<forec::ast::PrimaryExpression *> SymbolTable::getDeclarations(const std::string &scopeName, const std::string &type) {
		std::set<forec::ast::PrimaryExpression *> declarations;
	
		// Go through the entire symbol table.
		for (std::vector<std::vector<std::map<forec::ast::PrimaryExpression *, std::string > > >::const_iterator scopeLevel = SymbolTable::symbols[scopeName].begin(); scopeLevel != SymbolTable::symbols[scopeName].end(); ++scopeLevel) {
			for (std::vector<std::map<forec::ast::PrimaryExpression *, std::string > >::const_iterator scopeInstance = scopeLevel->begin(); scopeInstance != scopeLevel->end(); ++scopeInstance) {
				for (std::map<forec::ast::PrimaryExpression *, std::string >::const_iterator variable = scopeInstance->begin(); variable != scopeInstance->end(); ++variable) {
					if (type.compare(variable->second) == 0) {
						declarations.insert(variable->first);
					}
				}
			}
		}

		return declarations;
	}

	// Use and Def.
	std::set<forec::ast::PrimaryExpression *> SymbolTable::getUsesDefs(const bool includeUse, const bool includeDef, const std::string &scopeName, const std::string &type) {
		std::set<forec::ast::PrimaryExpression *> results;
		
		for (std::map<std::string, std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::string> > >::const_iterator scope = SymbolTable::useDef.begin(); scope != SymbolTable::useDef.end(); ++scope) {
			for (std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::string> >::const_iterator access = scope->second.begin(); access != scope->second.end(); ++access) {
				for (std::map<forec::ast::PrimaryExpression *, std::string>::const_iterator identifier = access->second.begin(); identifier != access->second.end(); ++identifier) {
					if (((access->first.compare("use") == 0 && includeUse) || (access->first.compare("def") == 0 && includeDef)) && (scope->first.compare(scopeName) == 0 || scopeName.empty()) && (identifier->second.compare(type) == 0 || type.empty())) {
						results.insert(identifier->first);
					}
				}
			}
		}
		
		return results;
	}

	std::set<forec::ast::PrimaryExpression *> SymbolTable::getOnlyUsesDefs(const bool includeUse, const bool includeDef, const std::string &scopeName, const std::string &type) {
		std::set<forec::ast::PrimaryExpression *> uses = SymbolTable::getUsesDefs(true, false, scopeName, type);
		std::set<forec::ast::PrimaryExpression *> defs = SymbolTable::getUsesDefs(false, true, scopeName, type);

		// onlyUses = uses - defs.
		std::set<forec::ast::PrimaryExpression *> onlyUseResults;
		if (includeUse) {
			std::set_difference(uses.begin(), uses.end(), defs.begin(), defs.end(), std::inserter(onlyUseResults, onlyUseResults.end()));
		}
		
		// onlyDefs = defs - uses.
		std::set<forec::ast::PrimaryExpression *> onlyDefResults;
		if (includeDef) {
			std::set_difference(defs.begin(), defs.end(), uses.begin(), uses.end(), std::inserter(onlyDefResults, onlyDefResults.end()));
		}
		
		// Aggregate the results.
		onlyUseResults.insert(onlyDefResults.begin(), onlyDefResults.end());
		return onlyUseResults;
	}

	std::map<forec::ast::PrimaryExpression *, std::set<std::string> > SymbolTable::getUsesDefsMultiple(const bool includeUse, const bool includeDef, const std::string &scopeName, const std::string &type) {
		std::map<forec::ast::PrimaryExpression *, std::set<std::string> > results;
		
		// map<scopeName, map<[use, def], map<identifier, [enumeration, storage, typedef, function, thread, label, variable, input, output, shared]> > >
		for (std::map<std::string, std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::string> > >::const_iterator scope = SymbolTable::useDef.begin(); scope != SymbolTable::useDef.end(); ++scope) {
			for (std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::string> >::const_iterator access = scope->second.begin(); access != scope->second.end(); ++access) {
				for (std::map<forec::ast::PrimaryExpression *, std::string>::const_iterator identifier = access->second.begin(); identifier != access->second.end(); ++identifier) {
					if (((access->first.compare("use") == 0 && includeUse) || (access->first.compare("def") == 0 && includeDef)) && 
						 (scope->first.compare(scopeName) == 0 || scopeName.empty()) && 
						 (identifier->second.compare(type) == 0 || type.empty()) &&
						 Threading::isThread(scope->first)) {
						results[identifier->first].insert(scope->first);
					}
				}
			}
		}

		
		return results;
	}

	// Shared variables.
	void SymbolTable::setIndirectParallelPar(const std::string &parId, std::map<forec::ast::PrimaryExpression *, std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > > > &results) {
		SymbolTable::indirectParallelVariablesPar[parId] = results;
	}
	
	void SymbolTable::setIndirectParallelThread(const std::string &threadId, std::map<forec::ast::PrimaryExpression *, std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > > > &results) {
		SymbolTable::indirectParallelVariablesThread[threadId] = results;
	}
	
	void SymbolTable::setIndirectParallelParUpdateType(const std::string &parId, forec::ast::PrimaryExpression &identifier, const std::string &useDef, SymbolTable::UpdateType updateType) {
		// map<parId, map<symbol, map<[use, def], pair<updateType, set<threadIds> > > > >
		if (SymbolTable::indirectParallelVariablesPar.find(parId) != SymbolTable::indirectParallelVariablesPar.end()) {
			if (SymbolTable::indirectParallelVariablesPar[parId].find(&identifier) != SymbolTable::indirectParallelVariablesPar[parId].end()) {
				if (SymbolTable::indirectParallelVariablesPar[parId][&identifier].find(useDef) != SymbolTable::indirectParallelVariablesPar[parId][&identifier].end()) {
					SymbolTable::indirectParallelVariablesPar[parId][&identifier][useDef].first = updateType;
				}
			}
		}
	}

	void SymbolTable::setIndirectParallelThreadUpdateType(const std::string &threadId, forec::ast::PrimaryExpression &identifier, const std::string &useDef, SymbolTable::UpdateType updateType) {
		// map<parId, map<symbol, map<[use, def], pair<updateType, set<threadIds> > > > >
		if (SymbolTable::indirectParallelVariablesThread.find(threadId) != SymbolTable::indirectParallelVariablesThread.end()) {
			if (SymbolTable::indirectParallelVariablesThread[threadId].find(&identifier) != SymbolTable::indirectParallelVariablesThread[threadId].end()) {
				if (SymbolTable::indirectParallelVariablesThread[threadId][&identifier].find(useDef) != SymbolTable::indirectParallelVariablesThread[threadId][&identifier].end()) {
					SymbolTable::indirectParallelVariablesThread[threadId][&identifier][useDef].first = updateType;
				}
			}
		}
	}
	
	std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > > SymbolTable::getIndirectParallelPar(const bool includeUse, const bool includeDef, const std::string &parId) {
		std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > > results;
		
		// map<parId, map<symbol, map<[use, def], pair<updateType, set<threadIds> > > > >
		if (SymbolTable::indirectParallelVariablesPar.find(parId) != SymbolTable::indirectParallelVariablesPar.end()) {
			for (std::map<forec::ast::PrimaryExpression *, std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > > >::const_iterator symbol = SymbolTable::indirectParallelVariablesPar[parId].begin(); symbol != SymbolTable::indirectParallelVariablesPar[parId].end(); ++symbol) {
				for (std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > >::const_iterator useDef = symbol->second.begin(); useDef != symbol->second.end(); ++useDef) {
					if ((useDef->first.compare("use") == 0 && includeUse) || (useDef->first.compare("def") == 0 && includeDef)) {
						results[symbol->first].first = useDef->second.first;
						results[symbol->first].second.insert(useDef->second.second.begin(), useDef->second.second.end());
					}
				}
			}
		}
		
		return results;
	}
	
	std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > > SymbolTable::getIndirectParallelThread(const bool includeUse, const bool includeDef, const std::string &threadId) {
		std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > > results;
		
		// map<parId, map<symbol, map<[use, def], pair<updateType, set<threadIds> > > > >
		if (SymbolTable::indirectParallelVariablesThread.find(threadId) != SymbolTable::indirectParallelVariablesThread.end()) {
			for (std::map<forec::ast::PrimaryExpression *, std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > > >::const_iterator symbol = SymbolTable::indirectParallelVariablesThread[threadId].begin(); symbol != SymbolTable::indirectParallelVariablesThread[threadId].end(); ++symbol) {
				for (std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > >::const_iterator useDef = symbol->second.begin(); useDef != symbol->second.end(); ++useDef) {
					if ((useDef->first.compare("use") == 0 && includeUse) || (useDef->first.compare("def") == 0 && includeDef)) {
						results[symbol->first] = useDef->second;
					}
				}
			}
		}
		
		return results;
	}

	const std::string SymbolTable::resolveSharedSuffix(forec::ast::PrimaryExpression &identifier, forec::ast::PrimaryExpression &declaration, const bool suppressValueElement, const bool suppressCopySuffix) {
		std::ostringstream suffix;
		if (&identifier != &declaration) {
			const std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > > indirectParallelThreadUseDef = SymbolTable::getIndirectParallelThread(true, true, identifier.getScope());
			const SymbolTable::UpdateType updateType = indirectParallelThreadUseDef.find(identifier.getDeclaration())->second.first;
			if (!suppressCopySuffix && updateType == SymbolTable::intermediate) {
				suffix << "_copy_" << identifier.getScope() << "_local";
			}
			if (!suppressValueElement) {
				suffix << ".value";
			}
		}
		
		return suffix.str();
	}
	
	// Combine functions
	void SymbolTable::addCombineSpecifier(const std::string &specifier) {
		SymbolTable::combineSpecifiers.insert(specifier);
	}
	
	const std::set<std::string> SymbolTable::getCombineSpecifiers(void) {
		return SymbolTable::combineSpecifiers;
	}

	// All variables that need a combine function.
	std::set<forec::ast::PrimaryExpression *> SymbolTable::getCombineNeeded(void) {
		std::set<forec::ast::PrimaryExpression *> combineNeeded;
		for (std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > > > >::const_iterator parId = SymbolTable::indirectParallelVariablesPar.begin(); parId != SymbolTable::indirectParallelVariablesPar.end(); ++parId) {
			for (std::map<forec::ast::PrimaryExpression *, std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > > >::const_iterator symbol = parId->second.begin(); symbol != parId->second.end(); ++symbol) {
				if (symbol->second.find("def") != symbol->second.end()) {
					if (symbol->second.find("def")->second.second.size() > 1) {
						combineNeeded.insert(symbol->first);
					}
				}
			}
		}
		return combineNeeded;
	}
	
	// All variables with a combine function.
	std::set<forec::ast::PrimaryExpression *> SymbolTable::getCombineSpecified(void) {
		std::set<forec::ast::PrimaryExpression *> combineSpecified;
		const std::map<std::string, std::set<forec::ast::PrimaryExpression *> > sharedDeclarations = SymbolTable::getDeclarations("shared");
		for (std::map<std::string, std::set<forec::ast::PrimaryExpression *> >::const_iterator scope = sharedDeclarations.begin(); scope != sharedDeclarations.end(); ++scope) {
			for (std::set<forec::ast::PrimaryExpression *>::const_iterator symbol = scope->second.begin(); symbol != scope->second.end(); ++symbol) {
				if ((*symbol)->getCombineSpecifier() != NULL) {
					combineSpecified.insert(*symbol);
				}
			}
		}
		
		const std::map<std::string, std::set<forec::ast::PrimaryExpression *> > sharedConstDeclarations = SymbolTable::getDeclarations("sharedConst");
		for (std::map<std::string, std::set<forec::ast::PrimaryExpression *> >::const_iterator scope = sharedConstDeclarations.begin(); scope != sharedConstDeclarations.end(); ++scope) {
			for (std::set<forec::ast::PrimaryExpression *>::const_iterator symbol = scope->second.begin(); symbol != scope->second.end(); ++symbol) {
				if ((*symbol)->getCombineSpecifier() != NULL) {
					combineSpecified.insert(*symbol);
				}
			}
		}
		
		return combineSpecified;
	}
	
	const std::string SymbolTable::toString(void) {
		std::ostringstream output;

		output << "==============================" << std::endl;
		output << "tools::SymbolTable::toString()" << std::endl;
		output << "==============================" << std::endl;

		output << "Symbol tables:" << std::endl;
		output << "--------------" << std::endl;

		// Delete empty trailing tables
		for (std::map<std::string, std::vector<std::vector<std::map<forec::ast::PrimaryExpression *, std::string > > > >::iterator scopeName = SymbolTable::symbols.begin(); scopeName != SymbolTable::symbols.end(); ++scopeName) {
			if (scopeName->second.size() > 0) {
				for (std::vector<std::vector<std::map<forec::ast::PrimaryExpression *, std::string > > >::reverse_iterator scopeLevel = scopeName->second.rbegin(); scopeLevel != scopeName->second.rend(); ++scopeLevel) {
					for (std::vector<std::map<forec::ast::PrimaryExpression *, std::string > >::reverse_iterator scopeInstance = scopeLevel->rbegin(); scopeInstance != scopeLevel->rend(); ++scopeInstance) {
						// Delete (in reverse) until a used table is encountered.
						if (scopeInstance->empty()) {
							int offset = scopeLevel->rend() - scopeInstance - 1;
							scopeLevel->erase(scopeLevel->begin() + offset);
						} else {
							break;
						}
					}

					// Delete the entire scope level if there are no instances and it is the last.
					if (scopeLevel->size() == 0 && scopeLevel == scopeName->second.rbegin()) {
						int offset = scopeName->second.rend() - scopeLevel - 1;
						scopeName->second.erase(scopeName->second.begin() + offset);
					}
				}
			}
		}

		for (std::map<std::string, std::vector<std::vector<std::map<forec::ast::PrimaryExpression *, std::string > > > >::const_iterator scope = SymbolTable::symbols.begin(); scope != SymbolTable::symbols.end(); ++scope) {
			if (scope->second.size() > 0) {
				output << "\tScope name: " << scope->first << std::endl;

				for (std::vector<std::vector<std::map<forec::ast::PrimaryExpression *, std::string > > >::const_iterator scopeLevel = scope->second.begin(); scopeLevel != scope->second.end(); ++scopeLevel) {
					output << "\t\tScope level: " << (scopeLevel - scope->second.begin()) << std::endl;

					for (std::vector<std::map<forec::ast::PrimaryExpression *, std::string > >::const_iterator scopeInstance = scopeLevel->begin(); scopeInstance != scopeLevel->end(); ++scopeInstance) {
						output << "\t\t\tInstance: " << (scopeInstance - scopeLevel->begin()) << std::endl;

						for (std::map<forec::ast::PrimaryExpression *, std::string >::const_iterator symbol = scopeInstance->begin(); symbol != scopeInstance->end(); ++symbol) {
							output << "\t\t\t\t(" << symbol->second << ") " << *symbol->first << std::endl;
						}
					}

					if (scopeLevel->size() == 0) {
						output << std::endl;
					}
				}
				output << std::endl;
			}
		}
		output << std::endl;
		
		output << "Declared shared symbols:" << std::endl;
		output << "------------------------" << std::endl;
		const std::map<std::string, std::set<forec::ast::PrimaryExpression *> > scopedShared = SymbolTable::getDeclarations("shared");
		for (std::map<std::string, std::set<forec::ast::PrimaryExpression *> >::const_iterator scope = scopedShared.begin(); scope != scopedShared.end(); ++scope) {
			output << "\tScope name: " << scope->first << std::endl;
			
			for (std::set<forec::ast::PrimaryExpression *>::const_iterator symbol = scope->second.begin(); symbol != scope->second.end(); ++symbol) {
				output << "\t\t(" << *(*symbol)->getSpecifiers() << ") " << *(*symbol) << std::endl;
			}
			
			output << std::endl;
		}
		const std::map<std::string, std::set<forec::ast::PrimaryExpression *> > scopedSharedConst = SymbolTable::getDeclarations("sharedConst");
		for (std::map<std::string, std::set<forec::ast::PrimaryExpression *> >::const_iterator scope = scopedSharedConst.begin(); scope != scopedSharedConst.end(); ++scope) {
			output << "\tScope name: " << scope->first << std::endl;
			
			for (std::set<forec::ast::PrimaryExpression *>::const_iterator symbol = scope->second.begin(); symbol != scope->second.end(); ++symbol) {
				output << "\t\t(" << *(*symbol)->getSpecifiers() << ") " << *(*symbol) << std::endl;
			}
			
			output << std::endl;
		}
		output << std::endl;
		
		output << "Use/Def of symbols:" << std::endl;
		output << "-------------------" << std::endl;
		
		// Delete empty scopes.
		std::set<std::string> emptyUseDefScopes;
		for (std::map<std::string, std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::string> > >::iterator scope = SymbolTable::useDef.begin(); scope != SymbolTable::useDef.end(); ++scope) {
			// Delete empty accesses.
			std::set<std::string> emptyAccesses;
			for (std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::string> >::iterator access = scope->second.begin(); access != scope->second.end(); ++access) {
				if (access->second.empty()) {
					emptyAccesses.insert(access->first);
				}
			}
			
			for (std::set<std::string>::const_iterator access = emptyAccesses.begin(); access != emptyAccesses.end(); ++access) {
				scope->second.erase(*access);
			}
			
			if (scope->second.empty()) {
				emptyUseDefScopes.insert(scope->first);
			}
		}
		
		for (std::set<std::string>::const_iterator scope = emptyUseDefScopes.begin(); scope != emptyUseDefScopes.end(); ++scope) {
			SymbolTable::useDef.erase(*scope);
		}
		
		for (std::map<std::string, std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::string> > >::const_iterator scope = SymbolTable::useDef.begin(); scope != SymbolTable::useDef.end(); ++scope) {
			output << "\tScope name: " << scope->first << std::endl;
			
			for (std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::string> >::const_iterator access = scope->second.begin(); access != scope->second.end(); ++access) {
				output << "\t\t" << access->first << ':' << std::endl;
			
				for (std::map<forec::ast::PrimaryExpression *, std::string>::const_iterator symbol = access->second.begin(); symbol != access->second.end(); ++symbol) {
					output << "\t\t\t(" << symbol->second << ") " << *symbol->first << std::endl;
				}
				output << std::endl;
			}
		}
		output << std::endl;

		output << "Indirect use/def of symbols by parId:" << std::endl;
		output << "-------------------------------------" << std::endl;
		
		for (std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > > > >::const_iterator parId = SymbolTable::indirectParallelVariablesPar.begin(); parId != SymbolTable::indirectParallelVariablesPar.end(); ++parId) {
			output << '\t' << parId->first << ':' << std::endl;
			
			for (std::map<forec::ast::PrimaryExpression *, std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > > >::const_iterator symbol = parId->second.begin(); symbol != parId->second.end(); ++symbol) {
				output << "\t\t" << *symbol->first << std::endl;
				
				for (std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > >::const_iterator useDef = symbol->second.begin(); useDef != symbol->second.end(); ++useDef) {
					output << "\t\t\t" << useDef->first << " (";
					switch (useDef->second.first) {
						case (SymbolTable::skip):			output << "skip";
															break;
															
						case (SymbolTable::intermediate):	output << "intermediate";
															break;
															
						case (SymbolTable::root):			output << "root";
															break;
															
						default:							output << "unknown";
															break;
					}
					output << "): ";
					
					for (std::set<std::string>::const_iterator threadId = useDef->second.second.begin(); threadId != useDef->second.second.end(); ++threadId) {
						output << *threadId << ' ';
					}
					output << std::endl;
				}
				output << std::endl;
			}
		}
		output << std::endl;

		output << "Indirect use/def of symbols by threadId:" << std::endl;
		output << "----------------------------------------" << std::endl;
		
		for (std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > > > >::const_iterator threadId = SymbolTable::indirectParallelVariablesThread.begin(); threadId != SymbolTable::indirectParallelVariablesThread.end(); ++threadId) {
			output << '\t' << threadId->first << ':' << std::endl;
			
			for (std::map<forec::ast::PrimaryExpression *, std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > > >::const_iterator symbol = threadId->second.begin(); symbol != threadId->second.end(); ++symbol) {
				output << "\t\t" << *symbol->first << std::endl;
				
				for (std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > >::const_iterator useDef = symbol->second.begin(); useDef != symbol->second.end(); ++useDef) {
					output << "\t\t\t" << useDef->first << " (";
					switch (useDef->second.first) {
						case (SymbolTable::skip):			output << "skip";
															break;
															
						case (SymbolTable::intermediate):	output << "intermediate";
															break;
															
						case (SymbolTable::root):			output << "root";
															break;
															
						default:							output << "unknown";
															break;
					}
					output << "): ";
					
					for (std::set<std::string>::const_iterator threadId = useDef->second.second.begin(); threadId != useDef->second.second.end(); ++threadId) {
						output << *threadId << ' ';
					}
					output << std::endl;
				}
				output << std::endl;
			}
		}
		output << std::endl;

		output << "Functions used for combining shared variables:" << std::endl;
		output << "----------------------------------------------" << std::endl;
		for (std::set<std::string>::const_iterator specifier = SymbolTable::combineSpecifiers.begin(); specifier != SymbolTable::combineSpecifiers.end(); ++specifier) {
			output << '\t' << *specifier << std::endl;
		}
		output << std::endl;

		return output.str();
	}


	const std::string SymbolTable::outputXml(const std::string &indent) {
		std::ostringstream output;
		
		output << indent << "<!-- Shared variables (SymbolTable.cpp::outputXml). -->" << std::endl;
		output << indent << "<shared>" << std::endl;

		// Clean the results.
		std::map<std::string, std::vector<forec::ast::ParStatement *> > cleanedThreadPar;
		const std::set<std::string> threadScopes = Threading::getDeclared();		
		for (std::set<std::string>::const_iterator threadScope = threadScopes.begin(); threadScope != threadScopes.end(); ++threadScope) {		
			const std::vector<forec::ast::ParStatement *> parStatements = Threading::getParStatements(*threadScope);
			for (std::vector<forec::ast::ParStatement *>::const_iterator parStatement = parStatements.begin(); parStatement != parStatements.end(); ++parStatement) {
				const std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > > parallelSharedDef = SymbolTable::getIndirectParallelPar(false, true, (*parStatement)->getId());
				for (std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > >::const_iterator variable = parallelSharedDef.begin(); variable != parallelSharedDef.end(); ++variable) {
					if (variable->second.first != SymbolTable::skip) {
						const int numberOfDefiners = variable->second.second.size();
						if (numberOfDefiners > 0) {
							cleanedThreadPar[*threadScope];
							cleanedThreadPar[*threadScope].push_back(*parStatement);
							break;
						}
					}
				}
			}
		}
		
		for (std::map<std::string, std::vector<forec::ast::ParStatement *> >::const_iterator threadScope = cleanedThreadPar.begin(); threadScope != cleanedThreadPar.end(); ++threadScope) {
			output << indent << "\t<threadScope id=\"" << threadScope->first << "\">" << std::endl;

			for (std::vector<forec::ast::ParStatement *>::const_iterator parStatement = threadScope->second.begin(); parStatement != threadScope->second.end(); ++parStatement) {
				output << indent << "\t\t<par id=\"" << (*parStatement)->getIdNumber() << "\">" << std::endl;

				// map<symbol, pair<updateType, set<threadIds> > >
				const std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > > parallelSharedDef = SymbolTable::getIndirectParallelPar(false, true, (*parStatement)->getId());
				for (std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > >::const_iterator variable = parallelSharedDef.begin(); variable != parallelSharedDef.end(); ++variable) {
					if (variable->second.first != SymbolTable::skip) {
						const int numberOfDefiners = variable->second.second.size();
						if (numberOfDefiners > 0) {
							output << indent << "\t\t\t<variable id=\"" << *variable->first << "\" defines=\"" << numberOfDefiners << "\"";
							if (numberOfDefiners > 1) {
								output << " combine=\"" << ((forec::ast::CombineSpecifier *)variable->first->getCombineSpecifier())->getTerminal() << "\"";
							}
							output << "/>" << std::endl;
						}
					}
				}
				output << indent << "\t\t</par>" << std::endl;
			}
			output << indent << "\t</threadScope>" << std::endl;
		}
		output << indent << "</shared>" << std::endl;
		
		return output.str();
	}
}

