#ifndef FOREC_CFG_PAUSE_STATEMENT_HPP
#define FOREC_CFG_PAUSE_STATEMENT_HPP

/*
 *  PauseStatement.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 11/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace cfg {
		class PauseStatement : public Node {
			public:	
				PauseStatement(const std::string &information, Node &node, const std::string &variant = "none");
							
				static const int getCount(void);
				const unsigned int getProgramCounter(void);
				const int getLatency(void);
				
				void linkNodes(void);
				void resolveDestinations(void);
				
				void inlineFunctions(void);
				
				void toXml(std::ostream &output);
				void toUppaal(std::ostream &output);
				void toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions);
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				
				std::string id;
		};
	}
}

#endif // FOREC_CFG_PAUSE_STATEMENT_HPP
