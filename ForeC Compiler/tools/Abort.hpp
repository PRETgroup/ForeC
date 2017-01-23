#ifndef TOOLS_ABORT_HPP
#define TOOLS_ABORT_HPP

/*
 *  Abort.hpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

namespace forec {
	namespace ast {
		class AbortStatement;
		class ParStatement;
	}
}

namespace tools {
	class Abort {
		public:
			static void clear(void);

			static void enterScope(forec::ast::AbortStatement &abortStatement);
			static void leaveScope(void);

			static void addParStatement(forec::ast::ParStatement &parStatement);

			static const std::vector<forec::ast::AbortStatement *> getCurrentAborts(void);
			static const forec::ast::AbortStatement *lookupId(const std::string &abortId);
			static const std::string getVariant(const std::string &abortId);
			static const std::set<forec::ast::ParStatement *> getParStatements(const std::string &threadScope);

			static const std::map<std::string, std::map<forec::ast::ParStatement *, std::vector<forec::ast::AbortStatement *> > > getAborts(void);
			static const std::map<forec::ast::ParStatement *, std::vector<forec::ast::AbortStatement *> > getAborts(const std::string &threadScope);
			static const std::vector<forec::ast::AbortStatement *> getAborts(const std::string &threadScope, forec::ast::ParStatement &parStatement);

			static const std::string toString(void);
			static const std::string outputXml(const std::string &indent);

		private:
			// set<abortStatement>
			static std::set<forec::ast::AbortStatement *> oldAbortScopes;

			// vector<abortStatement>
			static std::vector<forec::ast::AbortStatement *> scopeName;
			
			// map<abortId, abortStatement>
			static std::map<std::string, forec::ast::AbortStatement *> abortIdTable;

			// map<threadScope, map<parStatement, vector<abortStatement> > >
			static std::map<std::string, std::map<forec::ast::ParStatement *, std::vector<forec::ast::AbortStatement *> > > parStatements;
	};

}

#endif // TOOLS_ABORT_HPP
