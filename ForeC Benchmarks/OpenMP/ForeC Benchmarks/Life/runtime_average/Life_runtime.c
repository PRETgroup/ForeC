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
// Thread do_draw with par(...)s
volatile Parent do_drawParParent;
volatile Core do_drawParCore0;
volatile Core do_drawParCore1;
volatile Core do_drawParCore2;
volatile Core do_drawParCore3;
volatile int do_drawParReactionCounter;

// Thread do_step with par(...)s
volatile Parent do_stepParParent;
volatile Core do_stepParCore0;
volatile Core do_stepParCore1;
volatile Core do_stepParCore2;
volatile Core do_stepParCore3;
volatile int do_stepParReactionCounter;

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
#include <time.h>
#include <unistd.h>   // So we got the profile for 10 seconds

typedef void time_t__global_0_0;

#define time_t__global_0_0 time_t

int RAND_MAX__global_0_0;

#define RAND_MAX__global_0_0 RAND_MAX

typedef void clockid_t__global_0_0;

#define clockid_t__global_0_0 clockid_t
#undef CLOCK_MONOTONIC

clockid_t__global_0_0 CLOCK_MONOTONIC__global_0_0 = 1;
int blackColor__global_0_0;
int whiteColor__global_0_0;
static const int numXGrayscale__global_0_0 = 10;
static const int FALSE__global_0_0 = 0;
static const int TRUE__global_0_0 = 1;
static const int PIXEL_SIZE__global_0_0 = 5 - 1;
static const int LIFE_IMAGE_WIDTH__global_0_0 = 250*5;
static const int LIFE_IMAGE_HEIGHT__global_0_0 = 25*4*5;
static const int MAX_GENERATIONS__global_0_0 = 10000;

struct life_datum__global_0_0 {
	int color;
	int x1;
	int y1;
};

struct life_datum__global_0_0 ** life_data__global_0_0;

