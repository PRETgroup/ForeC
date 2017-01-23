/*
 *  Node.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 12/04/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"
#include "Thread.hpp"

#include "../ast/Node.hpp"

namespace forec {
	namespace tarot {
		int Node::count = 0;

		std::ostream &operator<<(std::ostream &output, Node &node) {
			node.prettyPrint(output);
			return output;
		}

		Node::Node(const std::string &threadScope, const std::string &type, forec::ast::Node *astNode) {
			children.clear();
			(this->threadScope) = threadScope;
			(this->parent) = NULL;
			(this->type) = type;
			(this->astNode) = astNode;
		}

		Node::Node(const Node &original, const std::string &type, const std::string &coreId) {
			(this->type) = original.type;
			(this->coreId) = coreId;

			children.clear();
			threadScope = original.threadScope;
			parent = original.parent;
			astNode = original.astNode;
			masterCoreId = original.masterCoreId;
		}

		void Node::incrementInternalId(void) {
			Node::count++;
		}
		
		void Node::setInternalId(void) {
			id = Node::count;
		}

		void Node::setInternalId(const int internalId) {
			id = internalId;
		}
				
		const int Node::getInternalId(void) const {
			return id;
		}

		const std::string Node::getId(void) const {
			return astNode->getId();
		}

		const std::string Node::getIdNumber(void) const {
			return astNode->getIdNumber();
		}


		const bool Node::isType(const std::string &type) const {
			return (this->type).compare(type) == 0;
		}

		const std::string Node::getType(void) const {
			return type;
		}

		const std::string Node::getThreadScope(void) const {
			return threadScope;
		}

		void Node::setThreadScope(const std::string &threadScope) {
			(this->threadScope) = threadScope;
		}

		void Node::setParent(Node *node) {
			parent = node;
		}

		const std::string Node::getCoreId(void) const {
			return coreId;
		}

		const std::string Node::getMasterCoreId(void) const {
			return masterCoreId;
		}

		void Node::setCoreId(const std::string &coreId) {
			(this->coreId) = coreId;
		}

		void Node::setMasterCoreId(const std::string &masterCoreId) {
			(this->masterCoreId) = masterCoreId;

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->setMasterCoreId(masterCoreId);
			}
		}

		const bool Node::isCoreId(const std::string &coreId) const {
			return (this->coreId).compare(coreId) == 0;
		}

		const bool Node::isMaster(void) const {
			return coreId.compare(masterCoreId) == 0;
		}

		void Node::append(Node &node) {
			children.push_back(&node);
			node.setParent(this);
		}

		void Node::prepend(Node &node) {
			children.insert(children.begin(), &node);
			node.setParent(this);
		}

		// Prepare tasks
		void Node::linkParThreads(void) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->linkParThreads();
			}
		}

		void Node::setParCore(void) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->setParCore();
			}
		}

		void Node::findThreadRecursion(std::set<std::string> &visitedThreadIds) throw(std::string) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->findThreadRecursion(visitedThreadIds);
			}
		}

		// Next par(...)s
		void Node::findNextPar(std::string &prevParId, std::vector<std::string> &prevAbortId, std::vector<std::string> &prevIterationId, std::vector<std::map<std::string, std::string> > &prevSelectionId, const std::string &threadScope) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->findNextPar(prevParId, prevAbortId, prevIterationId, prevSelectionId, threadScope);
			}
		}

		// Next par(...) in reaction
		void Node::findNextParInReaction(std::string &prevParId, std::vector<std::string> &prevAbortIdInReaction, std::vector<std::string> &prevIterationIdInReaction, std::vector<std::map<std::string, std::string> > &prevSelectionIdInReaction, const std::string &threadScope) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->findNextParInReaction(prevParId, prevAbortIdInReaction, prevIterationIdInReaction, prevSelectionIdInReaction, threadScope);
			}
		}
		
		// Last par(...)
		void Node::findLastPar(std::string &prevParId, const std::string &threadScope) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->findLastPar(prevParId, threadScope);
			}
		}

		void Node::addAborts(std::vector<std::string> &aborts, std::vector<std::pair<std::string, std::string> > &abortsWithPar) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->addAborts(aborts, abortsWithPar);
			}
		}

		// Process tasks
		void Node::extractParInformation(std::vector<Node *> &aborts, const std::string &enclosingParId) {
			for (std::vector<Node *>::reverse_iterator i = children.rbegin(); i != children.rend(); ++i) {
				(*i)->extractParInformation(aborts, enclosingParId);
			}
		}

		void Node::flatten(std::vector<Node *> &strongAborts, std::vector<Node *> &weakAborts, std::vector<Node *> &iterations, std::map<std::string, std::vector<Node *> > &selections, const std::string &enclosingParId, const std::string &enclosingThreadScope) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->flatten(strongAborts, weakAborts, iterations, selections, enclosingParId, enclosingThreadScope);
			}
		}

		const bool Node::hasChildren(void) {
			return children.size() > 0;
		}

		const bool Node::hasRecursive(const std::string &type, const std::string &coreId) {
			if (isType(type) && getMasterCoreId().compare(coreId) == 0) {
				return true;
			}
			
			// Return results of children.
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				if ((*i)->hasRecursive(type, coreId)) {
					return true;
				}
			}
			return false;
		}

		const bool Node::hasCoreIdRecursive(const std::string &coreId) {
			if (getMasterCoreId().compare(coreId) == 0) {
				return true;
			}

			// Return results of children.
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				if ((*i)->hasCoreIdRecursive(coreId)) {
					return true;
				}
			}
			return false;
		}

		std::vector<Node *> Node::find(const std::string &type) {
			// Search children.
			std::vector<Node *> results;
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				if ((*i)->isType(type)) {
					results.push_back(*i);
				}
			}
			return results;
		}

		std::vector<Node *> Node::findAll(const std::string &type) {
			std::vector<Node *> results;
			if (isType(type)) {
				results.push_back(this);
			}

			// Search children recursively.
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				std::vector<Node *> subResults = (*i)->findAll(type);
				results.insert(results.end(), subResults.begin(), subResults.end());
			}
			return results;
		}

		const std::string Node::toString(void) {
			std::ostringstream output;
			prettyPrint(output);
			return output.str();
		}

		void Node::toXml(std::ostream &output, const std::string &indent) {
			for (std::vector<Node *>::const_iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->toXml(output, indent);
			}
		}
		
	}
}
