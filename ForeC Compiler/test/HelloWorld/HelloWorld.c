/*==============================================================
| Hardware architecture specific declarations:
| Cores, mutex and input/output information.
*=============================================================*/
#include <pthread.h>

// Mapping Pthreads to processor cores
pthread_t cores[2];
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

// Structure to pass input arguments into forecMain.
typedef struct {
	unsigned short coreId;
	int argc;
	char **argv;
} Arguments;


// Shared control variables for par(...)s -------------------------
// Thread main with par(...)s
volatile Parent mainParParent;
volatile Core mainParCore0;
volatile Core mainParCore1;
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

// thread hello__thread(void);
// thread world__thread(void);

typedef struct {
	/* shared */ int value;
	unsigned short int status;
} Shared_state__global_0_0;
Shared_state__global_0_0 state__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED} /* combine with plus */;

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// hello
// main
Shared_state__global_0_0 state__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
// world
Shared_state__global_0_0 state__global_0_0_copy_world = {.status = FOREC_SHARED_UNMODIFIED};

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
	mainParCore1.sync = 1;
	mainParCore1.status = FOREC_CORE_REACTING;
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

	// Slave cores
	Arguments arguments1 = {.coreId = 1, .argc = argc__main_0_0, .argv = argv__main_0_0};
	pthread_create(&cores[1], &slaveCoreAttribute, forecMain, (void *)&arguments1);

	// End core execution
	pthread_attr_destroy(&masterCoreAttribute);
	pthread_attr_destroy(&slaveCoreAttribute);
	
	// Program termination
	pthread_join(cores[0], NULL);
	pthread_join(cores[1], NULL);

}


