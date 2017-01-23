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
volatile int mainParReactionCounter;


/*==============================================================
| Original global declarations:
| Global declarations in the original program code.
*=============================================================*/
// Original main function
void *forecMain(void *args);

#include <stdio.h>

typedef struct {
	int values[2];
	unsigned int count;
	unsigned int size;
} Buffer__global_0_0;

typedef struct {
	int baseRate;
	int operationalMode;
	int ekgSensitivity;
	int paceVoltage;
	int sensitivityThreshold;
	int maxRate;
	int minRate;
	int maxAttackSlope;
	int maxDecaySlope;
} Param__global_0_0;

typedef enum {
	absent = 0,
	present = 1
} Signal__global_0_0;

typedef struct {
	unsigned int timestamp;
	Signal__global_0_0 AP;
	Signal__global_0_0 VP;
	Signal__global_0_0 DDD;
	Signal__global_0_0 VDI;
	Signal__global_0_0 lrl;
	Signal__global_0_0 url;
	Signal__global_0_0 pmt;
	Signal__global_0_0 vurl;
	Signal__global_0_0 elt;
} Event__global_0_0;

typedef struct {
	Event__global_0_0 events[100];
	unsigned int tail;
	unsigned int size;
} Log__global_0_0;

const unsigned int max(const unsigned int *const copy1__max_0_0, const unsigned int *const copy2__max_0_0) {
	if (* copy1__max_0_0 > * copy2__max_0_0) {
		return * copy1__max_0_0;
	} else {
		// ifElse0
		return * copy2__max_0_0;
	}
}

const unsigned int Base_Period__global_0_0 = 1562500;

typedef struct {
	/* shared */ unsigned int value;
	unsigned short int status;
} Shared_TURI__global_0_0;
Shared_TURI__global_0_0 TURI__global_0_0 = {.value = 256, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ unsigned int value;
	unsigned short int status;
} Shared_TLRI__global_0_0;
Shared_TLRI__global_0_0 TLRI__global_0_0 = {.value = 640, .status = FOREC_SHARED_UNMODIFIED};

const unsigned int TAVI__global_0_0 = 96;
const unsigned int TVRP__global_0_0 = 96;
const unsigned int TPVAB__global_0_0 = 32;
const unsigned int Threshold__global_0_0 = 256;

typedef struct {
	/* shared */ unsigned int value;
	unsigned short int status;
} Shared_TPVARP__global_0_0;
Shared_TPVARP__global_0_0 TPVARP__global_0_0 = {.value = 64, .status = FOREC_SHARED_UNMODIFIED} /* combine with max */;

const unsigned int TPVARP_100__global_0_0 = 64;
const unsigned int TPVARP_500__global_0_0 = 320;
const unsigned int T_150__global_0_0 = 96;
const unsigned int T_200__global_0_0 = 128;
const unsigned int T_500__global_0_0 = 320;
const unsigned int Aminwait__global_0_0 = 320;
const unsigned int Vminwait__global_0_0 = 320;
const unsigned int Tantemin__global_0_0 = 128;
const unsigned int Tretromin__global_0_0 = 128;

typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_A_Get__global_0_0;
Shared_A_Get__global_0_0 A_Get__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_A_Act__global_0_0;
Shared_A_Act__global_0_0 A_Act__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_V_Get__global_0_0;
Shared_V_Get__global_0_0 V_Get__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_V_Act__global_0_0;
Shared_V_Act__global_0_0 V_Act__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};

/* input */ unsigned int motionSensor__global_0_0 = 0x0000;
/* input */ unsigned int rfIn__global_0_0 = 0x0000;

typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_AP__global_0_0;
Shared_AP__global_0_0 AP__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_VP__global_0_0;
Shared_VP__global_0_0 VP__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};

/* output */ unsigned int rfOut__global_0_0 = 0x0000;

typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_AS__global_0_0;
Shared_AS__global_0_0 AS__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_AR__global_0_0;
Shared_AR__global_0_0 AR__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_VS__global_0_0;
Shared_VS__global_0_0 VS__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_DDD__global_0_0;
Shared_DDD__global_0_0 DDD__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_VDI__global_0_0;
Shared_VDI__global_0_0 VDI__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Buffer__global_0_0 value;
	unsigned short int status;
} Shared_motionSensing2rateAdapter__global_0_0;
Shared_motionSensing2rateAdapter__global_0_0 motionSensing2rateAdapter__global_0_0 = {.value = {.values = {0, }, .count = 0, .size = 2}, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ unsigned int value;
	unsigned short int status;
} Shared_rate__global_0_0;
Shared_rate__global_0_0 rate__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Param__global_0_0 value;
	unsigned short int status;
} Shared_parameters__global_0_0;
Shared_parameters__global_0_0 parameters__global_0_0 = {.value = {.baseRate = 0, .operationalMode = 0, .ekgSensitivity = 0, .paceVoltage = 0, .sensitivityThreshold = 0, .maxRate = 0, .minRate = 0, .maxAttackSlope = 0, .maxDecaySlope = 0}, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Log__global_0_0 value;
	unsigned short int status;
} Shared_log__global_0_0;
Shared_log__global_0_0 log__global_0_0 = {.value = {.events = {{0}, }, .tail = 0, .size = 100}, .status = FOREC_SHARED_UNMODIFIED};

// thread ekgSensing__thread(/* shared */ Signal__global_0_0 AP, /* shared */ Signal__global_0_0 A_Act, /* shared */ Signal__global_0_0 A_Get, /* shared */ Signal__global_0_0 VP, /* shared */ Signal__global_0_0 V_Act, /* shared */ Signal__global_0_0 V_Get);
// thread basic__thread(/* shared */ Signal__global_0_0 AS, /* shared */ Signal__global_0_0 VS, /* shared */ Signal__global_0_0 VP, /* shared */ Signal__global_0_0 DDD, /* shared */ Signal__global_0_0 VDI, /* shared */ Signal__global_0_0 AP, /* input */ Signal__global_0_0 A_Get, /* input */ Signal__global_0_0 A_Act, /* shared */ Signal__global_0_0 AR, Signal__global_0_0 A_Block, /* shared */ unsigned int TPVARP, /* input */ Signal__global_0_0 V_Get, /* input */ Signal__global_0_0 V_Act, Signal__global_0_0 V_Block);
// thread modeSwitch__thread(/* shared */ Signal__global_0_0 AS, /* shared */ Signal__global_0_0 AR, /* shared */ Signal__global_0_0 AP, /* shared */ Signal__global_0_0 VS, /* shared */ Signal__global_0_0 VP, Signal__global_0_0 Fast, Signal__global_0_0 Slow, Signal__global_0_0 D_Beg, Signal__global_0_0 D_End, /* shared */ Signal__global_0_0 DDD, /* shared */ Signal__global_0_0 VDI);
// thread patternVpAs__thread(/* shared */ Signal__global_0_0 VP, /* shared */ Signal__global_0_0 VS, /* shared */ Signal__global_0_0 AP, /* shared */ Signal__global_0_0 AR, Signal__global_0_0 VP_AS, Signal__global_0_0 Reset, /* shared */ unsigned int TPVARP);
// thread motionSensing__thread(/* input */ unsigned int motionSensor, /* shared */ Buffer__global_0_0 motionSensing2rateAdapter);
// thread rateAdapter__thread(/* shared */ Buffer__global_0_0 motionSensing2rateAdapter, /* shared */ unsigned int rate);
// thread logging__thread(/* shared */ Signal__global_0_0 AS, /* shared */ Signal__global_0_0 AP, /* shared */ Signal__global_0_0 AR, /* shared */ Signal__global_0_0 VS, /* shared */ Signal__global_0_0 VP, /* shared */ Signal__global_0_0 VDI);
// thread communication__thread(/* input */ unsigned int rfIn, /* input */ unsigned int rfOut, /* shared */ Log__global_0_0 log);

double sin(double rad);
void icrc(unsigned short crc, unsigned long len, short jinit, int jrev);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// basic
Shared_TURI__global_0_0 TURI__global_0_0_copy_basic = {.status = FOREC_SHARED_UNMODIFIED};
Shared_TLRI__global_0_0 TLRI__global_0_0_copy_basic = {.status = FOREC_SHARED_UNMODIFIED};
Shared_TPVARP__global_0_0 TPVARP__global_0_0_copy_basic = {.status = FOREC_SHARED_UNMODIFIED};
Shared_A_Get__global_0_0 A_Get__global_0_0_copy_basic = {.status = FOREC_SHARED_UNMODIFIED};
Shared_A_Act__global_0_0 A_Act__global_0_0_copy_basic = {.status = FOREC_SHARED_UNMODIFIED};
Shared_V_Get__global_0_0 V_Get__global_0_0_copy_basic = {.status = FOREC_SHARED_UNMODIFIED};
Shared_V_Act__global_0_0 V_Act__global_0_0_copy_basic = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AP__global_0_0 AP__global_0_0_copy_basic = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VP__global_0_0 VP__global_0_0_copy_basic = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AS__global_0_0 AS__global_0_0_copy_basic = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AR__global_0_0 AR__global_0_0_copy_basic = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VS__global_0_0 VS__global_0_0_copy_basic = {.status = FOREC_SHARED_UNMODIFIED};
Shared_DDD__global_0_0 DDD__global_0_0_copy_basic = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VDI__global_0_0 VDI__global_0_0_copy_basic = {.status = FOREC_SHARED_UNMODIFIED};
// communication
Shared_parameters__global_0_0 parameters__global_0_0_copy_communication = {.status = FOREC_SHARED_UNMODIFIED};
Shared_log__global_0_0 log__global_0_0_copy_communication = {.status = FOREC_SHARED_UNMODIFIED};
// ekgSensing
Shared_A_Get__global_0_0 A_Get__global_0_0_copy_ekgSensing = {.status = FOREC_SHARED_UNMODIFIED};
Shared_A_Act__global_0_0 A_Act__global_0_0_copy_ekgSensing = {.status = FOREC_SHARED_UNMODIFIED};
Shared_V_Get__global_0_0 V_Get__global_0_0_copy_ekgSensing = {.status = FOREC_SHARED_UNMODIFIED};
Shared_V_Act__global_0_0 V_Act__global_0_0_copy_ekgSensing = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AP__global_0_0 AP__global_0_0_copy_ekgSensing = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VP__global_0_0 VP__global_0_0_copy_ekgSensing = {.status = FOREC_SHARED_UNMODIFIED};
// logging
Shared_TURI__global_0_0 TURI__global_0_0_copy_logging = {.status = FOREC_SHARED_UNMODIFIED};
Shared_TLRI__global_0_0 TLRI__global_0_0_copy_logging = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AP__global_0_0 AP__global_0_0_copy_logging = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VP__global_0_0 VP__global_0_0_copy_logging = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AS__global_0_0 AS__global_0_0_copy_logging = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AR__global_0_0 AR__global_0_0_copy_logging = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VS__global_0_0 VS__global_0_0_copy_logging = {.status = FOREC_SHARED_UNMODIFIED};
Shared_DDD__global_0_0 DDD__global_0_0_copy_logging = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VDI__global_0_0 VDI__global_0_0_copy_logging = {.status = FOREC_SHARED_UNMODIFIED};
Shared_log__global_0_0 log__global_0_0_copy_logging = {.status = FOREC_SHARED_UNMODIFIED};
// main
Shared_TPVARP__global_0_0 TPVARP__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_A_Get__global_0_0 A_Get__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_A_Act__global_0_0 A_Act__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_V_Get__global_0_0 V_Get__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_V_Act__global_0_0 V_Act__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AP__global_0_0 AP__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VP__global_0_0 VP__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AS__global_0_0 AS__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AR__global_0_0 AR__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VS__global_0_0 VS__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_DDD__global_0_0 DDD__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VDI__global_0_0 VDI__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_log__global_0_0 log__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
// modeSwitch
Shared_AP__global_0_0 AP__global_0_0_copy_modeSwitch = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VP__global_0_0 VP__global_0_0_copy_modeSwitch = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AS__global_0_0 AS__global_0_0_copy_modeSwitch = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AR__global_0_0 AR__global_0_0_copy_modeSwitch = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VS__global_0_0 VS__global_0_0_copy_modeSwitch = {.status = FOREC_SHARED_UNMODIFIED};
Shared_DDD__global_0_0 DDD__global_0_0_copy_modeSwitch = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VDI__global_0_0 VDI__global_0_0_copy_modeSwitch = {.status = FOREC_SHARED_UNMODIFIED};
// motionSensing
Shared_motionSensing2rateAdapter__global_0_0 motionSensing2rateAdapter__global_0_0_copy_motionSensing = {.status = FOREC_SHARED_UNMODIFIED};
// patternVpAs
Shared_TPVARP__global_0_0 TPVARP__global_0_0_copy_patternVpAs = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AP__global_0_0 AP__global_0_0_copy_patternVpAs = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VP__global_0_0 VP__global_0_0_copy_patternVpAs = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AS__global_0_0 AS__global_0_0_copy_patternVpAs = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AR__global_0_0 AR__global_0_0_copy_patternVpAs = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VS__global_0_0 VS__global_0_0_copy_patternVpAs = {.status = FOREC_SHARED_UNMODIFIED};
// rateAdapter

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
	unsigned short int coreId = arguments->coreId;
	int argc__main_0_0 = arguments->argc;
	char **argv__main_0_0 = arguments->argv;

	// Variables for par()s ----------------------------------------
	// par0
	Thread basic__thread;
	Thread communication__thread;
	Thread ekgSensing__thread;
	Thread logging__thread;
	Thread modeSwitch__thread;
	Thread motionSensing__thread;
	Thread patternVpAs__thread;
	Thread rateAdapter__thread;
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
	Shared_TPVARP__global_0_0 TPVARP__global_0_0_copy_main_local;
	Shared_A_Get__global_0_0 A_Get__global_0_0_copy_main_local;
	Shared_A_Act__global_0_0 A_Act__global_0_0_copy_main_local;
	Shared_V_Get__global_0_0 V_Get__global_0_0_copy_main_local;
	Shared_V_Act__global_0_0 V_Act__global_0_0_copy_main_local;
	Shared_AP__global_0_0 AP__global_0_0_copy_main_local;
	Shared_VP__global_0_0 VP__global_0_0_copy_main_local;
	Shared_AS__global_0_0 AS__global_0_0_copy_main_local;
	Shared_AR__global_0_0 AR__global_0_0_copy_main_local;
	Shared_VS__global_0_0 VS__global_0_0_copy_main_local;
	Shared_DDD__global_0_0 DDD__global_0_0_copy_main_local;
	Shared_VDI__global_0_0 VDI__global_0_0_copy_main_local;
	Shared_log__global_0_0 log__global_0_0_copy_main_local;

