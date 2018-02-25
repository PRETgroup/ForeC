/*==============================================================
| Hardware architecture specific declarations:
| Cores, mutex and input/output information.
*=============================================================*/
#include <pthread.h>

// Mapping Pthreads to processor cores
pthread_t cores[1];
pthread_attr_t masterCoreAttribute;
pthread_attr_t slaveCoreAttribute;

// ForeC mutexes
unsigned int forec_mutex_value_tABRO;

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

// Structure to pass input arguments into forecMain.
typedef struct {
	int coreId;
	int argc;
	char **argv;
} Arguments;

// Shared control variables for non-immediate aborts -----------
volatile int init__abortStrongNonImmediate0 = 0;

// Shared control variables for par(...)s ----------------------
// Thread main with par(...)s
volatile Parent mainParParent;
volatile Core mainParCore0;
volatile int mainParReactionCounter;

// Thread tABRO with par(...)s
volatile Parent tABROParParent;
volatile Core tABROParCore0;
volatile int tABROParReactionCounter;


/*==============================================================
| Original global declarations:
| Global declarations in the original program code.
*=============================================================*/
// Original main function
void *forecMain(void *args);

#include <stdio.h>

typedef struct {
	/* shared */ int value;
	int status;
} Shared_A__global_0_0;
Shared_A__global_0_0 A__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value;
	int status;
} Shared_B__global_0_0;
Shared_B__global_0_0 B__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value;
	int status;
} Shared_R__global_0_0;
Shared_R__global_0_0 R__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value;
	int status;
} Shared_O__global_0_0;
Shared_O__global_0_0 O__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};

// thread tSetInputs__thread(void);
// thread tA__thread(void);
// thread tB__thread(void);
// thread tABRO__thread(void);
// thread tDebug__thread(void);

/* shared */ const int MAX_TICK_NUMBER__global_0_0 = 12;

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// main
// tA
Shared_A__global_0_0 A__global_0_0_copy_tA = {.status = FOREC_SHARED_UNMODIFIED};
// tABRO
Shared_A__global_0_0 A__global_0_0_copy_tABRO = {.status = FOREC_SHARED_UNMODIFIED};
Shared_B__global_0_0 B__global_0_0_copy_tABRO = {.status = FOREC_SHARED_UNMODIFIED};
Shared_R__global_0_0 R__global_0_0_copy_tABRO = {.status = FOREC_SHARED_UNMODIFIED};
Shared_O__global_0_0 O__global_0_0_copy_tABRO = {.status = FOREC_SHARED_UNMODIFIED};
// tB
Shared_B__global_0_0 B__global_0_0_copy_tB = {.status = FOREC_SHARED_UNMODIFIED};
// tDebug
Shared_A__global_0_0 A__global_0_0_copy_tDebug = {.status = FOREC_SHARED_UNMODIFIED};
Shared_B__global_0_0 B__global_0_0_copy_tDebug = {.status = FOREC_SHARED_UNMODIFIED};
Shared_R__global_0_0 R__global_0_0_copy_tDebug = {.status = FOREC_SHARED_UNMODIFIED};
Shared_O__global_0_0 O__global_0_0_copy_tDebug = {.status = FOREC_SHARED_UNMODIFIED};
// tSetInputs
Shared_A__global_0_0 A__global_0_0_copy_tSetInputs = {.status = FOREC_SHARED_UNMODIFIED};
Shared_B__global_0_0 B__global_0_0_copy_tSetInputs = {.status = FOREC_SHARED_UNMODIFIED};
Shared_R__global_0_0 R__global_0_0_copy_tSetInputs = {.status = FOREC_SHARED_UNMODIFIED};

