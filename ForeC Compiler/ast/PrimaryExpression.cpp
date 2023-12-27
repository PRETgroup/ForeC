/*
 *  PrimaryExpression.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "PrimaryExpression.hpp"

#include "../tools/SymbolTable.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int PrimaryExpression::globalCount = 0;

		PrimaryExpression::PrimaryExpression(const PrimaryExpression &original, const std::string &type, const bool suppressValueElement) : Node("PrimaryExpression", original.variant, this->globalCount++), terminal(original.terminal), lineNumber(original.lineNumber), 
																																			type(type), isPointer(original.isPointer), declaration(original.declaration), suffix(original.suffix), scopeName(original.scopeName),
																										 									suppressValueElement(suppressValueElement), suppressCopySuffix(original.suppressCopySuffix), specifiers(original.specifiers), 
																																			combineSpecifier(original.combineSpecifier) {
			children = original.children;
		}

		PrimaryExpression::PrimaryExpression(const std::string &terminal, const int lineNumber, const std::string &variant) : Node("PrimaryExpression", variant, this->globalCount++), terminal(terminal), lineNumber(lineNumber) {
			declaration = NULL;
			suffix = "";
			scopeName = "";
			type = "";
			isPointer = false;
			suppressValueElement = false;
			suppressCopySuffix = false;
			
			specifiers = NULL;
			combineSpecifier = NULL;
		}
		
		PrimaryExpression::PrimaryExpression(const std::string &terminal, const std::string &variant) : Node("PrimaryExpression", variant, this->globalCount++), terminal(terminal), lineNumber(-1) {
			declaration = NULL;
			suffix = "";
			scopeName = "";
			type = "";
			isPointer = false;
			suppressValueElement = false;
			suppressCopySuffix = false;
			
			specifiers = NULL;
			combineSpecifier = NULL;
		}

		PrimaryExpression::PrimaryExpression(Node &node, const std::string &variant) : Node("PrimaryExpression", variant, this->globalCount++), lineNumber(((PrimaryExpression *)&node)->lineNumber) {
			declaration = NULL;
			suffix = "";
			scopeName = "";
			type = "";
			isPointer = false;
			suppressValueElement = false;
			suppressCopySuffix = false;
			
			specifiers = NULL;
			combineSpecifier = NULL;

			children.push_back(&node);
			node.setParent((Node *)this);
		}


		const int PrimaryExpression::getCount(void) {
			return globalCount;
		}

		const std::string PrimaryExpression::getTerminal(void) const {
			return this->terminal;
		}
		
		const std::string PrimaryExpression::getType(void) const {
			return this->type;
		}

		const std::string PrimaryExpression::getScope(void) const {
			return this->scopeName;
		}
		
		const int PrimaryExpression::getLineNumber(void) const {
			return this->lineNumber;
		}
		
		PrimaryExpression *PrimaryExpression::getDeclaration(void) const {
			return this->declaration;
		}
		
		void PrimaryExpression::setSuffix(const std::string &suffix) {
			this->suffix = suffix;
		}

		const std::string PrimaryExpression::getSuffix(void) const {
			return this->suffix;
		}

		void PrimaryExpression::setSpecifiers(Node &specifiers) {
			this->specifiers = &specifiers;
		}

		Node *PrimaryExpression::getSpecifiers(void) const {
			return this->specifiers;
		}
		
		void PrimaryExpression::setIsPointer(const bool isPointer) {
			this->isPointer = isPointer;
		}
		
		void PrimaryExpression::setSuppressValueElement(const bool suppressValueElement) {
			this->suppressValueElement = suppressValueElement;
		}

		void PrimaryExpression::setSuppressCopySuffix(const bool suppressCopySuffix) {
			this->suppressCopySuffix = suppressCopySuffix;
		}

		void PrimaryExpression::setCombineSpecifier(Node &node) {
			this->combineSpecifier = &node;
		}
		
		Node *PrimaryExpression::getCombineSpecifier(void) const {
			return this->combineSpecifier;
		}

		void PrimaryExpression::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			this->scopeName = tools::SymbolTable::getScopeName();
			this->type = type;
			
			if (isVariant("identifier")) {
				// Check if identifier is being accessed or declared.
				if (isUsage) {
					// Find declaration.
					this->declaration = tools::SymbolTable::getDeclaration(type, *this, isRead, isPointer);
					if (this->declaration != NULL) {
						// We take the declaration's suffix.
						this->suffix = this->declaration->getSuffix();
					}
				} else {
					// Add declaration.
					this->declaration = this;
					
					if (type.compare("function") == 0 || type.compare("enumeration") == 0 || type.compare("extern") == 0) {
						tools::SymbolTable::addDeclaration(type, *this);
					} else {
						this->suffix = tools::SymbolTable::addDeclaration(type, *this);
					}
				}
			} else if (isVariant("expression")) {
				children[0]->updateSymbolTable(type, isUsage, isRead);
			}
		}

		const std::string PrimaryExpression::getSharedSymbolString(void) {
			std::ostringstream output;
			if (isVariant("identifier")) {
				output << terminal << suffix;
				if (this->declaration != NULL && this->declaration->getType().compare("shared") == 0) {
					output << tools::SymbolTable::resolveSharedSuffix(*this, *this->declaration, true, suppressCopySuffix);
				}
			}
			
			return output.str();
		}

		void PrimaryExpression::prettyPrint(std::ostream &output) {
			if (isVariant("identifier")) {
				output << terminal << suffix;
				if (this->declaration != NULL && this->declaration->getType().compare("shared") == 0) {
					output << tools::SymbolTable::resolveSharedSuffix(*this, *this->declaration, suppressValueElement, suppressCopySuffix);
				}
			} else if (isVariant("terminal")) {
				output << terminal;
			} else if (isVariant("expression")) {
				output << "(" << *children[0] << ")";
			}
		}

	}
}
