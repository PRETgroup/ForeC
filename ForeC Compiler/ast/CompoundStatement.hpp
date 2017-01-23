#ifndef FOREC_AST_COMPOUND_STATEMENT_HPP
#define FOREC_AST_COMPOUND_STATEMENT_HPP

/*
 *  CompoundStatement.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class CompoundStatement : public Node {
			public:				
				CompoundStatement(const std::string &variant = "none");
				CompoundStatement(Node &node, const std::string &variant = "none");

				void setIsInsideSwitchStatement(const bool isInsideSwitchStatement);
				const bool getIsInsideSwitchStatement(void) const;
				
				static int getCount(void);

				void updateSymbolTable(const std::string &type = "none", const bool isUsage = false, const bool isRead = false);
								
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				bool isInsideSwitchStatement;
		};
	}
}

#endif // FOREC_AST_COMPOUND_STATEMENT_HPP
