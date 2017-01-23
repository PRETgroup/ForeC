#ifndef TOOLS_CONDITION_HPP
#define TOOLS_CONDITION_HPP
/*
 *  Condition.hpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 8/04/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>

namespace forec {
	namespace ast {
		class IterationStatement;
		class SelectionStatement;
		class ParStatement;
	}
}

namespace tools {
	class Condition {
		public:
			static void clear(void);

			static const bool enterScope(forec::ast::IterationStatement &iterationStatement);
			static void enterScope(forec::ast::SelectionStatement &selectionStatement);
			static void leaveScope(const std::string &type);
			static void setSelectionBranch(const std::string &branch);

			static void addParStatement(forec::ast::ParStatement &parStatement);

			static const std::vector<forec::ast::IterationStatement *> getCurrentIterations(void);
			static const std::vector<std::pair<forec::ast::SelectionStatement *, std::string> > getCurrentSelections(void);

			static const forec::ast::IterationStatement *lookupIterationId(const std::string &iterationId);
			static const forec::ast::SelectionStatement *lookupSelectionId(const std::string &selectionId);

			static const std::set<forec::ast::ParStatement *> getParStatements(const std::string &threadScope, const std::string &type, const std::string &id);
			static const std::set<forec::ast::ParStatement *> getParStatements(const std::string &threadScope, const std::string &type, const std::string &branch, const std::string &id);

			static bool hasParStatements(const std::string &threadScope, const std::string &type, const std::string &id);

			static const std::map<std::string, std::map<forec::ast::ParStatement *, forec::ast::IterationStatement *> > getIterations(void);
			static const forec::ast::IterationStatement *getIterations(const std::string &threadScope, forec::ast::ParStatement &parStatement);

			static const std::map<std::string, std::map<forec::ast::ParStatement *, std::pair<forec::ast::SelectionStatement *, std::string> > > getSelections(void);
			static const std::pair<forec::ast::SelectionStatement *, std::string> getSelections(const std::string &threadScope, forec::ast::ParStatement &parStatement);

			static const bool inIterationScope(const std::string &threadScope, forec::ast::ParStatement *parStatement);

			static const std::string toString(void);

		private:
			static std::string selectionBranch;

			// vector<iterationStatement>
			static std::vector<forec::ast::IterationStatement *> iterationScopeName;

			// vector<selectionStatement>
			static std::vector<std::pair<forec::ast::SelectionStatement *, std::string> > selectionScopeName;

			// map<iterationId, IterationStatement>
			static std::map<std::string, forec::ast::IterationStatement *> iterationIdTable;

			// map<selectionId, SelectionStatement>
			static std::map<std::string, forec::ast::SelectionStatement *> selectionIdTable;

			// map<threadScope, map<parStatement, iterationStatement> >
			static std::map<std::string, std::map<forec::ast::ParStatement *, forec::ast::IterationStatement *> > iterationParStatements;

			// map<threadScope, map<parStatement, pair<selectionStatement, branch> > >
			static std::map<std::string, std::map<forec::ast::ParStatement *, std::pair<forec::ast::SelectionStatement *, std::string> > > selectionParStatements;
	};

}

#endif // TOOLS_CONDITION_HPP
