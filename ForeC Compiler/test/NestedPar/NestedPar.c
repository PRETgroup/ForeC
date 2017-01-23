/*==============================================================
| Hardware architecture specific declarations:
| Cores, mutex and input/output information.
*=============================================================*/
#include <pthread.h>

// Mapping Pthreads to processor cores
pthread_t cores[7];
pthread_attr_t masterCoreAttribute;
pthread_attr_t slaveCoreAttribute;

// ForeC mutexes
unsigned int forec_mutex_value_t0;
unsigned int forec_mutex_value_t1;
unsigned int forec_mutex_value_t2;
unsigned int forec_mutex_value_t3;
unsigned int forec_mutex_value_t4;

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
volatile Core mainParCore4;
volatile Core mainParCore5;
volatile Core mainParCore6;
volatile int mainParReactionCounter;

// Thread t0 with par(...)s
volatile Parent t0ParParent;
volatile Core t0ParCore1;
volatile Core t0ParCore2;
volatile Core t0ParCore3;
volatile Core t0ParCore4;
volatile Core t0ParCore5;
volatile Core t0ParCore6;
volatile int t0ParReactionCounter;

// Thread t1 with par(...)s
volatile Parent t1ParParent;
volatile Core t1ParCore2;
volatile Core t1ParCore3;
volatile Core t1ParCore4;
volatile Core t1ParCore5;
volatile Core t1ParCore6;
volatile int t1ParReactionCounter;

// Thread t2 with par(...)s
volatile Parent t2ParParent;
volatile Core t2ParCore3;
volatile Core t2ParCore4;
volatile Core t2ParCore5;
volatile Core t2ParCore6;
volatile int t2ParReactionCounter;

// Thread t3 with par(...)s
volatile Parent t3ParParent;
volatile Core t3ParCore4;
volatile Core t3ParCore5;
volatile Core t3ParCore6;
volatile int t3ParReactionCounter;

// Thread t4 with par(...)s
volatile Parent t4ParParent;
volatile Core t4ParCore5;
volatile Core t4ParCore6;
volatile int t4ParReactionCounter;


/*==============================================================
| Original global declarations:
| Global declarations in the original program code.
*=============================================================*/
// Original main function
void *forecMain(void *args);

#include <stdio.h>

// thread t0__thread(void);
// thread t1__thread(void);
// thread t2__thread(void);
// thread t3__thread(void);
// thread t4__thread(void);
// thread t5__thread(void);

int counter__global_0_0 = 0;

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// main
// t0
// t1
// t2
// t3
// t4
// t5

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
	mainParCore4.sync = 1;
	mainParCore4.status = FOREC_CORE_REACTING;
	mainParCore5.sync = 1;
	mainParCore5.status = FOREC_CORE_REACTING;
	mainParCore6.sync = 1;
	mainParCore6.status = FOREC_CORE_REACTING;
	mainParReactionCounter = 0;

	// Thread t0 with par(...)s
	t0ParParent.parStatus = FOREC_PAR_OFF;
	t0ParCore1.sync = 1;
	t0ParCore1.status = FOREC_CORE_REACTING;
	t0ParCore2.sync = 1;
	t0ParCore2.status = FOREC_CORE_REACTING;
	t0ParCore3.sync = 1;
	t0ParCore3.status = FOREC_CORE_REACTING;
	t0ParCore4.sync = 1;
	t0ParCore4.status = FOREC_CORE_REACTING;
	t0ParCore5.sync = 1;
	t0ParCore5.status = FOREC_CORE_REACTING;
	t0ParCore6.sync = 1;
	t0ParCore6.status = FOREC_CORE_REACTING;
	t0ParReactionCounter = 0;

	// Thread t1 with par(...)s
	t1ParParent.parStatus = FOREC_PAR_OFF;
	t1ParCore2.sync = 1;
	t1ParCore2.status = FOREC_CORE_REACTING;
	t1ParCore3.sync = 1;
	t1ParCore3.status = FOREC_CORE_REACTING;
	t1ParCore4.sync = 1;
	t1ParCore4.status = FOREC_CORE_REACTING;
	t1ParCore5.sync = 1;
	t1ParCore5.status = FOREC_CORE_REACTING;
	t1ParCore6.sync = 1;
	t1ParCore6.status = FOREC_CORE_REACTING;
	t1ParReactionCounter = 0;

	// Thread t2 with par(...)s
	t2ParParent.parStatus = FOREC_PAR_OFF;
	t2ParCore3.sync = 1;
	t2ParCore3.status = FOREC_CORE_REACTING;
	t2ParCore4.sync = 1;
	t2ParCore4.status = FOREC_CORE_REACTING;
	t2ParCore5.sync = 1;
	t2ParCore5.status = FOREC_CORE_REACTING;
	t2ParCore6.sync = 1;
	t2ParCore6.status = FOREC_CORE_REACTING;
	t2ParReactionCounter = 0;

	// Thread t3 with par(...)s
	t3ParParent.parStatus = FOREC_PAR_OFF;
	t3ParCore4.sync = 1;
	t3ParCore4.status = FOREC_CORE_REACTING;
	t3ParCore5.sync = 1;
	t3ParCore5.status = FOREC_CORE_REACTING;
	t3ParCore6.sync = 1;
	t3ParCore6.status = FOREC_CORE_REACTING;
	t3ParReactionCounter = 0;

	// Thread t4 with par(...)s
	t4ParParent.parStatus = FOREC_PAR_OFF;
	t4ParCore5.sync = 1;
	t4ParCore5.status = FOREC_CORE_REACTING;
	t4ParCore6.sync = 1;
	t4ParCore6.status = FOREC_CORE_REACTING;
	t4ParReactionCounter = 0;


	// Reset ForeC mutex values
	forec_mutex_value_t0 = -1;
	forec_mutex_value_t1 = -1;
	forec_mutex_value_t2 = -1;
	forec_mutex_value_t3 = -1;
	forec_mutex_value_t4 = -1;

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
	Arguments arguments4 = {.coreId = 4, .argc = argc__main_0_0, .argv = argv__main_0_0};
	pthread_create(&cores[4], &slaveCoreAttribute, forecMain, (void *)&arguments4);
	Arguments arguments5 = {.coreId = 5, .argc = argc__main_0_0, .argv = argv__main_0_0};
	pthread_create(&cores[5], &slaveCoreAttribute, forecMain, (void *)&arguments5);
	Arguments arguments6 = {.coreId = 6, .argc = argc__main_0_0, .argv = argv__main_0_0};
	pthread_create(&cores[6], &slaveCoreAttribute, forecMain, (void *)&arguments6);

	// End core execution
	pthread_attr_destroy(&masterCoreAttribute);
	pthread_attr_destroy(&slaveCoreAttribute);
	
	// Program termination
	pthread_join(cores[0], NULL);
	pthread_join(cores[1], NULL);
	pthread_join(cores[2], NULL);
	pthread_join(cores[3], NULL);
	pthread_join(cores[4], NULL);
	pthread_join(cores[5], NULL);
	pthread_join(cores[6], NULL);

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
	Thread mainReactionStartMaster0;
	Thread mainReactionStartSlave1;
	Thread mainReactionStartSlave2;
	Thread mainReactionStartSlave3;
	Thread mainReactionStartSlave4;
	Thread mainReactionStartSlave5;
	Thread mainReactionStartSlave6;
	Thread mainReactionEndMaster0;
	Thread mainReactionEndSlave1;
	Thread mainReactionEndSlave2;
	Thread mainReactionEndSlave3;
	Thread mainReactionEndSlave4;
	Thread mainReactionEndSlave5;
	Thread mainReactionEndSlave6;
	Thread t0ParHandlerMaster1;
	Thread t0ParHandlerSlave2;
	Thread t0ParHandlerSlave3;
	Thread t0ParHandlerSlave4;
	Thread t0ParHandlerSlave5;
	Thread t0ParHandlerSlave6;

	// par1
	Thread t1__thread;
	Thread t0ReactionStartMaster1;
	Thread t0ReactionStartSlave2;
	Thread t0ReactionStartSlave3;
	Thread t0ReactionStartSlave4;
	Thread t0ReactionStartSlave5;
	Thread t0ReactionStartSlave6;
	Thread t0ReactionEndMaster1;
	Thread t0ReactionEndSlave2;
	Thread t0ReactionEndSlave3;
	Thread t0ReactionEndSlave4;
	Thread t0ReactionEndSlave5;
	Thread t0ReactionEndSlave6;
	Thread t1ParHandlerMaster2;
	Thread t1ParHandlerSlave3;
	Thread t1ParHandlerSlave4;
	Thread t1ParHandlerSlave5;
	Thread t1ParHandlerSlave6;

	// par2
	Thread t2__thread;
	Thread t1ReactionStartMaster2;
	Thread t1ReactionStartSlave3;
	Thread t1ReactionStartSlave4;
	Thread t1ReactionStartSlave5;
	Thread t1ReactionStartSlave6;
	Thread t1ReactionEndMaster2;
	Thread t1ReactionEndSlave3;
	Thread t1ReactionEndSlave4;
	Thread t1ReactionEndSlave5;
	Thread t1ReactionEndSlave6;
	Thread t2ParHandlerMaster3;
	Thread t2ParHandlerSlave4;
	Thread t2ParHandlerSlave5;
	Thread t2ParHandlerSlave6;

	// par3
	Thread t3__thread;
	Thread t2ReactionStartMaster3;
	Thread t2ReactionStartSlave4;
	Thread t2ReactionStartSlave5;
	Thread t2ReactionStartSlave6;
	Thread t2ReactionEndMaster3;
	Thread t2ReactionEndSlave4;
	Thread t2ReactionEndSlave5;
	Thread t2ReactionEndSlave6;
	Thread t3ParHandlerMaster4;
	Thread t3ParHandlerSlave5;
	Thread t3ParHandlerSlave6;

	// par4
	Thread t4__thread;
	Thread t3ReactionStartMaster4;
	Thread t3ReactionStartSlave5;
	Thread t3ReactionStartSlave6;
	Thread t3ReactionEndMaster4;
	Thread t3ReactionEndSlave5;
	Thread t3ReactionEndSlave6;
	Thread t4ParHandlerMaster5;
	Thread t4ParHandlerSlave6;

	// par5
	Thread t5__thread;
	Thread t4ReactionStartMaster5;
	Thread t4ReactionStartSlave6;
	Thread t4ReactionEndMaster5;
	Thread t4ReactionEndSlave6;


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

		case (4):
			goto mainParCore4;

		case (5):
			goto mainParCore5;

		case (6):
			goto mainParCore6;

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
	int i__main_0_0;

mainParCore0: {
	// Initialise the local copies of shared variables.
	//--------------------------------------------------------------

	printf("Hello world!\r\n");

	for (i__main_0_0 = 0; i__main_0_0 < 2; ++i__main_0_0) {
		// par0(t0__thread);
		// Set the par(...) information.
		mainParParent.parId = 0;
		mainParParent.parStatus = FOREC_PAR_ON;

		// Link the threads and handlers together.
		mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
		mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
		mainReactionStartMaster0.nextThread = &mainReactionEndMaster0;
		mainReactionEndMaster0.prevThread = &mainReactionStartMaster0;

		// Link the last and first threads/handlers together.
		mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
		mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

		// Set the join address.
		mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

		// Set the core information.
		mainParCore0.activeThreads = 0;
		mainParCore0.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		// forec:statement:par:par0:start
		goto mainReactionEndMaster0;
		par0JoinAddress_mainParCore0:;
		// forec:statement:par:par0:end

		// pause;
		// forec:statement:pause:pause0:start
		// forec:statement:pause:pause0:end


		// forec:scheduler:iterationEnd:for1_0:start
		// Synchronise end of iteration
		mainParParent.parId = -2;
		mainParParent.parStatus = FOREC_PAR_ON;
		mainParParent.programCounter = &&for1_0_endAddress;
		goto mainParHandlerMaster0;
		for1_0_endAddress:;
		// forec:scheduler:iterationEnd:for1_0:end
		// forec:iteration:for1_0:bound:2:2
	}

	printf("Goodbye world!\r\n");

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
		while(mainParCore4.status == FOREC_CORE_REACTING);
		while(mainParCore5.status == FOREC_CORE_REACTING);
		while(mainParCore6.status == FOREC_CORE_REACTING);

		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;

		// Set slave cores' status to reacting.
		mainParCore1.status = FOREC_CORE_REACTING;
		mainParCore2.status = FOREC_CORE_REACTING;
		mainParCore3.status = FOREC_CORE_REACTING;
		mainParCore4.status = FOREC_CORE_REACTING;
		mainParCore5.status = FOREC_CORE_REACTING;
		mainParCore6.status = FOREC_CORE_REACTING;

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
	while(mainParCore4.status == FOREC_CORE_REACTING);
	while(mainParCore5.status == FOREC_CORE_REACTING);
	while(mainParCore6.status == FOREC_CORE_REACTING);

	// Reset the mutex.
	forec_mutex_value_t0 = -1;
	forec_mutex_value_t1 = -1;
	forec_mutex_value_t2 = -1;
	forec_mutex_value_t3 = -1;
	forec_mutex_value_t4 = -1;

	// Return back to the parent thread if all the cores have terminated.
	if (1 && mainParCore0.status == FOREC_CORE_TERMINATED && mainParCore1.status == FOREC_CORE_TERMINATED && mainParCore2.status == FOREC_CORE_TERMINATED && mainParCore3.status == FOREC_CORE_TERMINATED && mainParCore4.status == FOREC_CORE_TERMINATED && mainParCore5.status == FOREC_CORE_TERMINATED && mainParCore6.status == FOREC_CORE_TERMINATED) {
		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;
		
		// Set slave cores' status to reacting
		mainParCore1.status = FOREC_CORE_REACTING;
		mainParCore2.status = FOREC_CORE_REACTING;
		mainParCore3.status = FOREC_CORE_REACTING;
		mainParCore4.status = FOREC_CORE_REACTING;
		mainParCore5.status = FOREC_CORE_REACTING;
		mainParCore6.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronization.
		mainParReactionCounter++;

		goto *mainParParent.programCounter;
	}

	// Set slave cores' status to reacting
	mainParCore1.status = FOREC_CORE_REACTING;
	mainParCore2.status = FOREC_CORE_REACTING;
	mainParCore3.status = FOREC_CORE_REACTING;
	mainParCore4.status = FOREC_CORE_REACTING;
	mainParCore5.status = FOREC_CORE_REACTING;
	mainParCore6.status = FOREC_CORE_REACTING;

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
		t0__thread.programCounter = &&t0__thread;
		mainReactionStartSlave1.nextThread = &t0__thread;
		t0__thread.prevThread = &mainReactionStartSlave1;
		t0ParHandlerMaster1.programCounter = &&t0ParHandlerMaster1;
		t0__thread.nextThread = &t0ParHandlerMaster1;
		t0ParHandlerMaster1.prevThread = &t0__thread;
		mainReactionEndSlave1.programCounter = &&mainReactionEndSlave1;
		t0ParHandlerMaster1.nextThread = &mainReactionEndSlave1;
		mainReactionEndSlave1.prevThread = &t0ParHandlerMaster1;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave1.nextThread = &mainReactionStartSlave1;
		mainReactionStartSlave1.prevThread = &mainReactionEndSlave1;

		// Set the core information.
		mainParCore1.activeThreads = 2;
		mainParCore1.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto t0__thread;
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
	// forec:scheduler:parHandler:t0:master:1:start
	//-- Thread t0 par(...) handlers
t0ParHandlerMaster1: {
	// Check the execution status of the nested par(...)s.
	if (t0ParParent.parStatus == FOREC_PAR_OFF) {
		// Release the mutex.
		forec_mutex_value_t0 &= 0x7fffffff;

		goto *t0ParHandlerMaster1.nextThread -> programCounter;
	}
	// Release the mutex.
	forec_mutex_value_t0 &= 0x7fffffff;

	short int parId = t0ParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		t0ReactionStartMaster1.programCounter = &&t0ReactionStartMaster1;
		t0ReactionEndMaster1.programCounter = &&t0ReactionEndMaster1;
		t0ReactionStartMaster1.nextThread = &t0ReactionEndMaster1;
		t0ReactionEndMaster1.prevThread = &t0ReactionStartMaster1;

		// Swap the nested par handler with the linked list.
		t0ParHandlerMaster1.prevThread -> nextThread = &t0ReactionStartMaster1;
		t0ReactionStartMaster1.prevThread = t0ParHandlerMaster1.prevThread;
		t0ReactionEndMaster1.nextThread = t0ParHandlerMaster1.nextThread;
		t0ParHandlerMaster1.nextThread -> prevThread = &t0ReactionEndMaster1;
		
		// Set the core information.
		t0ParCore1.activeThreads = 0;
		t0ParCore1.reactionCounter = t0ParReactionCounter;
		
		// Go to the first thread.
		goto t0ReactionEndMaster1;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.
		while(t0ParCore2.status == FOREC_CORE_REACTING);
		while(t0ParCore3.status == FOREC_CORE_REACTING);
		while(t0ParCore4.status == FOREC_CORE_REACTING);
		while(t0ParCore5.status == FOREC_CORE_REACTING);
		while(t0ParCore6.status == FOREC_CORE_REACTING);

		t0ParParent.parStatus = FOREC_PAR_OFF;
		t0ParParent.parId = -1;

		forec_mutex_value_t0 = -1;

		// Set slave cores' status to reacting.
		t0ParCore2.status = FOREC_CORE_REACTING;
		t0ParCore3.status = FOREC_CORE_REACTING;
		t0ParCore4.status = FOREC_CORE_REACTING;
		t0ParCore5.status = FOREC_CORE_REACTING;
		t0ParCore6.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		t0ParReactionCounter++;

		// Return to thread t0.
		goto *t0ParParent.programCounter;
	} else if (parId == -3) {
		// Thread termination
		mainParCore1.activeThreads--;
		t0ParCore1.activeThreads--;

		// Wait for other cores to complete their reaction.
		while(t0ParCore2.status == FOREC_CORE_REACTING);
		while(t0ParCore3.status == FOREC_CORE_REACTING);
		while(t0ParCore4.status == FOREC_CORE_REACTING);
		while(t0ParCore5.status == FOREC_CORE_REACTING);
		while(t0ParCore6.status == FOREC_CORE_REACTING);

		t0ParParent.parStatus = FOREC_PAR_OFF;
		t0ParParent.parId = -1;

		// Set slave cores' status to reacting.
		t0ParCore2.status = FOREC_CORE_REACTING;
		t0ParCore3.status = FOREC_CORE_REACTING;
		t0ParCore4.status = FOREC_CORE_REACTING;
		t0ParCore5.status = FOREC_CORE_REACTING;
		t0ParCore6.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		t0ParReactionCounter++;

		// Delete this par(...) handler.
		t0ParHandlerMaster1.prevThread -> nextThread = t0ParHandlerMaster1.nextThread;
		t0ParHandlerMaster1.nextThread -> prevThread = t0ParHandlerMaster1.prevThread;
			
		// Return to thread t0.
		goto *t0ParParent.programCounter;
	} else {
		// Unscheduled par(...)
		t0ParCore1.reactionCounter = t0ParReactionCounter;

		t0ParHandlerMaster1.programCounter = &&wrongParId_t0ParHandlerMaster1;
		wrongParId_t0ParHandlerMaster1:;

		t0ParCore1.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t0ParCore1.reactionCounter == t0ParReactionCounter);
		t0ParCore1.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t0ParParent.parStatus == FOREC_PAR_ON && t0ParParent.parId == parId) {
			goto *t0ParHandlerMaster1.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t0ParHandlerMaster1.programCounter = &&t0ParHandlerMaster1;
		
		goto t0ParHandlerMaster1;
	}
	
	// Control should not reach here.
	goto t0ParHandlerMaster1;
}
	// forec:scheduler:parHandler:t0:master:1:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:slave:1:start
	//-- main:
mainReactionStartSlave1: {
	// Go to the next thread.
	goto *mainReactionStartSlave1.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:1:end
 
	// forec:scheduler:reactionStart:t0:master:1:start
	//-- t0:
t0ReactionStartMaster1: {
	// Go to the next thread.
	goto *t0ReactionStartMaster1.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t0:master:1:end
 


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
 
	// forec:scheduler:reactionEnd:t0:master:1:start
	//-- t0:
t0ReactionEndMaster1: {
	// Determine if the core can still react or not.
	if (t0ParCore1.activeThreads) {
		t0ParCore1.status = FOREC_CORE_REACTED;
	} else {
		t0ParCore1.status = FOREC_CORE_TERMINATED;
	}
	
	// Wait for other cores to complete their reaction.
	while(t0ParCore2.status == FOREC_CORE_REACTING);
	while(t0ParCore3.status == FOREC_CORE_REACTING);
	while(t0ParCore4.status == FOREC_CORE_REACTING);
	while(t0ParCore5.status == FOREC_CORE_REACTING);
	while(t0ParCore6.status == FOREC_CORE_REACTING);


	// Return back to the parent thread if all the cores have terminated.
	if (1 && t0ParCore1.status == FOREC_CORE_TERMINATED && t0ParCore2.status == FOREC_CORE_TERMINATED && t0ParCore3.status == FOREC_CORE_TERMINATED && t0ParCore4.status == FOREC_CORE_TERMINATED && t0ParCore5.status == FOREC_CORE_TERMINATED && t0ParCore6.status == FOREC_CORE_TERMINATED) {
		forec_mutex_value_t0 = -1;

		t0ParParent.parStatus = FOREC_PAR_OFF;
		t0ParParent.parId = -1;
		
		// Set slave cores' status to reacting
		t0ParCore2.status = FOREC_CORE_REACTING;
		t0ParCore3.status = FOREC_CORE_REACTING;
		t0ParCore4.status = FOREC_CORE_REACTING;
		t0ParCore5.status = FOREC_CORE_REACTING;
		t0ParCore6.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronization.
		t0ParReactionCounter++;

		// Swap the reaction (start & end) handlers with (thread t0 & nested par handler).
		t0ReactionStartMaster1.prevThread -> nextThread = &t0__thread;
		t0__thread.prevThread = t0ReactionStartMaster1.prevThread;
		t0__thread.nextThread = &t0ParHandlerMaster1;
		t0ParHandlerMaster1.prevThread = &t0__thread;
		t0ParHandlerMaster1.nextThread = t0ReactionEndMaster1.nextThread;
		t0ReactionEndMaster1.nextThread -> prevThread = &t0ParHandlerMaster1;

		goto *t0ParParent.programCounter;
	}

	// Set slave cores' status to reacting
	t0ParCore2.status = FOREC_CORE_REACTING;
	t0ParCore3.status = FOREC_CORE_REACTING;
	t0ParCore4.status = FOREC_CORE_REACTING;
	t0ParCore5.status = FOREC_CORE_REACTING;
	t0ParCore6.status = FOREC_CORE_REACTING;

	// Increment the reaction counter for synchronization.
	t0ParReactionCounter++;

	// Go to the next thread.
	goto *t0ReactionEndMaster1.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:t0:master:1:end
 


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
		t0ParHandlerSlave2.programCounter = &&t0ParHandlerSlave2;
		mainReactionStartSlave2.nextThread = &t0ParHandlerSlave2;
		t0ParHandlerSlave2.prevThread = &mainReactionStartSlave2;
		mainReactionEndSlave2.programCounter = &&mainReactionEndSlave2;
		t0ParHandlerSlave2.nextThread = &mainReactionEndSlave2;
		mainReactionEndSlave2.prevThread = &t0ParHandlerSlave2;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave2.nextThread = &mainReactionStartSlave2;
		mainReactionStartSlave2.prevThread = &mainReactionEndSlave2;

		// Set the core information.
		mainParCore2.activeThreads = 1;
		mainParCore2.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto t0ParHandlerSlave2;
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
	// forec:scheduler:parHandler:t0:slave:2:start
	//-- Thread t0 par(...) handlers
t0ParHandlerSlave2: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_t0 & 0x80000000) == (unsigned)0x80000000);

	// Check the execution status of the nested par(...)s.
	if (t0ParParent.parStatus == FOREC_PAR_OFF) {
		goto *t0ParHandlerSlave2.nextThread -> programCounter;
	}

	short int parId = t0ParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		t0ReactionStartSlave2.programCounter = &&t0ReactionStartSlave2;
		t1__thread.programCounter = &&t1__thread;
		t0ReactionStartSlave2.nextThread = &t1__thread;
		t1__thread.prevThread = &t0ReactionStartSlave2;
		t1ParHandlerMaster2.programCounter = &&t1ParHandlerMaster2;
		t1__thread.nextThread = &t1ParHandlerMaster2;
		t1ParHandlerMaster2.prevThread = &t1__thread;
		t0ReactionEndSlave2.programCounter = &&t0ReactionEndSlave2;
		t1ParHandlerMaster2.nextThread = &t0ReactionEndSlave2;
		t0ReactionEndSlave2.prevThread = &t1ParHandlerMaster2;

		// Swap the nested par handler with the linked list.
		t0ParHandlerSlave2.prevThread -> nextThread = &t0ReactionStartSlave2;
		t0ReactionStartSlave2.prevThread = t0ParHandlerSlave2.prevThread;
		t0ReactionEndSlave2.nextThread = t0ParHandlerSlave2.nextThread;
		t0ParHandlerSlave2.nextThread -> prevThread = &t0ReactionEndSlave2;
		
		// Set the core information.
		t0ParCore2.activeThreads = 2;
		t0ParCore2.reactionCounter = t0ParReactionCounter;
		
		// Go to the first thread.
		goto t1__thread;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		t0ParCore2.reactionCounter = t0ParReactionCounter;
		t0ParCore2.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t0ParCore2.reactionCounter == t0ParReactionCounter);

		// Go to the next thread.
		goto t0ParHandlerSlave2;
	} else if (parId == -3) {
		// Thread termination
		mainParCore2.activeThreads--;
		t0ParCore2.activeThreads--;

		t0ParCore2.reactionCounter = t0ParReactionCounter;
		t0ParCore2.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t0ParCore2.reactionCounter == t0ParReactionCounter);

		// Delete this par(...) handler.
		t0ParHandlerSlave2.prevThread -> nextThread = t0ParHandlerSlave2.nextThread;
		t0ParHandlerSlave2.nextThread -> prevThread = t0ParHandlerSlave2.prevThread;
			
		// Go to the next thread.
		goto *t0ParHandlerSlave2.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		t0ParCore2.reactionCounter = t0ParReactionCounter;

		t0ParHandlerSlave2.programCounter = &&wrongParId_t0ParHandlerSlave2;
		wrongParId_t0ParHandlerSlave2:;

		t0ParCore2.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t0ParCore2.reactionCounter == t0ParReactionCounter);
		t0ParCore2.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t0ParParent.parStatus == FOREC_PAR_ON && t0ParParent.parId == parId) {
			goto *t0ParHandlerSlave2.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t0ParHandlerSlave2.programCounter = &&t0ParHandlerSlave2;
		
		goto t0ParHandlerSlave2;
	}
	
	// Control should not reach here.
	goto t0ParHandlerSlave2;
}
	// forec:scheduler:parHandler:t0:slave:2:end
 	// forec:scheduler:parHandler:t1:master:2:start
	//-- Thread t1 par(...) handlers
t1ParHandlerMaster2: {
	// Check the execution status of the nested par(...)s.
	if (t1ParParent.parStatus == FOREC_PAR_OFF) {
		// Release the mutex.
		forec_mutex_value_t1 &= 0xbfffffff;

		goto *t1ParHandlerMaster2.nextThread -> programCounter;
	}
	// Release the mutex.
	forec_mutex_value_t1 &= 0xbfffffff;

	short int parId = t1ParParent.parId;

	// Check the par(...) ID.
	if (parId == 2) {
		asm ("# par2 begin");
		// Link the threads and handlers together.
		t1ReactionStartMaster2.programCounter = &&t1ReactionStartMaster2;
		t1ReactionEndMaster2.programCounter = &&t1ReactionEndMaster2;
		t1ReactionStartMaster2.nextThread = &t1ReactionEndMaster2;
		t1ReactionEndMaster2.prevThread = &t1ReactionStartMaster2;

		// Swap the nested par handler with the linked list.
		t1ParHandlerMaster2.prevThread -> nextThread = &t1ReactionStartMaster2;
		t1ReactionStartMaster2.prevThread = t1ParHandlerMaster2.prevThread;
		t1ReactionEndMaster2.nextThread = t1ParHandlerMaster2.nextThread;
		t1ParHandlerMaster2.nextThread -> prevThread = &t1ReactionEndMaster2;
		
		// Set the core information.
		t1ParCore2.activeThreads = 0;
		t1ParCore2.reactionCounter = t1ParReactionCounter;
		
		// Go to the first thread.
		goto t1ReactionEndMaster2;
		asm ("# par2 end");
	} else if (parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.
		while(t1ParCore3.status == FOREC_CORE_REACTING);
		while(t1ParCore4.status == FOREC_CORE_REACTING);
		while(t1ParCore5.status == FOREC_CORE_REACTING);
		while(t1ParCore6.status == FOREC_CORE_REACTING);

		t1ParParent.parStatus = FOREC_PAR_OFF;
		t1ParParent.parId = -1;

		forec_mutex_value_t1 = -1;

		// Set slave cores' status to reacting.
		t1ParCore3.status = FOREC_CORE_REACTING;
		t1ParCore4.status = FOREC_CORE_REACTING;
		t1ParCore5.status = FOREC_CORE_REACTING;
		t1ParCore6.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		t1ParReactionCounter++;

		// Return to thread t1.
		goto *t1ParParent.programCounter;
	} else if (parId == -3) {
		// Thread termination
		t0ParCore2.activeThreads--;
		t1ParCore2.activeThreads--;

		// Wait for other cores to complete their reaction.
		while(t1ParCore3.status == FOREC_CORE_REACTING);
		while(t1ParCore4.status == FOREC_CORE_REACTING);
		while(t1ParCore5.status == FOREC_CORE_REACTING);
		while(t1ParCore6.status == FOREC_CORE_REACTING);

		t1ParParent.parStatus = FOREC_PAR_OFF;
		t1ParParent.parId = -1;

		// Set slave cores' status to reacting.
		t1ParCore3.status = FOREC_CORE_REACTING;
		t1ParCore4.status = FOREC_CORE_REACTING;
		t1ParCore5.status = FOREC_CORE_REACTING;
		t1ParCore6.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		t1ParReactionCounter++;

		// Delete this par(...) handler.
		t1ParHandlerMaster2.prevThread -> nextThread = t1ParHandlerMaster2.nextThread;
		t1ParHandlerMaster2.nextThread -> prevThread = t1ParHandlerMaster2.prevThread;
			
		// Return to thread t1.
		goto *t1ParParent.programCounter;
	} else {
		// Unscheduled par(...)
		t1ParCore2.reactionCounter = t1ParReactionCounter;

		t1ParHandlerMaster2.programCounter = &&wrongParId_t1ParHandlerMaster2;
		wrongParId_t1ParHandlerMaster2:;

		t1ParCore2.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t1ParCore2.reactionCounter == t1ParReactionCounter);
		t1ParCore2.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t1ParParent.parStatus == FOREC_PAR_ON && t1ParParent.parId == parId) {
			goto *t1ParHandlerMaster2.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t1ParHandlerMaster2.programCounter = &&t1ParHandlerMaster2;
		
		goto t1ParHandlerMaster2;
	}
	
	// Control should not reach here.
	goto t1ParHandlerMaster2;
}
	// forec:scheduler:parHandler:t1:master:2:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:slave:2:start
	//-- main:
