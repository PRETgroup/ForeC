#ifndef TOOLS_THREADING_HPP
#define TOOLS_THREADING_HPP
/*
 *  Thread.hpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <sstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>

namespace forec {
	namespace ast {
		class ParStatement;
		class ThreadDefinition;
	}
}

namespace tools {
	class Threading {
		public:
			static void clear(void);
			
			static void addDeclaration(const std::string &identifier);
			static void addDeclaration(const std::string &identifier, forec::ast::ThreadDefinition &declaration);
			static std::string addParStatement(forec::ast::ParStatement &parStatement);

			static const bool isThread(const std::string &identifier);
			static forec::ast::ParStatement *lookupId(const std::string &parId);

			static const std::set<std::string> getUnused(void);
			static const std::set<std::string> getDeclared(void);
			static forec::ast::ThreadDefinition *getDeclaration(const std::string &identifier);
			static const std::set<std::string> getReferenced(void);
			static const std::set<std::string> getUndeclared(void);
			static const std::map<std::string, std::vector<forec::ast::ParStatement *> > getParStatements(void);
			static const std::vector<forec::ast::ParStatement *> getParStatements(const std::string &threadScope);
			static const bool hasParStatements(const std::string &threadScope);
			static const std::string getEnclosingThreadScope(const std::string &threadId);
			static forec::ast::ParStatement *getEnclosingParStatement(const std::string &threadId);
			
			static const bool allDeclared(void);
			static const bool isUnused(const std::string &threadId);
			
			static void setCurrentName(const std::string &identifier);
			static const std::string getCurrentName(void);
						
			static const std::string toString(void);
			
			
		private:
			static const std::string suffix;
			static std::string currentName;
			
			// set<threadId>
			static std::set<std::string> used;
			
			// set<threadId>
			static std::set<std::string> declared;
			
			// set<pair<threadId,threading>
			static std::set<std::pair<std::string, forec::ast::ThreadDefinition *> > declarations;
			
			// map<threadId, parStatement>
			static std::map<std::string, forec::ast::ParStatement *> enclosingParStatements;
			
			// map<parId, parStatement>
			static std::map<std::string, forec::ast::ParStatement *> parIdTable;
			
			// map<threadScope, vector<parStatement> >
			static std::map<std::string, std::vector<forec::ast::ParStatement *> > parStatements;
	};

}

#endif // TOOLS_THREADING_HPP
