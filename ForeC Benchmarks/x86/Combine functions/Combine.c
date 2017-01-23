/*==============================================================
| Hardware architecture specific declarations:
| Cores, mutex and input/output information.
*=============================================================*/
#include <pthread.h>

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

// Structure to pass input arguments into forecMain.
typedef struct {
	int coreId;
	int argc;
	char **argv;
} Arguments;


// Shared control variables for par(...)s -------------------------
// Thread main with par(...)s
volatile Parent mainParParent;
volatile Core mainParCore0;
volatile int mainParReactionCounter;


/*==============================================================
| Original global declarations:
| Global declarations in the original program code.
*=============================================================*/
// Original main function
void *forecMain(void *args);

#include <stdio.h>

typedef struct {
	/* shared */ int value;
	int status;
} Shared_x_min__global_0_0;
Shared_x_min__global_0_0 x_min__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED} /* combine with min */;
typedef struct {
	/* shared */ int value;
	int status;
} Shared_x_max__global_0_0;
Shared_x_max__global_0_0 x_max__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED} /* combine with max */;
typedef struct {
	/* shared */ int value;
	int status;
} Shared_x_add__global_0_0;
Shared_x_add__global_0_0 x_add__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED} /* combine with add */;
typedef struct {
	/* shared */ int value;
	int status;
} Shared_x_mul__global_0_0;
Shared_x_mul__global_0_0 x_mul__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED} /* combine with mul */;

int min(int *th1__min_0_0, int *th2__min_0_0) {
	if (* th1__min_0_0 < * th2__min_0_0) {
		return * th1__min_0_0;
	} else {
		// ifElse0
		return * th2__min_0_0;
	}
}

int max(int *th1__max_0_0, int *th2__max_0_0) {
	if (* th1__max_0_0 > * th2__max_0_0) {
		return * th1__max_0_0;
	} else {
		// ifElse1
		return * th2__max_0_0;
	}
}

int add(int *th1__add_0_0, int *th2__add_0_0) {
	return (* th1__add_0_0 + * th2__add_0_0);
}

int mul(int *th1__mul_0_0, int *th2__mul_0_0) {
	return (* th1__mul_0_0** th2__mul_0_0);
}

typedef struct {
	/* shared */ int value;
	int status;
} Shared_x_band__global_0_0;
Shared_x_band__global_0_0 x_band__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED} /* combine with band */;
typedef struct {
	/* shared */ int value;
	int status;
} Shared_x_bor__global_0_0;
Shared_x_bor__global_0_0 x_bor__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED} /* combine with bor */;
typedef struct {
	/* shared */ int value;
	int status;
} Shared_x_land__global_0_0;
Shared_x_land__global_0_0 x_land__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED} /* combine with land */;
typedef struct {
	/* shared */ int value;
	int status;
} Shared_x_lor__global_0_0;
Shared_x_lor__global_0_0 x_lor__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED} /* combine with lor */;

int band(int *th1__band_0_0, int *th2__band_0_0) {
	return (* th1__band_0_0 & * th2__band_0_0);
}

int bor(int *th1__bor_0_0, int *th2__bor_0_0) {
	return (* th1__bor_0_0 | * th2__bor_0_0);
}

int land(int *th1__land_0_0, int *th2__land_0_0) {
	return (* th1__land_0_0 && * th2__land_0_0);
}

int lor(int *th1__lor_0_0, int *th2__lor_0_0) {
	return (* th1__lor_0_0 || * th2__lor_0_0);
}

typedef struct {
	int value;
	int min;
	int max;
} MinMax__global_0_0;

typedef struct {
	/* shared */ MinMax__global_0_0 value;
	int status;
} Shared_x_minmax__global_0_0;
Shared_x_minmax__global_0_0 x_minmax__global_0_0 = {.value = {.value = 0, .min = 0, .max = 0}, .status = FOREC_SHARED_UNMODIFIED} /* combine with minmax */;

