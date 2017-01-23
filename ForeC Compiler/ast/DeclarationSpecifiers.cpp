/*
 *  DeclarationSpecifiers.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "DeclarationSpecifiers.hpp"

#include "../tools/Tab.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int DeclarationSpecifiers::globalCount = 0;

		DeclarationSpecifiers::DeclarationSpecifiers(Node &node, const std::string &variant) : NodeList(node, "DeclarationSpecifiers", variant, this->globalCount++) {
			node.setParent((Node *)this);
			
			sharedIdentifier = NULL;
		}

		int DeclarationSpecifiers::getCount(void) {
			return globalCount;
		}
		
		void DeclarationSpecifiers::setSharedIdentifier(Node &sharedIdentifier) {
			this->sharedIdentifier = &sharedIdentifier;
		}
		
		void DeclarationSpecifiers::setSharedDirectDeclarator(const std::string &sharedDirectDeclarator) {
			this->sharedDirectDeclarator = sharedDirectDeclarator;
		}
		
		const std::string DeclarationSpecifiers::getSharedStruct(void) const {
			std::ostringstream output;
			
			output << tools::Tab::toString() << "typedef struct {" << std::endl;
			
			output << tools::Tab::toString() << '\t' << *children[0];
			if (children.size() > 1) {
				for (std::vector<Node *>::const_iterator i = children.begin() + 1; i != children.end(); ++i) {
					output << " " << *(*i);
				}
			}
			output << " " << sharedDirectDeclarator << ';' << std::endl;

			output << tools::Tab::toString() << "\tint status;" << std::endl;
			output << "} Shared_" << *sharedIdentifier << ';';

			return output.str();
		}
		
		void DeclarationSpecifiers::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end() - 1; ++i) {
				(*i)->updateSymbolTable(type, true, isRead);
			}
			
			children.back()->updateSymbolTable(type, isUsage, isRead);
		}
		
		
		void DeclarationSpecifiers::prettyPrint(std::ostream &output) {
			if (has("TypeQualifier", "shared")) {
				if (sharedIdentifier == NULL) {
					output << "/* shared */";
					if (children.size() > 1) {
						for (std::vector<Node *>::iterator i = children.begin() + 1; i != children.end(); ++i) {
							output << " " << *(*i);
						}
					}
				} else {
					output << "Shared_" << *sharedIdentifier;
				}
			} else {
				output << *children[0];
				
				if (children.size() > 1) {
					for (std::vector<Node *>::iterator i = children.begin() + 1; i != children.end(); ++i) {
						output << " " << *(*i);
					}
				}
			}
		}

	}
}
