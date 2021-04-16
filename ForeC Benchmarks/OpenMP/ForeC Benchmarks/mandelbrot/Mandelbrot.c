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
	unsigned short int status;
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
Shared_ASIZE__global_0_0 ASIZE__global_0_0_copy_display_double0 = {.status = FOREC_SHARED_UNMODIFIED};
// display_double1
Shared_ASIZE__global_0_0 ASIZE__global_0_0_copy_display_double1 = {.status = FOREC_SHARED_UNMODIFIED};
// display_double2
Shared_ASIZE__global_0_0 ASIZE__global_0_0_copy_display_double2 = {.status = FOREC_SHARED_UNMODIFIED};
// display_double3
Shared_ASIZE__global_0_0 ASIZE__global_0_0_copy_display_double3 = {.status = FOREC_SHARED_UNMODIFIED};
// main

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
	Thread display_double0__thread;
	Thread display_double1__thread;
	Thread display_double2__thread;
	Thread display_double3__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionStartSlave1;
	Thread mainReactionStartSlave2;
	Thread mainReactionStartSlave3;
	Thread mainReactionEndMaster0;
	Thread mainReactionEndSlave1;
	Thread mainReactionEndSlave2;
	Thread mainReactionEndSlave3;


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
	long seconds__main_0_0;
	int microseconds__main_0_0;

