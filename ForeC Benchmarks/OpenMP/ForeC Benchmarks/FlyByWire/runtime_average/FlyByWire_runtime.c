/*==============================================================
| Hardware architecture specific declarations:
| Cores, mutex and input/output information.
*=============================================================*/
#include <pthread.h>

// Mapping Pthreads to processor cores
pthread_t cores[4];
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
volatile Core mainParCore2;
volatile Core mainParCore3;
volatile int mainParReactionCounter;

// Thread servo with par(...)s
volatile Parent servoParParent;
volatile Core servoParCore0;
volatile Core servoParCore1;
volatile Core servoParCore2;
volatile Core servoParCore3;
volatile int servoParReactionCounter;


/*==============================================================
| Original global declarations:
| Global declarations in the original program code.
*=============================================================*/
// Original main function
void *forecMain(void *args);

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

typedef void clockid_t__global_0_0;

#define clockid_t__global_0_0 clockid_t
#undef CLOCK_MONOTONIC

clockid_t__global_0_0 CLOCK_MONOTONIC__global_0_0 = 1;

/* input */ char radioInput__global_0_0;
/* input */ char spiInput__global_0_0;
/* output */ double servoOutputs__global_0_0[4];

const int plus(const int *copy1__plus_0_0, const int *copy2__plus_0_0) {
	return * copy1__plus_0_0 + * copy2__plus_0_0;
}

typedef struct {
	/* shared */ int value;
	unsigned short int status;
} Shared_terminate__global_0_0;
Shared_terminate__global_0_0 terminate__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value;
	unsigned short int status;
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
	unsigned short int status;
} Shared_inputFile__global_0_0;
Shared_inputFile__global_0_0 inputFile__global_0_0;
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	unsigned short int status;
} Shared_outputFile__global_0_0;
Shared_outputFile__global_0_0 outputFile__global_0_0;
typedef struct {
	/* shared */ long long value;
	unsigned short int status;
} Shared_radioDownTime__global_0_0;
Shared_radioDownTime__global_0_0 radioDownTime__global_0_0;
typedef struct {
	/* shared */ long long value;
	unsigned short int status;
} Shared_spiDownTime__global_0_0;
Shared_spiDownTime__global_0_0 spiDownTime__global_0_0;

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
Shared_terminate__global_0_0 terminate__global_0_0_copy_failsafe = {.status = FOREC_SHARED_UNMODIFIED};
Shared_isSafe__global_0_0 isSafe__global_0_0_copy_failsafe = {.status = FOREC_SHARED_UNMODIFIED};
Shared_outputFile__global_0_0 outputFile__global_0_0_copy_failsafe = {.status = FOREC_SHARED_UNMODIFIED};
Shared_radioDownTime__global_0_0 radioDownTime__global_0_0_copy_failsafe = {.status = FOREC_SHARED_UNMODIFIED};
Shared_spiDownTime__global_0_0 spiDownTime__global_0_0_copy_failsafe = {.status = FOREC_SHARED_UNMODIFIED};
// flight
Shared_terminate__global_0_0 terminate__global_0_0_copy_flight = {.status = FOREC_SHARED_UNMODIFIED};
// main
Shared_terminate__global_0_0 terminate__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_isSafe__global_0_0 isSafe__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_inputFile__global_0_0 inputFile__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_outputFile__global_0_0 outputFile__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_radioDownTime__global_0_0 radioDownTime__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_spiDownTime__global_0_0 spiDownTime__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
// servo
Shared_terminate__global_0_0 terminate__global_0_0_copy_servo = {.status = FOREC_SHARED_UNMODIFIED};
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

	// Thread servo with par(...)s
	servoParParent.parStatus = FOREC_PAR_OFF;
	servoParCore0.sync = 1;
	servoParCore0.status = FOREC_CORE_REACTING;
	servoParCore1.sync = 1;
	servoParCore1.status = FOREC_CORE_REACTING;
	servoParCore2.sync = 1;
	servoParCore2.status = FOREC_CORE_REACTING;
	servoParCore3.sync = 1;
	servoParCore3.status = FOREC_CORE_REACTING;
	servoParReactionCounter = 0;


	// Reset ForeC mutex values
	forec_mutex_value_servo = -1;

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
	Arguments arguments2 = {.coreId = 2, .argc = argc__main_0_0, .argv = argv__main_0_0};
	pthread_create(&cores[2], &slaveCoreAttribute, forecMain, (void *)&arguments2);
	Arguments arguments3 = {.coreId = 3, .argc = argc__main_0_0, .argv = argv__main_0_0};
	pthread_create(&cores[3], &slaveCoreAttribute, forecMain, (void *)&arguments3);

	// End core execution
	pthread_attr_destroy(&masterCoreAttribute);
	pthread_attr_destroy(&slaveCoreAttribute);
	
	// Program termination
	pthread_join(cores[0], NULL);
	pthread_join(cores[1], NULL);
	pthread_join(cores[2], NULL);
	pthread_join(cores[3], NULL);

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
	Thread failsafe__thread;
	Thread flight__thread;
	Thread servo__thread;
	Thread timer__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionStartSlave1;
	Thread mainReactionStartSlave2;
	Thread mainReactionStartSlave3;
	Thread mainReactionEndMaster0;
	Thread mainReactionEndSlave1;
	Thread mainReactionEndSlave2;
	Thread mainReactionEndSlave3;
	Thread servoParHandlerMaster0;
	Thread servoParHandlerSlave1;
	Thread servoParHandlerSlave2;
	Thread servoParHandlerSlave3;
	Thread abortWeak0Check0;
	Thread abortWeak0Check1;
	Thread abortWeak0Check2;
	Thread abortWeak0Check3;

	// par1
	Thread servo0__thread;
	Thread servo1__thread;
	Thread servo2__thread;
	Thread servo3__thread;
	Thread servoReactionStartMaster0;
	Thread servoReactionStartSlave1;
	Thread servoReactionStartSlave2;
	Thread servoReactionStartSlave3;
	Thread servoReactionEndMaster0;
	Thread servoReactionEndSlave1;
	Thread servoReactionEndSlave2;
	Thread servoReactionEndSlave3;
	Thread abortStrong2Check0;
	Thread abortStrong2Check1;
	Thread abortStrong2Check2;
	Thread abortStrong2Check3;


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
	struct timespec ts_start__main_0_0;
	struct timespec ts_end__main_0_0;
	int NUM_TO_AVERAGE__main_0_0;
	float summation__main_0_0;
	int i__main_0_0;
	long seconds__main_1_0;
	int nanoseconds__main_1_0;
	float microseconds__main_1_0;
	float runtime__main_1_0;
	float average__main_0_0;
	Shared_terminate__global_0_0 terminate__global_0_0_copy_main_local;
	Shared_isSafe__global_0_0 isSafe__global_0_0_copy_main_local;
	Shared_inputFile__global_0_0 inputFile__global_0_0_copy_main_local;
	Shared_outputFile__global_0_0 outputFile__global_0_0_copy_main_local;
	Shared_radioDownTime__global_0_0 radioDownTime__global_0_0_copy_main_local;
	Shared_spiDownTime__global_0_0 spiDownTime__global_0_0_copy_main_local;

