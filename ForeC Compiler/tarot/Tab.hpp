#ifndef TAROT_TAB_HPP
#define TAROT_TAB_HPP
/*
 *  Tab.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <string>
#include <vector>

namespace forec {
	namespace tarot {
		class Tab {
			public:
				static void setLevel(const int level);
				static const int getLevel(void);
				
				static void indent(const std::string &delimiter = ".");
				static void dedent(void);
				
				static const std::string toString(void);
				
			private:				
				// vector<indent>
				static std::vector<std::string> indents;
		};
	}
}

#endif // TOOLS_TAB_HPP
