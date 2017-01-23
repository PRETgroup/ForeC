#ifndef TOOLS_QUERY_HPP
#define TOOLS_QUERY_HPP
/*
 *  Query.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <sstream>
#include <string>
#include <vector>

namespace forec {
	namespace ast {
		class Node;
	}
}

namespace tools {
	class Query {
		public:
			static std::vector<forec::ast::Node *> retrieveAll(forec::ast::Node &source, const std::string &type, const std::string &variant = "none");
			static std::vector<forec::ast::Node *> retrieveAll(std::vector<forec::ast::Node *> &source, const std::string &type, const std::string &variant = "none");

			static std::vector<forec::ast::Node *> retrieveChildren(forec::ast::Node &source, const std::string &type, const std::string &variant = "none");
			static std::vector<forec::ast::Node *> retrieveChildren(std::vector<forec::ast::Node *> &source, const std::string &type, const std::string &variant = "none");

			static std::vector<forec::ast::Node *> filterIn(forec::ast::Node &source, const std::string &type, const std::string &variant = "none");
			static std::vector<forec::ast::Node *> filterIn(std::vector<forec::ast::Node *> &source, const std::string &type, const std::string &variant = "none");

			static std::vector<forec::ast::Node *> filterOut(forec::ast::Node &source, const std::string &type, const std::string &variant = "none");
			static std::vector<forec::ast::Node *> filterOut(std::vector<forec::ast::Node *> &source, const std::string &type, const std::string &variant = "none");
		
		private:
			static std::vector<forec::ast::Node *> filter(forec::ast::Node &source, const std::string &type, const std::string &variant = "none", const bool condition = true);
			static std::vector<forec::ast::Node *> filter(std::vector<forec::ast::Node *> &source, const std::string &type, const std::string &variant = "none", const bool condition = true);

	};

}
#endif // TOOLS_QUERY_HPP