mainParCore0: {
	// Initialise the local copies of shared variables.
	TPVARP__global_0_0_copy_main_local = TPVARP__global_0_0;
	A_Get__global_0_0_copy_main_local = A_Get__global_0_0;
	A_Act__global_0_0_copy_main_local = A_Act__global_0_0;
	V_Get__global_0_0_copy_main_local = V_Get__global_0_0;
	V_Act__global_0_0_copy_main_local = V_Act__global_0_0;
	AP__global_0_0_copy_main_local = AP__global_0_0;
	VP__global_0_0_copy_main_local = VP__global_0_0;
	AS__global_0_0_copy_main_local = AS__global_0_0;
	AR__global_0_0_copy_main_local = AR__global_0_0;
	VS__global_0_0_copy_main_local = VS__global_0_0;
	DDD__global_0_0_copy_main_local = DDD__global_0_0;
	VDI__global_0_0_copy_main_local = VDI__global_0_0;
	log__global_0_0_copy_main_local = log__global_0_0;
	//--------------------------------------------------------------

	printf("Pacemaker\n");

	// par0(ekgSensing__thread, basic__thread, modeSwitch__thread, patternVpAs__thread, motionSensing__thread, rateAdapter__thread, logging__thread, communication__thread);
	TPVARP__global_0_0_copy_main = TPVARP__global_0_0_copy_main_local;
	TPVARP__global_0_0.value = TPVARP__global_0_0_copy_main_local.value;
	A_Get__global_0_0_copy_main = A_Get__global_0_0_copy_main_local;
	A_Get__global_0_0.value = A_Get__global_0_0_copy_main_local.value;
	A_Act__global_0_0_copy_main = A_Act__global_0_0_copy_main_local;
	A_Act__global_0_0.value = A_Act__global_0_0_copy_main_local.value;
	V_Get__global_0_0_copy_main = V_Get__global_0_0_copy_main_local;
	V_Get__global_0_0.value = V_Get__global_0_0_copy_main_local.value;
	V_Act__global_0_0_copy_main = V_Act__global_0_0_copy_main_local;
	V_Act__global_0_0.value = V_Act__global_0_0_copy_main_local.value;
	AP__global_0_0_copy_main = AP__global_0_0_copy_main_local;
	AP__global_0_0.value = AP__global_0_0_copy_main_local.value;
	VP__global_0_0_copy_main = VP__global_0_0_copy_main_local;
	VP__global_0_0.value = VP__global_0_0_copy_main_local.value;
	AS__global_0_0_copy_main = AS__global_0_0_copy_main_local;
	AS__global_0_0.value = AS__global_0_0_copy_main_local.value;
	AR__global_0_0_copy_main = AR__global_0_0_copy_main_local;
	AR__global_0_0.value = AR__global_0_0_copy_main_local.value;
	VS__global_0_0_copy_main = VS__global_0_0_copy_main_local;
	VS__global_0_0.value = VS__global_0_0_copy_main_local.value;
	DDD__global_0_0_copy_main = DDD__global_0_0_copy_main_local;
	DDD__global_0_0.value = DDD__global_0_0_copy_main_local.value;
	VDI__global_0_0_copy_main = VDI__global_0_0_copy_main_local;
	VDI__global_0_0.value = VDI__global_0_0_copy_main_local.value;
	log__global_0_0_copy_main = log__global_0_0_copy_main_local;
	log__global_0_0.value = log__global_0_0_copy_main_local.value;
	// Set the par(...) information.
	mainParParent.parId = 0;
	mainParParent.parStatus = FOREC_PAR_ON;

	// Link the threads and handlers together.
	mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
	ekgSensing__thread.programCounter = &&ekgSensing__thread;
	mainReactionStartMaster0.nextThread = &ekgSensing__thread;
	ekgSensing__thread.prevThread = &mainReactionStartMaster0;
	basic__thread.programCounter = &&basic__thread;
	ekgSensing__thread.nextThread = &basic__thread;
	basic__thread.prevThread = &ekgSensing__thread;
	modeSwitch__thread.programCounter = &&modeSwitch__thread;
	basic__thread.nextThread = &modeSwitch__thread;
	modeSwitch__thread.prevThread = &basic__thread;
	patternVpAs__thread.programCounter = &&patternVpAs__thread;
	modeSwitch__thread.nextThread = &patternVpAs__thread;
	patternVpAs__thread.prevThread = &modeSwitch__thread;
	motionSensing__thread.programCounter = &&motionSensing__thread;
	patternVpAs__thread.nextThread = &motionSensing__thread;
	motionSensing__thread.prevThread = &patternVpAs__thread;
	rateAdapter__thread.programCounter = &&rateAdapter__thread;
	motionSensing__thread.nextThread = &rateAdapter__thread;
	rateAdapter__thread.prevThread = &motionSensing__thread;
	logging__thread.programCounter = &&logging__thread;
	rateAdapter__thread.nextThread = &logging__thread;
	logging__thread.prevThread = &rateAdapter__thread;
	communication__thread.programCounter = &&communication__thread;
	logging__thread.nextThread = &communication__thread;
	communication__thread.prevThread = &logging__thread;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	communication__thread.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &communication__thread;

	// Link the last and first threads/handlers together.
	mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
	mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

	// Set the join address.
	mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

	// Set the core information.
	mainParCore0.activeThreads = 8;
	mainParCore0.reactionCounter = mainParReactionCounter;

	// Go to the first thread.
	// forec:statement:par:par0:start
	goto ekgSensing__thread;
	par0JoinAddress_mainParCore0:;
	// forec:statement:par:par0:end
	TPVARP__global_0_0_copy_main_local = TPVARP__global_0_0;
	A_Get__global_0_0_copy_main_local = A_Get__global_0_0;
	A_Act__global_0_0_copy_main_local = A_Act__global_0_0;
	V_Get__global_0_0_copy_main_local = V_Get__global_0_0;
	V_Act__global_0_0_copy_main_local = V_Act__global_0_0;
	AP__global_0_0_copy_main_local = AP__global_0_0;
	VP__global_0_0_copy_main_local = VP__global_0_0;
	AS__global_0_0_copy_main_local = AS__global_0_0;
	AR__global_0_0_copy_main_local = AR__global_0_0;
	VS__global_0_0_copy_main_local = VS__global_0_0;
	DDD__global_0_0_copy_main_local = DDD__global_0_0;
	VDI__global_0_0_copy_main_local = VDI__global_0_0;
	log__global_0_0_copy_main_local = log__global_0_0;

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
	unsigned short int parId = mainParParent.parId;
	if (parId == 0) {
		unsigned short int index;
		unsigned short int numberOfModifiedCopies;

		// TPVARP__global_0_0
		numberOfModifiedCopies = 0;
		Shared_TPVARP__global_0_0 *modified_TPVARP__global_0_0[2];
		// Find the modified copies.
		if (TPVARP__global_0_0_copy_basic.status == FOREC_SHARED_MODIFIED) {
			TPVARP__global_0_0_copy_basic.status = FOREC_SHARED_UNMODIFIED;
			modified_TPVARP__global_0_0[numberOfModifiedCopies] = &TPVARP__global_0_0_copy_basic;
			++numberOfModifiedCopies;
		}
		if (TPVARP__global_0_0_copy_patternVpAs.status == FOREC_SHARED_MODIFIED) {
			TPVARP__global_0_0_copy_patternVpAs.status = FOREC_SHARED_UNMODIFIED;
			modified_TPVARP__global_0_0[numberOfModifiedCopies] = &TPVARP__global_0_0_copy_patternVpAs;
			++numberOfModifiedCopies;
		}
		// Assign the first modified copy.
		if (numberOfModifiedCopies > 0) {
			TPVARP__global_0_0.value = modified_TPVARP__global_0_0[0]->value;
		}
		// Combine with the remaining modified copies.
		for (index = 1; index < numberOfModifiedCopies; ++index) {
			TPVARP__global_0_0.value = max(&TPVARP__global_0_0.value, &modified_TPVARP__global_0_0[index]->value);
		}

		// A_Get__global_0_0
		if (A_Get__global_0_0_copy_ekgSensing.status == FOREC_SHARED_MODIFIED) {
			A_Get__global_0_0_copy_ekgSensing.status = FOREC_SHARED_UNMODIFIED;
			A_Get__global_0_0.value = A_Get__global_0_0_copy_ekgSensing.value;
		}

		// A_Act__global_0_0
		if (A_Act__global_0_0_copy_ekgSensing.status == FOREC_SHARED_MODIFIED) {
			A_Act__global_0_0_copy_ekgSensing.status = FOREC_SHARED_UNMODIFIED;
			A_Act__global_0_0.value = A_Act__global_0_0_copy_ekgSensing.value;
		}

		// V_Get__global_0_0
		if (V_Get__global_0_0_copy_ekgSensing.status == FOREC_SHARED_MODIFIED) {
			V_Get__global_0_0_copy_ekgSensing.status = FOREC_SHARED_UNMODIFIED;
			V_Get__global_0_0.value = V_Get__global_0_0_copy_ekgSensing.value;
		}

		// V_Act__global_0_0
		if (V_Act__global_0_0_copy_ekgSensing.status == FOREC_SHARED_MODIFIED) {
			V_Act__global_0_0_copy_ekgSensing.status = FOREC_SHARED_UNMODIFIED;
			V_Act__global_0_0.value = V_Act__global_0_0_copy_ekgSensing.value;
		}

		// AP__global_0_0
		if (AP__global_0_0_copy_basic.status == FOREC_SHARED_MODIFIED) {
			AP__global_0_0_copy_basic.status = FOREC_SHARED_UNMODIFIED;
			AP__global_0_0.value = AP__global_0_0_copy_basic.value;
		}

		// VP__global_0_0
		if (VP__global_0_0_copy_basic.status == FOREC_SHARED_MODIFIED) {
			VP__global_0_0_copy_basic.status = FOREC_SHARED_UNMODIFIED;
			VP__global_0_0.value = VP__global_0_0_copy_basic.value;
		}

		// AS__global_0_0
		if (AS__global_0_0_copy_basic.status == FOREC_SHARED_MODIFIED) {
			AS__global_0_0_copy_basic.status = FOREC_SHARED_UNMODIFIED;
			AS__global_0_0.value = AS__global_0_0_copy_basic.value;
		}

		// AR__global_0_0
		if (AR__global_0_0_copy_basic.status == FOREC_SHARED_MODIFIED) {
			AR__global_0_0_copy_basic.status = FOREC_SHARED_UNMODIFIED;
			AR__global_0_0.value = AR__global_0_0_copy_basic.value;
		}

		// VS__global_0_0
		if (VS__global_0_0_copy_basic.status == FOREC_SHARED_MODIFIED) {
			VS__global_0_0_copy_basic.status = FOREC_SHARED_UNMODIFIED;
			VS__global_0_0.value = VS__global_0_0_copy_basic.value;
		}

		// DDD__global_0_0
		if (DDD__global_0_0_copy_modeSwitch.status == FOREC_SHARED_MODIFIED) {
			DDD__global_0_0_copy_modeSwitch.status = FOREC_SHARED_UNMODIFIED;
			DDD__global_0_0.value = DDD__global_0_0_copy_modeSwitch.value;
		}

		// VDI__global_0_0
		if (VDI__global_0_0_copy_modeSwitch.status == FOREC_SHARED_MODIFIED) {
			VDI__global_0_0_copy_modeSwitch.status = FOREC_SHARED_UNMODIFIED;
			VDI__global_0_0.value = VDI__global_0_0_copy_modeSwitch.value;
		}

		// log__global_0_0
		if (log__global_0_0_copy_logging.status == FOREC_SHARED_MODIFIED) {
			log__global_0_0_copy_logging.status = FOREC_SHARED_UNMODIFIED;
			log__global_0_0.value = log__global_0_0_copy_logging.value;
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
	// forec:thread:basic:start
	/*--------------------------------------------------------------
	| Thread basic
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	enum {
		Init_avi_ms = 0,
		AVI,
		Wait_URI,
		VDI_Idle,
		VDI_AVI
	} state_avi_ms__basic_0_0;

	enum {
		Init_lri_ms = 0,
		Sensed,
		VDI_LRI
	} state_lri_ms__basic_0_0;

	enum {
		Init_pvarp_elt = 0,
		PVAB,
		PVARP
	} state_pvarp_elt__basic_0_0;

	enum {
		Init_vrp = 0,
		VRP
	} state_vrp__basic_0_0;

	unsigned int timer_uri__basic_0_0;
	unsigned int timer_avi_ms__basic_0_0;
	unsigned int timer_lri_ms__basic_0_0;
	unsigned int timer_pvarp_elt__basic_0_0;
	unsigned int timer_vrp__basic_0_0;
	Signal__global_0_0 A_Block__basic_0_0;
	Signal__global_0_0 V_Block__basic_0_0;
	Signal__global_0_0 VP_new__basic_0_0;
	Shared_TURI__global_0_0 TURI__global_0_0_copy_basic_local;
	Shared_TLRI__global_0_0 TLRI__global_0_0_copy_basic_local;
	Shared_TPVARP__global_0_0 TPVARP__global_0_0_copy_basic_local;
	Shared_A_Get__global_0_0 A_Get__global_0_0_copy_basic_local;
	Shared_A_Act__global_0_0 A_Act__global_0_0_copy_basic_local;
	Shared_V_Get__global_0_0 V_Get__global_0_0_copy_basic_local;
	Shared_V_Act__global_0_0 V_Act__global_0_0_copy_basic_local;
	Shared_AP__global_0_0 AP__global_0_0_copy_basic_local;
	Shared_VP__global_0_0 VP__global_0_0_copy_basic_local;
	Shared_AS__global_0_0 AS__global_0_0_copy_basic_local;
	Shared_AR__global_0_0 AR__global_0_0_copy_basic_local;
	Shared_VS__global_0_0 VS__global_0_0_copy_basic_local;
	Shared_DDD__global_0_0 DDD__global_0_0_copy_basic_local;
	Shared_VDI__global_0_0 VDI__global_0_0_copy_basic_local;

	// Thread body -------------------------------------------------
	basic__thread: {
		// Initialise the local copies of shared variables.
		TURI__global_0_0_copy_basic_local.value = TURI__global_0_0.value;
		TURI__global_0_0_copy_basic_local.status = FOREC_SHARED_UNMODIFIED;
		TLRI__global_0_0_copy_basic_local.value = TLRI__global_0_0.value;
		TLRI__global_0_0_copy_basic_local.status = FOREC_SHARED_UNMODIFIED;
		TPVARP__global_0_0_copy_basic_local.value = TPVARP__global_0_0_copy_main.value;
		TPVARP__global_0_0_copy_basic_local.status = FOREC_SHARED_UNMODIFIED;
		A_Get__global_0_0_copy_basic_local.value = A_Get__global_0_0_copy_main.value;
		A_Get__global_0_0_copy_basic_local.status = FOREC_SHARED_UNMODIFIED;
		A_Act__global_0_0_copy_basic_local.value = A_Act__global_0_0_copy_main.value;
		A_Act__global_0_0_copy_basic_local.status = FOREC_SHARED_UNMODIFIED;
		V_Get__global_0_0_copy_basic_local.value = V_Get__global_0_0_copy_main.value;
		V_Get__global_0_0_copy_basic_local.status = FOREC_SHARED_UNMODIFIED;
		V_Act__global_0_0_copy_basic_local.value = V_Act__global_0_0_copy_main.value;
		V_Act__global_0_0_copy_basic_local.status = FOREC_SHARED_UNMODIFIED;
		AP__global_0_0_copy_basic_local.value = AP__global_0_0_copy_main.value;
		AP__global_0_0_copy_basic_local.status = FOREC_SHARED_UNMODIFIED;
		VP__global_0_0_copy_basic_local.value = VP__global_0_0_copy_main.value;
		VP__global_0_0_copy_basic_local.status = FOREC_SHARED_UNMODIFIED;
		AS__global_0_0_copy_basic_local.value = AS__global_0_0_copy_main.value;
		AS__global_0_0_copy_basic_local.status = FOREC_SHARED_UNMODIFIED;
		VS__global_0_0_copy_basic_local.value = VS__global_0_0_copy_main.value;
		VS__global_0_0_copy_basic_local.status = FOREC_SHARED_UNMODIFIED;
		DDD__global_0_0_copy_basic_local.value = DDD__global_0_0_copy_main.value;
		DDD__global_0_0_copy_basic_local.status = FOREC_SHARED_UNMODIFIED;
		VDI__global_0_0_copy_basic_local.value = VDI__global_0_0_copy_main.value;
		VDI__global_0_0_copy_basic_local.status = FOREC_SHARED_UNMODIFIED;
		AR__global_0_0_copy_basic_local.value = AR__global_0_0.value;
		AR__global_0_0_copy_basic_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		state_avi_ms__basic_0_0 = Init_avi_ms;
		state_lri_ms__basic_0_0 = Init_lri_ms;
		state_pvarp_elt__basic_0_0 = Init_pvarp_elt;
		state_vrp__basic_0_0 = Init_vrp;
		timer_uri__basic_0_0 = 0;
		timer_avi_ms__basic_0_0 = 0;
		timer_lri_ms__basic_0_0 = 0;
		timer_pvarp_elt__basic_0_0 = 0;
		timer_vrp__basic_0_0 = 0;
		A_Block__basic_0_0 = absent;
		V_Block__basic_0_0 = absent;
		VP_new__basic_0_0 = absent;

		while (1) {
			printf("uri\n");
			timer_uri__basic_0_0 = timer_uri__basic_0_0 + 1;
			if ((VP__global_0_0_copy_basic_local.value == present) || (VS__global_0_0_copy_basic_local.value == present)) {
				timer_uri__basic_0_0 = 0;
			} else {
				// ifElse15
				
			}
			printf("avi_ms\n");
			timer_avi_ms__basic_0_0 = timer_avi_ms__basic_0_0 + 1;
			VP_new__basic_0_0 = absent;
			if (state_avi_ms__basic_0_0 == Init_avi_ms) {
				if ((AS__global_0_0_copy_basic_local.value == present) || (AP__global_0_0_copy_basic_local.value == present)) {
					state_avi_ms__basic_0_0 = AVI;
					timer_avi_ms__basic_0_0 = 0;
				} else {
					// ifElse17
					if (VDI__global_0_0_copy_basic_local.value == present) {
						state_avi_ms__basic_0_0 = VDI_Idle;
					} else {
						// ifElse16
						
					}
				}
			} else {
				// ifElse35
				if (state_avi_ms__basic_0_0 == AVI) {
					if (VDI__global_0_0_copy_basic_local.value == present) {
						state_avi_ms__basic_0_0 = VDI_AVI;
					} else {
						// ifElse22
						if (VS__global_0_0_copy_basic_local.value == present) {
							state_avi_ms__basic_0_0 = Init_avi_ms;
						} else {
							// ifElse21
							if (timer_avi_ms__basic_0_0 >= TAVI__global_0_0) {
								if (timer_uri__basic_0_0 >= TURI__global_0_0_copy_basic_local.value) {
									state_avi_ms__basic_0_0 = Init_avi_ms;
									VP_new__basic_0_0 = present;
								} else {
									// ifElse19
									if (timer_uri__basic_0_0 <= TURI__global_0_0_copy_basic_local.value) {
										state_avi_ms__basic_0_0 = Wait_URI;
									} else {
										// ifElse18
										
									}
								}
							} else {
								// ifElse20
								
							}
						}
					}
				} else {
					// ifElse34
					if (state_avi_ms__basic_0_0 == Wait_URI) {
						if (timer_uri__basic_0_0 >= TURI__global_0_0_copy_basic_local.value) {
							state_avi_ms__basic_0_0 = Init_avi_ms;
							VP_new__basic_0_0 = present;
						} else {
							// ifElse25
							if (VS__global_0_0_copy_basic_local.value == present) {
								state_avi_ms__basic_0_0 = Init_avi_ms;
							} else {
								// ifElse24
								if (VDI__global_0_0_copy_basic_local.value == present) {
									state_avi_ms__basic_0_0 = VDI_Idle;
									timer_avi_ms__basic_0_0 = 0;
								} else {
									// ifElse23
									
								}
							}
						}
					} else {
						// ifElse33
						if (state_avi_ms__basic_0_0 == VDI_Idle) {
							if (DDD__global_0_0_copy_basic_local.value == present) {
								state_avi_ms__basic_0_0 = Init_avi_ms;
							} else {
								// ifElse27
								if ((AS__global_0_0_copy_basic_local.value == present) || (AP__global_0_0_copy_basic_local.value == present)) {
									state_avi_ms__basic_0_0 = VDI_AVI;
									timer_avi_ms__basic_0_0 = 0;
								} else {
									// ifElse26
									
								}
							}
						} else {
							// ifElse32
							if (state_avi_ms__basic_0_0 == VDI_AVI) {
								if (VS__global_0_0_copy_basic_local.value == present) {
									state_avi_ms__basic_0_0 = VDI_Idle;
								} else {
									// ifElse30
									if (DDD__global_0_0_copy_basic_local.value == present) {
										state_avi_ms__basic_0_0 = AVI;
									} else {
										// ifElse29
										if (timer_avi_ms__basic_0_0 >= TAVI__global_0_0) {
											state_avi_ms__basic_0_0 = VDI_Idle;
										} else {
											// ifElse28
											
										}
									}
								}
							} else {
								// ifElse31
								printf("!! avi_ms: In an undefined state (%d)\n", state_avi_ms__basic_0_0);
							}
						}
					}
				}
			}
			printf("lri_ms\n");
			timer_lri_ms__basic_0_0 = timer_lri_ms__basic_0_0 + 1;
			AP__global_0_0_copy_basic_local.value = absent;
			AP__global_0_0_copy_basic_local.status = FOREC_SHARED_MODIFIED;
			if (state_lri_ms__basic_0_0 == Init_lri_ms) {
				if ((VP__global_0_0_copy_basic_local.value == present) || (VS__global_0_0_copy_basic_local.value == present)) {
					state_lri_ms__basic_0_0 = Init_lri_ms;
					timer_lri_ms__basic_0_0 = 0;
				} else {
					// ifElse39
					if (timer_lri_ms__basic_0_0 >= (TLRI__global_0_0_copy_basic_local.value - TAVI__global_0_0)) {
						state_lri_ms__basic_0_0 = Init_lri_ms;
						AP__global_0_0_copy_basic_local.value = present;
						AP__global_0_0_copy_basic_local.status = FOREC_SHARED_MODIFIED;
					} else {
						// ifElse38
						if (AS__global_0_0_copy_basic_local.value == present) {
							state_lri_ms__basic_0_0 = Sensed;
						} else {
							// ifElse37
							if (VDI__global_0_0_copy_basic_local.value == present) {
								state_lri_ms__basic_0_0 = VDI_LRI;
							} else {
								// ifElse36
								
							}
						}
					}
				}
			} else {
				// ifElse47
				if (state_lri_ms__basic_0_0 == VDI_LRI) {
					if (VS__global_0_0_copy_basic_local.value == VDI_LRI) {
						state_lri_ms__basic_0_0 = Init_lri_ms;
						timer_lri_ms__basic_0_0 = 0;
					} else {
						// ifElse42
						if (timer_lri_ms__basic_0_0 >= TLRI__global_0_0_copy_basic_local.value) {
							state_lri_ms__basic_0_0 = Init_lri_ms;
							VP_new__basic_0_0 = present;
						} else {
							// ifElse41
							if (DDD__global_0_0_copy_basic_local.value == present) {
								state_lri_ms__basic_0_0 = Init_lri_ms;
								timer_lri_ms__basic_0_0 = 0;
							} else {
								// if40
							}
						}
					}
				} else {
					// ifElse46
					if (state_lri_ms__basic_0_0 == Sensed) {
						if (VDI__global_0_0_copy_basic_local.value == present) {
							state_lri_ms__basic_0_0 = VDI_LRI;
						} else {
							// ifElse44
							if ((VP__global_0_0_copy_basic_local.value == present) || (VS__global_0_0_copy_basic_local.value == present)) {
								state_lri_ms__basic_0_0 = Init_lri_ms;
								timer_lri_ms__basic_0_0 = 0;
							} else {
								// ifElse43
								
							}
						}
					} else {
						// ifElse45
						printf("!! lri_ms: In an undefined state (%d)\n", state_lri_ms__basic_0_0);
					}
				}
			}
			printf("pvarp_elt\n");
			timer_pvarp_elt__basic_0_0 = timer_pvarp_elt__basic_0_0 + 1;
			AS__global_0_0_copy_basic_local.value = absent;
			AS__global_0_0_copy_basic_local.status = FOREC_SHARED_MODIFIED;
			AR__global_0_0_copy_basic_local.value = absent;
			AR__global_0_0_copy_basic_local.status = FOREC_SHARED_MODIFIED;
			A_Block__basic_0_0 = absent;
			if (state_pvarp_elt__basic_0_0 == Init_pvarp_elt) {
				if ((A_Act__global_0_0_copy_basic_local.value == present) || (A_Get__global_0_0_copy_basic_local.value == present)) {
					state_pvarp_elt__basic_0_0 = Init_pvarp_elt;
					AS__global_0_0_copy_basic_local.value = present;
					AS__global_0_0_copy_basic_local.status = FOREC_SHARED_MODIFIED;
				} else {
					// ifElse49
					if ((VS__global_0_0_copy_basic_local.value == present) || (VS__global_0_0_copy_basic_local.value == present)) {
						state_pvarp_elt__basic_0_0 = PVAB;
						timer_pvarp_elt__basic_0_0 = 0;
					} else {
						// ifElse48
						
					}
				}
			} else {
				// ifElse56
				if (state_pvarp_elt__basic_0_0 == PVAB) {
					if ((A_Act__global_0_0_copy_basic_local.value == present) || (A_Get__global_0_0_copy_basic_local.value == present)) {
						state_pvarp_elt__basic_0_0 = PVAB;
						A_Block__basic_0_0 = present;
					} else {
						// ifElse51
						if (timer_pvarp_elt__basic_0_0 >= TPVAB__global_0_0) {
							state_pvarp_elt__basic_0_0 = PVARP;
						} else {
							// ifElse50
							
						}
					}
				} else {
					// ifElse55
					if (state_pvarp_elt__basic_0_0 == PVARP) {
						if ((A_Act__global_0_0_copy_basic_local.value == present) || (A_Get__global_0_0_copy_basic_local.value == present)) {
							state_pvarp_elt__basic_0_0 = PVARP;
							AR__global_0_0_copy_basic_local.value = present;
							AR__global_0_0_copy_basic_local.status = FOREC_SHARED_MODIFIED;
						} else {
							// ifElse53
							if (timer_pvarp_elt__basic_0_0 >= TPVARP__global_0_0_copy_basic_local.value) {
								state_pvarp_elt__basic_0_0 = Init_pvarp_elt;
								TPVARP__global_0_0_copy_basic_local.value = TPVARP_100__global_0_0;
								TPVARP__global_0_0_copy_basic_local.status = FOREC_SHARED_MODIFIED;
							} else {
								// ifElse52
								
							}
						}
					} else {
						// ifElse54
						printf("!! pvarp_elt: In an undefined state (%d)\n", state_pvarp_elt__basic_0_0);
					}
				}
			}
			printf("vrp\n");
			timer_vrp__basic_0_0 = timer_vrp__basic_0_0 + 1;
			VS__global_0_0_copy_basic_local.value = absent;
			VS__global_0_0_copy_basic_local.status = FOREC_SHARED_MODIFIED;
			V_Block__basic_0_0 = absent;
			if (state_vrp__basic_0_0 == Init_vrp) {
				if ((V_Act__global_0_0_copy_basic_local.value == present) || (V_Get__global_0_0_copy_basic_local.value == present)) {
					state_vrp__basic_0_0 = VRP;
					VS__global_0_0_copy_basic_local.value = present;
					VS__global_0_0_copy_basic_local.status = FOREC_SHARED_MODIFIED;
					timer_vrp__basic_0_0 = 0;
				} else {
					// ifElse58
					if (VP__global_0_0_copy_basic_local.value == present) {
						state_vrp__basic_0_0 = VRP;
						timer_vrp__basic_0_0 = 0;
					} else {
						// if57
					}
				}
			} else {
				// ifElse62
				if (state_vrp__basic_0_0 == VRP) {
					if (timer_vrp__basic_0_0 >= TVRP__global_0_0) {
						state_vrp__basic_0_0 = Init_vrp;
					} else {
						// ifElse60
						if ((V_Act__global_0_0_copy_basic_local.value == present) || (V_Get__global_0_0_copy_basic_local.value == present)) {
							state_vrp__basic_0_0 = VRP;
							V_Block__basic_0_0 = present;
						} else {
							// ifElse59
							
						}
					}
				} else {
					// ifElse61
					printf("!! vrp: In an undefined state (%d)\n", state_vrp__basic_0_0);
				}
			}
			VP__global_0_0_copy_basic_local.value = VP_new__basic_0_0;
			VP__global_0_0_copy_basic_local.status = FOREC_SHARED_MODIFIED;

			// pause;
			// Write the local copy of shared variables back to their global copy.

			TPVARP__global_0_0_copy_basic = TPVARP__global_0_0_copy_basic_local;
			AP__global_0_0_copy_basic = AP__global_0_0_copy_basic_local;
			VP__global_0_0_copy_basic = VP__global_0_0_copy_basic_local;
			AS__global_0_0_copy_basic = AS__global_0_0_copy_basic_local;
			AR__global_0_0_copy_basic = AR__global_0_0_copy_basic_local;
			VS__global_0_0_copy_basic = VS__global_0_0_copy_basic_local;			// forec:statement:pause:pause1:start
			basic__thread.programCounter = &&pause1;
			goto *basic__thread.nextThread -> programCounter;
			pause1:;
			// forec:statement:pause:pause1:end
			// Update the values of the used shared variables from their global copy.
			TURI__global_0_0_copy_basic_local = TURI__global_0_0;
			TLRI__global_0_0_copy_basic_local = TLRI__global_0_0;
			TPVARP__global_0_0_copy_basic_local = TPVARP__global_0_0;
			A_Get__global_0_0_copy_basic_local = A_Get__global_0_0;
			A_Act__global_0_0_copy_basic_local = A_Act__global_0_0;
			V_Get__global_0_0_copy_basic_local = V_Get__global_0_0;
			V_Act__global_0_0_copy_basic_local = V_Act__global_0_0;
			AP__global_0_0_copy_basic_local = AP__global_0_0;
			VP__global_0_0_copy_basic_local = VP__global_0_0;
			AS__global_0_0_copy_basic_local = AS__global_0_0;
			VS__global_0_0_copy_basic_local = VS__global_0_0;
			DDD__global_0_0_copy_basic_local = DDD__global_0_0;
			VDI__global_0_0_copy_basic_local = VDI__global_0_0;
			AR__global_0_0_copy_basic_local.status = FOREC_SHARED_UNMODIFIED;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		TPVARP__global_0_0_copy_basic = TPVARP__global_0_0_copy_basic_local;
		AP__global_0_0_copy_basic = AP__global_0_0_copy_basic_local;
		VP__global_0_0_copy_basic = VP__global_0_0_copy_basic_local;
		AS__global_0_0_copy_basic = AS__global_0_0_copy_basic_local;
		AR__global_0_0_copy_basic = AR__global_0_0_copy_basic_local;
		VS__global_0_0_copy_basic = VS__global_0_0_copy_basic_local;

		// forec:scheduler:threadRemove:basic:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		basic__thread.nextThread -> prevThread = basic__thread.prevThread;
		basic__thread.prevThread -> nextThread = basic__thread.nextThread;
		goto *basic__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:basic:end
	} // basic__thread
	// forec:thread:basic:end

	// forec:thread:communication:start
	/*--------------------------------------------------------------
	| Thread communication
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	enum Code__communication_0_0 {
		Nothing = 0,
		Acknowledge,
		Complete,
		Receive,
		Send
	};

	unsigned int state_rf__communication_0_0;
	unsigned int subState__communication_0_0;
	unsigned int data__communication_0_0;
	Log__global_0_0 logCopy__communication_0_0;
	int i__communication_0_0;
	unsigned int state_rf__communication_1_0;
	unsigned int subState__communication_1_0;
	unsigned int data__communication_1_0;
	Shared_parameters__global_0_0 parameters__global_0_0_copy_communication_local;
	Shared_log__global_0_0 log__global_0_0_copy_communication_local;

	// Thread body -------------------------------------------------
	communication__thread: {
		// Initialise the local copies of shared variables.
		log__global_0_0_copy_communication_local.value = log__global_0_0_copy_main.value;
		log__global_0_0_copy_communication_local.status = FOREC_SHARED_UNMODIFIED;
		parameters__global_0_0_copy_communication_local.value = parameters__global_0_0.value;
		parameters__global_0_0_copy_communication_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		state_rf__communication_0_0 = 0;
		subState__communication_0_0 = 0;
		data__communication_0_0 = 0;
		i__communication_0_0 = 0;

		while (1) {
			printf("communication\n");
			icrc(0, 40, (short)0, 1);
			state_rf__communication_1_0 = (rfIn__global_0_0 >> 30);
			subState__communication_1_0 = (rfIn__global_0_0 >> 28) & 0x03;
			data__communication_1_0 = (rfIn__global_0_0 & 0x0FFF);
			if (state_rf__communication_1_0 == Receive) {
				rfOut__global_0_0 = Acknowledge;
				if (subState__communication_1_0 == 0) {
					parameters__global_0_0_copy_communication_local.value.baseRate = data__communication_1_0;
					parameters__global_0_0_copy_communication_local.status = FOREC_SHARED_MODIFIED;
				} else {
					// ifElse143
					if (subState__communication_1_0 == 1) {
						parameters__global_0_0_copy_communication_local.value.operationalMode = data__communication_1_0;
						parameters__global_0_0_copy_communication_local.status = FOREC_SHARED_MODIFIED;
					} else {
						// ifElse142
						if (subState__communication_1_0 == 2) {
							parameters__global_0_0_copy_communication_local.value.ekgSensitivity = data__communication_1_0;
							parameters__global_0_0_copy_communication_local.status = FOREC_SHARED_MODIFIED;
						} else {
							// ifElse141
							if (subState__communication_1_0 == 3) {
								parameters__global_0_0_copy_communication_local.value.paceVoltage = data__communication_1_0;
								parameters__global_0_0_copy_communication_local.status = FOREC_SHARED_MODIFIED;
							} else {
								// ifElse140
								if (subState__communication_1_0 == 4) {
									parameters__global_0_0_copy_communication_local.value.sensitivityThreshold = data__communication_1_0;
									parameters__global_0_0_copy_communication_local.status = FOREC_SHARED_MODIFIED;
								} else {
									// ifElse139
									if (subState__communication_1_0 == 5) {
										parameters__global_0_0_copy_communication_local.value.maxRate = data__communication_1_0;
										parameters__global_0_0_copy_communication_local.status = FOREC_SHARED_MODIFIED;
									} else {
										// ifElse138
										if (subState__communication_1_0 == 6) {
											parameters__global_0_0_copy_communication_local.value.minRate = data__communication_1_0;
											parameters__global_0_0_copy_communication_local.status = FOREC_SHARED_MODIFIED;
										} else {
											// ifElse137
											if (subState__communication_1_0 == 7) {
												parameters__global_0_0_copy_communication_local.value.maxAttackSlope = data__communication_1_0;
												parameters__global_0_0_copy_communication_local.status = FOREC_SHARED_MODIFIED;
											} else {
												// ifElse136
												if (subState__communication_1_0 == 8) {
													parameters__global_0_0_copy_communication_local.value.maxDecaySlope = data__communication_1_0;
													parameters__global_0_0_copy_communication_local.status = FOREC_SHARED_MODIFIED;
												} else {
													// ifElse135
													
												}
											}
										}
									}
								}
							}
						}
					}
				}
			} else {
				// ifElse156
				if (state_rf__communication_1_0 == Send) {
					if (i__communication_0_0 == 0) {
						logCopy__communication_0_0 = log__global_0_0_copy_communication_local.value;
					} else {
						// if144
					}
					if (i__communication_0_0 < logCopy__communication_0_0.size) {
						if (subState__communication_1_0 == 0) {
							rfOut__global_0_0 = logCopy__communication_0_0.events[i__communication_0_0].AP;
						} else {
							// ifElse153
							if (subState__communication_1_0 == 1) {
								rfOut__global_0_0 = logCopy__communication_0_0.events[i__communication_0_0].VP;
							} else {
								// ifElse152
								if (subState__communication_1_0 == 2) {
									rfOut__global_0_0 = logCopy__communication_0_0.events[i__communication_0_0].DDD;
								} else {
									// ifElse151
									if (subState__communication_1_0 == 3) {
										rfOut__global_0_0 = logCopy__communication_0_0.events[i__communication_0_0].VDI;
									} else {
										// ifElse150
										if (subState__communication_1_0 == 4) {
											rfOut__global_0_0 = logCopy__communication_0_0.events[i__communication_0_0].lrl;
										} else {
											// ifElse149
											if (subState__communication_1_0 == 5) {
												rfOut__global_0_0 = logCopy__communication_0_0.events[i__communication_0_0].url;
											} else {
												// ifElse148
												if (subState__communication_1_0 == 6) {
													rfOut__global_0_0 = logCopy__communication_0_0.events[i__communication_0_0].pmt;
												} else {
													// ifElse147
													if (subState__communication_1_0 == 7) {
														rfOut__global_0_0 = logCopy__communication_0_0.events[i__communication_0_0].vurl;
													} else {
														// ifElse146
														if (subState__communication_1_0 == 8) {
															rfOut__global_0_0 = logCopy__communication_0_0.events[i__communication_0_0].elt;
														} else {
															// ifElse145
															i__communication_0_0 = i__communication_0_0 + 1;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					} else {
						// ifElse154
						rfOut__global_0_0 = Complete;
						i__communication_0_0 = 0;
					}
				} else {
					// ifElse155
					
				}
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.

			parameters__global_0_0 = parameters__global_0_0_copy_communication_local;			// forec:statement:pause:pause7:start
			communication__thread.programCounter = &&pause7;
			goto *communication__thread.nextThread -> programCounter;
			pause7:;
			// forec:statement:pause:pause7:end
			// Update the values of the used shared variables from their global copy.
			log__global_0_0_copy_communication_local = log__global_0_0;
			parameters__global_0_0_copy_communication_local.status = FOREC_SHARED_UNMODIFIED;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		parameters__global_0_0.value = parameters__global_0_0_copy_communication_local.value;

		// forec:scheduler:threadRemove:communication:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		communication__thread.nextThread -> prevThread = communication__thread.prevThread;
		communication__thread.prevThread -> nextThread = communication__thread.nextThread;
		goto *communication__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:communication:end
	} // communication__thread
	// forec:thread:communication:end

	// forec:thread:ekgSensing:start
	/*--------------------------------------------------------------
	| Thread ekgSensing
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	enum {
		Init_conduction = 0,
		Ante,
		Retro
	} state_conduction__ekgSensing_0_0;

	unsigned int timer_rhm_a__ekgSensing_0_0;
	unsigned int timer_rhm_v__ekgSensing_0_0;
	unsigned int timer_conduction__ekgSensing_0_0;
	Shared_A_Get__global_0_0 A_Get__global_0_0_copy_ekgSensing_local;
	Shared_A_Act__global_0_0 A_Act__global_0_0_copy_ekgSensing_local;
	Shared_V_Get__global_0_0 V_Get__global_0_0_copy_ekgSensing_local;
	Shared_V_Act__global_0_0 V_Act__global_0_0_copy_ekgSensing_local;
	Shared_AP__global_0_0 AP__global_0_0_copy_ekgSensing_local;
	Shared_VP__global_0_0 VP__global_0_0_copy_ekgSensing_local;

	// Thread body -------------------------------------------------
	ekgSensing__thread: {
		// Initialise the local copies of shared variables.
		A_Get__global_0_0_copy_ekgSensing_local.value = A_Get__global_0_0_copy_main.value;
		A_Get__global_0_0_copy_ekgSensing_local.status = FOREC_SHARED_UNMODIFIED;
		A_Act__global_0_0_copy_ekgSensing_local.value = A_Act__global_0_0_copy_main.value;
		A_Act__global_0_0_copy_ekgSensing_local.status = FOREC_SHARED_UNMODIFIED;
		V_Get__global_0_0_copy_ekgSensing_local.value = V_Get__global_0_0_copy_main.value;
		V_Get__global_0_0_copy_ekgSensing_local.status = FOREC_SHARED_UNMODIFIED;
		V_Act__global_0_0_copy_ekgSensing_local.value = V_Act__global_0_0_copy_main.value;
		V_Act__global_0_0_copy_ekgSensing_local.status = FOREC_SHARED_UNMODIFIED;
		AP__global_0_0_copy_ekgSensing_local.value = AP__global_0_0_copy_main.value;
		AP__global_0_0_copy_ekgSensing_local.status = FOREC_SHARED_UNMODIFIED;
		VP__global_0_0_copy_ekgSensing_local.value = VP__global_0_0_copy_main.value;
		VP__global_0_0_copy_ekgSensing_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		state_conduction__ekgSensing_0_0 = Init_conduction;
		timer_rhm_a__ekgSensing_0_0 = 0;
		timer_rhm_v__ekgSensing_0_0 = 0;
		timer_conduction__ekgSensing_0_0 = 0;

		while (1) {
			printf("rhm_a\n");
			timer_rhm_a__ekgSensing_0_0 = timer_rhm_a__ekgSensing_0_0 + 1;
			if ((A_Act__global_0_0_copy_ekgSensing_local.value == present) || (AP__global_0_0_copy_ekgSensing_local.value == present)) {
				timer_rhm_a__ekgSensing_0_0 = 0;
			} else {
				// ifElse2
				if (timer_rhm_a__ekgSensing_0_0 > Aminwait__global_0_0) {
					A_Get__global_0_0_copy_ekgSensing_local.value = present;
					A_Get__global_0_0_copy_ekgSensing_local.status = FOREC_SHARED_MODIFIED;
				} else {
					// ifElse1
					
				}
			}
			printf("rhm_v\n");
			timer_rhm_v__ekgSensing_0_0 = timer_rhm_v__ekgSensing_0_0 + 1;
			if ((V_Act__global_0_0_copy_ekgSensing_local.value == present) || (VP__global_0_0_copy_ekgSensing_local.value == present)) {
				timer_rhm_v__ekgSensing_0_0 = 0;
			} else {
				// ifElse4
				if (timer_rhm_v__ekgSensing_0_0 > Vminwait__global_0_0) {
					V_Get__global_0_0_copy_ekgSensing_local.value = present;
					V_Get__global_0_0_copy_ekgSensing_local.status = FOREC_SHARED_MODIFIED;
				} else {
					// ifElse3
					
				}
			}
			printf("conduction\n");
			timer_conduction__ekgSensing_0_0 = timer_conduction__ekgSensing_0_0 + 1;
			if (state_conduction__ekgSensing_0_0 == Init_conduction) {
				if ((A_Get__global_0_0_copy_ekgSensing_local.value == present) || (AP__global_0_0_copy_ekgSensing_local.value == present)) {
					state_conduction__ekgSensing_0_0 = Ante;
					timer_conduction__ekgSensing_0_0 = 0;
				} else {
					// ifElse7
					if ((V_Get__global_0_0_copy_ekgSensing_local.value == present) || (VP__global_0_0_copy_ekgSensing_local.value == present)) {
						state_conduction__ekgSensing_0_0 = Retro;
						timer_conduction__ekgSensing_0_0 = 0;
					} else {
						// ifElse6
						if ((A_Get__global_0_0_copy_ekgSensing_local.value == present) || (AP__global_0_0_copy_ekgSensing_local.value == present) || (V_Get__global_0_0_copy_ekgSensing_local.value == present) || (VP__global_0_0_copy_ekgSensing_local.value == present)) {
							state_conduction__ekgSensing_0_0 = Init_conduction;
						} else {
							// ifElse5
							
						}
					}
				}
			} else {
				// ifElse14
				if (state_conduction__ekgSensing_0_0 == Ante) {
					if ((V_Get__global_0_0_copy_ekgSensing_local.value == present) || (VP__global_0_0_copy_ekgSensing_local.value == present)) {
						state_conduction__ekgSensing_0_0 = Init_conduction;
					} else {
						// ifElse9
						if (timer_conduction__ekgSensing_0_0 >= Tantemin__global_0_0) {
							state_conduction__ekgSensing_0_0 = Init_conduction;
							V_Act__global_0_0_copy_ekgSensing_local.value = present;
							V_Act__global_0_0_copy_ekgSensing_local.status = FOREC_SHARED_MODIFIED;
						} else {
							// ifElse8
							
						}
					}
				} else {
					// ifElse13
					if (state_conduction__ekgSensing_0_0 == Retro) {
						if ((A_Get__global_0_0_copy_ekgSensing_local.value == present) || (AP__global_0_0_copy_ekgSensing_local.value == present)) {
							state_conduction__ekgSensing_0_0 = Init_conduction;
						} else {
							// ifElse11
							if (timer_conduction__ekgSensing_0_0 >= Tretromin__global_0_0) {
								state_conduction__ekgSensing_0_0 = Init_conduction;
								A_Act__global_0_0_copy_ekgSensing_local.value = present;
								A_Act__global_0_0_copy_ekgSensing_local.status = FOREC_SHARED_MODIFIED;
							} else {
								// ifElse10
								
							}
						}
					} else {
						// ifElse12
						printf("!! conduction: In an undefined state (%d)\n", state_conduction__ekgSensing_0_0);
					}
				}
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.

			A_Get__global_0_0_copy_ekgSensing = A_Get__global_0_0_copy_ekgSensing_local;
			A_Act__global_0_0_copy_ekgSensing = A_Act__global_0_0_copy_ekgSensing_local;
			V_Get__global_0_0_copy_ekgSensing = V_Get__global_0_0_copy_ekgSensing_local;
			V_Act__global_0_0_copy_ekgSensing = V_Act__global_0_0_copy_ekgSensing_local;			// forec:statement:pause:pause0:start
			ekgSensing__thread.programCounter = &&pause0;
			goto *ekgSensing__thread.nextThread -> programCounter;
			pause0:;
			// forec:statement:pause:pause0:end
			// Update the values of the used shared variables from their global copy.
			A_Get__global_0_0_copy_ekgSensing_local = A_Get__global_0_0;
			A_Act__global_0_0_copy_ekgSensing_local = A_Act__global_0_0;
			V_Get__global_0_0_copy_ekgSensing_local = V_Get__global_0_0;
			V_Act__global_0_0_copy_ekgSensing_local = V_Act__global_0_0;
			AP__global_0_0_copy_ekgSensing_local = AP__global_0_0;
			VP__global_0_0_copy_ekgSensing_local = VP__global_0_0;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		A_Get__global_0_0_copy_ekgSensing = A_Get__global_0_0_copy_ekgSensing_local;
		A_Act__global_0_0_copy_ekgSensing = A_Act__global_0_0_copy_ekgSensing_local;
		V_Get__global_0_0_copy_ekgSensing = V_Get__global_0_0_copy_ekgSensing_local;
		V_Act__global_0_0_copy_ekgSensing = V_Act__global_0_0_copy_ekgSensing_local;

		// forec:scheduler:threadRemove:ekgSensing:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		ekgSensing__thread.nextThread -> prevThread = ekgSensing__thread.prevThread;
		ekgSensing__thread.prevThread -> nextThread = ekgSensing__thread.nextThread;
		goto *ekgSensing__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:ekgSensing:end
	} // ekgSensing__thread
	// forec:thread:ekgSensing:end

	// forec:thread:logging:start
	/*--------------------------------------------------------------
	| Thread logging
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	enum {
		Init_lrl = 0,
		Wait_lrl
	} state_lrl__logging_0_0;

	enum {
		Init_url = 0,
		Wait_url
	} state_url__logging_0_0;

	enum {
		Init_pmt = 0,
		Wait_pmt,
		Error_pmt
	} state_pmt__logging_0_0;

	enum {
		Init_vurl = 0,
		V_vurl,
		Error_vurl
	} state_vurl__logging_0_0;

	enum {
		Init_elt = 0,
		AS_elt,
		VP_elt,
		Error_elt
	} state_elt__logging_0_0;

	unsigned int timer_lrl__logging_0_0;
	unsigned int timer_url__logging_0_0;
	unsigned int timer_pmt__logging_0_0;
	unsigned int timer_vurl__logging_0_0;
	Signal__global_0_0 violated__logging_0_0;
	Event__global_0_0 event__logging_0_0;
	Shared_TURI__global_0_0 TURI__global_0_0_copy_logging_local;
	Shared_TLRI__global_0_0 TLRI__global_0_0_copy_logging_local;
	Shared_AP__global_0_0 AP__global_0_0_copy_logging_local;
	Shared_VP__global_0_0 VP__global_0_0_copy_logging_local;
	Shared_AS__global_0_0 AS__global_0_0_copy_logging_local;
	Shared_AR__global_0_0 AR__global_0_0_copy_logging_local;
	Shared_VS__global_0_0 VS__global_0_0_copy_logging_local;
	Shared_DDD__global_0_0 DDD__global_0_0_copy_logging_local;
	Shared_VDI__global_0_0 VDI__global_0_0_copy_logging_local;
	Shared_log__global_0_0 log__global_0_0_copy_logging_local;

	// Thread body -------------------------------------------------
	logging__thread: {
		// Initialise the local copies of shared variables.
		TURI__global_0_0_copy_logging_local.value = TURI__global_0_0.value;
		TURI__global_0_0_copy_logging_local.status = FOREC_SHARED_UNMODIFIED;
		TLRI__global_0_0_copy_logging_local.value = TLRI__global_0_0.value;
		TLRI__global_0_0_copy_logging_local.status = FOREC_SHARED_UNMODIFIED;
		AP__global_0_0_copy_logging_local.value = AP__global_0_0_copy_main.value;
		AP__global_0_0_copy_logging_local.status = FOREC_SHARED_UNMODIFIED;
		VP__global_0_0_copy_logging_local.value = VP__global_0_0_copy_main.value;
		VP__global_0_0_copy_logging_local.status = FOREC_SHARED_UNMODIFIED;
		AS__global_0_0_copy_logging_local.value = AS__global_0_0_copy_main.value;
		AS__global_0_0_copy_logging_local.status = FOREC_SHARED_UNMODIFIED;
		AR__global_0_0_copy_logging_local.value = AR__global_0_0_copy_main.value;
		AR__global_0_0_copy_logging_local.status = FOREC_SHARED_UNMODIFIED;
		VS__global_0_0_copy_logging_local.value = VS__global_0_0_copy_main.value;
		VS__global_0_0_copy_logging_local.status = FOREC_SHARED_UNMODIFIED;
		DDD__global_0_0_copy_logging_local.value = DDD__global_0_0_copy_main.value;
		DDD__global_0_0_copy_logging_local.status = FOREC_SHARED_UNMODIFIED;
		VDI__global_0_0_copy_logging_local.value = VDI__global_0_0_copy_main.value;
		VDI__global_0_0_copy_logging_local.status = FOREC_SHARED_UNMODIFIED;
		log__global_0_0_copy_logging_local.value = log__global_0_0_copy_main.value;
		log__global_0_0_copy_logging_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		state_lrl__logging_0_0 = Init_lrl;
		state_url__logging_0_0 = Init_url;
		state_pmt__logging_0_0 = Init_pmt;
		state_vurl__logging_0_0 = Init_vurl;
		state_elt__logging_0_0 = Init_elt;
		timer_lrl__logging_0_0 = 0;
		timer_url__logging_0_0 = 0;
		timer_pmt__logging_0_0 = 0;
		timer_vurl__logging_0_0 = 0;
		violated__logging_0_0 = absent;

		while (1) {
			violated__logging_0_0 = absent;
			event__logging_0_0.timestamp = 0;
			event__logging_0_0.AP = absent;
			event__logging_0_0.VP = absent;
			event__logging_0_0.DDD = absent;
			event__logging_0_0.VDI = absent;
			event__logging_0_0.lrl = absent;
			event__logging_0_0.url = absent;
			event__logging_0_0.pmt = absent;
			event__logging_0_0.vurl = absent;
			event__logging_0_0.elt = absent;
			printf("lrl\n");
			timer_lrl__logging_0_0 = timer_lrl__logging_0_0 + 1;
			if (state_lrl__logging_0_0 == Init_lrl) {
				if ((VS__global_0_0_copy_logging_local.value == present) || (VP__global_0_0_copy_logging_local.value == present)) {
					state_lrl__logging_0_0 = Wait_lrl;
					timer_lrl__logging_0_0 = 0;
				} else {
					// ifElse100
					
				}
			} else {
				// ifElse104
				if (state_lrl__logging_0_0 == Wait_lrl) {
					if ((VS__global_0_0_copy_logging_local.value == present) || (VP__global_0_0_copy_logging_local.value == present)) {
						state_lrl__logging_0_0 = Wait_lrl;
						if (timer_lrl__logging_0_0 > TLRI__global_0_0_copy_logging_local.value) {
							violated__logging_0_0 = present;
							event__logging_0_0.lrl = present;
						} else {
							// if101
						}
						timer_lrl__logging_0_0 = 0;
					} else {
						// ifElse102
						
					}
				} else {
					// ifElse103
					printf("!! lrl: In an undefined state (%d)\n", state_lrl__logging_0_0);
				}
			}
			printf("url\n");
			timer_url__logging_0_0 = timer_url__logging_0_0 + 1;
			if (state_url__logging_0_0 == Init_url) {
				if ((VS__global_0_0_copy_logging_local.value == present) || (VP__global_0_0_copy_logging_local.value == present)) {
					state_url__logging_0_0 = Wait_url;
					timer_url__logging_0_0 = 0;
				} else {
					// ifElse105
					
				}
			} else {
				// ifElse110
				if (state_url__logging_0_0 == Wait_url) {
					if (VS__global_0_0_copy_logging_local.value == present) {
						state_url__logging_0_0 = Wait_url;
						timer_url__logging_0_0 = 0;
					} else {
						// ifElse108
						if (VP__global_0_0_copy_logging_local.value == present) {
							state_url__logging_0_0 = Wait_url;
							if (timer_url__logging_0_0 < TLRI__global_0_0_copy_logging_local.value) {
								violated__logging_0_0 = present;
								event__logging_0_0.url = present;
							} else {
								// if106
							}
							timer_url__logging_0_0 = 0;
						} else {
							// ifElse107
							
						}
					}
				} else {
					// ifElse109
					printf("!! url: In an undefined state (%d)\n", state_url__logging_0_0);
				}
			}
			printf("pmt\n");
			timer_pmt__logging_0_0 = timer_pmt__logging_0_0 + 1;
			if (state_pmt__logging_0_0 == Init_pmt) {
				if ((VS__global_0_0_copy_logging_local.value == present) || (VP__global_0_0_copy_logging_local.value == present)) {
					state_pmt__logging_0_0 = Wait_pmt;
					timer_pmt__logging_0_0 = 0;
				} else {
					// ifElse111
					
				}
			} else {
				// ifElse115
				if (state_pmt__logging_0_0 == Wait_pmt) {
					if ((VS__global_0_0_copy_logging_local.value == present) || (VP__global_0_0_copy_logging_local.value == present)) {
						state_pmt__logging_0_0 = Wait_pmt;
						if (timer_pmt__logging_0_0 > TLRI__global_0_0_copy_logging_local.value) {
							violated__logging_0_0 = present;
							event__logging_0_0.pmt = present;
						} else {
							// if112
						}
						timer_pmt__logging_0_0 = 0;
					} else {
						// ifElse113
						
					}
				} else {
					// ifElse114
					printf("!! pmt: In an undefined state (%d)\n", state_pmt__logging_0_0);
				}
			}
			printf("ms\n");
			if (VDI__global_0_0_copy_logging_local.value == present) {
				violated__logging_0_0 = present;
			} else {
				// ifElse116
				
			}
			printf("vurl\n");
			timer_vurl__logging_0_0 = timer_vurl__logging_0_0 + 1;
			if (state_vurl__logging_0_0 == Init_vurl) {
				if (VP__global_0_0_copy_logging_local.value == present) {
					state_vurl__logging_0_0 = V_vurl;
					timer_vurl__logging_0_0 = 0;
				} else {
					// ifElse117
					
				}
			} else {
				// ifElse122
				if (state_vurl__logging_0_0 == V_vurl) {
					if (VP__global_0_0_copy_logging_local.value == present) {
						if (timer_vurl__logging_0_0 <= TURI__global_0_0_copy_logging_local.value) {
							state_vurl__logging_0_0 = V_vurl;
						} else {
							// ifElse118
							state_vurl__logging_0_0 = Error_vurl;
							violated__logging_0_0 = present;
							event__logging_0_0.vurl = present;
						}
						timer_vurl__logging_0_0 = 0;
					} else {
						// ifElse119
						
					}
				} else {
					// ifElse121
					if (state_vurl__logging_0_0 == Error_vurl) {
						state_vurl__logging_0_0 = Error_vurl;
						violated__logging_0_0 = present;
						event__logging_0_0.vurl = present;
						timer_vurl__logging_0_0 = 0;
					} else {
						// ifElse120
						printf("!! vurl: In an undefined state (%d)\n", state_vurl__logging_0_0);
					}
				}
			}
			printf("elt\n");
			if (state_elt__logging_0_0 == Init_elt) {
				if (AS__global_0_0_copy_logging_local.value == present) {
					state_elt__logging_0_0 = AS_elt;
				} else {
					// ifElse125
					if ((AP__global_0_0_copy_logging_local.value == present) || (AR__global_0_0_copy_logging_local.value == present)) {
						state_elt__logging_0_0 = Error_elt;
					} else {
						// ifElse124
						if (VP__global_0_0_copy_logging_local.value == present) {
							state_elt__logging_0_0 = VP_elt;
						} else {
							// ifElse123
							
						}
					}
				}
			} else {
				// ifElse133
				if (state_elt__logging_0_0 == AS_elt) {
					if ((AS__global_0_0_copy_logging_local.value == present) || (AP__global_0_0_copy_logging_local.value == present) || (AR__global_0_0_copy_logging_local.value == present) || (VS__global_0_0_copy_logging_local.value == present)) {
						state_elt__logging_0_0 = Error_elt;
					} else {
						// ifElse127
						if (VP__global_0_0_copy_logging_local.value == present) {
							state_elt__logging_0_0 = VP_elt;
						} else {
							// ifElse126
							
						}
					}
				} else {
					// ifElse132
					if (state_elt__logging_0_0 == VP_elt) {
						if ((VS__global_0_0_copy_logging_local.value == present) || (VP__global_0_0_copy_logging_local.value == present) || (AP__global_0_0_copy_logging_local.value == present) || (AR__global_0_0_copy_logging_local.value == present)) {
							state_elt__logging_0_0 = Error_elt;
						} else {
							// ifElse129
							if (AS__global_0_0_copy_logging_local.value == present) {
								state_elt__logging_0_0 = AS_elt;
							} else {
								// ifElse128
								
							}
						}
					} else {
						// ifElse131
						if (state_elt__logging_0_0 == Error_elt) {
							state_elt__logging_0_0 = Error_elt;
							violated__logging_0_0 = present;
							event__logging_0_0.elt = present;
						} else {
							// ifElse130
							printf("!! elt: In an undefined state (%d)\n", state_elt__logging_0_0);
						}
					}
				}
			}
			if (violated__logging_0_0 == present) {
				event__logging_0_0.AP = AP__global_0_0_copy_logging_local.value;
				event__logging_0_0.VP = VP__global_0_0_copy_logging_local.value;
				event__logging_0_0.DDD = DDD__global_0_0_copy_logging_local.value;
				event__logging_0_0.VDI = VDI__global_0_0_copy_logging_local.value;
				log__global_0_0_copy_logging_local.value.events[log__global_0_0_copy_logging_local.value.tail] = event__logging_0_0;
				log__global_0_0_copy_logging_local.status = FOREC_SHARED_MODIFIED;
				log__global_0_0_copy_logging_local.value.tail = (log__global_0_0_copy_logging_local.value.tail + 1)%log__global_0_0_copy_logging_local.value.size;
				log__global_0_0_copy_logging_local.status = FOREC_SHARED_MODIFIED;
			} else {
				// if134
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.

			log__global_0_0_copy_logging = log__global_0_0_copy_logging_local;			// forec:statement:pause:pause6:start
			logging__thread.programCounter = &&pause6;
			goto *logging__thread.nextThread -> programCounter;
			pause6:;
			// forec:statement:pause:pause6:end
			// Update the values of the used shared variables from their global copy.
			TURI__global_0_0_copy_logging_local = TURI__global_0_0;
			TLRI__global_0_0_copy_logging_local = TLRI__global_0_0;
			AP__global_0_0_copy_logging_local = AP__global_0_0;
			VP__global_0_0_copy_logging_local = VP__global_0_0;
			AS__global_0_0_copy_logging_local = AS__global_0_0;
			AR__global_0_0_copy_logging_local = AR__global_0_0;
			VS__global_0_0_copy_logging_local = VS__global_0_0;
			DDD__global_0_0_copy_logging_local = DDD__global_0_0;
			VDI__global_0_0_copy_logging_local = VDI__global_0_0;
			log__global_0_0_copy_logging_local = log__global_0_0;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		log__global_0_0_copy_logging = log__global_0_0_copy_logging_local;

		// forec:scheduler:threadRemove:logging:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		logging__thread.nextThread -> prevThread = logging__thread.prevThread;
		logging__thread.prevThread -> nextThread = logging__thread.nextThread;
		goto *logging__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:logging:end
	} // logging__thread
	// forec:thread:logging:end

	// forec:thread:modeSwitch:start
	/*--------------------------------------------------------------
	| Thread modeSwitch
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	enum {
		Init_interval_ms = 0,
		Wait
	} state_interval_ms__modeSwitch_0_0;

	enum State__modeSwitch_0_0 {
		Init_counter_ms = 0,
		Fast1,
		Fast2,
		Fast3,
		Fast4,
		Fast5,
		Fast6,
		Fast7,
		Fast8
	} state_counter_ms__modeSwitch_0_0;

	enum {
		Init_duration_ms = 0,
		V1,
		V2,
		V3,
		V4,
		V5,
		V6,
		V7,
		V8,
		V9
	} state_duration_ms__modeSwitch_0_0;

	unsigned int timer_interval_ms__modeSwitch_0_0;
	Signal__global_0_0 Fast__modeSwitch_0_0;
	Signal__global_0_0 Slow__modeSwitch_0_0;
	Signal__global_0_0 D_Beg__modeSwitch_0_0;
	Signal__global_0_0 D_Beg_new__modeSwitch_0_0;
	Signal__global_0_0 D_End__modeSwitch_0_0;
	Shared_AP__global_0_0 AP__global_0_0_copy_modeSwitch_local;
	Shared_VP__global_0_0 VP__global_0_0_copy_modeSwitch_local;
	Shared_AS__global_0_0 AS__global_0_0_copy_modeSwitch_local;
	Shared_AR__global_0_0 AR__global_0_0_copy_modeSwitch_local;
	Shared_VS__global_0_0 VS__global_0_0_copy_modeSwitch_local;
	Shared_DDD__global_0_0 DDD__global_0_0_copy_modeSwitch_local;
	Shared_VDI__global_0_0 VDI__global_0_0_copy_modeSwitch_local;

	// Thread body -------------------------------------------------
	modeSwitch__thread: {
		// Initialise the local copies of shared variables.
		AP__global_0_0_copy_modeSwitch_local.value = AP__global_0_0_copy_main.value;
		AP__global_0_0_copy_modeSwitch_local.status = FOREC_SHARED_UNMODIFIED;
		VP__global_0_0_copy_modeSwitch_local.value = VP__global_0_0_copy_main.value;
		VP__global_0_0_copy_modeSwitch_local.status = FOREC_SHARED_UNMODIFIED;
		AS__global_0_0_copy_modeSwitch_local.value = AS__global_0_0_copy_main.value;
		AS__global_0_0_copy_modeSwitch_local.status = FOREC_SHARED_UNMODIFIED;
		AR__global_0_0_copy_modeSwitch_local.value = AR__global_0_0_copy_main.value;
		AR__global_0_0_copy_modeSwitch_local.status = FOREC_SHARED_UNMODIFIED;
		VS__global_0_0_copy_modeSwitch_local.value = VS__global_0_0_copy_main.value;
		VS__global_0_0_copy_modeSwitch_local.status = FOREC_SHARED_UNMODIFIED;
		DDD__global_0_0_copy_modeSwitch_local.value = DDD__global_0_0.value;
		DDD__global_0_0_copy_modeSwitch_local.status = FOREC_SHARED_UNMODIFIED;
		VDI__global_0_0_copy_modeSwitch_local.value = VDI__global_0_0.value;
		VDI__global_0_0_copy_modeSwitch_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		state_interval_ms__modeSwitch_0_0 = Init_interval_ms;
		state_counter_ms__modeSwitch_0_0 = Init_counter_ms;
		state_duration_ms__modeSwitch_0_0 = Init_duration_ms;
		timer_interval_ms__modeSwitch_0_0 = 0;
		Fast__modeSwitch_0_0 = absent;
		Slow__modeSwitch_0_0 = absent;
		D_Beg__modeSwitch_0_0 = absent;
		D_Beg_new__modeSwitch_0_0 = absent;
		D_End__modeSwitch_0_0 = absent;

		while (1) {
			printf("counter_ms\n");
			DDD__global_0_0_copy_modeSwitch_local.value = absent;
			DDD__global_0_0_copy_modeSwitch_local.status = FOREC_SHARED_MODIFIED;
			VDI__global_0_0_copy_modeSwitch_local.value = absent;
			VDI__global_0_0_copy_modeSwitch_local.status = FOREC_SHARED_MODIFIED;
			D_Beg_new__modeSwitch_0_0 = absent;
			if (state_counter_ms__modeSwitch_0_0 == Init_counter_ms) {
				if (Fast__modeSwitch_0_0 == present) {
					state_counter_ms__modeSwitch_0_0 = Fast1;
				} else {
					// ifElse63
					
				}
			} else {
				// ifElse75
				if (state_counter_ms__modeSwitch_0_0 == Fast1) {
					if (Slow__modeSwitch_0_0 == present) {
						state_counter_ms__modeSwitch_0_0 = Init_counter_ms;
						DDD__global_0_0_copy_modeSwitch_local.value = present;
						DDD__global_0_0_copy_modeSwitch_local.status = FOREC_SHARED_MODIFIED;
					} else {
						// ifElse66
						if (Fast__modeSwitch_0_0 == present) {
							state_counter_ms__modeSwitch_0_0 = Fast2;
						} else {
							// ifElse65
							if (D_End__modeSwitch_0_0 == present) {
								state_counter_ms__modeSwitch_0_0 = Fast1;
								VDI__global_0_0_copy_modeSwitch_local.value = present;
								VDI__global_0_0_copy_modeSwitch_local.status = FOREC_SHARED_MODIFIED;
							} else {
								// ifElse64
								
							}
						}
					}
				} else {
					// ifElse74
					if (state_counter_ms__modeSwitch_0_0 == Fast8) {
						if (Slow__modeSwitch_0_0 == present) {
							state_counter_ms__modeSwitch_0_0 = Fast7;
						} else {
							// ifElse68
							if (D_End__modeSwitch_0_0 == present) {
								state_counter_ms__modeSwitch_0_0 = Fast8;
								VDI__global_0_0_copy_modeSwitch_local.value = present;
								VDI__global_0_0_copy_modeSwitch_local.status = FOREC_SHARED_MODIFIED;
							} else {
								// ifElse67
								
							}
						}
					} else {
						// ifElse73
						if (Slow__modeSwitch_0_0 == present) {
							state_counter_ms__modeSwitch_0_0 = state_counter_ms__modeSwitch_0_0 - 1;
						} else {
							// ifElse72
							if (Fast__modeSwitch_0_0 == present) {
								if (state_counter_ms__modeSwitch_0_0 == Fast7) {
									D_Beg_new__modeSwitch_0_0 = present;
								} else {
									// if69
								}
								state_counter_ms__modeSwitch_0_0 = state_counter_ms__modeSwitch_0_0 + 1;
							} else {
								// ifElse71
								if (D_End__modeSwitch_0_0 == present) {
									state_counter_ms__modeSwitch_0_0 = state_counter_ms__modeSwitch_0_0 + 0;
									VDI__global_0_0_copy_modeSwitch_local.value = present;
									VDI__global_0_0_copy_modeSwitch_local.status = FOREC_SHARED_MODIFIED;
								} else {
									// ifElse70
									
								}
							}
						}
					}
				}
			}
			printf("duration_ms\n");
			D_End__modeSwitch_0_0 = absent;
			if (state_duration_ms__modeSwitch_0_0 == Init_duration_ms) {
				if (D_Beg__modeSwitch_0_0 == present) {
					state_duration_ms__modeSwitch_0_0 = V1;
				} else {
					// ifElse76
					
				}
			} else {
				// ifElse79
				if ((VS__global_0_0_copy_modeSwitch_local.value == present) || (VP__global_0_0_copy_modeSwitch_local.value == present)) {
					state_duration_ms__modeSwitch_0_0 = state_duration_ms__modeSwitch_0_0 + 1;
					if (state_duration_ms__modeSwitch_0_0 == V9) {
						state_duration_ms__modeSwitch_0_0 = Init_duration_ms;
						D_End__modeSwitch_0_0 = present;
					} else {
						// ifElse77
						
					}
				} else {
					// ifElse78
					
				}
			}
			D_Beg__modeSwitch_0_0 = D_Beg_new__modeSwitch_0_0;
			printf("interval_ms\n");
			timer_interval_ms__modeSwitch_0_0 = timer_interval_ms__modeSwitch_0_0 + 1;
			Fast__modeSwitch_0_0 = absent;
			Slow__modeSwitch_0_0 = absent;
			if (state_interval_ms__modeSwitch_0_0 == Init_interval_ms) {
				if ((AP__global_0_0_copy_modeSwitch_local.value == present) || (AR__global_0_0_copy_modeSwitch_local.value == present) || (AS__global_0_0_copy_modeSwitch_local.value == present)) {
					state_interval_ms__modeSwitch_0_0 = Wait;
					timer_interval_ms__modeSwitch_0_0 = 0;
				} else {
					// ifElse80
					
				}
			} else {
				// ifElse86
				if (state_interval_ms__modeSwitch_0_0 == Wait) {
					if ((AR__global_0_0_copy_modeSwitch_local.value == present) || (AS__global_0_0_copy_modeSwitch_local.value == present)) {
						if (timer_interval_ms__modeSwitch_0_0 <= Threshold__global_0_0) {
							state_interval_ms__modeSwitch_0_0 = Wait;
							Fast__modeSwitch_0_0 = present;
							timer_interval_ms__modeSwitch_0_0 = 0;
						} else {
							// ifElse82
							if (timer_interval_ms__modeSwitch_0_0 > Threshold__global_0_0) {
								state_interval_ms__modeSwitch_0_0 = Wait;
								Slow__modeSwitch_0_0 = present;
								timer_interval_ms__modeSwitch_0_0 = 0;
							} else {
								// ifElse81
								
							}
						}
					} else {
						// ifElse84
						if (AP__global_0_0_copy_modeSwitch_local.value == present) {
							state_interval_ms__modeSwitch_0_0 = Wait;
							Slow__modeSwitch_0_0 = present;
							timer_interval_ms__modeSwitch_0_0 = 0;
						} else {
							// ifElse83
							
						}
					}
				} else {
					// ifElse85
					printf("!! interval_ms: In an undefined state (%d)\n", state_interval_ms__modeSwitch_0_0);
				}
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.

			DDD__global_0_0_copy_modeSwitch = DDD__global_0_0_copy_modeSwitch_local;
			VDI__global_0_0_copy_modeSwitch = VDI__global_0_0_copy_modeSwitch_local;			// forec:statement:pause:pause2:start
			modeSwitch__thread.programCounter = &&pause2;
			goto *modeSwitch__thread.nextThread -> programCounter;
			pause2:;
			// forec:statement:pause:pause2:end
			// Update the values of the used shared variables from their global copy.
			AP__global_0_0_copy_modeSwitch_local = AP__global_0_0;
			VP__global_0_0_copy_modeSwitch_local = VP__global_0_0;
			AS__global_0_0_copy_modeSwitch_local = AS__global_0_0;
			AR__global_0_0_copy_modeSwitch_local = AR__global_0_0;
			VS__global_0_0_copy_modeSwitch_local = VS__global_0_0;
			DDD__global_0_0_copy_modeSwitch_local.status = FOREC_SHARED_UNMODIFIED;
			VDI__global_0_0_copy_modeSwitch_local.status = FOREC_SHARED_UNMODIFIED;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		DDD__global_0_0_copy_modeSwitch = DDD__global_0_0_copy_modeSwitch_local;
		VDI__global_0_0_copy_modeSwitch = VDI__global_0_0_copy_modeSwitch_local;

		// forec:scheduler:threadRemove:modeSwitch:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		modeSwitch__thread.nextThread -> prevThread = modeSwitch__thread.prevThread;
		modeSwitch__thread.prevThread -> nextThread = modeSwitch__thread.nextThread;
		goto *modeSwitch__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:modeSwitch:end
	} // modeSwitch__thread
	// forec:thread:modeSwitch:end

	// forec:thread:motionSensing:start
	/*--------------------------------------------------------------
	| Thread motionSensing
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	double PI__motionSensing_0_0;
	double PI_half__motionSensing_0_0;
	double PI_twice__motionSensing_0_0;
	double ar__motionSensing_0_0[8];
	double ai__motionSensing_0_0[8];
	int n__motionSensing_0_0, o__motionSensing_0_0;
	int i__motionSensing_0_0, j__motionSensing_0_0, k__motionSensing_0_0, it__motionSensing_0_0, xp__motionSensing_0_0, xp2__motionSensing_0_0, j1__motionSensing_0_0, j2__motionSensing_0_0;
	double w__motionSensing_0_0, wr__motionSensing_0_0, wi__motionSensing_0_0, dr1__motionSensing_0_0, dr2__motionSensing_0_0, di1__motionSensing_0_0, di2__motionSensing_0_0, tr__motionSensing_0_0, ti__motionSensing_0_0, arg__motionSensing_0_0;
	Shared_motionSensing2rateAdapter__global_0_0 motionSensing2rateAdapter__global_0_0_copy_motionSensing_local;

	// Thread body -------------------------------------------------
	motionSensing__thread: {
		// Initialise the local copies of shared variables.
		motionSensing2rateAdapter__global_0_0_copy_motionSensing_local.value = motionSensing2rateAdapter__global_0_0.value;
		motionSensing2rateAdapter__global_0_0_copy_motionSensing_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		PI__motionSensing_0_0 = 3.14159;
		PI_half__motionSensing_0_0 = 1.570795;
		PI_twice__motionSensing_0_0 = 6.28318;
		ar__motionSensing_0_0[0] = 1.0;
		ar__motionSensing_0_0[1] = 0.70711;
		ar__motionSensing_0_0[2] = 0.0;
		ar__motionSensing_0_0[3] = -0.70711;
		ar__motionSensing_0_0[4] = -1.0;
		ar__motionSensing_0_0[5] = -0.70711;
		ar__motionSensing_0_0[6] = 0.0;
		ar__motionSensing_0_0[7] = 0.70711;
		ai__motionSensing_0_0[0] = 0.0;
		ai__motionSensing_0_0[1] = 0.0;
		ai__motionSensing_0_0[2] = 0.0;
		ai__motionSensing_0_0[3] = 0.0;
		ai__motionSensing_0_0[4] = 0.0;
		ai__motionSensing_0_0[5] = 0.0;
		ai__motionSensing_0_0[6] = 0.0;
		ai__motionSensing_0_0[7] = 0.0;
		n__motionSensing_0_0 = 8, o__motionSensing_0_0 = 0;

		while (1) {
			printf("motionSensing\n");
			j__motionSensing_0_0 = 2;
			xp2__motionSensing_0_0 = n__motionSensing_0_0;
			for (it__motionSensing_0_0 = 0; it__motionSensing_0_0 < 1; it__motionSensing_0_0 = it__motionSensing_0_0 + 1) {
				xp__motionSensing_0_0 = xp2__motionSensing_0_0;
				xp2__motionSensing_0_0 = xp2__motionSensing_0_0/2;
				w__motionSensing_0_0 = PI__motionSensing_0_0/xp2__motionSensing_0_0;
				for (k__motionSensing_0_0 = 0; k__motionSensing_0_0 < xp2__motionSensing_0_0; k__motionSensing_0_0 = k__motionSensing_0_0 + 1) {
					arg__motionSensing_0_0 = k__motionSensing_0_0*w__motionSensing_0_0;
					wr__motionSensing_0_0 = sin(PI_half__motionSensing_0_0 - arg__motionSensing_0_0);
					wi__motionSensing_0_0 = -sin(arg__motionSensing_0_0);
					i__motionSensing_0_0 = k__motionSensing_0_0 - xp__motionSensing_0_0;
					for (j__motionSensing_0_0 = xp__motionSensing_0_0; j__motionSensing_0_0 <= n__motionSensing_0_0; j__motionSensing_0_0 = j__motionSensing_0_0 + xp__motionSensing_0_0) {
						j1__motionSensing_0_0 = j__motionSensing_0_0 + i__motionSensing_0_0;
						j2__motionSensing_0_0 = j1__motionSensing_0_0 + xp2__motionSensing_0_0;
						dr1__motionSensing_0_0 = ar__motionSensing_0_0[j1__motionSensing_0_0];
						dr2__motionSensing_0_0 = ar__motionSensing_0_0[j2__motionSensing_0_0];
						di1__motionSensing_0_0 = ai__motionSensing_0_0[j1__motionSensing_0_0];
						di2__motionSensing_0_0 = ai__motionSensing_0_0[j2__motionSensing_0_0];
						tr__motionSensing_0_0 = dr1__motionSensing_0_0 - dr2__motionSensing_0_0;
						ti__motionSensing_0_0 = di1__motionSensing_0_0 - di2__motionSensing_0_0;
						ar__motionSensing_0_0[j1__motionSensing_0_0] = dr1__motionSensing_0_0 + dr2__motionSensing_0_0;
						ai__motionSensing_0_0[j1__motionSensing_0_0] = di1__motionSensing_0_0 + di2__motionSensing_0_0;
						ar__motionSensing_0_0[j2__motionSensing_0_0] = tr__motionSensing_0_0*wr__motionSensing_0_0 - ti__motionSensing_0_0*wi__motionSensing_0_0;
						ai__motionSensing_0_0[j2__motionSensing_0_0] = ti__motionSensing_0_0*wr__motionSensing_0_0 + tr__motionSensing_0_0*wi__motionSensing_0_0;
						// forec:iteration:for1_4:bound:1:1
					}
					// forec:iteration:for1_5:bound:4:4
				}
				// forec:iteration:for1_6:bound:1:1
			}
			j1__motionSensing_0_0 = n__motionSensing_0_0/2;
			j2__motionSensing_0_0 = n__motionSensing_0_0 - 1;
			j__motionSensing_0_0 = 1;
			for (i__motionSensing_0_0 = 1; i__motionSensing_0_0 <= j2__motionSensing_0_0; i__motionSensing_0_0 = i__motionSensing_0_0 + 1) {
				if (i__motionSensing_0_0 < j__motionSensing_0_0) {
					tr__motionSensing_0_0 = ar__motionSensing_0_0[j__motionSensing_0_0 - 1];
					ti__motionSensing_0_0 = ai__motionSensing_0_0[j__motionSensing_0_0 - 1];
					ar__motionSensing_0_0[j__motionSensing_0_0 - 1] = ar__motionSensing_0_0[i__motionSensing_0_0 - 1];
					ai__motionSensing_0_0[j__motionSensing_0_0 - 1] = ai__motionSensing_0_0[i__motionSensing_0_0 - 1];
					ar__motionSensing_0_0[i__motionSensing_0_0 - 1] = tr__motionSensing_0_0;
					ai__motionSensing_0_0[i__motionSensing_0_0 - 1] = ti__motionSensing_0_0;
				} else {
					// if98
				}
				k__motionSensing_0_0 = j1__motionSensing_0_0;
				while (k__motionSensing_0_0 < j__motionSensing_0_0 && k__motionSensing_0_0 > 0) {
					j__motionSensing_0_0 = j__motionSensing_0_0 - k__motionSensing_0_0;
					k__motionSensing_0_0 = k__motionSensing_0_0/2;
					// forec:iteration:while_7:bound:0:2
				}
				j__motionSensing_0_0 = j__motionSensing_0_0 + k__motionSensing_0_0;
				// forec:iteration:for1_8:bound:7:7
			}
			o__motionSensing_0_0 = (o__motionSensing_0_0 + 1)%8;
			if (motionSensing2rateAdapter__global_0_0_copy_motionSensing_local.value.count == motionSensing2rateAdapter__global_0_0_copy_motionSensing_local.value.size) {
				printf("!! motionSensing2rateAdapter overflow\n");
				motionSensing2rateAdapter__global_0_0_copy_motionSensing_local.value.count = 0;
				motionSensing2rateAdapter__global_0_0_copy_motionSensing_local.status = FOREC_SHARED_MODIFIED;
			} else {
				// if99
			}
			motionSensing2rateAdapter__global_0_0_copy_motionSensing_local.value.values[motionSensing2rateAdapter__global_0_0_copy_motionSensing_local.value.count] = ai__motionSensing_0_0[o__motionSensing_0_0];
			motionSensing2rateAdapter__global_0_0_copy_motionSensing_local.status = FOREC_SHARED_MODIFIED;
			motionSensing2rateAdapter__global_0_0_copy_motionSensing_local.value.count = motionSensing2rateAdapter__global_0_0_copy_motionSensing_local.value.count + 1;
			motionSensing2rateAdapter__global_0_0_copy_motionSensing_local.status = FOREC_SHARED_MODIFIED;

			// pause;
			// Write the local copy of shared variables back to their global copy.

			motionSensing2rateAdapter__global_0_0 = motionSensing2rateAdapter__global_0_0_copy_motionSensing_local;			// forec:statement:pause:pause4:start
			motionSensing__thread.programCounter = &&pause4;
			goto *motionSensing__thread.nextThread -> programCounter;
			pause4:;
			// forec:statement:pause:pause4:end
			// Update the values of the used shared variables from their global copy.
			motionSensing2rateAdapter__global_0_0_copy_motionSensing_local = motionSensing2rateAdapter__global_0_0;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		motionSensing2rateAdapter__global_0_0.value = motionSensing2rateAdapter__global_0_0_copy_motionSensing_local.value;

		// forec:scheduler:threadRemove:motionSensing:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		motionSensing__thread.nextThread -> prevThread = motionSensing__thread.prevThread;
		motionSensing__thread.prevThread -> nextThread = motionSensing__thread.nextThread;
		goto *motionSensing__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:motionSensing:end
	} // motionSensing__thread
	// forec:thread:motionSensing:end

	// forec:thread:patternVpAs:start
	/*--------------------------------------------------------------
	| Thread patternVpAs
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	enum {
		Init_pattern_vpAs = 0,
		VP1
	} state_pattern_vpAs__patternVpAs_0_0;

	enum {
		Init_counter_vpAs = 0,
		E1,
		E2,
		E3,
		E4,
		E5,
		E6,
		E7,
		E8
	} state_counter_vpAs__patternVpAs_0_0;

	unsigned int timer_pattern_vpAs__patternVpAs_0_0;
	Signal__global_0_0 VP_AS__patternVpAs_0_0;
	Signal__global_0_0 Reset__patternVpAs_0_0;
	Shared_TPVARP__global_0_0 TPVARP__global_0_0_copy_patternVpAs_local;
	Shared_AP__global_0_0 AP__global_0_0_copy_patternVpAs_local;
	Shared_VP__global_0_0 VP__global_0_0_copy_patternVpAs_local;
	Shared_AS__global_0_0 AS__global_0_0_copy_patternVpAs_local;
	Shared_AR__global_0_0 AR__global_0_0_copy_patternVpAs_local;
	Shared_VS__global_0_0 VS__global_0_0_copy_patternVpAs_local;

	// Thread body -------------------------------------------------
	patternVpAs__thread: {
		// Initialise the local copies of shared variables.
		AP__global_0_0_copy_patternVpAs_local.value = AP__global_0_0_copy_main.value;
		AP__global_0_0_copy_patternVpAs_local.status = FOREC_SHARED_UNMODIFIED;
		VP__global_0_0_copy_patternVpAs_local.value = VP__global_0_0_copy_main.value;
		VP__global_0_0_copy_patternVpAs_local.status = FOREC_SHARED_UNMODIFIED;
		AS__global_0_0_copy_patternVpAs_local.value = AS__global_0_0_copy_main.value;
		AS__global_0_0_copy_patternVpAs_local.status = FOREC_SHARED_UNMODIFIED;
		AR__global_0_0_copy_patternVpAs_local.value = AR__global_0_0_copy_main.value;
		AR__global_0_0_copy_patternVpAs_local.status = FOREC_SHARED_UNMODIFIED;
		VS__global_0_0_copy_patternVpAs_local.value = VS__global_0_0_copy_main.value;
		VS__global_0_0_copy_patternVpAs_local.status = FOREC_SHARED_UNMODIFIED;
		TPVARP__global_0_0_copy_patternVpAs_local.value = TPVARP__global_0_0.value;
		TPVARP__global_0_0_copy_patternVpAs_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		state_pattern_vpAs__patternVpAs_0_0 = Init_pattern_vpAs;
		state_counter_vpAs__patternVpAs_0_0 = Init_counter_vpAs;
		timer_pattern_vpAs__patternVpAs_0_0 = 0;
		VP_AS__patternVpAs_0_0 = absent;
		Reset__patternVpAs_0_0 = absent;

		while (1) {
			printf("pattern_vpAs\n");
			timer_pattern_vpAs__patternVpAs_0_0 = timer_pattern_vpAs__patternVpAs_0_0 + 1;
			VP_AS__patternVpAs_0_0 = absent;
			Reset__patternVpAs_0_0 = absent;
			if (state_pattern_vpAs__patternVpAs_0_0 == Init_pattern_vpAs) {
				if (VP__global_0_0_copy_patternVpAs_local.value == present) {
					state_pattern_vpAs__patternVpAs_0_0 = VP1;
					timer_pattern_vpAs__patternVpAs_0_0 = 0;
				} else {
					// ifElse87
					
				}
			} else {
				// ifElse92
				if (state_pattern_vpAs__patternVpAs_0_0 == VP1) {
					if (AS__global_0_0_copy_patternVpAs_local.value == present) {
						if (T_150__global_0_0 <= timer_pattern_vpAs__patternVpAs_0_0 && timer_pattern_vpAs__patternVpAs_0_0 <= T_200__global_0_0) {
							VP_AS__patternVpAs_0_0 = present;
						} else {
							// ifElse88
							
						}
					} else {
						// ifElse90
						if ((VS__global_0_0_copy_patternVpAs_local.value == present) || (AP__global_0_0_copy_patternVpAs_local.value == present) || (AR__global_0_0_copy_patternVpAs_local.value == present)) {
							Reset__patternVpAs_0_0 = present;
						} else {
							// if89
						}
					}
					state_pattern_vpAs__patternVpAs_0_0 = Init_pattern_vpAs;
				} else {
					// ifElse91
					printf("!! pattern_vpAs: In an undefined state (%d)\n", state_pattern_vpAs__patternVpAs_0_0);
				}
			}
			printf("counter_vpAs\n");
			if (state_counter_vpAs__patternVpAs_0_0 == Init_counter_vpAs) {
				if (VP_AS__patternVpAs_0_0 == present) {
					state_counter_vpAs__patternVpAs_0_0 = E1;
				} else {
					// ifElse93
					
				}
			} else {
				// ifElse97
				if (Reset__patternVpAs_0_0 == present) {
					state_counter_vpAs__patternVpAs_0_0 = Init_counter_vpAs;
				} else {
					// ifElse96
					if (VP_AS__patternVpAs_0_0 == present) {
						state_counter_vpAs__patternVpAs_0_0 = state_counter_vpAs__patternVpAs_0_0 + 1;
						if (state_counter_vpAs__patternVpAs_0_0 == E8) {
							state_counter_vpAs__patternVpAs_0_0 = Init_counter_vpAs;
							TPVARP__global_0_0_copy_patternVpAs_local.value = T_500__global_0_0;
							TPVARP__global_0_0_copy_patternVpAs_local.status = FOREC_SHARED_MODIFIED;
						} else {
							// ifElse94
							
						}
					} else {
						// ifElse95
						
					}
				}
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.

			TPVARP__global_0_0_copy_patternVpAs = TPVARP__global_0_0_copy_patternVpAs_local;			// forec:statement:pause:pause3:start
			patternVpAs__thread.programCounter = &&pause3;
			goto *patternVpAs__thread.nextThread -> programCounter;
			pause3:;
			// forec:statement:pause:pause3:end
			// Update the values of the used shared variables from their global copy.
			AP__global_0_0_copy_patternVpAs_local = AP__global_0_0;
			VP__global_0_0_copy_patternVpAs_local = VP__global_0_0;
			AS__global_0_0_copy_patternVpAs_local = AS__global_0_0;
			AR__global_0_0_copy_patternVpAs_local = AR__global_0_0;
			VS__global_0_0_copy_patternVpAs_local = VS__global_0_0;
			TPVARP__global_0_0_copy_patternVpAs_local.status = FOREC_SHARED_UNMODIFIED;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		TPVARP__global_0_0_copy_patternVpAs = TPVARP__global_0_0_copy_patternVpAs_local;

		// forec:scheduler:threadRemove:patternVpAs:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		patternVpAs__thread.nextThread -> prevThread = patternVpAs__thread.prevThread;
		patternVpAs__thread.prevThread -> nextThread = patternVpAs__thread.nextThread;
		goto *patternVpAs__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:patternVpAs:end
	} // patternVpAs__thread
	// forec:thread:patternVpAs:end

	// forec:thread:rateAdapter:start
	/*--------------------------------------------------------------
	| Thread rateAdapter
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	int MAX__rateAdapter_0_0;
	int i__rateAdapter_0_0;
	int Seed__rateAdapter_0_0;
	double ArrayA__rateAdapter_0_0[1000], ArrayB__rateAdapter_0_0[1000];
	double MeanA__rateAdapter_0_0, MeanB__rateAdapter_0_0, VarA__rateAdapter_0_0, VarB__rateAdapter_0_0, StddevA__rateAdapter_0_0, StddevB__rateAdapter_0_0;
	double SumA__rateAdapter_0_0, SumB__rateAdapter_0_0;
	double numerator__rateAdapter_0_0;
	double diffsA__rateAdapter_0_0, diffsB__rateAdapter_0_0;
	double Aterm__rateAdapter_0_0, Bterm__rateAdapter_0_0, Aterm_sqrt__rateAdapter_0_0, Bterm_sqrt__rateAdapter_0_0;
	double Coef__rateAdapter_0_0;

	// Thread body -------------------------------------------------
	rateAdapter__thread: {
		// Initialise the local copies of shared variables.
		//--------------------------------------------------------------

		MAX__rateAdapter_0_0 = 1000;
		Seed__rateAdapter_0_0 = 0;

		while (1) {
			printf("rateAdapter\n");
			for (i__rateAdapter_0_0 = 0; i__rateAdapter_0_0 < MAX__rateAdapter_0_0; i__rateAdapter_0_0 = i__rateAdapter_0_0 + 1) {
				ArrayA__rateAdapter_0_0[i__rateAdapter_0_0] = i__rateAdapter_0_0 + (((Seed__rateAdapter_0_0*133) + 81)%8095)/8095.0;
				ArrayB__rateAdapter_0_0[i__rateAdapter_0_0] = i__rateAdapter_0_0 + (((Seed__rateAdapter_0_0*133) + 81)%8095)/8095.0;
				// forec:iteration:for1_13:bound:1000:1000
			}
			SumA__rateAdapter_0_0 = 0;
			SumB__rateAdapter_0_0 = 0;
			for (i__rateAdapter_0_0 = 0; i__rateAdapter_0_0 < MAX__rateAdapter_0_0; i__rateAdapter_0_0 = i__rateAdapter_0_0 + 1) {
				SumA__rateAdapter_0_0 = SumA__rateAdapter_0_0 + ArrayA__rateAdapter_0_0[i__rateAdapter_0_0];
				SumB__rateAdapter_0_0 = SumB__rateAdapter_0_0 + ArrayB__rateAdapter_0_0[i__rateAdapter_0_0];
				// forec:iteration:for1_14:bound:1000:1000
			}
			MeanA__rateAdapter_0_0 = SumA__rateAdapter_0_0/MAX__rateAdapter_0_0;
			MeanB__rateAdapter_0_0 = SumB__rateAdapter_0_0/MAX__rateAdapter_0_0;
			diffsA__rateAdapter_0_0 = 0.0;
			diffsB__rateAdapter_0_0 = 0.0;
			for (i__rateAdapter_0_0 = 0; i__rateAdapter_0_0 < MAX__rateAdapter_0_0; i__rateAdapter_0_0 = i__rateAdapter_0_0 + 1) {
				diffsA__rateAdapter_0_0 = diffsA__rateAdapter_0_0 + (ArrayA__rateAdapter_0_0[i__rateAdapter_0_0] - MeanA__rateAdapter_0_0)*(ArrayA__rateAdapter_0_0[i__rateAdapter_0_0] - MeanA__rateAdapter_0_0);
				diffsB__rateAdapter_0_0 = diffsB__rateAdapter_0_0 + (ArrayB__rateAdapter_0_0[i__rateAdapter_0_0] - MeanB__rateAdapter_0_0)*(ArrayB__rateAdapter_0_0[i__rateAdapter_0_0] - MeanB__rateAdapter_0_0);
				// forec:iteration:for1_15:bound:1000:1000
			}
			VarA__rateAdapter_0_0 = diffsA__rateAdapter_0_0/MAX__rateAdapter_0_0;
			VarB__rateAdapter_0_0 = diffsB__rateAdapter_0_0/MAX__rateAdapter_0_0;
			StddevA__rateAdapter_0_0 = VarA__rateAdapter_0_0;
			StddevB__rateAdapter_0_0 = VarB__rateAdapter_0_0;
			for (i__rateAdapter_0_0 = 0; i__rateAdapter_0_0 < 10; i__rateAdapter_0_0 = i__rateAdapter_0_0 + 1) {
				StddevA__rateAdapter_0_0 = 0.5*(StddevA__rateAdapter_0_0 + VarA__rateAdapter_0_0/StddevA__rateAdapter_0_0);
				StddevB__rateAdapter_0_0 = 0.5*(StddevB__rateAdapter_0_0 + VarB__rateAdapter_0_0/StddevB__rateAdapter_0_0);
			}
			numerator__rateAdapter_0_0 = 0.0;
			Aterm__rateAdapter_0_0 = Bterm__rateAdapter_0_0 = 0.0;
			for (i__rateAdapter_0_0 = 0; i__rateAdapter_0_0 < MAX__rateAdapter_0_0; i__rateAdapter_0_0 = i__rateAdapter_0_0 + 1) {
				numerator__rateAdapter_0_0 = numerator__rateAdapter_0_0 + (ArrayA__rateAdapter_0_0[i__rateAdapter_0_0] - MeanA__rateAdapter_0_0)*(ArrayB__rateAdapter_0_0[i__rateAdapter_0_0] - MeanB__rateAdapter_0_0);
				Aterm__rateAdapter_0_0 = Aterm__rateAdapter_0_0 + (ArrayA__rateAdapter_0_0[i__rateAdapter_0_0] - MeanA__rateAdapter_0_0)*(ArrayA__rateAdapter_0_0[i__rateAdapter_0_0] - MeanA__rateAdapter_0_0);
				Bterm__rateAdapter_0_0 = Bterm__rateAdapter_0_0 + (ArrayB__rateAdapter_0_0[i__rateAdapter_0_0] - MeanB__rateAdapter_0_0)*(ArrayB__rateAdapter_0_0[i__rateAdapter_0_0] - MeanB__rateAdapter_0_0);
				// forec:iteration:for1_17:bound:1000:1000
			}
			for (i__rateAdapter_0_0 = 0; i__rateAdapter_0_0 < 10; i__rateAdapter_0_0 = i__rateAdapter_0_0 + 1) {
				Aterm_sqrt__rateAdapter_0_0 = 0.5*(Aterm_sqrt__rateAdapter_0_0 + Aterm__rateAdapter_0_0/Aterm_sqrt__rateAdapter_0_0);
				Bterm_sqrt__rateAdapter_0_0 = 0.5*(Bterm_sqrt__rateAdapter_0_0 + Bterm__rateAdapter_0_0/Bterm_sqrt__rateAdapter_0_0);
			}
			Coef__rateAdapter_0_0 = numerator__rateAdapter_0_0/(Aterm_sqrt__rateAdapter_0_0*Bterm_sqrt__rateAdapter_0_0);

			// pause;
			// forec:statement:pause:pause5:start
			rateAdapter__thread.programCounter = &&pause5;
			goto *rateAdapter__thread.nextThread -> programCounter;
			pause5:;
			// forec:statement:pause:pause5:end

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:rateAdapter:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		rateAdapter__thread.nextThread -> prevThread = rateAdapter__thread.prevThread;
		rateAdapter__thread.prevThread -> nextThread = rateAdapter__thread.nextThread;
		goto *rateAdapter__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:rateAdapter:end
	} // rateAdapter__thread
	// forec:thread:rateAdapter:end


} // End of the main() function.

double sin(double rad__sin_0_0) {
	double PI_twice__sin_0_0 = 6.28318;
	double app__sin_0_0;
	double diff__sin_0_0;
	int inc__sin_0_0;
	while (rad__sin_0_0 > PI_twice__sin_0_0) {
		rad__sin_0_0 = rad__sin_0_0 - PI_twice__sin_0_0;
		// forec:iteration:while_10:bound:0:0
	}
	while (rad__sin_0_0 < -PI_twice__sin_0_0) {
		rad__sin_0_0 = rad__sin_0_0 + PI_twice__sin_0_0;
		// forec:iteration:while_11:bound:0:0
	}
	diff__sin_0_0 = (rad__sin_0_0*(-(rad__sin_0_0*rad__sin_0_0)))/6.0;
	app__sin_0_0 = rad__sin_0_0 + diff__sin_0_0;
	inc__sin_0_0 = 2;
	while ((diff__sin_0_0 >= 0.00001 && diff__sin_0_0 >= 0) || (-diff__sin_0_0 >= 0.00001 && diff__sin_0_0 < 0)) {
		diff__sin_0_0 = (diff__sin_0_0*(-(rad__sin_0_0*rad__sin_0_0)))/((2.0*inc__sin_0_0)*(2.0*inc__sin_0_0 + 1.0));
		app__sin_0_0 = app__sin_0_0 + diff__sin_0_0;
		inc__sin_0_0 = inc__sin_0_0 + 1;
		// forec:iteration:while_12:bound:0:11
	}
	return (app__sin_0_0);
}

void icrc(unsigned short crc__icrc_0_0, unsigned long len__icrc_0_0, short jinit__icrc_0_0, int jrev__icrc_0_0) {
	unsigned char lin__icrc_0_0[40] = "asdffeagewaHAFEFaeDsFEawFdsFaefaeerdjgp";
	unsigned short icrctb__icrc_0_0[40];
	unsigned char rchr__icrc_0_0[40];
	unsigned short tmp1__icrc_0_0;
	unsigned short tmp2__icrc_0_0;
	unsigned short j__icrc_0_0;
	unsigned short cword__icrc_0_0 = crc__icrc_0_0;
	unsigned char it__icrc_0_0[16] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
	for (j__icrc_0_0 = 0; j__icrc_0_0 < len__icrc_0_0; j__icrc_0_0 = j__icrc_0_0 + 1) {
		unsigned char onech__icrc_1_0 = (unsigned char)0;
		unsigned short ans__icrc_1_0 = ((j__icrc_0_0 << 8) ^ onech__icrc_1_0 << 8);
		unsigned short int i__icrc_1_0;
		for (i__icrc_1_0 = 0; i__icrc_1_0 < 8; i__icrc_1_0 = i__icrc_1_0 + 1) {
			if (ans__icrc_1_0 & 0x8000) {
				ans__icrc_1_0 = (ans__icrc_1_0 << 1);
				ans__icrc_1_0 = (ans__icrc_1_0 ^ 4129);
			} else {
				// ifElse157
				ans__icrc_1_0 = (ans__icrc_1_0 << 1);
			}
		}
		icrctb__icrc_0_0[j__icrc_0_0] = ans__icrc_1_0;
		rchr__icrc_0_0[j__icrc_0_0] = (unsigned char)(it__icrc_0_0[j__icrc_0_0 & 0xF] << 4 | it__icrc_0_0[j__icrc_0_0 >> 4]);
	}
	if (jinit__icrc_0_0 > -1) {
		cword__icrc_0_0 = ((unsigned char)jinit__icrc_0_0) | (((unsigned char)jinit__icrc_0_0) << 8);
	} else {
		// ifElse159
		if (jrev__icrc_0_0 < 0) {
			cword__icrc_0_0 = rchr__icrc_0_0[((unsigned char)((cword__icrc_0_0) >> 8))] | rchr__icrc_0_0[((unsigned char)((cword__icrc_0_0) & 0xFF))] << 8;
		} else {
			// if158
		}
	}
	for (j__icrc_0_0 = 1; j__icrc_0_0 <= len__icrc_0_0; j__icrc_0_0 = j__icrc_0_0 + 1) {
		if (jrev__icrc_0_0 < 0) {
			tmp1__icrc_0_0 = rchr__icrc_0_0[lin__icrc_0_0[j__icrc_0_0]] ^ ((unsigned char)((cword__icrc_0_0) >> 8));
		} else {
			// ifElse160
			tmp1__icrc_0_0 = lin__icrc_0_0[j__icrc_0_0] ^ ((unsigned char)((cword__icrc_0_0) >> 8));
		}
		cword__icrc_0_0 = icrctb__icrc_0_0[tmp1__icrc_0_0] ^ ((unsigned char)((cword__icrc_0_0) & 0xFF)) << 8;
	}
	if (jrev__icrc_0_0 > -1) {
		tmp2__icrc_0_0 = cword__icrc_0_0;
	} else {
		// ifElse161
		tmp2__icrc_0_0 = rchr__icrc_0_0[((unsigned char)((cword__icrc_0_0) >> 8))] | rchr__icrc_0_0[((unsigned char)((cword__icrc_0_0) & 0xFF))] << 8;
	}
}

