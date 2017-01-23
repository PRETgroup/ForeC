/*
 *  SelectionStatement.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "SelectionStatement.hpp"

#include "CompoundStatement.hpp"
#include "PrimaryExpression.hpp"

#include "../tarot/Node.hpp"
#include "../tarot/Selection.hpp"

#include "../tools/Condition.hpp"
#include "../tools/SymbolTable.hpp"
#include "../tools/Query.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int SelectionStatement::globalCount = 0;


		SelectionStatement::SelectionStatement(Node &node0, Node &node1, const std::string &variant) : Node("SelectionStatement", variant, this->globalCount++) {
			children.push_back(&node0);
			node0.setParent((Node *)this);

			if (node1.isType("CompoundStatement")) {
				std::vector<Node *> blockItemLists = tools::Query::retrieveChildren(node1, "BlockItemList");

				Node *blockItemList1;
				if (blockItemLists.size() > 0) {
					blockItemList1 = blockItemLists[0];
				} else {
					blockItemList1 = new PrimaryExpression("", "terminal");
				}

				children.push_back(blockItemList1);
				blockItemList1->setParent((Node *)this);
			} else {
				children.push_back(&node1);
				node1.setParent((Node *)this);
			}

			Node *blockItemList2 = new PrimaryExpression("", "terminal");

			children.push_back(blockItemList2);
			blockItemList2->setParent((Node *)this);
		}

		SelectionStatement::SelectionStatement(Node &node0, Node &node1, Node &node2, const std::string &variant) : Node("SelectionStatement", variant, this->globalCount++) {
			children.push_back(&node0);
			node0.setParent((Node *)this);

			if (node1.isType("CompoundStatement")) {
				std::vector<Node *> blockItemLists = tools::Query::retrieveChildren(node1, "BlockItemList");

				Node *blockItemList1;
				if (blockItemLists.size() > 0) {
					blockItemList1 = blockItemLists[0];
				} else {
					blockItemList1 = new PrimaryExpression("", "terminal");
				}

				children.push_back(blockItemList1);
				blockItemList1->setParent((Node *)this);
			} else {
				children.push_back(&node1);
				node1.setParent((Node *)this);
			}

			if (node2.isType("CompoundStatement")) {
				std::vector<Node *> blockItemLists = tools::Query::retrieveChildren(node2, "BlockItemList");

				Node *blockItemList2;
				if (blockItemLists.size() > 0) {
					blockItemList2 = blockItemLists[0];
				} else {
					blockItemList2 = new PrimaryExpression("", "terminal");
				}

				children.push_back(blockItemList2);
				blockItemList2->setParent((Node *)this);
			} else {
				children.push_back(&node2);
				node2.setParent((Node *)this);
			}
		}

		const std::string SelectionStatement::getId(void) const {
			std::ostringstream name;
			name << variant << id;
			return name.str();
		}

		const std::string SelectionStatement::getThreadScope(void) const {
			return threadScope;
		}

		int SelectionStatement::getCount(void) {
			return globalCount;
		}

		void SelectionStatement::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			threadScope = tools::SymbolTable::getScopeName();
			tools::SymbolTable::enterScope();
			tools::Condition::enterScope(*this);

			children[0]->updateSymbolTable(type, isUsage, isRead);

			tools::Condition::setSelectionBranch("if");
			children[1]->updateSymbolTable(type, isUsage, isRead);

			if (children.size() > 2) {
				tools::Condition::setSelectionBranch("else");
				children[2]->updateSymbolTable(type, isUsage, isRead);
			}

			tools::Condition::leaveScope(getType());
			tools::SymbolTable::leaveScope();
		}

		void SelectionStatement::createTarot(const std::string &threadScope, tarot::Node &tarotNode) {
			tarot::Selection *selectionIfTarot = new tarot::Selection(threadScope, "if", this);
			tarot::Selection *selectionElseTarot = new tarot::Selection(threadScope, "else", this);

			children[1]->createTarot(threadScope, *selectionIfTarot);
			children[2]->createTarot(threadScope, *selectionElseTarot);

			if (selectionIfTarot->hasChildren() || selectionElseTarot->hasChildren()) {
				tarotNode.append(*selectionIfTarot);
				tarotNode.append(*selectionElseTarot);

				selectionElseTarot->setIfBranch(*selectionIfTarot);
			}
		}
		
		const Node::Instantaneous SelectionStatement::willPause(const bool requireBothBranches) {
			instantaneous.pauses = false;
			instantaneous.breaks = false;
			instantaneous.continues = false;
			instantaneous.returns = false;
			
			if (isVariant("switch")) {
				if (children[1]->isType("BlockItemList")) {
					instantaneous = children[1]->willPause(requireBothBranches);
				} else {
					throw std::string("SelectionStatement::willPause: Unexpected \"" + children[1]->getType() + "\".");
				}
			} else if (isVariant("ifElse")) {
				instantaneous = children[1]->willPause(requireBothBranches);
				
				Node::Instantaneous result = children[2]->willPause(requireBothBranches);
				
				instantaneous.pauses = instantaneous.pauses && result.pauses;
				
				if (requireBothBranches) {
					instantaneous.breaks = instantaneous.breaks && result.breaks;
					instantaneous.continues = instantaneous.continues && result.continues;
					instantaneous.returns = instantaneous.returns && result.returns;
				} else {
					instantaneous.breaks = instantaneous.breaks || result.breaks;
					instantaneous.continues = instantaneous.continues || result.continues;
					instantaneous.returns = instantaneous.returns || result.returns;
				}
			} else {
				for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
					Node::Instantaneous result = (*i)->willPause(requireBothBranches);
					
					if (requireBothBranches) {
						instantaneous.breaks = instantaneous.breaks && result.breaks;
						instantaneous.continues = instantaneous.continues && result.continues;
						instantaneous.returns = instantaneous.returns && result.returns;
					} else {
						instantaneous.breaks = instantaneous.breaks || result.breaks;
						instantaneous.continues = instantaneous.continues || result.continues;
						instantaneous.returns = instantaneous.returns || result.returns;
					}
				}
			}
			
			return instantaneous;
		}

		void SelectionStatement::prettyPrint(std::ostream &output) {
			if (isVariant("if")) {
				output << "if (" << *children[0] << ") {" << std::endl;
				tools::Tab::indent();
				if (!children[1]->isType("BlockItemList")) {
					output << tools::Tab::toString();
				}
				output << *children[1] << std::endl;
				tools::Tab::dedent();
				output << tools::Tab::toString() << "} else {" << std::endl;
				output << tools::Tab::toString() << "\t// " << getId() << std::endl;
				output << tools::Tab::toString() << '}';
			} else if (isVariant("ifElse")) {
				output << "if (" << *children[0] << ") {" << std::endl;
				tools::Tab::indent();
				if (!children[1]->isType("BlockItemList")) {
					output << tools::Tab::toString();
				}
				output << *children[1] << std::endl;
				tools::Tab::dedent();

				output << tools::Tab::toString() << "} else {" << std::endl;
				tools::Tab::indent();
				output << tools::Tab::toString() << "// " << getId() << std::endl;
				if (!children[2]->isType("BlockItemList")) {
					output << tools::Tab::toString();
				}
				output << *children[2] << std::endl;
				tools::Tab::dedent();
				output << tools::Tab::toString() << '}';
			} else if (isVariant("switch")) {
				((CompoundStatement *)children[1])->setIsInsideSwitchStatement(true);

				output << "switch (" << *children[0] << ") {" << std::endl;
				tools::Tab::indent();
				tools::Tab::indent();
				output << *children[1] << std::endl;
				tools::Tab::dedent();
				tools::Tab::dedent();
				output << tools::Tab::toString() << '}';
			}
		}

	}
}
