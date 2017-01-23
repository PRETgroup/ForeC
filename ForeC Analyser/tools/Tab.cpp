/*
 *  Tab.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Tab.hpp"

namespace tools {
	int Tab::level = 0;
	std::string Tab::levelString = "";

	void Tab::setLevel(const int level) {
		Tab::level = level;
		
		Tab::levelString = "";
		for (int i = 0; i < Tab::level; i++) {
			Tab::levelString += "\t";
		}
	}
	
	const int Tab::getLevel(void) {
		return Tab::level;
	}
	
	void Tab::indent(void) {
		Tab::level++;
		
		Tab::levelString += "\t";
	}
	
	void Tab::dedent(void) {
		Tab::level--;
		
		Tab::levelString = "";
		for (int i = 0; i < Tab::level; i++) {
			Tab::levelString += "\t";
		}
	}
	
	const std::string Tab::toString(void) {
		return Tab::levelString;
	}

}
