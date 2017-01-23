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
#include <sys/time.h> 

// thread t0__thread(void);
// thread t1__thread(void);
// thread t2__thread(void);
// thread t3__thread(void);
// thread t4__thread(void);
// thread t5__thread(void);

typedef int integer__global_0_0;
typedef long double real__global_0_0;
integer__global_0_0 INITIAL__global_0_0 = 0;
integer__global_0_0 LIMIT__global_0_0 = 599999999;
integer__global_0_0 THREADS__global_0_0 = 6;
integer__global_0_0 ITERATIONS__global_0_0 = 10000000;

typedef struct {
	/* shared */ integer__global_0_0 value;
	unsigned short int status;
} Shared_RANGE__global_0_0;
Shared_RANGE__global_0_0 RANGE__global_0_0;
typedef struct {
	/* shared */ integer__global_0_0 value;
	unsigned short int status;
} Shared_SUBRANGE__global_0_0;
Shared_SUBRANGE__global_0_0 SUBRANGE__global_0_0;

typedef struct {
	real__global_0_0 total;
	real__global_0_0 current;
} AccumReal__global_0_0;

const AccumReal__global_0_0 plus(AccumReal__global_0_0 *copy1__plus_0_0, const AccumReal__global_0_0 *copy2__plus_0_0) {
	copy1__plus_0_0->total = copy1__plus_0_0->total + copy1__plus_0_0->current + copy2__plus_0_0->current;
	copy1__plus_0_0->current = 0;
	return * copy1__plus_0_0;
}

typedef struct {
	/* shared */ AccumReal__global_0_0 value;
	unsigned short int status;
} Shared_result__global_0_0;
Shared_result__global_0_0 result__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED} /* combine with plus */;
typedef struct {
	/* shared */ integer__global_0_0 value;
	unsigned short int status;
} Shared_segment__global_0_0;
Shared_segment__global_0_0 segment__global_0_0;

real__global_0_0 calculatePi(const integer__global_0_0 subSegment, integer__global_0_0 RANGE, integer__global_0_0 SUBRANGE, integer__global_0_0 segment);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// main
Shared_RANGE__global_0_0 RANGE__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_SUBRANGE__global_0_0 SUBRANGE__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_result__global_0_0 result__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_segment__global_0_0 segment__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
// t0
Shared_RANGE__global_0_0 RANGE__global_0_0_copy_t0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_SUBRANGE__global_0_0 SUBRANGE__global_0_0_copy_t0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_result__global_0_0 result__global_0_0_copy_t0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_segment__global_0_0 segment__global_0_0_copy_t0 = {.status = FOREC_SHARED_UNMODIFIED};
// t1
Shared_RANGE__global_0_0 RANGE__global_0_0_copy_t1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_SUBRANGE__global_0_0 SUBRANGE__global_0_0_copy_t1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_result__global_0_0 result__global_0_0_copy_t1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_segment__global_0_0 segment__global_0_0_copy_t1 = {.status = FOREC_SHARED_UNMODIFIED};
// t2
Shared_RANGE__global_0_0 RANGE__global_0_0_copy_t2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_SUBRANGE__global_0_0 SUBRANGE__global_0_0_copy_t2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_result__global_0_0 result__global_0_0_copy_t2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_segment__global_0_0 segment__global_0_0_copy_t2 = {.status = FOREC_SHARED_UNMODIFIED};
// t3
Shared_RANGE__global_0_0 RANGE__global_0_0_copy_t3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_SUBRANGE__global_0_0 SUBRANGE__global_0_0_copy_t3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_result__global_0_0 result__global_0_0_copy_t3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_segment__global_0_0 segment__global_0_0_copy_t3 = {.status = FOREC_SHARED_UNMODIFIED};
// t4
Shared_RANGE__global_0_0 RANGE__global_0_0_copy_t4 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_SUBRANGE__global_0_0 SUBRANGE__global_0_0_copy_t4 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_result__global_0_0 result__global_0_0_copy_t4 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_segment__global_0_0 segment__global_0_0_copy_t4 = {.status = FOREC_SHARED_UNMODIFIED};
// t5
Shared_RANGE__global_0_0 RANGE__global_0_0_copy_t5 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_SUBRANGE__global_0_0 SUBRANGE__global_0_0_copy_t5 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_result__global_0_0 result__global_0_0_copy_t5 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_segment__global_0_0 segment__global_0_0_copy_t5 = {.status = FOREC_SHARED_UNMODIFIED};

