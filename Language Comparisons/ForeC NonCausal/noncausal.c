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

// Shared control variables for par(...)s ----------------------
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

typedef struct {
	/* shared */ int value;
	int status;
} Shared_X__global_0_0;
Shared_X__global_0_0 X__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED} /* combine with max */;
typedef struct {
	/* shared */ int value;
	int status;
} Shared_Y__global_0_0;
Shared_Y__global_0_0 Y__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED} /* combine with max */;

int max(int *lhs__max_0_0, int *rhs__max_0_0) {
	return 0;
}

void t0(void);
void t1(void);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// main
// t0
Shared_X__global_0_0 X__global_0_0_copy_t0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_Y__global_0_0 Y__global_0_0_copy_t0 = {.status = FOREC_SHARED_UNMODIFIED};
// t1
Shared_X__global_0_0 X__global_0_0_copy_t1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_Y__global_0_0 Y__global_0_0_copy_t1 = {.status = FOREC_SHARED_UNMODIFIED};

// forec:scheduler:boot:start
int main(int argc__main_0_0, char ** argv__main_0_0) {

/*==============================================================
| Multicore startup:
| Platform dependent code.  Core identifies itself and
| executes its corresponding start up code.
*=============================================================*/
	programStatus = RUNNING;

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
	Thread t0__thread;
	Thread t1__thread;
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
	// forec:scheduler:counter:start
	// Initialise and start timing each reaction.
	clockTimeUs.previous = getClockTimeUs();
	// forec:scheduler:counter:end
	
	//--------------------------------------------------------------

	X__global_0_0.value = 0;
	Y__global_0_0.value = 0;
	if (X__global_0_0.value == 1) {
		
	} else {
		// ifElse0
		X__global_0_0.value = 1;
	}
	printf("X = %d Y = %d\n", X__global_0_0.value, Y__global_0_0.value);

	// pause;
	// forec:statement:pause:pause0:start
	asm volatile ("nop");
	// forec:statement:pause:pause0:end


	X__global_0_0.value = 0;
	Y__global_0_0.value = 0;

	// par0(t0, t1);
	// forec:statement:par:par0:start
	// Set the par(...) information.
	mainParParent.parId = 0;
	pthread_mutex_lock(&mainParParent.parStatusLock);
	mainParParent.parStatus = FOREC_PAR_ON;
	pthread_cond_broadcast(&mainParParent.parStatusCond);
	pthread_mutex_unlock(&mainParParent.parStatusLock);

	// Link the threads and handlers together.
	mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
	t0__thread.programCounter = &&t0__thread;
	mainReactionStartMaster0.nextThread = &t0__thread;
	t0__thread.prevThread = &mainReactionStartMaster0;
	t1__thread.programCounter = &&t1__thread;
	t0__thread.nextThread = &t1__thread;
	t1__thread.prevThread = &t0__thread;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	t1__thread.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &t1__thread;

	// Link the last and first threads/handlers together.
	mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
	mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

	// Set the join address.
	mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

	// Set the core information.
	mainParCore0.activeThreads = 2;
	mainParCore0.reactionCounter = mainParReactionCounter;

	// Go to the first thread.
	goto t0__thread;
	par0JoinAddress_mainParCore0:;
	// forec:statement:par:par0:end

	printf("X = %d Y = %d\n", X__global_0_0.value, Y__global_0_0.value);

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

	// Combine shared variables.
	int parId = mainParParent.parId;
	if (parId == 0) {

		// X__global_0_0
		if (X__global_0_0_copy_t1.status == FOREC_SHARED_MODIFIED) {
			X__global_0_0_copy_t1.status = FOREC_SHARED_UNMODIFIED;
			X__global_0_0.value = X__global_0_0_copy_t1.value;
		}

		// Y__global_0_0
		if (Y__global_0_0_copy_t0.status == FOREC_SHARED_MODIFIED) {
			Y__global_0_0_copy_t0.status = FOREC_SHARED_UNMODIFIED;
			Y__global_0_0.value = Y__global_0_0_copy_t0.value;
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




/*==============================================================
| ForeC threads:
| Threads' code translated into C code.
*=============================================================*/
	// forec:thread:t0:start
	/*--------------------------------------------------------------
	| Thread t0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_X__global_0_0 X__global_0_0_copy_t0_local;
	Shared_Y__global_0_0 Y__global_0_0_copy_t0_local;

	// Thread body -------------------------------------------------
	t0__thread: {
		// Initialise the local copies of shared variables.
		X__global_0_0_copy_t0_local.value = X__global_0_0.value;
		X__global_0_0_copy_t0_local.status = FOREC_SHARED_UNMODIFIED;
		Y__global_0_0_copy_t0_local.value = Y__global_0_0.value;
		Y__global_0_0_copy_t0_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		if (X__global_0_0_copy_t0_local.value == 1) {
			
		} else {
			// ifElse1
			Y__global_0_0_copy_t0_local.value = 1;
			Y__global_0_0_copy_t0_local.status = FOREC_SHARED_MODIFIED;
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		Y__global_0_0_copy_t0 = Y__global_0_0_copy_t0_local;

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
	Shared_X__global_0_0 X__global_0_0_copy_t1_local;
	Shared_Y__global_0_0 Y__global_0_0_copy_t1_local;

	// Thread body -------------------------------------------------
	t1__thread: {
		// Initialise the local copies of shared variables.
		X__global_0_0_copy_t1_local.value = X__global_0_0.value;
		X__global_0_0_copy_t1_local.status = FOREC_SHARED_UNMODIFIED;
		Y__global_0_0_copy_t1_local.value = Y__global_0_0.value;
		Y__global_0_0_copy_t1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		if (Y__global_0_0_copy_t1_local.value == 1) {
			X__global_0_0_copy_t1_local.value = 1;
			X__global_0_0_copy_t1_local.status = FOREC_SHARED_MODIFIED;
		} else {
			// if2
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		X__global_0_0_copy_t1 = X__global_0_0_copy_t1_local;

		// forec:scheduler:threadRemove:t1:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		t1__thread.nextThread -> prevThread = t1__thread.prevThread;
		t1__thread.prevThread -> nextThread = t1__thread.nextThread;
		goto *t1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:t1:end
	} // t1__thread
	// forec:thread:t1:end


} // End of the main() function.

