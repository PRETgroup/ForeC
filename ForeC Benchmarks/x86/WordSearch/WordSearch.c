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

// Shared control variables for non-immediate aborts -----------

// Shared control variables for par(...)s ----------------------
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

#include <sys/time.h>
#include <stdio.h>
#include <string.h>

typedef int FILE__global_0_0;

#define FILE__global_0_0 FILE

int NULL__global_0_0;

#define NULL__global_0_0 NULL

/* input */ char newWord__global_0_0[20] = "";

char oldWord__global_0_0[20] = "";

typedef struct {
	/* shared */ char (*value)[20];
	int status;
} Shared_oldWord_ptr__global_0_0;
Shared_oldWord_ptr__global_0_0 oldWord_ptr__global_0_0 = {.value = &oldWord__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_file1__global_0_0;
Shared_file1__global_0_0 file1__global_0_0;
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_file2__global_0_0;
Shared_file2__global_0_0 file2__global_0_0;

typedef struct {
	int last;
	int current;
} Accum__global_0_0;

typedef struct {
	/* shared */ Accum__global_0_0 value;
	int status;
} Shared_found__global_0_0;
Shared_found__global_0_0 found__global_0_0 = {.value = {.last = 0, .current = 0}, .status = FOREC_SHARED_UNMODIFIED} /* combine with plus */;

int fgetw(FILE__global_0_0 *file, char wordFound[20]);
int fgetws(FILE__global_0_0 *file, char word[20], int *wordsLeft);
const Accum__global_0_0 plus(Accum__global_0_0 *lhs, const Accum__global_0_0 *rhs);

// thread mimicInput__thread(void);
// thread search1__thread(void);
// thread search2__thread(void);

int tickCount__global_0_0 = 0;
static const int MAX_WORDS_TO_SEARCH__global_0_0 = 100;

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// main
// mimicInput
// search1
Shared_oldWord_ptr__global_0_0 oldWord_ptr__global_0_0_copy_search1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_file1__global_0_0 file1__global_0_0_copy_search1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_found__global_0_0 found__global_0_0_copy_search1 = {.status = FOREC_SHARED_UNMODIFIED};
// search2
Shared_oldWord_ptr__global_0_0 oldWord_ptr__global_0_0_copy_search2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_file2__global_0_0 file2__global_0_0_copy_search2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_found__global_0_0 found__global_0_0_copy_search2 = {.status = FOREC_SHARED_UNMODIFIED};

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
	Thread mimicInput__thread;
	Thread search1__thread;
	Thread search2__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionEndMaster0;
	Thread abortStrongImmediate0Check0;


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
	int i__main_1_3;
	int preemptionOccured__main_1_3;
	long seconds__main_0_0;
	int microseconds__main_0_0;

mainParCore0: {
	//--------------------------------------------------------------

	gettimeofday(&startTime__main_0_0, 0);
	printf("Case-sensitive word search across two text files.\n");
	if (argc__main_0_0 != 4) {
		printf("Usage: ./WordSearch <word> <file1> <file2>\n");
		return 0;
	} else {
		// if0
	}
	strcpy(newWord__global_0_0, argv__main_0_0[1]);
	file1__global_0_0.value = fopen(argv__main_0_0[2], "r");
	if (file1__global_0_0.value == NULL__global_0_0) {
		printf("Could not open \"%s\".\n", argv__main_0_0[2]);
	} else {
		// if1
	}
	file2__global_0_0.value = fopen(argv__main_0_0[3], "r");
	if (file2__global_0_0.value == NULL__global_0_0) {
		printf("Could not open \"%s\".\n", argv__main_0_0[3]);
	} else {
		// if2
	}

	for (i__main_1_3 = 0; i__main_1_3 < 4; i__main_1_3++) {
		found__global_0_0.value.current = 0;
		found__global_0_0.value.last = 0;
		strcpy(oldWord__global_0_0, newWord__global_0_0);
		preemptionOccured__main_1_3 = 1;

		/* abortStrongImmediate0 */ {
			// forec:statement:abort:abortStrongImmediate0:start
			if (strcmp(oldWord__global_0_0, newWord__global_0_0) != 0 && strcmp("", newWord__global_0_0) != 0) {
				goto abortEnd_abortStrongImmediate0;
			}
			// forec:statement:abort:abortStrongImmediate0:end

			// par0(mimicInput__thread, search1__thread, search2__thread);
			// forec:statement:par:par0:start
			// Set the par(...) information.
			mainParParent.parId = 0;
			mainParParent.parStatus = FOREC_PAR_ON;

			// Link the threads and handlers together.
			mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
			abortStrongImmediate0Check0.programCounter = &&abortStrongImmediate0Check0;
			mainReactionStartMaster0.nextThread = &abortStrongImmediate0Check0;
			abortStrongImmediate0Check0.prevThread = &mainReactionStartMaster0;
			mimicInput__thread.programCounter = &&mimicInput__thread;
			abortStrongImmediate0Check0.nextThread = &mimicInput__thread;
			mimicInput__thread.prevThread = &abortStrongImmediate0Check0;
			search1__thread.programCounter = &&search1__thread;
			mimicInput__thread.nextThread = &search1__thread;
			search1__thread.prevThread = &mimicInput__thread;
			search2__thread.programCounter = &&search2__thread;
			search1__thread.nextThread = &search2__thread;
			search2__thread.prevThread = &search1__thread;
			mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
			search2__thread.nextThread = &mainReactionEndMaster0;
			mainReactionEndMaster0.prevThread = &search2__thread;

			// Link the last and first threads/handlers together.
			mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
			mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

			// Set the join address.
			mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

			// Set the core information.
			mainParCore0.activeThreads = 3;
			mainParCore0.reactionCounter = mainParReactionCounter;

			// Go to the first thread.
			goto mimicInput__thread;
			par0JoinAddress_mainParCore0:;
			// forec:statement:par:par0:end

			printf("\"%s\" appears %d times in %s and %s.\n", * oldWord_ptr__global_0_0.value, found__global_0_0.value.current, argv__main_0_0[2], argv__main_0_0[3]);
			preemptionOccured__main_1_3 = 0;
			abortEnd_abortStrongImmediate0:;
		} // when (strcmp(oldWord__global_0_0, newWord__global_0_0) != 0 && strcmp("", newWord__global_0_0) != 0);
		// forec:statement:abort:abortStrongImmediate0:scope:end

		if (preemptionOccured__main_1_3) {
			printf("\"%s\" appeared %d times in %s and %s before being preempted.\n", * oldWord_ptr__global_0_0.value, found__global_0_0.value.current, argv__main_0_0[2], argv__main_0_0[3]);
		} else {
			// if3
		}

		// forec:scheduler:iterationEnd:for3_0:start
		// Synchronise end of iteration
		mainParParent.parId = -2;
		mainParParent.parStatus = FOREC_PAR_ON;
		mainParParent.programCounter = &&for3_0_endAddress;
		goto mainParHandlerMaster0;
		for3_0_endAddress:;
		// forec:scheduler:iterationEnd:for3_0:end
	}

	fclose(file1__global_0_0.value);
	fclose(file2__global_0_0.value);
	printf("Number of times \"%s\" appears in %s and %s is %d.\n", * oldWord_ptr__global_0_0.value, argv__main_0_0[2], argv__main_0_0[3], found__global_0_0.value.current);
	gettimeofday(&endTime__main_0_0, 0);
	seconds__main_0_0 = endTime__main_0_0.tv_sec - startTime__main_0_0.tv_sec;
	microseconds__main_0_0 = endTime__main_0_0.tv_usec - startTime__main_0_0.tv_usec;
	if (microseconds__main_0_0 < 0) {
		microseconds__main_0_0 += 1000000;
		seconds__main_0_0--;
	} else {
		// if4
	}
	printf("Runtime: %ld.%.6d\r\n", seconds__main_0_0, microseconds__main_0_0);
	return 0;

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

		// found__global_0_0
		numberOfModifiedCopies = 0;
		Shared_found__global_0_0 *modified_found__global_0_0[2];
		// Find the modified copies.
		if (found__global_0_0_copy_search1.status == FOREC_SHARED_MODIFIED) {
			found__global_0_0_copy_search1.status = FOREC_SHARED_UNMODIFIED;
			modified_found__global_0_0[numberOfModifiedCopies] = &found__global_0_0_copy_search1;
			++numberOfModifiedCopies;
		}
		if (found__global_0_0_copy_search2.status == FOREC_SHARED_MODIFIED) {
			found__global_0_0_copy_search2.status = FOREC_SHARED_UNMODIFIED;
			modified_found__global_0_0[numberOfModifiedCopies] = &found__global_0_0_copy_search2;
			++numberOfModifiedCopies;
		}
		// Assign the first modified copy.
		if (numberOfModifiedCopies > 0) {
			found__global_0_0.value = modified_found__global_0_0[0]->value;
		}
		// Combine with the remaining modified copies.
		for (index = 1; index < numberOfModifiedCopies; ++index) {
			found__global_0_0.value = plus(&found__global_0_0.value, &modified_found__global_0_0[index]->value);
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
	// forec:scheduler:abortHandler:abortStrongImmediate0:0:start
	// abortStrongImmediate0 (strcmp(oldWord__global_0_0, newWord__global_0_0) != 0 && strcmp("", newWord__global_0_0) != 0)
abortStrongImmediate0Check0: {
	// Check the abort condition.
	if (strcmp(oldWord__global_0_0, newWord__global_0_0) != 0 && strcmp("", newWord__global_0_0) != 0) {
		// Force the reaction end handler to terminate the par(...).
		mainParCore0.activeThreads = 0;

		// Update the parent thread to resume at the end of the abort scope.
		mainParParent.programCounter = &&abortEnd_abortStrongImmediate0;
		
		goto mainReactionEndMaster0;
	}
	
	// Continue to the next thread.
	goto *abortStrongImmediate0Check0.nextThread -> programCounter;
}
	// forec:scheduler:abortHandler:abortStrongImmediate0:0:end




/*==============================================================
| ForeC threads:
| Threads' code translated into C code.
*=============================================================*/
	// forec:thread:mimicInput:start
	/*--------------------------------------------------------------
	| Thread mimicInput
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	// No declarations.

	// Thread body -------------------------------------------------
	mimicInput__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		switch (tickCount__global_0_0) {
				
			case 0:
				strcpy(newWord__global_0_0, "");

				// pause;
				// forec:statement:pause:pause0:start
				mimicInput__thread.programCounter = &&pause0;
				goto *mimicInput__thread.nextThread -> programCounter;
				pause0:;
				// forec:statement:pause:pause0:end


				
			case 1:
				strcpy(newWord__global_0_0, "");

				// pause;
				// forec:statement:pause:pause1:start
				mimicInput__thread.programCounter = &&pause1;
				goto *mimicInput__thread.nextThread -> programCounter;
				pause1:;
				// forec:statement:pause:pause1:end


				
			case 2:
				strcpy(newWord__global_0_0, "if");

				// pause;
				// forec:statement:pause:pause2:start
				mimicInput__thread.programCounter = &&pause2;
				goto *mimicInput__thread.nextThread -> programCounter;
				pause2:;
				// forec:statement:pause:pause2:end


				
			default:
				break;
		}

		tickCount__global_0_0 = tickCount__global_0_0 + 1;

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:mimicInput:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		mimicInput__thread.nextThread -> prevThread = mimicInput__thread.prevThread;
		mimicInput__thread.prevThread -> nextThread = mimicInput__thread.nextThread;
		goto *mimicInput__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:mimicInput:end
	} // mimicInput__thread
	// forec:thread:mimicInput:end

	// forec:thread:search1:start
	/*--------------------------------------------------------------
	| Thread search1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_oldWord_ptr__global_0_0 oldWord_ptr__global_0_0_copy_search1_local;
	Shared_file1__global_0_0 file1__global_0_0_copy_search1_local;
	Shared_found__global_0_0 found__global_0_0_copy_search1_local;
	int numSearched__search1_0_0;

	// Thread body -------------------------------------------------
	search1__thread: {
		// Initialise the local copies of shared variables.
		oldWord_ptr__global_0_0_copy_search1_local.value = oldWord_ptr__global_0_0.value;
		oldWord_ptr__global_0_0_copy_search1_local.status = FOREC_SHARED_UNMODIFIED;
		file1__global_0_0_copy_search1_local.value = file1__global_0_0.value;
		file1__global_0_0_copy_search1_local.status = FOREC_SHARED_UNMODIFIED;
		found__global_0_0_copy_search1_local.value = found__global_0_0.value;
		found__global_0_0_copy_search1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		numSearched__search1_0_0 = 0;
		rewind(file1__global_0_0_copy_search1_local.value);

		do {
			numSearched__search1_0_0 = 0;
			found__global_0_0_copy_search1_local.value.current = found__global_0_0_copy_search1_local.value.current + fgetws(file1__global_0_0_copy_search1_local.value, * oldWord_ptr__global_0_0_copy_search1_local.value, &numSearched__search1_0_0);
			found__global_0_0_copy_search1_local.status = FOREC_SHARED_MODIFIED;

			// pause;
			// Write the local copy of shared variables back to their global copy.
			found__global_0_0_copy_search1 = found__global_0_0_copy_search1_local;
			// forec:statement:pause:pause3:start
			search1__thread.programCounter = &&pause3;
			goto *search1__thread.nextThread -> programCounter;
			pause3:;
			// forec:statement:pause:pause3:end
			// Update the values of the used shared variables from their global copy.
			oldWord_ptr__global_0_0_copy_search1_local = oldWord_ptr__global_0_0;
			file1__global_0_0_copy_search1_local = file1__global_0_0;
			found__global_0_0_copy_search1_local = found__global_0_0;

		} while (numSearched__search1_0_0 != 0);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		found__global_0_0_copy_search1 = found__global_0_0_copy_search1_local;

		// forec:scheduler:threadRemove:search1:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		search1__thread.nextThread -> prevThread = search1__thread.prevThread;
		search1__thread.prevThread -> nextThread = search1__thread.nextThread;
		goto *search1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:search1:end
	} // search1__thread
	// forec:thread:search1:end

	// forec:thread:search2:start
	/*--------------------------------------------------------------
	| Thread search2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_oldWord_ptr__global_0_0 oldWord_ptr__global_0_0_copy_search2_local;
	Shared_file2__global_0_0 file2__global_0_0_copy_search2_local;
	Shared_found__global_0_0 found__global_0_0_copy_search2_local;
	int numSearched__search2_0_0;

	// Thread body -------------------------------------------------
	search2__thread: {
		// Initialise the local copies of shared variables.
		oldWord_ptr__global_0_0_copy_search2_local.value = oldWord_ptr__global_0_0.value;
		oldWord_ptr__global_0_0_copy_search2_local.status = FOREC_SHARED_UNMODIFIED;
		file2__global_0_0_copy_search2_local.value = file2__global_0_0.value;
		file2__global_0_0_copy_search2_local.status = FOREC_SHARED_UNMODIFIED;
		found__global_0_0_copy_search2_local.value = found__global_0_0.value;
		found__global_0_0_copy_search2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		numSearched__search2_0_0 = 0;
		rewind(file2__global_0_0_copy_search2_local.value);

		do {
			numSearched__search2_0_0 = 0;
			found__global_0_0_copy_search2_local.value.current = found__global_0_0_copy_search2_local.value.current + fgetws(file2__global_0_0_copy_search2_local.value, * oldWord_ptr__global_0_0_copy_search2_local.value, &numSearched__search2_0_0);
			found__global_0_0_copy_search2_local.status = FOREC_SHARED_MODIFIED;

			// pause;
			// Write the local copy of shared variables back to their global copy.
			found__global_0_0_copy_search2 = found__global_0_0_copy_search2_local;
			// forec:statement:pause:pause4:start
			search2__thread.programCounter = &&pause4;
			goto *search2__thread.nextThread -> programCounter;
			pause4:;
			// forec:statement:pause:pause4:end
			// Update the values of the used shared variables from their global copy.
			oldWord_ptr__global_0_0_copy_search2_local = oldWord_ptr__global_0_0;
			file2__global_0_0_copy_search2_local = file2__global_0_0;
			found__global_0_0_copy_search2_local = found__global_0_0;

		} while (numSearched__search2_0_0 != 0);

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		found__global_0_0_copy_search2 = found__global_0_0_copy_search2_local;

		// forec:scheduler:threadRemove:search2:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		search2__thread.nextThread -> prevThread = search2__thread.prevThread;
		search2__thread.prevThread -> nextThread = search2__thread.nextThread;
		goto *search2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:search2:end
	} // search2__thread
	// forec:thread:search2:end


} // End of the main() function.

int fgetws(FILE__global_0_0 *file__fgetws_0_0, char word__fgetws_0_0[20], int *numSearched__fgetws_0_0) {
	int found__fgetws_0_0 = 0;
	char wordFound__fgetws_0_0[20];
	while ((fgetw(file__fgetws_0_0, wordFound__fgetws_0_0) != 0) && (* numSearched__fgetws_0_0 < MAX_WORDS_TO_SEARCH__global_0_0)) {
		if (strcmp(word__fgetws_0_0, wordFound__fgetws_0_0) == 0) {
			found__fgetws_0_0 = found__fgetws_0_0 + 1;
		} else {
			// if6
		}
		* numSearched__fgetws_0_0 = * numSearched__fgetws_0_0 + 1;
	}
	return found__fgetws_0_0;
}

int fgetw(FILE__global_0_0 *file__fgetw_0_0, char wordFound__fgetw_0_0[20]) {
	int length__fgetw_0_0 = 0;
	char c__fgetw_0_0 = fgetc(file__fgetw_0_0);
	while ((0x40 < c__fgetw_0_0 && c__fgetw_0_0 < 0x5B) || (0x60 < c__fgetw_0_0 && c__fgetw_0_0 < 0x7B)) {
		if (length__fgetw_0_0 < 20) {
			wordFound__fgetw_0_0[length__fgetw_0_0] = c__fgetw_0_0;
			length__fgetw_0_0 = length__fgetw_0_0 + 1;
		} else {
			// if7
		}
		c__fgetw_0_0 = fgetc(file__fgetw_0_0);
	}
	wordFound__fgetw_0_0[length__fgetw_0_0] = '\0';
	while ((-1 < c__fgetw_0_0 && c__fgetw_0_0 < 0x41) || (0x5A < c__fgetw_0_0 && c__fgetw_0_0 < 0x61) || 0x7A < c__fgetw_0_0) {
		c__fgetw_0_0 = fgetc(file__fgetw_0_0);
	}
	ungetc(c__fgetw_0_0, file__fgetw_0_0);
	return length__fgetw_0_0;
}

const Accum__global_0_0 plus(Accum__global_0_0 *lhs__plus_0_0, const Accum__global_0_0 *rhs__plus_0_0) {
	lhs__plus_0_0->current = lhs__plus_0_0->current + rhs__plus_0_0->current - rhs__plus_0_0->last;
	lhs__plus_0_0->last = lhs__plus_0_0->current;
	return * lhs__plus_0_0;
}