mainReactionStartSlave2: {
	// Go to the next thread.
	goto *mainReactionStartSlave2.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:2:end
 
	// forec:scheduler:reactionStart:t0:slave:2:start
	//-- t0:
t0ReactionStartSlave2: {
	// Go to the next thread.
	goto *t0ReactionStartSlave2.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t0:slave:2:end
 
	// forec:scheduler:reactionStart:t1:master:2:start
	//-- t1:
t1ReactionStartMaster2: {
	// Go to the next thread.
	goto *t1ReactionStartMaster2.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t1:master:2:end
 


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
 
	// forec:scheduler:reactionEnd:t0:slave:2:start
	//-- t0:
t0ReactionEndSlave2: {
	// Determine if the core can still react or not.
	if (t0ParCore2.activeThreads) {
		t0ParCore2.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (t0ParCore2.reactionCounter == t0ParReactionCounter);
		t0ParCore2.reactionCounter++;
		
		// Continue reacting.
		goto *t0ReactionEndSlave2.nextThread -> programCounter;
	} else {
		short int parId = t0ParParent.parId;

		t0ReactionEndSlave2.programCounter = &&terminated_t0ReactionEndSlave2;
		terminated_t0ReactionEndSlave2:;
		
		t0ParCore2.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (t0ParCore2.reactionCounter == t0ParReactionCounter);
		t0ParCore2.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (t0ParParent.parStatus == FOREC_PAR_ON && t0ParParent.parId == parId) {
			goto *t0ReactionEndSlave2.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		t0ReactionStartSlave2.prevThread -> nextThread = &t0ParHandlerSlave2;
		t0ParHandlerSlave2.prevThread = t0ReactionStartSlave2.prevThread;
		t0ParHandlerSlave2.nextThread = t0ReactionEndSlave2.nextThread;
		t0ReactionEndSlave2.nextThread -> prevThread = &t0ParHandlerSlave2;
		goto t0ParHandlerSlave2;
	}
	
	// Control shouldn't reach here.
	goto t0ReactionEndSlave2;
}
	// forec:scheduler:reactionEnd:t0:slave:2:end
 
	// forec:scheduler:reactionEnd:t1:master:2:start
	//-- t1:
t1ReactionEndMaster2: {
	// Determine if the core can still react or not.
	if (t1ParCore2.activeThreads) {
		t1ParCore2.status = FOREC_CORE_REACTED;
	} else {
		t1ParCore2.status = FOREC_CORE_TERMINATED;
	}
	
	// Wait for other cores to complete their reaction.
	while(t1ParCore3.status == FOREC_CORE_REACTING);
	while(t1ParCore4.status == FOREC_CORE_REACTING);
	while(t1ParCore5.status == FOREC_CORE_REACTING);
	while(t1ParCore6.status == FOREC_CORE_REACTING);


	// Return back to the parent thread if all the cores have terminated.
	if (1 && t1ParCore2.status == FOREC_CORE_TERMINATED && t1ParCore3.status == FOREC_CORE_TERMINATED && t1ParCore4.status == FOREC_CORE_TERMINATED && t1ParCore5.status == FOREC_CORE_TERMINATED && t1ParCore6.status == FOREC_CORE_TERMINATED) {
		forec_mutex_value_t1 = -1;

		t1ParParent.parStatus = FOREC_PAR_OFF;
		t1ParParent.parId = -1;
		
		// Set slave cores' status to reacting
		t1ParCore3.status = FOREC_CORE_REACTING;
		t1ParCore4.status = FOREC_CORE_REACTING;
		t1ParCore5.status = FOREC_CORE_REACTING;
		t1ParCore6.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronization.
		t1ParReactionCounter++;

		// Swap the reaction (start & end) handlers with (thread t1 & nested par handler).
		t1ReactionStartMaster2.prevThread -> nextThread = &t1__thread;
		t1__thread.prevThread = t1ReactionStartMaster2.prevThread;
		t1__thread.nextThread = &t1ParHandlerMaster2;
		t1ParHandlerMaster2.prevThread = &t1__thread;
		t1ParHandlerMaster2.nextThread = t1ReactionEndMaster2.nextThread;
		t1ReactionEndMaster2.nextThread -> prevThread = &t1ParHandlerMaster2;

		goto *t1ParParent.programCounter;
	}

	// Set slave cores' status to reacting
	t1ParCore3.status = FOREC_CORE_REACTING;
	t1ParCore4.status = FOREC_CORE_REACTING;
	t1ParCore5.status = FOREC_CORE_REACTING;
	t1ParCore6.status = FOREC_CORE_REACTING;

	// Increment the reaction counter for synchronization.
	t1ParReactionCounter++;

	// Go to the next thread.
	goto *t1ReactionEndMaster2.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:t1:master:2:end
 


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
		t0ParHandlerSlave3.programCounter = &&t0ParHandlerSlave3;
		mainReactionStartSlave3.nextThread = &t0ParHandlerSlave3;
		t0ParHandlerSlave3.prevThread = &mainReactionStartSlave3;
		mainReactionEndSlave3.programCounter = &&mainReactionEndSlave3;
		t0ParHandlerSlave3.nextThread = &mainReactionEndSlave3;
		mainReactionEndSlave3.prevThread = &t0ParHandlerSlave3;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave3.nextThread = &mainReactionStartSlave3;
		mainReactionStartSlave3.prevThread = &mainReactionEndSlave3;

		// Set the core information.
		mainParCore3.activeThreads = 1;
		mainParCore3.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto t0ParHandlerSlave3;
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
	// forec:scheduler:parHandler:t0:slave:3:start
	//-- Thread t0 par(...) handlers
t0ParHandlerSlave3: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_t0 & 0x80000000) == (unsigned)0x80000000);

	// Check the execution status of the nested par(...)s.
	if (t0ParParent.parStatus == FOREC_PAR_OFF) {
		goto *t0ParHandlerSlave3.nextThread -> programCounter;
	}

	short int parId = t0ParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		t0ReactionStartSlave3.programCounter = &&t0ReactionStartSlave3;
		t1ParHandlerSlave3.programCounter = &&t1ParHandlerSlave3;
		t0ReactionStartSlave3.nextThread = &t1ParHandlerSlave3;
		t1ParHandlerSlave3.prevThread = &t0ReactionStartSlave3;
		t0ReactionEndSlave3.programCounter = &&t0ReactionEndSlave3;
		t1ParHandlerSlave3.nextThread = &t0ReactionEndSlave3;
		t0ReactionEndSlave3.prevThread = &t1ParHandlerSlave3;

		// Swap the nested par handler with the linked list.
		t0ParHandlerSlave3.prevThread -> nextThread = &t0ReactionStartSlave3;
		t0ReactionStartSlave3.prevThread = t0ParHandlerSlave3.prevThread;
		t0ReactionEndSlave3.nextThread = t0ParHandlerSlave3.nextThread;
		t0ParHandlerSlave3.nextThread -> prevThread = &t0ReactionEndSlave3;
		
		// Set the core information.
		t0ParCore3.activeThreads = 1;
		t0ParCore3.reactionCounter = t0ParReactionCounter;
		
		// Go to the first thread.
		goto t1ParHandlerSlave3;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		t0ParCore3.reactionCounter = t0ParReactionCounter;
		t0ParCore3.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t0ParCore3.reactionCounter == t0ParReactionCounter);

		// Go to the next thread.
		goto t0ParHandlerSlave3;
	} else if (parId == -3) {
		// Thread termination
		mainParCore3.activeThreads--;
		t0ParCore3.activeThreads--;

		t0ParCore3.reactionCounter = t0ParReactionCounter;
		t0ParCore3.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t0ParCore3.reactionCounter == t0ParReactionCounter);

		// Delete this par(...) handler.
		t0ParHandlerSlave3.prevThread -> nextThread = t0ParHandlerSlave3.nextThread;
		t0ParHandlerSlave3.nextThread -> prevThread = t0ParHandlerSlave3.prevThread;
			
		// Go to the next thread.
		goto *t0ParHandlerSlave3.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		t0ParCore3.reactionCounter = t0ParReactionCounter;

		t0ParHandlerSlave3.programCounter = &&wrongParId_t0ParHandlerSlave3;
		wrongParId_t0ParHandlerSlave3:;

		t0ParCore3.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t0ParCore3.reactionCounter == t0ParReactionCounter);
		t0ParCore3.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t0ParParent.parStatus == FOREC_PAR_ON && t0ParParent.parId == parId) {
			goto *t0ParHandlerSlave3.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t0ParHandlerSlave3.programCounter = &&t0ParHandlerSlave3;
		
		goto t0ParHandlerSlave3;
	}
	
	// Control should not reach here.
	goto t0ParHandlerSlave3;
}
	// forec:scheduler:parHandler:t0:slave:3:end
 	// forec:scheduler:parHandler:t1:slave:3:start
	//-- Thread t1 par(...) handlers
t1ParHandlerSlave3: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_t1 & 0x40000000) == (unsigned)0x40000000);

	// Check the execution status of the nested par(...)s.
	if (t1ParParent.parStatus == FOREC_PAR_OFF) {
		goto *t1ParHandlerSlave3.nextThread -> programCounter;
	}

	short int parId = t1ParParent.parId;

	// Check the par(...) ID.
	if (parId == 2) {
		asm ("# par2 begin");
		// Link the threads and handlers together.
		t1ReactionStartSlave3.programCounter = &&t1ReactionStartSlave3;
		t2__thread.programCounter = &&t2__thread;
		t1ReactionStartSlave3.nextThread = &t2__thread;
		t2__thread.prevThread = &t1ReactionStartSlave3;
		t2ParHandlerMaster3.programCounter = &&t2ParHandlerMaster3;
		t2__thread.nextThread = &t2ParHandlerMaster3;
		t2ParHandlerMaster3.prevThread = &t2__thread;
		t1ReactionEndSlave3.programCounter = &&t1ReactionEndSlave3;
		t2ParHandlerMaster3.nextThread = &t1ReactionEndSlave3;
		t1ReactionEndSlave3.prevThread = &t2ParHandlerMaster3;

		// Swap the nested par handler with the linked list.
		t1ParHandlerSlave3.prevThread -> nextThread = &t1ReactionStartSlave3;
		t1ReactionStartSlave3.prevThread = t1ParHandlerSlave3.prevThread;
		t1ReactionEndSlave3.nextThread = t1ParHandlerSlave3.nextThread;
		t1ParHandlerSlave3.nextThread -> prevThread = &t1ReactionEndSlave3;
		
		// Set the core information.
		t1ParCore3.activeThreads = 2;
		t1ParCore3.reactionCounter = t1ParReactionCounter;
		
		// Go to the first thread.
		goto t2__thread;
		asm ("# par2 end");
	} else if (parId == -2) {
		// Iteration
		t1ParCore3.reactionCounter = t1ParReactionCounter;
		t1ParCore3.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t1ParCore3.reactionCounter == t1ParReactionCounter);

		// Go to the next thread.
		goto t1ParHandlerSlave3;
	} else if (parId == -3) {
		// Thread termination
		t0ParCore3.activeThreads--;
		t1ParCore3.activeThreads--;

		t1ParCore3.reactionCounter = t1ParReactionCounter;
		t1ParCore3.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t1ParCore3.reactionCounter == t1ParReactionCounter);

		// Delete this par(...) handler.
		t1ParHandlerSlave3.prevThread -> nextThread = t1ParHandlerSlave3.nextThread;
		t1ParHandlerSlave3.nextThread -> prevThread = t1ParHandlerSlave3.prevThread;
			
		// Go to the next thread.
		goto *t1ParHandlerSlave3.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		t1ParCore3.reactionCounter = t1ParReactionCounter;

		t1ParHandlerSlave3.programCounter = &&wrongParId_t1ParHandlerSlave3;
		wrongParId_t1ParHandlerSlave3:;

		t1ParCore3.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t1ParCore3.reactionCounter == t1ParReactionCounter);
		t1ParCore3.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t1ParParent.parStatus == FOREC_PAR_ON && t1ParParent.parId == parId) {
			goto *t1ParHandlerSlave3.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t1ParHandlerSlave3.programCounter = &&t1ParHandlerSlave3;
		
		goto t1ParHandlerSlave3;
	}
	
	// Control should not reach here.
	goto t1ParHandlerSlave3;
}
	// forec:scheduler:parHandler:t1:slave:3:end
 	// forec:scheduler:parHandler:t2:master:3:start
	//-- Thread t2 par(...) handlers
t2ParHandlerMaster3: {
	// Check the execution status of the nested par(...)s.
	if (t2ParParent.parStatus == FOREC_PAR_OFF) {
		// Release the mutex.
		forec_mutex_value_t2 &= 0xdfffffff;

		goto *t2ParHandlerMaster3.nextThread -> programCounter;
	}
	// Release the mutex.
	forec_mutex_value_t2 &= 0xdfffffff;

	short int parId = t2ParParent.parId;

	// Check the par(...) ID.
	if (parId == 3) {
		asm ("# par3 begin");
		// Link the threads and handlers together.
		t2ReactionStartMaster3.programCounter = &&t2ReactionStartMaster3;
		t2ReactionEndMaster3.programCounter = &&t2ReactionEndMaster3;
		t2ReactionStartMaster3.nextThread = &t2ReactionEndMaster3;
		t2ReactionEndMaster3.prevThread = &t2ReactionStartMaster3;

		// Swap the nested par handler with the linked list.
		t2ParHandlerMaster3.prevThread -> nextThread = &t2ReactionStartMaster3;
		t2ReactionStartMaster3.prevThread = t2ParHandlerMaster3.prevThread;
		t2ReactionEndMaster3.nextThread = t2ParHandlerMaster3.nextThread;
		t2ParHandlerMaster3.nextThread -> prevThread = &t2ReactionEndMaster3;
		
		// Set the core information.
		t2ParCore3.activeThreads = 0;
		t2ParCore3.reactionCounter = t2ParReactionCounter;
		
		// Go to the first thread.
		goto t2ReactionEndMaster3;
		asm ("# par3 end");
	} else if (parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.
		while(t2ParCore4.status == FOREC_CORE_REACTING);
		while(t2ParCore5.status == FOREC_CORE_REACTING);
		while(t2ParCore6.status == FOREC_CORE_REACTING);

		t2ParParent.parStatus = FOREC_PAR_OFF;
		t2ParParent.parId = -1;

		forec_mutex_value_t2 = -1;

		// Set slave cores' status to reacting.
		t2ParCore4.status = FOREC_CORE_REACTING;
		t2ParCore5.status = FOREC_CORE_REACTING;
		t2ParCore6.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		t2ParReactionCounter++;

		// Return to thread t2.
		goto *t2ParParent.programCounter;
	} else if (parId == -3) {
		// Thread termination
		t1ParCore3.activeThreads--;
		t2ParCore3.activeThreads--;

		// Wait for other cores to complete their reaction.
		while(t2ParCore4.status == FOREC_CORE_REACTING);
		while(t2ParCore5.status == FOREC_CORE_REACTING);
		while(t2ParCore6.status == FOREC_CORE_REACTING);

		t2ParParent.parStatus = FOREC_PAR_OFF;
		t2ParParent.parId = -1;

		// Set slave cores' status to reacting.
		t2ParCore4.status = FOREC_CORE_REACTING;
		t2ParCore5.status = FOREC_CORE_REACTING;
		t2ParCore6.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		t2ParReactionCounter++;

		// Delete this par(...) handler.
		t2ParHandlerMaster3.prevThread -> nextThread = t2ParHandlerMaster3.nextThread;
		t2ParHandlerMaster3.nextThread -> prevThread = t2ParHandlerMaster3.prevThread;
			
		// Return to thread t2.
		goto *t2ParParent.programCounter;
	} else {
		// Unscheduled par(...)
		t2ParCore3.reactionCounter = t2ParReactionCounter;

		t2ParHandlerMaster3.programCounter = &&wrongParId_t2ParHandlerMaster3;
		wrongParId_t2ParHandlerMaster3:;

		t2ParCore3.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t2ParCore3.reactionCounter == t2ParReactionCounter);
		t2ParCore3.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t2ParParent.parStatus == FOREC_PAR_ON && t2ParParent.parId == parId) {
			goto *t2ParHandlerMaster3.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t2ParHandlerMaster3.programCounter = &&t2ParHandlerMaster3;
		
		goto t2ParHandlerMaster3;
	}
	
	// Control should not reach here.
	goto t2ParHandlerMaster3;
}
	// forec:scheduler:parHandler:t2:master:3:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:slave:3:start
	//-- main:
