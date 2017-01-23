#ifndef FOREC_AST_DECLARATOR_HPP
#define FOREC_AST_DECLARATOR_HPP

/*
 *  Declarator.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class Declarator : public Node {
			public:				
				Declarator(Node &node0, Node &node1, const std::string &variant = "none");
								
				static int getCount(void);

				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_DECLARATOR_HPP
