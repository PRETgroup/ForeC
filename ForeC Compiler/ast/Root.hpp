#ifndef FOREC_AST_ROOT_HPP
#define FOREC_AST_ROOT_HPP

/*
 *  Root.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace ast {
		class PrimaryExpression;
	}
}
namespace forec {
	namespace ast {
		class Root : public Node {
			public:				
				Root(const std::string &variant = "none");
				
				void append(Node &node);
		
				static const int getCount(void);
				const std::string getSpacing(Node &node);
				
				std::map<PrimaryExpression *, std::map<std::string, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > > pullUpIndirectParallelVariables(void);
				void pullDownIndirectParallelVariables(std::set<PrimaryExpression *> &definedVariables);

				const Node::Instantaneous willPause(const bool requireBothBranches);

				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
		};
	}
}

#endif // FOREC_AST_ROOT_HPP