mainReactionStartSlave3: {
	// Go to the next thread.
	goto *mainReactionStartSlave3.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:3:end
 
	// forec:scheduler:reactionStart:t0:slave:3:start
	//-- t0:
t0ReactionStartSlave3: {
	// Go to the next thread.
	goto *t0ReactionStartSlave3.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t0:slave:3:end
 
	// forec:scheduler:reactionStart:t1:slave:3:start
	//-- t1:
t1ReactionStartSlave3: {
	// Go to the next thread.
	goto *t1ReactionStartSlave3.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t1:slave:3:end
 
	// forec:scheduler:reactionStart:t2:master:3:start
	//-- t2:
t2ReactionStartMaster3: {
	// Go to the next thread.
	goto *t2ReactionStartMaster3.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t2:master:3:end
 


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
 
	// forec:scheduler:reactionEnd:t0:slave:3:start
	//-- t0:
t0ReactionEndSlave3: {
	// Determine if the core can still react or not.
	if (t0ParCore3.activeThreads) {
		t0ParCore3.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (t0ParCore3.reactionCounter == t0ParReactionCounter);
		t0ParCore3.reactionCounter++;
		
		// Continue reacting.
		goto *t0ReactionEndSlave3.nextThread -> programCounter;
	} else {
		short int parId = t0ParParent.parId;

		t0ReactionEndSlave3.programCounter = &&terminated_t0ReactionEndSlave3;
		terminated_t0ReactionEndSlave3:;
		
		t0ParCore3.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (t0ParCore3.reactionCounter == t0ParReactionCounter);
		t0ParCore3.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (t0ParParent.parStatus == FOREC_PAR_ON && t0ParParent.parId == parId) {
			goto *t0ReactionEndSlave3.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		t0ReactionStartSlave3.prevThread -> nextThread = &t0ParHandlerSlave3;
		t0ParHandlerSlave3.prevThread = t0ReactionStartSlave3.prevThread;
		t0ParHandlerSlave3.nextThread = t0ReactionEndSlave3.nextThread;
		t0ReactionEndSlave3.nextThread -> prevThread = &t0ParHandlerSlave3;
		goto t0ParHandlerSlave3;
	}
	
	// Control shouldn't reach here.
	goto t0ReactionEndSlave3;
}
	// forec:scheduler:reactionEnd:t0:slave:3:end
 
	// forec:scheduler:reactionEnd:t1:slave:3:start
	//-- t1:
t1ReactionEndSlave3: {
	// Determine if the core can still react or not.
	if (t1ParCore3.activeThreads) {
		t1ParCore3.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (t1ParCore3.reactionCounter == t1ParReactionCounter);
		t1ParCore3.reactionCounter++;
		
		// Continue reacting.
		goto *t1ReactionEndSlave3.nextThread -> programCounter;
	} else {
		short int parId = t1ParParent.parId;

		t1ReactionEndSlave3.programCounter = &&terminated_t1ReactionEndSlave3;
		terminated_t1ReactionEndSlave3:;
		
		t1ParCore3.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (t1ParCore3.reactionCounter == t1ParReactionCounter);
		t1ParCore3.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (t1ParParent.parStatus == FOREC_PAR_ON && t1ParParent.parId == parId) {
			goto *t1ReactionEndSlave3.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		t1ReactionStartSlave3.prevThread -> nextThread = &t1ParHandlerSlave3;
		t1ParHandlerSlave3.prevThread = t1ReactionStartSlave3.prevThread;
		t1ParHandlerSlave3.nextThread = t1ReactionEndSlave3.nextThread;
		t1ReactionEndSlave3.nextThread -> prevThread = &t1ParHandlerSlave3;
		goto t1ParHandlerSlave3;
	}
	
	// Control shouldn't reach here.
	goto t1ReactionEndSlave3;
}
	// forec:scheduler:reactionEnd:t1:slave:3:end
 
	// forec:scheduler:reactionEnd:t2:master:3:start
	//-- t2:
t2ReactionEndMaster3: {
	// Determine if the core can still react or not.
	if (t2ParCore3.activeThreads) {
		t2ParCore3.status = FOREC_CORE_REACTED;
	} else {
		t2ParCore3.status = FOREC_CORE_TERMINATED;
	}
	
	// Wait for other cores to complete their reaction.
	while(t2ParCore4.status == FOREC_CORE_REACTING);
	while(t2ParCore5.status == FOREC_CORE_REACTING);
	while(t2ParCore6.status == FOREC_CORE_REACTING);


	// Return back to the parent thread if all the cores have terminated.
	if (1 && t2ParCore3.status == FOREC_CORE_TERMINATED && t2ParCore4.status == FOREC_CORE_TERMINATED && t2ParCore5.status == FOREC_CORE_TERMINATED && t2ParCore6.status == FOREC_CORE_TERMINATED) {
		forec_mutex_value_t2 = -1;

		t2ParParent.parStatus = FOREC_PAR_OFF;
		t2ParParent.parId = -1;
		
		// Set slave cores' status to reacting
		t2ParCore4.status = FOREC_CORE_REACTING;
		t2ParCore5.status = FOREC_CORE_REACTING;
		t2ParCore6.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronization.
		t2ParReactionCounter++;

		// Swap the reaction (start & end) handlers with (thread t2 & nested par handler).
		t2ReactionStartMaster3.prevThread -> nextThread = &t2__thread;
		t2__thread.prevThread = t2ReactionStartMaster3.prevThread;
		t2__thread.nextThread = &t2ParHandlerMaster3;
		t2ParHandlerMaster3.prevThread = &t2__thread;
		t2ParHandlerMaster3.nextThread = t2ReactionEndMaster3.nextThread;
		t2ReactionEndMaster3.nextThread -> prevThread = &t2ParHandlerMaster3;

		goto *t2ParParent.programCounter;
	}

	// Set slave cores' status to reacting
	t2ParCore4.status = FOREC_CORE_REACTING;
	t2ParCore5.status = FOREC_CORE_REACTING;
	t2ParCore6.status = FOREC_CORE_REACTING;

	// Increment the reaction counter for synchronization.
	t2ParReactionCounter++;

	// Go to the next thread.
	goto *t2ReactionEndMaster3.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:t2:master:3:end
 


	// Abort check handlers ----------------------------------------

// forec:scheduler:parHandler:main:slave:4:start
/*--------------------------------------------------------------
| Slave core: core4
*-------------------------------------------------------------*/
mainParCore4: {
	// Check the execution status of the root par(...)s.
	while (mainParParent.parStatus == FOREC_PAR_OFF);

	short int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave4.programCounter = &&mainReactionStartSlave4;
		t0ParHandlerSlave4.programCounter = &&t0ParHandlerSlave4;
		mainReactionStartSlave4.nextThread = &t0ParHandlerSlave4;
		t0ParHandlerSlave4.prevThread = &mainReactionStartSlave4;
		mainReactionEndSlave4.programCounter = &&mainReactionEndSlave4;
		t0ParHandlerSlave4.nextThread = &mainReactionEndSlave4;
		mainReactionEndSlave4.prevThread = &t0ParHandlerSlave4;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave4.nextThread = &mainReactionStartSlave4;
		mainReactionStartSlave4.prevThread = &mainReactionEndSlave4;

		// Set the core information.
		mainParCore4.activeThreads = 1;
		mainParCore4.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto t0ParHandlerSlave4;
		asm("# par0 end");
	} else {
		// Unscheduled par(...)
		mainParCore4.reactionCounter = mainParReactionCounter;
		
		// Wait for the par(...) to terminate.
		do {
			mainParCore4.status = FOREC_CORE_TERMINATED;
			
			// Wait for the next reaction.
			while (mainParCore4.reactionCounter == mainParReactionCounter);
			mainParCore4.reactionCounter++;
			
		} while (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId);
		
		// Go back to the top and wait for the next nested par(...) 
		goto mainParCore4;
	}
	
	// Control shouldn't reach here.
	goto mainParCore4;
}
// forec:scheduler:parHandler:main:slave:4:end

	// Nested par(...) handlers ------------------------------------
	// forec:scheduler:parHandler:t0:slave:4:start
	//-- Thread t0 par(...) handlers
t0ParHandlerSlave4: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_t0 & 0x80000000) == (unsigned)0x80000000);

	// Check the execution status of the nested par(...)s.
	if (t0ParParent.parStatus == FOREC_PAR_OFF) {
		goto *t0ParHandlerSlave4.nextThread -> programCounter;
	}

	short int parId = t0ParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		t0ReactionStartSlave4.programCounter = &&t0ReactionStartSlave4;
		t1ParHandlerSlave4.programCounter = &&t1ParHandlerSlave4;
		t0ReactionStartSlave4.nextThread = &t1ParHandlerSlave4;
		t1ParHandlerSlave4.prevThread = &t0ReactionStartSlave4;
		t0ReactionEndSlave4.programCounter = &&t0ReactionEndSlave4;
		t1ParHandlerSlave4.nextThread = &t0ReactionEndSlave4;
		t0ReactionEndSlave4.prevThread = &t1ParHandlerSlave4;

		// Swap the nested par handler with the linked list.
		t0ParHandlerSlave4.prevThread -> nextThread = &t0ReactionStartSlave4;
		t0ReactionStartSlave4.prevThread = t0ParHandlerSlave4.prevThread;
		t0ReactionEndSlave4.nextThread = t0ParHandlerSlave4.nextThread;
		t0ParHandlerSlave4.nextThread -> prevThread = &t0ReactionEndSlave4;
		
		// Set the core information.
		t0ParCore4.activeThreads = 1;
		t0ParCore4.reactionCounter = t0ParReactionCounter;
		
		// Go to the first thread.
		goto t1ParHandlerSlave4;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		t0ParCore4.reactionCounter = t0ParReactionCounter;
		t0ParCore4.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t0ParCore4.reactionCounter == t0ParReactionCounter);

		// Go to the next thread.
		goto t0ParHandlerSlave4;
	} else if (parId == -3) {
		// Thread termination
		mainParCore4.activeThreads--;
		t0ParCore4.activeThreads--;

		t0ParCore4.reactionCounter = t0ParReactionCounter;
		t0ParCore4.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t0ParCore4.reactionCounter == t0ParReactionCounter);

		// Delete this par(...) handler.
		t0ParHandlerSlave4.prevThread -> nextThread = t0ParHandlerSlave4.nextThread;
		t0ParHandlerSlave4.nextThread -> prevThread = t0ParHandlerSlave4.prevThread;
			
		// Go to the next thread.
		goto *t0ParHandlerSlave4.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		t0ParCore4.reactionCounter = t0ParReactionCounter;

		t0ParHandlerSlave4.programCounter = &&wrongParId_t0ParHandlerSlave4;
		wrongParId_t0ParHandlerSlave4:;

		t0ParCore4.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t0ParCore4.reactionCounter == t0ParReactionCounter);
		t0ParCore4.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t0ParParent.parStatus == FOREC_PAR_ON && t0ParParent.parId == parId) {
			goto *t0ParHandlerSlave4.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t0ParHandlerSlave4.programCounter = &&t0ParHandlerSlave4;
		
		goto t0ParHandlerSlave4;
	}
	
	// Control should not reach here.
	goto t0ParHandlerSlave4;
}
	// forec:scheduler:parHandler:t0:slave:4:end
 	// forec:scheduler:parHandler:t1:slave:4:start
	//-- Thread t1 par(...) handlers
t1ParHandlerSlave4: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_t1 & 0x40000000) == (unsigned)0x40000000);

	// Check the execution status of the nested par(...)s.
	if (t1ParParent.parStatus == FOREC_PAR_OFF) {
		goto *t1ParHandlerSlave4.nextThread -> programCounter;
	}

	short int parId = t1ParParent.parId;

	// Check the par(...) ID.
	if (parId == 2) {
		asm ("# par2 begin");
		// Link the threads and handlers together.
		t1ReactionStartSlave4.programCounter = &&t1ReactionStartSlave4;
		t2ParHandlerSlave4.programCounter = &&t2ParHandlerSlave4;
		t1ReactionStartSlave4.nextThread = &t2ParHandlerSlave4;
		t2ParHandlerSlave4.prevThread = &t1ReactionStartSlave4;
		t1ReactionEndSlave4.programCounter = &&t1ReactionEndSlave4;
		t2ParHandlerSlave4.nextThread = &t1ReactionEndSlave4;
		t1ReactionEndSlave4.prevThread = &t2ParHandlerSlave4;

		// Swap the nested par handler with the linked list.
		t1ParHandlerSlave4.prevThread -> nextThread = &t1ReactionStartSlave4;
		t1ReactionStartSlave4.prevThread = t1ParHandlerSlave4.prevThread;
		t1ReactionEndSlave4.nextThread = t1ParHandlerSlave4.nextThread;
		t1ParHandlerSlave4.nextThread -> prevThread = &t1ReactionEndSlave4;
		
		// Set the core information.
		t1ParCore4.activeThreads = 1;
		t1ParCore4.reactionCounter = t1ParReactionCounter;
		
		// Go to the first thread.
		goto t2ParHandlerSlave4;
		asm ("# par2 end");
	} else if (parId == -2) {
		// Iteration
		t1ParCore4.reactionCounter = t1ParReactionCounter;
		t1ParCore4.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t1ParCore4.reactionCounter == t1ParReactionCounter);

		// Go to the next thread.
		goto t1ParHandlerSlave4;
	} else if (parId == -3) {
		// Thread termination
		t0ParCore4.activeThreads--;
		t1ParCore4.activeThreads--;

		t1ParCore4.reactionCounter = t1ParReactionCounter;
		t1ParCore4.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t1ParCore4.reactionCounter == t1ParReactionCounter);

		// Delete this par(...) handler.
		t1ParHandlerSlave4.prevThread -> nextThread = t1ParHandlerSlave4.nextThread;
		t1ParHandlerSlave4.nextThread -> prevThread = t1ParHandlerSlave4.prevThread;
			
		// Go to the next thread.
		goto *t1ParHandlerSlave4.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		t1ParCore4.reactionCounter = t1ParReactionCounter;

		t1ParHandlerSlave4.programCounter = &&wrongParId_t1ParHandlerSlave4;
		wrongParId_t1ParHandlerSlave4:;

		t1ParCore4.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t1ParCore4.reactionCounter == t1ParReactionCounter);
		t1ParCore4.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t1ParParent.parStatus == FOREC_PAR_ON && t1ParParent.parId == parId) {
			goto *t1ParHandlerSlave4.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t1ParHandlerSlave4.programCounter = &&t1ParHandlerSlave4;
		
		goto t1ParHandlerSlave4;
	}
	
	// Control should not reach here.
	goto t1ParHandlerSlave4;
}
	// forec:scheduler:parHandler:t1:slave:4:end
 	// forec:scheduler:parHandler:t2:slave:4:start
	//-- Thread t2 par(...) handlers
t2ParHandlerSlave4: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_t2 & 0x20000000) == (unsigned)0x20000000);

	// Check the execution status of the nested par(...)s.
	if (t2ParParent.parStatus == FOREC_PAR_OFF) {
		goto *t2ParHandlerSlave4.nextThread -> programCounter;
	}

	short int parId = t2ParParent.parId;

	// Check the par(...) ID.
	if (parId == 3) {
		asm ("# par3 begin");
		// Link the threads and handlers together.
		t2ReactionStartSlave4.programCounter = &&t2ReactionStartSlave4;
		t3__thread.programCounter = &&t3__thread;
		t2ReactionStartSlave4.nextThread = &t3__thread;
		t3__thread.prevThread = &t2ReactionStartSlave4;
		t3ParHandlerMaster4.programCounter = &&t3ParHandlerMaster4;
		t3__thread.nextThread = &t3ParHandlerMaster4;
		t3ParHandlerMaster4.prevThread = &t3__thread;
		t2ReactionEndSlave4.programCounter = &&t2ReactionEndSlave4;
		t3ParHandlerMaster4.nextThread = &t2ReactionEndSlave4;
		t2ReactionEndSlave4.prevThread = &t3ParHandlerMaster4;

		// Swap the nested par handler with the linked list.
		t2ParHandlerSlave4.prevThread -> nextThread = &t2ReactionStartSlave4;
		t2ReactionStartSlave4.prevThread = t2ParHandlerSlave4.prevThread;
		t2ReactionEndSlave4.nextThread = t2ParHandlerSlave4.nextThread;
		t2ParHandlerSlave4.nextThread -> prevThread = &t2ReactionEndSlave4;
		
		// Set the core information.
		t2ParCore4.activeThreads = 2;
		t2ParCore4.reactionCounter = t2ParReactionCounter;
		
		// Go to the first thread.
		goto t3__thread;
		asm ("# par3 end");
	} else if (parId == -2) {
		// Iteration
		t2ParCore4.reactionCounter = t2ParReactionCounter;
		t2ParCore4.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t2ParCore4.reactionCounter == t2ParReactionCounter);

		// Go to the next thread.
		goto t2ParHandlerSlave4;
	} else if (parId == -3) {
		// Thread termination
		t1ParCore4.activeThreads--;
		t2ParCore4.activeThreads--;

		t2ParCore4.reactionCounter = t2ParReactionCounter;
		t2ParCore4.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t2ParCore4.reactionCounter == t2ParReactionCounter);

		// Delete this par(...) handler.
		t2ParHandlerSlave4.prevThread -> nextThread = t2ParHandlerSlave4.nextThread;
		t2ParHandlerSlave4.nextThread -> prevThread = t2ParHandlerSlave4.prevThread;
			
		// Go to the next thread.
		goto *t2ParHandlerSlave4.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		t2ParCore4.reactionCounter = t2ParReactionCounter;

		t2ParHandlerSlave4.programCounter = &&wrongParId_t2ParHandlerSlave4;
		wrongParId_t2ParHandlerSlave4:;

		t2ParCore4.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t2ParCore4.reactionCounter == t2ParReactionCounter);
		t2ParCore4.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t2ParParent.parStatus == FOREC_PAR_ON && t2ParParent.parId == parId) {
			goto *t2ParHandlerSlave4.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t2ParHandlerSlave4.programCounter = &&t2ParHandlerSlave4;
		
		goto t2ParHandlerSlave4;
	}
	
	// Control should not reach here.
	goto t2ParHandlerSlave4;
}
	// forec:scheduler:parHandler:t2:slave:4:end
 	// forec:scheduler:parHandler:t3:master:4:start
	//-- Thread t3 par(...) handlers
t3ParHandlerMaster4: {
	// Check the execution status of the nested par(...)s.
	if (t3ParParent.parStatus == FOREC_PAR_OFF) {
		// Release the mutex.
		forec_mutex_value_t3 &= 0xefffffff;

		goto *t3ParHandlerMaster4.nextThread -> programCounter;
	}
	// Release the mutex.
	forec_mutex_value_t3 &= 0xefffffff;

	short int parId = t3ParParent.parId;

	// Check the par(...) ID.
	if (parId == 4) {
		asm ("# par4 begin");
		// Link the threads and handlers together.
		t3ReactionStartMaster4.programCounter = &&t3ReactionStartMaster4;
		t3ReactionEndMaster4.programCounter = &&t3ReactionEndMaster4;
		t3ReactionStartMaster4.nextThread = &t3ReactionEndMaster4;
		t3ReactionEndMaster4.prevThread = &t3ReactionStartMaster4;

		// Swap the nested par handler with the linked list.
		t3ParHandlerMaster4.prevThread -> nextThread = &t3ReactionStartMaster4;
		t3ReactionStartMaster4.prevThread = t3ParHandlerMaster4.prevThread;
		t3ReactionEndMaster4.nextThread = t3ParHandlerMaster4.nextThread;
		t3ParHandlerMaster4.nextThread -> prevThread = &t3ReactionEndMaster4;
		
		// Set the core information.
		t3ParCore4.activeThreads = 0;
		t3ParCore4.reactionCounter = t3ParReactionCounter;
		
		// Go to the first thread.
		goto t3ReactionEndMaster4;
		asm ("# par4 end");
	} else if (parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.
		while(t3ParCore5.status == FOREC_CORE_REACTING);
		while(t3ParCore6.status == FOREC_CORE_REACTING);

		t3ParParent.parStatus = FOREC_PAR_OFF;
		t3ParParent.parId = -1;

		forec_mutex_value_t3 = -1;

		// Set slave cores' status to reacting.
		t3ParCore5.status = FOREC_CORE_REACTING;
		t3ParCore6.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		t3ParReactionCounter++;

		// Return to thread t3.
		goto *t3ParParent.programCounter;
	} else if (parId == -3) {
		// Thread termination
		t2ParCore4.activeThreads--;
		t3ParCore4.activeThreads--;

		// Wait for other cores to complete their reaction.
		while(t3ParCore5.status == FOREC_CORE_REACTING);
		while(t3ParCore6.status == FOREC_CORE_REACTING);

		t3ParParent.parStatus = FOREC_PAR_OFF;
		t3ParParent.parId = -1;

		// Set slave cores' status to reacting.
		t3ParCore5.status = FOREC_CORE_REACTING;
		t3ParCore6.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		t3ParReactionCounter++;

		// Delete this par(...) handler.
		t3ParHandlerMaster4.prevThread -> nextThread = t3ParHandlerMaster4.nextThread;
		t3ParHandlerMaster4.nextThread -> prevThread = t3ParHandlerMaster4.prevThread;
			
		// Return to thread t3.
		goto *t3ParParent.programCounter;
	} else {
		// Unscheduled par(...)
		t3ParCore4.reactionCounter = t3ParReactionCounter;

		t3ParHandlerMaster4.programCounter = &&wrongParId_t3ParHandlerMaster4;
		wrongParId_t3ParHandlerMaster4:;

		t3ParCore4.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t3ParCore4.reactionCounter == t3ParReactionCounter);
		t3ParCore4.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t3ParParent.parStatus == FOREC_PAR_ON && t3ParParent.parId == parId) {
			goto *t3ParHandlerMaster4.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t3ParHandlerMaster4.programCounter = &&t3ParHandlerMaster4;
		
		goto t3ParHandlerMaster4;
	}
	
	// Control should not reach here.
	goto t3ParHandlerMaster4;
}
	// forec:scheduler:parHandler:t3:master:4:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:slave:4:start
	//-- main:
