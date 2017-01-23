#ifndef FOREC_AST_TYPE_QUALIFIER_HPP
#define FOREC_AST_TYPE_QUALIFIER_HPP

/*
 *  TypeQualifier.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class TypeQualifier : public Node {
			public:				
				TypeQualifier(const std::string &variant = "none");
								
				static int getCount(void);

				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_TYPE_QUALIFIER_HPP
