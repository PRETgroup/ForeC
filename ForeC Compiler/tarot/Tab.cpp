/*
 *  Tab.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 14/04/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Tab.hpp"

namespace forec {
	namespace tarot {
		std::vector<std::string> Tab::indents;

		void Tab::setLevel(const int level) {
			Tab::indents.clear();
			
			for (int i = 0; i < level; i++) {
				Tab::indents.push_back("\t");
			}
		}
		
		const int Tab::getLevel(void) {
			return Tab::indents.size();
		}
		
		void Tab::indent(const std::string &delimiter) {
			Tab::indents.push_back(delimiter + "\t");
		}
		
		void Tab::dedent(void) {
			Tab::indents.pop_back();
		}
		
		const std::string Tab::toString(void) {
			std::string indentString = "";
			for (std::vector<std::string>::const_iterator i = Tab::indents.begin(); i != Tab::indents.end(); ++i) {
				indentString += *i;
			}
			
			return indentString;
		}
	}

}
