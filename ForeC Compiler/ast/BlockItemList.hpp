#ifndef FOREC_AST_BLOCK_ITEM_LIST_HPP
#define FOREC_AST_BLOCK_ITEM_LIST_HPP

/*
 *  BlockItemList.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "NodeList.hpp"

namespace forec {
	namespace ast {
		class BlockItemList : public NodeList {
			public:				
				BlockItemList(Node &node, const std::string &variant = "none");
		
				static int getCount(void);
				const std::string getSpacing(Node &node);
				
				const Node::Instantaneous willPause(const bool requireBothBranches);
				
				void prettyPrint(std::ostream &output);
			
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_BLOCK_ITEM_LIST_HPP
