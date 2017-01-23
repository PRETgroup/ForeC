#ifndef FOREC_CFG_ABORT_STATEMENT_HPP
#define FOREC_CFG_ABORT_STATEMENT_HPP

/*
 *  AbortStatement.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 11/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace cfg {
		class AbortStatement : public Node {
			public:				
				AbortStatement(const std::string &information, const std::string &variant = "none");
				AbortStatement(const std::string &information, Node &node, const std::string &variant = "none");
				void initialise(const std::string &information);

				static const int getCount(void);				
				const std::string getIdentifier(void);
				const int getIdNumber(void);
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
				
				int idNumber;
				std::string strength;
				std::string idString;
				
		};
	}
}

#endif // FOREC_CFG_ABORT_STATEMENT_HPP
