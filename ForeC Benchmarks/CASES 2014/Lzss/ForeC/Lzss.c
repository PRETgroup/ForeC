/*==============================================================
| Hardware architecture specific declarations:
| Cores, mutex and input/output information.
*=============================================================*/
// Xilinx Microblaze
#include "xparameters.h"

// Xilinx Microblaze Processor Version Register
#include "pvr.h"

// Hardware counter connected via a direct FSL bus.
#include "counter_dfsl.h"
Counter counter;

// ForeC hardware mutex
#include "forec_mutex.h"
#define FSL_FOREC_MUTEX_ID			0
#define FSL_FOREC_MUTEX_RESET_ID	1
#define FSL_COUNTER_ID				2
#define MAX_MUTEX_COUNT				31


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
	int parStatus;
	int parId;
} Parent;

// Keep track of child threads executing on
// a processor core.
typedef struct {
	int sync;
	int activeThreads;
	int status;
	int reactionCounter;
} Core;

// Global variable for counting the number of global reactions.
volatile long int globalReactions = 0;

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
typedef struct _Fifo__global_0_0 {
	char *data;
	unsigned size;
	unsigned written_size;
	int begin;
	int end;
} Fifo__global_0_0;

void Fifo_init(Fifo__global_0_0 *, unsigned, char *);
void Fifo_destroy(Fifo__global_0_0 *);
int Fifo_push_front(Fifo__global_0_0 *, char);
int Fifo_push_back(Fifo__global_0_0 *, char);
char Fifo_pop_front(Fifo__global_0_0 *);
char Fifo_pop_back(Fifo__global_0_0 *);
char Fifo_at(const Fifo__global_0_0 *, unsigned);
void Fifo_print(const Fifo__global_0_0 *);
int mgetc(char ** stream);
int mputc(char c, char ** stream);
int mwrite(const void *ptr, int size, int nmemb, char ** stream);

int FILE_SIZE__global_0_0 = 816;
int NUM_THREADS__global_0_0 = 4;
int WINLENGTH__global_0_0 = 256;
int LKLENGTH__global_0_0 = 16;
char archive__global_0_0[816];
char embedded__global_0_0[] = {35, 105, 110, 99, 108, 117, 100, 101, 32, 60, 105, 111, 115, 116, 114, 101, 97, 109, 62, 10, 35, 105, 110, 99, 108, 117, 100, 101, 32, 60, 102, 115, 116, 114, 101, 97, 109, 62, 10, 10, 117, 115, 105, 110, 103, 32, 110, 97, 109, 101, 115, 112, 97, 99, 101, 32, 115, 116, 100, 59, 10, 10, 105, 110, 116, 32, 109, 97, 105, 110, 40, 105, 110, 116, 32, 97, 114, 103, 99, 44, 32, 99, 104, 97, 114, 32, 42, 97, 114, 103, 118, 91, 93, 41, 10, 123, 10, 32, 32, 32, 32, 105, 102, 115, 116, 114, 101, 97, 109, 32, 105, 110, 40, 97, 114, 103, 118, 91, 49, 93, 41, 59, 10, 10, 32, 32, 32, 32, 105, 102, 32, 40, 33, 105, 110, 41, 10, 32, 32, 32, 32, 123, 10, 32, 32, 32, 32, 32, 32, 32, 32, 99, 101, 114, 114, 32, 60, 60, 32, 34, 67, 97, 110, 110, 111, 116, 32, 111, 112, 101, 110, 32, 105, 110, 112, 117, 116, 32, 102, 105, 108, 101, 58, 32, 34, 32, 60, 60, 32, 97, 114, 103, 118, 91, 50, 93, 32, 60, 60, 32, 101, 110, 100, 108, 59, 10, 32, 32, 32, 32, 32, 32, 32, 32, 114, 101, 116, 117, 114, 110, 32, 49, 59, 10, 32, 32, 32, 32, 125, 10, 10, 32, 32, 32, 32, 111, 102, 115, 116, 114, 101, 97, 109, 32, 111, 117, 116, 40, 34, 101, 109, 98, 101, 100, 46, 104, 34, 41, 59, 10, 10, 32, 32, 32, 32, 105, 102, 32, 40, 33, 111, 117, 116, 41, 10, 32, 32, 32, 32, 123, 10, 32, 32, 32, 32, 32, 32, 32, 32, 99, 101, 114, 114, 32, 60, 60, 32, 34, 67, 97, 110, 110, 111, 116, 32, 111, 112, 101, 110, 32, 111, 117, 116, 112, 117, 116, 32, 102, 105, 108, 101, 58, 32, 101, 109, 98, 101, 100, 46, 104, 34, 32, 60, 60, 32, 101, 110, 100, 108, 59, 10, 32, 32, 32, 32, 32, 32, 32, 32, 114, 101, 116, 117, 114, 110, 32, 50, 59, 10, 32, 32, 32, 32, 125, 10, 10, 32, 32, 32, 32, 108, 111, 110, 103, 32, 98, 101, 103, 105, 110, 44, 32, 101, 110, 100, 59, 10, 32, 32, 32, 32, 98, 101, 103, 105, 110, 32, 61, 32, 105, 110, 46, 116, 101, 108, 108, 103, 40, 41, 59, 10, 32, 32, 32, 32, 105, 110, 46, 115, 101, 101, 107, 103, 40, 48, 44, 32, 105, 111, 115, 58, 58, 101, 110, 100, 41, 59, 10, 32, 32, 32, 32, 101, 110, 100, 32, 61, 32, 105, 110, 46, 116, 101, 108, 108, 103, 40, 41, 59, 10, 32, 32, 32, 32, 105, 110, 46, 115, 101, 101, 107, 103, 40, 48, 44, 32, 105, 111, 115, 58, 58, 98, 101, 103, 41, 59, 10, 10, 32, 32, 32, 32, 117, 110, 115, 105, 103, 110, 101, 100, 32, 105, 110, 116, 32, 99, 32, 61, 32, 105, 110, 46, 103, 101, 116, 40, 41, 59, 10, 32, 32, 32, 32, 111, 117, 116, 32, 60, 60, 32, 34, 35, 100, 101, 102, 105, 110, 101, 32, 70, 73, 76, 69, 95, 83, 73, 90, 69, 32, 34, 32, 60, 60, 32, 40, 101, 110, 100, 32, 45, 32, 98, 101, 103, 105, 110, 41, 32, 60, 60, 32, 34, 92, 110, 92, 110, 34, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 99, 104, 97, 114, 32, 97, 114, 99, 104, 105, 118, 101, 91, 34, 32, 60, 60, 32, 40, 101, 110, 100, 32, 45, 32, 98, 101, 103, 105, 110, 41, 32, 60, 60, 32, 34, 93, 59, 92, 110, 92, 110, 34, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 99, 104, 97, 114, 32, 101, 109, 98, 101, 100, 100, 101, 100, 91, 93, 32, 61, 32, 123, 92, 110, 34, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 32, 32, 32, 32, 34, 32, 60, 60, 32, 99, 59, 10, 10, 32, 32, 32, 32, 119, 104, 105, 108, 101, 32, 40, 99, 32, 61, 32, 105, 110, 46, 103, 101, 116, 40, 41, 44, 32, 33, 105, 110, 46, 101, 111, 102, 40, 41, 41, 32, 123, 10, 32, 32, 32, 32, 32, 32, 32, 32, 111, 117, 116, 32, 60, 60, 32, 34, 44, 92, 110, 34, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 60, 60, 32, 34, 32, 32, 32, 32, 34, 32, 60, 60, 32, 99, 59, 10, 32, 32, 32, 32, 125, 10, 32, 32, 32, 32, 10, 32, 32, 32, 32, 111, 117, 116, 32, 60, 60, 32, 34, 92, 110, 125, 59, 92, 110, 34, 59, 10, 125, 10};
int offset__global_0_0;
int matches__global_0_0 = 0;

