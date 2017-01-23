#ifndef FOREC_AST_SPECIFIER_QUALIFIER_LIST_HPP
#define FOREC_AST_SPECIFIER_QUALIFIER_LIST_HPP

/*
 *  SpecifierQualifierList.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "NodeList.hpp"

namespace forec {
	namespace ast {
		class SpecifierQualifierList : public NodeList {
			public:				
				SpecifierQualifierList(Node &node, const std::string &variant = "none");

				static int getCount(void);
				
				void prettyPrint(std::ostream &output);

				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_SPECIFIER_QUALIFIER_LIST_HPP
