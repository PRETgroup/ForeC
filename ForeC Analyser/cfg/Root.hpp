#ifndef FOREC_CFG_ROOT_HPP
#define FOREC_CFG_ROOT_HPP

/*
 *  Root.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 04/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace cfg {
		class Root : public Node {
			public:				
				Root(const std::string &variant = "none");
				
				void append(Node &node);
				void addLastFunction(void);
		
				static const int getCount(void);
				
				const int mergeNodes(const bool mergeGlobalAccesses);
				const int mergeNodes(const bool mergeGlobalAccesses, std::map<std::string, int> &results);
				
				void toXml(std::ostream &output);
				void toUppaal(std::ostream &output);
				void toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions);
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				
				std::string lastLabel;
				std::vector<Node *> functionNodes;
		};
	}
}

#endif // FOREC_CFG_ROOT_HPP
