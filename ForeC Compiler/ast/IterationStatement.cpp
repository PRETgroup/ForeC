/*
 *  IterationStatement.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "IterationStatement.hpp"

#include "PrimaryExpression.hpp"

#include "../tarot/Node.hpp"
#include "../tarot/Iteration.hpp"

#include "../tarot/Tarot.hpp"

#include "../tools/Condition.hpp"
#include "../tools/Query.hpp"
#include "../tools/Multicore.hpp"
#include "../tools/SymbolTable.hpp"
#include "../tools/Threading.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int IterationStatement::globalCount = 0;


		IterationStatement::IterationStatement(const unsigned int lineNumber, Node &node0, Node &node1, const std::string &variant) : Node("IterationStatement", variant, this->globalCount++), lineNumber(lineNumber) {
			isRoot = false;

			if (node0.isType("CompoundStatement")) {
				std::vector<Node *> blockItemLists = tools::Query::retrieveChildren(node0, "BlockItemList");

				Node *blockItemList0;
				if (blockItemLists.size() > 0) {
					blockItemList0 = blockItemLists[0];
				} else {
					blockItemList0 = new PrimaryExpression("", "terminal");
				}

				children.push_back(blockItemList0);
				blockItemList0->setParent((Node *)this);
			} else {
				children.push_back(&node0);
				node0.setParent((Node *)this);
			}

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
		}

		IterationStatement::IterationStatement(const unsigned int lineNumber, Node &node0, Node &node1, Node &node2, const std::string &variant) : Node("IterationStatement", variant, this->globalCount++), lineNumber(lineNumber) {
			isRoot = false;

			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);

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

		IterationStatement::IterationStatement(const unsigned int lineNumber, Node &node0, Node &node1, Node &node2, Node &node3, const std::string &variant) : Node("IterationStatement", variant, this->globalCount++), lineNumber(lineNumber) {
			isRoot = false;

			children.push_back(&node0);
			children.push_back(&node1);
			children.push_back(&node2);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
			node2.setParent((Node *)this);

			if (node3.isType("CompoundStatement")) {
				std::vector<Node *> blockItemLists = tools::Query::retrieveChildren(node3, "BlockItemList");

				Node *blockItemList3;
				if (blockItemLists.size() > 0) {
					blockItemList3 = blockItemLists[0];
				} else {
					blockItemList3 = new PrimaryExpression("", "terminal");
				}

				children.push_back(blockItemList3);
				blockItemList3->setParent((Node *)this);
			} else {
				children.push_back(&node3);
				node3.setParent((Node *)this);
			}
		}

		// Bounded
		// while
		IterationStatement::IterationStatement(const unsigned int lineNumber, Node &node0, const std::string &lowerBound, const std::string &upperBound, Node &node1, const std::string &variant) : Node("IterationStatement", variant, this->globalCount++), lineNumber(lineNumber) {
			isRoot = false;

			if (node0.isType("CompoundStatement")) {
				std::vector<Node *> blockItemLists = tools::Query::retrieveChildren(node0, "BlockItemList");

				Node *blockItemList0;
				if (blockItemLists.size() > 0) {
					blockItemList0 = blockItemLists[0];
				} else {
					blockItemList0 = new PrimaryExpression("", "terminal");
				}

				children.push_back(blockItemList0);
				blockItemList0->setParent((Node *)this);
			} else {
				children.push_back(&node0);
				node0.setParent((Node *)this);
			}

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
			
			this->lowerBound = lowerBound;
			this->upperBound = upperBound;
		}

		// Bounded
		// dowhile
		IterationStatement::IterationStatement(const unsigned int lineNumber, Node &node0, Node &node1, const std::string &lowerBound, const std::string &upperBound, const std::string &variant) : Node("IterationStatement", variant, this->globalCount++), lineNumber(lineNumber) {
			isRoot = false;

			if (node0.isType("CompoundStatement")) {
				std::vector<Node *> blockItemLists = tools::Query::retrieveChildren(node0, "BlockItemList");

				Node *blockItemList0;
				if (blockItemLists.size() > 0) {
					blockItemList0 = blockItemLists[0];
				} else {
					blockItemList0 = new PrimaryExpression("", "terminal");
				}

				children.push_back(blockItemList0);
				blockItemList0->setParent((Node *)this);
			} else {
				children.push_back(&node0);
				node0.setParent((Node *)this);
			}

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
			
			this->lowerBound = lowerBound;
			this->upperBound = upperBound;
		}

		// Bounded
		// for0, for2
		IterationStatement::IterationStatement(const unsigned int lineNumber, Node &node0, Node &node1, const std::string &lowerBound, const std::string &upperBound, Node &node2, const std::string &variant) : Node("IterationStatement", variant, this->globalCount++), lineNumber(lineNumber) {
			isRoot = false;

			children.push_back(&node0);
			children.push_back(&node1);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);

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
			
			this->lowerBound = lowerBound;
			this->upperBound = upperBound;
		}

		// Bounded
		// for1, for3
		IterationStatement::IterationStatement(const unsigned int lineNumber, Node &node0, Node &node1, Node &node2, const std::string &lowerBound, const std::string &upperBound, Node &node3, const std::string &variant) : Node("IterationStatement", variant, this->globalCount++), lineNumber(lineNumber) {
			isRoot = false;

			children.push_back(&node0);
			children.push_back(&node1);
			children.push_back(&node2);

			node0.setParent((Node *)this);
			node1.setParent((Node *)this);
			node2.setParent((Node *)this);

			if (node3.isType("CompoundStatement")) {
				std::vector<Node *> blockItemLists = tools::Query::retrieveChildren(node3, "BlockItemList");

				Node *blockItemList3;
				if (blockItemLists.size() > 0) {
					blockItemList3 = blockItemLists[0];
				} else {
					blockItemList3 = new PrimaryExpression("", "terminal");
				}

				children.push_back(blockItemList3);
				blockItemList3->setParent((Node *)this);
			} else {
				children.push_back(&node3);
				node3.setParent((Node *)this);
			}
			
			this->lowerBound = lowerBound;
			this->upperBound = upperBound;
		}


		const std::string IterationStatement::getId(void) const {
			std::ostringstream name;
			name << variant << '_' << id;
			return name.str();
		}

		const std::string IterationStatement::getThreadScope(void) const {
			return threadScope;
		}

		int IterationStatement::getCount(void) {
			return globalCount;
		}

		void IterationStatement::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			threadScope = tools::SymbolTable::getScopeName();
			tools::SymbolTable::enterScope();
			isRoot = tools::Condition::enterScope(*this);

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->updateSymbolTable(type, isUsage, isRead);
			}

			tools::Condition::leaveScope(getType());
			tools::SymbolTable::leaveScope();
		}

		void IterationStatement::createTarot(const std::string &threadScope, tarot::Node &tarotNode) {
			tarot::Iteration *iterationTarot = new tarot::Iteration(threadScope, this);

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->createTarot(threadScope, *iterationTarot);
			}

			if (iterationTarot->hasChildren()) {
				tarotNode.append(*iterationTarot);
			}
		}

		const Node::Instantaneous IterationStatement::willPause(const bool requireBothBranches) {
			instantaneous.pauses = false;
			instantaneous.breaks = false;
			instantaneous.continues = false;
			instantaneous.returns = false;
			
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				const struct Node::Instantaneous result = (*i)->willPause(requireBothBranches);
				
				if (!instantaneous.breaks && !instantaneous.continues && !instantaneous.returns) {
					instantaneous.pauses = instantaneous.pauses || result.pauses;
					instantaneous.breaks = instantaneous.breaks || result.breaks;
					instantaneous.continues = instantaneous.continues || result.continues;
					instantaneous.returns = instantaneous.returns || result.returns;
				}
			}

			const bool isUnbounded1 = !instantaneous.pauses && instantaneous.continues;
			const bool isUnbounded2 = !instantaneous.pauses && !instantaneous.breaks && !instantaneous.continues && !instantaneous.returns;

			if ((isUnbounded1 || isUnbounded2) && upperBound.empty()) {
				std::ostringstream error;
				error << "IterationStatement::willPause: Loop at line " << lineNumber << " is potentially instantaneous." << std::endl;
				throw error.str();
			}
			
			instantaneous.breaks = false;
			instantaneous.continues = false;
			
			return instantaneous;
		}

		void IterationStatement::setWillPause(const bool pauses) {
			instantaneous.pauses = pauses;
		}
		
		const bool IterationStatement::getWillPause(void) {
			return instantaneous.pauses;
		}
		
		void IterationStatement::prettyPrint(std::ostream &output) {
			std::ostringstream synchronise;
			if (tools::Threading::isThread(threadScope) && tools::Condition::hasParStatements(threadScope, "IterationStatement", getId()) && !getWillPause()) {
				tools::Tab::indent();
				synchronise << std::endl << std::endl;
				synchronise << tools::Tab::toString() << "// forec:scheduler:iterationEnd:" << getId() << ":start" << std::endl;
				synchronise << tools::Tab::toString() << "// Synchronise end of iteration" << std::endl;
				synchronise << tools::Tab::toString() << threadScope << "ParParent.parId = -2;" << std::endl;
				synchronise << tools::Tab::toString() << threadScope << "ParParent.parStatus = FOREC_PAR_ON;" << std::endl;
				synchronise << tools::Tab::toString() << threadScope << "ParParent.programCounter = &&" << getId() << "_endAddress;" << std::endl;
				synchronise << tools::Tab::toString() << "goto " << threadScope << "ParHandlerMaster" << tools::Multicore::getCoreId(threadScope) << ';' << std::endl;
				synchronise << tools::Tab::toString() << getId() << "_endAddress:;" << std::endl;
				synchronise << tools::Tab::toString() << "// forec:scheduler:iterationEnd:" << getId() << ":end";
				tools::Tab::dedent();
			}

			if (isVariant("while")) {
				output << "while (" << *children[0] << ") {" << std::endl;
				tools::Tab::indent();
				
				if (!children[1]->isType("BlockItemList")) {
					output << tools::Tab::toString();
				}
				output << *children[1];
				output << synchronise.str() << std::endl;
				if (tools::Multicore::isArchitecture("microblaze") || tools::Multicore::isArchitecture("ptarm")) {
					output << tools::Tab::toString() << "asm volatile (\"nop\");" << std::endl;
				}
				if (!lowerBound.empty()) {
					output << tools::Tab::toString() << "// forec:iteration:"  << getId() << ":bound:" << lowerBound << ':' << upperBound << std::endl;
				}
				tools::Tab::dedent();
				output << tools::Tab::toString() << '}';
			} else if (isVariant("doWhile")) {
				output << "do {" << std::endl;
				tools::Tab::indent();
				
				if (!children[0]->isType("BlockItemList")) {
					output << tools::Tab::toString();
				}
				output << *children[0];
				output << synchronise.str() << std::endl;
				if (tools::Multicore::isArchitecture("microblaze") || tools::Multicore::isArchitecture("ptarm")) {
					output << tools::Tab::toString() << "asm volatile (\"nop\");" << std::endl;
				}
				if (!lowerBound.empty()) {
					output << tools::Tab::toString() << "// forec:iteration:"  << getId() << ":bound:" << lowerBound << ':' << upperBound << std::endl;
				}
				tools::Tab::dedent();
				output << tools::Tab::toString() << "} while (" << *children[1] << ");";
			} else if (isVariant("for0") || isVariant("for2")) {
				output << "for (" << *children[0] << " " << *children[1] << ") {" << std::endl;
				tools::Tab::indent();

				if (!children[2]->isType("BlockItemList")) {
					output << tools::Tab::toString();
				}
				output << *children[2];
				output << synchronise.str() << std::endl;
				if (tools::Multicore::isArchitecture("microblaze") || tools::Multicore::isArchitecture("ptarm")) {
					output << tools::Tab::toString() << "asm volatile (\"nop\");" << std::endl;
				}
				if (!lowerBound.empty()) {
					output << tools::Tab::toString() << "// forec:iteration:"  << getId() << ":bound:" << lowerBound << ':' << upperBound << std::endl;
				}
				tools::Tab::dedent();
				output << tools::Tab::toString() << '}';
			} else if (isVariant("for1") || isVariant("for3")) {
				output << "for (" << *children[0] << " " << *children[1] << " " << *children[2] << ") {" << std::endl;
				tools::Tab::indent();

				if (!children[3]->isType("BlockItemList")) {
					output << tools::Tab::toString();
				}
				output << *children[3];
				output << synchronise.str() << std::endl;
				if (tools::Multicore::isArchitecture("microblaze") || tools::Multicore::isArchitecture("ptarm")) {
					output << tools::Tab::toString() << "asm volatile (\"nop\");" << std::endl;
				}
				if (!lowerBound.empty()) {
					output << tools::Tab::toString() << "// forec:iteration:"  << getId() << ":bound:" << lowerBound << ':' << upperBound << std::endl;
				}
				tools::Tab::dedent();
				output << tools::Tab::toString() << '}';
			}
		}

	}
}