typedef struct {
	/* shared */ struct life_datum__global_0_0 *** value;
	unsigned short int status;
} Shared_life_data__global_0_0;
Shared_life_data__global_0_0 life_data_ptr__global_0_0 = {.value = &life_data__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

int ** grid__global_0_0;

typedef struct {
	/* shared */ int *** value;
	unsigned short int status;
} Shared_grid__global_0_0;
Shared_grid__global_0_0 grid_ptr__global_0_0 = {.value = &grid__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

int ** next_grid__global_0_0;

typedef struct {
	/* shared */ int *** value;
	unsigned short int status;
} Shared_next_grid__global_0_0;
Shared_next_grid__global_0_0 next_grid_ptr__global_0_0 = {.value = &next_grid__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

void initialise(const int ncols, const int nrows, int *** grid, int *** next_grid, struct life_datum__global_0_0 *** life_data);
void allocate_grid(const int ncols, const int nrows, int *** grid);
void allocate_life_data(const int ncols, const int nrows, struct life_datum__global_0_0 *** life_data);
void cleanup_grid(const int ncols, const int nrows, int *** grid);
void cleanup_life_data(const int ncols, const int nrows, struct life_datum__global_0_0 *** life_data);
void randomize_grid(const int ncols, const int nrows, int *** grid, const double prob);
double rand_double(void);
void random_initByTime(void);
void update_grid(const int threadNumber, int *** next_grid, int ** grid);
void update_display(const int threadNumber, struct life_datum__global_0_0 *** life_data, int ** grid);

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

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// do_draw
Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_draw = {.status = FOREC_SHARED_UNMODIFIED};
// do_draw_0
Shared_life_data__global_0_0 life_data_ptr__global_0_0_copy_do_draw_0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_draw_0 = {.status = FOREC_SHARED_UNMODIFIED};
// do_draw_1
Shared_life_data__global_0_0 life_data_ptr__global_0_0_copy_do_draw_1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_draw_1 = {.status = FOREC_SHARED_UNMODIFIED};
// do_draw_2
Shared_life_data__global_0_0 life_data_ptr__global_0_0_copy_do_draw_2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_draw_2 = {.status = FOREC_SHARED_UNMODIFIED};
// do_draw_3
Shared_life_data__global_0_0 life_data_ptr__global_0_0_copy_do_draw_3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_draw_3 = {.status = FOREC_SHARED_UNMODIFIED};
// do_step
Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_step = {.status = FOREC_SHARED_UNMODIFIED};
// do_step_0
Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_step_0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_next_grid__global_0_0 next_grid_ptr__global_0_0_copy_do_step_0 = {.status = FOREC_SHARED_UNMODIFIED};
// do_step_1
Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_step_1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_next_grid__global_0_0 next_grid_ptr__global_0_0_copy_do_step_1 = {.status = FOREC_SHARED_UNMODIFIED};
// do_step_2
Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_step_2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_next_grid__global_0_0 next_grid_ptr__global_0_0_copy_do_step_2 = {.status = FOREC_SHARED_UNMODIFIED};
// do_step_3
Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_step_3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_next_grid__global_0_0 next_grid_ptr__global_0_0_copy_do_step_3 = {.status = FOREC_SHARED_UNMODIFIED};
// main
Shared_grid__global_0_0 grid_ptr__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};

// forec:scheduler:boot:start
int main(int argc__main_0_0, char ** argv__main_0_0) {

/*==============================================================
| Multicore startup:
| Platform dependent code.  Core identifies itself and
| executes its corresponding start up code.
*=============================================================*/
	// Initialise ForeC specific values ---------------------------
	// Thread do_draw with par(...)s
	do_drawParParent.parStatus = FOREC_PAR_OFF;
	do_drawParCore0.sync = 1;
	do_drawParCore0.status = FOREC_CORE_REACTING;
	do_drawParCore1.sync = 1;
	do_drawParCore1.status = FOREC_CORE_REACTING;
	do_drawParCore2.sync = 1;
	do_drawParCore2.status = FOREC_CORE_REACTING;
	do_drawParCore3.sync = 1;
	do_drawParCore3.status = FOREC_CORE_REACTING;
	do_drawParReactionCounter = 0;

	// Thread do_step with par(...)s
	do_stepParParent.parStatus = FOREC_PAR_OFF;
	do_stepParCore0.sync = 1;
	do_stepParCore0.status = FOREC_CORE_REACTING;
	do_stepParCore1.sync = 1;
	do_stepParCore1.status = FOREC_CORE_REACTING;
	do_stepParCore2.sync = 1;
	do_stepParCore2.status = FOREC_CORE_REACTING;
	do_stepParCore3.sync = 1;
	do_stepParCore3.status = FOREC_CORE_REACTING;
	do_stepParReactionCounter = 0;

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
	forec_mutex_value_do_draw = -1;
	forec_mutex_value_do_step = -1;

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
	Thread do_draw__thread;
	Thread do_step__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionStartSlave1;
	Thread mainReactionStartSlave2;
	Thread mainReactionStartSlave3;
	Thread mainReactionEndMaster0;
	Thread mainReactionEndSlave1;
	Thread mainReactionEndSlave2;
	Thread mainReactionEndSlave3;
	Thread do_drawParHandlerMaster0;
	Thread do_drawParHandlerSlave1;
	Thread do_drawParHandlerSlave2;
	Thread do_drawParHandlerSlave3;
	Thread do_stepParHandlerMaster0;
	Thread do_stepParHandlerSlave1;
	Thread do_stepParHandlerSlave2;
	Thread do_stepParHandlerSlave3;

	// par1
	Thread do_step_0__thread;
	Thread do_step_1__thread;
	Thread do_step_2__thread;
	Thread do_step_3__thread;
	Thread do_stepReactionStartMaster0;
	Thread do_stepReactionStartSlave1;
	Thread do_stepReactionStartSlave2;
	Thread do_stepReactionStartSlave3;
	Thread do_stepReactionEndMaster0;
	Thread do_stepReactionEndSlave1;
	Thread do_stepReactionEndSlave2;
	Thread do_stepReactionEndSlave3;

	// par2
	Thread do_draw_0__thread;
	Thread do_draw_1__thread;
	Thread do_draw_2__thread;
	Thread do_draw_3__thread;
	Thread do_drawReactionStartMaster0;
	Thread do_drawReactionStartSlave1;
	Thread do_drawReactionStartSlave2;
	Thread do_drawReactionStartSlave3;
	Thread do_drawReactionEndMaster0;
	Thread do_drawReactionEndSlave1;
	Thread do_drawReactionEndSlave2;
	Thread do_drawReactionEndSlave3;


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
	int ncols__main_0_0;
	int nrows__main_0_0;
	int NUM_TO_AVERAGE__main_0_0;
	float summation__main_0_0;
	int i__main_0_0;
	int done__main_1_0;
	int generation__main_1_0;
	int i__main_2_0;
	int j__main_3_1;
	long seconds__main_1_0;
	int nanoseconds__main_1_0;
	float microseconds__main_1_0;
	float runtime__main_1_0;
	float average__main_0_0;
	Shared_grid__global_0_0 grid_ptr__global_0_0_copy_main_local;

mainParCore0: {
	// Initialise the local copies of shared variables.
	grid_ptr__global_0_0_copy_main_local = grid_ptr__global_0_0;
	//--------------------------------------------------------------

	ncols__main_0_0 = 250;
	nrows__main_0_0 = 25*4;
	printf("Number of iterations to average: ");
	scanf("%d", &NUM_TO_AVERAGE__main_0_0);
	summation__main_0_0 = 0;

	for (i__main_0_0 = 0; i__main_0_0 < NUM_TO_AVERAGE__main_0_0; i__main_0_0++) {
		clock_gettime(CLOCK_MONOTONIC__global_0_0, &ts_start__main_0_0);
		initialise(ncols__main_0_0, nrows__main_0_0, &grid__global_0_0, &next_grid__global_0_0, &life_data__global_0_0);
		done__main_1_0 = FALSE__global_0_0;
		generation__main_1_0 = 0;

		while (!done__main_1_0) {
			if (generation__main_1_0++ > MAX_GENERATIONS__global_0_0) {
				done__main_1_0 = TRUE__global_0_0;
			} else {
				// if0
			}

			// par0(do_step__thread, do_draw__thread);
			grid_ptr__global_0_0_copy_main = grid_ptr__global_0_0_copy_main_local;
			grid_ptr__global_0_0.value = grid_ptr__global_0_0_copy_main_local.value;
			// Set the par(...) information.
			mainParParent.parId = 0;
			mainParParent.parStatus = FOREC_PAR_ON;

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
			mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

			// Set the core information.
			mainParCore0.activeThreads = 4;
			mainParCore0.reactionCounter = mainParReactionCounter;

			// Go to the first thread.
			// forec:statement:par:par0:start
			goto do_step__thread;
			par0JoinAddress_mainParCore0:;
			// forec:statement:par:par0:end
			grid_ptr__global_0_0_copy_main_local = grid_ptr__global_0_0;

			for (i__main_2_0 = 0; i__main_2_0 < ncols__main_0_0 + 2; i__main_2_0++) {
				for (j__main_3_1 = 0; j__main_3_1 < nrows__main_0_0 + 2; j__main_3_1++) {
					grid__global_0_0[i__main_2_0][j__main_3_1] = next_grid__global_0_0[i__main_2_0][j__main_3_1];
				}
			}

			// forec:scheduler:iterationEnd:while_2:start
			// Synchronise end of iteration
			mainParParent.parId = -2;
			mainParParent.parStatus = FOREC_PAR_ON;
			mainParParent.programCounter = &&while_2_endAddress;
			goto mainParHandlerMaster0;
			while_2_endAddress:;
			// forec:scheduler:iterationEnd:while_2:end
		}

		cleanup_grid(ncols__main_0_0, nrows__main_0_0, &grid__global_0_0);
		cleanup_grid(ncols__main_0_0, nrows__main_0_0, &next_grid__global_0_0);
		cleanup_life_data(ncols__main_0_0, nrows__main_0_0, &life_data__global_0_0);
		clock_gettime(CLOCK_MONOTONIC__global_0_0, &ts_end__main_0_0);
		seconds__main_1_0 = ts_end__main_0_0.tv_sec - ts_start__main_0_0.tv_sec;
		nanoseconds__main_1_0 = ts_end__main_0_0.tv_nsec - ts_start__main_0_0.tv_nsec;
		if (nanoseconds__main_1_0 < 0) {
			nanoseconds__main_1_0 += 1000000000;
			seconds__main_1_0--;
		} else {
			// if1
		}
		microseconds__main_1_0 = (float)nanoseconds__main_1_0/1000000000;
		runtime__main_1_0 = (float)seconds__main_1_0 + microseconds__main_1_0;
		summation__main_0_0 += runtime__main_1_0;
		printf("Runtime = %f \n", runtime__main_1_0);
		printf("------######--------\n");
	}

	average__main_0_0 = summation__main_0_0/NUM_TO_AVERAGE__main_0_0;
	printf("\nAverage runtime = %f\n\n", average__main_0_0);
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

	short int parId = do_drawParParent.parId;

	// Check the par(...) ID.
	if (parId == 2) {
		asm ("# par2 begin");
		// Link the threads and handlers together.
		do_drawReactionStartMaster0.programCounter = &&do_drawReactionStartMaster0;
		do_draw_0__thread.programCounter = &&do_draw_0__thread;
		do_drawReactionStartMaster0.nextThread = &do_draw_0__thread;
		do_draw_0__thread.prevThread = &do_drawReactionStartMaster0;
		do_drawReactionEndMaster0.programCounter = &&do_drawReactionEndMaster0;
		do_draw_0__thread.nextThread = &do_drawReactionEndMaster0;
		do_drawReactionEndMaster0.prevThread = &do_draw_0__thread;

		// Swap the nested par handler with the linked list.
		do_drawParHandlerMaster0.prevThread -> nextThread = &do_drawReactionStartMaster0;
		do_drawReactionStartMaster0.prevThread = do_drawParHandlerMaster0.prevThread;
		do_drawReactionEndMaster0.nextThread = do_drawParHandlerMaster0.nextThread;
		do_drawParHandlerMaster0.nextThread -> prevThread = &do_drawReactionEndMaster0;
		
		// Set the core information.
		do_drawParCore0.activeThreads = 1;
		do_drawParCore0.reactionCounter = do_drawParReactionCounter;
		
		// Go to the first thread.
		goto do_draw_0__thread;
		asm ("# par2 end");
	} else if (parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.
		while(do_drawParCore1.status == FOREC_CORE_REACTING);
		while(do_drawParCore2.status == FOREC_CORE_REACTING);
		while(do_drawParCore3.status == FOREC_CORE_REACTING);

		do_drawParParent.parStatus = FOREC_PAR_OFF;
		do_drawParParent.parId = -1;

		forec_mutex_value_do_draw = -1;

		// Set slave cores' status to reacting.
		do_drawParCore1.status = FOREC_CORE_REACTING;
		do_drawParCore2.status = FOREC_CORE_REACTING;
		do_drawParCore3.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		do_drawParReactionCounter++;

		// Return to thread do_draw.
		goto *do_drawParParent.programCounter;
	} else if (parId == -3) {
		// Thread termination
		mainParCore0.activeThreads--;
		do_drawParCore0.activeThreads--;

		// Wait for other cores to complete their reaction.
		while(do_drawParCore1.status == FOREC_CORE_REACTING);
		while(do_drawParCore2.status == FOREC_CORE_REACTING);
		while(do_drawParCore3.status == FOREC_CORE_REACTING);

		do_drawParParent.parStatus = FOREC_PAR_OFF;
		do_drawParParent.parId = -1;

		// Set slave cores' status to reacting.
		do_drawParCore1.status = FOREC_CORE_REACTING;
		do_drawParCore2.status = FOREC_CORE_REACTING;
		do_drawParCore3.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		do_drawParReactionCounter++;

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

		do_drawParCore0.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore0.reactionCounter == do_drawParReactionCounter);
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

	short int parId = do_stepParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		do_stepReactionStartMaster0.programCounter = &&do_stepReactionStartMaster0;
		do_step_0__thread.programCounter = &&do_step_0__thread;
		do_stepReactionStartMaster0.nextThread = &do_step_0__thread;
		do_step_0__thread.prevThread = &do_stepReactionStartMaster0;
		do_stepReactionEndMaster0.programCounter = &&do_stepReactionEndMaster0;
		do_step_0__thread.nextThread = &do_stepReactionEndMaster0;
		do_stepReactionEndMaster0.prevThread = &do_step_0__thread;

		// Swap the nested par handler with the linked list.
		do_stepParHandlerMaster0.prevThread -> nextThread = &do_stepReactionStartMaster0;
		do_stepReactionStartMaster0.prevThread = do_stepParHandlerMaster0.prevThread;
		do_stepReactionEndMaster0.nextThread = do_stepParHandlerMaster0.nextThread;
		do_stepParHandlerMaster0.nextThread -> prevThread = &do_stepReactionEndMaster0;
		
		// Set the core information.
		do_stepParCore0.activeThreads = 1;
		do_stepParCore0.reactionCounter = do_stepParReactionCounter;
		
		// Go to the first thread.
		goto do_step_0__thread;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.
		while(do_stepParCore1.status == FOREC_CORE_REACTING);
		while(do_stepParCore2.status == FOREC_CORE_REACTING);
		while(do_stepParCore3.status == FOREC_CORE_REACTING);

		do_stepParParent.parStatus = FOREC_PAR_OFF;
		do_stepParParent.parId = -1;

		forec_mutex_value_do_step = -1;

		// Set slave cores' status to reacting.
		do_stepParCore1.status = FOREC_CORE_REACTING;
		do_stepParCore2.status = FOREC_CORE_REACTING;
		do_stepParCore3.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		do_stepParReactionCounter++;

		// Return to thread do_step.
		goto *do_stepParParent.programCounter;
	} else if (parId == -3) {
		// Thread termination
		mainParCore0.activeThreads--;
		do_stepParCore0.activeThreads--;

		// Wait for other cores to complete their reaction.
		while(do_stepParCore1.status == FOREC_CORE_REACTING);
		while(do_stepParCore2.status == FOREC_CORE_REACTING);
		while(do_stepParCore3.status == FOREC_CORE_REACTING);

		do_stepParParent.parStatus = FOREC_PAR_OFF;
		do_stepParParent.parId = -1;

		// Set slave cores' status to reacting.
		do_stepParCore1.status = FOREC_CORE_REACTING;
		do_stepParCore2.status = FOREC_CORE_REACTING;
		do_stepParCore3.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		do_stepParReactionCounter++;

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

		do_stepParCore0.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_stepParCore0.reactionCounter == do_stepParReactionCounter);
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
	if (do_drawParCore0.activeThreads) {
		do_drawParCore0.status = FOREC_CORE_REACTED;
	} else {
		do_drawParCore0.status = FOREC_CORE_TERMINATED;
	}
	
	// Wait for other cores to complete their reaction.
	while(do_drawParCore1.status == FOREC_CORE_REACTING);
	while(do_drawParCore2.status == FOREC_CORE_REACTING);
	while(do_drawParCore3.status == FOREC_CORE_REACTING);


	// Return back to the parent thread if all the cores have terminated.
	if (1 && do_drawParCore0.status == FOREC_CORE_TERMINATED && do_drawParCore1.status == FOREC_CORE_TERMINATED && do_drawParCore2.status == FOREC_CORE_TERMINATED && do_drawParCore3.status == FOREC_CORE_TERMINATED) {
		forec_mutex_value_do_draw = -1;

		do_drawParParent.parStatus = FOREC_PAR_OFF;
		do_drawParParent.parId = -1;
		
		// Set slave cores' status to reacting
		do_drawParCore1.status = FOREC_CORE_REACTING;
		do_drawParCore2.status = FOREC_CORE_REACTING;
		do_drawParCore3.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronization.
		do_drawParReactionCounter++;

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
	do_drawParCore1.status = FOREC_CORE_REACTING;
	do_drawParCore2.status = FOREC_CORE_REACTING;
	do_drawParCore3.status = FOREC_CORE_REACTING;

	// Increment the reaction counter for synchronization.
	do_drawParReactionCounter++;

	// Go to the next thread.
	goto *do_drawReactionEndMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:do_draw:master:0:end
 
	// forec:scheduler:reactionEnd:do_step:master:0:start
	//-- do_step:
do_stepReactionEndMaster0: {
	// Determine if the core can still react or not.
	if (do_stepParCore0.activeThreads) {
		do_stepParCore0.status = FOREC_CORE_REACTED;
	} else {
		do_stepParCore0.status = FOREC_CORE_TERMINATED;
	}
	
	// Wait for other cores to complete their reaction.
	while(do_stepParCore1.status == FOREC_CORE_REACTING);
	while(do_stepParCore2.status == FOREC_CORE_REACTING);
	while(do_stepParCore3.status == FOREC_CORE_REACTING);


	// Return back to the parent thread if all the cores have terminated.
	if (1 && do_stepParCore0.status == FOREC_CORE_TERMINATED && do_stepParCore1.status == FOREC_CORE_TERMINATED && do_stepParCore2.status == FOREC_CORE_TERMINATED && do_stepParCore3.status == FOREC_CORE_TERMINATED) {
		forec_mutex_value_do_step = -1;

		do_stepParParent.parStatus = FOREC_PAR_OFF;
		do_stepParParent.parId = -1;
		
		// Set slave cores' status to reacting
		do_stepParCore1.status = FOREC_CORE_REACTING;
		do_stepParCore2.status = FOREC_CORE_REACTING;
		do_stepParCore3.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronization.
		do_stepParReactionCounter++;

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
	do_stepParCore1.status = FOREC_CORE_REACTING;
	do_stepParCore2.status = FOREC_CORE_REACTING;
	do_stepParCore3.status = FOREC_CORE_REACTING;

	// Increment the reaction counter for synchronization.
	do_stepParReactionCounter++;

	// Go to the next thread.
	goto *do_stepReactionEndMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:do_step:master:0:end
 
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
	forec_mutex_value_do_draw = -1;
	forec_mutex_value_do_step = -1;

	// Combine shared variables.
	unsigned short int parId = mainParParent.parId;
	if (parId == 0) {
		unsigned short int index;
		unsigned short int numberOfModifiedCopies;

		// grid_ptr__global_0_0
		if (grid_ptr__global_0_0_copy_do_draw.status == FOREC_SHARED_MODIFIED) {
			grid_ptr__global_0_0_copy_do_draw.status = FOREC_SHARED_UNMODIFIED;
			grid_ptr__global_0_0.value = grid_ptr__global_0_0_copy_do_draw.value;
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
		do_stepParHandlerSlave1.programCounter = &&do_stepParHandlerSlave1;
		mainReactionStartSlave1.nextThread = &do_stepParHandlerSlave1;
		do_stepParHandlerSlave1.prevThread = &mainReactionStartSlave1;
		do_drawParHandlerSlave1.programCounter = &&do_drawParHandlerSlave1;
		do_stepParHandlerSlave1.nextThread = &do_drawParHandlerSlave1;
		do_drawParHandlerSlave1.prevThread = &do_stepParHandlerSlave1;
		mainReactionEndSlave1.programCounter = &&mainReactionEndSlave1;
		do_drawParHandlerSlave1.nextThread = &mainReactionEndSlave1;
		mainReactionEndSlave1.prevThread = &do_drawParHandlerSlave1;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave1.nextThread = &mainReactionStartSlave1;
		mainReactionStartSlave1.prevThread = &mainReactionEndSlave1;

		// Set the core information.
		mainParCore1.activeThreads = 2;
		mainParCore1.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto do_stepParHandlerSlave1;
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
	// forec:scheduler:parHandler:do_draw:slave:1:start
	//-- Thread do_draw par(...) handlers
do_drawParHandlerSlave1: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_do_draw & 0x80000000) == (unsigned)0x80000000);

	// Check the execution status of the nested par(...)s.
	if (do_drawParParent.parStatus == FOREC_PAR_OFF) {
		goto *do_drawParHandlerSlave1.nextThread -> programCounter;
	}

	short int parId = do_drawParParent.parId;

	// Check the par(...) ID.
	if (parId == 2) {
		asm ("# par2 begin");
		// Link the threads and handlers together.
		do_drawReactionStartSlave1.programCounter = &&do_drawReactionStartSlave1;
		do_draw_1__thread.programCounter = &&do_draw_1__thread;
		do_drawReactionStartSlave1.nextThread = &do_draw_1__thread;
		do_draw_1__thread.prevThread = &do_drawReactionStartSlave1;
		do_drawReactionEndSlave1.programCounter = &&do_drawReactionEndSlave1;
		do_draw_1__thread.nextThread = &do_drawReactionEndSlave1;
		do_drawReactionEndSlave1.prevThread = &do_draw_1__thread;

		// Swap the nested par handler with the linked list.
		do_drawParHandlerSlave1.prevThread -> nextThread = &do_drawReactionStartSlave1;
		do_drawReactionStartSlave1.prevThread = do_drawParHandlerSlave1.prevThread;
		do_drawReactionEndSlave1.nextThread = do_drawParHandlerSlave1.nextThread;
		do_drawParHandlerSlave1.nextThread -> prevThread = &do_drawReactionEndSlave1;
		
		// Set the core information.
		do_drawParCore1.activeThreads = 1;
		do_drawParCore1.reactionCounter = do_drawParReactionCounter;
		
		// Go to the first thread.
		goto do_draw_1__thread;
		asm ("# par2 end");
	} else if (parId == -2) {
		// Iteration
		do_drawParCore1.reactionCounter = do_drawParReactionCounter;
		do_drawParCore1.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore1.reactionCounter == do_drawParReactionCounter);

		// Go to the next thread.
		goto do_drawParHandlerSlave1;
	} else if (parId == -3) {
		// Thread termination
		mainParCore1.activeThreads--;
		do_drawParCore1.activeThreads--;

		do_drawParCore1.reactionCounter = do_drawParReactionCounter;
		do_drawParCore1.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore1.reactionCounter == do_drawParReactionCounter);

		// Delete this par(...) handler.
		do_drawParHandlerSlave1.prevThread -> nextThread = do_drawParHandlerSlave1.nextThread;
		do_drawParHandlerSlave1.nextThread -> prevThread = do_drawParHandlerSlave1.prevThread;
			
		// Go to the next thread.
		goto *do_drawParHandlerSlave1.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		do_drawParCore1.reactionCounter = do_drawParReactionCounter;

		do_drawParHandlerSlave1.programCounter = &&wrongParId_do_drawParHandlerSlave1;
		wrongParId_do_drawParHandlerSlave1:;

		do_drawParCore1.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore1.reactionCounter == do_drawParReactionCounter);
		do_drawParCore1.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (do_drawParParent.parStatus == FOREC_PAR_ON && do_drawParParent.parId == parId) {
			goto *do_drawParHandlerSlave1.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		do_drawParHandlerSlave1.programCounter = &&do_drawParHandlerSlave1;
		
		goto do_drawParHandlerSlave1;
	}
	
	// Control should not reach here.
	goto do_drawParHandlerSlave1;
}
	// forec:scheduler:parHandler:do_draw:slave:1:end
 	// forec:scheduler:parHandler:do_step:slave:1:start
	//-- Thread do_step par(...) handlers
do_stepParHandlerSlave1: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_do_step & 0x40000000) == (unsigned)0x40000000);

	// Check the execution status of the nested par(...)s.
	if (do_stepParParent.parStatus == FOREC_PAR_OFF) {
		goto *do_stepParHandlerSlave1.nextThread -> programCounter;
	}

	short int parId = do_stepParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		do_stepReactionStartSlave1.programCounter = &&do_stepReactionStartSlave1;
		do_step_1__thread.programCounter = &&do_step_1__thread;
		do_stepReactionStartSlave1.nextThread = &do_step_1__thread;
		do_step_1__thread.prevThread = &do_stepReactionStartSlave1;
		do_stepReactionEndSlave1.programCounter = &&do_stepReactionEndSlave1;
		do_step_1__thread.nextThread = &do_stepReactionEndSlave1;
		do_stepReactionEndSlave1.prevThread = &do_step_1__thread;

		// Swap the nested par handler with the linked list.
		do_stepParHandlerSlave1.prevThread -> nextThread = &do_stepReactionStartSlave1;
		do_stepReactionStartSlave1.prevThread = do_stepParHandlerSlave1.prevThread;
		do_stepReactionEndSlave1.nextThread = do_stepParHandlerSlave1.nextThread;
		do_stepParHandlerSlave1.nextThread -> prevThread = &do_stepReactionEndSlave1;
		
		// Set the core information.
		do_stepParCore1.activeThreads = 1;
		do_stepParCore1.reactionCounter = do_stepParReactionCounter;
		
		// Go to the first thread.
		goto do_step_1__thread;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		do_stepParCore1.reactionCounter = do_stepParReactionCounter;
		do_stepParCore1.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_stepParCore1.reactionCounter == do_stepParReactionCounter);

		// Go to the next thread.
		goto do_stepParHandlerSlave1;
	} else if (parId == -3) {
		// Thread termination
		mainParCore1.activeThreads--;
		do_stepParCore1.activeThreads--;

		do_stepParCore1.reactionCounter = do_stepParReactionCounter;
		do_stepParCore1.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_stepParCore1.reactionCounter == do_stepParReactionCounter);

		// Delete this par(...) handler.
		do_stepParHandlerSlave1.prevThread -> nextThread = do_stepParHandlerSlave1.nextThread;
		do_stepParHandlerSlave1.nextThread -> prevThread = do_stepParHandlerSlave1.prevThread;
			
		// Go to the next thread.
		goto *do_stepParHandlerSlave1.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		do_stepParCore1.reactionCounter = do_stepParReactionCounter;

		do_stepParHandlerSlave1.programCounter = &&wrongParId_do_stepParHandlerSlave1;
		wrongParId_do_stepParHandlerSlave1:;

		do_stepParCore1.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_stepParCore1.reactionCounter == do_stepParReactionCounter);
		do_stepParCore1.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (do_stepParParent.parStatus == FOREC_PAR_ON && do_stepParParent.parId == parId) {
			goto *do_stepParHandlerSlave1.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		do_stepParHandlerSlave1.programCounter = &&do_stepParHandlerSlave1;
		
		goto do_stepParHandlerSlave1;
	}
	
	// Control should not reach here.
	goto do_stepParHandlerSlave1;
}
	// forec:scheduler:parHandler:do_step:slave:1:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:do_draw:slave:1:start
	//-- do_draw:
