#ifndef FOREC_AST_INITIALIZER_HPP
#define FOREC_AST_INITIALIZER_HPP

/*
 *  Initializer.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class Initializer : public Node {
			public:				
				Initializer(Node &node, const std::string &variant = "none");

				static int getCount(void);
				
				void updateSymbolTable(const std::string &type = "none", const bool isUsage = false, const bool isRead = false);
				
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_INITIALIZER_HPP
