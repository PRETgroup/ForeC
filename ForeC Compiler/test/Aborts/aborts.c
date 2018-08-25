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
volatile int init__abortWeakNonImmediate2 = 0;

// Shared control variables for par(...)s ----------------------
// Thread main with par(...)s
volatile Parent mainParParent;
volatile Core mainParCore0;
volatile int mainParReactionCounter;


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
} Shared_R__global_0_0;
Shared_R__global_0_0 R__global_0_0 = {.value = 1, .status = FOREC_SHARED_UNMODIFIED};

// thread tSetInputs__thread(void);
// thread tDebug__thread(void);
// thread tStrongNonImmediateAbort__thread(void);
// thread tStrongImmediateAbort__thread(void);
// thread tWeakNonImmediateAbort__thread(void);
// thread tWeakImmediateAbort__thread(void);

typedef struct {
	/* shared */ int value;
	int status;
} Shared_strongNonImmediateAbortResult__global_0_0;
Shared_strongNonImmediateAbortResult__global_0_0 strongNonImmediateAbortResult__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value;
	int status;
} Shared_strongImmediateAbortResult__global_0_0;
Shared_strongImmediateAbortResult__global_0_0 strongImmediateAbortResult__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value;
	int status;
} Shared_weakNonImmediateAbortResult__global_0_0;
Shared_weakNonImmediateAbortResult__global_0_0 weakNonImmediateAbortResult__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value;
	int status;
} Shared_weakImmediateAbortResult__global_0_0;
Shared_weakImmediateAbortResult__global_0_0 weakImmediateAbortResult__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};