do_drawReactionStartSlave1: {
	// Go to the next thread.
	goto *do_drawReactionStartSlave1.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:do_draw:slave:1:end
 
	// forec:scheduler:reactionStart:do_step:slave:1:start
	//-- do_step:
do_stepReactionStartSlave1: {
	// Go to the next thread.
	goto *do_stepReactionStartSlave1.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:do_step:slave:1:end
 
	// forec:scheduler:reactionStart:main:slave:1:start
	//-- main:
mainReactionStartSlave1: {
	// Go to the next thread.
	goto *mainReactionStartSlave1.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:1:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:do_draw:slave:1:start
	//-- do_draw:
do_drawReactionEndSlave1: {
	// Determine if the core can still react or not.
	if (do_drawParCore1.activeThreads) {
		do_drawParCore1.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (do_drawParCore1.reactionCounter == do_drawParReactionCounter);
		do_drawParCore1.reactionCounter++;
		
		// Continue reacting.
		goto *do_drawReactionEndSlave1.nextThread -> programCounter;
	} else {
		short int parId = do_drawParParent.parId;

		do_drawReactionEndSlave1.programCounter = &&terminated_do_drawReactionEndSlave1;
		terminated_do_drawReactionEndSlave1:;
		
		do_drawParCore1.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (do_drawParCore1.reactionCounter == do_drawParReactionCounter);
		do_drawParCore1.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (do_drawParParent.parStatus == FOREC_PAR_ON && do_drawParParent.parId == parId) {
			goto *do_drawReactionEndSlave1.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		do_drawReactionStartSlave1.prevThread -> nextThread = &do_drawParHandlerSlave1;
		do_drawParHandlerSlave1.prevThread = do_drawReactionStartSlave1.prevThread;
		do_drawParHandlerSlave1.nextThread = do_drawReactionEndSlave1.nextThread;
		do_drawReactionEndSlave1.nextThread -> prevThread = &do_drawParHandlerSlave1;
		goto do_drawParHandlerSlave1;
	}
	
	// Control shouldn't reach here.
	goto do_drawReactionEndSlave1;
}
	// forec:scheduler:reactionEnd:do_draw:slave:1:end
 
	// forec:scheduler:reactionEnd:do_step:slave:1:start
	//-- do_step:
do_stepReactionEndSlave1: {
	// Determine if the core can still react or not.
	if (do_stepParCore1.activeThreads) {
		do_stepParCore1.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (do_stepParCore1.reactionCounter == do_stepParReactionCounter);
		do_stepParCore1.reactionCounter++;
		
		// Continue reacting.
		goto *do_stepReactionEndSlave1.nextThread -> programCounter;
	} else {
		short int parId = do_stepParParent.parId;

		do_stepReactionEndSlave1.programCounter = &&terminated_do_stepReactionEndSlave1;
		terminated_do_stepReactionEndSlave1:;
		
		do_stepParCore1.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (do_stepParCore1.reactionCounter == do_stepParReactionCounter);
		do_stepParCore1.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (do_stepParParent.parStatus == FOREC_PAR_ON && do_stepParParent.parId == parId) {
			goto *do_stepReactionEndSlave1.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		do_stepReactionStartSlave1.prevThread -> nextThread = &do_stepParHandlerSlave1;
		do_stepParHandlerSlave1.prevThread = do_stepReactionStartSlave1.prevThread;
		do_stepParHandlerSlave1.nextThread = do_stepReactionEndSlave1.nextThread;
		do_stepReactionEndSlave1.nextThread -> prevThread = &do_stepParHandlerSlave1;
		goto do_stepParHandlerSlave1;
	}
	
	// Control shouldn't reach here.
	goto do_stepReactionEndSlave1;
}
	// forec:scheduler:reactionEnd:do_step:slave:1:end
 
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
		do_stepParHandlerSlave2.programCounter = &&do_stepParHandlerSlave2;
		mainReactionStartSlave2.nextThread = &do_stepParHandlerSlave2;
		do_stepParHandlerSlave2.prevThread = &mainReactionStartSlave2;
		do_drawParHandlerSlave2.programCounter = &&do_drawParHandlerSlave2;
		do_stepParHandlerSlave2.nextThread = &do_drawParHandlerSlave2;
		do_drawParHandlerSlave2.prevThread = &do_stepParHandlerSlave2;
		mainReactionEndSlave2.programCounter = &&mainReactionEndSlave2;
		do_drawParHandlerSlave2.nextThread = &mainReactionEndSlave2;
		mainReactionEndSlave2.prevThread = &do_drawParHandlerSlave2;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave2.nextThread = &mainReactionStartSlave2;
		mainReactionStartSlave2.prevThread = &mainReactionEndSlave2;

		// Set the core information.
		mainParCore2.activeThreads = 2;
		mainParCore2.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto do_stepParHandlerSlave2;
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
	// forec:scheduler:parHandler:do_draw:slave:2:start
	//-- Thread do_draw par(...) handlers
do_drawParHandlerSlave2: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_do_draw & 0x80000000) == (unsigned)0x80000000);

	// Check the execution status of the nested par(...)s.
	if (do_drawParParent.parStatus == FOREC_PAR_OFF) {
		goto *do_drawParHandlerSlave2.nextThread -> programCounter;
	}

	short int parId = do_drawParParent.parId;

	// Check the par(...) ID.
	if (parId == 2) {
		asm ("# par2 begin");
		// Link the threads and handlers together.
		do_drawReactionStartSlave2.programCounter = &&do_drawReactionStartSlave2;
		do_draw_2__thread.programCounter = &&do_draw_2__thread;
		do_drawReactionStartSlave2.nextThread = &do_draw_2__thread;
		do_draw_2__thread.prevThread = &do_drawReactionStartSlave2;
		do_drawReactionEndSlave2.programCounter = &&do_drawReactionEndSlave2;
		do_draw_2__thread.nextThread = &do_drawReactionEndSlave2;
		do_drawReactionEndSlave2.prevThread = &do_draw_2__thread;

		// Swap the nested par handler with the linked list.
		do_drawParHandlerSlave2.prevThread -> nextThread = &do_drawReactionStartSlave2;
		do_drawReactionStartSlave2.prevThread = do_drawParHandlerSlave2.prevThread;
		do_drawReactionEndSlave2.nextThread = do_drawParHandlerSlave2.nextThread;
		do_drawParHandlerSlave2.nextThread -> prevThread = &do_drawReactionEndSlave2;
		
		// Set the core information.
		do_drawParCore2.activeThreads = 1;
		do_drawParCore2.reactionCounter = do_drawParReactionCounter;
		
		// Go to the first thread.
		goto do_draw_2__thread;
		asm ("# par2 end");
	} else if (parId == -2) {
		// Iteration
		do_drawParCore2.reactionCounter = do_drawParReactionCounter;
		do_drawParCore2.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore2.reactionCounter == do_drawParReactionCounter);

		// Go to the next thread.
		goto do_drawParHandlerSlave2;
	} else if (parId == -3) {
		// Thread termination
		mainParCore2.activeThreads--;
		do_drawParCore2.activeThreads--;

		do_drawParCore2.reactionCounter = do_drawParReactionCounter;
		do_drawParCore2.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore2.reactionCounter == do_drawParReactionCounter);

		// Delete this par(...) handler.
		do_drawParHandlerSlave2.prevThread -> nextThread = do_drawParHandlerSlave2.nextThread;
		do_drawParHandlerSlave2.nextThread -> prevThread = do_drawParHandlerSlave2.prevThread;
			
		// Go to the next thread.
		goto *do_drawParHandlerSlave2.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		do_drawParCore2.reactionCounter = do_drawParReactionCounter;

		do_drawParHandlerSlave2.programCounter = &&wrongParId_do_drawParHandlerSlave2;
		wrongParId_do_drawParHandlerSlave2:;

		do_drawParCore2.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore2.reactionCounter == do_drawParReactionCounter);
		do_drawParCore2.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (do_drawParParent.parStatus == FOREC_PAR_ON && do_drawParParent.parId == parId) {
			goto *do_drawParHandlerSlave2.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		do_drawParHandlerSlave2.programCounter = &&do_drawParHandlerSlave2;
		
		goto do_drawParHandlerSlave2;
	}
	
	// Control should not reach here.
	goto do_drawParHandlerSlave2;
}
	// forec:scheduler:parHandler:do_draw:slave:2:end
 	// forec:scheduler:parHandler:do_step:slave:2:start
	//-- Thread do_step par(...) handlers
