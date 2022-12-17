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
unsigned int forec_mutex_value_do_draw;
unsigned int forec_mutex_value_do_step;

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
// Thread do_draw with par(...)s
Parent do_drawParParent = { .parStatusCond = PTHREAD_COND_INITIALIZER, .parStatusLock = PTHREAD_MUTEX_INITIALIZER };
Core do_drawParCore0 = { .statusCond = PTHREAD_COND_INITIALIZER, .statusLock = PTHREAD_MUTEX_INITIALIZER, .reactionCounterCond = PTHREAD_COND_INITIALIZER, .reactionCounterLock = PTHREAD_MUTEX_INITIALIZER};
volatile int do_drawParReactionCounter;
pthread_cond_t do_drawParReactionCounterCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t do_drawParReactionCounterLock = PTHREAD_MUTEX_INITIALIZER;

// Thread do_step with par(...)s
Parent do_stepParParent = { .parStatusCond = PTHREAD_COND_INITIALIZER, .parStatusLock = PTHREAD_MUTEX_INITIALIZER };
Core do_stepParCore0 = { .statusCond = PTHREAD_COND_INITIALIZER, .statusLock = PTHREAD_MUTEX_INITIALIZER, .reactionCounterCond = PTHREAD_COND_INITIALIZER, .reactionCounterLock = PTHREAD_MUTEX_INITIALIZER};
volatile int do_stepParReactionCounter;
pthread_cond_t do_stepParReactionCounterCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t do_stepParReactionCounterLock = PTHREAD_MUTEX_INITIALIZER;

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
#include <time.h>
#include <unistd.h>   // So we got the profile for 10 seconds

typedef void time_t__global_0_0;

#define time_t__global_0_0 time_t

int RAND_MAX__global_0_0;

#define RAND_MAX__global_0_0 RAND_MAX

int blackColor__global_0_0;
int whiteColor__global_0_0;
static const int numXGrayscale__global_0_0 = 10;
static const int FALSE__global_0_0 = 0;
static const int TRUE__global_0_0 = 1;
static const int PIXEL_SIZE__global_0_0 = 4 - 1;
static const int MAX_GENERATIONS__global_0_0 = 10000;

struct life_datum__global_0_0 {
	int color;
	int x1;
	int y1;
};

struct life_datum__global_0_0 ** life_data__global_0_0;

