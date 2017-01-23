/*
 *  Par.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 12/04/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Par.hpp"

#include "Abort.hpp"
#include "Iteration.hpp"
#include "Selection.hpp"
#include "Thread.hpp"

#include "Tarot.hpp"

#include "../ast/ParStatement.hpp"

#include "../tools/Multicore.hpp"

namespace forec {
	namespace tarot {
		Par::Par(const std::string &threadScope, ast::Node *astNode) : Node(threadScope, "Par", astNode) {

		}

		Par::Par(const Par &original, const std::string &type, const std::string &coreId) : Node(original, type, coreId) {
			for (std::vector<Node *>::const_iterator i = original.children.begin(); i != original.children.end(); ++i) {
				if ((*i)->hasCoreIdRecursive(coreId)) {
					if ((*i)->isType("Thread")) {
						Thread *nodeByCoreId = new Thread(*(Thread *)(*i), type, coreId);
						children.push_back(nodeByCoreId);
					}
				}
			}
		}

		const std::string Par::getId(void) const {
			return ((ast::ParStatement *)astNode)->getId();
		}

		const std::string Par::getIdNumber(void) const {
			return ((ast::ParStatement *)astNode)->getIdNumber();
		}

		void Par::linkParThreads(void) {
			// Add Thread to the vector of children nodes.
			const std::vector<std::string> threadIds = ((ast::ParStatement *)astNode)->getThreadIds();
			for (std::vector<std::string>::const_iterator threadId = threadIds.begin(); threadId != threadIds.end(); ++threadId) {
				append(*Tarot::getThread(*threadId));
			}
		}

		void Par::setParCore(void) {
			tools::Multicore::setParCorePriority(getThreadScope(), getCoreId(), isMaster());

			// Add participating coreId.
			Tarot::setParCore(getThreadScope(), getId(), getCoreId());
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->setParCore();
			}
		}

		void Par::findNextPar(std::string &prevParId, std::vector<std::string> &prevAbortId, std::vector<std::string> &prevIterationId, std::vector<std::map<std::string, std::string> > &prevSelectionId, const std::string &threadScope) {
			// Add this par(...) to the end of various scopes.
			Tarot::addNextParAfterPar(getCoreId(), threadScope, prevParId, getId());
			Tarot::addNextParAfterAbort(getCoreId(), threadScope, prevAbortId, getId());
			Tarot::addNextParAfterIteration(getCoreId(), threadScope, prevIterationId, getId());
			Tarot::addNextParAfterSelection(getCoreId(), threadScope, prevSelectionId, getId());

			// Set the previous par(...) to this.
			prevParId = getId();

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				std::string newPrevParId = "";
				std::vector<std::string> newPrevAbortId;
				std::vector<std::string> newPrevIterationId;
				std::vector<std::map<std::string, std::string> > newPrevSelectionId;
				(*i)->findNextPar(newPrevParId, newPrevAbortId, newPrevIterationId, newPrevSelectionId, threadScope);
			}
		}

		void Par::findNextParInReaction(std::string &prevParId, std::vector<std::string> &prevAbortIdInReaction, std::vector<std::string> &prevIterationIdInReaction, std::vector<std::map<std::string, std::string> > &prevSelectionIdInReaction, const std::string &threadScope) {
			// Add this par(...) to the end of various scopes.
			Tarot::addNextParAfterAbortInReaction(getCoreId(), threadScope, prevAbortIdInReaction, getId());
			Tarot::addNextParAfterIterationInReaction(getCoreId(), threadScope, prevIterationIdInReaction, getId());
			Tarot::addNextParAfterSelectionInReaction(getCoreId(), threadScope, prevSelectionIdInReaction, getId());

			// Set the previous par(...) to this.
			prevParId = getId();

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				std::string newPrevParId = "";
				std::vector<std::string> newPrevAbortIdInReaction;
				std::vector<std::string> newPrevIterationIdInReaction;
				std::vector<std::map<std::string, std::string> > newPrevSelectionIdInReaction;
				(*i)->findNextParInReaction(newPrevParId, newPrevAbortIdInReaction, newPrevIterationIdInReaction, newPrevSelectionIdInReaction, threadScope);
			}
		}

		void Par::findLastPar(std::string &prevParId, const std::string &threadScope) {
			// Set the previous par(...) to this.
			prevParId = getId();

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				std::string newPrevParId = "";
				(*i)->findLastPar(newPrevParId, threadScope);
			}
		}

		void Par::addAborts(std::vector<std::string> &aborts, std::vector<std::pair<std::string, std::string> > &abortsWithPar) {
			// Copy previous abort scopes around previous nestings of par(...)s.
			std::vector<std::pair<std::string, std::string> > newAbortsWithPar = abortsWithPar;

			// Append new abort scopes around this par(...).
			for (std::vector<std::string>::const_iterator abortId = aborts.begin(); abortId != aborts.end(); ++abortId) {
				newAbortsWithPar.push_back(std::pair<std::string, std::string>(*abortId, getId()));
			}

			// Save abort scopes around par(...).
			Tarot::addAborts(newAbortsWithPar, getId());

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				std::vector<std::string> newAborts;
				std::vector<std::pair<std::string, std::string> > newAbortsWithParCopy = newAbortsWithPar;
				(*i)->addAborts(newAborts, newAbortsWithParCopy);
			}
		}

		void Par::extractParInformation(std::vector<Node *> &aborts, const std::string &enclosingParId) {
			Tarot::setActiveParCores(getThreadScope(), getId());
			Tarot::setInactiveParCores(getThreadScope(), getId());
			Tarot::addReactionStart(getMasterCoreId(), getId(), getThreadScope());
			Tarot::addReactionEnd(getMasterCoreId(), getId(), getThreadScope());
			Tarot::addParHandler(getThreadScope(), getId(), enclosingParId, getMasterCoreId());

			for (std::vector<Node *>::const_iterator abort = aborts.begin(); abort != aborts.end(); ++abort) {
				Tarot::addAbortHandler(getThreadScope(), getId(), ((Abort *)*abort)->isVariant("strong"), ((Abort *)*abort)->getId(), ((Abort *)*abort)->getCondition());
			}

			for (std::vector<Node *>::reverse_iterator i = children.rbegin(); i != children.rend(); ++i) {
				(*i)->extractParInformation(aborts, getId());
			}
		}

		void Par::flatten(std::vector<Node *> &strongAborts, std::vector<Node *> &weakAborts, std::vector<Node *> &iterations, std::map<std::string, std::vector<Node *> > &selections, const std::string &enclosingParId, const std::string &enclosingThreadScope) {
			// Add par(...) handler to enclosing thread.
			Tarot::addParToLinkedList(getCoreId(), getId(), getMasterCoreId(), getThreadScope(), enclosingParId, enclosingThreadScope);

			// Add par(...) start scope to current thread.
			Tarot::addReactionStartToLinkedList(getCoreId(), getMasterCoreId(), getThreadScope(), getId());

			// Add strong aborts.
			for (std::vector<Node *>::const_iterator abort = strongAborts.begin(); abort != strongAborts.end(); ++abort) {
				Tarot::addAbortToLinkedList(((Abort *)*abort)->getId(), ((Abort *)*abort)->isVariant("strong"), (*abort)->getCoreId(), (*abort)->getThreadScope(), getId());
				Tarot::addAbortScope(((Abort *)*abort)->getId(), (*abort)->getCoreId(), getId());
			}

			// Add par(...) to the current iteration scope.
			if (iterations.begin() != iterations.end()) {
				Tarot::addIterationScope(((Iteration *)iterations.front())->getId(), iterations.front()->getCoreId(), getId());
			}

			// Add par(...) to the nested if-else selection scopes.
			for (std::map<std::string, std::vector<Node *> >::const_iterator branchType = selections.begin(); branchType != selections.end(); ++branchType) {
				for (std::vector<Node *>::const_iterator selection = branchType->second.begin(); selection != branchType->second.end(); ++selection) {
					Tarot::addSelectionScope(((Selection *)*selection)->getId(), branchType->first, (*selection)->getCoreId(), getId());
				}
			}

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->flatten(strongAborts, weakAborts, iterations, selections, getId(), getThreadScope());
			}

			// Add weak aborts.
			for (std::vector<Node *>::const_reverse_iterator abort = weakAborts.rbegin(); abort != weakAborts.rend(); ++abort) {
				Tarot::addAbortToLinkedList(((Abort *)*abort)->getId(), ((Abort *)*abort)->isVariant("strong"), (*abort)->getCoreId(), (*abort)->getThreadScope(), getId());
				Tarot::addAbortScope(((Abort *)*abort)->getId(), (*abort)->getCoreId(), getId());
			}

			// Add par(...) end scope to current thread.
			Tarot::addReactionEndToLinkedList(getCoreId(), getMasterCoreId(), getThreadScope(), getId());
		}

		const std::string Par::getTopNode(void) {
			std::ostringstream output;
			output << getId() << '_' << getInternalId() << "Start";
			return output.str();
		}
		
		const std::string Par::getBottomNode(void) {
			std::ostringstream output;
			output << getId() << '_' << getInternalId() << "End";
			return output.str();
		}

		void Par::prettyPrint(std::ostream &output) {
			output << Tab::toString() << "core" << getMasterCoreId() << ": " << getId() << std::endl;
			Tab::indent("|");
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				output << *(*i);
			}
			Tab::dedent();
		}

		void Par::toDot(std::ostream &output, std::string &previousNode, std::string &edgeAttributes, const bool toggle, std::ostringstream &abortScope) {
			setInternalId();

			output << Tab::toString() << previousNode << " -> " << getId() << '_' << getInternalId() << "Start" << edgeAttributes << std::endl;

			output << abortScope.str();
			abortScope.str("");

			output << Tab::toString() << "subgraph cluster_" << getId() << '_' << getInternalId() << " {" << std::endl;
			Tab::indent("");
			output << Tab::toString() << "style = filled" << std::endl;
			output << Tab::toString() << "color = " << (toggle ? "lightgrey" : "white") << std::endl;
			output << std::endl;
			output << Tab::toString() << getId() << '_' << getInternalId() << "Start [label = " << getIdNumber() << ", shape = triangle]" << std::endl;
			output << Tab::toString() << getId() << '_' << getInternalId() << "End [label = " << getIdNumber() << ", shape = invtriangle]" << std::endl;

			std::ostringstream previousNodeString;
			previousNodeString << getId() << '_' << getInternalId() << "Start";
			edgeAttributes = "[headport = n, tailport = s]";
			std::vector<std::string> topNodes;
			std::vector<std::string> bottomNodes;
			for (std::vector<Node *>::const_iterator i = children.begin(); i != children.end(); ++i) {
				previousNode = previousNodeString.str();
				output << std::endl;
				if ((*i)->hasChildren()) {
					(*i)->toDot(output, previousNode, edgeAttributes, !toggle, abortScope);
					output << Tab::toString() << previousNode << " -> " << getId() << '_' << getInternalId() << "End" << edgeAttributes << std::endl;
					topNodes.push_back((*i)->getTopNode());
					bottomNodes.push_back((*i)->getBottomNode());
				} else {
					output << Tab::toString() << getId() << '_' << getInternalId() << "Start -> " << getId() << '_' << getInternalId() << "End [label = " << ((Thread *)(*i))->getId() << ", fontcolor = blue, sametail = 0, samehead = 0, headport = n, tailport = s]" << std::endl;
				}
			}

			Tab::dedent();
			output << Tab::toString() << '}' << std::endl;
			
			output << Tab::toString() << '{' << std::endl;
			Tab::indent("");
			output << Tab::toString() << "edge[style = invis]" << std::endl;
			if (!topNodes.empty()) {
				output << Tab::toString() << getId() << '_' << getInternalId() << "Start" << " -> {" << topNodes.front();
				for (std::vector<std::string>::const_iterator i = topNodes.begin() + 1; i != topNodes.end(); ++i) {
					output << ' ' << *i;
				}
				output << '}' << std::endl;
			}
			
			if (!bottomNodes.empty()) {
				output << Tab::toString() << '{' << bottomNodes.front();
				for (std::vector<std::string>::const_iterator i = bottomNodes.begin() + 1; i != bottomNodes.end(); ++i) {
					output << ' ' << *i;
				}
				output << "} -> " << getId() << '_' << getInternalId() << "End" << std::endl;
			}
			Tab::dedent();
			output << Tab::toString() << '}' << std::endl;

			previousNodeString.str("");
			previousNodeString << getId() << '_' << getInternalId() << "End";
			previousNode = previousNodeString.str();
			edgeAttributes = " [headport = n, tailport = s]";

			incrementInternalId();
		}

		void Par::toXml(std::ostream &output, const std::string &indent) {
			output << std::endl;
			output << indent << "\t<par id=\"" << getIdNumber() << "\">" << std::endl;
			for (std::vector<Node *>::const_iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->toXml(output, indent + "\t");
			}
			output << indent << "\t</par>" << std::endl;
			output << indent;
		}

	}
}
