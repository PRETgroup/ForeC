/*
 *  ThreadDefinition.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "ThreadDefinition.hpp"

#include "BlockItemList.hpp"
#include "Declaration.hpp"
#include "ParStatement.hpp"
#include "PrimaryExpression.hpp"

#include "../tarot/Tarot.hpp"
#include "../tarot/Thread.hpp"

#include "../tools/Query.hpp"
#include "../tools/SymbolTable.hpp"
#include "../tools/Template.hpp"
#include "../tools/Threading.hpp"

#include <algorithm>

namespace forec {
	namespace ast {

		// Initialise static variable
		int ThreadDefinition::globalCount = 0;

		ThreadDefinition::ThreadDefinition(Node &node0, Node &node1, const std::string &variant) : Node("ThreadDefinition", variant, this->globalCount++) {
			std::vector<Node *> identifiersFound = tools::Query::retrieveAll(node0, "PrimaryExpression", "identifier");
			identifier = ((PrimaryExpression *)identifiersFound[0])->getTerminal();
			tools::SymbolTable::setScopeName(identifier);
			tools::Threading::addDeclaration(identifier, *this);

			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		void ThreadDefinition::takeOutDeclarations(void) {
			privateDeclarations.clear();
			
			std::vector<Node *> declarationsFound = tools::Query::retrieveAll(*children.back(), "Declaration");
			for (std::vector<Node *>::iterator declaration = declarationsFound.begin(); declaration != declarationsFound.end(); ++declaration) {
				((Declaration *)*declaration)->takeOutDeclarations(privateDeclarations);
			}
		}

		const std::string ThreadDefinition::getId(void) const {
			return identifier;
		}

		int ThreadDefinition::getCount(void) {
			return globalCount;
		}

		void ThreadDefinition::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			tools::Threading::setCurrentName(identifier);
			tools::SymbolTable::enterScope(identifier);

			children.back()->updateSymbolTable("thread");
		}
		
		// map<variable, map<[use, def], pair<updateType, set<threadIds> > > >
		std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > > ThreadDefinition::pullUpIndirectParallelVariables(void) {
			std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > > indirectParallelVariables;
				
			// Collect all the child thread's indirect variable accesses. Set the accesses as sequential. Set this thread as the indirect accessor.
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > > subResults = (*i)->pullUpIndirectParallelVariables();
				for (std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > >::iterator variable = subResults.begin(); variable != subResults.end(); ++variable) {
					for (std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > >::iterator useDef = variable->second.begin(); useDef != variable->second.end(); ++useDef) {
						indirectParallelVariables[variable->first][useDef->first].first = tools::SymbolTable::skip;
						indirectParallelVariables[variable->first][useDef->first].second.insert(identifier);
					}
				}
			}
		
			// Find this thread's local uses and defines.
			std::map<std::string, std::set<PrimaryExpression *> > localUseDef;
			std::set<PrimaryExpression *> subResults;
			// Uses.
			subResults = tools::SymbolTable::getUsesDefs(true, false, identifier, "shared");
			localUseDef["use"].insert(subResults.begin(), subResults.end());
			subResults = tools::SymbolTable::getUsesDefs(true, false, identifier, "variable");
			localUseDef["use"].insert(subResults.begin(), subResults.end());
			//Defines.
			subResults = tools::SymbolTable::getUsesDefs(false, true, identifier, "shared");
			localUseDef["def"].insert(subResults.begin(), subResults.end());
			subResults = tools::SymbolTable::getUsesDefs(false, true, identifier, "variable");
			localUseDef["def"].insert(subResults.begin(), subResults.end());
			// Add this thread's access to non-local shared variables.
			const std::set<forec::ast::PrimaryExpression *> declarations = tools::SymbolTable::getDeclarations(identifier, "shared");
			for (std::map<std::string, std::set<PrimaryExpression *> >::const_iterator useDef = localUseDef.begin(); useDef != localUseDef.end(); ++useDef) {
				for (std::set<PrimaryExpression *>::const_iterator variable = useDef->second.begin(); variable != useDef->second.end(); ++variable) {
					if (declarations.count(*variable) == 0) {
						indirectParallelVariables[*variable][useDef->first].first = tools::SymbolTable::skip;
						indirectParallelVariables[*variable][useDef->first].second.insert(identifier);
					}
				}
			}
			
			if (!indirectParallelVariables.empty()) {
				tools::SymbolTable::setIndirectParallelThread(identifier, indirectParallelVariables);
			}
			
			return indirectParallelVariables;
		}

		void ThreadDefinition::pullDownIndirectParallelVariables(std::set<PrimaryExpression *> &definedVariables) {
			std::set<PrimaryExpression *> usesDefs = tools::SymbolTable::getUsesDefs(true, true, identifier, "shared");
			for (std::set<PrimaryExpression *>::const_iterator variable = usesDefs.begin(); variable != usesDefs.end(); ++variable) {
				tools::SymbolTable::setIndirectParallelThreadUpdateType(identifier, *(*variable), "use", tools::SymbolTable::root);
				tools::SymbolTable::setIndirectParallelThreadUpdateType(identifier, *(*variable), "def", tools::SymbolTable::root);
			}
			
			for (std::set<PrimaryExpression *>::const_iterator variable = definedVariables.begin(); variable != definedVariables.end(); ++variable) {
				tools::SymbolTable::setIndirectParallelThreadUpdateType(identifier, *(*variable), "use", tools::SymbolTable::intermediate);
				tools::SymbolTable::setIndirectParallelThreadUpdateType(identifier, *(*variable), "def", tools::SymbolTable::intermediate);
			}

			std::set<PrimaryExpression *> definedVariablesBefore = definedVariables;
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->pullDownIndirectParallelVariables(definedVariables);
			}
			
			for (std::set<PrimaryExpression *>::const_iterator variable = definedVariables.begin(); variable != definedVariables.end(); ++variable) {
				if (definedVariablesBefore.count(*variable) == 0) {
					tools::SymbolTable::setIndirectParallelThreadUpdateType(identifier, *(*variable), "use", tools::SymbolTable::root);
					tools::SymbolTable::setIndirectParallelThreadUpdateType(identifier, *(*variable), "def", tools::SymbolTable::root);
				}
			}
		}

		void ThreadDefinition::createTarot(const std::string &threadScope) {
			tarot::Thread *threadTarot = new tarot::Thread(identifier, this);
			children.back()->createTarot(identifier, *threadTarot);
			tarot::Tarot::addThread(identifier, *threadTarot);
		}
		
		const Node::Instantaneous ThreadDefinition::willPause(const bool requireBothBranches) {
			if (!instantaneous.found) {
				instantaneous = children.back()->willPause(requireBothBranches);
				instantaneous.breaks = false;
				instantaneous.continues = false;
				instantaneous.returns = false;

				instantaneous.found = true;
			}

			return instantaneous;
		}
		
		void ThreadDefinition::prettyPrint(std::ostream &output) {
			std::ostringstream declarationString;
			
			// Create local copies of shared variables.
			const std::map<forec::ast::PrimaryExpression *, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > indirectParallelThreadUseDef = tools::SymbolTable::getIndirectParallelThread(true, true, identifier);
			for (std::map<forec::ast::PrimaryExpression *, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > >::const_iterator variable = indirectParallelThreadUseDef.begin(); variable != indirectParallelThreadUseDef.end(); ++variable) {
				if (variable->second.first == tools::SymbolTable::intermediate) {
					declarationString << tools::Tab::toString() << *variable->first->getSpecifiers() << ' ' << *variable->first << "_copy_" << identifier << "_local;" << std::endl;
				}
			}

			// Declarations in the thread body.
			if (!privateDeclarations.empty()) {
				BlockItemList localDeclarations(*privateDeclarations[0]);
				for (std::vector<Node *>::const_iterator declaration = privateDeclarations.begin() + 1; declaration != privateDeclarations.end(); ++declaration) {
					localDeclarations.append(*(*declaration));
				}
				
				declarationString << localDeclarations << std::endl;
			}

			if (declarationString.str().empty()) {
				declarationString << tools::Tab::toString() << "// No declarations." << std::endl;
			}
			
			tools::Tab::indent();
			const std::vector<Node *> blockItemList = tools::Query::retrieveChildren(*children.back(), "BlockItemList");
			output << tools::Template::formatThread(declarationString.str(), identifier, blockItemList);
			tools::Tab::dedent();
		}

	}
}
