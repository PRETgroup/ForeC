/*
 *  PauseStatement.cpp
 *
 *
 *  Created by Eugene Kin Chee Yip on 24/12/10.
 *  Copyright 2010 Potential Publishers. All rights reserved.
 *
 */

#include "PauseStatement.hpp"

#include "AbortStatement.hpp"
#include "ParStatement.hpp"
#include "PrimaryExpression.hpp"

#include "../tarot/Tarot.hpp"
#include "../tarot/Node.hpp"
#include "../tarot/Pause.hpp"

#include "../tools/Abort.hpp"
#include "../tools/Multicore.hpp"
#include "../tools/Threading.hpp"
#include "../tools/SymbolTable.hpp"

namespace global {
	extern int debugLevel;
}

namespace forec {
	namespace ast {

		// Initialise static variable
		int PauseStatement::globalCount = 0;

		PauseStatement::PauseStatement(const std::string &variant) : Node("PauseStatement", variant, this->globalCount++) {
			
		}

		const std::string PauseStatement::getId(void) const {
			std::ostringstream name;
			name << "pause" << id;
			return name.str();
		}

		int PauseStatement::getCount(void) {
			return globalCount;
		}

		void PauseStatement::updateSymbolTable(const std::string &type, const bool isUsage, const bool isRead) {
			threadScope = tools::SymbolTable::getScopeName();
			aborts = tools::Abort::getCurrentAborts();
			parStatements = tools::Abort::getParStatements(threadScope);
		}

		void PauseStatement::createTarot(const std::string &threadScope, tarot::Node &tarotNode) {
			tarot::Pause *pauseTarot = new tarot::Pause(threadScope, this);
			tarotNode.append(*pauseTarot);
		}

		const Node::Instantaneous PauseStatement::willPause(const bool requireBothBranches) {
			instantaneous.pauses = true;
			instantaneous.breaks = false;
			instantaneous.continues = false;
			instantaneous.returns = false;
			
			return instantaneous;
		}

