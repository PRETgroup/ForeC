#ifndef FOREC_AST_PRIMARY_EXPRESSION_HPP
#define FOREC_AST_PRIMARY_EXPRESSION_HPP

/*
 *  PrimaryExpression.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class PrimaryExpression : public Node {
			public:
				PrimaryExpression(const PrimaryExpression &original, const std::string &type, const bool suppressValueElement);
				PrimaryExpression(const std::string &terminal, const int lineNumber, const std::string &variant = "none");
				PrimaryExpression(const std::string &terminal, const std::string &variant = "none");
				PrimaryExpression(Node &node, const std::string &variant = "none");
				
				static const int getCount(void);
				const std::string getTerminal(void) const;
				const std::string getType(void) const;
				const std::string getScope(void) const;
				const int getLineNumber(void) const;
				PrimaryExpression *getDeclaration(void) const;
				
				void setSuffix(const std::string &suffix);
				const std::string getSuffix(void) const;
				void setSpecifiers(Node &specifiers);
				Node *getSpecifiers(void) const;
				void setIsPointer(const bool isPointer);
				void setSuppressValueElement(const bool suppressValueElement);
				void setSuppressCopySuffix(const bool suppressCopySuffix);
				
				void setCombineSpecifier(Node &node);
				Node *getCombineSpecifier(void) const;
				
				void updateSymbolTable(const std::string &type = "none", const bool isUsage = false, const bool isRead = false);

				const std::string getSharedSymbolString(void);
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				const std::string terminal;
				const int lineNumber;
				std::string type;
				bool isPointer;
				
				// For suffix.
				PrimaryExpression *declaration;
				std::string suffix;
				std::string scopeName;
				bool suppressValueElement;
				bool suppressCopySuffix;
								
				// For declarations.
				Node *specifiers;
				Node *combineSpecifier;
		};
	}
}

#endif // FOREC_AST_PRIMARY_EXPRESSION_HPP
