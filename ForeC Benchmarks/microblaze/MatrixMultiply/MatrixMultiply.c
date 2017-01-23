/*==============================================================
| Hardware architecture specific declarations:
| Cores, mutex and input/output information.
*=============================================================*/
// Xilinx Microblaze
#include "xparameters.h"

// Xilinx Microblaze Processor Version Register
#include "pvr.h"

// Hardware counter connected via a direct FSL bus.
#include "counter_dfsl.h"
#define FSL_COUNTER_ID				2
Counter counter;

// ForeC hardware mutex
#include "forec_mutex.h"
#define FSL_FOREC_MUTEX_ID			0
#define FSL_FOREC_MUTEX_RESET_ID	1
#define MAX_MUTEX_COUNT				31


/*==============================================================
| ForeC type definitions:
| Defines the types of storage elements specific to ForeC.
*=============================================================*/
// Status values.
typedef enum {
	// PAR
	FOREC_PAR_OFF,				// 0
	FOREC_PAR_ON,				// 1

	// Core
	FOREC_CORE_REACTING,		// 2
	FOREC_CORE_REACTED,			// 3
	FOREC_CORE_TERMINATED,		// 4
	
	// Shared variables
	FOREC_SHARED_UNMODIFIED,	// 5
	FOREC_SHARED_MODIFIED,		// 6
	FOREC_SHARED_WAS_MODIFIED	// 7
} Status;

// Store child thread information.
typedef struct _Thread {
	void *programCounter;
	struct _Thread *nextThread;
	struct _Thread *prevThread;
} Thread;

// Store parent thread information
typedef struct {
	void *programCounter;
	int parStatus;
	int parId;
} Parent;

// Keep track of child threads executing on
// a processor core.
typedef struct {
	int sync;
	int activeThreads;
	int status;
	int reactionCounter;
} Core;

// Global variable for counting the number of global reactions.
volatile long int globalReactions = 0;

// Shared control variables for par(...)s -------------------------
// Thread main with par(...)s
volatile Parent mainParParent;
volatile Core mainParCore0;
volatile Core mainParCore1;
volatile Core mainParCore2;
volatile Core mainParCore3;
volatile Core mainParCore4;
volatile Core mainParCore5;
volatile Core mainParCore6;
volatile Core mainParCore7;
volatile int mainParReactionCounter;


/*==============================================================
| Original global declarations:
| Global declarations in the original program code.
*=============================================================*/
// thread multiply0__thread(void);
// thread multiply1__thread(void);
// thread multiply2__thread(void);
// thread multiply3__thread(void);
// thread multiply4__thread(void);
// thread multiply5__thread(void);
// thread multiply6__thread(void);
// thread multiply7__thread(void);

void multiply(void);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// main
// multiply0
// multiply1
// multiply2
// multiply3
// multiply4
// multiply5
// multiply6
// multiply7

