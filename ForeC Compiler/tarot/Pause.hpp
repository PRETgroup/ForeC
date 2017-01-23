#ifndef TAROT_PAUSE_HPP
#define TAROT_PAUSE_HPP

/*
 *  Pause.hpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 12/04/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace tarot {
		class Pause : public Node {
			public:
				Pause(const std::string &threadScope, ast::Node *astNode);
				Pause(const Pause &original, const std::string &type, const std::string &coreId);

				const std::string getId(void) const;

				void findNextPar(std::string &prevParId, std::vector<std::string> &prevAbortId, std::vector<std::string> &prevIterationId, std::vector<std::map<std::string, std::string> > &prevSelectionId, const std::string &threadScope);
				void findNextParInReaction(std::string &prevParId, std::vector<std::string> &prevAbortIdInReaction, std::vector<std::string> &prevIterationIdInReaction, std::vector<std::map<std::string, std::string> > &prevSelectionIdInReaction, const std::string &threadScope);

				const std::string getTopNode(void);
				const std::string getBottomNode(void);

				void prettyPrint(std::ostream &output);
				void toDot(std::ostream &output, std::string &previousNode, std::string &edgeAttributes, const bool toggle, std::ostringstream &abortScope);
		};
	}
}

#endif // TAROT_PAUSE_HPP
