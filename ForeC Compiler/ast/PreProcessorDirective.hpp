#ifndef FOREC_AST_PREPROCESSOR_DIRECTIVE_HPP
#define FOREC_AST_PREPROCESSOR_DIRECTIVE_HPP

/*
 *  PreProcessorDirective.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class PreProcessorDirective : public Node {
			public:				
				PreProcessorDirective(const std::string &directive, const std::string &variant = "none");

				static int getCount(void);
								
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				const std::string directive;
		};
	}
}

#endif // FOREC_AST_PREPROCESSOR_DIRECTIVE_HPP
