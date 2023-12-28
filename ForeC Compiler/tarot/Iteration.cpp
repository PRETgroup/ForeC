/*
 *  Iteration.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 12/04/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Iteration.hpp"

#include "Abort.hpp"
#include "Par.hpp"
#include "Pause.hpp"
#include "Selection.hpp"

#include "Tarot.hpp"

#include "../ast/IterationStatement.hpp"

namespace forec {
	namespace tarot {
		Iteration::Iteration(const std::string &threadScope, ast::Node *astNode) : Node(threadScope, "Iteration", astNode) {

		}

		Iteration::Iteration(const Iteration &original, const std::string &type, const std::string &coreId) : Node(original, type, coreId) {
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

		const std::string Iteration::getId(void) const {
			return ((ast::IterationStatement *)astNode)->getId();
		}

		void Iteration::findNextPar(std::string &prevParId, std::vector<std::string> &prevAbortId, std::vector<std::string> &prevIterationId, std::vector<std::map<std::string, std::string> > &prevSelectionId, const std::string &threadScope) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->findNextPar(prevParId, prevAbortId, prevIterationId, prevSelectionId, threadScope);
			}

			// Add as the last iteration scope.
			prevIterationId.push_back(getId());
		}

		void Iteration::findNextParInReaction(std::string &prevParId, std::vector<std::string> &prevAbortIdInReaction, std::vector<std::string> &prevIterationIdInReaction, std::vector<std::map<std::string, std::string> > &prevSelectionIdInReaction, const std::string &threadScope) {
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->findNextParInReaction(prevParId, prevAbortIdInReaction, prevIterationIdInReaction, prevSelectionIdInReaction, threadScope);
			}

			// Add as the last iteration scope.
			prevIterationIdInReaction.push_back(getId());
		}

		void Iteration::findLastPar(std::string &prevParId, const std::string &threadScope) {
			// Remember the last par(...) before entering this iteration.
			const std::string lastPrevParId = prevParId;

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->findLastPar(prevParId, threadScope);
			}

			// If a par(...) exists within the iteration body, then add the last par(...) encountered.
			if (prevParId.compare(lastPrevParId) != 0) {
				Tarot::addLastParIdInIteration(getCoreId(), threadScope, getId(), prevParId);
			}
		}

		void Iteration::flatten(std::vector<Node *> &strongAborts, std::vector<Node *> &weakAborts, std::vector<Node *> &iterations, std::map<std::string, std::vector<Node *> > &selections, const std::string &enclosingParId, const std::string &enclosingThreadScope) {
			// Add iteration scope.
			iterations.push_back(this);

			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->flatten(strongAborts, weakAborts, iterations, selections, enclosingParId, enclosingThreadScope);
			}

			iterations.pop_back();
		}

		const std::string Iteration::getTopNode(void) {
			std::ostringstream output;
			output << getId() << '_' << getInternalId();
			return output.str();
		}
		
		const std::string Iteration::getBottomNode(void) {
			if (!children.empty()) {
				return children.back()->getBottomNode();
			}
			
			return "";
		}

		void Iteration::prettyPrint(std::ostream &output) {
			output << Tab::toString() << "core" << getMasterCoreId() << ": " << getId() << std::endl;
			Tab::indent();
			for (std::vector<Node *>::const_iterator i = children.begin(); i != children.end(); ++i) {
				output << *(*i);
			}
			Tab::dedent();
		}

		void Iteration::toDot(std::ostream &output, std::string &previousNode, std::string &edgeAttributes, const bool toggle, std::ostringstream &abortScope) {
			setInternalId();

			output << Tab::toString() << previousNode << " -> " << getId() << '_' << getInternalId() << edgeAttributes << std::endl;

			output << abortScope.str();
			abortScope.str("");
			
			output << Tab::toString() << "subgraph cluster_" << getId() << '_' << getInternalId() << " {" << std::endl;
			Tab::indent("");
			output << Tab::toString() << "style = invis" << std::endl;
			
			output << Tab::toString() << getId() << '_' << getInternalId() << " [label = " << getIdNumber() << ", shape = diamond]" << std::endl;

			std::ostringstream previousNodeString;
			previousNodeString << getId() << '_' << getInternalId();
			previousNode = previousNodeString.str();
			edgeAttributes = " [label = true]";

			for (std::vector<Node *>::const_iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->toDot(output, previousNode, edgeAttributes, toggle, abortScope);
			}

			output << Tab::toString() << previousNode << " -> " << getId() << '_' << getInternalId() << " [tailport = s, constraint = false]" << std::endl;

			Tab::dedent();
			output << Tab::toString() << '}' << std::endl;

			previousNodeString.str("");
			previousNodeString << getId() << '_' << getInternalId();
			previousNode = previousNodeString.str();
			edgeAttributes = " [label = false]";

			incrementInternalId();
		}
	}
}
