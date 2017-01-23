#ifndef FOREC_AST_INITIALIZER_LIST_HPP
#define FOREC_AST_INITIALIZER_LIST_HPP

/*
 *  InitializerList.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class InitializerList : public Node {
			public:				
				InitializerList(Node &node0, Node &node1, const std::string &variant = "none");
				InitializerList(Node &node0, Node &node1, Node &node2, const std::string &variant = "none");

				static int getCount(void);
				
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_INITIALIZER_LIST_HPP