// forec:scheduler:boot:start
int main(integer__global_0_0 argc__main_0_0, char ** argv__main_0_0) {

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
	Thread t0__thread;
	Thread t1__thread;
	Thread t2__thread;
	Thread t3__thread;
	Thread t4__thread;
	Thread t5__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionStartSlave1;
	Thread mainReactionEndMaster0;
	Thread mainReactionEndSlave1;


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
	struct timeval startTime__main_0_0, endTime__main_0_0;
	int i__main_0_0;
	long seconds__main_0_0;
	integer__global_0_0 microseconds__main_0_0;
	Shared_RANGE__global_0_0 RANGE__global_0_0_copy_main_local;
	Shared_SUBRANGE__global_0_0 SUBRANGE__global_0_0_copy_main_local;
	Shared_result__global_0_0 result__global_0_0_copy_main_local;
	Shared_segment__global_0_0 segment__global_0_0_copy_main_local;

mainParCore0: {
	// Initialise the local copies of shared variables.
	RANGE__global_0_0_copy_main_local = RANGE__global_0_0;
	SUBRANGE__global_0_0_copy_main_local = SUBRANGE__global_0_0;
	segment__global_0_0_copy_main_local = segment__global_0_0;
	result__global_0_0_copy_main_local = result__global_0_0;
	//--------------------------------------------------------------

	gettimeofday(&startTime__main_0_0, 0);
	RANGE__global_0_0_copy_main_local.value = ((LIMIT__global_0_0 - INITIAL__global_0_0)/ITERATIONS__global_0_0 + 1);
	RANGE__global_0_0_copy_main_local.status = FOREC_SHARED_MODIFIED;
	SUBRANGE__global_0_0_copy_main_local.value = RANGE__global_0_0_copy_main_local.value/THREADS__global_0_0;
	SUBRANGE__global_0_0_copy_main_local.status = FOREC_SHARED_MODIFIED;

	for (i__main_0_0 = 0; i__main_0_0 < ITERATIONS__global_0_0; ++i__main_0_0) {
		segment__global_0_0_copy_main_local.value = i__main_0_0;
		segment__global_0_0_copy_main_local.status = FOREC_SHARED_MODIFIED;

		// par0(t0__thread, t1__thread, t2__thread, t3__thread, t4__thread, t5__thread);
		RANGE__global_0_0_copy_main = RANGE__global_0_0_copy_main_local;
		RANGE__global_0_0.value = RANGE__global_0_0_copy_main_local.value;
		SUBRANGE__global_0_0_copy_main = SUBRANGE__global_0_0_copy_main_local;
		SUBRANGE__global_0_0.value = SUBRANGE__global_0_0_copy_main_local.value;
		segment__global_0_0_copy_main = segment__global_0_0_copy_main_local;
		segment__global_0_0.value = segment__global_0_0_copy_main_local.value;
		// Set the par(...) information.
		mainParParent.parId = 0;
		mainParParent.parStatus = FOREC_PAR_ON;

		// Link the threads and handlers together.
		mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
		t0__thread.programCounter = &&t0__thread;
		mainReactionStartMaster0.nextThread = &t0__thread;
		t0__thread.prevThread = &mainReactionStartMaster0;
		t1__thread.programCounter = &&t1__thread;
		t0__thread.nextThread = &t1__thread;
		t1__thread.prevThread = &t0__thread;
		t2__thread.programCounter = &&t2__thread;
		t1__thread.nextThread = &t2__thread;
		t2__thread.prevThread = &t1__thread;
		mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
		t2__thread.nextThread = &mainReactionEndMaster0;
		mainReactionEndMaster0.prevThread = &t2__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
		mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

		// Set the join address.
		mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

		// Set the core information.
		mainParCore0.activeThreads = 3;
		mainParCore0.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		// forec:statement:par:par0:start
		goto t0__thread;
		par0JoinAddress_mainParCore0:;
		// forec:statement:par:par0:end
		RANGE__global_0_0_copy_main_local = RANGE__global_0_0;
		SUBRANGE__global_0_0_copy_main_local = SUBRANGE__global_0_0;
		segment__global_0_0_copy_main_local = segment__global_0_0;
		result__global_0_0_copy_main_local = result__global_0_0;

		// forec:scheduler:iterationEnd:for1_0:start
		// Synchronise end of iteration
		mainParParent.parId = -2;
		mainParParent.parStatus = FOREC_PAR_ON;
		mainParParent.programCounter = &&for1_0_endAddress;
		goto mainParHandlerMaster0;
		for1_0_endAddress:;
		// forec:scheduler:iterationEnd:for1_0:end
	}

	gettimeofday(&endTime__main_0_0, 0);
	seconds__main_0_0 = endTime__main_0_0.tv_sec - startTime__main_0_0.tv_sec;
	microseconds__main_0_0 = endTime__main_0_0.tv_usec - startTime__main_0_0.tv_usec;
	if (microseconds__main_0_0 < 0) {
		microseconds__main_0_0 += 1000000;
		seconds__main_0_0--;
	} else {
		// if0
	}
	printf("Pi1: %d.%ld\r\n", (integer__global_0_0)result__global_0_0_copy_main_local.value.total, (long)((result__global_0_0_copy_main_local.value.total - (integer__global_0_0)result__global_0_0_copy_main_local.value.total)*1000000000));
	printf("Runtime: %ld.%.6d\r\n", seconds__main_0_0, microseconds__main_0_0);
	return 0;

	//--------------------------------------------------------------
	// Write the defined shared variables back to their global copy.
	RANGE__global_0_0 = RANGE__global_0_0_copy_main_local;
	SUBRANGE__global_0_0 = SUBRANGE__global_0_0_copy_main_local;
	segment__global_0_0 = segment__global_0_0_copy_main_local;


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

		// result__global_0_0
		numberOfModifiedCopies = 0;
		Shared_result__global_0_0 *modified_result__global_0_0[6];
		// Find the modified copies.
		if (result__global_0_0_copy_t0.status == FOREC_SHARED_MODIFIED) {
			result__global_0_0_copy_t0.status = FOREC_SHARED_UNMODIFIED;
			modified_result__global_0_0[numberOfModifiedCopies] = &result__global_0_0_copy_t0;
			++numberOfModifiedCopies;
		}
		if (result__global_0_0_copy_t1.status == FOREC_SHARED_MODIFIED) {
			result__global_0_0_copy_t1.status = FOREC_SHARED_UNMODIFIED;
			modified_result__global_0_0[numberOfModifiedCopies] = &result__global_0_0_copy_t1;
			++numberOfModifiedCopies;
		}
		if (result__global_0_0_copy_t2.status == FOREC_SHARED_MODIFIED) {
			result__global_0_0_copy_t2.status = FOREC_SHARED_UNMODIFIED;
			modified_result__global_0_0[numberOfModifiedCopies] = &result__global_0_0_copy_t2;
			++numberOfModifiedCopies;
		}
		if (result__global_0_0_copy_t3.status == FOREC_SHARED_MODIFIED) {
			result__global_0_0_copy_t3.status = FOREC_SHARED_UNMODIFIED;
			modified_result__global_0_0[numberOfModifiedCopies] = &result__global_0_0_copy_t3;
			++numberOfModifiedCopies;
		}
		if (result__global_0_0_copy_t4.status == FOREC_SHARED_MODIFIED) {
			result__global_0_0_copy_t4.status = FOREC_SHARED_UNMODIFIED;
			modified_result__global_0_0[numberOfModifiedCopies] = &result__global_0_0_copy_t4;
			++numberOfModifiedCopies;
		}
		if (result__global_0_0_copy_t5.status == FOREC_SHARED_MODIFIED) {
			result__global_0_0_copy_t5.status = FOREC_SHARED_UNMODIFIED;
			modified_result__global_0_0[numberOfModifiedCopies] = &result__global_0_0_copy_t5;
			++numberOfModifiedCopies;
		}
		// Assign the first modified copy.
		if (numberOfModifiedCopies > 0) {
			result__global_0_0.value = modified_result__global_0_0[0]->value;
		}
		// Combine with the remaining modified copies.
		for (index = 1; index < numberOfModifiedCopies; ++index) {
			result__global_0_0.value = plus(&result__global_0_0.value, &modified_result__global_0_0[index]->value);
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
		t3__thread.programCounter = &&t3__thread;
		mainReactionStartSlave1.nextThread = &t3__thread;
		t3__thread.prevThread = &mainReactionStartSlave1;
		t4__thread.programCounter = &&t4__thread;
		t3__thread.nextThread = &t4__thread;
		t4__thread.prevThread = &t3__thread;
		t5__thread.programCounter = &&t5__thread;
		t4__thread.nextThread = &t5__thread;
		t5__thread.prevThread = &t4__thread;
		mainReactionEndSlave1.programCounter = &&mainReactionEndSlave1;
		t5__thread.nextThread = &mainReactionEndSlave1;
		mainReactionEndSlave1.prevThread = &t5__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave1.nextThread = &mainReactionStartSlave1;
		mainReactionStartSlave1.prevThread = &mainReactionEndSlave1;

		// Set the core information.
		mainParCore1.activeThreads = 3;
		mainParCore1.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto t3__thread;
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



/*==============================================================
| ForeC threads:
| Threads' code translated into C code.
*=============================================================*/
	// forec:thread:t0:start
	/*--------------------------------------------------------------
	| Thread t0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_RANGE__global_0_0 RANGE__global_0_0_copy_t0_local;
	Shared_SUBRANGE__global_0_0 SUBRANGE__global_0_0_copy_t0_local;
	Shared_result__global_0_0 result__global_0_0_copy_t0_local;
	Shared_segment__global_0_0 segment__global_0_0_copy_t0_local;

	// Thread body -------------------------------------------------
	t0__thread: {
		// Initialise the local copies of shared variables.
		RANGE__global_0_0_copy_t0_local.value = RANGE__global_0_0_copy_main.value;
		RANGE__global_0_0_copy_t0_local.status = FOREC_SHARED_UNMODIFIED;
		SUBRANGE__global_0_0_copy_t0_local.value = SUBRANGE__global_0_0_copy_main.value;
		SUBRANGE__global_0_0_copy_t0_local.status = FOREC_SHARED_UNMODIFIED;
		segment__global_0_0_copy_t0_local.value = segment__global_0_0_copy_main.value;
		segment__global_0_0_copy_t0_local.status = FOREC_SHARED_UNMODIFIED;
		result__global_0_0_copy_t0_local.value = result__global_0_0.value;
		result__global_0_0_copy_t0_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		result__global_0_0_copy_t0_local.value.current = calculatePi(0, RANGE__global_0_0_copy_t0_local.value, SUBRANGE__global_0_0_copy_t0_local.value, segment__global_0_0_copy_t0_local.value);
		result__global_0_0_copy_t0_local.status = FOREC_SHARED_MODIFIED;

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		result__global_0_0_copy_t0 = result__global_0_0_copy_t0_local;

		// forec:scheduler:threadRemove:t0:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		t0__thread.nextThread -> prevThread = t0__thread.prevThread;
		t0__thread.prevThread -> nextThread = t0__thread.nextThread;
		goto *t0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:t0:end
	} // t0__thread
	// forec:thread:t0:end

	// forec:thread:t1:start
	/*--------------------------------------------------------------
	| Thread t1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_RANGE__global_0_0 RANGE__global_0_0_copy_t1_local;
	Shared_SUBRANGE__global_0_0 SUBRANGE__global_0_0_copy_t1_local;
	Shared_result__global_0_0 result__global_0_0_copy_t1_local;
	Shared_segment__global_0_0 segment__global_0_0_copy_t1_local;

	// Thread body -------------------------------------------------
	t1__thread: {
		// Initialise the local copies of shared variables.
		RANGE__global_0_0_copy_t1_local.value = RANGE__global_0_0_copy_main.value;
		RANGE__global_0_0_copy_t1_local.status = FOREC_SHARED_UNMODIFIED;
		SUBRANGE__global_0_0_copy_t1_local.value = SUBRANGE__global_0_0_copy_main.value;
		SUBRANGE__global_0_0_copy_t1_local.status = FOREC_SHARED_UNMODIFIED;
		segment__global_0_0_copy_t1_local.value = segment__global_0_0_copy_main.value;
		segment__global_0_0_copy_t1_local.status = FOREC_SHARED_UNMODIFIED;
		result__global_0_0_copy_t1_local.value = result__global_0_0.value;
		result__global_0_0_copy_t1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		result__global_0_0_copy_t1_local.value.current = calculatePi(1, RANGE__global_0_0_copy_t1_local.value, SUBRANGE__global_0_0_copy_t1_local.value, segment__global_0_0_copy_t1_local.value);
		result__global_0_0_copy_t1_local.status = FOREC_SHARED_MODIFIED;

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		result__global_0_0_copy_t1 = result__global_0_0_copy_t1_local;

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
	Shared_RANGE__global_0_0 RANGE__global_0_0_copy_t2_local;
	Shared_SUBRANGE__global_0_0 SUBRANGE__global_0_0_copy_t2_local;
	Shared_result__global_0_0 result__global_0_0_copy_t2_local;
	Shared_segment__global_0_0 segment__global_0_0_copy_t2_local;

	// Thread body -------------------------------------------------
	t2__thread: {
		// Initialise the local copies of shared variables.
		RANGE__global_0_0_copy_t2_local.value = RANGE__global_0_0_copy_main.value;
		RANGE__global_0_0_copy_t2_local.status = FOREC_SHARED_UNMODIFIED;
		SUBRANGE__global_0_0_copy_t2_local.value = SUBRANGE__global_0_0_copy_main.value;
		SUBRANGE__global_0_0_copy_t2_local.status = FOREC_SHARED_UNMODIFIED;
		segment__global_0_0_copy_t2_local.value = segment__global_0_0_copy_main.value;
		segment__global_0_0_copy_t2_local.status = FOREC_SHARED_UNMODIFIED;
		result__global_0_0_copy_t2_local.value = result__global_0_0.value;
		result__global_0_0_copy_t2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		result__global_0_0_copy_t2_local.value.current = calculatePi(2, RANGE__global_0_0_copy_t2_local.value, SUBRANGE__global_0_0_copy_t2_local.value, segment__global_0_0_copy_t2_local.value);
		result__global_0_0_copy_t2_local.status = FOREC_SHARED_MODIFIED;

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		result__global_0_0_copy_t2 = result__global_0_0_copy_t2_local;

		// forec:scheduler:threadRemove:t2:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		t2__thread.nextThread -> prevThread = t2__thread.prevThread;
		t2__thread.prevThread -> nextThread = t2__thread.nextThread;
		goto *t2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:t2:end
	} // t2__thread
	// forec:thread:t2:end

	// forec:thread:t3:start
	/*--------------------------------------------------------------
	| Thread t3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_RANGE__global_0_0 RANGE__global_0_0_copy_t3_local;
	Shared_SUBRANGE__global_0_0 SUBRANGE__global_0_0_copy_t3_local;
	Shared_result__global_0_0 result__global_0_0_copy_t3_local;
	Shared_segment__global_0_0 segment__global_0_0_copy_t3_local;

	// Thread body -------------------------------------------------
	t3__thread: {
		// Initialise the local copies of shared variables.
		RANGE__global_0_0_copy_t3_local.value = RANGE__global_0_0_copy_main.value;
		RANGE__global_0_0_copy_t3_local.status = FOREC_SHARED_UNMODIFIED;
		SUBRANGE__global_0_0_copy_t3_local.value = SUBRANGE__global_0_0_copy_main.value;
		SUBRANGE__global_0_0_copy_t3_local.status = FOREC_SHARED_UNMODIFIED;
		segment__global_0_0_copy_t3_local.value = segment__global_0_0_copy_main.value;
		segment__global_0_0_copy_t3_local.status = FOREC_SHARED_UNMODIFIED;
		result__global_0_0_copy_t3_local.value = result__global_0_0.value;
		result__global_0_0_copy_t3_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		result__global_0_0_copy_t3_local.value.current = calculatePi(3, RANGE__global_0_0_copy_t3_local.value, SUBRANGE__global_0_0_copy_t3_local.value, segment__global_0_0_copy_t3_local.value);
		result__global_0_0_copy_t3_local.status = FOREC_SHARED_MODIFIED;

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		result__global_0_0_copy_t3 = result__global_0_0_copy_t3_local;

		// forec:scheduler:threadRemove:t3:start

		// Delete thread from the linked list and core.
		mainParCore1.activeThreads--;
		t3__thread.nextThread -> prevThread = t3__thread.prevThread;
		t3__thread.prevThread -> nextThread = t3__thread.nextThread;
		goto *t3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:t3:end
	} // t3__thread
	// forec:thread:t3:end

	// forec:thread:t4:start
	/*--------------------------------------------------------------
	| Thread t4
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_RANGE__global_0_0 RANGE__global_0_0_copy_t4_local;
	Shared_SUBRANGE__global_0_0 SUBRANGE__global_0_0_copy_t4_local;
	Shared_result__global_0_0 result__global_0_0_copy_t4_local;
	Shared_segment__global_0_0 segment__global_0_0_copy_t4_local;

	// Thread body -------------------------------------------------
	t4__thread: {
		// Initialise the local copies of shared variables.
		RANGE__global_0_0_copy_t4_local.value = RANGE__global_0_0_copy_main.value;
		RANGE__global_0_0_copy_t4_local.status = FOREC_SHARED_UNMODIFIED;
		SUBRANGE__global_0_0_copy_t4_local.value = SUBRANGE__global_0_0_copy_main.value;
		SUBRANGE__global_0_0_copy_t4_local.status = FOREC_SHARED_UNMODIFIED;
		segment__global_0_0_copy_t4_local.value = segment__global_0_0_copy_main.value;
		segment__global_0_0_copy_t4_local.status = FOREC_SHARED_UNMODIFIED;
		result__global_0_0_copy_t4_local.value = result__global_0_0.value;
		result__global_0_0_copy_t4_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		result__global_0_0_copy_t4_local.value.current = calculatePi(4, RANGE__global_0_0_copy_t4_local.value, SUBRANGE__global_0_0_copy_t4_local.value, segment__global_0_0_copy_t4_local.value);
		result__global_0_0_copy_t4_local.status = FOREC_SHARED_MODIFIED;

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		result__global_0_0_copy_t4 = result__global_0_0_copy_t4_local;

		// forec:scheduler:threadRemove:t4:start

		// Delete thread from the linked list and core.
		mainParCore1.activeThreads--;
		t4__thread.nextThread -> prevThread = t4__thread.prevThread;
		t4__thread.prevThread -> nextThread = t4__thread.nextThread;
		goto *t4__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:t4:end
	} // t4__thread
	// forec:thread:t4:end

	// forec:thread:t5:start
	/*--------------------------------------------------------------
	| Thread t5
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_RANGE__global_0_0 RANGE__global_0_0_copy_t5_local;
	Shared_SUBRANGE__global_0_0 SUBRANGE__global_0_0_copy_t5_local;
	Shared_result__global_0_0 result__global_0_0_copy_t5_local;
	Shared_segment__global_0_0 segment__global_0_0_copy_t5_local;

	// Thread body -------------------------------------------------
	t5__thread: {
		// Initialise the local copies of shared variables.
		RANGE__global_0_0_copy_t5_local.value = RANGE__global_0_0_copy_main.value;
		RANGE__global_0_0_copy_t5_local.status = FOREC_SHARED_UNMODIFIED;
		SUBRANGE__global_0_0_copy_t5_local.value = SUBRANGE__global_0_0_copy_main.value;
		SUBRANGE__global_0_0_copy_t5_local.status = FOREC_SHARED_UNMODIFIED;
		segment__global_0_0_copy_t5_local.value = segment__global_0_0_copy_main.value;
		segment__global_0_0_copy_t5_local.status = FOREC_SHARED_UNMODIFIED;
		result__global_0_0_copy_t5_local.value = result__global_0_0.value;
		result__global_0_0_copy_t5_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		result__global_0_0_copy_t5_local.value.current = calculatePi(5, RANGE__global_0_0_copy_t5_local.value, SUBRANGE__global_0_0_copy_t5_local.value, segment__global_0_0_copy_t5_local.value);
		result__global_0_0_copy_t5_local.status = FOREC_SHARED_MODIFIED;

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		result__global_0_0_copy_t5 = result__global_0_0_copy_t5_local;

		// forec:scheduler:threadRemove:t5:start

		// Delete thread from the linked list and core.
		mainParCore1.activeThreads--;
		t5__thread.nextThread -> prevThread = t5__thread.prevThread;
		t5__thread.prevThread -> nextThread = t5__thread.nextThread;
		goto *t5__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:t5:end
	} // t5__thread
	// forec:thread:t5:end


} // End of the main() function.

real__global_0_0 calculatePi(const integer__global_0_0 subSegment__calculatePi_0_0, integer__global_0_0 RANGE__calculatePi_0_0, integer__global_0_0 SUBRANGE__calculatePi_0_0, integer__global_0_0 segment__calculatePi_0_0) {
	real__global_0_0 result__calculatePi_0_0 = 0;
	real__global_0_0 denominator__calculatePi_0_0 = 0;
	real__global_0_0 numerator__calculatePi_0_0 = -1;
	const integer__global_0_0 startIndex__calculatePi_0_0 = SUBRANGE__calculatePi_0_0*subSegment__calculatePi_0_0 + RANGE__calculatePi_0_0*segment__calculatePi_0_0;
	const integer__global_0_0 endIndex__calculatePi_0_0 = SUBRANGE__calculatePi_0_0*(subSegment__calculatePi_0_0 + 1) + RANGE__calculatePi_0_0*segment__calculatePi_0_0;
	integer__global_0_0 i__calculatePi_0_0;
	for (i__calculatePi_0_0 = startIndex__calculatePi_0_0; i__calculatePi_0_0 < endIndex__calculatePi_0_0; ++i__calculatePi_0_0) {
		numerator__calculatePi_0_0 = numerator__calculatePi_0_0*-1;
		denominator__calculatePi_0_0 = 2*i__calculatePi_0_0 + 1;
		result__calculatePi_0_0 += 4*(numerator__calculatePi_0_0/denominator__calculatePi_0_0);
	}
	return result__calculatePi_0_0;
}

