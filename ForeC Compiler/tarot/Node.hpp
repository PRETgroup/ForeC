#ifndef TAROT_NODE_HPP
#define TAROT_NODE_HPP

/*
 *  Node.hpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 12/04/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "Tab.hpp"

namespace forec {
	namespace ast {
		class Node;
	}
}

namespace forec {
	namespace tarot {
		class Node {
			friend std::ostream &operator<<(std::ostream &output, Node &node);

			public:
				Node(const std::string &threadScope, const std::string &type, ast::Node *astNode);
				Node(const Node &original, const std::string &type, const std::string &coreId);

				void incrementInternalId(void);
				void setInternalId(void);
				void setInternalId(const int internalId);
				const int getInternalId(void) const;
				const std::string getId(void) const;
				const std::string getIdNumber(void) const;

				const bool isType(const std::string &type) const;
				const std::string getType(void) const;

				const std::string getThreadScope(void) const;
				void setThreadScope(const std::string &threadScope);
				void setParent(Node *node);

				const std::string getCoreId(void) const;
				const std::string getMasterCoreId(void) const;
				void setCoreId(const std::string &coreId);
				void setMasterCoreId(const std::string &masterCoreId);
				const bool isCoreId(const std::string &coreId) const;
				const bool isMaster(void) const;

				virtual void append(Node &node);
				virtual void prepend(Node &node);

				virtual void linkParThreads(void);
				virtual void setParCore(void);
				virtual void findThreadRecursion(std::set<std::string> &visitedThreadIds) throw(std::string);

				virtual void findNextPar(std::string &prevParId, std::vector<std::string> &prevAbortId, std::vector<std::string> &prevIterationId, std::vector<std::map<std::string, std::string> > &prevSelectionId, const std::string &threadScope);
				virtual void findNextParInReaction(std::string &prevParId, std::vector<std::string> &prevAbortIdInReaction, std::vector<std::string> &prevIterationIdInReaction, std::vector<std::map<std::string, std::string> > &prevSelectionIdInReaction, const std::string &threadScope);
				virtual void findLastPar(std::string &prevParId, const std::string &threadScope);

				virtual void addAborts(std::vector<std::string> &aborts, std::vector<std::pair<std::string, std::string> > &abortsWithPar);

				virtual void extractParInformation(std::vector<Node *> &aborts, const std::string &enclosingParId);
				virtual void flatten(std::vector<Node *> &strongAborts, std::vector<Node *> &weakAborts, std::vector<Node *> &iterations, std::map<std::string, std::vector<Node *> > &selections, const std::string &enclosingParId, const std::string &enclosingThreadScope);

				virtual const bool hasChildren(void);

				virtual const bool hasRecursive(const std::string &type, const std::string &coreId);
				virtual const bool hasCoreIdRecursive(const std::string &coreId);

				virtual std::vector<Node *> find(const std::string &type);
				virtual std::vector<Node *> findAll(const std::string &type);
				
				virtual const std::string getTopNode(void) = 0;
				virtual const std::string getBottomNode(void) = 0;

				virtual void prettyPrint(std::ostream &output) = 0;
				virtual void toDot(std::ostream &output, std::string &previousNode, std::string &edgeAttributes, const bool toggle, std::ostringstream &abortScope) = 0;
				virtual void toXml(std::ostream &output, const std::string &indent);
				virtual const std::string toString(void);
				

			protected:
				static int count;
				
				int id;						// Ensure all copies of a single node have a unique number.
				std::string type;
				std::string coreId;
				std::string masterCoreId;
				std::string threadScope;

				ast::Node *astNode;
				Node *parent;
				std::vector<Node *> children;
		};
	}
}

#endif // TAROT_NODE_HPP
