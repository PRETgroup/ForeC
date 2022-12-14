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
pthread_t cores[4];
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
Core mainParCore1 = { .statusCond = PTHREAD_COND_INITIALIZER, .statusLock = PTHREAD_MUTEX_INITIALIZER, .reactionCounterCond = PTHREAD_COND_INITIALIZER, .reactionCounterLock = PTHREAD_MUTEX_INITIALIZER};
Core mainParCore2 = { .statusCond = PTHREAD_COND_INITIALIZER, .statusLock = PTHREAD_MUTEX_INITIALIZER, .reactionCounterCond = PTHREAD_COND_INITIALIZER, .reactionCounterLock = PTHREAD_MUTEX_INITIALIZER};
Core mainParCore3 = { .statusCond = PTHREAD_COND_INITIALIZER, .statusLock = PTHREAD_MUTEX_INITIALIZER, .reactionCounterCond = PTHREAD_COND_INITIALIZER, .reactionCounterLock = PTHREAD_MUTEX_INITIALIZER};
volatile int mainParReactionCounter;
pthread_cond_t mainParReactionCounterCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mainParReactionCounterLock = PTHREAD_MUTEX_INITIALIZER;


/*==============================================================
| Original global declarations:
| Global declarations in the original program code.
*=============================================================*/
// Original main function
void *forecMain(void *args);

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

int RAND_MAX__global_0_0;

#define RAND_MAX__global_0_0 RAND_MAX

static const int MAXINT__global_0_0 = 10000;
static const int REPEAT__global_0_0 = 10;
int ** matrixA__global_0_0;
int ** matrixB__global_0_0;
int ** matrixC__global_0_0;