typedef struct {
	/* shared */ struct life_datum__global_0_0 *** value;
	int status;
} Shared_life_data_ptr__global_0_0;
Shared_life_data_ptr__global_0_0 life_data_ptr__global_0_0 = {.value = &life_data__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

int ** grid__global_0_0;

typedef struct {
	/* shared */ int (*** value);
	int status;
} Shared_grid_ptr__global_0_0;
Shared_grid_ptr__global_0_0 grid_ptr__global_0_0 = {.value = &grid__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

int ** next_grid__global_0_0;

typedef struct {
	/* shared */ int (*** value);
	int status;
} Shared_next_grid_ptr__global_0_0;
Shared_next_grid_ptr__global_0_0 next_grid_ptr__global_0_0 = {.value = &next_grid__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

void allocate_grid(const int ncols, const int nrows, int *** grid);
void allocate_life_data(const int ncols, const int nrows, struct life_datum__global_0_0 *** life_data);
void cleanup_grid(const int ncols, const int nrows, int *** grid);
void cleanup_life_data(const int ncols, const int nrows, struct life_datum__global_0_0 *** life_data);
void randomize_grid(const int ncols, const int nrows, int *** grid, const double prob);
double rand_double(void);
void update_grid(const int threadNumber, int *** next_grid, int ** grid);
void update_display(const int threadNumber, struct life_datum__global_0_0 *** life_data_ptr, int ** grid);
void transfer_grid(const int threadNumber, int ** grid, int *** nextgrid);

// thread initialise_grid__thread(void);
// thread initialise_next_grid__thread(void);
// thread initialise_life_data__thread(void);
// thread random_initByTime__thread(void);
// thread initialise_randomize_grid__thread(void);
// thread do_draw__thread(void);
// thread do_step__thread(void);
// thread do_step_0__thread(void);
// thread do_step_1__thread(void);
// thread do_step_2__thread(void);
// thread do_step_3__thread(void);
// thread do_draw_0__thread(void);
// thread do_draw_1__thread(void);
// thread do_draw_2__thread(void);
// thread do_draw_3__thread(void);
// thread transfer_grid_0__thread(void);
// thread transfer_grid_1__thread(void);
// thread transfer_grid_2__thread(void);
// thread transfer_grid_3__thread(void);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// do_draw
Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_draw = {.status = FOREC_SHARED_UNMODIFIED};
// do_draw_0
Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_draw_0 = {.status = FOREC_SHARED_UNMODIFIED};
// do_draw_1
Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_draw_1 = {.status = FOREC_SHARED_UNMODIFIED};
// do_draw_2
Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_draw_2 = {.status = FOREC_SHARED_UNMODIFIED};
// do_draw_3
Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_draw_3 = {.status = FOREC_SHARED_UNMODIFIED};
// do_step
Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_step = {.status = FOREC_SHARED_UNMODIFIED};
// do_step_0
Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_step_0 = {.status = FOREC_SHARED_UNMODIFIED};
// do_step_1
Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_step_1 = {.status = FOREC_SHARED_UNMODIFIED};
// do_step_2
Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_step_2 = {.status = FOREC_SHARED_UNMODIFIED};
// do_step_3
Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_step_3 = {.status = FOREC_SHARED_UNMODIFIED};
// initialise_grid
// initialise_life_data
// initialise_next_grid
// initialise_randomize_grid
// main
// random_initByTime
// transfer_grid_0
Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_transfer_grid_0 = {.status = FOREC_SHARED_UNMODIFIED};
// transfer_grid_1
Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_transfer_grid_1 = {.status = FOREC_SHARED_UNMODIFIED};
// transfer_grid_2
Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_transfer_grid_2 = {.status = FOREC_SHARED_UNMODIFIED};
// transfer_grid_3
Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_transfer_grid_3 = {.status = FOREC_SHARED_UNMODIFIED};

// forec:scheduler:boot:start
int main(int argc__main_0_0, char ** argv__main_0_0) {

/*==============================================================
| Multicore startup:
| Platform dependent code.  Core identifies itself and
| executes its corresponding start up code.
*=============================================================*/
	programStatus = RUNNING;

	// Initialise ForeC specific values ---------------------------
	// Thread do_draw with par(...)s
	do_drawParParent.parStatus = FOREC_PAR_OFF;
	do_drawParCore0.sync = 1;
	do_drawParCore0.status = FOREC_CORE_REACTING;
	do_drawParReactionCounter = 0;

	// Thread do_step with par(...)s
	do_stepParParent.parStatus = FOREC_PAR_OFF;
	do_stepParCore0.sync = 1;
	do_stepParCore0.status = FOREC_CORE_REACTING;
	do_stepParReactionCounter = 0;

	// Thread main with par(...)s
	mainParParent.parStatus = FOREC_PAR_OFF;
	mainParCore0.sync = 1;
	mainParCore0.status = FOREC_CORE_REACTING;
	mainParReactionCounter = 0;


	// Reset ForeC mutex values
	forec_mutex_value_do_draw = -1;
	forec_mutex_value_do_step = -1;

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
	Thread initialise_grid__thread;
	Thread initialise_life_data__thread;
	Thread initialise_next_grid__thread;
	Thread initialise_randomize_grid__thread;
	Thread random_initByTime__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionEndMaster0;

	// par1
	Thread do_draw__thread;
	Thread do_step__thread;
	// Thread mainReactionStartMaster0;
	// Thread mainReactionEndMaster0;
	Thread do_drawParHandlerMaster0;
	Thread do_stepParHandlerMaster0;

	// par2
	Thread transfer_grid_0__thread;
	Thread transfer_grid_1__thread;
	Thread transfer_grid_2__thread;
	Thread transfer_grid_3__thread;
	// Thread mainReactionStartMaster0;
	// Thread mainReactionEndMaster0;

	// par3
	Thread do_step_0__thread;
	Thread do_step_1__thread;
	Thread do_step_2__thread;
	Thread do_step_3__thread;
	Thread do_stepReactionStartMaster0;
	Thread do_stepReactionEndMaster0;

	// par4
	Thread do_draw_0__thread;
	Thread do_draw_1__thread;
	Thread do_draw_2__thread;
	Thread do_draw_3__thread;
	Thread do_drawReactionStartMaster0;
	Thread do_drawReactionEndMaster0;


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
	int ncols__main_0_0;
	int nrows__main_0_0;
	int done__main_0_0;
	int generation__main_0_0;
	long seconds__main_0_0;
	int microseconds__main_0_0;

mainParCore0: {
	// forec:scheduler:counter:start
	// Initialise and start timing each reaction.
	clockTimeUs.previous = getClockTimeUs();
	// forec:scheduler:counter:end
	
	//--------------------------------------------------------------

	gettimeofday(&startTime__main_0_0, 0);
	ncols__main_0_0 = 250;
	nrows__main_0_0 = 25*4;

	// par0(initialise_grid__thread, initialise_next_grid__thread, initialise_life_data__thread, random_initByTime__thread, initialise_randomize_grid__thread);
	// forec:statement:par:par0:start
	// Set the par(...) information.
	mainParParent.parId = 0;
	pthread_mutex_lock(&mainParParent.parStatusLock);
	mainParParent.parStatus = FOREC_PAR_ON;
	pthread_cond_broadcast(&mainParParent.parStatusCond);
	pthread_mutex_unlock(&mainParParent.parStatusLock);

	// Link the threads and handlers together.
	mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
	initialise_grid__thread.programCounter = &&initialise_grid__thread;
	mainReactionStartMaster0.nextThread = &initialise_grid__thread;
	initialise_grid__thread.prevThread = &mainReactionStartMaster0;
	initialise_next_grid__thread.programCounter = &&initialise_next_grid__thread;
	initialise_grid__thread.nextThread = &initialise_next_grid__thread;
	initialise_next_grid__thread.prevThread = &initialise_grid__thread;
	initialise_life_data__thread.programCounter = &&initialise_life_data__thread;
	initialise_next_grid__thread.nextThread = &initialise_life_data__thread;
	initialise_life_data__thread.prevThread = &initialise_next_grid__thread;
	random_initByTime__thread.programCounter = &&random_initByTime__thread;
	initialise_life_data__thread.nextThread = &random_initByTime__thread;
	random_initByTime__thread.prevThread = &initialise_life_data__thread;
	initialise_randomize_grid__thread.programCounter = &&initialise_randomize_grid__thread;
	random_initByTime__thread.nextThread = &initialise_randomize_grid__thread;
	initialise_randomize_grid__thread.prevThread = &random_initByTime__thread;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	initialise_randomize_grid__thread.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &initialise_randomize_grid__thread;

	// Link the last and first threads/handlers together.
	mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
	mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

	// Set the join address.
	mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

	// Set the core information.
	mainParCore0.activeThreads = 5;
	mainParCore0.reactionCounter = mainParReactionCounter;

	// Go to the first thread.
	goto initialise_grid__thread;
	par0JoinAddress_mainParCore0:;
	// forec:statement:par:par0:end

	done__main_0_0 = FALSE__global_0_0;
	generation__main_0_0 = 0;

	while (!done__main_0_0) {
		if (generation__main_0_0++ > MAX_GENERATIONS__global_0_0) {
			done__main_0_0 = TRUE__global_0_0;
		} else {
			// if0
		}

		// par1(do_step__thread, do_draw__thread);
		// forec:statement:par:par1:start
		// Set the par(...) information.
		mainParParent.parId = 1;
		pthread_mutex_lock(&mainParParent.parStatusLock);
		mainParParent.parStatus = FOREC_PAR_ON;
		pthread_cond_broadcast(&mainParParent.parStatusCond);
		pthread_mutex_unlock(&mainParParent.parStatusLock);

		// Link the threads and handlers together.
		mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
		do_step__thread.programCounter = &&do_step__thread;
		mainReactionStartMaster0.nextThread = &do_step__thread;
		do_step__thread.prevThread = &mainReactionStartMaster0;
		do_stepParHandlerMaster0.programCounter = &&do_stepParHandlerMaster0;
		do_step__thread.nextThread = &do_stepParHandlerMaster0;
		do_stepParHandlerMaster0.prevThread = &do_step__thread;
		do_draw__thread.programCounter = &&do_draw__thread;
		do_stepParHandlerMaster0.nextThread = &do_draw__thread;
		do_draw__thread.prevThread = &do_stepParHandlerMaster0;
		do_drawParHandlerMaster0.programCounter = &&do_drawParHandlerMaster0;
		do_draw__thread.nextThread = &do_drawParHandlerMaster0;
		do_drawParHandlerMaster0.prevThread = &do_draw__thread;
		mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
		do_drawParHandlerMaster0.nextThread = &mainReactionEndMaster0;
		mainReactionEndMaster0.prevThread = &do_drawParHandlerMaster0;

		// Link the last and first threads/handlers together.
		mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
		mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

		// Set the join address.
		mainParParent.programCounter = &&par1JoinAddress_mainParCore0;

		// Set the core information.
		mainParCore0.activeThreads = 4;
		mainParCore0.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto do_step__thread;
		par1JoinAddress_mainParCore0:;
		// forec:statement:par:par1:end

		// par2(transfer_grid_0__thread, transfer_grid_1__thread, transfer_grid_2__thread, transfer_grid_3__thread);
		// forec:statement:par:par2:start
		// Set the par(...) information.
		mainParParent.parId = 2;
		pthread_mutex_lock(&mainParParent.parStatusLock);
		mainParParent.parStatus = FOREC_PAR_ON;
		pthread_cond_broadcast(&mainParParent.parStatusCond);
		pthread_mutex_unlock(&mainParParent.parStatusLock);

		// Link the threads and handlers together.
		mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
		transfer_grid_0__thread.programCounter = &&transfer_grid_0__thread;
		mainReactionStartMaster0.nextThread = &transfer_grid_0__thread;
		transfer_grid_0__thread.prevThread = &mainReactionStartMaster0;
		transfer_grid_1__thread.programCounter = &&transfer_grid_1__thread;
		transfer_grid_0__thread.nextThread = &transfer_grid_1__thread;
		transfer_grid_1__thread.prevThread = &transfer_grid_0__thread;
		transfer_grid_2__thread.programCounter = &&transfer_grid_2__thread;
		transfer_grid_1__thread.nextThread = &transfer_grid_2__thread;
		transfer_grid_2__thread.prevThread = &transfer_grid_1__thread;
		transfer_grid_3__thread.programCounter = &&transfer_grid_3__thread;
		transfer_grid_2__thread.nextThread = &transfer_grid_3__thread;
		transfer_grid_3__thread.prevThread = &transfer_grid_2__thread;
		mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
		transfer_grid_3__thread.nextThread = &mainReactionEndMaster0;
		mainReactionEndMaster0.prevThread = &transfer_grid_3__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
		mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

		// Set the join address.
		mainParParent.programCounter = &&par2JoinAddress_mainParCore0;

		// Set the core information.
		mainParCore0.activeThreads = 4;
		mainParCore0.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto transfer_grid_0__thread;
		par2JoinAddress_mainParCore0:;
		// forec:statement:par:par2:end

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
		// forec:iteration:while_0:bound:1000:1000
	}

	cleanup_grid(ncols__main_0_0, nrows__main_0_0, &grid__global_0_0);
	cleanup_grid(ncols__main_0_0, nrows__main_0_0, &next_grid__global_0_0);
	cleanup_life_data(ncols__main_0_0, nrows__main_0_0, &life_data__global_0_0);
	gettimeofday(&endTime__main_0_0, 0);
	seconds__main_0_0 = endTime__main_0_0.tv_sec - startTime__main_0_0.tv_sec;
	microseconds__main_0_0 = endTime__main_0_0.tv_usec - startTime__main_0_0.tv_usec;
	if (microseconds__main_0_0 < 0) {
		microseconds__main_0_0 += 1000000;
		seconds__main_0_0--;
	} else {
		// if1
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
	// forec:scheduler:parHandler:do_draw:master:0:start
	//-- Thread do_draw par(...) handlers
do_drawParHandlerMaster0: {
	// Check the execution status of the nested par(...)s.
	if (do_drawParParent.parStatus == FOREC_PAR_OFF) {
		// Release the mutex.
		forec_mutex_value_do_draw &= 0x7fffffff;

		goto *do_drawParHandlerMaster0.nextThread -> programCounter;
	}
	// Release the mutex.
	forec_mutex_value_do_draw &= 0x7fffffff;

	int parId = do_drawParParent.parId;

	// Check the par(...) ID.
	if (parId == 4) {
		asm ("# par4 begin");
		// Link the threads and handlers together.
		do_drawReactionStartMaster0.programCounter = &&do_drawReactionStartMaster0;
		do_draw_0__thread.programCounter = &&do_draw_0__thread;
		do_drawReactionStartMaster0.nextThread = &do_draw_0__thread;
		do_draw_0__thread.prevThread = &do_drawReactionStartMaster0;
		do_draw_1__thread.programCounter = &&do_draw_1__thread;
		do_draw_0__thread.nextThread = &do_draw_1__thread;
		do_draw_1__thread.prevThread = &do_draw_0__thread;
		do_draw_2__thread.programCounter = &&do_draw_2__thread;
		do_draw_1__thread.nextThread = &do_draw_2__thread;
		do_draw_2__thread.prevThread = &do_draw_1__thread;
		do_draw_3__thread.programCounter = &&do_draw_3__thread;
		do_draw_2__thread.nextThread = &do_draw_3__thread;
		do_draw_3__thread.prevThread = &do_draw_2__thread;
		do_drawReactionEndMaster0.programCounter = &&do_drawReactionEndMaster0;
		do_draw_3__thread.nextThread = &do_drawReactionEndMaster0;
		do_drawReactionEndMaster0.prevThread = &do_draw_3__thread;

		// Swap the nested par handler with the linked list.
		do_drawParHandlerMaster0.prevThread -> nextThread = &do_drawReactionStartMaster0;
		do_drawReactionStartMaster0.prevThread = do_drawParHandlerMaster0.prevThread;
		do_drawReactionEndMaster0.nextThread = do_drawParHandlerMaster0.nextThread;
		do_drawParHandlerMaster0.nextThread -> prevThread = &do_drawReactionEndMaster0;
		
		// Set the core information.
		do_drawParCore0.activeThreads = 4;
		do_drawParCore0.reactionCounter = do_drawParReactionCounter;
		
		// Go to the first thread.
		goto do_draw_0__thread;
		asm ("# par4 end");
	} else if (parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.

		pthread_mutex_lock(&do_drawParParent.parStatusLock);
		do_drawParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&do_drawParParent.parStatusCond);
		pthread_mutex_unlock(&do_drawParParent.parStatusLock);
		do_drawParParent.parId = -1;

		forec_mutex_value_do_draw = -1;

		// Set slave cores' status to reacting.

		// Increment the reaction counter for synchronisation.
		pthread_mutex_lock(&do_drawParReactionCounterLock);
		do_drawParReactionCounter++;
		pthread_cond_broadcast(&do_drawParReactionCounterCond);
		pthread_mutex_unlock(&do_drawParReactionCounterLock);

		// Return to thread do_draw.
		goto *do_drawParParent.programCounter;
	} else if (parId == -3) {
		// Thread termination
		mainParCore0.activeThreads--;
		do_drawParCore0.activeThreads--;

		// Wait for other cores to complete their reaction.

		pthread_mutex_lock(&do_drawParParent.parStatusLock);
		do_drawParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&do_drawParParent.parStatusCond);
		pthread_mutex_unlock(&do_drawParParent.parStatusLock);
		do_drawParParent.parId = -1;

		// Set slave cores' status to reacting.

		// Increment the reaction counter for synchronisation.
		pthread_mutex_lock(&do_drawParReactionCounterLock);
		do_drawParReactionCounter++;
		pthread_cond_broadcast(&do_drawParReactionCounterCond);
		pthread_mutex_unlock(&do_drawParReactionCounterLock);

		// Delete this par(...) handler.
		do_drawParHandlerMaster0.prevThread -> nextThread = do_drawParHandlerMaster0.nextThread;
		do_drawParHandlerMaster0.nextThread -> prevThread = do_drawParHandlerMaster0.prevThread;
			
		// Return to thread do_draw.
		goto *do_drawParParent.programCounter;
	} else {
		// Unscheduled par(...)
		do_drawParCore0.reactionCounter = do_drawParReactionCounter;

		do_drawParHandlerMaster0.programCounter = &&wrongParId_do_drawParHandlerMaster0;
		wrongParId_do_drawParHandlerMaster0:;

		pthread_mutex_lock(&do_drawParCore0.statusLock);
		do_drawParCore0.status = FOREC_CORE_TERMINATED;
		pthread_cond_signal(&do_drawParCore0.statusCond);
		pthread_mutex_unlock(&do_drawParCore0.statusLock);

		// Wait for the next tick.
		pthread_mutex_lock(&do_drawParReactionCounterLock);
		while (do_drawParCore0.reactionCounter == do_drawParReactionCounter) { pthread_cond_wait(&do_drawParReactionCounterCond, &do_drawParReactionCounterLock); }
		pthread_mutex_unlock(&do_drawParReactionCounterLock);
		do_drawParCore0.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (do_drawParParent.parStatus == FOREC_PAR_ON && do_drawParParent.parId == parId) {
			goto *do_drawParHandlerMaster0.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		do_drawParHandlerMaster0.programCounter = &&do_drawParHandlerMaster0;
		
		goto do_drawParHandlerMaster0;
	}
	
	// Control should not reach here.
	goto do_drawParHandlerMaster0;
}
	// forec:scheduler:parHandler:do_draw:master:0:end
 	// forec:scheduler:parHandler:do_step:master:0:start
	//-- Thread do_step par(...) handlers
do_stepParHandlerMaster0: {
	// Check the execution status of the nested par(...)s.
	if (do_stepParParent.parStatus == FOREC_PAR_OFF) {
		// Release the mutex.
		forec_mutex_value_do_step &= 0xbfffffff;

		goto *do_stepParHandlerMaster0.nextThread -> programCounter;
	}
	// Release the mutex.
	forec_mutex_value_do_step &= 0xbfffffff;

	int parId = do_stepParParent.parId;

	// Check the par(...) ID.
	if (parId == 3) {
		asm ("# par3 begin");
		// Link the threads and handlers together.
		do_stepReactionStartMaster0.programCounter = &&do_stepReactionStartMaster0;
		do_step_0__thread.programCounter = &&do_step_0__thread;
		do_stepReactionStartMaster0.nextThread = &do_step_0__thread;
		do_step_0__thread.prevThread = &do_stepReactionStartMaster0;
		do_step_1__thread.programCounter = &&do_step_1__thread;
		do_step_0__thread.nextThread = &do_step_1__thread;
		do_step_1__thread.prevThread = &do_step_0__thread;
		do_step_2__thread.programCounter = &&do_step_2__thread;
		do_step_1__thread.nextThread = &do_step_2__thread;
		do_step_2__thread.prevThread = &do_step_1__thread;
		do_step_3__thread.programCounter = &&do_step_3__thread;
		do_step_2__thread.nextThread = &do_step_3__thread;
		do_step_3__thread.prevThread = &do_step_2__thread;
		do_stepReactionEndMaster0.programCounter = &&do_stepReactionEndMaster0;
		do_step_3__thread.nextThread = &do_stepReactionEndMaster0;
		do_stepReactionEndMaster0.prevThread = &do_step_3__thread;

		// Swap the nested par handler with the linked list.
		do_stepParHandlerMaster0.prevThread -> nextThread = &do_stepReactionStartMaster0;
		do_stepReactionStartMaster0.prevThread = do_stepParHandlerMaster0.prevThread;
		do_stepReactionEndMaster0.nextThread = do_stepParHandlerMaster0.nextThread;
		do_stepParHandlerMaster0.nextThread -> prevThread = &do_stepReactionEndMaster0;
		
		// Set the core information.
		do_stepParCore0.activeThreads = 4;
		do_stepParCore0.reactionCounter = do_stepParReactionCounter;
		
		// Go to the first thread.
		goto do_step_0__thread;
		asm ("# par3 end");
	} else if (parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.

		pthread_mutex_lock(&do_stepParParent.parStatusLock);
		do_stepParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&do_stepParParent.parStatusCond);
		pthread_mutex_unlock(&do_stepParParent.parStatusLock);
		do_stepParParent.parId = -1;

		forec_mutex_value_do_step = -1;

		// Set slave cores' status to reacting.

		// Increment the reaction counter for synchronisation.
		pthread_mutex_lock(&do_stepParReactionCounterLock);
		do_stepParReactionCounter++;
		pthread_cond_broadcast(&do_stepParReactionCounterCond);
		pthread_mutex_unlock(&do_stepParReactionCounterLock);

		// Return to thread do_step.
		goto *do_stepParParent.programCounter;
	} else if (parId == -3) {
		// Thread termination
		mainParCore0.activeThreads--;
		do_stepParCore0.activeThreads--;

		// Wait for other cores to complete their reaction.

		pthread_mutex_lock(&do_stepParParent.parStatusLock);
		do_stepParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&do_stepParParent.parStatusCond);
		pthread_mutex_unlock(&do_stepParParent.parStatusLock);
		do_stepParParent.parId = -1;

		// Set slave cores' status to reacting.

		// Increment the reaction counter for synchronisation.
		pthread_mutex_lock(&do_stepParReactionCounterLock);
		do_stepParReactionCounter++;
		pthread_cond_broadcast(&do_stepParReactionCounterCond);
		pthread_mutex_unlock(&do_stepParReactionCounterLock);

		// Delete this par(...) handler.
		do_stepParHandlerMaster0.prevThread -> nextThread = do_stepParHandlerMaster0.nextThread;
		do_stepParHandlerMaster0.nextThread -> prevThread = do_stepParHandlerMaster0.prevThread;
			
		// Return to thread do_step.
		goto *do_stepParParent.programCounter;
	} else {
		// Unscheduled par(...)
		do_stepParCore0.reactionCounter = do_stepParReactionCounter;

		do_stepParHandlerMaster0.programCounter = &&wrongParId_do_stepParHandlerMaster0;
		wrongParId_do_stepParHandlerMaster0:;

		pthread_mutex_lock(&do_stepParCore0.statusLock);
		do_stepParCore0.status = FOREC_CORE_TERMINATED;
		pthread_cond_signal(&do_stepParCore0.statusCond);
		pthread_mutex_unlock(&do_stepParCore0.statusLock);

		// Wait for the next tick.
		pthread_mutex_lock(&do_stepParReactionCounterLock);
		while (do_stepParCore0.reactionCounter == do_stepParReactionCounter) { pthread_cond_wait(&do_stepParReactionCounterCond, &do_stepParReactionCounterLock); }
		pthread_mutex_unlock(&do_stepParReactionCounterLock);
		do_stepParCore0.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (do_stepParParent.parStatus == FOREC_PAR_ON && do_stepParParent.parId == parId) {
			goto *do_stepParHandlerMaster0.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		do_stepParHandlerMaster0.programCounter = &&do_stepParHandlerMaster0;
		
		goto do_stepParHandlerMaster0;
	}
	
	// Control should not reach here.
	goto do_stepParHandlerMaster0;
}
	// forec:scheduler:parHandler:do_step:master:0:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:do_draw:master:0:start
	//-- do_draw:
do_drawReactionStartMaster0: {
	// Go to the next thread.
	goto *do_drawReactionStartMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:do_draw:master:0:end
 
	// forec:scheduler:reactionStart:do_step:master:0:start
	//-- do_step:
do_stepReactionStartMaster0: {
	// Go to the next thread.
	goto *do_stepReactionStartMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:do_step:master:0:end
 
	// forec:scheduler:reactionStart:main:master:0:start
	//-- main:
mainReactionStartMaster0: {
	// Go to the next thread.
	goto *mainReactionStartMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:master:0:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:do_draw:master:0:start
	//-- do_draw:
do_drawReactionEndMaster0: {
	// Determine if the core can still react or not.
	pthread_mutex_lock(&do_drawParCore0.statusLock);
	if (do_drawParCore0.activeThreads) {
		do_drawParCore0.status = FOREC_CORE_REACTED;
	} else {
		do_drawParCore0.status = FOREC_CORE_TERMINATED;
	}
	pthread_cond_signal(&do_drawParCore0.statusCond);
	pthread_mutex_unlock(&do_drawParCore0.statusLock);
	
	// Wait for other cores to complete their reaction.


	// Return back to the parent thread if all the cores have terminated.
	if (1 && do_drawParCore0.status == FOREC_CORE_TERMINATED) {
		forec_mutex_value_do_draw = -1;

		pthread_mutex_lock(&do_drawParParent.parStatusLock);
		do_drawParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&do_drawParParent.parStatusCond);
		pthread_mutex_unlock(&do_drawParParent.parStatusLock);
		do_drawParParent.parId = -1;
		
		// Set slave cores' status to reacting

		// Increment the reaction counter for synchronization.
		pthread_mutex_lock(&do_drawParReactionCounterLock);
		do_drawParReactionCounter++;
		pthread_cond_broadcast(&do_drawParReactionCounterCond);
		pthread_mutex_unlock(&do_drawParReactionCounterLock);

		// Swap the reaction (start & end) handlers with (thread do_draw & nested par handler).
		do_drawReactionStartMaster0.prevThread -> nextThread = &do_draw__thread;
		do_draw__thread.prevThread = do_drawReactionStartMaster0.prevThread;
		do_draw__thread.nextThread = &do_drawParHandlerMaster0;
		do_drawParHandlerMaster0.prevThread = &do_draw__thread;
		do_drawParHandlerMaster0.nextThread = do_drawReactionEndMaster0.nextThread;
		do_drawReactionEndMaster0.nextThread -> prevThread = &do_drawParHandlerMaster0;

		goto *do_drawParParent.programCounter;
	}

	// Set slave cores' status to reacting

	// Increment the reaction counter for synchronization.
	pthread_mutex_lock(&do_drawParReactionCounterLock);
	do_drawParReactionCounter++;
	pthread_cond_broadcast(&do_drawParReactionCounterCond);
	pthread_mutex_unlock(&do_drawParReactionCounterLock);

	// Go to the next thread.
	goto *do_drawReactionEndMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:do_draw:master:0:end
 
	// forec:scheduler:reactionEnd:do_step:master:0:start
	//-- do_step:
do_stepReactionEndMaster0: {
	// Determine if the core can still react or not.
	pthread_mutex_lock(&do_stepParCore0.statusLock);
	if (do_stepParCore0.activeThreads) {
		do_stepParCore0.status = FOREC_CORE_REACTED;
	} else {
		do_stepParCore0.status = FOREC_CORE_TERMINATED;
	}
	pthread_cond_signal(&do_stepParCore0.statusCond);
	pthread_mutex_unlock(&do_stepParCore0.statusLock);
	
	// Wait for other cores to complete their reaction.


	// Return back to the parent thread if all the cores have terminated.
	if (1 && do_stepParCore0.status == FOREC_CORE_TERMINATED) {
		forec_mutex_value_do_step = -1;

		pthread_mutex_lock(&do_stepParParent.parStatusLock);
		do_stepParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&do_stepParParent.parStatusCond);
		pthread_mutex_unlock(&do_stepParParent.parStatusLock);
		do_stepParParent.parId = -1;
		
		// Set slave cores' status to reacting

		// Increment the reaction counter for synchronization.
		pthread_mutex_lock(&do_stepParReactionCounterLock);
		do_stepParReactionCounter++;
		pthread_cond_broadcast(&do_stepParReactionCounterCond);
		pthread_mutex_unlock(&do_stepParReactionCounterLock);

		// Swap the reaction (start & end) handlers with (thread do_step & nested par handler).
		do_stepReactionStartMaster0.prevThread -> nextThread = &do_step__thread;
		do_step__thread.prevThread = do_stepReactionStartMaster0.prevThread;
		do_step__thread.nextThread = &do_stepParHandlerMaster0;
		do_stepParHandlerMaster0.prevThread = &do_step__thread;
		do_stepParHandlerMaster0.nextThread = do_stepReactionEndMaster0.nextThread;
		do_stepReactionEndMaster0.nextThread -> prevThread = &do_stepParHandlerMaster0;

		goto *do_stepParParent.programCounter;
	}

	// Set slave cores' status to reacting

	// Increment the reaction counter for synchronization.
	pthread_mutex_lock(&do_stepParReactionCounterLock);
	do_stepParReactionCounter++;
	pthread_cond_broadcast(&do_stepParReactionCounterCond);
	pthread_mutex_unlock(&do_stepParReactionCounterLock);

	// Go to the next thread.
	goto *do_stepReactionEndMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:do_step:master:0:end
 
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
	forec_mutex_value_do_draw = -1;
	forec_mutex_value_do_step = -1;

	// Combine shared variables.
	int parId = mainParParent.parId;
	if (parId == 1) {

		// grid_ptr__global_0_0
		if (grid_ptr__global_0_0_copy_do_draw.status == FOREC_SHARED_MODIFIED) {
			grid_ptr__global_0_0_copy_do_draw.status = FOREC_SHARED_UNMODIFIED;
			grid_ptr__global_0_0.value = grid_ptr__global_0_0_copy_do_draw.value;
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
	// forec:thread:do_draw:start
	/*--------------------------------------------------------------
	| Thread do_draw
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_draw_local;

	// Thread body -------------------------------------------------
	do_draw__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_do_draw_local.value = grid_ptr__global_0_0.value;
		grid_ptr__global_0_0_copy_do_draw_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		grid_ptr__global_0_0_copy_do_draw_local.value = grid_ptr__global_0_0_copy_do_draw_local.value;
		grid_ptr__global_0_0_copy_do_draw_local.status = FOREC_SHARED_MODIFIED;

		// par4(do_draw_0__thread, do_draw_1__thread, do_draw_2__thread, do_draw_3__thread);
		grid_ptr__global_0_0_copy_do_draw = grid_ptr__global_0_0_copy_do_draw_local;
		// Set the par(...) information.
		// forec:statement:par:par4:start
		do_drawParParent.parId = 4;
		pthread_mutex_lock(&do_drawParParent.parStatusLock);
		do_drawParParent.parStatus = FOREC_PAR_ON;
		pthread_cond_broadcast(&do_drawParParent.parStatusCond);
		pthread_mutex_unlock(&do_drawParParent.parStatusLock);
		do_drawParParent.programCounter = &&par4JoinAddress_do_drawParParent;

		// Remove this thread from the linked list.
		do_draw__thread.nextThread -> prevThread = do_draw__thread.prevThread;
		do_draw__thread.prevThread -> nextThread = do_draw__thread.nextThread;
		goto do_drawParHandlerMaster0;
		par4JoinAddress_do_drawParParent:;
		// forec:statement:par:par4:end
		if (grid_ptr__global_0_0_copy_do_draw.status == FOREC_SHARED_MODIFIED) {
			grid_ptr__global_0_0_copy_do_draw_local = grid_ptr__global_0_0_copy_do_draw;
		} else {
			grid_ptr__global_0_0_copy_do_draw_local = grid_ptr__global_0_0;
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		grid_ptr__global_0_0_copy_do_draw = grid_ptr__global_0_0_copy_do_draw_local;

		// forec:scheduler:threadRemove:do_draw:start
		// Delete par handler
		do_drawParParent.parId = -3;
		do_drawParParent.parStatus = FOREC_PAR_ON;
		do_drawParParent.programCounter = &&do_draw_endAddress;
		goto do_drawParHandlerMaster0;
		do_draw_endAddress:;

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		do_draw__thread.nextThread -> prevThread = do_draw__thread.prevThread;
		do_draw__thread.prevThread -> nextThread = do_draw__thread.nextThread;
		goto *do_draw__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:do_draw:end
	} // do_draw__thread
	// forec:thread:do_draw:end

	// forec:thread:do_draw_0:start
	/*--------------------------------------------------------------
	| Thread do_draw_0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_draw_0_local;

	// Thread body -------------------------------------------------
	do_draw_0__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_do_draw_0_local.value = grid_ptr__global_0_0_copy_do_draw.value;
		grid_ptr__global_0_0_copy_do_draw_0_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		update_display(0, life_data_ptr__global_0_0.value, * grid_ptr__global_0_0_copy_do_draw_0_local.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_draw_0:start

		// Delete thread from the linked list and core.
		do_drawParCore0.activeThreads--;
		do_draw_0__thread.nextThread -> prevThread = do_draw_0__thread.prevThread;
		do_draw_0__thread.prevThread -> nextThread = do_draw_0__thread.nextThread;
		goto *do_draw_0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:do_draw_0:end
	} // do_draw_0__thread
	// forec:thread:do_draw_0:end

	// forec:thread:do_draw_1:start
	/*--------------------------------------------------------------
	| Thread do_draw_1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_draw_1_local;

	// Thread body -------------------------------------------------
	do_draw_1__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_do_draw_1_local.value = grid_ptr__global_0_0_copy_do_draw.value;
		grid_ptr__global_0_0_copy_do_draw_1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		update_display(1, life_data_ptr__global_0_0.value, * grid_ptr__global_0_0_copy_do_draw_1_local.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_draw_1:start

		// Delete thread from the linked list and core.
		do_drawParCore0.activeThreads--;
		do_draw_1__thread.nextThread -> prevThread = do_draw_1__thread.prevThread;
		do_draw_1__thread.prevThread -> nextThread = do_draw_1__thread.nextThread;
		goto *do_draw_1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:do_draw_1:end
	} // do_draw_1__thread
	// forec:thread:do_draw_1:end

	// forec:thread:do_draw_2:start
	/*--------------------------------------------------------------
	| Thread do_draw_2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_draw_2_local;

	// Thread body -------------------------------------------------
	do_draw_2__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_do_draw_2_local.value = grid_ptr__global_0_0_copy_do_draw.value;
		grid_ptr__global_0_0_copy_do_draw_2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		update_display(2, life_data_ptr__global_0_0.value, * grid_ptr__global_0_0_copy_do_draw_2_local.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_draw_2:start

		// Delete thread from the linked list and core.
		do_drawParCore0.activeThreads--;
		do_draw_2__thread.nextThread -> prevThread = do_draw_2__thread.prevThread;
		do_draw_2__thread.prevThread -> nextThread = do_draw_2__thread.nextThread;
		goto *do_draw_2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:do_draw_2:end
	} // do_draw_2__thread
	// forec:thread:do_draw_2:end

	// forec:thread:do_draw_3:start
	/*--------------------------------------------------------------
	| Thread do_draw_3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_draw_3_local;

	// Thread body -------------------------------------------------
	do_draw_3__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_do_draw_3_local.value = grid_ptr__global_0_0_copy_do_draw.value;
		grid_ptr__global_0_0_copy_do_draw_3_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		update_display(3, life_data_ptr__global_0_0.value, * grid_ptr__global_0_0_copy_do_draw_3_local.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_draw_3:start

		// Delete thread from the linked list and core.
		do_drawParCore0.activeThreads--;
		do_draw_3__thread.nextThread -> prevThread = do_draw_3__thread.prevThread;
		do_draw_3__thread.prevThread -> nextThread = do_draw_3__thread.nextThread;
		goto *do_draw_3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:do_draw_3:end
	} // do_draw_3__thread
	// forec:thread:do_draw_3:end

	// forec:thread:do_step:start
	/*--------------------------------------------------------------
	| Thread do_step
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_step_local;
	int ncols__do_step_0_0;
	int nrows__do_step_0_0;
	int i__do_step_0_0;

	// Thread body -------------------------------------------------
	do_step__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_do_step_local.value = grid_ptr__global_0_0.value;
		grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		ncols__do_step_0_0 = 250;
		nrows__do_step_0_0 = 25*4;
		for (i__do_step_0_0 = 0; i__do_step_0_0 <= nrows__do_step_0_0 + 1; i__do_step_0_0++) {
			(* grid_ptr__global_0_0_copy_do_step_local.value)[0][i__do_step_0_0] = (* grid_ptr__global_0_0_copy_do_step_local.value)[1][i__do_step_0_0];
			grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_MODIFIED;
			(* grid_ptr__global_0_0_copy_do_step_local.value)[ncols__do_step_0_0 + 1][i__do_step_0_0] = (* grid_ptr__global_0_0_copy_do_step_local.value)[ncols__do_step_0_0][i__do_step_0_0];
			grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_MODIFIED;
			// forec:iteration:for1_1:bound:252:252
		}
		for (i__do_step_0_0 = 1; i__do_step_0_0 <= ncols__do_step_0_0; i__do_step_0_0++) {
			(* grid_ptr__global_0_0_copy_do_step_local.value)[i__do_step_0_0][0] = (* grid_ptr__global_0_0_copy_do_step_local.value)[i__do_step_0_0][nrows__do_step_0_0];
			grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_MODIFIED;
			(* grid_ptr__global_0_0_copy_do_step_local.value)[i__do_step_0_0][nrows__do_step_0_0 + 1] = (* grid_ptr__global_0_0_copy_do_step_local.value)[i__do_step_0_0][1];
			grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_MODIFIED;
			// forec:iteration:for1_2:bound:100:100
		}
		(* grid_ptr__global_0_0_copy_do_step_local.value)[0][0] = (* grid_ptr__global_0_0_copy_do_step_local.value)[0][nrows__do_step_0_0];
		grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_MODIFIED;
		(* grid_ptr__global_0_0_copy_do_step_local.value)[0][nrows__do_step_0_0 + 1] = (* grid_ptr__global_0_0_copy_do_step_local.value)[0][1];
		grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_MODIFIED;
		(* grid_ptr__global_0_0_copy_do_step_local.value)[ncols__do_step_0_0 + 1][0] = (* grid_ptr__global_0_0_copy_do_step_local.value)[ncols__do_step_0_0 + 1][nrows__do_step_0_0];
		grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_MODIFIED;
		(* grid_ptr__global_0_0_copy_do_step_local.value)[ncols__do_step_0_0 + 1][nrows__do_step_0_0 + 1] = (* grid_ptr__global_0_0_copy_do_step_local.value)[ncols__do_step_0_0 + 1][1];
		grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_MODIFIED;

		// par3(do_step_0__thread, do_step_1__thread, do_step_2__thread, do_step_3__thread);
		grid_ptr__global_0_0_copy_do_step = grid_ptr__global_0_0_copy_do_step_local;
		// Set the par(...) information.
		// forec:statement:par:par3:start
		do_stepParParent.parId = 3;
		pthread_mutex_lock(&do_stepParParent.parStatusLock);
		do_stepParParent.parStatus = FOREC_PAR_ON;
		pthread_cond_broadcast(&do_stepParParent.parStatusCond);
		pthread_mutex_unlock(&do_stepParParent.parStatusLock);
		do_stepParParent.programCounter = &&par3JoinAddress_do_stepParParent;

		// Remove this thread from the linked list.
		do_step__thread.nextThread -> prevThread = do_step__thread.prevThread;
		do_step__thread.prevThread -> nextThread = do_step__thread.nextThread;
		goto do_stepParHandlerMaster0;
		par3JoinAddress_do_stepParParent:;
		// forec:statement:par:par3:end
		if (grid_ptr__global_0_0_copy_do_step.status == FOREC_SHARED_MODIFIED) {
			grid_ptr__global_0_0_copy_do_step_local = grid_ptr__global_0_0_copy_do_step;
		} else {
			grid_ptr__global_0_0_copy_do_step_local = grid_ptr__global_0_0;
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_step:start
		// Delete par handler
		do_stepParParent.parId = -3;
		do_stepParParent.parStatus = FOREC_PAR_ON;
		do_stepParParent.programCounter = &&do_step_endAddress;
		goto do_stepParHandlerMaster0;
		do_step_endAddress:;

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		do_step__thread.nextThread -> prevThread = do_step__thread.prevThread;
		do_step__thread.prevThread -> nextThread = do_step__thread.nextThread;
		goto *do_step__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:do_step:end
	} // do_step__thread
	// forec:thread:do_step:end

	// forec:thread:do_step_0:start
	/*--------------------------------------------------------------
	| Thread do_step_0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_step_0_local;

	// Thread body -------------------------------------------------
	do_step_0__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_do_step_0_local.value = grid_ptr__global_0_0_copy_do_step.value;
		grid_ptr__global_0_0_copy_do_step_0_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		update_grid(0, next_grid_ptr__global_0_0.value, * grid_ptr__global_0_0_copy_do_step_0_local.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_step_0:start

		// Delete thread from the linked list and core.
		do_stepParCore0.activeThreads--;
		do_step_0__thread.nextThread -> prevThread = do_step_0__thread.prevThread;
		do_step_0__thread.prevThread -> nextThread = do_step_0__thread.nextThread;
		goto *do_step_0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:do_step_0:end
	} // do_step_0__thread
	// forec:thread:do_step_0:end

	// forec:thread:do_step_1:start
	/*--------------------------------------------------------------
	| Thread do_step_1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_step_1_local;

	// Thread body -------------------------------------------------
	do_step_1__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_do_step_1_local.value = grid_ptr__global_0_0_copy_do_step.value;
		grid_ptr__global_0_0_copy_do_step_1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		update_grid(1, next_grid_ptr__global_0_0.value, * grid_ptr__global_0_0_copy_do_step_1_local.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_step_1:start

		// Delete thread from the linked list and core.
		do_stepParCore0.activeThreads--;
		do_step_1__thread.nextThread -> prevThread = do_step_1__thread.prevThread;
		do_step_1__thread.prevThread -> nextThread = do_step_1__thread.nextThread;
		goto *do_step_1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:do_step_1:end
	} // do_step_1__thread
	// forec:thread:do_step_1:end

	// forec:thread:do_step_2:start
	/*--------------------------------------------------------------
	| Thread do_step_2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_step_2_local;

	// Thread body -------------------------------------------------
	do_step_2__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_do_step_2_local.value = grid_ptr__global_0_0_copy_do_step.value;
		grid_ptr__global_0_0_copy_do_step_2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		update_grid(2, next_grid_ptr__global_0_0.value, * grid_ptr__global_0_0_copy_do_step_2_local.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_step_2:start

		// Delete thread from the linked list and core.
		do_stepParCore0.activeThreads--;
		do_step_2__thread.nextThread -> prevThread = do_step_2__thread.prevThread;
		do_step_2__thread.prevThread -> nextThread = do_step_2__thread.nextThread;
		goto *do_step_2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:do_step_2:end
	} // do_step_2__thread
	// forec:thread:do_step_2:end

	// forec:thread:do_step_3:start
	/*--------------------------------------------------------------
	| Thread do_step_3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_do_step_3_local;

	// Thread body -------------------------------------------------
	do_step_3__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_do_step_3_local.value = grid_ptr__global_0_0_copy_do_step.value;
		grid_ptr__global_0_0_copy_do_step_3_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		update_grid(3, next_grid_ptr__global_0_0.value, * grid_ptr__global_0_0_copy_do_step_3_local.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_step_3:start

		// Delete thread from the linked list and core.
		do_stepParCore0.activeThreads--;
		do_step_3__thread.nextThread -> prevThread = do_step_3__thread.prevThread;
		do_step_3__thread.prevThread -> nextThread = do_step_3__thread.nextThread;
		goto *do_step_3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:do_step_3:end
	} // do_step_3__thread
	// forec:thread:do_step_3:end

	// forec:thread:initialise_grid:start
	/*--------------------------------------------------------------
	| Thread initialise_grid
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	int ncols__initialise_grid_0_0;
	int nrows__initialise_grid_0_0;

	// Thread body -------------------------------------------------
	initialise_grid__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		ncols__initialise_grid_0_0 = 250;
		nrows__initialise_grid_0_0 = 25*4;
		allocate_grid(ncols__initialise_grid_0_0, nrows__initialise_grid_0_0, grid_ptr__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:initialise_grid:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		initialise_grid__thread.nextThread -> prevThread = initialise_grid__thread.prevThread;
		initialise_grid__thread.prevThread -> nextThread = initialise_grid__thread.nextThread;
		goto *initialise_grid__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:initialise_grid:end
	} // initialise_grid__thread
	// forec:thread:initialise_grid:end

	// forec:thread:initialise_life_data:start
	/*--------------------------------------------------------------
	| Thread initialise_life_data
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	int ncols__initialise_life_data_0_0;
	int nrows__initialise_life_data_0_0;

	// Thread body -------------------------------------------------
	initialise_life_data__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		ncols__initialise_life_data_0_0 = 250;
		nrows__initialise_life_data_0_0 = 25*4;
		allocate_life_data(ncols__initialise_life_data_0_0, nrows__initialise_life_data_0_0, life_data_ptr__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:initialise_life_data:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		initialise_life_data__thread.nextThread -> prevThread = initialise_life_data__thread.prevThread;
		initialise_life_data__thread.prevThread -> nextThread = initialise_life_data__thread.nextThread;
		goto *initialise_life_data__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:initialise_life_data:end
	} // initialise_life_data__thread
	// forec:thread:initialise_life_data:end

	// forec:thread:initialise_next_grid:start
	/*--------------------------------------------------------------
	| Thread initialise_next_grid
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	int ncols__initialise_next_grid_0_0;
	int nrows__initialise_next_grid_0_0;

	// Thread body -------------------------------------------------
	initialise_next_grid__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		ncols__initialise_next_grid_0_0 = 250;
		nrows__initialise_next_grid_0_0 = 25*4;
		allocate_grid(ncols__initialise_next_grid_0_0, nrows__initialise_next_grid_0_0, next_grid_ptr__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:initialise_next_grid:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		initialise_next_grid__thread.nextThread -> prevThread = initialise_next_grid__thread.prevThread;
		initialise_next_grid__thread.prevThread -> nextThread = initialise_next_grid__thread.nextThread;
		goto *initialise_next_grid__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:initialise_next_grid:end
	} // initialise_next_grid__thread
	// forec:thread:initialise_next_grid:end

	// forec:thread:initialise_randomize_grid:start
	/*--------------------------------------------------------------
	| Thread initialise_randomize_grid
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	int ncols__initialise_randomize_grid_0_0;
	int nrows__initialise_randomize_grid_0_0;

	// Thread body -------------------------------------------------
	initialise_randomize_grid__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		ncols__initialise_randomize_grid_0_0 = 250;
		nrows__initialise_randomize_grid_0_0 = 25*4;
		randomize_grid(ncols__initialise_randomize_grid_0_0, nrows__initialise_randomize_grid_0_0, grid_ptr__global_0_0.value, 0.25);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:initialise_randomize_grid:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		initialise_randomize_grid__thread.nextThread -> prevThread = initialise_randomize_grid__thread.prevThread;
		initialise_randomize_grid__thread.prevThread -> nextThread = initialise_randomize_grid__thread.nextThread;
		goto *initialise_randomize_grid__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:initialise_randomize_grid:end
	} // initialise_randomize_grid__thread
	// forec:thread:initialise_randomize_grid:end

	// forec:thread:random_initByTime:start
	/*--------------------------------------------------------------
	| Thread random_initByTime
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	time_t__global_0_0 ltime__random_initByTime_0_0;

	// Thread body -------------------------------------------------
	random_initByTime__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		time(&ltime__random_initByTime_0_0);
		srand((unsigned)ltime__random_initByTime_0_0);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:random_initByTime:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		random_initByTime__thread.nextThread -> prevThread = random_initByTime__thread.prevThread;
		random_initByTime__thread.prevThread -> nextThread = random_initByTime__thread.nextThread;
		goto *random_initByTime__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:random_initByTime:end
	} // random_initByTime__thread
	// forec:thread:random_initByTime:end

	// forec:thread:transfer_grid_0:start
	/*--------------------------------------------------------------
	| Thread transfer_grid_0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_transfer_grid_0_local;

	// Thread body -------------------------------------------------
	transfer_grid_0__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_transfer_grid_0_local.value = grid_ptr__global_0_0.value;
		grid_ptr__global_0_0_copy_transfer_grid_0_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		transfer_grid(0, * grid_ptr__global_0_0_copy_transfer_grid_0_local.value, next_grid_ptr__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:transfer_grid_0:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		transfer_grid_0__thread.nextThread -> prevThread = transfer_grid_0__thread.prevThread;
		transfer_grid_0__thread.prevThread -> nextThread = transfer_grid_0__thread.nextThread;
		goto *transfer_grid_0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:transfer_grid_0:end
	} // transfer_grid_0__thread
	// forec:thread:transfer_grid_0:end

	// forec:thread:transfer_grid_1:start
	/*--------------------------------------------------------------
	| Thread transfer_grid_1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_transfer_grid_1_local;

	// Thread body -------------------------------------------------
	transfer_grid_1__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_transfer_grid_1_local.value = grid_ptr__global_0_0.value;
		grid_ptr__global_0_0_copy_transfer_grid_1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		transfer_grid(1, * grid_ptr__global_0_0_copy_transfer_grid_1_local.value, next_grid_ptr__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:transfer_grid_1:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		transfer_grid_1__thread.nextThread -> prevThread = transfer_grid_1__thread.prevThread;
		transfer_grid_1__thread.prevThread -> nextThread = transfer_grid_1__thread.nextThread;
		goto *transfer_grid_1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:transfer_grid_1:end
	} // transfer_grid_1__thread
	// forec:thread:transfer_grid_1:end

	// forec:thread:transfer_grid_2:start
	/*--------------------------------------------------------------
	| Thread transfer_grid_2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_transfer_grid_2_local;

	// Thread body -------------------------------------------------
	transfer_grid_2__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_transfer_grid_2_local.value = grid_ptr__global_0_0.value;
		grid_ptr__global_0_0_copy_transfer_grid_2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		transfer_grid(2, * grid_ptr__global_0_0_copy_transfer_grid_2_local.value, next_grid_ptr__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:transfer_grid_2:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		transfer_grid_2__thread.nextThread -> prevThread = transfer_grid_2__thread.prevThread;
		transfer_grid_2__thread.prevThread -> nextThread = transfer_grid_2__thread.nextThread;
		goto *transfer_grid_2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:transfer_grid_2:end
	} // transfer_grid_2__thread
	// forec:thread:transfer_grid_2:end

	// forec:thread:transfer_grid_3:start
	/*--------------------------------------------------------------
	| Thread transfer_grid_3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_grid_ptr__global_0_0 grid_ptr__global_0_0_copy_transfer_grid_3_local;

	// Thread body -------------------------------------------------
	transfer_grid_3__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_transfer_grid_3_local.value = grid_ptr__global_0_0.value;
		grid_ptr__global_0_0_copy_transfer_grid_3_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		transfer_grid(3, * grid_ptr__global_0_0_copy_transfer_grid_3_local.value, next_grid_ptr__global_0_0.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:transfer_grid_3:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		transfer_grid_3__thread.nextThread -> prevThread = transfer_grid_3__thread.prevThread;
		transfer_grid_3__thread.prevThread -> nextThread = transfer_grid_3__thread.nextThread;
		goto *transfer_grid_3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:transfer_grid_3:end
	} // transfer_grid_3__thread
	// forec:thread:transfer_grid_3:end


} // End of the main() function.

void allocate_grid(const int ncols__allocate_grid_0_0, const int nrows__allocate_grid_0_0, int *** grid__allocate_grid_0_0) {
	(* grid__allocate_grid_0_0) = (int **)malloc((ncols__allocate_grid_0_0 + 2)*sizeof(int *));
	int i__allocate_grid_0_0;
	for (i__allocate_grid_0_0 = 0; i__allocate_grid_0_0 < ncols__allocate_grid_0_0 + 2; i__allocate_grid_0_0++) {
		(* grid__allocate_grid_0_0)[i__allocate_grid_0_0] = (int *)malloc((nrows__allocate_grid_0_0 + 2)*sizeof(int));
		int j__allocate_grid_1_0;
		for (j__allocate_grid_1_0 = 0; j__allocate_grid_1_0 < nrows__allocate_grid_0_0 + 2; j__allocate_grid_1_0++) {
			(* grid__allocate_grid_0_0)[i__allocate_grid_0_0][j__allocate_grid_1_0] = 0;
			// forec:iteration:for1_3:bound:102:102
		}
		// forec:iteration:for1_4:bound:252:252
	}
}

void allocate_life_data(const int ncols__allocate_life_data_0_0, const int nrows__allocate_life_data_0_0, struct life_datum__global_0_0 *** life_data__allocate_life_data_0_0) {
	(* life_data__allocate_life_data_0_0) = (struct life_datum__global_0_0 **)malloc((ncols__allocate_life_data_0_0)*sizeof(struct life_datum__global_0_0 *));
	int i__allocate_life_data_0_0;
	for (i__allocate_life_data_0_0 = 0; i__allocate_life_data_0_0 < ncols__allocate_life_data_0_0; i__allocate_life_data_0_0++) {
		(* life_data__allocate_life_data_0_0)[i__allocate_life_data_0_0] = (struct life_datum__global_0_0 *)malloc((nrows__allocate_life_data_0_0)*sizeof(struct life_datum__global_0_0));
		// forec:iteration:for1_5:bound:250:250
	}
}

void cleanup_grid(const int ncols__cleanup_grid_0_0, const int nrows__cleanup_grid_0_0, int *** grid__cleanup_grid_0_0) {
	int i__cleanup_grid_0_0;
	for (i__cleanup_grid_0_0 = 0; i__cleanup_grid_0_0 < ncols__cleanup_grid_0_0 + 2; i__cleanup_grid_0_0++) {
		free((* grid__cleanup_grid_0_0)[i__cleanup_grid_0_0]);
		// forec:iteration:for1_6:bound:252:252
	}
	free(* grid__cleanup_grid_0_0);
}

void cleanup_life_data(const int ncols__cleanup_life_data_0_0, const int nrows__cleanup_life_data_0_0, struct life_datum__global_0_0 *** life_data__cleanup_life_data_0_0) {
	int i__cleanup_life_data_0_0;
	for (i__cleanup_life_data_0_0 = 0; i__cleanup_life_data_0_0 < ncols__cleanup_life_data_0_0; i__cleanup_life_data_0_0++) {
		free((* life_data__cleanup_life_data_0_0)[i__cleanup_life_data_0_0]);
		// forec:iteration:for1_7:bound:100:100
	}
	free(* life_data__cleanup_life_data_0_0);
}

void randomize_grid(const int ncols__randomize_grid_0_0, const int nrows__randomize_grid_0_0, int *** grid__randomize_grid_0_0, const double prob__randomize_grid_0_0) {
	int i__randomize_grid_0_0;
	for (i__randomize_grid_0_0 = 1; i__randomize_grid_0_0 <= ncols__randomize_grid_0_0; i__randomize_grid_0_0++) {
		int j__randomize_grid_1_0;
		for (j__randomize_grid_1_0 = 1; j__randomize_grid_1_0 <= nrows__randomize_grid_0_0; j__randomize_grid_1_0++) {
			if (rand_double() < prob__randomize_grid_0_0) {
				(* grid__randomize_grid_0_0)[i__randomize_grid_0_0][j__randomize_grid_1_0] = 1;
			} else {
				// if2
			}
			// forec:iteration:for1_8:bound:100:100
		}
		// forec:iteration:for1_9:bound:250:250
	}
}

double rand_double(void) {
	return (double)rand()/(double)RAND_MAX__global_0_0;
}

void update_grid(const int threadNumber__update_grid_0_0, int *** next_grid__update_grid_0_0, int ** grid__update_grid_0_0) {
	const int ncols__update_grid_0_0 = 250;
	const int RANGE__update_grid_0_0 = 25;
	const int startIndex__update_grid_0_0 = 1 + RANGE__update_grid_0_0*threadNumber__update_grid_0_0;
	const int endIndex__update_grid_0_0 = RANGE__update_grid_0_0*(threadNumber__update_grid_0_0 + 1);
	int i__update_grid_0_0;
	for (i__update_grid_0_0 = 1; i__update_grid_0_0 <= ncols__update_grid_0_0; i__update_grid_0_0++) {
		int j__update_grid_1_0;
		for (j__update_grid_1_0 = startIndex__update_grid_0_0; j__update_grid_1_0 <= endIndex__update_grid_0_0; j__update_grid_1_0++) {
			int neighbors__update_grid_2_0 = 0;
			int k__update_grid_2_0;
			for (k__update_grid_2_0 = i__update_grid_0_0 - 1; k__update_grid_2_0 <= i__update_grid_0_0 + 1; k__update_grid_2_0++) {
				int l__update_grid_3_0;
				for (l__update_grid_3_0 = j__update_grid_1_0 - 1; l__update_grid_3_0 <= j__update_grid_1_0 + 1; l__update_grid_3_0++) {
					if (!(k__update_grid_2_0 == i__update_grid_0_0 && l__update_grid_3_0 == j__update_grid_1_0) && grid__update_grid_0_0[k__update_grid_2_0][l__update_grid_3_0] > 0) {
						neighbors__update_grid_2_0++;
					} else {
						// if3
					}
					// forec:iteration:for1_10:bound:3:3
				}
				if (neighbors__update_grid_2_0 > 3) {
					continue;
				} else {
					// if4
				}
				// forec:iteration:for1_11:bound:3:3
			}
			if (neighbors__update_grid_2_0 < 2 || neighbors__update_grid_2_0 > 3) {
				(* next_grid__update_grid_0_0)[i__update_grid_0_0][j__update_grid_1_0] = 0;
			} else {
				// ifElse6
				if (grid__update_grid_0_0[i__update_grid_0_0][j__update_grid_1_0] > 0 || neighbors__update_grid_2_0 == 3) {
					(* next_grid__update_grid_0_0)[i__update_grid_0_0][j__update_grid_1_0] = grid__update_grid_0_0[i__update_grid_0_0][j__update_grid_1_0] + 1;
				} else {
					// if5
				}
			}
			// forec:iteration:for1_12:bound:25:25
		}
		// forec:iteration:for1_13:bound:250:250
	}
}

void update_display(const int threadNumber__update_display_0_0, struct life_datum__global_0_0 *** life_data__update_display_0_0, int ** grid__update_display_0_0) {
	const int ncols__update_display_0_0 = 250;
	const int RANGE__update_display_0_0 = 25;
	const int y1StartIndex__update_display_0_0 = 1 + RANGE__update_display_0_0*threadNumber__update_display_0_0;
	const int y1EndIndex__update_display_0_0 = RANGE__update_display_0_0*(threadNumber__update_display_0_0 + 1);
	int i__update_display_0_0;
	for (i__update_display_0_0 = 1; i__update_display_0_0 <= ncols__update_display_0_0; i__update_display_0_0++) {
		int x1__update_display_1_0 = (PIXEL_SIZE__global_0_0 + 1)*(i__update_display_0_0 - 1);
		int j__update_display_1_0;
		for (j__update_display_1_0 = y1StartIndex__update_display_0_0; j__update_display_1_0 <= y1EndIndex__update_display_0_0; j__update_display_1_0++) {
			int y1__update_display_2_0 = (PIXEL_SIZE__global_0_0 + 1)*(j__update_display_1_0 - 1);
			if (grid__update_display_0_0[i__update_display_0_0][j__update_display_1_0] > 0) {
				int life__update_display_3_0 = grid__update_display_0_0[i__update_display_0_0][j__update_display_1_0];
				if (life__update_display_3_0 > numXGrayscale__global_0_0 - 1) {
					life__update_display_3_0 = numXGrayscale__global_0_0 - 1;
				} else {
					// if7
				}
				(* life_data__update_display_0_0)[i__update_display_0_0 - 1][j__update_display_1_0 - 1].color = life__update_display_3_0;
			} else {
				// ifElse8
				(* life_data__update_display_0_0)[i__update_display_0_0 - 1][j__update_display_1_0 - 1].color = blackColor__global_0_0;
			}
			(* life_data__update_display_0_0)[i__update_display_0_0 - 1][j__update_display_1_0 - 1].x1 = x1__update_display_1_0;
			(* life_data__update_display_0_0)[i__update_display_0_0 - 1][j__update_display_1_0 - 1].y1 = y1__update_display_2_0;
			// forec:iteration:for1_14:bound:25:25
		}
		// forec:iteration:for1_15:bound:250:250
	}
}

void transfer_grid(const int threadNumber__transfer_grid_0_0, int ** grid__transfer_grid_0_0, int *** next_grid__transfer_grid_0_0) {
	const int ncols__transfer_grid_0_0 = 250;
	const int RANGE__transfer_grid_0_0 = 25;
	const int y1StartIndex__transfer_grid_0_0 = 1 + RANGE__transfer_grid_0_0*threadNumber__transfer_grid_0_0;
	const int y1EndIndex__transfer_grid_0_0 = RANGE__transfer_grid_0_0*(threadNumber__transfer_grid_0_0 + 1);
	int i__transfer_grid_0_0;
	for (i__transfer_grid_0_0 = 0; i__transfer_grid_0_0 < ncols__transfer_grid_0_0 + 2; i__transfer_grid_0_0++) {
		int j__transfer_grid_1_0;
		for (j__transfer_grid_1_0 = y1StartIndex__transfer_grid_0_0; j__transfer_grid_1_0 <= y1EndIndex__transfer_grid_0_0; j__transfer_grid_1_0++) {
			grid__transfer_grid_0_0[i__transfer_grid_0_0][j__transfer_grid_1_0] = (* next_grid__transfer_grid_0_0)[i__transfer_grid_0_0][j__transfer_grid_1_0];
			// forec:iteration:for1_16:bound:25:25
		}
		// forec:iteration:for1_17:bound:252:252
	}
}

