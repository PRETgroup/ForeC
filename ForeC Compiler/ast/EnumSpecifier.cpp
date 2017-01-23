/*
 *  EnumSpecifier.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "EnumSpecifier.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int EnumSpecifier::globalCount = 0;
		
		EnumSpecifier::EnumSpecifier(Node &node, const std::string &variant) : Node("EnumSpecifier", variant, this->globalCount++) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}

		EnumSpecifier::EnumSpecifier(Node &node0, Node &node1, const std::string &variant) : Node("EnumSpecifier", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}

		int EnumSpecifier::getCount(void) {
			return globalCount;
		}
		
		void EnumSpecifier::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			if (isVariant("definition0") || isVariant("definition1")) {
				children[0]->updateSymbolTable("storage");
				children[1]->updateSymbolTable("enumeration");
			} else if (isVariant("anonymous0")) {
				children[0]->updateSymbolTable("enumeration");
			} else if (isVariant("declaration")) {
				children[0]->updateSymbolTable("storage", true, isRead);
			}
		}
		
		void EnumSpecifier::prettyPrint(std::ostream &output) {
			if (variant.compare("anonymous0") == 0) {
				output << "enum {" << std::endl;
				tools::Tab::indent();
				output << *children[0] << std::endl;
				tools::Tab::dedent();
				output << tools::Tab::toString() << "}";
			} else if (variant.compare("definition0") == 0) {
				output << "enum " << *children[0] << " {" << std::endl;
				tools::Tab::indent();
				output << *children[1] << std::endl;
				tools::Tab::dedent();
				output << tools::Tab::toString() << "}";
			} if (variant.compare("anonymous1") == 0) {
				output << "enum {" << std::endl;
				tools::Tab::indent();
				output << *children[0] << "," << std::endl;
				tools::Tab::dedent();
				output << tools::Tab::toString() << "}";
			} else if (variant.compare("definition1") == 0) {
				output << "enum " << *children[0] << " {" << std::endl;
				tools::Tab::indent();
				output << *children[1] << "," << std::endl;
				tools::Tab::dedent();
				output << tools::Tab::toString() << "}";
			} else if (variant.compare("declaration") == 0) {
				output << "enum " << *children[0];
			}
		}

	}
}
