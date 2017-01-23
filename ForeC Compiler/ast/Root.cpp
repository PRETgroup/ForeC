/*
 *  Root.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Root.hpp"

#include "FunctionDefinition.hpp"
#include "PrimaryExpression.hpp"

#include "../tools/Function.hpp"
#include "../tools/Query.hpp"
#include "../tools/SymbolTable.hpp"
#include "../tools/Template.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int Root::globalCount = 0;

		Root::Root(const std::string &variant) : Node("Root", variant, this->globalCount++) {

		}
		
		void Root::append(Node &node) {
			children.push_back(&node);
			
			node.setParent((Node *)this);
		}

		const int Root::getCount(void) {
			return globalCount;
		}
		
		const std::string Root::getSpacing(Node &node) {
			if (node.has("FunctionDefinition", "none")) {
				return "separateFunctions";
			} else if (node.has("ThreadDefinition", "none")) {
				return "separateThreads";
			} else if (node.has("StructUnionSpecifier", "definition") || node.has("StructUnionSpecifier", "anonymous") || node.has("EnumSpecifier", "none") || node.has("FunctionDefinition", "none") || node.has("ThreadDefinition", "none")) {
				return "separateStorages";
			} else if (node.has("Declaration", "threadDeclaration")) {
				return "groupThreadDeclarations";
			} else if (node.has("DirectDeclarator", "function0") || node.has("DirectDeclarator", "function1")) {
				return "groupFunctionDeclarations";
			} else if (node.has("TypeQualifier", "input") || node.has("TypeQualifier", "output")) {
				return "groupIOs";
			} else if (node.has("TypeQualifier", "shared")) {
				return "groupShared";
			} else if (node.has("PreProcessorDirective", "include")) {
				return "groupPreProcessorInclude";
			} else if (node.has("PreProcessorDirective", "define")) {
				return "groupPreProcessorDefine";
			}
			
			return "groupOthers";
		}
		
		std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > > Root::pullUpIndirectParallelVariables(void) {
			FunctionDefinition *function = tools::Function::getDeclaration("main");
			std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > > subResults = function->pullUpIndirectParallelVariables();
			for (std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > >::iterator variable = subResults.begin(); variable != subResults.end(); ++variable) {
				for (std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > >::iterator useDef = variable->second.begin(); useDef != variable->second.end(); ++useDef) {
					useDef->second.first = tools::SymbolTable::skip;
					useDef->second.second.clear();
					useDef->second.second.insert("main");
				}
			}

			tools::SymbolTable::setIndirectParallelThread("main", subResults);
			
			return subResults;
		}
		
		void Root::pullDownIndirectParallelVariables(std::set<PrimaryExpression *> &definedVariables) {
			// Get all variables defined by the thread.
			const std::set<PrimaryExpression *> defs = tools::SymbolTable::getUsesDefs(false, true, "main", "shared");
			
			for (std::set<PrimaryExpression *>::const_iterator variable = defs.begin(); variable != defs.end(); ++variable) {
				if (definedVariables.count(*variable) == 0) {
					tools::SymbolTable::setIndirectParallelThreadUpdateType("main", *(*variable), "use", tools::SymbolTable::root);
					tools::SymbolTable::setIndirectParallelThreadUpdateType("main", *(*variable), "def", tools::SymbolTable::root);
				} else {
					tools::SymbolTable::setIndirectParallelThreadUpdateType("main", *(*variable), "use", tools::SymbolTable::intermediate);
					tools::SymbolTable::setIndirectParallelThreadUpdateType("main", *(*variable), "def", tools::SymbolTable::intermediate);
				}
			}

			std::set<PrimaryExpression *> definedVariablesBefore = definedVariables;
			FunctionDefinition *function = tools::Function::getDeclaration("main");
			function->pullDownIndirectParallelVariables(definedVariables);

			for (std::set<PrimaryExpression *>::const_iterator variable = definedVariables.begin(); variable != definedVariables.end(); ++variable) {
				if (definedVariablesBefore.count(*variable) == 0) {
					tools::SymbolTable::setIndirectParallelThreadUpdateType("main", *(*variable), "use", tools::SymbolTable::root);
					tools::SymbolTable::setIndirectParallelThreadUpdateType("main", *(*variable), "def", tools::SymbolTable::root);
				}
			}
		}
		
		const struct Node::Instantaneous Root::willPause(const bool requireBothBranches) {
			FunctionDefinition *function = tools::Function::getDeclaration("main");
			return function->willPause(requireBothBranches);
		}
		
		void Root::prettyPrint(std::ostream &output) {
			output << tools::Template::formatGlobal();

			if (children.size() > 0) {	
				std::string lastSpacing = getSpacing(*children[0]);
		
				output << tools::Tab::toString() << *children[0] << std::endl;
				for (std::vector<Node *>::iterator i = children.begin() + 1; i != children.end(); ++i) {
					std::string currentSpacing = getSpacing(*(*i));
					if (currentSpacing.find("separate") != std::string::npos || (currentSpacing.find("group") != std::string::npos && currentSpacing.compare(lastSpacing) != 0)) {
						output << std::endl;
					}

					output << *(*i) << std::endl;
				
					lastSpacing = currentSpacing;
				}
			}
		}

	}
}

