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
unsigned int forec_mutex_value_servo;

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

// Thread servo with par(...)s
Parent servoParParent = { .parStatusCond = PTHREAD_COND_INITIALIZER, .parStatusLock = PTHREAD_MUTEX_INITIALIZER };
Core servoParCore0 = { .statusCond = PTHREAD_COND_INITIALIZER, .statusLock = PTHREAD_MUTEX_INITIALIZER, .reactionCounterCond = PTHREAD_COND_INITIALIZER, .reactionCounterLock = PTHREAD_MUTEX_INITIALIZER};
volatile int servoParReactionCounter;
pthread_cond_t servoParReactionCounterCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t servoParReactionCounterLock = PTHREAD_MUTEX_INITIALIZER;


/*==============================================================
| Original global declarations:
| Global declarations in the original program code.
*=============================================================*/
// Original main function
void *forecMain(void *args);

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* input */ char radioInput__global_0_0;
/* input */ char spiInput__global_0_0;
/* output */ double servoOutputs__global_0_0[4];

typedef struct {
	/* shared */ int value;
	int status;
} Shared_terminate__global_0_0;
Shared_terminate__global_0_0 terminate__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value;
	int status;
} Shared_isSafe__global_0_0;
Shared_isSafe__global_0_0 isSafe__global_0_0 = {.value = 1, .status = FOREC_SHARED_UNMODIFIED};

double decision__global_0_0 = 0.0;
int _1Hz__global_0_0 = 0;
int _20Hz__global_0_0 = 0;
const int MAX_DOWN_TIME__global_0_0 = 100;
const char INVALID__global_0_0 = '0';
const char VALID__global_0_0 = '1';
const int MANUAL__global_0_0 = 0;
const int AUTOMATIC__global_0_0 = 1;
typedef int FILE__global_0_0;

#define FILE__global_0_0 FILE

int EOF__global_0_0;

#define EOF__global_0_0 EOF

typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_inputFile__global_0_0;
Shared_inputFile__global_0_0 inputFile__global_0_0;
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_outputFile__global_0_0;
Shared_outputFile__global_0_0 outputFile__global_0_0;

long long radioDownTime__global_0_0 = 0;
long long spiDownTime__global_0_0 = 0;

int getMode(const int communicationInput);
double autopilot(const int mode, const int communicationInput);
void computation(void);

