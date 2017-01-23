/*
 *  Declaration.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Declaration.hpp"

#include "BinaryExpression.hpp"
#include "DeclarationSpecifiers.hpp"
#include "InitDeclaratorList.hpp"
#include "PrimaryExpression.hpp"

#include "../tools/Query.hpp"
#include "../tools/SymbolTable.hpp"
#include "../tools/Threading.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int Declaration::globalCount = 0;

		Declaration::Declaration(Node &node, const std::string &variant) : Node("Declaration", variant, this->globalCount++) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}

		Declaration::Declaration(Node &node0, Node &node1, const std::string &variant) : Node("Declaration", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		void Declaration::takeOutDeclarations(std::vector<Node *> &privateDeclarations) {
			const bool hasShared = this->has("TypeQualifier", "shared");

			if (isVariant("initDeclaration")) {
				// Copy the declarators only.
				std::vector<Node *> declarators;
				
				if (hasShared) {
					declarators = tools::Query::retrieveAll(*children.back(), "PrimaryExpression", "identifier");
				} else {
					declarators = tools::Query::retrieveAll(*children.back(), "BinaryExpression", "declarator");
				}
				
				InitDeclaratorList *initDeclaratorList = new InitDeclaratorList(*declarators[0]);
				for (std::vector<Node *>::iterator declarator = declarators.begin() + 1; declarator != declarators.end(); ++declarator) {
					initDeclaratorList->append(*(*declarator));
				}
				Declaration *declaration = new Declaration(*children[0], *initDeclaratorList, "declaration");
					
				if (!hasShared) {
					privateDeclarations.push_back((Node *)declaration);
				}

				// Remove the specifiers
				children.erase(children.begin());

				// Add an update to the local copy of the shared variable.
				std::vector<Node *> originalBinaryExpressions = tools::Query::retrieveAll(*children.back(), "BinaryExpression", " = ");
				if (originalBinaryExpressions.empty()) {
					parent->remove((Node *)this);
				} else if (hasShared) {
					// Prepend a copy of each shared variable to the existing binary expressions.
					for (std::vector<Node *>::const_iterator expression = originalBinaryExpressions.begin(); expression != originalBinaryExpressions.end(); ++expression) {
						BinaryExpression *originalBinaryExpression = (BinaryExpression *)*expression;
						PrimaryExpression *originalPrimaryExpression = (PrimaryExpression *)tools::Query::retrieveAll(*originalBinaryExpression, "PrimaryExpression", "identifier")[0];

						// Save a pointer to the parent node.
						Node *parent = (*expression)->getParent();
						BinaryExpression *newBinaryExpression = new BinaryExpression(*(new PrimaryExpression(*originalPrimaryExpression, "variable", true)), *originalBinaryExpression, " = ");
						parent->replace(*expression, newBinaryExpression);
					}
				}
			} else {
				if (!hasShared) {
					privateDeclarations.push_back((Node *)this);
				}

				parent->remove((Node *)this);
			}
		}

		int Declaration::getCount(void) {
			return globalCount;
		}
		
		void Declaration::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			if (has("StorageClassSpecifier", "typedef")) {
				children[0]->updateSymbolTable("typedef");
			} else if (isVariant("threadDeclaration")) {
				children[0]->updateSymbolTable("thread");
			} else {
				children[0]->updateSymbolTable("none", true, isRead);
			}
			
			if (isVariant("initDeclaration")) {
				if (has("TypeQualifier", "input")) {
					children[1]->updateSymbolTable("input");
				} else if (has("TypeQualifier", "output")) {
					children[1]->updateSymbolTable("output");
				} else if (has("TypeQualifier", "shared")) {
					if (has("TypeQualifier", "const")) {
						std::vector<Node *> identifiersFound = tools::Query::retrieveAll(*children.back(), "PrimaryExpression", "identifier");
						
						if (!identifiersFound.empty()) {
							((PrimaryExpression *)identifiersFound.front())->setSpecifiers(*children.front());
						}
						
						children[1]->updateSymbolTable("sharedConst");
					} else {
						std::vector<Node *> identifiersFound = tools::Query::retrieveAll(*children.back(), "PrimaryExpression", "identifier");
						
						if (!identifiersFound.empty()) {
							((PrimaryExpression *)identifiersFound.front())->setSpecifiers(*children.front());
							((DeclarationSpecifiers *)children.front())->setSharedIdentifier(*identifiersFound.front());
						}

						children[1]->updateSymbolTable("shared");
						
						// Copy the direct declarator but replace the identifier with "value" instead.
						std::vector<Node *> declarators = tools::Query::retrieveAll(*children.back(), "BinaryExpression", "declarator");
						if (declarators.size() > 1) {
							int lineNumber = ((PrimaryExpression *)identifiersFound.front())->getLineNumber();
							std::ostringstream output;
							output << "Declaration::updateSymbolTable: Declaration of a list of shared variables is not supported (line " << lineNumber << ").";
							throw output.str();
						}

						PrimaryExpression *originalPrimaryExpression = (PrimaryExpression *)identifiersFound.front();
						PrimaryExpression *newPrimaryExpression = new forec::ast::PrimaryExpression("value", "identifier");
						
						Node *parent = originalPrimaryExpression->getParent();
						
						std::ostringstream directDeclarator;
						parent->replace(originalPrimaryExpression, newPrimaryExpression);
						directDeclarator << *declarators.front();
						parent->replace(newPrimaryExpression, originalPrimaryExpression);

						// Give the new direct declarator to the specifier for creating the shared struct.
						((DeclarationSpecifiers *)originalPrimaryExpression->getSpecifiers())->setSharedDirectDeclarator(directDeclarator.str());
						
						// Remove indirections.
						Node *identifier = tools::Query::retrieveAll(*declarators.front(), "PrimaryExpression", "identifier").front();
						parent = declarators.front()->getParent();
						parent->replace(declarators.front(), identifier);
					}
				} else if (has("DirectDeclarator", "function0") || has("DirectDeclarator", "function1") || has("DirectDeclarator", "function2")) {
					children[1]->updateSymbolTable("function", true, isRead);
				} else {
					children[1]->updateSymbolTable("variable");
				}
			}
		}
		
		void Declaration::prettyPrint(std::ostream &output) {
			if (isVariant("threadDeclaration")) {
				output << "// thread ";
			} else if (has("TypeQualifier", "shared") && !has("TypeQualifier", "const")) {
				std::vector<Node *> identifiersFound = tools::Query::retrieveAll(*children[1], "PrimaryExpression", "identifier");
				if (!identifiersFound.empty()) {
					if (((PrimaryExpression *)identifiersFound[0])->getScope().compare("global") == 0) {
						output << ((DeclarationSpecifiers *)children[0])->getSharedStruct() << std::endl;
					}
				}
			}
			
 			output << *children[0];
		
			if (children.size() > 1) {
				for (std::vector<Node *>::iterator i = children.begin() + 1; i != children.end(); ++i) {
					output << " " << *(*i);
				}
			}
			
			output << ";";
		}

	}
}
