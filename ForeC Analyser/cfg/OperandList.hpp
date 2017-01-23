#ifndef FOREC_CFG_OPERAND_LIST_HPP
#define FOREC_CFG_OPERAND_LIST_HPP

/*
 *  OperandList.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 08/120/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "NodeList.hpp"

namespace forec {
	namespace cfg {
		class OperandList : public NodeList {
			public:				
				OperandList(Node &node, const std::string &variant = "none");
				
				static int getCount(void);

				std::vector<Node *> getOperands(void);
				
				void inlineFunctions(void);
				
				void toXml(std::ostream &output);
				void toUppaal(std::ostream &output);
				void toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions);

			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_CFG_OPERAND_LIST_HPP
