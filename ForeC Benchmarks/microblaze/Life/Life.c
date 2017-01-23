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
#define FSL_COUNTER_ID				2
Counter counter;

// ForeC hardware mutex
#include "forec_mutex.h"
#define FSL_FOREC_MUTEX_ID			0
#define FSL_FOREC_MUTEX_RESET_ID	1
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
// Thread do_draw with par(...)s
volatile Parent do_drawParParent;
volatile Core do_drawParCore4;
volatile Core do_drawParCore5;
volatile Core do_drawParCore6;
volatile Core do_drawParCore7;
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
volatile Core mainParCore4;
volatile Core mainParCore5;
volatile Core mainParCore6;
volatile Core mainParCore7;
volatile int mainParReactionCounter;


/*==============================================================
| Original global declarations:
| Global declarations in the original program code.
*=============================================================*/
int rand_seed__global_0_0 = 0;
int whiteColor__global_0_0;

int *leftInt(int ** lhs__leftInt_0_0, int ** rhs__leftInt_0_0) {
	return * lhs__leftInt_0_0;
}

int life_data_color__global_0_0[(10 + 2)*(12 + 2)];
int *life_data_color_ptr1__global_0_0 = life_data_color__global_0_0;
int *life_data_color_ptr2__global_0_0 = life_data_color__global_0_0;
int *life_data_color_ptr3__global_0_0 = life_data_color__global_0_0;
int *life_data_color_ptr4__global_0_0 = life_data_color__global_0_0;
int life_data_x1__global_0_0[(10 + 2)*(12 + 2)];
int *life_data_x1_ptr1__global_0_0 = life_data_x1__global_0_0;
int *life_data_x1_ptr2__global_0_0 = life_data_x1__global_0_0;
int *life_data_x1_ptr3__global_0_0 = life_data_x1__global_0_0;
int *life_data_x1_ptr4__global_0_0 = life_data_x1__global_0_0;
int life_data_y1__global_0_0[(10 + 2)*(12 + 2)];
int *life_data_y1_ptr1__global_0_0 = life_data_y1__global_0_0;
int *life_data_y1_ptr2__global_0_0 = life_data_y1__global_0_0;
int *life_data_y1_ptr3__global_0_0 = life_data_y1__global_0_0;
int *life_data_y1_ptr4__global_0_0 = life_data_y1__global_0_0;
int grid__global_0_0[(10 + 2)*(12 + 2)];
int *grid_ptr1__global_0_0 = grid__global_0_0;
int *grid_ptr2__global_0_0 = grid__global_0_0;
int *grid_ptr3__global_0_0 = grid__global_0_0;
int *grid_ptr4__global_0_0 = grid__global_0_0;
int *grid_ptr5__global_0_0 = grid__global_0_0;
int next_grid__global_0_0[(10 + 2)*(12 + 2)];
int *next_grid_ptr2__global_0_0 = next_grid__global_0_0;
int *next_grid_ptr3__global_0_0 = next_grid__global_0_0;
int *next_grid_ptr4__global_0_0 = next_grid__global_0_0;
int *next_grid_ptr5__global_0_0 = next_grid__global_0_0;

float rand_float(void);

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

/* input */ int freeze__global_0_0;

int done__global_0_0 = 0;

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// do_draw
// do_draw_0
// do_draw_1
// do_draw_2
// do_draw_3
// do_step
// do_step_0
// do_step_1
// do_step_2
// do_step_3
// main