		void PauseStatement::prettyPrint(std::ostream &output) {
			std::set<std::string> parStatementsString;
			for (std::set<ParStatement *>::const_iterator par = parStatements.begin(); par != parStatements.end(); ++par) {
				parStatementsString.insert((*par)->getId());
			}

			std::vector<AbortStatement *> weakAborts;
			std::vector<AbortStatement *> strongAborts;
			for (std::vector<AbortStatement *>::const_iterator abort = aborts.begin(); abort != aborts.end(); ++abort) {
				if ((*abort)->isVariant("weak")) {
					weakAborts.push_back(*abort);
				} else {
					strongAborts.push_back(*abort);
				}
			}
			
			if (weakAborts.size() > 0) {
				output << "// Weak aborts:" << std::endl;
				for (std::vector<AbortStatement *>::const_reverse_iterator abort = weakAborts.rbegin(); abort != weakAborts.rend(); ++abort) {
					output << "// forec:statement:abort:" <<  (*abort)->getId() << ":start" << std::endl;
					output << tools::Tab::toString() << "if (" << (*abort)->getCondition(false) << ") {" << std::endl;
					tools::Tab::indent();
					output << tools::Tab::toString() << "goto abortEnd_" << (*abort)->getId() << ';' << std::endl;
					tools::Tab::dedent();
					output << tools::Tab::toString() << '}' << std::endl;
					output << tools::Tab::toString() << "// forec:statement:abort:" <<  (*abort)->getId() << ":end" << std::endl;
				}
				output << tools::Tab::toString();
			}
			
			output << "// pause;" << std::endl;
			
			// Update the global projections of the local copies of shared variables that may have been defined.
			std::ostringstream sharedOutputEnd;
			const std::map<forec::ast::PrimaryExpression *, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > indirectParallelThreadDef = tools::SymbolTable::getIndirectParallelThread(false, true, threadScope);
			for (std::map<forec::ast::PrimaryExpression *, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > >::const_iterator variable = indirectParallelThreadDef.begin(); variable != indirectParallelThreadDef.end(); ++variable) {
				if (variable->second.first == tools::SymbolTable::intermediate) {
					sharedOutputEnd << tools::Tab::toString() << *variable->first << "_copy_" << threadScope << " = " << *variable->first << "_copy_" << threadScope << "_local;" << std::endl;
				}
			}
			if (!sharedOutputEnd.str().empty()) {
				output << tools::Tab::toString() << "// Write the local copy of shared variables back to their global copy." << std::endl;
				output << sharedOutputEnd.str();
			}

			output << tools::Tab::toString() << "// forec:statement:pause:" << getId() << ":start" << std::endl;
			if (threadScope.compare("main") != 0) {
				output << tools::Tab::toString() << threadScope << "__thread.programCounter = &&pause" << getIdNumber() << ';' << std::endl;
				output << tools::Tab::toString() << "goto *" << threadScope << "__thread.nextThread -> programCounter;" << std::endl;
				output << tools::Tab::toString() << "pause" << getIdNumber() << ":;" << std::endl;
			}

			if (global::debugLevel > 0) {
				if (tools::Multicore::isArchitecture("microblaze") && threadScope.compare("main") == 0) {
					output << std::endl;
					output << tools::Tab::toString() << "// forec:scheduler:counter:start" << std::endl;
					output << tools::Tab::toString() << "// Stop counting the elapsed cycles for the current reaction." << std::endl;
					output << tools::Tab::toString() << "counterStop(FSL_COUNTER_ID);" << std::endl;
					output << tools::Tab::toString() << "counterRead(counter, FSL_COUNTER_ID);" << std::endl;
					output << tools::Tab::toString() << "counterDifference(counter);" << std::endl;
					output << tools::Tab::toString() << "counterMaximum(counter);" << std::endl;
					output << tools::Tab::toString() << "counterMinimum(counter);" << std::endl;
					output << tools::Tab::toString() << "counterAccumulate(counter);" << std::endl;
					output << tools::Tab::toString() << "counterAverage(counter);" << std::endl;
					output << tools::Tab::toString() << "xil_printf(\"%d Reaction time: %ld cycles, Min: %d, Avg: %d, Max: %d\\r\\n\", globalReactions, counter.difference, counter.min, counter.avg, counter.max);" << std::endl;
					output << tools::Tab::toString() << "globalReactions++;" << std::endl;
					output << tools::Tab::toString() << "// Restart the counting of elapsed cycles for the next reaction." << std::endl;
					output << tools::Tab::toString() << "counterReset(counter);" << std::endl;
					output << tools::Tab::toString() << "counterStart(counter, FSL_COUNTER_ID);" << std::endl;
					output << tools::Tab::toString() << "// forec:scheduler:counter:end" << std::endl;
				} else if (tools::Multicore::isArchitecture("ptarm") && threadScope.compare("main") == 0) {
					output << std::endl;
					output << tools::Tab::toString() << "// forec:scheduler:counter:start" << std::endl;
					output << tools::Tab::toString() << "PTARM_TIME_GET(reactionTimeEnd);" << std::endl;
					output << tools::Tab::toString() << "PTARM_MINUS(reactionTime, reactionTimeEnd, reactionTimeStart);" << std::endl;
					output << tools::Tab::toString() << "printf(utoa(globalReactions)); printf(\" \"); printf(\"Reaction time: \"); printf(utoa(reactionTime.msb)); printf(utoa(reactionTime.lsb)); printf(\" ns\\r\\n\");" << std::endl;
					output << tools::Tab::toString() << "globalReactions++;" << std::endl;
					output << tools::Tab::toString() << "// Restart counting of the elapsed cycles for the next reaction." << std::endl;
					output << tools::Tab::toString() << "PTARM_TIME_GET(reactionTimeStart);" << std::endl;
					output << tools::Tab::toString() << "// forec:scheduler:counter:end" << std::endl;
				}
			} else if (threadScope.compare("main") == 0) {
				output << tools::Tab::toString() << "asm volatile (\"nop\");" << std::endl;
			}
			output << tools::Tab::toString() << "// forec:statement:pause:" << getId() << ":end" << std::endl;
			
			// Update the local copies of shared variables from the global projections.
			std::ostringstream sharedOutputStart;
			const std::map<forec::ast::PrimaryExpression *, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > > indirectParallelThreadUseDef = tools::SymbolTable::getIndirectParallelThread(true, true, threadScope);
			for (std::map<forec::ast::PrimaryExpression *, std::pair<tools::SymbolTable::UpdateType, std::set<std::string> > >::const_iterator variable = indirectParallelThreadUseDef.begin(); variable != indirectParallelThreadUseDef.end(); ++variable) {
				if (variable->second.first == tools::SymbolTable::intermediate) {
					// Value and status.
					sharedOutputStart << tools::Tab::toString() << *variable->first << "_copy_" << threadScope << "_local = " << *variable->first << ';' << std::endl;
				}
			}

			if (!sharedOutputStart.str().empty()) {
				output << tools::Tab::toString() << "// Update the values of the used shared variables from their global copy." << std::endl;
				output << sharedOutputStart.str();
			}

			if (strongAborts.size() > 0) {
				output << std::endl << tools::Tab::toString() << "// Strong aborts:";
				for (std::vector<AbortStatement *>::const_iterator abort = strongAborts.begin(); abort != strongAborts.end(); ++abort) {
					output << std::endl << tools::Tab::toString() << "// forec:statement:abort:" <<  (*abort)->getId() << ":start" << std::endl;
					output << tools::Tab::toString() << "if (" << (*abort)->getCondition(false) << ") {" << std::endl;
					tools::Tab::indent();
					output << tools::Tab::toString() << "goto abortEnd_" << (*abort)->getId() << ';' << std::endl;
					tools::Tab::dedent();
					output << tools::Tab::toString() << '}' << std::endl;
					output << tools::Tab::toString() << "// forec:statement:abort:" <<  (*abort)->getId() << ":end";
				}
			}

		}

	}
}