mainParCore0: {
	// Initialise the local copies of shared variables.
	terminate__global_0_0_copy_main_local = terminate__global_0_0;
	isSafe__global_0_0_copy_main_local = isSafe__global_0_0;
	inputFile__global_0_0_copy_main_local = inputFile__global_0_0;
	outputFile__global_0_0_copy_main_local = outputFile__global_0_0;
	radioDownTime__global_0_0_copy_main_local = radioDownTime__global_0_0;
	spiDownTime__global_0_0_copy_main_local = spiDownTime__global_0_0;
	//--------------------------------------------------------------

	printf("Number of iterations to average: ");
	scanf("%d", &NUM_TO_AVERAGE__main_0_0);
	summation__main_0_0 = 0;

	for (i__main_0_0 = 0; i__main_0_0 < NUM_TO_AVERAGE__main_0_0; i__main_0_0++) {
		clock_gettime(CLOCK_MONOTONIC__global_0_0, &ts_start__main_0_0);
		inputFile__global_0_0_copy_main_local.value = fopen("input.dat", "r");
		inputFile__global_0_0_copy_main_local.status = FOREC_SHARED_MODIFIED;
		outputFile__global_0_0_copy_main_local.value = fopen("output.txt", "w");
		outputFile__global_0_0_copy_main_local.status = FOREC_SHARED_MODIFIED;
		terminate__global_0_0_copy_main_local.value = 0;
		terminate__global_0_0_copy_main_local.status = FOREC_SHARED_MODIFIED;
		isSafe__global_0_0_copy_main_local.value = 1;
		isSafe__global_0_0_copy_main_local.status = FOREC_SHARED_MODIFIED;
		servoOutputs__global_0_0[0] = 0.0;
		servoOutputs__global_0_0[1] = 0.0;
		servoOutputs__global_0_0[2] = 0.0;
		servoOutputs__global_0_0[3] = 0.0;
		radioDownTime__global_0_0_copy_main_local.value = 0;
		radioDownTime__global_0_0_copy_main_local.status = FOREC_SHARED_MODIFIED;
		spiDownTime__global_0_0_copy_main_local.value = 0;
		spiDownTime__global_0_0_copy_main_local.status = FOREC_SHARED_MODIFIED;

		while (!terminate__global_0_0_copy_main_local.value) {
			/* abortWeak0 */ {
				// par0(servo__thread, timer__thread, flight__thread, failsafe__thread);
				terminate__global_0_0_copy_main = terminate__global_0_0_copy_main_local;
				terminate__global_0_0.value = terminate__global_0_0_copy_main_local.value;
				isSafe__global_0_0_copy_main = isSafe__global_0_0_copy_main_local;
				isSafe__global_0_0.value = isSafe__global_0_0_copy_main_local.value;
				inputFile__global_0_0_copy_main = inputFile__global_0_0_copy_main_local;
				inputFile__global_0_0.value = inputFile__global_0_0_copy_main_local.value;
				outputFile__global_0_0_copy_main = outputFile__global_0_0_copy_main_local;
				outputFile__global_0_0.value = outputFile__global_0_0_copy_main_local.value;
				radioDownTime__global_0_0_copy_main = radioDownTime__global_0_0_copy_main_local;
				radioDownTime__global_0_0.value = radioDownTime__global_0_0_copy_main_local.value;
				spiDownTime__global_0_0_copy_main = spiDownTime__global_0_0_copy_main_local;
				spiDownTime__global_0_0.value = spiDownTime__global_0_0_copy_main_local.value;
				// Set the par(...) information.
				mainParParent.parId = 0;
				mainParParent.parStatus = FOREC_PAR_ON;

				// Link the threads and handlers together.
				mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
				servo__thread.programCounter = &&servo__thread;
				mainReactionStartMaster0.nextThread = &servo__thread;
				servo__thread.prevThread = &mainReactionStartMaster0;
				servoParHandlerMaster0.programCounter = &&servoParHandlerMaster0;
				servo__thread.nextThread = &servoParHandlerMaster0;
				servoParHandlerMaster0.prevThread = &servo__thread;
				abortWeak0Check0.programCounter = &&abortWeak0Check0;
				servoParHandlerMaster0.nextThread = &abortWeak0Check0;
				abortWeak0Check0.prevThread = &servoParHandlerMaster0;
				mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
				abortWeak0Check0.nextThread = &mainReactionEndMaster0;
				mainReactionEndMaster0.prevThread = &abortWeak0Check0;

				// Link the last and first threads/handlers together.
				mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
				mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

				// Set the join address.
				mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

				// Set the core information.
				mainParCore0.activeThreads = 2;
				mainParCore0.reactionCounter = mainParReactionCounter;

				// Go to the first thread.
				// forec:statement:par:par0:start
				goto servo__thread;
				par0JoinAddress_mainParCore0:;
				// forec:statement:par:par0:end
				terminate__global_0_0_copy_main_local = terminate__global_0_0;
				isSafe__global_0_0_copy_main_local = isSafe__global_0_0;
				inputFile__global_0_0_copy_main_local = inputFile__global_0_0;
				outputFile__global_0_0_copy_main_local = outputFile__global_0_0;
				radioDownTime__global_0_0_copy_main_local = radioDownTime__global_0_0;
				spiDownTime__global_0_0_copy_main_local = spiDownTime__global_0_0;
				abortEnd_abortWeak0:;
			} // when (!isSafe__global_0_0_copy_main_local.value);
			// forec:statement:abort:abortWeak0:scope:end

			// pause;
			// Write the local copy of shared variables back to their global copy.

			terminate__global_0_0 = terminate__global_0_0_copy_main_local;
			isSafe__global_0_0 = isSafe__global_0_0_copy_main_local;
			radioDownTime__global_0_0 = radioDownTime__global_0_0_copy_main_local;
			spiDownTime__global_0_0 = spiDownTime__global_0_0_copy_main_local;			// forec:statement:pause:pause0:start
			// forec:statement:pause:pause0:end
			// Update the values of the used shared variables from their global copy.
			terminate__global_0_0_copy_main_local = terminate__global_0_0;
			isSafe__global_0_0_copy_main_local = isSafe__global_0_0;
			inputFile__global_0_0_copy_main_local = inputFile__global_0_0;
			outputFile__global_0_0_copy_main_local = outputFile__global_0_0;
			radioDownTime__global_0_0_copy_main_local = radioDownTime__global_0_0;
			spiDownTime__global_0_0_copy_main_local = spiDownTime__global_0_0;


			// forec:scheduler:iterationEnd:while_0:start
			// Synchronise end of iteration
			mainParParent.parId = -2;
			mainParParent.parStatus = FOREC_PAR_ON;
			mainParParent.programCounter = &&while_0_endAddress;
			goto mainParHandlerMaster0;
			while_0_endAddress:;
			// forec:scheduler:iterationEnd:while_0:end
		}

		clock_gettime(CLOCK_MONOTONIC__global_0_0, &ts_end__main_0_0);
		fclose(inputFile__global_0_0_copy_main_local.value);
		fclose(outputFile__global_0_0_copy_main_local.value);
		seconds__main_1_0 = ts_end__main_0_0.tv_sec - ts_start__main_0_0.tv_sec;
		nanoseconds__main_1_0 = ts_end__main_0_0.tv_nsec - ts_start__main_0_0.tv_nsec;
		if (nanoseconds__main_1_0 < 0) {
			nanoseconds__main_1_0 += 1000000000;
			seconds__main_1_0--;
		} else {
			// if0
		}
		microseconds__main_1_0 = (float)nanoseconds__main_1_0/1000000000;
		runtime__main_1_0 = (float)seconds__main_1_0 + microseconds__main_1_0;
		summation__main_0_0 += runtime__main_1_0;
		printf("Runtime = %f \n", runtime__main_1_0);
		printf("------###%d###--------\n", i__main_0_0);
	}

	average__main_0_0 = summation__main_0_0/NUM_TO_AVERAGE__main_0_0;
	printf("\nAverage runtime = %f\n\n", average__main_0_0);
	return 0;

	//--------------------------------------------------------------
	// Write the defined shared variables back to their global copy.
	terminate__global_0_0 = terminate__global_0_0_copy_main_local;
	isSafe__global_0_0 = isSafe__global_0_0_copy_main_local;
	inputFile__global_0_0 = inputFile__global_0_0_copy_main_local;
	outputFile__global_0_0 = outputFile__global_0_0_copy_main_local;
	radioDownTime__global_0_0 = radioDownTime__global_0_0_copy_main_local;
	spiDownTime__global_0_0 = spiDownTime__global_0_0_copy_main_local;


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
		while(mainParCore2.status == FOREC_CORE_REACTING);
		while(mainParCore3.status == FOREC_CORE_REACTING);

		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;

		// Set slave cores' status to reacting.
		mainParCore1.status = FOREC_CORE_REACTING;
		mainParCore2.status = FOREC_CORE_REACTING;
		mainParCore3.status = FOREC_CORE_REACTING;

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

	short int parId = servoParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		servoReactionStartMaster0.programCounter = &&servoReactionStartMaster0;
		abortStrong2Check0.programCounter = &&abortStrong2Check0;
		servoReactionStartMaster0.nextThread = &abortStrong2Check0;
		abortStrong2Check0.prevThread = &servoReactionStartMaster0;
		servo0__thread.programCounter = &&servo0__thread;
		abortStrong2Check0.nextThread = &servo0__thread;
		servo0__thread.prevThread = &abortStrong2Check0;
		servoReactionEndMaster0.programCounter = &&servoReactionEndMaster0;
		servo0__thread.nextThread = &servoReactionEndMaster0;
		servoReactionEndMaster0.prevThread = &servo0__thread;

		// Swap the nested par handler with the linked list.
		servoParHandlerMaster0.prevThread -> nextThread = &servoReactionStartMaster0;
		servoReactionStartMaster0.prevThread = servoParHandlerMaster0.prevThread;
		servoReactionEndMaster0.nextThread = servoParHandlerMaster0.nextThread;
		servoParHandlerMaster0.nextThread -> prevThread = &servoReactionEndMaster0;
		
		// Set the core information.
		servoParCore0.activeThreads = 1;
		servoParCore0.reactionCounter = servoParReactionCounter;
		
		// Go to the first thread.
		goto servo0__thread;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.
		while(servoParCore1.status == FOREC_CORE_REACTING);
		while(servoParCore2.status == FOREC_CORE_REACTING);
		while(servoParCore3.status == FOREC_CORE_REACTING);

		servoParParent.parStatus = FOREC_PAR_OFF;
		servoParParent.parId = -1;

		forec_mutex_value_servo = -1;

		// Set slave cores' status to reacting.
		servoParCore1.status = FOREC_CORE_REACTING;
		servoParCore2.status = FOREC_CORE_REACTING;
		servoParCore3.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		servoParReactionCounter++;

		// Return to thread servo.
		goto *servoParParent.programCounter;
	} else if (parId == -3) {
		// Thread termination
		mainParCore0.activeThreads--;
		servoParCore0.activeThreads--;

		// Wait for other cores to complete their reaction.
		while(servoParCore1.status == FOREC_CORE_REACTING);
		while(servoParCore2.status == FOREC_CORE_REACTING);
		while(servoParCore3.status == FOREC_CORE_REACTING);

		servoParParent.parStatus = FOREC_PAR_OFF;
		servoParParent.parId = -1;

		// Set slave cores' status to reacting.
		servoParCore1.status = FOREC_CORE_REACTING;
		servoParCore2.status = FOREC_CORE_REACTING;
		servoParCore3.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		servoParReactionCounter++;

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

		servoParCore0.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (servoParCore0.reactionCounter == servoParReactionCounter);
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
	if (mainParCore0.activeThreads) {
		mainParCore0.status = FOREC_CORE_REACTED;
	} else {
		mainParCore0.status = FOREC_CORE_TERMINATED;
	}
	
	// Wait for other cores to complete their reaction.
	while(mainParCore1.status == FOREC_CORE_REACTING);
	while(mainParCore2.status == FOREC_CORE_REACTING);
	while(mainParCore3.status == FOREC_CORE_REACTING);

	// Reset the mutex.
	forec_mutex_value_servo = -1;

	// Combine shared variables.
	unsigned short int parId = mainParParent.parId;
	if (parId == 0) {
		unsigned short int index;
		unsigned short int numberOfModifiedCopies;

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

		// radioDownTime__global_0_0
		if (radioDownTime__global_0_0_copy_failsafe.status == FOREC_SHARED_MODIFIED) {
			radioDownTime__global_0_0_copy_failsafe.status = FOREC_SHARED_UNMODIFIED;
			radioDownTime__global_0_0.value = radioDownTime__global_0_0_copy_failsafe.value;
		}

		// spiDownTime__global_0_0
		if (spiDownTime__global_0_0_copy_failsafe.status == FOREC_SHARED_MODIFIED) {
			spiDownTime__global_0_0_copy_failsafe.status = FOREC_SHARED_UNMODIFIED;
			spiDownTime__global_0_0.value = spiDownTime__global_0_0_copy_failsafe.value;
		}
	} else {
		// Nothing.
	}

	// Return back to the parent thread if all the cores have terminated.
	if (1 && mainParCore0.status == FOREC_CORE_TERMINATED && mainParCore1.status == FOREC_CORE_TERMINATED && mainParCore2.status == FOREC_CORE_TERMINATED && mainParCore3.status == FOREC_CORE_TERMINATED) {
		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;
		
		// Set slave cores' status to reacting
		mainParCore1.status = FOREC_CORE_REACTING;
		mainParCore2.status = FOREC_CORE_REACTING;
		mainParCore3.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronization.
		mainParReactionCounter++;

		goto *mainParParent.programCounter;
	}

	// Set slave cores' status to reacting
	mainParCore1.status = FOREC_CORE_REACTING;
	mainParCore2.status = FOREC_CORE_REACTING;
	mainParCore3.status = FOREC_CORE_REACTING;

	// Increment the reaction counter for synchronization.
	mainParReactionCounter++;

	// Go to the next thread.
	goto *mainReactionEndMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:main:master:0:end
 
	// forec:scheduler:reactionEnd:servo:master:0:start
	//-- servo:
servoReactionEndMaster0: {
	// Determine if the core can still react or not.
	if (servoParCore0.activeThreads) {
		servoParCore0.status = FOREC_CORE_REACTED;
	} else {
		servoParCore0.status = FOREC_CORE_TERMINATED;
	}
	
	// Wait for other cores to complete their reaction.
	while(servoParCore1.status == FOREC_CORE_REACTING);
	while(servoParCore2.status == FOREC_CORE_REACTING);
	while(servoParCore3.status == FOREC_CORE_REACTING);


	// Return back to the parent thread if all the cores have terminated.
	if (1 && servoParCore0.status == FOREC_CORE_TERMINATED && servoParCore1.status == FOREC_CORE_TERMINATED && servoParCore2.status == FOREC_CORE_TERMINATED && servoParCore3.status == FOREC_CORE_TERMINATED) {
		forec_mutex_value_servo = -1;

		servoParParent.parStatus = FOREC_PAR_OFF;
		servoParParent.parId = -1;
		
		// Set slave cores' status to reacting
		servoParCore1.status = FOREC_CORE_REACTING;
		servoParCore2.status = FOREC_CORE_REACTING;
		servoParCore3.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronization.
		servoParReactionCounter++;

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
	servoParCore1.status = FOREC_CORE_REACTING;
	servoParCore2.status = FOREC_CORE_REACTING;
	servoParCore3.status = FOREC_CORE_REACTING;

	// Increment the reaction counter for synchronization.
	servoParReactionCounter++;

	// Go to the next thread.
	goto *servoReactionEndMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:servo:master:0:end
 


	// Abort check handlers ----------------------------------------
	// forec:scheduler:abortHandler:abortWeak0:0:start
	// abortWeak0 (!isSafe__global_0_0.value)
abortWeak0Check0: {
	// Check the abort condition.
	if (!isSafe__global_0_0.value) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore0.activeThreads = 0;

		// Update the parent thread to resume at the end of the abort scope.
		mainParParent.programCounter = &&abortEnd_abortWeak0;
		
		goto mainReactionEndMaster0;
	}
	
	// Continue to the next thread.
	goto *abortWeak0Check0.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortWeak0:0:end
	// forec:scheduler:abortHandler:abortStrong2:0:start
	// abortStrong2 (terminate__global_0_0.value)
abortStrong2Check0: {
	// Check the abort condition.
	if (terminate__global_0_0.value) {
		// Force the reaction end handler to terminate the par(...).
		servoParCore0.activeThreads = 0;

		// Update the parent thread to resume at the end of the abort scope.
		servoParParent.programCounter = &&abortEnd_abortStrong2;
		
		goto servoReactionEndMaster0;
	}
	
	// Continue to the next thread.
	goto *abortStrong2Check0.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrong2:0:end


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
		servoParHandlerSlave1.programCounter = &&servoParHandlerSlave1;
		mainReactionStartSlave1.nextThread = &servoParHandlerSlave1;
		servoParHandlerSlave1.prevThread = &mainReactionStartSlave1;
		failsafe__thread.programCounter = &&failsafe__thread;
		servoParHandlerSlave1.nextThread = &failsafe__thread;
		failsafe__thread.prevThread = &servoParHandlerSlave1;
		abortWeak0Check1.programCounter = &&abortWeak0Check1;
		failsafe__thread.nextThread = &abortWeak0Check1;
		abortWeak0Check1.prevThread = &failsafe__thread;
		mainReactionEndSlave1.programCounter = &&mainReactionEndSlave1;
		abortWeak0Check1.nextThread = &mainReactionEndSlave1;
		mainReactionEndSlave1.prevThread = &abortWeak0Check1;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave1.nextThread = &mainReactionStartSlave1;
		mainReactionStartSlave1.prevThread = &mainReactionEndSlave1;

		// Set the core information.
		mainParCore1.activeThreads = 2;
		mainParCore1.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto servoParHandlerSlave1;
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
	// forec:scheduler:parHandler:servo:slave:1:start
	//-- Thread servo par(...) handlers
servoParHandlerSlave1: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_servo & 0x80000000) == (unsigned)0x80000000);

	// Check the execution status of the nested par(...)s.
	if (servoParParent.parStatus == FOREC_PAR_OFF) {
		goto *servoParHandlerSlave1.nextThread -> programCounter;
	}

	short int parId = servoParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		servoReactionStartSlave1.programCounter = &&servoReactionStartSlave1;
		abortStrong2Check1.programCounter = &&abortStrong2Check1;
		servoReactionStartSlave1.nextThread = &abortStrong2Check1;
		abortStrong2Check1.prevThread = &servoReactionStartSlave1;
		servo1__thread.programCounter = &&servo1__thread;
		abortStrong2Check1.nextThread = &servo1__thread;
		servo1__thread.prevThread = &abortStrong2Check1;
		servoReactionEndSlave1.programCounter = &&servoReactionEndSlave1;
		servo1__thread.nextThread = &servoReactionEndSlave1;
		servoReactionEndSlave1.prevThread = &servo1__thread;

		// Swap the nested par handler with the linked list.
		servoParHandlerSlave1.prevThread -> nextThread = &servoReactionStartSlave1;
		servoReactionStartSlave1.prevThread = servoParHandlerSlave1.prevThread;
		servoReactionEndSlave1.nextThread = servoParHandlerSlave1.nextThread;
		servoParHandlerSlave1.nextThread -> prevThread = &servoReactionEndSlave1;
		
		// Set the core information.
		servoParCore1.activeThreads = 1;
		servoParCore1.reactionCounter = servoParReactionCounter;
		
		// Go to the first thread.
		goto servo1__thread;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		servoParCore1.reactionCounter = servoParReactionCounter;
		servoParCore1.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (servoParCore1.reactionCounter == servoParReactionCounter);

		// Go to the next thread.
		goto servoParHandlerSlave1;
	} else if (parId == -3) {
		// Thread termination
		mainParCore1.activeThreads--;
		servoParCore1.activeThreads--;

		servoParCore1.reactionCounter = servoParReactionCounter;
		servoParCore1.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (servoParCore1.reactionCounter == servoParReactionCounter);

		// Delete this par(...) handler.
		servoParHandlerSlave1.prevThread -> nextThread = servoParHandlerSlave1.nextThread;
		servoParHandlerSlave1.nextThread -> prevThread = servoParHandlerSlave1.prevThread;
			
		// Go to the next thread.
		goto *servoParHandlerSlave1.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		servoParCore1.reactionCounter = servoParReactionCounter;

		servoParHandlerSlave1.programCounter = &&wrongParId_servoParHandlerSlave1;
		wrongParId_servoParHandlerSlave1:;

		servoParCore1.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (servoParCore1.reactionCounter == servoParReactionCounter);
		servoParCore1.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (servoParParent.parStatus == FOREC_PAR_ON && servoParParent.parId == parId) {
			goto *servoParHandlerSlave1.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		servoParHandlerSlave1.programCounter = &&servoParHandlerSlave1;
		
		goto servoParHandlerSlave1;
	}
	
	// Control should not reach here.
	goto servoParHandlerSlave1;
}
	// forec:scheduler:parHandler:servo:slave:1:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:slave:1:start
	//-- main:
mainReactionStartSlave1: {
	// Go to the next thread.
	goto *mainReactionStartSlave1.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:1:end
 
	// forec:scheduler:reactionStart:servo:slave:1:start
	//-- servo:
servoReactionStartSlave1: {
	// Go to the next thread.
	goto *servoReactionStartSlave1.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:servo:slave:1:end
 


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
 
	// forec:scheduler:reactionEnd:servo:slave:1:start
	//-- servo:
servoReactionEndSlave1: {
	// Determine if the core can still react or not.
	if (servoParCore1.activeThreads) {
		servoParCore1.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (servoParCore1.reactionCounter == servoParReactionCounter);
		servoParCore1.reactionCounter++;
		
		// Continue reacting.
		goto *servoReactionEndSlave1.nextThread -> programCounter;
	} else {
		short int parId = servoParParent.parId;

		servoReactionEndSlave1.programCounter = &&terminated_servoReactionEndSlave1;
		terminated_servoReactionEndSlave1:;
		
		servoParCore1.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (servoParCore1.reactionCounter == servoParReactionCounter);
		servoParCore1.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (servoParParent.parStatus == FOREC_PAR_ON && servoParParent.parId == parId) {
			goto *servoReactionEndSlave1.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		servoReactionStartSlave1.prevThread -> nextThread = &servoParHandlerSlave1;
		servoParHandlerSlave1.prevThread = servoReactionStartSlave1.prevThread;
		servoParHandlerSlave1.nextThread = servoReactionEndSlave1.nextThread;
		servoReactionEndSlave1.nextThread -> prevThread = &servoParHandlerSlave1;
		goto servoParHandlerSlave1;
	}
	
	// Control shouldn't reach here.
	goto servoReactionEndSlave1;
}
	// forec:scheduler:reactionEnd:servo:slave:1:end
 


	// Abort check handlers ----------------------------------------
	// forec:scheduler:abortHandler:abortWeak0:1:start
	// abortWeak0 (!isSafe__global_0_0.value)
abortWeak0Check1: {
	// Check the abort condition.
	if (!isSafe__global_0_0.value) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore1.activeThreads = 0;
		
		goto mainReactionEndSlave1;
	}
	
	// Continue to the next thread.
	goto *abortWeak0Check1.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortWeak0:1:end
	// forec:scheduler:abortHandler:abortStrong2:1:start
	// abortStrong2 (terminate__global_0_0.value)
abortStrong2Check1: {
	// Check the abort condition.
	if (terminate__global_0_0.value) {
		// Force the reaction end handler to terminate the par(...).
		servoParCore1.activeThreads = 0;
		
		goto servoReactionEndSlave1;
	}
	
	// Continue to the next thread.
	goto *abortStrong2Check1.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrong2:1:end

// forec:scheduler:parHandler:main:slave:2:start
/*--------------------------------------------------------------
| Slave core: core2
*-------------------------------------------------------------*/
mainParCore2: {
	// Check the execution status of the root par(...)s.
	while (mainParParent.parStatus == FOREC_PAR_OFF);

	short int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave2.programCounter = &&mainReactionStartSlave2;
		servoParHandlerSlave2.programCounter = &&servoParHandlerSlave2;
		mainReactionStartSlave2.nextThread = &servoParHandlerSlave2;
		servoParHandlerSlave2.prevThread = &mainReactionStartSlave2;
		timer__thread.programCounter = &&timer__thread;
		servoParHandlerSlave2.nextThread = &timer__thread;
		timer__thread.prevThread = &servoParHandlerSlave2;
		abortWeak0Check2.programCounter = &&abortWeak0Check2;
		timer__thread.nextThread = &abortWeak0Check2;
		abortWeak0Check2.prevThread = &timer__thread;
		mainReactionEndSlave2.programCounter = &&mainReactionEndSlave2;
		abortWeak0Check2.nextThread = &mainReactionEndSlave2;
		mainReactionEndSlave2.prevThread = &abortWeak0Check2;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave2.nextThread = &mainReactionStartSlave2;
		mainReactionStartSlave2.prevThread = &mainReactionEndSlave2;

		// Set the core information.
		mainParCore2.activeThreads = 2;
		mainParCore2.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto servoParHandlerSlave2;
		asm("# par0 end");
	} else {
		// Unscheduled par(...)
		mainParCore2.reactionCounter = mainParReactionCounter;
		
		// Wait for the par(...) to terminate.
		do {
			mainParCore2.status = FOREC_CORE_TERMINATED;
			
			// Wait for the next reaction.
			while (mainParCore2.reactionCounter == mainParReactionCounter);
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
	// forec:scheduler:parHandler:servo:slave:2:start
	//-- Thread servo par(...) handlers
servoParHandlerSlave2: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_servo & 0x80000000) == (unsigned)0x80000000);

	// Check the execution status of the nested par(...)s.
	if (servoParParent.parStatus == FOREC_PAR_OFF) {
		goto *servoParHandlerSlave2.nextThread -> programCounter;
	}

	short int parId = servoParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		servoReactionStartSlave2.programCounter = &&servoReactionStartSlave2;
		abortStrong2Check2.programCounter = &&abortStrong2Check2;
		servoReactionStartSlave2.nextThread = &abortStrong2Check2;
		abortStrong2Check2.prevThread = &servoReactionStartSlave2;
		servo2__thread.programCounter = &&servo2__thread;
		abortStrong2Check2.nextThread = &servo2__thread;
		servo2__thread.prevThread = &abortStrong2Check2;
		servoReactionEndSlave2.programCounter = &&servoReactionEndSlave2;
		servo2__thread.nextThread = &servoReactionEndSlave2;
		servoReactionEndSlave2.prevThread = &servo2__thread;

		// Swap the nested par handler with the linked list.
		servoParHandlerSlave2.prevThread -> nextThread = &servoReactionStartSlave2;
		servoReactionStartSlave2.prevThread = servoParHandlerSlave2.prevThread;
		servoReactionEndSlave2.nextThread = servoParHandlerSlave2.nextThread;
		servoParHandlerSlave2.nextThread -> prevThread = &servoReactionEndSlave2;
		
		// Set the core information.
		servoParCore2.activeThreads = 1;
		servoParCore2.reactionCounter = servoParReactionCounter;
		
		// Go to the first thread.
		goto servo2__thread;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		servoParCore2.reactionCounter = servoParReactionCounter;
		servoParCore2.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (servoParCore2.reactionCounter == servoParReactionCounter);

		// Go to the next thread.
		goto servoParHandlerSlave2;
	} else if (parId == -3) {
		// Thread termination
		mainParCore2.activeThreads--;
		servoParCore2.activeThreads--;

		servoParCore2.reactionCounter = servoParReactionCounter;
		servoParCore2.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (servoParCore2.reactionCounter == servoParReactionCounter);

		// Delete this par(...) handler.
		servoParHandlerSlave2.prevThread -> nextThread = servoParHandlerSlave2.nextThread;
		servoParHandlerSlave2.nextThread -> prevThread = servoParHandlerSlave2.prevThread;
			
		// Go to the next thread.
		goto *servoParHandlerSlave2.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		servoParCore2.reactionCounter = servoParReactionCounter;

		servoParHandlerSlave2.programCounter = &&wrongParId_servoParHandlerSlave2;
		wrongParId_servoParHandlerSlave2:;

		servoParCore2.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (servoParCore2.reactionCounter == servoParReactionCounter);
		servoParCore2.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (servoParParent.parStatus == FOREC_PAR_ON && servoParParent.parId == parId) {
			goto *servoParHandlerSlave2.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		servoParHandlerSlave2.programCounter = &&servoParHandlerSlave2;
		
		goto servoParHandlerSlave2;
	}
	
	// Control should not reach here.
	goto servoParHandlerSlave2;
}
	// forec:scheduler:parHandler:servo:slave:2:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:slave:2:start
	//-- main:
mainReactionStartSlave2: {
	// Go to the next thread.
	goto *mainReactionStartSlave2.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:2:end
 
	// forec:scheduler:reactionStart:servo:slave:2:start
	//-- servo:
servoReactionStartSlave2: {
	// Go to the next thread.
	goto *servoReactionStartSlave2.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:servo:slave:2:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:main:slave:2:start
	//-- main:
mainReactionEndSlave2: {
	// Determine if the core can still react or not.
	if (mainParCore2.activeThreads) {
		mainParCore2.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (mainParCore2.reactionCounter == mainParReactionCounter);
		mainParCore2.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave2.nextThread -> programCounter;
	} else {
		short int parId = mainParParent.parId;

		mainReactionEndSlave2.programCounter = &&terminated_mainReactionEndSlave2;
		terminated_mainReactionEndSlave2:;
		
		mainParCore2.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (mainParCore2.reactionCounter == mainParReactionCounter);
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
 
	// forec:scheduler:reactionEnd:servo:slave:2:start
	//-- servo:
servoReactionEndSlave2: {
	// Determine if the core can still react or not.
	if (servoParCore2.activeThreads) {
		servoParCore2.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (servoParCore2.reactionCounter == servoParReactionCounter);
		servoParCore2.reactionCounter++;
		
		// Continue reacting.
		goto *servoReactionEndSlave2.nextThread -> programCounter;
	} else {
		short int parId = servoParParent.parId;

		servoReactionEndSlave2.programCounter = &&terminated_servoReactionEndSlave2;
		terminated_servoReactionEndSlave2:;
		
		servoParCore2.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (servoParCore2.reactionCounter == servoParReactionCounter);
		servoParCore2.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (servoParParent.parStatus == FOREC_PAR_ON && servoParParent.parId == parId) {
			goto *servoReactionEndSlave2.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		servoReactionStartSlave2.prevThread -> nextThread = &servoParHandlerSlave2;
		servoParHandlerSlave2.prevThread = servoReactionStartSlave2.prevThread;
		servoParHandlerSlave2.nextThread = servoReactionEndSlave2.nextThread;
		servoReactionEndSlave2.nextThread -> prevThread = &servoParHandlerSlave2;
		goto servoParHandlerSlave2;
	}
	
	// Control shouldn't reach here.
	goto servoReactionEndSlave2;
}
	// forec:scheduler:reactionEnd:servo:slave:2:end
 


	// Abort check handlers ----------------------------------------
	// forec:scheduler:abortHandler:abortWeak0:2:start
	// abortWeak0 (!isSafe__global_0_0.value)
abortWeak0Check2: {
	// Check the abort condition.
	if (!isSafe__global_0_0.value) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore2.activeThreads = 0;
		
		goto mainReactionEndSlave2;
	}
	
	// Continue to the next thread.
	goto *abortWeak0Check2.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortWeak0:2:end
	// forec:scheduler:abortHandler:abortStrong2:2:start
	// abortStrong2 (terminate__global_0_0.value)
abortStrong2Check2: {
	// Check the abort condition.
	if (terminate__global_0_0.value) {
		// Force the reaction end handler to terminate the par(...).
		servoParCore2.activeThreads = 0;
		
		goto servoReactionEndSlave2;
	}
	
	// Continue to the next thread.
	goto *abortStrong2Check2.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrong2:2:end

// forec:scheduler:parHandler:main:slave:3:start
/*--------------------------------------------------------------
| Slave core: core3
*-------------------------------------------------------------*/
mainParCore3: {
	// Check the execution status of the root par(...)s.
	while (mainParParent.parStatus == FOREC_PAR_OFF);

	short int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave3.programCounter = &&mainReactionStartSlave3;
		servoParHandlerSlave3.programCounter = &&servoParHandlerSlave3;
		mainReactionStartSlave3.nextThread = &servoParHandlerSlave3;
		servoParHandlerSlave3.prevThread = &mainReactionStartSlave3;
		flight__thread.programCounter = &&flight__thread;
		servoParHandlerSlave3.nextThread = &flight__thread;
		flight__thread.prevThread = &servoParHandlerSlave3;
		abortWeak0Check3.programCounter = &&abortWeak0Check3;
		flight__thread.nextThread = &abortWeak0Check3;
		abortWeak0Check3.prevThread = &flight__thread;
		mainReactionEndSlave3.programCounter = &&mainReactionEndSlave3;
		abortWeak0Check3.nextThread = &mainReactionEndSlave3;
		mainReactionEndSlave3.prevThread = &abortWeak0Check3;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave3.nextThread = &mainReactionStartSlave3;
		mainReactionStartSlave3.prevThread = &mainReactionEndSlave3;

		// Set the core information.
		mainParCore3.activeThreads = 2;
		mainParCore3.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto servoParHandlerSlave3;
		asm("# par0 end");
	} else {
		// Unscheduled par(...)
		mainParCore3.reactionCounter = mainParReactionCounter;
		
		// Wait for the par(...) to terminate.
		do {
			mainParCore3.status = FOREC_CORE_TERMINATED;
			
			// Wait for the next reaction.
			while (mainParCore3.reactionCounter == mainParReactionCounter);
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
	// forec:scheduler:parHandler:servo:slave:3:start
	//-- Thread servo par(...) handlers
servoParHandlerSlave3: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_servo & 0x80000000) == (unsigned)0x80000000);

	// Check the execution status of the nested par(...)s.
	if (servoParParent.parStatus == FOREC_PAR_OFF) {
		goto *servoParHandlerSlave3.nextThread -> programCounter;
	}

	short int parId = servoParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		servoReactionStartSlave3.programCounter = &&servoReactionStartSlave3;
		abortStrong2Check3.programCounter = &&abortStrong2Check3;
		servoReactionStartSlave3.nextThread = &abortStrong2Check3;
		abortStrong2Check3.prevThread = &servoReactionStartSlave3;
		servo3__thread.programCounter = &&servo3__thread;
		abortStrong2Check3.nextThread = &servo3__thread;
		servo3__thread.prevThread = &abortStrong2Check3;
		servoReactionEndSlave3.programCounter = &&servoReactionEndSlave3;
		servo3__thread.nextThread = &servoReactionEndSlave3;
		servoReactionEndSlave3.prevThread = &servo3__thread;

		// Swap the nested par handler with the linked list.
		servoParHandlerSlave3.prevThread -> nextThread = &servoReactionStartSlave3;
		servoReactionStartSlave3.prevThread = servoParHandlerSlave3.prevThread;
		servoReactionEndSlave3.nextThread = servoParHandlerSlave3.nextThread;
		servoParHandlerSlave3.nextThread -> prevThread = &servoReactionEndSlave3;
		
		// Set the core information.
		servoParCore3.activeThreads = 1;
		servoParCore3.reactionCounter = servoParReactionCounter;
		
		// Go to the first thread.
		goto servo3__thread;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		servoParCore3.reactionCounter = servoParReactionCounter;
		servoParCore3.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (servoParCore3.reactionCounter == servoParReactionCounter);

		// Go to the next thread.
		goto servoParHandlerSlave3;
	} else if (parId == -3) {
		// Thread termination
		mainParCore3.activeThreads--;
		servoParCore3.activeThreads--;

		servoParCore3.reactionCounter = servoParReactionCounter;
		servoParCore3.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (servoParCore3.reactionCounter == servoParReactionCounter);

		// Delete this par(...) handler.
		servoParHandlerSlave3.prevThread -> nextThread = servoParHandlerSlave3.nextThread;
		servoParHandlerSlave3.nextThread -> prevThread = servoParHandlerSlave3.prevThread;
			
		// Go to the next thread.
		goto *servoParHandlerSlave3.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		servoParCore3.reactionCounter = servoParReactionCounter;

		servoParHandlerSlave3.programCounter = &&wrongParId_servoParHandlerSlave3;
		wrongParId_servoParHandlerSlave3:;

		servoParCore3.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (servoParCore3.reactionCounter == servoParReactionCounter);
		servoParCore3.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (servoParParent.parStatus == FOREC_PAR_ON && servoParParent.parId == parId) {
			goto *servoParHandlerSlave3.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		servoParHandlerSlave3.programCounter = &&servoParHandlerSlave3;
		
		goto servoParHandlerSlave3;
	}
	
	// Control should not reach here.
	goto servoParHandlerSlave3;
}
	// forec:scheduler:parHandler:servo:slave:3:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:slave:3:start
	//-- main:
mainReactionStartSlave3: {
	// Go to the next thread.
	goto *mainReactionStartSlave3.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:3:end
 
	// forec:scheduler:reactionStart:servo:slave:3:start
	//-- servo:
servoReactionStartSlave3: {
	// Go to the next thread.
	goto *servoReactionStartSlave3.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:servo:slave:3:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:main:slave:3:start
	//-- main:
mainReactionEndSlave3: {
	// Determine if the core can still react or not.
	if (mainParCore3.activeThreads) {
		mainParCore3.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (mainParCore3.reactionCounter == mainParReactionCounter);
		mainParCore3.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave3.nextThread -> programCounter;
	} else {
		short int parId = mainParParent.parId;

		mainReactionEndSlave3.programCounter = &&terminated_mainReactionEndSlave3;
		terminated_mainReactionEndSlave3:;
		
		mainParCore3.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (mainParCore3.reactionCounter == mainParReactionCounter);
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
 
	// forec:scheduler:reactionEnd:servo:slave:3:start
	//-- servo:
servoReactionEndSlave3: {
	// Determine if the core can still react or not.
	if (servoParCore3.activeThreads) {
		servoParCore3.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (servoParCore3.reactionCounter == servoParReactionCounter);
		servoParCore3.reactionCounter++;
		
		// Continue reacting.
		goto *servoReactionEndSlave3.nextThread -> programCounter;
	} else {
		short int parId = servoParParent.parId;

		servoReactionEndSlave3.programCounter = &&terminated_servoReactionEndSlave3;
		terminated_servoReactionEndSlave3:;
		
		servoParCore3.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (servoParCore3.reactionCounter == servoParReactionCounter);
		servoParCore3.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (servoParParent.parStatus == FOREC_PAR_ON && servoParParent.parId == parId) {
			goto *servoReactionEndSlave3.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		servoReactionStartSlave3.prevThread -> nextThread = &servoParHandlerSlave3;
		servoParHandlerSlave3.prevThread = servoReactionStartSlave3.prevThread;
		servoParHandlerSlave3.nextThread = servoReactionEndSlave3.nextThread;
		servoReactionEndSlave3.nextThread -> prevThread = &servoParHandlerSlave3;
		goto servoParHandlerSlave3;
	}
	
	// Control shouldn't reach here.
	goto servoReactionEndSlave3;
}
	// forec:scheduler:reactionEnd:servo:slave:3:end
 


	// Abort check handlers ----------------------------------------
	// forec:scheduler:abortHandler:abortWeak0:3:start
	// abortWeak0 (!isSafe__global_0_0.value)
abortWeak0Check3: {
	// Check the abort condition.
	if (!isSafe__global_0_0.value) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore3.activeThreads = 0;
		
		goto mainReactionEndSlave3;
	}
	
	// Continue to the next thread.
	goto *abortWeak0Check3.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortWeak0:3:end
	// forec:scheduler:abortHandler:abortStrong2:3:start
	// abortStrong2 (terminate__global_0_0.value)
abortStrong2Check3: {
	// Check the abort condition.
	if (terminate__global_0_0.value) {
		// Force the reaction end handler to terminate the par(...).
		servoParCore3.activeThreads = 0;
		
		goto servoReactionEndSlave3;
	}
	
	// Continue to the next thread.
	goto *abortStrong2Check3.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrong2:3:end



/*==============================================================
| ForeC threads:
| Threads' code translated into C code.
*=============================================================*/
	// forec:thread:failsafe:start
	/*--------------------------------------------------------------
	| Thread failsafe
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_terminate__global_0_0 terminate__global_0_0_copy_failsafe_local;
	Shared_isSafe__global_0_0 isSafe__global_0_0_copy_failsafe_local;
	Shared_outputFile__global_0_0 outputFile__global_0_0_copy_failsafe_local;
	Shared_radioDownTime__global_0_0 radioDownTime__global_0_0_copy_failsafe_local;
	Shared_spiDownTime__global_0_0 spiDownTime__global_0_0_copy_failsafe_local;

	// Thread body -------------------------------------------------
	failsafe__thread: {
		// Initialise the local copies of shared variables.
		terminate__global_0_0_copy_failsafe_local.value = terminate__global_0_0_copy_main.value;
		terminate__global_0_0_copy_failsafe_local.status = FOREC_SHARED_UNMODIFIED;
		isSafe__global_0_0_copy_failsafe_local.value = isSafe__global_0_0_copy_main.value;
		isSafe__global_0_0_copy_failsafe_local.status = FOREC_SHARED_UNMODIFIED;
		outputFile__global_0_0_copy_failsafe_local.value = outputFile__global_0_0_copy_main.value;
		outputFile__global_0_0_copy_failsafe_local.status = FOREC_SHARED_UNMODIFIED;
		radioDownTime__global_0_0_copy_failsafe_local.value = radioDownTime__global_0_0_copy_main.value;
		radioDownTime__global_0_0_copy_failsafe_local.status = FOREC_SHARED_UNMODIFIED;
		spiDownTime__global_0_0_copy_failsafe_local.value = spiDownTime__global_0_0_copy_main.value;
		spiDownTime__global_0_0_copy_failsafe_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		/* abortStrong4 */ {
			// forec:statement:abort:abortStrong4:start
			if (terminate__global_0_0_copy_failsafe_local.value) {
				goto abortEnd_abortStrong4;
			}
			// forec:statement:abort:abortStrong4:end

			while (1) {
				computation();
				computation();
				computation();
				computation();
				if (radioInput__global_0_0 == INVALID__global_0_0) {
					radioDownTime__global_0_0_copy_failsafe_local.value++;
				} else {
					// ifElse5
					radioDownTime__global_0_0_copy_failsafe_local.value = 0;
					radioDownTime__global_0_0_copy_failsafe_local.status = FOREC_SHARED_MODIFIED;
				}
				computation();
				computation();
				computation();
				computation();
				if (spiInput__global_0_0 == INVALID__global_0_0) {
					spiDownTime__global_0_0_copy_failsafe_local.value++;
				} else {
					// ifElse6
					spiDownTime__global_0_0_copy_failsafe_local.value = 0;
					spiDownTime__global_0_0_copy_failsafe_local.status = FOREC_SHARED_MODIFIED;
				}
				isSafe__global_0_0_copy_failsafe_local.value = (radioDownTime__global_0_0_copy_failsafe_local.value < MAX_DOWN_TIME__global_0_0) || (spiDownTime__global_0_0_copy_failsafe_local.value < MAX_DOWN_TIME__global_0_0);
				isSafe__global_0_0_copy_failsafe_local.status = FOREC_SHARED_MODIFIED;
				fprintf(outputFile__global_0_0_copy_failsafe_local.value, "%d\n", isSafe__global_0_0_copy_failsafe_local.value);

				// pause;
				// Write the local copy of shared variables back to their global copy.

				isSafe__global_0_0_copy_failsafe = isSafe__global_0_0_copy_failsafe_local;
				radioDownTime__global_0_0_copy_failsafe = radioDownTime__global_0_0_copy_failsafe_local;
				spiDownTime__global_0_0_copy_failsafe = spiDownTime__global_0_0_copy_failsafe_local;				// forec:statement:pause:pause4:start
				failsafe__thread.programCounter = &&pause4;
				goto *failsafe__thread.nextThread -> programCounter;
				pause4:;
				// forec:statement:pause:pause4:end
				// Update the values of the used shared variables from their global copy.
				terminate__global_0_0_copy_failsafe_local = terminate__global_0_0;
				isSafe__global_0_0_copy_failsafe_local = isSafe__global_0_0;
				outputFile__global_0_0_copy_failsafe_local = outputFile__global_0_0;
				radioDownTime__global_0_0_copy_failsafe_local = radioDownTime__global_0_0;
				spiDownTime__global_0_0_copy_failsafe_local = spiDownTime__global_0_0;

				// Strong aborts:
				// forec:statement:abort:abortStrong4:start
				if (terminate__global_0_0_copy_failsafe_local.value) {
					goto abortEnd_abortStrong4;
				}
				// forec:statement:abort:abortStrong4:end
			}
			abortEnd_abortStrong4:;
		} // when (terminate__global_0_0_copy_failsafe_local.value);
		// forec:statement:abort:abortStrong4:scope:end

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		isSafe__global_0_0_copy_failsafe = isSafe__global_0_0_copy_failsafe_local;
		radioDownTime__global_0_0_copy_failsafe = radioDownTime__global_0_0_copy_failsafe_local;
		spiDownTime__global_0_0_copy_failsafe = spiDownTime__global_0_0_copy_failsafe_local;

		// forec:scheduler:threadRemove:failsafe:start

		// Delete thread from the linked list and core.
		mainParCore1.activeThreads--;
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
	int mode__flight_0_0;
	Shared_terminate__global_0_0 terminate__global_0_0_copy_flight_local;

	// Thread body -------------------------------------------------
	flight__thread: {
		// Initialise the local copies of shared variables.
		terminate__global_0_0_copy_flight_local.value = terminate__global_0_0_copy_main.value;
		terminate__global_0_0_copy_flight_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		/* abortStrong1 */ {
			// forec:statement:abort:abortStrong1:start
			if (terminate__global_0_0_copy_flight_local.value) {
				goto abortEnd_abortStrong1;
			}
			// forec:statement:abort:abortStrong1:end

			while (1) {
				if (getMode(radioInput__global_0_0) != VALID__global_0_0) {
					mode__flight_0_0 = getMode(radioInput__global_0_0);
				} else {
					// if1
				}
				decision__global_0_0 = autopilot(mode__flight_0_0, radioInput__global_0_0);

				// pause;
				// forec:statement:pause:pause1:start
				flight__thread.programCounter = &&pause1;
				goto *flight__thread.nextThread -> programCounter;
				pause1:;
				// forec:statement:pause:pause1:end
				// Update the values of the used shared variables from their global copy.
				terminate__global_0_0_copy_flight_local = terminate__global_0_0;

				// Strong aborts:
				// forec:statement:abort:abortStrong1:start
				if (terminate__global_0_0_copy_flight_local.value) {
					goto abortEnd_abortStrong1;
				}
				// forec:statement:abort:abortStrong1:end
			}
			abortEnd_abortStrong1:;
		} // when (terminate__global_0_0_copy_flight_local.value);
		// forec:statement:abort:abortStrong1:scope:end

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:flight:start

		// Delete thread from the linked list and core.
		mainParCore3.activeThreads--;
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
	Shared_terminate__global_0_0 terminate__global_0_0_copy_servo_local;

	// Thread body -------------------------------------------------
	servo__thread: {
		// Initialise the local copies of shared variables.
		terminate__global_0_0_copy_servo_local.value = terminate__global_0_0_copy_main.value;
		terminate__global_0_0_copy_servo_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		/* abortStrong2 */ {
			// forec:statement:abort:abortStrong2:start
			if (terminate__global_0_0_copy_servo_local.value) {
				goto abortEnd_abortStrong2;
			}
			// forec:statement:abort:abortStrong2:end

			while (1) {
				// par1(servo0__thread, servo1__thread, servo2__thread, servo3__thread);
				// Set the par(...) information.
				servoParParent.parId = 1;
				servoParParent.parStatus = FOREC_PAR_ON;
				servoParParent.programCounter = &&par1JoinAddress_servoParParent;

				// Remove this thread from the linked list.
				servo__thread.nextThread -> prevThread = servo__thread.prevThread;
				servo__thread.prevThread -> nextThread = servo__thread.nextThread;
				// forec:statement:par:par1:start
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
				// Update the values of the used shared variables from their global copy.
				terminate__global_0_0_copy_servo_local = terminate__global_0_0;

				// Strong aborts:
				// forec:statement:abort:abortStrong2:start
				if (terminate__global_0_0_copy_servo_local.value) {
					goto abortEnd_abortStrong2;
				}
				// forec:statement:abort:abortStrong2:end

				// forec:scheduler:iterationEnd:while_3:start
				// Synchronise end of iteration
				servoParParent.parId = -2;
				servoParParent.parStatus = FOREC_PAR_ON;
				servoParParent.programCounter = &&while_3_endAddress;
				goto servoParHandlerMaster0;
				while_3_endAddress:;
				// forec:scheduler:iterationEnd:while_3:end
			}
			abortEnd_abortStrong2:;
		} // when (terminate__global_0_0_copy_servo_local.value);
		// forec:statement:abort:abortStrong2:scope:end

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
		servoParCore1.activeThreads--;
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
		servoParCore2.activeThreads--;
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
		servoParCore3.activeThreads--;
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
	char newLine__timer_2_0;
	Shared_terminate__global_0_0 terminate__global_0_0_copy_timer_local;
	Shared_inputFile__global_0_0 inputFile__global_0_0_copy_timer_local;

	// Thread body -------------------------------------------------
	timer__thread: {
		// Initialise the local copies of shared variables.
		terminate__global_0_0_copy_timer_local.value = terminate__global_0_0_copy_main.value;
		terminate__global_0_0_copy_timer_local.status = FOREC_SHARED_UNMODIFIED;
		inputFile__global_0_0_copy_timer_local.value = inputFile__global_0_0_copy_main.value;
		inputFile__global_0_0_copy_timer_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		_1Hz__global_0_0 = 0;
		_20Hz__global_0_0 = 0;

		/* abortStrong3 */ {
			// forec:statement:abort:abortStrong3:start
			if (terminate__global_0_0_copy_timer_local.value) {
				goto abortEnd_abortStrong3;
			}
			// forec:statement:abort:abortStrong3:end

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
				newLine__timer_2_0 = fgetc(inputFile__global_0_0_copy_timer_local.value);
				while (newLine__timer_2_0 == '\n' || newLine__timer_2_0 == '\r') {
					newLine__timer_2_0 = fgetc(inputFile__global_0_0_copy_timer_local.value);
					// forec:iteration:while_4:bound:0:10
				}
				ungetc(newLine__timer_2_0, inputFile__global_0_0_copy_timer_local.value);
				if (radioInput__global_0_0 == EOF__global_0_0 || spiInput__global_0_0 == EOF__global_0_0) {
					terminate__global_0_0_copy_timer_local.value = 1;
					terminate__global_0_0_copy_timer_local.status = FOREC_SHARED_MODIFIED;
				} else {
					// if4
				}

				// pause;
				// Write the local copy of shared variables back to their global copy.

				terminate__global_0_0_copy_timer = terminate__global_0_0_copy_timer_local;				// forec:statement:pause:pause3:start
				timer__thread.programCounter = &&pause3;
				goto *timer__thread.nextThread -> programCounter;
				pause3:;
				// forec:statement:pause:pause3:end
				// Update the values of the used shared variables from their global copy.
				terminate__global_0_0_copy_timer_local = terminate__global_0_0;
				inputFile__global_0_0_copy_timer_local = inputFile__global_0_0;

				// Strong aborts:
				// forec:statement:abort:abortStrong3:start
				if (terminate__global_0_0_copy_timer_local.value) {
					goto abortEnd_abortStrong3;
				}
				// forec:statement:abort:abortStrong3:end
			}
			abortEnd_abortStrong3:;
		} // when (terminate__global_0_0_copy_timer_local.value);
		// forec:statement:abort:abortStrong3:scope:end

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		terminate__global_0_0_copy_timer = terminate__global_0_0_copy_timer_local;

		// forec:scheduler:threadRemove:timer:start

		// Delete thread from the linked list and core.
		mainParCore2.activeThreads--;
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
		// forec:iteration:for1_7:bound:1999:1999
	}
}