// forec:scheduler:boot:start
int main(int argc__main_0_0, char ** argv__main_0_0) {

/*==============================================================
| Multicore startup:
| Platform dependent code.  Core identifies itself and
| executes its corresponding start up code.
*=============================================================*/
	// Initialise ForeC specific values ---------------------------
	// Thread main with par(...)s
	mainParParent.parStatus = FOREC_PAR_OFF;
	mainParCore0.sync = 1;
	mainParCore0.status = FOREC_CORE_REACTING;
	mainParReactionCounter = 0;

	// Thread tABRO with par(...)s
	tABROParParent.parStatus = FOREC_PAR_OFF;
	tABROParCore0.sync = 1;
	tABROParCore0.status = FOREC_CORE_REACTING;
	tABROParReactionCounter = 0;


	// Reset ForeC mutex values
	forec_mutex_value_tABRO = -1;

	// Start core execution
	pthread_attr_init(&masterCoreAttribute);
	pthread_attr_init(&slaveCoreAttribute);
	pthread_attr_setdetachstate(&masterCoreAttribute, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setdetachstate(&slaveCoreAttribute, PTHREAD_CREATE_DETACHED);
		
	// Master core
	Arguments arguments0 = {.coreId = 0, .argc = argc__main_0_0, .argv = argv__main_0_0};
	pthread_create(&cores[0], &masterCoreAttribute, forecMain, (void *)&arguments0);

	// End core execution
	pthread_attr_destroy(&masterCoreAttribute);
	pthread_attr_destroy(&slaveCoreAttribute);
	
	// Program termination
	pthread_join(cores[0], NULL);
}


/*==============================================================
| Original main(...) function:
*=============================================================*/
void *forecMain(void *args) {
	Arguments *arguments = (Arguments *)args;
	int coreId = arguments->coreId;
	int argc__main_0_0 = arguments->argc;
	char **argv__main_0_0 = arguments->argv;

	// Variables for par()s ----------------------------------------
	// par0
	Thread tABRO__thread;
	Thread tDebug__thread;
	Thread tSetInputs__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionEndMaster0;
	Thread tABROParHandlerMaster0;

	// par1
	Thread tA__thread;
	Thread tB__thread;
	Thread tABROReactionStartMaster0;
	Thread tABROReactionEndMaster0;
	Thread abortStrongNonImmediate0Check0;


	// Let cores jump to their code segment ------------------------
	switch (coreId) {
		case (0):
			goto mainParCore0;

		default:
			// Terminate unused cores.
			pthread_exit(NULL);
	}
// forec:scheduler:boot:end

/*==============================================================
| Core specific instructions:
| Contains par, abort and synchronisation handlers.
*=============================================================*/
	/*--------------------------------------------------------------
	| Master core: core0
	| ForeC program's main() function:
	| Original main() function code with ForeC constructs
	| translated into C code.
	*-------------------------------------------------------------*/
	
	// Thread local declarations -----------------------------------
	// No declarations.
mainParCore0: {
	//--------------------------------------------------------------

	// par0(tSetInputs__thread, tDebug__thread, tABRO__thread);
	// forec:statement:par:par0:start
	// Set the par(...) information.
	mainParParent.parId = 0;
	mainParParent.parStatus = FOREC_PAR_ON;

	// Link the threads and handlers together.
	mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
	tSetInputs__thread.programCounter = &&tSetInputs__thread;
	mainReactionStartMaster0.nextThread = &tSetInputs__thread;
	tSetInputs__thread.prevThread = &mainReactionStartMaster0;
	tDebug__thread.programCounter = &&tDebug__thread;
	tSetInputs__thread.nextThread = &tDebug__thread;
	tDebug__thread.prevThread = &tSetInputs__thread;
	tABRO__thread.programCounter = &&tABRO__thread;
	tDebug__thread.nextThread = &tABRO__thread;
	tABRO__thread.prevThread = &tDebug__thread;
	tABROParHandlerMaster0.programCounter = &&tABROParHandlerMaster0;
	tABRO__thread.nextThread = &tABROParHandlerMaster0;
	tABROParHandlerMaster0.prevThread = &tABRO__thread;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	tABROParHandlerMaster0.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &tABROParHandlerMaster0;

	// Link the last and first threads/handlers together.
	mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
	mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

	// Set the join address.
	mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

	// Set the core information.
	mainParCore0.activeThreads = 4;
	mainParCore0.reactionCounter = mainParReactionCounter;

	// Go to the first thread.
	goto tSetInputs__thread;
	par0JoinAddress_mainParCore0:;
	// forec:statement:par:par0:end

	//--------------------------------------------------------------


	// forec:scheduler:threadRemove:main:start
	pthread_exit(NULL);
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
	// forec:scheduler:parHandler:tABRO:master:0:start
	//-- Thread tABRO par(...) handlers
tABROParHandlerMaster0: {
	// Check the execution status of the nested par(...)s.
	if (tABROParParent.parStatus == FOREC_PAR_OFF) {
		// Release the mutex.
		forec_mutex_value_tABRO &= 0x7fffffff;

		goto *tABROParHandlerMaster0.nextThread -> programCounter;
	}
	// Release the mutex.
	forec_mutex_value_tABRO &= 0x7fffffff;

	int parId = tABROParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		tABROReactionStartMaster0.programCounter = &&tABROReactionStartMaster0;
		abortStrongNonImmediate0Check0.programCounter = &&abortStrongNonImmediate0Check0;
		tABROReactionStartMaster0.nextThread = &abortStrongNonImmediate0Check0;
		abortStrongNonImmediate0Check0.prevThread = &tABROReactionStartMaster0;
		tA__thread.programCounter = &&tA__thread;
		abortStrongNonImmediate0Check0.nextThread = &tA__thread;
		tA__thread.prevThread = &abortStrongNonImmediate0Check0;
		tB__thread.programCounter = &&tB__thread;
		tA__thread.nextThread = &tB__thread;
		tB__thread.prevThread = &tA__thread;
		tABROReactionEndMaster0.programCounter = &&tABROReactionEndMaster0;
		tB__thread.nextThread = &tABROReactionEndMaster0;
		tABROReactionEndMaster0.prevThread = &tB__thread;

		// Swap the nested par handler with the linked list.
		tABROParHandlerMaster0.prevThread -> nextThread = &tABROReactionStartMaster0;
		tABROReactionStartMaster0.prevThread = tABROParHandlerMaster0.prevThread;
		tABROReactionEndMaster0.nextThread = tABROParHandlerMaster0.nextThread;
		tABROParHandlerMaster0.nextThread -> prevThread = &tABROReactionEndMaster0;
		
		// Set the core information.
		tABROParCore0.activeThreads = 2;
		tABROParCore0.reactionCounter = tABROParReactionCounter;
		
		// Go to the first thread.
		goto tA__thread;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.

		tABROParParent.parStatus = FOREC_PAR_OFF;
		tABROParParent.parId = -1;

		forec_mutex_value_tABRO = -1;

		// Set slave cores' status to reacting.

		// Increment the reaction counter for synchronisation.
		tABROParReactionCounter++;

		// Return to thread tABRO.
		goto *tABROParParent.programCounter;
	} else if (parId == -3) {
		// Thread termination
		mainParCore0.activeThreads--;
		tABROParCore0.activeThreads--;

		// Wait for other cores to complete their reaction.

		tABROParParent.parStatus = FOREC_PAR_OFF;
		tABROParParent.parId = -1;

		// Set slave cores' status to reacting.

		// Increment the reaction counter for synchronisation.
		tABROParReactionCounter++;

		// Delete this par(...) handler.
		tABROParHandlerMaster0.prevThread -> nextThread = tABROParHandlerMaster0.nextThread;
		tABROParHandlerMaster0.nextThread -> prevThread = tABROParHandlerMaster0.prevThread;
			
		// Return to thread tABRO.
		goto *tABROParParent.programCounter;
	} else {
		// Unscheduled par(...)
		tABROParCore0.reactionCounter = tABROParReactionCounter;

		tABROParHandlerMaster0.programCounter = &&wrongParId_tABROParHandlerMaster0;
		wrongParId_tABROParHandlerMaster0:;

		tABROParCore0.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (tABROParCore0.reactionCounter == tABROParReactionCounter);
		tABROParCore0.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (tABROParParent.parStatus == FOREC_PAR_ON && tABROParParent.parId == parId) {
			goto *tABROParHandlerMaster0.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		tABROParHandlerMaster0.programCounter = &&tABROParHandlerMaster0;
		
		goto tABROParHandlerMaster0;
	}
	
	// Control should not reach here.
	goto tABROParHandlerMaster0;
}
	// forec:scheduler:parHandler:tABRO:master:0:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:master:0:start
	//-- main:
mainReactionStartMaster0: {
	// Go to the next thread.
	goto *mainReactionStartMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:master:0:end
 
	// forec:scheduler:reactionStart:tABRO:master:0:start
	//-- tABRO:
tABROReactionStartMaster0: {
	// Go to the next thread.
	goto *tABROReactionStartMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:tABRO:master:0:end
 


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
	forec_mutex_value_tABRO = -1;

	// Combine shared variables.
	int parId = mainParParent.parId;
	if (parId == 0) {

		// A__global_0_0
		if (A__global_0_0_copy_tSetInputs.status == FOREC_SHARED_MODIFIED) {
			A__global_0_0_copy_tSetInputs.status = FOREC_SHARED_UNMODIFIED;
			A__global_0_0.value = A__global_0_0_copy_tSetInputs.value;
		}

		// B__global_0_0
		if (B__global_0_0_copy_tSetInputs.status == FOREC_SHARED_MODIFIED) {
			B__global_0_0_copy_tSetInputs.status = FOREC_SHARED_UNMODIFIED;
			B__global_0_0.value = B__global_0_0_copy_tSetInputs.value;
		}

		// R__global_0_0
		if (R__global_0_0_copy_tSetInputs.status == FOREC_SHARED_MODIFIED) {
			R__global_0_0_copy_tSetInputs.status = FOREC_SHARED_UNMODIFIED;
			R__global_0_0.value = R__global_0_0_copy_tSetInputs.value;
		}

		// O__global_0_0
		if (O__global_0_0_copy_tABRO.status == FOREC_SHARED_MODIFIED) {
			O__global_0_0_copy_tABRO.status = FOREC_SHARED_UNMODIFIED;
			O__global_0_0.value = O__global_0_0_copy_tABRO.value;
		}
	} else {
		// Nothing.
	}

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
 
	// forec:scheduler:reactionEnd:tABRO:master:0:start
	//-- tABRO:
tABROReactionEndMaster0: {
	// Determine if the core can still react or not.
	if (tABROParCore0.activeThreads) {
		tABROParCore0.status = FOREC_CORE_REACTED;
	} else {
		tABROParCore0.status = FOREC_CORE_TERMINATED;
	}
	
	// Wait for other cores to complete their reaction.


	// Return back to the parent thread if all the cores have terminated.
	if (1 && tABROParCore0.status == FOREC_CORE_TERMINATED) {
		forec_mutex_value_tABRO = -1;

		tABROParParent.parStatus = FOREC_PAR_OFF;
		tABROParParent.parId = -1;
		
		// Set slave cores' status to reacting

		// Increment the reaction counter for synchronization.
		tABROParReactionCounter++;

		// Swap the reaction (start & end) handlers with (thread tABRO & nested par handler).
		tABROReactionStartMaster0.prevThread -> nextThread = &tABRO__thread;
		tABRO__thread.prevThread = tABROReactionStartMaster0.prevThread;
		tABRO__thread.nextThread = &tABROParHandlerMaster0;
		tABROParHandlerMaster0.prevThread = &tABRO__thread;
		tABROParHandlerMaster0.nextThread = tABROReactionEndMaster0.nextThread;
		tABROReactionEndMaster0.nextThread -> prevThread = &tABROParHandlerMaster0;

		goto *tABROParParent.programCounter;
	}

	// Set slave cores' status to reacting

	// Increment the reaction counter for synchronization.
	tABROParReactionCounter++;

	// Go to the next thread.
	goto *tABROReactionEndMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:tABRO:master:0:end
 


	// Abort check handlers ----------------------------------------
	// forec:scheduler:abortHandler:abortStrongNonImmediate0:0:start
	// abortStrongNonImmediate0 (R__global_0_0.value == 1 && init__abortStrongNonImmediate0 == 1)
abortStrongNonImmediate0Check0: {
	// Check the abort condition.
	if (R__global_0_0.value == 1 && init__abortStrongNonImmediate0 == 1) {
		// Force the reaction end handler to terminate the par(...).
		tABROParCore0.activeThreads = 0;

		// Update the parent thread to resume at the end of the abort scope.
		tABROParParent.programCounter = &&abortEnd_abortStrongNonImmediate0;
		
		goto tABROReactionEndMaster0;
	}
	
	// Continue to the next thread.
	goto *abortStrongNonImmediate0Check0.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrongNonImmediate0:0:end




/*==============================================================
| ForeC threads:
| Threads' code translated into C code.
*=============================================================*/
	// forec:thread:tA:start
	/*--------------------------------------------------------------
	| Thread tA
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_A__global_0_0 A__global_0_0_copy_tA_local;
	int initAwait__tA_0_0;

	// Thread body -------------------------------------------------
	tA__thread: {
		// Initialise the local copies of shared variables.
		A__global_0_0_copy_tA_local.value = A__global_0_0_copy_tABRO.value;
		A__global_0_0_copy_tA_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		initAwait__tA_0_0 = 0;

		while (A__global_0_0_copy_tA_local.value == 0 || initAwait__tA_0_0 == 0) {
			initAwait__tA_0_0 = 1;

			// pause;
			// forec:statement:pause:pause11:start
			tA__thread.programCounter = &&pause11;
			goto *tA__thread.nextThread -> programCounter;
			pause11:;
			// forec:statement:pause:pause11:end
			// Update the values of the used shared variables from their global copy.
			A__global_0_0_copy_tA_local = A__global_0_0;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:tA:start

		// Delete thread from the linked list and core.
		tABROParCore0.activeThreads--;
		tA__thread.nextThread -> prevThread = tA__thread.prevThread;
		tA__thread.prevThread -> nextThread = tA__thread.nextThread;
		goto *tA__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:tA:end
	} // tA__thread
	// forec:thread:tA:end

	// forec:thread:tABRO:start
	/*--------------------------------------------------------------
	| Thread tABRO
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_A__global_0_0 A__global_0_0_copy_tABRO_local;
	Shared_B__global_0_0 B__global_0_0_copy_tABRO_local;
	Shared_R__global_0_0 R__global_0_0_copy_tABRO_local;
	Shared_O__global_0_0 O__global_0_0_copy_tABRO_local;
	int i__tABRO_1_0;

	// Thread body -------------------------------------------------
	tABRO__thread: {
		// Initialise the local copies of shared variables.
		A__global_0_0_copy_tABRO_local.value = A__global_0_0.value;
		A__global_0_0_copy_tABRO_local.status = FOREC_SHARED_UNMODIFIED;
		B__global_0_0_copy_tABRO_local.value = B__global_0_0.value;
		B__global_0_0_copy_tABRO_local.status = FOREC_SHARED_UNMODIFIED;
		R__global_0_0_copy_tABRO_local.value = R__global_0_0.value;
		R__global_0_0_copy_tABRO_local.status = FOREC_SHARED_UNMODIFIED;
		O__global_0_0_copy_tABRO_local.value = O__global_0_0.value;
		O__global_0_0_copy_tABRO_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		for (i__tABRO_1_0 = 0; i__tABRO_1_0 < MAX_TICK_NUMBER__global_0_0; i__tABRO_1_0++) {
			/* abortStrongNonImmediate0 */ {
				init__abortStrongNonImmediate0 = 0;
				// forec:statement:abort:abortStrongNonImmediate0:start
				if (R__global_0_0_copy_tABRO_local.value == 1 && init__abortStrongNonImmediate0 == 1) {
					goto abortEnd_abortStrongNonImmediate0;
				}
				init__abortStrongNonImmediate0 = 1;
				// forec:statement:abort:abortStrongNonImmediate0:end

				O__global_0_0_copy_tABRO_local.value = 0;
				O__global_0_0_copy_tABRO_local.status = FOREC_SHARED_MODIFIED;

				// par1(tA__thread, tB__thread);
				A__global_0_0_copy_tABRO = A__global_0_0_copy_tABRO_local;
				B__global_0_0_copy_tABRO = B__global_0_0_copy_tABRO_local;
				O__global_0_0_copy_tABRO = O__global_0_0_copy_tABRO_local;
				// Set the par(...) information.
				// forec:statement:par:par1:start
				tABROParParent.parId = 1;
				tABROParParent.parStatus = FOREC_PAR_ON;
				tABROParParent.programCounter = &&par1JoinAddress_tABROParParent;

				// Remove this thread from the linked list.
				tABRO__thread.nextThread -> prevThread = tABRO__thread.prevThread;
				tABRO__thread.prevThread -> nextThread = tABRO__thread.nextThread;
				goto tABROParHandlerMaster0;
				par1JoinAddress_tABROParParent:;
				// forec:statement:par:par1:end
				if (A__global_0_0_copy_tABRO.status == FOREC_SHARED_MODIFIED) {
					A__global_0_0_copy_tABRO_local = A__global_0_0_copy_tABRO;
				} else {
					A__global_0_0_copy_tABRO_local = A__global_0_0;
				}
				if (B__global_0_0_copy_tABRO.status == FOREC_SHARED_MODIFIED) {
					B__global_0_0_copy_tABRO_local = B__global_0_0_copy_tABRO;
				} else {
					B__global_0_0_copy_tABRO_local = B__global_0_0;
				}

				O__global_0_0_copy_tABRO_local.value = 1;
				O__global_0_0_copy_tABRO_local.status = FOREC_SHARED_MODIFIED;

				while (1) {
					// pause;
					// Write the local copy of shared variables back to their global copy.
					O__global_0_0_copy_tABRO = O__global_0_0_copy_tABRO_local;
					// forec:statement:pause:pause10:start
					tABRO__thread.programCounter = &&pause10;
					goto *tABRO__thread.nextThread -> programCounter;
					pause10:;
					// forec:statement:pause:pause10:end
					// Update the values of the used shared variables from their global copy.
					A__global_0_0_copy_tABRO_local = A__global_0_0;
					B__global_0_0_copy_tABRO_local = B__global_0_0;
					R__global_0_0_copy_tABRO_local = R__global_0_0;
					O__global_0_0_copy_tABRO_local = O__global_0_0;

					// Strong aborts:
					// forec:statement:abort:abortStrongNonImmediate0:start
					if (R__global_0_0_copy_tABRO_local.value == 1 && init__abortStrongNonImmediate0 == 1) {
						goto abortEnd_abortStrongNonImmediate0;
					}
					// forec:statement:abort:abortStrongNonImmediate0:end
				}
				abortEnd_abortStrongNonImmediate0:;
			} // when (R__global_0_0_copy_tABRO_local.value == 1 && init__abortStrongNonImmediate0 == 1);
			// forec:statement:abort:abortStrongNonImmediate0:scope:end

			// forec:scheduler:iterationEnd:for3_1:start
			// Synchronise end of iteration
			tABROParParent.parId = -2;
			tABROParParent.parStatus = FOREC_PAR_ON;
			tABROParParent.programCounter = &&for3_1_endAddress;
			goto tABROParHandlerMaster0;
			for3_1_endAddress:;
			// forec:scheduler:iterationEnd:for3_1:end
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		O__global_0_0_copy_tABRO = O__global_0_0_copy_tABRO_local;

		// forec:scheduler:threadRemove:tABRO:start
		// Delete par handler
		tABROParParent.parId = -3;
		tABROParParent.parStatus = FOREC_PAR_ON;
		tABROParParent.programCounter = &&tABRO_endAddress;
		goto tABROParHandlerMaster0;
		tABRO_endAddress:;

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		tABRO__thread.nextThread -> prevThread = tABRO__thread.prevThread;
		tABRO__thread.prevThread -> nextThread = tABRO__thread.nextThread;
		goto *tABRO__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:tABRO:end
	} // tABRO__thread
	// forec:thread:tABRO:end

	// forec:thread:tB:start
	/*--------------------------------------------------------------
	| Thread tB
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_B__global_0_0 B__global_0_0_copy_tB_local;
	int initAwait__tB_0_0;

	// Thread body -------------------------------------------------
	tB__thread: {
		// Initialise the local copies of shared variables.
		B__global_0_0_copy_tB_local.value = B__global_0_0_copy_tABRO.value;
		B__global_0_0_copy_tB_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		initAwait__tB_0_0 = 0;

		while (B__global_0_0_copy_tB_local.value == 0 || initAwait__tB_0_0 == 0) {
			initAwait__tB_0_0 = 1;

			// pause;
			// forec:statement:pause:pause12:start
			tB__thread.programCounter = &&pause12;
			goto *tB__thread.nextThread -> programCounter;
			pause12:;
			// forec:statement:pause:pause12:end
			// Update the values of the used shared variables from their global copy.
			B__global_0_0_copy_tB_local = B__global_0_0;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:tB:start

		// Delete thread from the linked list and core.
		tABROParCore0.activeThreads--;
		tB__thread.nextThread -> prevThread = tB__thread.prevThread;
		tB__thread.prevThread -> nextThread = tB__thread.nextThread;
		goto *tB__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:tB:end
	} // tB__thread
	// forec:thread:tB:end

	// forec:thread:tDebug:start
	/*--------------------------------------------------------------
	| Thread tDebug
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_A__global_0_0 A__global_0_0_copy_tDebug_local;
	Shared_B__global_0_0 B__global_0_0_copy_tDebug_local;
	Shared_R__global_0_0 R__global_0_0_copy_tDebug_local;
	Shared_O__global_0_0 O__global_0_0_copy_tDebug_local;
	int i__tDebug_1_0;

	// Thread body -------------------------------------------------
	tDebug__thread: {
		// Initialise the local copies of shared variables.
		A__global_0_0_copy_tDebug_local.value = A__global_0_0.value;
		A__global_0_0_copy_tDebug_local.status = FOREC_SHARED_UNMODIFIED;
		B__global_0_0_copy_tDebug_local.value = B__global_0_0.value;
		B__global_0_0_copy_tDebug_local.status = FOREC_SHARED_UNMODIFIED;
		R__global_0_0_copy_tDebug_local.value = R__global_0_0.value;
		R__global_0_0_copy_tDebug_local.status = FOREC_SHARED_UNMODIFIED;
		O__global_0_0_copy_tDebug_local.value = O__global_0_0.value;
		O__global_0_0_copy_tDebug_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		for (i__tDebug_1_0 = 0; i__tDebug_1_0 < MAX_TICK_NUMBER__global_0_0; i__tDebug_1_0++) {
			printf("Tick %d: A = %d, B = %d, R = %d, O = %d\n", i__tDebug_1_0, A__global_0_0_copy_tDebug_local.value, B__global_0_0_copy_tDebug_local.value, R__global_0_0_copy_tDebug_local.value, O__global_0_0_copy_tDebug_local.value);

			// pause;
			// forec:statement:pause:pause13:start
			tDebug__thread.programCounter = &&pause13;
			goto *tDebug__thread.nextThread -> programCounter;
			pause13:;
			// forec:statement:pause:pause13:end
			// Update the values of the used shared variables from their global copy.
			A__global_0_0_copy_tDebug_local = A__global_0_0;
			B__global_0_0_copy_tDebug_local = B__global_0_0;
			R__global_0_0_copy_tDebug_local = R__global_0_0;
			O__global_0_0_copy_tDebug_local = O__global_0_0;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:tDebug:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		tDebug__thread.nextThread -> prevThread = tDebug__thread.prevThread;
		tDebug__thread.prevThread -> nextThread = tDebug__thread.nextThread;
		goto *tDebug__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:tDebug:end
	} // tDebug__thread
	// forec:thread:tDebug:end

	// forec:thread:tSetInputs:start
	/*--------------------------------------------------------------
	| Thread tSetInputs
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_A__global_0_0 A__global_0_0_copy_tSetInputs_local;
	Shared_B__global_0_0 B__global_0_0_copy_tSetInputs_local;
	Shared_R__global_0_0 R__global_0_0_copy_tSetInputs_local;

	// Thread body -------------------------------------------------
	tSetInputs__thread: {
		// Initialise the local copies of shared variables.
		A__global_0_0_copy_tSetInputs_local.value = A__global_0_0.value;
		A__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_UNMODIFIED;
		B__global_0_0_copy_tSetInputs_local.value = B__global_0_0.value;
		B__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_UNMODIFIED;
		R__global_0_0_copy_tSetInputs_local.value = R__global_0_0.value;
		R__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		A__global_0_0_copy_tSetInputs_local.value = 0;
		A__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		B__global_0_0_copy_tSetInputs_local.value = 0;
		B__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		R__global_0_0_copy_tSetInputs_local.value = 0;
		R__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		A__global_0_0_copy_tSetInputs = A__global_0_0_copy_tSetInputs_local;
		B__global_0_0_copy_tSetInputs = B__global_0_0_copy_tSetInputs_local;
		R__global_0_0_copy_tSetInputs = R__global_0_0_copy_tSetInputs_local;
		// forec:statement:pause:pause0:start
		tSetInputs__thread.programCounter = &&pause0;
		goto *tSetInputs__thread.nextThread -> programCounter;
		pause0:;
		// forec:statement:pause:pause0:end
		// Update the values of the used shared variables from their global copy.
		A__global_0_0_copy_tSetInputs_local = A__global_0_0;
		B__global_0_0_copy_tSetInputs_local = B__global_0_0;
		R__global_0_0_copy_tSetInputs_local = R__global_0_0;


		A__global_0_0_copy_tSetInputs_local.value = 1;
		A__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		B__global_0_0_copy_tSetInputs_local.value = 0;
		B__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		R__global_0_0_copy_tSetInputs_local.value = 0;
		R__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		A__global_0_0_copy_tSetInputs = A__global_0_0_copy_tSetInputs_local;
		B__global_0_0_copy_tSetInputs = B__global_0_0_copy_tSetInputs_local;
		R__global_0_0_copy_tSetInputs = R__global_0_0_copy_tSetInputs_local;
		// forec:statement:pause:pause1:start
		tSetInputs__thread.programCounter = &&pause1;
		goto *tSetInputs__thread.nextThread -> programCounter;
		pause1:;
		// forec:statement:pause:pause1:end
		// Update the values of the used shared variables from their global copy.
		A__global_0_0_copy_tSetInputs_local = A__global_0_0;
		B__global_0_0_copy_tSetInputs_local = B__global_0_0;
		R__global_0_0_copy_tSetInputs_local = R__global_0_0;


		A__global_0_0_copy_tSetInputs_local.value = 0;
		A__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		B__global_0_0_copy_tSetInputs_local.value = 1;
		B__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		R__global_0_0_copy_tSetInputs_local.value = 0;
		R__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		A__global_0_0_copy_tSetInputs = A__global_0_0_copy_tSetInputs_local;
		B__global_0_0_copy_tSetInputs = B__global_0_0_copy_tSetInputs_local;
		R__global_0_0_copy_tSetInputs = R__global_0_0_copy_tSetInputs_local;
		// forec:statement:pause:pause2:start
		tSetInputs__thread.programCounter = &&pause2;
		goto *tSetInputs__thread.nextThread -> programCounter;
		pause2:;
		// forec:statement:pause:pause2:end
		// Update the values of the used shared variables from their global copy.
		A__global_0_0_copy_tSetInputs_local = A__global_0_0;
		B__global_0_0_copy_tSetInputs_local = B__global_0_0;
		R__global_0_0_copy_tSetInputs_local = R__global_0_0;


		A__global_0_0_copy_tSetInputs_local.value = 0;
		A__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		B__global_0_0_copy_tSetInputs_local.value = 0;
		B__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		R__global_0_0_copy_tSetInputs_local.value = 1;
		R__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		A__global_0_0_copy_tSetInputs = A__global_0_0_copy_tSetInputs_local;
		B__global_0_0_copy_tSetInputs = B__global_0_0_copy_tSetInputs_local;
		R__global_0_0_copy_tSetInputs = R__global_0_0_copy_tSetInputs_local;
		// forec:statement:pause:pause3:start
		tSetInputs__thread.programCounter = &&pause3;
		goto *tSetInputs__thread.nextThread -> programCounter;
		pause3:;
		// forec:statement:pause:pause3:end
		// Update the values of the used shared variables from their global copy.
		A__global_0_0_copy_tSetInputs_local = A__global_0_0;
		B__global_0_0_copy_tSetInputs_local = B__global_0_0;
		R__global_0_0_copy_tSetInputs_local = R__global_0_0;


		A__global_0_0_copy_tSetInputs_local.value = 0;
		A__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		B__global_0_0_copy_tSetInputs_local.value = 0;
		B__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		R__global_0_0_copy_tSetInputs_local.value = 0;
		R__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		A__global_0_0_copy_tSetInputs = A__global_0_0_copy_tSetInputs_local;
		B__global_0_0_copy_tSetInputs = B__global_0_0_copy_tSetInputs_local;
		R__global_0_0_copy_tSetInputs = R__global_0_0_copy_tSetInputs_local;
		// forec:statement:pause:pause4:start
		tSetInputs__thread.programCounter = &&pause4;
		goto *tSetInputs__thread.nextThread -> programCounter;
		pause4:;
		// forec:statement:pause:pause4:end
		// Update the values of the used shared variables from their global copy.
		A__global_0_0_copy_tSetInputs_local = A__global_0_0;
		B__global_0_0_copy_tSetInputs_local = B__global_0_0;
		R__global_0_0_copy_tSetInputs_local = R__global_0_0;


		A__global_0_0_copy_tSetInputs_local.value = 0;
		A__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		B__global_0_0_copy_tSetInputs_local.value = 0;
		B__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		R__global_0_0_copy_tSetInputs_local.value = 0;
		R__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		A__global_0_0_copy_tSetInputs = A__global_0_0_copy_tSetInputs_local;
		B__global_0_0_copy_tSetInputs = B__global_0_0_copy_tSetInputs_local;
		R__global_0_0_copy_tSetInputs = R__global_0_0_copy_tSetInputs_local;
		// forec:statement:pause:pause5:start
		tSetInputs__thread.programCounter = &&pause5;
		goto *tSetInputs__thread.nextThread -> programCounter;
		pause5:;
		// forec:statement:pause:pause5:end
		// Update the values of the used shared variables from their global copy.
		A__global_0_0_copy_tSetInputs_local = A__global_0_0;
		B__global_0_0_copy_tSetInputs_local = B__global_0_0;
		R__global_0_0_copy_tSetInputs_local = R__global_0_0;


		A__global_0_0_copy_tSetInputs_local.value = 1;
		A__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		B__global_0_0_copy_tSetInputs_local.value = 1;
		B__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		R__global_0_0_copy_tSetInputs_local.value = 1;
		R__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		A__global_0_0_copy_tSetInputs = A__global_0_0_copy_tSetInputs_local;
		B__global_0_0_copy_tSetInputs = B__global_0_0_copy_tSetInputs_local;
		R__global_0_0_copy_tSetInputs = R__global_0_0_copy_tSetInputs_local;
		// forec:statement:pause:pause6:start
		tSetInputs__thread.programCounter = &&pause6;
		goto *tSetInputs__thread.nextThread -> programCounter;
		pause6:;
		// forec:statement:pause:pause6:end
		// Update the values of the used shared variables from their global copy.
		A__global_0_0_copy_tSetInputs_local = A__global_0_0;
		B__global_0_0_copy_tSetInputs_local = B__global_0_0;
		R__global_0_0_copy_tSetInputs_local = R__global_0_0;


		A__global_0_0_copy_tSetInputs_local.value = 0;
		A__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		B__global_0_0_copy_tSetInputs_local.value = 0;
		B__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		R__global_0_0_copy_tSetInputs_local.value = 0;
		R__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		A__global_0_0_copy_tSetInputs = A__global_0_0_copy_tSetInputs_local;
		B__global_0_0_copy_tSetInputs = B__global_0_0_copy_tSetInputs_local;
		R__global_0_0_copy_tSetInputs = R__global_0_0_copy_tSetInputs_local;
		// forec:statement:pause:pause7:start
		tSetInputs__thread.programCounter = &&pause7;
		goto *tSetInputs__thread.nextThread -> programCounter;
		pause7:;
		// forec:statement:pause:pause7:end
		// Update the values of the used shared variables from their global copy.
		A__global_0_0_copy_tSetInputs_local = A__global_0_0;
		B__global_0_0_copy_tSetInputs_local = B__global_0_0;
		R__global_0_0_copy_tSetInputs_local = R__global_0_0;


		A__global_0_0_copy_tSetInputs_local.value = 1;
		A__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		B__global_0_0_copy_tSetInputs_local.value = 1;
		B__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		R__global_0_0_copy_tSetInputs_local.value = 0;
		R__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		A__global_0_0_copy_tSetInputs = A__global_0_0_copy_tSetInputs_local;
		B__global_0_0_copy_tSetInputs = B__global_0_0_copy_tSetInputs_local;
		R__global_0_0_copy_tSetInputs = R__global_0_0_copy_tSetInputs_local;
		// forec:statement:pause:pause8:start
		tSetInputs__thread.programCounter = &&pause8;
		goto *tSetInputs__thread.nextThread -> programCounter;
		pause8:;
		// forec:statement:pause:pause8:end
		// Update the values of the used shared variables from their global copy.
		A__global_0_0_copy_tSetInputs_local = A__global_0_0;
		B__global_0_0_copy_tSetInputs_local = B__global_0_0;
		R__global_0_0_copy_tSetInputs_local = R__global_0_0;


		A__global_0_0_copy_tSetInputs_local.value = 0;
		A__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		B__global_0_0_copy_tSetInputs_local.value = 0;
		B__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;
		R__global_0_0_copy_tSetInputs_local.value = 0;
		R__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		A__global_0_0_copy_tSetInputs = A__global_0_0_copy_tSetInputs_local;
		B__global_0_0_copy_tSetInputs = B__global_0_0_copy_tSetInputs_local;
		R__global_0_0_copy_tSetInputs = R__global_0_0_copy_tSetInputs_local;
		// forec:statement:pause:pause9:start
		tSetInputs__thread.programCounter = &&pause9;
		goto *tSetInputs__thread.nextThread -> programCounter;
		pause9:;
		// forec:statement:pause:pause9:end
		// Update the values of the used shared variables from their global copy.
		A__global_0_0_copy_tSetInputs_local = A__global_0_0;
		B__global_0_0_copy_tSetInputs_local = B__global_0_0;
		R__global_0_0_copy_tSetInputs_local = R__global_0_0;


		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		A__global_0_0_copy_tSetInputs = A__global_0_0_copy_tSetInputs_local;
		B__global_0_0_copy_tSetInputs = B__global_0_0_copy_tSetInputs_local;
		R__global_0_0_copy_tSetInputs = R__global_0_0_copy_tSetInputs_local;

		// forec:scheduler:threadRemove:tSetInputs:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		tSetInputs__thread.nextThread -> prevThread = tSetInputs__thread.prevThread;
		tSetInputs__thread.prevThread -> nextThread = tSetInputs__thread.nextThread;
		goto *tSetInputs__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:tSetInputs:end
	} // tSetInputs__thread
	// forec:thread:tSetInputs:end


} // End of the main() function.