mainReactionStartSlave4: {
	// Go to the next thread.
	goto *mainReactionStartSlave4.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:4:end
 
	// forec:scheduler:reactionStart:t0:slave:4:start
	//-- t0:
t0ReactionStartSlave4: {
	// Go to the next thread.
	goto *t0ReactionStartSlave4.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t0:slave:4:end
 
	// forec:scheduler:reactionStart:t1:slave:4:start
	//-- t1:
t1ReactionStartSlave4: {
	// Go to the next thread.
	goto *t1ReactionStartSlave4.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t1:slave:4:end
 
	// forec:scheduler:reactionStart:t2:slave:4:start
	//-- t2:
t2ReactionStartSlave4: {
	// Go to the next thread.
	goto *t2ReactionStartSlave4.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t2:slave:4:end
 
	// forec:scheduler:reactionStart:t3:master:4:start
	//-- t3:
t3ReactionStartMaster4: {
	// Go to the next thread.
	goto *t3ReactionStartMaster4.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t3:master:4:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:main:slave:4:start
	//-- main:
mainReactionEndSlave4: {
	// Determine if the core can still react or not.
	if (mainParCore4.activeThreads) {
		mainParCore4.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (mainParCore4.reactionCounter == mainParReactionCounter);
		mainParCore4.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave4.nextThread -> programCounter;
	} else {
		short int parId = mainParParent.parId;

		mainReactionEndSlave4.programCounter = &&terminated_mainReactionEndSlave4;
		terminated_mainReactionEndSlave4:;
		
		mainParCore4.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (mainParCore4.reactionCounter == mainParReactionCounter);
		mainParCore4.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId) {
			goto *mainReactionEndSlave4.nextThread -> programCounter;
		}

		goto mainParCore4;
	}
	
	// Control shouldn't reach here.
	goto mainReactionEndSlave4;
}
	// forec:scheduler:reactionEnd:main:slave:4:end
 
	// forec:scheduler:reactionEnd:t0:slave:4:start
	//-- t0:
t0ReactionEndSlave4: {
	// Determine if the core can still react or not.
	if (t0ParCore4.activeThreads) {
		t0ParCore4.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (t0ParCore4.reactionCounter == t0ParReactionCounter);
		t0ParCore4.reactionCounter++;
		
		// Continue reacting.
		goto *t0ReactionEndSlave4.nextThread -> programCounter;
	} else {
		short int parId = t0ParParent.parId;

		t0ReactionEndSlave4.programCounter = &&terminated_t0ReactionEndSlave4;
		terminated_t0ReactionEndSlave4:;
		
		t0ParCore4.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (t0ParCore4.reactionCounter == t0ParReactionCounter);
		t0ParCore4.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (t0ParParent.parStatus == FOREC_PAR_ON && t0ParParent.parId == parId) {
			goto *t0ReactionEndSlave4.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		t0ReactionStartSlave4.prevThread -> nextThread = &t0ParHandlerSlave4;
		t0ParHandlerSlave4.prevThread = t0ReactionStartSlave4.prevThread;
		t0ParHandlerSlave4.nextThread = t0ReactionEndSlave4.nextThread;
		t0ReactionEndSlave4.nextThread -> prevThread = &t0ParHandlerSlave4;
		goto t0ParHandlerSlave4;
	}
	
	// Control shouldn't reach here.
	goto t0ReactionEndSlave4;
}
	// forec:scheduler:reactionEnd:t0:slave:4:end
 
	// forec:scheduler:reactionEnd:t1:slave:4:start
	//-- t1:
t1ReactionEndSlave4: {
	// Determine if the core can still react or not.
	if (t1ParCore4.activeThreads) {
		t1ParCore4.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (t1ParCore4.reactionCounter == t1ParReactionCounter);
		t1ParCore4.reactionCounter++;
		
		// Continue reacting.
		goto *t1ReactionEndSlave4.nextThread -> programCounter;
	} else {
		short int parId = t1ParParent.parId;

		t1ReactionEndSlave4.programCounter = &&terminated_t1ReactionEndSlave4;
		terminated_t1ReactionEndSlave4:;
		
		t1ParCore4.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (t1ParCore4.reactionCounter == t1ParReactionCounter);
		t1ParCore4.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (t1ParParent.parStatus == FOREC_PAR_ON && t1ParParent.parId == parId) {
			goto *t1ReactionEndSlave4.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		t1ReactionStartSlave4.prevThread -> nextThread = &t1ParHandlerSlave4;
		t1ParHandlerSlave4.prevThread = t1ReactionStartSlave4.prevThread;
		t1ParHandlerSlave4.nextThread = t1ReactionEndSlave4.nextThread;
		t1ReactionEndSlave4.nextThread -> prevThread = &t1ParHandlerSlave4;
		goto t1ParHandlerSlave4;
	}
	
	// Control shouldn't reach here.
	goto t1ReactionEndSlave4;
}
	// forec:scheduler:reactionEnd:t1:slave:4:end
 
	// forec:scheduler:reactionEnd:t2:slave:4:start
	//-- t2:
t2ReactionEndSlave4: {
	// Determine if the core can still react or not.
	if (t2ParCore4.activeThreads) {
		t2ParCore4.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (t2ParCore4.reactionCounter == t2ParReactionCounter);
		t2ParCore4.reactionCounter++;
		
		// Continue reacting.
		goto *t2ReactionEndSlave4.nextThread -> programCounter;
	} else {
		short int parId = t2ParParent.parId;

		t2ReactionEndSlave4.programCounter = &&terminated_t2ReactionEndSlave4;
		terminated_t2ReactionEndSlave4:;
		
		t2ParCore4.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (t2ParCore4.reactionCounter == t2ParReactionCounter);
		t2ParCore4.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (t2ParParent.parStatus == FOREC_PAR_ON && t2ParParent.parId == parId) {
			goto *t2ReactionEndSlave4.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		t2ReactionStartSlave4.prevThread -> nextThread = &t2ParHandlerSlave4;
		t2ParHandlerSlave4.prevThread = t2ReactionStartSlave4.prevThread;
		t2ParHandlerSlave4.nextThread = t2ReactionEndSlave4.nextThread;
		t2ReactionEndSlave4.nextThread -> prevThread = &t2ParHandlerSlave4;
		goto t2ParHandlerSlave4;
	}
	
	// Control shouldn't reach here.
	goto t2ReactionEndSlave4;
}
	// forec:scheduler:reactionEnd:t2:slave:4:end
 
	// forec:scheduler:reactionEnd:t3:master:4:start
	//-- t3:
t3ReactionEndMaster4: {
	// Determine if the core can still react or not.
	if (t3ParCore4.activeThreads) {
		t3ParCore4.status = FOREC_CORE_REACTED;
	} else {
		t3ParCore4.status = FOREC_CORE_TERMINATED;
	}
	
	// Wait for other cores to complete their reaction.
	while(t3ParCore5.status == FOREC_CORE_REACTING);
	while(t3ParCore6.status == FOREC_CORE_REACTING);


	// Return back to the parent thread if all the cores have terminated.
	if (1 && t3ParCore4.status == FOREC_CORE_TERMINATED && t3ParCore5.status == FOREC_CORE_TERMINATED && t3ParCore6.status == FOREC_CORE_TERMINATED) {
		forec_mutex_value_t3 = -1;

		t3ParParent.parStatus = FOREC_PAR_OFF;
		t3ParParent.parId = -1;
		
		// Set slave cores' status to reacting
		t3ParCore5.status = FOREC_CORE_REACTING;
		t3ParCore6.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronization.
		t3ParReactionCounter++;

		// Swap the reaction (start & end) handlers with (thread t3 & nested par handler).
		t3ReactionStartMaster4.prevThread -> nextThread = &t3__thread;
		t3__thread.prevThread = t3ReactionStartMaster4.prevThread;
		t3__thread.nextThread = &t3ParHandlerMaster4;
		t3ParHandlerMaster4.prevThread = &t3__thread;
		t3ParHandlerMaster4.nextThread = t3ReactionEndMaster4.nextThread;
		t3ReactionEndMaster4.nextThread -> prevThread = &t3ParHandlerMaster4;

		goto *t3ParParent.programCounter;
	}

	// Set slave cores' status to reacting
	t3ParCore5.status = FOREC_CORE_REACTING;
	t3ParCore6.status = FOREC_CORE_REACTING;

	// Increment the reaction counter for synchronization.
	t3ParReactionCounter++;

	// Go to the next thread.
	goto *t3ReactionEndMaster4.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:t3:master:4:end
 


	// Abort check handlers ----------------------------------------

// forec:scheduler:parHandler:main:slave:5:start
/*--------------------------------------------------------------
| Slave core: core5
*-------------------------------------------------------------*/
mainParCore5: {
	// Check the execution status of the root par(...)s.
	while (mainParParent.parStatus == FOREC_PAR_OFF);

	short int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave5.programCounter = &&mainReactionStartSlave5;
		t0ParHandlerSlave5.programCounter = &&t0ParHandlerSlave5;
		mainReactionStartSlave5.nextThread = &t0ParHandlerSlave5;
		t0ParHandlerSlave5.prevThread = &mainReactionStartSlave5;
		mainReactionEndSlave5.programCounter = &&mainReactionEndSlave5;
		t0ParHandlerSlave5.nextThread = &mainReactionEndSlave5;
		mainReactionEndSlave5.prevThread = &t0ParHandlerSlave5;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave5.nextThread = &mainReactionStartSlave5;
		mainReactionStartSlave5.prevThread = &mainReactionEndSlave5;

		// Set the core information.
		mainParCore5.activeThreads = 1;
		mainParCore5.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto t0ParHandlerSlave5;
		asm("# par0 end");
	} else {
		// Unscheduled par(...)
		mainParCore5.reactionCounter = mainParReactionCounter;
		
		// Wait for the par(...) to terminate.
		do {
			mainParCore5.status = FOREC_CORE_TERMINATED;
			
			// Wait for the next reaction.
			while (mainParCore5.reactionCounter == mainParReactionCounter);
			mainParCore5.reactionCounter++;
			
		} while (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId);
		
		// Go back to the top and wait for the next nested par(...) 
		goto mainParCore5;
	}
	
	// Control shouldn't reach here.
	goto mainParCore5;
}
// forec:scheduler:parHandler:main:slave:5:end

	// Nested par(...) handlers ------------------------------------
	// forec:scheduler:parHandler:t0:slave:5:start
	//-- Thread t0 par(...) handlers
t0ParHandlerSlave5: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_t0 & 0x80000000) == (unsigned)0x80000000);

	// Check the execution status of the nested par(...)s.
	if (t0ParParent.parStatus == FOREC_PAR_OFF) {
		goto *t0ParHandlerSlave5.nextThread -> programCounter;
	}

	short int parId = t0ParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		t0ReactionStartSlave5.programCounter = &&t0ReactionStartSlave5;
		t1ParHandlerSlave5.programCounter = &&t1ParHandlerSlave5;
		t0ReactionStartSlave5.nextThread = &t1ParHandlerSlave5;
		t1ParHandlerSlave5.prevThread = &t0ReactionStartSlave5;
		t0ReactionEndSlave5.programCounter = &&t0ReactionEndSlave5;
		t1ParHandlerSlave5.nextThread = &t0ReactionEndSlave5;
		t0ReactionEndSlave5.prevThread = &t1ParHandlerSlave5;

		// Swap the nested par handler with the linked list.
		t0ParHandlerSlave5.prevThread -> nextThread = &t0ReactionStartSlave5;
		t0ReactionStartSlave5.prevThread = t0ParHandlerSlave5.prevThread;
		t0ReactionEndSlave5.nextThread = t0ParHandlerSlave5.nextThread;
		t0ParHandlerSlave5.nextThread -> prevThread = &t0ReactionEndSlave5;
		
		// Set the core information.
		t0ParCore5.activeThreads = 1;
		t0ParCore5.reactionCounter = t0ParReactionCounter;
		
		// Go to the first thread.
		goto t1ParHandlerSlave5;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		t0ParCore5.reactionCounter = t0ParReactionCounter;
		t0ParCore5.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t0ParCore5.reactionCounter == t0ParReactionCounter);

		// Go to the next thread.
		goto t0ParHandlerSlave5;
	} else if (parId == -3) {
		// Thread termination
		mainParCore5.activeThreads--;
		t0ParCore5.activeThreads--;

		t0ParCore5.reactionCounter = t0ParReactionCounter;
		t0ParCore5.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t0ParCore5.reactionCounter == t0ParReactionCounter);

		// Delete this par(...) handler.
		t0ParHandlerSlave5.prevThread -> nextThread = t0ParHandlerSlave5.nextThread;
		t0ParHandlerSlave5.nextThread -> prevThread = t0ParHandlerSlave5.prevThread;
			
		// Go to the next thread.
		goto *t0ParHandlerSlave5.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		t0ParCore5.reactionCounter = t0ParReactionCounter;

		t0ParHandlerSlave5.programCounter = &&wrongParId_t0ParHandlerSlave5;
		wrongParId_t0ParHandlerSlave5:;

		t0ParCore5.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t0ParCore5.reactionCounter == t0ParReactionCounter);
		t0ParCore5.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t0ParParent.parStatus == FOREC_PAR_ON && t0ParParent.parId == parId) {
			goto *t0ParHandlerSlave5.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t0ParHandlerSlave5.programCounter = &&t0ParHandlerSlave5;
		
		goto t0ParHandlerSlave5;
	}
	
	// Control should not reach here.
	goto t0ParHandlerSlave5;
}
	// forec:scheduler:parHandler:t0:slave:5:end
 	// forec:scheduler:parHandler:t1:slave:5:start
	//-- Thread t1 par(...) handlers
t1ParHandlerSlave5: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_t1 & 0x40000000) == (unsigned)0x40000000);

	// Check the execution status of the nested par(...)s.
	if (t1ParParent.parStatus == FOREC_PAR_OFF) {
		goto *t1ParHandlerSlave5.nextThread -> programCounter;
	}

	short int parId = t1ParParent.parId;

	// Check the par(...) ID.
	if (parId == 2) {
		asm ("# par2 begin");
		// Link the threads and handlers together.
		t1ReactionStartSlave5.programCounter = &&t1ReactionStartSlave5;
		t2ParHandlerSlave5.programCounter = &&t2ParHandlerSlave5;
		t1ReactionStartSlave5.nextThread = &t2ParHandlerSlave5;
		t2ParHandlerSlave5.prevThread = &t1ReactionStartSlave5;
		t1ReactionEndSlave5.programCounter = &&t1ReactionEndSlave5;
		t2ParHandlerSlave5.nextThread = &t1ReactionEndSlave5;
		t1ReactionEndSlave5.prevThread = &t2ParHandlerSlave5;

		// Swap the nested par handler with the linked list.
		t1ParHandlerSlave5.prevThread -> nextThread = &t1ReactionStartSlave5;
		t1ReactionStartSlave5.prevThread = t1ParHandlerSlave5.prevThread;
		t1ReactionEndSlave5.nextThread = t1ParHandlerSlave5.nextThread;
		t1ParHandlerSlave5.nextThread -> prevThread = &t1ReactionEndSlave5;
		
		// Set the core information.
		t1ParCore5.activeThreads = 1;
		t1ParCore5.reactionCounter = t1ParReactionCounter;
		
		// Go to the first thread.
		goto t2ParHandlerSlave5;
		asm ("# par2 end");
	} else if (parId == -2) {
		// Iteration
		t1ParCore5.reactionCounter = t1ParReactionCounter;
		t1ParCore5.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t1ParCore5.reactionCounter == t1ParReactionCounter);

		// Go to the next thread.
		goto t1ParHandlerSlave5;
	} else if (parId == -3) {
		// Thread termination
		t0ParCore5.activeThreads--;
		t1ParCore5.activeThreads--;

		t1ParCore5.reactionCounter = t1ParReactionCounter;
		t1ParCore5.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t1ParCore5.reactionCounter == t1ParReactionCounter);

		// Delete this par(...) handler.
		t1ParHandlerSlave5.prevThread -> nextThread = t1ParHandlerSlave5.nextThread;
		t1ParHandlerSlave5.nextThread -> prevThread = t1ParHandlerSlave5.prevThread;
			
		// Go to the next thread.
		goto *t1ParHandlerSlave5.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		t1ParCore5.reactionCounter = t1ParReactionCounter;

		t1ParHandlerSlave5.programCounter = &&wrongParId_t1ParHandlerSlave5;
		wrongParId_t1ParHandlerSlave5:;

		t1ParCore5.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t1ParCore5.reactionCounter == t1ParReactionCounter);
		t1ParCore5.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t1ParParent.parStatus == FOREC_PAR_ON && t1ParParent.parId == parId) {
			goto *t1ParHandlerSlave5.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t1ParHandlerSlave5.programCounter = &&t1ParHandlerSlave5;
		
		goto t1ParHandlerSlave5;
	}
	
	// Control should not reach here.
	goto t1ParHandlerSlave5;
}
	// forec:scheduler:parHandler:t1:slave:5:end
 	// forec:scheduler:parHandler:t2:slave:5:start
	//-- Thread t2 par(...) handlers