typedef struct {
	/* shared */ int *** value;
	int status;
} Shared_matrixA_ptr__global_0_0;
Shared_matrixA_ptr__global_0_0 matrixA_ptr__global_0_0 = {.value = &matrixA__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int *** value;
	int status;
} Shared_matrixB_ptr__global_0_0;
Shared_matrixB_ptr__global_0_0 matrixB_ptr__global_0_0 = {.value = &matrixB__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int *** value;
	int status;
} Shared_matrixC_ptr__global_0_0;
Shared_matrixC_ptr__global_0_0 matrixC_ptr__global_0_0 = {.value = &matrixC__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

void allocateMatrix(int *** matrix);
void fillMatrix(int *** matrix);
void multiplyMatrix(int *** matrixA, int *** matrixB, int *** matrixC, const int startIndex);

// thread initialiseMatrixA__thread(void);
// thread initialiseMatrixB__thread(void);
// thread initialiseMatrixC__thread(void);
// thread multiplyMatrix0__thread(void);
// thread multiplyMatrix1__thread(void);
// thread multiplyMatrix2__thread(void);
// thread multiplyMatrix3__thread(void);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// initialiseMatrixA
// initialiseMatrixB
// initialiseMatrixC
// main
// multiplyMatrix0
// multiplyMatrix1
// multiplyMatrix2
// multiplyMatrix3

// forec:scheduler:boot:start
int main(int argc__main_0_0, char ** args__main_0_0) {

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
	mainParCore1.sync = 1;
	mainParCore1.status = FOREC_CORE_REACTING;
	mainParCore2.sync = 1;
	mainParCore2.status = FOREC_CORE_REACTING;
	mainParCore3.sync = 1;
	mainParCore3.status = FOREC_CORE_REACTING;
	mainParReactionCounter = 0;


	// Reset ForeC mutex values

	// Start core execution
	pthread_attr_init(&masterCoreAttribute);
	pthread_attr_init(&slaveCoreAttribute);
	pthread_attr_setdetachstate(&masterCoreAttribute, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setdetachstate(&slaveCoreAttribute, PTHREAD_CREATE_JOINABLE);
		
	// Master core
	Arguments arguments0 = {.coreId = 0, .argc = argc__main_0_0, .argv = args__main_0_0};
	pthread_create(&cores[0], &masterCoreAttribute, forecMain, (void *)&arguments0);

	// Slave cores
	Arguments arguments1 = {.coreId = 1, .argc = argc__main_0_0, .argv = args__main_0_0};
	pthread_create(&cores[1], &slaveCoreAttribute, forecMain, (void *)&arguments1);
	Arguments arguments2 = {.coreId = 2, .argc = argc__main_0_0, .argv = args__main_0_0};
	pthread_create(&cores[2], &slaveCoreAttribute, forecMain, (void *)&arguments2);
	Arguments arguments3 = {.coreId = 3, .argc = argc__main_0_0, .argv = args__main_0_0};
	pthread_create(&cores[3], &slaveCoreAttribute, forecMain, (void *)&arguments3);

	// End core execution
	pthread_attr_destroy(&masterCoreAttribute);
	pthread_attr_destroy(&slaveCoreAttribute);
	
	// Program termination
	pthread_join(cores[0], NULL);
	pthread_cond_broadcast(&mainParParent.parStatusCond);
	pthread_join(cores[1], NULL);
	pthread_cond_broadcast(&mainParParent.parStatusCond);
	pthread_join(cores[2], NULL);
	pthread_cond_broadcast(&mainParParent.parStatusCond);
	pthread_join(cores[3], NULL);

}


/*==============================================================
| Original main(...) function:
*=============================================================*/
void *forecMain(void *args) {
	Arguments *arguments = (Arguments *)args;
	int coreId = arguments->coreId;
	int argc__main_0_0 __attribute__((unused)) = arguments->argc;
	char **args__main_0_0 __attribute__((unused)) = arguments->argv;

	// Variables for par()s ----------------------------------------
	// par0
	Thread initialiseMatrixA__thread;
	Thread initialiseMatrixB__thread;
	Thread initialiseMatrixC__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionStartSlave1;
	Thread mainReactionStartSlave2;
	Thread mainReactionStartSlave3;
	Thread mainReactionEndMaster0;
	Thread mainReactionEndSlave1;
	Thread mainReactionEndSlave2;
	Thread mainReactionEndSlave3;

	// par1
	Thread multiplyMatrix0__thread;
	Thread multiplyMatrix1__thread;
	Thread multiplyMatrix2__thread;
	Thread multiplyMatrix3__thread;
	// Thread mainReactionStartMaster0;
	// Thread mainReactionStartSlave1;
	// Thread mainReactionStartSlave2;
	// Thread mainReactionStartSlave3;
	// Thread mainReactionEndMaster0;
	// Thread mainReactionEndSlave1;
	// Thread mainReactionEndSlave2;
	// Thread mainReactionEndSlave3;


	// Let cores jump to their code segment ------------------------
	switch (coreId) {
		case (0):
			goto mainParCore0;

		case (1):
			goto mainParCore1;

		case (2):
			goto mainParCore2;

		case (3):
			goto mainParCore3;

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
	int microseconds__main_0_0;

mainParCore0: {
	// forec:scheduler:counter:start
	// Initialise and start timing each reaction.
	clockTimeUs.previous = getClockTimeUs();
	// forec:scheduler:counter:end
	
	//--------------------------------------------------------------

	gettimeofday(&startTime__main_0_0, 0);
	printf("Initialising matrices\n");

	// par0(initialiseMatrixA__thread, initialiseMatrixB__thread, initialiseMatrixC__thread);
	// forec:statement:par:par0:start
	// Set the par(...) information.
	mainParParent.parId = 0;
	pthread_mutex_lock(&mainParParent.parStatusLock);
	mainParParent.parStatus = FOREC_PAR_ON;
	pthread_cond_broadcast(&mainParParent.parStatusCond);
	pthread_mutex_unlock(&mainParParent.parStatusLock);

	// Link the threads and handlers together.
	mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
	initialiseMatrixA__thread.programCounter = &&initialiseMatrixA__thread;
	mainReactionStartMaster0.nextThread = &initialiseMatrixA__thread;
	initialiseMatrixA__thread.prevThread = &mainReactionStartMaster0;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	initialiseMatrixA__thread.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &initialiseMatrixA__thread;

	// Link the last and first threads/handlers together.
	mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
	mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

	// Set the join address.
	mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

	// Set the core information.
	mainParCore0.activeThreads = 1;
	mainParCore0.reactionCounter = mainParReactionCounter;

	// Go to the first thread.
	goto initialiseMatrixA__thread;
	par0JoinAddress_mainParCore0:;
	// forec:statement:par:par0:end

	for (i__main_0_0 = 0; i__main_0_0 < REPEAT__global_0_0; i__main_0_0++) {
		printf("Iteration %d\n", i__main_0_0);

		// par1(multiplyMatrix0__thread, multiplyMatrix1__thread, multiplyMatrix2__thread, multiplyMatrix3__thread);
		// forec:statement:par:par1:start
		// Set the par(...) information.
		mainParParent.parId = 1;
		pthread_mutex_lock(&mainParParent.parStatusLock);
		mainParParent.parStatus = FOREC_PAR_ON;
		pthread_cond_broadcast(&mainParParent.parStatusCond);
		pthread_mutex_unlock(&mainParParent.parStatusLock);

		// Link the threads and handlers together.
		mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
		multiplyMatrix0__thread.programCounter = &&multiplyMatrix0__thread;
		mainReactionStartMaster0.nextThread = &multiplyMatrix0__thread;
		multiplyMatrix0__thread.prevThread = &mainReactionStartMaster0;
		mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
		multiplyMatrix0__thread.nextThread = &mainReactionEndMaster0;
		mainReactionEndMaster0.prevThread = &multiplyMatrix0__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
		mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

		// Set the join address.
		mainParParent.programCounter = &&par1JoinAddress_mainParCore0;

		// Set the core information.
		mainParCore0.activeThreads = 1;
		mainParCore0.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto multiplyMatrix0__thread;
		par1JoinAddress_mainParCore0:;
		// forec:statement:par:par1:end

		// forec:scheduler:iterationEnd:for1_0:start
		// Synchronise end of iteration
		mainParParent.parId = -2;
		pthread_mutex_lock(&mainParParent.parStatusLock);
		mainParParent.parStatus = FOREC_PAR_ON;
		pthread_cond_broadcast(&mainParParent.parStatusCond);
		pthread_mutex_unlock(&mainParParent.parStatusLock);
		mainParParent.programCounter = &&for1_0_endAddress;
		goto mainParHandlerMaster0;
		for1_0_endAddress:;
		// forec:scheduler:iterationEnd:for1_0:end
		// forec:iteration:for1_0:bound:10:10
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
	printf("Runtime: %ld.%.6d\r\n", seconds__main_0_0, microseconds__main_0_0);

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
		pthread_mutex_lock(&mainParCore1.statusLock);
		while(mainParCore1.status == FOREC_CORE_REACTING) { pthread_cond_wait(&mainParCore1.statusCond, &mainParCore1.statusLock); }
		pthread_mutex_unlock(&mainParCore1.statusLock);
		pthread_mutex_lock(&mainParCore2.statusLock);
		while(mainParCore2.status == FOREC_CORE_REACTING) { pthread_cond_wait(&mainParCore2.statusCond, &mainParCore2.statusLock); }
		pthread_mutex_unlock(&mainParCore2.statusLock);
		pthread_mutex_lock(&mainParCore3.statusLock);
		while(mainParCore3.status == FOREC_CORE_REACTING) { pthread_cond_wait(&mainParCore3.statusCond, &mainParCore3.statusLock); }
		pthread_mutex_unlock(&mainParCore3.statusLock);

		pthread_mutex_lock(&mainParParent.parStatusLock);
		mainParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&mainParParent.parStatusCond);
		pthread_mutex_unlock(&mainParParent.parStatusLock);
		mainParParent.parId = -1;

		// Set slave cores' status to reacting.
		mainParCore1.status = FOREC_CORE_REACTING;
		mainParCore2.status = FOREC_CORE_REACTING;
		mainParCore3.status = FOREC_CORE_REACTING;

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
	pthread_mutex_lock(&mainParCore1.statusLock);
	while(mainParCore1.status == FOREC_CORE_REACTING) { pthread_cond_wait(&mainParCore1.statusCond, &mainParCore1.statusLock); }
	pthread_mutex_unlock(&mainParCore1.statusLock);
	pthread_mutex_lock(&mainParCore2.statusLock);
	while(mainParCore2.status == FOREC_CORE_REACTING) { pthread_cond_wait(&mainParCore2.statusCond, &mainParCore2.statusLock); }
	pthread_mutex_unlock(&mainParCore2.statusLock);
	pthread_mutex_lock(&mainParCore3.statusLock);
	while(mainParCore3.status == FOREC_CORE_REACTING) { pthread_cond_wait(&mainParCore3.statusCond, &mainParCore3.statusLock); }
	pthread_mutex_unlock(&mainParCore3.statusLock);

	// Reset the mutex.

	// Return back to the parent thread if all the cores have terminated.
	if (1 && mainParCore0.status == FOREC_CORE_TERMINATED && mainParCore1.status == FOREC_CORE_TERMINATED && mainParCore2.status == FOREC_CORE_TERMINATED && mainParCore3.status == FOREC_CORE_TERMINATED) {
		pthread_mutex_lock(&mainParParent.parStatusLock);
		mainParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&mainParParent.parStatusCond);
		pthread_mutex_unlock(&mainParParent.parStatusLock);
		mainParParent.parId = -1;
		
		// Set slave cores' status to reacting
		mainParCore1.status = FOREC_CORE_REACTING;
		mainParCore2.status = FOREC_CORE_REACTING;
		mainParCore3.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronization.
		pthread_mutex_lock(&mainParReactionCounterLock);
		mainParReactionCounter++;
		pthread_cond_broadcast(&mainParReactionCounterCond);
		pthread_mutex_unlock(&mainParReactionCounterLock);

		goto *mainParParent.programCounter;
	}

	// Set slave cores' status to reacting
	mainParCore1.status = FOREC_CORE_REACTING;
	mainParCore2.status = FOREC_CORE_REACTING;
	mainParCore3.status = FOREC_CORE_REACTING;

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


// forec:scheduler:parHandler:main:slave:1:start
/*--------------------------------------------------------------
| Slave core: core1
*-------------------------------------------------------------*/
mainParCore1: {
	// Check the execution status of the root par(...)s.
	pthread_mutex_lock(&mainParParent.parStatusLock);
	while (mainParParent.parStatus == FOREC_PAR_OFF) {
		if (programStatus == TERMINATED) {
			pthread_mutex_unlock(&mainParParent.parStatusLock);
			pthread_exit(NULL);
		}
		pthread_cond_wait(&mainParParent.parStatusCond, &mainParParent.parStatusLock);
	}
	pthread_mutex_unlock(&mainParParent.parStatusLock);

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave1.programCounter = &&mainReactionStartSlave1;
		initialiseMatrixB__thread.programCounter = &&initialiseMatrixB__thread;
		mainReactionStartSlave1.nextThread = &initialiseMatrixB__thread;
		initialiseMatrixB__thread.prevThread = &mainReactionStartSlave1;
		mainReactionEndSlave1.programCounter = &&mainReactionEndSlave1;
		initialiseMatrixB__thread.nextThread = &mainReactionEndSlave1;
		mainReactionEndSlave1.prevThread = &initialiseMatrixB__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave1.nextThread = &mainReactionStartSlave1;
		mainReactionStartSlave1.prevThread = &mainReactionEndSlave1;

		// Set the core information.
		mainParCore1.activeThreads = 1;
		mainParCore1.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto initialiseMatrixB__thread;
		asm("# par0 end");
	} else if (parId == 1) {
		asm("# par1 start");
		// Link the threads and handlers together.
		mainReactionStartSlave1.programCounter = &&mainReactionStartSlave1;
		multiplyMatrix1__thread.programCounter = &&multiplyMatrix1__thread;
		mainReactionStartSlave1.nextThread = &multiplyMatrix1__thread;
		multiplyMatrix1__thread.prevThread = &mainReactionStartSlave1;
		mainReactionEndSlave1.programCounter = &&mainReactionEndSlave1;
		multiplyMatrix1__thread.nextThread = &mainReactionEndSlave1;
		mainReactionEndSlave1.prevThread = &multiplyMatrix1__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave1.nextThread = &mainReactionStartSlave1;
		mainReactionStartSlave1.prevThread = &mainReactionEndSlave1;

		// Set the core information.
		mainParCore1.activeThreads = 1;
		mainParCore1.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto multiplyMatrix1__thread;
		asm("# par1 end");
	} else {
		// Unscheduled par(...)
		mainParCore1.reactionCounter = mainParReactionCounter;
		
		// Wait for the par(...) to terminate.
		do {
			pthread_mutex_lock(&mainParCore1.statusLock);
			mainParCore1.status = FOREC_CORE_TERMINATED;
			pthread_cond_signal(&mainParCore1.statusCond);
			pthread_mutex_unlock(&mainParCore1.statusLock);
			
			// Wait for the next tick.
			pthread_mutex_lock(&mainParReactionCounterLock);
			while (mainParCore1.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
			pthread_mutex_unlock(&mainParReactionCounterLock);
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
		pthread_mutex_lock(&mainParCore1.statusLock);
		mainParCore1.status = FOREC_CORE_REACTED;
		pthread_cond_signal(&mainParCore1.statusCond);
		pthread_mutex_unlock(&mainParCore1.statusLock);
		
		// Wait for the next tick.
		pthread_mutex_lock(&mainParReactionCounterLock);
		while (mainParCore1.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
		pthread_mutex_unlock(&mainParReactionCounterLock);
		mainParCore1.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave1.nextThread -> programCounter;
	} else {
		int parId = mainParParent.parId;

		mainReactionEndSlave1.programCounter = &&terminated_mainReactionEndSlave1;
		terminated_mainReactionEndSlave1:;
		
		pthread_mutex_lock(&mainParCore1.statusLock);
		mainParCore1.status = FOREC_CORE_TERMINATED;
		pthread_cond_signal(&mainParCore1.statusCond);
		pthread_mutex_unlock(&mainParCore1.statusLock);
		
		// Wait for the next tick.
		pthread_mutex_lock(&mainParReactionCounterLock);
		while (mainParCore1.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
		pthread_mutex_unlock(&mainParReactionCounterLock);
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
	pthread_mutex_lock(&mainParParent.parStatusLock);
	while (mainParParent.parStatus == FOREC_PAR_OFF) {
		if (programStatus == TERMINATED) {
			pthread_mutex_unlock(&mainParParent.parStatusLock);
			pthread_exit(NULL);
		}
		pthread_cond_wait(&mainParParent.parStatusCond, &mainParParent.parStatusLock);
	}
	pthread_mutex_unlock(&mainParParent.parStatusLock);

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave2.programCounter = &&mainReactionStartSlave2;
		initialiseMatrixC__thread.programCounter = &&initialiseMatrixC__thread;
		mainReactionStartSlave2.nextThread = &initialiseMatrixC__thread;
		initialiseMatrixC__thread.prevThread = &mainReactionStartSlave2;
		mainReactionEndSlave2.programCounter = &&mainReactionEndSlave2;
		initialiseMatrixC__thread.nextThread = &mainReactionEndSlave2;
		mainReactionEndSlave2.prevThread = &initialiseMatrixC__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave2.nextThread = &mainReactionStartSlave2;
		mainReactionStartSlave2.prevThread = &mainReactionEndSlave2;

		// Set the core information.
		mainParCore2.activeThreads = 1;
		mainParCore2.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto initialiseMatrixC__thread;
		asm("# par0 end");
	} else if (parId == 1) {
		asm("# par1 start");
		// Link the threads and handlers together.
		mainReactionStartSlave2.programCounter = &&mainReactionStartSlave2;
		multiplyMatrix2__thread.programCounter = &&multiplyMatrix2__thread;
		mainReactionStartSlave2.nextThread = &multiplyMatrix2__thread;
		multiplyMatrix2__thread.prevThread = &mainReactionStartSlave2;
		mainReactionEndSlave2.programCounter = &&mainReactionEndSlave2;
		multiplyMatrix2__thread.nextThread = &mainReactionEndSlave2;
		mainReactionEndSlave2.prevThread = &multiplyMatrix2__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave2.nextThread = &mainReactionStartSlave2;
		mainReactionStartSlave2.prevThread = &mainReactionEndSlave2;

		// Set the core information.
		mainParCore2.activeThreads = 1;
		mainParCore2.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto multiplyMatrix2__thread;
		asm("# par1 end");
	} else {
		// Unscheduled par(...)
		mainParCore2.reactionCounter = mainParReactionCounter;
		
		// Wait for the par(...) to terminate.
		do {
			pthread_mutex_lock(&mainParCore2.statusLock);
			mainParCore2.status = FOREC_CORE_TERMINATED;
			pthread_cond_signal(&mainParCore2.statusCond);
			pthread_mutex_unlock(&mainParCore2.statusLock);
			
			// Wait for the next tick.
			pthread_mutex_lock(&mainParReactionCounterLock);
			while (mainParCore2.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
			pthread_mutex_unlock(&mainParReactionCounterLock);
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
		pthread_mutex_lock(&mainParCore2.statusLock);
		mainParCore2.status = FOREC_CORE_REACTED;
		pthread_cond_signal(&mainParCore2.statusCond);
		pthread_mutex_unlock(&mainParCore2.statusLock);
		
		// Wait for the next tick.
		pthread_mutex_lock(&mainParReactionCounterLock);
		while (mainParCore2.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
		pthread_mutex_unlock(&mainParReactionCounterLock);
		mainParCore2.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave2.nextThread -> programCounter;
	} else {
		int parId = mainParParent.parId;

		mainReactionEndSlave2.programCounter = &&terminated_mainReactionEndSlave2;
		terminated_mainReactionEndSlave2:;
		
		pthread_mutex_lock(&mainParCore2.statusLock);
		mainParCore2.status = FOREC_CORE_TERMINATED;
		pthread_cond_signal(&mainParCore2.statusCond);
		pthread_mutex_unlock(&mainParCore2.statusLock);
		
		// Wait for the next tick.
		pthread_mutex_lock(&mainParReactionCounterLock);
		while (mainParCore2.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
		pthread_mutex_unlock(&mainParReactionCounterLock);
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
	pthread_mutex_lock(&mainParParent.parStatusLock);
	while (mainParParent.parStatus == FOREC_PAR_OFF) {
		if (programStatus == TERMINATED) {
			pthread_mutex_unlock(&mainParParent.parStatusLock);
			pthread_exit(NULL);
		}
		pthread_cond_wait(&mainParParent.parStatusCond, &mainParParent.parStatusLock);
	}
	pthread_mutex_unlock(&mainParParent.parStatusLock);

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm("# par1 start");
		// Link the threads and handlers together.
		mainReactionStartSlave3.programCounter = &&mainReactionStartSlave3;
		multiplyMatrix3__thread.programCounter = &&multiplyMatrix3__thread;
		mainReactionStartSlave3.nextThread = &multiplyMatrix3__thread;
		multiplyMatrix3__thread.prevThread = &mainReactionStartSlave3;
		mainReactionEndSlave3.programCounter = &&mainReactionEndSlave3;
		multiplyMatrix3__thread.nextThread = &mainReactionEndSlave3;
		mainReactionEndSlave3.prevThread = &multiplyMatrix3__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave3.nextThread = &mainReactionStartSlave3;
		mainReactionStartSlave3.prevThread = &mainReactionEndSlave3;

		// Set the core information.
		mainParCore3.activeThreads = 1;
		mainParCore3.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto multiplyMatrix3__thread;
		asm("# par1 end");
	} else {
		// Unscheduled par(...)
		mainParCore3.reactionCounter = mainParReactionCounter;
		
		// Wait for the par(...) to terminate.
		do {
			pthread_mutex_lock(&mainParCore3.statusLock);
			mainParCore3.status = FOREC_CORE_TERMINATED;
			pthread_cond_signal(&mainParCore3.statusCond);
			pthread_mutex_unlock(&mainParCore3.statusLock);
			
			// Wait for the next tick.
			pthread_mutex_lock(&mainParReactionCounterLock);
			while (mainParCore3.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
			pthread_mutex_unlock(&mainParReactionCounterLock);
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
		pthread_mutex_lock(&mainParCore3.statusLock);
		mainParCore3.status = FOREC_CORE_REACTED;
		pthread_cond_signal(&mainParCore3.statusCond);
		pthread_mutex_unlock(&mainParCore3.statusLock);
		
		// Wait for the next tick.
		pthread_mutex_lock(&mainParReactionCounterLock);
		while (mainParCore3.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
		pthread_mutex_unlock(&mainParReactionCounterLock);
		mainParCore3.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave3.nextThread -> programCounter;
	} else {
		int parId = mainParParent.parId;

		mainReactionEndSlave3.programCounter = &&terminated_mainReactionEndSlave3;
		terminated_mainReactionEndSlave3:;
		
		pthread_mutex_lock(&mainParCore3.statusLock);
		mainParCore3.status = FOREC_CORE_TERMINATED;
		pthread_cond_signal(&mainParCore3.statusCond);
		pthread_mutex_unlock(&mainParCore3.statusLock);
		
		// Wait for the next tick.
		pthread_mutex_lock(&mainParReactionCounterLock);
		while (mainParCore3.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
		pthread_mutex_unlock(&mainParReactionCounterLock);
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
| Threads' code translated into C code.
*=============================================================*/
	// forec:thread:initialiseMatrixA:start
	/*--------------------------------------------------------------
	| Thread initialiseMatrixA
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	initialiseMatrixA__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		allocateMatrix(matrixA_ptr__global_0_0.value);
		fillMatrix(matrixA_ptr__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:initialiseMatrixA:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		initialiseMatrixA__thread.nextThread -> prevThread = initialiseMatrixA__thread.prevThread;
		initialiseMatrixA__thread.prevThread -> nextThread = initialiseMatrixA__thread.nextThread;
		goto *initialiseMatrixA__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:initialiseMatrixA:end
	} // initialiseMatrixA__thread
	// forec:thread:initialiseMatrixA:end

	// forec:thread:initialiseMatrixB:start
	/*--------------------------------------------------------------
	| Thread initialiseMatrixB
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	initialiseMatrixB__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		allocateMatrix(matrixB_ptr__global_0_0.value);
		fillMatrix(matrixB_ptr__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:initialiseMatrixB:start

		// Delete thread from the linked list and core.
		mainParCore1.activeThreads--;
		initialiseMatrixB__thread.nextThread -> prevThread = initialiseMatrixB__thread.prevThread;
		initialiseMatrixB__thread.prevThread -> nextThread = initialiseMatrixB__thread.nextThread;
		goto *initialiseMatrixB__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:initialiseMatrixB:end
	} // initialiseMatrixB__thread
	// forec:thread:initialiseMatrixB:end

	// forec:thread:initialiseMatrixC:start
	/*--------------------------------------------------------------
	| Thread initialiseMatrixC
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	initialiseMatrixC__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		allocateMatrix(matrixC_ptr__global_0_0.value);
		fillMatrix(matrixC_ptr__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:initialiseMatrixC:start

		// Delete thread from the linked list and core.
		mainParCore2.activeThreads--;
		initialiseMatrixC__thread.nextThread -> prevThread = initialiseMatrixC__thread.prevThread;
		initialiseMatrixC__thread.prevThread -> nextThread = initialiseMatrixC__thread.nextThread;
		goto *initialiseMatrixC__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:initialiseMatrixC:end
	} // initialiseMatrixC__thread
	// forec:thread:initialiseMatrixC:end

	// forec:thread:multiplyMatrix0:start
	/*--------------------------------------------------------------
	| Thread multiplyMatrix0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	int RANGE__multiplyMatrix0_0_0;

	// Thread body -------------------------------------------------
	multiplyMatrix0__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		RANGE__multiplyMatrix0_0_0 = 150;
		multiplyMatrix(matrixA_ptr__global_0_0.value, matrixB_ptr__global_0_0.value, matrixC_ptr__global_0_0.value, 0*RANGE__multiplyMatrix0_0_0);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiplyMatrix0:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		multiplyMatrix0__thread.nextThread -> prevThread = multiplyMatrix0__thread.prevThread;
		multiplyMatrix0__thread.prevThread -> nextThread = multiplyMatrix0__thread.nextThread;
		goto *multiplyMatrix0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:multiplyMatrix0:end
	} // multiplyMatrix0__thread
	// forec:thread:multiplyMatrix0:end

	// forec:thread:multiplyMatrix1:start
	/*--------------------------------------------------------------
	| Thread multiplyMatrix1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	int RANGE__multiplyMatrix1_0_0;

	// Thread body -------------------------------------------------
	multiplyMatrix1__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		RANGE__multiplyMatrix1_0_0 = 150;
		multiplyMatrix(matrixA_ptr__global_0_0.value, matrixB_ptr__global_0_0.value, matrixC_ptr__global_0_0.value, 1*RANGE__multiplyMatrix1_0_0);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiplyMatrix1:start

		// Delete thread from the linked list and core.
		mainParCore1.activeThreads--;
		multiplyMatrix1__thread.nextThread -> prevThread = multiplyMatrix1__thread.prevThread;
		multiplyMatrix1__thread.prevThread -> nextThread = multiplyMatrix1__thread.nextThread;
		goto *multiplyMatrix1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:multiplyMatrix1:end
	} // multiplyMatrix1__thread
	// forec:thread:multiplyMatrix1:end

	// forec:thread:multiplyMatrix2:start
	/*--------------------------------------------------------------
	| Thread multiplyMatrix2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	int RANGE__multiplyMatrix2_0_0;

	// Thread body -------------------------------------------------
	multiplyMatrix2__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		RANGE__multiplyMatrix2_0_0 = 150;
		multiplyMatrix(matrixA_ptr__global_0_0.value, matrixB_ptr__global_0_0.value, matrixC_ptr__global_0_0.value, 2*RANGE__multiplyMatrix2_0_0);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiplyMatrix2:start

		// Delete thread from the linked list and core.
		mainParCore2.activeThreads--;
		multiplyMatrix2__thread.nextThread -> prevThread = multiplyMatrix2__thread.prevThread;
		multiplyMatrix2__thread.prevThread -> nextThread = multiplyMatrix2__thread.nextThread;
		goto *multiplyMatrix2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:multiplyMatrix2:end
	} // multiplyMatrix2__thread
	// forec:thread:multiplyMatrix2:end

	// forec:thread:multiplyMatrix3:start
	/*--------------------------------------------------------------
	| Thread multiplyMatrix3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	int RANGE__multiplyMatrix3_0_0;

	// Thread body -------------------------------------------------
	multiplyMatrix3__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		RANGE__multiplyMatrix3_0_0 = 150;
		multiplyMatrix(matrixA_ptr__global_0_0.value, matrixB_ptr__global_0_0.value, matrixC_ptr__global_0_0.value, 3*RANGE__multiplyMatrix3_0_0);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:multiplyMatrix3:start

		// Delete thread from the linked list and core.
		mainParCore3.activeThreads--;
		multiplyMatrix3__thread.nextThread -> prevThread = multiplyMatrix3__thread.prevThread;
		multiplyMatrix3__thread.prevThread -> nextThread = multiplyMatrix3__thread.nextThread;
		goto *multiplyMatrix3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:multiplyMatrix3:end
	} // multiplyMatrix3__thread
	// forec:thread:multiplyMatrix3:end


} // End of the main() function.

void allocateMatrix(int *** matrix__allocateMatrix_0_0) {
	int SIZE__allocateMatrix_0_0 = 150*4;
	(* matrix__allocateMatrix_0_0) = (int **)malloc(SIZE__allocateMatrix_0_0*sizeof(int *));
	int i__allocateMatrix_0_0;
	for (i__allocateMatrix_0_0 = 0; i__allocateMatrix_0_0 < SIZE__allocateMatrix_0_0; i__allocateMatrix_0_0++) {
		(* matrix__allocateMatrix_0_0)[i__allocateMatrix_0_0] = (int *)malloc(SIZE__allocateMatrix_0_0*sizeof(int));
		// forec:iteration:for1_1:bound:600:600
	}
}

void fillMatrix(int *** matrix__fillMatrix_0_0) {
	int SIZE__fillMatrix_0_0 = 150*4;
	unsigned int seed__fillMatrix_0_0 = 10000;
	int i__fillMatrix_0_0;
	int j__fillMatrix_0_0;
	for (i__fillMatrix_0_0 = 0; i__fillMatrix_0_0 < SIZE__fillMatrix_0_0; i__fillMatrix_0_0++) {
		for (j__fillMatrix_0_0 = 0; j__fillMatrix_0_0 < SIZE__fillMatrix_0_0; j__fillMatrix_0_0++) {
			(* matrix__fillMatrix_0_0)[i__fillMatrix_0_0][j__fillMatrix_0_0] = 1 + (int)(MAXINT__global_0_0*(rand_r(&seed__fillMatrix_0_0)/(RAND_MAX__global_0_0 + 1.0)));
			// forec:iteration:for1_2:bound:600:600
		}
		// forec:iteration:for1_3:bound:600:600
	}
}

void multiplyMatrix(int *** matrixA__multiplyMatrix_0_0, int *** matrixB__multiplyMatrix_0_0, int *** matrixC__multiplyMatrix_0_0, const int startIndex__multiplyMatrix_0_0) {
	int SIZE__multiplyMatrix_0_0 = 150*4;
	int RANGE__multiplyMatrix_0_0 = 150;
	int i__multiplyMatrix_0_0;
	int j__multiplyMatrix_0_0;
	int k__multiplyMatrix_0_0;
	for (i__multiplyMatrix_0_0 = startIndex__multiplyMatrix_0_0; i__multiplyMatrix_0_0 < startIndex__multiplyMatrix_0_0 + RANGE__multiplyMatrix_0_0; i__multiplyMatrix_0_0++) {
		for (j__multiplyMatrix_0_0 = 0; j__multiplyMatrix_0_0 < SIZE__multiplyMatrix_0_0; j__multiplyMatrix_0_0++) {
			int sum__multiplyMatrix_2_0 = 0;
			for (k__multiplyMatrix_0_0 = 0; k__multiplyMatrix_0_0 < SIZE__multiplyMatrix_0_0; k__multiplyMatrix_0_0++) {
				sum__multiplyMatrix_2_0 += (* matrixA__multiplyMatrix_0_0)[i__multiplyMatrix_0_0][k__multiplyMatrix_0_0]*(* matrixB__multiplyMatrix_0_0)[k__multiplyMatrix_0_0][j__multiplyMatrix_0_0];
				// forec:iteration:for1_4:bound:600:600
			}
			(* matrixC__multiplyMatrix_0_0)[i__multiplyMatrix_0_0][j__multiplyMatrix_0_0] = sum__multiplyMatrix_2_0;
			// forec:iteration:for1_5:bound:600:600
		}
		// forec:iteration:for1_6:bound:150:150
	}
}

