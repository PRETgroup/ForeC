/*
 *  DirectAbstractDeclarator.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "DirectAbstractDeclarator.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int DirectAbstractDeclarator::globalCount = 0;

		DirectAbstractDeclarator::DirectAbstractDeclarator(const std::string &variant) : Node("DirectAbstractDeclarator", variant, this->globalCount++) {
			
		}

		DirectAbstractDeclarator::DirectAbstractDeclarator(Node &node, const std::string &variant) : Node("DirectAbstractDeclarator", variant, this->globalCount++) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}
		
		DirectAbstractDeclarator::DirectAbstractDeclarator(Node &node0, Node &node1, const std::string &variant) : Node("DirectAbstractDeclarator", variant, this->globalCount++) {
			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
		}
		
		int DirectAbstractDeclarator::getCount(void) {
			return globalCount;
		}
		
		
		void DirectAbstractDeclarator::prettyPrint(std::ostream &output) {
			if (isVariant("cast")) {
				output << "(" << *children[0] << ")";
			} else if (isVariant("index0")) {
				output << "[]";
			} else if (variant.compare("index1")) {
				output << "[" << *children[0] << "]";
			} else if (isVariant("array0")) {
				output << *children[0] << "[]";
			} else if (isVariant("array1")) {
				output << *children[0] << "[" << *children[1] << "]";
			} else if (isVariant("index2")) {
				output << "[*]";
			} else if (isVariant("array2")) {
				output << *children[0] << "[*]";
			} else if (isVariant("function0")) {
				output << "()";
			} else if (isVariant("function1")) {
				output << "(" << *children[0] << ")";
			} else if (isVariant("function2")) {
				output << *children[0] << "()";
			} else if (isVariant("function3")) {
				output << *children[0] << "(" << *children[1] << ")";
			}
		}

	}
}
