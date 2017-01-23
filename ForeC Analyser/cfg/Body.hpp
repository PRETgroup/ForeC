#ifndef FOREC_CFG_BODY_HPP
#define FOREC_CFG_BODY_HPP

/*
 *  Body.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 08/120/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "NodeList.hpp"

namespace forec {
	namespace cfg {
		class AssemblyLine;
	}
}

namespace forec {
	namespace cfg {
		class Body : public NodeList {
			public:				
				Body(Node &node, const std::string &variant = "none");
				
				static int getCount(void);

				void append(Node &node);

				void inlineFunctions(void);
				void removeUnreachableNodes(void);
				void mergeBranches(void);

				void toXml(std::ostream &output);
				void toUppaal(std::ostream &output);
				void toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions);
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				
			private:
				int globalMemoryMatch;
		};
	}
}

#endif // FOREC_CFG_BODY_HPP
