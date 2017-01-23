#ifndef FOREC_AST_ENUMERATOR_LIST_HPP
#define FOREC_AST_ENUMERATOR_LIST_HPP

/*
 *  EnumeratorList.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "NodeList.hpp"

namespace forec {
	namespace ast {
		class EnumeratorList : public NodeList {
			public:				
				EnumeratorList(Node &node, const std::string &variant = "none");
				
				static int getCount(void);
							
				void prettyPrint(std::ostream &output);
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_ENUMERATOR_LIST_HPP
