/*
 *  Thread.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 12/04/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Thread.hpp"

#include "Abort.hpp"
#include "Iteration.hpp"
#include "Par.hpp"
#include "Pause.hpp"
#include "Selection.hpp"

#include "Tarot.hpp"

#include "../ast/ThreadDefinition.hpp"

namespace forec {
	namespace tarot {
		Thread::Thread(const std::string &threadScope, ast::Node *astNode) : Node(threadScope, "Thread", astNode) {

		}

		Thread::Thread(const Thread &original, const std::string &type, const std::string &coreId) : Node(original, type, coreId) {
			for (std::vector<Node *>::const_iterator i = original.children.begin(); i != original.children.end(); ++i) {
				if ((*i)->isType("Pause")) {
					Pause *nodeByCoreId = new Pause(*(Pause *)(*i), type, coreId);
					children.push_back(nodeByCoreId);
				}

				if ((*i)->hasCoreIdRecursive(coreId)) {
					if ((*i)->isType("Abort")) {
						Abort *nodeByCoreId = new Abort(*(Abort *)(*i), type, coreId);
						children.push_back(nodeByCoreId);
					} else if ((*i)->isType("Iteration")) {
						Iteration *nodeByCoreId = new Iteration(*(Iteration *)(*i), type, coreId);
						children.push_back(nodeByCoreId);
					} else if ((*i)->isType("Par")) {
						Par *nodeByCoreId = new Par(*(Par *)(*i), type, coreId);
						children.push_back(nodeByCoreId);
					} else if ((*i)->isType("Selection")) {
						Selection *nodeByCoreId = new Selection(*(Selection *)(*i), type, coreId);
						children.push_back(nodeByCoreId);
					}
				}
			}
		}

		const std::string Thread::getId(void) const {
			return ((ast::ThreadDefinition *)astNode)->getId();
		}

		void Thread::findThreadRecursion(std::set<std::string> &visitedThreadIds) throw(std::string) {
			// Determine if thread ID has been encountered.
			if (visitedThreadIds.count(getId()) > 0) {
				throw std::string("Tarot::Thread::findThreadRecursion: Thread recursion found for thread " + getId() + '.');
			}

			// Add thread ID
			visitedThreadIds.insert(getId());

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->findThreadRecursion(visitedThreadIds);
			}

			// Remove thread ID
			visitedThreadIds.erase(getId());
		}

		void Thread::findNextPar(std::string &prevParId, std::vector<std::string> &prevAbortId, std::vector<std::string> &prevIterationId, std::vector<std::map<std::string, std::string> > &prevSelectionId, const std::string &threadScope) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->findNextPar(prevParId, prevAbortId, prevIterationId, prevSelectionId, getId());
			}
		}

		void Thread::findNextParInReaction(std::string &prevParId, std::vector<std::string> &prevAbortIdInReaction, std::vector<std::string> &prevIterationIdInReaction, std::vector<std::map<std::string, std::string> > &prevSelectionIdInReaction, const std::string &threadScope) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->findNextParInReaction(prevParId, prevAbortIdInReaction, prevIterationIdInReaction, prevSelectionIdInReaction, getId());
			}
		}

		void Thread::findLastPar(std::string &prevParId, const std::string &threadScope) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->findLastPar(prevParId, getId());
			}

			// Add the previously encountered par(...).
			Tarot::addLastParInReaction(getCoreId(), getId(), prevParId);
			Tarot::addLastParIdInThread(getCoreId(), getId(), prevParId);
		}

		void Thread::extractParInformation(std::vector<Node *> &aborts, const std::string &enclosingParId) {
			Tarot::addThreadHandler(getId(), enclosingParId);

			std::vector<Node *> newAborts;
			for (std::vector<Node *>::reverse_iterator i = children.rbegin(); i != children.rend(); ++i) {
				(*i)->extractParInformation(newAborts, enclosingParId);
			}
		}

		void Thread::flatten(std::vector<Node *> &strongAborts, std::vector<Node *> &weakAborts, std::vector<Node *> &iterations, std::map<std::string, std::vector<Node *> > &selections, const std::string &enclosingParId, const std::string &enclosingThreadScope) {
			Tarot::addThreadToLinkedList(getId(), getCoreId(), isMaster(), enclosingThreadScope, enclosingParId);

			// Create separate scoping for aborts.
			std::vector<Node *> newStrongAborts;
			std::vector<Node *> newWeakAborts;
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->flatten(newStrongAborts, newWeakAborts, iterations, selections, enclosingParId, enclosingThreadScope);
			}
		}

		const std::string Thread::getTopNode(void) {
			if (!children.empty()) {
				return children.front()->getTopNode();
			}
			
			return "";
		}
		
		const std::string Thread::getBottomNode(void) {
			if (!children.empty()) {
				return children.back()->getBottomNode();
			}
			
			return "";
		}

		void Thread::prettyPrint(std::ostream &output) {
			output << Tab::toString() << "core" << getMasterCoreId() << ": " << getId() << "__thread" << std::endl;
			Tab::indent();
			for (std::vector<Node *>::const_iterator i = children.begin(); i != children.end(); ++i) {
				output << *(*i);
			}
			Tab::dedent();
		}

		void Thread::toDot(std::ostream &output, std::string &previousNode, std::string &edgeAttributes, const bool toggle, std::ostringstream &abortScope) {
			setInternalId();

			output << abortScope.str();
			abortScope.str("");

			edgeAttributes = " [label = " + getId() + ", fontcolor = blue]";

			for (std::vector<Node *>::const_iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->toDot(output, previousNode, edgeAttributes, toggle, abortScope);
			}

			incrementInternalId();
		}

		void Thread::toXml(std::ostream &output, const std::string &indent) {
			output << indent << "\t<thread id=\"" << getId() << "\">";
			for (std::vector<Node *>::const_iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->toXml(output, indent + "\t");
			}
			output << "</thread>" << std::endl;
		}
	}
}


