/*==============================================================
| Hardware architecture specific declarations:
| Cores, mutex and input/output information.
*=============================================================*/
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <unistd.h>

typedef struct {
	long long previous;
	long long current;
	long long elapsed;
} ClockTimeUs;
ClockTimeUs clockTimeUs;

// Returns the current time in microseconds
long long getClockTimeUs(void) {
	struct timespec ts;

	if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0) {
		return (long long) (ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
	} else {
		return 0;
	}
}

// Mapping Pthreads to processor cores
pthread_t cores[1];
pthread_attr_t masterCoreAttribute;
pthread_attr_t slaveCoreAttribute;

// ForeC mutexes
unsigned int forec_mutex_value_abro;

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
	FOREC_SHARED_WAS_MODIFIED,	// 7
	
	// Program termination
	RUNNING,					// 8
	TERMINATED					// 9
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
	volatile Status parStatus;
	pthread_cond_t parStatusCond;
	pthread_mutex_t parStatusLock;
	volatile int parId;
} Parent;

// Keep track of child threads executing on
// a processor core.
typedef struct {
	volatile int sync;
	volatile int activeThreads;
	volatile Status status;
	pthread_cond_t statusCond;
	pthread_mutex_t statusLock;
	volatile int reactionCounter;
	pthread_cond_t reactionCounterCond;
	pthread_mutex_t reactionCounterLock;
} Core;

// Structure to pass input arguments into forecMain.
typedef struct {
	int coreId;
	int argc;
	char **argv;
} Arguments;

// Shared control variable to signal program termination to the slave pthreads
volatile Status programStatus;

// Shared control variables for non-immediate aborts -----------
volatile int init__abortStrongNonImmediate0 = 0;
volatile int init__abortStrongNonImmediate1 = 0;

// Shared control variables for par(...)s ----------------------
// Thread abro with par(...)s
Parent abroParParent = { .parStatusCond = PTHREAD_COND_INITIALIZER, .parStatusLock = PTHREAD_MUTEX_INITIALIZER };
Core abroParCore0 = { .statusCond = PTHREAD_COND_INITIALIZER, .statusLock = PTHREAD_MUTEX_INITIALIZER, .reactionCounterCond = PTHREAD_COND_INITIALIZER, .reactionCounterLock = PTHREAD_MUTEX_INITIALIZER};
volatile int abroParReactionCounter;
pthread_cond_t abroParReactionCounterCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t abroParReactionCounterLock = PTHREAD_MUTEX_INITIALIZER;

// Thread main with par(...)s
Parent mainParParent = { .parStatusCond = PTHREAD_COND_INITIALIZER, .parStatusLock = PTHREAD_MUTEX_INITIALIZER };
Core mainParCore0 = { .statusCond = PTHREAD_COND_INITIALIZER, .statusLock = PTHREAD_MUTEX_INITIALIZER, .reactionCounterCond = PTHREAD_COND_INITIALIZER, .reactionCounterLock = PTHREAD_MUTEX_INITIALIZER};
volatile int mainParReactionCounter;
pthread_cond_t mainParReactionCounterCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mainParReactionCounterLock = PTHREAD_MUTEX_INITIALIZER;


/*==============================================================
| Original global declarations:
| Global declarations in the original program code.
*=============================================================*/
// Original main function
void *forecMain(void *args);

#include <stdio.h>

const int INPUT_SEQUENCE__global_0_0 = 7;
const int I__global_0_0[INPUT_SEQUENCE__global_0_0][3] = {{1, 1, 0}, {1, 1, 0}, {0, 0, 0}, {0, 0, 1}, {1, 1, 0}, {1, 1, 1}, {1, 1, 0}};

typedef struct {
	/* shared */ int value;
	int status;
} Shared_tick__global_0_0;
Shared_tick__global_0_0 tick__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};

/* input */ int A__global_0_0;
/* input */ int B__global_0_0;
/* input */ int R__global_0_0;
/* output */ int O__global_0_0 = 0;

// thread abro__thread(void);
// thread tA__thread(void);
// thread tB__thread(void);
// thread Inputs__thread(void);
// thread Results__thread(void);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// Inputs
Shared_tick__global_0_0 tick__global_0_0_copy_Inputs = {.status = FOREC_SHARED_UNMODIFIED};
// Results
Shared_tick__global_0_0 tick__global_0_0_copy_Results = {.status = FOREC_SHARED_UNMODIFIED};
// abro
// main
// tA
// tB

