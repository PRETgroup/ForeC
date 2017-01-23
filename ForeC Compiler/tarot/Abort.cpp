/*
 *  Abort.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 12/04/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Abort.hpp"

#include "Tarot.hpp"

#include "Iteration.hpp"
#include "Par.hpp"
#include "Pause.hpp"
#include "Selection.hpp"

#include "../ast/AbortStatement.hpp"

namespace forec {
	namespace tarot {
		Abort::Abort(const std::string &threadScope, ast::Node *astNode) : Node(threadScope, "Abort", astNode) {

		}

		Abort::Abort(const Abort &original, const std::string &type, const std::string &coreId) : Node(original, type, coreId) {
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

		const std::string Abort::getId(void) const {
			return ((ast::AbortStatement *)astNode)->getId();
		}

		const std::string Abort::getCondition(void) const {
			return ((ast::AbortStatement *)astNode)->getCondition(true);
		}

		const bool Abort::isVariant(const std::string &variant) const {
			return ((ast::AbortStatement *)astNode)->isVariant(variant);
		}

		void Abort::findNextPar(std::string &prevParId, std::vector<std::string> &prevAbortId, std::vector<std::string> &prevIterationId, std::vector<std::map<std::string, std::string> > &prevSelectionId, const std::string &enclosingThreadScope) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->findNextPar(prevParId, prevAbortId, prevIterationId, prevSelectionId, enclosingThreadScope);
			}

			// Add as the last abort scope.
			prevAbortId.push_back(getId());
		}

		void Abort::findNextParInReaction(std::string &prevParId, std::vector<std::string> &prevAbortIdInReaction, std::vector<std::string> &prevIterationIdInReaction, std::vector<std::map<std::string, std::string> > &prevSelectionIdInReaction, const std::string &enclosingThreadScope) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->findNextParInReaction(prevParId, prevAbortIdInReaction, prevIterationIdInReaction, prevSelectionIdInReaction, enclosingThreadScope);
			}

			// Add as the last abort scope.
			prevAbortIdInReaction.push_back(getId());
		}

		void Abort::findLastPar(std::string &prevParId, const std::string &threadScope) {
			// Remember the last par(...) before entering this abort.
			const std::string lastPrevParId = prevParId;

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->findLastPar(prevParId, threadScope);
			}

			// If a par(...) exists within the abort body, then add the last par(...) encountered.
			if (prevParId.compare(lastPrevParId) != 0) {
				Tarot::addLastParIdInAbort(getCoreId(), threadScope, getId(), prevParId);
			}
		}

		void Abort::addAborts(std::vector<std::string> &aborts, std::vector<std::pair<std::string, std::string> > &abortsWithPar) {
			// Add abort scope.
			aborts.push_back(getId());

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->addAborts(aborts, abortsWithPar);
			}

			aborts.pop_back();
		}

		void Abort::extractParInformation(std::vector<Node *> &aborts, const std::string &enclosingParId) {
			// Add abort scope.
			aborts.push_back(this);

			for (std::vector<Node *>::reverse_iterator i = children.rbegin(); i != children.rend(); ++i) {
				(*i)->extractParInformation(aborts, enclosingParId);
			}

			aborts.pop_back();
		}

		void Abort::flatten(std::vector<Node *> &strongAborts, std::vector<Node *> &weakAborts, std::vector<Node *> &iterations, std::map<std::string, std::vector<Node *> > &selections, const std::string &enclosingParId, const std::string &enclosingThreadScope) {
			// Add abort to relevant abort type.
			if (isVariant("strong")) {
				strongAborts.push_back(this);
			} else if (isVariant("weak")) {
				weakAborts.push_back(this);
			}

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->flatten(strongAborts, weakAborts, iterations, selections, enclosingParId, enclosingThreadScope);
			}

			// Remove abort from relevant abort type.
			if (isVariant("strong")) {
				strongAborts.pop_back();
			} else if (isVariant("weak")) {
				weakAborts.pop_back();
			}
		}

		const std::string Abort::getTopNode(void) {
			if (!children.empty()) {
				return children.front()->getTopNode();
			}
			
			return "";
		}

		const std::string Abort::getBottomNode(void) {
			if (!children.empty()) {
				return children.back()->getBottomNode();
			}
			
			return "";
		}

		void Abort::prettyPrint(std::ostream &output) {
			output << Tab::toString() << "core" << getMasterCoreId() << ": " << getId() << std::endl;
			Tab::indent(":");
			for (std::vector<Node *>::const_iterator i = children.begin(); i != children.end(); ++i) {
				output << *(*i);
			}
			Tab::dedent();
		}

		void Abort::toDot(std::ostream &output, std::string &previousNode, std::string &edgeAttributes, const bool toggle, std::ostringstream &abortScope) {
			setInternalId();

			abortScope << Tab::toString() << "subgraph cluster_" << getId() << '_' << getInternalId() << " {" << std::endl;
			Tab::indent("");
			abortScope << Tab::toString() << "color = black" << std::endl;
			abortScope << Tab::toString() << "style = dotted" << std::endl;
			abortScope << std::endl;

			for (std::vector<Node *>::const_iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->toDot(output, previousNode, edgeAttributes, toggle, abortScope);
			}

			output << Tab::toString() << "label = \"" << getId() << "\\nwhen (" << getCondition() << ")\"" << std::endl;
			Tab::dedent();
			output << Tab::toString() << '}' << std::endl;

			incrementInternalId();
		}
	}
}