// forec:scheduler:boot:start
int main(int argc__main_0_0, char ** args__main_0_0) {

/*==============================================================
| Multicore startup:
| Platform dependent code.  Core identifies itself and
| executes its corresponding start up code.
*=============================================================*/
	// Initialise ForeC specific values ----------------------------
	// Thread main with par(...)s
	mainParParent.parStatus = FOREC_PAR_OFF;
	mainParCore0.sync = 1;
	mainParCore0.status = FOREC_CORE_REACTING;
	mainParCore1.sync = 1;
	mainParCore1.status = FOREC_CORE_REACTING;
	mainParCore2.sync = 1;
	mainParCore2.status = FOREC_CORE_REACTING;
	mainParCore3.sync = 1;
	mainParCore3.status = FOREC_CORE_REACTING;
	mainParCore4.sync = 1;
	mainParCore4.status = FOREC_CORE_REACTING;
	mainParCore5.sync = 1;
	mainParCore5.status = FOREC_CORE_REACTING;
	mainParCore6.sync = 1;
	mainParCore6.status = FOREC_CORE_REACTING;
	mainParCore7.sync = 1;
	mainParCore7.status = FOREC_CORE_REACTING;
	mainParReactionCounter = 0;


	// ForeC mutex -------------------------------------------------
	unsigned int forec_mutex_value;
	forec_mutex_reset(FSL_FOREC_MUTEX_RESET_ID);
	
	// Variables for par()s ----------------------------------------
	// par0
	Thread multiply0__thread;
	Thread multiply1__thread;
	Thread multiply2__thread;
	Thread multiply3__thread;
	Thread multiply4__thread;
	Thread multiply5__thread;
	Thread multiply6__thread;
	Thread multiply7__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionStartSlave1;
	Thread mainReactionStartSlave2;
	Thread mainReactionStartSlave3;
	Thread mainReactionStartSlave4;
	Thread mainReactionStartSlave5;
	Thread mainReactionStartSlave6;
	Thread mainReactionStartSlave7;
	Thread mainReactionEndMaster0;
	Thread mainReactionEndSlave1;
	Thread mainReactionEndSlave2;
	Thread mainReactionEndSlave3;
	Thread mainReactionEndSlave4;
	Thread mainReactionEndSlave5;
	Thread mainReactionEndSlave6;
	Thread mainReactionEndSlave7;


	// Synchronise execution of cores ------------------------------
	// pvr = Processor Version Register
	unsigned int pvr0;
	getpvr(0, pvr0);
	pvr0 &= MICROBLAZE_PVR0_USER1_MASK;

	switch (pvr0) {
		case (0):
			while(mainParCore1.sync);
			while(mainParCore2.sync);
			while(mainParCore3.sync);
			while(mainParCore4.sync);
			while(mainParCore5.sync);
			while(mainParCore6.sync);
			while(mainParCore7.sync);
			goto mainParCore0;

		case (1):
			mainParCore1.sync = 0;
			goto mainParCore1;

		case (2):
			mainParCore2.sync = 0;
			goto mainParCore2;

		case (3):
			mainParCore3.sync = 0;
			goto mainParCore3;

		case (4):
			mainParCore4.sync = 0;
			goto mainParCore4;

		case (5):
			mainParCore5.sync = 0;
			goto mainParCore5;

		case (6):
			mainParCore6.sync = 0;
			goto mainParCore6;

		case (7):
			mainParCore7.sync = 0;
			goto mainParCore7;

		default:
			// "Lock-up" unused cores.
			while(1);
	}
// forec:scheduler:boot:end

/*==============================================================
| Core specific instructions:
| Contains par, abort and synchronisation handlers.
*=============================================================*/

	// forec:thread:main:start
	/*--------------------------------------------------------------
	| Master core: core0
	| ForeC program's main() function:
	| Original main() function code with ForeC constructs
	| translated into C code.
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.
mainParCore0: {
	// forec:scheduler:counter:start
	// Initialise and start counting the elapsed cycles for each reaction.
	counterInitialise(counter);
	counterStart(counter, FSL_COUNTER_ID);
	// forec:scheduler:counter:end
	
	//--------------------------------------------------------------

	// par0(multiply0__thread, multiply1__thread, multiply2__thread, multiply3__thread, multiply4__thread, multiply5__thread, multiply6__thread, multiply7__thread);
	// forec:statement:par:par0:start
	// Set the par(...) information.
	mainParParent.parId = 0;
	mainParParent.parStatus = FOREC_PAR_ON;

	// Link the threads and handlers together.
	mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
	multiply0__thread.programCounter = &&multiply0__thread;
	mainReactionStartMaster0.nextThread = &multiply0__thread;
	multiply0__thread.prevThread = &mainReactionStartMaster0;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	multiply0__thread.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &multiply0__thread;

	// Link the last and first threads/handlers together.
	mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
	mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

	// Set the join address.
	mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

	// Set the core information.
	mainParCore0.activeThreads = 1;
	mainParCore0.reactionCounter = mainParReactionCounter;

	// Go to the first thread.
	goto multiply0__thread;
	par0JoinAddress_mainParCore0:;
	// forec:statement:par:par0:end

	//--------------------------------------------------------------

	// forec:scheduler:threadRemove:main:start

	// forec:scheduler:counter:start
	do { counterRead(counter, FSL_COUNTER_ID); } while (counter.current < 5719);
	// Stop counting the elapsed cycles for the current reaction.
	counterStop(FSL_COUNTER_ID);
	counterRead(counter, FSL_COUNTER_ID);
	counterDifference(counter);
	counterMaximum(counter);
	counterMinimum(counter);
	counterAccumulate(counter);
	counterAverage(counter);
	xil_printf("%ld Reaction time: %d cycles, Min: %d, Avg: %d, Max: %d\r\n", globalReactions, counter.difference, counter.min, counter.avg, counter.max);
	xil_printf("Total time: %d cycles\r\n", counter.total);
	xil_printf("Program termination\r\n");
	// forec:scheduler:counter:end

	asm volatile (".long 0x80000001\r\n");
	return 0;
	// forec:scheduler:threadRemove:main:end
} // mainParCore0
	// forec:thread:main:end

// forec:scheduler:parHandler:main:master:0:start
mainParHandlerMaster0: {
	if (mainParParent.parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.
		while(mainParCore1.status == FOREC_CORE_REACTING);
		while(mainParCore2.status == FOREC_CORE_REACTING);
		while(mainParCore3.status == FOREC_CORE_REACTING);
		while(mainParCore4.status == FOREC_CORE_REACTING);
		while(mainParCore5.status == FOREC_CORE_REACTING);
		while(mainParCore6.status == FOREC_CORE_REACTING);
		while(mainParCore7.status == FOREC_CORE_REACTING);

		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;

		// Set slave cores' status to reacting.
		mainParCore1.status = FOREC_CORE_REACTING;
		mainParCore2.status = FOREC_CORE_REACTING;
		mainParCore3.status = FOREC_CORE_REACTING;
		mainParCore4.status = FOREC_CORE_REACTING;
		mainParCore5.status = FOREC_CORE_REACTING;
		mainParCore6.status = FOREC_CORE_REACTING;
		mainParCore7.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		mainParReactionCounter++;

		// Return to thread main.
		goto *mainParParent.programCounter;
	}

	// Control should not reach here.
	goto mainParHandlerMaster0;
}
// forec:scheduler:parHandler:main:master:0:end


	// Nested par(...) handlers ------------------------------------


	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:master:0:start
	//-- main:
mainReactionStartMaster0: {
	// Go to the next thread.
	goto *mainReactionStartMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:master:0:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:main:master:0:start
	//-- main:
mainReactionEndMaster0: {
	// Determine if the core can still react or not.
	if (mainParCore0.activeThreads) {
		mainParCore0.status = FOREC_CORE_REACTED;
	} else {
		mainParCore0.status = FOREC_CORE_TERMINATED;
	}
	
	// Wait for other cores to complete their reaction.
	while(mainParCore1.status == FOREC_CORE_REACTING);
	while(mainParCore2.status == FOREC_CORE_REACTING);
	while(mainParCore3.status == FOREC_CORE_REACTING);
	while(mainParCore4.status == FOREC_CORE_REACTING);
	while(mainParCore5.status == FOREC_CORE_REACTING);
	while(mainParCore6.status == FOREC_CORE_REACTING);
	while(mainParCore7.status == FOREC_CORE_REACTING);

	// Reset the mutex.
	forec_mutex_reset(FSL_FOREC_MUTEX_RESET_ID);

	// Return back to the parent thread if all the cores have terminated.
	if (1 && mainParCore0.status == FOREC_CORE_TERMINATED && mainParCore1.status == FOREC_CORE_TERMINATED && mainParCore2.status == FOREC_CORE_TERMINATED && mainParCore3.status == FOREC_CORE_TERMINATED && mainParCore4.status == FOREC_CORE_TERMINATED && mainParCore5.status == FOREC_CORE_TERMINATED && mainParCore6.status == FOREC_CORE_TERMINATED && mainParCore7.status == FOREC_CORE_TERMINATED) {
		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;
		
		// Set slave cores' status to reacting
		mainParCore1.status = FOREC_CORE_REACTING;
		mainParCore2.status = FOREC_CORE_REACTING;
		mainParCore3.status = FOREC_CORE_REACTING;
		mainParCore4.status = FOREC_CORE_REACTING;
		mainParCore5.status = FOREC_CORE_REACTING;
		mainParCore6.status = FOREC_CORE_REACTING;
		mainParCore7.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronization.
		mainParReactionCounter++;

		goto *mainParParent.programCounter;
	}

	// Set slave cores' status to reacting
	mainParCore1.status = FOREC_CORE_REACTING;
	mainParCore2.status = FOREC_CORE_REACTING;
	mainParCore3.status = FOREC_CORE_REACTING;
	mainParCore4.status = FOREC_CORE_REACTING;
	mainParCore5.status = FOREC_CORE_REACTING;
	mainParCore6.status = FOREC_CORE_REACTING;
	mainParCore7.status = FOREC_CORE_REACTING;

	// forec:scheduler:counter:start
	do { counterRead(counter, FSL_COUNTER_ID); } while (counter.current < 5719);
	// Stop counting the elapsed cycles for the current reaction.
	counterStop(FSL_COUNTER_ID);
	counterRead(counter, FSL_COUNTER_ID);
	counterDifference(counter);
	counterMaximum(counter);
	counterMinimum(counter);
	counterAccumulate(counter);
	counterAverage(counter);
	xil_printf("%d Reaction time: %ld cycles, Min: %d, Avg: %d, Max: %d\r\n", globalReactions, counter.difference, counter.min, counter.avg, counter.max);
	globalReactions++;
	// Restart counting of the elapsed cycles for the next reaction.
	counterReset(counter);
	counterStart(counter, FSL_COUNTER_ID);
	// forec:scheduler:counter:end

	// Increment the reaction counter for synchronization.
	mainParReactionCounter++;

	// Go to the next thread.
	goto *mainReactionEndMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:main:master:0:end
 


	// Abort check handlers ----------------------------------------


// forec:scheduler:parHandler:main:slave:1:start
/*--------------------------------------------------------------
| Slave core: core1
*-------------------------------------------------------------*/
mainParCore1: {
	// Check the execution status of the root par(...)s.
	while (mainParParent.parStatus == FOREC_PAR_OFF);

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave1.programCounter = &&mainReactionStartSlave1;
		multiply1__thread.programCounter = &&multiply1__thread;
		mainReactionStartSlave1.nextThread = &multiply1__thread;
		multiply1__thread.prevThread = &mainReactionStartSlave1;
		mainReactionEndSlave1.programCounter = &&mainReactionEndSlave1;
		multiply1__thread.nextThread = &mainReactionEndSlave1;
		mainReactionEndSlave1.prevThread = &multiply1__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave1.nextThread = &mainReactionStartSlave1;
		mainReactionStartSlave1.prevThread = &mainReactionEndSlave1;

		// Set the core information.
		mainParCore1.activeThreads = 1;
		mainParCore1.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto multiply1__thread;
		asm("# par0 end");
	} else {
		// Unscheduled par(...)
		mainParCore1.reactionCounter = mainParReactionCounter;
		
		// Wait for the par(...) to terminate.
		do {
			mainParCore1.status = FOREC_CORE_TERMINATED;
			
			// Wait for the next reaction.
			while (mainParCore1.reactionCounter == mainParReactionCounter);
			mainParCore1.reactionCounter++;
			
		} while (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId);
		
		// Go back to the top and wait for the next nested par(...) 
		goto mainParCore1;
	}
	
	// Control shouldn't reach here.
	goto mainParCore1;
}
// forec:scheduler:parHandler:main:slave:1:end

	// Nested par(...) handlers ------------------------------------


	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:slave:1:start
	//-- main:
