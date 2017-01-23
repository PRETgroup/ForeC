#ifndef FOREC_CFG_NODE_HPP
#define FOREC_CFG_NODE_HPP

/*
 *  Node.hpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 04/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>

#include "../tools/Tab.hpp"
#include "../tools/Link.hpp"

namespace forec {
	namespace cfg {
		class Node {
			friend std::ostream &operator<<(std::ostream &output, Node &node);

			public:
				Node(const std::string &type, const std::string &variant, const int id);

				const std::string getId(void) const;
				const std::string getIdNumber(void) const;

				const bool isType(const std::string &type) const;
				const std::string getType(void) const;

				const bool isVariant(const std::string &variant) const;
				const std::string getVariant(void) const;
				void setVariant(const std::string &variant);

				void setParent(Node *node);
				Node *getParent(void);

				static int getGlobalCount(void);

				virtual void append(Node &node);
				virtual void prepend(Node &node);

				virtual Node *getFirstChildNode(void);

				virtual void linkNodes(void);
				virtual void addPreviousNode(Node &previousNode);
				virtual void removePreviousNode(Node &previousNode);
				virtual void addNextNode(Node &nextNode, const int latency, const bool needAlignment = true);
				virtual void removeNextNode(Node &previousNode);
				virtual void removeAllNextNodes(void);
				virtual void removeAllPreviousNodes(void);
				virtual std::vector<Node *> getPreviousNodes(void);
				virtual std::vector<std::pair<Node *, std::pair<int, bool> > > getNextNodes(void);
				virtual void resolveDestinations(void);

				virtual void setIterationBound(Node &iterationBound);
				virtual Node *getIterationBound(void);
				virtual const bool hasIterationBound(void);

				virtual const int mergeNodes(const bool mergeGlobalAccesses);
				virtual void removeUnreachableNodes(void);
				virtual void mergeBranches(void);
				
				virtual void inlineFunctions(void);
				
				virtual const bool has(const std::string &type, const std::string &variant);
				virtual std::vector<Node *> find(const std::string &type, const std::string &variant);
				virtual std::vector<Node *> findAll(const std::string &type, const std::string &variant);
				virtual Node *findFirst(const std::string &type, const std::string &variant);
				virtual Node *findFirstChildNot(const std::string &type, const std::string &variant);
				
				virtual void toXml(std::ostream &output) = 0;
				virtual void toUppaal(std::ostream &output) = 0;
				virtual void toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) = 0;
				virtual void prettyPrint(std::ostream &output) = 0;
				virtual std::string *toString(void);


			protected:
				static int globalCount;
				
				const int id;
				const std::string type;
				std::string variant;
				Node *parent;
				Node *iterationBound;
				std::vector<Node *> children;

				std::vector<Node *> previousNodes;
				
				//vector<pair<link, pair<latency, needBusAlignment> > >
				std::vector<std::pair<Node *, std::pair<int, bool> > > nextNodes;

		};
	}
}

#endif // FOREC_CFG_NODE_HPP