do_stepParHandlerSlave2: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_do_step & 0x40000000) == (unsigned)0x40000000);

	// Check the execution status of the nested par(...)s.
	if (do_stepParParent.parStatus == FOREC_PAR_OFF) {
		goto *do_stepParHandlerSlave2.nextThread -> programCounter;
	}

	short int parId = do_stepParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		do_stepReactionStartSlave2.programCounter = &&do_stepReactionStartSlave2;
		do_step_2__thread.programCounter = &&do_step_2__thread;
		do_stepReactionStartSlave2.nextThread = &do_step_2__thread;
		do_step_2__thread.prevThread = &do_stepReactionStartSlave2;
		do_stepReactionEndSlave2.programCounter = &&do_stepReactionEndSlave2;
		do_step_2__thread.nextThread = &do_stepReactionEndSlave2;
		do_stepReactionEndSlave2.prevThread = &do_step_2__thread;

		// Swap the nested par handler with the linked list.
		do_stepParHandlerSlave2.prevThread -> nextThread = &do_stepReactionStartSlave2;
		do_stepReactionStartSlave2.prevThread = do_stepParHandlerSlave2.prevThread;
		do_stepReactionEndSlave2.nextThread = do_stepParHandlerSlave2.nextThread;
		do_stepParHandlerSlave2.nextThread -> prevThread = &do_stepReactionEndSlave2;
		
		// Set the core information.
		do_stepParCore2.activeThreads = 1;
		do_stepParCore2.reactionCounter = do_stepParReactionCounter;
		
		// Go to the first thread.
		goto do_step_2__thread;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		do_stepParCore2.reactionCounter = do_stepParReactionCounter;
		do_stepParCore2.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_stepParCore2.reactionCounter == do_stepParReactionCounter);

		// Go to the next thread.
		goto do_stepParHandlerSlave2;
	} else if (parId == -3) {
		// Thread termination
		mainParCore2.activeThreads--;
		do_stepParCore2.activeThreads--;

		do_stepParCore2.reactionCounter = do_stepParReactionCounter;
		do_stepParCore2.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_stepParCore2.reactionCounter == do_stepParReactionCounter);

		// Delete this par(...) handler.
		do_stepParHandlerSlave2.prevThread -> nextThread = do_stepParHandlerSlave2.nextThread;
		do_stepParHandlerSlave2.nextThread -> prevThread = do_stepParHandlerSlave2.prevThread;
			
		// Go to the next thread.
		goto *do_stepParHandlerSlave2.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		do_stepParCore2.reactionCounter = do_stepParReactionCounter;

		do_stepParHandlerSlave2.programCounter = &&wrongParId_do_stepParHandlerSlave2;
		wrongParId_do_stepParHandlerSlave2:;

		do_stepParCore2.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_stepParCore2.reactionCounter == do_stepParReactionCounter);
		do_stepParCore2.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (do_stepParParent.parStatus == FOREC_PAR_ON && do_stepParParent.parId == parId) {
			goto *do_stepParHandlerSlave2.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		do_stepParHandlerSlave2.programCounter = &&do_stepParHandlerSlave2;
		
		goto do_stepParHandlerSlave2;
	}
	
	// Control should not reach here.
	goto do_stepParHandlerSlave2;
}
	// forec:scheduler:parHandler:do_step:slave:2:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:do_draw:slave:2:start
	//-- do_draw:
do_drawReactionStartSlave2: {
	// Go to the next thread.
	goto *do_drawReactionStartSlave2.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:do_draw:slave:2:end
 
	// forec:scheduler:reactionStart:do_step:slave:2:start
	//-- do_step:
do_stepReactionStartSlave2: {
	// Go to the next thread.
	goto *do_stepReactionStartSlave2.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:do_step:slave:2:end
 
	// forec:scheduler:reactionStart:main:slave:2:start
	//-- main:
mainReactionStartSlave2: {
	// Go to the next thread.
	goto *mainReactionStartSlave2.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:2:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:do_draw:slave:2:start
	//-- do_draw:
do_drawReactionEndSlave2: {
	// Determine if the core can still react or not.
	if (do_drawParCore2.activeThreads) {
		do_drawParCore2.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (do_drawParCore2.reactionCounter == do_drawParReactionCounter);
		do_drawParCore2.reactionCounter++;
		
		// Continue reacting.
		goto *do_drawReactionEndSlave2.nextThread -> programCounter;
	} else {
		short int parId = do_drawParParent.parId;

		do_drawReactionEndSlave2.programCounter = &&terminated_do_drawReactionEndSlave2;
		terminated_do_drawReactionEndSlave2:;
		
		do_drawParCore2.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (do_drawParCore2.reactionCounter == do_drawParReactionCounter);
		do_drawParCore2.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (do_drawParParent.parStatus == FOREC_PAR_ON && do_drawParParent.parId == parId) {
			goto *do_drawReactionEndSlave2.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		do_drawReactionStartSlave2.prevThread -> nextThread = &do_drawParHandlerSlave2;
		do_drawParHandlerSlave2.prevThread = do_drawReactionStartSlave2.prevThread;
		do_drawParHandlerSlave2.nextThread = do_drawReactionEndSlave2.nextThread;
		do_drawReactionEndSlave2.nextThread -> prevThread = &do_drawParHandlerSlave2;
		goto do_drawParHandlerSlave2;
	}
	
	// Control shouldn't reach here.
	goto do_drawReactionEndSlave2;
}
	// forec:scheduler:reactionEnd:do_draw:slave:2:end
 
	// forec:scheduler:reactionEnd:do_step:slave:2:start
	//-- do_step:
do_stepReactionEndSlave2: {
	// Determine if the core can still react or not.
	if (do_stepParCore2.activeThreads) {
		do_stepParCore2.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (do_stepParCore2.reactionCounter == do_stepParReactionCounter);
		do_stepParCore2.reactionCounter++;
		
		// Continue reacting.
		goto *do_stepReactionEndSlave2.nextThread -> programCounter;
	} else {
		short int parId = do_stepParParent.parId;

		do_stepReactionEndSlave2.programCounter = &&terminated_do_stepReactionEndSlave2;
		terminated_do_stepReactionEndSlave2:;
		
		do_stepParCore2.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (do_stepParCore2.reactionCounter == do_stepParReactionCounter);
		do_stepParCore2.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (do_stepParParent.parStatus == FOREC_PAR_ON && do_stepParParent.parId == parId) {
			goto *do_stepReactionEndSlave2.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		do_stepReactionStartSlave2.prevThread -> nextThread = &do_stepParHandlerSlave2;
		do_stepParHandlerSlave2.prevThread = do_stepReactionStartSlave2.prevThread;
		do_stepParHandlerSlave2.nextThread = do_stepReactionEndSlave2.nextThread;
		do_stepReactionEndSlave2.nextThread -> prevThread = &do_stepParHandlerSlave2;
		goto do_stepParHandlerSlave2;
	}
	
	// Control shouldn't reach here.
	goto do_stepReactionEndSlave2;
}
	// forec:scheduler:reactionEnd:do_step:slave:2:end
 
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
		do_stepParHandlerSlave3.programCounter = &&do_stepParHandlerSlave3;
		mainReactionStartSlave3.nextThread = &do_stepParHandlerSlave3;
		do_stepParHandlerSlave3.prevThread = &mainReactionStartSlave3;
		do_drawParHandlerSlave3.programCounter = &&do_drawParHandlerSlave3;
		do_stepParHandlerSlave3.nextThread = &do_drawParHandlerSlave3;
		do_drawParHandlerSlave3.prevThread = &do_stepParHandlerSlave3;
		mainReactionEndSlave3.programCounter = &&mainReactionEndSlave3;
		do_drawParHandlerSlave3.nextThread = &mainReactionEndSlave3;
		mainReactionEndSlave3.prevThread = &do_drawParHandlerSlave3;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave3.nextThread = &mainReactionStartSlave3;
		mainReactionStartSlave3.prevThread = &mainReactionEndSlave3;

		// Set the core information.
		mainParCore3.activeThreads = 2;
		mainParCore3.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto do_stepParHandlerSlave3;
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
	// forec:scheduler:parHandler:do_draw:slave:3:start
	//-- Thread do_draw par(...) handlers
do_drawParHandlerSlave3: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_do_draw & 0x80000000) == (unsigned)0x80000000);

	// Check the execution status of the nested par(...)s.
	if (do_drawParParent.parStatus == FOREC_PAR_OFF) {
		goto *do_drawParHandlerSlave3.nextThread -> programCounter;
	}

	short int parId = do_drawParParent.parId;

	// Check the par(...) ID.
	if (parId == 2) {
		asm ("# par2 begin");
		// Link the threads and handlers together.
		do_drawReactionStartSlave3.programCounter = &&do_drawReactionStartSlave3;
		do_draw_3__thread.programCounter = &&do_draw_3__thread;
		do_drawReactionStartSlave3.nextThread = &do_draw_3__thread;
		do_draw_3__thread.prevThread = &do_drawReactionStartSlave3;
		do_drawReactionEndSlave3.programCounter = &&do_drawReactionEndSlave3;
		do_draw_3__thread.nextThread = &do_drawReactionEndSlave3;
		do_drawReactionEndSlave3.prevThread = &do_draw_3__thread;

		// Swap the nested par handler with the linked list.
		do_drawParHandlerSlave3.prevThread -> nextThread = &do_drawReactionStartSlave3;
		do_drawReactionStartSlave3.prevThread = do_drawParHandlerSlave3.prevThread;
		do_drawReactionEndSlave3.nextThread = do_drawParHandlerSlave3.nextThread;
		do_drawParHandlerSlave3.nextThread -> prevThread = &do_drawReactionEndSlave3;
		
		// Set the core information.
		do_drawParCore3.activeThreads = 1;
		do_drawParCore3.reactionCounter = do_drawParReactionCounter;
		
		// Go to the first thread.
		goto do_draw_3__thread;
		asm ("# par2 end");
	} else if (parId == -2) {
		// Iteration
		do_drawParCore3.reactionCounter = do_drawParReactionCounter;
		do_drawParCore3.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore3.reactionCounter == do_drawParReactionCounter);

		// Go to the next thread.
		goto do_drawParHandlerSlave3;
	} else if (parId == -3) {
		// Thread termination
		mainParCore3.activeThreads--;
		do_drawParCore3.activeThreads--;

		do_drawParCore3.reactionCounter = do_drawParReactionCounter;
		do_drawParCore3.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore3.reactionCounter == do_drawParReactionCounter);

		// Delete this par(...) handler.
		do_drawParHandlerSlave3.prevThread -> nextThread = do_drawParHandlerSlave3.nextThread;
		do_drawParHandlerSlave3.nextThread -> prevThread = do_drawParHandlerSlave3.prevThread;
			
		// Go to the next thread.
		goto *do_drawParHandlerSlave3.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		do_drawParCore3.reactionCounter = do_drawParReactionCounter;

		do_drawParHandlerSlave3.programCounter = &&wrongParId_do_drawParHandlerSlave3;
		wrongParId_do_drawParHandlerSlave3:;

		do_drawParCore3.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore3.reactionCounter == do_drawParReactionCounter);
		do_drawParCore3.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (do_drawParParent.parStatus == FOREC_PAR_ON && do_drawParParent.parId == parId) {
			goto *do_drawParHandlerSlave3.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		do_drawParHandlerSlave3.programCounter = &&do_drawParHandlerSlave3;
		
		goto do_drawParHandlerSlave3;
	}
	
	// Control should not reach here.
	goto do_drawParHandlerSlave3;
}
	// forec:scheduler:parHandler:do_draw:slave:3:end
 	// forec:scheduler:parHandler:do_step:slave:3:start
	//-- Thread do_step par(...) handlers
