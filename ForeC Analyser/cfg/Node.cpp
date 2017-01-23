/*
 *  Node.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 04/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace cfg {

		// Initialise static variable
		int Node::globalCount = 0;

		std::ostream &operator<<(std::ostream &output, Node &node) {
			node.prettyPrint(output);
			return output;
		}

		Node::Node(const std::string &type, const std::string &variant, const int id) : id(id), type(type), variant(variant) {
			parent = NULL;
			iterationBound = NULL;
			children.clear();
			globalCount++;

			previousNodes.clear();
			nextNodes.clear();
		}

		const std::string Node::getId(void) const {
			std::ostringstream name;
			name << type << "_" << variant << "_" << id;
			return name.str();
		}

		const std::string Node::getIdNumber(void) const {
			std::ostringstream name;
			name << id;
			return name.str();
		}

		const bool Node::isType(const std::string &type) const {
			return (this->type).compare(type) == 0;
		}

		const std::string Node::getType(void) const {
			return type;
		}

		const bool Node::isVariant(const std::string &variant) const {
			return (this->variant).compare(variant) == 0;
		}

		const std::string Node::getVariant(void) const {
			return variant;
		}
		
		void Node::setVariant(const std::string &variant) {
			this->variant = variant;
		}

		void Node::setParent(Node *node) {
			parent = node;
		}
		
		Node *Node::getParent(void) {
			return parent;
		}
		
		int Node::getGlobalCount(void) {
			return globalCount;
		}

		void Node::append(Node &node) {
			children.push_back(&node);

			node.setParent(this);
		}

		void Node::prepend(Node &node) {
			children.insert(children.begin(), &node);

			node.setParent(this);
		}
		
		Node *Node::getFirstChildNode(void) {
			if (children.empty()) {
				return NULL;
			}
			
			return children.front();
		}
		
		void Node::linkNodes(void) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->linkNodes();
			}
		}

		void Node::addPreviousNode(Node &previousNode) {
			previousNodes.push_back(&previousNode);
		}
		
		void Node::addNextNode(Node &nextNode, const int latency, const bool needAlignment) {
			std::pair<int, bool> latencyAlignment (latency, needAlignment);
			std::pair<Node *, std::pair<int, bool> > next (&nextNode, latencyAlignment);
			nextNodes.push_back(next);
		}
		
		void Node::removePreviousNode(Node &previousNode) {
			for (std::vector<Node *>::iterator i = previousNodes.begin(); i != previousNodes.end(); ++i) {
				if ((*i) == &previousNode) {
					previousNodes.erase(i);
					break;
				}
			}
		}
		
		void Node::removeNextNode(Node &nextNode) {
			for (std::vector<std::pair<Node *, std::pair<int, bool> > >::iterator i = nextNodes.begin(); i != nextNodes.end(); ++i) {
				if (i->first == &nextNode) {
					nextNodes.erase(i);
					break;
				}
			}
		}
		
		void Node::removeAllNextNodes(void) {
			nextNodes.clear();
		}
		
		void Node::removeAllPreviousNodes(void) {
			previousNodes.clear();
		}
		
		std::vector<Node *> Node::getPreviousNodes(void) {
			return previousNodes;
		}
		
		std::vector<std::pair<Node *, std::pair<int, bool> > > Node::getNextNodes(void) {
			return nextNodes;
		}
		
		void Node::resolveDestinations(void) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->resolveDestinations();
			}
		}
		
		void Node::setIterationBound(Node &iterationBound) {
			this->iterationBound = &iterationBound;
		}
		
		Node *Node::getIterationBound(void) {
			return this->iterationBound;
		}
		
		const bool Node::hasIterationBound(void) {
			return (this->iterationBound != NULL);
		}

		const int Node::mergeNodes(const bool mergeGlobalAccesses) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->mergeNodes(mergeGlobalAccesses);
			}
			
			return -1;
		}
		
		void Node::removeUnreachableNodes(void) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->removeUnreachableNodes();
			}
		}
		
		void Node::mergeBranches(void) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->mergeBranches();
			}
		}
		
		void Node::inlineFunctions(void) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->inlineFunctions();
			}
		}

		const bool Node::has(const std::string &type, const std::string &variant) {
			if (isType(type)) {
				if (variant.compare("none") == 0 || isVariant(variant)) {
					return true;
				}
			}
			
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				if ((*i)->has(type, variant)) {
					return true;
				}
			}
			return false;
		}

		std::vector<Node *> Node::find(const std::string &type, const std::string &variant) {
			std::vector<Node *> results;
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				if ((*i)->isType(type)) {
					if (variant.compare("none") == 0 || (*(*i)).isVariant(variant)) {
						results.push_back(*i);
					}
				}
			}
			return results;
		}

		std::vector<Node *> Node::findAll(const std::string &type, const std::string &variant) {
			std::vector<Node *> results;

			// Ignore forec::scheduler::counter
			if (isType("Scheduler") && isVariant("counter")) {
				return results;
			}
			
			if (isType(type)) {
				if (variant.compare("none") == 0 || isVariant(variant)) {
					results.push_back(this);
				}
			}

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				std::vector<Node *> subResults = (*i)->findAll(type, variant);
				results.insert(results.end(), subResults.begin(), subResults.end());
			}
			return results;
		}

		Node *Node::findFirst(const std::string &type, const std::string &variant) {
			std::vector<Node *> results;
			if (isType(type)) {
				if (variant.compare("none") == 0 || isVariant(variant)) {
					return this;
				}
			}
			
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				Node *subResults = (*i)->findFirst(type, variant);
				if (subResults != NULL) {
					return subResults;
				}
			}
			return NULL;
		}

		Node *Node::findFirstChildNot(const std::string &type, const std::string &variant) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				if (!(*i)->isType(type)) {
					if (variant.compare("none") == 0 || !(*(*i)).isVariant(variant)) {
						return *i;
					}
				}
			}
			return NULL;
		}

		std::string *Node::toString(void) {
			std::ostringstream output;
			prettyPrint(output);
			return new std::string(output.str());
		}
		
	}
}

