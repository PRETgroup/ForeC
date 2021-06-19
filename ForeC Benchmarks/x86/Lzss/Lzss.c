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
Core mainParCore1 = { .statusCond = PTHREAD_COND_INITIALIZER, .statusLock = PTHREAD_MUTEX_INITIALIZER, .reactionCounterCond = PTHREAD_COND_INITIALIZER, .reactionCounterLock = PTHREAD_MUTEX_INITIALIZER};
Core mainParCore2 = { .statusCond = PTHREAD_COND_INITIALIZER, .statusLock = PTHREAD_MUTEX_INITIALIZER, .reactionCounterCond = PTHREAD_COND_INITIALIZER, .reactionCounterLock = PTHREAD_MUTEX_INITIALIZER};
Core mainParCore3 = { .statusCond = PTHREAD_COND_INITIALIZER, .statusLock = PTHREAD_MUTEX_INITIALIZER, .reactionCounterCond = PTHREAD_COND_INITIALIZER, .reactionCounterLock = PTHREAD_MUTEX_INITIALIZER};
volatile int mainParReactionCounter;
pthread_cond_t mainParReactionCounterCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mainParReactionCounterLock = PTHREAD_MUTEX_INITIALIZER;


/*==============================================================
| Original global declarations:
| Global declarations in the original program code.
*=============================================================*/
// Original main function
void *forecMain(void *args);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

typedef struct _Fifo__global_0_0 {
	char *data;
	unsigned size;
	unsigned written_size;
	int begin;
	int end;
} Fifo__global_0_0;

void Fifo_init(Fifo__global_0_0 *, unsigned);
void Fifo_destroy(Fifo__global_0_0 *);
int Fifo_push_front(Fifo__global_0_0 *, char);
int Fifo_push_back(Fifo__global_0_0 *, char);
char Fifo_pop_front(Fifo__global_0_0 *);
char Fifo_pop_back(Fifo__global_0_0 *);
char Fifo_at(const Fifo__global_0_0, unsigned);
void Fifo_print(const Fifo__global_0_0);

int NUM_THREADS__global_0_0 = 4;
int WINLENGTH__global_0_0 = 131072;
int LKLENGTH__global_0_0 = 32;
int offset__global_0_0;
int matches__global_0_0 = 0;
int offset_thread__global_0_0[4];