const int MAX_TICK_NUMBER__global_0_0 = 3;

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// main
// tDebug
Shared_R__global_0_0 R__global_0_0_copy_tDebug = {.status = FOREC_SHARED_UNMODIFIED};
// tSetInputs
Shared_R__global_0_0 R__global_0_0_copy_tSetInputs = {.status = FOREC_SHARED_UNMODIFIED};
// tStrongImmediateAbort
Shared_R__global_0_0 R__global_0_0_copy_tStrongImmediateAbort = {.status = FOREC_SHARED_UNMODIFIED};
// tStrongNonImmediateAbort
Shared_R__global_0_0 R__global_0_0_copy_tStrongNonImmediateAbort = {.status = FOREC_SHARED_UNMODIFIED};
// tWeakImmediateAbort
Shared_R__global_0_0 R__global_0_0_copy_tWeakImmediateAbort = {.status = FOREC_SHARED_UNMODIFIED};
// tWeakNonImmediateAbort
Shared_R__global_0_0 R__global_0_0_copy_tWeakNonImmediateAbort = {.status = FOREC_SHARED_UNMODIFIED};

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


	// Reset ForeC mutex values

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
	Thread tDebug__thread;
	Thread tSetInputs__thread;
	Thread tStrongImmediateAbort__thread;
	Thread tStrongNonImmediateAbort__thread;
	Thread tWeakImmediateAbort__thread;
	Thread tWeakNonImmediateAbort__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionEndMaster0;


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

	// par0(tSetInputs__thread, tDebug__thread, tStrongNonImmediateAbort__thread, tStrongImmediateAbort__thread, tWeakNonImmediateAbort__thread, tWeakImmediateAbort__thread);
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
	tStrongNonImmediateAbort__thread.programCounter = &&tStrongNonImmediateAbort__thread;
	tDebug__thread.nextThread = &tStrongNonImmediateAbort__thread;
	tStrongNonImmediateAbort__thread.prevThread = &tDebug__thread;
	tStrongImmediateAbort__thread.programCounter = &&tStrongImmediateAbort__thread;
	tStrongNonImmediateAbort__thread.nextThread = &tStrongImmediateAbort__thread;
	tStrongImmediateAbort__thread.prevThread = &tStrongNonImmediateAbort__thread;
	tWeakNonImmediateAbort__thread.programCounter = &&tWeakNonImmediateAbort__thread;
	tStrongImmediateAbort__thread.nextThread = &tWeakNonImmediateAbort__thread;
	tWeakNonImmediateAbort__thread.prevThread = &tStrongImmediateAbort__thread;
	tWeakImmediateAbort__thread.programCounter = &&tWeakImmediateAbort__thread;
	tWeakNonImmediateAbort__thread.nextThread = &tWeakImmediateAbort__thread;
	tWeakImmediateAbort__thread.prevThread = &tWeakNonImmediateAbort__thread;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	tWeakImmediateAbort__thread.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &tWeakImmediateAbort__thread;

	// Link the last and first threads/handlers together.
	mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
	mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

	// Set the join address.
	mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

	// Set the core information.
	mainParCore0.activeThreads = 6;
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

	// Combine shared variables.
	int parId = mainParParent.parId;
	if (parId == 0) {

		// R__global_0_0
		if (R__global_0_0_copy_tSetInputs.status == FOREC_SHARED_MODIFIED) {
			R__global_0_0_copy_tSetInputs.status = FOREC_SHARED_UNMODIFIED;
			R__global_0_0.value = R__global_0_0_copy_tSetInputs.value;
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
 


	// Abort check handlers ----------------------------------------




/*==============================================================
| ForeC threads:
| Threads' code translated into C code.
*=============================================================*/
	// forec:thread:tDebug:start
	/*--------------------------------------------------------------
	| Thread tDebug
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_R__global_0_0 R__global_0_0_copy_tDebug_local;
	int i__tDebug_1_0;

	// Thread body -------------------------------------------------
	tDebug__thread: {
		// Initialise the local copies of shared variables.
		R__global_0_0_copy_tDebug_local.value = R__global_0_0.value;
		R__global_0_0_copy_tDebug_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		for (i__tDebug_1_0 = 0; i__tDebug_1_0 < MAX_TICK_NUMBER__global_0_0; i__tDebug_1_0++) {
			printf("Tick %d: R = %d\n", i__tDebug_1_0, R__global_0_0_copy_tDebug_local.value);

			// pause;
			// forec:statement:pause:pause10:start
			tDebug__thread.programCounter = &&pause10;
			goto *tDebug__thread.nextThread -> programCounter;
			pause10:;
			// forec:statement:pause:pause10:end
			// Update the values of the used shared variables from their global copy.
			R__global_0_0_copy_tDebug_local = R__global_0_0;

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
	Shared_R__global_0_0 R__global_0_0_copy_tSetInputs_local;

	// Thread body -------------------------------------------------
	tSetInputs__thread: {
		// Initialise the local copies of shared variables.
		R__global_0_0_copy_tSetInputs_local.value = R__global_0_0.value;
		R__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		R__global_0_0_copy_tSetInputs_local.value = 1;
		R__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		R__global_0_0_copy_tSetInputs = R__global_0_0_copy_tSetInputs_local;
		// forec:statement:pause:pause0:start
		tSetInputs__thread.programCounter = &&pause0;
		goto *tSetInputs__thread.nextThread -> programCounter;
		pause0:;
		// forec:statement:pause:pause0:end
		// Update the values of the used shared variables from their global copy.
		R__global_0_0_copy_tSetInputs_local = R__global_0_0;


		R__global_0_0_copy_tSetInputs_local.value = 1;
		R__global_0_0_copy_tSetInputs_local.status = FOREC_SHARED_MODIFIED;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		R__global_0_0_copy_tSetInputs = R__global_0_0_copy_tSetInputs_local;
		// forec:statement:pause:pause1:start
		tSetInputs__thread.programCounter = &&pause1;
		goto *tSetInputs__thread.nextThread -> programCounter;
		pause1:;
		// forec:statement:pause:pause1:end
		// Update the values of the used shared variables from their global copy.
		R__global_0_0_copy_tSetInputs_local = R__global_0_0;


		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
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

	// forec:thread:tStrongImmediateAbort:start
	/*--------------------------------------------------------------
	| Thread tStrongImmediateAbort
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_R__global_0_0 R__global_0_0_copy_tStrongImmediateAbort_local;

	// Thread body -------------------------------------------------
	tStrongImmediateAbort__thread: {
		// Initialise the local copies of shared variables.
		R__global_0_0_copy_tStrongImmediateAbort_local.value = R__global_0_0.value;
		R__global_0_0_copy_tStrongImmediateAbort_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		/* abortStrongImmediate1 */ {
			// forec:statement:abort:abortStrongImmediate1:start
			if (R__global_0_0_copy_tStrongImmediateAbort_local.value == 1) {
				goto abortEnd_abortStrongImmediate1;
			}
			// forec:statement:abort:abortStrongImmediate1:end

			printf("strongImmediateAbortResult = 1\n");

			// pause;
			// forec:statement:pause:pause4:start
			tStrongImmediateAbort__thread.programCounter = &&pause4;
			goto *tStrongImmediateAbort__thread.nextThread -> programCounter;
			pause4:;
			// forec:statement:pause:pause4:end
			// Update the values of the used shared variables from their global copy.
			R__global_0_0_copy_tStrongImmediateAbort_local = R__global_0_0;

			// Strong aborts:
			// forec:statement:abort:abortStrongImmediate1:start
			if (R__global_0_0_copy_tStrongImmediateAbort_local.value == 1) {
				goto abortEnd_abortStrongImmediate1;
			}
			// forec:statement:abort:abortStrongImmediate1:end

			printf("strongImmediateAbortResult = 2\n");

			// pause;
			// forec:statement:pause:pause5:start
			tStrongImmediateAbort__thread.programCounter = &&pause5;
			goto *tStrongImmediateAbort__thread.nextThread -> programCounter;
			pause5:;
			// forec:statement:pause:pause5:end
			// Update the values of the used shared variables from their global copy.
			R__global_0_0_copy_tStrongImmediateAbort_local = R__global_0_0;

			// Strong aborts:
			// forec:statement:abort:abortStrongImmediate1:start
			if (R__global_0_0_copy_tStrongImmediateAbort_local.value == 1) {
				goto abortEnd_abortStrongImmediate1;
			}
			// forec:statement:abort:abortStrongImmediate1:end
			abortEnd_abortStrongImmediate1:;
		} // when (R__global_0_0_copy_tStrongImmediateAbort_local.value == 1);
		// forec:statement:abort:abortStrongImmediate1:scope:end

		printf("strongImmediateAbortResult = terminated\n");

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:tStrongImmediateAbort:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		tStrongImmediateAbort__thread.nextThread -> prevThread = tStrongImmediateAbort__thread.prevThread;
		tStrongImmediateAbort__thread.prevThread -> nextThread = tStrongImmediateAbort__thread.nextThread;
		goto *tStrongImmediateAbort__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:tStrongImmediateAbort:end
	} // tStrongImmediateAbort__thread
	// forec:thread:tStrongImmediateAbort:end

	// forec:thread:tStrongNonImmediateAbort:start
	/*--------------------------------------------------------------
	| Thread tStrongNonImmediateAbort
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_R__global_0_0 R__global_0_0_copy_tStrongNonImmediateAbort_local;

	// Thread body -------------------------------------------------
	tStrongNonImmediateAbort__thread: {
		// Initialise the local copies of shared variables.
		R__global_0_0_copy_tStrongNonImmediateAbort_local.value = R__global_0_0.value;
		R__global_0_0_copy_tStrongNonImmediateAbort_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		/* abortStrongNonImmediate0 */ {
			init__abortStrongNonImmediate0 = 0;
			// forec:statement:abort:abortStrongNonImmediate0:start
			if (R__global_0_0_copy_tStrongNonImmediateAbort_local.value == 1 && init__abortStrongNonImmediate0 == 1) {
				goto abortEnd_abortStrongNonImmediate0;
			}
			init__abortStrongNonImmediate0 = 1;
			// forec:statement:abort:abortStrongNonImmediate0:end

			printf("strongNonImmediateAbortResult = 1\n");

			// pause;
			// forec:statement:pause:pause2:start
			tStrongNonImmediateAbort__thread.programCounter = &&pause2;
			goto *tStrongNonImmediateAbort__thread.nextThread -> programCounter;
			pause2:;
			// forec:statement:pause:pause2:end
			// Update the values of the used shared variables from their global copy.
			R__global_0_0_copy_tStrongNonImmediateAbort_local = R__global_0_0;

			// Strong aborts:
			// forec:statement:abort:abortStrongNonImmediate0:start
			if (R__global_0_0_copy_tStrongNonImmediateAbort_local.value == 1 && init__abortStrongNonImmediate0 == 1) {
				goto abortEnd_abortStrongNonImmediate0;
			}
			// forec:statement:abort:abortStrongNonImmediate0:end

			printf("strongNonImmediateAbortResult = 2\n");

			// pause;
			// forec:statement:pause:pause3:start
			tStrongNonImmediateAbort__thread.programCounter = &&pause3;
			goto *tStrongNonImmediateAbort__thread.nextThread -> programCounter;
			pause3:;
			// forec:statement:pause:pause3:end
			// Update the values of the used shared variables from their global copy.
			R__global_0_0_copy_tStrongNonImmediateAbort_local = R__global_0_0;

			// Strong aborts:
			// forec:statement:abort:abortStrongNonImmediate0:start
			if (R__global_0_0_copy_tStrongNonImmediateAbort_local.value == 1 && init__abortStrongNonImmediate0 == 1) {
				goto abortEnd_abortStrongNonImmediate0;
			}
			// forec:statement:abort:abortStrongNonImmediate0:end
			abortEnd_abortStrongNonImmediate0:;
		} // when (R__global_0_0_copy_tStrongNonImmediateAbort_local.value == 1 && init__abortStrongNonImmediate0 == 1);
		// forec:statement:abort:abortStrongNonImmediate0:scope:end

		printf("strongNonImmediateAbortResult = terminated\n");

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:tStrongNonImmediateAbort:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		tStrongNonImmediateAbort__thread.nextThread -> prevThread = tStrongNonImmediateAbort__thread.prevThread;
		tStrongNonImmediateAbort__thread.prevThread -> nextThread = tStrongNonImmediateAbort__thread.nextThread;
		goto *tStrongNonImmediateAbort__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:tStrongNonImmediateAbort:end
	} // tStrongNonImmediateAbort__thread
	// forec:thread:tStrongNonImmediateAbort:end

	// forec:thread:tWeakImmediateAbort:start
	/*--------------------------------------------------------------
	| Thread tWeakImmediateAbort
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_R__global_0_0 R__global_0_0_copy_tWeakImmediateAbort_local;

	// Thread body -------------------------------------------------
	tWeakImmediateAbort__thread: {
		// Initialise the local copies of shared variables.
		R__global_0_0_copy_tWeakImmediateAbort_local.value = R__global_0_0.value;
		R__global_0_0_copy_tWeakImmediateAbort_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		/* abortWeakImmediate3 */ {
			printf("weakImmediateAbortResult = 1\n");

			// Weak aborts:
			// forec:statement:abort:abortWeakImmediate3:start
			if (R__global_0_0_copy_tWeakImmediateAbort_local.value == 1) {
				goto abortEnd_abortWeakImmediate3;
			}
			// forec:statement:abort:abortWeakImmediate3:end
			// pause;
			// forec:statement:pause:pause8:start
			tWeakImmediateAbort__thread.programCounter = &&pause8;
			goto *tWeakImmediateAbort__thread.nextThread -> programCounter;
			pause8:;
			// forec:statement:pause:pause8:end
			// Update the values of the used shared variables from their global copy.
			R__global_0_0_copy_tWeakImmediateAbort_local = R__global_0_0;


			printf("weakImmediateAbortResult = 2\n");

			// Weak aborts:
			// forec:statement:abort:abortWeakImmediate3:start
			if (R__global_0_0_copy_tWeakImmediateAbort_local.value == 1) {
				goto abortEnd_abortWeakImmediate3;
			}
			// forec:statement:abort:abortWeakImmediate3:end
			// pause;
			// forec:statement:pause:pause9:start
			tWeakImmediateAbort__thread.programCounter = &&pause9;
			goto *tWeakImmediateAbort__thread.nextThread -> programCounter;
			pause9:;
			// forec:statement:pause:pause9:end
			// Update the values of the used shared variables from their global copy.
			R__global_0_0_copy_tWeakImmediateAbort_local = R__global_0_0;

			abortEnd_abortWeakImmediate3:;
		} // when (R__global_0_0_copy_tWeakImmediateAbort_local.value == 1);
		// forec:statement:abort:abortWeakImmediate3:scope:end

		printf("weakImmediateAbortResult = terminated\n");

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:tWeakImmediateAbort:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		tWeakImmediateAbort__thread.nextThread -> prevThread = tWeakImmediateAbort__thread.prevThread;
		tWeakImmediateAbort__thread.prevThread -> nextThread = tWeakImmediateAbort__thread.nextThread;
		goto *tWeakImmediateAbort__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:tWeakImmediateAbort:end
	} // tWeakImmediateAbort__thread
	// forec:thread:tWeakImmediateAbort:end

	// forec:thread:tWeakNonImmediateAbort:start
	/*--------------------------------------------------------------
	| Thread tWeakNonImmediateAbort
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_R__global_0_0 R__global_0_0_copy_tWeakNonImmediateAbort_local;

	// Thread body -------------------------------------------------
	tWeakNonImmediateAbort__thread: {
		// Initialise the local copies of shared variables.
		R__global_0_0_copy_tWeakNonImmediateAbort_local.value = R__global_0_0.value;
		R__global_0_0_copy_tWeakNonImmediateAbort_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		/* abortWeakNonImmediate2 */ {
			init__abortWeakNonImmediate2 = 0;
			printf("weakNonImmediateAbortResult = 1\n");

			// Weak aborts:
			// forec:statement:abort:abortWeakNonImmediate2:start
			if (R__global_0_0_copy_tWeakNonImmediateAbort_local.value == 1 && init__abortWeakNonImmediate2 == 1) {
				goto abortEnd_abortWeakNonImmediate2;
			}
			init__abortWeakNonImmediate2 = 1;
			// forec:statement:abort:abortWeakNonImmediate2:end
			// pause;
			// forec:statement:pause:pause6:start
			tWeakNonImmediateAbort__thread.programCounter = &&pause6;
			goto *tWeakNonImmediateAbort__thread.nextThread -> programCounter;
			pause6:;
			// forec:statement:pause:pause6:end
			// Update the values of the used shared variables from their global copy.
			R__global_0_0_copy_tWeakNonImmediateAbort_local = R__global_0_0;


			printf("weakNonImmediateAbortResult = 2\n");

			// Weak aborts:
			// forec:statement:abort:abortWeakNonImmediate2:start
			if (R__global_0_0_copy_tWeakNonImmediateAbort_local.value == 1 && init__abortWeakNonImmediate2 == 1) {
				goto abortEnd_abortWeakNonImmediate2;
			}
			init__abortWeakNonImmediate2 = 1;
			// forec:statement:abort:abortWeakNonImmediate2:end
			// pause;
			// forec:statement:pause:pause7:start
			tWeakNonImmediateAbort__thread.programCounter = &&pause7;
			goto *tWeakNonImmediateAbort__thread.nextThread -> programCounter;
			pause7:;
			// forec:statement:pause:pause7:end
			// Update the values of the used shared variables from their global copy.
			R__global_0_0_copy_tWeakNonImmediateAbort_local = R__global_0_0;

			abortEnd_abortWeakNonImmediate2:;
		} // when (R__global_0_0_copy_tWeakNonImmediateAbort_local.value == 1 && init__abortWeakNonImmediate2 == 1);
		// forec:statement:abort:abortWeakNonImmediate2:scope:end

		printf("weakNonImmediateAbortResult = terminated\n");

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:tWeakNonImmediateAbort:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		tWeakNonImmediateAbort__thread.nextThread -> prevThread = tWeakNonImmediateAbort__thread.prevThread;
		tWeakNonImmediateAbort__thread.prevThread -> nextThread = tWeakNonImmediateAbort__thread.nextThread;
		goto *tWeakNonImmediateAbort__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:tWeakNonImmediateAbort:end
	} // tWeakNonImmediateAbort__thread
	// forec:thread:tWeakNonImmediateAbort:end


} // End of the main() function.

