#ifndef TOOLS_SYMBOL_TABLE_HPP
#define TOOLS_SYMBOL_TABLE_HPP
/*
 *  SymbolTable.hpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <utility>

namespace forec {
	namespace ast {
		class CombineSpecifier;
		class PrimaryExpression;
	}
}

namespace tools {
	class SymbolTable {
		public:
			enum UpdateType {
				skip = 0,
				intermediate,
				root
			};
			
			static void clear(void);

			static void enterScope(const std::string &scopeName = "");
			static void leaveScope();
			static void resetScope(void);
			
			// Scoping information.
			static void setScopeName(const std::string &scopeName);
			static const std::string getScopeName(void);
			static const int getInstance(const std::string &scopeName = SymbolTable::scopeName, const int currentLevel = SymbolTable::currentLevel);

			// Declarations.
			static const std::string addDeclaration(const std::string &type, forec::ast::PrimaryExpression &identifier);
			static forec::ast::PrimaryExpression *getDeclaration(const std::string &type, forec::ast::PrimaryExpression &identifier, const bool isRead, const bool isPointer);
			static const std::map<std::string, std::set<forec::ast::PrimaryExpression *> > getDeclarations(const std::string &type);
			static const std::set<forec::ast::PrimaryExpression *> getDeclarations(const std::string &scopeName, const std::string &type);
						
			// Use and Def.
			static std::set<forec::ast::PrimaryExpression *> getUsesDefs(const bool includeUse, const bool includeDef, const std::string &scopeName = "", const std::string &type = "");
			static std::set<forec::ast::PrimaryExpression *> getOnlyUsesDefs(const bool includeUse, const bool includeDef, const std::string &scopeName = "", const std::string &type = "");
			static std::map<forec::ast::PrimaryExpression *, std::set<std::string> > getUsesDefsMultiple(const bool includeUse, const bool includeDef, const std::string &scopeName = "", const std::string &type = "");

			// Shared variables.
			static void setIndirectParallelPar(const std::string &parId, std::map<forec::ast::PrimaryExpression *, std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > > > &results);
			static void setIndirectParallelThread(const std::string &threadId, std::map<forec::ast::PrimaryExpression *, std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > > > &results);

			static void setIndirectParallelParUpdateType(const std::string &parId, forec::ast::PrimaryExpression &identifier, const std::string &useDef, SymbolTable::UpdateType updateType);
			static void setIndirectParallelThreadUpdateType(const std::string &threadId, forec::ast::PrimaryExpression &identifier, const std::string &useDef, SymbolTable::UpdateType updateType);
			
			static std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > > getIndirectParallelPar(const bool includeUse, const bool includeDef, const std::string &parId);
			static std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > > getIndirectParallelThread(const bool includeUse, const bool includeDef, const std::string &threadId);
			static const std::string resolveSharedSuffix(forec::ast::PrimaryExpression &identifier, forec::ast::PrimaryExpression &declaration, const bool suppressValueElement, const bool suppressCopySuffix);

			// Combine functions.
			static void addCombineSpecifier(const std::string &specifier);
			static const std::set<std::string> getCombineSpecifiers(void);
			
			static std::set<forec::ast::PrimaryExpression *> getCombineNeeded(void);
			static std::set<forec::ast::PrimaryExpression *> getCombineSpecified(void);

			static const std::string toString(void);
			static const std::string outputXml(const std::string &indent = "");
			
				
		private:
			static std::string scopeName;
			static unsigned int currentLevel;
					
			// Declared symbols defined by each thread.
			// map<scopeName, map<[use, def], map<identifier, [enumeration, storage, typedef, function, thread, label, variable, input, output, shared]> > >
			static std::map<std::string, std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::string> > > useDef;
			
			// The shared variables used/defined indirectly by the child threads of a par(...) statement.
			// Used to construct a hierarchy of local copies of shared variables.
			// map<parId, map<symbol, map<[use, def], pair<updateType, set<threadIds> > > > >
			static std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > > > > indirectParallelVariablesPar;
			
			// The shared variables used/defined indirectly by the child threads of a thread.
			// Used to construct a hierachy of local copies of shared variables.
			// map<threadId, map<symbol, map<[use, def], pair<updateType, set<threadIds> > > > >
			static std::map<std::string, std::map<forec::ast::PrimaryExpression *, std::map<std::string, std::pair<SymbolTable::UpdateType, std::set<std::string> > > > > indirectParallelVariablesThread;

									
			// All the declared variables.
			// map<scopeName, vector[depth]<vector[instance]<map<declaration, [enumeration, storage, typedef, function, thread, label, variable, input, output, shared, sharedConst] > > > >
			static std::map<std::string, std::vector<std::vector<std::map<forec::ast::PrimaryExpression *, std::string > > > > symbols;
			
			// All the combine specifiers.
			// map<combineSpecifier>
			static std::set<std::string> combineSpecifiers;

	};

}
#endif // TOOLS_SYMBOL_TABLE_HPP
