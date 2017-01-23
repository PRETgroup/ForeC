#ifndef TOOLS_UPPAAL_HPP
#define TOOLS_UPPAAL_HPP
/*
 *  Uppaal.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 13/10/12.
 *  Copyright 2012 Potential Publishers. All rights reserved.
 *
 */

#include <string>

namespace tools {
	class Uppaal {
		public:
			static void clear(void);

			static void enterThreadScope(const std::string &threadScope);
			static void leaveThreadScope(const std::string &threadScope);
			static const std::string getThreadScope(void);

		private:
			static std::string threadScope;

	};

}

#endif // TOOLS_UPPAAL_HPP