t2ParHandlerSlave5: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_t2 & 0x20000000) == (unsigned)0x20000000);

	// Check the execution status of the nested par(...)s.
	if (t2ParParent.parStatus == FOREC_PAR_OFF) {
		goto *t2ParHandlerSlave5.nextThread -> programCounter;
	}

	short int parId = t2ParParent.parId;

	// Check the par(...) ID.
	if (parId == 3) {
		asm ("# par3 begin");
		// Link the threads and handlers together.
		t2ReactionStartSlave5.programCounter = &&t2ReactionStartSlave5;
		t3ParHandlerSlave5.programCounter = &&t3ParHandlerSlave5;
		t2ReactionStartSlave5.nextThread = &t3ParHandlerSlave5;
		t3ParHandlerSlave5.prevThread = &t2ReactionStartSlave5;
		t2ReactionEndSlave5.programCounter = &&t2ReactionEndSlave5;
		t3ParHandlerSlave5.nextThread = &t2ReactionEndSlave5;
		t2ReactionEndSlave5.prevThread = &t3ParHandlerSlave5;

		// Swap the nested par handler with the linked list.
		t2ParHandlerSlave5.prevThread -> nextThread = &t2ReactionStartSlave5;
		t2ReactionStartSlave5.prevThread = t2ParHandlerSlave5.prevThread;
		t2ReactionEndSlave5.nextThread = t2ParHandlerSlave5.nextThread;
		t2ParHandlerSlave5.nextThread -> prevThread = &t2ReactionEndSlave5;
		
		// Set the core information.
		t2ParCore5.activeThreads = 1;
		t2ParCore5.reactionCounter = t2ParReactionCounter;
		
		// Go to the first thread.
		goto t3ParHandlerSlave5;
		asm ("# par3 end");
	} else if (parId == -2) {
		// Iteration
		t2ParCore5.reactionCounter = t2ParReactionCounter;
		t2ParCore5.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t2ParCore5.reactionCounter == t2ParReactionCounter);

		// Go to the next thread.
		goto t2ParHandlerSlave5;
	} else if (parId == -3) {
		// Thread termination
		t1ParCore5.activeThreads--;
		t2ParCore5.activeThreads--;

		t2ParCore5.reactionCounter = t2ParReactionCounter;
		t2ParCore5.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t2ParCore5.reactionCounter == t2ParReactionCounter);

		// Delete this par(...) handler.
		t2ParHandlerSlave5.prevThread -> nextThread = t2ParHandlerSlave5.nextThread;
		t2ParHandlerSlave5.nextThread -> prevThread = t2ParHandlerSlave5.prevThread;
			
		// Go to the next thread.
		goto *t2ParHandlerSlave5.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		t2ParCore5.reactionCounter = t2ParReactionCounter;

		t2ParHandlerSlave5.programCounter = &&wrongParId_t2ParHandlerSlave5;
		wrongParId_t2ParHandlerSlave5:;

		t2ParCore5.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t2ParCore5.reactionCounter == t2ParReactionCounter);
		t2ParCore5.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t2ParParent.parStatus == FOREC_PAR_ON && t2ParParent.parId == parId) {
			goto *t2ParHandlerSlave5.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t2ParHandlerSlave5.programCounter = &&t2ParHandlerSlave5;
		
		goto t2ParHandlerSlave5;
	}
	
	// Control should not reach here.
	goto t2ParHandlerSlave5;
}
	// forec:scheduler:parHandler:t2:slave:5:end
 	// forec:scheduler:parHandler:t3:slave:5:start
	//-- Thread t3 par(...) handlers
t3ParHandlerSlave5: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_t3 & 0x10000000) == (unsigned)0x10000000);

	// Check the execution status of the nested par(...)s.
	if (t3ParParent.parStatus == FOREC_PAR_OFF) {
		goto *t3ParHandlerSlave5.nextThread -> programCounter;
	}

	short int parId = t3ParParent.parId;

	// Check the par(...) ID.
	if (parId == 4) {
		asm ("# par4 begin");
		// Link the threads and handlers together.
		t3ReactionStartSlave5.programCounter = &&t3ReactionStartSlave5;
		t4__thread.programCounter = &&t4__thread;
		t3ReactionStartSlave5.nextThread = &t4__thread;
		t4__thread.prevThread = &t3ReactionStartSlave5;
		t4ParHandlerMaster5.programCounter = &&t4ParHandlerMaster5;
		t4__thread.nextThread = &t4ParHandlerMaster5;
		t4ParHandlerMaster5.prevThread = &t4__thread;
		t3ReactionEndSlave5.programCounter = &&t3ReactionEndSlave5;
		t4ParHandlerMaster5.nextThread = &t3ReactionEndSlave5;
		t3ReactionEndSlave5.prevThread = &t4ParHandlerMaster5;

		// Swap the nested par handler with the linked list.
		t3ParHandlerSlave5.prevThread -> nextThread = &t3ReactionStartSlave5;
		t3ReactionStartSlave5.prevThread = t3ParHandlerSlave5.prevThread;
		t3ReactionEndSlave5.nextThread = t3ParHandlerSlave5.nextThread;
		t3ParHandlerSlave5.nextThread -> prevThread = &t3ReactionEndSlave5;
		
		// Set the core information.
		t3ParCore5.activeThreads = 2;
		t3ParCore5.reactionCounter = t3ParReactionCounter;
		
		// Go to the first thread.
		goto t4__thread;
		asm ("# par4 end");
	} else if (parId == -2) {
		// Iteration
		t3ParCore5.reactionCounter = t3ParReactionCounter;
		t3ParCore5.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t3ParCore5.reactionCounter == t3ParReactionCounter);

		// Go to the next thread.
		goto t3ParHandlerSlave5;
	} else if (parId == -3) {
		// Thread termination
		t2ParCore5.activeThreads--;
		t3ParCore5.activeThreads--;

		t3ParCore5.reactionCounter = t3ParReactionCounter;
		t3ParCore5.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t3ParCore5.reactionCounter == t3ParReactionCounter);

		// Delete this par(...) handler.
		t3ParHandlerSlave5.prevThread -> nextThread = t3ParHandlerSlave5.nextThread;
		t3ParHandlerSlave5.nextThread -> prevThread = t3ParHandlerSlave5.prevThread;
			
		// Go to the next thread.
		goto *t3ParHandlerSlave5.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		t3ParCore5.reactionCounter = t3ParReactionCounter;

		t3ParHandlerSlave5.programCounter = &&wrongParId_t3ParHandlerSlave5;
		wrongParId_t3ParHandlerSlave5:;

		t3ParCore5.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t3ParCore5.reactionCounter == t3ParReactionCounter);
		t3ParCore5.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t3ParParent.parStatus == FOREC_PAR_ON && t3ParParent.parId == parId) {
			goto *t3ParHandlerSlave5.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t3ParHandlerSlave5.programCounter = &&t3ParHandlerSlave5;
		
		goto t3ParHandlerSlave5;
	}
	
	// Control should not reach here.
	goto t3ParHandlerSlave5;
}
	// forec:scheduler:parHandler:t3:slave:5:end
 	// forec:scheduler:parHandler:t4:master:5:start
	//-- Thread t4 par(...) handlers
t4ParHandlerMaster5: {
	// Check the execution status of the nested par(...)s.
	if (t4ParParent.parStatus == FOREC_PAR_OFF) {
		// Release the mutex.
		forec_mutex_value_t4 &= 0xf7ffffff;

		goto *t4ParHandlerMaster5.nextThread -> programCounter;
	}
	// Release the mutex.
	forec_mutex_value_t4 &= 0xf7ffffff;

	short int parId = t4ParParent.parId;

	// Check the par(...) ID.
	if (parId == 5) {
		asm ("# par5 begin");
		// Link the threads and handlers together.
		t4ReactionStartMaster5.programCounter = &&t4ReactionStartMaster5;
		t4ReactionEndMaster5.programCounter = &&t4ReactionEndMaster5;
		t4ReactionStartMaster5.nextThread = &t4ReactionEndMaster5;
		t4ReactionEndMaster5.prevThread = &t4ReactionStartMaster5;

		// Swap the nested par handler with the linked list.
		t4ParHandlerMaster5.prevThread -> nextThread = &t4ReactionStartMaster5;
		t4ReactionStartMaster5.prevThread = t4ParHandlerMaster5.prevThread;
		t4ReactionEndMaster5.nextThread = t4ParHandlerMaster5.nextThread;
		t4ParHandlerMaster5.nextThread -> prevThread = &t4ReactionEndMaster5;
		
		// Set the core information.
		t4ParCore5.activeThreads = 0;
		t4ParCore5.reactionCounter = t4ParReactionCounter;
		
		// Go to the first thread.
		goto t4ReactionEndMaster5;
		asm ("# par5 end");
	} else if (parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.
		while(t4ParCore6.status == FOREC_CORE_REACTING);

		t4ParParent.parStatus = FOREC_PAR_OFF;
		t4ParParent.parId = -1;

		forec_mutex_value_t4 = -1;

		// Set slave cores' status to reacting.
		t4ParCore6.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		t4ParReactionCounter++;

		// Return to thread t4.
		goto *t4ParParent.programCounter;
	} else if (parId == -3) {
		// Thread termination
		t3ParCore5.activeThreads--;
		t4ParCore5.activeThreads--;

		// Wait for other cores to complete their reaction.
		while(t4ParCore6.status == FOREC_CORE_REACTING);

		t4ParParent.parStatus = FOREC_PAR_OFF;
		t4ParParent.parId = -1;

		// Set slave cores' status to reacting.
		t4ParCore6.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		t4ParReactionCounter++;

		// Delete this par(...) handler.
		t4ParHandlerMaster5.prevThread -> nextThread = t4ParHandlerMaster5.nextThread;
		t4ParHandlerMaster5.nextThread -> prevThread = t4ParHandlerMaster5.prevThread;
			
		// Return to thread t4.
		goto *t4ParParent.programCounter;
	} else {
		// Unscheduled par(...)
		t4ParCore5.reactionCounter = t4ParReactionCounter;

		t4ParHandlerMaster5.programCounter = &&wrongParId_t4ParHandlerMaster5;
		wrongParId_t4ParHandlerMaster5:;

		t4ParCore5.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t4ParCore5.reactionCounter == t4ParReactionCounter);
		t4ParCore5.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t4ParParent.parStatus == FOREC_PAR_ON && t4ParParent.parId == parId) {
			goto *t4ParHandlerMaster5.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t4ParHandlerMaster5.programCounter = &&t4ParHandlerMaster5;
		
		goto t4ParHandlerMaster5;
	}
	
	// Control should not reach here.
	goto t4ParHandlerMaster5;
}
	// forec:scheduler:parHandler:t4:master:5:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:slave:5:start
	//-- main:
