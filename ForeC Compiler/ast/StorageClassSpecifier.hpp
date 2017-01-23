#ifndef FOREC_AST_STORAGE_CLASS_SPECIFIER_HPP
#define FOREC_AST_STORAGE_CLASS_SPECIFIER_HPP

/*
 *  StorageClassSpecifier.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class StorageClassSpecifier : public Node {
			public:				
				StorageClassSpecifier(const std::string &variant = "none");
								
				static int getCount(void);

				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_ROOT_HPP