MinMax__global_0_0 minmax(MinMax__global_0_0 *th1__minmax_0_0, MinMax__global_0_0 *th2__minmax_0_0) {
	th1__minmax_0_0->min = min(&th1__minmax_0_0->value, &th2__minmax_0_0->value);
	th1__minmax_0_0->max = max(&th1__minmax_0_0->value, &th2__minmax_0_0->value);
	return * th1__minmax_0_0;
}

// thread t1__thread(void);
// thread t2__thread(void);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// main
// t1
Shared_x_min__global_0_0 x_min__global_0_0_copy_t1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_x_max__global_0_0 x_max__global_0_0_copy_t1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_x_add__global_0_0 x_add__global_0_0_copy_t1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_x_mul__global_0_0 x_mul__global_0_0_copy_t1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_x_band__global_0_0 x_band__global_0_0_copy_t1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_x_bor__global_0_0 x_bor__global_0_0_copy_t1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_x_land__global_0_0 x_land__global_0_0_copy_t1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_x_lor__global_0_0 x_lor__global_0_0_copy_t1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_x_minmax__global_0_0 x_minmax__global_0_0_copy_t1 = {.status = FOREC_SHARED_UNMODIFIED};
// t2
Shared_x_min__global_0_0 x_min__global_0_0_copy_t2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_x_max__global_0_0 x_max__global_0_0_copy_t2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_x_add__global_0_0 x_add__global_0_0_copy_t2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_x_mul__global_0_0 x_mul__global_0_0_copy_t2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_x_band__global_0_0 x_band__global_0_0_copy_t2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_x_bor__global_0_0 x_bor__global_0_0_copy_t2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_x_land__global_0_0 x_land__global_0_0_copy_t2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_x_lor__global_0_0 x_lor__global_0_0_copy_t2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_x_minmax__global_0_0 x_minmax__global_0_0_copy_t2 = {.status = FOREC_SHARED_UNMODIFIED};

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
	int argc__main_0_0 = arguments->argc;
	char **argv__main_0_0 = arguments->argv;

	// Variables for par()s ----------------------------------------
	// par0
	Thread t1__thread;
	Thread t2__thread;
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
	// No declarations.
