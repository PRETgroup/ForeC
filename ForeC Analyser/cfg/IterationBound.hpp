#ifndef FOREC_CFG_ITERATION_BOUND_HPP
#define FOREC_CFG_ITERATION_BOUND_HPP

/*
 *  IterationBound.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 14/05/12.
 *  Copyright 2012 Potential Publishers. All rights reserved.
 *
 */

#include "Node.hpp"

namespace forec {
	namespace cfg {
		class IterationBound : public Node {
			public:				
				IterationBound(const std::string &information, const std::string &variant = "none");
							
				static const int getCount(void);
				const std::string getIdentifier(void) const;
				const int getLowerBound(void) const;
				const int getUpperBound(void) const;
				
				void linkNodes(void);
				
				void inlineFunctions(void);

				void toXml(std::ostream &output);
				void toUppaal(std::ostream &output);
				void toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions);
				void prettyPrint(std::ostream &output);
				
				
			protected:
				static int globalCount;
				
				std::string identifier;
				int lowerBound;
				int upperBound;
		};
	}
}

#endif // FOREC_CFG_ITERATION_BOUND_HPP
