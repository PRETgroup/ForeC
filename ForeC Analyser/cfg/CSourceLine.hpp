#ifndef FOREC_CFG_C_SOURCE_LINE_HPP
#define FOREC_CFG_C_SOURCE_LINE_HPP

/*
 *  CSourceLine.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 09/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace cfg {
		class CSourceLine : public Node {
			public:	
				CSourceLine(const CSourceLine &original);
				CSourceLine(const std::string &variant = "none");
				CSourceLine(std::string &source, const std::string &variant = "none");
							
				static const int getCount(void);
				
				void inlineFunctions(void);
				
				void toXml(std::ostream &output);
				void toUppaal(std::ostream &output);
				void toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions);
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				
				std::string source;
		};
	}
}

#endif // FOREC_CFG_C_SOURCE_LINE_HPP
