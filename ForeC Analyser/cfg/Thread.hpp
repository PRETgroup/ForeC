#ifndef FOREC_CFG_THREAD_HPP
#define FOREC_CFG_THREAD_HPP

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
		class Thread : public Node {
			public:				
				Thread(const std::string &information, Node &node, const std::string &variant = "none");
							
				static const int getCount(void);
				const std::string getIdentifier(void);
				const unsigned int getProgramCounter(void);

				void linkNodes(void);
				const int mergeNodes(const bool mergeGlobalAccesses);
				void mergeBranches(void);
				
				void toXml(std::ostream &output);
				void toUppaal(std::ostream &output);
				void toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions);
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				
				std::string identifier;
		};
	}
}

#endif // FOREC_CFG_THREAD_HPP
