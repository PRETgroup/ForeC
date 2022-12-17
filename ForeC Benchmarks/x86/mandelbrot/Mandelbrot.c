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

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct {
	/* shared */ int value;
	int status;
} Shared_ASIZE__global_0_0;
Shared_ASIZE__global_0_0 ASIZE__global_0_0 = {.value = 1000, .status = FOREC_SHARED_UNMODIFIED};

const int MAX_ITER__global_0_0 = (1 << 14);

unsigned mandel_double(const double cr, const double ci);
void display_double(const int size, const double xmin, const double xmax, const double ymin, const double ymax, const int ystart, const int yrange);

// thread display_double0__thread(void);
// thread display_double1__thread(void);
// thread display_double2__thread(void);
// thread display_double3__thread(void);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// display_double0
// display_double1
// display_double2
// display_double3
// main

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
	Thread display_double0__thread;
	Thread display_double1__thread;
	Thread display_double2__thread;
	Thread display_double3__thread;
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
	struct timeval startTime__main_0_0, endTime__main_0_0;
	long seconds__main_0_0;
	int microseconds__main_0_0;

mainParCore0: {
	// forec:scheduler:counter:start
	// Initialise and start timing each reaction.
	clockTimeUs.previous = getClockTimeUs();
	// forec:scheduler:counter:end
	
	//--------------------------------------------------------------

	gettimeofday(&startTime__main_0_0, 0);

	// par0(display_double0__thread, display_double1__thread, display_double2__thread, display_double3__thread);
	// forec:statement:par:par0:start
	// Set the par(...) information.
	mainParParent.parId = 0;
	pthread_mutex_lock(&mainParParent.parStatusLock);
	mainParParent.parStatus = FOREC_PAR_ON;
	pthread_cond_broadcast(&mainParParent.parStatusCond);
	pthread_mutex_unlock(&mainParParent.parStatusLock);

	// Link the threads and handlers together.
	mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
	display_double0__thread.programCounter = &&display_double0__thread;
	mainReactionStartMaster0.nextThread = &display_double0__thread;
	display_double0__thread.prevThread = &mainReactionStartMaster0;
	display_double1__thread.programCounter = &&display_double1__thread;
	display_double0__thread.nextThread = &display_double1__thread;
	display_double1__thread.prevThread = &display_double0__thread;
	display_double2__thread.programCounter = &&display_double2__thread;
	display_double1__thread.nextThread = &display_double2__thread;
	display_double2__thread.prevThread = &display_double1__thread;
	display_double3__thread.programCounter = &&display_double3__thread;
	display_double2__thread.nextThread = &display_double3__thread;
	display_double3__thread.prevThread = &display_double2__thread;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	display_double3__thread.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &display_double3__thread;

	// Link the last and first threads/handlers together.
	mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
	mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

	// Set the join address.
	mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

	// Set the core information.
	mainParCore0.activeThreads = 4;
	mainParCore0.reactionCounter = mainParReactionCounter;

	// Go to the first thread.
	goto display_double0__thread;
	par0JoinAddress_mainParCore0:;
	// forec:statement:par:par0:end

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
	// forec:thread:display_double0:start
	/*--------------------------------------------------------------
	| Thread display_double0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	double xmin__display_double0_0_0;
	double xmax__display_double0_0_0;
	double ymin__display_double0_0_0;
	double ymax__display_double0_0_0;

	// Thread body -------------------------------------------------
	display_double0__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		xmin__display_double0_0_0 = -2;
		xmax__display_double0_0_0 = 1.0;
		ymin__display_double0_0_0 = -1.5;
		ymax__display_double0_0_0 = 1.5;
		display_double(ASIZE__global_0_0.value, xmin__display_double0_0_0, xmax__display_double0_0_0, ymin__display_double0_0_0, ymax__display_double0_0_0, 0, 415);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:display_double0:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		display_double0__thread.nextThread -> prevThread = display_double0__thread.prevThread;
		display_double0__thread.prevThread -> nextThread = display_double0__thread.nextThread;
		goto *display_double0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:display_double0:end
	} // display_double0__thread
	// forec:thread:display_double0:end

	// forec:thread:display_double1:start
	/*--------------------------------------------------------------
	| Thread display_double1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	double xmin__display_double1_0_0;
	double xmax__display_double1_0_0;
	double ymin__display_double1_0_0;
	double ymax__display_double1_0_0;

	// Thread body -------------------------------------------------
	display_double1__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		xmin__display_double1_0_0 = -2;
		xmax__display_double1_0_0 = 1.0;
		ymin__display_double1_0_0 = -1.5;
		ymax__display_double1_0_0 = 1.5;
		display_double(ASIZE__global_0_0.value, xmin__display_double1_0_0, xmax__display_double1_0_0, ymin__display_double1_0_0, ymax__display_double1_0_0, 415, 85);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:display_double1:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		display_double1__thread.nextThread -> prevThread = display_double1__thread.prevThread;
		display_double1__thread.prevThread -> nextThread = display_double1__thread.nextThread;
		goto *display_double1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:display_double1:end
	} // display_double1__thread
	// forec:thread:display_double1:end

	// forec:thread:display_double2:start
	/*--------------------------------------------------------------
	| Thread display_double2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	double xmin__display_double2_0_0;
	double xmax__display_double2_0_0;
	double ymin__display_double2_0_0;
	double ymax__display_double2_0_0;

	// Thread body -------------------------------------------------
	display_double2__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		xmin__display_double2_0_0 = -2;
		xmax__display_double2_0_0 = 1.0;
		ymin__display_double2_0_0 = -1.5;
		ymax__display_double2_0_0 = 1.5;
		display_double(ASIZE__global_0_0.value, xmin__display_double2_0_0, xmax__display_double2_0_0, ymin__display_double2_0_0, ymax__display_double2_0_0, 500, 85);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:display_double2:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		display_double2__thread.nextThread -> prevThread = display_double2__thread.prevThread;
		display_double2__thread.prevThread -> nextThread = display_double2__thread.nextThread;
		goto *display_double2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:display_double2:end
	} // display_double2__thread
	// forec:thread:display_double2:end

	// forec:thread:display_double3:start
	/*--------------------------------------------------------------
	| Thread display_double3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	double xmin__display_double3_0_0;
	double xmax__display_double3_0_0;
	double ymin__display_double3_0_0;
	double ymax__display_double3_0_0;

	// Thread body -------------------------------------------------
	display_double3__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		xmin__display_double3_0_0 = -2;
		xmax__display_double3_0_0 = 1.0;
		ymin__display_double3_0_0 = -1.5;
		ymax__display_double3_0_0 = 1.5;
		display_double(ASIZE__global_0_0.value, xmin__display_double3_0_0, xmax__display_double3_0_0, ymin__display_double3_0_0, ymax__display_double3_0_0, 585, 415);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:display_double3:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		display_double3__thread.nextThread -> prevThread = display_double3__thread.prevThread;
		display_double3__thread.prevThread -> nextThread = display_double3__thread.nextThread;
		goto *display_double3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:display_double3:end
	} // display_double3__thread
	// forec:thread:display_double3:end


} // End of the main() function.

unsigned mandel_double(const double cr__mandel_double_0_0, const double ci__mandel_double_0_0) {
	double zr__mandel_double_0_0 = cr__mandel_double_0_0, zi__mandel_double_0_0 = ci__mandel_double_0_0;
	double tmp__mandel_double_0_0;
	unsigned i__mandel_double_0_0;
	for (i__mandel_double_0_0 = 0; i__mandel_double_0_0 < MAX_ITER__global_0_0; i__mandel_double_0_0++) {
		tmp__mandel_double_0_0 = zr__mandel_double_0_0*zr__mandel_double_0_0 - zi__mandel_double_0_0*zi__mandel_double_0_0 + cr__mandel_double_0_0;
		zi__mandel_double_0_0 *= 2*zr__mandel_double_0_0;
		zi__mandel_double_0_0 += ci__mandel_double_0_0;
		zr__mandel_double_0_0 = tmp__mandel_double_0_0;
		if (zr__mandel_double_0_0*zr__mandel_double_0_0 + zi__mandel_double_0_0*zi__mandel_double_0_0 > 4.0) {
			break;
		} else {
			// if1
		}
	}
	return i__mandel_double_0_0;
}

void display_double(const int size__display_double_0_0, const double xmin__display_double_0_0, const double xmax__display_double_0_0, const double ymin__display_double_0_0, const double ymax__display_double_0_0, const int ystart__display_double_0_0, const int yrange__display_double_0_0) {
	int x__display_double_0_0, y__display_double_0_0;
	double cr__display_double_0_0, ci__display_double_0_0;
	double xscal__display_double_0_0 = (xmax__display_double_0_0 - xmin__display_double_0_0)/size__display_double_0_0;
	double yscal__display_double_0_0 = (ymax__display_double_0_0 - ymin__display_double_0_0)/size__display_double_0_0;
	unsigned counts__display_double_0_0;
	for (y__display_double_0_0 = ystart__display_double_0_0; y__display_double_0_0 < ystart__display_double_0_0 + yrange__display_double_0_0; y__display_double_0_0++) {
		for (x__display_double_0_0 = 0; x__display_double_0_0 < size__display_double_0_0; x__display_double_0_0++) {
			cr__display_double_0_0 = xmin__display_double_0_0 + x__display_double_0_0*xscal__display_double_0_0;
			ci__display_double_0_0 = ymin__display_double_0_0 + y__display_double_0_0*yscal__display_double_0_0;
			counts__display_double_0_0 = mandel_double(cr__display_double_0_0, ci__display_double_0_0);
		}
	}
}