mainReactionStartSlave1: {
	// Go to the next thread.
	goto *mainReactionStartSlave1.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:1:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:main:slave:1:start
	//-- main:
mainReactionEndSlave1: {
	// Determine if the core can still react or not.
	if (mainParCore1.activeThreads) {
		mainParCore1.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (mainParCore1.reactionCounter == mainParReactionCounter);
		mainParCore1.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave1.nextThread -> programCounter;
	} else {
		int parId = mainParParent.parId;

		mainReactionEndSlave1.programCounter = &&terminated_mainReactionEndSlave1;
		terminated_mainReactionEndSlave1:;
		
		mainParCore1.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (mainParCore1.reactionCounter == mainParReactionCounter);
		mainParCore1.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId) {
			goto *mainReactionEndSlave1.nextThread -> programCounter;
		}

		goto mainParCore1;
	}
	
	// Control shouldn't reach here.
	goto mainReactionEndSlave1;
}
	// forec:scheduler:reactionEnd:main:slave:1:end
 


	// Abort check handlers ----------------------------------------

// forec:scheduler:parHandler:main:slave:2:start
/*--------------------------------------------------------------
| Slave core: core2
*-------------------------------------------------------------*/
mainParCore2: {
	// Check the execution status of the root par(...)s.
	while (mainParParent.parStatus == FOREC_PAR_OFF);

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave2.programCounter = &&mainReactionStartSlave2;
		multiply3__thread.programCounter = &&multiply3__thread;
		mainReactionStartSlave2.nextThread = &multiply3__thread;
		multiply3__thread.prevThread = &mainReactionStartSlave2;
		mainReactionEndSlave2.programCounter = &&mainReactionEndSlave2;
		multiply3__thread.nextThread = &mainReactionEndSlave2;
		mainReactionEndSlave2.prevThread = &multiply3__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave2.nextThread = &mainReactionStartSlave2;
		mainReactionStartSlave2.prevThread = &mainReactionEndSlave2;

		// Set the core information.
		mainParCore2.activeThreads = 1;
		mainParCore2.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto multiply3__thread;
		asm("# par0 end");
	} else {
		// Unscheduled par(...)
		mainParCore2.reactionCounter = mainParReactionCounter;
		
		// Wait for the par(...) to terminate.
		do {
			mainParCore2.status = FOREC_CORE_TERMINATED;
			
			// Wait for the next reaction.
			while (mainParCore2.reactionCounter == mainParReactionCounter);
			mainParCore2.reactionCounter++;
			
		} while (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId);
		
		// Go back to the top and wait for the next nested par(...) 
		goto mainParCore2;
	}
	
	// Control shouldn't reach here.
	goto mainParCore2;
}
// forec:scheduler:parHandler:main:slave:2:end

	// Nested par(...) handlers ------------------------------------


	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:slave:2:start
	//-- main:
