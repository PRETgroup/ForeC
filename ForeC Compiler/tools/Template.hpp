#ifndef TOOLS_TEMPLATE_HPP
#define TOOLS_TEMPLATE_HPP
/*
 *  Template.hpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <cstdlib>

namespace forec {
	namespace ast {
		class Node;
		class AbortStatement;
		class IterationStatement;
		class ParStatement;
		class SelectionStatement;
	}
}

namespace tools {
	class Template {
		public:
			static void readFiles(void);
			static void replace(std::string &content, const std::string &tag, const std::string &data);

			static const std::string formatGlobal(void);
			static const std::string formatSharedSymbols(void);
			static const std::string formatMain(const std::string &declarations, std::vector<forec::ast::Node *> &mainBody, std::vector<forec::ast::Node *> &threads, const std::string argcName, const std::string argvName);
			static const std::string formatThread(const std::string &declarations, const std::string &identifier, const std::vector<forec::ast::Node *> &body);
			static const std::string formatPar(const std::string &parId, const std::string &coreId, const std::string &parStatement, const std::vector<std::pair<std::string, std::string> > &linkedList);
			static const std::string formatPar(const std::string &parId, const std::string &coreId, const std::string &parStatement, const std::string &threadScope);

			static const std::string toString(void);

		private:
			// map<fileName, fileContent>
			static std::map<std::string, std::string> structures;

			static const std::string threadSuffix;
			static const std::string rootFilePath;
			static const std::string fileExtension;
			static const std::string genericFiles[10];
			static const std::string architectureFiles[3];

			static const std::string formatMulticore(const std::string argcName, const std::string argvName);
			static const std::string formatSlaves(const std::string &coreId);
			static const std::string formatReactionStart(const std::string &threadScope, const bool isMaster, const std::string &coreId);
			static const std::string formatReactionEnd(const std::string &threadScope, std::map<std::string, std::set<std::string> > &information, const std::string &coreId);
			static const std::string formatNestedParHandlers(const std::string &threadScope, std::map<std::string, std::vector<std::pair<std::string, std::string> > > &parHandlers, const std::string &coreId);
			static const std::string formatAbortHandlers(const std::string &threadScope, const std::map<std::string, std::map<std::string, std::string> > &aborts, const std::string &coreId);
	};

}

#endif // TOOLS_TEMPLATE_HPP
