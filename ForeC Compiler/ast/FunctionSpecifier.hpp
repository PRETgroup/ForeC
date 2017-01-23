#ifndef FOREC_AST_FUNCTION_SPECIFIER_HPP
#define FOREC_AST_FUNCTION_SPECIFIER_HPP

/*
 *  FunctionSpecifier.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class FunctionSpecifier : public Node {
			public:				
				FunctionSpecifier(const std::string &variant = "none");
								
				static int getCount(void);

				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_FUNCTION_SPECIFIER_HPP
