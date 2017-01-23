#ifndef FOREC_CFG_LABEL_HPP
#define FOREC_CFG_LABEL_HPP

/*
 *  Label.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 09/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace cfg {
		class Label : public Node {
			public:				
				Label(const std::string &address, const std::string &label, const std::string &variant = "none");
				
				static const int getCount(void);

				const std::string getId(void);
				const int getLatency(void);
				const std::string getAddress(void);
				
				void linkNodes(void);
				
				void inlineFunctions(void);
							
				void toXml(std::ostream &output);
				void toUppaal(std::ostream &output);
				void toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions);
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				
				const std::string address;
				const std::string label;
		};
	}
}

#endif // FOREC_CFG_LABEL_HPP
