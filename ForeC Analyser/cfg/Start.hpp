#ifndef FOREC_CFG_START_HPP
#define FOREC_CFG_START_HPP

/*
 *  Start.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 09/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace cfg {
		class Start : public Node {
			public:				
				Start(const unsigned int programCounter, const std::string &variant = "none");
				
				static const int getCount(void);
				
				const unsigned int getProgramCounter(void);
				
				const int getInstructionLatency(void);
				
				void linkNodes(void);
				void inlineFunctions(void);
		
				void toXml(std::ostream &output);
				void toUppaal(std::ostream &output);
				void toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions);
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				
				const unsigned int programCounter;
		};
	}
}

#endif // FOREC_CFG_START_HPP
