/*
 *  Node.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

#include "../tarot/Node.hpp"

#include "../tools/SymbolTable.hpp"
#include "../tools/Template.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int Node::globalCount = 0;

		std::ostream &operator<<(std::ostream &output, Node &node) {
			node.prettyPrint(output);
			return output;
		}

		Node::Node(const std::string &type, const std::string &variant, const int id) : id(id), type(type), variant(variant) {
			parent = NULL;
			children.clear();
			globalCount++;
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

		void Node::setParent(Node *node) {
			parent = node;
		}
		
		Node *Node::getParent(void) const {
			return parent;
		}

		void Node::takeOut(std::vector<Node *> &nodes) {
			nodes.push_back((Node *)this);
			parent->remove((Node *)this);
		}

		void Node::remove(const Node *node) {
			for (std::vector<Node *>::reverse_iterator i = children.rbegin(); i != children.rend(); ++i) {
				if ((*i) == node) {
					long int offset = children.rend() - i - 1;
					children.erase(children.begin() + offset);
					break;
				}
			}
		}
		
		void Node::replace(Node *oldNode, Node *newNode) {
			for (std::vector<Node *>::reverse_iterator i = children.rbegin(); i != children.rend(); ++i) {
				if ((*i) == oldNode) {
					(*i) = newNode;
					newNode->setParent(this);
					break;
				}
			}
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
		
		// requireBothBranches determines whether jump statements in SelectionStatements
		// are required in both branches to be returned.
		const struct Node::Instantaneous Node::willPause(const bool requireBothBranches) {
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
			
			return instantaneous;
		}

		void Node::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->updateSymbolTable(type, isUsage, isRead);
			}
		}
		
		std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > > Node::pullUpIndirectParallelVariables(void) {
			std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > > indirectParallelVariables;
				
			// Collect all the child thread's indirect variable accesses. Set the accesses as sequential. Set this thread as the indirect accessor.
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > > subResults = (*i)->pullUpIndirectParallelVariables();
				for (std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > >::iterator variable = subResults.begin(); variable != subResults.end(); ++variable) {
					for (std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > >::iterator useDef = variable->second.begin(); useDef != variable->second.end(); ++useDef) {
						indirectParallelVariables[variable->first][useDef->first].first = tools::SymbolTable::skip;
						indirectParallelVariables[variable->first][useDef->first].second.insert(useDef->second.second.begin(), useDef->second.second.end());
					}
				}
			}
			
			return indirectParallelVariables;
		}
		
		void Node::pullDownIndirectParallelVariables(std::set<PrimaryExpression *> &definedVariables) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->pullDownIndirectParallelVariables(definedVariables);
			}
		}
		
		void Node::createTarot(const std::string &threadScope) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->createTarot(threadScope);
			}
		}

		void Node::createTarot(const std::string &threadScope, tarot::Node &tarotNode) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->createTarot(threadScope, tarotNode);
			}
		}

		std::string *Node::toString(void) {
			std::ostringstream output;
			prettyPrint(output);
			return new std::string(output.str());
		}
	}
}