/*==============================================================
| Original main(...) function:
*=============================================================*/
void *forecMain(void *args) {
	Arguments *arguments = (Arguments *)args;
	unsigned short int coreId = arguments->coreId;
	int argc__main_0_0 = arguments->argc;
	char **argv__main_0_0 = arguments->argv;

	// Variables for par()s ----------------------------------------
	// par0
	Thread hello__thread;
	Thread world__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionStartSlave1;
	Thread mainReactionEndMaster0;
	Thread mainReactionEndSlave1;
	Thread abortStrong0Check0;
	Thread abortStrong0Check1;


	// Let cores jump to their code segment ------------------------
	switch (coreId) {
		case (0):
			goto mainParCore0;

		case (1):
			goto mainParCore1;

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
	Shared_state__global_0_0 state__global_0_0_copy_main_local;

mainParCore0: {
	// Initialise the local copies of shared variables.
	state__global_0_0_copy_main_local = state__global_0_0;
	//--------------------------------------------------------------

	/* abortStrong0 */ {
		// forec:statement:abort:abortStrong0:start
		if (state__global_0_0_copy_main_local.value == 1) {
			goto abortEnd_abortStrong0;
		}
		// forec:statement:abort:abortStrong0:end

		// par0(hello__thread, world__thread);
		// Set the par(...) information.
		mainParParent.parId = 0;
		mainParParent.parStatus = FOREC_PAR_ON;

		// Link the threads and handlers together.
		mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
		abortStrong0Check0.programCounter = &&abortStrong0Check0;
		mainReactionStartMaster0.nextThread = &abortStrong0Check0;
		abortStrong0Check0.prevThread = &mainReactionStartMaster0;
		hello__thread.programCounter = &&hello__thread;
		abortStrong0Check0.nextThread = &hello__thread;
		hello__thread.prevThread = &abortStrong0Check0;
		mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
		hello__thread.nextThread = &mainReactionEndMaster0;
		mainReactionEndMaster0.prevThread = &hello__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
		mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

		// Set the join address.
		mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

		// Set the core information.
		mainParCore0.activeThreads = 1;
		mainParCore0.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		// forec:statement:par:par0:start
		goto hello__thread;
		par0JoinAddress_mainParCore0:;
		// forec:statement:par:par0:end
		state__global_0_0_copy_main_local = state__global_0_0;
		abortEnd_abortStrong0:;
	} // when (state__global_0_0_copy_main_local.value == 1);
	// forec:statement:abort:abortStrong0:scope:end

	//--------------------------------------------------------------
	// Write the defined shared variables back to their global copy.


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
		while(mainParCore1.status == FOREC_CORE_REACTING);

		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;

		// Set slave cores' status to reacting.
		mainParCore1.status = FOREC_CORE_REACTING;

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

	// Reset the mutex.

	// Combine shared variables.
	unsigned short int parId = mainParParent.parId;
	if (parId == 0) {
		unsigned short int index;
		unsigned short int numberOfModifiedCopies;

		// state__global_0_0
		if (state__global_0_0_copy_world.status == FOREC_SHARED_MODIFIED) {
			state__global_0_0_copy_world.status = FOREC_SHARED_UNMODIFIED;
			state__global_0_0.value = state__global_0_0_copy_world.value;
		}
	} else {
		// Nothing.
	}

	// Return back to the parent thread if all the cores have terminated.
	if (1 && mainParCore0.status == FOREC_CORE_TERMINATED && mainParCore1.status == FOREC_CORE_TERMINATED) {
		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;
		
		// Set slave cores' status to reacting
		mainParCore1.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronization.
		mainParReactionCounter++;

		goto *mainParParent.programCounter;
	}

	// Set slave cores' status to reacting
	mainParCore1.status = FOREC_CORE_REACTING;

	// Increment the reaction counter for synchronization.
	mainParReactionCounter++;

	// Go to the next thread.
	goto *mainReactionEndMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:main:master:0:end
 


	// Abort check handlers ----------------------------------------
	// forec:scheduler:abortHandler:abortStrong0:0:start
	// abortStrong0 (state__global_0_0.value == 1)
abortStrong0Check0: {
	// Check the abort condition.
	if (state__global_0_0.value == 1) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore0.activeThreads = 0;

		// Update the parent thread to resume at the end of the abort scope.
		mainParParent.programCounter = &&abortEnd_abortStrong0;
		
		goto mainReactionEndMaster0;
	}
	
	// Continue to the next thread.
	goto *abortStrong0Check0.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrong0:0:end


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
		abortStrong0Check1.programCounter = &&abortStrong0Check1;
		mainReactionStartSlave1.nextThread = &abortStrong0Check1;
		abortStrong0Check1.prevThread = &mainReactionStartSlave1;
		world__thread.programCounter = &&world__thread;
		abortStrong0Check1.nextThread = &world__thread;
		world__thread.prevThread = &abortStrong0Check1;
		mainReactionEndSlave1.programCounter = &&mainReactionEndSlave1;
		world__thread.nextThread = &mainReactionEndSlave1;
		mainReactionEndSlave1.prevThread = &world__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave1.nextThread = &mainReactionStartSlave1;
		mainReactionStartSlave1.prevThread = &mainReactionEndSlave1;

		// Set the core information.
		mainParCore1.activeThreads = 1;
		mainParCore1.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto world__thread;
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
	// forec:scheduler:abortHandler:abortStrong0:1:start
	// abortStrong0 (state__global_0_0.value == 1)
abortStrong0Check1: {
	// Check the abort condition.
	if (state__global_0_0.value == 1) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore1.activeThreads = 0;
		
		goto mainReactionEndSlave1;
	}
	
	// Continue to the next thread.
	goto *abortStrong0Check1.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrong0:1:end



/*==============================================================
| ForeC threads:
| Threads' code translated into C code.
*=============================================================*/
	// forec:thread:hello:start
	/*--------------------------------------------------------------
	| Thread hello
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	hello__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		while (1) {
			printf("Hello");

			// pause;
			// forec:statement:pause:pause0:start
			hello__thread.programCounter = &&pause0;
			goto *hello__thread.nextThread -> programCounter;
			pause0:;
			// forec:statement:pause:pause0:end


			// pause;
			// forec:statement:pause:pause1:start
			hello__thread.programCounter = &&pause1;
			goto *hello__thread.nextThread -> programCounter;
			pause1:;
			// forec:statement:pause:pause1:end

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:hello:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		hello__thread.nextThread -> prevThread = hello__thread.prevThread;
		hello__thread.prevThread -> nextThread = hello__thread.nextThread;
		goto *hello__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:hello:end
	} // hello__thread
	// forec:thread:hello:end

	// forec:thread:world:start
	/*--------------------------------------------------------------
	| Thread world
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_state__global_0_0 state__global_0_0_copy_world_local;

	// Thread body -------------------------------------------------
	world__thread: {
		// Initialise the local copies of shared variables.
		state__global_0_0_copy_world_local.value = state__global_0_0.value;
		state__global_0_0_copy_world_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		// pause;
		// Write the local copy of shared variables back to their global copy.

		state__global_0_0_copy_world = state__global_0_0_copy_world_local;		// forec:statement:pause:pause2:start
		world__thread.programCounter = &&pause2;
		goto *world__thread.nextThread -> programCounter;
		pause2:;
		// forec:statement:pause:pause2:end
		// Update the values of the used shared variables from their global copy.
		state__global_0_0_copy_world_local.status = FOREC_SHARED_UNMODIFIED;


		state__global_0_0_copy_world_local.value = 1;
		state__global_0_0_copy_world_local.status = FOREC_SHARED_MODIFIED;
		printf(" world!\r\n");

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		state__global_0_0_copy_world = state__global_0_0_copy_world_local;

		// forec:scheduler:threadRemove:world:start

		// Delete thread from the linked list and core.
		mainParCore1.activeThreads--;
		world__thread.nextThread -> prevThread = world__thread.prevThread;
		world__thread.prevThread -> nextThread = world__thread.nextThread;
		goto *world__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:world:end
	} // world__thread
	// forec:thread:world:end


} // End of the main() function.

