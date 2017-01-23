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
volatile int mainParReactionCounter;


/*==============================================================
| Original global declarations:
| Global declarations in the original program code.
*=============================================================*/
#include <stdio.h>

typedef struct {
	/* shared */ int value;
	int status;
} Shared_SIZE__global_0_0;
Shared_SIZE__global_0_0 SIZE__global_0_0 = {.value = 80, .status = FOREC_SHARED_UNMODIFIED};

int NumberOfFillThreads__global_0_0 = 4;
int NumberOfMultiplyThreads__global_0_0 = 8;
int A__global_0_0[80][80] = {{0}};
int B__global_0_0[80][80] = {{0}};
int C__global_0_0[80][80] = {{0}};

typedef struct {
	/* shared */ int (*value)[80][80];
	int status;
} Shared_A_ptr__global_0_0;
Shared_A_ptr__global_0_0 A_ptr__global_0_0 = {.value = &A__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int (*value)[80][80];
	int status;
} Shared_B_ptr__global_0_0;
Shared_B_ptr__global_0_0 B_ptr__global_0_0 = {.value = &B__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int (*value)[80][80];
	int status;
} Shared_C_ptr__global_0_0;
Shared_C_ptr__global_0_0 C_ptr__global_0_0 = {.value = &C__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

void fillMatrix(int (*A)[80][80], int threadId, int SIZE);
void multiply(int (*A)[80][80], int (*B)[80][80], int (*C)[80][80], int threadId, int SIZE);
void printOut(int (*A)[80][80], int SIZE);

// thread fillMatrixA0__thread(void);
// thread fillMatrixA1__thread(void);
// thread fillMatrixA2__thread(void);
// thread fillMatrixA3__thread(void);
// thread fillMatrixB0__thread(void);
// thread fillMatrixB1__thread(void);
// thread fillMatrixB2__thread(void);
// thread fillMatrixB3__thread(void);
// thread multiply0__thread(void);
// thread multiply1__thread(void);
// thread multiply2__thread(void);
// thread multiply3__thread(void);
// thread multiply4__thread(void);
// thread multiply5__thread(void);
// thread multiply6__thread(void);
// thread multiply7__thread(void);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// fillMatrixA0
// fillMatrixA1
// fillMatrixA2
// fillMatrixA3
// fillMatrixB0
// fillMatrixB1
// fillMatrixB2
// fillMatrixB3
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
	mainParReactionCounter = 0;


	// ForeC mutex -------------------------------------------------
	unsigned int forec_mutex_value;
	forec_mutex_reset(FSL_FOREC_MUTEX_RESET_ID);
	
	// Variables for par()s ----------------------------------------
	// par0
	Thread fillMatrixA0__thread;
	Thread fillMatrixA1__thread;
	Thread fillMatrixA2__thread;
	Thread fillMatrixA3__thread;
	Thread fillMatrixB0__thread;
	Thread fillMatrixB1__thread;
	Thread fillMatrixB2__thread;
	Thread fillMatrixB3__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionEndMaster0;

	// par1
	Thread multiply0__thread;
	Thread multiply1__thread;
	Thread multiply2__thread;
	Thread multiply3__thread;
	Thread multiply4__thread;
	Thread multiply5__thread;
	Thread multiply6__thread;
	Thread multiply7__thread;
	// Thread mainReactionStartMaster0;
	// Thread mainReactionEndMaster0;


	// Synchronise execution of cores ------------------------------
	// pvr = Processor Version Register
	unsigned int pvr0;
	getpvr(0, pvr0);
	pvr0 &= MICROBLAZE_PVR0_USER1_MASK;

	switch (pvr0) {
		case (0):
			goto mainParCore0;

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

	// par0(fillMatrixA0__thread, fillMatrixA1__thread, fillMatrixA2__thread, fillMatrixA3__thread, fillMatrixB0__thread, fillMatrixB1__thread, fillMatrixB2__thread, fillMatrixB3__thread);
	// forec:statement:par:par0:start
	// Set the par(...) information.
	mainParParent.parId = 0;
	mainParParent.parStatus = FOREC_PAR_ON;

	// Link the threads and handlers together.
	mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
	fillMatrixA0__thread.programCounter = &&fillMatrixA0__thread;
	mainReactionStartMaster0.nextThread = &fillMatrixA0__thread;
	fillMatrixA0__thread.prevThread = &mainReactionStartMaster0;
	fillMatrixA1__thread.programCounter = &&fillMatrixA1__thread;
	fillMatrixA0__thread.nextThread = &fillMatrixA1__thread;
	fillMatrixA1__thread.prevThread = &fillMatrixA0__thread;
	fillMatrixA2__thread.programCounter = &&fillMatrixA2__thread;
	fillMatrixA1__thread.nextThread = &fillMatrixA2__thread;
	fillMatrixA2__thread.prevThread = &fillMatrixA1__thread;
	fillMatrixA3__thread.programCounter = &&fillMatrixA3__thread;
	fillMatrixA2__thread.nextThread = &fillMatrixA3__thread;
	fillMatrixA3__thread.prevThread = &fillMatrixA2__thread;
	fillMatrixB0__thread.programCounter = &&fillMatrixB0__thread;
	fillMatrixA3__thread.nextThread = &fillMatrixB0__thread;
	fillMatrixB0__thread.prevThread = &fillMatrixA3__thread;
	fillMatrixB1__thread.programCounter = &&fillMatrixB1__thread;
	fillMatrixB0__thread.nextThread = &fillMatrixB1__thread;
	fillMatrixB1__thread.prevThread = &fillMatrixB0__thread;
	fillMatrixB2__thread.programCounter = &&fillMatrixB2__thread;
	fillMatrixB1__thread.nextThread = &fillMatrixB2__thread;
	fillMatrixB2__thread.prevThread = &fillMatrixB1__thread;
	fillMatrixB3__thread.programCounter = &&fillMatrixB3__thread;
	fillMatrixB2__thread.nextThread = &fillMatrixB3__thread;
	fillMatrixB3__thread.prevThread = &fillMatrixB2__thread;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	fillMatrixB3__thread.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &fillMatrixB3__thread;

	// Link the last and first threads/handlers together.
	mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
	mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

	// Set the join address.
	mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

	// Set the core information.
	mainParCore0.activeThreads = 8;
	mainParCore0.reactionCounter = mainParReactionCounter;

	// Go to the first thread.
	goto fillMatrixA0__thread;
	par0JoinAddress_mainParCore0:;
	// forec:statement:par:par0:end

	// par1(multiply0__thread, multiply1__thread, multiply2__thread, multiply3__thread, multiply4__thread, multiply5__thread, multiply6__thread, multiply7__thread);
	// forec:statement:par:par1:start
	// Set the par(...) information.
	mainParParent.parId = 1;
	mainParParent.parStatus = FOREC_PAR_ON;

	// Link the threads and handlers together.
	mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
	multiply0__thread.programCounter = &&multiply0__thread;
	mainReactionStartMaster0.nextThread = &multiply0__thread;
	multiply0__thread.prevThread = &mainReactionStartMaster0;
	multiply1__thread.programCounter = &&multiply1__thread;
	multiply0__thread.nextThread = &multiply1__thread;
	multiply1__thread.prevThread = &multiply0__thread;
	multiply2__thread.programCounter = &&multiply2__thread;
	multiply1__thread.nextThread = &multiply2__thread;
	multiply2__thread.prevThread = &multiply1__thread;
	multiply3__thread.programCounter = &&multiply3__thread;
	multiply2__thread.nextThread = &multiply3__thread;
	multiply3__thread.prevThread = &multiply2__thread;
	multiply4__thread.programCounter = &&multiply4__thread;
	multiply3__thread.nextThread = &multiply4__thread;
	multiply4__thread.prevThread = &multiply3__thread;
	multiply5__thread.programCounter = &&multiply5__thread;
	multiply4__thread.nextThread = &multiply5__thread;
	multiply5__thread.prevThread = &multiply4__thread;
	multiply6__thread.programCounter = &&multiply6__thread;
	multiply5__thread.nextThread = &multiply6__thread;
	multiply6__thread.prevThread = &multiply5__thread;
	multiply7__thread.programCounter = &&multiply7__thread;
	multiply6__thread.nextThread = &multiply7__thread;
	multiply7__thread.prevThread = &multiply6__thread;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	multiply7__thread.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &multiply7__thread;

	// Link the last and first threads/handlers together.
	mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
	mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

	// Set the join address.
	mainParParent.programCounter = &&par1JoinAddress_mainParCore0;

	// Set the core information.
	mainParCore0.activeThreads = 8;
	mainParCore0.reactionCounter = mainParReactionCounter;

	// Go to the first thread.
	goto multiply0__thread;
	par1JoinAddress_mainParCore0:;
	// forec:statement:par:par1:end

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

		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;

		// Set slave cores' status to reacting.

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

	// Reset the mutex.
	forec_mutex_reset(FSL_FOREC_MUTEX_RESET_ID);

	// Return back to the parent thread if all the cores have terminated.
	if (1 && mainParCore0.status == FOREC_CORE_TERMINATED) {
		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;
		
		// Set slave cores' status to reacting

		// Increment the reaction counter for synchronization.
		mainParReactionCounter++;

		goto *mainParParent.programCounter;
	}

	// Set slave cores' status to reacting

	// Increment the reaction counter for synchronization.
	mainParReactionCounter++;

	// Go to the next thread.
	goto *mainReactionEndMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:main:master:0:end
 


	// Abort check handlers ----------------------------------------




/*==============================================================
| ForeC threads:
| Threads code translated into C code.
*=============================================================*/
	// forec:thread:fillMatrixA0:start
	/*--------------------------------------------------------------
	| Thread fillMatrixA0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	fillMatrixA0__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		fillMatrix(A_ptr__global_0_0.value, 0, SIZE__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:fillMatrixA0:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		fillMatrixA0__thread.nextThread -> prevThread = fillMatrixA0__thread.prevThread;
		fillMatrixA0__thread.prevThread -> nextThread = fillMatrixA0__thread.nextThread;
		goto *fillMatrixA0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:fillMatrixA0:end
	} // fillMatrixA0__thread
	// forec:thread:fillMatrixA0:end

	// forec:thread:fillMatrixA1:start
	/*--------------------------------------------------------------
	| Thread fillMatrixA1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	fillMatrixA1__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		fillMatrix(A_ptr__global_0_0.value, 1, SIZE__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:fillMatrixA1:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		fillMatrixA1__thread.nextThread -> prevThread = fillMatrixA1__thread.prevThread;
		fillMatrixA1__thread.prevThread -> nextThread = fillMatrixA1__thread.nextThread;
		goto *fillMatrixA1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:fillMatrixA1:end
	} // fillMatrixA1__thread
	// forec:thread:fillMatrixA1:end

	// forec:thread:fillMatrixA2:start
	/*--------------------------------------------------------------
	| Thread fillMatrixA2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	fillMatrixA2__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		fillMatrix(A_ptr__global_0_0.value, 2, SIZE__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:fillMatrixA2:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		fillMatrixA2__thread.nextThread -> prevThread = fillMatrixA2__thread.prevThread;
		fillMatrixA2__thread.prevThread -> nextThread = fillMatrixA2__thread.nextThread;
		goto *fillMatrixA2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:fillMatrixA2:end
	} // fillMatrixA2__thread
	// forec:thread:fillMatrixA2:end

	// forec:thread:fillMatrixA3:start
	/*--------------------------------------------------------------
	| Thread fillMatrixA3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	fillMatrixA3__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		fillMatrix(A_ptr__global_0_0.value, 3, SIZE__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:fillMatrixA3:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		fillMatrixA3__thread.nextThread -> prevThread = fillMatrixA3__thread.prevThread;
		fillMatrixA3__thread.prevThread -> nextThread = fillMatrixA3__thread.nextThread;
		goto *fillMatrixA3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:fillMatrixA3:end
	} // fillMatrixA3__thread
	// forec:thread:fillMatrixA3:end

	// forec:thread:fillMatrixB0:start
	/*--------------------------------------------------------------
	| Thread fillMatrixB0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	fillMatrixB0__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		fillMatrix(B_ptr__global_0_0.value, 0, SIZE__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:fillMatrixB0:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		fillMatrixB0__thread.nextThread -> prevThread = fillMatrixB0__thread.prevThread;
		fillMatrixB0__thread.prevThread -> nextThread = fillMatrixB0__thread.nextThread;
		goto *fillMatrixB0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:fillMatrixB0:end
	} // fillMatrixB0__thread
	// forec:thread:fillMatrixB0:end

	// forec:thread:fillMatrixB1:start
	/*--------------------------------------------------------------
	| Thread fillMatrixB1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	fillMatrixB1__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		fillMatrix(B_ptr__global_0_0.value, 1, SIZE__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:fillMatrixB1:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		fillMatrixB1__thread.nextThread -> prevThread = fillMatrixB1__thread.prevThread;
		fillMatrixB1__thread.prevThread -> nextThread = fillMatrixB1__thread.nextThread;
		goto *fillMatrixB1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:fillMatrixB1:end
	} // fillMatrixB1__thread
	// forec:thread:fillMatrixB1:end

	// forec:thread:fillMatrixB2:start
	/*--------------------------------------------------------------
	| Thread fillMatrixB2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	fillMatrixB2__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		fillMatrix(B_ptr__global_0_0.value, 2, SIZE__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:fillMatrixB2:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		fillMatrixB2__thread.nextThread -> prevThread = fillMatrixB2__thread.prevThread;
		fillMatrixB2__thread.prevThread -> nextThread = fillMatrixB2__thread.nextThread;
		goto *fillMatrixB2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:fillMatrixB2:end
	} // fillMatrixB2__thread
	// forec:thread:fillMatrixB2:end

	// forec:thread:fillMatrixB3:start
	/*--------------------------------------------------------------
	| Thread fillMatrixB3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	fillMatrixB3__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		fillMatrix(B_ptr__global_0_0.value, 3, SIZE__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:fillMatrixB3:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		fillMatrixB3__thread.nextThread -> prevThread = fillMatrixB3__thread.prevThread;
		fillMatrixB3__thread.prevThread -> nextThread = fillMatrixB3__thread.nextThread;
		goto *fillMatrixB3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:fillMatrixB3:end
	} // fillMatrixB3__thread
	// forec:thread:fillMatrixB3:end

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

		multiply(A_ptr__global_0_0.value, B_ptr__global_0_0.value, C_ptr__global_0_0.value, 0, SIZE__global_0_0.value);

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

		multiply(A_ptr__global_0_0.value, B_ptr__global_0_0.value, C_ptr__global_0_0.value, 1, SIZE__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiply1:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
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

		multiply(A_ptr__global_0_0.value, B_ptr__global_0_0.value, C_ptr__global_0_0.value, 2, SIZE__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiply2:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
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

		multiply(A_ptr__global_0_0.value, B_ptr__global_0_0.value, C_ptr__global_0_0.value, 3, SIZE__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiply3:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
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

		multiply(A_ptr__global_0_0.value, B_ptr__global_0_0.value, C_ptr__global_0_0.value, 4, SIZE__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiply4:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
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

		multiply(A_ptr__global_0_0.value, B_ptr__global_0_0.value, C_ptr__global_0_0.value, 5, SIZE__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiply5:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
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

		multiply(A_ptr__global_0_0.value, B_ptr__global_0_0.value, C_ptr__global_0_0.value, 6, SIZE__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiply6:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
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

		multiply(A_ptr__global_0_0.value, B_ptr__global_0_0.value, C_ptr__global_0_0.value, 7, SIZE__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiply7:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		multiply7__thread.nextThread -> prevThread = multiply7__thread.prevThread;
		multiply7__thread.prevThread -> nextThread = multiply7__thread.nextThread;
		goto *multiply7__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:multiply7:end
	} // multiply7__thread
	// forec:thread:multiply7:end


} // End of the main() function.

void fillMatrix(int (*A__fillMatrix_0_0)[80][80], int threadId__fillMatrix_0_0, int SIZE__fillMatrix_0_0) {
	int startRow__fillMatrix_0_0 = threadId__fillMatrix_0_0*SIZE__fillMatrix_0_0/NumberOfFillThreads__global_0_0;
	int range__fillMatrix_0_0 = SIZE__fillMatrix_0_0/NumberOfFillThreads__global_0_0;
	int i__fillMatrix_0_0;
	for (i__fillMatrix_0_0 = startRow__fillMatrix_0_0; i__fillMatrix_0_0 < (startRow__fillMatrix_0_0 + range__fillMatrix_0_0); i__fillMatrix_0_0++) {
		int j__fillMatrix_1_0;
		for (j__fillMatrix_1_0 = 0; j__fillMatrix_1_0 < SIZE__fillMatrix_0_0; j__fillMatrix_1_0++) {
			(* A__fillMatrix_0_0)[i__fillMatrix_0_0][j__fillMatrix_1_0] = j__fillMatrix_1_0;
			asm volatile ("nop");
			// forec:iteration:for1_0:bound:80:80
		}
		asm volatile ("nop");
		// forec:iteration:for1_1:bound:20:20
	}
}

void multiply(int (*A__multiply_0_0)[80][80], int (*B__multiply_0_0)[80][80], int (*C__multiply_0_0)[80][80], int threadId__multiply_0_0, int SIZE__multiply_0_0) {
	int startRow__multiply_0_0 = threadId__multiply_0_0*SIZE__multiply_0_0/NumberOfMultiplyThreads__global_0_0;
	int range__multiply_0_0 = SIZE__multiply_0_0/NumberOfMultiplyThreads__global_0_0;
	int i__multiply_0_0;
	for (i__multiply_0_0 = startRow__multiply_0_0; i__multiply_0_0 < (startRow__multiply_0_0 + range__multiply_0_0); i__multiply_0_0++) {
		int j__multiply_1_0;
		for (j__multiply_1_0 = 0; j__multiply_1_0 < SIZE__multiply_0_0; j__multiply_1_0++) {
			(* C__multiply_0_0)[i__multiply_0_0][j__multiply_1_0] = 0;
			int k__multiply_2_0;
			for (k__multiply_2_0 = 0; k__multiply_2_0 < SIZE__multiply_0_0; k__multiply_2_0++) {
				(* C__multiply_0_0)[i__multiply_0_0][j__multiply_1_0] += (* A__multiply_0_0)[i__multiply_0_0][k__multiply_2_0]*(* B__multiply_0_0)[k__multiply_2_0][j__multiply_1_0];
				asm volatile ("nop");
				// forec:iteration:for1_2:bound:80:80
			}
			asm volatile ("nop");
			// forec:iteration:for1_3:bound:80:80
		}
		asm volatile ("nop");
		// forec:iteration:for1_4:bound:20:20
	}
}

void printOut(int (*A__printOut_0_0)[80][80], int SIZE__printOut_0_0) {
	int i__printOut_0_0;
	for (i__printOut_0_0 = 0; i__printOut_0_0 < SIZE__printOut_0_0; i__printOut_0_0++) {
		int j__printOut_1_0;
		for (j__printOut_1_0 = 0; j__printOut_1_0 < SIZE__printOut_0_0; j__printOut_1_0++) {
			xil_printf("%d ", (* A__printOut_0_0)[i__printOut_0_0][j__printOut_1_0]);
			asm volatile ("nop");
			// forec:iteration:for1_5:bound:80:80
		}
		xil_printf("\n");
		asm volatile ("nop");
		// forec:iteration:for1_6:bound:80:80
	}
	xil_printf("\n");
}

