/*
 *  Uppaal.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 13/10/12.
 *  Copyright 2012 Potential Publishers. All rights reserved.
 *
 */

#include "Uppaal.hpp"

namespace tools {
	std::string Uppaal::threadScope;
			
	void Uppaal::clear(void) {
		Uppaal::threadScope.clear();
	}

	void Uppaal::enterThreadScope(const std::string &threadScope) {
		Uppaal::threadScope = threadScope;
	}
	
	void Uppaal::leaveThreadScope(const std::string &threadScope) {
		Uppaal::threadScope.clear();
	}
	
	const std::string Uppaal::getThreadScope(void) {
		return Uppaal::threadScope;
	}
}

