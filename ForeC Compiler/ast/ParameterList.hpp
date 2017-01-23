#ifndef FOREC_AST_PARAMETER_LIST_HPP
#define FOREC_AST_PARAMETER_LIST_HPP

/*
 *  ParameterList.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "NodeList.hpp"

namespace forec {
	namespace ast {
		class ParameterList : public NodeList {
			public:				
				ParameterList(Node &node, const std::string &variant = "none");
		
				static int getCount(void);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_PARAMETER_LIST_HPP
