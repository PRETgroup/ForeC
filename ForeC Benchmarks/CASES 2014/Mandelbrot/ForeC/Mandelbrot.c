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
	unsigned short int parStatus;
	short int parId;
} Parent;

// Keep track of child threads executing on
// a processor core.
typedef struct {
	unsigned short int sync;
	unsigned short int activeThreads;
	unsigned short int status;
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
#include <float.h>

int FLT_MAX__global_0_0;

#define FLT_MAX__global_0_0 FLT_MAX

int FLT_MIN__global_0_0;

#define FLT_MIN__global_0_0 FLT_MIN

int FLT_EPSILON__global_0_0;

#define FLT_EPSILON__global_0_0 FLT_EPSILON

const int ColormapSize__global_0_0 = 128;
const int problemSize__global_0_0 = 10;
const float centerX__global_0_0 = -0.637011f;
const float centerY__global_0_0 = -0.0395159f;
const float pixmapScale__global_0_0 = 0.00403897f;
const int resultWidth__global_0_0 = 220;
const int resultHeight__global_0_0 = 160;

typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} Pixel__global_0_0;

unsigned colormap__global_0_0[128];
Pixel__global_0_0 image__global_0_0[160][220];

void compute(int threadId);
void init(int threadId);
void calculate(int x, int y);
unsigned rgbFromWaveLength(float wave);
Pixel__global_0_0 uintToRgb(unsigned rgb);
float fs_pow(float x, float y);
float fs_fmod(float x, float y);
float fs_exp(float x);
float fs_log(float x);
float fs_sqrt(float x);

