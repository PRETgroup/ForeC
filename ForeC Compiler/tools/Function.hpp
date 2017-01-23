#ifndef TOOLS_FUNCTION_HPP
#define TOOLS_FUNCTION_HPP
/*
 *  Function.hpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 3/03/13.
 *  Copyright 2013 Potential Publishers. All rights reserved.
 *
 */

#include <string>
#include <set>

namespace forec {
	namespace ast {
		class FunctionDefinition;
	}
}

namespace tools {
	class Function {
	public:
		static void addDeclaration(std::string &identifier, forec::ast::FunctionDefinition &function);
		static forec::ast::FunctionDefinition *getDeclaration(const std::string &identifier);
		
	private:
		// set<pair<functionId,function>
		static std::set<std::pair<std::string, forec::ast::FunctionDefinition *> > declarations;
	};
	
}

#endif // TOOLS_FUNCTION_HPP