mainReactionStartSlave5: {
	// Go to the next thread.
	goto *mainReactionStartSlave5.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:5:end
 
	// forec:scheduler:reactionStart:t0:slave:5:start
	//-- t0:
t0ReactionStartSlave5: {
	// Go to the next thread.
	goto *t0ReactionStartSlave5.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t0:slave:5:end
 
	// forec:scheduler:reactionStart:t1:slave:5:start
	//-- t1:
t1ReactionStartSlave5: {
	// Go to the next thread.
	goto *t1ReactionStartSlave5.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t1:slave:5:end
 
	// forec:scheduler:reactionStart:t2:slave:5:start
	//-- t2:
t2ReactionStartSlave5: {
	// Go to the next thread.
	goto *t2ReactionStartSlave5.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t2:slave:5:end
 
	// forec:scheduler:reactionStart:t3:slave:5:start
	//-- t3:
t3ReactionStartSlave5: {
	// Go to the next thread.
	goto *t3ReactionStartSlave5.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t3:slave:5:end
 
	// forec:scheduler:reactionStart:t4:master:5:start
	//-- t4:
t4ReactionStartMaster5: {
	// Go to the next thread.
	goto *t4ReactionStartMaster5.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t4:master:5:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:main:slave:5:start
	//-- main:
mainReactionEndSlave5: {
	// Determine if the core can still react or not.
	if (mainParCore5.activeThreads) {
		mainParCore5.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (mainParCore5.reactionCounter == mainParReactionCounter);
		mainParCore5.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave5.nextThread -> programCounter;
	} else {
		short int parId = mainParParent.parId;

		mainReactionEndSlave5.programCounter = &&terminated_mainReactionEndSlave5;
		terminated_mainReactionEndSlave5:;
		
		mainParCore5.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (mainParCore5.reactionCounter == mainParReactionCounter);
		mainParCore5.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId) {
			goto *mainReactionEndSlave5.nextThread -> programCounter;
		}

		goto mainParCore5;
	}
	
	// Control shouldn't reach here.
	goto mainReactionEndSlave5;
}
	// forec:scheduler:reactionEnd:main:slave:5:end
 
	// forec:scheduler:reactionEnd:t0:slave:5:start
	//-- t0:
t0ReactionEndSlave5: {
	// Determine if the core can still react or not.
	if (t0ParCore5.activeThreads) {
		t0ParCore5.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (t0ParCore5.reactionCounter == t0ParReactionCounter);
		t0ParCore5.reactionCounter++;
		
		// Continue reacting.
		goto *t0ReactionEndSlave5.nextThread -> programCounter;
	} else {
		short int parId = t0ParParent.parId;

		t0ReactionEndSlave5.programCounter = &&terminated_t0ReactionEndSlave5;
		terminated_t0ReactionEndSlave5:;
		
		t0ParCore5.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (t0ParCore5.reactionCounter == t0ParReactionCounter);
		t0ParCore5.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (t0ParParent.parStatus == FOREC_PAR_ON && t0ParParent.parId == parId) {
			goto *t0ReactionEndSlave5.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		t0ReactionStartSlave5.prevThread -> nextThread = &t0ParHandlerSlave5;
		t0ParHandlerSlave5.prevThread = t0ReactionStartSlave5.prevThread;
		t0ParHandlerSlave5.nextThread = t0ReactionEndSlave5.nextThread;
		t0ReactionEndSlave5.nextThread -> prevThread = &t0ParHandlerSlave5;
		goto t0ParHandlerSlave5;
	}
	
	// Control shouldn't reach here.
	goto t0ReactionEndSlave5;
}
	// forec:scheduler:reactionEnd:t0:slave:5:end
 
	// forec:scheduler:reactionEnd:t1:slave:5:start
	//-- t1:
t1ReactionEndSlave5: {
	// Determine if the core can still react or not.
	if (t1ParCore5.activeThreads) {
		t1ParCore5.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (t1ParCore5.reactionCounter == t1ParReactionCounter);
		t1ParCore5.reactionCounter++;
		
		// Continue reacting.
		goto *t1ReactionEndSlave5.nextThread -> programCounter;
	} else {
		short int parId = t1ParParent.parId;

		t1ReactionEndSlave5.programCounter = &&terminated_t1ReactionEndSlave5;
		terminated_t1ReactionEndSlave5:;
		
		t1ParCore5.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (t1ParCore5.reactionCounter == t1ParReactionCounter);
		t1ParCore5.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (t1ParParent.parStatus == FOREC_PAR_ON && t1ParParent.parId == parId) {
			goto *t1ReactionEndSlave5.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		t1ReactionStartSlave5.prevThread -> nextThread = &t1ParHandlerSlave5;
		t1ParHandlerSlave5.prevThread = t1ReactionStartSlave5.prevThread;
		t1ParHandlerSlave5.nextThread = t1ReactionEndSlave5.nextThread;
		t1ReactionEndSlave5.nextThread -> prevThread = &t1ParHandlerSlave5;
		goto t1ParHandlerSlave5;
	}
	
	// Control shouldn't reach here.
	goto t1ReactionEndSlave5;
}
	// forec:scheduler:reactionEnd:t1:slave:5:end
 
	// forec:scheduler:reactionEnd:t2:slave:5:start
	//-- t2:
t2ReactionEndSlave5: {
	// Determine if the core can still react or not.
	if (t2ParCore5.activeThreads) {
		t2ParCore5.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (t2ParCore5.reactionCounter == t2ParReactionCounter);
		t2ParCore5.reactionCounter++;
		
		// Continue reacting.
		goto *t2ReactionEndSlave5.nextThread -> programCounter;
	} else {
		short int parId = t2ParParent.parId;

		t2ReactionEndSlave5.programCounter = &&terminated_t2ReactionEndSlave5;
		terminated_t2ReactionEndSlave5:;
		
		t2ParCore5.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (t2ParCore5.reactionCounter == t2ParReactionCounter);
		t2ParCore5.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (t2ParParent.parStatus == FOREC_PAR_ON && t2ParParent.parId == parId) {
			goto *t2ReactionEndSlave5.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		t2ReactionStartSlave5.prevThread -> nextThread = &t2ParHandlerSlave5;
		t2ParHandlerSlave5.prevThread = t2ReactionStartSlave5.prevThread;
		t2ParHandlerSlave5.nextThread = t2ReactionEndSlave5.nextThread;
		t2ReactionEndSlave5.nextThread -> prevThread = &t2ParHandlerSlave5;
		goto t2ParHandlerSlave5;
	}
	
	// Control shouldn't reach here.
	goto t2ReactionEndSlave5;
}
	// forec:scheduler:reactionEnd:t2:slave:5:end
 
	// forec:scheduler:reactionEnd:t3:slave:5:start
	//-- t3:
t3ReactionEndSlave5: {
	// Determine if the core can still react or not.
	if (t3ParCore5.activeThreads) {
		t3ParCore5.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (t3ParCore5.reactionCounter == t3ParReactionCounter);
		t3ParCore5.reactionCounter++;
		
		// Continue reacting.
		goto *t3ReactionEndSlave5.nextThread -> programCounter;
	} else {
		short int parId = t3ParParent.parId;

		t3ReactionEndSlave5.programCounter = &&terminated_t3ReactionEndSlave5;
		terminated_t3ReactionEndSlave5:;
		
		t3ParCore5.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (t3ParCore5.reactionCounter == t3ParReactionCounter);
		t3ParCore5.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (t3ParParent.parStatus == FOREC_PAR_ON && t3ParParent.parId == parId) {
			goto *t3ReactionEndSlave5.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		t3ReactionStartSlave5.prevThread -> nextThread = &t3ParHandlerSlave5;
		t3ParHandlerSlave5.prevThread = t3ReactionStartSlave5.prevThread;
		t3ParHandlerSlave5.nextThread = t3ReactionEndSlave5.nextThread;
		t3ReactionEndSlave5.nextThread -> prevThread = &t3ParHandlerSlave5;
		goto t3ParHandlerSlave5;
	}
	
	// Control shouldn't reach here.
	goto t3ReactionEndSlave5;
}
	// forec:scheduler:reactionEnd:t3:slave:5:end
 
	// forec:scheduler:reactionEnd:t4:master:5:start
	//-- t4:
t4ReactionEndMaster5: {
	// Determine if the core can still react or not.
	if (t4ParCore5.activeThreads) {
		t4ParCore5.status = FOREC_CORE_REACTED;
	} else {
		t4ParCore5.status = FOREC_CORE_TERMINATED;
	}
	
	// Wait for other cores to complete their reaction.
	while(t4ParCore6.status == FOREC_CORE_REACTING);


	// Return back to the parent thread if all the cores have terminated.
	if (1 && t4ParCore5.status == FOREC_CORE_TERMINATED && t4ParCore6.status == FOREC_CORE_TERMINATED) {
		forec_mutex_value_t4 = -1;

		t4ParParent.parStatus = FOREC_PAR_OFF;
		t4ParParent.parId = -1;
		
		// Set slave cores' status to reacting
		t4ParCore6.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronization.
		t4ParReactionCounter++;

		// Swap the reaction (start & end) handlers with (thread t4 & nested par handler).
		t4ReactionStartMaster5.prevThread -> nextThread = &t4__thread;
		t4__thread.prevThread = t4ReactionStartMaster5.prevThread;
		t4__thread.nextThread = &t4ParHandlerMaster5;
		t4ParHandlerMaster5.prevThread = &t4__thread;
		t4ParHandlerMaster5.nextThread = t4ReactionEndMaster5.nextThread;
		t4ReactionEndMaster5.nextThread -> prevThread = &t4ParHandlerMaster5;

		goto *t4ParParent.programCounter;
	}

	// Set slave cores' status to reacting
	t4ParCore6.status = FOREC_CORE_REACTING;

	// Increment the reaction counter for synchronization.
	t4ParReactionCounter++;

	// Go to the next thread.
	goto *t4ReactionEndMaster5.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:t4:master:5:end
 


	// Abort check handlers ----------------------------------------

// forec:scheduler:parHandler:main:slave:6:start
/*--------------------------------------------------------------
| Slave core: core6
*-------------------------------------------------------------*/
mainParCore6: {
	// Check the execution status of the root par(...)s.
	while (mainParParent.parStatus == FOREC_PAR_OFF);

	short int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave6.programCounter = &&mainReactionStartSlave6;
		t0ParHandlerSlave6.programCounter = &&t0ParHandlerSlave6;
		mainReactionStartSlave6.nextThread = &t0ParHandlerSlave6;
		t0ParHandlerSlave6.prevThread = &mainReactionStartSlave6;
		mainReactionEndSlave6.programCounter = &&mainReactionEndSlave6;
		t0ParHandlerSlave6.nextThread = &mainReactionEndSlave6;
		mainReactionEndSlave6.prevThread = &t0ParHandlerSlave6;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave6.nextThread = &mainReactionStartSlave6;
		mainReactionStartSlave6.prevThread = &mainReactionEndSlave6;

		// Set the core information.
		mainParCore6.activeThreads = 1;
		mainParCore6.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto t0ParHandlerSlave6;
		asm("# par0 end");
	} else {
		// Unscheduled par(...)
		mainParCore6.reactionCounter = mainParReactionCounter;
		
		// Wait for the par(...) to terminate.
		do {
			mainParCore6.status = FOREC_CORE_TERMINATED;
			
			// Wait for the next reaction.
			while (mainParCore6.reactionCounter == mainParReactionCounter);
			mainParCore6.reactionCounter++;
			
		} while (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId);
		
		// Go back to the top and wait for the next nested par(...) 
		goto mainParCore6;
	}
	
	// Control shouldn't reach here.
	goto mainParCore6;
}
// forec:scheduler:parHandler:main:slave:6:end

	// Nested par(...) handlers ------------------------------------
	// forec:scheduler:parHandler:t0:slave:6:start
	//-- Thread t0 par(...) handlers
t0ParHandlerSlave6: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_t0 & 0x80000000) == (unsigned)0x80000000);

	// Check the execution status of the nested par(...)s.
	if (t0ParParent.parStatus == FOREC_PAR_OFF) {
		goto *t0ParHandlerSlave6.nextThread -> programCounter;
	}

	short int parId = t0ParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		t0ReactionStartSlave6.programCounter = &&t0ReactionStartSlave6;
		t1ParHandlerSlave6.programCounter = &&t1ParHandlerSlave6;
		t0ReactionStartSlave6.nextThread = &t1ParHandlerSlave6;
		t1ParHandlerSlave6.prevThread = &t0ReactionStartSlave6;
		t0ReactionEndSlave6.programCounter = &&t0ReactionEndSlave6;
		t1ParHandlerSlave6.nextThread = &t0ReactionEndSlave6;
		t0ReactionEndSlave6.prevThread = &t1ParHandlerSlave6;

		// Swap the nested par handler with the linked list.
		t0ParHandlerSlave6.prevThread -> nextThread = &t0ReactionStartSlave6;
		t0ReactionStartSlave6.prevThread = t0ParHandlerSlave6.prevThread;
		t0ReactionEndSlave6.nextThread = t0ParHandlerSlave6.nextThread;
		t0ParHandlerSlave6.nextThread -> prevThread = &t0ReactionEndSlave6;
		
		// Set the core information.
		t0ParCore6.activeThreads = 1;
		t0ParCore6.reactionCounter = t0ParReactionCounter;
		
		// Go to the first thread.
		goto t1ParHandlerSlave6;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		t0ParCore6.reactionCounter = t0ParReactionCounter;
		t0ParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t0ParCore6.reactionCounter == t0ParReactionCounter);

		// Go to the next thread.
		goto t0ParHandlerSlave6;
	} else if (parId == -3) {
		// Thread termination
		mainParCore6.activeThreads--;
		t0ParCore6.activeThreads--;

		t0ParCore6.reactionCounter = t0ParReactionCounter;
		t0ParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t0ParCore6.reactionCounter == t0ParReactionCounter);

		// Delete this par(...) handler.
		t0ParHandlerSlave6.prevThread -> nextThread = t0ParHandlerSlave6.nextThread;
		t0ParHandlerSlave6.nextThread -> prevThread = t0ParHandlerSlave6.prevThread;
			
		// Go to the next thread.
		goto *t0ParHandlerSlave6.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		t0ParCore6.reactionCounter = t0ParReactionCounter;

		t0ParHandlerSlave6.programCounter = &&wrongParId_t0ParHandlerSlave6;
		wrongParId_t0ParHandlerSlave6:;

		t0ParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t0ParCore6.reactionCounter == t0ParReactionCounter);
		t0ParCore6.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t0ParParent.parStatus == FOREC_PAR_ON && t0ParParent.parId == parId) {
			goto *t0ParHandlerSlave6.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t0ParHandlerSlave6.programCounter = &&t0ParHandlerSlave6;
		
		goto t0ParHandlerSlave6;
	}
	
	// Control should not reach here.
	goto t0ParHandlerSlave6;
}
	// forec:scheduler:parHandler:t0:slave:6:end
 	// forec:scheduler:parHandler:t1:slave:6:start
	//-- Thread t1 par(...) handlers
t1ParHandlerSlave6: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_t1 & 0x40000000) == (unsigned)0x40000000);

	// Check the execution status of the nested par(...)s.
	if (t1ParParent.parStatus == FOREC_PAR_OFF) {
		goto *t1ParHandlerSlave6.nextThread -> programCounter;
	}

	short int parId = t1ParParent.parId;

	// Check the par(...) ID.
	if (parId == 2) {
		asm ("# par2 begin");
		// Link the threads and handlers together.
		t1ReactionStartSlave6.programCounter = &&t1ReactionStartSlave6;
		t2ParHandlerSlave6.programCounter = &&t2ParHandlerSlave6;
		t1ReactionStartSlave6.nextThread = &t2ParHandlerSlave6;
		t2ParHandlerSlave6.prevThread = &t1ReactionStartSlave6;
		t1ReactionEndSlave6.programCounter = &&t1ReactionEndSlave6;
		t2ParHandlerSlave6.nextThread = &t1ReactionEndSlave6;
		t1ReactionEndSlave6.prevThread = &t2ParHandlerSlave6;

		// Swap the nested par handler with the linked list.
		t1ParHandlerSlave6.prevThread -> nextThread = &t1ReactionStartSlave6;
		t1ReactionStartSlave6.prevThread = t1ParHandlerSlave6.prevThread;
		t1ReactionEndSlave6.nextThread = t1ParHandlerSlave6.nextThread;
		t1ParHandlerSlave6.nextThread -> prevThread = &t1ReactionEndSlave6;
		
		// Set the core information.
		t1ParCore6.activeThreads = 1;
		t1ParCore6.reactionCounter = t1ParReactionCounter;
		
		// Go to the first thread.
		goto t2ParHandlerSlave6;
		asm ("# par2 end");
	} else if (parId == -2) {
		// Iteration
		t1ParCore6.reactionCounter = t1ParReactionCounter;
		t1ParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t1ParCore6.reactionCounter == t1ParReactionCounter);

		// Go to the next thread.
		goto t1ParHandlerSlave6;
	} else if (parId == -3) {
		// Thread termination
		t0ParCore6.activeThreads--;
		t1ParCore6.activeThreads--;

		t1ParCore6.reactionCounter = t1ParReactionCounter;
		t1ParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t1ParCore6.reactionCounter == t1ParReactionCounter);

		// Delete this par(...) handler.
		t1ParHandlerSlave6.prevThread -> nextThread = t1ParHandlerSlave6.nextThread;
		t1ParHandlerSlave6.nextThread -> prevThread = t1ParHandlerSlave6.prevThread;
			
		// Go to the next thread.
		goto *t1ParHandlerSlave6.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		t1ParCore6.reactionCounter = t1ParReactionCounter;

		t1ParHandlerSlave6.programCounter = &&wrongParId_t1ParHandlerSlave6;
		wrongParId_t1ParHandlerSlave6:;

		t1ParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t1ParCore6.reactionCounter == t1ParReactionCounter);
		t1ParCore6.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t1ParParent.parStatus == FOREC_PAR_ON && t1ParParent.parId == parId) {
			goto *t1ParHandlerSlave6.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t1ParHandlerSlave6.programCounter = &&t1ParHandlerSlave6;
		
		goto t1ParHandlerSlave6;
	}
	
	// Control should not reach here.
	goto t1ParHandlerSlave6;
}
	// forec:scheduler:parHandler:t1:slave:6:end
 	// forec:scheduler:parHandler:t2:slave:6:start
	//-- Thread t2 par(...) handlers
t2ParHandlerSlave6: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_t2 & 0x20000000) == (unsigned)0x20000000);

	// Check the execution status of the nested par(...)s.
	if (t2ParParent.parStatus == FOREC_PAR_OFF) {
		goto *t2ParHandlerSlave6.nextThread -> programCounter;
	}

	short int parId = t2ParParent.parId;

	// Check the par(...) ID.
	if (parId == 3) {
		asm ("# par3 begin");
		// Link the threads and handlers together.
		t2ReactionStartSlave6.programCounter = &&t2ReactionStartSlave6;
		t3ParHandlerSlave6.programCounter = &&t3ParHandlerSlave6;
		t2ReactionStartSlave6.nextThread = &t3ParHandlerSlave6;
		t3ParHandlerSlave6.prevThread = &t2ReactionStartSlave6;
		t2ReactionEndSlave6.programCounter = &&t2ReactionEndSlave6;
		t3ParHandlerSlave6.nextThread = &t2ReactionEndSlave6;
		t2ReactionEndSlave6.prevThread = &t3ParHandlerSlave6;

		// Swap the nested par handler with the linked list.
		t2ParHandlerSlave6.prevThread -> nextThread = &t2ReactionStartSlave6;
		t2ReactionStartSlave6.prevThread = t2ParHandlerSlave6.prevThread;
		t2ReactionEndSlave6.nextThread = t2ParHandlerSlave6.nextThread;
		t2ParHandlerSlave6.nextThread -> prevThread = &t2ReactionEndSlave6;
		
		// Set the core information.
		t2ParCore6.activeThreads = 1;
		t2ParCore6.reactionCounter = t2ParReactionCounter;
		
		// Go to the first thread.
		goto t3ParHandlerSlave6;
		asm ("# par3 end");
	} else if (parId == -2) {
		// Iteration
		t2ParCore6.reactionCounter = t2ParReactionCounter;
		t2ParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t2ParCore6.reactionCounter == t2ParReactionCounter);

		// Go to the next thread.
		goto t2ParHandlerSlave6;
	} else if (parId == -3) {
		// Thread termination
		t1ParCore6.activeThreads--;
		t2ParCore6.activeThreads--;

		t2ParCore6.reactionCounter = t2ParReactionCounter;
		t2ParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t2ParCore6.reactionCounter == t2ParReactionCounter);

		// Delete this par(...) handler.
		t2ParHandlerSlave6.prevThread -> nextThread = t2ParHandlerSlave6.nextThread;
		t2ParHandlerSlave6.nextThread -> prevThread = t2ParHandlerSlave6.prevThread;
			
		// Go to the next thread.
		goto *t2ParHandlerSlave6.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		t2ParCore6.reactionCounter = t2ParReactionCounter;

		t2ParHandlerSlave6.programCounter = &&wrongParId_t2ParHandlerSlave6;
		wrongParId_t2ParHandlerSlave6:;

		t2ParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t2ParCore6.reactionCounter == t2ParReactionCounter);
		t2ParCore6.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t2ParParent.parStatus == FOREC_PAR_ON && t2ParParent.parId == parId) {
			goto *t2ParHandlerSlave6.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t2ParHandlerSlave6.programCounter = &&t2ParHandlerSlave6;
		
		goto t2ParHandlerSlave6;
	}
	
	// Control should not reach here.
	goto t2ParHandlerSlave6;
}
	// forec:scheduler:parHandler:t2:slave:6:end
 	// forec:scheduler:parHandler:t3:slave:6:start
	//-- Thread t3 par(...) handlers
t3ParHandlerSlave6: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_t3 & 0x10000000) == (unsigned)0x10000000);

	// Check the execution status of the nested par(...)s.
	if (t3ParParent.parStatus == FOREC_PAR_OFF) {
		goto *t3ParHandlerSlave6.nextThread -> programCounter;
	}

	short int parId = t3ParParent.parId;

	// Check the par(...) ID.
	if (parId == 4) {
		asm ("# par4 begin");
		// Link the threads and handlers together.
		t3ReactionStartSlave6.programCounter = &&t3ReactionStartSlave6;
		t4ParHandlerSlave6.programCounter = &&t4ParHandlerSlave6;
		t3ReactionStartSlave6.nextThread = &t4ParHandlerSlave6;
		t4ParHandlerSlave6.prevThread = &t3ReactionStartSlave6;
		t3ReactionEndSlave6.programCounter = &&t3ReactionEndSlave6;
		t4ParHandlerSlave6.nextThread = &t3ReactionEndSlave6;
		t3ReactionEndSlave6.prevThread = &t4ParHandlerSlave6;

		// Swap the nested par handler with the linked list.
		t3ParHandlerSlave6.prevThread -> nextThread = &t3ReactionStartSlave6;
		t3ReactionStartSlave6.prevThread = t3ParHandlerSlave6.prevThread;
		t3ReactionEndSlave6.nextThread = t3ParHandlerSlave6.nextThread;
		t3ParHandlerSlave6.nextThread -> prevThread = &t3ReactionEndSlave6;
		
		// Set the core information.
		t3ParCore6.activeThreads = 1;
		t3ParCore6.reactionCounter = t3ParReactionCounter;
		
		// Go to the first thread.
		goto t4ParHandlerSlave6;
		asm ("# par4 end");
	} else if (parId == -2) {
		// Iteration
		t3ParCore6.reactionCounter = t3ParReactionCounter;
		t3ParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t3ParCore6.reactionCounter == t3ParReactionCounter);

		// Go to the next thread.
		goto t3ParHandlerSlave6;
	} else if (parId == -3) {
		// Thread termination
		t2ParCore6.activeThreads--;
		t3ParCore6.activeThreads--;

		t3ParCore6.reactionCounter = t3ParReactionCounter;
		t3ParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t3ParCore6.reactionCounter == t3ParReactionCounter);

		// Delete this par(...) handler.
		t3ParHandlerSlave6.prevThread -> nextThread = t3ParHandlerSlave6.nextThread;
		t3ParHandlerSlave6.nextThread -> prevThread = t3ParHandlerSlave6.prevThread;
			
		// Go to the next thread.
		goto *t3ParHandlerSlave6.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		t3ParCore6.reactionCounter = t3ParReactionCounter;

		t3ParHandlerSlave6.programCounter = &&wrongParId_t3ParHandlerSlave6;
		wrongParId_t3ParHandlerSlave6:;

		t3ParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t3ParCore6.reactionCounter == t3ParReactionCounter);
		t3ParCore6.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t3ParParent.parStatus == FOREC_PAR_ON && t3ParParent.parId == parId) {
			goto *t3ParHandlerSlave6.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t3ParHandlerSlave6.programCounter = &&t3ParHandlerSlave6;
		
		goto t3ParHandlerSlave6;
	}
	
	// Control should not reach here.
	goto t3ParHandlerSlave6;
}
	// forec:scheduler:parHandler:t3:slave:6:end
 	// forec:scheduler:parHandler:t4:slave:6:start
	//-- Thread t4 par(...) handlers