// thread flight__thread(void);
// thread servo__thread(void);
// thread servo0__thread(void);
// thread servo1__thread(void);
// thread servo2__thread(void);
// thread servo3__thread(void);
// thread timer__thread(void);
// thread failsafe__thread(void);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// failsafe
Shared_isSafe__global_0_0 isSafe__global_0_0_copy_failsafe = {.status = FOREC_SHARED_UNMODIFIED};
Shared_outputFile__global_0_0 outputFile__global_0_0_copy_failsafe = {.status = FOREC_SHARED_UNMODIFIED};
// flight
// main
// servo
// servo0
// servo1
// servo2
// servo3
// timer
Shared_terminate__global_0_0 terminate__global_0_0_copy_timer = {.status = FOREC_SHARED_UNMODIFIED};
Shared_inputFile__global_0_0 inputFile__global_0_0_copy_timer = {.status = FOREC_SHARED_UNMODIFIED};

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

	// Thread servo with par(...)s
	servoParParent.parStatus = FOREC_PAR_OFF;
	servoParCore0.sync = 1;
	servoParCore0.status = FOREC_CORE_REACTING;
	servoParReactionCounter = 0;


	// Reset ForeC mutex values
	forec_mutex_value_servo = -1;

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
	Thread failsafe__thread;
	Thread flight__thread;
	Thread servo__thread;
	Thread timer__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionEndMaster0;
	Thread servoParHandlerMaster0;
	Thread abortWeakImmediate0Check0;
	Thread abortStrongImmediate1Check0;

	// par1
	Thread servo0__thread;
	Thread servo1__thread;
	Thread servo2__thread;
	Thread servo3__thread;
	Thread servoReactionStartMaster0;
	Thread servoReactionEndMaster0;


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
	inputFile__global_0_0.value = fopen("input.dat", "r");
	outputFile__global_0_0.value = fopen("output.txt", "w");
	servoOutputs__global_0_0[0] = 0.0;
	servoOutputs__global_0_0[1] = 0.0;
	servoOutputs__global_0_0[2] = 0.0;
	servoOutputs__global_0_0[3] = 0.0;

	while (!terminate__global_0_0.value) {
		/* abortStrongImmediate1 */ {
			// forec:statement:abort:abortStrongImmediate1:start
			if (terminate__global_0_0.value) {
				goto abortEnd_abortStrongImmediate1;
			}
			// forec:statement:abort:abortStrongImmediate1:end

			/* abortWeakImmediate0 */ {
				// par0(servo__thread, timer__thread, flight__thread, failsafe__thread);
				// forec:statement:par:par0:start
				// Set the par(...) information.
				mainParParent.parId = 0;
				pthread_mutex_lock(&mainParParent.parStatusLock);
				mainParParent.parStatus = FOREC_PAR_ON;
				pthread_cond_broadcast(&mainParParent.parStatusCond);
				pthread_mutex_unlock(&mainParParent.parStatusLock);

				// Link the threads and handlers together.
				mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
				abortStrongImmediate1Check0.programCounter = &&abortStrongImmediate1Check0;
				mainReactionStartMaster0.nextThread = &abortStrongImmediate1Check0;
				abortStrongImmediate1Check0.prevThread = &mainReactionStartMaster0;
				servo__thread.programCounter = &&servo__thread;
				abortStrongImmediate1Check0.nextThread = &servo__thread;
				servo__thread.prevThread = &abortStrongImmediate1Check0;
				servoParHandlerMaster0.programCounter = &&servoParHandlerMaster0;
				servo__thread.nextThread = &servoParHandlerMaster0;
				servoParHandlerMaster0.prevThread = &servo__thread;
				timer__thread.programCounter = &&timer__thread;
				servoParHandlerMaster0.nextThread = &timer__thread;
				timer__thread.prevThread = &servoParHandlerMaster0;
				flight__thread.programCounter = &&flight__thread;
				timer__thread.nextThread = &flight__thread;
				flight__thread.prevThread = &timer__thread;
				failsafe__thread.programCounter = &&failsafe__thread;
				flight__thread.nextThread = &failsafe__thread;
				failsafe__thread.prevThread = &flight__thread;
				abortWeakImmediate0Check0.programCounter = &&abortWeakImmediate0Check0;
				failsafe__thread.nextThread = &abortWeakImmediate0Check0;
				abortWeakImmediate0Check0.prevThread = &failsafe__thread;
				mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
				abortWeakImmediate0Check0.nextThread = &mainReactionEndMaster0;
				mainReactionEndMaster0.prevThread = &abortWeakImmediate0Check0;

				// Link the last and first threads/handlers together.
				mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
				mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

				// Set the join address.
				mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

				// Set the core information.
				mainParCore0.activeThreads = 5;
				mainParCore0.reactionCounter = mainParReactionCounter;

				// Go to the first thread.
				goto servo__thread;
				par0JoinAddress_mainParCore0:;
				// forec:statement:par:par0:end
				abortEnd_abortWeakImmediate0:;
			} // when (!isSafe__global_0_0.value);
			// forec:statement:abort:abortWeakImmediate0:scope:end
			abortEnd_abortStrongImmediate1:;
		} // when (terminate__global_0_0.value);
		// forec:statement:abort:abortStrongImmediate1:scope:end

		// pause;
		// forec:statement:pause:pause0:start
		asm volatile ("nop");
		// forec:statement:pause:pause0:end


		// forec:scheduler:iterationEnd:while_0:start
		// Synchronise end of iteration
		mainParParent.parId = -2;
		pthread_mutex_lock(&mainParParent.parStatusLock);
		mainParParent.parStatus = FOREC_PAR_ON;
		pthread_cond_broadcast(&mainParParent.parStatusCond);
		pthread_mutex_unlock(&mainParParent.parStatusLock);
		mainParParent.programCounter = &&while_0_endAddress;
		goto mainParHandlerMaster0;
		while_0_endAddress:;
		// forec:scheduler:iterationEnd:while_0:end
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
	// forec:scheduler:parHandler:servo:master:0:start
	//-- Thread servo par(...) handlers
servoParHandlerMaster0: {
	// Check the execution status of the nested par(...)s.
	if (servoParParent.parStatus == FOREC_PAR_OFF) {
		// Release the mutex.
		forec_mutex_value_servo &= 0x7fffffff;

		goto *servoParHandlerMaster0.nextThread -> programCounter;
	}
	// Release the mutex.
	forec_mutex_value_servo &= 0x7fffffff;

	int parId = servoParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		servoReactionStartMaster0.programCounter = &&servoReactionStartMaster0;
		servo0__thread.programCounter = &&servo0__thread;
		servoReactionStartMaster0.nextThread = &servo0__thread;
		servo0__thread.prevThread = &servoReactionStartMaster0;
		servo1__thread.programCounter = &&servo1__thread;
		servo0__thread.nextThread = &servo1__thread;
		servo1__thread.prevThread = &servo0__thread;
		servo2__thread.programCounter = &&servo2__thread;
		servo1__thread.nextThread = &servo2__thread;
		servo2__thread.prevThread = &servo1__thread;
		servo3__thread.programCounter = &&servo3__thread;
		servo2__thread.nextThread = &servo3__thread;
		servo3__thread.prevThread = &servo2__thread;
		servoReactionEndMaster0.programCounter = &&servoReactionEndMaster0;
		servo3__thread.nextThread = &servoReactionEndMaster0;
		servoReactionEndMaster0.prevThread = &servo3__thread;

		// Swap the nested par handler with the linked list.
		servoParHandlerMaster0.prevThread -> nextThread = &servoReactionStartMaster0;
		servoReactionStartMaster0.prevThread = servoParHandlerMaster0.prevThread;
		servoReactionEndMaster0.nextThread = servoParHandlerMaster0.nextThread;
		servoParHandlerMaster0.nextThread -> prevThread = &servoReactionEndMaster0;
		
		// Set the core information.
		servoParCore0.activeThreads = 4;
		servoParCore0.reactionCounter = servoParReactionCounter;
		
		// Go to the first thread.
		goto servo0__thread;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.

		pthread_mutex_lock(&servoParParent.parStatusLock);
		servoParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&servoParParent.parStatusCond);
		pthread_mutex_unlock(&servoParParent.parStatusLock);
		servoParParent.parId = -1;

		forec_mutex_value_servo = -1;

		// Set slave cores' status to reacting.

		// Increment the reaction counter for synchronisation.
		pthread_mutex_lock(&servoParReactionCounterLock);
		servoParReactionCounter++;
		pthread_cond_broadcast(&servoParReactionCounterCond);
		pthread_mutex_unlock(&servoParReactionCounterLock);

		// Return to thread servo.
		goto *servoParParent.programCounter;
	} else if (parId == -3) {
		// Thread termination
		mainParCore0.activeThreads--;
		servoParCore0.activeThreads--;

		// Wait for other cores to complete their reaction.

		pthread_mutex_lock(&servoParParent.parStatusLock);
		servoParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&servoParParent.parStatusCond);
		pthread_mutex_unlock(&servoParParent.parStatusLock);
		servoParParent.parId = -1;

		// Set slave cores' status to reacting.

		// Increment the reaction counter for synchronisation.
		pthread_mutex_lock(&servoParReactionCounterLock);
		servoParReactionCounter++;
		pthread_cond_broadcast(&servoParReactionCounterCond);
		pthread_mutex_unlock(&servoParReactionCounterLock);

		// Delete this par(...) handler.
		servoParHandlerMaster0.prevThread -> nextThread = servoParHandlerMaster0.nextThread;
		servoParHandlerMaster0.nextThread -> prevThread = servoParHandlerMaster0.prevThread;
			
		// Return to thread servo.
		goto *servoParParent.programCounter;
	} else {
		// Unscheduled par(...)
		servoParCore0.reactionCounter = servoParReactionCounter;

		servoParHandlerMaster0.programCounter = &&wrongParId_servoParHandlerMaster0;
		wrongParId_servoParHandlerMaster0:;

		pthread_mutex_lock(&servoParCore0.statusLock);
		servoParCore0.status = FOREC_CORE_TERMINATED;
		pthread_cond_signal(&servoParCore0.statusCond);
		pthread_mutex_unlock(&servoParCore0.statusLock);

		// Wait for the next tick.
		pthread_mutex_lock(&servoParReactionCounterLock);
		while (servoParCore0.reactionCounter == servoParReactionCounter) { pthread_cond_wait(&servoParReactionCounterCond, &servoParReactionCounterLock); }
		pthread_mutex_unlock(&servoParReactionCounterLock);
		servoParCore0.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (servoParParent.parStatus == FOREC_PAR_ON && servoParParent.parId == parId) {
			goto *servoParHandlerMaster0.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		servoParHandlerMaster0.programCounter = &&servoParHandlerMaster0;
		
		goto servoParHandlerMaster0;
	}
	
	// Control should not reach here.
	goto servoParHandlerMaster0;
}
	// forec:scheduler:parHandler:servo:master:0:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:master:0:start
	//-- main:
mainReactionStartMaster0: {
	// Go to the next thread.
	goto *mainReactionStartMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:master:0:end
 
	// forec:scheduler:reactionStart:servo:master:0:start
	//-- servo:
servoReactionStartMaster0: {
	// Go to the next thread.
	goto *servoReactionStartMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:servo:master:0:end
 


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
	forec_mutex_value_servo = -1;

	// Combine shared variables.
	int parId = mainParParent.parId;
	if (parId == 0) {

		// terminate__global_0_0
		if (terminate__global_0_0_copy_timer.status == FOREC_SHARED_MODIFIED) {
			terminate__global_0_0_copy_timer.status = FOREC_SHARED_UNMODIFIED;
			terminate__global_0_0.value = terminate__global_0_0_copy_timer.value;
		}

		// isSafe__global_0_0
		if (isSafe__global_0_0_copy_failsafe.status == FOREC_SHARED_MODIFIED) {
			isSafe__global_0_0_copy_failsafe.status = FOREC_SHARED_UNMODIFIED;
			isSafe__global_0_0.value = isSafe__global_0_0_copy_failsafe.value;
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
 
	// forec:scheduler:reactionEnd:servo:master:0:start
	//-- servo:
servoReactionEndMaster0: {
	// Determine if the core can still react or not.
	pthread_mutex_lock(&servoParCore0.statusLock);
	if (servoParCore0.activeThreads) {
		servoParCore0.status = FOREC_CORE_REACTED;
	} else {
		servoParCore0.status = FOREC_CORE_TERMINATED;
	}
	pthread_cond_signal(&servoParCore0.statusCond);
	pthread_mutex_unlock(&servoParCore0.statusLock);
	
	// Wait for other cores to complete their reaction.


	// Return back to the parent thread if all the cores have terminated.
	if (1 && servoParCore0.status == FOREC_CORE_TERMINATED) {
		forec_mutex_value_servo = -1;

		pthread_mutex_lock(&servoParParent.parStatusLock);
		servoParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&servoParParent.parStatusCond);
		pthread_mutex_unlock(&servoParParent.parStatusLock);
		servoParParent.parId = -1;
		
		// Set slave cores' status to reacting

		// Increment the reaction counter for synchronization.
		pthread_mutex_lock(&servoParReactionCounterLock);
		servoParReactionCounter++;
		pthread_cond_broadcast(&servoParReactionCounterCond);
		pthread_mutex_unlock(&servoParReactionCounterLock);

		// Swap the reaction (start & end) handlers with (thread servo & nested par handler).
		servoReactionStartMaster0.prevThread -> nextThread = &servo__thread;
		servo__thread.prevThread = servoReactionStartMaster0.prevThread;
		servo__thread.nextThread = &servoParHandlerMaster0;
		servoParHandlerMaster0.prevThread = &servo__thread;
		servoParHandlerMaster0.nextThread = servoReactionEndMaster0.nextThread;
		servoReactionEndMaster0.nextThread -> prevThread = &servoParHandlerMaster0;

		goto *servoParParent.programCounter;
	}

	// Set slave cores' status to reacting

	// Increment the reaction counter for synchronization.
	pthread_mutex_lock(&servoParReactionCounterLock);
	servoParReactionCounter++;
	pthread_cond_broadcast(&servoParReactionCounterCond);
	pthread_mutex_unlock(&servoParReactionCounterLock);

	// Go to the next thread.
	goto *servoReactionEndMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:servo:master:0:end
 


	// Abort check handlers ----------------------------------------
	// forec:scheduler:abortHandler:abortStrongImmediate1:0:start
	// abortStrongImmediate1 (terminate__global_0_0.value)
abortStrongImmediate1Check0: {
	// Check the abort condition.
	if (terminate__global_0_0.value) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore0.activeThreads = 0;

		// Update the parent thread to resume at the end of the abort scope.
		mainParParent.programCounter = &&abortEnd_abortStrongImmediate1;
		
		goto mainReactionEndMaster0;
	}
	
	// Continue to the next thread.
	goto *abortStrongImmediate1Check0.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrongImmediate1:0:end
	// forec:scheduler:abortHandler:abortWeakImmediate0:0:start
	// abortWeakImmediate0 (!isSafe__global_0_0.value)
abortWeakImmediate0Check0: {
	// Check the abort condition.
	if (!isSafe__global_0_0.value) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore0.activeThreads = 0;

		// Update the parent thread to resume at the end of the abort scope.
		mainParParent.programCounter = &&abortEnd_abortWeakImmediate0;
		
		goto mainReactionEndMaster0;
	}
	
	// Continue to the next thread.
	goto *abortWeakImmediate0Check0.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortWeakImmediate0:0:end




/*==============================================================
| ForeC threads:
| Threads' code translated into C code.
*=============================================================*/
	// forec:thread:failsafe:start
	/*--------------------------------------------------------------
	| Thread failsafe
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_isSafe__global_0_0 isSafe__global_0_0_copy_failsafe_local;
	Shared_outputFile__global_0_0 outputFile__global_0_0_copy_failsafe_local;

	// Thread body -------------------------------------------------
	failsafe__thread: {
		// Initialise the local copies of shared variables.
		isSafe__global_0_0_copy_failsafe_local.value = isSafe__global_0_0.value;
		isSafe__global_0_0_copy_failsafe_local.status = FOREC_SHARED_UNMODIFIED;
		outputFile__global_0_0_copy_failsafe_local.value = outputFile__global_0_0.value;
		outputFile__global_0_0_copy_failsafe_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		while (1) {
			computation();
			computation();
			computation();
			computation();
			if (radioInput__global_0_0 == INVALID__global_0_0) {
				radioDownTime__global_0_0++;
			} else {
				// ifElse5
				radioDownTime__global_0_0 = 0;
			}
			computation();
			computation();
			computation();
			computation();
			if (spiInput__global_0_0 == INVALID__global_0_0) {
				spiDownTime__global_0_0++;
			} else {
				// ifElse6
				spiDownTime__global_0_0 = 0;
			}
			isSafe__global_0_0_copy_failsafe_local.value = (radioDownTime__global_0_0 < MAX_DOWN_TIME__global_0_0) || (spiDownTime__global_0_0 < MAX_DOWN_TIME__global_0_0);
			isSafe__global_0_0_copy_failsafe_local.status = FOREC_SHARED_MODIFIED;
			fprintf(outputFile__global_0_0_copy_failsafe_local.value, "%d\n", isSafe__global_0_0_copy_failsafe_local.value);

			// pause;
			// Write the local copy of shared variables back to their global copy.
			isSafe__global_0_0_copy_failsafe = isSafe__global_0_0_copy_failsafe_local;
			// forec:statement:pause:pause4:start
			failsafe__thread.programCounter = &&pause4;
			goto *failsafe__thread.nextThread -> programCounter;
			pause4:;
			// forec:statement:pause:pause4:end
			// Update the values of the used shared variables from their global copy.
			isSafe__global_0_0_copy_failsafe_local = isSafe__global_0_0;
			outputFile__global_0_0_copy_failsafe_local = outputFile__global_0_0;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		isSafe__global_0_0_copy_failsafe = isSafe__global_0_0_copy_failsafe_local;

		// forec:scheduler:threadRemove:failsafe:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		failsafe__thread.nextThread -> prevThread = failsafe__thread.prevThread;
		failsafe__thread.prevThread -> nextThread = failsafe__thread.nextThread;
		goto *failsafe__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:failsafe:end
	} // failsafe__thread
	// forec:thread:failsafe:end

	// forec:thread:flight:start
	/*--------------------------------------------------------------
	| Thread flight
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	int mode__flight_1_0;

	// Thread body -------------------------------------------------
	flight__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		while (1) {
			mode__flight_1_0 = 0;
			if (getMode(radioInput__global_0_0) != VALID__global_0_0) {
				mode__flight_1_0 = getMode(radioInput__global_0_0);
			} else {
				// if1
			}
			decision__global_0_0 = autopilot(mode__flight_1_0, radioInput__global_0_0);

			// pause;
			// forec:statement:pause:pause1:start
			flight__thread.programCounter = &&pause1;
			goto *flight__thread.nextThread -> programCounter;
			pause1:;
			// forec:statement:pause:pause1:end

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:flight:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		flight__thread.nextThread -> prevThread = flight__thread.prevThread;
		flight__thread.prevThread -> nextThread = flight__thread.nextThread;
		goto *flight__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:flight:end
	} // flight__thread
	// forec:thread:flight:end

	// forec:thread:servo:start
	/*--------------------------------------------------------------
	| Thread servo
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	servo__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		while (1) {
			// par1(servo0__thread, servo1__thread, servo2__thread, servo3__thread);
			// Set the par(...) information.
			// forec:statement:par:par1:start
			servoParParent.parId = 1;
			pthread_mutex_lock(&servoParParent.parStatusLock);
			servoParParent.parStatus = FOREC_PAR_ON;
			pthread_cond_broadcast(&servoParParent.parStatusCond);
			pthread_mutex_unlock(&servoParParent.parStatusLock);
			servoParParent.programCounter = &&par1JoinAddress_servoParParent;

			// Remove this thread from the linked list.
			servo__thread.nextThread -> prevThread = servo__thread.prevThread;
			servo__thread.prevThread -> nextThread = servo__thread.nextThread;
			goto servoParHandlerMaster0;
			par1JoinAddress_servoParParent:;
			// forec:statement:par:par1:end

			computation();

			// pause;
			// forec:statement:pause:pause2:start
			servo__thread.programCounter = &&pause2;
			goto *servo__thread.nextThread -> programCounter;
			pause2:;
			// forec:statement:pause:pause2:end


			// forec:scheduler:iterationEnd:while_2:start
			// Synchronise end of iteration
			servoParParent.parId = -2;
			pthread_mutex_lock(&servoParParent.parStatusLock);
			servoParParent.parStatus = FOREC_PAR_ON;
			pthread_cond_broadcast(&servoParParent.parStatusCond);
			pthread_mutex_unlock(&servoParParent.parStatusLock);
			servoParParent.programCounter = &&while_2_endAddress;
			goto servoParHandlerMaster0;
			while_2_endAddress:;
			// forec:scheduler:iterationEnd:while_2:end
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:servo:start
		// Delete par handler
		servoParParent.parId = -3;
		servoParParent.parStatus = FOREC_PAR_ON;
		servoParParent.programCounter = &&servo_endAddress;
		goto servoParHandlerMaster0;
		servo_endAddress:;

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		servo__thread.nextThread -> prevThread = servo__thread.prevThread;
		servo__thread.prevThread -> nextThread = servo__thread.nextThread;
		goto *servo__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:servo:end
	} // servo__thread
	// forec:thread:servo:end

	// forec:thread:servo0:start
	/*--------------------------------------------------------------
	| Thread servo0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	servo0__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		computation();
		computation();
		computation();
		servoOutputs__global_0_0[0] = 0;

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:servo0:start

		// Delete thread from the linked list and core.
		servoParCore0.activeThreads--;
		servo0__thread.nextThread -> prevThread = servo0__thread.prevThread;
		servo0__thread.prevThread -> nextThread = servo0__thread.nextThread;
		goto *servo0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:servo0:end
	} // servo0__thread
	// forec:thread:servo0:end

	// forec:thread:servo1:start
	/*--------------------------------------------------------------
	| Thread servo1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	servo1__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		computation();
		computation();
		computation();
		servoOutputs__global_0_0[1] = 1;

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:servo1:start

		// Delete thread from the linked list and core.
		servoParCore0.activeThreads--;
		servo1__thread.nextThread -> prevThread = servo1__thread.prevThread;
		servo1__thread.prevThread -> nextThread = servo1__thread.nextThread;
		goto *servo1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:servo1:end
	} // servo1__thread
	// forec:thread:servo1:end

	// forec:thread:servo2:start
	/*--------------------------------------------------------------
	| Thread servo2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	servo2__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		computation();
		computation();
		computation();
		servoOutputs__global_0_0[2] = 2;

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:servo2:start

		// Delete thread from the linked list and core.
		servoParCore0.activeThreads--;
		servo2__thread.nextThread -> prevThread = servo2__thread.prevThread;
		servo2__thread.prevThread -> nextThread = servo2__thread.nextThread;
		goto *servo2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:servo2:end
	} // servo2__thread
	// forec:thread:servo2:end

	// forec:thread:servo3:start
	/*--------------------------------------------------------------
	| Thread servo3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	servo3__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		computation();
		computation();
		computation();
		servoOutputs__global_0_0[3] = 3;

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:servo3:start

		// Delete thread from the linked list and core.
		servoParCore0.activeThreads--;
		servo3__thread.nextThread -> prevThread = servo3__thread.prevThread;
		servo3__thread.prevThread -> nextThread = servo3__thread.nextThread;
		goto *servo3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:servo3:end
	} // servo3__thread
	// forec:thread:servo3:end

	// forec:thread:timer:start
	/*--------------------------------------------------------------
	| Thread timer
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_terminate__global_0_0 terminate__global_0_0_copy_timer_local;
	Shared_inputFile__global_0_0 inputFile__global_0_0_copy_timer_local;
	char newLine__timer_1_0;

	// Thread body -------------------------------------------------
	timer__thread: {
		// Initialise the local copies of shared variables.
		terminate__global_0_0_copy_timer_local.value = terminate__global_0_0.value;
		terminate__global_0_0_copy_timer_local.status = FOREC_SHARED_UNMODIFIED;
		inputFile__global_0_0_copy_timer_local.value = inputFile__global_0_0.value;
		inputFile__global_0_0_copy_timer_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		while (1) {
			if (_1Hz__global_0_0++ > 60) {
				computation();
				_1Hz__global_0_0 = 0;
			} else {
				// if2
			}
			if (_20Hz__global_0_0++ > 3) {
				computation();
				_20Hz__global_0_0 = 0;
			} else {
				// if3
			}
			radioInput__global_0_0 = fgetc(inputFile__global_0_0_copy_timer_local.value);
			spiInput__global_0_0 = fgetc(inputFile__global_0_0_copy_timer_local.value);
			newLine__timer_1_0 = fgetc(inputFile__global_0_0_copy_timer_local.value);
			while (newLine__timer_1_0 == '\n' || newLine__timer_1_0 == '\r') {
				newLine__timer_1_0 = fgetc(inputFile__global_0_0_copy_timer_local.value);
				// forec:iteration:while_3:bound:0:10
			}
			ungetc(newLine__timer_1_0, inputFile__global_0_0_copy_timer_local.value);
			if (radioInput__global_0_0 == EOF__global_0_0 || spiInput__global_0_0 == EOF__global_0_0) {
				terminate__global_0_0_copy_timer_local.value = 1;
				terminate__global_0_0_copy_timer_local.status = FOREC_SHARED_MODIFIED;
			} else {
				// if4
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.
			terminate__global_0_0_copy_timer = terminate__global_0_0_copy_timer_local;
			// forec:statement:pause:pause3:start
			timer__thread.programCounter = &&pause3;
			goto *timer__thread.nextThread -> programCounter;
			pause3:;
			// forec:statement:pause:pause3:end
			// Update the values of the used shared variables from their global copy.
			terminate__global_0_0_copy_timer_local = terminate__global_0_0;
			inputFile__global_0_0_copy_timer_local = inputFile__global_0_0;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		terminate__global_0_0_copy_timer = terminate__global_0_0_copy_timer_local;

		// forec:scheduler:threadRemove:timer:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		timer__thread.nextThread -> prevThread = timer__thread.prevThread;
		timer__thread.prevThread -> nextThread = timer__thread.nextThread;
		goto *timer__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:timer:end
	} // timer__thread
	// forec:thread:timer:end


} // End of the main() function.

int getMode(const int communicationInput__getMode_0_0) {
	const int mask__getMode_0_0 = (communicationInput__getMode_0_0 & 0x02) > 1;
	switch (mask__getMode_0_0) {
			
		case (0):
			return MANUAL__global_0_0;
			
		case (1):
			return AUTOMATIC__global_0_0;
			
		default:
			break;
	}
	return AUTOMATIC__global_0_0;
}

double autopilot(const int mode__autopilot_0_0, const int communicationInput__autopilot_0_0) {
	computation();
	computation();
	computation();
	computation();
	computation();
	computation();
	computation();
	computation();
	return (double)(communicationInput__autopilot_0_0*mode__autopilot_0_0);
}

void computation(void) {
	double result__computation_0_0 = 1.0;
	int i__computation_0_0;
	for (i__computation_0_0 = 1; i__computation_0_0 < 2000; i__computation_0_0++) {
		result__computation_0_0 += (double)((int)result__computation_0_0%i__computation_0_0)*(result__computation_0_0/result__computation_0_0);
		// forec:iteration:for1_6:bound:1999:1999
	}
}

