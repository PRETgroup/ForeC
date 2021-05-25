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

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef int FILE__global_0_0;

#define FILE__global_0_0 FILE

int NULL__global_0_0;

#define NULL__global_0_0 NULL

FILE__global_0_0 *input_file__global_0_0;
FILE__global_0_0 *output_file__global_0_0;
FILE__global_0_0 *text_file__global_0_0;

#undef M_PI

static const int KSMPS__global_0_0 = 1024;
static const int FM_MAX__global_0_0 = 5;
static const int FM_LIMIT__global_0_0 = (65536/2) - 1;
static const int GAIN_LMR__global_0_0 = 2000;
static const int WIN_HANNING__global_0_0 = 1;

typedef struct {
	/* shared */ int value;
	int status;
} Shared_BUFFER_PAIRS__global_0_0;
Shared_BUFFER_PAIRS__global_0_0 BUFFER_PAIRS__global_0_0 = {.value = 8, .status = FOREC_SHARED_UNMODIFIED};

typedef struct {
	float real;
	float imag;
} complex__global_0_0;

typedef struct {
	float history[2];
} fm_quad_demod_filter__global_0_0;

typedef struct {
	double *coeff;
	int decimation;
	int taps;
	float *history;
	int next;
} ntaps_filter_conf__global_0_0;