// forec:scheduler:boot:start
int main(int argc__main_0_0, char ** argv__main_0_0) {

/*==============================================================
| Multicore startup:
| Platform dependent code.  Core identifies itself and
| executes its corresponding start up code.
*=============================================================*/
	programStatus = RUNNING;

	// Initialise ForeC specific values ---------------------------
	// Thread abro with par(...)s
	abroParParent.parStatus = FOREC_PAR_OFF;
	abroParCore0.sync = 1;
	abroParCore0.status = FOREC_CORE_REACTING;
	abroParReactionCounter = 0;

	// Thread main with par(...)s
	mainParParent.parStatus = FOREC_PAR_OFF;
	mainParCore0.sync = 1;
	mainParCore0.status = FOREC_CORE_REACTING;
	mainParReactionCounter = 0;


	// Reset ForeC mutex values
	forec_mutex_value_abro = -1;

	// Start core execution
	pthread_attr_init(&masterCoreAttribute);
	pthread_attr_init(&slaveCoreAttribute);
	pthread_attr_setdetachstate(&masterCoreAttribute, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setdetachstate(&slaveCoreAttribute, PTHREAD_CREATE_JOINABLE);
		
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
	int argc__main_0_0 __attribute__((unused)) = arguments->argc;
	char **argv__main_0_0 __attribute__((unused)) = arguments->argv;

	// Variables for par()s ----------------------------------------
	// par0
	Thread Inputs__thread;
	Thread Results__thread;
	Thread abro__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionEndMaster0;
	Thread abroParHandlerMaster0;
	Thread abortStrongNonImmediate0Check0;

	// par1
	Thread tA__thread;
	Thread tB__thread;
	Thread abroReactionStartMaster0;
	Thread abroReactionEndMaster0;
	Thread abortStrongNonImmediate1Check0;


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
	// forec:scheduler:counter:start
	// Initialise and start timing each reaction.
	clockTimeUs.previous = getClockTimeUs();
	// forec:scheduler:counter:end
	
	//--------------------------------------------------------------

	printf("        A B R  O\n");

	/* abortStrongNonImmediate0 */ {
		init__abortStrongNonImmediate0 = 0;
		// forec:statement:abort:abortStrongNonImmediate0:start
		if (tick__global_0_0.value == INPUT_SEQUENCE__global_0_0 && init__abortStrongNonImmediate0 == 1) {
			goto abortEnd_abortStrongNonImmediate0;
		}
		init__abortStrongNonImmediate0 = 1;
		// forec:statement:abort:abortStrongNonImmediate0:end

		// par0(Inputs__thread, abro__thread, Results__thread);
		// forec:statement:par:par0:start
		// Set the par(...) information.
		mainParParent.parId = 0;
		pthread_mutex_lock(&mainParParent.parStatusLock);
		mainParParent.parStatus = FOREC_PAR_ON;
		pthread_cond_broadcast(&mainParParent.parStatusCond);
		pthread_mutex_unlock(&mainParParent.parStatusLock);

		// Link the threads and handlers together.
		mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
		abortStrongNonImmediate0Check0.programCounter = &&abortStrongNonImmediate0Check0;
		mainReactionStartMaster0.nextThread = &abortStrongNonImmediate0Check0;
		abortStrongNonImmediate0Check0.prevThread = &mainReactionStartMaster0;
		Inputs__thread.programCounter = &&Inputs__thread;
		abortStrongNonImmediate0Check0.nextThread = &Inputs__thread;
		Inputs__thread.prevThread = &abortStrongNonImmediate0Check0;
		abro__thread.programCounter = &&abro__thread;
		Inputs__thread.nextThread = &abro__thread;
		abro__thread.prevThread = &Inputs__thread;
		abroParHandlerMaster0.programCounter = &&abroParHandlerMaster0;
		abro__thread.nextThread = &abroParHandlerMaster0;
		abroParHandlerMaster0.prevThread = &abro__thread;
		Results__thread.programCounter = &&Results__thread;
		abroParHandlerMaster0.nextThread = &Results__thread;
		Results__thread.prevThread = &abroParHandlerMaster0;
		mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
		Results__thread.nextThread = &mainReactionEndMaster0;
		mainReactionEndMaster0.prevThread = &Results__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
		mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

		// Set the join address.
		mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

		// Set the core information.
		mainParCore0.activeThreads = 4;
		mainParCore0.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto Inputs__thread;
		par0JoinAddress_mainParCore0:;
		// forec:statement:par:par0:end
		abortEnd_abortStrongNonImmediate0:;
	} // when (tick__global_0_0.value == INPUT_SEQUENCE__global_0_0 && init__abortStrongNonImmediate0 == 1);
	// forec:statement:abort:abortStrongNonImmediate0:scope:end

	//--------------------------------------------------------------

	// forec:scheduler:threadRemove:main:start

	// forec:scheduler:counter:start
	clockTimeUs.current = getClockTimeUs();
	clockTimeUs.elapsed = clockTimeUs.current - clockTimeUs.previous;
	if (clockTimeUs.elapsed < 0) {
		usleep(0 - clockTimeUs.elapsed);
	}
	clockTimeUs.previous = getClockTimeUs();
	// forec:scheduler:counter:end
	
	programStatus = TERMINATED;
	pthread_exit(NULL);
	// forec:scheduler:threadRemove:main:end
} // mainParCore0
	// forec:thread:main:end

// forec:scheduler:parHandler:main:master:0:start
mainParHandlerMaster0: {
	if (mainParParent.parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.

		pthread_mutex_lock(&mainParParent.parStatusLock);
		mainParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&mainParParent.parStatusCond);
		pthread_mutex_unlock(&mainParParent.parStatusLock);
		mainParParent.parId = -1;

		// Set slave cores' status to reacting.

		// Increment the reaction counter for synchronisation.
		pthread_mutex_lock(&mainParReactionCounterLock);
		mainParReactionCounter++;
		pthread_cond_broadcast(&mainParReactionCounterCond);
		pthread_mutex_unlock(&mainParReactionCounterLock);

		// Return to thread main.
		goto *mainParParent.programCounter;
	}

	// Control should not reach here.
	goto mainParHandlerMaster0;
}
// forec:scheduler:parHandler:main:master:0:end


	// Nested par(...) handlers ------------------------------------
	// forec:scheduler:parHandler:abro:master:0:start
	//-- Thread abro par(...) handlers
