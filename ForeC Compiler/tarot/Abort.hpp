#ifndef TAROT_ABORT_HPP
#define TAROT_ABORT_HPP

/*
 *  Abort.hpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 12/04/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace tarot {
		class Abort : public Node {
			public:
				Abort(const std::string &threadScope, ast::Node *astNode);
				Abort(const Abort &original, const std::string &type, const std::string &coreId);

				const std::string getId(void) const;
				const std::string getCondition(void) const;
				const bool isVariant(const std::string &variant) const;

				void findNextPar(std::string &prevParId, std::vector<std::string> &prevAbortId, std::vector<std::string> &prevIterationId, std::vector<std::map<std::string, std::string> > &prevSelectionId, const std::string &enclosingThreadScope);
				void findNextParInReaction(std::string &prevParId, std::vector<std::string> &prevAbortIdInReaction, std::vector<std::string> &prevIterationIdInReaction, std::vector<std::map<std::string, std::string> > &prevSelectionIdInReaction, const std::string &enclosingThreadScope);
				void findLastPar(std::string &prevParId, const std::string &threadScope);

				void addAborts(std::vector<std::string> &aborts, std::vector<std::pair<std::string, std::string> > &abortsWithPar);

				void extractParInformation(std::vector<Node *> &aborts, const std::string &enclosingParId);
				void flatten(std::vector<Node *> &strongAborts, std::vector<Node *> &weakAborts, std::vector<Node *> &iterations, std::map<std::string, std::vector<Node *> > &selections, const std::string &enclosingParId, const std::string &enclosingThreadScope);

				const std::string getTopNode(void);
				const std::string getBottomNode(void);
			
				void prettyPrint(std::ostream &output);
				void toDot(std::ostream &output, std::string &previousNode, std::string &edgeAttributes, const bool toggle, std::ostringstream &abortScope);
		};
	}
}

#endif // TAROT_ABORT_HPP