// thread region0__thread(void);
// thread region1__thread(void);
// thread region2__thread(void);
// thread region3__thread(void);
// thread region4__thread(void);
// thread region5__thread(void);
// thread region6__thread(void);
// thread region7__thread(void);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// main
// region0
// region1
// region2
// region3
// region4
// region5
// region6
// region7

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
	Thread region0__thread;
	Thread region1__thread;
	Thread region2__thread;
	Thread region3__thread;
	Thread region4__thread;
	Thread region5__thread;
	Thread region6__thread;
	Thread region7__thread;
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
	
	// Initialise the local copies of shared variables.
	//--------------------------------------------------------------

	// par0(region0__thread, region1__thread, region2__thread, region3__thread, region4__thread, region5__thread, region6__thread, region7__thread);
	// Set the par(...) information.
	mainParParent.parId = 0;
	mainParParent.parStatus = FOREC_PAR_ON;

	// Link the threads and handlers together.
	mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
	region0__thread.programCounter = &&region0__thread;
	mainReactionStartMaster0.nextThread = &region0__thread;
	region0__thread.prevThread = &mainReactionStartMaster0;
	region1__thread.programCounter = &&region1__thread;
	region0__thread.nextThread = &region1__thread;
	region1__thread.prevThread = &region0__thread;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	region1__thread.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &region1__thread;

	// Link the last and first threads/handlers together.
	mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
	mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

	// Set the join address.
	mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

	// Set the core information.
	mainParCore0.activeThreads = 2;
	mainParCore0.reactionCounter = mainParReactionCounter;

	// Go to the first thread.
	// forec:statement:par:par0:start
	goto region0__thread;
	par0JoinAddress_mainParCore0:;
	// forec:statement:par:par0:end

	//--------------------------------------------------------------
	// Write the defined shared variables back to their global copy.

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

	short int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave1.programCounter = &&mainReactionStartSlave1;
		region2__thread.programCounter = &&region2__thread;
		mainReactionStartSlave1.nextThread = &region2__thread;
		region2__thread.prevThread = &mainReactionStartSlave1;
		region3__thread.programCounter = &&region3__thread;
		region2__thread.nextThread = &region3__thread;
		region3__thread.prevThread = &region2__thread;
		mainReactionEndSlave1.programCounter = &&mainReactionEndSlave1;
		region3__thread.nextThread = &mainReactionEndSlave1;
		mainReactionEndSlave1.prevThread = &region3__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave1.nextThread = &mainReactionStartSlave1;
		mainReactionStartSlave1.prevThread = &mainReactionEndSlave1;

		// Set the core information.
		mainParCore1.activeThreads = 2;
		mainParCore1.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto region2__thread;
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
		short int parId = mainParParent.parId;

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

	short int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave2.programCounter = &&mainReactionStartSlave2;
		region4__thread.programCounter = &&region4__thread;
		mainReactionStartSlave2.nextThread = &region4__thread;
		region4__thread.prevThread = &mainReactionStartSlave2;
		region5__thread.programCounter = &&region5__thread;
		region4__thread.nextThread = &region5__thread;
		region5__thread.prevThread = &region4__thread;
		mainReactionEndSlave2.programCounter = &&mainReactionEndSlave2;
		region5__thread.nextThread = &mainReactionEndSlave2;
		mainReactionEndSlave2.prevThread = &region5__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave2.nextThread = &mainReactionStartSlave2;
		mainReactionStartSlave2.prevThread = &mainReactionEndSlave2;

		// Set the core information.
		mainParCore2.activeThreads = 2;
		mainParCore2.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto region4__thread;
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
		short int parId = mainParParent.parId;

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

	short int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave3.programCounter = &&mainReactionStartSlave3;
		region6__thread.programCounter = &&region6__thread;
		mainReactionStartSlave3.nextThread = &region6__thread;
		region6__thread.prevThread = &mainReactionStartSlave3;
		region7__thread.programCounter = &&region7__thread;
		region6__thread.nextThread = &region7__thread;
		region7__thread.prevThread = &region6__thread;
		mainReactionEndSlave3.programCounter = &&mainReactionEndSlave3;
		region7__thread.nextThread = &mainReactionEndSlave3;
		mainReactionEndSlave3.prevThread = &region7__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave3.nextThread = &mainReactionStartSlave3;
		mainReactionStartSlave3.prevThread = &mainReactionEndSlave3;

		// Set the core information.
		mainParCore3.activeThreads = 2;
		mainParCore3.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto region6__thread;
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
		short int parId = mainParParent.parId;

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
	// forec:thread:region0:start
	/*--------------------------------------------------------------
	| Thread region0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	region0__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		init(0);

		// pause;
		// forec:statement:pause:pause0:start
		region0__thread.programCounter = &&pause0;
		goto *region0__thread.nextThread -> programCounter;
		pause0:;
		// forec:statement:pause:pause0:end


		compute(0);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:region0:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		region0__thread.nextThread -> prevThread = region0__thread.prevThread;
		region0__thread.prevThread -> nextThread = region0__thread.nextThread;
		goto *region0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:region0:end
	} // region0__thread
	// forec:thread:region0:end

	// forec:thread:region1:start
	/*--------------------------------------------------------------
	| Thread region1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	region1__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		init(1);

		// pause;
		// forec:statement:pause:pause1:start
		region1__thread.programCounter = &&pause1;
		goto *region1__thread.nextThread -> programCounter;
		pause1:;
		// forec:statement:pause:pause1:end


		compute(1);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:region1:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		region1__thread.nextThread -> prevThread = region1__thread.prevThread;
		region1__thread.prevThread -> nextThread = region1__thread.nextThread;
		goto *region1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:region1:end
	} // region1__thread
	// forec:thread:region1:end

	// forec:thread:region2:start
	/*--------------------------------------------------------------
	| Thread region2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	region2__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		init(2);

		// pause;
		// forec:statement:pause:pause2:start
		region2__thread.programCounter = &&pause2;
		goto *region2__thread.nextThread -> programCounter;
		pause2:;
		// forec:statement:pause:pause2:end


		compute(2);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:region2:start

		// Delete thread from the linked list and core.
		mainParCore1.activeThreads--;
		region2__thread.nextThread -> prevThread = region2__thread.prevThread;
		region2__thread.prevThread -> nextThread = region2__thread.nextThread;
		goto *region2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:region2:end
	} // region2__thread
	// forec:thread:region2:end

	// forec:thread:region3:start
	/*--------------------------------------------------------------
	| Thread region3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	region3__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		init(3);

		// pause;
		// forec:statement:pause:pause3:start
		region3__thread.programCounter = &&pause3;
		goto *region3__thread.nextThread -> programCounter;
		pause3:;
		// forec:statement:pause:pause3:end


		compute(3);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:region3:start

		// Delete thread from the linked list and core.
		mainParCore1.activeThreads--;
		region3__thread.nextThread -> prevThread = region3__thread.prevThread;
		region3__thread.prevThread -> nextThread = region3__thread.nextThread;
		goto *region3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:region3:end
	} // region3__thread
	// forec:thread:region3:end

	// forec:thread:region4:start
	/*--------------------------------------------------------------
	| Thread region4
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	region4__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		init(4);

		// pause;
		// forec:statement:pause:pause4:start
		region4__thread.programCounter = &&pause4;
		goto *region4__thread.nextThread -> programCounter;
		pause4:;
		// forec:statement:pause:pause4:end


		compute(4);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:region4:start

		// Delete thread from the linked list and core.
		mainParCore2.activeThreads--;
		region4__thread.nextThread -> prevThread = region4__thread.prevThread;
		region4__thread.prevThread -> nextThread = region4__thread.nextThread;
		goto *region4__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:region4:end
	} // region4__thread
	// forec:thread:region4:end

	// forec:thread:region5:start
	/*--------------------------------------------------------------
	| Thread region5
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	region5__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		init(5);

		// pause;
		// forec:statement:pause:pause5:start
		region5__thread.programCounter = &&pause5;
		goto *region5__thread.nextThread -> programCounter;
		pause5:;
		// forec:statement:pause:pause5:end


		compute(5);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:region5:start

		// Delete thread from the linked list and core.
		mainParCore2.activeThreads--;
		region5__thread.nextThread -> prevThread = region5__thread.prevThread;
		region5__thread.prevThread -> nextThread = region5__thread.nextThread;
		goto *region5__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:region5:end
	} // region5__thread
	// forec:thread:region5:end

	// forec:thread:region6:start
	/*--------------------------------------------------------------
	| Thread region6
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	region6__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		init(6);

		// pause;
		// forec:statement:pause:pause6:start
		region6__thread.programCounter = &&pause6;
		goto *region6__thread.nextThread -> programCounter;
		pause6:;
		// forec:statement:pause:pause6:end


		compute(6);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:region6:start

		// Delete thread from the linked list and core.
		mainParCore3.activeThreads--;
		region6__thread.nextThread -> prevThread = region6__thread.prevThread;
		region6__thread.prevThread -> nextThread = region6__thread.nextThread;
		goto *region6__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:region6:end
	} // region6__thread
	// forec:thread:region6:end

	// forec:thread:region7:start
	/*--------------------------------------------------------------
	| Thread region7
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	region7__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		init(7);

		// pause;
		// forec:statement:pause:pause7:start
		region7__thread.programCounter = &&pause7;
		goto *region7__thread.nextThread -> programCounter;
		pause7:;
		// forec:statement:pause:pause7:end


		compute(7);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:region7:start

		// Delete thread from the linked list and core.
		mainParCore3.activeThreads--;
		region7__thread.nextThread -> prevThread = region7__thread.prevThread;
		region7__thread.prevThread -> nextThread = region7__thread.nextThread;
		goto *region7__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:region7:end
	} // region7__thread
	// forec:thread:region7:end


} // End of the main() function.

void compute(int threadId__compute_0_0) {
	const int NUMBER_OF_THREADS__compute_0_0 = 8;
	const int y_RANGE__compute_0_0 = resultHeight__global_0_0/NUMBER_OF_THREADS__compute_0_0;
	int y__compute_0_0;
	for (y__compute_0_0 = (threadId__compute_0_0*y_RANGE__compute_0_0); y__compute_0_0 < ((threadId__compute_0_0 + 1)*y_RANGE__compute_0_0); ++y__compute_0_0) {
		int x__compute_1_0;
		for (x__compute_1_0 = 0; x__compute_1_0 < resultWidth__global_0_0; ++x__compute_1_0) {
			calculate(x__compute_1_0, 0);
			asm volatile ("nop");
		}
		asm volatile ("nop");
	}
}

void init(int threadId__init_0_0) {
	const int NUMBER_OF_THREADS__init_0_0 = 8;
	const int i_RANGE__init_0_0 = ColormapSize__global_0_0/NUMBER_OF_THREADS__init_0_0;
	int i__init_0_0;
	for (i__init_0_0 = (threadId__init_0_0*i_RANGE__init_0_0); i__init_0_0 < ((threadId__init_0_0 + 1)*i_RANGE__init_0_0); ++i__init_0_0) {
		colormap__global_0_0[i__init_0_0] = rgbFromWaveLength(380.0 + (i__init_0_0*400.0/ColormapSize__global_0_0));
		asm volatile ("nop");
	}
}

void calculate(int x__calculate_0_0, int y__calculate_0_0) {
	const int halfWidth__calculate_0_0 = resultWidth__global_0_0/2;
	const int halfHeight__calculate_0_0 = resultHeight__global_0_0/2;
	const int pass__calculate_0_0 = problemSize__global_0_0 - 1;
	const int MaxIterations__calculate_0_0 = (1 << (2*pass__calculate_0_0 + 6)) + 32;
	const int Limit__calculate_0_0 = 4;
	const int mod_x__calculate_0_0 = x__calculate_0_0 - halfWidth__calculate_0_0;
	const int mod_y__calculate_0_0 = y__calculate_0_0 - halfHeight__calculate_0_0;
	const float ay__calculate_0_0 = centerY__global_0_0 + (mod_y__calculate_0_0*pixmapScale__global_0_0);
	const float ax__calculate_0_0 = centerX__global_0_0 + (mod_x__calculate_0_0*pixmapScale__global_0_0);
	float a1__calculate_0_0 = ax__calculate_0_0;
	float b1__calculate_0_0 = ay__calculate_0_0;
	int numIterations__calculate_0_0 = 0;
	do {
		++numIterations__calculate_0_0;
		float a2__calculate_1_0 = (a1__calculate_0_0*a1__calculate_0_0) - (b1__calculate_0_0*b1__calculate_0_0) + ax__calculate_0_0;
		float b2__calculate_1_0 = (2*a1__calculate_0_0*b1__calculate_0_0) + ay__calculate_0_0;
		if ((a2__calculate_1_0*a2__calculate_1_0) + (b2__calculate_1_0*b2__calculate_1_0) > Limit__calculate_0_0) {
			break;
		} else {
			// if0
		}
		++numIterations__calculate_0_0;
		a1__calculate_0_0 = (a2__calculate_1_0*a2__calculate_1_0) - (b2__calculate_1_0*b2__calculate_1_0) + ax__calculate_0_0;
		b1__calculate_0_0 = (2*a2__calculate_1_0*b2__calculate_1_0) + ay__calculate_0_0;
		if ((a1__calculate_0_0*a1__calculate_0_0) + (b1__calculate_0_0*b1__calculate_0_0) > Limit__calculate_0_0) {
			break;
		} else {
			// if1
		}
		asm volatile ("nop");
	} while (numIterations__calculate_0_0 < MaxIterations__calculate_0_0);
	if (numIterations__calculate_0_0 < MaxIterations__calculate_0_0) {
		image__global_0_0[y__calculate_0_0][x__calculate_0_0] = uintToRgb(colormap__global_0_0[numIterations__calculate_0_0%ColormapSize__global_0_0]);
	} else {
		// ifElse2
		image__global_0_0[y__calculate_0_0][x__calculate_0_0] = uintToRgb(0);
	}
}

unsigned rgbFromWaveLength(float wave__rgbFromWaveLength_0_0) {
	unsigned char rr__rgbFromWaveLength_0_0;
	unsigned char gg__rgbFromWaveLength_0_0;
	unsigned char bb__rgbFromWaveLength_0_0;
	float r__rgbFromWaveLength_0_0 = 0.0;
	float g__rgbFromWaveLength_0_0 = 0.0;
	float b__rgbFromWaveLength_0_0 = 0.0;
	if (wave__rgbFromWaveLength_0_0 >= 380.0 && wave__rgbFromWaveLength_0_0 <= 440.0) {
		r__rgbFromWaveLength_0_0 = -1.0*(wave__rgbFromWaveLength_0_0 - 440.0)/(440.0 - 380.0);
		b__rgbFromWaveLength_0_0 = 1.0;
	} else {
		// ifElse8
		if (wave__rgbFromWaveLength_0_0 >= 440.0 && wave__rgbFromWaveLength_0_0 <= 490.0) {
			g__rgbFromWaveLength_0_0 = (wave__rgbFromWaveLength_0_0 - 440.0)/(490.0 - 440.0);
			b__rgbFromWaveLength_0_0 = 1.0;
		} else {
			// ifElse7
			if (wave__rgbFromWaveLength_0_0 >= 490.0 && wave__rgbFromWaveLength_0_0 <= 510.0) {
				g__rgbFromWaveLength_0_0 = 1.0;
				b__rgbFromWaveLength_0_0 = -1.0*(wave__rgbFromWaveLength_0_0 - 510.0)/(510.0 - 490.0);
			} else {
				// ifElse6
				if (wave__rgbFromWaveLength_0_0 >= 510.0 && wave__rgbFromWaveLength_0_0 <= 580.0) {
					r__rgbFromWaveLength_0_0 = (wave__rgbFromWaveLength_0_0 - 510.0)/(580.0 - 510.0);
					g__rgbFromWaveLength_0_0 = 1.0;
				} else {
					// ifElse5
					if (wave__rgbFromWaveLength_0_0 >= 580.0 && wave__rgbFromWaveLength_0_0 <= 645.0) {
						r__rgbFromWaveLength_0_0 = 1.0;
						g__rgbFromWaveLength_0_0 = -1.0*(wave__rgbFromWaveLength_0_0 - 645.0)/(645.0 - 580.0);
					} else {
						// ifElse4
						if (wave__rgbFromWaveLength_0_0 >= 645.0 && wave__rgbFromWaveLength_0_0 <= 780.0) {
							r__rgbFromWaveLength_0_0 = 1.0;
						} else {
							// if3
						}
					}
				}
			}
		}
	}
	float s__rgbFromWaveLength_0_0 = 1.0;
	if (wave__rgbFromWaveLength_0_0 > 700.0) {
		s__rgbFromWaveLength_0_0 = 0.3 + 0.7*(780.0 - wave__rgbFromWaveLength_0_0)/(780.0 - 700.0);
	} else {
		// ifElse10
		if (wave__rgbFromWaveLength_0_0 < 420.0) {
			s__rgbFromWaveLength_0_0 = 0.3 + 0.7*(wave__rgbFromWaveLength_0_0 - 380.0)/(420.0 - 380.0);
		} else {
			// if9
		}
	}
	r__rgbFromWaveLength_0_0 = fs_pow(r__rgbFromWaveLength_0_0*s__rgbFromWaveLength_0_0, 0.8);
	g__rgbFromWaveLength_0_0 = fs_pow(g__rgbFromWaveLength_0_0*s__rgbFromWaveLength_0_0, 0.8);
	b__rgbFromWaveLength_0_0 = fs_pow(b__rgbFromWaveLength_0_0*s__rgbFromWaveLength_0_0, 0.8);
	rr__rgbFromWaveLength_0_0 = (r__rgbFromWaveLength_0_0*255);
	gg__rgbFromWaveLength_0_0 = (g__rgbFromWaveLength_0_0*255);
	bb__rgbFromWaveLength_0_0 = (b__rgbFromWaveLength_0_0*255);
	return 0xFF000000 + (rr__rgbFromWaveLength_0_0 << 16) + (gg__rgbFromWaveLength_0_0 << 8) + bb__rgbFromWaveLength_0_0;
}

Pixel__global_0_0 uintToRgb(unsigned rgb__uintToRgb_0_0) {
	Pixel__global_0_0 p__uintToRgb_0_0 = {0, 0, 0};
	if (rgb__uintToRgb_0_0 != 0) {
		p__uintToRgb_0_0.r = (rgb__uintToRgb_0_0 & 0x00FF0000) >> 16;
		p__uintToRgb_0_0.g = (rgb__uintToRgb_0_0 & 0x0000FF00) >> 8;
		p__uintToRgb_0_0.b = (rgb__uintToRgb_0_0 & 0x000000FF);
	} else {
		// if11
	}
	return p__uintToRgb_0_0;
}

float fs_pow(float x__fs_pow_0_0, float y__fs_pow_0_0) {
	float p__fs_pow_0_0 = 0;
	if (0 > x__fs_pow_0_0 && fs_fmod(y__fs_pow_0_0, 1) == 0) {
		if (fs_fmod(y__fs_pow_0_0, 2) == 0) {
			p__fs_pow_0_0 = fs_exp(fs_log(-x__fs_pow_0_0)*y__fs_pow_0_0);
		} else {
			// ifElse12
			p__fs_pow_0_0 = -fs_exp(fs_log(-x__fs_pow_0_0)*y__fs_pow_0_0);
		}
	} else {
		// ifElse14
		if (x__fs_pow_0_0 != 0 || 0 >= y__fs_pow_0_0) {
			p__fs_pow_0_0 = fs_exp(fs_log(x__fs_pow_0_0)*y__fs_pow_0_0);
		} else {
			// if13
		}
	}
	return p__fs_pow_0_0;
}

float fs_fmod(float x__fs_fmod_0_0, float y__fs_fmod_0_0) {
	float a__fs_fmod_0_0, b__fs_fmod_0_0;
	const float c__fs_fmod_0_0 = x__fs_fmod_0_0;
	if (0 > c__fs_fmod_0_0) {
		x__fs_fmod_0_0 = -x__fs_fmod_0_0;
	} else {
		// if15
	}
	if (0 > y__fs_fmod_0_0) {
		y__fs_fmod_0_0 = -y__fs_fmod_0_0;
	} else {
		// if16
	}
	if (y__fs_fmod_0_0 != 0 && FLT_MAX__global_0_0 >= y__fs_fmod_0_0 && FLT_MAX__global_0_0 >= x__fs_fmod_0_0) {
		while (x__fs_fmod_0_0 >= y__fs_fmod_0_0) {
			a__fs_fmod_0_0 = x__fs_fmod_0_0/2;
			b__fs_fmod_0_0 = y__fs_fmod_0_0;
			while (a__fs_fmod_0_0 >= b__fs_fmod_0_0) {
				b__fs_fmod_0_0 *= 2;
				asm volatile ("nop");
			}
			x__fs_fmod_0_0 -= b__fs_fmod_0_0;
			asm volatile ("nop");
		}
	} else {
		// ifElse17
		x__fs_fmod_0_0 = 0;
	}
	return 0 > c__fs_fmod_0_0 ? -x__fs_fmod_0_0 : x__fs_fmod_0_0;
}

float fs_exp(float x__fs_exp_0_0) {
	unsigned n__fs_exp_0_0, square__fs_exp_0_0;
	float b__fs_exp_0_0, e__fs_exp_0_0;
	static float x_max__fs_exp_0_0, x_min__fs_exp_0_0, epsilon__fs_exp_0_0;
	static int initialized__fs_exp_0_0;
	if (!initialized__fs_exp_0_0) {
		initialized__fs_exp_0_0 = 1;
		x_max__fs_exp_0_0 = fs_log(FLT_MAX__global_0_0);
		x_min__fs_exp_0_0 = fs_log(FLT_MIN__global_0_0);
		epsilon__fs_exp_0_0 = FLT_EPSILON__global_0_0/4;
	} else {
		// if18
	}
	if (x_max__fs_exp_0_0 >= x__fs_exp_0_0 && x__fs_exp_0_0 >= x_min__fs_exp_0_0) {
		for (square__fs_exp_0_0 = 0; x__fs_exp_0_0 > 1; x__fs_exp_0_0 /= 2) {
			++square__fs_exp_0_0;
			asm volatile ("nop");
		}
		while (-1 > x__fs_exp_0_0) {
			++square__fs_exp_0_0;
			x__fs_exp_0_0 /= 2;
			asm volatile ("nop");
		}
		e__fs_exp_0_0 = b__fs_exp_0_0 = n__fs_exp_0_0 = 1;
		do {
			b__fs_exp_0_0 /= n__fs_exp_0_0++;
			b__fs_exp_0_0 *= x__fs_exp_0_0;
			e__fs_exp_0_0 += b__fs_exp_0_0;
			b__fs_exp_0_0 /= n__fs_exp_0_0++;
			b__fs_exp_0_0 *= x__fs_exp_0_0;
			e__fs_exp_0_0 += b__fs_exp_0_0;
			asm volatile ("nop");
		} while (b__fs_exp_0_0 > epsilon__fs_exp_0_0);
		while (square__fs_exp_0_0-- != 0) {
			e__fs_exp_0_0 *= e__fs_exp_0_0;
			asm volatile ("nop");
		}
	} else {
		// ifElse19
		e__fs_exp_0_0 = x__fs_exp_0_0 > 0 ? FLT_MAX__global_0_0 : 0;
	}
	return e__fs_exp_0_0;
}

float fs_log(float x__fs_log_0_0) {
	int n__fs_log_0_0;
	float a__fs_log_0_0, b__fs_log_0_0, c__fs_log_0_0, epsilon__fs_log_0_0;
	static float A__fs_log_0_0, B__fs_log_0_0, C__fs_log_0_0;
	static int initialized__fs_log_0_0;
	if (x__fs_log_0_0 > 0 && FLT_MAX__global_0_0 >= x__fs_log_0_0) {
		if (!initialized__fs_log_0_0) {
			initialized__fs_log_0_0 = 1;
			A__fs_log_0_0 = fs_sqrt(2);
			B__fs_log_0_0 = A__fs_log_0_0/2;
			C__fs_log_0_0 = fs_log(A__fs_log_0_0);
		} else {
			// if20
		}
		for (n__fs_log_0_0 = 0; x__fs_log_0_0 > A__fs_log_0_0; x__fs_log_0_0 /= 2) {
			++n__fs_log_0_0;
			asm volatile ("nop");
		}
		while (B__fs_log_0_0 > x__fs_log_0_0) {
			--n__fs_log_0_0;
			x__fs_log_0_0 *= 2;
			asm volatile ("nop");
		}
		a__fs_log_0_0 = (x__fs_log_0_0 - 1)/(x__fs_log_0_0 + 1);
		x__fs_log_0_0 = C__fs_log_0_0*n__fs_log_0_0 + a__fs_log_0_0;
		c__fs_log_0_0 = a__fs_log_0_0*a__fs_log_0_0;
		n__fs_log_0_0 = 1;
		epsilon__fs_log_0_0 = FLT_EPSILON__global_0_0*x__fs_log_0_0;
		if (0 > a__fs_log_0_0) {
			if (epsilon__fs_log_0_0 > 0) {
				epsilon__fs_log_0_0 = -epsilon__fs_log_0_0;
			} else {
				// if21
			}
			do {
				n__fs_log_0_0 += 2;
				a__fs_log_0_0 *= c__fs_log_0_0;
				b__fs_log_0_0 = a__fs_log_0_0/n__fs_log_0_0;
				x__fs_log_0_0 += b__fs_log_0_0;
				asm volatile ("nop");
			} while (epsilon__fs_log_0_0 > b__fs_log_0_0);
		} else {
			// ifElse23
			if (0 > epsilon__fs_log_0_0) {
				epsilon__fs_log_0_0 = -epsilon__fs_log_0_0;
			} else {
				// if22
			}
			do {
				n__fs_log_0_0 += 2;
				a__fs_log_0_0 *= c__fs_log_0_0;
				b__fs_log_0_0 = a__fs_log_0_0/n__fs_log_0_0;
				x__fs_log_0_0 += b__fs_log_0_0;
				asm volatile ("nop");
			} while (b__fs_log_0_0 > epsilon__fs_log_0_0);
		}
		x__fs_log_0_0 *= 2;
	} else {
		// ifElse24
		x__fs_log_0_0 = -FLT_MAX__global_0_0;
	}
	return x__fs_log_0_0;
}

float fs_sqrt(float x__fs_sqrt_0_0) {
	int n__fs_sqrt_0_0;
	float a__fs_sqrt_0_0, b__fs_sqrt_0_0;
	if (x__fs_sqrt_0_0 > 0 && FLT_MAX__global_0_0 >= x__fs_sqrt_0_0) {
		for (n__fs_sqrt_0_0 = 0; x__fs_sqrt_0_0 > 2; x__fs_sqrt_0_0 /= 4) {
			++n__fs_sqrt_0_0;
			asm volatile ("nop");
		}
		while (0.5 > x__fs_sqrt_0_0) {
			--n__fs_sqrt_0_0;
			x__fs_sqrt_0_0 *= 4;
			asm volatile ("nop");
		}
		a__fs_sqrt_0_0 = x__fs_sqrt_0_0;
		b__fs_sqrt_0_0 = (1 + x__fs_sqrt_0_0)/2;
		do {
			x__fs_sqrt_0_0 = b__fs_sqrt_0_0;
			b__fs_sqrt_0_0 = (a__fs_sqrt_0_0/x__fs_sqrt_0_0 + x__fs_sqrt_0_0)/2;
			asm volatile ("nop");
		} while (x__fs_sqrt_0_0 > b__fs_sqrt_0_0);
		while (n__fs_sqrt_0_0 > 0) {
			x__fs_sqrt_0_0 *= 2;
			--n__fs_sqrt_0_0;
			asm volatile ("nop");
		}
		while (0 > n__fs_sqrt_0_0) {
			x__fs_sqrt_0_0 /= 2;
			++n__fs_sqrt_0_0;
			asm volatile ("nop");
		}
	} else {
		// ifElse26
		if (x__fs_sqrt_0_0 != 0) {
			x__fs_sqrt_0_0 = FLT_MAX__global_0_0;
		} else {
			// if25
		}
	}
	return x__fs_sqrt_0_0;
}

