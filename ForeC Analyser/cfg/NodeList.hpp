#ifndef FOREC_CFG_NODE_LIST_HPP
#define FOREC_CFG_NODE_LIST_HPP

/*
 *  NodeList.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 08/10/10.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace cfg {
		class NodeList : public Node {
			public:			
				NodeList(Node &node, const std::string &type, const std::string &variant, const int id);
				
				virtual void toXml(std::ostream &output);
				virtual void toUppaal(std::ostream &output);
				virtual void toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions);
				virtual void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_CFG_NODE_LIST_HPP
