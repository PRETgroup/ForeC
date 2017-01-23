/*
 *  AbortStatement.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "AbortStatement.hpp"

#include "ParStatement.hpp"
#include "PrimaryExpression.hpp"

#include "../tarot/Tarot.hpp"
#include "../tarot/Node.hpp"
#include "../tarot/Abort.hpp"

#include "../tools/Abort.hpp"
#include "../tools/Query.hpp"
#include "../tools/Multicore.hpp"
#include "../tools/SymbolTable.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int AbortStatement::globalCount = 0;

		AbortStatement::AbortStatement(Node &node0, Node &node1, const std::string &variant) : Node("AbortStatement", variant, this->globalCount++) {
			// Check that the compound statement isn't empty
			std::vector<Node *> blockItemLists = tools::Query::retrieveChildren(node0, "BlockItemList");

			Node *blockItemList0;
			if (blockItemLists.size() > 0) {
				blockItemList0 = blockItemLists[0];
			} else {
				blockItemList0 = new PrimaryExpression("", "terminal");
			}

			children.push_back(blockItemList0);
			blockItemList0->setParent((Node *)this);

			children.push_back(&node1);
			node1.setParent((Node *)this);
		}

		const std::string AbortStatement::getId(void) const {
			std::ostringstream name;
			name << "abort" << (isVariant("weak") ? "Weak" : "Strong") << id;
			return name.str();
		}

		const std::string AbortStatement::getCondition(const bool suppressCopySuffix) {
			std::vector<Node *> primaryExpressions = tools::Query::retrieveAll(*children.back(), "PrimaryExpression", "identifier");
			for (std::vector<Node *>::iterator variable = primaryExpressions.begin(); variable != primaryExpressions.end(); ++variable) {
				((PrimaryExpression *)*variable)->setSuppressCopySuffix(suppressCopySuffix);
			}
		
			std::ostringstream condition;
			condition << *children.back();
			
			for (std::vector<Node *>::iterator variable = primaryExpressions.begin(); variable != primaryExpressions.end(); ++variable) {
				((PrimaryExpression *)*variable)->setSuppressCopySuffix(false);
			}
			
			return condition.str();
		}

		const std::string AbortStatement::getThreadScope(void) const {
			return threadScope;
		}

		int AbortStatement::getCount(void) {
			return globalCount;
		}

		void AbortStatement::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			threadScope = tools::SymbolTable::getScopeName();
			tools::Abort::enterScope(*this);
			tools::SymbolTable::enterScope();

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->updateSymbolTable(type, isUsage, isRead);
			}

			tools::SymbolTable::leaveScope();
			tools::Abort::leaveScope();
		}

		void AbortStatement::createTarot(const std::string &threadScope, tarot::Node &tarotNode) {
			tarot::Abort *abortTarot = new tarot::Abort(threadScope, this);

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->createTarot(threadScope, *abortTarot);
			}
			tarotNode.append(*abortTarot);
		}

		const struct Node::Instantaneous AbortStatement::willPause(const bool requireBothBranches) {
			// An immediate abort can preempt its body without pausing.
			instantaneous = children[0]->willPause(requireBothBranches);
			instantaneous.pauses = false;
			
			return instantaneous;
		}
		
		void AbortStatement::prettyPrint(std::ostream &output) {
			output << "/* " << getId() << " */ {" << std::endl;
			tools::Tab::indent();

			if (isVariant("strong")) {
				output << tools::Tab::toString() << "// forec:statement:abort:" << getId() << ":start" << std::endl;
				output << tools::Tab::toString() << "if (" << getCondition(false) << ") {" << std::endl;
				tools::Tab::indent();
				output << tools::Tab::toString() << "goto abortEnd_" << getId() << ';' << std::endl;
				tools::Tab::dedent();
				output << tools::Tab::toString() << '}' << std::endl;
				output << tools::Tab::toString() << "// forec:statement:abort:" << getId() << ":end" << std::endl << std::endl;
			}

			output << *children[0] << std::endl;
			output << tools::Tab::toString() << "abortEnd_" << getId() << ":;" << std::endl;
			tools::Tab::dedent();
			output << tools::Tab::toString() << "} // when (" << getCondition(false) << ");" << std::endl;
			output << tools::Tab::toString() << "// forec:statement:abort:" << getId() << ":scope:end";
		}

	}
}
