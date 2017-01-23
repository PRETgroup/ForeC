/*
 *  Tarot.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 12/04/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Tarot.hpp"

#include "Abort.hpp"
#include "Thread.hpp"

#include "../tools/Abort.hpp"

namespace forec {
	namespace tarot {
		std::map<std::string, Thread *> Tarot::threads;
		std::map<std::string, Thread *> Tarot::tarotByCoreId;
		std::map<std::string, std::map<std::string, std::set<std::string> > > Tarot::parCores;
		std::map<std::string, std::map<std::string, std::set<std::string> > > Tarot::activeParCores;
		std::map<std::string, std::map<std::string, std::set<std::string> > > Tarot::inactiveParCores;
		std::map<std::string, std::map<std::string, std::set<std::string> > > Tarot::handlers;
		std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > > Tarot::abortChecks;
		std::map<std::string, std::map<std::string, bool> > Tarot::reactionStarts;
		std::map<std::string, std::map<std::string, std::map<std::string, std::set<std::string> > > > Tarot::reactionEnds;
		std::map<std::string, std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, std::string> > > > > Tarot::linkedLists;
		std::map<std::string, std::string> Tarot::parThreadScope;

		std::map<std::string, std::map<std::string, std::set<std::string> > > Tarot::scopedAborts;
		std::map<std::string, std::map<std::string, std::set<std::string> > > Tarot::scopedIterations;
		std::map<std::string, std::map<std::string, std::map<std::string, std::set<std::string> > > > Tarot::scopedSelections;

		std::map<std::string, std::vector<std::pair<std::string, std::string> > > Tarot::aborts;

		std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > Tarot::nextParAfterPar;
		std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > Tarot::nextParAfterAbort;
		std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > Tarot::nextParAfterIteration;
		std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > > Tarot::nextParAfterSelection;

		std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > Tarot::nextParAfterAbortInReaction;
		std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > Tarot::nextParAfterIterationInReaction;
		std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > > Tarot::nextParAfterSelectionInReaction;

		std::map<std::string, std::map<std::string, std::set<std::string> > > Tarot::lastParIdInReaction;
		std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > Tarot::lastParIdInAbort;
		std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > Tarot::lastParIdInIteration;
		std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > > Tarot::lastParIdInSelection;
		std::map<std::string, std::map<std::string, std::string> > Tarot::lastParIdInThread;

		std::set<std::string> Tarot::existingHandlers;


		void Tarot::clear(void) {
			Tarot::threads.clear();
			Tarot::tarotByCoreId.clear();
			Tarot::parCores.clear();
			Tarot::activeParCores.clear();
			Tarot::inactiveParCores.clear();
			Tarot::handlers.clear();
			Tarot::abortChecks.clear();
			Tarot::reactionStarts.clear();
			Tarot::reactionEnds.clear();
			Tarot::linkedLists.clear();
			Tarot::parThreadScope.clear();

			Tarot::scopedAborts.clear();
			Tarot::scopedIterations.clear();
			Tarot::scopedSelections.clear();

			Tarot::aborts.clear();

			Tarot::nextParAfterPar.clear();
			Tarot::nextParAfterAbort.clear();
			Tarot::nextParAfterIteration.clear();
			Tarot::nextParAfterSelection.clear();

			Tarot::nextParAfterAbortInReaction.clear();
			Tarot::nextParAfterIterationInReaction.clear();
			Tarot::nextParAfterSelectionInReaction.clear();

			Tarot::lastParIdInReaction.clear();
			Tarot::lastParIdInAbort.clear();
			Tarot::lastParIdInIteration.clear();
			Tarot::lastParIdInSelection.clear();
			Tarot::lastParIdInThread.clear();

			Tarot::existingHandlers.clear();
		}

		// Thread lookup
		void Tarot::addThread(const std::string &identifier, Thread &thread) {
			Tarot::threads[identifier] = &thread;
		}

		Thread *Tarot::getThread(const std::string &identifier) {
			return Tarot::threads[identifier];
		}

		// Core allocations
		void Tarot::setCoreAllocations(const std::map<std::string, std::string> &coreAllocations) {
			for (std::map<std::string, Thread *>::const_iterator thread = Tarot::threads.begin(); thread != Tarot::threads.end(); ++thread) {
				// Find core allocation for the thread.
				const std::string masterCoreId = (coreAllocations.find(thread->first))->second;
				thread->second->setMasterCoreId(masterCoreId);
			}
		}

		void Tarot::setParCore(const std::string &threadScope, const std::string &parId, const std::string &coreId) {
			// Save participating core Id.
			Tarot::parCores[threadScope]["all"].insert(coreId);
			Tarot::parCores[threadScope][parId].insert(coreId);
		}

		// Core activity
		void Tarot::setActiveParCores(const std::string &threadScope, const std::string &parId) {
			// Save superset of participating core IDs.
			std::set<std::string> parCores = Tarot::getParCores(threadScope, parId);
			Tarot::activeParCores[threadScope]["all"].insert(parCores.begin(), parCores.end());
			Tarot::activeParCores[threadScope][parId] = Tarot::activeParCores[threadScope]["all"];
		}

		const std::set<std::string> Tarot::getActiveParCores(const std::string &threadScope, const std::string &parId) {
			if (Tarot::activeParCores.find(threadScope) != Tarot::activeParCores.end()) {
				if (Tarot::activeParCores[threadScope].find(parId) != Tarot::activeParCores[threadScope].end()) {
					return Tarot::activeParCores[threadScope][parId];
				}
			}

			return std::set<std::string>();
		}

		void Tarot::setInactiveParCores(const std::string &threadScope, const std::string &parId) {
			// inactiveCores = allParCores - activeCores
			std::set<std::string> allCores = Tarot::getParCores(threadScope, "all");
			std::set<std::string> activeCores = Tarot::getActiveParCores(threadScope, parId);
			std::set<std::string> inactiveCores;
			std::set_difference(allCores.begin(), allCores.end(), activeCores.begin(), activeCores.end(), std::inserter(inactiveCores, inactiveCores.end()));

			if (inactiveCores.size() > 0) {
				Tarot::inactiveParCores[threadScope][parId] = inactiveCores;
			}
		}

		// Handlers
		void Tarot::addReactionStart(const std::string &masterCoreId, const std::string &parId, const std::string &threadScope) {
			// Get all participating cores within a thread.
			std::set<std::string> allParCores = Tarot::getParCores(threadScope, "all");
			for (std::set<std::string>::const_iterator coreId = allParCores.begin(); coreId != allParCores.end(); ++coreId) {
				Tarot::reactionStarts[*coreId][threadScope] = false;

				const std::string reactionStartName = threadScope + "ReactionStart" + (coreId->compare(masterCoreId) == 0 ? "Master" : "Slave") + *coreId;
				Tarot::handlers[parId]["reactionStart"].insert(reactionStartName);
			}

			Tarot::reactionStarts[masterCoreId][threadScope] = true;
		}

		void Tarot::addReactionEnd(const std::string &masterCoreId, const std::string &parId, const std::string &threadScope) {
			Tarot::reactionEnds[masterCoreId][parId]["isMaster"].insert("true");
			Tarot::reactionEnds[masterCoreId][parId]["coreIds"] = Tarot::getActiveParCores(threadScope, "all");

			// Get all participating cores within a thread.
			std::set<std::string> allParCores = Tarot::getParCores(threadScope, "all");
			for (std::set<std::string>::const_iterator coreId = allParCores.begin(); coreId != allParCores.end(); ++coreId) {
				Tarot::reactionEnds[*coreId][parId]["threadScope"].insert(threadScope);

				const std::string reactionEndName = threadScope + "ReactionEnd" + (coreId->compare(masterCoreId) == 0 ? "Master" : "Slave") + *coreId;
				Tarot::handlers[parId]["reactionEnd"].insert(reactionEndName);
			}
		}

		void Tarot::addAbortHandler(const std::string &threadScope, const std::string &parId, const bool isStrong, const std::string &abortId, const std::string &condition) {
			// Get participating cores for a par(...).
			std::set<std::string> parCores = Tarot::getParCores(threadScope, parId);
			for (std::set<std::string>::const_iterator coreId = parCores.begin(); coreId != parCores.end(); ++coreId) {
				const std::string abortHandlerName = abortId + "Check" + *coreId;
				const std::string abortType = std::string("abort") + std::string(isStrong ? "Strong" : "Weak");

				Tarot::handlers[parId][abortType].insert(abortHandlerName);
				Tarot::abortChecks[*coreId][threadScope][(isStrong ? "strong" : "weak")][abortId] = condition;
			}
		}

		void Tarot::addParHandler(const std::string &threadScope, const std::string &parId, const std::string &enclosingParId, const std::string &masterCoreId) {
			if (threadScope.compare("main") != 0) {
				// Get participating cores for a par(...).
				std::set<std::string> parCores = Tarot::getParCores(threadScope, parId);
				for (std::set<std::string>::const_iterator coreId = parCores.begin(); coreId != parCores.end(); ++coreId) {
					const std::string parHandlerName = threadScope + "ParHandler" + (coreId->compare(masterCoreId) == 0 ? "Master" : "Slave") + *coreId;

					Tarot::handlers[enclosingParId]["parHandler"].insert(parHandlerName);
				}
			}
		}

		void Tarot::addThreadHandler(const std::string &threadId, const std::string &enclosingParId) {
			if (threadId.compare("main") != 0) {
				Tarot::handlers[enclosingParId]["thread"].insert(threadId + "__thread");
			}
		}

		// Linked lists
		void Tarot::addAbortToLinkedList(const std::string &abortId, const bool isStrong, const std::string &coreId, const std::string &threadScope, const std::string &parId) {
			const std::string abortHandlerName = abortId + "Check" + coreId;

			// Only add the handler once for each par(...).
			if (Tarot::existingHandlers.find(parId + "_" + abortHandlerName) == Tarot::existingHandlers.end()) {
				Tarot::linkedLists[coreId][threadScope][parId].push_back(std::make_pair("abort" + std::string(isStrong ? "Strong" : "Weak"), abortHandlerName));
				Tarot::existingHandlers.insert(parId + "_" + abortHandlerName);
			}
		}

		void Tarot::addParToLinkedList(const std::string &coreId, const std::string &parId, const std::string &masterCoreId, const std::string &threadScope, const std::string &enclosingParId, const std::string &enclosingThreadScope) {
			const std::string parHandlerName = threadScope + "ParHandler" + (coreId.compare(masterCoreId) == 0 ? "Master" : "Slave") + coreId;

			// Only add the handler once for each enclosing par(...).
			if (threadScope.compare("main") != 0 && Tarot::existingHandlers.find(parHandlerName + "_" + enclosingParId) == Tarot::existingHandlers.end()) {
				Tarot::linkedLists[coreId][enclosingThreadScope][enclosingParId].push_back(std::make_pair("parHandler", parHandlerName));
				Tarot::existingHandlers.insert(parHandlerName + "_" + enclosingParId);
			}

			Tarot::parThreadScope[parId] = threadScope;
		}

		void Tarot::addReactionStartToLinkedList(const std::string &coreId, const std::string &masterCoreId, const std::string &threadScope, const std::string &parId) {
			const std::string reactionStartName = threadScope + "ReactionStart" + (coreId.compare(masterCoreId) == 0 ? "Master" : "Slave") + coreId;

			// Only add the handler once for each par(...).
			if (Tarot::existingHandlers.find(parId + "_" + reactionStartName) == Tarot::existingHandlers.end()) {
				Tarot::linkedLists[coreId][threadScope][parId].push_back(std::make_pair("parStart", reactionStartName));
				Tarot::existingHandlers.insert(parId + "_" + reactionStartName);
			}
		}

		void Tarot::addReactionEndToLinkedList(const std::string &coreId, const std::string &masterCoreId, const std::string &threadScope, const std::string &parId) {
			const std::string reactionEndName = threadScope + "ReactionEnd" + (coreId.compare(masterCoreId) == 0 ? "Master" : "Slave") + coreId;

			// Only add the handler once for each par(...).
			if (Tarot::existingHandlers.find(parId + "_" + reactionEndName) == Tarot::existingHandlers.end()) {
				Tarot::linkedLists[coreId][threadScope][parId].push_back(std::make_pair("parEnd", reactionEndName));
				Tarot::existingHandlers.insert(parId + "_" + reactionEndName);
			}
		}

		void Tarot::addThreadToLinkedList(const std::string &threadId, const std::string &coreId, const bool isMaster, const std::string &threadScope, const std::string &enclosingParId) {
			// Only add the handler once for each enclosing par(...).
			if (threadId.compare("main") != 0 && isMaster && Tarot::existingHandlers.find(threadId + "__thread_" + enclosingParId) == Tarot::existingHandlers.end()) {
				Tarot::linkedLists[coreId][threadScope][enclosingParId].push_back(std::make_pair("thread", threadId + "__thread"));
				Tarot::existingHandlers.insert(threadId + "__thread_" + enclosingParId);
			}
		}

		// Next par(...)s
		void Tarot::addNextParAfterPar(const std::string &coreId, const std::string &threadScope, const std::string &prevParId, const std::string &parId) {
			if (!prevParId.empty() && threadScope.compare("main") != 0) {
				Tarot::nextParAfterPar[coreId][threadScope][prevParId] = parId;
			}
		}

		void Tarot::addNextParAfterAbort(const std::string &coreId, const std::string &threadScope, std::vector<std::string> &prevAbortId, const std::string &parId) {
			if (threadScope.compare("main") != 0) {
				for (std::vector<std::string>::const_iterator abortId = prevAbortId.begin(); abortId != prevAbortId.end(); ++abortId) {
					Tarot::nextParAfterAbort[coreId][threadScope][*abortId] = parId;
				}
			}

			// Remove abort scopes.
			prevAbortId.clear();
		}

		void Tarot::addNextParAfterIteration(const std::string &coreId, const std::string &threadScope, std::vector<std::string> &prevIterationId, const std::string &parId) {
			if (threadScope.compare("main") != 0) {
				for (std::vector<std::string>::const_iterator iterationId = prevIterationId.begin(); iterationId != prevIterationId.end(); ++iterationId) {
					Tarot::nextParAfterIteration[coreId][threadScope][*iterationId] = parId;
				}
			}

			// Remove iteration scopes.
			prevIterationId.clear();
		}

		void Tarot::addNextParAfterSelection(const std::string &coreId, const std::string &threadScope, std::vector<std::map<std::string, std::string> > &prevSelectionId, const std::string &parId) {
			if (threadScope.compare("main") != 0) {
				for (std::vector<std::map<std::string, std::string> >::const_iterator selectionId = prevSelectionId.begin(); selectionId != prevSelectionId.end(); ++selectionId) {
					for (std::map<std::string, std::string>::const_iterator branchType = selectionId->begin(); branchType != selectionId->end(); ++branchType) {
						Tarot::nextParAfterSelection[coreId][threadScope][branchType->first][branchType->second] = parId;
					}
				}
			}
			
			// Remove selection scopes.
			prevSelectionId.clear();
		}

		// Next par(...) in reaction
		void Tarot::addNextParAfterAbortInReaction(const std::string &coreId, const std::string &threadScope, std::vector<std::string> &prevAbortIdInReaction, const std::string &parId) {
			if (threadScope.compare("main") != 0) {
				for (std::vector<std::string>::const_iterator abortId = prevAbortIdInReaction.begin(); abortId != prevAbortIdInReaction.end(); ++abortId) {
					Tarot::nextParAfterAbortInReaction[coreId][threadScope][*abortId] = parId;
				}
			}
			
			// Remove abort scopes.
			prevAbortIdInReaction.clear();
		}

		void Tarot::addNextParAfterIterationInReaction(const std::string &coreId, const std::string &threadScope, std::vector<std::string> &prevIterationIdInReaction, const std::string &parId) {
			if (threadScope.compare("main") != 0) {
				for (std::vector<std::string>::const_iterator iterationId = prevIterationIdInReaction.begin(); iterationId != prevIterationIdInReaction.end(); ++iterationId) {
					Tarot::nextParAfterIterationInReaction[coreId][threadScope][*iterationId] = parId;
				}
			}

			// Remove iterations.
			prevIterationIdInReaction.clear();
		}

		void Tarot::addNextParAfterSelectionInReaction(const std::string &coreId, const std::string &threadScope, std::vector<std::map<std::string, std::string> > &prevSelectionIdInReaction, const std::string &parId) {
			if (threadScope.compare("main") != 0) {
				for (std::vector<std::map<std::string, std::string> >::const_iterator selectionId = prevSelectionIdInReaction.begin(); selectionId != prevSelectionIdInReaction.end(); ++selectionId) {
					for (std::map<std::string, std::string>::const_iterator branchType = selectionId->begin(); branchType != selectionId->end(); ++branchType) {
						Tarot::nextParAfterSelectionInReaction[coreId][threadScope][branchType->first][branchType->second] = parId;
					}
				}
			}

			// Remove selections
			prevSelectionIdInReaction.clear();
		}

		void Tarot::addLastParInReaction(const std::string &coreId, const std::string &threadScope, const std::string &prevParId) {
			if (!prevParId.empty() && threadScope.compare("main") != 0) {
				Tarot::lastParIdInReaction[coreId][threadScope].insert(prevParId);
			}
		}

		void Tarot::addLastParIdInAbort(const std::string &coreId, const std::string &threadScope, const std::string &abortId, const std::string &prevParId) {
			if (!prevParId.empty()) {
				Tarot::lastParIdInAbort[coreId][threadScope][abortId] = prevParId;
			}
		}

		void Tarot::addLastParIdInIteration(const std::string &coreId, const std::string &threadScope, const std::string &iterationId, const std::string &prevParId) {
			if (!prevParId.empty() && threadScope.compare("main") != 0) {
				Tarot::lastParIdInIteration[coreId][threadScope][iterationId] = prevParId;
			}
		}

		void Tarot::addLastParIdInSelection(const std::string &coreId, const std::string &threadScope, const std::string &selectionId, const std::string &branchType, const std::string &prevParId) {
			if (!prevParId.empty() && threadScope.compare("main") != 0) {
				Tarot::lastParIdInSelection[coreId][threadScope][selectionId][branchType] = prevParId;
			}
		}

		void Tarot::addLastParIdInThread(const std::string &coreId, const std::string &threadScope, const std::string &prevParId) {
			if (!prevParId.empty() && threadScope.compare("main") != 0) {
				Tarot::lastParIdInThread[coreId][threadScope] = prevParId;
			}
		}

		// Scopes.
		void Tarot::addAbortScope(const std::string &abortId, const std::string &coreId, const std::string &parId) {
			// Save participating cores and par(...)s.
			Tarot::scopedAborts[abortId]["coreIds"].insert(coreId);
			Tarot::scopedAborts[abortId]["parIds"].insert(parId);
		}

		void Tarot::addIterationScope(const std::string &iterationId, const std::string &coreId, const std::string &parId) {
			// Save participating cores and par(...)s.
			Tarot::scopedIterations[iterationId]["coreIds"].insert(coreId);
			Tarot::scopedIterations[iterationId]["parIds"].insert(parId);
		}

		void Tarot::addSelectionScope(const std::string &selectionId, const std::string &branchType, const std::string &coreId, const std::string &parId) {
			// Save participating cores and par(...)s.
			Tarot::scopedSelections[selectionId][branchType]["coreIds"].insert(coreId);
			Tarot::scopedSelections[selectionId][branchType]["parIds"].insert(parId);
		}

		void Tarot::addAborts(const std::vector<std::pair<std::string, std::string> > &abortsWithPar, const std::string &parId) {
			// Save abort scopes with enclosed par(...).
			if (!parId.empty() && abortsWithPar.size() > 0) {
				Tarot::aborts[parId] = abortsWithPar;
			}
		}

		// Prepare tasks.
		void Tarot::linkParThreads(void) {
			for (std::map<std::string, Thread *>::const_iterator thread = Tarot::threads.begin(); thread != Tarot::threads.end(); ++thread) {
				thread->second->linkParThreads();
			}
		}

		void Tarot::findThreadRecursion(void) {
			std::set<std::string> visitedThreadIds;
			Tarot::threads["main"]->findThreadRecursion(visitedThreadIds);
		}

		void Tarot::splitByCoreId(const std::set<std::string> &coreIds) {
			for (std::set<std::string>::const_iterator coreId = coreIds.begin(); coreId != coreIds.end(); ++coreId) {
				// Copy nodes relevant to core.
				if (Tarot::threads["main"]->hasRecursive("Thread", *coreId) || Tarot::threads["main"]->hasRecursive("Par", *coreId)) {
					Thread *threadByCoreId = new Thread(*Tarot::threads["main"], "Thread", *coreId);
					Tarot::tarotByCoreId[*coreId] = threadByCoreId;
				}
			}
		}

		void Tarot::findNextPar(void) {
			for (std::map<std::string, Thread *>::const_iterator tarot = Tarot::tarotByCoreId.begin(); tarot != Tarot::tarotByCoreId.end(); ++tarot) {
				std::string prevParId = "";
				std::vector<std::string> prevAbortId;
				std::vector<std::string> prevIterationId;
				std::vector<std::map<std::string, std::string> > prevSelectionId;

				tarot->second->findNextPar(prevParId, prevAbortId, prevIterationId, prevSelectionId, "main");
			}
		}

		void Tarot::findNextParInReaction(void) {
			for (std::map<std::string, Thread *>::const_iterator tarot = Tarot::tarotByCoreId.begin(); tarot != Tarot::tarotByCoreId.end(); ++tarot) {
				std::string prevParId = "";
				std::vector<std::string> prevAbortIdInReaction;
				std::vector<std::string> prevIterationIdInReaction;
				std::vector<std::map<std::string, std::string> > prevSelectionIdInReaction;

				tarot->second->findNextParInReaction(prevParId, prevAbortIdInReaction, prevIterationIdInReaction, prevSelectionIdInReaction, "main");
			}
		}

		void Tarot::findLastPar(void) {
			for (std::map<std::string, Thread *>::const_iterator tarot = Tarot::tarotByCoreId.begin(); tarot != Tarot::tarotByCoreId.end(); ++tarot) {
				std::string prevParId = "";

				tarot->second->findLastPar(prevParId, "main");
			}
		}

		// Process tasks.
		void Tarot::extractParInformation(void) {
			for (std::map<std::string, Thread *>::const_iterator tarot = Tarot::tarotByCoreId.begin(); tarot != Tarot::tarotByCoreId.end(); ++tarot) {
				tarot->second->setParCore();
			}

			std::vector<Node *> abortNodes;
			Tarot::threads["main"]->extractParInformation(abortNodes, "");

			std::vector<std::string> aborts;
			std::vector<std::pair<std::string, std::string> > abortsWithPar;
			Tarot::threads["main"]->addAborts(aborts, abortsWithPar);
		}

		void Tarot::flatten(void) {
			std::vector<Node *> strongAborts;
			std::vector<Node *> weakAborts;
			std::vector<Node *> iterations;
			std::map<std::string, std::vector<Node *> > selections;
			for (std::map<std::string, Thread *>::const_iterator tarot = Tarot::tarotByCoreId.begin(); tarot != Tarot::tarotByCoreId.end(); ++tarot) {
				tarot->second->flatten(strongAborts, weakAborts, iterations, selections, "", "main");
			}
		}

		// Accessors
		const std::map<std::string, std::set<std::string> > Tarot::getControlVariables(void) {
			// Control variables for synchronisation each core.
			std::map<std::string, std::set<std::string> > controlVariables;

			for (std::map<std::string, std::map<std::string, std::map<std::string, std::set<std::string> > > >::iterator core = Tarot::reactionEnds.begin(); core != Tarot::reactionEnds.end(); ++core) {
				for (std::map<std::string, std::map<std::string, std::set<std::string> > >::iterator par = core->second.begin(); par != core->second.end(); ++par) {
					std::string threadScope = *(par->second["threadScope"].begin());
					controlVariables[threadScope].insert(core->first);
				}
			}

			return controlVariables;
		}

		const std::set<std::string> Tarot::getParCores(const std::string &threadScope, const std::string &parId) {
			return Tarot::parCores[threadScope][parId];
		}

		const std::map<std::string, std::map<std::string, std::set<std::string> > > Tarot::getInactiveParCores(void) {
			return Tarot::inactiveParCores;
		}

		const std::map<std::string, std::map<std::string, std::set<std::string> > > Tarot::getHandlers(void) {
			return Tarot::handlers;
		}

		const std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, std::string> > > > Tarot::getLinkedLists(const std::string &coreId) {
			return Tarot::linkedLists[coreId];
		}

		const std::vector<std::pair<std::string, std::string> > Tarot::getLinkedList(const std::string &coreId, const std::string &threadScope, const std::string &parId) {
			return Tarot::linkedLists[coreId][threadScope][parId];
		}

		const std::map<std::string, bool> Tarot::getReactionStarts(const std::string &coreId) {
			return Tarot::reactionStarts[coreId];
		}

		const std::map<std::string, std::map<std::string, std::set<std::string> > > Tarot::getReactionEnds(const std::string &coreId) {
			return Tarot::reactionEnds[coreId];
		}

		const std::map<std::string, std::map<std::string, std::set<std::string> > > Tarot::getScopedReactionEnds(const std::string &coreId) {
			// map<threadScope, map<[coreIds, isMaster, parIds], set<values> > >
			std::map<std::string, std::map<std::string, std::set<std::string> > > scopedReactionEnds;

			// Re-arrange based on thread scope.
			std::map<std::string, std::map<std::string, std::set<std::string> > > reactionEnds = Tarot::getReactionEnds(coreId);
			for (std::map<std::string, std::map<std::string, std::set<std::string> > >::const_iterator parId = reactionEnds.begin(); parId != reactionEnds.end(); ++parId) {
				const std::string threadScope = *parId->second.find("threadScope")->second.begin();
				const bool isMaster = parId->second.find("isMaster") != parId->second.end();

				if (isMaster) {
					scopedReactionEnds[threadScope]["isMaster"].insert("true");

					const std::set<std::string> coreIds = parId->second.find("coreIds")->second;
					scopedReactionEnds[threadScope]["coreIds"].insert(coreIds.begin(), coreIds.end());
				}

				scopedReactionEnds[threadScope]["parIds"].insert(parId->first);
			}

			return scopedReactionEnds;
		}

		const std::map<std::string, std::set<std::string> > Tarot::getScopedReactionEnd(const std::string &threadScope, const std::string &coreId) {
			const std::map<std::string, std::map<std::string, std::set<std::string> > > scopedReactionEnds = Tarot::getScopedReactionEnds(coreId);
			if (scopedReactionEnds.find(threadScope) != scopedReactionEnds.end()) {
				return scopedReactionEnds.find(threadScope)->second;
			}
			
			return std::map<std::string, std::set<std::string> >();
		}

		const std::map<std::string, std::set<std::string> > Tarot::getReactionEnds(const std::string &coreId, const std::string &parId) {
			return Tarot::reactionEnds[coreId][parId];
		}

		const std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > Tarot::getAbortChecks(const std::string &coreId) {
			return Tarot::abortChecks[coreId];
		}

		const std::string Tarot::getNextParAfterPar(const std::string &coreId, const std::string &threadScope, const std::string &parId) {
			if (Tarot::nextParAfterPar[coreId].find(threadScope) != Tarot::nextParAfterPar[coreId].end()) {
				if (Tarot::nextParAfterPar[coreId][threadScope].find(parId) != Tarot::nextParAfterPar[coreId][threadScope].end()) {
					return Tarot::nextParAfterPar[coreId][threadScope][parId];
				}
			}
			return "";
		}

		const std::string Tarot::getNextParAfterAbort(const std::string &coreId, const std::string &threadScope, const std::string &abortId) {
			if (Tarot::nextParAfterAbort[coreId].find(threadScope) != Tarot::nextParAfterAbort[coreId].end()) {
				if (Tarot::nextParAfterAbort[coreId][threadScope].find(abortId) != Tarot::nextParAfterAbort[coreId][threadScope].end()) {
					return Tarot::nextParAfterAbort[coreId][threadScope][abortId];
				}
			}
			return "";
		}

		const std::string Tarot::getNextParAfterIteration(const std::string &coreId, const std::string &threadScope, const std::string &iterationId) {
			if (Tarot::nextParAfterIteration[coreId].find(threadScope) != Tarot::nextParAfterIteration[coreId].end()) {
				if (Tarot::nextParAfterIteration[coreId][threadScope].find(iterationId) != Tarot::nextParAfterIteration[coreId][threadScope].end()) {
					return Tarot::nextParAfterIteration[coreId][threadScope][iterationId];
				}
			}
			return "";
		}

		const std::string Tarot::getNextParAfterSelection(const std::string &coreId, const std::string &threadScope, const std::string &selectionId, const std::string &branchType) {
			if (Tarot::nextParAfterSelection[coreId].find(threadScope) != Tarot::nextParAfterSelection[coreId].end()) {
				if (Tarot::nextParAfterSelection[coreId][threadScope].find(selectionId) != Tarot::nextParAfterSelection[coreId][threadScope].end()) {
					if (Tarot::nextParAfterSelection[coreId][threadScope][selectionId].find(branchType) != Tarot::nextParAfterSelection[coreId][threadScope][selectionId].end()) {
						return Tarot::nextParAfterSelection[coreId][threadScope][selectionId][branchType];
					}
				}
			}
			return "";
		}

		const std::string Tarot::getNextParAfterAbortInReaction(const std::string &coreId, const std::string &threadScope, const std::string &abortId) {
			if (Tarot::nextParAfterAbortInReaction[coreId].find(threadScope) != Tarot::nextParAfterAbortInReaction[coreId].end()) {
				if (Tarot::nextParAfterAbortInReaction[coreId][threadScope].find(abortId) != Tarot::nextParAfterAbortInReaction[coreId][threadScope].end()) {
					return Tarot::nextParAfterAbortInReaction[coreId][threadScope][abortId];
				}
			}
			return "";
		}

		const std::string Tarot::getNextParAfterIterationInReaction(const std::string &coreId, const std::string &threadScope, const std::string &iterationId) {
			if (Tarot::nextParAfterIterationInReaction[coreId].find(threadScope) != Tarot::nextParAfterIterationInReaction[coreId].end()) {
				if (Tarot::nextParAfterIterationInReaction[coreId][threadScope].find(iterationId) != Tarot::nextParAfterIterationInReaction[coreId][threadScope].end()) {
					return Tarot::nextParAfterIterationInReaction[coreId][threadScope][iterationId];
				}
			}
			return "";
		}

		const std::string Tarot::getNextParAfterSelectionInReaction(const std::string &coreId, const std::string &threadScope, const std::string &selectionId, const std::string &branchType) {
			if (Tarot::nextParAfterSelectionInReaction[coreId].find(threadScope) != Tarot::nextParAfterSelectionInReaction[coreId].end()) {
				if (Tarot::nextParAfterSelectionInReaction[coreId][threadScope].find(selectionId) != Tarot::nextParAfterSelectionInReaction[coreId][threadScope].end()) {
					if (Tarot::nextParAfterSelectionInReaction[coreId][threadScope][selectionId].find(branchType) != Tarot::nextParAfterSelectionInReaction[coreId][threadScope][selectionId].end()) {
						return Tarot::nextParAfterSelectionInReaction[coreId][threadScope][selectionId][branchType];
					}
				}
			}
			return "";
		}

		const std::string Tarot::getLastParIdInAbort(const std::string &abortId, const std::string &threadScope, const std::string &coreId) {
			if (Tarot::lastParIdInAbort[coreId].find(threadScope) != Tarot::lastParIdInAbort[coreId].end()) {
				if (Tarot::lastParIdInAbort[coreId][threadScope].find(abortId) != Tarot::lastParIdInAbort[coreId][threadScope].end()) {
					return Tarot::lastParIdInAbort[coreId][threadScope][abortId];
				}
			}

			return "";
		}

		const std::string Tarot::getLastParIdInIteration(const std::string &iterationId, const std::string &threadScope, const std::string &coreId) {
			if (Tarot::lastParIdInIteration[coreId].find(threadScope) != Tarot::lastParIdInIteration[coreId].end()) {
				if (Tarot::lastParIdInIteration[coreId][threadScope].find(iterationId) != Tarot::lastParIdInIteration[coreId][threadScope].end()) {
					return Tarot::lastParIdInIteration[coreId][threadScope][iterationId];
				}
			}

			return "";
		}

		const std::string Tarot::getLastParIdInSelection(const std::string &selectionId, const std::string &branchType, const std::string &threadScope, const std::string &coreId) {
			if (Tarot::lastParIdInSelection[coreId].find(threadScope) != Tarot::lastParIdInSelection[coreId].end()) {
				if (Tarot::lastParIdInSelection[coreId][threadScope].find(selectionId) != Tarot::lastParIdInSelection[coreId][threadScope].end()) {
					if (Tarot::lastParIdInSelection[coreId][threadScope][selectionId].find(branchType) != Tarot::lastParIdInSelection[coreId][threadScope][selectionId].end()) {
						return Tarot::lastParIdInSelection[coreId][threadScope][selectionId][branchType];
					}
				}
			}

			return "";
		}

		const std::map<std::string, std::map<std::string, std::string> > Tarot::getLastParIdInThread(void) {
			return Tarot::lastParIdInThread;
		}

		const std::string Tarot::getLastParIdInThread(const std::string &threadScope, const std::string &coreId) {
			if (Tarot::lastParIdInThread[coreId].find(threadScope) != Tarot::lastParIdInThread[coreId].end()) {
				return Tarot::lastParIdInThread[coreId][threadScope];
			}

			return "";
		}

		const bool Tarot::isLastParIdInThread(const std::string &threadScope, const std::string &coreId, const std::string &parId) {
			return Tarot::getLastParIdInThread(threadScope, coreId).compare(parId) == 0;
		}


		const std::map<std::string, std::map<std::string, std::set<std::string> > > Tarot::getScopedAborts(void) {
			return scopedAborts;
		}

		const std::set<std::string> Tarot::getScopedAborts(const std::string &abortId, const std::string &information) {
			if (Tarot::scopedAborts.find(abortId) != Tarot::scopedAborts.end()) {
				return Tarot::scopedAborts[abortId][information];
			}

			return std::set<std::string>();
		}


		const std::map<std::string, std::map<std::string, std::set<std::string> > > Tarot::getScopedIterations(void) {
			return Tarot::scopedIterations;
		}

		const std::set<std::string> Tarot::getScopedIterations(const std::string &iterationId, const std::string &information) {
			if (Tarot::scopedIterations.find(iterationId) != Tarot::scopedIterations.end()) {
				return Tarot::scopedIterations[iterationId][information];
			}

			return std::set<std::string>();
		}

		const std::map<std::string, std::map<std::string, std::map<std::string, std::set<std::string> > > > Tarot::getScopedSelections(void) {
			return Tarot::scopedSelections;
		}

		const std::set<std::string> Tarot::getScopedSelections(const std::string &selectionId, const std::string &branchType, const std::string &information) {
			if (Tarot::scopedSelections.find(selectionId) != Tarot::scopedSelections.end()) {
				if (Tarot::scopedSelections[selectionId].find(branchType) != Tarot::scopedSelections[selectionId].end()) {
					return Tarot::scopedSelections[selectionId][branchType][information];
				}
			}

			return std::set<std::string>();
		}

		const std::vector<std::pair<std::string, std::string> > Tarot::getAborts(const std::string &parId) {
			if (Tarot::aborts.find(parId) != Tarot::aborts.end()){
				return Tarot::aborts[parId];
			}
			return std::vector<std::pair<std::string, std::string> >();
		}


		const std::string Tarot::toString(void) {
			std::ostringstream output;

			output << "========================" << std::endl;
			output << "tarot::Tarot::toString()" << std::endl;
			output << "========================" << std::endl;

			output << "Full tarot:" << std::endl;
			output << "-----------" << std::endl;
			Tab::setLevel(1);
			output << *Tarot::threads["main"] << std::endl;
			output << std::endl;

			output << "Tarot by coreId:" << std::endl;
			output << "----------------" << std::endl;
			for (std::map<std::string, Thread *>::const_iterator tarot = Tarot::tarotByCoreId.begin(); tarot != Tarot::tarotByCoreId.end(); ++tarot) {
				Tab::setLevel(2);
				output << "\tcore" << tarot->first << ':' << std::endl;
				output << "\t-------" << std::endl;
				output << *(tarot->second) << std::endl;
			}
			output << std::endl;

			if (Tarot::parCores.size() > 0) {
				output << "par(...) statements with core allocation:" << std::endl;
				output << "-----------------------------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::set<std::string> > >::const_iterator threadScope = Tarot::parCores.begin(); threadScope != Tarot::parCores.end(); ++threadScope) {

					output << "\tThread " << threadScope->first << "__thread:" << std::endl;
					for (std::map<std::string, std::set<std::string> >::const_iterator parId = threadScope->second.begin(); parId != threadScope->second.end(); ++parId) {

						output << "\t\t" << parId->first << ':' << std::endl;
						for (std::set<std::string>::const_iterator coreId = parId->second.begin(); coreId != parId->second.end(); ++coreId) {
							output << "\t\t* core" << *coreId << std::endl;
						}
						output << std::endl;
					}
				}
				output << std::endl;
			}

			if (Tarot::activeParCores.size() > 0) {
				output << "par(...) statements with active cores:" << std::endl;
				output << "--------------------------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::set<std::string> > >::const_iterator threadScope = Tarot::activeParCores.begin(); threadScope != Tarot::activeParCores.end(); ++threadScope) {

					output << "\tThread " << threadScope->first << "__thread:" << std::endl;
					for (std::map<std::string, std::set<std::string> >::const_iterator parId = threadScope->second.begin(); parId != threadScope->second.end(); ++parId) {

						output << "\t\t" << parId->first << ':' << std::endl;
						for (std::set<std::string>::const_iterator coreId = parId->second.begin(); coreId != parId->second.end(); ++coreId) {
							output << "\t\t* core" << *coreId << std::endl;
						}
						output << std::endl;
					}
				}
				output << std::endl;
			}

			if (Tarot::inactiveParCores.size() > 0) {
				output << "par(...) statements with inactive cores:" << std::endl;
				output << "----------------------------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::set<std::string> > >::const_iterator threadScope = Tarot::inactiveParCores.begin(); threadScope != Tarot::inactiveParCores.end(); ++threadScope) {

					output << "\tThread " << threadScope->first << "__thread:" << std::endl;
					for (std::map<std::string, std::set<std::string> >::const_iterator parId = threadScope->second.begin(); parId != threadScope->second.end(); ++parId) {

						output << "\t\t" << parId->first << ':' << std::endl;
						for (std::set<std::string>::const_iterator coreId = parId->second.begin(); coreId != parId->second.end(); ++coreId) {
							output << "\t\t* core" << *coreId << std::endl;
						}
						output << std::endl;
					}
				}
				output << std::endl;
			}

			if (Tarot::reactionStarts.size() > 0) {
				output << "Reaction starts:" << std::endl;
				output << "----------------" << std::endl;
				for (std::map<std::string, std::map<std::string, bool> >::const_iterator reactionStart = Tarot::reactionStarts.begin(); reactionStart != Tarot::reactionStarts.end(); ++reactionStart) {

					output << "\tcore" << reactionStart->first << ':' << std::endl;
					for (std::map<std::string, bool>::const_iterator threadScope = reactionStart->second.begin(); threadScope != reactionStart->second.end(); ++threadScope) {

						output << "\t\t" << threadScope->first << ": " << (threadScope->second ? "Master" : "Slave") << std::endl;
					}
					output << std::endl;
				}
				output << std::endl;
			}

			if (Tarot::reactionEnds.size() > 0) {
				output << "Reaction ends:" << std::endl;
				output << "--------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::map<std::string, std::set<std::string> > > >::const_iterator reactionEnd = Tarot::reactionEnds.begin(); reactionEnd != Tarot::reactionEnds.end(); ++reactionEnd) {

					output << "\tcore" << reactionEnd->first << ':' << std::endl;
					for (std::map<std::string, std::map<std::string, std::set<std::string> > >::const_iterator parHandler = reactionEnd->second.begin(); parHandler != reactionEnd->second.end(); ++parHandler) {

						output << "\t\t" << parHandler->first << ':' << std::endl;
						for (std::map<std::string, std::set<std::string> >::const_iterator information = parHandler->second.begin(); information != parHandler->second.end(); ++information) {

							output << "\t\t\t" << information->first << ':' << std::endl;
							for (std::set<std::string>::const_iterator element = information->second.begin(); element != information->second.end(); ++element) {
								output << "\t\t\t* " << *element << std::endl;
							}
							output << std::endl;
						}
					}
				}
				output << std::endl;
			}

			if (Tarot::handlers.size() > 0) {
				output << "Par(...) handlers:" << std::endl;
				output << "------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::set<std::string> > >::const_iterator parHandler = Tarot::handlers.begin(); parHandler != Tarot::handlers.end(); ++parHandler) {

					output << "\t" << parHandler->first << ':' << std::endl;
					for (std::map<std::string, std::set<std::string> >::const_reverse_iterator handlerType = parHandler->second.rbegin(); handlerType != parHandler->second.rend(); ++handlerType) {
						for (std::set<std::string>::const_iterator handler = handlerType->second.begin(); handler != handlerType->second.end(); ++handler) {
							output << "\t* " << *handler << std::endl;
						}
					}
					output << std::endl;
				}
				output << std::endl;
			}

			if (Tarot::abortChecks.size() > 0) {
				output << "Abort checks:" << std::endl;
				output << "-------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > >::const_iterator abortCheck = Tarot::abortChecks.begin(); abortCheck != Tarot::abortChecks.end(); ++abortCheck) {

					output << "\tcore" << abortCheck->first << ':' << std::endl;
					for (std::map<std::string, std::map<std::string, std::map<std::string, std::string> > >::const_iterator parScope = abortCheck->second.begin(); parScope != abortCheck->second.end(); ++parScope) {

						output << "\t\t" << parScope->first << ':' << std::endl;
						for (std::map<std::string, std::map<std::string, std::string> >::const_iterator type = parScope->second.begin(); type != parScope->second.end(); ++type) {

							output << "\t\t\t" << type->first << ':' << std::endl;
							for (std::map<std::string, std::string>::const_iterator abort = type->second.begin(); abort != type->second.end(); ++abort) {
								output << "\t\t\t* " << abort->first << '(' << abort->second << ')' << std::endl;
							}
							output << std::endl;
						}
					}
				}
				output << std::endl;
			}

			if (Tarot::linkedLists.size() > 0) {
				output << "Linked lists:" << std::endl;
				output << "-------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, std::string> > > > >::const_iterator flattenedCoreResult = Tarot::linkedLists.begin(); flattenedCoreResult != Tarot::linkedLists.end(); ++flattenedCoreResult) {

					output << "\tcore" << flattenedCoreResult->first << ':' << std::endl;
					for (std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, std::string> > > >::const_iterator threadScope = flattenedCoreResult->second.begin(); threadScope != flattenedCoreResult->second.end(); ++threadScope) {

						output << "\t\tThread " << threadScope->first << "__thread linked lists:" << std::endl;
						for (std::map<std::string, std::vector<std::pair<std::string, std::string> > >::const_iterator parHandler = threadScope->second.begin(); parHandler != threadScope->second.end(); ++parHandler) {

							output << "\t\t\t" << parHandler->first << ':' << std::endl;
							for (std::vector<std::pair<std::string, std::string> >::const_iterator node = parHandler->second.begin(); node != parHandler->second.end(); ++node) {
								output << "\t\t\t* (" << node->first << ") " << node->second << std::endl;
							}
							output << std::endl;
						}
					}
				}
				output << std::endl;
			}

			if (Tarot::parThreadScope.size() > 0) {
				output << "par(...) handlers in thread scopes:" << std::endl;
				output << "-----------------------------------" << std::endl;
				for (std::map<std::string, std::string>::const_iterator parHandler = Tarot::parThreadScope.begin(); parHandler != Tarot::parThreadScope.end(); ++parHandler) {
					output << "\t" << parHandler->first << "\t" << parHandler->second << "__thread" << std::endl;
				}
				output << std::endl;
			}

			if (Tarot::nextParAfterPar.size() > 0) {
				output << "Next par(...) after par(...):" << std::endl;
				output << "-----------------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::map<std::string, std::string> > >::const_iterator coreId = Tarot::nextParAfterPar.begin(); coreId != Tarot::nextParAfterPar.end(); ++coreId) {

					output << "\tcore" << coreId->first << ':' << std::endl;
					for (std::map<std::string, std::map<std::string, std::string> >::const_iterator threadScope = coreId->second.begin(); threadScope != coreId->second.end(); ++threadScope) {

						output << "\t\tThread " << threadScope->first << ':' << std::endl;
						for (std::map<std::string, std::string>::const_iterator parId = threadScope->second.begin(); parId != threadScope->second.end(); ++parId) {
							output << "\t\t* " << parId->first << " -> " << parId->second << std::endl;
						}
						output << std::endl;
					}
				}
				output << std::endl;
			}

			if (Tarot::lastParIdInReaction.size() > 0) {
				output << "Last par(...)s in each thread's reaction:" << std::endl;
				output << "-----------------------------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::set<std::string> > >::iterator coreId = Tarot::lastParIdInReaction.begin(); coreId != Tarot::lastParIdInReaction.end(); ++coreId) {

					output << "\tcore" << coreId->first << ':' << std::endl;
					for (std::map<std::string, std::set<std::string> >::iterator threadScope = coreId->second.begin(); threadScope != coreId->second.end(); ++threadScope) {

						output << "\t\tThread scope: " << threadScope->first << std::endl;
						for (std::set<std::string>::iterator parId = threadScope->second.begin(); parId != threadScope->second.end(); ++parId) {
							output << "\t\t* " << *parId << std::endl;
						}
						output << std::endl;
					}
				}
				output << std::endl;
			}

			if (Tarot::lastParIdInAbort.size() > 0) {
				output << "Last par(...)s in each abort:" << std::endl;
				output << "-------------------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::map<std::string, std::string> > >::iterator coreId = Tarot::lastParIdInAbort.begin(); coreId != Tarot::lastParIdInAbort.end(); ++coreId) {

					output << "\tcore" << coreId->first << ':' << std::endl;
					for (std::map<std::string, std::map<std::string, std::string> >::iterator threadScope = coreId->second.begin(); threadScope != coreId->second.end(); ++threadScope) {

						output << "\t\tThread scope: " << threadScope->first << std::endl;
						for (std::map<std::string, std::string>::iterator abortId = threadScope->second.begin(); abortId != threadScope->second.end(); ++abortId) {
							output << "\t\t* " << abortId->first << "->" << abortId->second << std::endl;
						}
						output << std::endl;
					}
				}
				output << std::endl;
			}

			if (Tarot::lastParIdInIteration.size() > 0) {
				output << "Last par(...)s in each iteration:" << std::endl;
				output << "---------------------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::map<std::string, std::string> > >::iterator coreId = Tarot::lastParIdInIteration.begin(); coreId != Tarot::lastParIdInIteration.end(); ++coreId) {

					output << "\tcore" << coreId->first << ':' << std::endl;
					for (std::map<std::string, std::map<std::string, std::string> >::iterator threadScope = coreId->second.begin(); threadScope != coreId->second.end(); ++threadScope) {

						output << "\t\tThread scope: " << threadScope->first << std::endl;
						for (std::map<std::string, std::string>::iterator iterationId = threadScope->second.begin(); iterationId != threadScope->second.end(); ++iterationId) {
							output << "\t\t* " << iterationId->first << "->" << iterationId->second << std::endl;
						}
						output << std::endl;
					}
				}
				output << std::endl;
			}

			if (Tarot::lastParIdInSelection.size() > 0) {
				output << "Last par(...)s in each selection:" << std::endl;
				output << "---------------------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > >::iterator coreId = Tarot::lastParIdInSelection.begin(); coreId != Tarot::lastParIdInSelection.end(); ++coreId) {

					output << "\tcore" << coreId->first << ':' << std::endl;
					for (std::map<std::string, std::map<std::string, std::map<std::string, std::string> > >::iterator threadScope = coreId->second.begin(); threadScope != coreId->second.end(); ++threadScope) {

						output << "\t\tThread scope: " << threadScope->first << std::endl;
						for (std::map<std::string, std::map<std::string, std::string> >::iterator selectionId = threadScope->second.begin(); selectionId != threadScope->second.end(); ++selectionId) {

							output << "\t\t\t" << selectionId->first << ':' << std::endl;
							for (std::map<std::string, std::string>::iterator branchType = selectionId->second.begin(); branchType != selectionId->second.end(); ++branchType) {
								output << "\t\t\t* " << branchType->first << "->" << branchType->second << std::endl;
							}
							output << std::endl;
						}
					}
				}
				output << std::endl;
			}

			if (Tarot::lastParIdInThread.size() > 0) {
				output << "Last par(...) in each thread:" << std::endl;
				output << "------------------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::string> >::iterator coreId = Tarot::lastParIdInThread.begin(); coreId != Tarot::lastParIdInThread.end(); ++coreId) {

					output << "\tcore" << coreId->first << ':' << std::endl;
					for (std::map<std::string, std::string>::iterator threadScope = coreId->second.begin(); threadScope != coreId->second.end(); ++threadScope) {
						output << "\t\tThread scope: " << threadScope->first << std::endl;
						output << "\t\t* " << threadScope->second << std::endl;
						output << std::endl;
					}
				}
				output << std::endl;
			}

			if (Tarot::nextParAfterAbort.size() > 0) {
				output << "Next par(...) after abort:" << std::endl;
				output << "--------------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::map<std::string, std::string> > >::const_iterator coreId = Tarot::nextParAfterAbort.begin(); coreId != Tarot::nextParAfterAbort.end(); ++coreId) {

					output << "\tcore" << coreId->first << ':' << std::endl;
					for (std::map<std::string, std::map<std::string, std::string> >::const_iterator threadScope = coreId->second.begin(); threadScope != coreId->second.end(); ++threadScope) {

						output << "\t\tThread " << threadScope->first << ':' << std::endl;
						for (std::map<std::string, std::string>::const_iterator abortId = threadScope->second.begin(); abortId != threadScope->second.end(); ++abortId) {
							output << "\t\t* " << abortId->first << " -> " << abortId->second << std::endl;
						}
						output << std::endl;
					}
				}
				output << std::endl;
			}

			if (Tarot::nextParAfterIteration.size() > 0) {
				output << "Next par(...) after iteration:" << std::endl;
				output << "------------------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::map<std::string, std::string> > >::const_iterator coreId = Tarot::nextParAfterIteration.begin(); coreId != Tarot::nextParAfterIteration.end(); ++coreId) {

					output << "\tcore" << coreId->first << ':' << std::endl;
					for (std::map<std::string, std::map<std::string, std::string> >::const_iterator threadScope = coreId->second.begin(); threadScope != coreId->second.end(); ++threadScope) {

						output << "\t\tThread " << threadScope->first << ':' << std::endl;
						for (std::map<std::string, std::string>::const_iterator iterationId = threadScope->second.begin(); iterationId != threadScope->second.end(); ++iterationId) {
							output << "\t\t* " << iterationId->first << " -> " << iterationId->second << std::endl;
						}
						output << std::endl;
					}
				}
				output << std::endl;
			}

			if (Tarot::nextParAfterSelection.size() > 0) {
				output << "Next par(...) after selection:" << std::endl;
				output << "------------------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > >::const_iterator coreId = Tarot::nextParAfterSelection.begin(); coreId != Tarot::nextParAfterSelection.end(); ++coreId) {

					output << "\tcore" << coreId->first << ':' << std::endl;
					for (std::map<std::string, std::map<std::string, std::map<std::string, std::string> > >::const_iterator threadScope = coreId->second.begin(); threadScope != coreId->second.end(); ++threadScope) {

						output << "\t\tThread " << threadScope->first << ':' << std::endl;
						for (std::map<std::string, std::map<std::string, std::string> >::const_iterator selectionId = threadScope->second.begin(); selectionId != threadScope->second.end(); ++selectionId) {

							output << "\t\t\t" << selectionId->first << ':' << std::endl;
							for (std::map<std::string, std::string>::const_reverse_iterator branchType = selectionId->second.rbegin(); branchType != selectionId->second.rend(); ++branchType) {
								output << "\t\t\t* " << branchType->first << " -> " << branchType->second << std::endl;
							}
							output << std::endl;
						}
					}
				}
				output << std::endl;
			}

			if (Tarot::nextParAfterAbortInReaction.size() > 0) {
				output << "Next par(...) after abort in reaction:" << std::endl;
				output << "--------------------------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::map<std::string, std::string> > >::const_iterator coreId = Tarot::nextParAfterAbortInReaction.begin(); coreId != Tarot::nextParAfterAbortInReaction.end(); ++coreId) {

					output << "\tcore" << coreId->first << ':' << std::endl;
					for (std::map<std::string, std::map<std::string, std::string> >::const_iterator threadScope = coreId->second.begin(); threadScope != coreId->second.end(); ++threadScope) {

						output << "\t\tThread " << threadScope->first << ':' << std::endl;
						for (std::map<std::string, std::string>::const_iterator abortId = threadScope->second.begin(); abortId != threadScope->second.end(); ++abortId) {
							output << "\t\t* " << abortId->first << " -> " << abortId->second << std::endl;
						}
						output << std::endl;
					}
				}
				output << std::endl;
			}

			if (Tarot::nextParAfterIterationInReaction.size() > 0) {
				output << "Next par(...) after iteration in reaction:" << std::endl;
				output << "------------------------------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::map<std::string, std::string> > >::const_iterator coreId = Tarot::nextParAfterIterationInReaction.begin(); coreId != Tarot::nextParAfterIterationInReaction.end(); ++coreId) {

					output << "\tcore" << coreId->first << ':' << std::endl;
					for (std::map<std::string, std::map<std::string, std::string> >::const_iterator threadScope = coreId->second.begin(); threadScope != coreId->second.end(); ++threadScope) {

						output << "\t\tThread " << threadScope->first << ':' << std::endl;
						for (std::map<std::string, std::string>::const_iterator iterationId = threadScope->second.begin(); iterationId != threadScope->second.end(); ++iterationId) {
							output << "\t\t* " << iterationId->first << " -> " << iterationId->second << std::endl;
						}
						output << std::endl;
					}
				}
				output << std::endl;
			}

			if (Tarot::nextParAfterSelectionInReaction.size() > 0) {
				output << "Next par(...) after selection in reaction:" << std::endl;
				output << "------------------------------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::string> > > >::const_iterator coreId = Tarot::nextParAfterSelectionInReaction.begin(); coreId != Tarot::nextParAfterSelectionInReaction.end(); ++coreId) {

					output << "\tcore" << coreId->first << ':' << std::endl;
					for (std::map<std::string, std::map<std::string, std::map<std::string, std::string> > >::const_iterator threadScope = coreId->second.begin(); threadScope != coreId->second.end(); ++threadScope) {

						output << "\t\tThread " << threadScope->first << ':' << std::endl;
						for (std::map<std::string, std::map<std::string, std::string> >::const_iterator selectionId = threadScope->second.begin(); selectionId != threadScope->second.end(); ++selectionId) {

							output << "\t\t\t" << selectionId->first << ':' << std::endl;
							for (std::map<std::string, std::string>::const_reverse_iterator branchType = selectionId->second.rbegin(); branchType != selectionId->second.rend(); ++branchType) {
								output << "\t\t\t* " << branchType->first << " -> " << branchType->second << std::endl;
							}
							output << std::endl;
						}
					}
				}
				output << std::endl;
			}

			if (Tarot::scopedAborts.size() > 0) {
				output << "Scoped aborts:" << std::endl;
				output << "--------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::set<std::string> > >::iterator abortId = Tarot::scopedAborts.begin(); abortId != Tarot::scopedAborts.end(); ++abortId) {

					output << '\t' << abortId->first << ':' << std::endl;
					for (std::map<std::string, std::set<std::string> >::iterator information = abortId->second.begin(); information != abortId->second.end(); ++information) {

						output << "\t\t" << information->first << ':' << std::endl;
						for (std::set<std::string>::iterator value = information->second.begin(); value != information->second.end(); ++value) {
							output << "\t\t* " << *value << std::endl;
						}
						output << std::endl;
					}
				}
				output << std::endl;
			}

			if (Tarot::scopedIterations.size() > 0) {
				output << "Scoped iterations:" << std::endl;
				output << "------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::set<std::string> > >::iterator iterationId = Tarot::scopedIterations.begin(); iterationId != Tarot::scopedIterations.end(); ++iterationId) {

					output << '\t' << iterationId->first << ':' << std::endl;
					for (std::map<std::string, std::set<std::string> >::iterator information = iterationId->second.begin(); information != iterationId->second.end(); ++information) {

						output << "\t\t" << information->first << ':' << std::endl;
						for (std::set<std::string>::iterator value = information->second.begin(); value != information->second.end(); ++value) {
							output << "\t\t* " << *value << std::endl;
						}
						output << std::endl;
					}
				}
				output << std::endl;
			}

			if (Tarot::scopedSelections.size() > 0) {
				output << "Scoped selections:" << std::endl;
				output << "------------------" << std::endl;
				for (std::map<std::string, std::map<std::string, std::map<std::string, std::set<std::string> > > >::iterator selectionId = Tarot::scopedSelections.begin(); selectionId != Tarot::scopedSelections.end(); ++selectionId) {

					output << '\t' << selectionId->first << ':' << std::endl;
					for (std::map<std::string, std::map<std::string, std::set<std::string> > >::iterator branchType = selectionId->second.begin(); branchType != selectionId->second.end(); ++branchType) {

						output << "\t\t" << branchType->first << ':' << std::endl;
						for (std::map<std::string, std::set<std::string> >::iterator information = branchType->second.begin(); information != branchType->second.end(); ++information) {

							output << "\t\t\t" << information->first << ':' << std::endl;
							for (std::set<std::string>::iterator value = information->second.begin(); value != information->second.end(); ++value) {
								output << "\t\t\t* " << *value << std::endl;
							}
							output << std::endl;
						}
					}
				}
				output << std::endl;
			}

			if (Tarot::aborts.size() > 0) {
				output << "Aborts around par(...):" << std::endl;
				output << "-----------------------" << std::endl;
				for (std::map<std::string, std::vector<std::pair<std::string, std::string> > >::iterator parId = Tarot::aborts.begin(); parId != Tarot::aborts.end(); ++parId) {

					output << '\t' << parId->first << ':' << std::endl;
					for (std::vector<std::pair<std::string, std::string> >::iterator abort = parId->second.begin(); abort != parId->second.end(); ++abort) {
						output << "\t* " << abort->first << " (" << abort->second << ')' << std::endl;
					}
					output << std::endl;
				}
				output << std::endl;
			}

			return output.str();
		}
		

		const std::string Tarot::toDot(const std::string &fileName) {
			std::ostringstream output;

			Tab::setLevel(0);

			output << "digraph \"" << fileName << "\" {" << std::endl;
			Tab::indent("");
			output << Tab::toString() << "ordering = out" << std::endl;
			output << std::endl;
			output << Tab::toString() << "labeljust = l" << std::endl;
			output << Tab::toString() << "node [shape = box, fixedsize = true, height = 0.7, width = 1.1]" << std::endl;
			output << std::endl;
			output << Tab::toString() << "start [shape = plaintext, height = 0.4]" << std::endl;
			output << std::endl;

			std::string previousNode = "start";
			std::string edgeAttributes = " /*[headport = n, tailport = s]*/";
			std::ostringstream abortScope;
			Tarot::threads["main"]->toDot(output, previousNode, edgeAttributes, true, abortScope);

			output << Tab::toString() << previousNode << " -> end" << edgeAttributes << std::endl;
			output << std::endl;
			output << Tab::toString() << "end [shape = plaintext, height = 0.4]" << std::endl;

			output << Tab::toString() << '{' << std::endl;
			output << Tab::toString() << "\tedge[style = invis]" << std::endl;
			output << Tab::toString() << "\tstart -> " << Tarot::threads["main"]->getTopNode() << std::endl;
			output << Tab::toString() << '\t' << Tarot::threads["main"]->getBottomNode() << " -> end" << std::endl;
			output << Tab::toString() << '}' << std::endl;
			
			output << Tab::toString() << "label = \"" << fileName << ".forec\"" << std::endl;
			output << Tab::toString() << "labelloc = t" << std::endl;
			output << Tab::toString() << "labeljust = c" << std::endl;
			Tab::dedent();
			output << Tab::toString() << '}' << std::endl;

			return output.str();
		}

		const std::string Tarot::outputXml(const std::string &indent) {
			std::ostringstream output;
			
			output << indent << "<!-- Nested thread structure (Tarot.cpp::outputXml). -->" << std::endl;
			output << indent << "<tarot>" << std::endl;
			Tarot::threads["main"]->toXml(output, indent);
			output << indent << "</tarot>" << std::endl;


			output << indent << "<!-- Index of each par(...) in the par handlers of each core (Tarot.cpp::outputXml). -->" << std::endl;
			output << indent << "<parIndexes>" << std::endl;
			for (std::map<std::string, std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, std::string> > > > >::iterator core = Tarot::linkedLists.begin(); core != Tarot::linkedLists.end(); ++core) {
				output << indent << "\t<core id=\"" << core->first << "\">" << std::endl;
				
				for (std::map<std::string, std::map<std::string, std::vector<std::pair<std::string, std::string> > > >::iterator threadScope = core->second.begin(); threadScope != core->second.end(); ++threadScope) {
					output << indent << "\t\t<threadScope id=\"" << threadScope->first << "\">" << std::endl;
				
					for (std::map<std::string, std::vector<std::pair<std::string, std::string> > >::iterator parId = threadScope->second.begin(); parId != threadScope->second.end(); ++parId) {
						std::string parNumber = parId->first;
						parNumber.replace(parNumber.find("par"), std::string("par").length(), "");
						output << indent << "\t\t\t<par id=\"" << parNumber << "\" handlers=\"" << parId->second.size() << "\" />" << std::endl;
					}
					
					output << indent << "\t\t</threadScope>" << std::endl;
				}
				
				output << indent << "\t</core>" << std::endl;
			}
			
			output << indent << "</parIndexes>" << std::endl;
			
			
			output << indent << "<!-- Cores involved in executing each par(...) (Tarot.cpp::outputXml). -->" << std::endl;
			output << indent << "<allocatedParCores>" << std::endl;
			for (std::map<std::string, std::map<std::string, std::set<std::string> > >::const_iterator threadScope = Tarot::parCores.begin(); threadScope != Tarot::parCores.end(); ++threadScope) {
				for (std::map<std::string, std::set<std::string> >::const_iterator parId = threadScope->second.begin(); parId != threadScope->second.end(); ++parId) {
					if (parId->first.compare("all") != 0) {
						std::string parNumber = parId->first;
						parNumber.replace(parNumber.find("par"), std::string("par").length(), "");
						output << indent << "\t<par id=\"" << parNumber << "\">" << std::endl;
					
						for (std::set<std::string>::const_iterator coreId = parId->second.begin(); coreId != parId->second.end(); ++coreId) {
							output << indent << "\t\t<core id=\"" << *coreId << "\" />" << std::endl;
						}
					
						output << indent << "\t</par>" << std::endl;
					}
				}
			}
			
			output << indent << "</allocatedParCores>" << std::endl;
			
			
			output << indent << "<!-- Cores involved in executing all the par(...)s in each thread (Tarot.cpp::outputXml). -->" << std::endl;
			output << indent << "<activeParCores>" << std::endl;
			for (std::map<std::string, std::map<std::string, std::set<std::string> > >::const_iterator threadScope = Tarot::parCores.begin(); threadScope != Tarot::parCores.end(); ++threadScope) {
				output << indent << "\t<thread id=\"" << threadScope->first << "\">" << std::endl;
				
				std::set<std::string> coreIds = threadScope->second.find("all")->second;
				for (std::set<std::string>::const_iterator coreId = coreIds.begin(); coreId != coreIds.end(); ++coreId) {
					output << indent << "\t\t<core id=\"" << *coreId << "\" />" << std::endl;
				}
				
				output << indent << "\t</thread>" << std::endl;
			}

			output << indent << "</activeParCores>" << std::endl;


			return output.str();
		}
		
	}
}


