/*
 *  StructUnionSpecifier.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "StructUnionSpecifier.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int StructUnionSpecifier::globalCount = 0;
		
		StructUnionSpecifier::StructUnionSpecifier(const std::string &structUnion, Node &node, const std::string &variant) : Node("StructUnionSpecifier", variant, this->globalCount++), structUnion(structUnion) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}

		StructUnionSpecifier::StructUnionSpecifier(const std::string &structUnion, Node &node0, Node &node1, const std::string &variant) : Node("StructUnionSpecifier", variant, this->globalCount++), structUnion(structUnion) {
			children.push_back(&node0);
			children.push_back(&node1);
			
			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		int StructUnionSpecifier::getCount(void) {
			return globalCount;
		}
		
		void StructUnionSpecifier::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			std::string newType = (type.compare("extern") == 0) ? "extern" : "storage";
		//	std::cout << "StructUnionSpecifier: " << *this << ' ' << type << ' ' << newType << ' ' << variant << ' ' << isUsage << std::endl;

			if (type.compare("usage") == 0) {
				// Workaround when a struct or union declaration is actually followed by a declarator, in which case
				// the struct name is being used (not declared).
				children[0]->updateSymbolTable(newType, isUsage, isRead);
			} else if (isVariant("definition")) {
				children[0]->updateSymbolTable(newType, false, isRead);
				children[1]->updateSymbolTable(newType, isUsage, isRead);
			} else if (isVariant("anonymous")) {
				children[0]->updateSymbolTable(newType, isUsage, isRead);
			} else if (isVariant("declaration")) {
				children[0]->updateSymbolTable(newType, isUsage, isRead);
			}
		}
		
		void StructUnionSpecifier::prettyPrint(std::ostream &output) {
			if (variant.compare("definition") == 0) {
				output << structUnion << " " << *children[0] << " {" << std::endl;
				tools::Tab::indent();
				output << *children[1] << std::endl;
				tools::Tab::dedent();
				output << tools::Tab::toString() << "}";
			} else if (variant.compare("anonymous") == 0) {
				output << structUnion << " {" << std::endl;
				tools::Tab::indent();
				output << *children[0] << std::endl;
				tools::Tab::dedent();
				output << tools::Tab::toString() << "}";
			} else if (variant.compare("declaration") == 0) {
				output << structUnion << " " << *children[0];
			}
		}

	}
}