abroParHandlerMaster0: {
	// Check the execution status of the nested par(...)s.
	if (abroParParent.parStatus == FOREC_PAR_OFF) {
		// Release the mutex.
		forec_mutex_value_abro &= 0x7fffffff;

		goto *abroParHandlerMaster0.nextThread -> programCounter;
	}
	// Release the mutex.
	forec_mutex_value_abro &= 0x7fffffff;

	int parId = abroParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		abroReactionStartMaster0.programCounter = &&abroReactionStartMaster0;
		abortStrongNonImmediate1Check0.programCounter = &&abortStrongNonImmediate1Check0;
		abroReactionStartMaster0.nextThread = &abortStrongNonImmediate1Check0;
		abortStrongNonImmediate1Check0.prevThread = &abroReactionStartMaster0;
		tA__thread.programCounter = &&tA__thread;
		abortStrongNonImmediate1Check0.nextThread = &tA__thread;
		tA__thread.prevThread = &abortStrongNonImmediate1Check0;
		tB__thread.programCounter = &&tB__thread;
		tA__thread.nextThread = &tB__thread;
		tB__thread.prevThread = &tA__thread;
		abroReactionEndMaster0.programCounter = &&abroReactionEndMaster0;
		tB__thread.nextThread = &abroReactionEndMaster0;
		abroReactionEndMaster0.prevThread = &tB__thread;

		// Swap the nested par handler with the linked list.
		abroParHandlerMaster0.prevThread -> nextThread = &abroReactionStartMaster0;
		abroReactionStartMaster0.prevThread = abroParHandlerMaster0.prevThread;
		abroReactionEndMaster0.nextThread = abroParHandlerMaster0.nextThread;
		abroParHandlerMaster0.nextThread -> prevThread = &abroReactionEndMaster0;
		
		// Set the core information.
		abroParCore0.activeThreads = 2;
		abroParCore0.reactionCounter = abroParReactionCounter;
		
		// Go to the first thread.
		goto tA__thread;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.

		pthread_mutex_lock(&abroParParent.parStatusLock);
		abroParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&abroParParent.parStatusCond);
		pthread_mutex_unlock(&abroParParent.parStatusLock);
		abroParParent.parId = -1;

		forec_mutex_value_abro = -1;

		// Set slave cores' status to reacting.

		// Increment the reaction counter for synchronisation.
		pthread_mutex_lock(&abroParReactionCounterLock);
		abroParReactionCounter++;
		pthread_cond_broadcast(&abroParReactionCounterCond);
		pthread_mutex_unlock(&abroParReactionCounterLock);

		// Return to thread abro.
		goto *abroParParent.programCounter;
	} else if (parId == -3) {
		// Thread termination
		mainParCore0.activeThreads--;
		abroParCore0.activeThreads--;

		// Wait for other cores to complete their reaction.

		pthread_mutex_lock(&abroParParent.parStatusLock);
		abroParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&abroParParent.parStatusCond);
		pthread_mutex_unlock(&abroParParent.parStatusLock);
		abroParParent.parId = -1;

		// Set slave cores' status to reacting.

		// Increment the reaction counter for synchronisation.
		pthread_mutex_lock(&abroParReactionCounterLock);
		abroParReactionCounter++;
		pthread_cond_broadcast(&abroParReactionCounterCond);
		pthread_mutex_unlock(&abroParReactionCounterLock);

		// Delete this par(...) handler.
		abroParHandlerMaster0.prevThread -> nextThread = abroParHandlerMaster0.nextThread;
		abroParHandlerMaster0.nextThread -> prevThread = abroParHandlerMaster0.prevThread;
			
		// Return to thread abro.
		goto *abroParParent.programCounter;
	} else {
		// Unscheduled par(...)
		abroParCore0.reactionCounter = abroParReactionCounter;

		abroParHandlerMaster0.programCounter = &&wrongParId_abroParHandlerMaster0;
		wrongParId_abroParHandlerMaster0:;

		pthread_mutex_lock(&abroParCore0.statusLock);
		abroParCore0.status = FOREC_CORE_TERMINATED;
		pthread_cond_signal(&abroParCore0.statusCond);
		pthread_mutex_unlock(&abroParCore0.statusLock);

		// Wait for the next tick.
		pthread_mutex_lock(&abroParReactionCounterLock);
		while (abroParCore0.reactionCounter == abroParReactionCounter) { pthread_cond_wait(&abroParReactionCounterCond, &abroParReactionCounterLock); }
		pthread_mutex_unlock(&abroParReactionCounterLock);
		abroParCore0.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (abroParParent.parStatus == FOREC_PAR_ON && abroParParent.parId == parId) {
			goto *abroParHandlerMaster0.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		abroParHandlerMaster0.programCounter = &&abroParHandlerMaster0;
		
		goto abroParHandlerMaster0;
	}
	
	// Control should not reach here.
	goto abroParHandlerMaster0;
}
	// forec:scheduler:parHandler:abro:master:0:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:abro:master:0:start
	//-- abro:
abroReactionStartMaster0: {
	// Go to the next thread.
	goto *abroReactionStartMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:abro:master:0:end
 
	// forec:scheduler:reactionStart:main:master:0:start
	//-- main:
mainReactionStartMaster0: {
	// Go to the next thread.
	goto *mainReactionStartMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:master:0:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:abro:master:0:start
	//-- abro:
abroReactionEndMaster0: {
	// Determine if the core can still react or not.
	pthread_mutex_lock(&abroParCore0.statusLock);
	if (abroParCore0.activeThreads) {
		abroParCore0.status = FOREC_CORE_REACTED;
	} else {
		abroParCore0.status = FOREC_CORE_TERMINATED;
	}
	pthread_cond_signal(&abroParCore0.statusCond);
	pthread_mutex_unlock(&abroParCore0.statusLock);
	
	// Wait for other cores to complete their reaction.


	// Return back to the parent thread if all the cores have terminated.
	if (1 && abroParCore0.status == FOREC_CORE_TERMINATED) {
		forec_mutex_value_abro = -1;

		pthread_mutex_lock(&abroParParent.parStatusLock);
		abroParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&abroParParent.parStatusCond);
		pthread_mutex_unlock(&abroParParent.parStatusLock);
		abroParParent.parId = -1;
		
		// Set slave cores' status to reacting

		// Increment the reaction counter for synchronization.
		pthread_mutex_lock(&abroParReactionCounterLock);
		abroParReactionCounter++;
		pthread_cond_broadcast(&abroParReactionCounterCond);
		pthread_mutex_unlock(&abroParReactionCounterLock);

		// Swap the reaction (start & end) handlers with (thread abro & nested par handler).
		abroReactionStartMaster0.prevThread -> nextThread = &abro__thread;
		abro__thread.prevThread = abroReactionStartMaster0.prevThread;
		abro__thread.nextThread = &abroParHandlerMaster0;
		abroParHandlerMaster0.prevThread = &abro__thread;
		abroParHandlerMaster0.nextThread = abroReactionEndMaster0.nextThread;
		abroReactionEndMaster0.nextThread -> prevThread = &abroParHandlerMaster0;

		goto *abroParParent.programCounter;
	}

	// Set slave cores' status to reacting

	// Increment the reaction counter for synchronization.
	pthread_mutex_lock(&abroParReactionCounterLock);
	abroParReactionCounter++;
	pthread_cond_broadcast(&abroParReactionCounterCond);
	pthread_mutex_unlock(&abroParReactionCounterLock);

	// Go to the next thread.
	goto *abroReactionEndMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:abro:master:0:end
 
	// forec:scheduler:reactionEnd:main:master:0:start
	//-- main:
mainReactionEndMaster0: {
	// Determine if the core can still react or not.
	pthread_mutex_lock(&mainParCore0.statusLock);
	if (mainParCore0.activeThreads) {
		mainParCore0.status = FOREC_CORE_REACTED;
	} else {
		mainParCore0.status = FOREC_CORE_TERMINATED;
	}
	pthread_cond_signal(&mainParCore0.statusCond);
	pthread_mutex_unlock(&mainParCore0.statusLock);
	
	// Wait for other cores to complete their reaction.

	// Reset the mutex.
	forec_mutex_value_abro = -1;

	// Combine shared variables.
	int parId = mainParParent.parId;
	if (parId == 0) {

		// tick__global_0_0
		if (tick__global_0_0_copy_Results.status == FOREC_SHARED_MODIFIED) {
			tick__global_0_0_copy_Results.status = FOREC_SHARED_UNMODIFIED;
			tick__global_0_0.value = tick__global_0_0_copy_Results.value;
		}
	} else {
		// Nothing.
	}

	// Return back to the parent thread if all the cores have terminated.
	if (1 && mainParCore0.status == FOREC_CORE_TERMINATED) {
		pthread_mutex_lock(&mainParParent.parStatusLock);
		mainParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&mainParParent.parStatusCond);
		pthread_mutex_unlock(&mainParParent.parStatusLock);
		mainParParent.parId = -1;
		
		// Set slave cores' status to reacting

		// Increment the reaction counter for synchronization.
		pthread_mutex_lock(&mainParReactionCounterLock);
		mainParReactionCounter++;
		pthread_cond_broadcast(&mainParReactionCounterCond);
		pthread_mutex_unlock(&mainParReactionCounterLock);

		goto *mainParParent.programCounter;
	}

	// Set slave cores' status to reacting

	// forec:scheduler:counter:start
	clockTimeUs.current = getClockTimeUs();
	clockTimeUs.elapsed = clockTimeUs.current - clockTimeUs.previous;
	if (clockTimeUs.elapsed < 0) {
		usleep(0 - clockTimeUs.elapsed);
	}
	clockTimeUs.previous = getClockTimeUs();
	// forec:scheduler:counter:end

	// Increment the reaction counter for synchronization.
	pthread_mutex_lock(&mainParReactionCounterLock);
	mainParReactionCounter++;
	pthread_cond_broadcast(&mainParReactionCounterCond);
	pthread_mutex_unlock(&mainParReactionCounterLock);

	// Go to the next thread.
	goto *mainReactionEndMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:main:master:0:end
 


	// Abort check handlers ----------------------------------------
	// forec:scheduler:abortHandler:abortStrongNonImmediate1:0:start
	// abortStrongNonImmediate1 (R__global_0_0 == 1 && init__abortStrongNonImmediate1 == 1)
abortStrongNonImmediate1Check0: {
	// Check the abort condition.
	if (R__global_0_0 == 1 && init__abortStrongNonImmediate1 == 1) {
		// Force the reaction end handler to terminate the par(...).
		abroParCore0.activeThreads = 0;

		// Update the parent thread to resume at the end of the abort scope.
		abroParParent.programCounter = &&abortEnd_abortStrongNonImmediate1;
		
		goto abroReactionEndMaster0;
	}
	
	// Continue to the next thread.
	goto *abortStrongNonImmediate1Check0.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrongNonImmediate1:0:end
	// forec:scheduler:abortHandler:abortStrongNonImmediate0:0:start
	// abortStrongNonImmediate0 (tick__global_0_0.value == INPUT_SEQUENCE__global_0_0 && init__abortStrongNonImmediate0 == 1)
abortStrongNonImmediate0Check0: {
	// Check the abort condition.
	if (tick__global_0_0.value == INPUT_SEQUENCE__global_0_0 && init__abortStrongNonImmediate0 == 1) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore0.activeThreads = 0;

		// Update the parent thread to resume at the end of the abort scope.
		mainParParent.programCounter = &&abortEnd_abortStrongNonImmediate0;
		
		goto mainReactionEndMaster0;
	}
	
	// Continue to the next thread.
	goto *abortStrongNonImmediate0Check0.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrongNonImmediate0:0:end




/*==============================================================
| ForeC threads:
| Threads' code translated into C code.
*=============================================================*/
	// forec:thread:Inputs:start
	/*--------------------------------------------------------------
	| Thread Inputs
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_tick__global_0_0 tick__global_0_0_copy_Inputs_local;

	// Thread body -------------------------------------------------
	Inputs__thread: {
		// Initialise the local copies of shared variables.
		tick__global_0_0_copy_Inputs_local.value = tick__global_0_0.value;
		tick__global_0_0_copy_Inputs_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		while (1) {
			A__global_0_0 = I__global_0_0[tick__global_0_0_copy_Inputs_local.value][0];
			B__global_0_0 = I__global_0_0[tick__global_0_0_copy_Inputs_local.value][1];
			R__global_0_0 = I__global_0_0[tick__global_0_0_copy_Inputs_local.value][2];

			// pause;
			// forec:statement:pause:pause3:start
			Inputs__thread.programCounter = &&pause3;
			goto *Inputs__thread.nextThread -> programCounter;
			pause3:;
			// forec:statement:pause:pause3:end
			// Update the values of the used shared variables from their global copy.
			tick__global_0_0_copy_Inputs_local = tick__global_0_0;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:Inputs:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		Inputs__thread.nextThread -> prevThread = Inputs__thread.prevThread;
		Inputs__thread.prevThread -> nextThread = Inputs__thread.nextThread;
		goto *Inputs__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:Inputs:end
	} // Inputs__thread
	// forec:thread:Inputs:end

	// forec:thread:Results:start
	/*--------------------------------------------------------------
	| Thread Results
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_tick__global_0_0 tick__global_0_0_copy_Results_local;

	// Thread body -------------------------------------------------
	Results__thread: {
		// Initialise the local copies of shared variables.
		tick__global_0_0_copy_Results_local.value = tick__global_0_0.value;
		tick__global_0_0_copy_Results_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		while (1) {
			printf("Tick %d: %d %d %d  %d\n", tick__global_0_0_copy_Results_local.value, A__global_0_0, B__global_0_0, R__global_0_0, O__global_0_0);
			tick__global_0_0_copy_Results_local.value += 1;
			tick__global_0_0_copy_Results_local.status = FOREC_SHARED_MODIFIED;

			// pause;
			// Write the local copy of shared variables back to their global copy.
			tick__global_0_0_copy_Results = tick__global_0_0_copy_Results_local;
			// forec:statement:pause:pause4:start
			Results__thread.programCounter = &&pause4;
			goto *Results__thread.nextThread -> programCounter;
			pause4:;
			// forec:statement:pause:pause4:end
			// Update the values of the used shared variables from their global copy.
			tick__global_0_0_copy_Results_local = tick__global_0_0;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		tick__global_0_0_copy_Results = tick__global_0_0_copy_Results_local;

		// forec:scheduler:threadRemove:Results:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		Results__thread.nextThread -> prevThread = Results__thread.prevThread;
		Results__thread.prevThread -> nextThread = Results__thread.nextThread;
		goto *Results__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:Results:end
	} // Results__thread
	// forec:thread:Results:end

	// forec:thread:abro:start
	/*--------------------------------------------------------------
	| Thread abro
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	abro__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		while (1) {
			O__global_0_0 = 0;

			/* abortStrongNonImmediate1 */ {
				init__abortStrongNonImmediate1 = 0;
				// forec:statement:abort:abortStrongNonImmediate1:start
				if (R__global_0_0 == 1 && init__abortStrongNonImmediate1 == 1) {
					goto abortEnd_abortStrongNonImmediate1;
				}
				init__abortStrongNonImmediate1 = 1;
				// forec:statement:abort:abortStrongNonImmediate1:end

				// par1(tA__thread, tB__thread);
				// Set the par(...) information.
				// forec:statement:par:par1:start
				abroParParent.parId = 1;
				pthread_mutex_lock(&abroParParent.parStatusLock);
				abroParParent.parStatus = FOREC_PAR_ON;
				pthread_cond_broadcast(&abroParParent.parStatusCond);
				pthread_mutex_unlock(&abroParParent.parStatusLock);
				abroParParent.programCounter = &&par1JoinAddress_abroParParent;

				// Remove this thread from the linked list.
				abro__thread.nextThread -> prevThread = abro__thread.prevThread;
				abro__thread.prevThread -> nextThread = abro__thread.nextThread;
				goto abroParHandlerMaster0;
				par1JoinAddress_abroParParent:;
				// forec:statement:par:par1:end

				O__global_0_0 = 1;

				while (1) {
					// pause;
					// forec:statement:pause:pause0:start
					abro__thread.programCounter = &&pause0;
					goto *abro__thread.nextThread -> programCounter;
					pause0:;
					// forec:statement:pause:pause0:end

					// Strong aborts:
					// forec:statement:abort:abortStrongNonImmediate1:start
					if (R__global_0_0 == 1 && init__abortStrongNonImmediate1 == 1) {
						goto abortEnd_abortStrongNonImmediate1;
					}
					// forec:statement:abort:abortStrongNonImmediate1:end

					O__global_0_0 = 0;
				}
				abortEnd_abortStrongNonImmediate1:;
			} // when (R__global_0_0 == 1 && init__abortStrongNonImmediate1 == 1);
			// forec:statement:abort:abortStrongNonImmediate1:scope:end

			// forec:scheduler:iterationEnd:while_1:start
			// Synchronise end of iteration
			abroParParent.parId = -2;
			pthread_mutex_lock(&abroParParent.parStatusLock);
			abroParParent.parStatus = FOREC_PAR_ON;
			pthread_cond_broadcast(&abroParParent.parStatusCond);
			pthread_mutex_unlock(&abroParParent.parStatusLock);
			abroParParent.programCounter = &&while_1_endAddress;
			goto abroParHandlerMaster0;
			while_1_endAddress:;
			// forec:scheduler:iterationEnd:while_1:end
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:abro:start
		// Delete par handler
		abroParParent.parId = -3;
		abroParParent.parStatus = FOREC_PAR_ON;
		abroParParent.programCounter = &&abro_endAddress;
		goto abroParHandlerMaster0;
		abro_endAddress:;

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		abro__thread.nextThread -> prevThread = abro__thread.prevThread;
		abro__thread.prevThread -> nextThread = abro__thread.nextThread;
		goto *abro__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:abro:end
	} // abro__thread
	// forec:thread:abro:end

	// forec:thread:tA:start
	/*--------------------------------------------------------------
	| Thread tA
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	tA__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		do {
			// pause;
			// forec:statement:pause:pause1:start
			tA__thread.programCounter = &&pause1;
			goto *tA__thread.nextThread -> programCounter;
			pause1:;
			// forec:statement:pause:pause1:end

		} while (A__global_0_0 != 1);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:tA:start

		// Delete thread from the linked list and core.
		abroParCore0.activeThreads--;
		tA__thread.nextThread -> prevThread = tA__thread.prevThread;
		tA__thread.prevThread -> nextThread = tA__thread.nextThread;
		goto *tA__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:tA:end
	} // tA__thread
	// forec:thread:tA:end

	// forec:thread:tB:start
	/*--------------------------------------------------------------
	| Thread tB
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	tB__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		do {
			// pause;
			// forec:statement:pause:pause2:start
			tB__thread.programCounter = &&pause2;
			goto *tB__thread.nextThread -> programCounter;
			pause2:;
			// forec:statement:pause:pause2:end

		} while (B__global_0_0 != 1);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:tB:start

		// Delete thread from the linked list and core.
		abroParCore0.activeThreads--;
		tB__thread.nextThread -> prevThread = tB__thread.prevThread;
		tB__thread.prevThread -> nextThread = tB__thread.nextThread;
		goto *tB__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:tB:end
	} // tB__thread
	// forec:thread:tB:end


} // End of the main() function.

