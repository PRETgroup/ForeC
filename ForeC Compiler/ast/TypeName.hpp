#ifndef FOREC_AST_TYPE_NAME_HPP
#define FOREC_AST_TYPE_NAME_HPP

/*
 *  TypeName.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class TypeName : public Node {
			public:				
				TypeName(Node &node, const std::string &variant = "none");
				TypeName(Node &node0, Node &node1, const std::string &variant = "none");
								
				static int getCount(void);

				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_TYPE_NAME_HPP
