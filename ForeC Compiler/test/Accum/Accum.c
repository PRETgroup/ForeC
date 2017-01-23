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


// Shared control variables for par(...)s -------------------------
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

const int plus(const int *copy1__plus_0_0, const int *copy2__plus_0_0) {
	return * copy1__plus_0_0 + * copy2__plus_0_0;
}

// thread t1__thread(void);
// thread t2__thread(void);
// thread accumulate__thread(void);

typedef struct {
	/* shared */ int value;
	int status;
} Shared_count__global_0_0;
Shared_count__global_0_0 count__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED} /* combine with plus */;

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// accumulate
Shared_count__global_0_0 count__global_0_0_copy_accumulate = {.status = FOREC_SHARED_UNMODIFIED};
// main
// t1
Shared_count__global_0_0 count__global_0_0_copy_t1 = {.status = FOREC_SHARED_UNMODIFIED};
// t2
Shared_count__global_0_0 count__global_0_0_copy_t2 = {.status = FOREC_SHARED_UNMODIFIED};

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
	Thread accumulate__thread;
	Thread t1__thread;
	Thread t2__thread;
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

	// par0(t1__thread, t2__thread, accumulate__thread);
	// forec:statement:par:par0:start
	// Set the par(...) information.
	mainParParent.parId = 0;
	mainParParent.parStatus = FOREC_PAR_ON;

	// Link the threads and handlers together.
	mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
	t1__thread.programCounter = &&t1__thread;
	mainReactionStartMaster0.nextThread = &t1__thread;
	t1__thread.prevThread = &mainReactionStartMaster0;
	t2__thread.programCounter = &&t2__thread;
	t1__thread.nextThread = &t2__thread;
	t2__thread.prevThread = &t1__thread;
	accumulate__thread.programCounter = &&accumulate__thread;
	t2__thread.nextThread = &accumulate__thread;
	accumulate__thread.prevThread = &t2__thread;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	accumulate__thread.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &accumulate__thread;

	// Link the last and first threads/handlers together.
	mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
	mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

	// Set the join address.
	mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

	// Set the core information.
	mainParCore0.activeThreads = 3;
	mainParCore0.reactionCounter = mainParReactionCounter;

	// Go to the first thread.
	goto t1__thread;
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
		int index;
		int numberOfModifiedCopies;

		// count__global_0_0
		numberOfModifiedCopies = 0;
		Shared_count__global_0_0 *modified_count__global_0_0[2];
		// Find the modified copies.
		if (count__global_0_0_copy_t1.status == FOREC_SHARED_MODIFIED) {
			count__global_0_0_copy_t1.status = FOREC_SHARED_UNMODIFIED;
			modified_count__global_0_0[numberOfModifiedCopies] = &count__global_0_0_copy_t1;
			++numberOfModifiedCopies;
		}
		if (count__global_0_0_copy_t2.status == FOREC_SHARED_MODIFIED) {
			count__global_0_0_copy_t2.status = FOREC_SHARED_UNMODIFIED;
			modified_count__global_0_0[numberOfModifiedCopies] = &count__global_0_0_copy_t2;
			++numberOfModifiedCopies;
		}
		// Assign the first modified copy.
		if (numberOfModifiedCopies > 0) {
			count__global_0_0.value = modified_count__global_0_0[0]->value;
		}
		// Combine with the remaining modified copies.
		for (index = 1; index < numberOfModifiedCopies; ++index) {
			count__global_0_0.value = plus(&count__global_0_0.value, &modified_count__global_0_0[index]->value);
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
	// forec:thread:accumulate:start
	/*--------------------------------------------------------------
	| Thread accumulate
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_count__global_0_0 count__global_0_0_copy_accumulate_local;

	// Thread body -------------------------------------------------
	accumulate__thread: {
		// Initialise the local copies of shared variables.
		count__global_0_0_copy_accumulate_local.value = count__global_0_0.value;
		count__global_0_0_copy_accumulate_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		while (1) {
			// pause;
			// forec:statement:pause:pause2:start
			accumulate__thread.programCounter = &&pause2;
			goto *accumulate__thread.nextThread -> programCounter;
			pause2:;
			// forec:statement:pause:pause2:end
			// Update the values of the used shared variables from their global copy.
			count__global_0_0_copy_accumulate_local = count__global_0_0;


			printf("%d\n", count__global_0_0_copy_accumulate_local.value);
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:accumulate:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		accumulate__thread.nextThread -> prevThread = accumulate__thread.prevThread;
		accumulate__thread.prevThread -> nextThread = accumulate__thread.nextThread;
		goto *accumulate__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:accumulate:end
	} // accumulate__thread
	// forec:thread:accumulate:end

	// forec:thread:t1:start
	/*--------------------------------------------------------------
	| Thread t1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_count__global_0_0 count__global_0_0_copy_t1_local;

	// Thread body -------------------------------------------------
	t1__thread: {
		// Initialise the local copies of shared variables.
		count__global_0_0_copy_t1_local.value = count__global_0_0.value;
		count__global_0_0_copy_t1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		while (1) {
			count__global_0_0_copy_t1_local.value = count__global_0_0_copy_t1_local.value + 1;
			count__global_0_0_copy_t1_local.status = FOREC_SHARED_MODIFIED;

			// pause;
			// Write the local copy of shared variables back to their global copy.
			count__global_0_0_copy_t1 = count__global_0_0_copy_t1_local;
			// forec:statement:pause:pause0:start
			t1__thread.programCounter = &&pause0;
			goto *t1__thread.nextThread -> programCounter;
			pause0:;
			// forec:statement:pause:pause0:end
			// Update the values of the used shared variables from their global copy.
			count__global_0_0_copy_t1_local = count__global_0_0;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		count__global_0_0_copy_t1 = count__global_0_0_copy_t1_local;

		// forec:scheduler:threadRemove:t1:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		t1__thread.nextThread -> prevThread = t1__thread.prevThread;
		t1__thread.prevThread -> nextThread = t1__thread.nextThread;
		goto *t1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:t1:end
	} // t1__thread
	// forec:thread:t1:end

	// forec:thread:t2:start
	/*--------------------------------------------------------------
	| Thread t2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_count__global_0_0 count__global_0_0_copy_t2_local;

	// Thread body -------------------------------------------------
	t2__thread: {
		// Initialise the local copies of shared variables.
		count__global_0_0_copy_t2_local.value = count__global_0_0.value;
		count__global_0_0_copy_t2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		while (1) {
			count__global_0_0_copy_t2_local.value = count__global_0_0_copy_t2_local.value + 1;
			count__global_0_0_copy_t2_local.status = FOREC_SHARED_MODIFIED;

			// pause;
			// Write the local copy of shared variables back to their global copy.
			count__global_0_0_copy_t2 = count__global_0_0_copy_t2_local;
			// forec:statement:pause:pause1:start
			t2__thread.programCounter = &&pause1;
			goto *t2__thread.nextThread -> programCounter;
			pause1:;
			// forec:statement:pause:pause1:end
			// Update the values of the used shared variables from their global copy.
			count__global_0_0_copy_t2_local = count__global_0_0;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		count__global_0_0_copy_t2 = count__global_0_0_copy_t2_local;

		// forec:scheduler:threadRemove:t2:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		t2__thread.nextThread -> prevThread = t2__thread.prevThread;
		t2__thread.prevThread -> nextThread = t2__thread.nextThread;
		goto *t2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:t2:end
	} // t2__thread
	// forec:thread:t2:end


} // End of the main() function.