// forec:scheduler:boot:start
int main(int argc__main_0_0, char ** argv__main_0_0) {

/*==============================================================
| Multicore startup:
| Platform dependent code.  Core identifies itself and
| executes its corresponding start up code.
*=============================================================*/
	// Initialise ForeC specific values ----------------------------
	// Thread do_draw with par(...)s
	do_drawParParent.parStatus = FOREC_PAR_OFF;
	do_drawParCore4.sync = 1;
	do_drawParCore4.status = FOREC_CORE_REACTING;
	do_drawParCore5.sync = 1;
	do_drawParCore5.status = FOREC_CORE_REACTING;
	do_drawParCore6.sync = 1;
	do_drawParCore6.status = FOREC_CORE_REACTING;
	do_drawParCore7.sync = 1;
	do_drawParCore7.status = FOREC_CORE_REACTING;
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
	mainParCore4.sync = 1;
	mainParCore4.status = FOREC_CORE_REACTING;
	mainParCore5.sync = 1;
	mainParCore5.status = FOREC_CORE_REACTING;
	mainParCore6.sync = 1;
	mainParCore6.status = FOREC_CORE_REACTING;
	mainParCore7.sync = 1;
	mainParCore7.status = FOREC_CORE_REACTING;
	mainParReactionCounter = 0;


	// ForeC mutex -------------------------------------------------
	unsigned int forec_mutex_value;
	forec_mutex_reset(FSL_FOREC_MUTEX_RESET_ID);
	
	// Variables for par()s ----------------------------------------
	// par0
	Thread do_draw__thread;
	Thread do_step__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionStartSlave1;
	Thread mainReactionStartSlave2;
	Thread mainReactionStartSlave3;
	Thread mainReactionStartSlave4;
	Thread mainReactionStartSlave5;
	Thread mainReactionStartSlave6;
	Thread mainReactionStartSlave7;
	Thread mainReactionEndMaster0;
	Thread mainReactionEndSlave1;
	Thread mainReactionEndSlave2;
	Thread mainReactionEndSlave3;
	Thread mainReactionEndSlave4;
	Thread mainReactionEndSlave5;
	Thread mainReactionEndSlave6;
	Thread mainReactionEndSlave7;
	Thread do_drawParHandlerMaster4;
	Thread do_drawParHandlerSlave5;
	Thread do_drawParHandlerSlave6;
	Thread do_drawParHandlerSlave7;
	Thread do_stepParHandlerMaster0;
	Thread do_stepParHandlerSlave1;
	Thread do_stepParHandlerSlave2;
	Thread do_stepParHandlerSlave3;
	Thread abortStrong0Check0;
	Thread abortStrong0Check1;
	Thread abortStrong0Check2;
	Thread abortStrong0Check3;
	Thread abortStrong0Check4;
	Thread abortStrong0Check5;
	Thread abortStrong0Check6;
	Thread abortStrong0Check7;

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
	Thread do_drawReactionStartMaster4;
	Thread do_drawReactionStartSlave5;
	Thread do_drawReactionStartSlave6;
	Thread do_drawReactionStartSlave7;
	Thread do_drawReactionEndMaster4;
	Thread do_drawReactionEndSlave5;
	Thread do_drawReactionEndSlave6;
	Thread do_drawReactionEndSlave7;


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
			while(mainParCore4.sync);
			while(mainParCore5.sync);
			while(mainParCore6.sync);
			while(mainParCore7.sync);
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

		case (4):
			mainParCore4.sync = 0;
			goto mainParCore4;

		case (5):
			mainParCore5.sync = 0;
			goto mainParCore5;

		case (6):
			mainParCore6.sync = 0;
			goto mainParCore6;

		case (7):
			mainParCore7.sync = 0;
			goto mainParCore7;

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
	int MAX_GENERATIONS__main_0_0;
	int ncols__main_0_0;
	int nrows__main_0_0;
	int i__main_0_0;
	int j__main_1_0;
	int index__main_2_0;
	int value__main_2_0;
	int generation__main_0_0;
	int i__main_2_1;
	int j__main_3_0;
	int index__main_4_0;
	int datum__main_4_0;

mainParCore0: {
	// forec:scheduler:counter:start
	// Initialise and start counting the elapsed cycles for each reaction.
	counterInitialise(counter);
	counterStart(counter, FSL_COUNTER_ID);
	// forec:scheduler:counter:end
	
	//--------------------------------------------------------------

	MAX_GENERATIONS__main_0_0 = 10000;
	ncols__main_0_0 = 10;
	nrows__main_0_0 = 3*4;
	rand_seed__global_0_0 = (rand_seed__global_0_0 + 0)%3;
	for (i__main_0_0 = 1; i__main_0_0 <= ncols__main_0_0; i__main_0_0++) {
		for (j__main_1_0 = 1; j__main_1_0 <= nrows__main_0_0; j__main_1_0++) {
			index__main_2_0 = i__main_0_0*ncols__main_0_0 + j__main_1_0;
			value__main_2_0 = rand_float() < 0.25;
			grid__global_0_0[1] = value__main_2_0;
			asm volatile ("nop");
			// forec:iteration:for1_0:bound:12:12
		}
		asm volatile ("nop");
		// forec:iteration:for1_1:bound:10:10
	}
	freeze__global_0_0 = 0;
	generation__main_0_0 = 0;

	/* abortStrong0 */ {
		// forec:statement:abort:abortStrong0:start
		if (done__global_0_0) {
			goto abortEnd_abortStrong0;
		}
		// forec:statement:abort:abortStrong0:end

		while (1) {
			// par0(do_step__thread, do_draw__thread);
			// forec:statement:par:par0:start
			// Set the par(...) information.
			mainParParent.parId = 0;
			mainParParent.parStatus = FOREC_PAR_ON;

			// Link the threads and handlers together.
			mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
			abortStrong0Check0.programCounter = &&abortStrong0Check0;
			mainReactionStartMaster0.nextThread = &abortStrong0Check0;
			abortStrong0Check0.prevThread = &mainReactionStartMaster0;
			do_step__thread.programCounter = &&do_step__thread;
			abortStrong0Check0.nextThread = &do_step__thread;
			do_step__thread.prevThread = &abortStrong0Check0;
			do_stepParHandlerMaster0.programCounter = &&do_stepParHandlerMaster0;
			do_step__thread.nextThread = &do_stepParHandlerMaster0;
			do_stepParHandlerMaster0.prevThread = &do_step__thread;
			mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
			do_stepParHandlerMaster0.nextThread = &mainReactionEndMaster0;
			mainReactionEndMaster0.prevThread = &do_stepParHandlerMaster0;

			// Link the last and first threads/handlers together.
			mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
			mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

			// Set the join address.
			mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

			// Set the core information.
			mainParCore0.activeThreads = 2;
			mainParCore0.reactionCounter = mainParReactionCounter;

			// Go to the first thread.
			goto do_step__thread;
			par0JoinAddress_mainParCore0:;
			// forec:statement:par:par0:end

			for (i__main_2_1 = 0; i__main_2_1 < ncols__main_0_0 + 2; i__main_2_1++) {
				for (j__main_3_0 = 0; j__main_3_0 < nrows__main_0_0 + 2; j__main_3_0++) {
					index__main_4_0 = i__main_2_1*ncols__main_0_0 + j__main_3_0;
					datum__main_4_0 = next_grid__global_0_0[1];
					grid__global_0_0[1] = datum__main_4_0;
					asm volatile ("nop");
					// forec:iteration:for1_2:bound:14:14
				}
				asm volatile ("nop");
				// forec:iteration:for1_3:bound:12:12
			}
			if (generation__main_0_0++ > MAX_GENERATIONS__main_0_0) {
				done__global_0_0 = 1;
			} else {
				// if0
			}
			if (freeze__global_0_0) {
				done__global_0_0 = 1;
			} else {
				// if1
			}

			// pause;
			// forec:statement:pause:pause0:start

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
			// Restart the counting of elapsed cycles for the next reaction.
			counterReset(counter);
			counterStart(counter, FSL_COUNTER_ID);
			// forec:scheduler:counter:end
			// forec:statement:pause:pause0:end

			// Strong aborts:
			// forec:statement:abort:abortStrong0:start
			if (done__global_0_0) {
				goto abortEnd_abortStrong0;
			}
			// forec:statement:abort:abortStrong0:end

			// forec:scheduler:iterationEnd:while_4:start
			// Synchronise end of iteration
			mainParParent.parId = -2;
			mainParParent.parStatus = FOREC_PAR_ON;
			mainParParent.programCounter = &&while_4_endAddress;
			goto mainParHandlerMaster0;
			while_4_endAddress:;
			// forec:scheduler:iterationEnd:while_4:end
			asm volatile ("nop");
		}
		abortEnd_abortStrong0:;
	} // when (done__global_0_0);
	// forec:statement:abort:abortStrong0:scope:end

	//--------------------------------------------------------------

	// forec:scheduler:threadRemove:main:start

	// forec:scheduler:counter:start
	do { counterRead(counter, FSL_COUNTER_ID); } while (counter.current < 0);
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
		while(mainParCore4.status == FOREC_CORE_REACTING);
		while(mainParCore5.status == FOREC_CORE_REACTING);
		while(mainParCore6.status == FOREC_CORE_REACTING);
		while(mainParCore7.status == FOREC_CORE_REACTING);

		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;

		// Set slave cores' status to reacting.
		mainParCore1.status = FOREC_CORE_REACTING;
		mainParCore2.status = FOREC_CORE_REACTING;
		mainParCore3.status = FOREC_CORE_REACTING;
		mainParCore4.status = FOREC_CORE_REACTING;
		mainParCore5.status = FOREC_CORE_REACTING;
		mainParCore6.status = FOREC_CORE_REACTING;
		mainParCore7.status = FOREC_CORE_REACTING;

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
	// forec:scheduler:parHandler:do_step:master:0:start
	//-- Thread do_step par(...) handlers
do_stepParHandlerMaster0: {
	// Check the execution status of the nested par(...)s.
	if (do_stepParParent.parStatus == FOREC_PAR_OFF) {
		// Release the mutex.
		forec_mutex_clear(30, FSL_FOREC_MUTEX_ID);

		goto *do_stepParHandlerMaster0.nextThread -> programCounter;
	}
	// Release the mutex.
	forec_mutex_clear(30, FSL_FOREC_MUTEX_ID);

	int parId = do_stepParParent.parId;

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

		forec_mutex_set(30, FSL_FOREC_MUTEX_ID);

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
		forec_mutex_set(30, FSL_FOREC_MUTEX_ID);

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
	while(mainParCore4.status == FOREC_CORE_REACTING);
	while(mainParCore5.status == FOREC_CORE_REACTING);
	while(mainParCore6.status == FOREC_CORE_REACTING);
	while(mainParCore7.status == FOREC_CORE_REACTING);

	// Reset the mutex.
	forec_mutex_reset(FSL_FOREC_MUTEX_RESET_ID);

	// Return back to the parent thread if all the cores have terminated.
	if (1 && mainParCore0.status == FOREC_CORE_TERMINATED && mainParCore1.status == FOREC_CORE_TERMINATED && mainParCore2.status == FOREC_CORE_TERMINATED && mainParCore3.status == FOREC_CORE_TERMINATED && mainParCore4.status == FOREC_CORE_TERMINATED && mainParCore5.status == FOREC_CORE_TERMINATED && mainParCore6.status == FOREC_CORE_TERMINATED && mainParCore7.status == FOREC_CORE_TERMINATED) {
		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;
		
		// Set slave cores' status to reacting
		mainParCore1.status = FOREC_CORE_REACTING;
		mainParCore2.status = FOREC_CORE_REACTING;
		mainParCore3.status = FOREC_CORE_REACTING;
		mainParCore4.status = FOREC_CORE_REACTING;
		mainParCore5.status = FOREC_CORE_REACTING;
		mainParCore6.status = FOREC_CORE_REACTING;
		mainParCore7.status = FOREC_CORE_REACTING;

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
	mainParCore7.status = FOREC_CORE_REACTING;

	// forec:scheduler:counter:start
	do { counterRead(counter, FSL_COUNTER_ID); } while (counter.current < 0);
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
	// forec:scheduler:abortHandler:abortStrong0:0:start
	// abortStrong0 (done__global_0_0)
abortStrong0Check0: {
	// Check the abort condition.
	if (done__global_0_0) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore0.activeThreads = 0;

		// Update the parent thread to resume at the end of the abort scope.
		mainParParent.programCounter = &&abortEnd_abortStrong0;
		
		goto mainReactionEndMaster0;
	}
	
	// Continue to the next thread.
	goto *abortStrong0Check0.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrong0:0:end


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
		abortStrong0Check1.programCounter = &&abortStrong0Check1;
		mainReactionStartSlave1.nextThread = &abortStrong0Check1;
		abortStrong0Check1.prevThread = &mainReactionStartSlave1;
		do_stepParHandlerSlave1.programCounter = &&do_stepParHandlerSlave1;
		abortStrong0Check1.nextThread = &do_stepParHandlerSlave1;
		do_stepParHandlerSlave1.prevThread = &abortStrong0Check1;
		mainReactionEndSlave1.programCounter = &&mainReactionEndSlave1;
		do_stepParHandlerSlave1.nextThread = &mainReactionEndSlave1;
		mainReactionEndSlave1.prevThread = &do_stepParHandlerSlave1;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave1.nextThread = &mainReactionStartSlave1;
		mainReactionStartSlave1.prevThread = &mainReactionEndSlave1;

		// Set the core information.
		mainParCore1.activeThreads = 1;
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
	// forec:scheduler:parHandler:do_step:slave:1:start
	//-- Thread do_step par(...) handlers
do_stepParHandlerSlave1: {
	// Synchronise the checking of the nested par(...) via a mutex.
	forec_mutex_read(forec_mutex_value, FSL_FOREC_MUTEX_ID);
	while ((unsigned)(forec_mutex_value & 0x40000000) == (unsigned)0x40000000) {
		forec_mutex_read(forec_mutex_value, FSL_FOREC_MUTEX_ID);
	}

	// Check the execution status of the nested par(...)s.
	if (do_stepParParent.parStatus == FOREC_PAR_OFF) {
		goto *do_stepParHandlerSlave1.nextThread -> programCounter;
	}

	int parId = do_stepParParent.parId;

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
		int parId = do_stepParParent.parId;

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
	// forec:scheduler:abortHandler:abortStrong0:1:start
	// abortStrong0 (done__global_0_0)
abortStrong0Check1: {
	// Check the abort condition.
	if (done__global_0_0) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore1.activeThreads = 0;
		
		goto mainReactionEndSlave1;
	}
	
	// Continue to the next thread.
	goto *abortStrong0Check1.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrong0:1:end

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
		abortStrong0Check2.programCounter = &&abortStrong0Check2;
		mainReactionStartSlave2.nextThread = &abortStrong0Check2;
		abortStrong0Check2.prevThread = &mainReactionStartSlave2;
		do_stepParHandlerSlave2.programCounter = &&do_stepParHandlerSlave2;
		abortStrong0Check2.nextThread = &do_stepParHandlerSlave2;
		do_stepParHandlerSlave2.prevThread = &abortStrong0Check2;
		mainReactionEndSlave2.programCounter = &&mainReactionEndSlave2;
		do_stepParHandlerSlave2.nextThread = &mainReactionEndSlave2;
		mainReactionEndSlave2.prevThread = &do_stepParHandlerSlave2;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave2.nextThread = &mainReactionStartSlave2;
		mainReactionStartSlave2.prevThread = &mainReactionEndSlave2;

		// Set the core information.
		mainParCore2.activeThreads = 1;
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
	// forec:scheduler:parHandler:do_step:slave:2:start
	//-- Thread do_step par(...) handlers
do_stepParHandlerSlave2: {
	// Synchronise the checking of the nested par(...) via a mutex.
	forec_mutex_read(forec_mutex_value, FSL_FOREC_MUTEX_ID);
	while ((unsigned)(forec_mutex_value & 0x40000000) == (unsigned)0x40000000) {
		forec_mutex_read(forec_mutex_value, FSL_FOREC_MUTEX_ID);
	}

	// Check the execution status of the nested par(...)s.
	if (do_stepParParent.parStatus == FOREC_PAR_OFF) {
		goto *do_stepParHandlerSlave2.nextThread -> programCounter;
	}

	int parId = do_stepParParent.parId;

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
		int parId = do_stepParParent.parId;

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
	// forec:scheduler:abortHandler:abortStrong0:2:start
	// abortStrong0 (done__global_0_0)
abortStrong0Check2: {
	// Check the abort condition.
	if (done__global_0_0) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore2.activeThreads = 0;
		
		goto mainReactionEndSlave2;
	}
	
	// Continue to the next thread.
	goto *abortStrong0Check2.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrong0:2:end

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
		abortStrong0Check3.programCounter = &&abortStrong0Check3;
		mainReactionStartSlave3.nextThread = &abortStrong0Check3;
		abortStrong0Check3.prevThread = &mainReactionStartSlave3;
		do_stepParHandlerSlave3.programCounter = &&do_stepParHandlerSlave3;
		abortStrong0Check3.nextThread = &do_stepParHandlerSlave3;
		do_stepParHandlerSlave3.prevThread = &abortStrong0Check3;
		mainReactionEndSlave3.programCounter = &&mainReactionEndSlave3;
		do_stepParHandlerSlave3.nextThread = &mainReactionEndSlave3;
		mainReactionEndSlave3.prevThread = &do_stepParHandlerSlave3;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave3.nextThread = &mainReactionStartSlave3;
		mainReactionStartSlave3.prevThread = &mainReactionEndSlave3;

		// Set the core information.
		mainParCore3.activeThreads = 1;
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
	// forec:scheduler:parHandler:do_step:slave:3:start
	//-- Thread do_step par(...) handlers
do_stepParHandlerSlave3: {
	// Synchronise the checking of the nested par(...) via a mutex.
	forec_mutex_read(forec_mutex_value, FSL_FOREC_MUTEX_ID);
	while ((unsigned)(forec_mutex_value & 0x40000000) == (unsigned)0x40000000) {
		forec_mutex_read(forec_mutex_value, FSL_FOREC_MUTEX_ID);
	}

	// Check the execution status of the nested par(...)s.
	if (do_stepParParent.parStatus == FOREC_PAR_OFF) {
		goto *do_stepParHandlerSlave3.nextThread -> programCounter;
	}

	int parId = do_stepParParent.parId;

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
		int parId = do_stepParParent.parId;

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
	// forec:scheduler:abortHandler:abortStrong0:3:start
	// abortStrong0 (done__global_0_0)
abortStrong0Check3: {
	// Check the abort condition.
	if (done__global_0_0) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore3.activeThreads = 0;
		
		goto mainReactionEndSlave3;
	}
	
	// Continue to the next thread.
	goto *abortStrong0Check3.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrong0:3:end

// forec:scheduler:parHandler:main:slave:4:start
/*--------------------------------------------------------------
| Slave core: core4
*-------------------------------------------------------------*/
mainParCore4: {
	// Check the execution status of the root par(...)s.
	while (mainParParent.parStatus == FOREC_PAR_OFF);

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave4.programCounter = &&mainReactionStartSlave4;
		abortStrong0Check4.programCounter = &&abortStrong0Check4;
		mainReactionStartSlave4.nextThread = &abortStrong0Check4;
		abortStrong0Check4.prevThread = &mainReactionStartSlave4;
		do_draw__thread.programCounter = &&do_draw__thread;
		abortStrong0Check4.nextThread = &do_draw__thread;
		do_draw__thread.prevThread = &abortStrong0Check4;
		do_drawParHandlerMaster4.programCounter = &&do_drawParHandlerMaster4;
		do_draw__thread.nextThread = &do_drawParHandlerMaster4;
		do_drawParHandlerMaster4.prevThread = &do_draw__thread;
		mainReactionEndSlave4.programCounter = &&mainReactionEndSlave4;
		do_drawParHandlerMaster4.nextThread = &mainReactionEndSlave4;
		mainReactionEndSlave4.prevThread = &do_drawParHandlerMaster4;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave4.nextThread = &mainReactionStartSlave4;
		mainReactionStartSlave4.prevThread = &mainReactionEndSlave4;

		// Set the core information.
		mainParCore4.activeThreads = 2;
		mainParCore4.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto do_draw__thread;
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
	// forec:scheduler:parHandler:do_draw:master:4:start
	//-- Thread do_draw par(...) handlers
do_drawParHandlerMaster4: {
	// Check the execution status of the nested par(...)s.
	if (do_drawParParent.parStatus == FOREC_PAR_OFF) {
		// Release the mutex.
		forec_mutex_clear(31, FSL_FOREC_MUTEX_ID);

		goto *do_drawParHandlerMaster4.nextThread -> programCounter;
	}
	// Release the mutex.
	forec_mutex_clear(31, FSL_FOREC_MUTEX_ID);

	int parId = do_drawParParent.parId;

	// Check the par(...) ID.
	if (parId == 2) {
		asm ("# par2 begin");
		// Link the threads and handlers together.
		do_drawReactionStartMaster4.programCounter = &&do_drawReactionStartMaster4;
		do_draw_0__thread.programCounter = &&do_draw_0__thread;
		do_drawReactionStartMaster4.nextThread = &do_draw_0__thread;
		do_draw_0__thread.prevThread = &do_drawReactionStartMaster4;
		do_drawReactionEndMaster4.programCounter = &&do_drawReactionEndMaster4;
		do_draw_0__thread.nextThread = &do_drawReactionEndMaster4;
		do_drawReactionEndMaster4.prevThread = &do_draw_0__thread;

		// Swap the nested par handler with the linked list.
		do_drawParHandlerMaster4.prevThread -> nextThread = &do_drawReactionStartMaster4;
		do_drawReactionStartMaster4.prevThread = do_drawParHandlerMaster4.prevThread;
		do_drawReactionEndMaster4.nextThread = do_drawParHandlerMaster4.nextThread;
		do_drawParHandlerMaster4.nextThread -> prevThread = &do_drawReactionEndMaster4;
		
		// Set the core information.
		do_drawParCore4.activeThreads = 1;
		do_drawParCore4.reactionCounter = do_drawParReactionCounter;
		
		// Go to the first thread.
		goto do_draw_0__thread;
		asm ("# par2 end");
	} else if (parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.
		while(do_drawParCore5.status == FOREC_CORE_REACTING);
		while(do_drawParCore6.status == FOREC_CORE_REACTING);
		while(do_drawParCore7.status == FOREC_CORE_REACTING);

		do_drawParParent.parStatus = FOREC_PAR_OFF;
		do_drawParParent.parId = -1;

		forec_mutex_set(31, FSL_FOREC_MUTEX_ID);

		// Set slave cores' status to reacting.
		do_drawParCore5.status = FOREC_CORE_REACTING;
		do_drawParCore6.status = FOREC_CORE_REACTING;
		do_drawParCore7.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		do_drawParReactionCounter++;

		// Return to thread do_draw.
		goto *do_drawParParent.programCounter;
	} else if (parId == -3) {
		// Thread termination
		mainParCore4.activeThreads--;
		do_drawParCore4.activeThreads--;

		// Wait for other cores to complete their reaction.
		while(do_drawParCore5.status == FOREC_CORE_REACTING);
		while(do_drawParCore6.status == FOREC_CORE_REACTING);
		while(do_drawParCore7.status == FOREC_CORE_REACTING);

		do_drawParParent.parStatus = FOREC_PAR_OFF;
		do_drawParParent.parId = -1;

		// Set slave cores' status to reacting.
		do_drawParCore5.status = FOREC_CORE_REACTING;
		do_drawParCore6.status = FOREC_CORE_REACTING;
		do_drawParCore7.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronisation.
		do_drawParReactionCounter++;

		// Delete this par(...) handler.
		do_drawParHandlerMaster4.prevThread -> nextThread = do_drawParHandlerMaster4.nextThread;
		do_drawParHandlerMaster4.nextThread -> prevThread = do_drawParHandlerMaster4.prevThread;
			
		// Return to thread do_draw.
		goto *do_drawParParent.programCounter;
	} else {
		// Unscheduled par(...)
		do_drawParCore4.reactionCounter = do_drawParReactionCounter;

		do_drawParHandlerMaster4.programCounter = &&wrongParId_do_drawParHandlerMaster4;
		wrongParId_do_drawParHandlerMaster4:;

		do_drawParCore4.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore4.reactionCounter == do_drawParReactionCounter);
		do_drawParCore4.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (do_drawParParent.parStatus == FOREC_PAR_ON && do_drawParParent.parId == parId) {
			goto *do_drawParHandlerMaster4.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		do_drawParHandlerMaster4.programCounter = &&do_drawParHandlerMaster4;
		
		goto do_drawParHandlerMaster4;
	}
	
	// Control should not reach here.
	goto do_drawParHandlerMaster4;
}
	// forec:scheduler:parHandler:do_draw:master:4:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:do_draw:master:4:start
	//-- do_draw:
do_drawReactionStartMaster4: {
	// Go to the next thread.
	goto *do_drawReactionStartMaster4.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:do_draw:master:4:end
 
	// forec:scheduler:reactionStart:main:slave:4:start
	//-- main:
mainReactionStartSlave4: {
	// Go to the next thread.
	goto *mainReactionStartSlave4.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:4:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:do_draw:master:4:start
	//-- do_draw:
do_drawReactionEndMaster4: {
	// Determine if the core can still react or not.
	if (do_drawParCore4.activeThreads) {
		do_drawParCore4.status = FOREC_CORE_REACTED;
	} else {
		do_drawParCore4.status = FOREC_CORE_TERMINATED;
	}
	
	// Wait for other cores to complete their reaction.
	while(do_drawParCore5.status == FOREC_CORE_REACTING);
	while(do_drawParCore6.status == FOREC_CORE_REACTING);
	while(do_drawParCore7.status == FOREC_CORE_REACTING);


	// Return back to the parent thread if all the cores have terminated.
	if (1 && do_drawParCore4.status == FOREC_CORE_TERMINATED && do_drawParCore5.status == FOREC_CORE_TERMINATED && do_drawParCore6.status == FOREC_CORE_TERMINATED && do_drawParCore7.status == FOREC_CORE_TERMINATED) {
		forec_mutex_set(31, FSL_FOREC_MUTEX_ID);

		do_drawParParent.parStatus = FOREC_PAR_OFF;
		do_drawParParent.parId = -1;
		
		// Set slave cores' status to reacting
		do_drawParCore5.status = FOREC_CORE_REACTING;
		do_drawParCore6.status = FOREC_CORE_REACTING;
		do_drawParCore7.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronization.
		do_drawParReactionCounter++;

		// Swap the reaction (start & end) handlers with (thread do_draw & nested par handler).
		do_drawReactionStartMaster4.prevThread -> nextThread = &do_draw__thread;
		do_draw__thread.prevThread = do_drawReactionStartMaster4.prevThread;
		do_draw__thread.nextThread = &do_drawParHandlerMaster4;
		do_drawParHandlerMaster4.prevThread = &do_draw__thread;
		do_drawParHandlerMaster4.nextThread = do_drawReactionEndMaster4.nextThread;
		do_drawReactionEndMaster4.nextThread -> prevThread = &do_drawParHandlerMaster4;

		goto *do_drawParParent.programCounter;
	}

	// Set slave cores' status to reacting
	do_drawParCore5.status = FOREC_CORE_REACTING;
	do_drawParCore6.status = FOREC_CORE_REACTING;
	do_drawParCore7.status = FOREC_CORE_REACTING;

	// Increment the reaction counter for synchronization.
	do_drawParReactionCounter++;

	// Go to the next thread.
	goto *do_drawReactionEndMaster4.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:do_draw:master:4:end
 
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
		int parId = mainParParent.parId;

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
 


	// Abort check handlers ----------------------------------------
	// forec:scheduler:abortHandler:abortStrong0:4:start
	// abortStrong0 (done__global_0_0)
abortStrong0Check4: {
	// Check the abort condition.
	if (done__global_0_0) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore4.activeThreads = 0;
		
		goto mainReactionEndSlave4;
	}
	
	// Continue to the next thread.
	goto *abortStrong0Check4.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrong0:4:end

// forec:scheduler:parHandler:main:slave:5:start
/*--------------------------------------------------------------
| Slave core: core5
*-------------------------------------------------------------*/
mainParCore5: {
	// Check the execution status of the root par(...)s.
	while (mainParParent.parStatus == FOREC_PAR_OFF);

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave5.programCounter = &&mainReactionStartSlave5;
		abortStrong0Check5.programCounter = &&abortStrong0Check5;
		mainReactionStartSlave5.nextThread = &abortStrong0Check5;
		abortStrong0Check5.prevThread = &mainReactionStartSlave5;
		do_drawParHandlerSlave5.programCounter = &&do_drawParHandlerSlave5;
		abortStrong0Check5.nextThread = &do_drawParHandlerSlave5;
		do_drawParHandlerSlave5.prevThread = &abortStrong0Check5;
		mainReactionEndSlave5.programCounter = &&mainReactionEndSlave5;
		do_drawParHandlerSlave5.nextThread = &mainReactionEndSlave5;
		mainReactionEndSlave5.prevThread = &do_drawParHandlerSlave5;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave5.nextThread = &mainReactionStartSlave5;
		mainReactionStartSlave5.prevThread = &mainReactionEndSlave5;

		// Set the core information.
		mainParCore5.activeThreads = 1;
		mainParCore5.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto do_drawParHandlerSlave5;
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
	// forec:scheduler:parHandler:do_draw:slave:5:start
	//-- Thread do_draw par(...) handlers
do_drawParHandlerSlave5: {
	// Synchronise the checking of the nested par(...) via a mutex.
	forec_mutex_read(forec_mutex_value, FSL_FOREC_MUTEX_ID);
	while ((unsigned)(forec_mutex_value & 0x80000000) == (unsigned)0x80000000) {
		forec_mutex_read(forec_mutex_value, FSL_FOREC_MUTEX_ID);
	}

	// Check the execution status of the nested par(...)s.
	if (do_drawParParent.parStatus == FOREC_PAR_OFF) {
		goto *do_drawParHandlerSlave5.nextThread -> programCounter;
	}

	int parId = do_drawParParent.parId;

	// Check the par(...) ID.
	if (parId == 2) {
		asm ("# par2 begin");
		// Link the threads and handlers together.
		do_drawReactionStartSlave5.programCounter = &&do_drawReactionStartSlave5;
		do_draw_1__thread.programCounter = &&do_draw_1__thread;
		do_drawReactionStartSlave5.nextThread = &do_draw_1__thread;
		do_draw_1__thread.prevThread = &do_drawReactionStartSlave5;
		do_drawReactionEndSlave5.programCounter = &&do_drawReactionEndSlave5;
		do_draw_1__thread.nextThread = &do_drawReactionEndSlave5;
		do_drawReactionEndSlave5.prevThread = &do_draw_1__thread;

		// Swap the nested par handler with the linked list.
		do_drawParHandlerSlave5.prevThread -> nextThread = &do_drawReactionStartSlave5;
		do_drawReactionStartSlave5.prevThread = do_drawParHandlerSlave5.prevThread;
		do_drawReactionEndSlave5.nextThread = do_drawParHandlerSlave5.nextThread;
		do_drawParHandlerSlave5.nextThread -> prevThread = &do_drawReactionEndSlave5;
		
		// Set the core information.
		do_drawParCore5.activeThreads = 1;
		do_drawParCore5.reactionCounter = do_drawParReactionCounter;
		
		// Go to the first thread.
		goto do_draw_1__thread;
		asm ("# par2 end");
	} else if (parId == -2) {
		// Iteration
		do_drawParCore5.reactionCounter = do_drawParReactionCounter;
		do_drawParCore5.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore5.reactionCounter == do_drawParReactionCounter);

		// Go to the next thread.
		goto do_drawParHandlerSlave5;
	} else if (parId == -3) {
		// Thread termination
		mainParCore5.activeThreads--;
		do_drawParCore5.activeThreads--;

		do_drawParCore5.reactionCounter = do_drawParReactionCounter;
		do_drawParCore5.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore5.reactionCounter == do_drawParReactionCounter);

		// Delete this par(...) handler.
		do_drawParHandlerSlave5.prevThread -> nextThread = do_drawParHandlerSlave5.nextThread;
		do_drawParHandlerSlave5.nextThread -> prevThread = do_drawParHandlerSlave5.prevThread;
			
		// Go to the next thread.
		goto *do_drawParHandlerSlave5.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		do_drawParCore5.reactionCounter = do_drawParReactionCounter;

		do_drawParHandlerSlave5.programCounter = &&wrongParId_do_drawParHandlerSlave5;
		wrongParId_do_drawParHandlerSlave5:;

		do_drawParCore5.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore5.reactionCounter == do_drawParReactionCounter);
		do_drawParCore5.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (do_drawParParent.parStatus == FOREC_PAR_ON && do_drawParParent.parId == parId) {
			goto *do_drawParHandlerSlave5.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		do_drawParHandlerSlave5.programCounter = &&do_drawParHandlerSlave5;
		
		goto do_drawParHandlerSlave5;
	}
	
	// Control should not reach here.
	goto do_drawParHandlerSlave5;
}
	// forec:scheduler:parHandler:do_draw:slave:5:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:do_draw:slave:5:start
	//-- do_draw:
do_drawReactionStartSlave5: {
	// Go to the next thread.
	goto *do_drawReactionStartSlave5.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:do_draw:slave:5:end
 
	// forec:scheduler:reactionStart:main:slave:5:start
	//-- main:
mainReactionStartSlave5: {
	// Go to the next thread.
	goto *mainReactionStartSlave5.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:5:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:do_draw:slave:5:start
	//-- do_draw:
do_drawReactionEndSlave5: {
	// Determine if the core can still react or not.
	if (do_drawParCore5.activeThreads) {
		do_drawParCore5.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (do_drawParCore5.reactionCounter == do_drawParReactionCounter);
		do_drawParCore5.reactionCounter++;
		
		// Continue reacting.
		goto *do_drawReactionEndSlave5.nextThread -> programCounter;
	} else {
		int parId = do_drawParParent.parId;

		do_drawReactionEndSlave5.programCounter = &&terminated_do_drawReactionEndSlave5;
		terminated_do_drawReactionEndSlave5:;
		
		do_drawParCore5.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (do_drawParCore5.reactionCounter == do_drawParReactionCounter);
		do_drawParCore5.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (do_drawParParent.parStatus == FOREC_PAR_ON && do_drawParParent.parId == parId) {
			goto *do_drawReactionEndSlave5.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		do_drawReactionStartSlave5.prevThread -> nextThread = &do_drawParHandlerSlave5;
		do_drawParHandlerSlave5.prevThread = do_drawReactionStartSlave5.prevThread;
		do_drawParHandlerSlave5.nextThread = do_drawReactionEndSlave5.nextThread;
		do_drawReactionEndSlave5.nextThread -> prevThread = &do_drawParHandlerSlave5;
		goto do_drawParHandlerSlave5;
	}
	
	// Control shouldn't reach here.
	goto do_drawReactionEndSlave5;
}
	// forec:scheduler:reactionEnd:do_draw:slave:5:end
 
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
		int parId = mainParParent.parId;

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
 


	// Abort check handlers ----------------------------------------
	// forec:scheduler:abortHandler:abortStrong0:5:start
	// abortStrong0 (done__global_0_0)
abortStrong0Check5: {
	// Check the abort condition.
	if (done__global_0_0) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore5.activeThreads = 0;
		
		goto mainReactionEndSlave5;
	}
	
	// Continue to the next thread.
	goto *abortStrong0Check5.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrong0:5:end

// forec:scheduler:parHandler:main:slave:6:start
/*--------------------------------------------------------------
| Slave core: core6
*-------------------------------------------------------------*/
mainParCore6: {
	// Check the execution status of the root par(...)s.
	while (mainParParent.parStatus == FOREC_PAR_OFF);

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave6.programCounter = &&mainReactionStartSlave6;
		abortStrong0Check6.programCounter = &&abortStrong0Check6;
		mainReactionStartSlave6.nextThread = &abortStrong0Check6;
		abortStrong0Check6.prevThread = &mainReactionStartSlave6;
		do_drawParHandlerSlave6.programCounter = &&do_drawParHandlerSlave6;
		abortStrong0Check6.nextThread = &do_drawParHandlerSlave6;
		do_drawParHandlerSlave6.prevThread = &abortStrong0Check6;
		mainReactionEndSlave6.programCounter = &&mainReactionEndSlave6;
		do_drawParHandlerSlave6.nextThread = &mainReactionEndSlave6;
		mainReactionEndSlave6.prevThread = &do_drawParHandlerSlave6;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave6.nextThread = &mainReactionStartSlave6;
		mainReactionStartSlave6.prevThread = &mainReactionEndSlave6;

		// Set the core information.
		mainParCore6.activeThreads = 1;
		mainParCore6.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto do_drawParHandlerSlave6;
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
	// forec:scheduler:parHandler:do_draw:slave:6:start
	//-- Thread do_draw par(...) handlers
do_drawParHandlerSlave6: {
	// Synchronise the checking of the nested par(...) via a mutex.
	forec_mutex_read(forec_mutex_value, FSL_FOREC_MUTEX_ID);
	while ((unsigned)(forec_mutex_value & 0x80000000) == (unsigned)0x80000000) {
		forec_mutex_read(forec_mutex_value, FSL_FOREC_MUTEX_ID);
	}

	// Check the execution status of the nested par(...)s.
	if (do_drawParParent.parStatus == FOREC_PAR_OFF) {
		goto *do_drawParHandlerSlave6.nextThread -> programCounter;
	}

	int parId = do_drawParParent.parId;

	// Check the par(...) ID.
	if (parId == 2) {
		asm ("# par2 begin");
		// Link the threads and handlers together.
		do_drawReactionStartSlave6.programCounter = &&do_drawReactionStartSlave6;
		do_draw_2__thread.programCounter = &&do_draw_2__thread;
		do_drawReactionStartSlave6.nextThread = &do_draw_2__thread;
		do_draw_2__thread.prevThread = &do_drawReactionStartSlave6;
		do_drawReactionEndSlave6.programCounter = &&do_drawReactionEndSlave6;
		do_draw_2__thread.nextThread = &do_drawReactionEndSlave6;
		do_drawReactionEndSlave6.prevThread = &do_draw_2__thread;

		// Swap the nested par handler with the linked list.
		do_drawParHandlerSlave6.prevThread -> nextThread = &do_drawReactionStartSlave6;
		do_drawReactionStartSlave6.prevThread = do_drawParHandlerSlave6.prevThread;
		do_drawReactionEndSlave6.nextThread = do_drawParHandlerSlave6.nextThread;
		do_drawParHandlerSlave6.nextThread -> prevThread = &do_drawReactionEndSlave6;
		
		// Set the core information.
		do_drawParCore6.activeThreads = 1;
		do_drawParCore6.reactionCounter = do_drawParReactionCounter;
		
		// Go to the first thread.
		goto do_draw_2__thread;
		asm ("# par2 end");
	} else if (parId == -2) {
		// Iteration
		do_drawParCore6.reactionCounter = do_drawParReactionCounter;
		do_drawParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore6.reactionCounter == do_drawParReactionCounter);

		// Go to the next thread.
		goto do_drawParHandlerSlave6;
	} else if (parId == -3) {
		// Thread termination
		mainParCore6.activeThreads--;
		do_drawParCore6.activeThreads--;

		do_drawParCore6.reactionCounter = do_drawParReactionCounter;
		do_drawParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore6.reactionCounter == do_drawParReactionCounter);

		// Delete this par(...) handler.
		do_drawParHandlerSlave6.prevThread -> nextThread = do_drawParHandlerSlave6.nextThread;
		do_drawParHandlerSlave6.nextThread -> prevThread = do_drawParHandlerSlave6.prevThread;
			
		// Go to the next thread.
		goto *do_drawParHandlerSlave6.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		do_drawParCore6.reactionCounter = do_drawParReactionCounter;

		do_drawParHandlerSlave6.programCounter = &&wrongParId_do_drawParHandlerSlave6;
		wrongParId_do_drawParHandlerSlave6:;

		do_drawParCore6.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore6.reactionCounter == do_drawParReactionCounter);
		do_drawParCore6.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (do_drawParParent.parStatus == FOREC_PAR_ON && do_drawParParent.parId == parId) {
			goto *do_drawParHandlerSlave6.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		do_drawParHandlerSlave6.programCounter = &&do_drawParHandlerSlave6;
		
		goto do_drawParHandlerSlave6;
	}
	
	// Control should not reach here.
	goto do_drawParHandlerSlave6;
}
	// forec:scheduler:parHandler:do_draw:slave:6:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:do_draw:slave:6:start
	//-- do_draw:
do_drawReactionStartSlave6: {
	// Go to the next thread.
	goto *do_drawReactionStartSlave6.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:do_draw:slave:6:end
 
	// forec:scheduler:reactionStart:main:slave:6:start
	//-- main:
mainReactionStartSlave6: {
	// Go to the next thread.
	goto *mainReactionStartSlave6.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:6:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:do_draw:slave:6:start
	//-- do_draw:
do_drawReactionEndSlave6: {
	// Determine if the core can still react or not.
	if (do_drawParCore6.activeThreads) {
		do_drawParCore6.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (do_drawParCore6.reactionCounter == do_drawParReactionCounter);
		do_drawParCore6.reactionCounter++;
		
		// Continue reacting.
		goto *do_drawReactionEndSlave6.nextThread -> programCounter;
	} else {
		int parId = do_drawParParent.parId;

		do_drawReactionEndSlave6.programCounter = &&terminated_do_drawReactionEndSlave6;
		terminated_do_drawReactionEndSlave6:;
		
		do_drawParCore6.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (do_drawParCore6.reactionCounter == do_drawParReactionCounter);
		do_drawParCore6.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (do_drawParParent.parStatus == FOREC_PAR_ON && do_drawParParent.parId == parId) {
			goto *do_drawReactionEndSlave6.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		do_drawReactionStartSlave6.prevThread -> nextThread = &do_drawParHandlerSlave6;
		do_drawParHandlerSlave6.prevThread = do_drawReactionStartSlave6.prevThread;
		do_drawParHandlerSlave6.nextThread = do_drawReactionEndSlave6.nextThread;
		do_drawReactionEndSlave6.nextThread -> prevThread = &do_drawParHandlerSlave6;
		goto do_drawParHandlerSlave6;
	}
	
	// Control shouldn't reach here.
	goto do_drawReactionEndSlave6;
}
	// forec:scheduler:reactionEnd:do_draw:slave:6:end
 
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
		int parId = mainParParent.parId;

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
 


	// Abort check handlers ----------------------------------------
	// forec:scheduler:abortHandler:abortStrong0:6:start
	// abortStrong0 (done__global_0_0)
abortStrong0Check6: {
	// Check the abort condition.
	if (done__global_0_0) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore6.activeThreads = 0;
		
		goto mainReactionEndSlave6;
	}
	
	// Continue to the next thread.
	goto *abortStrong0Check6.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrong0:6:end

// forec:scheduler:parHandler:main:slave:7:start
/*--------------------------------------------------------------
| Slave core: core7
*-------------------------------------------------------------*/
mainParCore7: {
	// Check the execution status of the root par(...)s.
	while (mainParParent.parStatus == FOREC_PAR_OFF);

	int parId = mainParParent.parId;

	// Check the par(...) ID.
	if (parId == 0) {
		asm("# par0 start");
		// Link the threads and handlers together.
		mainReactionStartSlave7.programCounter = &&mainReactionStartSlave7;
		abortStrong0Check7.programCounter = &&abortStrong0Check7;
		mainReactionStartSlave7.nextThread = &abortStrong0Check7;
		abortStrong0Check7.prevThread = &mainReactionStartSlave7;
		do_drawParHandlerSlave7.programCounter = &&do_drawParHandlerSlave7;
		abortStrong0Check7.nextThread = &do_drawParHandlerSlave7;
		do_drawParHandlerSlave7.prevThread = &abortStrong0Check7;
		mainReactionEndSlave7.programCounter = &&mainReactionEndSlave7;
		do_drawParHandlerSlave7.nextThread = &mainReactionEndSlave7;
		mainReactionEndSlave7.prevThread = &do_drawParHandlerSlave7;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave7.nextThread = &mainReactionStartSlave7;
		mainReactionStartSlave7.prevThread = &mainReactionEndSlave7;

		// Set the core information.
		mainParCore7.activeThreads = 1;
		mainParCore7.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto do_drawParHandlerSlave7;
		asm("# par0 end");
	} else {
		// Unscheduled par(...)
		mainParCore7.reactionCounter = mainParReactionCounter;
		
		// Wait for the par(...) to terminate.
		do {
			mainParCore7.status = FOREC_CORE_TERMINATED;
			
			// Wait for the next reaction.
			while (mainParCore7.reactionCounter == mainParReactionCounter);
			mainParCore7.reactionCounter++;
			
		} while (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId);
		
		// Go back to the top and wait for the next nested par(...) 
		goto mainParCore7;
	}
	
	// Control shouldn't reach here.
	goto mainParCore7;
}
// forec:scheduler:parHandler:main:slave:7:end

	// Nested par(...) handlers ------------------------------------
	// forec:scheduler:parHandler:do_draw:slave:7:start
	//-- Thread do_draw par(...) handlers
do_drawParHandlerSlave7: {
	// Synchronise the checking of the nested par(...) via a mutex.
	forec_mutex_read(forec_mutex_value, FSL_FOREC_MUTEX_ID);
	while ((unsigned)(forec_mutex_value & 0x80000000) == (unsigned)0x80000000) {
		forec_mutex_read(forec_mutex_value, FSL_FOREC_MUTEX_ID);
	}

	// Check the execution status of the nested par(...)s.
	if (do_drawParParent.parStatus == FOREC_PAR_OFF) {
		goto *do_drawParHandlerSlave7.nextThread -> programCounter;
	}

	int parId = do_drawParParent.parId;

	// Check the par(...) ID.
	if (parId == 2) {
		asm ("# par2 begin");
		// Link the threads and handlers together.
		do_drawReactionStartSlave7.programCounter = &&do_drawReactionStartSlave7;
		do_draw_3__thread.programCounter = &&do_draw_3__thread;
		do_drawReactionStartSlave7.nextThread = &do_draw_3__thread;
		do_draw_3__thread.prevThread = &do_drawReactionStartSlave7;
		do_drawReactionEndSlave7.programCounter = &&do_drawReactionEndSlave7;
		do_draw_3__thread.nextThread = &do_drawReactionEndSlave7;
		do_drawReactionEndSlave7.prevThread = &do_draw_3__thread;

		// Swap the nested par handler with the linked list.
		do_drawParHandlerSlave7.prevThread -> nextThread = &do_drawReactionStartSlave7;
		do_drawReactionStartSlave7.prevThread = do_drawParHandlerSlave7.prevThread;
		do_drawReactionEndSlave7.nextThread = do_drawParHandlerSlave7.nextThread;
		do_drawParHandlerSlave7.nextThread -> prevThread = &do_drawReactionEndSlave7;
		
		// Set the core information.
		do_drawParCore7.activeThreads = 1;
		do_drawParCore7.reactionCounter = do_drawParReactionCounter;
		
		// Go to the first thread.
		goto do_draw_3__thread;
		asm ("# par2 end");
	} else if (parId == -2) {
		// Iteration
		do_drawParCore7.reactionCounter = do_drawParReactionCounter;
		do_drawParCore7.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore7.reactionCounter == do_drawParReactionCounter);

		// Go to the next thread.
		goto do_drawParHandlerSlave7;
	} else if (parId == -3) {
		// Thread termination
		mainParCore7.activeThreads--;
		do_drawParCore7.activeThreads--;

		do_drawParCore7.reactionCounter = do_drawParReactionCounter;
		do_drawParCore7.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore7.reactionCounter == do_drawParReactionCounter);

		// Delete this par(...) handler.
		do_drawParHandlerSlave7.prevThread -> nextThread = do_drawParHandlerSlave7.nextThread;
		do_drawParHandlerSlave7.nextThread -> prevThread = do_drawParHandlerSlave7.prevThread;
			
		// Go to the next thread.
		goto *do_drawParHandlerSlave7.nextThread -> programCounter;
	} else {
		// Unscheduled par(...)
		do_drawParCore7.reactionCounter = do_drawParReactionCounter;

		do_drawParHandlerSlave7.programCounter = &&wrongParId_do_drawParHandlerSlave7;
		wrongParId_do_drawParHandlerSlave7:;

		do_drawParCore7.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (do_drawParCore7.reactionCounter == do_drawParReactionCounter);
		do_drawParCore7.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (do_drawParParent.parStatus == FOREC_PAR_ON && do_drawParParent.parId == parId) {
			goto *do_drawParHandlerSlave7.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		do_drawParHandlerSlave7.programCounter = &&do_drawParHandlerSlave7;
		
		goto do_drawParHandlerSlave7;
	}
	
	// Control should not reach here.
	goto do_drawParHandlerSlave7;
}
	// forec:scheduler:parHandler:do_draw:slave:7:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:do_draw:slave:7:start
	//-- do_draw:
do_drawReactionStartSlave7: {
	// Go to the next thread.
	goto *do_drawReactionStartSlave7.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:do_draw:slave:7:end
 
	// forec:scheduler:reactionStart:main:slave:7:start
	//-- main:
mainReactionStartSlave7: {
	// Go to the next thread.
	goto *mainReactionStartSlave7.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:slave:7:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:do_draw:slave:7:start
	//-- do_draw:
do_drawReactionEndSlave7: {
	// Determine if the core can still react or not.
	if (do_drawParCore7.activeThreads) {
		do_drawParCore7.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (do_drawParCore7.reactionCounter == do_drawParReactionCounter);
		do_drawParCore7.reactionCounter++;
		
		// Continue reacting.
		goto *do_drawReactionEndSlave7.nextThread -> programCounter;
	} else {
		int parId = do_drawParParent.parId;

		do_drawReactionEndSlave7.programCounter = &&terminated_do_drawReactionEndSlave7;
		terminated_do_drawReactionEndSlave7:;
		
		do_drawParCore7.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (do_drawParCore7.reactionCounter == do_drawParReactionCounter);
		do_drawParCore7.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (do_drawParParent.parStatus == FOREC_PAR_ON && do_drawParParent.parId == parId) {
			goto *do_drawReactionEndSlave7.nextThread -> programCounter;
		}

		// Swap the reaction (start & end) handlers with the nested par handler.
		do_drawReactionStartSlave7.prevThread -> nextThread = &do_drawParHandlerSlave7;
		do_drawParHandlerSlave7.prevThread = do_drawReactionStartSlave7.prevThread;
		do_drawParHandlerSlave7.nextThread = do_drawReactionEndSlave7.nextThread;
		do_drawReactionEndSlave7.nextThread -> prevThread = &do_drawParHandlerSlave7;
		goto do_drawParHandlerSlave7;
	}
	
	// Control shouldn't reach here.
	goto do_drawReactionEndSlave7;
}
	// forec:scheduler:reactionEnd:do_draw:slave:7:end
 
	// forec:scheduler:reactionEnd:main:slave:7:start
	//-- main:
mainReactionEndSlave7: {
	// Determine if the core can still react or not.
	if (mainParCore7.activeThreads) {
		mainParCore7.status = FOREC_CORE_REACTED;
		
		// Wait for the next tick.
		while (mainParCore7.reactionCounter == mainParReactionCounter);
		mainParCore7.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave7.nextThread -> programCounter;
	} else {
		int parId = mainParParent.parId;

		mainReactionEndSlave7.programCounter = &&terminated_mainReactionEndSlave7;
		terminated_mainReactionEndSlave7:;
		
		mainParCore7.status = FOREC_CORE_TERMINATED;
		
		// Wait for the next reaction.
		while (mainParCore7.reactionCounter == mainParReactionCounter);
		mainParCore7.reactionCounter++;
		
		// Wait for the par(...) to terminate.
		if (mainParParent.parStatus == FOREC_PAR_ON && mainParParent.parId == parId) {
			goto *mainReactionEndSlave7.nextThread -> programCounter;
		}

		goto mainParCore7;
	}
	
	// Control shouldn't reach here.
	goto mainReactionEndSlave7;
}
	// forec:scheduler:reactionEnd:main:slave:7:end
 


	// Abort check handlers ----------------------------------------
	// forec:scheduler:abortHandler:abortStrong0:7:start
	// abortStrong0 (done__global_0_0)
abortStrong0Check7: {
	// Check the abort condition.
	if (done__global_0_0) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore7.activeThreads = 0;
		
		goto mainReactionEndSlave7;
	}
	
	// Continue to the next thread.
	goto *abortStrong0Check7.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrong0:7:end



/*==============================================================
| ForeC threads:
| Threads code translated into C code.
*=============================================================*/
	// forec:thread:do_draw:start
	/*--------------------------------------------------------------
	| Thread do_draw
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	do_draw__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		// pause;
		// forec:statement:pause:pause2:start
		do_draw__thread.programCounter = &&pause2;
		goto *do_draw__thread.nextThread -> programCounter;
		pause2:;
		// forec:statement:pause:pause2:end


		// par2(do_draw_0__thread, do_draw_1__thread, do_draw_2__thread, do_draw_3__thread);
		// Set the par(...) information.
		// forec:statement:par:par2:start
		do_drawParParent.parId = 2;
		do_drawParParent.parStatus = FOREC_PAR_ON;
		do_drawParParent.programCounter = &&par2JoinAddress_do_drawParParent;

		// Remove this thread from the linked list.
		do_draw__thread.nextThread -> prevThread = do_draw__thread.prevThread;
		do_draw__thread.prevThread -> nextThread = do_draw__thread.nextThread;
		goto do_drawParHandlerMaster4;
		par2JoinAddress_do_drawParParent:;
		// forec:statement:par:par2:end

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_draw:start
		// Delete par handler
		do_drawParParent.parId = -3;
		do_drawParParent.parStatus = FOREC_PAR_ON;
		do_drawParParent.programCounter = &&do_draw_endAddress;
		goto do_drawParHandlerMaster4;
		do_draw_endAddress:;

		// Delete thread from the linked list and core.
		mainParCore4.activeThreads--;
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
	int blackColor__do_draw_0_0_0;
	int numXGrayscale__do_draw_0_0_0;
	int PIXEL_SIZE__do_draw_0_0_0;
	int ncols__do_draw_0_0_0;
	int RANGE__do_draw_0_0_0;
	int threadNumber__do_draw_0_1_0;
	int y1StartIndex__do_draw_0_1_0;
	int y1EndIndex__do_draw_0_1_0;
	int i__do_draw_0_1_0;
	int x1__do_draw_0_2_0;
	int j__do_draw_0_2_0;
	int index__do_draw_0_3_0;
	int index1__do_draw_0_3_0;
	int y1__do_draw_0_3_0;
	int life__do_draw_0_3_0;

	// Thread body -------------------------------------------------
	do_draw_0__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		numXGrayscale__do_draw_0_0_0 = 10;
		PIXEL_SIZE__do_draw_0_0_0 = 5 - 1;
		ncols__do_draw_0_0_0 = 10;
		RANGE__do_draw_0_0_0 = 3;
		if (!freeze__global_0_0) {
			threadNumber__do_draw_0_1_0 = 0;
			y1StartIndex__do_draw_0_1_0 = 1 + RANGE__do_draw_0_0_0*threadNumber__do_draw_0_1_0;
			y1EndIndex__do_draw_0_1_0 = RANGE__do_draw_0_0_0*(threadNumber__do_draw_0_1_0 + 1);
			for (i__do_draw_0_1_0 = 1; i__do_draw_0_1_0 <= ncols__do_draw_0_0_0; i__do_draw_0_1_0++) {
				x1__do_draw_0_2_0 = (PIXEL_SIZE__do_draw_0_0_0 + 1)*(i__do_draw_0_1_0 - 1);
				for (j__do_draw_0_2_0 = y1StartIndex__do_draw_0_1_0; j__do_draw_0_2_0 <= y1EndIndex__do_draw_0_1_0; j__do_draw_0_2_0++) {
					index__do_draw_0_3_0 = ncols__do_draw_0_0_0*i__do_draw_0_1_0 + j__do_draw_0_2_0;
					index1__do_draw_0_3_0 = ncols__do_draw_0_0_0*(i__do_draw_0_1_0 - 1) + j__do_draw_0_2_0 - 1;
					y1__do_draw_0_3_0 = (PIXEL_SIZE__do_draw_0_0_0 + 1)*(j__do_draw_0_2_0 - 1);
					life_data_color_ptr1__global_0_0[1] = blackColor__do_draw_0_0_0;
					life__do_draw_0_3_0 = grid_ptr2__global_0_0[1];
					life__do_draw_0_3_0 = numXGrayscale__do_draw_0_0_0 - 1;
					life_data_color_ptr1__global_0_0[1] = life__do_draw_0_3_0;
					life_data_color_ptr1__global_0_0[1] = blackColor__do_draw_0_0_0;
					life_data_x1_ptr1__global_0_0[1] = x1__do_draw_0_2_0;
					life_data_y1_ptr1__global_0_0[1] = y1__do_draw_0_3_0;
					asm volatile ("nop");
					// forec:iteration:for1_23:bound:3:3
				}
				asm volatile ("nop");
				// forec:iteration:for1_24:bound:10:10
			}
		} else {
			// if6
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_draw_0:start

		// Delete thread from the linked list and core.
		do_drawParCore4.activeThreads--;
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
	int blackColor__do_draw_1_0_0;
	int numXGrayscale__do_draw_1_0_0;
	int PIXEL_SIZE__do_draw_1_0_0;
	int ncols__do_draw_1_0_0;
	int RANGE__do_draw_1_0_0;
	int threadNumber__do_draw_1_1_0;
	int y1StartIndex__do_draw_1_1_0;
	int y1EndIndex__do_draw_1_1_0;
	int i__do_draw_1_1_0;
	int x1__do_draw_1_2_0;
	int j__do_draw_1_2_0;
	int index__do_draw_1_3_0;
	int index1__do_draw_1_3_0;
	int y1__do_draw_1_3_0;
	int life__do_draw_1_3_0;

	// Thread body -------------------------------------------------
	do_draw_1__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		numXGrayscale__do_draw_1_0_0 = 10;
		PIXEL_SIZE__do_draw_1_0_0 = 5 - 1;
		ncols__do_draw_1_0_0 = 10;
		RANGE__do_draw_1_0_0 = 3;
		if (!freeze__global_0_0) {
			threadNumber__do_draw_1_1_0 = 1;
			y1StartIndex__do_draw_1_1_0 = 1 + RANGE__do_draw_1_0_0*threadNumber__do_draw_1_1_0;
			y1EndIndex__do_draw_1_1_0 = RANGE__do_draw_1_0_0*(threadNumber__do_draw_1_1_0 + 1);
			for (i__do_draw_1_1_0 = 1; i__do_draw_1_1_0 <= ncols__do_draw_1_0_0; i__do_draw_1_1_0++) {
				x1__do_draw_1_2_0 = (PIXEL_SIZE__do_draw_1_0_0 + 1)*(i__do_draw_1_1_0 - 1);
				for (j__do_draw_1_2_0 = y1StartIndex__do_draw_1_1_0; j__do_draw_1_2_0 <= y1EndIndex__do_draw_1_1_0; j__do_draw_1_2_0++) {
					index__do_draw_1_3_0 = ncols__do_draw_1_0_0*i__do_draw_1_1_0 + j__do_draw_1_2_0;
					index1__do_draw_1_3_0 = ncols__do_draw_1_0_0*(i__do_draw_1_1_0 - 1) + j__do_draw_1_2_0 - 1;
					y1__do_draw_1_3_0 = (PIXEL_SIZE__do_draw_1_0_0 + 1)*(j__do_draw_1_2_0 - 1);
					life_data_color_ptr2__global_0_0[1] = blackColor__do_draw_1_0_0;
					life__do_draw_1_3_0 = grid_ptr3__global_0_0[1];
					life__do_draw_1_3_0 = numXGrayscale__do_draw_1_0_0 - 1;
					life_data_color_ptr2__global_0_0[1] = life__do_draw_1_3_0;
					life_data_color_ptr2__global_0_0[1] = blackColor__do_draw_1_0_0;
					life_data_x1_ptr2__global_0_0[1] = x1__do_draw_1_2_0;
					life_data_y1_ptr2__global_0_0[1] = y1__do_draw_1_3_0;
					asm volatile ("nop");
					// forec:iteration:for1_25:bound:3:3
				}
				asm volatile ("nop");
				// forec:iteration:for1_26:bound:10:10
			}
		} else {
			// if7
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_draw_1:start

		// Delete thread from the linked list and core.
		do_drawParCore5.activeThreads--;
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
	int blackColor__do_draw_2_0_0;
	int numXGrayscale__do_draw_2_0_0;
	int PIXEL_SIZE__do_draw_2_0_0;
	int ncols__do_draw_2_0_0;
	int RANGE__do_draw_2_0_0;
	int threadNumber__do_draw_2_1_0;
	int y1StartIndex__do_draw_2_1_0;
	int y1EndIndex__do_draw_2_1_0;
	int i__do_draw_2_1_0;
	int x1__do_draw_2_2_0;
	int j__do_draw_2_2_0;
	int index__do_draw_2_3_0;
	int index1__do_draw_2_3_0;
	int y1__do_draw_2_3_0;
	int life__do_draw_2_3_0;

	// Thread body -------------------------------------------------
	do_draw_2__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		numXGrayscale__do_draw_2_0_0 = 10;
		PIXEL_SIZE__do_draw_2_0_0 = 5 - 1;
		ncols__do_draw_2_0_0 = 10;
		RANGE__do_draw_2_0_0 = 3;
		if (!freeze__global_0_0) {
			threadNumber__do_draw_2_1_0 = 2;
			y1StartIndex__do_draw_2_1_0 = 1 + RANGE__do_draw_2_0_0*threadNumber__do_draw_2_1_0;
			y1EndIndex__do_draw_2_1_0 = RANGE__do_draw_2_0_0*(threadNumber__do_draw_2_1_0 + 1);
			for (i__do_draw_2_1_0 = 1; i__do_draw_2_1_0 <= ncols__do_draw_2_0_0; i__do_draw_2_1_0++) {
				x1__do_draw_2_2_0 = (PIXEL_SIZE__do_draw_2_0_0 + 1)*(i__do_draw_2_1_0 - 1);
				for (j__do_draw_2_2_0 = y1StartIndex__do_draw_2_1_0; j__do_draw_2_2_0 <= y1EndIndex__do_draw_2_1_0; j__do_draw_2_2_0++) {
					index__do_draw_2_3_0 = ncols__do_draw_2_0_0*i__do_draw_2_1_0 + j__do_draw_2_2_0;
					index1__do_draw_2_3_0 = ncols__do_draw_2_0_0*(i__do_draw_2_1_0 - 1) + j__do_draw_2_2_0 - 1;
					y1__do_draw_2_3_0 = (PIXEL_SIZE__do_draw_2_0_0 + 1)*(j__do_draw_2_2_0 - 1);
					life_data_color_ptr3__global_0_0[1] = blackColor__do_draw_2_0_0;
					life__do_draw_2_3_0 = grid_ptr4__global_0_0[1];
					life__do_draw_2_3_0 = numXGrayscale__do_draw_2_0_0 - 1;
					life_data_color_ptr3__global_0_0[1] = life__do_draw_2_3_0;
					life_data_color_ptr3__global_0_0[1] = blackColor__do_draw_2_0_0;
					life_data_x1_ptr3__global_0_0[1] = x1__do_draw_2_2_0;
					life_data_y1_ptr3__global_0_0[1] = y1__do_draw_2_3_0;
					asm volatile ("nop");
					// forec:iteration:for1_27:bound:3:3
				}
				asm volatile ("nop");
				// forec:iteration:for1_28:bound:10:10
			}
		} else {
			// if8
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_draw_2:start

		// Delete thread from the linked list and core.
		do_drawParCore6.activeThreads--;
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
	int blackColor__do_draw_3_0_0;
	int numXGrayscale__do_draw_3_0_0;
	int PIXEL_SIZE__do_draw_3_0_0;
	int ncols__do_draw_3_0_0;
	int RANGE__do_draw_3_0_0;
	int threadNumber__do_draw_3_1_0;
	int y1StartIndex__do_draw_3_1_0;
	int y1EndIndex__do_draw_3_1_0;
	int i__do_draw_3_1_0;
	int x1__do_draw_3_2_0;
	int j__do_draw_3_2_0;
	int index__do_draw_3_3_0;
	int index1__do_draw_3_3_0;
	int y1__do_draw_3_3_0;
	int life__do_draw_3_3_0;

	// Thread body -------------------------------------------------
	do_draw_3__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		numXGrayscale__do_draw_3_0_0 = 10;
		PIXEL_SIZE__do_draw_3_0_0 = 5 - 1;
		ncols__do_draw_3_0_0 = 10;
		RANGE__do_draw_3_0_0 = 3;
		if (!freeze__global_0_0) {
			threadNumber__do_draw_3_1_0 = 3;
			y1StartIndex__do_draw_3_1_0 = 1 + RANGE__do_draw_3_0_0*threadNumber__do_draw_3_1_0;
			y1EndIndex__do_draw_3_1_0 = RANGE__do_draw_3_0_0*(threadNumber__do_draw_3_1_0 + 1);
			for (i__do_draw_3_1_0 = 1; i__do_draw_3_1_0 <= ncols__do_draw_3_0_0; i__do_draw_3_1_0++) {
				x1__do_draw_3_2_0 = (PIXEL_SIZE__do_draw_3_0_0 + 1)*(i__do_draw_3_1_0 - 1);
				for (j__do_draw_3_2_0 = y1StartIndex__do_draw_3_1_0; j__do_draw_3_2_0 <= y1EndIndex__do_draw_3_1_0; j__do_draw_3_2_0++) {
					index__do_draw_3_3_0 = ncols__do_draw_3_0_0*i__do_draw_3_1_0 + j__do_draw_3_2_0;
					index1__do_draw_3_3_0 = ncols__do_draw_3_0_0*(i__do_draw_3_1_0 - 1) + j__do_draw_3_2_0 - 1;
					y1__do_draw_3_3_0 = (PIXEL_SIZE__do_draw_3_0_0 + 1)*(j__do_draw_3_2_0 - 1);
					life_data_color_ptr4__global_0_0[1] = blackColor__do_draw_3_0_0;
					life__do_draw_3_3_0 = grid_ptr5__global_0_0[1];
					life__do_draw_3_3_0 = numXGrayscale__do_draw_3_0_0 - 1;
					life_data_color_ptr4__global_0_0[1] = life__do_draw_3_3_0;
					life_data_color_ptr4__global_0_0[1] = blackColor__do_draw_3_0_0;
					life_data_x1_ptr4__global_0_0[1] = x1__do_draw_3_2_0;
					life_data_y1_ptr4__global_0_0[1] = y1__do_draw_3_3_0;
					asm volatile ("nop");
					// forec:iteration:for1_29:bound:3:3
				}
				asm volatile ("nop");
				// forec:iteration:for1_30:bound:10:10
			}
		} else {
			// if9
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:do_draw_3:start

		// Delete thread from the linked list and core.
		do_drawParCore7.activeThreads--;
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
	int index1__do_step_1_0;
	int datum__do_step_1_0;
	int index2__do_step_1_0;
	int index3__do_step_1_0;
	int index1__do_step_1_1;
	int index2__do_step_1_1;
	int datum__do_step_1_1;
	int index3__do_step_1_1;
	int index4__do_step_1_1;
	int datum__do_step_0_0;
	int index1__do_step_0_0;
	int index2__do_step_0_0;
	int index3__do_step_0_0;
	int index4__do_step_0_0;
	int index5__do_step_0_0;

	// Thread body -------------------------------------------------
	do_step__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		ncols__do_step_0_0 = 10;
		nrows__do_step_0_0 = 3*4;
		for (i__do_step_0_0 = 0; i__do_step_0_0 <= nrows__do_step_0_0 + 1; i__do_step_0_0++) {
			index1__do_step_1_0 = ncols__do_step_0_0 + i__do_step_0_0;
			datum__do_step_1_0 = grid_ptr1__global_0_0[1];
			grid_ptr1__global_0_0[1] = datum__do_step_1_0;
			index2__do_step_1_0 = (ncols__do_step_0_0 + 1)*i__do_step_0_0;
			index3__do_step_1_0 = ncols__do_step_0_0*i__do_step_0_0;
			datum__do_step_1_0 = grid_ptr1__global_0_0[1];
			grid_ptr1__global_0_0[1] = datum__do_step_1_0;
			asm volatile ("nop");
			// forec:iteration:for1_5:bound:13:13
		}
		for (i__do_step_0_0 = 1; i__do_step_0_0 <= ncols__do_step_0_0; i__do_step_0_0++) {
			index1__do_step_1_1 = ncols__do_step_0_0*i__do_step_0_0;
			index2__do_step_1_1 = ncols__do_step_0_0*i__do_step_0_0 + nrows__do_step_0_0;
			datum__do_step_1_1 = grid_ptr1__global_0_0[1];
			grid_ptr1__global_0_0[1] = datum__do_step_1_1;
			index3__do_step_1_1 = ncols__do_step_0_0*i__do_step_0_0 + nrows__do_step_0_0 + 1;
			index4__do_step_1_1 = ncols__do_step_0_0*i__do_step_0_0 + 1;
			datum__do_step_1_1 = grid_ptr1__global_0_0[1];
			grid_ptr1__global_0_0[1] = datum__do_step_1_1;
			asm volatile ("nop");
			// forec:iteration:for1_6:bound:11:11
		}
		datum__do_step_0_0 = grid_ptr1__global_0_0[1];
		grid_ptr1__global_0_0[1] = datum__do_step_0_0;
		index1__do_step_0_0 = nrows__do_step_0_0 + 1;
		datum__do_step_0_0 = grid_ptr1__global_0_0[1];
		grid_ptr1__global_0_0[1] = datum__do_step_0_0;
		index2__do_step_0_0 = ncols__do_step_0_0*(ncols__do_step_0_0 + 1);
		index3__do_step_0_0 = ncols__do_step_0_0*(ncols__do_step_0_0 + 1) + nrows__do_step_0_0;
		datum__do_step_0_0 = grid_ptr1__global_0_0[1];
		grid_ptr1__global_0_0[1] = datum__do_step_0_0;
		index4__do_step_0_0 = ncols__do_step_0_0*(ncols__do_step_0_0 + 1) + nrows__do_step_0_0 + 1;
		index5__do_step_0_0 = ncols__do_step_0_0*(ncols__do_step_0_0 + 1) + 1;
		datum__do_step_0_0 = grid_ptr1__global_0_0[1];
		grid_ptr1__global_0_0[1] = datum__do_step_0_0;

		// pause;
		// forec:statement:pause:pause1:start
		do_step__thread.programCounter = &&pause1;
		goto *do_step__thread.nextThread -> programCounter;
		pause1:;
		// forec:statement:pause:pause1:end


		// par1(do_step_0__thread, do_step_1__thread, do_step_2__thread, do_step_3__thread);
		// Set the par(...) information.
		// forec:statement:par:par1:start
		do_stepParParent.parId = 1;
		do_stepParParent.parStatus = FOREC_PAR_ON;
		do_stepParParent.programCounter = &&par1JoinAddress_do_stepParParent;

		// Remove this thread from the linked list.
		do_step__thread.nextThread -> prevThread = do_step__thread.prevThread;
		do_step__thread.prevThread -> nextThread = do_step__thread.nextThread;
		goto do_stepParHandlerMaster0;
		par1JoinAddress_do_stepParParent:;
		// forec:statement:par:par1:end

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
	int RANGE__do_step_0_0_0;
	int ncols__do_step_0_0_0;
	int threadNumber__do_step_0_1_0;
	int startIndex__do_step_0_1_0;
	int endIndex__do_step_0_1_0;
	int i__do_step_0_1_0;
	int j__do_step_0_2_0;
	int neighbors__do_step_0_3_0;
	int k__do_step_0_3_0;
	int l__do_step_0_4_0;
	int index__do_step_0_3_0;

	// Thread body -------------------------------------------------
	do_step_0__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		RANGE__do_step_0_0_0 = 3;
		ncols__do_step_0_0_0 = 10;
		if (!freeze__global_0_0) {
			threadNumber__do_step_0_1_0 = 0;
			startIndex__do_step_0_1_0 = 1 + RANGE__do_step_0_0_0*threadNumber__do_step_0_1_0;
			endIndex__do_step_0_1_0 = RANGE__do_step_0_0_0*(threadNumber__do_step_0_1_0 + 1);
			for (i__do_step_0_1_0 = 1; i__do_step_0_1_0 <= ncols__do_step_0_0_0; i__do_step_0_1_0++) {
				for (j__do_step_0_2_0 = startIndex__do_step_0_1_0; j__do_step_0_2_0 <= endIndex__do_step_0_1_0; j__do_step_0_2_0++) {
					neighbors__do_step_0_3_0 = 0;
					for (k__do_step_0_3_0 = i__do_step_0_1_0 - 1; k__do_step_0_3_0 <= i__do_step_0_1_0 + 1; k__do_step_0_3_0++) {
						for (l__do_step_0_4_0 = j__do_step_0_2_0 - 1; l__do_step_0_4_0 <= j__do_step_0_2_0 + 1; l__do_step_0_4_0++) {
							neighbors__do_step_0_3_0++;
							asm volatile ("nop");
							// forec:iteration:for1_7:bound:3:3
						}
						asm volatile ("nop");
						// forec:iteration:for1_8:bound:3:3
					}
					index__do_step_0_3_0 = ncols__do_step_0_0_0*i__do_step_0_1_0 + j__do_step_0_2_0;
					next_grid_ptr2__global_0_0[1] = 0;
					asm volatile ("nop");
					// forec:iteration:for1_9:bound:3:3
				}
				asm volatile ("nop");
				// forec:iteration:for1_10:bound:10:10
			}
		} else {
			// if2
		}

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
	int RANGE__do_step_1_0_0;
	int ncols__do_step_1_0_0;
	int threadNumber__do_step_1_1_0;
	int startIndex__do_step_1_1_0;
	int endIndex__do_step_1_1_0;
	int i__do_step_1_1_0;
	int j__do_step_1_2_0;
	int neighbors__do_step_1_3_0;
	int k__do_step_1_3_0;
	int l__do_step_1_4_0;
	int index__do_step_1_3_0;

	// Thread body -------------------------------------------------
	do_step_1__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		RANGE__do_step_1_0_0 = 3;
		ncols__do_step_1_0_0 = 10;
		if (!freeze__global_0_0) {
			threadNumber__do_step_1_1_0 = 1;
			startIndex__do_step_1_1_0 = 1 + RANGE__do_step_1_0_0*threadNumber__do_step_1_1_0;
			endIndex__do_step_1_1_0 = RANGE__do_step_1_0_0*(threadNumber__do_step_1_1_0 + 1);
			for (i__do_step_1_1_0 = 1; i__do_step_1_1_0 <= ncols__do_step_1_0_0; i__do_step_1_1_0++) {
				for (j__do_step_1_2_0 = startIndex__do_step_1_1_0; j__do_step_1_2_0 <= endIndex__do_step_1_1_0; j__do_step_1_2_0++) {
					neighbors__do_step_1_3_0 = 0;
					for (k__do_step_1_3_0 = i__do_step_1_1_0 - 1; k__do_step_1_3_0 <= i__do_step_1_1_0 + 1; k__do_step_1_3_0++) {
						for (l__do_step_1_4_0 = j__do_step_1_2_0 - 1; l__do_step_1_4_0 <= j__do_step_1_2_0 + 1; l__do_step_1_4_0++) {
							neighbors__do_step_1_3_0++;
							asm volatile ("nop");
							// forec:iteration:for1_11:bound:3:3
						}
						asm volatile ("nop");
						// forec:iteration:for1_12:bound:3:3
					}
					index__do_step_1_3_0 = ncols__do_step_1_0_0*i__do_step_1_1_0 + j__do_step_1_2_0;
					next_grid_ptr3__global_0_0[1] = 0;
					asm volatile ("nop");
					// forec:iteration:for1_13:bound:3:3
				}
				asm volatile ("nop");
				// forec:iteration:for1_14:bound:10:10
			}
		} else {
			// if3
		}

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
	int RANGE__do_step_2_0_0;
	int ncols__do_step_2_0_0;
	int threadNumber__do_step_2_1_0;
	int startIndex__do_step_2_1_0;
	int endIndex__do_step_2_1_0;
	int i__do_step_2_1_0;
	int j__do_step_2_2_0;
	int neighbors__do_step_2_3_0;
	int k__do_step_2_3_0;
	int l__do_step_2_4_0;
	int index__do_step_2_3_0;

	// Thread body -------------------------------------------------
	do_step_2__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		RANGE__do_step_2_0_0 = 3;
		ncols__do_step_2_0_0 = 10;
		if (!freeze__global_0_0) {
			threadNumber__do_step_2_1_0 = 2;
			startIndex__do_step_2_1_0 = 1 + RANGE__do_step_2_0_0*threadNumber__do_step_2_1_0;
			endIndex__do_step_2_1_0 = RANGE__do_step_2_0_0*(threadNumber__do_step_2_1_0 + 1);
			for (i__do_step_2_1_0 = 1; i__do_step_2_1_0 <= ncols__do_step_2_0_0; i__do_step_2_1_0++) {
				for (j__do_step_2_2_0 = startIndex__do_step_2_1_0; j__do_step_2_2_0 <= endIndex__do_step_2_1_0; j__do_step_2_2_0++) {
					neighbors__do_step_2_3_0 = 0;
					for (k__do_step_2_3_0 = i__do_step_2_1_0 - 1; k__do_step_2_3_0 <= i__do_step_2_1_0 + 1; k__do_step_2_3_0++) {
						for (l__do_step_2_4_0 = j__do_step_2_2_0 - 1; l__do_step_2_4_0 <= j__do_step_2_2_0 + 1; l__do_step_2_4_0++) {
							neighbors__do_step_2_3_0++;
							asm volatile ("nop");
							// forec:iteration:for1_15:bound:3:3
						}
						asm volatile ("nop");
						// forec:iteration:for1_16:bound:3:3
					}
					index__do_step_2_3_0 = ncols__do_step_2_0_0*i__do_step_2_1_0 + j__do_step_2_2_0;
					next_grid_ptr4__global_0_0[1] = 0;
					asm volatile ("nop");
					// forec:iteration:for1_17:bound:3:3
				}
				asm volatile ("nop");
				// forec:iteration:for1_18:bound:10:10
			}
		} else {
			// if4
		}

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
	int RANGE__do_step_3_0_0;
	int ncols__do_step_3_0_0;
	int threadNumber__do_step_3_1_0;
	int startIndex__do_step_3_1_0;
	int endIndex__do_step_3_1_0;
	int i__do_step_3_1_0;
	int j__do_step_3_2_0;
	int neighbors__do_step_3_3_0;
	int k__do_step_3_3_0;
	int l__do_step_3_4_0;
	int index__do_step_3_3_0;

	// Thread body -------------------------------------------------
	do_step_3__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		RANGE__do_step_3_0_0 = 3;
		ncols__do_step_3_0_0 = 10;
		if (!freeze__global_0_0) {
			threadNumber__do_step_3_1_0 = 3;
			startIndex__do_step_3_1_0 = 1 + RANGE__do_step_3_0_0*threadNumber__do_step_3_1_0;
			endIndex__do_step_3_1_0 = RANGE__do_step_3_0_0*(threadNumber__do_step_3_1_0 + 1);
			for (i__do_step_3_1_0 = 1; i__do_step_3_1_0 <= ncols__do_step_3_0_0; i__do_step_3_1_0++) {
				for (j__do_step_3_2_0 = startIndex__do_step_3_1_0; j__do_step_3_2_0 <= endIndex__do_step_3_1_0; j__do_step_3_2_0++) {
					neighbors__do_step_3_3_0 = 0;
					for (k__do_step_3_3_0 = i__do_step_3_1_0 - 1; k__do_step_3_3_0 <= i__do_step_3_1_0 + 1; k__do_step_3_3_0++) {
						for (l__do_step_3_4_0 = j__do_step_3_2_0 - 1; l__do_step_3_4_0 <= j__do_step_3_2_0 + 1; l__do_step_3_4_0++) {
							neighbors__do_step_3_3_0++;
							asm volatile ("nop");
							// forec:iteration:for1_19:bound:3:3
						}
						asm volatile ("nop");
						// forec:iteration:for1_20:bound:3:3
					}
					index__do_step_3_3_0 = ncols__do_step_3_0_0*i__do_step_3_1_0 + j__do_step_3_2_0;
					next_grid_ptr5__global_0_0[1] = 0;
					asm volatile ("nop");
					// forec:iteration:for1_21:bound:3:3
				}
				asm volatile ("nop");
				// forec:iteration:for1_22:bound:10:10
			}
		} else {
			// if5
		}

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

float rand_float(void) {
	return (float)1/(float)rand_seed__global_0_0;
}

