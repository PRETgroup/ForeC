#ifndef TOOLS_TAB_HPP
#define TOOLS_TAB_HPP
/*
 *  Tab.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <string>

namespace tools {
	class Tab {
		public:
			static void setLevel(const int level);
			static const int getLevel(void);
			
			static void indent(void);
			static void dedent(void);
			
			static const std::string toString(void);
			
		private:
			static int level;
			static std::string levelString;
	};

}

#endif // TOOLS_TAB_HPP
