#ifndef TAROT_SELECTION_HPP
#define TAROT_SELECTION_HPP

/*
 *  Selection.hpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 12/04/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace tarot {
		class Selection : public Node {
			public:
				Selection(const std::string &threadScope, const std::string &branchType, ast::Node *astNode);
				Selection(const Selection &original, const std::string &type, const std::string &coreId);

				void setIfBranch(Selection &selectionIfTarot);
				
				const std::string getId(void) const;
				const std::string getIdNumber(void) const;
				const std::string getBranchType(void) const;
				const bool isBranchType(const std::string &branchType) const;

				void findNextPar(std::string &prevParId, std::vector<std::string> &prevAbortId, std::vector<std::string> &prevIterationId, std::vector<std::map<std::string, std::string> > &prevSelectionId, const std::string &threadScope);
				void findNextParInReaction(std::string &prevParId, std::vector<std::string> &prevAbortIdInReaction, std::vector<std::string> &prevIterationIdInReaction, std::vector<std::map<std::string, std::string> > &prevSelectionIdInReaction, const std::string &threadScope);
				void findLastPar(std::string &prevParId, const std::string &threadScope);

				void flatten(std::vector<Node *> &strongAborts, std::vector<Node *> &weakAborts, std::vector<Node *> &iterations, std::map<std::string, std::vector<Node *> > &selections, const std::string &enclosingParId, const std::string &enclosingThreadScope);

				const std::string getTopNode(void);
				const std::string getBottomNode(void);

				void prettyPrint(std::ostream &output);
				void toDot(std::ostream &output, std::string &previousNode, std::string &edgeAttributes, const bool toggle, std::ostringstream &abortScope);

			private:
				const std::string branchType;
				Selection *selectionIfTarot;
		};
	}
}

#endif // TAROT_SELECTION_HPP