int *first(int ** copy1__first_0_0, int ** copy2__first_0_0) {
	return * copy1__first_0_0;
}

int offset_thread__global_0_0[4];

typedef struct {
	/* shared */ int *value;
	int status;
} Shared_offset_thread_ptr__global_0_0;
Shared_offset_thread_ptr__global_0_0 offset_thread_ptr__global_0_0 = {.value = offset_thread__global_0_0, .status = FOREC_SHARED_UNMODIFIED} /* combine with first */;

int matches_thread__global_0_0[4];

typedef struct {
	/* shared */ int *value;
	int status;
} Shared_matches_thread_ptr__global_0_0;
Shared_matches_thread_ptr__global_0_0 matches_thread_ptr__global_0_0 = {.value = matches_thread__global_0_0, .status = FOREC_SHARED_UNMODIFIED} /* combine with first */;

struct fileStats__global_0_0 {
	char *p_file;
	char *fileaddr;
	int filesize;
	int totalSize;
	int bytesProcessed;
} fileInfo__global_0_0, archiveInfo__global_0_0;

char window_buf__global_0_0[256];
char lookAhead_buf__global_0_0[16];

typedef struct {
	/* shared */ Fifo__global_0_0 value;
	int status;
} Shared_window__global_0_0;
Shared_window__global_0_0 window__global_0_0;
typedef struct {
	/* shared */ Fifo__global_0_0 value;
	int status;
} Shared_lookAhead__global_0_0;
Shared_lookAhead__global_0_0 lookAhead__global_0_0;

int getFileSize(void);
int getBytesProcessed(void);
void openFile(void);
void createDescriptor(struct fileStats__global_0_0 *, struct fileStats__global_0_0 *);
void storeFileInfo(struct fileStats__global_0_0 *, struct fileStats__global_0_0 *);
void longestMatch(const Fifo__global_0_0, const Fifo__global_0_0, int, int **, int **);
void writeToArchive(const Fifo__global_0_0 *, int *, int *, struct fileStats__global_0_0 *, int *, int *, Fifo__global_0_0 *, Fifo__global_0_0 *);
void printResult(struct fileStats__global_0_0 *, struct fileStats__global_0_0 *);
void unpackArchive(char *filename, int *, int *, struct fileStats__global_0_0 *, struct fileStats__global_0_0 *);
void processDescriptor(struct fileStats__global_0_0 *, struct fileStats__global_0_0 *);
void decompressFile(int *, int *, struct fileStats__global_0_0 *, struct fileStats__global_0_0 *);
void decode(Fifo__global_0_0 *, int *, int *, int *, struct fileStats__global_0_0 *, struct fileStats__global_0_0 *);
void obtainFileInfo(struct fileStats__global_0_0 *);

