/*
 *  Function.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 3/03/13.
 *  Copyright 2013 Potential Publishers. All rights reserved.
 *
 */

#include "Function.hpp"

#include "../ast/FunctionDefinition.hpp"

namespace tools {
	std::set<std::pair<std::string, forec::ast::FunctionDefinition *> > Function::declarations;

	void Function::addDeclaration(std::string &identifier, forec::ast::FunctionDefinition &function) {
		Function::declarations.insert(std::make_pair(identifier, &function));
	}
	
	forec::ast::FunctionDefinition *Function::getDeclaration(const std::string &identifier) {
		for (std::set<std::pair<std::string, forec::ast::FunctionDefinition *> >::const_iterator declaration = Function::declarations.begin(); declaration != Function::declarations.end(); ++declaration) {
			if (declaration->first.compare(identifier) == 0) {
				return declaration->second;
			}
		}
	
		throw std::string("Function::getDeclaration: Could not find function \"" + identifier + "\".");
	}
	
}