mainReactionStartSlave2: {
	// Go to the next thread.
	goto *mainReactionStartSlave2.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:2:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:main:slave:2:start
	//-- main:
mainReactionEndSlave2: {
	// Determine if the core can still react or not.
	if (mainParCore2.activeThreads) {
		mainParCore2.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (mainParCore2.reactionCounter == mainParReactionCounter);
		mainParCore2.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave2.nextThread -> programCounter;
	} else {
		int parId = mainParParent.parId;

		mainReactionEndSlave2.programCounter = &&terminated_mainReactionEndSlave2;
		terminated_mainReactionEndSlave2:;
		
		mainParCore2.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (mainParCore2.reactionCounter == mainParReactionCounter);
		mainParCore2.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId) {
			goto *mainReactionEndSlave2.nextThread -> programCounter;
		}

		goto mainParCore2;
	}
	
	// Control shouldn't reach here.
	goto mainReactionEndSlave2;
}
	// forec:scheduler:reactionEnd:main:slave:2:end
 


	// Abort check handlers ----------------------------------------

// forec:scheduler:parHandler:main:slave:3:start
/*--------------------------------------------------------------
| Slave core: core3
*-------------------------------------------------------------*/
mainParCore3: {
	// Check the execution status of the root par(...)s.
	while (mainParParent.parStatus == FOREC_PAR_OFF);

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave3.programCounter = &&mainReactionStartSlave3;
		multiply4__thread.programCounter = &&multiply4__thread;
		mainReactionStartSlave3.nextThread = &multiply4__thread;
		multiply4__thread.prevThread = &mainReactionStartSlave3;
		mainReactionEndSlave3.programCounter = &&mainReactionEndSlave3;
		multiply4__thread.nextThread = &mainReactionEndSlave3;
		mainReactionEndSlave3.prevThread = &multiply4__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave3.nextThread = &mainReactionStartSlave3;
		mainReactionStartSlave3.prevThread = &mainReactionEndSlave3;

		// Set the core information.
		mainParCore3.activeThreads = 1;
		mainParCore3.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto multiply4__thread;
		asm("# par0 end");
	} else {
		// Unscheduled par(...)
		mainParCore3.reactionCounter = mainParReactionCounter;
		
		// Wait for the par(...) to terminate.
		do {
			mainParCore3.status = FOREC_CORE_TERMINATED;
			
			// Wait for the next reaction.
			while (mainParCore3.reactionCounter == mainParReactionCounter);
			mainParCore3.reactionCounter++;
			
		} while (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId);
		
		// Go back to the top and wait for the next nested par(...) 
		goto mainParCore3;
	}
	
	// Control shouldn't reach here.
	goto mainParCore3;
}
// forec:scheduler:parHandler:main:slave:3:end

	// Nested par(...) handlers ------------------------------------


	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:slave:3:start
	//-- main:
mainReactionStartSlave3: {
	// Go to the next thread.
	goto *mainReactionStartSlave3.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:3:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:main:slave:3:start
	//-- main:
mainReactionEndSlave3: {
	// Determine if the core can still react or not.
	if (mainParCore3.activeThreads) {
		mainParCore3.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (mainParCore3.reactionCounter == mainParReactionCounter);
		mainParCore3.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave3.nextThread -> programCounter;
	} else {
		int parId = mainParParent.parId;

		mainReactionEndSlave3.programCounter = &&terminated_mainReactionEndSlave3;
		terminated_mainReactionEndSlave3:;
		
		mainParCore3.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (mainParCore3.reactionCounter == mainParReactionCounter);
		mainParCore3.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId) {
			goto *mainReactionEndSlave3.nextThread -> programCounter;
		}

		goto mainParCore3;
	}
	
	// Control shouldn't reach here.
	goto mainReactionEndSlave3;
}
	// forec:scheduler:reactionEnd:main:slave:3:end
 


	// Abort check handlers ----------------------------------------