mainParCore0: {
	//--------------------------------------------------------------

	// par0(t1__thread, t2__thread);
	// forec:statement:par:par0:start
	// Set the par(...) information.
	mainParParent.parId = 0;
	mainParParent.parStatus = FOREC_PAR_ON;

	// Link the threads and handlers together.
	mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
	t1__thread.programCounter = &&t1__thread;
	mainReactionStartMaster0.nextThread = &t1__thread;
	t1__thread.prevThread = &mainReactionStartMaster0;
	t2__thread.programCounter = &&t2__thread;
	t1__thread.nextThread = &t2__thread;
	t2__thread.prevThread = &t1__thread;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	t2__thread.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &t2__thread;

	// Link the last and first threads/handlers together.
	mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
	mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

	// Set the join address.
	mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

	// Set the core information.
	mainParCore0.activeThreads = 2;
	mainParCore0.reactionCounter = mainParReactionCounter;

	// Go to the first thread.
	goto t1__thread;
	par0JoinAddress_mainParCore0:;
	// forec:statement:par:par0:end

	printf("min(2,5) = %d\n", x_min__global_0_0.value);
	printf("max(2,5) = %d\n", x_max__global_0_0.value);
	printf("add(2,5) = %d\n", x_add__global_0_0.value);
	printf("mul(2,5) = %d\n", x_mul__global_0_0.value);
	printf("\n");
	printf("band(0x2,0x5) = 0x%x\n", x_band__global_0_0.value);
	printf("bor(0x2,0x5)  = 0x%x\n", x_bor__global_0_0.value);
	printf("land(0x2,0x5) = 0x%x\n", x_land__global_0_0.value);
	printf("lor(0x2,0x5)  = 0x%x\n", x_lor__global_0_0.value);
	printf("\n");
	printf("minmax(2,5) = {%d,%d}\n", x_minmax__global_0_0.value.min, x_minmax__global_0_0.value.max);

	//--------------------------------------------------------------


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

		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;

		// Set slave cores' status to reacting.

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

	// Reset the mutex.

	// Combine shared variables.
	int parId = mainParParent.parId;
	if (parId == 0) {
		int index;
		int numberOfModifiedCopies;

		// x_min__global_0_0
		numberOfModifiedCopies = 0;
		Shared_x_min__global_0_0 *modified_x_min__global_0_0[2];
		// Find the modified copies.
		if (x_min__global_0_0_copy_t1.status == FOREC_SHARED_MODIFIED) {
			x_min__global_0_0_copy_t1.status = FOREC_SHARED_UNMODIFIED;
			modified_x_min__global_0_0[numberOfModifiedCopies] = &x_min__global_0_0_copy_t1;
			++numberOfModifiedCopies;
		}
		if (x_min__global_0_0_copy_t2.status == FOREC_SHARED_MODIFIED) {
			x_min__global_0_0_copy_t2.status = FOREC_SHARED_UNMODIFIED;
			modified_x_min__global_0_0[numberOfModifiedCopies] = &x_min__global_0_0_copy_t2;
			++numberOfModifiedCopies;
		}
		// Assign the first modified copy.
		if (numberOfModifiedCopies > 0) {
			x_min__global_0_0.value = modified_x_min__global_0_0[0]->value;
		}
		// Combine with the remaining modified copies.
		for (index = 1; index < numberOfModifiedCopies; ++index) {
			x_min__global_0_0.value = min(&x_min__global_0_0.value, &modified_x_min__global_0_0[index]->value);
		}

		// x_max__global_0_0
		numberOfModifiedCopies = 0;
		Shared_x_max__global_0_0 *modified_x_max__global_0_0[2];
		// Find the modified copies.
		if (x_max__global_0_0_copy_t1.status == FOREC_SHARED_MODIFIED) {
			x_max__global_0_0_copy_t1.status = FOREC_SHARED_UNMODIFIED;
			modified_x_max__global_0_0[numberOfModifiedCopies] = &x_max__global_0_0_copy_t1;
			++numberOfModifiedCopies;
		}
		if (x_max__global_0_0_copy_t2.status == FOREC_SHARED_MODIFIED) {
			x_max__global_0_0_copy_t2.status = FOREC_SHARED_UNMODIFIED;
			modified_x_max__global_0_0[numberOfModifiedCopies] = &x_max__global_0_0_copy_t2;
			++numberOfModifiedCopies;
		}
		// Assign the first modified copy.
		if (numberOfModifiedCopies > 0) {
			x_max__global_0_0.value = modified_x_max__global_0_0[0]->value;
		}
		// Combine with the remaining modified copies.
		for (index = 1; index < numberOfModifiedCopies; ++index) {
			x_max__global_0_0.value = max(&x_max__global_0_0.value, &modified_x_max__global_0_0[index]->value);
		}

		// x_add__global_0_0
		numberOfModifiedCopies = 0;
		Shared_x_add__global_0_0 *modified_x_add__global_0_0[2];
		// Find the modified copies.
		if (x_add__global_0_0_copy_t1.status == FOREC_SHARED_MODIFIED) {
			x_add__global_0_0_copy_t1.status = FOREC_SHARED_UNMODIFIED;
			modified_x_add__global_0_0[numberOfModifiedCopies] = &x_add__global_0_0_copy_t1;
			++numberOfModifiedCopies;
		}
		if (x_add__global_0_0_copy_t2.status == FOREC_SHARED_MODIFIED) {
			x_add__global_0_0_copy_t2.status = FOREC_SHARED_UNMODIFIED;
			modified_x_add__global_0_0[numberOfModifiedCopies] = &x_add__global_0_0_copy_t2;
			++numberOfModifiedCopies;
		}
		// Assign the first modified copy.
		if (numberOfModifiedCopies > 0) {
			x_add__global_0_0.value = modified_x_add__global_0_0[0]->value;
		}
		// Combine with the remaining modified copies.
		for (index = 1; index < numberOfModifiedCopies; ++index) {
			x_add__global_0_0.value = add(&x_add__global_0_0.value, &modified_x_add__global_0_0[index]->value);
		}

		// x_mul__global_0_0
		numberOfModifiedCopies = 0;
		Shared_x_mul__global_0_0 *modified_x_mul__global_0_0[2];
		// Find the modified copies.
		if (x_mul__global_0_0_copy_t1.status == FOREC_SHARED_MODIFIED) {
			x_mul__global_0_0_copy_t1.status = FOREC_SHARED_UNMODIFIED;
			modified_x_mul__global_0_0[numberOfModifiedCopies] = &x_mul__global_0_0_copy_t1;
			++numberOfModifiedCopies;
		}
		if (x_mul__global_0_0_copy_t2.status == FOREC_SHARED_MODIFIED) {
			x_mul__global_0_0_copy_t2.status = FOREC_SHARED_UNMODIFIED;
			modified_x_mul__global_0_0[numberOfModifiedCopies] = &x_mul__global_0_0_copy_t2;
			++numberOfModifiedCopies;
		}
		// Assign the first modified copy.
		if (numberOfModifiedCopies > 0) {
			x_mul__global_0_0.value = modified_x_mul__global_0_0[0]->value;
		}
		// Combine with the remaining modified copies.
		for (index = 1; index < numberOfModifiedCopies; ++index) {
			x_mul__global_0_0.value = mul(&x_mul__global_0_0.value, &modified_x_mul__global_0_0[index]->value);
		}

		// x_band__global_0_0
		numberOfModifiedCopies = 0;
		Shared_x_band__global_0_0 *modified_x_band__global_0_0[2];
		// Find the modified copies.
		if (x_band__global_0_0_copy_t1.status == FOREC_SHARED_MODIFIED) {
			x_band__global_0_0_copy_t1.status = FOREC_SHARED_UNMODIFIED;
			modified_x_band__global_0_0[numberOfModifiedCopies] = &x_band__global_0_0_copy_t1;
			++numberOfModifiedCopies;
		}
		if (x_band__global_0_0_copy_t2.status == FOREC_SHARED_MODIFIED) {
			x_band__global_0_0_copy_t2.status = FOREC_SHARED_UNMODIFIED;
			modified_x_band__global_0_0[numberOfModifiedCopies] = &x_band__global_0_0_copy_t2;
			++numberOfModifiedCopies;
		}
		// Assign the first modified copy.
		if (numberOfModifiedCopies > 0) {
			x_band__global_0_0.value = modified_x_band__global_0_0[0]->value;
		}
		// Combine with the remaining modified copies.
		for (index = 1; index < numberOfModifiedCopies; ++index) {
			x_band__global_0_0.value = band(&x_band__global_0_0.value, &modified_x_band__global_0_0[index]->value);
		}

		// x_bor__global_0_0
		numberOfModifiedCopies = 0;
		Shared_x_bor__global_0_0 *modified_x_bor__global_0_0[2];
		// Find the modified copies.
		if (x_bor__global_0_0_copy_t1.status == FOREC_SHARED_MODIFIED) {
			x_bor__global_0_0_copy_t1.status = FOREC_SHARED_UNMODIFIED;
			modified_x_bor__global_0_0[numberOfModifiedCopies] = &x_bor__global_0_0_copy_t1;
			++numberOfModifiedCopies;
		}
		if (x_bor__global_0_0_copy_t2.status == FOREC_SHARED_MODIFIED) {
			x_bor__global_0_0_copy_t2.status = FOREC_SHARED_UNMODIFIED;
			modified_x_bor__global_0_0[numberOfModifiedCopies] = &x_bor__global_0_0_copy_t2;
			++numberOfModifiedCopies;
		}
		// Assign the first modified copy.
		if (numberOfModifiedCopies > 0) {
			x_bor__global_0_0.value = modified_x_bor__global_0_0[0]->value;
		}
		// Combine with the remaining modified copies.
		for (index = 1; index < numberOfModifiedCopies; ++index) {
			x_bor__global_0_0.value = bor(&x_bor__global_0_0.value, &modified_x_bor__global_0_0[index]->value);
		}

		// x_land__global_0_0
		numberOfModifiedCopies = 0;
		Shared_x_land__global_0_0 *modified_x_land__global_0_0[2];
		// Find the modified copies.
		if (x_land__global_0_0_copy_t1.status == FOREC_SHARED_MODIFIED) {
			x_land__global_0_0_copy_t1.status = FOREC_SHARED_UNMODIFIED;
			modified_x_land__global_0_0[numberOfModifiedCopies] = &x_land__global_0_0_copy_t1;
			++numberOfModifiedCopies;
		}
		if (x_land__global_0_0_copy_t2.status == FOREC_SHARED_MODIFIED) {
			x_land__global_0_0_copy_t2.status = FOREC_SHARED_UNMODIFIED;
			modified_x_land__global_0_0[numberOfModifiedCopies] = &x_land__global_0_0_copy_t2;
			++numberOfModifiedCopies;
		}
		// Assign the first modified copy.
		if (numberOfModifiedCopies > 0) {
			x_land__global_0_0.value = modified_x_land__global_0_0[0]->value;
		}
		// Combine with the remaining modified copies.
		for (index = 1; index < numberOfModifiedCopies; ++index) {
			x_land__global_0_0.value = land(&x_land__global_0_0.value, &modified_x_land__global_0_0[index]->value);
		}

		// x_lor__global_0_0
		numberOfModifiedCopies = 0;
		Shared_x_lor__global_0_0 *modified_x_lor__global_0_0[2];
		// Find the modified copies.
		if (x_lor__global_0_0_copy_t1.status == FOREC_SHARED_MODIFIED) {
			x_lor__global_0_0_copy_t1.status = FOREC_SHARED_UNMODIFIED;
			modified_x_lor__global_0_0[numberOfModifiedCopies] = &x_lor__global_0_0_copy_t1;
			++numberOfModifiedCopies;
		}
		if (x_lor__global_0_0_copy_t2.status == FOREC_SHARED_MODIFIED) {
			x_lor__global_0_0_copy_t2.status = FOREC_SHARED_UNMODIFIED;
			modified_x_lor__global_0_0[numberOfModifiedCopies] = &x_lor__global_0_0_copy_t2;
			++numberOfModifiedCopies;
		}
		// Assign the first modified copy.
		if (numberOfModifiedCopies > 0) {
			x_lor__global_0_0.value = modified_x_lor__global_0_0[0]->value;
		}
		// Combine with the remaining modified copies.
		for (index = 1; index < numberOfModifiedCopies; ++index) {
			x_lor__global_0_0.value = lor(&x_lor__global_0_0.value, &modified_x_lor__global_0_0[index]->value);
		}

		// x_minmax__global_0_0
		numberOfModifiedCopies = 0;
		Shared_x_minmax__global_0_0 *modified_x_minmax__global_0_0[2];
		// Find the modified copies.
		if (x_minmax__global_0_0_copy_t1.status == FOREC_SHARED_MODIFIED) {
			x_minmax__global_0_0_copy_t1.status = FOREC_SHARED_UNMODIFIED;
			modified_x_minmax__global_0_0[numberOfModifiedCopies] = &x_minmax__global_0_0_copy_t1;
			++numberOfModifiedCopies;
		}
		if (x_minmax__global_0_0_copy_t2.status == FOREC_SHARED_MODIFIED) {
			x_minmax__global_0_0_copy_t2.status = FOREC_SHARED_UNMODIFIED;
			modified_x_minmax__global_0_0[numberOfModifiedCopies] = &x_minmax__global_0_0_copy_t2;
			++numberOfModifiedCopies;
		}
		// Assign the first modified copy.
		if (numberOfModifiedCopies > 0) {
			x_minmax__global_0_0.value = modified_x_minmax__global_0_0[0]->value;
		}
		// Combine with the remaining modified copies.
		for (index = 1; index < numberOfModifiedCopies; ++index) {
			x_minmax__global_0_0.value = minmax(&x_minmax__global_0_0.value, &modified_x_minmax__global_0_0[index]->value);
		}
	} else {
		// Nothing.
	}

	// Return back to the parent thread if all the cores have terminated.
	if (1 && mainParCore0.status == FOREC_CORE_TERMINATED) {
		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;
		
		// Set slave cores' status to reacting

		// Increment the reaction counter for synchronization.
		mainParReactionCounter++;

		goto *mainParParent.programCounter;
	}

	// Set slave cores' status to reacting

	// Increment the reaction counter for synchronization.
	mainParReactionCounter++;

	// Go to the next thread.
	goto *mainReactionEndMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:main:master:0:end
 


	// Abort check handlers ----------------------------------------




/*==============================================================
| ForeC threads:
| Threads' code translated into C code.
*=============================================================*/
	// forec:thread:t1:start
	/*--------------------------------------------------------------
	| Thread t1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_x_min__global_0_0 x_min__global_0_0_copy_t1_local;
	Shared_x_max__global_0_0 x_max__global_0_0_copy_t1_local;
	Shared_x_add__global_0_0 x_add__global_0_0_copy_t1_local;
	Shared_x_mul__global_0_0 x_mul__global_0_0_copy_t1_local;
	Shared_x_band__global_0_0 x_band__global_0_0_copy_t1_local;
	Shared_x_bor__global_0_0 x_bor__global_0_0_copy_t1_local;
	Shared_x_land__global_0_0 x_land__global_0_0_copy_t1_local;
	Shared_x_lor__global_0_0 x_lor__global_0_0_copy_t1_local;
	Shared_x_minmax__global_0_0 x_minmax__global_0_0_copy_t1_local;

	// Thread body -------------------------------------------------
	t1__thread: {
		// Initialise the local copies of shared variables.
		x_min__global_0_0_copy_t1_local.value = x_min__global_0_0.value;
		x_min__global_0_0_copy_t1_local.status = FOREC_SHARED_UNMODIFIED;
		x_max__global_0_0_copy_t1_local.value = x_max__global_0_0.value;
		x_max__global_0_0_copy_t1_local.status = FOREC_SHARED_UNMODIFIED;
		x_add__global_0_0_copy_t1_local.value = x_add__global_0_0.value;
		x_add__global_0_0_copy_t1_local.status = FOREC_SHARED_UNMODIFIED;
		x_mul__global_0_0_copy_t1_local.value = x_mul__global_0_0.value;
		x_mul__global_0_0_copy_t1_local.status = FOREC_SHARED_UNMODIFIED;
		x_band__global_0_0_copy_t1_local.value = x_band__global_0_0.value;
		x_band__global_0_0_copy_t1_local.status = FOREC_SHARED_UNMODIFIED;
		x_bor__global_0_0_copy_t1_local.value = x_bor__global_0_0.value;
		x_bor__global_0_0_copy_t1_local.status = FOREC_SHARED_UNMODIFIED;
		x_land__global_0_0_copy_t1_local.value = x_land__global_0_0.value;
		x_land__global_0_0_copy_t1_local.status = FOREC_SHARED_UNMODIFIED;
		x_lor__global_0_0_copy_t1_local.value = x_lor__global_0_0.value;
		x_lor__global_0_0_copy_t1_local.status = FOREC_SHARED_UNMODIFIED;
		x_minmax__global_0_0_copy_t1_local.value = x_minmax__global_0_0.value;
		x_minmax__global_0_0_copy_t1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		x_min__global_0_0_copy_t1_local.value = x_max__global_0_0_copy_t1_local.value = x_add__global_0_0_copy_t1_local.value = x_mul__global_0_0_copy_t1_local.value = 2;
		x_mul__global_0_0_copy_t1_local.status = FOREC_SHARED_MODIFIED;
		x_add__global_0_0_copy_t1_local.status = FOREC_SHARED_MODIFIED;
		x_max__global_0_0_copy_t1_local.status = FOREC_SHARED_MODIFIED;
		x_min__global_0_0_copy_t1_local.status = FOREC_SHARED_MODIFIED;
		x_band__global_0_0_copy_t1_local.value = x_bor__global_0_0_copy_t1_local.value = x_land__global_0_0_copy_t1_local.value = x_lor__global_0_0_copy_t1_local.value = 0x2;
		x_lor__global_0_0_copy_t1_local.status = FOREC_SHARED_MODIFIED;
		x_land__global_0_0_copy_t1_local.status = FOREC_SHARED_MODIFIED;
		x_bor__global_0_0_copy_t1_local.status = FOREC_SHARED_MODIFIED;
		x_band__global_0_0_copy_t1_local.status = FOREC_SHARED_MODIFIED;
		x_minmax__global_0_0_copy_t1_local.value.value = 2;
		x_minmax__global_0_0_copy_t1_local.status = FOREC_SHARED_MODIFIED;

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		x_min__global_0_0_copy_t1 = x_min__global_0_0_copy_t1_local;
		x_max__global_0_0_copy_t1 = x_max__global_0_0_copy_t1_local;
		x_add__global_0_0_copy_t1 = x_add__global_0_0_copy_t1_local;
		x_mul__global_0_0_copy_t1 = x_mul__global_0_0_copy_t1_local;
		x_band__global_0_0_copy_t1 = x_band__global_0_0_copy_t1_local;
		x_bor__global_0_0_copy_t1 = x_bor__global_0_0_copy_t1_local;
		x_land__global_0_0_copy_t1 = x_land__global_0_0_copy_t1_local;
		x_lor__global_0_0_copy_t1 = x_lor__global_0_0_copy_t1_local;
		x_minmax__global_0_0_copy_t1 = x_minmax__global_0_0_copy_t1_local;

		// forec:scheduler:threadRemove:t1:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
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
	Shared_x_min__global_0_0 x_min__global_0_0_copy_t2_local;
	Shared_x_max__global_0_0 x_max__global_0_0_copy_t2_local;
	Shared_x_add__global_0_0 x_add__global_0_0_copy_t2_local;
	Shared_x_mul__global_0_0 x_mul__global_0_0_copy_t2_local;
	Shared_x_band__global_0_0 x_band__global_0_0_copy_t2_local;
	Shared_x_bor__global_0_0 x_bor__global_0_0_copy_t2_local;
	Shared_x_land__global_0_0 x_land__global_0_0_copy_t2_local;
	Shared_x_lor__global_0_0 x_lor__global_0_0_copy_t2_local;
	Shared_x_minmax__global_0_0 x_minmax__global_0_0_copy_t2_local;

	// Thread body -------------------------------------------------
	t2__thread: {
		// Initialise the local copies of shared variables.
		x_min__global_0_0_copy_t2_local.value = x_min__global_0_0.value;
		x_min__global_0_0_copy_t2_local.status = FOREC_SHARED_UNMODIFIED;
		x_max__global_0_0_copy_t2_local.value = x_max__global_0_0.value;
		x_max__global_0_0_copy_t2_local.status = FOREC_SHARED_UNMODIFIED;
		x_add__global_0_0_copy_t2_local.value = x_add__global_0_0.value;
		x_add__global_0_0_copy_t2_local.status = FOREC_SHARED_UNMODIFIED;
		x_mul__global_0_0_copy_t2_local.value = x_mul__global_0_0.value;
		x_mul__global_0_0_copy_t2_local.status = FOREC_SHARED_UNMODIFIED;
		x_band__global_0_0_copy_t2_local.value = x_band__global_0_0.value;
		x_band__global_0_0_copy_t2_local.status = FOREC_SHARED_UNMODIFIED;
		x_bor__global_0_0_copy_t2_local.value = x_bor__global_0_0.value;
		x_bor__global_0_0_copy_t2_local.status = FOREC_SHARED_UNMODIFIED;
		x_land__global_0_0_copy_t2_local.value = x_land__global_0_0.value;
		x_land__global_0_0_copy_t2_local.status = FOREC_SHARED_UNMODIFIED;
		x_lor__global_0_0_copy_t2_local.value = x_lor__global_0_0.value;
		x_lor__global_0_0_copy_t2_local.status = FOREC_SHARED_UNMODIFIED;
		x_minmax__global_0_0_copy_t2_local.value = x_minmax__global_0_0.value;
		x_minmax__global_0_0_copy_t2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		x_min__global_0_0_copy_t2_local.value = x_max__global_0_0_copy_t2_local.value = x_add__global_0_0_copy_t2_local.value = x_mul__global_0_0_copy_t2_local.value = 5;
		x_mul__global_0_0_copy_t2_local.status = FOREC_SHARED_MODIFIED;
		x_add__global_0_0_copy_t2_local.status = FOREC_SHARED_MODIFIED;
		x_max__global_0_0_copy_t2_local.status = FOREC_SHARED_MODIFIED;
		x_min__global_0_0_copy_t2_local.status = FOREC_SHARED_MODIFIED;
		x_band__global_0_0_copy_t2_local.value = x_bor__global_0_0_copy_t2_local.value = x_land__global_0_0_copy_t2_local.value = x_lor__global_0_0_copy_t2_local.value = 0x5;
		x_lor__global_0_0_copy_t2_local.status = FOREC_SHARED_MODIFIED;
		x_land__global_0_0_copy_t2_local.status = FOREC_SHARED_MODIFIED;
		x_bor__global_0_0_copy_t2_local.status = FOREC_SHARED_MODIFIED;
		x_band__global_0_0_copy_t2_local.status = FOREC_SHARED_MODIFIED;
		x_minmax__global_0_0_copy_t2_local.value.value = 5;
		x_minmax__global_0_0_copy_t2_local.status = FOREC_SHARED_MODIFIED;

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		x_min__global_0_0_copy_t2 = x_min__global_0_0_copy_t2_local;
		x_max__global_0_0_copy_t2 = x_max__global_0_0_copy_t2_local;
		x_add__global_0_0_copy_t2 = x_add__global_0_0_copy_t2_local;
		x_mul__global_0_0_copy_t2 = x_mul__global_0_0_copy_t2_local;
		x_band__global_0_0_copy_t2 = x_band__global_0_0_copy_t2_local;
		x_bor__global_0_0_copy_t2 = x_bor__global_0_0_copy_t2_local;
		x_land__global_0_0_copy_t2 = x_land__global_0_0_copy_t2_local;
		x_lor__global_0_0_copy_t2 = x_lor__global_0_0_copy_t2_local;
		x_minmax__global_0_0_copy_t2 = x_minmax__global_0_0_copy_t2_local;

		// forec:scheduler:threadRemove:t2:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		t2__thread.nextThread -> prevThread = t2__thread.prevThread;
		t2__thread.prevThread -> nextThread = t2__thread.nextThread;
		goto *t2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:t2:end
	} // t2__thread
	// forec:thread:t2:end


} // End of the main() function.

