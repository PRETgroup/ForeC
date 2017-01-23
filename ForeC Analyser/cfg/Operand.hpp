#ifndef FOREC_CFG_OPERAND_HPP
#define FOREC_CFG_OPERAND_HPP

/*
 *  Operand.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 08/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace cfg {
		class Operand : public Node {
			public:				
				Operand(const std::string &value, const std::string &variant = "none");
				Operand(const Node &operand, const std::string &variant = "none");
				Operand(const Node &operand1, const Node &operand2, const std::string &variant = "none");
							
				static const int getCount(void);
				
				const std::string getValue(void);
				
				void toXml(std::ostream &output);
				void toUppaal(std::ostream &output);
				void toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions);
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				
				const std::string value;
				const Node *operand1;
				const Node *operand2;
		};
	}
}

#endif // FOREC_CFG_OPERAND_HPP
