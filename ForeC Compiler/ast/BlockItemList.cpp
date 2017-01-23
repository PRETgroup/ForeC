/*
 *  BlockItemList.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "BlockItemList.hpp"

namespace forec {
	namespace ast {

		// Initialise static variable
		int BlockItemList::globalCount = 0;

		BlockItemList::BlockItemList(Node &node, const std::string &variant) : NodeList(node, "BlockItemList", variant, this->globalCount++) {
			node.setParent((Node *)this);
		}
		
		int BlockItemList::getCount(void) {
			return globalCount;
		}
		
		const std::string BlockItemList::getSpacing(Node &node) {
			if (node.has("StructUnionSpecifier", "definition") || node.has("StructUnionSpecifier", "anonymous") || node.has("EnumSpecifier", "none") || node.has("FunctionDefinition", "none") || node.has("ThreadDefinition", "none")) {
				return "separateStorages";
			} else if (node.has("PauseStatement", "none")) {
				return "separatePauses";
			} else if (node.has("ParStatement", "none")) {
				return "separateParStatements";
			} else if (node.has("CompoundStatement", "none")) {
				return "separateCompounds";
			}
			
			return "groupOthers";
		}

		const Node::Instantaneous BlockItemList::willPause(const bool requireBothBranches) {
			// Get all case statements.
			instantaneous.pauses = true;
			instantaneous.breaks = false;
			instantaneous.continues = false;
			instantaneous.returns = false;
			
			bool noCaseStatements = true;
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				if ((*i)->isType("LabeledStatements") && !(*i)->isVariant("label")) {
					const Node::Instantaneous result = (*i)->willPause(requireBothBranches);
				
					instantaneous.pauses = instantaneous.pauses && result.pauses;
					
					if (requireBothBranches) {
						instantaneous.breaks = instantaneous.breaks && result.breaks;
						instantaneous.continues = instantaneous.continues && result.continues;
						instantaneous.returns = instantaneous.returns && result.returns;
					} else {
						instantaneous.breaks = instantaneous.breaks || result.breaks;
						instantaneous.continues = instantaneous.continues || result.continues;
						instantaneous.returns = instantaneous.returns || result.returns;
					}
				
					noCaseStatements = false;
				}				
			}

			if (noCaseStatements) {
				instantaneous.pauses = false;
				instantaneous.breaks = false;
				instantaneous.continues = false;
				instantaneous.returns = false;
				
				for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
					const Node::Instantaneous result = (*i)->willPause(requireBothBranches);
				
					if (!instantaneous.breaks && !instantaneous.continues && !instantaneous.returns) {
						instantaneous.pauses = instantaneous.pauses || result.pauses;
						instantaneous.breaks = instantaneous.breaks || result.breaks;
						instantaneous.continues = instantaneous.continues || result.continues;
						instantaneous.returns = instantaneous.returns || result.returns;
					}
				}
			}
			
			return instantaneous;
		}
		
		void BlockItemList::prettyPrint(std::ostream &output) {
			if (children.size() > 0) {	
				if (children.size() > 1) {
					std::string lastSpacing = getSpacing(*children[0]);
					output << tools::Tab::toString() << *children[0] << std::endl;
					
					for (std::vector<Node *>::iterator i = children.begin() + 1; i != children.end() - 1; ++i) {
						std::string currentSpacing = getSpacing(*(*i));
						if (currentSpacing.find("separate") != std::string::npos || (currentSpacing.find("group") != std::string::npos && currentSpacing.compare(lastSpacing) != 0)) {
							output << std::endl;
						}
					
						output << tools::Tab::toString() << *(*i) << std::endl;
						
						lastSpacing = currentSpacing;
					}
					
					std::string currentSpacing = getSpacing(*children.back());
					if (currentSpacing.find("separate") != std::string::npos || (currentSpacing.find("group") != std::string::npos && currentSpacing.compare(lastSpacing) != 0)) {
						output << std::endl;
					}
				}

				output << tools::Tab::toString() << *children.back();
			}
		}

	}
}
