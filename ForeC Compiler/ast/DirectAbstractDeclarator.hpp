#ifndef FOREC_AST_DIRECT_ABSTRACT_DECLARATOR_HPP
#define FOREC_AST_DIRECT_ABSTRACT_DECLARATOR_HPP

/*
 *  DirectAbstractDeclarator.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class DirectAbstractDeclarator : public Node {
			public:				
				DirectAbstractDeclarator(const std::string &variant = "none");
				DirectAbstractDeclarator(Node &node, const std::string &variant = "none");
				DirectAbstractDeclarator(Node &node0, Node &node1, const std::string &variant = "none");
	
				static int getCount(void);

				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_DIRECT_ABSTRACT_DECLARATOR_HPP