mainParCore0: {
	// Initialise the local copies of shared variables.
	//--------------------------------------------------------------

	gettimeofday(&startTime__main_0_0, 0);

	// par0(display_double0__thread, display_double1__thread, display_double2__thread, display_double3__thread);
	// Set the par(...) information.
	mainParParent.parId = 0;
	mainParParent.parStatus = FOREC_PAR_ON;

	// Link the threads and handlers together.
	mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
	display_double0__thread.programCounter = &&display_double0__thread;
	mainReactionStartMaster0.nextThread = &display_double0__thread;
	display_double0__thread.prevThread = &mainReactionStartMaster0;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	display_double0__thread.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &display_double0__thread;

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
	return 0;

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
	while(mainParCore2.status == FOREC_CORE_REACTING);
	while(mainParCore3.status == FOREC_CORE_REACTING);

	// Reset the mutex.

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
		display_double1__thread.programCounter = &&display_double1__thread;
		mainReactionStartSlave1.nextThread = &display_double1__thread;
		display_double1__thread.prevThread = &mainReactionStartSlave1;
		mainReactionEndSlave1.programCounter = &&mainReactionEndSlave1;
		display_double1__thread.nextThread = &mainReactionEndSlave1;
		mainReactionEndSlave1.prevThread = &display_double1__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave1.nextThread = &mainReactionStartSlave1;
		mainReactionStartSlave1.prevThread = &mainReactionEndSlave1;

		// Set the core information.
		mainParCore1.activeThreads = 1;
		mainParCore1.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto display_double1__thread;
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
		display_double2__thread.programCounter = &&display_double2__thread;
		mainReactionStartSlave2.nextThread = &display_double2__thread;
		display_double2__thread.prevThread = &mainReactionStartSlave2;
		mainReactionEndSlave2.programCounter = &&mainReactionEndSlave2;
		display_double2__thread.nextThread = &mainReactionEndSlave2;
		mainReactionEndSlave2.prevThread = &display_double2__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave2.nextThread = &mainReactionStartSlave2;
		mainReactionStartSlave2.prevThread = &mainReactionEndSlave2;

		// Set the core information.
		mainParCore2.activeThreads = 1;
		mainParCore2.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto display_double2__thread;
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
 


	// Abort check handlers ----------------------------------------

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
		display_double3__thread.programCounter = &&display_double3__thread;
		mainReactionStartSlave3.nextThread = &display_double3__thread;
		display_double3__thread.prevThread = &mainReactionStartSlave3;
		mainReactionEndSlave3.programCounter = &&mainReactionEndSlave3;
		display_double3__thread.nextThread = &mainReactionEndSlave3;
		mainReactionEndSlave3.prevThread = &display_double3__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave3.nextThread = &mainReactionStartSlave3;
		mainReactionStartSlave3.prevThread = &mainReactionEndSlave3;

		// Set the core information.
		mainParCore3.activeThreads = 1;
		mainParCore3.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto display_double3__thread;
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
	Shared_ASIZE__global_0_0 ASIZE__global_0_0_copy_display_double0_local;

	// Thread body -------------------------------------------------
	display_double0__thread: {
		// Initialise the local copies of shared variables.
		ASIZE__global_0_0_copy_display_double0_local.value = ASIZE__global_0_0.value;
		ASIZE__global_0_0_copy_display_double0_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		xmin__display_double0_0_0 = -2;
		xmax__display_double0_0_0 = 1.0;
		ymin__display_double0_0_0 = -1.5;
		ymax__display_double0_0_0 = 1.5;
		display_double(ASIZE__global_0_0_copy_display_double0_local.value, xmin__display_double0_0_0, xmax__display_double0_0_0, ymin__display_double0_0_0, ymax__display_double0_0_0, 0, 415);

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
	Shared_ASIZE__global_0_0 ASIZE__global_0_0_copy_display_double1_local;

	// Thread body -------------------------------------------------
	display_double1__thread: {
		// Initialise the local copies of shared variables.
		ASIZE__global_0_0_copy_display_double1_local.value = ASIZE__global_0_0.value;
		ASIZE__global_0_0_copy_display_double1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		xmin__display_double1_0_0 = -2;
		xmax__display_double1_0_0 = 1.0;
		ymin__display_double1_0_0 = -1.5;
		ymax__display_double1_0_0 = 1.5;
		display_double(ASIZE__global_0_0_copy_display_double1_local.value, xmin__display_double1_0_0, xmax__display_double1_0_0, ymin__display_double1_0_0, ymax__display_double1_0_0, 415, 85);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:display_double1:start

		// Delete thread from the linked list and core.
		mainParCore1.activeThreads--;
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
	Shared_ASIZE__global_0_0 ASIZE__global_0_0_copy_display_double2_local;

	// Thread body -------------------------------------------------
	display_double2__thread: {
		// Initialise the local copies of shared variables.
		ASIZE__global_0_0_copy_display_double2_local.value = ASIZE__global_0_0.value;
		ASIZE__global_0_0_copy_display_double2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		xmin__display_double2_0_0 = -2;
		xmax__display_double2_0_0 = 1.0;
		ymin__display_double2_0_0 = -1.5;
		ymax__display_double2_0_0 = 1.5;
		display_double(ASIZE__global_0_0_copy_display_double2_local.value, xmin__display_double2_0_0, xmax__display_double2_0_0, ymin__display_double2_0_0, ymax__display_double2_0_0, 500, 85);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:display_double2:start

		// Delete thread from the linked list and core.
		mainParCore2.activeThreads--;
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
	Shared_ASIZE__global_0_0 ASIZE__global_0_0_copy_display_double3_local;

	// Thread body -------------------------------------------------
	display_double3__thread: {
		// Initialise the local copies of shared variables.
		ASIZE__global_0_0_copy_display_double3_local.value = ASIZE__global_0_0.value;
		ASIZE__global_0_0_copy_display_double3_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		xmin__display_double3_0_0 = -2;
		xmax__display_double3_0_0 = 1.0;
		ymin__display_double3_0_0 = -1.5;
		ymax__display_double3_0_0 = 1.5;
		display_double(ASIZE__global_0_0_copy_display_double3_local.value, xmin__display_double3_0_0, xmax__display_double3_0_0, ymin__display_double3_0_0, ymax__display_double3_0_0, 585, 415);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:display_double3:start

		// Delete thread from the linked list and core.
		mainParCore3.activeThreads--;
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

