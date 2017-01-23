/*
 *  CompoundStatement.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "CompoundStatement.hpp"

#include "../tools/SymbolTable.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int CompoundStatement::globalCount = 0;


		CompoundStatement::CompoundStatement(const std::string &variant) : Node("CompoundStatement", variant, this->globalCount++) {
			isInsideSwitchStatement = false;
		}

		CompoundStatement::CompoundStatement(Node &node, const std::string &variant) : Node("CompoundStatement", variant, this->globalCount++) {
			isInsideSwitchStatement = false;
			children.push_back(&node);

			node.setParent((Node *)this);
		}

		void CompoundStatement::setIsInsideSwitchStatement(const bool isInsideSwitchStatement) {
			(this->isInsideSwitchStatement) = isInsideSwitchStatement;
		}
		
		const bool CompoundStatement::getIsInsideSwitchStatement(void) const {
			return isInsideSwitchStatement;
		}

		int CompoundStatement::getCount(void) {
			return globalCount;
		}

		void CompoundStatement::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			if (type.compare("thread") != 0 && type.compare("function") != 0) {
				tools::SymbolTable::enterScope();
			}

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->updateSymbolTable();
			}
			
			tools::SymbolTable::leaveScope();
		}
		
		void CompoundStatement::prettyPrint(std::ostream &output) {
			output << "{";
		
			if (children.size() == 1) {
				if (!isInsideSwitchStatement) {
					output << std::endl;
				}

				tools::Tab::indent();
				output << *children[0];

				if (isInsideSwitchStatement) {
					tools::Tab::dedent();
				}
				tools::Tab::dedent();
				output << std::endl << tools::Tab::toString();
			}
			
			output << "}";
		}

	}
}
