/*
 *  Template.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Template.hpp"

#include "Multicore.hpp"
#include "Threading.hpp"
#include "Abort.hpp"
#include "Condition.hpp"
#include "Mutex.hpp"
#include "SymbolTable.hpp"

#include "../ast/AbortStatement.hpp"
#include "../ast/CombineSpecifier.hpp"
#include "../ast/DeclarationSpecifiers.hpp"
#include "../ast/IterationStatement.hpp"
#include "../ast/SelectionStatement.hpp"
#include "../ast/ParStatement.hpp"
#include "../ast/PrimaryExpression.hpp"

#include "../tarot/Tarot.hpp"

namespace global {
	extern int debugLevel;
	extern unsigned long minReactionTime;
	extern std::string embeddedMainFunctionName;
}

namespace tools {
	std::map<std::string, std::string> Template::structures;
	const std::string Template::threadSuffix = "__thread";
	const std::string Template::rootFilePath = "tools/template/";
	const std::string Template::fileExtension = ".txt";
	const std::string Template::genericFiles[10] =	{
														"abort",
														"masterPar",
														"nestedHandler",
														"nestedHandlers",
														"reactionStart",
														"reactionEndMaster",
														"reactionEndSlave",
														"slave",
														"slavePar",
														"thread"
													};
	const std::string Template::architectureFiles[3] =	{
															"core",
															"global",
															"main"
														};

	void Template::readFiles(void) {
		const std::string foreccPath = getenv("FOREC_COMPILER_PATH");
		if (foreccPath.empty()) {
			throw std::string("Check your environment for FOREC_COMPILER_PATH: \"" + foreccPath + "\"");
		}

		int size = sizeof(Template::genericFiles)/sizeof(Template::genericFiles[0]);
		for (int i = 0; i < size; i++) {
			std::string filePath = foreccPath + Template::rootFilePath + Template::genericFiles[i] + Template::fileExtension;
			std::ifstream inFile(filePath.c_str());
			if (!inFile.good()) {
				throw std::string("Template::readFiles: Unable to open file \"" + filePath + "\".");
			}

			Template::structures[Template::genericFiles[i]] = "";

			std::string line;
			if (std::getline(inFile, line)) {
				Template::structures[Template::genericFiles[i]] += line;
			}
			while (std::getline(inFile, line)) {
				Template::structures[Template::genericFiles[i]] += std::string("\r\n") + line;
			}
		}

		size = sizeof(Template::architectureFiles)/sizeof(Template::architectureFiles[0]);
		for (int i = 0; i < size; i++) {
			std::string filePath = foreccPath + Template::rootFilePath + Multicore::getArchitecture() + '/' + Template::architectureFiles[i] + Template::fileExtension;
			std::ifstream inFile(filePath.c_str());
			if (!inFile.good()) {
				throw std::string("Template::readFiles: Unable to open file \"" + filePath + "\".");
			}

			Template::structures[Template::architectureFiles[i]] = "";

			std::string line;
			if (std::getline(inFile, line)) {
				Template::structures[Template::architectureFiles[i]] += line;
			}
			while (std::getline(inFile, line)) {
				Template::structures[Template::architectureFiles[i]] += std::string("\r\n") + line;
			}
		}
	}

	void Template::replace(std::string &content, const std::string &tag, const std::string &data) {
		while (content.find("%{" + tag + "}") != std::string::npos) {
			content.replace(content.find("%{" + tag + "}"), std::string("%{" + tag + "}").length(), data);
		}
	}

	const std::string Template::formatGlobal(void) {
		std::string content(Template::structures["global"]);

		if (Multicore::isArchitecture("x86")) {
			std::ostringstream coreCount;
			coreCount << Multicore::getCoreIds().size();
			Template::replace(content, "coreCount", coreCount.str());
		}
		
		if (Multicore::isArchitecture("x86") || Multicore::isArchitecture("ptarm")) {
			std::ostringstream mutexValues;
			std::set<std::string> mutexThreadScopes = Mutex::getThreadScopes();
			for (std::set<std::string>::const_iterator mutexThreadScope = mutexThreadScopes.begin(); mutexThreadScope != mutexThreadScopes.end(); ++mutexThreadScope) {
				mutexValues << "unsigned int forec_mutex_value_" << *mutexThreadScope << ';' << std::endl;
			}
			Template::replace(content, "mutexValues", mutexValues.str());
		}
		
		const std::vector<std::string> abortInitIdentifiers = Abort::getInitIdentifiers();
		std::ostringstream abort;
		for (std::vector<std::string>::const_iterator initIdentifier = abortInitIdentifiers.begin(); initIdentifier != abortInitIdentifiers.end(); initIdentifier++) {
			abort << "volatile int " << *initIdentifier << " = 0;" << std::endl;
		}
		Template::replace(content, "abort", abort.str());
		
		const std::map<std::string, std::vector<forec::ast::ParStatement *> > parStatements = Threading::getParStatements();
		std::map<std::string, std::set<std::string> > coreIds = forec::tarot::Tarot::getControlVariables();

		std::ostringstream par;
		for (std::map<std::string, std::vector<forec::ast::ParStatement *> >::const_iterator threadScope = parStatements.begin(); threadScope != parStatements.end(); ++ threadScope) {
			par << "// Thread " << threadScope->first << " with par(...)s" << std::endl;
			par << "volatile Parent " << threadScope->first << "ParParent;" << std::endl;

			for (std::set<std::string>::const_iterator coreId = coreIds[threadScope->first].begin(); coreId != coreIds[threadScope->first].end(); ++coreId) {
				par << "volatile Core " << threadScope->first << "ParCore" << *coreId << ';' << std::endl;
			}

			par << "volatile int " << threadScope->first << "ParReactionCounter;" << std::endl << std::endl;
		}
		Template::replace(content, "par", par.str());
		
		return content;
	}

	const std::string Template::formatSharedSymbols(void) {
		std::ostringstream output;
		std::set<std::string> existingSymbols;

		output << "// Locally declared shared variables -------------------------------" << std::endl;

		const std::map<std::string, std::set<forec::ast::PrimaryExpression *> > sharedDeclarations = SymbolTable::getDeclarations("shared");
		for (std::map<std::string, std::set<forec::ast::PrimaryExpression *> >::const_iterator sharedDeclaration = sharedDeclarations.begin(); sharedDeclaration != sharedDeclarations.end(); ++sharedDeclaration) {
			if (sharedDeclaration->first.compare("global") != 0) {
				output << "// " << sharedDeclaration->first << std::endl;

				for (std::set<forec::ast::PrimaryExpression *>::const_iterator symbol = sharedDeclaration->second.begin(); symbol != sharedDeclaration->second.end(); ++symbol) {
					output << ((forec::ast::DeclarationSpecifiers *)((*symbol)->getSpecifiers()))->getSharedStruct() << std::endl;
					
					std::ostringstream symbolName;
					symbolName << *(*symbol)->getSpecifiers() << ' ' << *(*symbol);
					existingSymbols.insert(symbolName.str());
					
					output << symbolName.str() << " = {.status = FOREC_SHARED_UNMODIFIED};" << std::endl;
				}

				output << std::endl;
			}
		}

		output << std::endl << "// Global versions of local copies of shared variables -------------" << std::endl;
		const std::set<std::string> threadIds = Threading::getDeclared();
		for (std::set<std::string>::const_iterator threadId = threadIds.begin(); threadId != threadIds.end(); ++threadId) {
			output << "// " << *threadId << std::endl;
			const std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > > indirectParallelThreadUseDef = SymbolTable::getIndirectParallelThread(true, true, *threadId);
			for (std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > >::const_iterator variable = indirectParallelThreadUseDef.begin(); variable != indirectParallelThreadUseDef.end(); ++variable) {
				if (variable->second.first == SymbolTable::intermediate) {
					output << *variable->first->getSpecifiers() << ' ' << *variable->first << "_copy_" << *threadId << " = {.status = FOREC_SHARED_UNMODIFIED};" << std::endl;
				}
			}
		}

		return output.str();
	}

	const std::string Template::formatMain(const std::string &declarations, std::vector<forec::ast::Node *> &mainBody, std::vector<forec::ast::Node *> &threads, const std::string argcName, const std::string argvName) {
		std::string content(Template::structures["main"]);

		Template::replace(content, "multicore", Template::formatMulticore(argcName, argvName));

		std::string masterCoreId = Multicore::getMasterCoreId();
		Template::replace(content, "masterCoreId", masterCoreId);
		
		Template::replace(content, "declarations", declarations);
		
		std::ostringstream minReactionTime;
		minReactionTime << global::minReactionTime;
		Template::replace(content, "minReactionTime", minReactionTime.str());

		if (mainBody.size() == 0) {
			Template::replace(content, "masterCoreBody", Tab::toString() + "// No statements found.");
		} else {
			std::ostringstream bodyOutput;
			bodyOutput << Tab::toString() << "//--------------------------------------------------------------" << std::endl << std::endl;
			bodyOutput << *(mainBody[0]->toString()) << std::endl << std::endl;
			bodyOutput << Tab::toString() << "//--------------------------------------------------------------" << std::endl;
			Template::replace(content, "masterCoreBody", bodyOutput.str());
		}

		std::ostringstream parHandler;
		if (Threading::hasParStatements("main")) {
			std::ostringstream reactingCondition;
			std::ostringstream setParCoresAsReacting;
			std::set<std::string> cores;
			std::map<std::string, std::set<std::string> > scopedReactionEnd = forec::tarot::Tarot::getScopedReactionEnd("main", masterCoreId);
			if (scopedReactionEnd.find("coreIds") != scopedReactionEnd.end()) {
				cores = scopedReactionEnd.find("coreIds")->second;
				cores.erase(masterCoreId);
			}
			for (std::set<std::string>::const_iterator core = cores.begin(); core != cores.end(); ++core) {
				const std::string parCore = "mainParCore" + *core;
				reactingCondition << "\t\twhile(" << parCore << ".status == FOREC_CORE_REACTING);" << std::endl;
				setParCoresAsReacting << "\t\t" << parCore << ".status = FOREC_CORE_REACTING;" << std::endl;
			}

			parHandler << "// forec:scheduler:parHandler:main:master:" << masterCoreId << ":start" << std::endl;
			parHandler << "mainParHandlerMaster" << masterCoreId << ": {" << std::endl;
			parHandler << "\tif (mainParParent.parId == -2) {" << std::endl;
			parHandler << "\t\t// Iteration" << std::endl;
			parHandler << "\t\t// Wait for other cores to complete their reaction." << std::endl;
			parHandler << reactingCondition.str() << std::endl;
			parHandler << "\t\tmainParParent.parStatus = FOREC_PAR_OFF;" << std::endl;
			parHandler << "\t\tmainParParent.parId = -1;" << std::endl;
			parHandler << std::endl;
			parHandler << "\t\t// Set slave cores' status to reacting." << std::endl;
			parHandler << setParCoresAsReacting.str() << std::endl;
			parHandler << "\t\t// Increment the reaction counter for synchronisation." << std::endl;
			parHandler << "\t\tmainParReactionCounter++;" << std::endl;
			parHandler << std::endl;
			parHandler << "\t\t// Return to thread main." << std::endl;
			parHandler << "\t\tgoto *mainParParent.programCounter;" << std::endl;
			parHandler << "\t}" << std::endl;
			parHandler << std::endl;
			parHandler << "\t// Control should not reach here." << std::endl;
			if (Multicore::isArchitecture("ptarm")) {
				parHandler << "\tasm volatile (\"nop\");" << std::endl;
			}
			parHandler << "\tgoto mainParHandlerMaster" << masterCoreId << ';' << std::endl;
			parHandler << '}' << std::endl;
			parHandler << "// forec:scheduler:parHandler:main:master:" << masterCoreId << ":end" << std::endl;
		}
		Template::replace(content, "parHandler", parHandler.str());

		// Generate nested par handlers
		std::ostringstream masterCoreParHandlers;
		std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, std::string> > > > linkedLists = forec::tarot::Tarot::getLinkedLists(masterCoreId);
		for (std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, std::string> > > >::const_iterator threadScope = linkedLists.begin(); threadScope != linkedLists.end(); ++threadScope) {
			std::string currentThreadScope = threadScope->first;
			if (currentThreadScope.compare("main") != 0) {
				std::map<std::string, std::vector<std::pair<std::string, std::string> > > parHandlers = threadScope->second;

				masterCoreParHandlers << Template::formatNestedParHandlers(currentThreadScope, parHandlers, masterCoreId);
			}
		}
		Template::replace(content, "masterCoreParHandlers", masterCoreParHandlers.str());

		// Generate reaction start handlers for each par(...)
		std::ostringstream masterReactionStarts;
		std::map<std::string, bool> reactionStarts = forec::tarot::Tarot::getReactionStarts(masterCoreId);
		for (std::map<std::string, bool>::const_iterator reactionStart = reactionStarts.begin(); reactionStart != reactionStarts.end(); ++reactionStart) {
			masterReactionStarts << Template::formatReactionStart(reactionStart->first, reactionStart->second, masterCoreId);
		}
		Template::replace(content, "masterReactionStarts", masterReactionStarts.str());

		// Generate reaction end handlers for each par(...)
		std::ostringstream masterReactionEnds;
		std::map<std::string, std::map<std::string, std::set<std::string> > > reactionEnds = forec::tarot::Tarot::getScopedReactionEnds(masterCoreId);
		for (std::map<std::string, std::map<std::string, std::set<std::string> > >::const_iterator reactionEnd = reactionEnds.begin(); reactionEnd != reactionEnds.end(); ++reactionEnd) {
			std::string threadScope = reactionEnd->first;
			std::map<std::string, std::set<std::string> > information = reactionEnd->second;

			masterReactionEnds << Template::formatReactionEnd(threadScope, information, masterCoreId);
		}
		Template::replace(content, "masterReactionEnds", masterReactionEnds.str());

		// Generate abort check handlers
		std::ostringstream masterAbortChecks;
		std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > abortChecks = forec::tarot::Tarot::getAbortChecks(masterCoreId);
		for (std::map<std::string, std::map<std::string, std::map<std::string, std::string> > >::const_iterator threadScope = abortChecks.begin(); threadScope != abortChecks.end(); ++threadScope) {
			masterAbortChecks << Template::formatAbortHandlers(threadScope->first, threadScope->second, masterCoreId);
		}
		Template::replace(content,"masterAbortChecks", masterAbortChecks.str());

		std::ostringstream slaveCoreBodies;
		const std::set<std::string> slaveCoreIds = Multicore::getSlaveCoreIds();
		for (std::set<std::string>::iterator slaveCoreId = slaveCoreIds.begin(); slaveCoreId != slaveCoreIds.end(); ++slaveCoreId) {
			slaveCoreBodies << Template::formatSlaves(*slaveCoreId);
		}
		Template::replace(content, "slaveCoreBodies", slaveCoreBodies.str());

		std::ostringstream threadContent;
		for (std::vector<forec::ast::Node *>::iterator thread = threads.begin(); thread != threads.end(); ++thread) {
			threadContent << *(*thread)->toString() << std::endl << std::endl;
		}
		Template::replace(content, "threads", threadContent.str());

		return content;
	}

	const std::string Template::formatThread(const std::string &declarations, const std::string &identifier, const std::vector<forec::ast::Node *> &body) {
		if (Threading::isUnused(identifier)) {
			return "";
		}

		std::string content(Template::structures["thread"]);


		if (body.empty()) {
			Template::replace(content, "body", Tab::toString() + "// No statements found.");
		} else {
			std::ostringstream bodyOutput;

			// Initialise the local copies of shared variables.
			bodyOutput << Tab::toString() << "// Initialise the local copies of shared variables." << std::endl;
			const std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > > indirectParallelThreadUseDef = SymbolTable::getIndirectParallelThread(true, true, identifier);
			for (std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > >::const_iterator variable = indirectParallelThreadUseDef.begin(); variable != indirectParallelThreadUseDef.end(); ++variable) {
				if (variable->second.first == SymbolTable::intermediate) {
					const std::string enclosingThreadScope = Threading::getEnclosingThreadScope(identifier);
					const SymbolTable::UpdateType enclosingThreadUpdateType = SymbolTable::getIndirectParallelThread(true, true, enclosingThreadScope).find(variable->first)->second.first;
					
					// Value and status.
					bodyOutput << Tab::toString() << *variable->first << "_copy_" << identifier << "_local.value = " << *variable->first;
					if (enclosingThreadUpdateType == SymbolTable::intermediate) {
						bodyOutput << "_copy_" << enclosingThreadScope;
					}
					bodyOutput << ".value;" << std::endl;
					bodyOutput << Tab::toString() << *variable->first << "_copy_" << identifier << "_local.status = FOREC_SHARED_UNMODIFIED;" << std::endl;
				}
			}
			bodyOutput << Tab::toString() << "//--------------------------------------------------------------" << std::endl << std::endl;

			bodyOutput << *(body[0]->toString());
			
			// Write back the defined copies back to their global copy.
			bodyOutput << std::endl << std::endl;
			bodyOutput << Tab::toString() << "//--------------------------------------------------------------" << std::endl;
			bodyOutput << Tab::toString() << "// Write the defined shared variables back to their global copy.";
			const std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > > indirectParallelThreadDef = SymbolTable::getIndirectParallelThread(false, true, identifier);
			for (std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > >::const_iterator variable = indirectParallelThreadDef.begin(); variable != indirectParallelThreadDef.end(); ++variable) {
				if (variable->second.first == SymbolTable::intermediate) {
					bodyOutput << std::endl << Tab::toString() << *variable->first << "_copy_" << identifier << " = " << *variable->first << "_copy_" << identifier << "_local;";
				}
			}
			
			Template::replace(content, "body", bodyOutput.str());
		}

		std::ostringstream deleteParHandler;
		if (Threading::hasParStatements(identifier)) {
			deleteParHandler << Tab::toString() << "// Delete par handler" << std::endl;
			deleteParHandler << Tab::toString() << identifier << "ParParent.parId = -3;" << std::endl;
			deleteParHandler << Tab::toString() << identifier << "ParParent.parStatus = FOREC_PAR_ON;" << std::endl;
			deleteParHandler << Tab::toString() << identifier << "ParParent.programCounter = &&" << identifier << "_endAddress;" << std::endl;
			deleteParHandler << Tab::toString() << "goto " << identifier << "ParHandlerMaster" << Multicore::getCoreId(identifier) << ';' << std::endl;
			deleteParHandler << Tab::toString() << identifier << "_endAddress:;" << std::endl;
		}

		const std::string parCore = Threading::getEnclosingThreadScope(identifier) + "ParCore" + Multicore::getCoreId(identifier);

		Template::replace(content, "threadId", identifier);
		Template::replace(content, "declarations", declarations);
		Template::replace(content, "parCore", parCore);
		Template::replace(content, "deleteParHandler", deleteParHandler.str());

		return content;
	}


	const std::string Template::formatPar(const std::string &parId, const std::string &coreId, const std::string &parStatement, const std::vector<std::pair<std::string, std::string> > &linkedList) {
		std::string content(Template::structures["masterPar"]);

		std::string parNumber(parId);
		parNumber.replace(parNumber.find("par"), std::string("par").length(), "");

		Template::replace(content, "tab", Tab::toString());
		Template::replace(content, "parStatement", parStatement);
		Template::replace(content, "parId", parId);
		Template::replace(content, "coreId", coreId);
		Template::replace(content, "parNumber", parNumber);

		int activeThreadsCount = 0;
		std::ostringstream linkedListString;
		if (linkedList.empty()) {
			linkedListString << Tab::toString() << "//-- No threads or nested par(...)s given." << std::endl;
			throw std::string("Template::formatPar: No linked list given for " + parStatement + " on core" + coreId + "\r\n");
		} else {
			std::string currentHandlerName;
			std::string currentHandlerAddress;
			std::string previousHandlerName;
			bool beginThread = true;
			for (std::vector<std::pair<std::string, std::string> >::const_iterator handler = linkedList.begin(); handler != linkedList.end(); ++handler) {
				activeThreadsCount += (handler->first.compare("thread") == 0) || (handler->first.compare("parHandler") == 0);

				currentHandlerName = handler->second;
				currentHandlerAddress = handler->second;

				if (beginThread && ((handler->first.compare("thread") == 0) || (handler->first.compare("parHandler") == 0) || (handler->first.compare("abortWeak") == 0) || (handler->first.compare("parEnd") == 0))) {
					beginThread = false;
					Template::replace(content, "beginThread", handler->second);
				}

				linkedListString << Tab::toString() << handler->second << ".programCounter = &&" << handler->second << ';' << std::endl;
				if (handler != linkedList.begin()) {
					linkedListString << Tab::toString() << (handler - 1)->second << ".nextThread = &" << handler->second << ';' << std::endl;
					linkedListString << Tab::toString() << handler->second << ".prevThread = &" << (handler - 1)->second << ';' << std::endl;
				}
			}
		}

		std::ostringstream activeThreadsCountString;
		activeThreadsCountString << activeThreadsCount;
		Template::replace(content, "activeThreadsCount", activeThreadsCountString.str());
		Template::replace(content, "linkedList", linkedListString.str());
		Template::replace(content, "firstThread", linkedList.front().second);
		Template::replace(content, "lastThread", linkedList.back().second);

		return content;
	}

	const std::string Template::formatPar(const std::string &parId, const std::string &coreId, const std::string &parStatement, const std::string &threadScope, const bool parWillPause) {
		std::ostringstream content;

		const std::string parParent = threadScope + "ParParent";
		const std::string threadId = threadScope + "__thread";

		std::string parNumber(parId);
		parNumber.replace(parNumber.find("par"), std::string("par").length(), "");

		// Propagate the latest values of shared variables to the child threads that use it
		// Note that, the child threads that do not use a shared variable may still define it.
		std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > > indirectParallelUseDef = SymbolTable::getIndirectParallelPar(true, false, parId);;
		if (parWillPause) {
			// If the can par pause, then update the global projections of the parent's local copies of shared variables that may have been defined.
			// Otherwise, the defines will be lost when the par pauses.
			const std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > > indirectParallelThreadDef = SymbolTable::getIndirectParallelThread(false, true, threadScope);
			indirectParallelUseDef.insert(indirectParallelThreadDef.begin(), indirectParallelThreadDef.end());
		}
		std::ostringstream propagateSharedToChildren;
		for (std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > >::const_iterator variable = indirectParallelUseDef.begin(); variable != indirectParallelUseDef.end(); ++variable) {
			if (variable->second.first == SymbolTable::intermediate) {
				propagateSharedToChildren << Tab::toString() << *(variable->first) << "_copy_" << threadScope << " = " << *(variable->first) << "_copy_" << threadScope << "_local" << ';' << std::endl;
			}
		}

		// Note that, a parent thread that does not define a shared variable may still use it.
		std::ostringstream propagateSharedToParent;
		const std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > > indirectParallelParUseDef = SymbolTable::getIndirectParallelPar(true, true, parId);
		for (std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > >::const_iterator variable = indirectParallelParUseDef.begin(); variable != indirectParallelParUseDef.end(); ++variable) {
			if (variable->second.first == SymbolTable::intermediate) {
				// From children to parent.
				propagateSharedToParent << std::endl << Tab::toString() << "if (" << *(variable->first) << "_copy_" << threadScope << ".status == FOREC_SHARED_MODIFIED) {";
				propagateSharedToParent << std::endl << Tab::toString() << '\t' << *(variable->first) << "_copy_" << threadScope << "_local = " << *(variable->first) << "_copy_" << threadScope << ';';
				propagateSharedToParent << std::endl << Tab::toString() << "} else {";
				propagateSharedToParent << std::endl << Tab::toString() << '\t' << *(variable->first) << "_copy_" << threadScope << "_local = " << *(variable->first) << ';';
				propagateSharedToParent << std::endl << Tab::toString() << '}';
			}
		}

		content << "// " << parStatement << std::endl;
		content << propagateSharedToChildren.str();
		content << Tab::toString() << "// Set the par(...) information." << std::endl;
		content << Tab::toString() << "// forec:statement:par:" << parId << ":start" << std::endl;
		content << Tab::toString() << parParent << ".parId = " << parNumber << ';' << std::endl;
		content << Tab::toString() << parParent << ".parStatus = FOREC_PAR_ON;" << std::endl;
		content << Tab::toString() << parParent << ".programCounter = &&" << parId << "JoinAddress_" << parParent << ';' << std::endl;
		content << std::endl;
		content << Tab::toString() << "// Remove this thread from the linked list." << std::endl;
		content << Tab::toString() << threadId << ".nextThread -> prevThread = " << threadId << ".prevThread;" << std::endl;
		content << Tab::toString() << threadId << ".prevThread -> nextThread = " << threadId << ".nextThread;" << std::endl;
		content << Tab::toString() << "goto " << threadScope << "ParHandlerMaster" << coreId << ";" << std::endl;
		content << Tab::toString() << parId << "JoinAddress_" << parParent << ":;" << std::endl;
		content << Tab::toString() << "// forec:statement:par:" << parId << ":end";
		content << propagateSharedToParent.str();

		return content.str();
	}

	const std::string Template::toString(void) {
		std::ostringstream output;

		output << "Templates available:" << std::endl;
		for (std::map<std::string, std::string>::iterator structure = Template::structures.begin(); structure != Template::structures.end(); ++structure) {
			output << structure->first << std::endl;
		}

		return output.str();
	}


	const std::string Template::formatMulticore(const std::string argcName, const std::string argvName) {
		std::string content(Template::structures["core"]);

		if (Multicore::isArchitecture("x86")) {
			std::ostringstream declareArgcArgv;			
			std::ostringstream returnValue;			
			if (!global::embeddedMainFunctionName.empty()) {
				declareArgcArgv << tools::Tab::toString() << "int argc__main_0_0 = 0;" << std::endl;
				declareArgcArgv << tools::Tab::toString() << "char ** argv__main_0_0 = NULL;" << std::endl << std::endl;
				
				returnValue << std::endl << tools::Tab::toString() << "pthread_exit(NULL);";
			}
		
			std::ostringstream pthreadSlavesCreate;			
			std::ostringstream pthreadSlavesJoin;
			std::set<std::string> slaveCoreIds = Multicore::getSlaveCoreIds();
			
			if (!slaveCoreIds.empty()) {
				pthreadSlavesCreate << std::endl << Tab::toString() << "// Slave cores" << std::endl;
				pthreadSlavesJoin << std::endl;
			}
			
			int i = 1;
			for (std::set<std::string>::const_iterator slaveCoreId = slaveCoreIds.begin(); slaveCoreId != slaveCoreIds.end(); ++slaveCoreId) {
				pthreadSlavesCreate << Tab::toString() << "Arguments arguments" << i << " = {.coreId = " << i << ", .argc = " << argcName << ", .argv = " << argvName << "};" << std::endl;
				pthreadSlavesCreate << Tab::toString() << "pthread_create(&cores[" << i << "], &slaveCoreAttribute, forecMain, (void *)&arguments" << i << ");" << std::endl;
				pthreadSlavesJoin   << Tab::toString() << "pthread_cancel(cores[" << i << "]);" << std::endl;
				pthreadSlavesJoin   << Tab::toString() << "pthread_join(cores[" << i << "], NULL);" << std::endl;
				++i;
			}
			
			Template::replace(content, "declareArgcArgv", declareArgcArgv.str());
			Template::replace(content, "argcName", argcName);
			Template::replace(content, "argvName", argvName);
			Template::replace(content, "pthreadSlavesCreate", pthreadSlavesCreate.str());
			Template::replace(content, "pthreadSlavesJoin", pthreadSlavesJoin.str());
			Template::replace(content, "returnValue", returnValue.str());
		}
		
		if (Multicore::isArchitecture("x86") || Multicore::isArchitecture("ptarm")) {
			std::ostringstream resetMutexValues;
			std::set<std::string> mutexThreadScopes = Mutex::getThreadScopes();
			for (std::set<std::string>::const_iterator mutexThreadScope = mutexThreadScopes.begin(); mutexThreadScope != mutexThreadScopes.end(); ++mutexThreadScope) {
				resetMutexValues << Tab::toString() << "forec_mutex_value_" << *mutexThreadScope << " = -1;" << std::endl;
			}

			Template::replace(content, "resetMutexValues", resetMutexValues.str());
		}

		const std::map<std::string, std::vector<forec::ast::ParStatement *> > parStatements = Threading::getParStatements();
		std::map<std::string, std::set<std::string> > controlCoreIds = forec::tarot::Tarot::getControlVariables();

		std::ostringstream initialise;
		for (std::map<std::string, std::vector<forec::ast::ParStatement *> >::const_iterator threadScope = parStatements.begin(); threadScope != parStatements.end(); ++ threadScope) {
			initialise << Tab::toString() << "// Thread " << threadScope->first << " with par(...)s" << std::endl;
			initialise << Tab::toString() << threadScope->first << "ParParent.parStatus = FOREC_PAR_OFF;" << std::endl;

			for (std::set<std::string>::const_iterator controlCoreId = controlCoreIds[threadScope->first].begin(); controlCoreId != controlCoreIds[threadScope->first].end(); ++controlCoreId) {
				initialise << Tab::toString() << threadScope->first << "ParCore" << *controlCoreId << ".sync = 1;" << std::endl;
				initialise << Tab::toString() << threadScope->first << "ParCore" << *controlCoreId << ".status = FOREC_CORE_REACTING;" << std::endl;
			}

			initialise << Tab::toString() << threadScope->first << "ParReactionCounter = 0;" << std::endl << std::endl;
		}

		std::set<std::string> existingThreads;
		std::ostringstream par;
		const std::map<std::string, std::map<std::string, std::set<std::string> > > handlers = forec::tarot::Tarot::getHandlers();
		for (std::map<std::string, std::map<std::string, std::set<std::string> > >::const_iterator parHandler = handlers.begin(); parHandler != handlers.end(); ++parHandler) {
			par << Tab::toString() << "// " << parHandler->first << std::endl;

			for (std::map<std::string, std::set<std::string> >::const_reverse_iterator handlerType = parHandler->second.rbegin(); handlerType != parHandler->second.rend(); ++handlerType) {
				for (std::set<std::string>::const_iterator handler = handlerType->second.begin(); handler != handlerType->second.end(); ++handler) {
					par << Tab::toString();
					if (existingThreads.find(*handler) != existingThreads.end()) {
						par << "// ";
					}
					par << "Thread " << *handler << ';' << std::endl;
					existingThreads.insert(*handler);
				}
			}

			par << std::endl;
		}

		const std::set<std::string> coreIds = Multicore::getCoreIds();
		std::ostringstream cases;
		for (std::set<std::string>::iterator coreId = coreIds.begin(); coreId != coreIds.end(); ++coreId) {
			if (Multicore::isArchitecture("ptarm")) {
				cases << Tab::toString() << "\tcase (" << *coreId << "):" << std::endl;
				Tab::indent();
				if (Multicore::isMasterCoreId(*coreId)) {
					std::set<std::string> slaveCores = Multicore::getSlaveCoreIds();
					for (std::set<std::string>::const_iterator slaveCore = slaveCores.begin(); slaveCore != slaveCores.end(); ++slaveCore) {
						cases << Tab::toString() << "\twhile(mainParCore" << *slaveCore << ".sync);" << std::endl;
					}
				} else {
					cases << Tab::toString() << "\tmainParCore" << *coreId << ".sync = 0;" << std::endl;
				}
				cases << Tab::toString() << "\tgoto mainParCore" << *coreId << ';' << std::endl << std::endl;
				Tab::dedent();
			} else {
				cases << Tab::toString() << "\tcase (" << *coreId << "):" << std::endl;
				Tab::indent();
				if (Multicore::isArchitecture("microblaze")) {
					if (Multicore::isMasterCoreId(*coreId)) {
						std::set<std::string> slaveCores = Multicore::getSlaveCoreIds();
						for (std::set<std::string>::const_iterator slaveCore = slaveCores.begin(); slaveCore != slaveCores.end(); ++slaveCore) {
							cases << Tab::toString() << "\twhile(mainParCore" << *slaveCore << ".sync);" << std::endl;
						}
					} else {
						cases << Tab::toString() << "\tmainParCore" << *coreId << ".sync = 0;" << std::endl;
					}
					cases << Tab::toString() << "\tgoto mainParCore" << *coreId << ';' << std::endl << std::endl;
				} else if (Multicore::isArchitecture("x86")) {
					cases << Tab::toString() << "\tgoto mainParCore" << *coreId << ';' << std::endl << std::endl;
				}
				Tab::dedent();
			}
		}

		Template::replace(content, "initialise", initialise.str());
		Template::replace(content, "par", par.str());
		Template::replace(content, "cases", cases.str());

		return content;
	}

	const std::string Template::formatSlaves(const std::string &coreId) {
		std::string content(Template::structures["slave"]);

		Template::replace(content, "slaveCoreId", coreId);

		if (Multicore::isArchitecture("ptarm")) {
			Template::replace(content, "armNop", "asm volatile (\"nop\");");
		} else {
			Template::replace(content, "armNop", "");
		}
		
		std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, std::string> > > > linkedLists = forec::tarot::Tarot::getLinkedLists(coreId);
		std::ostringstream slaveCoreParHandlers;
		std::ostringstream slavePars;
		for (std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, std::string> > > >::const_iterator threadScope = linkedLists.begin(); threadScope != linkedLists.end(); ++threadScope) {
			if (threadScope->first.compare("main") == 0) {
				for (std::map<std::string, std::vector<std::pair<std::string, std::string> > >::const_iterator parHandler = threadScope->second.begin(); parHandler != threadScope->second.end(); ++parHandler) {
					std::string slavePar(Template::structures["slavePar"]);

					std::string parNumber(parHandler->first);
					parNumber.replace(parNumber.find("par"), std::string("par").length(), "");

					Template::replace(slavePar, "parId", parHandler->first);
					Template::replace(slavePar, "coreId", coreId);
					Template::replace(slavePar, "firstThread", parHandler->second.front().second);
					Template::replace(slavePar, "lastThread", parHandler->second.back().second);
					Template::replace(slavePar, "parNumber", parNumber);

					int activeThreadsCount = 0;
					std::ostringstream linkedListString;
					bool beginThread = true;
					Tab::indent();
					for (std::vector<std::pair<std::string, std::string> >::const_iterator handler = parHandler->second.begin(); handler!= parHandler->second.end(); ++handler) {
						activeThreadsCount += (handler->first.compare("thread") == 0) || (handler->first.compare("parHandler") == 0);

						if (beginThread && ((handler->first.compare("thread") == 0) || (handler->first.compare("parHandler") == 0) || (handler->first.compare("abortWeak") == 0) || (handler->first.compare("parEnd") == 0))) {
							beginThread = false;
							Template::replace(slavePar, "beginThread", handler->second);
						}

						linkedListString << Tab::toString() << handler->second << ".programCounter = &&" << handler->second << ';' << std::endl;
						if (handler != parHandler->second.begin()) {
							linkedListString << Tab::toString() << (handler - 1)->second << ".nextThread = &" << handler->second << ';' << std::endl;
							linkedListString << Tab::toString() << handler->second << ".prevThread = &" << (handler - 1)->second << ';' << std::endl;
						}
					}
					Tab::dedent();

					std::ostringstream activeThreadsCountString;
					activeThreadsCountString << activeThreadsCount;
					Template::replace(slavePar, "activeThreadsCount", activeThreadsCountString.str());
					Template::replace(slavePar, "linkedList", linkedListString.str());
					slavePars << slavePar;
				}
			} else {
				const std::string currentThreadScope = threadScope->first;
				std::map<std::string, std::vector<std::pair<std::string, std::string> > > parHandlers = threadScope->second;

				slaveCoreParHandlers << Template::formatNestedParHandlers(currentThreadScope, parHandlers, coreId);
			}
		}

		Template::replace(content, "slavePars", slavePars.str());
		Template::replace(content, "slaveCoreParHandlers", slaveCoreParHandlers.str());

		// Generate reaction start handlers for each thread with par(...)s
		std::ostringstream slaveReactionStarts;
		std::map<std::string, bool> reactionStarts = forec::tarot::Tarot::getReactionStarts(coreId);
		for (std::map<std::string, bool>::const_iterator reactionStart = reactionStarts.begin(); reactionStart != reactionStarts.end(); ++reactionStart) {
			slaveReactionStarts << Template::formatReactionStart(reactionStart->first, reactionStart->second, coreId);
		}
		Template::replace(content, "slaveReactionStarts", slaveReactionStarts.str());

		// Generate reaction end handlers for each par(...)
		std::ostringstream slaveReactionEnds;
		std::map<std::string, std::map<std::string, std::set<std::string> > > reactionEnds = forec::tarot::Tarot::getScopedReactionEnds(coreId);
		for (std::map<std::string, std::map<std::string, std::set<std::string> > >::const_iterator reactionEnd = reactionEnds.begin(); reactionEnd != reactionEnds.end(); ++reactionEnd) {
			std::string threadScope = reactionEnd->first;
			std::map<std::string, std::set<std::string> > information = reactionEnd->second;

			slaveReactionEnds << Template::formatReactionEnd(threadScope, information, coreId);
		}
		Template::replace(content, "slaveReactionEnds", slaveReactionEnds.str());

		// Generate abort check handlers
		std::ostringstream slaveAbortChecks;
		std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > abortChecks = forec::tarot::Tarot::getAbortChecks(coreId);
		for (std::map<std::string, std::map<std::string, std::map<std::string, std::string> > >::const_iterator threadScope = abortChecks.begin(); threadScope != abortChecks.end(); ++threadScope) {
			slaveAbortChecks << Template::formatAbortHandlers(threadScope->first, threadScope->second, coreId);
		}
		Template::replace(content, "slaveAbortChecks", slaveAbortChecks.str());

		return content;
	}

	const std::string Template::formatReactionStart(const std::string &threadScope, const bool isMaster, const std::string &coreId) {
		std::string content = Template::structures["reactionStart"];

		const std::string handlerStartName = threadScope + "ReactionStart" + ((isMaster) ? "Master" : "Slave") + coreId;

		Template::replace(content, "threadScope", threadScope);
		Template::replace(content, "masterOrSlave", (isMaster) ? "master" : "slave");
		Template::replace(content, "coreId", coreId);
		Template::replace(content, "handlerStartName", handlerStartName);

		return content;
	}

	const std::string Template::formatReactionEnd(const std::string &threadScope, std::map<std::string, std::set<std::string> > &information, const std::string &coreId) {
		std::string content;

		const bool isMaster = information.find("isMaster") != information.end();
		const std::string handlerStartName = threadScope + "ReactionStart" + ((isMaster) ? "Master" : "Slave") + coreId;
		const std::string handlerEndName = threadScope + "ReactionEnd" + ((isMaster) ? "Master" : "Slave") + coreId;
		const std::string parHandler = threadScope + "ParHandler" + ((isMaster) ? "Master" : "Slave") + coreId;

		if (isMaster) {
			content = Template::structures["reactionEndMaster"];
		} else {
			content = Template::structures["reactionEndSlave"];
		}

		Template::replace(content, "coreId", coreId);
		Template::replace(content, "threadScope", threadScope);
		Template::replace(content, "handlerEndName", handlerEndName);

		if (Multicore::isArchitecture("ptarm")) {
			Template::replace(content, "armNop", "asm volatile (\"nop\");");
		} else {
			Template::replace(content, "armNop", "");
		}

		if (isMaster) {
			std::set<std::string> cores = information["coreIds"];
			std::ostringstream terminatedCondition;
			for (std::set<std::string>::const_iterator core = cores.begin(); core != cores.end(); ++core) {
				terminatedCondition << " && " << threadScope << "ParCore" << *core << ".status == FOREC_CORE_TERMINATED";
			}

			cores.erase(coreId);
			std::ostringstream reactingCondition;
			std::ostringstream setParCoresAsReacting;
			std::ostringstream setParCoresAsReactingIndented;
			for (std::set<std::string>::const_iterator core = cores.begin(); core != cores.end(); ++core) {
				const std::string parCore = threadScope + "ParCore" + *core;
				reactingCondition << "\twhile(" << parCore << ".status == FOREC_CORE_REACTING);" << std::endl;
				setParCoresAsReacting << "\t" << parCore << ".status = FOREC_CORE_REACTING;" << std::endl;
				setParCoresAsReactingIndented << "\t\t" << parCore << ".status = FOREC_CORE_REACTING;" << std::endl;
			}

			Template::replace(content, "reactingCondition", reactingCondition.str());
			Template::replace(content, "terminatedCondition", terminatedCondition.str());
			Template::replace(content, "setParCoresAsReacting", setParCoresAsReacting.str());
			Template::replace(content, "setParCoresAsReactingIndented", setParCoresAsReactingIndented.str());

			std::ostringstream nestedSwap;
			std::ostringstream resetMutex;
			std::ostringstream resetLocalMutex;
			if (threadScope.compare("main") != 0) {
				Tab::indent();

				if (Multicore::isArchitecture("x86") || Multicore::isArchitecture("ptarm")) {
					resetLocalMutex << std::endl << Tab::toString() << "forec_mutex_value_" << threadScope << " = -1;" << std::endl;
				} else if (Multicore::isArchitecture("microblaze")) {
					resetLocalMutex << std::endl;
					resetLocalMutex << Tab::toString() << "forec_mutex_set(" << Mutex::getOffset(threadScope) << ", FSL_FOREC_MUTEX_ID);" << std::endl;
				}

				nestedSwap << std::endl << std::endl;
				nestedSwap << Tab::toString() << "// Swap the reaction (start & end) handlers with (thread " << threadScope << " & nested par handler)." << std::endl;
				nestedSwap << Tab::toString() << handlerStartName << ".prevThread -> nextThread = &" << threadScope << "__thread;" << std::endl;
				nestedSwap << Tab::toString() << threadScope << "__thread.prevThread = " << handlerStartName << ".prevThread;" << std::endl;
				nestedSwap << Tab::toString() << threadScope << "__thread.nextThread = &" << parHandler << ';' << std::endl;
				nestedSwap << Tab::toString() << parHandler << ".prevThread = &" << threadScope << "__thread;" << std::endl;
				nestedSwap << Tab::toString() << parHandler << ".nextThread = " << handlerEndName << ".nextThread;" << std::endl;
				nestedSwap << Tab::toString() << handlerEndName << ".nextThread -> prevThread = &" << parHandler << ';';

				Tab::dedent();
			} else {
				resetMutex << Tab::toString() << "// Reset the mutex." << std::endl;
				if (Multicore::isArchitecture("x86") || Multicore::isArchitecture("ptarm")) {
					std::set<std::string> mutexThreadScopes = Mutex::getThreadScopes();
					for (std::set<std::string>::const_iterator mutexThreadScope = mutexThreadScopes.begin(); mutexThreadScope != mutexThreadScopes.end(); ++mutexThreadScope) {
						resetMutex << Tab::toString() << "forec_mutex_value_" << *mutexThreadScope << " = -1;" << std::endl;
					}
				} else if (Multicore::isArchitecture("microblaze")) {
					resetMutex << Tab::toString() << "forec_mutex_reset(FSL_FOREC_MUTEX_RESET_ID);" << std::endl;
				}

			}

			// Shared variables.
			std::ostringstream combineShared;
			std::ostringstream combineCases;
			const std::vector<forec::ast::ParStatement *> parStatements = Threading::getParStatements(threadScope);
			for (std::vector<forec::ast::ParStatement *>::const_iterator parStatement = parStatements.begin(); parStatement != parStatements.end(); ++parStatement) {
				const std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > > parallelSharedDef = SymbolTable::getIndirectParallelPar(false, true, (*parStatement)->getId());
				
				Tab::indent();
				std::ostringstream combine;
				
				// map<symbol, pair<updateType, set<threadIds> > >
				bool forLoopNeeded = false;
				for (std::map<forec::ast::PrimaryExpression *, std::pair<SymbolTable::UpdateType, std::set<std::string> > >::const_iterator variable = parallelSharedDef.begin(); variable != parallelSharedDef.end(); ++variable) {
					SymbolTable::UpdateType updateType = variable->second.first;

					if (updateType != SymbolTable::skip) {
						const std::set<std::string> threadIds = variable->second.second;
						const int numberOfDefiners = threadIds.size();
					
						// Name of the parent thread's global copy of the shared variable.
						std::ostringstream parentCopy;
						parentCopy << *variable->first;
						if (updateType == SymbolTable::intermediate) {
							// Write to the intermediate global variable instead of directly to the shared variable.
							parentCopy << "_copy_" << (*parStatement)->getThreadScope();
						}

						if (numberOfDefiners == 0) {
							// Nothing.
						} else if (numberOfDefiners == 1) {
							// Assign the modified copy.
							combine << std::endl;
							combine << Tab::toString() << "// " << *variable->first << std::endl;
							combine << Tab::toString() << "if (" << *variable->first << "_copy_" << *threadIds.begin() << ".status == FOREC_SHARED_MODIFIED) {" << std::endl;
							combine << Tab::toString() << '\t' << *variable->first << "_copy_" << *threadIds.begin() << ".status = FOREC_SHARED_UNMODIFIED;" << std::endl;
							combine << Tab::toString() << '\t' << parentCopy.str() << ".value = " << *variable->first << "_copy_" << *threadIds.begin() << ".value;" << std::endl;
							if (updateType == SymbolTable::intermediate) {
								combine << Tab::toString() << '\t' << parentCopy.str() << ".status = FOREC_SHARED_MODIFIED;" << std::endl;
							}

							combine << Tab::toString() << '}' << std::endl;
						} else {
							forLoopNeeded = true;
							
							// Create if-statements to find the modified copies.
							combine << std::endl;
							combine << Tab::toString() << "// " << *variable->first << std::endl;
							combine << Tab::toString() << "numberOfModifiedCopies = 0;" << std::endl;
							combine << Tab::toString() << *variable->first->getSpecifiers() << " *modified_" << *variable->first << '[' << numberOfDefiners << "];" << std::endl;
							combine << Tab::toString() << "// Find the modified copies." << std::endl;
							for (std::set<std::string>::const_iterator threadId = threadIds.begin(); threadId != threadIds.end(); ++threadId) {
								combine << Tab::toString() << "if (" << *variable->first << "_copy_" << *threadId << ".status == FOREC_SHARED_MODIFIED) {" << std::endl;
								combine << Tab::toString() << '\t' << *variable->first << "_copy_" << *threadId << ".status = FOREC_SHARED_UNMODIFIED;" << std::endl;
								combine << Tab::toString() << "\tmodified_" << *variable->first << "[numberOfModifiedCopies] = &" << *variable->first << "_copy_" << *threadId << ';' << std::endl;
								combine << Tab::toString() << "\t++numberOfModifiedCopies;" << std::endl;
								combine << Tab::toString() << '}' << std::endl;
							}

							// Assign the first modified copy.
							combine << Tab::toString() << "// Assign the first modified copy." << std::endl;
							combine << Tab::toString() << "if (numberOfModifiedCopies > 0) {" << std::endl;
							combine << Tab::toString() << '\t' << parentCopy.str() << ".value = modified_" << *variable->first << "[0]->value;" << std::endl;
							if (updateType == SymbolTable::intermediate) {
								combine << Tab::toString() << '\t' << parentCopy.str() << ".status = FOREC_SHARED_MODIFIED;" << std::endl;
							}
							if (updateType == SymbolTable::intermediate) {
								combine << Tab::toString() << "} else {" << std::endl;
								combine << Tab::toString() << '\t' << parentCopy.str() << ".status = FOREC_SHARED_UNMODIFIED;" << std::endl;
							}
							combine << Tab::toString() << '}' << std::endl;

							// Combine with the remaining modified copies.
							combine << Tab::toString() << "// Combine with the remaining modified copies." << std::endl;
							combine << Tab::toString() << "for (index = 1; index < numberOfModifiedCopies; ++index) {" << std::endl;
							if ((forec::ast::CombineSpecifier *)variable->first->getCombineSpecifier() == NULL) {
								std::ostringstream output;
								output << "Template::formatReactionEnd: Combine specifier needed for the shared variable \"" << variable->first->getTerminal() << "\" (line " << variable->first->getLineNumber() << ") but not found.";
								throw output.str();
							}
							combine << Tab::toString() << '\t' << parentCopy.str() << ".value = " << ((forec::ast::CombineSpecifier *)variable->first->getCombineSpecifier())->getTerminal() << "(&" << parentCopy.str() << ".value, &modified_" << *variable->first << "[index]->value);" << std::endl;
							combine << Tab::toString() << '}' << std::endl;
						}
					}
				}
				
				Tab::dedent();
				
				if (!combine.str().empty()) {
					combineCases << Tab::toString() << "if (parId == " << (*parStatement)->getIdNumber() << ") {" << std::endl;
					if (forLoopNeeded) {
						combineCases << Tab::toString() << "\tint index;" << std::endl;
						combineCases << Tab::toString() << "\tint numberOfModifiedCopies;" << std::endl;
					}
					combineCases << combine.str();
					combineCases << Tab::toString() << "} else ";
				}
			}

			if (!combineCases.str().empty()) {
				combineShared << std::endl;
				combineShared << Tab::toString() << "// Combine shared variables." << std::endl;
				combineShared << Tab::toString() << "int parId = " << threadScope << "ParParent.parId;" << std::endl;
				
				combineShared << combineCases.str();
				combineShared << '{' << std::endl;
				combineShared << Tab::toString() << "\t// Nothing." << std::endl;
				combineShared << Tab::toString() << '}' << std::endl;
			}

			std::ostringstream reactionCounter;
			if (global::debugLevel > 0) {
				if (Multicore::isArchitecture("microblaze") && threadScope.compare("main") == 0) {
					reactionCounter << std::endl;
					reactionCounter << Tab::toString() << "// forec:scheduler:counter:start" << std::endl;
					reactionCounter << Tab::toString() << "do { counterRead(counter, FSL_COUNTER_ID); } while (counter.current < " << global::minReactionTime << ");" << std::endl;
					reactionCounter << Tab::toString() << "// Stop counting the elapsed cycles for the current reaction." << std::endl;
					reactionCounter << Tab::toString() << "counterStop(FSL_COUNTER_ID);" << std::endl;
					reactionCounter << Tab::toString() << "counterRead(counter, FSL_COUNTER_ID);" << std::endl;
					reactionCounter << Tab::toString() << "counterDifference(counter);" << std::endl;
					reactionCounter << Tab::toString() << "counterMaximum(counter);" << std::endl;
					reactionCounter << Tab::toString() << "counterMinimum(counter);" << std::endl;
					reactionCounter << Tab::toString() << "counterAccumulate(counter);" << std::endl;
					reactionCounter << Tab::toString() << "counterAverage(counter);" << std::endl;
					reactionCounter << Tab::toString() << "xil_printf(\"%d Reaction time: %ld cycles, Min: %d, Avg: %d, Max: %d\\r\\n\", globalReactions, counter.difference, counter.min, counter.avg, counter.max);" << std::endl;
					reactionCounter << Tab::toString() << "globalReactions++;" << std::endl;
					reactionCounter << Tab::toString() << "// Restart counting of the elapsed cycles for the next reaction." << std::endl;
					reactionCounter << Tab::toString() << "counterReset(counter);" << std::endl;
					reactionCounter << Tab::toString() << "counterStart(counter, FSL_COUNTER_ID);" << std::endl;
					reactionCounter << Tab::toString() << "// forec:scheduler:counter:end" << std::endl;
				} else if (Multicore::isArchitecture("ptarm") && threadScope.compare("main") == 0) {
					reactionCounter << std::endl;
					reactionCounter << Tab::toString() << "// forec:scheduler:counter:start" << std::endl;
					reactionCounter << Tab::toString() << "PTARM_TIME_GET(reactionTimeEnd);" << std::endl;
					reactionCounter << Tab::toString() << "PTARM_MINUS(reactionTime, reactionTimeEnd, reactionTimeStart);" << std::endl;
					reactionCounter << Tab::toString() << "printf(utoa(globalReactions)); printf(\" \"); printf(\"Reaction time: \"); if (reactionTime.msb > 0) {printf(utoa(reactionTime.msb));}; printf(utoa(reactionTime.lsb)); printf(\" ns\\r\\n\");" << std::endl;
					reactionCounter << Tab::toString() << "globalReactions++;" << std::endl;
					reactionCounter << Tab::toString() << "// Restart counting of the elapsed cycles for the next reaction." << std::endl;
					reactionCounter << Tab::toString() << "PTARM_TIME_GET(reactionTimeStart);" << std::endl;
					reactionCounter << Tab::toString() << "// forec:scheduler:counter:end" << std::endl;
				}
			}

			Template::replace(content, "nestedSwap", nestedSwap.str());
			Template::replace(content, "resetMutex", resetMutex.str());
			Template::replace(content, "resetLocalMutex", resetLocalMutex.str());
			Template::replace(content, "combineShared", combineShared.str());
			Template::replace(content, "reactionCounter", reactionCounter.str());
		} else {
			Tab::indent();
			std::ostringstream nestedSwap;
			nestedSwap << std::endl;
			if (threadScope.compare("main") != 0) {
				nestedSwap << Tab::toString() << "// Swap the reaction (start & end) handlers with the nested par handler." << std::endl;
				nestedSwap << Tab::toString() << handlerStartName << ".prevThread -> nextThread = &" << parHandler << ';' << std::endl;
				nestedSwap << Tab::toString() << parHandler << ".prevThread = " << handlerStartName << ".prevThread;" << std::endl;
				nestedSwap << Tab::toString() << parHandler << ".nextThread = " << handlerEndName << ".nextThread;" << std::endl;
				nestedSwap << Tab::toString() << handlerEndName << ".nextThread -> prevThread = &" << parHandler << ';' << std::endl;
				if (Multicore::isArchitecture("ptarm")) {
					nestedSwap << Tab::toString() << "asm volatile (\"nop\");" << std::endl;
				}
				nestedSwap << Tab::toString() << "goto " << parHandler << ';';
			} else {
				if (Multicore::isArchitecture("ptarm")) {
					nestedSwap << Tab::toString() << "asm volatile (\"nop\");" << std::endl;
				}
				nestedSwap << Tab::toString() << "goto " << threadScope << "ParCore" << coreId << ';';
			}

			Tab::dedent();
			Template::replace(content, "nestedSwap", nestedSwap.str());
		}

		return content;
	}

	const std::string Template::formatNestedParHandlers(const std::string &threadScope, std::map<std::string, std::vector<std::pair<std::string, std::string> > > &parHandlers, const std::string &coreId) {
		std::string content(Template::structures["nestedHandler"]);

		const bool isMaster = Multicore::isMasterCoreId(threadScope, coreId);
		const std::string handlerName = threadScope + "ParHandler" + ((isMaster) ? "Master" : "Slave") + coreId;

		Template::replace(content, "coreId", coreId);
		Template::replace(content, "threadScope", threadScope);
		Template::replace(content, "masterOrSlave", (isMaster) ? "master" : "slave");
		Template::replace(content, "handlerName", handlerName);

		if (Multicore::isArchitecture("ptarm")) {
			Template::replace(content, "armNop", "asm volatile (\"nop\");");
		} else {
			Template::replace(content, "armNop", "");
		}

		std::ostringstream decrementEnclosingThreadCount;
		if (threadScope.compare("main") != 0) {
			decrementEnclosingThreadCount << Threading::getEnclosingThreadScope(threadScope) << "ParCore" << coreId << ".activeThreads--;";
		}

		std::ostringstream nextThread;
		std::ostringstream synchronise;
		std::ostringstream forLoop;
		std::ostringstream mutex;
		if (isMaster) {
			mutex << "\t// Check the execution status of the nested par(...)s." << std::endl;
			mutex << "\tif (" << threadScope << "ParParent.parStatus == FOREC_PAR_OFF) {" << std::endl;
			mutex << "\t\t// Release the mutex." << std::endl;
			if (Multicore::isArchitecture("x86") || Multicore::isArchitecture("ptarm")) {
				mutex << "\t\tforec_mutex_value_" << threadScope << " &= " << "0x" << std::hex << ~Mutex::getBaseMask(threadScope) << ';' << std::endl;
				mutex << std::endl;
				mutex << "\t\tgoto *" << handlerName << ".nextThread -> programCounter;" << std::endl;
				mutex << "\t}" << std::endl;
				mutex << "\t// Release the mutex." << std::endl;
				mutex << "\tforec_mutex_value_" << threadScope << " &= " << "0x" << std::hex << ~Mutex::getBaseMask(threadScope) << ';' << std::endl;
			} else if (Multicore::isArchitecture("microblaze")) {
				mutex << "\t\tforec_mutex_clear(" << Mutex::getOffset(threadScope) << ", FSL_FOREC_MUTEX_ID);" << std::endl;
				mutex << std::endl;
				mutex << "\t\tgoto *" << handlerName << ".nextThread -> programCounter;" << std::endl;
				mutex << "\t}" << std::endl;
				mutex << "\t// Release the mutex." << std::endl;
				mutex << "\tforec_mutex_clear(" << Mutex::getOffset(threadScope) << ", FSL_FOREC_MUTEX_ID);" << std::endl;
			}

			std::ostringstream reactingCondition;
			std::ostringstream setParCoresAsReacting;
			std::set<std::string> cores = forec::tarot::Tarot::getScopedReactionEnd(threadScope, coreId).find("coreIds")->second;
			cores.erase(coreId);
			for (std::set<std::string>::const_iterator core = cores.begin(); core != cores.end(); ++core) {
				const std::string parCore = threadScope + "ParCore" + *core;
				reactingCondition << "\t\twhile(" << parCore << ".status == FOREC_CORE_REACTING);" << std::endl;
				setParCoresAsReacting << "\t\t" << parCore << ".status = FOREC_CORE_REACTING;" << std::endl;
			}

			forLoop << "\t\t// Wait for other cores to complete their reaction." << std::endl;
			forLoop << reactingCondition.str() << std::endl;
			forLoop << "\t\t" << threadScope << "ParParent.parStatus = FOREC_PAR_OFF;" << std::endl;
			forLoop << "\t\t" << threadScope << "ParParent.parId = -1;" << std::endl << std::endl;
			if (Multicore::isArchitecture("x86") || Multicore::isArchitecture("ptarm")) {
				forLoop << "\t\tforec_mutex_value_" << threadScope << " = -1;" << std::endl;
			} else if (Multicore::isArchitecture("microblaze")) {
				forLoop << "\t\tforec_mutex_set(" << Mutex::getOffset(threadScope) << ", FSL_FOREC_MUTEX_ID);" << std::endl;
			}

			forLoop << std::endl;
			forLoop << "\t\t// Set slave cores' status to reacting." << std::endl;
			forLoop << setParCoresAsReacting.str() << std::endl;
			forLoop << "\t\t// Increment the reaction counter for synchronisation." << std::endl;
			forLoop << "\t\t" << threadScope << "ParReactionCounter++;" << std::endl;
			forLoop << std::endl;
			forLoop << "\t\t// Return to thread " << threadScope << '.' << std::endl;
			forLoop << "\t\tgoto *" << threadScope << "ParParent.programCounter;";

			synchronise << "\t\t// Wait for other cores to complete their reaction." << std::endl;
			synchronise << reactingCondition.str() << std::endl;
			synchronise << "\t\t" << threadScope << "ParParent.parStatus = FOREC_PAR_OFF;" << std::endl;
			synchronise << "\t\t" << threadScope << "ParParent.parId = -1;" << std::endl;
			synchronise << std::endl;
			synchronise << "\t\t// Set slave cores' status to reacting." << std::endl;
			synchronise << setParCoresAsReacting.str() << std::endl;
			synchronise << "\t\t// Increment the reaction counter for synchronisation." << std::endl;
			synchronise << "\t\t" << threadScope << "ParReactionCounter++;" << std::endl;

			nextThread << "\t\t// Return to thread " << threadScope << '.' << std::endl;
			nextThread << "\t\tgoto *" << threadScope << "ParParent.programCounter;";
		} else {
			mutex << "\t// Synchronise the checking of the nested par(...) via a mutex." << std::endl;
			if (Multicore::isArchitecture("x86") || Multicore::isArchitecture("ptarm")) {
				mutex << "\twhile ((unsigned)(forec_mutex_value_" << threadScope << " & " << "0x" << std::hex << Mutex::getBaseMask(threadScope) << ") == (unsigned)" << "0x" << std::hex << Mutex::getBaseMask(threadScope) << ");" << std::endl;
			} else if (Multicore::isArchitecture("microblaze")) {
				mutex << "\tforec_mutex_read(forec_mutex_value, FSL_FOREC_MUTEX_ID);" << std::endl;
				mutex << "\twhile ((unsigned)(forec_mutex_value & " << "0x" << std::hex << Mutex::getBaseMask(threadScope) << ") == (unsigned)" << "0x" << std::hex << Mutex::getBaseMask(threadScope) << ") {" << std::endl;
				mutex << "\t\tforec_mutex_read(forec_mutex_value, FSL_FOREC_MUTEX_ID);" << std::endl;
				mutex << "\t}" << std::endl;
			}
			mutex << std::endl;
			mutex << "\t// Check the execution status of the nested par(...)s." << std::endl;
			mutex << "\tif (" << threadScope << "ParParent.parStatus == FOREC_PAR_OFF) {" << std::endl;
			mutex << "\t\tgoto *" << handlerName << ".nextThread -> programCounter;" << std::endl;
			mutex << "\t}" << std::endl;

			forLoop << "\t\t" << threadScope << "ParCore" << coreId << ".reactionCounter = " << threadScope << "ParReactionCounter;" << std::endl;
			forLoop << "\t\t" << threadScope << "ParCore" << coreId << ".status = FOREC_CORE_TERMINATED;" << std::endl;
			forLoop << std::endl;
			forLoop << "\t\t// Wait for the next reaction." << std::endl;
			forLoop << "\t\t" << "while (" << threadScope << "ParCore" << coreId << ".reactionCounter == " << threadScope << "ParReactionCounter);" << std::endl;
			forLoop << std::endl;
			forLoop << "\t\t// Go to the next thread." << std::endl;
			forLoop << "\t\tgoto " << handlerName << ';';

			synchronise << "\t\t" << threadScope << "ParCore" << coreId << ".reactionCounter = " << threadScope << "ParReactionCounter;" << std::endl;
			synchronise << "\t\t" << threadScope << "ParCore" << coreId << ".status = FOREC_CORE_TERMINATED;" << std::endl;
			synchronise << std::endl;
			synchronise << "\t\t// Wait for the next reaction." << std::endl;
			synchronise << "\t\t" << "while (" << threadScope << "ParCore" << coreId << ".reactionCounter == " << threadScope << "ParReactionCounter);" << std::endl;

			nextThread << "\t\t// Go to the next thread." << std::endl;
			nextThread << "\t\tgoto *" << handlerName << ".nextThread -> programCounter;";
		}

		Template::replace(content, "decrementEnclosingThreadCount", decrementEnclosingThreadCount.str());
		Template::replace(content, "mutex", mutex.str());
		Template::replace(content, "forLoop", forLoop.str());
		Template::replace(content, "nextThread", nextThread.str());
		Template::replace(content, "synchronise", synchronise.str());

		std::ostringstream nestedHandlersString;
		for (std::map<std::string, std::vector<std::pair<std::string, std::string> > >::const_iterator parHandler = parHandlers.begin(); parHandler != parHandlers.end(); ++parHandler) {
			std::string nestedHandlers(Template::structures["nestedHandlers"]);

			std::string parNumber(parHandler->first);
			parNumber.replace(parNumber.find("par"), std::string("par").length(), "");

			const std::string linkedListFirstThread = parHandler->second.front().second;
			const std::string linkedListLastThread = parHandler->second.back().second;

			Template::replace(nestedHandlers, "threadScope", threadScope);
			Template::replace(nestedHandlers, "coreId", coreId);
			Template::replace(nestedHandlers, "handlerName", handlerName);
			Template::replace(nestedHandlers, "linkedListFirstThread", linkedListFirstThread);
			Template::replace(nestedHandlers, "linkedListLastThread", linkedListLastThread);
			Template::replace(nestedHandlers, "parId", parHandler->first);
			Template::replace(nestedHandlers, "parNumber", parNumber);

			int activeThreadsCount = 0;
			bool beginThread = true;
			std::ostringstream linkedListString;
			Tab::indent();
			for (std::vector<std::pair<std::string, std::string> >::const_iterator handler = parHandler->second.begin(); handler!= parHandler->second.end(); ++handler) {
				activeThreadsCount += (handler->first.compare("thread") == 0) || (handler->first.compare("parHandler") == 0);

				if (beginThread && ((handler->first.compare("thread") == 0) || (handler->first.compare("parHandler") == 0) || (handler->first.compare("abortWeak") == 0) || (handler->first.compare("parEnd") == 0))) {
					beginThread = false;
					Template::replace(nestedHandlers, "beginThread", handler->second);
				}

				linkedListString << Tab::toString() << handler->second << ".programCounter = &&" << handler->second << ';' << std::endl;

				if (handler != parHandler->second.begin()) {
					linkedListString << Tab::toString() << (handler - 1)->second << ".nextThread = &" << handler->second << ';' << std::endl;
					linkedListString << Tab::toString() << handler->second << ".prevThread = &" << (handler - 1)->second << ';' << std::endl;
				}
			}
			Tab::dedent();

			std::ostringstream activeThreadsCountString;
			activeThreadsCountString << activeThreadsCount;
			Template::replace(nestedHandlers, "activeThreadsCount", activeThreadsCountString.str());
			Template::replace(nestedHandlers, "linkedList", linkedListString.str());
			nestedHandlersString << nestedHandlers;
		}

		Template::replace(content, "nestedHandlers", nestedHandlersString.str());

		return content;
	}

	const std::string Template::formatAbortHandlers(const std::string &threadScope, const std::map<std::string, std::map<std::string, std::string> > &aborts, const std::string &coreId) {
		std::ostringstream content;

		for (std::map<std::string, std::map<std::string, std::string> >::const_iterator type = aborts.begin(); type != aborts.end(); ++type) {
			for (std::map<std::string, std::string>::const_iterator abort = type->second.begin(); abort != type->second.end(); ++abort) {
				std::string abortHandler(Template::structures["abort"]);

				const bool isMaster = Multicore::isMasterCoreId(threadScope, coreId);
				const std::string reactionEndName = threadScope + "ReactionEnd" + ((isMaster) ? "Master" : "Slave") + coreId;

				std::ostringstream newParParentAddress;
				if (isMaster) {
					newParParentAddress << std::endl << std::endl << "\t\t// Update the parent thread to resume at the end of the abort scope." << std::endl;
					newParParentAddress << "\t\t" << threadScope << "ParParent.programCounter = &&abortEnd_" << abort->first << ';';
				}

				Template::replace(abortHandler, "abortId", abort->first);
				Template::replace(abortHandler, "condition", abort->second);
				Template::replace(abortHandler, "threadScope", threadScope);
				Template::replace(abortHandler, "coreId", coreId);
				Template::replace(abortHandler, "newParParentAddress", newParParentAddress.str());
				Template::replace(abortHandler, "reactionEndName", reactionEndName);

				if (Multicore::isArchitecture("ptarm")) {
					Template::replace(abortHandler, "armNop", "asm volatile (\"nop\");");
				} else {
					Template::replace(abortHandler, "armNop", "");
				}
				
				content << abortHandler;
			}
		}

		return content.str();
	}


}