// thread longestMatch0__thread(void);
// thread longestMatch1__thread(void);
// thread longestMatch2__thread(void);
// thread longestMatch3__thread(void);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// longestMatch0
Shared_window__global_0_0 window__global_0_0_copy_longestMatch0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_lookAhead__global_0_0 lookAhead__global_0_0_copy_longestMatch0 = {.status = FOREC_SHARED_UNMODIFIED};
// longestMatch1
Shared_window__global_0_0 window__global_0_0_copy_longestMatch1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_lookAhead__global_0_0 lookAhead__global_0_0_copy_longestMatch1 = {.status = FOREC_SHARED_UNMODIFIED};
// longestMatch2
Shared_window__global_0_0 window__global_0_0_copy_longestMatch2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_lookAhead__global_0_0 lookAhead__global_0_0_copy_longestMatch2 = {.status = FOREC_SHARED_UNMODIFIED};
// longestMatch3
Shared_window__global_0_0 window__global_0_0_copy_longestMatch3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_lookAhead__global_0_0 lookAhead__global_0_0_copy_longestMatch3 = {.status = FOREC_SHARED_UNMODIFIED};
// main

// forec:scheduler:boot:start
int main(int argc__main_0_0, char ** argv__main_0_0) {

/*==============================================================
| Multicore startup:
| Platform dependent code.  Core identifies itself and
| executes its corresponding start up code.
*=============================================================*/
	// Initialise ForeC specific values ----------------------------
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


	// ForeC mutex -------------------------------------------------
	unsigned int forec_mutex_value;
	forec_mutex_reset(FSL_FOREC_MUTEX_RESET_ID);
	
	// Variables for par()s ----------------------------------------
	// par0
	Thread longestMatch0__thread;
	Thread longestMatch1__thread;
	Thread longestMatch2__thread;
	Thread longestMatch3__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionStartSlave1;
	Thread mainReactionStartSlave2;
	Thread mainReactionStartSlave3;
	Thread mainReactionEndMaster0;
	Thread mainReactionEndSlave1;
	Thread mainReactionEndSlave2;
	Thread mainReactionEndSlave3;


	// Synchronise execution of cores ------------------------------
	// pvr = Processor Version Register
	unsigned int pvr0;
	getpvr(0, pvr0);
	pvr0 &= MICROBLAZE_PVR0_USER1_MASK;

	switch (pvr0) {
		case (0):
			while(mainParCore1.sync);
			while(mainParCore2.sync);
			while(mainParCore3.sync);
			goto mainParCore0;

		case (1):
			mainParCore1.sync = 0;
			goto mainParCore1;

		case (2):
			mainParCore2.sync = 0;
			goto mainParCore2;

		case (3):
			mainParCore3.sync = 0;
			goto mainParCore3;

		default:
			// "Lock-up" unused cores.
			while(1);
	}
// forec:scheduler:boot:end

/*==============================================================
| Core specific instructions:
| Contains par, abort and synchronisation handlers.
*=============================================================*/

	// forec:thread:main:start
	/*--------------------------------------------------------------
	| Master core: core0
	| ForeC program's main() function:
	| Original main() function code with ForeC constructs
	| translated into C code.
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	int count__main_1_1;

mainParCore0: {
	// forec:scheduler:counter:start
	// Initialise and start counting the elapsed cycles for each reaction.
	counterInitialise(counter);
	counterStart(counter, FSL_COUNTER_ID);
	// forec:scheduler:counter:end
	
	//--------------------------------------------------------------

	openFile();
	Fifo_init(&window__global_0_0.value, WINLENGTH__global_0_0, window_buf__global_0_0);
	Fifo_push_back(&window__global_0_0.value, mgetc(&fileInfo__global_0_0.p_file));
	writeToArchive(&window__global_0_0.value, &offset__global_0_0, &matches__global_0_0, &archiveInfo__global_0_0, offset_thread__global_0_0, matches_thread__global_0_0, &window__global_0_0.value, &lookAhead__global_0_0.value);
	fileInfo__global_0_0.p_file = fileInfo__global_0_0.fileaddr;
	Fifo_pop_back(&window__global_0_0.value);
	Fifo_init(&lookAhead__global_0_0.value, LKLENGTH__global_0_0, lookAhead_buf__global_0_0);
	while (lookAhead__global_0_0.value.written_size < LKLENGTH__global_0_0) {
		Fifo_push_back(&lookAhead__global_0_0.value, mgetc(&fileInfo__global_0_0.p_file));
		asm volatile ("nop");
	}

	while (getFileSize() != getBytesProcessed()) {
		count__main_1_1 = 1;
		do {
			if (window__global_0_0.value.written_size >= WINLENGTH__global_0_0) {
				Fifo_pop_front(&window__global_0_0.value);
			} else {
				// if0
			}
			Fifo_push_back(&window__global_0_0.value, Fifo_pop_front(&lookAhead__global_0_0.value));
			Fifo_push_back(&lookAhead__global_0_0.value, mgetc(&fileInfo__global_0_0.p_file));
			asm volatile ("nop");
		} while (count__main_1_1++ < matches__global_0_0);

		// par0(longestMatch0__thread, longestMatch1__thread, longestMatch2__thread, longestMatch3__thread);
		// forec:statement:par:par0:start
		// Set the par(...) information.
		mainParParent.parId = 0;
		mainParParent.parStatus = FOREC_PAR_ON;

		// Link the threads and handlers together.
		mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
		longestMatch0__thread.programCounter = &&longestMatch0__thread;
		mainReactionStartMaster0.nextThread = &longestMatch0__thread;
		longestMatch0__thread.prevThread = &mainReactionStartMaster0;
		mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
		longestMatch0__thread.nextThread = &mainReactionEndMaster0;
		mainReactionEndMaster0.prevThread = &longestMatch0__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
		mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

		// Set the join address.
		mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

		// Set the core information.
		mainParCore0.activeThreads = 1;
		mainParCore0.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto longestMatch0__thread;
		par0JoinAddress_mainParCore0:;
		// forec:statement:par:par0:end

		writeToArchive(&lookAhead__global_0_0.value, &offset__global_0_0, &matches__global_0_0, &archiveInfo__global_0_0, offset_thread__global_0_0, matches_thread__global_0_0, &window__global_0_0.value, &lookAhead__global_0_0.value);

		// forec:scheduler:iterationEnd:while_2:start
		// Synchronise end of iteration
		mainParParent.parId = -2;
		mainParParent.parStatus = FOREC_PAR_ON;
		mainParParent.programCounter = &&while_2_endAddress;
		goto mainParHandlerMaster0;
		while_2_endAddress:;
		// forec:scheduler:iterationEnd:while_2:end
		asm volatile ("nop");
	}

	//--------------------------------------------------------------

	// forec:scheduler:threadRemove:main:start

	// forec:scheduler:counter:start
	// Stop counting the elapsed cycles for the current reaction.
	counterStop(FSL_COUNTER_ID);
	counterRead(counter, FSL_COUNTER_ID);
	counterDifference(counter);
	counterMaximum(counter);
	counterMinimum(counter);
	counterAccumulate(counter);
	counterAverage(counter);
	xil_printf("%ld Reaction time: %d cycles, Min: %d, Avg: %d, Max: %d\r\n", globalReactions, counter.difference, counter.min, counter.avg, counter.max);
	xil_printf("Total time: %d cycles\r\n", counter.total);
	xil_printf("Program termination\r\n");
	// forec:scheduler:counter:end

	asm volatile (".long 0x80000001\r\n");
	return 0;
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
	forec_mutex_reset(FSL_FOREC_MUTEX_RESET_ID);

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

	// forec:scheduler:counter:start
	// Stop counting the elapsed cycles for the current reaction.
	counterStop(FSL_COUNTER_ID);
	counterRead(counter, FSL_COUNTER_ID);
	counterDifference(counter);
	counterMaximum(counter);
	counterMinimum(counter);
	counterAccumulate(counter);
	counterAverage(counter);
	xil_printf("%d Reaction time: %ld cycles, Min: %d, Avg: %d, Max: %d\r\n", globalReactions, counter.difference, counter.min, counter.avg, counter.max);
	globalReactions++;
	// Restart counting of the elapsed cycles for the next reaction.
	counterReset(counter);
	counterStart(counter, FSL_COUNTER_ID);
	// forec:scheduler:counter:end

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

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave1.programCounter = &&mainReactionStartSlave1;
		longestMatch1__thread.programCounter = &&longestMatch1__thread;
		mainReactionStartSlave1.nextThread = &longestMatch1__thread;
		longestMatch1__thread.prevThread = &mainReactionStartSlave1;
		mainReactionEndSlave1.programCounter = &&mainReactionEndSlave1;
		longestMatch1__thread.nextThread = &mainReactionEndSlave1;
		mainReactionEndSlave1.prevThread = &longestMatch1__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave1.nextThread = &mainReactionStartSlave1;
		mainReactionStartSlave1.prevThread = &mainReactionEndSlave1;

		// Set the core information.
		mainParCore1.activeThreads = 1;
		mainParCore1.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto longestMatch1__thread;
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
		int parId = mainParParent.parId;

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

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave2.programCounter = &&mainReactionStartSlave2;
		longestMatch2__thread.programCounter = &&longestMatch2__thread;
		mainReactionStartSlave2.nextThread = &longestMatch2__thread;
		longestMatch2__thread.prevThread = &mainReactionStartSlave2;
		mainReactionEndSlave2.programCounter = &&mainReactionEndSlave2;
		longestMatch2__thread.nextThread = &mainReactionEndSlave2;
		mainReactionEndSlave2.prevThread = &longestMatch2__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave2.nextThread = &mainReactionStartSlave2;
		mainReactionStartSlave2.prevThread = &mainReactionEndSlave2;

		// Set the core information.
		mainParCore2.activeThreads = 1;
		mainParCore2.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto longestMatch2__thread;
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
		int parId = mainParParent.parId;

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

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave3.programCounter = &&mainReactionStartSlave3;
		longestMatch3__thread.programCounter = &&longestMatch3__thread;
		mainReactionStartSlave3.nextThread = &longestMatch3__thread;
		longestMatch3__thread.prevThread = &mainReactionStartSlave3;
		mainReactionEndSlave3.programCounter = &&mainReactionEndSlave3;
		longestMatch3__thread.nextThread = &mainReactionEndSlave3;
		mainReactionEndSlave3.prevThread = &longestMatch3__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave3.nextThread = &mainReactionStartSlave3;
		mainReactionStartSlave3.prevThread = &mainReactionEndSlave3;

		// Set the core information.
		mainParCore3.activeThreads = 1;
		mainParCore3.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto longestMatch3__thread;
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
		int parId = mainParParent.parId;

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
| Threads code translated into C code.
*=============================================================*/
	// forec:thread:longestMatch0:start
	/*--------------------------------------------------------------
	| Thread longestMatch0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_window__global_0_0 window__global_0_0_copy_longestMatch0_local;
	Shared_lookAhead__global_0_0 lookAhead__global_0_0_copy_longestMatch0_local;

	// Thread body -------------------------------------------------
	longestMatch0__thread: {
		// Initialise the local copies of shared variables.
		window__global_0_0_copy_longestMatch0_local.value = window__global_0_0.value;
		window__global_0_0_copy_longestMatch0_local.status = FOREC_SHARED_UNMODIFIED;
		lookAhead__global_0_0_copy_longestMatch0_local.value = lookAhead__global_0_0.value;
		lookAhead__global_0_0_copy_longestMatch0_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		longestMatch(window__global_0_0_copy_longestMatch0_local.value, lookAhead__global_0_0_copy_longestMatch0_local.value, 0, &offset_thread_ptr__global_0_0.value, &matches_thread_ptr__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:longestMatch0:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		longestMatch0__thread.nextThread -> prevThread = longestMatch0__thread.prevThread;
		longestMatch0__thread.prevThread -> nextThread = longestMatch0__thread.nextThread;
		goto *longestMatch0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:longestMatch0:end
	} // longestMatch0__thread
	// forec:thread:longestMatch0:end

	// forec:thread:longestMatch1:start
	/*--------------------------------------------------------------
	| Thread longestMatch1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_window__global_0_0 window__global_0_0_copy_longestMatch1_local;
	Shared_lookAhead__global_0_0 lookAhead__global_0_0_copy_longestMatch1_local;

	// Thread body -------------------------------------------------
	longestMatch1__thread: {
		// Initialise the local copies of shared variables.
		window__global_0_0_copy_longestMatch1_local.value = window__global_0_0.value;
		window__global_0_0_copy_longestMatch1_local.status = FOREC_SHARED_UNMODIFIED;
		lookAhead__global_0_0_copy_longestMatch1_local.value = lookAhead__global_0_0.value;
		lookAhead__global_0_0_copy_longestMatch1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		longestMatch(window__global_0_0_copy_longestMatch1_local.value, lookAhead__global_0_0_copy_longestMatch1_local.value, 1, &offset_thread_ptr__global_0_0.value, &matches_thread_ptr__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:longestMatch1:start

		// Delete thread from the linked list and core.
		mainParCore1.activeThreads--;
		longestMatch1__thread.nextThread -> prevThread = longestMatch1__thread.prevThread;
		longestMatch1__thread.prevThread -> nextThread = longestMatch1__thread.nextThread;
		goto *longestMatch1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:longestMatch1:end
	} // longestMatch1__thread
	// forec:thread:longestMatch1:end

	// forec:thread:longestMatch2:start
	/*--------------------------------------------------------------
	| Thread longestMatch2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_window__global_0_0 window__global_0_0_copy_longestMatch2_local;
	Shared_lookAhead__global_0_0 lookAhead__global_0_0_copy_longestMatch2_local;

	// Thread body -------------------------------------------------
	longestMatch2__thread: {
		// Initialise the local copies of shared variables.
		window__global_0_0_copy_longestMatch2_local.value = window__global_0_0.value;
		window__global_0_0_copy_longestMatch2_local.status = FOREC_SHARED_UNMODIFIED;
		lookAhead__global_0_0_copy_longestMatch2_local.value = lookAhead__global_0_0.value;
		lookAhead__global_0_0_copy_longestMatch2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		longestMatch(window__global_0_0_copy_longestMatch2_local.value, lookAhead__global_0_0_copy_longestMatch2_local.value, 2, &offset_thread_ptr__global_0_0.value, &matches_thread_ptr__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:longestMatch2:start

		// Delete thread from the linked list and core.
		mainParCore2.activeThreads--;
		longestMatch2__thread.nextThread -> prevThread = longestMatch2__thread.prevThread;
		longestMatch2__thread.prevThread -> nextThread = longestMatch2__thread.nextThread;
		goto *longestMatch2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:longestMatch2:end
	} // longestMatch2__thread
	// forec:thread:longestMatch2:end

	// forec:thread:longestMatch3:start
	/*--------------------------------------------------------------
	| Thread longestMatch3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_window__global_0_0 window__global_0_0_copy_longestMatch3_local;
	Shared_lookAhead__global_0_0 lookAhead__global_0_0_copy_longestMatch3_local;

	// Thread body -------------------------------------------------
	longestMatch3__thread: {
		// Initialise the local copies of shared variables.
		window__global_0_0_copy_longestMatch3_local.value = window__global_0_0.value;
		window__global_0_0_copy_longestMatch3_local.status = FOREC_SHARED_UNMODIFIED;
		lookAhead__global_0_0_copy_longestMatch3_local.value = lookAhead__global_0_0.value;
		lookAhead__global_0_0_copy_longestMatch3_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		longestMatch(window__global_0_0_copy_longestMatch3_local.value, lookAhead__global_0_0_copy_longestMatch3_local.value, 3, &offset_thread_ptr__global_0_0.value, &matches_thread_ptr__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:longestMatch3:start

		// Delete thread from the linked list and core.
		mainParCore3.activeThreads--;
		longestMatch3__thread.nextThread -> prevThread = longestMatch3__thread.prevThread;
		longestMatch3__thread.prevThread -> nextThread = longestMatch3__thread.nextThread;
		goto *longestMatch3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:longestMatch3:end
	} // longestMatch3__thread
	// forec:thread:longestMatch3:end


} // End of the main() function.

void openFile(void) {
	archiveInfo__global_0_0.fileaddr = archive__global_0_0;
	fileInfo__global_0_0.totalSize = 0;
	fileInfo__global_0_0.bytesProcessed = 0;
	fileInfo__global_0_0.fileaddr = embedded__global_0_0;
	fileInfo__global_0_0.p_file = embedded__global_0_0;
	obtainFileInfo(&fileInfo__global_0_0);
	createDescriptor(&fileInfo__global_0_0, &archiveInfo__global_0_0);
}

int getFileSize(void) {
	return fileInfo__global_0_0.totalSize;
}

int getBytesProcessed(void) {
	if (fileInfo__global_0_0.bytesProcessed < fileInfo__global_0_0.totalSize) {
		return fileInfo__global_0_0.bytesProcessed;
	} else {
		// ifElse1
		return fileInfo__global_0_0.totalSize;
	}
}

void createDescriptor(struct fileStats__global_0_0 *fileInfo__createDescriptor_0_0, struct fileStats__global_0_0 *archiveInfo__createDescriptor_0_0) {
	storeFileInfo(fileInfo__createDescriptor_0_0, archiveInfo__createDescriptor_0_0);
}

void obtainFileInfo(struct fileStats__global_0_0 *fileInfo__obtainFileInfo_0_0) {
	fileInfo__obtainFileInfo_0_0->filesize = FILE_SIZE__global_0_0;
	fileInfo__obtainFileInfo_0_0->totalSize = fileInfo__obtainFileInfo_0_0->filesize;
}

void storeFileInfo(struct fileStats__global_0_0 *fileInfo__storeFileInfo_0_0, struct fileStats__global_0_0 *archiveInfo__storeFileInfo_0_0) {
	mwrite(&(fileInfo__storeFileInfo_0_0->filesize), 4, 1, &archiveInfo__storeFileInfo_0_0->p_file);
}

void longestMatch(const Fifo__global_0_0 win__longestMatch_0_0, const Fifo__global_0_0 lk__longestMatch_0_0, int begin__longestMatch_0_0, int ** offset_thread__longestMatch_0_0, int ** matches_thread__longestMatch_0_0) {
	int NUM_THREADS__longestMatch_0_0 = 4;
	int _matches__longestMatch_0_0 = 0;
	(* matches_thread__longestMatch_0_0)[begin__longestMatch_0_0] = 0;
	int i__longestMatch_0_0, j__longestMatch_0_0, k__longestMatch_0_0, _offset__longestMatch_0_0;
	for (i__longestMatch_0_0 = begin__longestMatch_0_0; i__longestMatch_0_0 < win__longestMatch_0_0.written_size && Fifo_at(&win__longestMatch_0_0, i__longestMatch_0_0);) {
		j__longestMatch_0_0 = 0;
		_offset__longestMatch_0_0 = i__longestMatch_0_0;
		for (k__longestMatch_0_0 = i__longestMatch_0_0; j__longestMatch_0_0 < LKLENGTH__global_0_0 && Fifo_at(&win__longestMatch_0_0, k__longestMatch_0_0) == Fifo_at(&lk__longestMatch_0_0, j__longestMatch_0_0);) {
			_matches__longestMatch_0_0++;
			j__longestMatch_0_0++;
			k__longestMatch_0_0++;
			if (k__longestMatch_0_0 == win__longestMatch_0_0.written_size) {
				k__longestMatch_0_0 = 0;
			} else {
				// if2
			}
			asm volatile ("nop");
		}
		if (_matches__longestMatch_0_0 > (* matches_thread__longestMatch_0_0)[begin__longestMatch_0_0]) {
			(* matches_thread__longestMatch_0_0)[begin__longestMatch_0_0] = _matches__longestMatch_0_0;
			(* offset_thread__longestMatch_0_0)[begin__longestMatch_0_0] = _offset__longestMatch_0_0;
		} else {
			// if3
		}
		i__longestMatch_0_0 += NUM_THREADS__longestMatch_0_0;
		_matches__longestMatch_0_0 = 0;
		asm volatile ("nop");
	}
}

void writeToArchive(const Fifo__global_0_0 *fifo__writeToArchive_0_0, int *offset__writeToArchive_0_0, int *matches__writeToArchive_0_0, struct fileStats__global_0_0 *archiveInfo__writeToArchive_0_0, int *offset_thread__writeToArchive_0_0, int *matches_thread__writeToArchive_0_0, Fifo__global_0_0 *window__writeToArchive_0_0, Fifo__global_0_0 *lookAhead__writeToArchive_0_0) {
	int NUM_THREADS__writeToArchive_0_0 = 4;
	int EOF__writeToArchive_0_0 = -1;
	* matches__writeToArchive_0_0 = 0;
	int i__writeToArchive_0_0;
	for (i__writeToArchive_0_0 = 0; i__writeToArchive_0_0 < NUM_THREADS__writeToArchive_0_0; i__writeToArchive_0_0++) {
		if (matches_thread__writeToArchive_0_0[i__writeToArchive_0_0] > * matches__writeToArchive_0_0) {
			* matches__writeToArchive_0_0 = matches_thread__writeToArchive_0_0[i__writeToArchive_0_0];
			* offset__writeToArchive_0_0 = offset_thread__writeToArchive_0_0[i__writeToArchive_0_0];
		} else {
			// if4
		}
		asm volatile ("nop");
	}
	int encode__writeToArchive_0_0 = 0x800000;
	encode__writeToArchive_0_0 += (* offset__writeToArchive_0_0 << 5) + (* matches__writeToArchive_0_0 - 1);
	if (* matches__writeToArchive_0_0 > 2) {
		fileInfo__global_0_0.bytesProcessed += * matches__writeToArchive_0_0;
		mputc(encode__writeToArchive_0_0 >> 16, &archiveInfo__writeToArchive_0_0->p_file);
		mputc(encode__writeToArchive_0_0 >> 8, &archiveInfo__writeToArchive_0_0->p_file);
		mputc(encode__writeToArchive_0_0, &archiveInfo__writeToArchive_0_0->p_file);
	} else {
		// ifElse7
		if (Fifo_at(fifo__writeToArchive_0_0, 0) != EOF__writeToArchive_0_0) {
			fileInfo__global_0_0.bytesProcessed++;
			mputc(Fifo_at(fifo__writeToArchive_0_0, 0), &archiveInfo__writeToArchive_0_0->p_file);
			if (* matches__writeToArchive_0_0 == 2 && Fifo_at(fifo__writeToArchive_0_0, 1) != EOF__writeToArchive_0_0) {
				fileInfo__global_0_0.bytesProcessed++;
				mputc(Fifo_at(fifo__writeToArchive_0_0, 1), &archiveInfo__writeToArchive_0_0->p_file);
			} else {
				// if5
			}
		} else {
			// if6
		}
	}
	if (fileInfo__global_0_0.bytesProcessed >= fileInfo__global_0_0.totalSize) {
		int count__writeToArchive_1_2 = 1;
		do {
			if (window__writeToArchive_0_0->written_size >= WINLENGTH__global_0_0) {
				Fifo_pop_front(window__writeToArchive_0_0);
			} else {
				// if8
			}
			Fifo_push_back(window__writeToArchive_0_0, Fifo_pop_front(lookAhead__writeToArchive_0_0));
			Fifo_push_back(lookAhead__writeToArchive_0_0, mgetc(&fileInfo__global_0_0.p_file));
			asm volatile ("nop");
		} while (count__writeToArchive_1_2++ < * matches__writeToArchive_0_0);
		* matches__writeToArchive_0_0 = 0;
		for (count__writeToArchive_1_2 = 0; count__writeToArchive_1_2 < LKLENGTH__global_0_0 - 1 && Fifo_at(lookAhead__writeToArchive_0_0, 0) != EOF__writeToArchive_0_0; count__writeToArchive_1_2++) {
			mputc(Fifo_at(lookAhead__writeToArchive_0_0, 0), &archiveInfo__writeToArchive_0_0->p_file);
			Fifo_pop_front(lookAhead__writeToArchive_0_0);
			asm volatile ("nop");
		}
	} else {
		// if9
	}
}

void printResult(struct fileStats__global_0_0 *fileInfo__printResult_0_0, struct fileStats__global_0_0 *archiveInfo__printResult_0_0) {
	obtainFileInfo(archiveInfo__printResult_0_0);
}

void unpackArchive(char *filename__unpackArchive_0_0, int *offset__unpackArchive_0_0, int *matches__unpackArchive_0_0, struct fileStats__global_0_0 *fileInfo__unpackArchive_0_0, struct fileStats__global_0_0 *archiveInfo__unpackArchive_0_0) {}

void processDescriptor(struct fileStats__global_0_0 *fileInfo__processDescriptor_0_0, struct fileStats__global_0_0 *archiveInfo__processDescriptor_0_0) {}

void decompressFile(int *offset__decompressFile_0_0, int *matches__decompressFile_0_0, struct fileStats__global_0_0 *fileInfo__decompressFile_0_0, struct fileStats__global_0_0 *archiveInfo__decompressFile_0_0) {}

void decode(Fifo__global_0_0 *win__decode_0_0, int *sizeCount__decode_0_0, int *offset__decode_0_0, int *matches__decode_0_0, struct fileStats__global_0_0 *fileInfo__decode_0_0, struct fileStats__global_0_0 *archiveInfo__decode_0_0) {}

void Fifo_init(Fifo__global_0_0 *fifo__Fifo_init_0_0, unsigned size__Fifo_init_0_0, char *buf__Fifo_init_0_0) {
	fifo__Fifo_init_0_0->begin = 0;
	fifo__Fifo_init_0_0->end = 0;
	fifo__Fifo_init_0_0->size = size__Fifo_init_0_0;
	fifo__Fifo_init_0_0->written_size = 0;
	fifo__Fifo_init_0_0->data = buf__Fifo_init_0_0;
}

void Fifo_destroy(Fifo__global_0_0 *fifo__Fifo_destroy_0_0) {}

int Fifo_push_front(Fifo__global_0_0 *fifo__Fifo_push_front_0_0, char c__Fifo_push_front_0_0) {
	if (fifo__Fifo_push_front_0_0->written_size == 0) {
		Fifo_push_back(fifo__Fifo_push_front_0_0, c__Fifo_push_front_0_0);
	} else {
		// ifElse11
		if (fifo__Fifo_push_front_0_0->written_size >= fifo__Fifo_push_front_0_0->size) {
			return -1;
		} else {
			// if10
		}
	}
	fifo__Fifo_push_front_0_0->begin--;
	if (fifo__Fifo_push_front_0_0->begin < 0) {
		fifo__Fifo_push_front_0_0->begin = fifo__Fifo_push_front_0_0->size - 1;
	} else {
		// if12
	}
	fifo__Fifo_push_front_0_0->data[fifo__Fifo_push_front_0_0->begin] = c__Fifo_push_front_0_0;
	fifo__Fifo_push_front_0_0->written_size++;
	return 0;
}

int Fifo_push_back(Fifo__global_0_0 *fifo__Fifo_push_back_0_0, char c__Fifo_push_back_0_0) {
	if (fifo__Fifo_push_back_0_0->written_size >= fifo__Fifo_push_back_0_0->size) {
		return -1;
	} else {
		// if13
	}
	fifo__Fifo_push_back_0_0->written_size++;
	fifo__Fifo_push_back_0_0->data[fifo__Fifo_push_back_0_0->end] = c__Fifo_push_back_0_0;
	fifo__Fifo_push_back_0_0->end++;
	if (fifo__Fifo_push_back_0_0->end == fifo__Fifo_push_back_0_0->size) {
		fifo__Fifo_push_back_0_0->end = 0;
	} else {
		// if14
	}
	return 0;
}

char Fifo_pop_front(Fifo__global_0_0 *fifo__Fifo_pop_front_0_0) {
	if (fifo__Fifo_pop_front_0_0->written_size == 0) {
		return -1;
	} else {
		// if15
	}
	char c__Fifo_pop_front_0_0 = fifo__Fifo_pop_front_0_0->data[fifo__Fifo_pop_front_0_0->begin];
	fifo__Fifo_pop_front_0_0->written_size--;
	fifo__Fifo_pop_front_0_0->begin++;
	if (fifo__Fifo_pop_front_0_0->begin == fifo__Fifo_pop_front_0_0->size) {
		fifo__Fifo_pop_front_0_0->begin = 0;
	} else {
		// if16
	}
	return c__Fifo_pop_front_0_0;
}

char Fifo_pop_back(Fifo__global_0_0 *fifo__Fifo_pop_back_0_0) {
	if (fifo__Fifo_pop_back_0_0->written_size == 0) {
		return -1;
	} else {
		// if17
	}
	fifo__Fifo_pop_back_0_0->written_size--;
	fifo__Fifo_pop_back_0_0->end--;
	if (fifo__Fifo_pop_back_0_0->end < 0) {
		fifo__Fifo_pop_back_0_0->end = fifo__Fifo_pop_back_0_0->size - 1;
	} else {
		// if18
	}
	return fifo__Fifo_pop_back_0_0->data[fifo__Fifo_pop_back_0_0->end];
}

char Fifo_at(const Fifo__global_0_0 *fifo__Fifo_at_0_0, unsigned i__Fifo_at_0_0) {
	if (i__Fifo_at_0_0 < fifo__Fifo_at_0_0->written_size) {
		return fifo__Fifo_at_0_0->data[(fifo__Fifo_at_0_0->begin + i__Fifo_at_0_0)%fifo__Fifo_at_0_0->size];
	} else {
		// ifElse19
		return -1;
	}
}

void Fifo_print(const Fifo__global_0_0 *fifo__Fifo_print_0_0) {
	int i__Fifo_print_0_0, j__Fifo_print_0_0;
	for (i__Fifo_print_0_0 = fifo__Fifo_print_0_0->begin, j__Fifo_print_0_0 = 0; j__Fifo_print_0_0 < fifo__Fifo_print_0_0->written_size; i__Fifo_print_0_0++, j__Fifo_print_0_0++) {
		if (i__Fifo_print_0_0 == fifo__Fifo_print_0_0->size) {
			i__Fifo_print_0_0 = 0;
		} else {
			// if20
		}
		asm volatile ("nop");
	}
}

int mgetc(char ** stream__mgetc_0_0) {
	char *c__mgetc_0_0 = * stream__mgetc_0_0++;
	return * c__mgetc_0_0;
}

int mputc(char c__mputc_0_0, char ** stream__mputc_0_0) {
	* * stream__mputc_0_0 = c__mputc_0_0;
	stream__mputc_0_0++;
	return c__mputc_0_0;
}

int mwrite(const void *ptr__mwrite_0_0, int size__mwrite_0_0, int nmemb__mwrite_0_0, char ** stream__mwrite_0_0) {
	int n__mwrite_0_0, s__mwrite_0_0, ret__mwrite_0_0 = 0;
	for (n__mwrite_0_0 = 0; n__mwrite_0_0 < nmemb__mwrite_0_0; n__mwrite_0_0++) {
		for (s__mwrite_0_0 = 0; s__mwrite_0_0 < size__mwrite_0_0; s__mwrite_0_0++) {
			* * stream__mwrite_0_0 = * ((char *)ptr__mwrite_0_0);
			stream__mwrite_0_0++;
			ret__mwrite_0_0++;
			asm volatile ("nop");
		}
		asm volatile ("nop");
	}
	return ret__mwrite_0_0;
}

