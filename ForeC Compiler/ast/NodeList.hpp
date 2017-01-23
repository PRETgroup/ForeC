#ifndef FOREC_AST_NODE_LIST_HPP
#define FOREC_AST_NODE_LIST_HPP

/*
 *  NodeList.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class NodeList : public Node {
			public:			
				NodeList(Node &node, const std::string &type, const std::string &variant, const int id);
								
				virtual void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_NODE_LIST_HPP
