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
Counter counter;

// ForeC hardware mutex
#include "forec_mutex.h"
#define FSL_FOREC_MUTEX_ID			0
#define FSL_FOREC_MUTEX_RESET_ID	1
#define FSL_COUNTER_ID				2
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
volatile int mainParReactionCounter;


/*==============================================================
| Original global declarations:
| Global declarations in the original program code.
*=============================================================*/
#include "stdlib.h"

int RAND_MAX__global_0_0;

#define RAND_MAX__global_0_0 RAND_MAX

typedef struct {
	/* shared */ int value;
	int status;
} Shared_blackColor__global_0_0;
Shared_blackColor__global_0_0 blackColor__global_0_0;

struct life_datum__global_0_0 {
	int color;
	int x1;
	int y1;
};

struct life_datum__global_0_0 life_data__global_0_0[96 + 2][24 + 2];

typedef struct {
	/* shared */ struct life_datum__global_0_0 (*value)[96 + 2][24 + 2];
	int status;
} Shared_life_data_ptr__global_0_0;
Shared_life_data_ptr__global_0_0 life_data_ptr__global_0_0 = {.value = &life_data__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

int grid__global_0_0[96 + 2][24 + 2];

typedef struct {
	/* shared */ int (*value)[96 + 2][24 + 2];
	int status;
} Shared_grid_ptr__global_0_0;
Shared_grid_ptr__global_0_0 grid_ptr__global_0_0 = {.value = &grid__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

int next_grid__global_0_0[96 + 2][24 + 2];

typedef struct {
	/* shared */ int (*value)[96 + 2][24 + 2];
	int status;
} Shared_next_grid_ptr__global_0_0;
Shared_next_grid_ptr__global_0_0 next_grid_ptr__global_0_0 = {.value = &next_grid__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

void do_step(const int threadNumber, int (*grid_ptr)[96 + 2][24 + 2], int (*next_grid_ptr)[96 + 2][24 + 2]);
void initialise(const int ncols, const int startIndex, const int endIndex, int (*grid_ptr)[96 + 2][24 + 2]);
void randomize_grid(const int ncols, const int startIndex, const int endIndex, int (*grid_ptr)[96 + 2][24 + 2], const float prob);
float rand_float(void);
void random_initByTime(void);

// thread do_step_0__thread(void);
// thread do_step_1__thread(void);
// thread do_step_2__thread(void);
// thread do_step_3__thread(void);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// do_step_0
// do_step_1
// do_step_2
// do_step_3
// main

// forec:scheduler:boot:start
int main(int argc__main_0_0, char ** argv__main_0_0) {

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
	mainParReactionCounter = 0;


	// ForeC mutex -------------------------------------------------
	unsigned int forec_mutex_value;
	forec_mutex_reset(FSL_FOREC_MUTEX_RESET_ID);
	
	// Variables for par()s ----------------------------------------
	// par0
	Thread do_step_0__thread;
	Thread do_step_1__thread;
	Thread do_step_2__thread;
	Thread do_step_3__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionStartSlave1;
	Thread mainReactionStartSlave2;
	Thread mainReactionStartSlave3;
	Thread mainReactionEndMaster0;
	Thread mainReactionEndSlave1;
	Thread mainReactionEndSlave2;
	Thread mainReactionEndSlave3;


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

	// par0(do_step_0__thread, do_step_1__thread, do_step_2__thread, do_step_3__thread);
	// forec:statement:par:par0:start
	// Set the par(...) information.
	mainParParent.parId = 0;
	mainParParent.parStatus = FOREC_PAR_ON;

	// Link the threads and handlers together.
	mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
	do_step_0__thread.programCounter = &&do_step_0__thread;
	mainReactionStartMaster0.nextThread = &do_step_0__thread;
	do_step_0__thread.prevThread = &mainReactionStartMaster0;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	do_step_0__thread.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &do_step_0__thread;

	// Link the last and first threads/handlers together.
	mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
	mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

	// Set the join address.
	mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

	// Set the core information.
	mainParCore0.activeThreads = 1;
	mainParCore0.reactionCounter = mainParReactionCounter;

	// Go to the first thread.
	goto do_step_0__thread;
	par0JoinAddress_mainParCore0:;
	// forec:statement:par:par0:end

	//--------------------------------------------------------------

	// forec:scheduler:threadRemove:main:start

	// forec:scheduler:counter:start
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

		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;

		// Set slave cores' status to reacting.
		mainParCore1.status = FOREC_CORE_REACTING;
		mainParCore2.status = FOREC_CORE_REACTING;
		mainParCore3.status = FOREC_CORE_REACTING;

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

	// Reset the mutex.
	forec_mutex_reset(FSL_FOREC_MUTEX_RESET_ID);

	// Return back to the parent thread if all the cores have terminated.
	if (1 && mainParCore0.status == FOREC_CORE_TERMINATED && mainParCore1.status == FOREC_CORE_TERMINATED && mainParCore2.status == FOREC_CORE_TERMINATED && mainParCore3.status == FOREC_CORE_TERMINATED) {
		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;
		
		// Set slave cores' status to reacting
		mainParCore1.status = FOREC_CORE_REACTING;
		mainParCore2.status = FOREC_CORE_REACTING;
		mainParCore3.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronization.
		mainParReactionCounter++;

		goto *mainParParent.programCounter;
	}

	// Set slave cores' status to reacting
	mainParCore1.status = FOREC_CORE_REACTING;
	mainParCore2.status = FOREC_CORE_REACTING;
	mainParCore3.status = FOREC_CORE_REACTING;

	// forec:scheduler:counter:start
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
		do_step_1__thread.programCounter = &&do_step_1__thread;
		mainReactionStartSlave1.nextThread = &do_step_1__thread;
		do_step_1__thread.prevThread = &mainReactionStartSlave1;
		mainReactionEndSlave1.programCounter = &&mainReactionEndSlave1;
		do_step_1__thread.nextThread = &mainReactionEndSlave1;
		mainReactionEndSlave1.prevThread = &do_step_1__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave1.nextThread = &mainReactionStartSlave1;
		mainReactionStartSlave1.prevThread = &mainReactionEndSlave1;

		// Set the core information.
		mainParCore1.activeThreads = 1;
		mainParCore1.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto do_step_1__thread;
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
		do_step_2__thread.programCounter = &&do_step_2__thread;
		mainReactionStartSlave2.nextThread = &do_step_2__thread;
		do_step_2__thread.prevThread = &mainReactionStartSlave2;
		mainReactionEndSlave2.programCounter = &&mainReactionEndSlave2;
		do_step_2__thread.nextThread = &mainReactionEndSlave2;
		mainReactionEndSlave2.prevThread = &do_step_2__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave2.nextThread = &mainReactionStartSlave2;
		mainReactionStartSlave2.prevThread = &mainReactionEndSlave2;

		// Set the core information.
		mainParCore2.activeThreads = 1;
		mainParCore2.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto do_step_2__thread;
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
		do_step_3__thread.programCounter = &&do_step_3__thread;
		mainReactionStartSlave3.nextThread = &do_step_3__thread;
		do_step_3__thread.prevThread = &mainReactionStartSlave3;
		mainReactionEndSlave3.programCounter = &&mainReactionEndSlave3;
		do_step_3__thread.nextThread = &mainReactionEndSlave3;
		mainReactionEndSlave3.prevThread = &do_step_3__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave3.nextThread = &mainReactionStartSlave3;
		mainReactionStartSlave3.prevThread = &mainReactionEndSlave3;

		// Set the core information.
		mainParCore3.activeThreads = 1;
		mainParCore3.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto do_step_3__thread;
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



/*==============================================================
| ForeC threads:
| Threads code translated into C code.
*=============================================================*/
	// forec:thread:do_step_0:start
	/*--------------------------------------------------------------
	| Thread do_step_0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	int RANGE__do_step_0_0_0;
	int ncols__do_step_0_0_0;
	int nrows__do_step_0_0_0;
	int threadNumber__do_step_0_0_0;
	int startIndex__do_step_0_0_0;
	int endIndex__do_step_0_0_0;
	int MAX_GENERATIONS__do_step_0_0_0;
	int generation__do_step_0_0_0;
	int i__do_step_0_1_0;

	// Thread body -------------------------------------------------
	do_step_0__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		RANGE__do_step_0_0_0 = 6;
		ncols__do_step_0_0_0 = 96;
		nrows__do_step_0_0_0 = 6*4;
		threadNumber__do_step_0_0_0 = 0;
		startIndex__do_step_0_0_0 = 1 + RANGE__do_step_0_0_0*threadNumber__do_step_0_0_0;
		endIndex__do_step_0_0_0 = RANGE__do_step_0_0_0*(threadNumber__do_step_0_0_0 + 1);
		MAX_GENERATIONS__do_step_0_0_0 = 2;
		generation__do_step_0_0_0 = 0;
		initialise(ncols__do_step_0_0_0, startIndex__do_step_0_0_0, endIndex__do_step_0_0_0, grid_ptr__global_0_0.value);

		while (generation__do_step_0_0_0++ < MAX_GENERATIONS__do_step_0_0_0) {
			for (i__do_step_0_1_0 = 0; i__do_step_0_1_0 <= nrows__do_step_0_0_0 + 1; i__do_step_0_1_0++) {
				(* grid_ptr__global_0_0.value)[0][i__do_step_0_1_0] = (* grid_ptr__global_0_0.value)[1][i__do_step_0_1_0];
				(* grid_ptr__global_0_0.value)[ncols__do_step_0_0_0 + 1][i__do_step_0_1_0] = (* grid_ptr__global_0_0.value)[ncols__do_step_0_0_0][i__do_step_0_1_0];
				asm volatile ("nop");
			}

			// pause;
			// forec:statement:pause:pause0:start
			do_step_0__thread.programCounter = &&pause0;
			goto *do_step_0__thread.nextThread -> programCounter;
			pause0:;
			// forec:statement:pause:pause0:end


			do_step(0, grid_ptr__global_0_0.value, next_grid_ptr__global_0_0.value);
			asm volatile ("nop");
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_step_0:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		do_step_0__thread.nextThread -> prevThread = do_step_0__thread.prevThread;
		do_step_0__thread.prevThread -> nextThread = do_step_0__thread.nextThread;
		goto *do_step_0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:do_step_0:end
	} // do_step_0__thread
	// forec:thread:do_step_0:end

	// forec:thread:do_step_1:start
	/*--------------------------------------------------------------
	| Thread do_step_1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	int RANGE__do_step_1_0_0;
	int ncols__do_step_1_0_0;
	int nrows__do_step_1_0_0;
	int threadNumber__do_step_1_0_0;
	int startIndex__do_step_1_0_0;
	int endIndex__do_step_1_0_0;
	int MAX_GENERATIONS__do_step_1_0_0;
	int generation__do_step_1_0_0;
	int i__do_step_1_1_0;

	// Thread body -------------------------------------------------
	do_step_1__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		RANGE__do_step_1_0_0 = 6;
		ncols__do_step_1_0_0 = 96;
		nrows__do_step_1_0_0 = 6*4;
		threadNumber__do_step_1_0_0 = 1;
		startIndex__do_step_1_0_0 = 1 + RANGE__do_step_1_0_0*threadNumber__do_step_1_0_0;
		endIndex__do_step_1_0_0 = RANGE__do_step_1_0_0*(threadNumber__do_step_1_0_0 + 1);
		MAX_GENERATIONS__do_step_1_0_0 = 2;
		generation__do_step_1_0_0 = 0;
		initialise(ncols__do_step_1_0_0, startIndex__do_step_1_0_0, endIndex__do_step_1_0_0, grid_ptr__global_0_0.value);

		while (generation__do_step_1_0_0++ < MAX_GENERATIONS__do_step_1_0_0) {
			for (i__do_step_1_1_0 = 1; i__do_step_1_1_0 <= ncols__do_step_1_0_0; i__do_step_1_1_0++) {
				(* grid_ptr__global_0_0.value)[i__do_step_1_1_0][0] = (* grid_ptr__global_0_0.value)[i__do_step_1_1_0][nrows__do_step_1_0_0];
				(* grid_ptr__global_0_0.value)[i__do_step_1_1_0][nrows__do_step_1_0_0 + 1] = (* grid_ptr__global_0_0.value)[i__do_step_1_1_0][1];
				asm volatile ("nop");
			}

			// pause;
			// forec:statement:pause:pause1:start
			do_step_1__thread.programCounter = &&pause1;
			goto *do_step_1__thread.nextThread -> programCounter;
			pause1:;
			// forec:statement:pause:pause1:end


			do_step(1, grid_ptr__global_0_0.value, next_grid_ptr__global_0_0.value);
			asm volatile ("nop");
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_step_1:start

		// Delete thread from the linked list and core.
		mainParCore1.activeThreads--;
		do_step_1__thread.nextThread -> prevThread = do_step_1__thread.prevThread;
		do_step_1__thread.prevThread -> nextThread = do_step_1__thread.nextThread;
		goto *do_step_1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:do_step_1:end
	} // do_step_1__thread
	// forec:thread:do_step_1:end

	// forec:thread:do_step_2:start
	/*--------------------------------------------------------------
	| Thread do_step_2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	int RANGE__do_step_2_0_0;
	int ncols__do_step_2_0_0;
	int nrows__do_step_2_0_0;
	int threadNumber__do_step_2_0_0;
	int startIndex__do_step_2_0_0;
	int endIndex__do_step_2_0_0;
	int MAX_GENERATIONS__do_step_2_0_0;
	int generation__do_step_2_0_0;

	// Thread body -------------------------------------------------
	do_step_2__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		RANGE__do_step_2_0_0 = 6;
		ncols__do_step_2_0_0 = 96;
		nrows__do_step_2_0_0 = 6*4;
		threadNumber__do_step_2_0_0 = 2;
		startIndex__do_step_2_0_0 = 1 + RANGE__do_step_2_0_0*threadNumber__do_step_2_0_0;
		endIndex__do_step_2_0_0 = RANGE__do_step_2_0_0*(threadNumber__do_step_2_0_0 + 1);
		MAX_GENERATIONS__do_step_2_0_0 = 2;
		generation__do_step_2_0_0 = 0;
		initialise(ncols__do_step_2_0_0, startIndex__do_step_2_0_0, endIndex__do_step_2_0_0, grid_ptr__global_0_0.value);

		while (generation__do_step_2_0_0++ < MAX_GENERATIONS__do_step_2_0_0) {
			(* grid_ptr__global_0_0.value)[0][0] = (* grid_ptr__global_0_0.value)[0][nrows__do_step_2_0_0];
			(* grid_ptr__global_0_0.value)[0][nrows__do_step_2_0_0 + 1] = (* grid_ptr__global_0_0.value)[0][1];
			(* grid_ptr__global_0_0.value)[ncols__do_step_2_0_0 + 1][0] = (* grid_ptr__global_0_0.value)[ncols__do_step_2_0_0 + 1][nrows__do_step_2_0_0];
			(* grid_ptr__global_0_0.value)[ncols__do_step_2_0_0 + 1][nrows__do_step_2_0_0 + 1] = (* grid_ptr__global_0_0.value)[ncols__do_step_2_0_0 + 1][1];

			// pause;
			// forec:statement:pause:pause2:start
			do_step_2__thread.programCounter = &&pause2;
			goto *do_step_2__thread.nextThread -> programCounter;
			pause2:;
			// forec:statement:pause:pause2:end


			do_step(2, grid_ptr__global_0_0.value, next_grid_ptr__global_0_0.value);
			asm volatile ("nop");
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_step_2:start

		// Delete thread from the linked list and core.
		mainParCore2.activeThreads--;
		do_step_2__thread.nextThread -> prevThread = do_step_2__thread.prevThread;
		do_step_2__thread.prevThread -> nextThread = do_step_2__thread.nextThread;
		goto *do_step_2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:do_step_2:end
	} // do_step_2__thread
	// forec:thread:do_step_2:end

	// forec:thread:do_step_3:start
	/*--------------------------------------------------------------
	| Thread do_step_3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	int RANGE__do_step_3_0_0;
	int ncols__do_step_3_0_0;
	int threadNumber__do_step_3_0_0;
	int startIndex__do_step_3_0_0;
	int endIndex__do_step_3_0_0;
	int MAX_GENERATIONS__do_step_3_0_0;
	int generation__do_step_3_0_0;

	// Thread body -------------------------------------------------
	do_step_3__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		RANGE__do_step_3_0_0 = 6;
		ncols__do_step_3_0_0 = 96;
		threadNumber__do_step_3_0_0 = 3;
		startIndex__do_step_3_0_0 = 1 + RANGE__do_step_3_0_0*threadNumber__do_step_3_0_0;
		endIndex__do_step_3_0_0 = RANGE__do_step_3_0_0*(threadNumber__do_step_3_0_0 + 1);
		MAX_GENERATIONS__do_step_3_0_0 = 2;
		generation__do_step_3_0_0 = 0;
		initialise(ncols__do_step_3_0_0, startIndex__do_step_3_0_0, endIndex__do_step_3_0_0, grid_ptr__global_0_0.value);

		while (generation__do_step_3_0_0++ < MAX_GENERATIONS__do_step_3_0_0) {
			// pause;
			// forec:statement:pause:pause3:start
			do_step_3__thread.programCounter = &&pause3;
			goto *do_step_3__thread.nextThread -> programCounter;
			pause3:;
			// forec:statement:pause:pause3:end


			do_step(3, grid_ptr__global_0_0.value, next_grid_ptr__global_0_0.value);
			asm volatile ("nop");
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_step_3:start

		// Delete thread from the linked list and core.
		mainParCore3.activeThreads--;
		do_step_3__thread.nextThread -> prevThread = do_step_3__thread.prevThread;
		do_step_3__thread.prevThread -> nextThread = do_step_3__thread.nextThread;
		goto *do_step_3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:do_step_3:end
	} // do_step_3__thread
	// forec:thread:do_step_3:end


} // End of the main() function.

void do_step(const int threadNumber__do_step_0_0, int (*grid_ptr__do_step_0_0)[96 + 2][24 + 2], int (*next_grid_ptr__do_step_0_0)[96 + 2][24 + 2]) {
	int RANGE__do_step_0_0 = 6;
	int ncols__do_step_0_0 = 96;
	int startIndex__do_step_0_0 = 1 + RANGE__do_step_0_0*threadNumber__do_step_0_0;
	int endIndex__do_step_0_0 = RANGE__do_step_0_0*(threadNumber__do_step_0_0 + 1);
	int i__do_step_0_0;
	for (i__do_step_0_0 = 1; i__do_step_0_0 <= ncols__do_step_0_0; i__do_step_0_0++) {
		int j__do_step_1_0;
		for (j__do_step_1_0 = startIndex__do_step_0_0; j__do_step_1_0 <= endIndex__do_step_0_0; j__do_step_1_0++) {
			int neighbors__do_step_2_0 = 0;
			int k__do_step_2_0;
			for (k__do_step_2_0 = i__do_step_0_0 - 1; k__do_step_2_0 <= i__do_step_0_0 + 1; k__do_step_2_0++) {
				int l__do_step_3_0;
				for (l__do_step_3_0 = j__do_step_1_0 - 1; l__do_step_3_0 <= j__do_step_1_0 + 1; l__do_step_3_0++) {
					if (!(k__do_step_2_0 == i__do_step_0_0 && l__do_step_3_0 == j__do_step_1_0) && (* grid_ptr__do_step_0_0)[k__do_step_2_0][l__do_step_3_0] > 0) {
						neighbors__do_step_2_0++;
					} else {
						// if0
					}
					asm volatile ("nop");
				}
				if (neighbors__do_step_2_0 > 3) {
					continue;
				} else {
					// if1
				}
				asm volatile ("nop");
			}
			if (neighbors__do_step_2_0 < 2 || neighbors__do_step_2_0 > 3) {
				(* next_grid_ptr__do_step_0_0)[i__do_step_0_0][j__do_step_1_0] = 0;
			} else {
				// ifElse3
				if ((* grid_ptr__do_step_0_0)[i__do_step_0_0][j__do_step_1_0] > 0 || neighbors__do_step_2_0 == 3) {
					(* next_grid_ptr__do_step_0_0)[i__do_step_0_0][j__do_step_1_0] = (* grid_ptr__do_step_0_0)[i__do_step_0_0][j__do_step_1_0] + 1;
				} else {
					// if2
				}
			}
			asm volatile ("nop");
		}
		asm volatile ("nop");
	}
	for (i__do_step_0_0 = 0; i__do_step_0_0 < ncols__do_step_0_0 + 2; i__do_step_0_0++) {
		int j__do_step_1_1;
		for (j__do_step_1_1 = startIndex__do_step_0_0; j__do_step_1_1 <= endIndex__do_step_0_0; j__do_step_1_1++) {
			(* grid_ptr__do_step_0_0)[i__do_step_0_0][j__do_step_1_1] = (* next_grid_ptr__do_step_0_0)[i__do_step_0_0][j__do_step_1_1];
			asm volatile ("nop");
		}
		asm volatile ("nop");
	}
}

void initialise(const int ncols__initialise_0_0, const int startIndex__initialise_0_0, const int endIndex__initialise_0_0, int (*grid_ptr__initialise_0_0)[96 + 2][24 + 2]) {
	srand(0x0);
	randomize_grid(ncols__initialise_0_0, startIndex__initialise_0_0, endIndex__initialise_0_0, grid_ptr__initialise_0_0, 0.25);
}

void randomize_grid(const int ncols__randomize_grid_0_0, const int startIndex__randomize_grid_0_0, const int endIndex__randomize_grid_0_0, int (*grid_ptr__randomize_grid_0_0)[96 + 2][24 + 2], const float prob__randomize_grid_0_0) {
	int i__randomize_grid_0_0;
	for (i__randomize_grid_0_0 = 1; i__randomize_grid_0_0 <= ncols__randomize_grid_0_0; i__randomize_grid_0_0++) {
		int j__randomize_grid_1_0;
		for (j__randomize_grid_1_0 = startIndex__randomize_grid_0_0; j__randomize_grid_1_0 <= endIndex__randomize_grid_0_0; j__randomize_grid_1_0++) {
			(* grid_ptr__randomize_grid_0_0)[i__randomize_grid_0_0][j__randomize_grid_1_0] = rand_float() < prob__randomize_grid_0_0;
			asm volatile ("nop");
		}
		asm volatile ("nop");
	}
}

float rand_float(void) {
	return (float)rand()/(float)RAND_MAX__global_0_0;
}