ntaps_filter_conf__global_0_0 lp_11_conf__global_0_0;
ntaps_filter_conf__global_0_0 lp_12_conf__global_0_0;
ntaps_filter_conf__global_0_0 lp_21_conf__global_0_0;
ntaps_filter_conf__global_0_0 lp_22_conf__global_0_0;
ntaps_filter_conf__global_0_0 *lp_11_conf_1__global_0_0 = &lp_11_conf__global_0_0;
ntaps_filter_conf__global_0_0 *lp_12_conf_1__global_0_0 = &lp_12_conf__global_0_0;
ntaps_filter_conf__global_0_0 *lp_21_conf_1__global_0_0 = &lp_21_conf__global_0_0;
ntaps_filter_conf__global_0_0 *lp_22_conf_1__global_0_0 = &lp_22_conf__global_0_0;
float band_11_obj__global_0_0[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float band_12_obj__global_0_0[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float band_21_obj__global_0_0[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float band_22_obj__global_0_0[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

typedef struct {
	/* shared */ float *value;
	int status;
} Shared_band_11__global_0_0;
Shared_band_11__global_0_0 band_11__global_0_0 = {.value = band_11_obj__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ float *value;
	int status;
} Shared_band_12__global_0_0;
Shared_band_12__global_0_0 band_12__global_0_0 = {.value = band_12_obj__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ float *value;
	int status;
} Shared_band_21__global_0_0;
Shared_band_21__global_0_0 band_21__global_0_0 = {.value = band_21_obj__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ float *value;
	int status;
} Shared_band_22__global_0_0;
Shared_band_22__global_0_0 band_22__global_0_0 = {.value = band_22_obj__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

float resume_1__global_0_0[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float resume_2__global_0_0[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float band_2__global_0_0 = 0.0;
float band_3__global_0_0 = 0.0;
float fm_qd_buffer_array__global_0_0[8];

typedef struct {
	/* shared */ float *value;
	int status;
} Shared_fm_qd_buffer__global_0_0;
Shared_fm_qd_buffer__global_0_0 fm_qd_buffer__global_0_0 = {.value = fm_qd_buffer_array__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

void complex_conj(const complex__global_0_0 *s, complex__global_0_0 *d);
float complex_arg(const complex__global_0_0 *x);
void complex_mul(const complex__global_0_0 *a, const complex__global_0_0 *b, complex__global_0_0 *d);
short dac_cast_trunc_and_normalize_to_short(float f);
void fm_quad_demod_init(fm_quad_demod_filter__global_0_0 *filter);
void fm_quad_demod(fm_quad_demod_filter__global_0_0 *filter, const float i1, const float i2, float *result);
void multiply_square(const float i1, const float i2, float *result);
void compute_window(const unsigned int ntaps, double *taps, const unsigned int type);
int compute_ntaps(const float sampling_freq, const float transition_width, const int window_type);
void ntaps_filter_ffd_init(ntaps_filter_conf__global_0_0 *conf, const double cutoff_freq, const double transition_band, double gain, const int decimation, const double sampling_rate, const int window_type);
float ntaps_filter_ffd(ntaps_filter_conf__global_0_0 *conf, const int input_size, const float input_values[]);
void stereo_sum(const float data_spm, const float data_smm, float *left, float *right);
float subctract(const float i1, const float i2);

// thread ntaps_filter_ffd_0__thread(void);
// thread ntaps_filter_ffd_1__thread(void);
// thread ntaps_filter_ffd_2__thread(void);
// thread ntaps_filter_ffd_3__thread(void);
// thread pipeline_subctract_multiply_square__thread(void);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// main
// ntaps_filter_ffd_0
Shared_BUFFER_PAIRS__global_0_0 BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_band_11__global_0_0 band_11__global_0_0_copy_ntaps_filter_ffd_0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_fm_qd_buffer__global_0_0 fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_0 = {.status = FOREC_SHARED_UNMODIFIED};
// ntaps_filter_ffd_1
Shared_BUFFER_PAIRS__global_0_0 BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_band_12__global_0_0 band_12__global_0_0_copy_ntaps_filter_ffd_1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_fm_qd_buffer__global_0_0 fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_1 = {.status = FOREC_SHARED_UNMODIFIED};
// ntaps_filter_ffd_2
Shared_BUFFER_PAIRS__global_0_0 BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_band_21__global_0_0 band_21__global_0_0_copy_ntaps_filter_ffd_2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_fm_qd_buffer__global_0_0 fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_2 = {.status = FOREC_SHARED_UNMODIFIED};
// ntaps_filter_ffd_3
Shared_BUFFER_PAIRS__global_0_0 BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_band_22__global_0_0 band_22__global_0_0_copy_ntaps_filter_ffd_3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_fm_qd_buffer__global_0_0 fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_3 = {.status = FOREC_SHARED_UNMODIFIED};

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
	Thread ntaps_filter_ffd_0__thread;
	Thread ntaps_filter_ffd_1__thread;
	Thread ntaps_filter_ffd_2__thread;
	Thread ntaps_filter_ffd_3__thread;
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
	int final_audio_frequency__main_0_0;
	float input_rate__main_0_0;
	fm_quad_demod_filter__global_0_0 fm_qd_conf__main_0_0;
	float read_buffer__main_0_0[16];
	ntaps_filter_conf__global_0_0 lp_2_conf__main_0_0;
	ntaps_filter_conf__global_0_0 lp_3_conf__main_0_0;
	float fm_qd_value__main_0_0;
	float ffd_value__main_0_0;
	float ffd_buffer__main_0_0[8];
	float output1__main_0_0;
	float output2__main_0_0;
	short output_short__main_0_0[2];
	float inout_ratio__main_0_0;
	int i__main_1_3;
	long seconds__main_0_0;
	int microseconds__main_0_0;

mainParCore0: {
	// forec:scheduler:counter:start
	// Initialise and start timing each reaction.
	clockTimeUs.previous = getClockTimeUs();
	// forec:scheduler:counter:end
	
	//--------------------------------------------------------------

	gettimeofday(&startTime__main_0_0, 0);
	input_file__global_0_0 = fopen("input.dat", "r");
	if (input_file__global_0_0 == NULL__global_0_0) {
		printf("Cannot open input file input.dat\n");
		exit(1);
	} else {
		// if0
	}
	output_file__global_0_0 = fopen("FmRadio.raw", "w");
	if (output_file__global_0_0 == NULL__global_0_0) {
		printf("Cannot open output file FmRadio.raw\n");
		exit(1);
	} else {
		// if1
	}
	text_file__global_0_0 = fopen("FmRadio.txt", "w");
	if (text_file__global_0_0 == NULL__global_0_0) {
		printf("Cannot open output file FmRadio.txt\n");
		exit(1);
	} else {
		// if2
	}
	final_audio_frequency__main_0_0 = 64*KSMPS__global_0_0;
	input_rate__main_0_0 = 512*KSMPS__global_0_0;
	fm_qd_value__main_0_0 = 0.0;
	ffd_value__main_0_0 = 0.0;
	output1__main_0_0 = 0.0;
	output2__main_0_0 = 0.0;
	inout_ratio__main_0_0 = ((int)input_rate__main_0_0)/final_audio_frequency__main_0_0;
	ntaps_filter_ffd_init(&lp_11_conf__global_0_0, 53000, 4000, 1, 1, input_rate__main_0_0, WIN_HANNING__global_0_0);
	ntaps_filter_ffd_init(&lp_12_conf__global_0_0, 23000, 4000, 1, 1, input_rate__main_0_0, WIN_HANNING__global_0_0);
	ntaps_filter_ffd_init(&lp_21_conf__global_0_0, 21000, 2000, 1, 1, input_rate__main_0_0, WIN_HANNING__global_0_0);
	ntaps_filter_ffd_init(&lp_22_conf__global_0_0, 17000, 2000, 1, 1, input_rate__main_0_0, WIN_HANNING__global_0_0);
	ntaps_filter_ffd_init(&lp_2_conf__main_0_0, 15000, 4000, 0.5, inout_ratio__main_0_0, input_rate__main_0_0, WIN_HANNING__global_0_0);
	ntaps_filter_ffd_init(&lp_3_conf__main_0_0, 15000, 4000, 1.0, inout_ratio__main_0_0, input_rate__main_0_0, WIN_HANNING__global_0_0);
	fm_quad_demod_init(&fm_qd_conf__main_0_0);

	while (fread(read_buffer__main_0_0, sizeof(float), 16, input_file__global_0_0) == 16) {
		for (i__main_1_3 = 0; i__main_1_3 < BUFFER_PAIRS__global_0_0.value; i__main_1_3++) {
			fm_quad_demod(&fm_qd_conf__main_0_0, read_buffer__main_0_0[i__main_1_3*2], read_buffer__main_0_0[i__main_1_3*2 + 1], &fm_qd_value__main_0_0);
			fm_qd_buffer__global_0_0.value[i__main_1_3] = fm_qd_value__main_0_0;
			// forec:iteration:for1_0:bound:8:8
		}

		// par0(ntaps_filter_ffd_0__thread, ntaps_filter_ffd_1__thread, ntaps_filter_ffd_2__thread, ntaps_filter_ffd_3__thread);
		// forec:statement:par:par0:start
		// Set the par(...) information.
		mainParParent.parId = 0;
		pthread_mutex_lock(&mainParParent.parStatusLock);
		mainParParent.parStatus = FOREC_PAR_ON;
		pthread_cond_broadcast(&mainParParent.parStatusCond);
		pthread_mutex_unlock(&mainParParent.parStatusLock);

		// Link the threads and handlers together.
		mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
		ntaps_filter_ffd_0__thread.programCounter = &&ntaps_filter_ffd_0__thread;
		mainReactionStartMaster0.nextThread = &ntaps_filter_ffd_0__thread;
		ntaps_filter_ffd_0__thread.prevThread = &mainReactionStartMaster0;
		mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
		ntaps_filter_ffd_0__thread.nextThread = &mainReactionEndMaster0;
		mainReactionEndMaster0.prevThread = &ntaps_filter_ffd_0__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
		mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

		// Set the join address.
		mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

		// Set the core information.
		mainParCore0.activeThreads = 1;
		mainParCore0.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto ntaps_filter_ffd_0__thread;
		par0JoinAddress_mainParCore0:;
		// forec:statement:par:par0:end

		for (i__main_1_3 = 0; i__main_1_3 < BUFFER_PAIRS__global_0_0.value; i__main_1_3++) {
			resume_1__global_0_0[i__main_1_3] = subctract(band_11__global_0_0.value[i__main_1_3], band_12__global_0_0.value[i__main_1_3]);
			resume_2__global_0_0[i__main_1_3] = subctract(band_21__global_0_0.value[i__main_1_3], band_22__global_0_0.value[i__main_1_3]);
			multiply_square(resume_1__global_0_0[i__main_1_3], resume_2__global_0_0[i__main_1_3], &ffd_value__main_0_0);
			ffd_buffer__main_0_0[i__main_1_3] = ffd_value__main_0_0;
			// forec:iteration:for1_1:bound:8:8
		}
		band_2__global_0_0 = ntaps_filter_ffd(&lp_2_conf__main_0_0, 8, fm_qd_buffer__global_0_0.value);
		band_3__global_0_0 = ntaps_filter_ffd(&lp_3_conf__main_0_0, 8, ffd_buffer__main_0_0);
		stereo_sum(band_2__global_0_0, band_3__global_0_0, &output1__main_0_0, &output2__main_0_0);
		output_short__main_0_0[0] = dac_cast_trunc_and_normalize_to_short(output1__main_0_0);
		output_short__main_0_0[1] = dac_cast_trunc_and_normalize_to_short(output2__main_0_0);
		fwrite(output_short__main_0_0, sizeof(short), 2, output_file__global_0_0);
		fprintf(text_file__global_0_0, "%-10.5f %-10.5f\n", output1__main_0_0, output2__main_0_0);

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
		// forec:iteration:while_2:bound:1000:1000
	}

	fclose(input_file__global_0_0);
	fclose(output_file__global_0_0);
	fclose(text_file__global_0_0);
	gettimeofday(&endTime__main_0_0, 0);
	seconds__main_0_0 = endTime__main_0_0.tv_sec - startTime__main_0_0.tv_sec;
	microseconds__main_0_0 = endTime__main_0_0.tv_usec - startTime__main_0_0.tv_usec;
	if (microseconds__main_0_0 < 0) {
		microseconds__main_0_0 += 1000000;
		seconds__main_0_0--;
	} else {
		// if3
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

	// Combine shared variables.
	int parId = mainParParent.parId;
	if (parId == 0) {

		// band_11__global_0_0
		if (band_11__global_0_0_copy_ntaps_filter_ffd_0.status == FOREC_SHARED_MODIFIED) {
			band_11__global_0_0_copy_ntaps_filter_ffd_0.status = FOREC_SHARED_UNMODIFIED;
			band_11__global_0_0.value = band_11__global_0_0_copy_ntaps_filter_ffd_0.value;
		}

		// band_12__global_0_0
		if (band_12__global_0_0_copy_ntaps_filter_ffd_1.status == FOREC_SHARED_MODIFIED) {
			band_12__global_0_0_copy_ntaps_filter_ffd_1.status = FOREC_SHARED_UNMODIFIED;
			band_12__global_0_0.value = band_12__global_0_0_copy_ntaps_filter_ffd_1.value;
		}

		// band_21__global_0_0
		if (band_21__global_0_0_copy_ntaps_filter_ffd_2.status == FOREC_SHARED_MODIFIED) {
			band_21__global_0_0_copy_ntaps_filter_ffd_2.status = FOREC_SHARED_UNMODIFIED;
			band_21__global_0_0.value = band_21__global_0_0_copy_ntaps_filter_ffd_2.value;
		}

		// band_22__global_0_0
		if (band_22__global_0_0_copy_ntaps_filter_ffd_3.status == FOREC_SHARED_MODIFIED) {
			band_22__global_0_0_copy_ntaps_filter_ffd_3.status = FOREC_SHARED_UNMODIFIED;
			band_22__global_0_0.value = band_22__global_0_0_copy_ntaps_filter_ffd_3.value;
		}
	} else {
		// Nothing.
	}

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
		ntaps_filter_ffd_1__thread.programCounter = &&ntaps_filter_ffd_1__thread;
		mainReactionStartSlave1.nextThread = &ntaps_filter_ffd_1__thread;
		ntaps_filter_ffd_1__thread.prevThread = &mainReactionStartSlave1;
		mainReactionEndSlave1.programCounter = &&mainReactionEndSlave1;
		ntaps_filter_ffd_1__thread.nextThread = &mainReactionEndSlave1;
		mainReactionEndSlave1.prevThread = &ntaps_filter_ffd_1__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave1.nextThread = &mainReactionStartSlave1;
		mainReactionStartSlave1.prevThread = &mainReactionEndSlave1;

		// Set the core information.
		mainParCore1.activeThreads = 1;
		mainParCore1.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto ntaps_filter_ffd_1__thread;
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
		ntaps_filter_ffd_2__thread.programCounter = &&ntaps_filter_ffd_2__thread;
		mainReactionStartSlave2.nextThread = &ntaps_filter_ffd_2__thread;
		ntaps_filter_ffd_2__thread.prevThread = &mainReactionStartSlave2;
		mainReactionEndSlave2.programCounter = &&mainReactionEndSlave2;
		ntaps_filter_ffd_2__thread.nextThread = &mainReactionEndSlave2;
		mainReactionEndSlave2.prevThread = &ntaps_filter_ffd_2__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave2.nextThread = &mainReactionStartSlave2;
		mainReactionStartSlave2.prevThread = &mainReactionEndSlave2;

		// Set the core information.
		mainParCore2.activeThreads = 1;
		mainParCore2.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto ntaps_filter_ffd_2__thread;
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
		ntaps_filter_ffd_3__thread.programCounter = &&ntaps_filter_ffd_3__thread;
		mainReactionStartSlave3.nextThread = &ntaps_filter_ffd_3__thread;
		ntaps_filter_ffd_3__thread.prevThread = &mainReactionStartSlave3;
		mainReactionEndSlave3.programCounter = &&mainReactionEndSlave3;
		ntaps_filter_ffd_3__thread.nextThread = &mainReactionEndSlave3;
		mainReactionEndSlave3.prevThread = &ntaps_filter_ffd_3__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndSlave3.nextThread = &mainReactionStartSlave3;
		mainReactionStartSlave3.prevThread = &mainReactionEndSlave3;

		// Set the core information.
		mainParCore3.activeThreads = 1;
		mainParCore3.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		goto ntaps_filter_ffd_3__thread;
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
	// forec:thread:ntaps_filter_ffd_0:start
	/*--------------------------------------------------------------
	| Thread ntaps_filter_ffd_0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_BUFFER_PAIRS__global_0_0 BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_0_local;
	Shared_band_11__global_0_0 band_11__global_0_0_copy_ntaps_filter_ffd_0_local;
	Shared_fm_qd_buffer__global_0_0 fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_0_local;
	int i__ntaps_filter_ffd_0_0_0;

	// Thread body -------------------------------------------------
	ntaps_filter_ffd_0__thread: {
		// Initialise the local copies of shared variables.
		BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_0_local.value = BUFFER_PAIRS__global_0_0.value;
		BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_0_local.status = FOREC_SHARED_UNMODIFIED;
		band_11__global_0_0_copy_ntaps_filter_ffd_0_local.value = band_11__global_0_0.value;
		band_11__global_0_0_copy_ntaps_filter_ffd_0_local.status = FOREC_SHARED_UNMODIFIED;
		fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_0_local.value = fm_qd_buffer__global_0_0.value;
		fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_0_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		for (i__ntaps_filter_ffd_0_0_0 = 0; i__ntaps_filter_ffd_0_0_0 < BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_0_local.value; i__ntaps_filter_ffd_0_0_0++) {
			band_11__global_0_0_copy_ntaps_filter_ffd_0_local.value[i__ntaps_filter_ffd_0_0_0] = ntaps_filter_ffd(lp_11_conf_1__global_0_0, 1, fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_0_local.value + i__ntaps_filter_ffd_0_0_0);
			band_11__global_0_0_copy_ntaps_filter_ffd_0_local.status = FOREC_SHARED_MODIFIED;
			// forec:iteration:for1_3:bound:8:8
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		band_11__global_0_0_copy_ntaps_filter_ffd_0 = band_11__global_0_0_copy_ntaps_filter_ffd_0_local;

		// forec:scheduler:threadRemove:ntaps_filter_ffd_0:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		ntaps_filter_ffd_0__thread.nextThread -> prevThread = ntaps_filter_ffd_0__thread.prevThread;
		ntaps_filter_ffd_0__thread.prevThread -> nextThread = ntaps_filter_ffd_0__thread.nextThread;
		goto *ntaps_filter_ffd_0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:ntaps_filter_ffd_0:end
	} // ntaps_filter_ffd_0__thread
	// forec:thread:ntaps_filter_ffd_0:end

	// forec:thread:ntaps_filter_ffd_1:start
	/*--------------------------------------------------------------
	| Thread ntaps_filter_ffd_1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_BUFFER_PAIRS__global_0_0 BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_1_local;
	Shared_band_12__global_0_0 band_12__global_0_0_copy_ntaps_filter_ffd_1_local;
	Shared_fm_qd_buffer__global_0_0 fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_1_local;
	int i__ntaps_filter_ffd_1_0_0;

	// Thread body -------------------------------------------------
	ntaps_filter_ffd_1__thread: {
		// Initialise the local copies of shared variables.
		BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_1_local.value = BUFFER_PAIRS__global_0_0.value;
		BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_1_local.status = FOREC_SHARED_UNMODIFIED;
		band_12__global_0_0_copy_ntaps_filter_ffd_1_local.value = band_12__global_0_0.value;
		band_12__global_0_0_copy_ntaps_filter_ffd_1_local.status = FOREC_SHARED_UNMODIFIED;
		fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_1_local.value = fm_qd_buffer__global_0_0.value;
		fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		for (i__ntaps_filter_ffd_1_0_0 = 0; i__ntaps_filter_ffd_1_0_0 < BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_1_local.value; i__ntaps_filter_ffd_1_0_0++) {
			band_12__global_0_0_copy_ntaps_filter_ffd_1_local.value[i__ntaps_filter_ffd_1_0_0] = ntaps_filter_ffd(lp_12_conf_1__global_0_0, 1, fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_1_local.value + i__ntaps_filter_ffd_1_0_0);
			band_12__global_0_0_copy_ntaps_filter_ffd_1_local.status = FOREC_SHARED_MODIFIED;
			// forec:iteration:for1_4:bound:8:8
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		band_12__global_0_0_copy_ntaps_filter_ffd_1 = band_12__global_0_0_copy_ntaps_filter_ffd_1_local;

		// forec:scheduler:threadRemove:ntaps_filter_ffd_1:start

		// Delete thread from the linked list and core.
		mainParCore1.activeThreads--;
		ntaps_filter_ffd_1__thread.nextThread -> prevThread = ntaps_filter_ffd_1__thread.prevThread;
		ntaps_filter_ffd_1__thread.prevThread -> nextThread = ntaps_filter_ffd_1__thread.nextThread;
		goto *ntaps_filter_ffd_1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:ntaps_filter_ffd_1:end
	} // ntaps_filter_ffd_1__thread
	// forec:thread:ntaps_filter_ffd_1:end

	// forec:thread:ntaps_filter_ffd_2:start
	/*--------------------------------------------------------------
	| Thread ntaps_filter_ffd_2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_BUFFER_PAIRS__global_0_0 BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_2_local;
	Shared_band_21__global_0_0 band_21__global_0_0_copy_ntaps_filter_ffd_2_local;
	Shared_fm_qd_buffer__global_0_0 fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_2_local;
	int i__ntaps_filter_ffd_2_0_0;

	// Thread body -------------------------------------------------
	ntaps_filter_ffd_2__thread: {
		// Initialise the local copies of shared variables.
		BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_2_local.value = BUFFER_PAIRS__global_0_0.value;
		BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_2_local.status = FOREC_SHARED_UNMODIFIED;
		band_21__global_0_0_copy_ntaps_filter_ffd_2_local.value = band_21__global_0_0.value;
		band_21__global_0_0_copy_ntaps_filter_ffd_2_local.status = FOREC_SHARED_UNMODIFIED;
		fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_2_local.value = fm_qd_buffer__global_0_0.value;
		fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		for (i__ntaps_filter_ffd_2_0_0 = 0; i__ntaps_filter_ffd_2_0_0 < BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_2_local.value; i__ntaps_filter_ffd_2_0_0++) {
			band_21__global_0_0_copy_ntaps_filter_ffd_2_local.value[i__ntaps_filter_ffd_2_0_0] = ntaps_filter_ffd(lp_21_conf_1__global_0_0, 1, fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_2_local.value + i__ntaps_filter_ffd_2_0_0);
			band_21__global_0_0_copy_ntaps_filter_ffd_2_local.status = FOREC_SHARED_MODIFIED;
			// forec:iteration:for1_5:bound:8:8
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		band_21__global_0_0_copy_ntaps_filter_ffd_2 = band_21__global_0_0_copy_ntaps_filter_ffd_2_local;

		// forec:scheduler:threadRemove:ntaps_filter_ffd_2:start

		// Delete thread from the linked list and core.
		mainParCore2.activeThreads--;
		ntaps_filter_ffd_2__thread.nextThread -> prevThread = ntaps_filter_ffd_2__thread.prevThread;
		ntaps_filter_ffd_2__thread.prevThread -> nextThread = ntaps_filter_ffd_2__thread.nextThread;
		goto *ntaps_filter_ffd_2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:ntaps_filter_ffd_2:end
	} // ntaps_filter_ffd_2__thread
	// forec:thread:ntaps_filter_ffd_2:end

	// forec:thread:ntaps_filter_ffd_3:start
	/*--------------------------------------------------------------
	| Thread ntaps_filter_ffd_3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_BUFFER_PAIRS__global_0_0 BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_3_local;
	Shared_band_22__global_0_0 band_22__global_0_0_copy_ntaps_filter_ffd_3_local;
	Shared_fm_qd_buffer__global_0_0 fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_3_local;
	int i__ntaps_filter_ffd_3_0_0;

	// Thread body -------------------------------------------------
	ntaps_filter_ffd_3__thread: {
		// Initialise the local copies of shared variables.
		BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_3_local.value = BUFFER_PAIRS__global_0_0.value;
		BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_3_local.status = FOREC_SHARED_UNMODIFIED;
		band_22__global_0_0_copy_ntaps_filter_ffd_3_local.value = band_22__global_0_0.value;
		band_22__global_0_0_copy_ntaps_filter_ffd_3_local.status = FOREC_SHARED_UNMODIFIED;
		fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_3_local.value = fm_qd_buffer__global_0_0.value;
		fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_3_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		for (i__ntaps_filter_ffd_3_0_0 = 0; i__ntaps_filter_ffd_3_0_0 < BUFFER_PAIRS__global_0_0_copy_ntaps_filter_ffd_3_local.value; i__ntaps_filter_ffd_3_0_0++) {
			band_22__global_0_0_copy_ntaps_filter_ffd_3_local.value[i__ntaps_filter_ffd_3_0_0] = ntaps_filter_ffd(lp_22_conf_1__global_0_0, 1, fm_qd_buffer__global_0_0_copy_ntaps_filter_ffd_3_local.value + i__ntaps_filter_ffd_3_0_0);
			band_22__global_0_0_copy_ntaps_filter_ffd_3_local.status = FOREC_SHARED_MODIFIED;
			// forec:iteration:for1_6:bound:8:8
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		band_22__global_0_0_copy_ntaps_filter_ffd_3 = band_22__global_0_0_copy_ntaps_filter_ffd_3_local;

		// forec:scheduler:threadRemove:ntaps_filter_ffd_3:start

		// Delete thread from the linked list and core.
		mainParCore3.activeThreads--;
		ntaps_filter_ffd_3__thread.nextThread -> prevThread = ntaps_filter_ffd_3__thread.prevThread;
		ntaps_filter_ffd_3__thread.prevThread -> nextThread = ntaps_filter_ffd_3__thread.nextThread;
		goto *ntaps_filter_ffd_3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:ntaps_filter_ffd_3:end
	} // ntaps_filter_ffd_3__thread
	// forec:thread:ntaps_filter_ffd_3:end


} // End of the main() function.

void complex_conj(const complex__global_0_0 *s__complex_conj_0_0, complex__global_0_0 *d__complex_conj_0_0) {
	(d__complex_conj_0_0)->real = (s__complex_conj_0_0)->real;
	(d__complex_conj_0_0)->imag = -1*(s__complex_conj_0_0)->imag;
}

float complex_arg(const complex__global_0_0 *x__complex_arg_0_0) {
	return atan2((x__complex_arg_0_0)->imag, (x__complex_arg_0_0)->real);
}

void complex_mul(const complex__global_0_0 *a__complex_mul_0_0, const complex__global_0_0 *b__complex_mul_0_0, complex__global_0_0 *d__complex_mul_0_0) {
	(d__complex_mul_0_0)->real = (a__complex_mul_0_0)->real*(b__complex_mul_0_0)->real - ((a__complex_mul_0_0)->imag*(b__complex_mul_0_0)->imag);
	(d__complex_mul_0_0)->imag = (a__complex_mul_0_0)->real*(b__complex_mul_0_0)->imag + (a__complex_mul_0_0)->imag*(b__complex_mul_0_0)->real;
}

short dac_cast_trunc_and_normalize_to_short(float f__dac_cast_trunc_and_normalize_to_short_0_0) {
	short x__dac_cast_trunc_and_normalize_to_short_0_0;
	f__dac_cast_trunc_and_normalize_to_short_0_0 = (f__dac_cast_trunc_and_normalize_to_short_0_0/FM_MAX__global_0_0)*FM_LIMIT__global_0_0;
	x__dac_cast_trunc_and_normalize_to_short_0_0 = f__dac_cast_trunc_and_normalize_to_short_0_0;
	return x__dac_cast_trunc_and_normalize_to_short_0_0;
}

void fm_quad_demod_init(fm_quad_demod_filter__global_0_0 *filter__fm_quad_demod_init_0_0) {
	filter__fm_quad_demod_init_0_0->history[0] = 0;
	filter__fm_quad_demod_init_0_0->history[1] = 0;
}

void fm_quad_demod(fm_quad_demod_filter__global_0_0 *filter__fm_quad_demod_0_0, const float i1__fm_quad_demod_0_0, const float i2__fm_quad_demod_0_0, float *result__fm_quad_demod_0_0) {
	complex__global_0_0 x_N__fm_quad_demod_0_0;
	complex__global_0_0 x_N_1__fm_quad_demod_0_0;
	complex__global_0_0 x_N_1_conj__fm_quad_demod_0_0;
	complex__global_0_0 y_N__fm_quad_demod_0_0;
	float demod__fm_quad_demod_0_0;
	const float d_gain__fm_quad_demod_0_0 = 0.5;
	x_N__fm_quad_demod_0_0.real = i2__fm_quad_demod_0_0;
	x_N__fm_quad_demod_0_0.imag = i1__fm_quad_demod_0_0;
	x_N_1__fm_quad_demod_0_0.real = filter__fm_quad_demod_0_0->history[1];
	x_N_1__fm_quad_demod_0_0.imag = filter__fm_quad_demod_0_0->history[0];
	complex_conj(&x_N_1__fm_quad_demod_0_0, &x_N_1_conj__fm_quad_demod_0_0);
	complex_mul(&x_N_1_conj__fm_quad_demod_0_0, &x_N__fm_quad_demod_0_0, &y_N__fm_quad_demod_0_0);
	demod__fm_quad_demod_0_0 = d_gain__fm_quad_demod_0_0*complex_arg(&y_N__fm_quad_demod_0_0);
	filter__fm_quad_demod_0_0->history[0] = i1__fm_quad_demod_0_0;
	filter__fm_quad_demod_0_0->history[1] = i2__fm_quad_demod_0_0;
	* result__fm_quad_demod_0_0 = demod__fm_quad_demod_0_0;
}

void multiply_square(const float i1__multiply_square_0_0, const float i2__multiply_square_0_0, float *result__multiply_square_0_0) {
	* result__multiply_square_0_0 = GAIN_LMR__global_0_0*i1__multiply_square_0_0*i2__multiply_square_0_0*i2__multiply_square_0_0;
}

void compute_window(const unsigned int ntaps__compute_window_0_0, double *taps__compute_window_0_0, const unsigned int type__compute_window_0_0) {
	const double M_PI__compute_window_0_0 = 3.14159265358979323846;
	const int WIN_HAMMING__compute_window_0_0 = 0;
	const int WIN_HANNING__compute_window_0_0 = 1;
	const int WIN_BLACKMAN__compute_window_0_0 = 2;
	int n__compute_window_0_0;
	const int M__compute_window_0_0 = ntaps__compute_window_0_0 - 1;
	if (type__compute_window_0_0 == WIN_HAMMING__compute_window_0_0) {
		for (n__compute_window_0_0 = 0; n__compute_window_0_0 < ntaps__compute_window_0_0; n__compute_window_0_0++) {
			taps__compute_window_0_0[n__compute_window_0_0] = 0.54 - 0.46*cos((2*M_PI__compute_window_0_0*n__compute_window_0_0)/M__compute_window_0_0);
			// forec:iteration:for1_7:bound:407:407
		}
	} else {
		// ifElse6
		if (type__compute_window_0_0 == WIN_HANNING__compute_window_0_0) {
			for (n__compute_window_0_0 = 0; n__compute_window_0_0 < ntaps__compute_window_0_0; n__compute_window_0_0++) {
				taps__compute_window_0_0[n__compute_window_0_0] = 0.5 - 0.5*cos((2*M_PI__compute_window_0_0*n__compute_window_0_0)/M__compute_window_0_0);
				// forec:iteration:for1_8:bound:407:407
			}
		} else {
			// ifElse5
			if (type__compute_window_0_0 == WIN_BLACKMAN__compute_window_0_0) {
				for (n__compute_window_0_0 = 0; n__compute_window_0_0 < ntaps__compute_window_0_0; n__compute_window_0_0++) {
					taps__compute_window_0_0[n__compute_window_0_0] = 0.42 - 0.50*cos((2*M_PI__compute_window_0_0*n__compute_window_0_0)/(M__compute_window_0_0 - 1)) - 0.08*cos((4*M_PI__compute_window_0_0*n__compute_window_0_0)/(M__compute_window_0_0 - 1));
					// forec:iteration:for1_9:bound:407:407
				}
			} else {
				// if4
			}
		}
	}
}

int compute_ntaps(const float sampling_freq__compute_ntaps_0_0, const float transition_width__compute_ntaps_0_0, const int window_type__compute_ntaps_0_0) {
	const float delta_f__compute_ntaps_0_0 = transition_width__compute_ntaps_0_0/sampling_freq__compute_ntaps_0_0;
	const float width_factor__compute_ntaps_0_0[3] = {3.3, 3.1, 5.5};
	int ntaps__compute_ntaps_0_0 = (int)(width_factor__compute_ntaps_0_0[window_type__compute_ntaps_0_0]/delta_f__compute_ntaps_0_0 + 0.5);
	if ((ntaps__compute_ntaps_0_0 & 1) == 0) {
		ntaps__compute_ntaps_0_0++;
	} else {
		// if7
	}
	return ntaps__compute_ntaps_0_0;
}

void ntaps_filter_ffd_init(ntaps_filter_conf__global_0_0 *conf__ntaps_filter_ffd_init_0_0, const double cutoff_freq__ntaps_filter_ffd_init_0_0, const double transition_band__ntaps_filter_ffd_init_0_0, double gain__ntaps_filter_ffd_init_0_0, const int decimation__ntaps_filter_ffd_init_0_0, const double sampling_rate__ntaps_filter_ffd_init_0_0, const int window_type__ntaps_filter_ffd_init_0_0) {
	const double M_PI__ntaps_filter_ffd_init_0_0 = 3.14159265358979323846;
	int n__ntaps_filter_ffd_init_0_0;
	int i__ntaps_filter_ffd_init_0_0;
	const unsigned int ntaps__ntaps_filter_ffd_init_0_0 = compute_ntaps(sampling_rate__ntaps_filter_ffd_init_0_0, transition_band__ntaps_filter_ffd_init_0_0, window_type__ntaps_filter_ffd_init_0_0);
	double *w__ntaps_filter_ffd_init_0_0 = malloc(ntaps__ntaps_filter_ffd_init_0_0*sizeof(double));
	const int M__ntaps_filter_ffd_init_0_0 = (ntaps__ntaps_filter_ffd_init_0_0 - 1)/2;
	const double fwT0__ntaps_filter_ffd_init_0_0 = 2*M_PI__ntaps_filter_ffd_init_0_0*cutoff_freq__ntaps_filter_ffd_init_0_0/sampling_rate__ntaps_filter_ffd_init_0_0;
	conf__ntaps_filter_ffd_init_0_0->coeff = malloc(ntaps__ntaps_filter_ffd_init_0_0*sizeof(double));
	conf__ntaps_filter_ffd_init_0_0->taps = ntaps__ntaps_filter_ffd_init_0_0;
	conf__ntaps_filter_ffd_init_0_0->decimation = decimation__ntaps_filter_ffd_init_0_0;
	compute_window(ntaps__ntaps_filter_ffd_init_0_0, w__ntaps_filter_ffd_init_0_0, window_type__ntaps_filter_ffd_init_0_0);
	for (n__ntaps_filter_ffd_init_0_0 = 0; n__ntaps_filter_ffd_init_0_0 < ntaps__ntaps_filter_ffd_init_0_0; n__ntaps_filter_ffd_init_0_0++) {
		conf__ntaps_filter_ffd_init_0_0->coeff[n__ntaps_filter_ffd_init_0_0] = 0.0;
		// forec:iteration:for1_10:bound:407:407
	}
	for (n__ntaps_filter_ffd_init_0_0 = -M__ntaps_filter_ffd_init_0_0; n__ntaps_filter_ffd_init_0_0 <= M__ntaps_filter_ffd_init_0_0; n__ntaps_filter_ffd_init_0_0++) {
		if (n__ntaps_filter_ffd_init_0_0 == 0) {
			conf__ntaps_filter_ffd_init_0_0->coeff[n__ntaps_filter_ffd_init_0_0 + M__ntaps_filter_ffd_init_0_0] = fwT0__ntaps_filter_ffd_init_0_0/M_PI__ntaps_filter_ffd_init_0_0*w__ntaps_filter_ffd_init_0_0[n__ntaps_filter_ffd_init_0_0 + M__ntaps_filter_ffd_init_0_0];
		} else {
			// ifElse8
			conf__ntaps_filter_ffd_init_0_0->coeff[n__ntaps_filter_ffd_init_0_0 + M__ntaps_filter_ffd_init_0_0] = sin(n__ntaps_filter_ffd_init_0_0*fwT0__ntaps_filter_ffd_init_0_0)/(n__ntaps_filter_ffd_init_0_0*M_PI__ntaps_filter_ffd_init_0_0)*w__ntaps_filter_ffd_init_0_0[n__ntaps_filter_ffd_init_0_0 + M__ntaps_filter_ffd_init_0_0];
		}
		// forec:iteration:for1_11:bound:407:407
	}
	double fmax__ntaps_filter_ffd_init_0_0 = conf__ntaps_filter_ffd_init_0_0->coeff[0 + M__ntaps_filter_ffd_init_0_0];
	for (n__ntaps_filter_ffd_init_0_0 = 1; n__ntaps_filter_ffd_init_0_0 <= M__ntaps_filter_ffd_init_0_0; n__ntaps_filter_ffd_init_0_0++) {
		fmax__ntaps_filter_ffd_init_0_0 += 2*conf__ntaps_filter_ffd_init_0_0->coeff[n__ntaps_filter_ffd_init_0_0 + M__ntaps_filter_ffd_init_0_0];
		// forec:iteration:for1_12:bound:407:407
	}
	gain__ntaps_filter_ffd_init_0_0 /= fmax__ntaps_filter_ffd_init_0_0;
	for (i__ntaps_filter_ffd_init_0_0 = 0; i__ntaps_filter_ffd_init_0_0 < ntaps__ntaps_filter_ffd_init_0_0; i__ntaps_filter_ffd_init_0_0++) {
		conf__ntaps_filter_ffd_init_0_0->coeff[i__ntaps_filter_ffd_init_0_0] *= gain__ntaps_filter_ffd_init_0_0;
		// forec:iteration:for1_13:bound:407:407
	}
	conf__ntaps_filter_ffd_init_0_0->next = 0;
	conf__ntaps_filter_ffd_init_0_0->history = (float *)malloc(sizeof(float)*conf__ntaps_filter_ffd_init_0_0->taps);
	for (n__ntaps_filter_ffd_init_0_0 = 0; n__ntaps_filter_ffd_init_0_0 < conf__ntaps_filter_ffd_init_0_0->taps; n__ntaps_filter_ffd_init_0_0++) {
		conf__ntaps_filter_ffd_init_0_0->history[n__ntaps_filter_ffd_init_0_0] = 0;
		// forec:iteration:for1_14:bound:407:407
	}
	free(w__ntaps_filter_ffd_init_0_0);
}

float ntaps_filter_ffd(ntaps_filter_conf__global_0_0 *conf__ntaps_filter_ffd_0_0, const int input_size__ntaps_filter_ffd_0_0, const float input_values__ntaps_filter_ffd_0_0[]) {
	assert(input_size__ntaps_filter_ffd_0_0 == conf__ntaps_filter_ffd_0_0->decimation);
	int i__ntaps_filter_ffd_0_0;
	for (i__ntaps_filter_ffd_0_0 = 0; i__ntaps_filter_ffd_0_0 < conf__ntaps_filter_ffd_0_0->decimation; i__ntaps_filter_ffd_0_0++) {
		conf__ntaps_filter_ffd_0_0->history[conf__ntaps_filter_ffd_0_0->next] = input_values__ntaps_filter_ffd_0_0[i__ntaps_filter_ffd_0_0];
		conf__ntaps_filter_ffd_0_0->next = (conf__ntaps_filter_ffd_0_0->next + 1)%conf__ntaps_filter_ffd_0_0->taps;
		// forec:iteration:for1_15:bound:1:8
	}
	float sum__ntaps_filter_ffd_0_0 = 0.0;
	for (i__ntaps_filter_ffd_0_0 = 0; i__ntaps_filter_ffd_0_0 < conf__ntaps_filter_ffd_0_0->taps; i__ntaps_filter_ffd_0_0++) {
		sum__ntaps_filter_ffd_0_0 = sum__ntaps_filter_ffd_0_0 + conf__ntaps_filter_ffd_0_0->history[(conf__ntaps_filter_ffd_0_0->next + i__ntaps_filter_ffd_0_0)%conf__ntaps_filter_ffd_0_0->taps]*conf__ntaps_filter_ffd_0_0->coeff[conf__ntaps_filter_ffd_0_0->taps - i__ntaps_filter_ffd_0_0 - 1];
		// forec:iteration:for1_16:bound:407:407
	}
	return sum__ntaps_filter_ffd_0_0;
}

void stereo_sum(const float data_spm__stereo_sum_0_0, const float data_smm__stereo_sum_0_0, float *left__stereo_sum_0_0, float *right__stereo_sum_0_0) {
	* left__stereo_sum_0_0 = (data_spm__stereo_sum_0_0 + data_smm__stereo_sum_0_0);
	* right__stereo_sum_0_0 = (data_spm__stereo_sum_0_0 - data_smm__stereo_sum_0_0);
}

float subctract(const float i1__subctract_0_0, const float i2__subctract_0_0) {
	return i1__subctract_0_0 - i2__subctract_0_0;
}

