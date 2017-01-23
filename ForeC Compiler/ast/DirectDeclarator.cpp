/*
 *  DirectDeclarator.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "DirectDeclarator.hpp"

#include "../tools/Query.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int DirectDeclarator::globalCount = 0;

		DirectDeclarator::DirectDeclarator(Node &node, const std::string &variant) : Node("DirectDeclarator", variant, this->globalCount++) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}

		DirectDeclarator::DirectDeclarator(Node &node0, Node &node1, const std::string &variant) : Node("DirectDeclarator", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		DirectDeclarator::DirectDeclarator(Node &node0, Node &node1, Node &node2, const std::string &variant) : Node("DirectDeclarator", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);
			children.push_back(&node2);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
			node2.setParent((Node *)this);
		}

		int DirectDeclarator::getCount(void) {
			return globalCount;
		}

		void DirectDeclarator::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			if (type.compare("function") == 0 || type.compare("thread") == 0) {
				children.front()->updateSymbolTable(type, false, isRead);
				if (children.size() > 1) {
					std::vector<Node *> declarationSpecifiersFound = tools::Query::retrieveAll(*children[1], "DeclarationSpecifiers");
					for (std::vector<Node *>::iterator declarationSpecifier = declarationSpecifiersFound.begin(); declarationSpecifier != declarationSpecifiersFound.end(); ++declarationSpecifier) {
						(*declarationSpecifier)->updateSymbolTable(type, true);
					}
				}
			} else if (type.compare("storage") == 0) {
				// Empty: Do nothing.
			} else {
				for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
					(*i)->updateSymbolTable(type, isUsage, isRead);
				}
			}
		}

		void DirectDeclarator::prettyPrint(std::ostream &output) {
			if (variant.compare("identifier") == 0) {
				output << *children[0];
			} else if (variant.compare("cast") == 0) {
				output << "(" << *children[0] << ")";
			} else if (variant.compare("array0") == 0) {
				output << *children[0] << "[" << *children[1] << " " << *children[2] << "]";
			} else if (variant.compare("array1") == 0) {
				output << *children[0] << "[" << *children[1] << "]";
			} else if (variant.compare("array2") == 0) {
				output << *children[0] << "[" << *children[1] << "]";
			} else if (variant.compare("array3") == 0) {
				output << *children[0] << "[static " << *children[1] << " " << *children[2] << "]";
			} else if (variant.compare("array4") == 0) {
				output << *children[0] << "[" << *children[1] << " static " << *children[2] << "]";
			} else if (variant.compare("array5") == 0) {
				output << *children[0] << "[" << *children[1] << " *]";
			} else if (variant.compare("array6") == 0) {
				output << *children[0] << "[*]";
			} else if (variant.compare("array7") == 0) {
				output << *children[0] << "[]";
			} else if (variant.compare("function0") == 0) {
				output << *children[0] << "(" << *children[1] << ")";
			} else if (variant.compare("function1") == 0) {
				output << *children[0] << "(" << *children[1] << ")";
			} else if (variant.compare("function2") == 0) {
				output << *children[0] << "()";
			}
		}

	}
}
