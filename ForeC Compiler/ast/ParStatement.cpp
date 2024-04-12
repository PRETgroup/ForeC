/*
 *  ParStatement.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "ParStatement.hpp"

#include "PrimaryExpression.hpp"
#include "ThreadDefinition.hpp"

#include "../tarot/Tarot.hpp"
#include "../tarot/Node.hpp"
#include "../tarot/Par.hpp"

#include "../tools/Query.hpp"
#include "../tools/Threading.hpp"
#include "../tools/Abort.hpp"
#include "../tools/Condition.hpp"
#include "../tools/Multicore.hpp"
#include "../tools/SymbolTable.hpp"
#include "../tools/Template.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int ParStatement::globalCount = 0;

		ParStatement::ParStatement(Node &node, const std::string &variant) : Node("ParStatement", variant, this->globalCount++) {
			std::vector<Node *> identifiersFound = tools::Query::retrieveAll(node, "PrimaryExpression", "identifier");
			for (std::vector<Node *>::iterator i = identifiersFound.begin(); i != identifiersFound.end(); ++i) {
				threadIds.push_back(((PrimaryExpression *)*i)->getTerminal());
			}

			children.push_back(&node);

			node.setParent((Node *)this);
		}

		const std::string ParStatement::getId(void) const {
			std::ostringstream name;
			name << "par" << id;
			return name.str();
		}

		int ParStatement::getCount(void) {
			return globalCount;
		}
		
		const std::string ParStatement::getThreadScope(void) const {
			return threadScope;
		}
			
		const std::vector<std::string> ParStatement::getThreadIds(void) const {
			return threadIds;
		}
		
		const bool ParStatement::hasThreadId(const std::string &threadId) const {
			for (std::vector<std::string>::const_iterator currentThreadId = threadIds.begin(); currentThreadId != threadIds.end(); ++currentThreadId) {
				if (currentThreadId->compare(threadId) == 0) {
					return true;
				}
			}

			return false;
		}

		void ParStatement::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			threadScope = tools::Threading::addParStatement(*this);
			
			tools::Abort::addParStatement(*this);
			tools::Condition::addParStatement(*this);

			children.back()->updateSymbolTable("thread", true, isRead);
		}

		// map<variable, map<[use, def], pair<updateType, set<threadIds> > > >
		std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > > ParStatement::pullUpIndirectParallelVariables(void) {
			std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > > indirectParallelVariables;
		
			// Collect all the child thread's indirect variables. Determine if the variables are used/defined in parallel.
			for (std::vector<std::string>::const_iterator currentThreadId = threadIds.begin(); currentThreadId != threadIds.end(); ++currentThreadId) {
				ThreadDefinition *thread = tools::Threading::getDeclaration(*currentThreadId);
				std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > > subResults = thread->pullUpIndirectParallelVariables();
				for (std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > >::iterator variable = subResults.begin(); variable != subResults.end(); ++variable) {
					for (std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > >::iterator useDef = variable->second.begin(); useDef != variable->second.end(); ++useDef) {
						indirectParallelVariables[variable->first][useDef->first].first = tools::SymbolTable::skip;
						indirectParallelVariables[variable->first][useDef->first].second.insert(*currentThreadId);
					}
				}
			}
			
			tools::SymbolTable::setIndirectParallelPar(getId(), indirectParallelVariables);
			
			return indirectParallelVariables;
		}
		
		void ParStatement::pullDownIndirectParallelVariables(std::set<PrimaryExpression *> &definedVariables) {
			// Get all variables defined by the parent thread.
			std::set<PrimaryExpression *> parentUsesDefs = tools::SymbolTable::getUsesDefs(true, true, threadScope, "shared");
			const std::map<forec::ast::PrimaryExpression *, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > parentIndirectParallelUseDef = tools::SymbolTable::getIndirectParallelThread(true, true, threadScope);
			
			// Get all the indirectly defined variables from the child threads.
			const std::map<forec::ast::PrimaryExpression *, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > indirectParallelDef = tools::SymbolTable::getIndirectParallelPar(false, true, getId());
			const std::map<forec::ast::PrimaryExpression *, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > indirectParallelUseDef = tools::SymbolTable::getIndirectParallelPar(true, true, getId());
			for (std::map<forec::ast::PrimaryExpression *, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > >::const_iterator variable = indirectParallelUseDef.begin(); variable != indirectParallelUseDef.end(); ++variable) {
				// Check if each indirectly accessed variable has already been defined.
				tools::SymbolTable::UpdateType parentUpdateType = parentIndirectParallelUseDef.find(variable->first)->second.first;
				
				if (parentUpdateType != tools::SymbolTable::intermediate || definedVariables.count(variable->first) == 0) {
					// Check if propagation is needed.
					int numberOfDefs = 0;
					if (indirectParallelDef.find(variable->first) != indirectParallelDef.end()) {
						numberOfDefs = indirectParallelDef.find(variable->first)->second.second.size();
					}
					const bool isRoot = (numberOfDefs > 0 && variable->second.second.size() > 1) || (parentUsesDefs.count(variable->first) > 0);	// Parallel accesses or first definition.
					if (isRoot) {
						// First par with parallel variable access, or the parent thread defines the variable.
						tools::SymbolTable::setIndirectParallelParUpdateType(this->getId(), *variable->first, "use", tools::SymbolTable::root);
						tools::SymbolTable::setIndirectParallelParUpdateType(this->getId(), *variable->first, "def", tools::SymbolTable::root);
						definedVariables.insert(variable->first);

					} else {
						// Not defined so far.
						tools::SymbolTable::setIndirectParallelParUpdateType(this->getId(), *variable->first, "use", tools::SymbolTable::skip);
						tools::SymbolTable::setIndirectParallelParUpdateType(this->getId(), *variable->first, "def", tools::SymbolTable::skip);
					}
				} else {
					// Already defined.
					tools::SymbolTable::setIndirectParallelParUpdateType(this->getId(), *variable->first, "use", tools::SymbolTable::intermediate);
					tools::SymbolTable::setIndirectParallelParUpdateType(this->getId(), *variable->first, "def", tools::SymbolTable::intermediate);
				}
			}
			
			// Propagate the defined variables.
			for (std::vector<std::string>::const_iterator currentThreadId = threadIds.begin(); currentThreadId != threadIds.end(); ++currentThreadId) {
				std::set<PrimaryExpression *> definedVariablesCopy = definedVariables;
				ThreadDefinition *thread = tools::Threading::getDeclaration(*currentThreadId);
				thread->pullDownIndirectParallelVariables(definedVariablesCopy);
			}
		}

		void ParStatement::createTarot(const std::string &threadScope, tarot::Node &tarotNode) {
			tarot::Par *parTarot = new tarot::Par(threadScope, this);
			children.back()->createTarot(threadScope, *parTarot);
			tarotNode.append(*parTarot);
		}

		const Node::Instantaneous ParStatement::willPause(const bool requireBothBranches) {
			instantaneous.pauses = false;
			instantaneous.breaks = false;
			instantaneous.continues = false;
			instantaneous.returns = false;
			
			for (std::vector<std::string>::const_iterator currentThreadId = threadIds.begin(); currentThreadId != threadIds.end(); ++currentThreadId) {
				ThreadDefinition *thread = tools::Threading::getDeclaration(*currentThreadId);
				const struct Node::Instantaneous result = thread->willPause(requireBothBranches);
				instantaneous.pauses = instantaneous.pauses || result.pauses;
			}
			
			return instantaneous;
		}

		void ParStatement::prettyPrint(std::ostream &output) {
			std::string parStatement = this->getId() + "(" + *children[0]->toString() + ");";

			std::string coreId = tools::Multicore::getCoreId(threadScope);

			if (threadScope.compare("main") == 0) {
				std::vector<std::pair<std::string, std::string> > linkedList = tarot::Tarot::getLinkedList(coreId, "main", this->getId());

				output << tools::Template::formatPar(this->getId(), coreId, parStatement, linkedList);
			} else {
				output << tools::Template::formatPar(this->getId(), coreId, parStatement, threadScope, this->willPause(false).pauses);
			}
		}

	}
}

