/*
 *  Selection.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 12/04/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Selection.hpp"

#include "Abort.hpp"
#include "Iteration.hpp"
#include "Par.hpp"
#include "Pause.hpp"

#include "Tarot.hpp"

#include "../ast/SelectionStatement.hpp"

namespace forec {
	namespace tarot {
		Selection::Selection(const std::string &threadScope, const std::string &branchType, ast::Node *astNode) : Node(threadScope, "Selection", astNode), branchType(branchType) {

		}

		Selection::Selection(const Selection &original, const std::string &type, const std::string &coreId) : Node(original, type, coreId), branchType(original.branchType) {
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

		void Selection::setIfBranch(Selection &selectionIfTarot) {
			(this->selectionIfTarot) = &selectionIfTarot;
		}

		const std::string Selection::getId(void) const {
			return ((ast::SelectionStatement *)astNode)->getId();
		}

		const std::string Selection::getIdNumber(void) const {
			return ((ast::SelectionStatement *)astNode)->getIdNumber();
		}

		const std::string Selection::getBranchType(void) const {
			return branchType;
		}

		const bool Selection::isBranchType(const std::string &branchType) const {
			return (this->branchType).compare(branchType) == 0;
		}

		void Selection::findNextPar(std::string &prevParId, std::vector<std::string> &prevAbortId, std::vector<std::string> &prevIterationId, std::vector<std::map<std::string, std::string> > &prevSelectionId, const std::string &threadScope) {
			// Save selection ID and branch type as a map.
			std::map<std::string, std::string> selectionId;
			selectionId[getId()] = getBranchType();

			if (isBranchType("if")) {
				for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
					(*i)->findNextPar(prevParId, prevAbortId, prevIterationId, prevSelectionId, threadScope);
				}

				// Add as the last selection scope.
				prevSelectionId.push_back(selectionId);
			} else if (isBranchType("else")) {
				// Create a separate scoping.
				std::vector<std::string> newPrevAbortId;
				std::vector<std::string> newPrevIterationId;
				std::vector<std::map<std::string, std::string> > newPrevSelectionId;

				for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
					(*i)->findNextPar(prevParId, newPrevAbortId, newPrevIterationId, newPrevSelectionId, threadScope);
				}

				// Add separate scoping of aborts, iterations and selections to the original.
				prevAbortId.insert(prevAbortId.end(), newPrevAbortId.begin(), newPrevAbortId.end());
				prevIterationId.insert(prevIterationId.end(), newPrevIterationId.begin(), newPrevIterationId.end());
				prevSelectionId.insert(prevSelectionId.end(), newPrevSelectionId.begin(), newPrevSelectionId.end());

				// Add as the last selection scope.
				prevSelectionId.push_back(selectionId);
			}
		}

		void Selection::findNextParInReaction(std::string &prevParId, std::vector<std::string> &prevAbortIdInReaction, std::vector<std::string> &prevIterationIdInReaction, std::vector<std::map<std::string, std::string> > &prevSelectionIdInReaction, const std::string &threadScope) {
			// Save selection ID and branch type as a map.
			std::map<std::string, std::string> selectionId;
			selectionId[getId()] = getBranchType();

			if (isBranchType("if")) {
				for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
					(*i)->findNextParInReaction(prevParId, prevAbortIdInReaction, prevIterationIdInReaction, prevSelectionIdInReaction, threadScope);
				}

				// Add as the last selection scope.
				prevSelectionIdInReaction.push_back(selectionId);
			} else if (isBranchType("else")) {
				// Create a separate scoping.
				std::vector<std::string> newPrevAbortIdInReaction;
				std::vector<std::string> newPrevIterationIdInReaction;
				std::vector<std::map<std::string, std::string> > newPrevSelectionIdInReaction;

				for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
					(*i)->findNextParInReaction(prevParId, newPrevAbortIdInReaction, newPrevIterationIdInReaction, newPrevSelectionIdInReaction, threadScope);
				}

				// Add separate scoping of aborts, iterations and selections to the original.
				prevAbortIdInReaction.insert(prevAbortIdInReaction.end(), newPrevAbortIdInReaction.begin(), newPrevAbortIdInReaction.end());
				prevIterationIdInReaction.insert(prevIterationIdInReaction.end(), newPrevIterationIdInReaction.begin(), newPrevIterationIdInReaction.end());
				prevSelectionIdInReaction.insert(prevSelectionIdInReaction.end(), newPrevSelectionIdInReaction.begin(), newPrevSelectionIdInReaction.end());

				// Add as the last selection scope.
				prevSelectionIdInReaction.push_back(selectionId);
			}
		}

		void Selection::findLastPar(std::string &prevParId, const std::string &threadScope) {
			// Remember the last par(...) before entering this selection.
			const std::string lastPrevParId = prevParId;

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->findLastPar(prevParId, threadScope);
			}

			// If a par(...) exists within the selection body, then add the last par(...) encountered.
			if (prevParId.compare(lastPrevParId) != 0) {
				Tarot::addLastParIdInSelection(getCoreId(), threadScope, getId(), getBranchType(), prevParId);
			}
		}

		void Selection::flatten(std::vector<Node *> &strongAborts, std::vector<Node *> &weakAborts, std::vector<Node *> &iterations, std::map<std::string, std::vector<Node *> > &selections, const std::string &enclosingParId, const std::string &enclosingThreadScope) {
			// Add selection scope.
			selections[getBranchType()].push_back(this);

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->flatten(strongAborts, weakAborts, iterations, selections, enclosingParId, enclosingThreadScope);
			}

			// Remove selection scope.
			selections[getBranchType()].pop_back();
		}

		const std::string Selection::getTopNode(void) {
			std::ostringstream output;
			output << getId() << '_' << getInternalId() << "Start";
			return output.str();
		}
		
		const std::string Selection::getBottomNode(void) {
			std::ostringstream output;
			output << getId() << '_' << getInternalId() << "End";
			return output.str();
		}

		void Selection::prettyPrint(std::ostream &output) {
			output << Tab::toString() << "core" << getMasterCoreId() << ": " << getBranchType() << '_' << getId() << std::endl;
			Tab::indent();
			for (std::vector<Node *>::const_iterator i = children.begin(); i != children.end(); ++i) {
				output << *(*i);
			}
			Tab::dedent();
		}

		void Selection::toDot(std::ostream &output, std::string &previousNode, std::string &edgeAttributes, const bool toggle, std::ostringstream &abortScope) {
			if (isBranchType("if")) {
				setInternalId();

				output << Tab::toString() << previousNode << " -> " << getId() << '_' << getInternalId() << "Start" << edgeAttributes << std::endl;

				output << abortScope.str();
				abortScope.str("");

				output << Tab::toString() << "subgraph cluster_" << getId() << '_' << getInternalId() << " {" << std::endl;
				Tab::indent("");
				output << Tab::toString() << "style = invis" << std::endl;

				output << Tab::toString() << getId() << '_' << getInternalId() << "Start [label = " << getIdNumber() << ", shape = diamond]" << std::endl;

				edgeAttributes = " [label = true]";
			} else {
				setInternalId(selectionIfTarot->getInternalId());
				edgeAttributes = " [label = false]";
			}

			std::ostringstream previousNodeString;
			previousNodeString << getId() << '_' << getInternalId() << "Start";

			if (children.size() > 0) {
				previousNode = previousNodeString.str();
				for (std::vector<Node *>::const_iterator i = children.begin(); i != children.end(); ++i) {
					(*i)->toDot(output, previousNode, edgeAttributes, toggle, abortScope);
				}

				output << Tab::toString() << previousNode << " -> " << getId() << '_' << getInternalId() << "End" << edgeAttributes << std::endl;
			} else {
				output << Tab::toString() << getId() << '_' << getInternalId() << "Start -> " << getId() << '_' << getInternalId() << "End" << edgeAttributes << std::endl;
			}

			if (isBranchType("if")) {
				output << Tab::toString() << getId() << '_' << getInternalId() << "End [label = " << getIdNumber() << ", shape = point, width = 0.01]" << std::endl;
			}

			edgeAttributes = "";

			previousNodeString.str("");
			previousNodeString << getId() << '_' << getInternalId() << "End";
			previousNode = previousNodeString.str();

			if (isBranchType("else")) {
				incrementInternalId();
				
				Tab::dedent();
				output << Tab::toString() << '}' << std::endl;
			}
		}
	}
}