typedef struct {
	/* shared */ int *value;
	int status;
} Shared_offset_thread_ptr__global_0_0;
Shared_offset_thread_ptr__global_0_0 offset_thread_ptr__global_0_0 = {.value = offset_thread__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

int matches_thread__global_0_0[4];

typedef struct {
	/* shared */ int *value;
	int status;
} Shared_matches_thread_ptr__global_0_0;
Shared_matches_thread_ptr__global_0_0 matches_thread_ptr__global_0_0 = {.value = matches_thread__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

typedef int FILE__global_0_0;

#define FILE__global_0_0 FILE

struct fileStats__global_0_0 {
	FILE__global_0_0 *p_file;
	char filenameArray[512];
	char *filename;
	int filesize;
	int totalSize;
	int isDir;
} fileInfo__global_0_0, archiveInfo__global_0_0;

void *null__global_0_0 = (void *)0;

#undef EOF

int EOF__global_0_0 = -1;
FILE__global_0_0 *stderr__global_0_0;

#define stderr__global_0_0 stderr

FILE__global_0_0 ** stderr_ptr_0__global_0_0 = &stderr__global_0_0;
FILE__global_0_0 ** stderr_ptr_1__global_0_0 = &stderr__global_0_0;
FILE__global_0_0 ** stderr_ptr_2__global_0_0 = &stderr__global_0_0;
FILE__global_0_0 ** stderr_ptr_3__global_0_0 = &stderr__global_0_0;
FILE__global_0_0 *stdout__global_0_0;

#define stdout__global_0_0 stdout

FILE__global_0_0 ** stdout_ptr_0__global_0_0 = &stdout__global_0_0;
FILE__global_0_0 ** stdout_ptr_1__global_0_0 = &stdout__global_0_0;
FILE__global_0_0 ** stdout_ptr_2__global_0_0 = &stdout__global_0_0;

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

void printhelp(void);
void createDescriptor(struct fileStats__global_0_0 *, struct fileStats__global_0_0 *);
void storeFileInfo(struct fileStats__global_0_0 *, struct fileStats__global_0_0 *);
void longestMatch(const Fifo__global_0_0, const Fifo__global_0_0, int, int **, int **);
void writeToArchive(const Fifo__global_0_0, int *, int *, struct fileStats__global_0_0 *, int *, int *);
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
	programStatus = RUNNING;

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
	pthread_attr_setdetachstate(&slaveCoreAttribute, PTHREAD_CREATE_JOINABLE);
		
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
	pthread_cond_broadcast(&mainParParent.parStatusCond);
	pthread_join(cores[1], NULL);
	pthread_cond_broadcast(&mainParParent.parStatusCond);
	pthread_join(cores[2], NULL);
	pthread_cond_broadcast(&mainParParent.parStatusCond);
	pthread_join(cores[3], NULL);

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
	int count__main_2_0;
	int count__main_5_0;
	int i__main_5_0;
	long seconds__main_0_0;
	int microseconds__main_0_0;

mainParCore0: {
	// forec:scheduler:counter:start
	// Initialise and start timing each reaction.
	clockTimeUs.previous = getClockTimeUs();
	// forec:scheduler:counter:end
	
	//--------------------------------------------------------------

	gettimeofday(&startTime__main_0_0, 0);

	if (argc__main_0_0 > 1 && !strcmp(argv__main_0_0[1], "-h")) {
		printhelp();
		exit(0);
	} else {
		// ifElse6
		if (argc__main_0_0 > 3 && !strcmp(argv__main_0_0[1], "-c")) {
			archiveInfo__global_0_0.filename = argv__main_0_0[2];
			fileInfo__global_0_0.totalSize = 0;
			if ((archiveInfo__global_0_0.p_file = fopen(archiveInfo__global_0_0.filename, "w")) == null__global_0_0) {
				fprintf(* stderr_ptr_0__global_0_0, "Error writing to file '%s'.", archiveInfo__global_0_0.filename);
				exit(1);
			} else {
				// if0
			}

			for (count__main_2_0 = 3; count__main_2_0 < argc__main_0_0; count__main_2_0++) {
				fileInfo__global_0_0.filename = argv__main_0_0[count__main_2_0];
				obtainFileInfo(&fileInfo__global_0_0);

				if ((fileInfo__global_0_0.p_file = fopen(fileInfo__global_0_0.filename, "r")) == null__global_0_0) {
					fprintf(* stderr_ptr_0__global_0_0, "Error opening file '%s', ignored.\n", fileInfo__global_0_0.filename);
				} else {
					// ifElse3
					if (fileInfo__global_0_0.isDir) {
						fprintf(* stderr_ptr_0__global_0_0, "'%s' is a directory, ignored.\n", fileInfo__global_0_0.filename);
					} else {
						// ifElse2
						printf("Compressing '%s'....", fileInfo__global_0_0.filename);
						fflush(* stdout_ptr_0__global_0_0);
						createDescriptor(&fileInfo__global_0_0, &archiveInfo__global_0_0);
						Fifo_init(&window__global_0_0.value, WINLENGTH__global_0_0);
						Fifo_push_back(&window__global_0_0.value, fgetc(fileInfo__global_0_0.p_file));
						writeToArchive(window__global_0_0.value, &offset__global_0_0, &matches__global_0_0, &archiveInfo__global_0_0, offset_thread__global_0_0, matches_thread__global_0_0);
						Fifo_init(&lookAhead__global_0_0.value, LKLENGTH__global_0_0);
						Fifo_push_back(&lookAhead__global_0_0.value, fgetc(fileInfo__global_0_0.p_file));
						while (lookAhead__global_0_0.value.written_size < LKLENGTH__global_0_0) {
							Fifo_push_back(&lookAhead__global_0_0.value, fgetc(fileInfo__global_0_0.p_file));
						}

						while (!feof(fileInfo__global_0_0.p_file)) {
							// par0(longestMatch0__thread, longestMatch1__thread, longestMatch2__thread, longestMatch3__thread);
							// forec:statement:par:par0:start
							// Set the par(...) information.
							mainParParent.parId = 0;
							pthread_mutex_lock(&mainParParent.parStatusLock);
							mainParParent.parStatus = FOREC_PAR_ON;
							pthread_cond_broadcast(&mainParParent.parStatusCond);
							pthread_mutex_unlock(&mainParParent.parStatusLock);

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

							writeToArchive(lookAhead__global_0_0.value, &offset__global_0_0, &matches__global_0_0, &archiveInfo__global_0_0, offset_thread__global_0_0, matches_thread__global_0_0);
							count__main_5_0 = 1;
							do {
								if (window__global_0_0.value.written_size >= WINLENGTH__global_0_0) {
									Fifo_pop_front(&window__global_0_0.value);
								} else {
									// if1
								}
								Fifo_push_back(&window__global_0_0.value, Fifo_pop_front(&lookAhead__global_0_0.value));
								Fifo_push_back(&lookAhead__global_0_0.value, fgetc(fileInfo__global_0_0.p_file));
							} while (count__main_5_0++ < matches__global_0_0);

							// forec:scheduler:iterationEnd:while_2:start
							// Synchronise end of iteration
							mainParParent.parId = -2;
							pthread_mutex_lock(&mainParParent.parStatusLock);
							mainParParent.parStatus = FOREC_PAR_ON;
							pthread_cond_broadcast(&mainParParent.parStatusCond);
							pthread_mutex_unlock(&mainParParent.parStatusLock);
							mainParParent.programCounter = &&while_2_endAddress;
							goto mainParHandlerMaster0;
							while_2_endAddress:;
							// forec:scheduler:iterationEnd:while_2:end
						}

						for (i__main_5_0 = 0; i__main_5_0 < NUM_THREADS__global_0_0; i__main_5_0++) {
							matches_thread__global_0_0[i__main_5_0] = 0;
						}
						for (count__main_5_0 = 0; count__main_5_0 < LKLENGTH__global_0_0 - 1 && Fifo_at(lookAhead__global_0_0.value, 0) != EOF__global_0_0; count__main_5_0++) {
							writeToArchive(lookAhead__global_0_0.value, &offset__global_0_0, &matches__global_0_0, &archiveInfo__global_0_0, offset_thread__global_0_0, matches_thread__global_0_0);
							Fifo_pop_front(&lookAhead__global_0_0.value);
						}
						fclose(fileInfo__global_0_0.p_file);
						printf(" Done\n");
					}
				}
			}

			fclose(archiveInfo__global_0_0.p_file);
			printResult(&fileInfo__global_0_0, &archiveInfo__global_0_0);
		} else {
			// ifElse5
			if (argc__main_0_0 > 2 && !strcmp(argv__main_0_0[1], "-d")) {
				unpackArchive(argv__main_0_0[2], &offset__global_0_0, &matches__global_0_0, &fileInfo__global_0_0, &archiveInfo__global_0_0);
			} else {
				// ifElse4
				printhelp();
				exit(1);
			}
		}
	}

	gettimeofday(&endTime__main_0_0, 0);
	seconds__main_0_0 = endTime__main_0_0.tv_sec - startTime__main_0_0.tv_sec;
	microseconds__main_0_0 = endTime__main_0_0.tv_usec - startTime__main_0_0.tv_usec;
	if (microseconds__main_0_0 < 0) {
		microseconds__main_0_0 += 1000000;
		seconds__main_0_0--;
	} else {
		// if7
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
		pthread_mutex_lock(&mainParCore1.statusLock);
		while(mainParCore1.status == FOREC_CORE_REACTING) { pthread_cond_wait(&mainParCore1.statusCond, &mainParCore1.statusLock); }
		pthread_mutex_unlock(&mainParCore1.statusLock);
		pthread_mutex_lock(&mainParCore2.statusLock);
		while(mainParCore2.status == FOREC_CORE_REACTING) { pthread_cond_wait(&mainParCore2.statusCond, &mainParCore2.statusLock); }
		pthread_mutex_unlock(&mainParCore2.statusLock);
		pthread_mutex_lock(&mainParCore3.statusLock);
		while(mainParCore3.status == FOREC_CORE_REACTING) { pthread_cond_wait(&mainParCore3.statusCond, &mainParCore3.statusLock); }
		pthread_mutex_unlock(&mainParCore3.statusLock);

		pthread_mutex_lock(&mainParParent.parStatusLock);
		mainParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&mainParParent.parStatusCond);
		pthread_mutex_unlock(&mainParParent.parStatusLock);
		mainParParent.parId = -1;

		// Set slave cores' status to reacting.
		mainParCore1.status = FOREC_CORE_REACTING;
		mainParCore2.status = FOREC_CORE_REACTING;
		mainParCore3.status = FOREC_CORE_REACTING;

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
	pthread_mutex_lock(&mainParCore0.statusLock);
	if (mainParCore0.activeThreads) {
		mainParCore0.status = FOREC_CORE_REACTED;
	} else {
		mainParCore0.status = FOREC_CORE_TERMINATED;
	}
	pthread_cond_signal(&mainParCore0.statusCond);
	pthread_mutex_unlock(&mainParCore0.statusLock);
	
	// Wait for other cores to complete their reaction.
	pthread_mutex_lock(&mainParCore1.statusLock);
	while(mainParCore1.status == FOREC_CORE_REACTING) { pthread_cond_wait(&mainParCore1.statusCond, &mainParCore1.statusLock); }
	pthread_mutex_unlock(&mainParCore1.statusLock);
	pthread_mutex_lock(&mainParCore2.statusLock);
	while(mainParCore2.status == FOREC_CORE_REACTING) { pthread_cond_wait(&mainParCore2.statusCond, &mainParCore2.statusLock); }
	pthread_mutex_unlock(&mainParCore2.statusLock);
	pthread_mutex_lock(&mainParCore3.statusLock);
	while(mainParCore3.status == FOREC_CORE_REACTING) { pthread_cond_wait(&mainParCore3.statusCond, &mainParCore3.statusLock); }
	pthread_mutex_unlock(&mainParCore3.statusLock);

	// Reset the mutex.

	// Return back to the parent thread if all the cores have terminated.
	if (1 && mainParCore0.status == FOREC_CORE_TERMINATED && mainParCore1.status == FOREC_CORE_TERMINATED && mainParCore2.status == FOREC_CORE_TERMINATED && mainParCore3.status == FOREC_CORE_TERMINATED) {
		pthread_mutex_lock(&mainParParent.parStatusLock);
		mainParParent.parStatus = FOREC_PAR_OFF;
		pthread_cond_broadcast(&mainParParent.parStatusCond);
		pthread_mutex_unlock(&mainParParent.parStatusLock);
		mainParParent.parId = -1;
		
		// Set slave cores' status to reacting
		mainParCore1.status = FOREC_CORE_REACTING;
		mainParCore2.status = FOREC_CORE_REACTING;
		mainParCore3.status = FOREC_CORE_REACTING;

		// Increment the reaction counter for synchronization.
		pthread_mutex_lock(&mainParReactionCounterLock);
		mainParReactionCounter++;
		pthread_cond_broadcast(&mainParReactionCounterCond);
		pthread_mutex_unlock(&mainParReactionCounterLock);

		goto *mainParParent.programCounter;
	}

	// Set slave cores' status to reacting
	mainParCore1.status = FOREC_CORE_REACTING;
	mainParCore2.status = FOREC_CORE_REACTING;
	mainParCore3.status = FOREC_CORE_REACTING;

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


// forec:scheduler:parHandler:main:slave:1:start
/*--------------------------------------------------------------
| Slave core: core1
*-------------------------------------------------------------*/
mainParCore1: {
	// Check the execution status of the root par(...)s.
	pthread_mutex_lock(&mainParParent.parStatusLock);
	while (mainParParent.parStatus == FOREC_PAR_OFF) {
		if (programStatus == TERMINATED) {
			pthread_mutex_unlock(&mainParParent.parStatusLock);
			pthread_exit(NULL);
		}
		pthread_cond_wait(&mainParParent.parStatusCond, &mainParParent.parStatusLock);
	}
	pthread_mutex_unlock(&mainParParent.parStatusLock);

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
			pthread_mutex_lock(&mainParCore1.statusLock);
			mainParCore1.status = FOREC_CORE_TERMINATED;
			pthread_cond_signal(&mainParCore1.statusCond);
			pthread_mutex_unlock(&mainParCore1.statusLock);
			
			// Wait for the next tick.
			pthread_mutex_lock(&mainParReactionCounterLock);
			while (mainParCore1.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
			pthread_mutex_unlock(&mainParReactionCounterLock);
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
		pthread_mutex_lock(&mainParCore1.statusLock);
		mainParCore1.status = FOREC_CORE_REACTED;
		pthread_cond_signal(&mainParCore1.statusCond);
		pthread_mutex_unlock(&mainParCore1.statusLock);
		
		// Wait for the next tick.
		pthread_mutex_lock(&mainParReactionCounterLock);
		while (mainParCore1.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
		pthread_mutex_unlock(&mainParReactionCounterLock);
		mainParCore1.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave1.nextThread -> programCounter;
	} else {
		int parId = mainParParent.parId;

		mainReactionEndSlave1.programCounter = &&terminated_mainReactionEndSlave1;
		terminated_mainReactionEndSlave1:;
		
		pthread_mutex_lock(&mainParCore1.statusLock);
		mainParCore1.status = FOREC_CORE_TERMINATED;
		pthread_cond_signal(&mainParCore1.statusCond);
		pthread_mutex_unlock(&mainParCore1.statusLock);
		
		// Wait for the next tick.
		pthread_mutex_lock(&mainParReactionCounterLock);
		while (mainParCore1.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
		pthread_mutex_unlock(&mainParReactionCounterLock);
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
	pthread_mutex_lock(&mainParParent.parStatusLock);
	while (mainParParent.parStatus == FOREC_PAR_OFF) {
		if (programStatus == TERMINATED) {
			pthread_mutex_unlock(&mainParParent.parStatusLock);
			pthread_exit(NULL);
		}
		pthread_cond_wait(&mainParParent.parStatusCond, &mainParParent.parStatusLock);
	}
	pthread_mutex_unlock(&mainParParent.parStatusLock);

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
			pthread_mutex_lock(&mainParCore2.statusLock);
			mainParCore2.status = FOREC_CORE_TERMINATED;
			pthread_cond_signal(&mainParCore2.statusCond);
			pthread_mutex_unlock(&mainParCore2.statusLock);
			
			// Wait for the next tick.
			pthread_mutex_lock(&mainParReactionCounterLock);
			while (mainParCore2.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
			pthread_mutex_unlock(&mainParReactionCounterLock);
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
		pthread_mutex_lock(&mainParCore2.statusLock);
		mainParCore2.status = FOREC_CORE_REACTED;
		pthread_cond_signal(&mainParCore2.statusCond);
		pthread_mutex_unlock(&mainParCore2.statusLock);
		
		// Wait for the next tick.
		pthread_mutex_lock(&mainParReactionCounterLock);
		while (mainParCore2.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
		pthread_mutex_unlock(&mainParReactionCounterLock);
		mainParCore2.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave2.nextThread -> programCounter;
	} else {
		int parId = mainParParent.parId;

		mainReactionEndSlave2.programCounter = &&terminated_mainReactionEndSlave2;
		terminated_mainReactionEndSlave2:;
		
		pthread_mutex_lock(&mainParCore2.statusLock);
		mainParCore2.status = FOREC_CORE_TERMINATED;
		pthread_cond_signal(&mainParCore2.statusCond);
		pthread_mutex_unlock(&mainParCore2.statusLock);
		
		// Wait for the next tick.
		pthread_mutex_lock(&mainParReactionCounterLock);
		while (mainParCore2.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
		pthread_mutex_unlock(&mainParReactionCounterLock);
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
	pthread_mutex_lock(&mainParParent.parStatusLock);
	while (mainParParent.parStatus == FOREC_PAR_OFF) {
		if (programStatus == TERMINATED) {
			pthread_mutex_unlock(&mainParParent.parStatusLock);
			pthread_exit(NULL);
		}
		pthread_cond_wait(&mainParParent.parStatusCond, &mainParParent.parStatusLock);
	}
	pthread_mutex_unlock(&mainParParent.parStatusLock);

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
			pthread_mutex_lock(&mainParCore3.statusLock);
			mainParCore3.status = FOREC_CORE_TERMINATED;
			pthread_cond_signal(&mainParCore3.statusCond);
			pthread_mutex_unlock(&mainParCore3.statusLock);
			
			// Wait for the next tick.
			pthread_mutex_lock(&mainParReactionCounterLock);
			while (mainParCore3.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
			pthread_mutex_unlock(&mainParReactionCounterLock);
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
		pthread_mutex_lock(&mainParCore3.statusLock);
		mainParCore3.status = FOREC_CORE_REACTED;
		pthread_cond_signal(&mainParCore3.statusCond);
		pthread_mutex_unlock(&mainParCore3.statusLock);
		
		// Wait for the next tick.
		pthread_mutex_lock(&mainParReactionCounterLock);
		while (mainParCore3.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
		pthread_mutex_unlock(&mainParReactionCounterLock);
		mainParCore3.reactionCounter++;
		
		// Continue reacting.
		goto *mainReactionEndSlave3.nextThread -> programCounter;
	} else {
		int parId = mainParParent.parId;

		mainReactionEndSlave3.programCounter = &&terminated_mainReactionEndSlave3;
		terminated_mainReactionEndSlave3:;
		
		pthread_mutex_lock(&mainParCore3.statusLock);
		mainParCore3.status = FOREC_CORE_TERMINATED;
		pthread_cond_signal(&mainParCore3.statusCond);
		pthread_mutex_unlock(&mainParCore3.statusLock);
		
		// Wait for the next tick.
		pthread_mutex_lock(&mainParReactionCounterLock);
		while (mainParCore3.reactionCounter == mainParReactionCounter) { pthread_cond_wait(&mainParReactionCounterCond, &mainParReactionCounterLock); }
		pthread_mutex_unlock(&mainParReactionCounterLock);
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

void printhelp(void) {
	printf("lzss is a text file archiver.\n\nUsage:\n    lzss [OPTION] [FILE]...\n\nExamples:\n   lzss -c archive.lzs file1 file2  # Create archive.lzs from files file1 and file2\n   lzss -d archive.lzs              # Extract all files from archive.lzs\n\nOptions:\n   -c <filename>   compress files\n   -d <file>       extract file\n   -h              print this help\n\n");
}

void createDescriptor(struct fileStats__global_0_0 *fileInfo__createDescriptor_0_0, struct fileStats__global_0_0 *archiveInfo__createDescriptor_0_0) {
	storeFileInfo(fileInfo__createDescriptor_0_0, archiveInfo__createDescriptor_0_0);
}

void obtainFileInfo(struct fileStats__global_0_0 *fileInfo__obtainFileInfo_0_0) {
	struct stat filestats__obtainFileInfo_0_0;
	stat(fileInfo__obtainFileInfo_0_0->filename, &filestats__obtainFileInfo_0_0);
	fileInfo__obtainFileInfo_0_0->filesize = (int)filestats__obtainFileInfo_0_0.st_size;
	fileInfo__obtainFileInfo_0_0->isDir = S_ISDIR(filestats__obtainFileInfo_0_0.st_mode);
	if (!fileInfo__obtainFileInfo_0_0->isDir) {
		fileInfo__obtainFileInfo_0_0->totalSize += fileInfo__obtainFileInfo_0_0->filesize;
	} else {
		// if8
	}
}

void storeFileInfo(struct fileStats__global_0_0 *fileInfo__storeFileInfo_0_0, struct fileStats__global_0_0 *archiveInfo__storeFileInfo_0_0) {
	fwrite(fileInfo__storeFileInfo_0_0->filename, 1, strlen(fileInfo__storeFileInfo_0_0->filename) + 1, archiveInfo__storeFileInfo_0_0->p_file);
	fwrite(&(fileInfo__storeFileInfo_0_0->filesize), 4, 1, archiveInfo__storeFileInfo_0_0->p_file);
}

void longestMatch(const Fifo__global_0_0 win__longestMatch_0_0, const Fifo__global_0_0 lk__longestMatch_0_0, int begin__longestMatch_0_0, int ** offset_thread__longestMatch_0_0, int ** matches_thread__longestMatch_0_0) {
	int NUM_THREADS__longestMatch_0_0 = 4;
	int LKLENGTH__longestMatch_0_0 = 32;
	int _matches__longestMatch_0_0 = 0;
	(* matches_thread__longestMatch_0_0)[begin__longestMatch_0_0] = 0;
	int i__longestMatch_0_0, j__longestMatch_0_0, k__longestMatch_0_0, _offset__longestMatch_0_0;
	for (i__longestMatch_0_0 = begin__longestMatch_0_0; i__longestMatch_0_0 < win__longestMatch_0_0.written_size && Fifo_at(win__longestMatch_0_0, i__longestMatch_0_0);) {
		j__longestMatch_0_0 = 0;
		_offset__longestMatch_0_0 = i__longestMatch_0_0;
		for (k__longestMatch_0_0 = i__longestMatch_0_0; j__longestMatch_0_0 < LKLENGTH__longestMatch_0_0 && Fifo_at(win__longestMatch_0_0, k__longestMatch_0_0) == Fifo_at(lk__longestMatch_0_0, j__longestMatch_0_0);) {
			_matches__longestMatch_0_0++;
			j__longestMatch_0_0++;
			k__longestMatch_0_0++;
			if (k__longestMatch_0_0 == win__longestMatch_0_0.written_size) {
				k__longestMatch_0_0 = 0;
			} else {
				// if9
			}
		}
		if (_matches__longestMatch_0_0 > (* matches_thread__longestMatch_0_0)[begin__longestMatch_0_0]) {
			(* matches_thread__longestMatch_0_0)[begin__longestMatch_0_0] = _matches__longestMatch_0_0;
			(* offset_thread__longestMatch_0_0)[begin__longestMatch_0_0] = _offset__longestMatch_0_0;
		} else {
			// if10
		}
		i__longestMatch_0_0 += NUM_THREADS__longestMatch_0_0;
		_matches__longestMatch_0_0 = 0;
	}
}

void writeToArchive(const Fifo__global_0_0 fifo__writeToArchive_0_0, int *offset__writeToArchive_0_0, int *matches__writeToArchive_0_0, struct fileStats__global_0_0 *archiveInfo__writeToArchive_0_0, int *offset_thread__writeToArchive_0_0, int *matches_thread__writeToArchive_0_0) {
	int NUM_THREADS__writeToArchive_0_0 = 4;
	int EOF__writeToArchive_0_0 = -1;
	* matches__writeToArchive_0_0 = 0;
	int i__writeToArchive_0_0;
	for (i__writeToArchive_0_0 = 0; i__writeToArchive_0_0 < NUM_THREADS__writeToArchive_0_0; i__writeToArchive_0_0++) {
		if (matches_thread__writeToArchive_0_0[i__writeToArchive_0_0] > * matches__writeToArchive_0_0) {
			* matches__writeToArchive_0_0 = matches_thread__writeToArchive_0_0[i__writeToArchive_0_0];
			* offset__writeToArchive_0_0 = offset_thread__writeToArchive_0_0[i__writeToArchive_0_0];
		} else {
			// if11
		}
	}
	int encode__writeToArchive_0_0 = 0x800000;
	encode__writeToArchive_0_0 += (* offset__writeToArchive_0_0 << 6) + (* matches__writeToArchive_0_0 - 1);
	if (* matches__writeToArchive_0_0 > 2) {
		fputc(encode__writeToArchive_0_0 >> 16, archiveInfo__writeToArchive_0_0->p_file);
		fputc(encode__writeToArchive_0_0 >> 8, archiveInfo__writeToArchive_0_0->p_file);
		fputc(encode__writeToArchive_0_0, archiveInfo__writeToArchive_0_0->p_file);
	} else {
		// ifElse14
		if (Fifo_at(fifo__writeToArchive_0_0, 0) != EOF__writeToArchive_0_0) {
			fputc(Fifo_at(fifo__writeToArchive_0_0, 0), archiveInfo__writeToArchive_0_0->p_file);
			if (* matches__writeToArchive_0_0 == 2 && Fifo_at(fifo__writeToArchive_0_0, 1) != EOF__writeToArchive_0_0) {
				fputc(Fifo_at(fifo__writeToArchive_0_0, 1), archiveInfo__writeToArchive_0_0->p_file);
			} else {
				// if12
			}
		} else {
			// if13
		}
	}
}

void printResult(struct fileStats__global_0_0 *fileInfo__printResult_0_0, struct fileStats__global_0_0 *archiveInfo__printResult_0_0) {
	obtainFileInfo(archiveInfo__printResult_0_0);
	printf("\nFiles compressed successfully.\nRatio %.3f:1  Saved %d%%\n", (float)fileInfo__printResult_0_0->totalSize/archiveInfo__printResult_0_0->filesize, (int)(100.0*(1.0 - (float)archiveInfo__printResult_0_0->filesize/fileInfo__printResult_0_0->totalSize) + 0.5));
	fflush(* stdout_ptr_1__global_0_0);
}

void unpackArchive(char *filename__unpackArchive_0_0, int *offset__unpackArchive_0_0, int *matches__unpackArchive_0_0, struct fileStats__global_0_0 *fileInfo__unpackArchive_0_0, struct fileStats__global_0_0 *archiveInfo__unpackArchive_0_0) {
	void *null__unpackArchive_0_0 = (void *)0;
	int countFiles__unpackArchive_0_0 = 0;
	archiveInfo__unpackArchive_0_0->filename = filename__unpackArchive_0_0;
	obtainFileInfo(archiveInfo__unpackArchive_0_0);
	if ((archiveInfo__unpackArchive_0_0->p_file = fopen(archiveInfo__unpackArchive_0_0->filename, "r")) == null__unpackArchive_0_0) {
		fprintf(* stderr_ptr_1__global_0_0, "Error opening file '%s'.\n", archiveInfo__unpackArchive_0_0->filename);
		exit(1);
	} else {
		// ifElse16
		if (archiveInfo__unpackArchive_0_0->isDir) {
			fprintf(* stderr_ptr_1__global_0_0, "'%s' is a directory, not a lzss archive.\n", archiveInfo__unpackArchive_0_0->filename);
			exit(1);
		} else {
			// if15
		}
	}
	while (ftell(archiveInfo__unpackArchive_0_0->p_file) < archiveInfo__unpackArchive_0_0->filesize) {
		countFiles__unpackArchive_0_0++;
		processDescriptor(fileInfo__unpackArchive_0_0, archiveInfo__unpackArchive_0_0);
		printf("Decompressing '%s'....", fileInfo__unpackArchive_0_0->filename);
		fflush(* stdout_ptr_2__global_0_0);
		decompressFile(offset__unpackArchive_0_0, matches__unpackArchive_0_0, fileInfo__unpackArchive_0_0, archiveInfo__unpackArchive_0_0);
		printf(" Done\n");
	}
	fclose(archiveInfo__unpackArchive_0_0->p_file);
	printf("\nFiles decompressed successfully.\n%d files were extracted.\n", countFiles__unpackArchive_0_0);
}

void processDescriptor(struct fileStats__global_0_0 *fileInfo__processDescriptor_0_0, struct fileStats__global_0_0 *archiveInfo__processDescriptor_0_0) {
	char c__processDescriptor_0_0;
	int count__processDescriptor_0_0 = 0;
	fileInfo__processDescriptor_0_0->filenameArray[count__processDescriptor_0_0++] = 'r';
	fileInfo__processDescriptor_0_0->filenameArray[count__processDescriptor_0_0++] = 'e';
	fileInfo__processDescriptor_0_0->filenameArray[count__processDescriptor_0_0++] = 's';
	fileInfo__processDescriptor_0_0->filenameArray[count__processDescriptor_0_0++] = 'u';
	fileInfo__processDescriptor_0_0->filenameArray[count__processDescriptor_0_0++] = 'l';
	fileInfo__processDescriptor_0_0->filenameArray[count__processDescriptor_0_0++] = 't';
	fileInfo__processDescriptor_0_0->filenameArray[count__processDescriptor_0_0++] = '_';
	while ((c__processDescriptor_0_0 = fgetc(archiveInfo__processDescriptor_0_0->p_file)) != 0) {
		fileInfo__processDescriptor_0_0->filenameArray[count__processDescriptor_0_0++] = c__processDescriptor_0_0;
	}
	fileInfo__processDescriptor_0_0->filenameArray[count__processDescriptor_0_0] = 0;
	fileInfo__processDescriptor_0_0->filename = fileInfo__processDescriptor_0_0->filenameArray;
	fread(&(fileInfo__processDescriptor_0_0->filesize), 4, 1, archiveInfo__processDescriptor_0_0->p_file);
}

void decompressFile(int *offset__decompressFile_0_0, int *matches__decompressFile_0_0, struct fileStats__global_0_0 *fileInfo__decompressFile_0_0, struct fileStats__global_0_0 *archiveInfo__decompressFile_0_0) {
	void *null__decompressFile_0_0 = (void *)0;
	int WINLENGTH__decompressFile_0_0 = 131072;
	int EOF__decompressFile_0_0 = -1;
	int sizeCount__decompressFile_0_0 = 1;
	char *p_slashPos__decompressFile_0_0, *p_stringStart__decompressFile_0_0 = fileInfo__decompressFile_0_0->filename;
	while ((p_slashPos__decompressFile_0_0 = strchr(p_stringStart__decompressFile_0_0, '/')) != null__decompressFile_0_0) {
		* p_slashPos__decompressFile_0_0 = 0;
		mkdir(fileInfo__decompressFile_0_0->filename, 0777);
		* p_slashPos__decompressFile_0_0 = '/';
		p_stringStart__decompressFile_0_0 = ++p_slashPos__decompressFile_0_0;
	}
	if ((fileInfo__decompressFile_0_0->p_file = fopen(fileInfo__decompressFile_0_0->filename, "w")) == null__decompressFile_0_0) {
		fprintf(* stderr_ptr_2__global_0_0, "Error writing to file '%s'.", fileInfo__decompressFile_0_0->filename);
		exit(1);
	} else {
		// if17
	}
	Fifo__global_0_0 window__decompressFile_0_0;
	Fifo_init(&window__decompressFile_0_0, WINLENGTH__decompressFile_0_0);
	Fifo_push_back(&window__decompressFile_0_0, fgetc(archiveInfo__decompressFile_0_0->p_file));
	if (Fifo_at(window__decompressFile_0_0, 0) != EOF__decompressFile_0_0) {
		fputc(Fifo_at(window__decompressFile_0_0, 0), fileInfo__decompressFile_0_0->p_file);
	} else {
		// if18
	}
	while (sizeCount__decompressFile_0_0 < fileInfo__decompressFile_0_0->filesize) {
		decode(&window__decompressFile_0_0, &sizeCount__decompressFile_0_0, offset__decompressFile_0_0, matches__decompressFile_0_0, fileInfo__decompressFile_0_0, archiveInfo__decompressFile_0_0);
	}
	fclose(fileInfo__decompressFile_0_0->p_file);
}

void decode(Fifo__global_0_0 *win__decode_0_0, int *sizeCount__decode_0_0, int *offset__decode_0_0, int *matches__decode_0_0, struct fileStats__global_0_0 *fileInfo__decode_0_0, struct fileStats__global_0_0 *archiveInfo__decode_0_0) {
	int WINLENGTH__decode_0_0 = 131072;
	int LKLENGTH__decode_0_0 = 32;
	int count__decode_0_0, encoded__decode_0_0;
	char buffer__decode_0_0[LKLENGTH__decode_0_0];
	char c__decode_0_0 = fgetc(archiveInfo__decode_0_0->p_file);
	if (feof(archiveInfo__decode_0_0->p_file)) {
		return;
	} else {
		// if19
	}
	if (c__decode_0_0 >> 7) {
		encoded__decode_0_0 = c__decode_0_0 << 16;
		encoded__decode_0_0 += fgetc(archiveInfo__decode_0_0->p_file) << 8;
		encoded__decode_0_0 += fgetc(archiveInfo__decode_0_0->p_file);
		* matches__decode_0_0 = (encoded__decode_0_0 & 0x3F) + 1;
		* offset__decode_0_0 = (encoded__decode_0_0 & 0x7FFFFF) >> 6;
		int i__decode_1_1;
		for (count__decode_0_0 = 0, i__decode_1_1 = * offset__decode_0_0; count__decode_0_0 < * matches__decode_0_0; count__decode_0_0++) {
			fputc(Fifo_at(* win__decode_0_0, i__decode_1_1), fileInfo__decode_0_0->p_file);
			buffer__decode_0_0[count__decode_0_0] = Fifo_at(* win__decode_0_0, i__decode_1_1);
			i__decode_1_1++;
			if (i__decode_1_1 == win__decode_0_0->written_size) {
				i__decode_1_1 = 0;
			} else {
				// if20
			}
		}
		for (count__decode_0_0 = 0; count__decode_0_0 < * matches__decode_0_0; count__decode_0_0++) {
			if (win__decode_0_0->written_size >= WINLENGTH__decode_0_0) {
				Fifo_pop_front(win__decode_0_0);
			} else {
				// if21
			}
			Fifo_push_back(win__decode_0_0, buffer__decode_0_0[count__decode_0_0]);
		}
		* sizeCount__decode_0_0 += * matches__decode_0_0;
	} else {
		// ifElse23
		fputc(c__decode_0_0, fileInfo__decode_0_0->p_file);
		if (win__decode_0_0->written_size >= WINLENGTH__decode_0_0) {
			Fifo_pop_front(win__decode_0_0);
		} else {
			// if22
		}
		Fifo_push_back(win__decode_0_0, c__decode_0_0);
		(* sizeCount__decode_0_0)++;
	}
}

void Fifo_init(Fifo__global_0_0 *fifo__Fifo_init_0_0, unsigned size__Fifo_init_0_0) {
	fifo__Fifo_init_0_0->begin = 0;
	fifo__Fifo_init_0_0->end = 0;
	fifo__Fifo_init_0_0->size = size__Fifo_init_0_0;
	fifo__Fifo_init_0_0->written_size = 0;
	fifo__Fifo_init_0_0->data = (char *)malloc(size__Fifo_init_0_0);
	if (!fifo__Fifo_init_0_0->data) {
		fputs("Fifo: out of memory\n", * stderr_ptr_3__global_0_0);
		exit(1);
	} else {
		// if24
	}
}

void Fifo_destroy(Fifo__global_0_0 *fifo__Fifo_destroy_0_0) {
	free(fifo__Fifo_destroy_0_0->data);
}

int Fifo_push_front(Fifo__global_0_0 *fifo__Fifo_push_front_0_0, char c__Fifo_push_front_0_0) {
	if (fifo__Fifo_push_front_0_0->written_size == 0) {
		Fifo_push_back(fifo__Fifo_push_front_0_0, c__Fifo_push_front_0_0);
	} else {
		// ifElse26
		if (fifo__Fifo_push_front_0_0->written_size >= fifo__Fifo_push_front_0_0->size) {
			return -1;
		} else {
			// if25
		}
	}
	fifo__Fifo_push_front_0_0->begin--;
	if (fifo__Fifo_push_front_0_0->begin < 0) {
		fifo__Fifo_push_front_0_0->begin = fifo__Fifo_push_front_0_0->size - 1;
	} else {
		// if27
	}
	fifo__Fifo_push_front_0_0->data[fifo__Fifo_push_front_0_0->begin] = c__Fifo_push_front_0_0;
	fifo__Fifo_push_front_0_0->written_size++;
	return 0;
}

int Fifo_push_back(Fifo__global_0_0 *fifo__Fifo_push_back_0_0, char c__Fifo_push_back_0_0) {
	if (fifo__Fifo_push_back_0_0->written_size >= fifo__Fifo_push_back_0_0->size) {
		return -1;
	} else {
		// if28
	}
	fifo__Fifo_push_back_0_0->written_size++;
	fifo__Fifo_push_back_0_0->data[fifo__Fifo_push_back_0_0->end] = c__Fifo_push_back_0_0;
	fifo__Fifo_push_back_0_0->end++;
	if (fifo__Fifo_push_back_0_0->end == fifo__Fifo_push_back_0_0->size) {
		fifo__Fifo_push_back_0_0->end = 0;
	} else {
		// if29
	}
	return 0;
}

char Fifo_pop_front(Fifo__global_0_0 *fifo__Fifo_pop_front_0_0) {
	if (fifo__Fifo_pop_front_0_0->written_size == 0) {
		return -1;
	} else {
		// if30
	}
	char c__Fifo_pop_front_0_0 = fifo__Fifo_pop_front_0_0->data[fifo__Fifo_pop_front_0_0->begin];
	fifo__Fifo_pop_front_0_0->written_size--;
	fifo__Fifo_pop_front_0_0->begin++;
	if (fifo__Fifo_pop_front_0_0->begin == fifo__Fifo_pop_front_0_0->size) {
		fifo__Fifo_pop_front_0_0->begin = 0;
	} else {
		// if31
	}
	return c__Fifo_pop_front_0_0;
}

char Fifo_pop_back(Fifo__global_0_0 *fifo__Fifo_pop_back_0_0) {
	if (fifo__Fifo_pop_back_0_0->written_size == 0) {
		return -1;
	} else {
		// if32
	}
	fifo__Fifo_pop_back_0_0->written_size--;
	fifo__Fifo_pop_back_0_0->end--;
	if (fifo__Fifo_pop_back_0_0->end < 0) {
		fifo__Fifo_pop_back_0_0->end = fifo__Fifo_pop_back_0_0->size - 1;
	} else {
		// if33
	}
	return fifo__Fifo_pop_back_0_0->data[fifo__Fifo_pop_back_0_0->end];
}

char Fifo_at(const Fifo__global_0_0 fifo__Fifo_at_0_0, unsigned i__Fifo_at_0_0) {
	if (i__Fifo_at_0_0 < fifo__Fifo_at_0_0.written_size) {
		return fifo__Fifo_at_0_0.data[(fifo__Fifo_at_0_0.begin + i__Fifo_at_0_0)%fifo__Fifo_at_0_0.size];
	} else {
		// ifElse34
		return -1;
	}
}

void Fifo_print(const Fifo__global_0_0 fifo__Fifo_print_0_0) {
	int i__Fifo_print_0_0, j__Fifo_print_0_0;
	for (i__Fifo_print_0_0 = fifo__Fifo_print_0_0.begin, j__Fifo_print_0_0 = 0; j__Fifo_print_0_0 < fifo__Fifo_print_0_0.written_size; i__Fifo_print_0_0++, j__Fifo_print_0_0++) {
		if (i__Fifo_print_0_0 == fifo__Fifo_print_0_0.size) {
			i__Fifo_print_0_0 = 0;
		} else {
			// if35
		}
		putchar(fifo__Fifo_print_0_0.data[i__Fifo_print_0_0]);
	}
}

