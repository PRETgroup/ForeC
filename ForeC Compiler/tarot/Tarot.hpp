#ifndef TAROT_TAROT_HPP
#define TAROT_TAROT_HPP

/*
 *  Thread.hpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 12/04/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

namespace forec {
	namespace tarot {
		class Thread;
	}
}

namespace forec {
	namespace tarot {
		class Tarot {
			public:
				static void clear(void);

				// Thread
				static void addThread(const std::string &identifier, Thread &thread);
				static Thread *getThread(const std::string &identifier);

				// Core allocations
				static void setCoreAllocations(const std::map<std::string, std::string> &coreAllocations);
				static void setParCore(const std::string &threadScope, const std::string &parId, const std::string &coreId);

				// Core activity
				static void setActiveParCores(const std::string &threadScope, const std::string &parId);
				static const std::set<std::string> getActiveParCores(const std::string &threadScope, const std::string &parId);
				static void setInactiveParCores(const std::string &threadScope, const std::string &parId);

				// Handlers
				static void addReactionStart(const std::string &masterCoreId, const std::string &parId, const std::string &threadScope);
				static void addReactionEnd(const std::string &masterCoreId, const std::string &parId, const std::string &threadScope);
				static void addAbortHandler(const std::string &threadScope, const std::string &parId, const bool isStrong, const std::string &abortId, const std::string &condition);
				static void addParHandler(const std::string &threadScope, const std::string &parId, const std::string &enclosingParId, const std::string &masterCoreId);
				static void addThreadHandler(const std::string &threadId, const std::string &enclosingParId);

				// Linked lists
				static void addAbortToLinkedList(const std::string &abortId, const bool isStrong, const std::string &coreId, const std::string &threadScope, const std::string &parId);
				static void addParToLinkedList(const std::string &coreId, const std::string &parId, const std::string &masterCoreId, const std::string &threadScope, const std::string &enclosingParId, const std::string &enclosingThreadScope);
				static void addReactionStartToLinkedList(const std::string &coreId, const std::string &masterCoreId, const std::string &threadScope, const std::string &parId);
				static void addReactionEndToLinkedList(const std::string &coreId, const std::string &masterCoreId, const std::string &threadScope, const std::string &parId);
				static void addThreadToLinkedList(const std::string &threadId, const std::string &coreId, const bool isMaster, const std::string &threadScope, const std::string &enclosingParId);

				// Next par(...)s
				static void addNextParAfterPar(const std::string &coreId, const std::string &threadScope, const std::string &prevParId, const std::string &parId);
				static void addNextParAfterAbort(const std::string &coreId, const std::string &threadScope, std::vector<std::string> &prevAbortId, const std::string &parId);
				static void addNextParAfterIteration(const std::string &coreId, const std::string &threadScope, std::vector<std::string> &prevIterationId, const std::string &parId);
				static void addNextParAfterSelection(const std::string &coreId, const std::string &threadScope, std::vector<std::map<std::string, std::string> > &prevSelectionId, const std::string &parId);

				// Next par(...) in reaction
				static void addNextParAfterAbortInReaction(const std::string &coreId, const std::string &threadScope, std::vector<std::string> &prevAbortIdInReaction, const std::string &parId);
				static void addNextParAfterIterationInReaction(const std::string &coreId, const std::string &threadScope, std::vector<std::string> &prevIterationIdInReaction, const std::string &parId);
				static void addNextParAfterSelectionInReaction(const std::string &coreId, const std::string &threadScope, std::vector<std::map<std::string, std::string> > &prevSelectionIdInReaction, const std::string &parId);

				// Last par(...)
				static void addLastParInReaction(const std::string &coreId, const std::string &threadScope, const std::string &prevParId);
				static void addLastParIdInAbort(const std::string &coreId, const std::string &threadScope, const std::string &abortId, const std::string &prevParId);
				static void addLastParIdInIteration(const std::string &coreId, const std::string &threadScope, const std::string &iterationId, const std::string &prevParId);
				static void addLastParIdInSelection(const std::string &coreId, const std::string &threadScope, const std::string &selectionId, const std::string &branchType, const std::string &prevParId);
				static void addLastParIdInThread(const std::string &coreId, const std::string &threadScope, const std::string &prevParId);

				// Scopes
				static void addAbortScope(const std::string &abortId, const std::string &coreId, const std::string &parId);
				static void addIterationScope(const std::string &iterationId, const std::string &coreId, const std::string &parId);
				static void addSelectionScope(const std::string &selectionId, const std::string &branchType, const std::string &coreId, const std::string &parId);

				static void addAborts(const std::vector<std::pair<std::string, std::string> > &abortsWithPar, const std::string &parId);

				// Prepare
				static void linkParThreads(void);
				static void findThreadRecursion(void);
				static void splitByCoreId(const std::set<std::string> &coreIds);
				static void findNextPar(void);
				static void findNextParInReaction(void);
				static void findLastPar(void);

				// Process tasks
				static void flatten(void);
				static void extractParInformation(void);

				// Accessors
				static const std::map<std::string, std::set<std::string> > getControlVariables(void);
				static const std::set<std::string> getParCores(const std::string &threadScope, const std::string &parId);
				static const std::map<std::string, std::map<std::string, std::set<std::string> > > getInactiveParCores(void);
				static const std::map<std::string, std::map<std::string, std::set<std::string> > > getHandlers(void);
				static const std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, std::string> > > > getLinkedLists(const std::string &coreId);
				static const std::vector<std::pair<std::string, std::string> > getLinkedList(const std::string &coreId, const std::string &threadScope, const std::string &parId);

				static const std::map<std::string, bool> getReactionStarts(const std::string &coreId);
				static const std::map<std::string, std::map<std::string, std::set<std::string> > > getReactionEnds(const std::string &coreId);
				static const std::map<std::string, std::map<std::string, std::set<std::string> > > getScopedReactionEnds(const std::string &coreId);
				static const std::map<std::string, std::set<std::string> > getScopedReactionEnd(const std::string &threadScope, const std::string &coreId);
				static const std::map<std::string, std::set<std::string> > getReactionEnds(const std::string &coreId, const std::string &parId);
				static const std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > getAbortChecks(const std::string &coreId);

				static const std::string getNextParAfterPar(const std::string &coreId, const std::string &threadScope, const std::string &parId);
				static const std::string getNextParAfterAbort(const std::string &coreId, const std::string &threadScope, const std::string &abortId);
				static const std::string getNextParAfterIteration(const std::string &coreId, const std::string &threadScope, const std::string &iterationId);
				static const std::string getNextParAfterSelection(const std::string &coreId, const std::string &threadScope, const std::string &selectionId, const std::string &branchType);

				static const std::string getNextParAfterAbortInReaction(const std::string &coreId, const std::string &threadScope, const std::string &abortId);
				static const std::string getNextParAfterIterationInReaction(const std::string &coreId, const std::string &threadScope, const std::string &iterationId);
				static const std::string getNextParAfterSelectionInReaction(const std::string &coreId, const std::string &threadScope, const std::string &selectionId, const std::string &branchType);

				static const std::string getLastParIdInAbort(const std::string &abortId, const std::string &threadScope, const std::string &coreId);
				static const std::string getLastParIdInIteration(const std::string &iterationId, const std::string &threadScope, const std::string &coreId);
				static const std::string getLastParIdInSelection(const std::string &selectionId, const std::string &branchType, const std::string &threadScope, const std::string &coreId);
				static const std::map<std::string, std::map<std::string, std::string> > getLastParIdInThread(void);
				static const std::string getLastParIdInThread(const std::string &threadScope, const std::string &coreId);
				static const bool isLastParIdInThread(const std::string &threadScope, const std::string &coreId, const std::string &parId);

				static const std::map<std::string, std::map<std::string, std::set<std::string> > > getScopedAborts(void);
				static const std::set<std::string> getScopedAborts(const std::string &abortId, const std::string &information);
				static const std::map<std::string, std::map<std::string, std::set<std::string> > > getScopedIterations(void);
				static const std::set<std::string> getScopedIterations(const std::string &iterationId, const std::string &information);
				static const std::map<std::string, std::map<std::string, std::map<std::string, std::set<std::string> > > > getScopedSelections(void);
				static const std::set<std::string> getScopedSelections(const std::string &selectionId, const std::string &branchType, const std::string &information);

				static const std::vector<std::pair<std::string, std::string> > getAborts(const std::string &parId);

				static const std::string toString(void);
				static const std::string toDot(const std::string &fileName);
				static const std::string outputXml(const std::string &indent = "");
				

			private:
				// map<threadId, Thread>
				static std::map<std::string, Thread *> threads;

				// map<coreId, Thread>
				static std::map<std::string, Thread *> tarotByCoreId;

				// map<threadScope, map<parId, set<coreId> > >
				static std::map<std::string, std::map<std::string, std::set<std::string> > > parCores;

				// map<threadScope, map<parId, set<coreId> > >
				static std::map<std::string, std::map<std::string, std::set<std::string> > > activeParCores;

				// map<threadScope, map<parId, set<coreId> > >
				static std::map<std::string, std::map<std::string, std::set<std::string> > > inactiveParCores;

				// map<parId, map<[thread, par, abortWeak, abortStrong, reactionStart, reactionEnd], vector<handler> > >
				static std::map<std::string, std::map<std::string, std::set<std::string> > > handlers;

				// map<coreId, map<threadId, map<[weak,strong], map<abortId, condition> > > >
				static std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > > abortChecks;

				// map<coreId, map<threadScope, isMaster> >
				static std::map<std::string, std::map<std::string, bool> > reactionStarts;

				// map<coreId, map<parId, map<[coreIds, isMaster, threadScope], set<value> > > >
				static std::map<std::string, std::map<std::string, std::map<std::string, std::set<std::string> > > > reactionEnds;

				// map<coreId, map<threadScope, map<parId, vector<pair<[thread, parHandler, parStart, parEnd, abortStrong, abortWeak], handler> > > > >
				static std::map<std::string, std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, std::string> > > > > linkedLists;

				// map<parId, threadScope>
				static std::map<std::string, std::string> parThreadScope;


				// map<abortId, map<[coreIds, parIds], set<value> > >
				static std::map<std::string, std::map<std::string, std::set<std::string> > > scopedAborts;

				// map<selectionId, map<[coreIds, parIds], set<value> > >
				static std::map<std::string, std::map<std::string, std::set<std::string> > > scopedIterations;

				// map<iterationId, map<[if, else], map<[coreIds, parIds], set<value> > > >
				static std::map<std::string, std::map<std::string, std::map<std::string, std::set<std::string> > > > scopedSelections;

				// map<parId, vector<pair<abortId, parId> > >
				static std::map<std::string, std::vector<std::pair<std::string, std::string> > > aborts;


				// map<coreId, map<threadScope, map<parId, parId> > >
				static std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > nextParAfterPar;

				// map<coreId, map<threadScope, map<abortId, parId> > >
				static std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > nextParAfterAbort;

				// map<coreId, map<threadScope, map<iterationId, parId> > >
				static std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > nextParAfterIteration;

				// map<coreId, map<threadScope, map<selectionId, map<[if, else], parId> > > >
				static std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > > nextParAfterSelection;


				// map<coreId, map<threadScope, map<abortId, parId> > >
				static std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > nextParAfterAbortInReaction;

				// map<coreId, map<threadScope, map<iterationId, parId> > >
				static std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > nextParAfterIterationInReaction;

				// map<coreId, map<threadScope, map<selectionId, map<[if, else], parId> > > >
				static std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > > nextParAfterSelectionInReaction;


				// map<coreId, map<threadScope, set<parId> > >
				static std::map<std::string, std::map<std::string, std::set<std::string> > > lastParIdInReaction;

				// map<coreId, map<threadScope, map<abortId, parId> > >
				static std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > lastParIdInAbort;

				// map<coreId, map<threadScope, map<iterationId, parId> > >
				static std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > lastParIdInIteration;

				// map<coreId, map<threadScope, map<selectionId, map<branchType, parId> > > >
				static std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > > lastParIdInSelection;

				// map<coreId, map<threadScope, parId> >
				static std::map<std::string, std::map<std::string, std::string> > lastParIdInThread;


				// set<handlerName>
				static std::set<std::string> existingHandlers;
		};
	}
}

#endif // TAROT_TAROT_HPP
