#ifndef FOREC_AST_STRUCT_UNION_SPECIFIER_HPP
#define FOREC_AST_STRUCT_UNION_SPECIFIER_HPP

/*
 *  StructUnionSpecifier.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class StructUnionSpecifier : public Node {
			public:				
				StructUnionSpecifier(const std::string &structUnion, Node &node, const std::string &variant = "none");
				StructUnionSpecifier(const std::string &structUnion, Node &node0, Node &node1, const std::string &variant = "none");

				static int getCount(void);
				
				void updateSymbolTable(const std::string &type = "none", const bool isUsage = false, const bool isRead = false);

				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				const std::string structUnion;
		};
	}
}

#endif // FOREC_AST_STRUCT_UNION_SPECIFIER_HPP