// forec:scheduler:parHandler:main:slave:4:start
/*--------------------------------------------------------------
| Slave core: core4
*-------------------------------------------------------------*/
mainParCore4: {
	// Check the execution status of the root par(...)s.
	while (mainParParent.parStatus == FOREC_PAR_OFF);

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave4.programCounter = &&mainReactionStartSlave4;
		multiply6__thread.programCounter = &&multiply6__thread;
		mainReactionStartSlave4.nextThread = &multiply6__thread;
		multiply6__thread.prevThread = &mainReactionStartSlave4;
		mainReactionEndSlave4.programCounter = &&mainReactionEndSlave4;
		multiply6__thread.nextThread = &mainReactionEndSlave4;
		mainReactionEndSlave4.prevThread = &multiply6__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave4.nextThread = &mainReactionStartSlave4;
		mainReactionStartSlave4.prevThread = &mainReactionEndSlave4;

		// Set the core information.
		mainParCore4.activeThreads = 1;
		mainParCore4.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto multiply6__thread;
		asm("# par0 end");
	} else {
		// Unscheduled par(...)
		mainParCore4.reactionCounter = mainParReactionCounter;
		
		// Wait for the par(...) to terminate.
		do {
			mainParCore4.status = FOREC_CORE_TERMINATED;
			
			// Wait for the next reaction.
			while (mainParCore4.reactionCounter == mainParReactionCounter);
			mainParCore4.reactionCounter++;
			
		} while (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId);
		
		// Go back to the top and wait for the next nested par(...) 
		goto mainParCore4;
	}
	
	// Control shouldn't reach here.
	goto mainParCore4;
}
// forec:scheduler:parHandler:main:slave:4:end

	// Nested par(...) handlers ------------------------------------


	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:slave:4:start
	//-- main:
mainReactionStartSlave4: {
	// Go to the next thread.
	goto *mainReactionStartSlave4.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:4:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:main:slave:4:start
	//-- main:
mainReactionEndSlave4: {
	// Determine if the core can still react or not.
	if (mainParCore4.activeThreads) {
		mainParCore4.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (mainParCore4.reactionCounter == mainParReactionCounter);
		mainParCore4.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave4.nextThread -> programCounter;
	} else {
		int parId = mainParParent.parId;

		mainReactionEndSlave4.programCounter = &&terminated_mainReactionEndSlave4;
		terminated_mainReactionEndSlave4:;
		
		mainParCore4.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (mainParCore4.reactionCounter == mainParReactionCounter);
		mainParCore4.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId) {
			goto *mainReactionEndSlave4.nextThread -> programCounter;
		}

		goto mainParCore4;
	}
	
	// Control shouldn't reach here.
	goto mainReactionEndSlave4;
}
	// forec:scheduler:reactionEnd:main:slave:4:end
 


	// Abort check handlers ----------------------------------------

// forec:scheduler:parHandler:main:slave:5:start
/*--------------------------------------------------------------
| Slave core: core5
*-------------------------------------------------------------*/
mainParCore5: {
	// Check the execution status of the root par(...)s.
	while (mainParParent.parStatus == FOREC_PAR_OFF);

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave5.programCounter = &&mainReactionStartSlave5;
		multiply7__thread.programCounter = &&multiply7__thread;
		mainReactionStartSlave5.nextThread = &multiply7__thread;
		multiply7__thread.prevThread = &mainReactionStartSlave5;
		mainReactionEndSlave5.programCounter = &&mainReactionEndSlave5;
		multiply7__thread.nextThread = &mainReactionEndSlave5;
		mainReactionEndSlave5.prevThread = &multiply7__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave5.nextThread = &mainReactionStartSlave5;
		mainReactionStartSlave5.prevThread = &mainReactionEndSlave5;

		// Set the core information.
		mainParCore5.activeThreads = 1;
		mainParCore5.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto multiply7__thread;
		asm("# par0 end");
	} else {
		// Unscheduled par(...)
		mainParCore5.reactionCounter = mainParReactionCounter;
		
		// Wait for the par(...) to terminate.
		do {
			mainParCore5.status = FOREC_CORE_TERMINATED;
			
			// Wait for the next reaction.
			while (mainParCore5.reactionCounter == mainParReactionCounter);
			mainParCore5.reactionCounter++;
			
		} while (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId);
		
		// Go back to the top and wait for the next nested par(...) 
		goto mainParCore5;
	}
	
	// Control shouldn't reach here.
	goto mainParCore5;
}
// forec:scheduler:parHandler:main:slave:5:end

	// Nested par(...) handlers ------------------------------------


	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:slave:5:start
	//-- main:
mainReactionStartSlave5: {
	// Go to the next thread.
	goto *mainReactionStartSlave5.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:5:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:main:slave:5:start
	//-- main:
mainReactionEndSlave5: {
	// Determine if the core can still react or not.
	if (mainParCore5.activeThreads) {
		mainParCore5.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (mainParCore5.reactionCounter == mainParReactionCounter);
		mainParCore5.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave5.nextThread -> programCounter;
	} else {
		int parId = mainParParent.parId;

		mainReactionEndSlave5.programCounter = &&terminated_mainReactionEndSlave5;
		terminated_mainReactionEndSlave5:;
		
		mainParCore5.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (mainParCore5.reactionCounter == mainParReactionCounter);
		mainParCore5.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId) {
			goto *mainReactionEndSlave5.nextThread -> programCounter;
		}

		goto mainParCore5;
	}
	
	// Control shouldn't reach here.
	goto mainReactionEndSlave5;
}
	// forec:scheduler:reactionEnd:main:slave:5:end
 


	// Abort check handlers ----------------------------------------

