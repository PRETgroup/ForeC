/*
 *  NodeList.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 08/10/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "NodeList.hpp"

namespace forec {
	namespace cfg {

		// Initialise static variable
		int NodeList::globalCount = 0;

		NodeList::NodeList(Node &node, const std::string &type, const std::string &variant, const int id) : Node(type, variant, this->globalCount) {
			children.push_back(&node);

			node.setParent((Node *)this);
		}

		void NodeList::toXml(std::ostream &output) {
			output << "<list>" << std::endl;
			tools::Tab::indent();
			
			for (std::vector<Node *>::iterator i = children.begin(); i != children.end(); ++i) {
				(*i)->toXml(output);
			}
				
			tools::Tab::dedent();
			output << "</list>" << std::endl;
		}

		void NodeList::toUppaal(std::ostream &output) {
			// Nothing.
		}
		
		void NodeList::toUppaal(int &x, int &y, std::ostream &locations, std::ostream &transitions) {
			// Nothing.
		}

		void NodeList::prettyPrint(std::ostream &output) {
			output << *children[0];
			
			if (children.size() > 1) {
				for (std::vector<Node *>::iterator i = children.begin() + 1; i != children.end(); ++i) {
					output << ", " << *(*i);
				}
			}
		}

	}
}
