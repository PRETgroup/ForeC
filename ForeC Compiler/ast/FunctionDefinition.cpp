/*
 *  FunctionDefinition.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "FunctionDefinition.hpp"

#include "BlockItemList.hpp"
#include "Declaration.hpp"
#include "ParStatement.hpp"
#include "PrimaryExpression.hpp"

#include "../tarot/Tarot.hpp"
#include "../tarot/Thread.hpp"

#include "../tools/Function.hpp"
#include "../tools/Threading.hpp"
#include "../tools/Query.hpp"
#include "../tools/Template.hpp"
#include "../tools/SymbolTable.hpp"

namespace global {
	extern std::string embeddedMainFunctionName;
}

namespace forec {
	namespace ast {

		// Initialise static variable
		int FunctionDefinition::globalCount = 0;

		FunctionDefinition::FunctionDefinition(Node &node0, Node &node1, Node &node2, const std::string &variant) : Node("FunctionDefinition", variant, this->globalCount++) {
			std::vector<forec::ast::Node *> identifiersFound = tools::Query::retrieveAll(node1, "PrimaryExpression", "identifier");
			identifier = ((PrimaryExpression *)identifiersFound[0])->getTerminal();
			tools::SymbolTable::setScopeName(identifier);
			if (identifier.compare("main") == 0) {
				tools::Threading::addDeclaration(identifier);
			}
			tools::Function::addDeclaration(identifier, *this);

			children.push_back(&node0);
			children.push_back(&node1);
			children.push_back(&node2);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
			node2.setParent((Node *)this);
		}

		FunctionDefinition::FunctionDefinition(Node &node0, Node &node1, Node &node2, Node &node3, const std::string &variant) : Node("FunctionDefinition", variant, this->globalCount++) {
			std::vector<forec::ast::Node *> identifiersFound = tools::Query::retrieveAll(node1, "PrimaryExpression", "identifier");
			identifier = ((PrimaryExpression *)identifiersFound[0])->getTerminal();
			tools::SymbolTable::setScopeName(identifier);
			if (identifier.compare("main") == 0) {
				tools::Threading::addDeclaration(identifier);
			} else {
				tools::Function::addDeclaration(identifier, *this);
			}

			children.push_back(&node0);
			children.push_back(&node1);
			children.push_back(&node2);
			children.push_back(&node3);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
			node2.setParent((Node *)this);
			node3.setParent((Node *)this);
		}

		const std::string FunctionDefinition::getIdentifier(void) {
			return identifier;
		}

		void FunctionDefinition::setThreads(std::vector<Node *> threads) {
			(this->threads) = threads;
		}
		
		void FunctionDefinition::takeOutDeclarations(void) {
			privateDeclarations.clear();
			
			std::vector<Node *> declarationsFound = tools::Query::retrieveAll(*children.back(), "Declaration");			
			for (std::vector<Node *>::iterator declaration = declarationsFound.begin(); declaration != declarationsFound.end(); ++declaration) {
				((Declaration *)*declaration)->takeOutDeclarations(privateDeclarations);
			}
		}

		int FunctionDefinition::getCount(void) {
			return globalCount;
		}

		void FunctionDefinition::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			tools::Threading::setCurrentName(identifier);
			tools::SymbolTable::enterScope(identifier);

			std::vector<Node *> parameters = tools::Query::retrieveAll(*children[1], "ParameterList");
			for (std::vector<Node *>::iterator parameter = parameters.begin(); parameter != parameters.end(); ++parameter) {
				(*parameter)->updateSymbolTable("function");
			}

			children.front()->updateSymbolTable("typedef", true);
			children.back()->updateSymbolTable("function");
		}

		void FunctionDefinition::createTarot(const std::string &threadScope) {
			if (identifier.compare("main") == 0) {
				tarot::Thread *threadTarot = new tarot::Thread(identifier, this);

				for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
					(*i)->createTarot(identifier, *threadTarot);
				}

				tarot::Tarot::addThread(identifier, *threadTarot);
			}
		}
		
		const Node::Instantaneous FunctionDefinition::willPause(const bool requireBothBranches) {
			if (!instantaneous.found) {
				instantaneous = children.back()->willPause(requireBothBranches);
				instantaneous.breaks = false;
				instantaneous.continues = false;
				instantaneous.returns = false;

				instantaneous.found = true;
			}
			
			return instantaneous;
		}
		
		void FunctionDefinition::prettyPrint(std::ostream &output) {
			if (identifier.compare("main") == 0) {
				output << tools::Template::formatSharedSymbols() << std::endl;
				output << "// forec:scheduler:boot:start" << std::endl;
				if (global::embeddedMainFunctionName.empty()) {
					output << "int ";
				} else {
					output << "void *";
				}
			} else {
				output << *children[0] << " ";
			}

			if (identifier.compare("main") == 0 && !global::embeddedMainFunctionName.empty()) {
				output << global::embeddedMainFunctionName << "(void *_) ";
			} else {
				for (std::vector<Node *>::iterator i = children.begin() + 1; i != children.end() - 1; ++i) {
					output << *(*i) << " ";
				}
			}

			if (identifier.compare("main") == 0) {
				tools::Tab::indent();

				std::ostringstream argcName;
				std::ostringstream argvName;
				std::vector<Node *> arguments = tools::Query::retrieveAll(*children[1], "DirectDeclarator");
				if (arguments.size() == 4) {
					argcName << *arguments[2];
					argvName << *arguments[3];
				} else {
					std::ostringstream output;
					output << "FunctionDefinition::prettyPrint: Expected the signature main(int, char **) but got " << *children[1] << " instead." << std::endl;
					throw output.str();
				}
				
				std::ostringstream declarationString;
				if (!privateDeclarations.empty()) {
					BlockItemList localDeclarations(*privateDeclarations[0]);
					for (std::vector<Node *>::iterator declaration = privateDeclarations.begin() + 1; declaration != privateDeclarations.end(); ++declaration) {
						localDeclarations.append(*(*declaration));
					}
					
					declarationString << localDeclarations << std::endl;
				}
				
				if (declarationString.str().empty()) {
					declarationString << tools::Tab::toString() << "// No declarations.";
				}
				
				std::vector<Node *> blockItemList = tools::Query::retrieveChildren(*children.back(), "BlockItemList");
				output << tools::Template::formatMain(declarationString.str(), blockItemList, threads, argcName.str(), argvName.str());
				tools::Tab::dedent();
			} else {
				output << *children.back();
			}
		}

	}
}