// forec:scheduler:parHandler:main:slave:6:start
/*--------------------------------------------------------------
| Slave core: core6
*-------------------------------------------------------------*/
mainParCore6: {
	// Check the execution status of the root par(...)s.
	while (mainParParent.parStatus == FOREC_PAR_OFF);

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave6.programCounter = &&mainReactionStartSlave6;
		multiply2__thread.programCounter = &&multiply2__thread;
		mainReactionStartSlave6.nextThread = &multiply2__thread;
		multiply2__thread.prevThread = &mainReactionStartSlave6;
		mainReactionEndSlave6.programCounter = &&mainReactionEndSlave6;
		multiply2__thread.nextThread = &mainReactionEndSlave6;
		mainReactionEndSlave6.prevThread = &multiply2__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave6.nextThread = &mainReactionStartSlave6;
		mainReactionStartSlave6.prevThread = &mainReactionEndSlave6;

		// Set the core information.
		mainParCore6.activeThreads = 1;
		mainParCore6.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto multiply2__thread;
		asm("# par0 end");
	} else {
		// Unscheduled par(...)
		mainParCore6.reactionCounter = mainParReactionCounter;
		
		// Wait for the par(...) to terminate.
		do {
			mainParCore6.status = FOREC_CORE_TERMINATED;
			
			// Wait for the next reaction.
			while (mainParCore6.reactionCounter == mainParReactionCounter);
			mainParCore6.reactionCounter++;
			
		} while (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId);
		
		// Go back to the top and wait for the next nested par(...) 
		goto mainParCore6;
	}
	
	// Control shouldn't reach here.
	goto mainParCore6;
}
// forec:scheduler:parHandler:main:slave:6:end

	// Nested par(...) handlers ------------------------------------


	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:slave:6:start
	//-- main:
mainReactionStartSlave6: {
	// Go to the next thread.
	goto *mainReactionStartSlave6.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:6:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:main:slave:6:start
	//-- main:
mainReactionEndSlave6: {
	// Determine if the core can still react or not.
	if (mainParCore6.activeThreads) {
		mainParCore6.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (mainParCore6.reactionCounter == mainParReactionCounter);
		mainParCore6.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave6.nextThread -> programCounter;
	} else {
		int parId = mainParParent.parId;

		mainReactionEndSlave6.programCounter = &&terminated_mainReactionEndSlave6;
		terminated_mainReactionEndSlave6:;
		
		mainParCore6.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (mainParCore6.reactionCounter == mainParReactionCounter);
		mainParCore6.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId) {
			goto *mainReactionEndSlave6.nextThread -> programCounter;
		}

		goto mainParCore6;
	}
	
	// Control shouldn't reach here.
	goto mainReactionEndSlave6;
}
	// forec:scheduler:reactionEnd:main:slave:6:end
 


	// Abort check handlers ----------------------------------------

// forec:scheduler:parHandler:main:slave:7:start
/*--------------------------------------------------------------
| Slave core: core7
*-------------------------------------------------------------*/
mainParCore7: {
	// Check the execution status of the root par(...)s.
	while (mainParParent.parStatus == FOREC_PAR_OFF);

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave7.programCounter = &&mainReactionStartSlave7;
		multiply5__thread.programCounter = &&multiply5__thread;
		mainReactionStartSlave7.nextThread = &multiply5__thread;
		multiply5__thread.prevThread = &mainReactionStartSlave7;
		mainReactionEndSlave7.programCounter = &&mainReactionEndSlave7;
		multiply5__thread.nextThread = &mainReactionEndSlave7;
		mainReactionEndSlave7.prevThread = &multiply5__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave7.nextThread = &mainReactionStartSlave7;
		mainReactionStartSlave7.prevThread = &mainReactionEndSlave7;

		// Set the core information.
		mainParCore7.activeThreads = 1;
		mainParCore7.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto multiply5__thread;
		asm("# par0 end");
	} else {
		// Unscheduled par(...)
		mainParCore7.reactionCounter = mainParReactionCounter;
		
		// Wait for the par(...) to terminate.
		do {
			mainParCore7.status = FOREC_CORE_TERMINATED;
			
			// Wait for the next reaction.
			while (mainParCore7.reactionCounter == mainParReactionCounter);
			mainParCore7.reactionCounter++;
			
		} while (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId);
		
		// Go back to the top and wait for the next nested par(...) 
		goto mainParCore7;
	}
	
	// Control shouldn't reach here.
	goto mainParCore7;
}
// forec:scheduler:parHandler:main:slave:7:end

	// Nested par(...) handlers ------------------------------------


	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:slave:7:start
	//-- main:
mainReactionStartSlave7: {
	// Go to the next thread.
	goto *mainReactionStartSlave7.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:7:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:main:slave:7:start
	//-- main:
mainReactionEndSlave7: {
	// Determine if the core can still react or not.
	if (mainParCore7.activeThreads) {
		mainParCore7.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (mainParCore7.reactionCounter == mainParReactionCounter);
		mainParCore7.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave7.nextThread -> programCounter;
	} else {
		int parId = mainParParent.parId;

		mainReactionEndSlave7.programCounter = &&terminated_mainReactionEndSlave7;
		terminated_mainReactionEndSlave7:;
		
		mainParCore7.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (mainParCore7.reactionCounter == mainParReactionCounter);
		mainParCore7.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId) {
			goto *mainReactionEndSlave7.nextThread -> programCounter;
		}

		goto mainParCore7;
	}
	
	// Control shouldn't reach here.
	goto mainReactionEndSlave7;
}
	// forec:scheduler:reactionEnd:main:slave:7:end
 


	// Abort check handlers ----------------------------------------