do_stepParHandlerSlave3: {
	// Synchronise the checking of the nested par(...) via a mutex.
	while ((unsigned)(forec_mutex_value_do_step & 0x40000000) == (unsigned)0x40000000);

	// Check the execution status of the nested par(...)s.
	if (do_stepParParent.parStatus == FOREC_PAR_OFF) {
		goto *do_stepParHandlerSlave3.nextThread -> programCounter;
	}

	short int parId = do_stepParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		do_stepReactionStartSlave3.programCounter = &&do_stepReactionStartSlave3;
		do_step_3__thread.programCounter = &&do_step_3__thread;
		do_stepReactionStartSlave3.nextThread = &do_step_3__thread;
		do_step_3__thread.prevThread = &do_stepReactionStartSlave3;
		do_stepReactionEndSlave3.programCounter = &&do_stepReactionEndSlave3;
		do_step_3__thread.nextThread = &do_stepReactionEndSlave3;
		do_stepReactionEndSlave3.prevThread = &do_step_3__thread;

		// Swap the nested par handler with the linked list.
		do_stepParHandlerSlave3.prevThread -> nextThread = &do_stepReactionStartSlave3;
		do_stepReactionStartSlave3.prevThread = do_stepParHandlerSlave3.prevThread;
		do_stepReactionEndSlave3.nextThread = do_stepParHandlerSlave3.nextThread;
		do_stepParHandlerSlave3.nextThread -> prevThread = &do_stepReactionEndSlave3;
		
		// Set the core information.
		do_stepParCore3.activeThreads = 1;
		do_stepParCore3.reactionCounter = do_stepParReactionCounter;
		
		// Go to the first thread.
		goto do_step_3__thread;
		asm ("# par1 end");
	} else if (parId == -2) {
		// Iteration
		do_stepParCore3.reactionCounter = do_stepParReactionCounter;
		do_stepParCore3.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_stepParCore3.reactionCounter == do_stepParReactionCounter);

		// Go to the next thread.
		goto do_stepParHandlerSlave3;
	} else if (parId == -3) {
		// Thread termination
		mainParCore3.activeThreads--;
		do_stepParCore3.activeThreads--;

		do_stepParCore3.reactionCounter = do_stepParReactionCounter;
		do_stepParCore3.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_stepParCore3.reactionCounter == do_stepParReactionCounter);

		// Delete this par(...) handler.
		do_stepParHandlerSlave3.prevThread -> nextThread = do_stepParHandlerSlave3.nextThread;
		do_stepParHandlerSlave3.nextThread -> prevThread = do_stepParHandlerSlave3.prevThread;
			
		// Go to the next thread.
		goto *do_stepParHandlerSlave3.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		do_stepParCore3.reactionCounter = do_stepParReactionCounter;

		do_stepParHandlerSlave3.programCounter = &&wrongParId_do_stepParHandlerSlave3;
		wrongParId_do_stepParHandlerSlave3:;

		do_stepParCore3.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_stepParCore3.reactionCounter == do_stepParReactionCounter);
		do_stepParCore3.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (do_stepParParent.parStatus == FOREC_PAR_ON && do_stepParParent.parId == parId) {
			goto *do_stepParHandlerSlave3.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		do_stepParHandlerSlave3.programCounter = &&do_stepParHandlerSlave3;
		
		goto do_stepParHandlerSlave3;
	}
	
	// Control should not reach here.
	goto do_stepParHandlerSlave3;
}
	// forec:scheduler:parHandler:do_step:slave:3:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:do_draw:slave:3:start
	//-- do_draw:
