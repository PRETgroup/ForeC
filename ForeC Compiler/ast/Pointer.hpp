#ifndef FOREC_AST_POINTER_HPP
#define FOREC_AST_POINTER_HPP

/*
 *  Pointer.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class Pointer : public Node {
			public:				
				Pointer(const std::string &variant = "none");
				Pointer(Node &node, const std::string &variant = "none");
				Pointer(Node &node0, Node &node1, const std::string &variant = "none");

				static int getCount(void);
			
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_POINTER_HPP