/*==============================================================
| ForeC threads:
| Threads code translated into C code.
*=============================================================*/
	// forec:thread:multiply0:start
	/*--------------------------------------------------------------
	| Thread multiply0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	multiply0__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		multiply();

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiply0:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		multiply0__thread.nextThread -> prevThread = multiply0__thread.prevThread;
		multiply0__thread.prevThread -> nextThread = multiply0__thread.nextThread;
		goto *multiply0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:multiply0:end
	} // multiply0__thread
	// forec:thread:multiply0:end

	// forec:thread:multiply1:start
	/*--------------------------------------------------------------
	| Thread multiply1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	multiply1__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		multiply();

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiply1:start

		// Delete thread from the linked list and core.
		mainParCore1.activeThreads--;
		multiply1__thread.nextThread -> prevThread = multiply1__thread.prevThread;
		multiply1__thread.prevThread -> nextThread = multiply1__thread.nextThread;
		goto *multiply1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:multiply1:end
	} // multiply1__thread
	// forec:thread:multiply1:end

	// forec:thread:multiply2:start
	/*--------------------------------------------------------------
	| Thread multiply2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	multiply2__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		multiply();

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiply2:start

		// Delete thread from the linked list and core.
		mainParCore6.activeThreads--;
		multiply2__thread.nextThread -> prevThread = multiply2__thread.prevThread;
		multiply2__thread.prevThread -> nextThread = multiply2__thread.nextThread;
		goto *multiply2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:multiply2:end
	} // multiply2__thread
	// forec:thread:multiply2:end

	// forec:thread:multiply3:start
	/*--------------------------------------------------------------
	| Thread multiply3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	multiply3__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		multiply();

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiply3:start

		// Delete thread from the linked list and core.
		mainParCore2.activeThreads--;
		multiply3__thread.nextThread -> prevThread = multiply3__thread.prevThread;
		multiply3__thread.prevThread -> nextThread = multiply3__thread.nextThread;
		goto *multiply3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:multiply3:end
	} // multiply3__thread
	// forec:thread:multiply3:end

	// forec:thread:multiply4:start
	/*--------------------------------------------------------------
	| Thread multiply4
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	multiply4__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		multiply();

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiply4:start

		// Delete thread from the linked list and core.
		mainParCore3.activeThreads--;
		multiply4__thread.nextThread -> prevThread = multiply4__thread.prevThread;
		multiply4__thread.prevThread -> nextThread = multiply4__thread.nextThread;
		goto *multiply4__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:multiply4:end
	} // multiply4__thread
	// forec:thread:multiply4:end

	// forec:thread:multiply5:start
	/*--------------------------------------------------------------
	| Thread multiply5
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	multiply5__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		multiply();

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiply5:start

		// Delete thread from the linked list and core.
		mainParCore7.activeThreads--;
		multiply5__thread.nextThread -> prevThread = multiply5__thread.prevThread;
		multiply5__thread.prevThread -> nextThread = multiply5__thread.nextThread;
		goto *multiply5__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:multiply5:end
	} // multiply5__thread
	// forec:thread:multiply5:end

	// forec:thread:multiply6:start
	/*--------------------------------------------------------------
	| Thread multiply6
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	multiply6__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		multiply();

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiply6:start

		// Delete thread from the linked list and core.
		mainParCore4.activeThreads--;
		multiply6__thread.nextThread -> prevThread = multiply6__thread.prevThread;
		multiply6__thread.prevThread -> nextThread = multiply6__thread.nextThread;
		goto *multiply6__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:multiply6:end
	} // multiply6__thread
	// forec:thread:multiply6:end

	// forec:thread:multiply7:start
	/*--------------------------------------------------------------
	| Thread multiply7
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	multiply7__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		multiply();

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiply7:start

		// Delete thread from the linked list and core.
		mainParCore5.activeThreads--;
		multiply7__thread.nextThread -> prevThread = multiply7__thread.prevThread;
		multiply7__thread.prevThread -> nextThread = multiply7__thread.nextThread;
		goto *multiply7__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:multiply7:end
	} // multiply7__thread
	// forec:thread:multiply7:end


} // End of the main() function.

void multiply(void) {
	int SIZE__multiply_0_0 = 5;
	int matrixA__multiply_0_0[SIZE__multiply_0_0][SIZE__multiply_0_0];
	int matrixB__multiply_0_0[SIZE__multiply_0_0][SIZE__multiply_0_0];
	int matrixC__multiply_0_0[SIZE__multiply_0_0][SIZE__multiply_0_0];
	int sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[0][0]*matrixB__multiply_0_0[0][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][1]*matrixB__multiply_0_0[1][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][2]*matrixB__multiply_0_0[2][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][3]*matrixB__multiply_0_0[3][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][4]*matrixB__multiply_0_0[4][0];
	matrixC__multiply_0_0[0][0] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[0][0]*matrixB__multiply_0_0[0][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][1]*matrixB__multiply_0_0[1][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][2]*matrixB__multiply_0_0[2][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][3]*matrixB__multiply_0_0[3][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][4]*matrixB__multiply_0_0[4][1];
	matrixC__multiply_0_0[0][1] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[0][0]*matrixB__multiply_0_0[0][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][1]*matrixB__multiply_0_0[1][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][2]*matrixB__multiply_0_0[2][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][3]*matrixB__multiply_0_0[3][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][4]*matrixB__multiply_0_0[4][2];
	matrixC__multiply_0_0[0][2] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[0][0]*matrixB__multiply_0_0[0][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][1]*matrixB__multiply_0_0[1][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][2]*matrixB__multiply_0_0[2][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][3]*matrixB__multiply_0_0[3][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][4]*matrixB__multiply_0_0[4][3];
	matrixC__multiply_0_0[0][3] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[0][0]*matrixB__multiply_0_0[0][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][1]*matrixB__multiply_0_0[1][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][2]*matrixB__multiply_0_0[2][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][3]*matrixB__multiply_0_0[3][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[0][4]*matrixB__multiply_0_0[4][4];
	matrixC__multiply_0_0[0][4] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[1][0]*matrixB__multiply_0_0[0][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][1]*matrixB__multiply_0_0[1][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][2]*matrixB__multiply_0_0[2][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][3]*matrixB__multiply_0_0[3][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][4]*matrixB__multiply_0_0[4][0];
	matrixC__multiply_0_0[1][0] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[1][0]*matrixB__multiply_0_0[0][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][1]*matrixB__multiply_0_0[1][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][2]*matrixB__multiply_0_0[2][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][3]*matrixB__multiply_0_0[3][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][4]*matrixB__multiply_0_0[4][1];
	matrixC__multiply_0_0[1][1] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[1][0]*matrixB__multiply_0_0[0][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][1]*matrixB__multiply_0_0[1][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][2]*matrixB__multiply_0_0[2][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][3]*matrixB__multiply_0_0[3][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][4]*matrixB__multiply_0_0[4][2];
	matrixC__multiply_0_0[1][2] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[1][0]*matrixB__multiply_0_0[0][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][1]*matrixB__multiply_0_0[1][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][2]*matrixB__multiply_0_0[2][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][3]*matrixB__multiply_0_0[3][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][4]*matrixB__multiply_0_0[4][3];
	matrixC__multiply_0_0[1][3] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[1][0]*matrixB__multiply_0_0[0][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][1]*matrixB__multiply_0_0[1][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][2]*matrixB__multiply_0_0[2][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][3]*matrixB__multiply_0_0[3][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[1][4]*matrixB__multiply_0_0[4][4];
	matrixC__multiply_0_0[1][4] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[2][0]*matrixB__multiply_0_0[0][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][1]*matrixB__multiply_0_0[1][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][2]*matrixB__multiply_0_0[2][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][3]*matrixB__multiply_0_0[3][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][4]*matrixB__multiply_0_0[4][0];
	matrixC__multiply_0_0[2][0] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[2][0]*matrixB__multiply_0_0[0][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][1]*matrixB__multiply_0_0[1][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][2]*matrixB__multiply_0_0[2][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][3]*matrixB__multiply_0_0[3][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][4]*matrixB__multiply_0_0[4][1];
	matrixC__multiply_0_0[2][1] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[2][0]*matrixB__multiply_0_0[0][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][1]*matrixB__multiply_0_0[1][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][2]*matrixB__multiply_0_0[2][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][3]*matrixB__multiply_0_0[3][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][4]*matrixB__multiply_0_0[4][2];
	matrixC__multiply_0_0[2][2] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[2][0]*matrixB__multiply_0_0[0][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][1]*matrixB__multiply_0_0[1][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][2]*matrixB__multiply_0_0[2][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][3]*matrixB__multiply_0_0[3][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][4]*matrixB__multiply_0_0[4][3];
	matrixC__multiply_0_0[2][3] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[2][0]*matrixB__multiply_0_0[0][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][1]*matrixB__multiply_0_0[1][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][2]*matrixB__multiply_0_0[2][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][3]*matrixB__multiply_0_0[3][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[2][4]*matrixB__multiply_0_0[4][4];
	matrixC__multiply_0_0[2][4] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[3][0]*matrixB__multiply_0_0[0][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][1]*matrixB__multiply_0_0[1][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][2]*matrixB__multiply_0_0[2][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][3]*matrixB__multiply_0_0[3][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][4]*matrixB__multiply_0_0[4][0];
	matrixC__multiply_0_0[3][0] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[3][0]*matrixB__multiply_0_0[0][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][1]*matrixB__multiply_0_0[1][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][2]*matrixB__multiply_0_0[2][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][3]*matrixB__multiply_0_0[3][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][4]*matrixB__multiply_0_0[4][1];
	matrixC__multiply_0_0[3][1] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[3][0]*matrixB__multiply_0_0[0][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][1]*matrixB__multiply_0_0[1][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][2]*matrixB__multiply_0_0[2][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][3]*matrixB__multiply_0_0[3][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][4]*matrixB__multiply_0_0[4][2];
	matrixC__multiply_0_0[3][2] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[3][0]*matrixB__multiply_0_0[0][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][1]*matrixB__multiply_0_0[1][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][2]*matrixB__multiply_0_0[2][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][3]*matrixB__multiply_0_0[3][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][4]*matrixB__multiply_0_0[4][3];
	matrixC__multiply_0_0[3][3] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[3][0]*matrixB__multiply_0_0[0][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][1]*matrixB__multiply_0_0[1][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][2]*matrixB__multiply_0_0[2][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][3]*matrixB__multiply_0_0[3][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[3][4]*matrixB__multiply_0_0[4][4];
	matrixC__multiply_0_0[3][4] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[4][0]*matrixB__multiply_0_0[0][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][1]*matrixB__multiply_0_0[1][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][2]*matrixB__multiply_0_0[2][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][3]*matrixB__multiply_0_0[3][0];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][4]*matrixB__multiply_0_0[4][0];
	matrixC__multiply_0_0[4][0] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[4][0]*matrixB__multiply_0_0[0][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][1]*matrixB__multiply_0_0[1][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][2]*matrixB__multiply_0_0[2][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][3]*matrixB__multiply_0_0[3][1];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][4]*matrixB__multiply_0_0[4][1];
	matrixC__multiply_0_0[4][1] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[4][0]*matrixB__multiply_0_0[0][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][1]*matrixB__multiply_0_0[1][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][2]*matrixB__multiply_0_0[2][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][3]*matrixB__multiply_0_0[3][2];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][4]*matrixB__multiply_0_0[4][2];
	matrixC__multiply_0_0[4][2] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[4][0]*matrixB__multiply_0_0[0][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][1]*matrixB__multiply_0_0[1][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][2]*matrixB__multiply_0_0[2][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][3]*matrixB__multiply_0_0[3][3];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][4]*matrixB__multiply_0_0[4][3];
	matrixC__multiply_0_0[4][3] = sum__multiply_0_0;
	sum__multiply_0_0 = 0;
	sum__multiply_0_0 += matrixA__multiply_0_0[4][0]*matrixB__multiply_0_0[0][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][1]*matrixB__multiply_0_0[1][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][2]*matrixB__multiply_0_0[2][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][3]*matrixB__multiply_0_0[3][4];
	sum__multiply_0_0 += matrixA__multiply_0_0[4][4]*matrixB__multiply_0_0[4][4];
	matrixC__multiply_0_0[4][4] = sum__multiply_0_0;
}

