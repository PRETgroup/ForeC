/*
 *  Pause.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 12/04/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Pause.hpp"

#include "Tarot.hpp"

#include "../ast/PauseStatement.hpp"

namespace forec {
	namespace tarot {
		Pause::Pause(const std::string &threadScope, ast::Node *astNode) : Node(threadScope, "Pause", astNode) {

		}

		Pause::Pause(const Pause &original, const std::string &type, const std::string &coreId) : Node(original, type, coreId) {

		}

		const std::string Pause::getId(void) const {
			return ((ast::PauseStatement *)astNode)->getId();
		}

		void Pause::findNextPar(std::string &prevParId, std::vector<std::string> &prevAbortId, std::vector<std::string> &prevIterationId, std::vector<std::map<std::string, std::string> > &prevSelectionId, const std::string &threadScope) {
			// Add the previously encountered par(...).
			Tarot::addLastParInReaction(getCoreId(), threadScope, prevParId);
		}

		void Pause::findNextParInReaction(std::string &prevParId, std::vector<std::string> &prevAbortIdInReaction, std::vector<std::string> &prevIterationIdInReaction, std::vector<std::map<std::string, std::string> > &prevSelectionIdInReaction, const std::string &threadScope) {
			// Clear all records of past abort, iteration and selection scopes.
			prevAbortIdInReaction.clear();
			prevIterationIdInReaction.clear();
			prevSelectionIdInReaction.clear();
		}

		const std::string Pause::getTopNode(void) {
			std::ostringstream output;
			output << getId() << '_' << getInternalId();
			return output.str();
		}
		
		const std::string Pause::getBottomNode(void) {
			std::ostringstream output;
			output << getId() << '_' << getInternalId();
			return output.str();
		}


		void Pause::prettyPrint(std::ostream &output) {
			output << Tab::toString() << getId() << std::endl;
		}

		void Pause::toDot(std::ostream &output, std::string &previousNode, std::string &edgeAttributes, const bool toggle, std::ostringstream &abortScope) {
			setInternalId();

			output << Tab::toString() << previousNode << " -> " << getId() << '_' << getInternalId() << edgeAttributes << std::endl;

			output << abortScope.str();
			abortScope.str("");

			output << Tab::toString() << getId() << '_' << getInternalId() << " [label = \"\", shape = box, height = 0.4, style = filled, fillcolor = black]" << std::endl;

			std::ostringstream previousNodeString;
			previousNodeString << getId() << '_' << getInternalId();
			previousNode = previousNodeString.str();
			edgeAttributes = " [headport = n, tailport = s]";

			incrementInternalId();
		}
	}
}