do_drawReactionStartSlave3: {
	// Go to the next thread.
	goto *do_drawReactionStartSlave3.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:do_draw:slave:3:end
 
	// forec:scheduler:reactionStart:do_step:slave:3:start
	//-- do_step:
do_stepReactionStartSlave3: {
	// Go to the next thread.
	goto *do_stepReactionStartSlave3.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:do_step:slave:3:end
 
	// forec:scheduler:reactionStart:main:slave:3:start
	//-- main:
mainReactionStartSlave3: {
	// Go to the next thread.
	goto *mainReactionStartSlave3.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:3:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:do_draw:slave:3:start
	//-- do_draw:
do_drawReactionEndSlave3: {
	// Determine if the core can still react or not.
	if (do_drawParCore3.activeThreads) {
		do_drawParCore3.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (do_drawParCore3.reactionCounter == do_drawParReactionCounter);
		do_drawParCore3.reactionCounter++;
		
		// Continue reacting.
		goto *do_drawReactionEndSlave3.nextThread -> programCounter;
	} else {
		short int parId = do_drawParParent.parId;

		do_drawReactionEndSlave3.programCounter = &&terminated_do_drawReactionEndSlave3;
		terminated_do_drawReactionEndSlave3:;
		
		do_drawParCore3.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (do_drawParCore3.reactionCounter == do_drawParReactionCounter);
		do_drawParCore3.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (do_drawParParent.parStatus == FOREC_PAR_ON && do_drawParParent.parId == parId) {
			goto *do_drawReactionEndSlave3.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		do_drawReactionStartSlave3.prevThread -> nextThread = &do_drawParHandlerSlave3;
		do_drawParHandlerSlave3.prevThread = do_drawReactionStartSlave3.prevThread;
		do_drawParHandlerSlave3.nextThread = do_drawReactionEndSlave3.nextThread;
		do_drawReactionEndSlave3.nextThread -> prevThread = &do_drawParHandlerSlave3;
		goto do_drawParHandlerSlave3;
	}
	
	// Control shouldn't reach here.
	goto do_drawReactionEndSlave3;
}
	// forec:scheduler:reactionEnd:do_draw:slave:3:end
 
	// forec:scheduler:reactionEnd:do_step:slave:3:start
	//-- do_step:
do_stepReactionEndSlave3: {
	// Determine if the core can still react or not.
	if (do_stepParCore3.activeThreads) {
		do_stepParCore3.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (do_stepParCore3.reactionCounter == do_stepParReactionCounter);
		do_stepParCore3.reactionCounter++;
		
		// Continue reacting.
		goto *do_stepReactionEndSlave3.nextThread -> programCounter;
	} else {
		short int parId = do_stepParParent.parId;

		do_stepReactionEndSlave3.programCounter = &&terminated_do_stepReactionEndSlave3;
		terminated_do_stepReactionEndSlave3:;
		
		do_stepParCore3.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (do_stepParCore3.reactionCounter == do_stepParReactionCounter);
		do_stepParCore3.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (do_stepParParent.parStatus == FOREC_PAR_ON && do_stepParParent.parId == parId) {
			goto *do_stepReactionEndSlave3.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		do_stepReactionStartSlave3.prevThread -> nextThread = &do_stepParHandlerSlave3;
		do_stepParHandlerSlave3.prevThread = do_stepReactionStartSlave3.prevThread;
		do_stepParHandlerSlave3.nextThread = do_stepReactionEndSlave3.nextThread;
		do_stepReactionEndSlave3.nextThread -> prevThread = &do_stepParHandlerSlave3;
		goto do_stepParHandlerSlave3;
	}
	
	// Control shouldn't reach here.
	goto do_stepReactionEndSlave3;
}
	// forec:scheduler:reactionEnd:do_step:slave:3:end
 
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
	// forec:thread:do_draw:start
	/*--------------------------------------------------------------
	| Thread do_draw
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_draw_local;

	// Thread body -------------------------------------------------
	do_draw__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_do_draw_local.value = grid_ptr__global_0_0_copy_main.value;
		grid_ptr__global_0_0_copy_do_draw_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		grid_ptr__global_0_0_copy_do_draw_local.value = grid_ptr__global_0_0_copy_do_draw_local.value;
		grid_ptr__global_0_0_copy_do_draw_local.status = FOREC_SHARED_MODIFIED;

		// par2(do_draw_0__thread, do_draw_1__thread, do_draw_2__thread, do_draw_3__thread);
		grid_ptr__global_0_0_copy_do_draw = grid_ptr__global_0_0_copy_do_draw_local;
		// Set the par(...) information.
		do_drawParParent.parId = 2;
		do_drawParParent.parStatus = FOREC_PAR_ON;
		do_drawParParent.programCounter = &&par2JoinAddress_do_drawParParent;

		// Remove this thread from the linked list.
		do_draw__thread.nextThread -> prevThread = do_draw__thread.prevThread;
		do_draw__thread.prevThread -> nextThread = do_draw__thread.nextThread;
		// forec:statement:par:par2:start
		goto do_drawParHandlerMaster0;
		par2JoinAddress_do_drawParParent:;
		// forec:statement:par:par2:end
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
	Shared_life_data__global_0_0 life_data_ptr__global_0_0_copy_do_draw_0_local;
	Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_draw_0_local;

	// Thread body -------------------------------------------------
	do_draw_0__thread: {
		// Initialise the local copies of shared variables.
		life_data_ptr__global_0_0_copy_do_draw_0_local.value = life_data_ptr__global_0_0.value;
		life_data_ptr__global_0_0_copy_do_draw_0_local.status = FOREC_SHARED_UNMODIFIED;
		grid_ptr__global_0_0_copy_do_draw_0_local.value = grid_ptr__global_0_0_copy_do_draw.value;
		grid_ptr__global_0_0_copy_do_draw_0_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		update_display(0, life_data_ptr__global_0_0_copy_do_draw_0_local.value, * grid_ptr__global_0_0_copy_do_draw_0_local.value);

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
	Shared_life_data__global_0_0 life_data_ptr__global_0_0_copy_do_draw_1_local;
	Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_draw_1_local;

	// Thread body -------------------------------------------------
	do_draw_1__thread: {
		// Initialise the local copies of shared variables.
		life_data_ptr__global_0_0_copy_do_draw_1_local.value = life_data_ptr__global_0_0.value;
		life_data_ptr__global_0_0_copy_do_draw_1_local.status = FOREC_SHARED_UNMODIFIED;
		grid_ptr__global_0_0_copy_do_draw_1_local.value = grid_ptr__global_0_0_copy_do_draw.value;
		grid_ptr__global_0_0_copy_do_draw_1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		update_display(1, life_data_ptr__global_0_0_copy_do_draw_1_local.value, * grid_ptr__global_0_0_copy_do_draw_1_local.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_draw_1:start

		// Delete thread from the linked list and core.
		do_drawParCore1.activeThreads--;
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
	Shared_life_data__global_0_0 life_data_ptr__global_0_0_copy_do_draw_2_local;
	Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_draw_2_local;

	// Thread body -------------------------------------------------
	do_draw_2__thread: {
		// Initialise the local copies of shared variables.
		life_data_ptr__global_0_0_copy_do_draw_2_local.value = life_data_ptr__global_0_0.value;
		life_data_ptr__global_0_0_copy_do_draw_2_local.status = FOREC_SHARED_UNMODIFIED;
		grid_ptr__global_0_0_copy_do_draw_2_local.value = grid_ptr__global_0_0_copy_do_draw.value;
		grid_ptr__global_0_0_copy_do_draw_2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		update_display(2, life_data_ptr__global_0_0_copy_do_draw_2_local.value, * grid_ptr__global_0_0_copy_do_draw_2_local.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_draw_2:start

		// Delete thread from the linked list and core.
		do_drawParCore2.activeThreads--;
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
	Shared_life_data__global_0_0 life_data_ptr__global_0_0_copy_do_draw_3_local;
	Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_draw_3_local;

	// Thread body -------------------------------------------------
	do_draw_3__thread: {
		// Initialise the local copies of shared variables.
		life_data_ptr__global_0_0_copy_do_draw_3_local.value = life_data_ptr__global_0_0.value;
		life_data_ptr__global_0_0_copy_do_draw_3_local.status = FOREC_SHARED_UNMODIFIED;
		grid_ptr__global_0_0_copy_do_draw_3_local.value = grid_ptr__global_0_0_copy_do_draw.value;
		grid_ptr__global_0_0_copy_do_draw_3_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		update_display(3, life_data_ptr__global_0_0_copy_do_draw_3_local.value, * grid_ptr__global_0_0_copy_do_draw_3_local.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_draw_3:start

		// Delete thread from the linked list and core.
		do_drawParCore3.activeThreads--;
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
	int ncols__do_step_0_0;
	int nrows__do_step_0_0;
	int i__do_step_0_0;
	Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_step_local;

	// Thread body -------------------------------------------------
	do_step__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_do_step_local.value = grid_ptr__global_0_0_copy_main.value;
		grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		ncols__do_step_0_0 = 250;
		nrows__do_step_0_0 = 25*4;
		for (i__do_step_0_0 = 0; i__do_step_0_0 <= nrows__do_step_0_0 + 1; i__do_step_0_0++) {
			(* grid_ptr__global_0_0_copy_do_step_local.value)[0][i__do_step_0_0] = (* grid_ptr__global_0_0_copy_do_step_local.value)[1][i__do_step_0_0];
			grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_MODIFIED;
			(* grid_ptr__global_0_0_copy_do_step_local.value)[ncols__do_step_0_0 + 1][i__do_step_0_0] = (* grid_ptr__global_0_0_copy_do_step_local.value)[ncols__do_step_0_0][i__do_step_0_0];
			grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_MODIFIED;
		}
		for (i__do_step_0_0 = 1; i__do_step_0_0 <= ncols__do_step_0_0; i__do_step_0_0++) {
			(* grid_ptr__global_0_0_copy_do_step_local.value)[i__do_step_0_0][0] = (* grid_ptr__global_0_0_copy_do_step_local.value)[i__do_step_0_0][nrows__do_step_0_0];
			grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_MODIFIED;
			(* grid_ptr__global_0_0_copy_do_step_local.value)[i__do_step_0_0][nrows__do_step_0_0 + 1] = (* grid_ptr__global_0_0_copy_do_step_local.value)[i__do_step_0_0][1];
			grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_MODIFIED;
		}
		(* grid_ptr__global_0_0_copy_do_step_local.value)[0][0] = (* grid_ptr__global_0_0_copy_do_step_local.value)[0][nrows__do_step_0_0];
		grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_MODIFIED;
		(* grid_ptr__global_0_0_copy_do_step_local.value)[0][nrows__do_step_0_0 + 1] = (* grid_ptr__global_0_0_copy_do_step_local.value)[0][1];
		grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_MODIFIED;
		(* grid_ptr__global_0_0_copy_do_step_local.value)[ncols__do_step_0_0 + 1][0] = (* grid_ptr__global_0_0_copy_do_step_local.value)[ncols__do_step_0_0 + 1][nrows__do_step_0_0];
		grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_MODIFIED;
		(* grid_ptr__global_0_0_copy_do_step_local.value)[ncols__do_step_0_0 + 1][nrows__do_step_0_0 + 1] = (* grid_ptr__global_0_0_copy_do_step_local.value)[ncols__do_step_0_0 + 1][1];
		grid_ptr__global_0_0_copy_do_step_local.status = FOREC_SHARED_MODIFIED;

		// par1(do_step_0__thread, do_step_1__thread, do_step_2__thread, do_step_3__thread);
		grid_ptr__global_0_0_copy_do_step = grid_ptr__global_0_0_copy_do_step_local;
		// Set the par(...) information.
		do_stepParParent.parId = 1;
		do_stepParParent.parStatus = FOREC_PAR_ON;
		do_stepParParent.programCounter = &&par1JoinAddress_do_stepParParent;

		// Remove this thread from the linked list.
		do_step__thread.nextThread -> prevThread = do_step__thread.prevThread;
		do_step__thread.prevThread -> nextThread = do_step__thread.nextThread;
		// forec:statement:par:par1:start
		goto do_stepParHandlerMaster0;
		par1JoinAddress_do_stepParParent:;
		// forec:statement:par:par1:end
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
	Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_step_0_local;
	Shared_next_grid__global_0_0 next_grid_ptr__global_0_0_copy_do_step_0_local;

	// Thread body -------------------------------------------------
	do_step_0__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_do_step_0_local.value = grid_ptr__global_0_0_copy_do_step.value;
		grid_ptr__global_0_0_copy_do_step_0_local.status = FOREC_SHARED_UNMODIFIED;
		next_grid_ptr__global_0_0_copy_do_step_0_local.value = next_grid_ptr__global_0_0.value;
		next_grid_ptr__global_0_0_copy_do_step_0_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		update_grid(0, next_grid_ptr__global_0_0_copy_do_step_0_local.value, * grid_ptr__global_0_0_copy_do_step_0_local.value);

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
	Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_step_1_local;
	Shared_next_grid__global_0_0 next_grid_ptr__global_0_0_copy_do_step_1_local;

	// Thread body -------------------------------------------------
	do_step_1__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_do_step_1_local.value = grid_ptr__global_0_0_copy_do_step.value;
		grid_ptr__global_0_0_copy_do_step_1_local.status = FOREC_SHARED_UNMODIFIED;
		next_grid_ptr__global_0_0_copy_do_step_1_local.value = next_grid_ptr__global_0_0.value;
		next_grid_ptr__global_0_0_copy_do_step_1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		update_grid(1, next_grid_ptr__global_0_0_copy_do_step_1_local.value, * grid_ptr__global_0_0_copy_do_step_1_local.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_step_1:start

		// Delete thread from the linked list and core.
		do_stepParCore1.activeThreads--;
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
	Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_step_2_local;
	Shared_next_grid__global_0_0 next_grid_ptr__global_0_0_copy_do_step_2_local;

	// Thread body -------------------------------------------------
	do_step_2__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_do_step_2_local.value = grid_ptr__global_0_0_copy_do_step.value;
		grid_ptr__global_0_0_copy_do_step_2_local.status = FOREC_SHARED_UNMODIFIED;
		next_grid_ptr__global_0_0_copy_do_step_2_local.value = next_grid_ptr__global_0_0.value;
		next_grid_ptr__global_0_0_copy_do_step_2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		update_grid(2, next_grid_ptr__global_0_0_copy_do_step_2_local.value, * grid_ptr__global_0_0_copy_do_step_2_local.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_step_2:start

		// Delete thread from the linked list and core.
		do_stepParCore2.activeThreads--;
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
	Shared_grid__global_0_0 grid_ptr__global_0_0_copy_do_step_3_local;
	Shared_next_grid__global_0_0 next_grid_ptr__global_0_0_copy_do_step_3_local;

	// Thread body -------------------------------------------------
	do_step_3__thread: {
		// Initialise the local copies of shared variables.
		grid_ptr__global_0_0_copy_do_step_3_local.value = grid_ptr__global_0_0_copy_do_step.value;
		grid_ptr__global_0_0_copy_do_step_3_local.status = FOREC_SHARED_UNMODIFIED;
		next_grid_ptr__global_0_0_copy_do_step_3_local.value = next_grid_ptr__global_0_0.value;
		next_grid_ptr__global_0_0_copy_do_step_3_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		update_grid(3, next_grid_ptr__global_0_0_copy_do_step_3_local.value, * grid_ptr__global_0_0_copy_do_step_3_local.value);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_step_3:start

		// Delete thread from the linked list and core.
		do_stepParCore3.activeThreads--;
		do_step_3__thread.nextThread -> prevThread = do_step_3__thread.prevThread;
		do_step_3__thread.prevThread -> nextThread = do_step_3__thread.nextThread;
		goto *do_step_3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:do_step_3:end
	} // do_step_3__thread
	// forec:thread:do_step_3:end


} // End of the main() function.

void initialise(const int ncols__initialise_0_0, const int nrows__initialise_0_0, int *** grid__initialise_0_0, int *** next_grid__initialise_0_0, struct life_datum__global_0_0 *** life_data__initialise_0_0) {
	allocate_grid(ncols__initialise_0_0, nrows__initialise_0_0, grid__initialise_0_0);
	allocate_grid(ncols__initialise_0_0, nrows__initialise_0_0, next_grid__initialise_0_0);
	allocate_life_data(ncols__initialise_0_0, nrows__initialise_0_0, life_data__initialise_0_0);
	random_initByTime();
	randomize_grid(ncols__initialise_0_0, nrows__initialise_0_0, grid__initialise_0_0, 0.25);
}

void allocate_grid(const int ncols__allocate_grid_0_0, const int nrows__allocate_grid_0_0, int *** grid__allocate_grid_0_0) {
	(* grid__allocate_grid_0_0) = (int **)malloc((ncols__allocate_grid_0_0 + 2)*sizeof(int *));
	int i__allocate_grid_0_0;
	for (i__allocate_grid_0_0 = 0; i__allocate_grid_0_0 < ncols__allocate_grid_0_0 + 2; i__allocate_grid_0_0++) {
		(* grid__allocate_grid_0_0)[i__allocate_grid_0_0] = (int *)malloc((nrows__allocate_grid_0_0 + 2)*sizeof(int));
		int j__allocate_grid_1_0;
		for (j__allocate_grid_1_0 = 0; j__allocate_grid_1_0 < nrows__allocate_grid_0_0 + 2; j__allocate_grid_1_0++) {
			(* grid__allocate_grid_0_0)[i__allocate_grid_0_0][j__allocate_grid_1_0] = 0;
		}
	}
}

void allocate_life_data(const int ncols__allocate_life_data_0_0, const int nrows__allocate_life_data_0_0, struct life_datum__global_0_0 *** life_data__allocate_life_data_0_0) {
	(* life_data__allocate_life_data_0_0) = (struct life_datum__global_0_0 **)malloc((ncols__allocate_life_data_0_0)*sizeof(struct life_datum__global_0_0 *));
	int i__allocate_life_data_0_0;
	for (i__allocate_life_data_0_0 = 0; i__allocate_life_data_0_0 < ncols__allocate_life_data_0_0; i__allocate_life_data_0_0++) {
		(* life_data__allocate_life_data_0_0)[i__allocate_life_data_0_0] = (struct life_datum__global_0_0 *)malloc((nrows__allocate_life_data_0_0)*sizeof(struct life_datum__global_0_0));
	}
}

void cleanup_grid(const int ncols__cleanup_grid_0_0, const int nrows__cleanup_grid_0_0, int *** grid__cleanup_grid_0_0) {
	int i__cleanup_grid_0_0;
	for (i__cleanup_grid_0_0 = 0; i__cleanup_grid_0_0 < ncols__cleanup_grid_0_0 + 2; i__cleanup_grid_0_0++) {
		free((* grid__cleanup_grid_0_0)[i__cleanup_grid_0_0]);
	}
	free(* grid__cleanup_grid_0_0);
}

void cleanup_life_data(const int ncols__cleanup_life_data_0_0, const int nrows__cleanup_life_data_0_0, struct life_datum__global_0_0 *** life_data__cleanup_life_data_0_0) {
	int i__cleanup_life_data_0_0;
	for (i__cleanup_life_data_0_0 = 0; i__cleanup_life_data_0_0 < ncols__cleanup_life_data_0_0; i__cleanup_life_data_0_0++) {
		free((* life_data__cleanup_life_data_0_0)[i__cleanup_life_data_0_0]);
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
		}
	}
}

double rand_double(void) {
	return (double)rand()/(double)RAND_MAX__global_0_0;
}

void random_initByTime(void) {
	time_t__global_0_0 ltime__random_initByTime_0_0;
	time(&ltime__random_initByTime_0_0);
	srand((unsigned)ltime__random_initByTime_0_0);
}

void update_grid(const int threadNumber__update_grid_0_0, int *** next_grid__update_grid_0_0, int ** grid__update_grid_0_0) {
	int ncols__update_grid_0_0 = 250;
	int RANGE__update_grid_0_0 = 25;
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
				}
				if (neighbors__update_grid_2_0 > 3) {
					continue;
				} else {
					// if4
				}
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
		}
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
		}
	}
}