t4ParHandlerSlave6: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_t4 & 0x8000000) == (unsigned)0x8000000);

	// Check the execution status of the nested par(...)s.
	if (t4ParParent.parStatus == FOREC_PAR_OFF) {
		goto *t4ParHandlerSlave6.nextThread -> programCounter;
	}

	short int parId = t4ParParent.parId;

	// Check the par(...) ID.
	if (parId == 5) {
		asm ("# par5 begin");
		// Link the threads and handlers together.
		t4ReactionStartSlave6.programCounter = &&t4ReactionStartSlave6;
		t5__thread.programCounter = &&t5__thread;
		t4ReactionStartSlave6.nextThread = &t5__thread;
		t5__thread.prevThread = &t4ReactionStartSlave6;
		t4ReactionEndSlave6.programCounter = &&t4ReactionEndSlave6;
		t5__thread.nextThread = &t4ReactionEndSlave6;
		t4ReactionEndSlave6.prevThread = &t5__thread;

		// Swap the nested par handler with the linked list.
		t4ParHandlerSlave6.prevThread -> nextThread = &t4ReactionStartSlave6;
		t4ReactionStartSlave6.prevThread = t4ParHandlerSlave6.prevThread;
		t4ReactionEndSlave6.nextThread = t4ParHandlerSlave6.nextThread;
		t4ParHandlerSlave6.nextThread -> prevThread = &t4ReactionEndSlave6;
		
		// Set the core information.
		t4ParCore6.activeThreads = 1;
		t4ParCore6.reactionCounter = t4ParReactionCounter;
		
		// Go to the first thread.
		goto t5__thread;
		asm ("# par5 end");
	} else if (parId == -2) {
		// Iteration
		t4ParCore6.reactionCounter = t4ParReactionCounter;
		t4ParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t4ParCore6.reactionCounter == t4ParReactionCounter);

		// Go to the next thread.
		goto t4ParHandlerSlave6;
	} else if (parId == -3) {
		// Thread termination
		t3ParCore6.activeThreads--;
		t4ParCore6.activeThreads--;

		t4ParCore6.reactionCounter = t4ParReactionCounter;
		t4ParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t4ParCore6.reactionCounter == t4ParReactionCounter);

		// Delete this par(...) handler.
		t4ParHandlerSlave6.prevThread -> nextThread = t4ParHandlerSlave6.nextThread;
		t4ParHandlerSlave6.nextThread -> prevThread = t4ParHandlerSlave6.prevThread;
			
		// Go to the next thread.
		goto *t4ParHandlerSlave6.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		t4ParCore6.reactionCounter = t4ParReactionCounter;

		t4ParHandlerSlave6.programCounter = &&wrongParId_t4ParHandlerSlave6;
		wrongParId_t4ParHandlerSlave6:;

		t4ParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (t4ParCore6.reactionCounter == t4ParReactionCounter);
		t4ParCore6.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (t4ParParent.parStatus == FOREC_PAR_ON && t4ParParent.parId == parId) {
			goto *t4ParHandlerSlave6.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		t4ParHandlerSlave6.programCounter = &&t4ParHandlerSlave6;
		
		goto t4ParHandlerSlave6;
	}
	
	// Control should not reach here.
	goto t4ParHandlerSlave6;
}
	// forec:scheduler:parHandler:t4:slave:6:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:slave:6:start
	//-- main:
mainReactionStartSlave6: {
	// Go to the next thread.
	goto *mainReactionStartSlave6.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:6:end
 
	// forec:scheduler:reactionStart:t0:slave:6:start
	//-- t0:
t0ReactionStartSlave6: {
	// Go to the next thread.
	goto *t0ReactionStartSlave6.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t0:slave:6:end
 
	// forec:scheduler:reactionStart:t1:slave:6:start
	//-- t1:
t1ReactionStartSlave6: {
	// Go to the next thread.
	goto *t1ReactionStartSlave6.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t1:slave:6:end
 
	// forec:scheduler:reactionStart:t2:slave:6:start
	//-- t2:
t2ReactionStartSlave6: {
	// Go to the next thread.
	goto *t2ReactionStartSlave6.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t2:slave:6:end
 
	// forec:scheduler:reactionStart:t3:slave:6:start
	//-- t3:
t3ReactionStartSlave6: {
	// Go to the next thread.
	goto *t3ReactionStartSlave6.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t3:slave:6:end
 
	// forec:scheduler:reactionStart:t4:slave:6:start
	//-- t4:
t4ReactionStartSlave6: {
	// Go to the next thread.
	goto *t4ReactionStartSlave6.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:t4:slave:6:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:main:slave:6:start
	//-- main:
mainReactionEndSlave6: {
	// Determine if the core can still react or not.
	if (mainParCore6.activeThreads) {
		mainParCore6.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (mainParCore6.reactionCounter == mainParReactionCounter);
		mainParCore6.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave6.nextThread -> programCounter;
	} else {
		short int parId = mainParParent.parId;

		mainReactionEndSlave6.programCounter = &&terminated_mainReactionEndSlave6;
		terminated_mainReactionEndSlave6:;
		
		mainParCore6.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (mainParCore6.reactionCounter == mainParReactionCounter);
		mainParCore6.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId) {
			goto *mainReactionEndSlave6.nextThread -> programCounter;
		}

		goto mainParCore6;
	}
	
	// Control shouldn't reach here.
	goto mainReactionEndSlave6;
}
	// forec:scheduler:reactionEnd:main:slave:6:end
 
	// forec:scheduler:reactionEnd:t0:slave:6:start
	//-- t0:
t0ReactionEndSlave6: {
	// Determine if the core can still react or not.
	if (t0ParCore6.activeThreads) {
		t0ParCore6.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (t0ParCore6.reactionCounter == t0ParReactionCounter);
		t0ParCore6.reactionCounter++;
		
		// Continue reacting.
		goto *t0ReactionEndSlave6.nextThread -> programCounter;
	} else {
		short int parId = t0ParParent.parId;

		t0ReactionEndSlave6.programCounter = &&terminated_t0ReactionEndSlave6;
		terminated_t0ReactionEndSlave6:;
		
		t0ParCore6.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (t0ParCore6.reactionCounter == t0ParReactionCounter);
		t0ParCore6.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (t0ParParent.parStatus == FOREC_PAR_ON && t0ParParent.parId == parId) {
			goto *t0ReactionEndSlave6.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		t0ReactionStartSlave6.prevThread -> nextThread = &t0ParHandlerSlave6;
		t0ParHandlerSlave6.prevThread = t0ReactionStartSlave6.prevThread;
		t0ParHandlerSlave6.nextThread = t0ReactionEndSlave6.nextThread;
		t0ReactionEndSlave6.nextThread -> prevThread = &t0ParHandlerSlave6;
		goto t0ParHandlerSlave6;
	}
	
	// Control shouldn't reach here.
	goto t0ReactionEndSlave6;
}
	// forec:scheduler:reactionEnd:t0:slave:6:end
 
	// forec:scheduler:reactionEnd:t1:slave:6:start
	//-- t1:
t1ReactionEndSlave6: {
	// Determine if the core can still react or not.
	if (t1ParCore6.activeThreads) {
		t1ParCore6.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (t1ParCore6.reactionCounter == t1ParReactionCounter);
		t1ParCore6.reactionCounter++;
		
		// Continue reacting.
		goto *t1ReactionEndSlave6.nextThread -> programCounter;
	} else {
		short int parId = t1ParParent.parId;

		t1ReactionEndSlave6.programCounter = &&terminated_t1ReactionEndSlave6;
		terminated_t1ReactionEndSlave6:;
		
		t1ParCore6.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (t1ParCore6.reactionCounter == t1ParReactionCounter);
		t1ParCore6.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (t1ParParent.parStatus == FOREC_PAR_ON && t1ParParent.parId == parId) {
			goto *t1ReactionEndSlave6.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		t1ReactionStartSlave6.prevThread -> nextThread = &t1ParHandlerSlave6;
		t1ParHandlerSlave6.prevThread = t1ReactionStartSlave6.prevThread;
		t1ParHandlerSlave6.nextThread = t1ReactionEndSlave6.nextThread;
		t1ReactionEndSlave6.nextThread -> prevThread = &t1ParHandlerSlave6;
		goto t1ParHandlerSlave6;
	}
	
	// Control shouldn't reach here.
	goto t1ReactionEndSlave6;
}
	// forec:scheduler:reactionEnd:t1:slave:6:end
 
	// forec:scheduler:reactionEnd:t2:slave:6:start
	//-- t2:
t2ReactionEndSlave6: {
	// Determine if the core can still react or not.
	if (t2ParCore6.activeThreads) {
		t2ParCore6.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (t2ParCore6.reactionCounter == t2ParReactionCounter);
		t2ParCore6.reactionCounter++;
		
		// Continue reacting.
		goto *t2ReactionEndSlave6.nextThread -> programCounter;
	} else {
		short int parId = t2ParParent.parId;

		t2ReactionEndSlave6.programCounter = &&terminated_t2ReactionEndSlave6;
		terminated_t2ReactionEndSlave6:;
		
		t2ParCore6.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (t2ParCore6.reactionCounter == t2ParReactionCounter);
		t2ParCore6.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (t2ParParent.parStatus == FOREC_PAR_ON && t2ParParent.parId == parId) {
			goto *t2ReactionEndSlave6.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		t2ReactionStartSlave6.prevThread -> nextThread = &t2ParHandlerSlave6;
		t2ParHandlerSlave6.prevThread = t2ReactionStartSlave6.prevThread;
		t2ParHandlerSlave6.nextThread = t2ReactionEndSlave6.nextThread;
		t2ReactionEndSlave6.nextThread -> prevThread = &t2ParHandlerSlave6;
		goto t2ParHandlerSlave6;
	}
	
	// Control shouldn't reach here.
	goto t2ReactionEndSlave6;
}
	// forec:scheduler:reactionEnd:t2:slave:6:end
 
	// forec:scheduler:reactionEnd:t3:slave:6:start
	//-- t3:
t3ReactionEndSlave6: {
	// Determine if the core can still react or not.
	if (t3ParCore6.activeThreads) {
		t3ParCore6.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (t3ParCore6.reactionCounter == t3ParReactionCounter);
		t3ParCore6.reactionCounter++;
		
		// Continue reacting.
		goto *t3ReactionEndSlave6.nextThread -> programCounter;
	} else {
		short int parId = t3ParParent.parId;

		t3ReactionEndSlave6.programCounter = &&terminated_t3ReactionEndSlave6;
		terminated_t3ReactionEndSlave6:;
		
		t3ParCore6.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (t3ParCore6.reactionCounter == t3ParReactionCounter);
		t3ParCore6.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (t3ParParent.parStatus == FOREC_PAR_ON && t3ParParent.parId == parId) {
			goto *t3ReactionEndSlave6.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		t3ReactionStartSlave6.prevThread -> nextThread = &t3ParHandlerSlave6;
		t3ParHandlerSlave6.prevThread = t3ReactionStartSlave6.prevThread;
		t3ParHandlerSlave6.nextThread = t3ReactionEndSlave6.nextThread;
		t3ReactionEndSlave6.nextThread -> prevThread = &t3ParHandlerSlave6;
		goto t3ParHandlerSlave6;
	}
	
	// Control shouldn't reach here.
	goto t3ReactionEndSlave6;
}
	// forec:scheduler:reactionEnd:t3:slave:6:end
 
	// forec:scheduler:reactionEnd:t4:slave:6:start
	//-- t4:
t4ReactionEndSlave6: {
	// Determine if the core can still react or not.
	if (t4ParCore6.activeThreads) {
		t4ParCore6.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (t4ParCore6.reactionCounter == t4ParReactionCounter);
		t4ParCore6.reactionCounter++;
		
		// Continue reacting.
		goto *t4ReactionEndSlave6.nextThread -> programCounter;
	} else {
		short int parId = t4ParParent.parId;

		t4ReactionEndSlave6.programCounter = &&terminated_t4ReactionEndSlave6;
		terminated_t4ReactionEndSlave6:;
		
		t4ParCore6.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (t4ParCore6.reactionCounter == t4ParReactionCounter);
		t4ParCore6.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (t4ParParent.parStatus == FOREC_PAR_ON && t4ParParent.parId == parId) {
			goto *t4ReactionEndSlave6.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		t4ReactionStartSlave6.prevThread -> nextThread = &t4ParHandlerSlave6;
		t4ParHandlerSlave6.prevThread = t4ReactionStartSlave6.prevThread;
		t4ParHandlerSlave6.nextThread = t4ReactionEndSlave6.nextThread;
		t4ReactionEndSlave6.nextThread -> prevThread = &t4ParHandlerSlave6;
		goto t4ParHandlerSlave6;
	}
	
	// Control shouldn't reach here.
	goto t4ReactionEndSlave6;
}
	// forec:scheduler:reactionEnd:t4:slave:6:end
 


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
	// No declarations.

	// Thread body -------------------------------------------------
	t0__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		printf("*\r\n");

		// pause;
		// forec:statement:pause:pause1:start
		t0__thread.programCounter = &&pause1;
		goto *t0__thread.nextThread -> programCounter;
		pause1:;
		// forec:statement:pause:pause1:end


		// par1(t1__thread);
		// Set the par(...) information.
		t0ParParent.parId = 1;
		t0ParParent.parStatus = FOREC_PAR_ON;
		t0ParParent.programCounter = &&par1JoinAddress_t0ParParent;

		// Remove this thread from the linked list.
		t0__thread.nextThread -> prevThread = t0__thread.prevThread;
		t0__thread.prevThread -> nextThread = t0__thread.nextThread;
		// forec:statement:par:par1:start
		goto t0ParHandlerMaster1;
		par1JoinAddress_t0ParParent:;
		// forec:statement:par:par1:end

		printf(".\r\n");

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:t0:start
		// Delete par handler
		t0ParParent.parId = -3;
		t0ParParent.parStatus = FOREC_PAR_ON;
		t0ParParent.programCounter = &&t0_endAddress;
		goto t0ParHandlerMaster1;
		t0_endAddress:;

		// Delete thread from the linked list and core.
		mainParCore1.activeThreads--;
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
	// No declarations.

	// Thread body -------------------------------------------------
	t1__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		printf("**\r\n");

		// par2(t2__thread);
		// Set the par(...) information.
		t1ParParent.parId = 2;
		t1ParParent.parStatus = FOREC_PAR_ON;
		t1ParParent.programCounter = &&par2JoinAddress_t1ParParent;

		// Remove this thread from the linked list.
		t1__thread.nextThread -> prevThread = t1__thread.prevThread;
		t1__thread.prevThread -> nextThread = t1__thread.nextThread;
		// forec:statement:par:par2:start
		goto t1ParHandlerMaster2;
		par2JoinAddress_t1ParParent:;
		// forec:statement:par:par2:end

		printf("..\r\n");

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:t1:start
		// Delete par handler
		t1ParParent.parId = -3;
		t1ParParent.parStatus = FOREC_PAR_ON;
		t1ParParent.programCounter = &&t1_endAddress;
		goto t1ParHandlerMaster2;
		t1_endAddress:;

		// Delete thread from the linked list and core.
		t0ParCore2.activeThreads--;
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
	// No declarations.

	// Thread body -------------------------------------------------
	t2__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		printf("***\r\n");

		// par3(t3__thread);
		// Set the par(...) information.
		t2ParParent.parId = 3;
		t2ParParent.parStatus = FOREC_PAR_ON;
		t2ParParent.programCounter = &&par3JoinAddress_t2ParParent;

		// Remove this thread from the linked list.
		t2__thread.nextThread -> prevThread = t2__thread.prevThread;
		t2__thread.prevThread -> nextThread = t2__thread.nextThread;
		// forec:statement:par:par3:start
		goto t2ParHandlerMaster3;
		par3JoinAddress_t2ParParent:;
		// forec:statement:par:par3:end

		printf("...\r\n");

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:t2:start
		// Delete par handler
		t2ParParent.parId = -3;
		t2ParParent.parStatus = FOREC_PAR_ON;
		t2ParParent.programCounter = &&t2_endAddress;
		goto t2ParHandlerMaster3;
		t2_endAddress:;

		// Delete thread from the linked list and core.
		t1ParCore3.activeThreads--;
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
	// No declarations.

	// Thread body -------------------------------------------------
	t3__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		printf("****\r\n");

		// par4(t4__thread);
		// Set the par(...) information.
		t3ParParent.parId = 4;
		t3ParParent.parStatus = FOREC_PAR_ON;
		t3ParParent.programCounter = &&par4JoinAddress_t3ParParent;

		// Remove this thread from the linked list.
		t3__thread.nextThread -> prevThread = t3__thread.prevThread;
		t3__thread.prevThread -> nextThread = t3__thread.nextThread;
		// forec:statement:par:par4:start
		goto t3ParHandlerMaster4;
		par4JoinAddress_t3ParParent:;
		// forec:statement:par:par4:end

		// pause;
		// forec:statement:pause:pause2:start
		t3__thread.programCounter = &&pause2;
		goto *t3__thread.nextThread -> programCounter;
		pause2:;
		// forec:statement:pause:pause2:end


		printf("....\r\n");

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:t3:start
		// Delete par handler
		t3ParParent.parId = -3;
		t3ParParent.parStatus = FOREC_PAR_ON;
		t3ParParent.programCounter = &&t3_endAddress;
		goto t3ParHandlerMaster4;
		t3_endAddress:;

		// Delete thread from the linked list and core.
		t2ParCore4.activeThreads--;
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
	// No declarations.

	// Thread body -------------------------------------------------
	t4__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		printf("*****\r\n");

		// par5(t5__thread);
		// Set the par(...) information.
		t4ParParent.parId = 5;
		t4ParParent.parStatus = FOREC_PAR_ON;
		t4ParParent.programCounter = &&par5JoinAddress_t4ParParent;

		// Remove this thread from the linked list.
		t4__thread.nextThread -> prevThread = t4__thread.prevThread;
		t4__thread.prevThread -> nextThread = t4__thread.nextThread;
		// forec:statement:par:par5:start
		goto t4ParHandlerMaster5;
		par5JoinAddress_t4ParParent:;
		// forec:statement:par:par5:end

		printf(".....\r\n");

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:t4:start
		// Delete par handler
		t4ParParent.parId = -3;
		t4ParParent.parStatus = FOREC_PAR_ON;
		t4ParParent.programCounter = &&t4_endAddress;
		goto t4ParHandlerMaster5;
		t4_endAddress:;

		// Delete thread from the linked list and core.
		t3ParCore5.activeThreads--;
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
	// No declarations.

	// Thread body -------------------------------------------------
	t5__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		// pause;
		// forec:statement:pause:pause3:start
		t5__thread.programCounter = &&pause3;
		goto *t5__thread.nextThread -> programCounter;
		pause3:;
		// forec:statement:pause:pause3:end


		printf("......\r\n");

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:t5:start

		// Delete thread from the linked list and core.
		t4ParCore6.activeThreads--;
		t5__thread.nextThread -> prevThread = t5__thread.prevThread;
		t5__thread.prevThread -> nextThread = t5__thread.nextThread;
		goto *t5__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:t5:end
	} // t5__thread
	// forec:thread:t5:end


} // End of the main() function.

