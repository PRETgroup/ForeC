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

const Signal__global_0_0 or(const Signal__global_0_0 *const copy1__or_0_0, const Signal__global_0_0 *const copy2__or_0_0) {
	if ((* copy1__or_0_0 == present) || (* copy2__or_0_0 == present)) {
		return present;
	} else {
		// ifElse1
		return absent;
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
typedef struct {
	/* shared */ unsigned int value;
	unsigned short int status;
} Shared_TAVI__global_0_0;
Shared_TAVI__global_0_0 TAVI__global_0_0 = {.value = 96, .status = FOREC_SHARED_UNMODIFIED};

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
	/* shared */ unsigned int value;
	unsigned short int status;
} Shared_timer_uri__global_0_0;
Shared_timer_uri__global_0_0 timer_uri__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_A_Get__global_0_0;
Shared_A_Get__global_0_0 A_Get__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};

/* input */ Signal__global_0_0 A_Get_o__global_0_0 = absent;

typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_A_Act__global_0_0;
Shared_A_Act__global_0_0 A_Act__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};

/* input */ Signal__global_0_0 A_Act_o__global_0_0 = absent;

typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_V_Get__global_0_0;
Shared_V_Get__global_0_0 V_Get__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};

/* input */ Signal__global_0_0 V_Get_o__global_0_0 = absent;

typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_V_Act__global_0_0;
Shared_V_Act__global_0_0 V_Act__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};

/* input */ Signal__global_0_0 V_Act_o__global_0_0 = absent;

typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_AP__global_0_0;
Shared_AP__global_0_0 AP__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};

/* output */ Signal__global_0_0 AP_o__global_0_0 = absent;

typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_VP__global_0_0;
Shared_VP__global_0_0 VP__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED} /* combine with or */;

/* output */ Signal__global_0_0 VP_o__global_0_0 = absent;

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
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_A_Block__global_0_0;
Shared_A_Block__global_0_0 A_Block__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_V_Block__global_0_0;
Shared_V_Block__global_0_0 V_Block__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_Fast__global_0_0;
Shared_Fast__global_0_0 Fast__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_Slow__global_0_0;
Shared_Slow__global_0_0 Slow__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_D_Beg__global_0_0;
Shared_D_Beg__global_0_0 D_Beg__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_D_End__global_0_0;
Shared_D_End__global_0_0 D_End__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_VP_AS__global_0_0;
Shared_VP_AS__global_0_0 VP_AS__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Signal__global_0_0 value;
	unsigned short int status;
} Shared_Reset__global_0_0;
Shared_Reset__global_0_0 Reset__global_0_0 = {.value = absent, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ Log__global_0_0 value;
	unsigned short int status;
} Shared_log__global_0_0;
Shared_log__global_0_0 log__global_0_0 = {.value = {.events = {{0}, }, .tail = 0, .size = 100}, .status = FOREC_SHARED_UNMODIFIED};

// thread ekgSensing__thread(/* shared */ Signal__global_0_0 AP, /* shared */ Signal__global_0_0 A_Act, /* shared */ Signal__global_0_0 A_Get, /* shared */ Signal__global_0_0 VP, /* shared */ Signal__global_0_0 V_Act, /* shared */ Signal__global_0_0 V_Get);
// thread lri_ms__thread(/* shared */ Signal__global_0_0 AS, /* shared */ Signal__global_0_0 VS, /* shared */ Signal__global_0_0 VP, /* shared */ Signal__global_0_0 DDD, /* shared */ Signal__global_0_0 VDI, /* shared */ Signal__global_0_0 AP, /* shared */ Signal__global_0_0 VP);
// thread avi_ms__thread(/* shared */ Signal__global_0_0 AS, /* shared */ Signal__global_0_0 VS, /* shared */ Signal__global_0_0 VP, /* shared */ Signal__global_0_0 DDD, /* shared */ Signal__global_0_0 VDI, /* shared */ Signal__global_0_0 AP, /* shared */ Signal__global_0_0 VP, /* shared */ unsigned int timer_uri);
// thread uri__thread(/* shared */ Signal__global_0_0 VP, /* shared */ Signal__global_0_0 VS, /* shared */ unsigned int timer_uri);
// thread pvarp_elt__thread(/* shared */ Signal__global_0_0 A_Get, /* shared */ Signal__global_0_0 VS, /* shared */ Signal__global_0_0 VP, /* shared */ Signal__global_0_0 A_Act, /* shared */ Signal__global_0_0 AS, /* shared */ Signal__global_0_0 AR, /* shared */ Signal__global_0_0 A_Block, /* shared */ unsigned int TPVARP);
// thread vrp__thread(/* shared */ Signal__global_0_0 V_Get, /* shared */ Signal__global_0_0 VP, /* shared */ Signal__global_0_0 V_Act, /* shared */ Signal__global_0_0 VS, /* shared */ Signal__global_0_0 V_Block);
// thread interval_ms__thread(/* shared */ Signal__global_0_0 AS, /* shared */ Signal__global_0_0 AR, /* shared */ Signal__global_0_0 AP, /* shared */ Signal__global_0_0 Fast, /* shared */ Signal__global_0_0 Slow);
// thread counter_ms__thread(/* shared */ Signal__global_0_0 Fast, /* shared */ Signal__global_0_0 Slow, /* shared */ Signal__global_0_0 D_End, /* shared */ Signal__global_0_0 DDD, /* shared */ Signal__global_0_0 VDI, /* shared */ Signal__global_0_0 D_Beg);
// thread duration_ms__thread(/* shared */ Signal__global_0_0 VS, /* shared */ Signal__global_0_0 VP, /* shared */ Signal__global_0_0 D_Beg, /* shared */ Signal__global_0_0 D_End);
// thread pattern_vpAs__thread(/* shared */ Signal__global_0_0 VP, /* shared */ Signal__global_0_0 VS, /* shared */ Signal__global_0_0 AP, /* shared */ Signal__global_0_0 AR, /* shared */ Signal__global_0_0 VP_AS, /* shared */ Signal__global_0_0 Reset);
// thread counter_vpAs__thread(/* shared */ Signal__global_0_0 VP_AS, /* shared */ Signal__global_0_0 Reset, /* shared */ unsigned int TPVARP);
// thread logging__thread(/* shared */ Signal__global_0_0 AS, /* shared */ Signal__global_0_0 AP, /* shared */ Signal__global_0_0 AR, /* shared */ Signal__global_0_0 A_Block, /* shared */ Signal__global_0_0 VS, /* shared */ Signal__global_0_0 VP, /* shared */ Signal__global_0_0 V_Block, /* shared */ Log__global_0_0 log);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// avi_ms
Shared_TURI__global_0_0 TURI__global_0_0_copy_avi_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_TAVI__global_0_0 TAVI__global_0_0_copy_avi_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_timer_uri__global_0_0 timer_uri__global_0_0_copy_avi_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AP__global_0_0 AP__global_0_0_copy_avi_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VP__global_0_0 VP__global_0_0_copy_avi_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AS__global_0_0 AS__global_0_0_copy_avi_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VS__global_0_0 VS__global_0_0_copy_avi_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_DDD__global_0_0 DDD__global_0_0_copy_avi_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VDI__global_0_0 VDI__global_0_0_copy_avi_ms = {.status = FOREC_SHARED_UNMODIFIED};
// counter_ms
Shared_DDD__global_0_0 DDD__global_0_0_copy_counter_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VDI__global_0_0 VDI__global_0_0_copy_counter_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_Fast__global_0_0 Fast__global_0_0_copy_counter_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_Slow__global_0_0 Slow__global_0_0_copy_counter_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_D_Beg__global_0_0 D_Beg__global_0_0_copy_counter_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_D_End__global_0_0 D_End__global_0_0_copy_counter_ms = {.status = FOREC_SHARED_UNMODIFIED};
// counter_vpAs
Shared_TPVARP__global_0_0 TPVARP__global_0_0_copy_counter_vpAs = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VP_AS__global_0_0 VP_AS__global_0_0_copy_counter_vpAs = {.status = FOREC_SHARED_UNMODIFIED};
Shared_Reset__global_0_0 Reset__global_0_0_copy_counter_vpAs = {.status = FOREC_SHARED_UNMODIFIED};
// duration_ms
Shared_VP__global_0_0 VP__global_0_0_copy_duration_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VS__global_0_0 VS__global_0_0_copy_duration_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_D_Beg__global_0_0 D_Beg__global_0_0_copy_duration_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_D_End__global_0_0 D_End__global_0_0_copy_duration_ms = {.status = FOREC_SHARED_UNMODIFIED};
// ekgSensing
Shared_A_Get__global_0_0 A_Get__global_0_0_copy_ekgSensing = {.status = FOREC_SHARED_UNMODIFIED};
Shared_A_Act__global_0_0 A_Act__global_0_0_copy_ekgSensing = {.status = FOREC_SHARED_UNMODIFIED};
Shared_V_Get__global_0_0 V_Get__global_0_0_copy_ekgSensing = {.status = FOREC_SHARED_UNMODIFIED};
Shared_V_Act__global_0_0 V_Act__global_0_0_copy_ekgSensing = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AP__global_0_0 AP__global_0_0_copy_ekgSensing = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VP__global_0_0 VP__global_0_0_copy_ekgSensing = {.status = FOREC_SHARED_UNMODIFIED};
// interval_ms
Shared_AP__global_0_0 AP__global_0_0_copy_interval_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AS__global_0_0 AS__global_0_0_copy_interval_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AR__global_0_0 AR__global_0_0_copy_interval_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_Fast__global_0_0 Fast__global_0_0_copy_interval_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_Slow__global_0_0 Slow__global_0_0_copy_interval_ms = {.status = FOREC_SHARED_UNMODIFIED};
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
Shared_A_Block__global_0_0 A_Block__global_0_0_copy_logging = {.status = FOREC_SHARED_UNMODIFIED};
Shared_V_Block__global_0_0 V_Block__global_0_0_copy_logging = {.status = FOREC_SHARED_UNMODIFIED};
Shared_log__global_0_0 log__global_0_0_copy_logging = {.status = FOREC_SHARED_UNMODIFIED};
// lri_ms
Shared_TLRI__global_0_0 TLRI__global_0_0_copy_lri_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_TAVI__global_0_0 TAVI__global_0_0_copy_lri_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AP__global_0_0 AP__global_0_0_copy_lri_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VP__global_0_0 VP__global_0_0_copy_lri_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AS__global_0_0 AS__global_0_0_copy_lri_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VS__global_0_0 VS__global_0_0_copy_lri_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_DDD__global_0_0 DDD__global_0_0_copy_lri_ms = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VDI__global_0_0 VDI__global_0_0_copy_lri_ms = {.status = FOREC_SHARED_UNMODIFIED};
// main
Shared_TPVARP__global_0_0 TPVARP__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_timer_uri__global_0_0 timer_uri__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
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
Shared_A_Block__global_0_0 A_Block__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_V_Block__global_0_0 V_Block__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_Fast__global_0_0 Fast__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_Slow__global_0_0 Slow__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_D_Beg__global_0_0 D_Beg__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_D_End__global_0_0 D_End__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VP_AS__global_0_0 VP_AS__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
Shared_Reset__global_0_0 Reset__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};
// pattern_vpAs
Shared_AP__global_0_0 AP__global_0_0_copy_pattern_vpAs = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VP__global_0_0 VP__global_0_0_copy_pattern_vpAs = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AS__global_0_0 AS__global_0_0_copy_pattern_vpAs = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AR__global_0_0 AR__global_0_0_copy_pattern_vpAs = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VS__global_0_0 VS__global_0_0_copy_pattern_vpAs = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VP_AS__global_0_0 VP_AS__global_0_0_copy_pattern_vpAs = {.status = FOREC_SHARED_UNMODIFIED};
Shared_Reset__global_0_0 Reset__global_0_0_copy_pattern_vpAs = {.status = FOREC_SHARED_UNMODIFIED};
// pvarp_elt
Shared_TPVARP__global_0_0 TPVARP__global_0_0_copy_pvarp_elt = {.status = FOREC_SHARED_UNMODIFIED};
Shared_A_Get__global_0_0 A_Get__global_0_0_copy_pvarp_elt = {.status = FOREC_SHARED_UNMODIFIED};
Shared_A_Act__global_0_0 A_Act__global_0_0_copy_pvarp_elt = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AS__global_0_0 AS__global_0_0_copy_pvarp_elt = {.status = FOREC_SHARED_UNMODIFIED};
Shared_AR__global_0_0 AR__global_0_0_copy_pvarp_elt = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VS__global_0_0 VS__global_0_0_copy_pvarp_elt = {.status = FOREC_SHARED_UNMODIFIED};
Shared_A_Block__global_0_0 A_Block__global_0_0_copy_pvarp_elt = {.status = FOREC_SHARED_UNMODIFIED};
// uri
Shared_timer_uri__global_0_0 timer_uri__global_0_0_copy_uri = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VP__global_0_0 VP__global_0_0_copy_uri = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VS__global_0_0 VS__global_0_0_copy_uri = {.status = FOREC_SHARED_UNMODIFIED};
// vrp
Shared_V_Get__global_0_0 V_Get__global_0_0_copy_vrp = {.status = FOREC_SHARED_UNMODIFIED};
Shared_V_Act__global_0_0 V_Act__global_0_0_copy_vrp = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VP__global_0_0 VP__global_0_0_copy_vrp = {.status = FOREC_SHARED_UNMODIFIED};
Shared_VS__global_0_0 VS__global_0_0_copy_vrp = {.status = FOREC_SHARED_UNMODIFIED};
Shared_V_Block__global_0_0 V_Block__global_0_0_copy_vrp = {.status = FOREC_SHARED_UNMODIFIED};

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
	Thread avi_ms__thread;
	Thread counter_ms__thread;
	Thread counter_vpAs__thread;
	Thread duration_ms__thread;
	Thread ekgSensing__thread;
	Thread interval_ms__thread;
	Thread logging__thread;
	Thread lri_ms__thread;
	Thread pattern_vpAs__thread;
	Thread pvarp_elt__thread;
	Thread uri__thread;
	Thread vrp__thread;
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
	Shared_timer_uri__global_0_0 timer_uri__global_0_0_copy_main_local;
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
	Shared_A_Block__global_0_0 A_Block__global_0_0_copy_main_local;
	Shared_V_Block__global_0_0 V_Block__global_0_0_copy_main_local;
	Shared_Fast__global_0_0 Fast__global_0_0_copy_main_local;
	Shared_Slow__global_0_0 Slow__global_0_0_copy_main_local;
	Shared_D_Beg__global_0_0 D_Beg__global_0_0_copy_main_local;
	Shared_D_End__global_0_0 D_End__global_0_0_copy_main_local;
	Shared_VP_AS__global_0_0 VP_AS__global_0_0_copy_main_local;
	Shared_Reset__global_0_0 Reset__global_0_0_copy_main_local;

mainParCore0: {
	// Initialise the local copies of shared variables.
	TPVARP__global_0_0_copy_main_local = TPVARP__global_0_0;
	timer_uri__global_0_0_copy_main_local = timer_uri__global_0_0;
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
	A_Block__global_0_0_copy_main_local = A_Block__global_0_0;
	V_Block__global_0_0_copy_main_local = V_Block__global_0_0;
	Fast__global_0_0_copy_main_local = Fast__global_0_0;
	Slow__global_0_0_copy_main_local = Slow__global_0_0;
	D_Beg__global_0_0_copy_main_local = D_Beg__global_0_0;
	D_End__global_0_0_copy_main_local = D_End__global_0_0;
	VP_AS__global_0_0_copy_main_local = VP_AS__global_0_0;
	Reset__global_0_0_copy_main_local = Reset__global_0_0;
	//--------------------------------------------------------------

	printf("Pacemaker\n");

	// par0(ekgSensing__thread, lri_ms__thread, avi_ms__thread, uri__thread, pvarp_elt__thread, vrp__thread, interval_ms__thread, counter_ms__thread, duration_ms__thread, pattern_vpAs__thread, counter_vpAs__thread, logging__thread);
	TPVARP__global_0_0_copy_main = TPVARP__global_0_0_copy_main_local;
	TPVARP__global_0_0.value = TPVARP__global_0_0_copy_main_local.value;
	timer_uri__global_0_0_copy_main = timer_uri__global_0_0_copy_main_local;
	timer_uri__global_0_0.value = timer_uri__global_0_0_copy_main_local.value;
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
	A_Block__global_0_0_copy_main = A_Block__global_0_0_copy_main_local;
	A_Block__global_0_0.value = A_Block__global_0_0_copy_main_local.value;
	V_Block__global_0_0_copy_main = V_Block__global_0_0_copy_main_local;
	V_Block__global_0_0.value = V_Block__global_0_0_copy_main_local.value;
	Fast__global_0_0_copy_main = Fast__global_0_0_copy_main_local;
	Fast__global_0_0.value = Fast__global_0_0_copy_main_local.value;
	Slow__global_0_0_copy_main = Slow__global_0_0_copy_main_local;
	Slow__global_0_0.value = Slow__global_0_0_copy_main_local.value;
	D_Beg__global_0_0_copy_main = D_Beg__global_0_0_copy_main_local;
	D_Beg__global_0_0.value = D_Beg__global_0_0_copy_main_local.value;
	D_End__global_0_0_copy_main = D_End__global_0_0_copy_main_local;
	D_End__global_0_0.value = D_End__global_0_0_copy_main_local.value;
	VP_AS__global_0_0_copy_main = VP_AS__global_0_0_copy_main_local;
	VP_AS__global_0_0.value = VP_AS__global_0_0_copy_main_local.value;
	Reset__global_0_0_copy_main = Reset__global_0_0_copy_main_local;
	Reset__global_0_0.value = Reset__global_0_0_copy_main_local.value;
	// Set the par(...) information.
	mainParParent.parId = 0;
	mainParParent.parStatus = FOREC_PAR_ON;

	// Link the threads and handlers together.
	mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
	ekgSensing__thread.programCounter = &&ekgSensing__thread;
	mainReactionStartMaster0.nextThread = &ekgSensing__thread;
	ekgSensing__thread.prevThread = &mainReactionStartMaster0;
	lri_ms__thread.programCounter = &&lri_ms__thread;
	ekgSensing__thread.nextThread = &lri_ms__thread;
	lri_ms__thread.prevThread = &ekgSensing__thread;
	avi_ms__thread.programCounter = &&avi_ms__thread;
	lri_ms__thread.nextThread = &avi_ms__thread;
	avi_ms__thread.prevThread = &lri_ms__thread;
	uri__thread.programCounter = &&uri__thread;
	avi_ms__thread.nextThread = &uri__thread;
	uri__thread.prevThread = &avi_ms__thread;
	pvarp_elt__thread.programCounter = &&pvarp_elt__thread;
	uri__thread.nextThread = &pvarp_elt__thread;
	pvarp_elt__thread.prevThread = &uri__thread;
	vrp__thread.programCounter = &&vrp__thread;
	pvarp_elt__thread.nextThread = &vrp__thread;
	vrp__thread.prevThread = &pvarp_elt__thread;
	interval_ms__thread.programCounter = &&interval_ms__thread;
	vrp__thread.nextThread = &interval_ms__thread;
	interval_ms__thread.prevThread = &vrp__thread;
	counter_ms__thread.programCounter = &&counter_ms__thread;
	interval_ms__thread.nextThread = &counter_ms__thread;
	counter_ms__thread.prevThread = &interval_ms__thread;
	duration_ms__thread.programCounter = &&duration_ms__thread;
	counter_ms__thread.nextThread = &duration_ms__thread;
	duration_ms__thread.prevThread = &counter_ms__thread;
	pattern_vpAs__thread.programCounter = &&pattern_vpAs__thread;
	duration_ms__thread.nextThread = &pattern_vpAs__thread;
	pattern_vpAs__thread.prevThread = &duration_ms__thread;
	counter_vpAs__thread.programCounter = &&counter_vpAs__thread;
	pattern_vpAs__thread.nextThread = &counter_vpAs__thread;
	counter_vpAs__thread.prevThread = &pattern_vpAs__thread;
	logging__thread.programCounter = &&logging__thread;
	counter_vpAs__thread.nextThread = &logging__thread;
	logging__thread.prevThread = &counter_vpAs__thread;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	logging__thread.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &logging__thread;

	// Link the last and first threads/handlers together.
	mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
	mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

	// Set the join address.
	mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

	// Set the core information.
	mainParCore0.activeThreads = 12;
	mainParCore0.reactionCounter = mainParReactionCounter;

	// Go to the first thread.
	// forec:statement:par:par0:start
	goto ekgSensing__thread;
	par0JoinAddress_mainParCore0:;
	// forec:statement:par:par0:end
	TPVARP__global_0_0_copy_main_local = TPVARP__global_0_0;
	timer_uri__global_0_0_copy_main_local = timer_uri__global_0_0;
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
	A_Block__global_0_0_copy_main_local = A_Block__global_0_0;
	V_Block__global_0_0_copy_main_local = V_Block__global_0_0;
	Fast__global_0_0_copy_main_local = Fast__global_0_0;
	Slow__global_0_0_copy_main_local = Slow__global_0_0;
	D_Beg__global_0_0_copy_main_local = D_Beg__global_0_0;
	D_End__global_0_0_copy_main_local = D_End__global_0_0;
	VP_AS__global_0_0_copy_main_local = VP_AS__global_0_0;
	Reset__global_0_0_copy_main_local = Reset__global_0_0;

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
		if (TPVARP__global_0_0_copy_counter_vpAs.status == FOREC_SHARED_MODIFIED) {
			TPVARP__global_0_0_copy_counter_vpAs.status = FOREC_SHARED_UNMODIFIED;
			modified_TPVARP__global_0_0[numberOfModifiedCopies] = &TPVARP__global_0_0_copy_counter_vpAs;
			++numberOfModifiedCopies;
		}
		if (TPVARP__global_0_0_copy_pvarp_elt.status == FOREC_SHARED_MODIFIED) {
			TPVARP__global_0_0_copy_pvarp_elt.status = FOREC_SHARED_UNMODIFIED;
			modified_TPVARP__global_0_0[numberOfModifiedCopies] = &TPVARP__global_0_0_copy_pvarp_elt;
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

		// timer_uri__global_0_0
		if (timer_uri__global_0_0_copy_uri.status == FOREC_SHARED_MODIFIED) {
			timer_uri__global_0_0_copy_uri.status = FOREC_SHARED_UNMODIFIED;
			timer_uri__global_0_0.value = timer_uri__global_0_0_copy_uri.value;
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
		if (AP__global_0_0_copy_lri_ms.status == FOREC_SHARED_MODIFIED) {
			AP__global_0_0_copy_lri_ms.status = FOREC_SHARED_UNMODIFIED;
			AP__global_0_0.value = AP__global_0_0_copy_lri_ms.value;
		}

		// VP__global_0_0
		numberOfModifiedCopies = 0;
		Shared_VP__global_0_0 *modified_VP__global_0_0[2];
		// Find the modified copies.
		if (VP__global_0_0_copy_avi_ms.status == FOREC_SHARED_MODIFIED) {
			VP__global_0_0_copy_avi_ms.status = FOREC_SHARED_UNMODIFIED;
			modified_VP__global_0_0[numberOfModifiedCopies] = &VP__global_0_0_copy_avi_ms;
			++numberOfModifiedCopies;
		}
		if (VP__global_0_0_copy_lri_ms.status == FOREC_SHARED_MODIFIED) {
			VP__global_0_0_copy_lri_ms.status = FOREC_SHARED_UNMODIFIED;
			modified_VP__global_0_0[numberOfModifiedCopies] = &VP__global_0_0_copy_lri_ms;
			++numberOfModifiedCopies;
		}
		// Assign the first modified copy.
		if (numberOfModifiedCopies > 0) {
			VP__global_0_0.value = modified_VP__global_0_0[0]->value;
		}
		// Combine with the remaining modified copies.
		for (index = 1; index < numberOfModifiedCopies; ++index) {
			VP__global_0_0.value = or(&VP__global_0_0.value, &modified_VP__global_0_0[index]->value);
		}

		// AS__global_0_0
		if (AS__global_0_0_copy_pvarp_elt.status == FOREC_SHARED_MODIFIED) {
			AS__global_0_0_copy_pvarp_elt.status = FOREC_SHARED_UNMODIFIED;
			AS__global_0_0.value = AS__global_0_0_copy_pvarp_elt.value;
		}

		// AR__global_0_0
		if (AR__global_0_0_copy_pvarp_elt.status == FOREC_SHARED_MODIFIED) {
			AR__global_0_0_copy_pvarp_elt.status = FOREC_SHARED_UNMODIFIED;
			AR__global_0_0.value = AR__global_0_0_copy_pvarp_elt.value;
		}

		// VS__global_0_0
		if (VS__global_0_0_copy_vrp.status == FOREC_SHARED_MODIFIED) {
			VS__global_0_0_copy_vrp.status = FOREC_SHARED_UNMODIFIED;
			VS__global_0_0.value = VS__global_0_0_copy_vrp.value;
		}

		// DDD__global_0_0
		if (DDD__global_0_0_copy_counter_ms.status == FOREC_SHARED_MODIFIED) {
			DDD__global_0_0_copy_counter_ms.status = FOREC_SHARED_UNMODIFIED;
			DDD__global_0_0.value = DDD__global_0_0_copy_counter_ms.value;
		}

		// VDI__global_0_0
		if (VDI__global_0_0_copy_counter_ms.status == FOREC_SHARED_MODIFIED) {
			VDI__global_0_0_copy_counter_ms.status = FOREC_SHARED_UNMODIFIED;
			VDI__global_0_0.value = VDI__global_0_0_copy_counter_ms.value;
		}

		// A_Block__global_0_0
		if (A_Block__global_0_0_copy_pvarp_elt.status == FOREC_SHARED_MODIFIED) {
			A_Block__global_0_0_copy_pvarp_elt.status = FOREC_SHARED_UNMODIFIED;
			A_Block__global_0_0.value = A_Block__global_0_0_copy_pvarp_elt.value;
		}

		// V_Block__global_0_0
		if (V_Block__global_0_0_copy_vrp.status == FOREC_SHARED_MODIFIED) {
			V_Block__global_0_0_copy_vrp.status = FOREC_SHARED_UNMODIFIED;
			V_Block__global_0_0.value = V_Block__global_0_0_copy_vrp.value;
		}

		// Fast__global_0_0
		if (Fast__global_0_0_copy_interval_ms.status == FOREC_SHARED_MODIFIED) {
			Fast__global_0_0_copy_interval_ms.status = FOREC_SHARED_UNMODIFIED;
			Fast__global_0_0.value = Fast__global_0_0_copy_interval_ms.value;
		}

		// Slow__global_0_0
		if (Slow__global_0_0_copy_interval_ms.status == FOREC_SHARED_MODIFIED) {
			Slow__global_0_0_copy_interval_ms.status = FOREC_SHARED_UNMODIFIED;
			Slow__global_0_0.value = Slow__global_0_0_copy_interval_ms.value;
		}

		// D_Beg__global_0_0
		if (D_Beg__global_0_0_copy_counter_ms.status == FOREC_SHARED_MODIFIED) {
			D_Beg__global_0_0_copy_counter_ms.status = FOREC_SHARED_UNMODIFIED;
			D_Beg__global_0_0.value = D_Beg__global_0_0_copy_counter_ms.value;
		}

		// D_End__global_0_0
		if (D_End__global_0_0_copy_duration_ms.status == FOREC_SHARED_MODIFIED) {
			D_End__global_0_0_copy_duration_ms.status = FOREC_SHARED_UNMODIFIED;
			D_End__global_0_0.value = D_End__global_0_0_copy_duration_ms.value;
		}

		// VP_AS__global_0_0
		if (VP_AS__global_0_0_copy_pattern_vpAs.status == FOREC_SHARED_MODIFIED) {
			VP_AS__global_0_0_copy_pattern_vpAs.status = FOREC_SHARED_UNMODIFIED;
			VP_AS__global_0_0.value = VP_AS__global_0_0_copy_pattern_vpAs.value;
		}

		// Reset__global_0_0
		if (Reset__global_0_0_copy_pattern_vpAs.status == FOREC_SHARED_MODIFIED) {
			Reset__global_0_0_copy_pattern_vpAs.status = FOREC_SHARED_UNMODIFIED;
			Reset__global_0_0.value = Reset__global_0_0_copy_pattern_vpAs.value;
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
	// forec:thread:avi_ms:start
	/*--------------------------------------------------------------
	| Thread avi_ms
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	enum State__avi_ms_0_0 {
		Init_avi_ms = 0,
		AVI,
		Wait_URI,
		VDI_Idle,
		VDI_AVI
	} state_avi_ms__avi_ms_0_0;

	unsigned int timer_avi_ms__avi_ms_0_0;
	Shared_TURI__global_0_0 TURI__global_0_0_copy_avi_ms_local;
	Shared_TAVI__global_0_0 TAVI__global_0_0_copy_avi_ms_local;
	Shared_timer_uri__global_0_0 timer_uri__global_0_0_copy_avi_ms_local;
	Shared_AP__global_0_0 AP__global_0_0_copy_avi_ms_local;
	Shared_VP__global_0_0 VP__global_0_0_copy_avi_ms_local;
	Shared_AS__global_0_0 AS__global_0_0_copy_avi_ms_local;
	Shared_VS__global_0_0 VS__global_0_0_copy_avi_ms_local;
	Shared_DDD__global_0_0 DDD__global_0_0_copy_avi_ms_local;
	Shared_VDI__global_0_0 VDI__global_0_0_copy_avi_ms_local;

	// Thread body -------------------------------------------------
	avi_ms__thread: {
		// Initialise the local copies of shared variables.
		TURI__global_0_0_copy_avi_ms_local.value = TURI__global_0_0.value;
		TURI__global_0_0_copy_avi_ms_local.status = FOREC_SHARED_UNMODIFIED;
		TAVI__global_0_0_copy_avi_ms_local.value = TAVI__global_0_0.value;
		TAVI__global_0_0_copy_avi_ms_local.status = FOREC_SHARED_UNMODIFIED;
		timer_uri__global_0_0_copy_avi_ms_local.value = timer_uri__global_0_0_copy_main.value;
		timer_uri__global_0_0_copy_avi_ms_local.status = FOREC_SHARED_UNMODIFIED;
		AP__global_0_0_copy_avi_ms_local.value = AP__global_0_0_copy_main.value;
		AP__global_0_0_copy_avi_ms_local.status = FOREC_SHARED_UNMODIFIED;
		AS__global_0_0_copy_avi_ms_local.value = AS__global_0_0_copy_main.value;
		AS__global_0_0_copy_avi_ms_local.status = FOREC_SHARED_UNMODIFIED;
		VS__global_0_0_copy_avi_ms_local.value = VS__global_0_0_copy_main.value;
		VS__global_0_0_copy_avi_ms_local.status = FOREC_SHARED_UNMODIFIED;
		DDD__global_0_0_copy_avi_ms_local.value = DDD__global_0_0_copy_main.value;
		DDD__global_0_0_copy_avi_ms_local.status = FOREC_SHARED_UNMODIFIED;
		VDI__global_0_0_copy_avi_ms_local.value = VDI__global_0_0_copy_main.value;
		VDI__global_0_0_copy_avi_ms_local.status = FOREC_SHARED_UNMODIFIED;
		VP__global_0_0_copy_avi_ms_local.value = VP__global_0_0.value;
		VP__global_0_0_copy_avi_ms_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		state_avi_ms__avi_ms_0_0 = Init_avi_ms;
		timer_avi_ms__avi_ms_0_0 = 0;

		while (1) {
			printf("avi_ms\n");
			timer_avi_ms__avi_ms_0_0 = timer_avi_ms__avi_ms_0_0 + 1;
			VP__global_0_0_copy_avi_ms_local.value = absent;
			VP__global_0_0_copy_avi_ms_local.status = FOREC_SHARED_MODIFIED;
			if (state_avi_ms__avi_ms_0_0 == Init_avi_ms) {
				if ((AS__global_0_0_copy_avi_ms_local.value == present) || (AP__global_0_0_copy_avi_ms_local.value == present)) {
					state_avi_ms__avi_ms_0_0 = AVI;
					timer_avi_ms__avi_ms_0_0 = 0;
				} else {
					// ifElse29
					if (VDI__global_0_0_copy_avi_ms_local.value == present) {
						state_avi_ms__avi_ms_0_0 = VDI_Idle;
					} else {
						// ifElse28
						
					}
				}
			} else {
				// ifElse47
				if (state_avi_ms__avi_ms_0_0 == AVI) {
					if (VDI__global_0_0_copy_avi_ms_local.value == present) {
						state_avi_ms__avi_ms_0_0 = VDI_AVI;
					} else {
						// ifElse34
						if (VS__global_0_0_copy_avi_ms_local.value == present) {
							state_avi_ms__avi_ms_0_0 = Init_avi_ms;
						} else {
							// ifElse33
							if (timer_avi_ms__avi_ms_0_0 >= TAVI__global_0_0_copy_avi_ms_local.value) {
								if (timer_uri__global_0_0_copy_avi_ms_local.value >= TURI__global_0_0_copy_avi_ms_local.value) {
									state_avi_ms__avi_ms_0_0 = Init_avi_ms;
									VP__global_0_0_copy_avi_ms_local.value = present;
									VP__global_0_0_copy_avi_ms_local.status = FOREC_SHARED_MODIFIED;
								} else {
									// ifElse31
									if (timer_uri__global_0_0_copy_avi_ms_local.value <= TURI__global_0_0_copy_avi_ms_local.value) {
										state_avi_ms__avi_ms_0_0 = Wait_URI;
									} else {
										// ifElse30
										
									}
								}
							} else {
								// ifElse32
								
							}
						}
					}
				} else {
					// ifElse46
					if (state_avi_ms__avi_ms_0_0 == Wait_URI) {
						if (timer_uri__global_0_0_copy_avi_ms_local.value >= TURI__global_0_0_copy_avi_ms_local.value) {
							state_avi_ms__avi_ms_0_0 = Init_avi_ms;
							VP__global_0_0_copy_avi_ms_local.value = present;
							VP__global_0_0_copy_avi_ms_local.status = FOREC_SHARED_MODIFIED;
						} else {
							// ifElse37
							if (VS__global_0_0_copy_avi_ms_local.value == present) {
								state_avi_ms__avi_ms_0_0 = Init_avi_ms;
							} else {
								// ifElse36
								if (VDI__global_0_0_copy_avi_ms_local.value == present) {
									state_avi_ms__avi_ms_0_0 = VDI_Idle;
									timer_avi_ms__avi_ms_0_0 = 0;
								} else {
									// ifElse35
									
								}
							}
						}
					} else {
						// ifElse45
						if (state_avi_ms__avi_ms_0_0 == VDI_Idle) {
							if (DDD__global_0_0_copy_avi_ms_local.value == present) {
								state_avi_ms__avi_ms_0_0 = Init_avi_ms;
							} else {
								// ifElse39
								if ((AS__global_0_0_copy_avi_ms_local.value == present) || (AP__global_0_0_copy_avi_ms_local.value == present)) {
									state_avi_ms__avi_ms_0_0 = VDI_AVI;
									timer_avi_ms__avi_ms_0_0 = 0;
								} else {
									// ifElse38
									
								}
							}
						} else {
							// ifElse44
							if (state_avi_ms__avi_ms_0_0 == VDI_AVI) {
								if (VS__global_0_0_copy_avi_ms_local.value == present) {
									state_avi_ms__avi_ms_0_0 = VDI_Idle;
								} else {
									// ifElse42
									if (DDD__global_0_0_copy_avi_ms_local.value == present) {
										state_avi_ms__avi_ms_0_0 = AVI;
									} else {
										// ifElse41
										if (timer_avi_ms__avi_ms_0_0 >= TAVI__global_0_0_copy_avi_ms_local.value) {
											state_avi_ms__avi_ms_0_0 = VDI_Idle;
										} else {
											// ifElse40
											
										}
									}
								}
							} else {
								// ifElse43
								printf("avi_ms: In an undefined state (%d)\n", state_avi_ms__avi_ms_0_0);
							}
						}
					}
				}
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.

			VP__global_0_0_copy_avi_ms = VP__global_0_0_copy_avi_ms_local;			// forec:statement:pause:pause2:start
			avi_ms__thread.programCounter = &&pause2;
			goto *avi_ms__thread.nextThread -> programCounter;
			pause2:;
			// forec:statement:pause:pause2:end
			// Update the values of the used shared variables from their global copy.
			TURI__global_0_0_copy_avi_ms_local = TURI__global_0_0;
			TAVI__global_0_0_copy_avi_ms_local = TAVI__global_0_0;
			timer_uri__global_0_0_copy_avi_ms_local = timer_uri__global_0_0;
			AP__global_0_0_copy_avi_ms_local = AP__global_0_0;
			AS__global_0_0_copy_avi_ms_local = AS__global_0_0;
			VS__global_0_0_copy_avi_ms_local = VS__global_0_0;
			DDD__global_0_0_copy_avi_ms_local = DDD__global_0_0;
			VDI__global_0_0_copy_avi_ms_local = VDI__global_0_0;
			VP__global_0_0_copy_avi_ms_local.status = FOREC_SHARED_UNMODIFIED;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		VP__global_0_0_copy_avi_ms = VP__global_0_0_copy_avi_ms_local;

		// forec:scheduler:threadRemove:avi_ms:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		avi_ms__thread.nextThread -> prevThread = avi_ms__thread.prevThread;
		avi_ms__thread.prevThread -> nextThread = avi_ms__thread.nextThread;
		goto *avi_ms__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:avi_ms:end
	} // avi_ms__thread
	// forec:thread:avi_ms:end

	// forec:thread:counter_ms:start
	/*--------------------------------------------------------------
	| Thread counter_ms
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	enum State__counter_ms_0_0 {
		Init_counter_ms = 0,
		Fast1,
		Fast2,
		Fast3,
		Fast4,
		Fast5,
		Fast6,
		Fast7,
		Fast8
	} state_counter_ms__counter_ms_0_0;
	Shared_DDD__global_0_0 DDD__global_0_0_copy_counter_ms_local;
	Shared_VDI__global_0_0 VDI__global_0_0_copy_counter_ms_local;
	Shared_Fast__global_0_0 Fast__global_0_0_copy_counter_ms_local;
	Shared_Slow__global_0_0 Slow__global_0_0_copy_counter_ms_local;
	Shared_D_Beg__global_0_0 D_Beg__global_0_0_copy_counter_ms_local;
	Shared_D_End__global_0_0 D_End__global_0_0_copy_counter_ms_local;

	// Thread body -------------------------------------------------
	counter_ms__thread: {
		// Initialise the local copies of shared variables.
		Fast__global_0_0_copy_counter_ms_local.value = Fast__global_0_0_copy_main.value;
		Fast__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_UNMODIFIED;
		Slow__global_0_0_copy_counter_ms_local.value = Slow__global_0_0_copy_main.value;
		Slow__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_UNMODIFIED;
		D_End__global_0_0_copy_counter_ms_local.value = D_End__global_0_0_copy_main.value;
		D_End__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_UNMODIFIED;
		DDD__global_0_0_copy_counter_ms_local.value = DDD__global_0_0.value;
		DDD__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_UNMODIFIED;
		VDI__global_0_0_copy_counter_ms_local.value = VDI__global_0_0.value;
		VDI__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_UNMODIFIED;
		D_Beg__global_0_0_copy_counter_ms_local.value = D_Beg__global_0_0.value;
		D_Beg__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		state_counter_ms__counter_ms_0_0 = Init_counter_ms;

		while (1) {
			printf("counter_ms\n");
			DDD__global_0_0_copy_counter_ms_local.value = absent;
			DDD__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_MODIFIED;
			VDI__global_0_0_copy_counter_ms_local.value = absent;
			VDI__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_MODIFIED;
			D_Beg__global_0_0_copy_counter_ms_local.value = absent;
			D_Beg__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_MODIFIED;
			if (state_counter_ms__counter_ms_0_0 == Init_counter_ms) {
				if (Fast__global_0_0_copy_counter_ms_local.value == present) {
					state_counter_ms__counter_ms_0_0 = Fast1;
				} else {
					// ifElse71
					
				}
			} else {
				// ifElse83
				if (state_counter_ms__counter_ms_0_0 == Fast1) {
					if (Slow__global_0_0_copy_counter_ms_local.value == present) {
						state_counter_ms__counter_ms_0_0 = Init_counter_ms;
						DDD__global_0_0_copy_counter_ms_local.value = present;
						DDD__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_MODIFIED;
					} else {
						// ifElse74
						if (Fast__global_0_0_copy_counter_ms_local.value == present) {
							state_counter_ms__counter_ms_0_0 = Fast2;
						} else {
							// ifElse73
							if (D_End__global_0_0_copy_counter_ms_local.value == present) {
								state_counter_ms__counter_ms_0_0 = Fast1;
								VDI__global_0_0_copy_counter_ms_local.value = present;
								VDI__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_MODIFIED;
							} else {
								// ifElse72
								
							}
						}
					}
				} else {
					// ifElse82
					if (state_counter_ms__counter_ms_0_0 == Fast8) {
						if (Slow__global_0_0_copy_counter_ms_local.value == present) {
							state_counter_ms__counter_ms_0_0 = Fast7;
						} else {
							// ifElse76
							if (D_End__global_0_0_copy_counter_ms_local.value == present) {
								state_counter_ms__counter_ms_0_0 = Fast8;
								VDI__global_0_0_copy_counter_ms_local.value = present;
								VDI__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_MODIFIED;
							} else {
								// ifElse75
								
							}
						}
					} else {
						// ifElse81
						if (Slow__global_0_0_copy_counter_ms_local.value == present) {
							state_counter_ms__counter_ms_0_0 = state_counter_ms__counter_ms_0_0 - 1;
						} else {
							// ifElse80
							if (Fast__global_0_0_copy_counter_ms_local.value == present) {
								if (state_counter_ms__counter_ms_0_0 == Fast7) {
									D_Beg__global_0_0_copy_counter_ms_local.value = present;
									D_Beg__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_MODIFIED;
								} else {
									// if77
								}
								state_counter_ms__counter_ms_0_0 = state_counter_ms__counter_ms_0_0 + 1;
							} else {
								// ifElse79
								if (D_End__global_0_0_copy_counter_ms_local.value == present) {
									state_counter_ms__counter_ms_0_0 = state_counter_ms__counter_ms_0_0 + 0;
									VDI__global_0_0_copy_counter_ms_local.value = present;
									VDI__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_MODIFIED;
								} else {
									// ifElse78
									
								}
							}
						}
					}
				}
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.

			DDD__global_0_0_copy_counter_ms = DDD__global_0_0_copy_counter_ms_local;
			VDI__global_0_0_copy_counter_ms = VDI__global_0_0_copy_counter_ms_local;
			D_Beg__global_0_0_copy_counter_ms = D_Beg__global_0_0_copy_counter_ms_local;			// forec:statement:pause:pause7:start
			counter_ms__thread.programCounter = &&pause7;
			goto *counter_ms__thread.nextThread -> programCounter;
			pause7:;
			// forec:statement:pause:pause7:end
			// Update the values of the used shared variables from their global copy.
			Fast__global_0_0_copy_counter_ms_local = Fast__global_0_0;
			Slow__global_0_0_copy_counter_ms_local = Slow__global_0_0;
			D_End__global_0_0_copy_counter_ms_local = D_End__global_0_0;
			DDD__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_UNMODIFIED;
			VDI__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_UNMODIFIED;
			D_Beg__global_0_0_copy_counter_ms_local.status = FOREC_SHARED_UNMODIFIED;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		DDD__global_0_0_copy_counter_ms = DDD__global_0_0_copy_counter_ms_local;
		VDI__global_0_0_copy_counter_ms = VDI__global_0_0_copy_counter_ms_local;
		D_Beg__global_0_0_copy_counter_ms = D_Beg__global_0_0_copy_counter_ms_local;

		// forec:scheduler:threadRemove:counter_ms:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		counter_ms__thread.nextThread -> prevThread = counter_ms__thread.prevThread;
		counter_ms__thread.prevThread -> nextThread = counter_ms__thread.nextThread;
		goto *counter_ms__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:counter_ms:end
	} // counter_ms__thread
	// forec:thread:counter_ms:end

	// forec:thread:counter_vpAs:start
	/*--------------------------------------------------------------
	| Thread counter_vpAs
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	enum State__counter_vpAs_0_0 {
		Init_counter_vpAs = 0,
		E1,
		E2,
		E3,
		E4,
		E5,
		E6,
		E7,
		E8
	} state_counter_vpAs__counter_vpAs_0_0;
	Shared_TPVARP__global_0_0 TPVARP__global_0_0_copy_counter_vpAs_local;
	Shared_VP_AS__global_0_0 VP_AS__global_0_0_copy_counter_vpAs_local;
	Shared_Reset__global_0_0 Reset__global_0_0_copy_counter_vpAs_local;

	// Thread body -------------------------------------------------
	counter_vpAs__thread: {
		// Initialise the local copies of shared variables.
		VP_AS__global_0_0_copy_counter_vpAs_local.value = VP_AS__global_0_0_copy_main.value;
		VP_AS__global_0_0_copy_counter_vpAs_local.status = FOREC_SHARED_UNMODIFIED;
		Reset__global_0_0_copy_counter_vpAs_local.value = Reset__global_0_0_copy_main.value;
		Reset__global_0_0_copy_counter_vpAs_local.status = FOREC_SHARED_UNMODIFIED;
		TPVARP__global_0_0_copy_counter_vpAs_local.value = TPVARP__global_0_0.value;
		TPVARP__global_0_0_copy_counter_vpAs_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		state_counter_vpAs__counter_vpAs_0_0 = Init_counter_vpAs;

		while (1) {
			printf("counter_vpAs\n");
			if (state_counter_vpAs__counter_vpAs_0_0 == Init_counter_vpAs) {
				if (VP_AS__global_0_0_copy_counter_vpAs_local.value == present) {
					state_counter_vpAs__counter_vpAs_0_0 = E1;
				} else {
					// ifElse94
					
				}
			} else {
				// ifElse98
				if (Reset__global_0_0_copy_counter_vpAs_local.value == present) {
					state_counter_vpAs__counter_vpAs_0_0 = Init_counter_vpAs;
				} else {
					// ifElse97
					if (VP_AS__global_0_0_copy_counter_vpAs_local.value == present) {
						state_counter_vpAs__counter_vpAs_0_0 = state_counter_vpAs__counter_vpAs_0_0 + 1;
						if (state_counter_vpAs__counter_vpAs_0_0 == E8) {
							state_counter_vpAs__counter_vpAs_0_0 = Init_counter_vpAs;
							TPVARP__global_0_0_copy_counter_vpAs_local.value = T_500__global_0_0;
							TPVARP__global_0_0_copy_counter_vpAs_local.status = FOREC_SHARED_MODIFIED;
						} else {
							// ifElse95
							
						}
					} else {
						// ifElse96
						
					}
				}
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.

			TPVARP__global_0_0_copy_counter_vpAs = TPVARP__global_0_0_copy_counter_vpAs_local;			// forec:statement:pause:pause10:start
			counter_vpAs__thread.programCounter = &&pause10;
			goto *counter_vpAs__thread.nextThread -> programCounter;
			pause10:;
			// forec:statement:pause:pause10:end
			// Update the values of the used shared variables from their global copy.
			VP_AS__global_0_0_copy_counter_vpAs_local = VP_AS__global_0_0;
			Reset__global_0_0_copy_counter_vpAs_local = Reset__global_0_0;
			TPVARP__global_0_0_copy_counter_vpAs_local.status = FOREC_SHARED_UNMODIFIED;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		TPVARP__global_0_0_copy_counter_vpAs = TPVARP__global_0_0_copy_counter_vpAs_local;

		// forec:scheduler:threadRemove:counter_vpAs:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		counter_vpAs__thread.nextThread -> prevThread = counter_vpAs__thread.prevThread;
		counter_vpAs__thread.prevThread -> nextThread = counter_vpAs__thread.nextThread;
		goto *counter_vpAs__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:counter_vpAs:end
	} // counter_vpAs__thread
	// forec:thread:counter_vpAs:end

	// forec:thread:duration_ms:start
	/*--------------------------------------------------------------
	| Thread duration_ms
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	enum State__duration_ms_0_0 {
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
	} state_duration_ms__duration_ms_0_0;
	Shared_VP__global_0_0 VP__global_0_0_copy_duration_ms_local;
	Shared_VS__global_0_0 VS__global_0_0_copy_duration_ms_local;
	Shared_D_Beg__global_0_0 D_Beg__global_0_0_copy_duration_ms_local;
	Shared_D_End__global_0_0 D_End__global_0_0_copy_duration_ms_local;

	// Thread body -------------------------------------------------
	duration_ms__thread: {
		// Initialise the local copies of shared variables.
		VP__global_0_0_copy_duration_ms_local.value = VP__global_0_0_copy_main.value;
		VP__global_0_0_copy_duration_ms_local.status = FOREC_SHARED_UNMODIFIED;
		VS__global_0_0_copy_duration_ms_local.value = VS__global_0_0_copy_main.value;
		VS__global_0_0_copy_duration_ms_local.status = FOREC_SHARED_UNMODIFIED;
		D_Beg__global_0_0_copy_duration_ms_local.value = D_Beg__global_0_0_copy_main.value;
		D_Beg__global_0_0_copy_duration_ms_local.status = FOREC_SHARED_UNMODIFIED;
		D_End__global_0_0_copy_duration_ms_local.value = D_End__global_0_0.value;
		D_End__global_0_0_copy_duration_ms_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		state_duration_ms__duration_ms_0_0 = Init_duration_ms;

		while (1) {
			printf("duration_ms\n");
			D_End__global_0_0_copy_duration_ms_local.value = absent;
			D_End__global_0_0_copy_duration_ms_local.status = FOREC_SHARED_MODIFIED;
			if (state_duration_ms__duration_ms_0_0 == Init_duration_ms) {
				if (D_Beg__global_0_0_copy_duration_ms_local.value == present) {
					state_duration_ms__duration_ms_0_0 = V1;
				} else {
					// ifElse84
					
				}
			} else {
				// ifElse87
				if ((VS__global_0_0_copy_duration_ms_local.value == present) || (VP__global_0_0_copy_duration_ms_local.value == present)) {
					state_duration_ms__duration_ms_0_0 = state_duration_ms__duration_ms_0_0 + 1;
					if (state_duration_ms__duration_ms_0_0 == V9) {
						state_duration_ms__duration_ms_0_0 = Init_duration_ms;
						D_End__global_0_0_copy_duration_ms_local.value = present;
						D_End__global_0_0_copy_duration_ms_local.status = FOREC_SHARED_MODIFIED;
					} else {
						// ifElse85
						
					}
				} else {
					// ifElse86
					
				}
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.

			D_End__global_0_0_copy_duration_ms = D_End__global_0_0_copy_duration_ms_local;			// forec:statement:pause:pause8:start
			duration_ms__thread.programCounter = &&pause8;
			goto *duration_ms__thread.nextThread -> programCounter;
			pause8:;
			// forec:statement:pause:pause8:end
			// Update the values of the used shared variables from their global copy.
			VP__global_0_0_copy_duration_ms_local = VP__global_0_0;
			VS__global_0_0_copy_duration_ms_local = VS__global_0_0;
			D_Beg__global_0_0_copy_duration_ms_local = D_Beg__global_0_0;
			D_End__global_0_0_copy_duration_ms_local.status = FOREC_SHARED_UNMODIFIED;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		D_End__global_0_0_copy_duration_ms = D_End__global_0_0_copy_duration_ms_local;

		// forec:scheduler:threadRemove:duration_ms:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		duration_ms__thread.nextThread -> prevThread = duration_ms__thread.prevThread;
		duration_ms__thread.prevThread -> nextThread = duration_ms__thread.nextThread;
		goto *duration_ms__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:duration_ms:end
	} // duration_ms__thread
	// forec:thread:duration_ms:end

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
				// ifElse3
				if (timer_rhm_a__ekgSensing_0_0 > Aminwait__global_0_0) {
					A_Get__global_0_0_copy_ekgSensing_local.value = present;
					A_Get__global_0_0_copy_ekgSensing_local.status = FOREC_SHARED_MODIFIED;
				} else {
					// ifElse2
					
				}
			}
			printf("rhm_v\n");
			timer_rhm_v__ekgSensing_0_0 = timer_rhm_v__ekgSensing_0_0 + 1;
			if ((V_Act__global_0_0_copy_ekgSensing_local.value == present) || (VP__global_0_0_copy_ekgSensing_local.value == present)) {
				timer_rhm_v__ekgSensing_0_0 = 0;
			} else {
				// ifElse5
				if (timer_rhm_v__ekgSensing_0_0 > Vminwait__global_0_0) {
					V_Get__global_0_0_copy_ekgSensing_local.value = present;
					V_Get__global_0_0_copy_ekgSensing_local.status = FOREC_SHARED_MODIFIED;
				} else {
					// ifElse4
					
				}
			}
			printf("conduction\n");
			timer_conduction__ekgSensing_0_0 = timer_conduction__ekgSensing_0_0 + 1;
			if (state_conduction__ekgSensing_0_0 == Init_conduction) {
				if ((A_Get__global_0_0_copy_ekgSensing_local.value == present) || (AP__global_0_0_copy_ekgSensing_local.value == present)) {
					state_conduction__ekgSensing_0_0 = Ante;
					timer_conduction__ekgSensing_0_0 = 0;
				} else {
					// ifElse8
					if ((V_Get__global_0_0_copy_ekgSensing_local.value == present) || (VP__global_0_0_copy_ekgSensing_local.value == present)) {
						state_conduction__ekgSensing_0_0 = Retro;
						timer_conduction__ekgSensing_0_0 = 0;
					} else {
						// ifElse7
						if ((A_Get__global_0_0_copy_ekgSensing_local.value == present) || (AP__global_0_0_copy_ekgSensing_local.value == present) || (V_Get__global_0_0_copy_ekgSensing_local.value == present) || (VP__global_0_0_copy_ekgSensing_local.value == present)) {
							state_conduction__ekgSensing_0_0 = Init_conduction;
						} else {
							// ifElse6
							
						}
					}
				}
			} else {
				// ifElse15
				if (state_conduction__ekgSensing_0_0 == Ante) {
					if ((V_Get__global_0_0_copy_ekgSensing_local.value == present) || (VP__global_0_0_copy_ekgSensing_local.value == present)) {
						state_conduction__ekgSensing_0_0 = Init_conduction;
					} else {
						// ifElse10
						if (timer_conduction__ekgSensing_0_0 >= Tantemin__global_0_0) {
							state_conduction__ekgSensing_0_0 = Init_conduction;
							V_Act__global_0_0_copy_ekgSensing_local.value = present;
							V_Act__global_0_0_copy_ekgSensing_local.status = FOREC_SHARED_MODIFIED;
						} else {
							// ifElse9
							
						}
					}
				} else {
					// ifElse14
					if (state_conduction__ekgSensing_0_0 == Retro) {
						if ((A_Get__global_0_0_copy_ekgSensing_local.value == present) || (AP__global_0_0_copy_ekgSensing_local.value == present)) {
							state_conduction__ekgSensing_0_0 = Init_conduction;
						} else {
							// ifElse12
							if (timer_conduction__ekgSensing_0_0 >= Tretromin__global_0_0) {
								state_conduction__ekgSensing_0_0 = Init_conduction;
								A_Act__global_0_0_copy_ekgSensing_local.value = present;
								A_Act__global_0_0_copy_ekgSensing_local.status = FOREC_SHARED_MODIFIED;
							} else {
								// ifElse11
								
							}
						}
					} else {
						// ifElse13
						printf("conduction: In an undefined state (%d)\n", state_conduction__ekgSensing_0_0);
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

	// forec:thread:interval_ms:start
	/*--------------------------------------------------------------
	| Thread interval_ms
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	enum State__interval_ms_0_0 {
		Init_interval_ms = 0,
		Wait
	} state_interval_ms__interval_ms_0_0;

	unsigned int timer_interval_ms__interval_ms_0_0;
	Shared_AP__global_0_0 AP__global_0_0_copy_interval_ms_local;
	Shared_AS__global_0_0 AS__global_0_0_copy_interval_ms_local;
	Shared_AR__global_0_0 AR__global_0_0_copy_interval_ms_local;
	Shared_Fast__global_0_0 Fast__global_0_0_copy_interval_ms_local;
	Shared_Slow__global_0_0 Slow__global_0_0_copy_interval_ms_local;

	// Thread body -------------------------------------------------
	interval_ms__thread: {
		// Initialise the local copies of shared variables.
		AP__global_0_0_copy_interval_ms_local.value = AP__global_0_0_copy_main.value;
		AP__global_0_0_copy_interval_ms_local.status = FOREC_SHARED_UNMODIFIED;
		AS__global_0_0_copy_interval_ms_local.value = AS__global_0_0_copy_main.value;
		AS__global_0_0_copy_interval_ms_local.status = FOREC_SHARED_UNMODIFIED;
		AR__global_0_0_copy_interval_ms_local.value = AR__global_0_0_copy_main.value;
		AR__global_0_0_copy_interval_ms_local.status = FOREC_SHARED_UNMODIFIED;
		Fast__global_0_0_copy_interval_ms_local.value = Fast__global_0_0.value;
		Fast__global_0_0_copy_interval_ms_local.status = FOREC_SHARED_UNMODIFIED;
		Slow__global_0_0_copy_interval_ms_local.value = Slow__global_0_0.value;
		Slow__global_0_0_copy_interval_ms_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		state_interval_ms__interval_ms_0_0 = Init_interval_ms;
		timer_interval_ms__interval_ms_0_0 = 0;

		while (1) {
			printf("interval_ms\n");
			timer_interval_ms__interval_ms_0_0 = timer_interval_ms__interval_ms_0_0 + 1;
			Fast__global_0_0_copy_interval_ms_local.value = absent;
			Fast__global_0_0_copy_interval_ms_local.status = FOREC_SHARED_MODIFIED;
			Slow__global_0_0_copy_interval_ms_local.value = absent;
			Slow__global_0_0_copy_interval_ms_local.status = FOREC_SHARED_MODIFIED;
			if (state_interval_ms__interval_ms_0_0 == Init_interval_ms) {
				if ((AP__global_0_0_copy_interval_ms_local.value == present) || (AR__global_0_0_copy_interval_ms_local.value == present) || (AS__global_0_0_copy_interval_ms_local.value == present)) {
					state_interval_ms__interval_ms_0_0 = Wait;
					timer_interval_ms__interval_ms_0_0 = 0;
				} else {
					// ifElse64
					
				}
			} else {
				// ifElse70
				if (state_interval_ms__interval_ms_0_0 == Wait) {
					if ((AR__global_0_0_copy_interval_ms_local.value == present) || (AS__global_0_0_copy_interval_ms_local.value == present)) {
						if (timer_interval_ms__interval_ms_0_0 <= Threshold__global_0_0) {
							state_interval_ms__interval_ms_0_0 = Wait;
							Fast__global_0_0_copy_interval_ms_local.value = present;
							Fast__global_0_0_copy_interval_ms_local.status = FOREC_SHARED_MODIFIED;
							timer_interval_ms__interval_ms_0_0 = 0;
						} else {
							// ifElse66
							if (timer_interval_ms__interval_ms_0_0 > Threshold__global_0_0) {
								state_interval_ms__interval_ms_0_0 = Wait;
								Slow__global_0_0_copy_interval_ms_local.value = present;
								Slow__global_0_0_copy_interval_ms_local.status = FOREC_SHARED_MODIFIED;
								timer_interval_ms__interval_ms_0_0 = 0;
							} else {
								// ifElse65
								
							}
						}
					} else {
						// ifElse68
						if (AP__global_0_0_copy_interval_ms_local.value == present) {
							state_interval_ms__interval_ms_0_0 = Wait;
							Slow__global_0_0_copy_interval_ms_local.value = present;
							Slow__global_0_0_copy_interval_ms_local.status = FOREC_SHARED_MODIFIED;
							timer_interval_ms__interval_ms_0_0 = 0;
						} else {
							// ifElse67
							
						}
					}
				} else {
					// ifElse69
					printf("interval_ms: In an undefined state (%d)\n", state_interval_ms__interval_ms_0_0);
				}
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.

			Fast__global_0_0_copy_interval_ms = Fast__global_0_0_copy_interval_ms_local;
			Slow__global_0_0_copy_interval_ms = Slow__global_0_0_copy_interval_ms_local;			// forec:statement:pause:pause6:start
			interval_ms__thread.programCounter = &&pause6;
			goto *interval_ms__thread.nextThread -> programCounter;
			pause6:;
			// forec:statement:pause:pause6:end
			// Update the values of the used shared variables from their global copy.
			AP__global_0_0_copy_interval_ms_local = AP__global_0_0;
			AS__global_0_0_copy_interval_ms_local = AS__global_0_0;
			AR__global_0_0_copy_interval_ms_local = AR__global_0_0;
			Fast__global_0_0_copy_interval_ms_local.status = FOREC_SHARED_UNMODIFIED;
			Slow__global_0_0_copy_interval_ms_local.status = FOREC_SHARED_UNMODIFIED;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		Fast__global_0_0_copy_interval_ms = Fast__global_0_0_copy_interval_ms_local;
		Slow__global_0_0_copy_interval_ms = Slow__global_0_0_copy_interval_ms_local;

		// forec:scheduler:threadRemove:interval_ms:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		interval_ms__thread.nextThread -> prevThread = interval_ms__thread.prevThread;
		interval_ms__thread.prevThread -> nextThread = interval_ms__thread.nextThread;
		goto *interval_ms__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:interval_ms:end
	} // interval_ms__thread
	// forec:thread:interval_ms:end

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
	Shared_A_Block__global_0_0 A_Block__global_0_0_copy_logging_local;
	Shared_V_Block__global_0_0 V_Block__global_0_0_copy_logging_local;
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
		A_Block__global_0_0_copy_logging_local.value = A_Block__global_0_0_copy_main.value;
		A_Block__global_0_0_copy_logging_local.status = FOREC_SHARED_UNMODIFIED;
		V_Block__global_0_0_copy_logging_local.value = V_Block__global_0_0_copy_main.value;
		V_Block__global_0_0_copy_logging_local.status = FOREC_SHARED_UNMODIFIED;
		log__global_0_0_copy_logging_local.value = log__global_0_0.value;
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
					// ifElse99
					
				}
			} else {
				// ifElse103
				if (state_lrl__logging_0_0 == Wait_lrl) {
					if ((VS__global_0_0_copy_logging_local.value == present) || (VP__global_0_0_copy_logging_local.value == present)) {
						state_lrl__logging_0_0 = Wait_lrl;
						if (timer_lrl__logging_0_0 > TLRI__global_0_0_copy_logging_local.value) {
							violated__logging_0_0 = present;
							event__logging_0_0.lrl = present;
						} else {
							// if100
						}
						timer_lrl__logging_0_0 = 0;
					} else {
						// ifElse101
						
					}
				} else {
					// ifElse102
					printf("lrl: In an undefined state (%d)\n", state_lrl__logging_0_0);
				}
			}
			printf("url\n");
			timer_url__logging_0_0 = timer_url__logging_0_0 + 1;
			if (state_url__logging_0_0 == Init_url) {
				if ((VS__global_0_0_copy_logging_local.value == present) || (VP__global_0_0_copy_logging_local.value == present)) {
					state_url__logging_0_0 = Wait_url;
					timer_url__logging_0_0 = 0;
				} else {
					// ifElse104
					
				}
			} else {
				// ifElse109
				if (state_url__logging_0_0 == Wait_url) {
					if (VS__global_0_0_copy_logging_local.value == present) {
						state_url__logging_0_0 = Wait_url;
						timer_url__logging_0_0 = 0;
					} else {
						// ifElse107
						if (VP__global_0_0_copy_logging_local.value == present) {
							state_url__logging_0_0 = Wait_url;
							if (timer_url__logging_0_0 < TLRI__global_0_0_copy_logging_local.value) {
								violated__logging_0_0 = present;
								event__logging_0_0.url = present;
							} else {
								// if105
							}
							timer_url__logging_0_0 = 0;
						} else {
							// ifElse106
							
						}
					}
				} else {
					// ifElse108
					printf("url: In an undefined state (%d)\n", state_url__logging_0_0);
				}
			}
			printf("pmt\n");
			timer_pmt__logging_0_0 = timer_pmt__logging_0_0 + 1;
			if (state_pmt__logging_0_0 == Init_pmt) {
				if ((VS__global_0_0_copy_logging_local.value == present) || (VP__global_0_0_copy_logging_local.value == present)) {
					state_pmt__logging_0_0 = Wait_pmt;
					timer_pmt__logging_0_0 = 0;
				} else {
					// ifElse110
					
				}
			} else {
				// ifElse114
				if (state_pmt__logging_0_0 == Wait_pmt) {
					if ((VS__global_0_0_copy_logging_local.value == present) || (VP__global_0_0_copy_logging_local.value == present)) {
						state_pmt__logging_0_0 = Wait_pmt;
						if (timer_pmt__logging_0_0 > TLRI__global_0_0_copy_logging_local.value) {
							violated__logging_0_0 = present;
							event__logging_0_0.pmt = present;
						} else {
							// if111
						}
						timer_pmt__logging_0_0 = 0;
					} else {
						// ifElse112
						
					}
				} else {
					// ifElse113
					printf("pmt: In an undefined state (%d)\n", state_pmt__logging_0_0);
				}
			}
			printf("ms\n");
			if (VDI__global_0_0_copy_logging_local.value == present) {
				violated__logging_0_0 = present;
			} else {
				// ifElse115
				
			}
			printf("vurl\n");
			timer_vurl__logging_0_0 = timer_vurl__logging_0_0 + 1;
			if (state_vurl__logging_0_0 == Init_vurl) {
				if (VP__global_0_0_copy_logging_local.value == present) {
					state_vurl__logging_0_0 = V_vurl;
					timer_vurl__logging_0_0 = 0;
				} else {
					// ifElse116
					
				}
			} else {
				// ifElse121
				if (state_vurl__logging_0_0 == V_vurl) {
					if (VP__global_0_0_copy_logging_local.value == present) {
						if (timer_vurl__logging_0_0 <= TURI__global_0_0_copy_logging_local.value) {
							state_vurl__logging_0_0 = V_vurl;
						} else {
							// ifElse117
							state_vurl__logging_0_0 = Error_vurl;
							violated__logging_0_0 = present;
							event__logging_0_0.vurl = present;
						}
						timer_vurl__logging_0_0 = 0;
					} else {
						// ifElse118
						
					}
				} else {
					// ifElse120
					if (state_vurl__logging_0_0 == Error_vurl) {
						state_vurl__logging_0_0 = Error_vurl;
						violated__logging_0_0 = present;
						event__logging_0_0.vurl = present;
						timer_vurl__logging_0_0 = 0;
					} else {
						// ifElse119
						printf("vurl: In an undefined state (%d)\n", state_vurl__logging_0_0);
					}
				}
			}
			printf("elt\n");
			if (state_elt__logging_0_0 == Init_elt) {
				if (AS__global_0_0_copy_logging_local.value == present) {
					state_elt__logging_0_0 = AS_elt;
				} else {
					// ifElse124
					if ((AP__global_0_0_copy_logging_local.value == present) || (AR__global_0_0_copy_logging_local.value == present) || (A_Block__global_0_0_copy_logging_local.value == present) || (V_Block__global_0_0_copy_logging_local.value == present)) {
						state_elt__logging_0_0 = Error_elt;
					} else {
						// ifElse123
						if (VP__global_0_0_copy_logging_local.value == present) {
							state_elt__logging_0_0 = VP_elt;
						} else {
							// ifElse122
							
						}
					}
				}
			} else {
				// ifElse132
				if (state_elt__logging_0_0 == AS_elt) {
					if ((AS__global_0_0_copy_logging_local.value == present) || (AP__global_0_0_copy_logging_local.value == present) || (AR__global_0_0_copy_logging_local.value == present) || (A_Block__global_0_0_copy_logging_local.value == present) || (VS__global_0_0_copy_logging_local.value == present) || (V_Block__global_0_0_copy_logging_local.value == present)) {
						state_elt__logging_0_0 = Error_elt;
					} else {
						// ifElse126
						if (VP__global_0_0_copy_logging_local.value == present) {
							state_elt__logging_0_0 = VP_elt;
						} else {
							// ifElse125
							
						}
					}
				} else {
					// ifElse131
					if (state_elt__logging_0_0 == VP_elt) {
						if ((VS__global_0_0_copy_logging_local.value == present) || (VP__global_0_0_copy_logging_local.value == present) || (AP__global_0_0_copy_logging_local.value == present) || (AR__global_0_0_copy_logging_local.value == present) || (A_Block__global_0_0_copy_logging_local.value == present) || (V_Block__global_0_0_copy_logging_local.value == present)) {
							state_elt__logging_0_0 = Error_elt;
						} else {
							// ifElse128
							if (AS__global_0_0_copy_logging_local.value == present) {
								state_elt__logging_0_0 = AS_elt;
							} else {
								// ifElse127
								
							}
						}
					} else {
						// ifElse130
						if (state_elt__logging_0_0 == Error_elt) {
							state_elt__logging_0_0 = Error_elt;
							violated__logging_0_0 = present;
							event__logging_0_0.elt = present;
						} else {
							// ifElse129
							printf("elt: In an undefined state (%d)\n", state_elt__logging_0_0);
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
				// if133
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.

			log__global_0_0 = log__global_0_0_copy_logging_local;			// forec:statement:pause:pause11:start
			logging__thread.programCounter = &&pause11;
			goto *logging__thread.nextThread -> programCounter;
			pause11:;
			// forec:statement:pause:pause11:end
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
			A_Block__global_0_0_copy_logging_local = A_Block__global_0_0;
			V_Block__global_0_0_copy_logging_local = V_Block__global_0_0;
			log__global_0_0_copy_logging_local = log__global_0_0;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		log__global_0_0.value = log__global_0_0_copy_logging_local.value;

		// forec:scheduler:threadRemove:logging:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		logging__thread.nextThread -> prevThread = logging__thread.prevThread;
		logging__thread.prevThread -> nextThread = logging__thread.nextThread;
		goto *logging__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:logging:end
	} // logging__thread
	// forec:thread:logging:end

	// forec:thread:lri_ms:start
	/*--------------------------------------------------------------
	| Thread lri_ms
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	enum State__lri_ms_0_0 {
		Init_lri_ms = 0,
		Sensed,
		VDI_LRI
	} state_lri_ms__lri_ms_0_0;

	unsigned int timer_lri_ms__lri_ms_0_0;
	Signal__global_0_0 VP_new__lri_ms_0_0;
	Shared_TLRI__global_0_0 TLRI__global_0_0_copy_lri_ms_local;
	Shared_TAVI__global_0_0 TAVI__global_0_0_copy_lri_ms_local;
	Shared_AP__global_0_0 AP__global_0_0_copy_lri_ms_local;
	Shared_VP__global_0_0 VP__global_0_0_copy_lri_ms_local;
	Shared_AS__global_0_0 AS__global_0_0_copy_lri_ms_local;
	Shared_VS__global_0_0 VS__global_0_0_copy_lri_ms_local;
	Shared_DDD__global_0_0 DDD__global_0_0_copy_lri_ms_local;
	Shared_VDI__global_0_0 VDI__global_0_0_copy_lri_ms_local;

	// Thread body -------------------------------------------------
	lri_ms__thread: {
		// Initialise the local copies of shared variables.
		TLRI__global_0_0_copy_lri_ms_local.value = TLRI__global_0_0.value;
		TLRI__global_0_0_copy_lri_ms_local.status = FOREC_SHARED_UNMODIFIED;
		TAVI__global_0_0_copy_lri_ms_local.value = TAVI__global_0_0.value;
		TAVI__global_0_0_copy_lri_ms_local.status = FOREC_SHARED_UNMODIFIED;
		VP__global_0_0_copy_lri_ms_local.value = VP__global_0_0_copy_main.value;
		VP__global_0_0_copy_lri_ms_local.status = FOREC_SHARED_UNMODIFIED;
		AS__global_0_0_copy_lri_ms_local.value = AS__global_0_0_copy_main.value;
		AS__global_0_0_copy_lri_ms_local.status = FOREC_SHARED_UNMODIFIED;
		VS__global_0_0_copy_lri_ms_local.value = VS__global_0_0_copy_main.value;
		VS__global_0_0_copy_lri_ms_local.status = FOREC_SHARED_UNMODIFIED;
		DDD__global_0_0_copy_lri_ms_local.value = DDD__global_0_0_copy_main.value;
		DDD__global_0_0_copy_lri_ms_local.status = FOREC_SHARED_UNMODIFIED;
		VDI__global_0_0_copy_lri_ms_local.value = VDI__global_0_0_copy_main.value;
		VDI__global_0_0_copy_lri_ms_local.status = FOREC_SHARED_UNMODIFIED;
		AP__global_0_0_copy_lri_ms_local.value = AP__global_0_0.value;
		AP__global_0_0_copy_lri_ms_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		state_lri_ms__lri_ms_0_0 = Init_lri_ms;
		timer_lri_ms__lri_ms_0_0 = 0;
		VP_new__lri_ms_0_0 = absent;

		while (1) {
			printf("lri_ms\n");
			timer_lri_ms__lri_ms_0_0 = timer_lri_ms__lri_ms_0_0 + 1;
			AP__global_0_0_copy_lri_ms_local.value = absent;
			AP__global_0_0_copy_lri_ms_local.status = FOREC_SHARED_MODIFIED;
			VP_new__lri_ms_0_0 = absent;
			if (state_lri_ms__lri_ms_0_0 == Init_lri_ms) {
				if ((VP__global_0_0_copy_lri_ms_local.value == present) || (VS__global_0_0_copy_lri_ms_local.value == present)) {
					state_lri_ms__lri_ms_0_0 = Init_lri_ms;
					timer_lri_ms__lri_ms_0_0 = 0;
				} else {
					// ifElse19
					if (timer_lri_ms__lri_ms_0_0 >= (TLRI__global_0_0_copy_lri_ms_local.value - TAVI__global_0_0_copy_lri_ms_local.value)) {
						state_lri_ms__lri_ms_0_0 = Init_lri_ms;
						AP__global_0_0_copy_lri_ms_local.value = present;
						AP__global_0_0_copy_lri_ms_local.status = FOREC_SHARED_MODIFIED;
					} else {
						// ifElse18
						if (AS__global_0_0_copy_lri_ms_local.value == present) {
							state_lri_ms__lri_ms_0_0 = Sensed;
						} else {
							// ifElse17
							if (VDI__global_0_0_copy_lri_ms_local.value == present) {
								state_lri_ms__lri_ms_0_0 = VDI_LRI;
							} else {
								// ifElse16
								
							}
						}
					}
				}
			} else {
				// ifElse27
				if (state_lri_ms__lri_ms_0_0 == VDI_LRI) {
					if (VS__global_0_0_copy_lri_ms_local.value == VDI_LRI) {
						state_lri_ms__lri_ms_0_0 = Init_lri_ms;
						timer_lri_ms__lri_ms_0_0 = 0;
					} else {
						// ifElse22
						if (timer_lri_ms__lri_ms_0_0 >= TLRI__global_0_0_copy_lri_ms_local.value) {
							state_lri_ms__lri_ms_0_0 = Init_lri_ms;
							VP_new__lri_ms_0_0 = present;
						} else {
							// ifElse21
							if (DDD__global_0_0_copy_lri_ms_local.value == present) {
								state_lri_ms__lri_ms_0_0 = Init_lri_ms;
								timer_lri_ms__lri_ms_0_0 = 0;
							} else {
								// if20
							}
						}
					}
				} else {
					// ifElse26
					if (state_lri_ms__lri_ms_0_0 == Sensed) {
						if (VDI__global_0_0_copy_lri_ms_local.value == present) {
							state_lri_ms__lri_ms_0_0 = VDI_LRI;
						} else {
							// ifElse24
							if ((VP__global_0_0_copy_lri_ms_local.value == present) || (VS__global_0_0_copy_lri_ms_local.value == present)) {
								state_lri_ms__lri_ms_0_0 = Init_lri_ms;
								timer_lri_ms__lri_ms_0_0 = 0;
							} else {
								// ifElse23
								
							}
						}
					} else {
						// ifElse25
						printf("lri_ms: In an undefined state (%d)\n", state_lri_ms__lri_ms_0_0);
					}
				}
			}
			VP__global_0_0_copy_lri_ms_local.value = VP_new__lri_ms_0_0;
			VP__global_0_0_copy_lri_ms_local.status = FOREC_SHARED_MODIFIED;

			// pause;
			// Write the local copy of shared variables back to their global copy.

			AP__global_0_0_copy_lri_ms = AP__global_0_0_copy_lri_ms_local;
			VP__global_0_0_copy_lri_ms = VP__global_0_0_copy_lri_ms_local;			// forec:statement:pause:pause1:start
			lri_ms__thread.programCounter = &&pause1;
			goto *lri_ms__thread.nextThread -> programCounter;
			pause1:;
			// forec:statement:pause:pause1:end
			// Update the values of the used shared variables from their global copy.
			TLRI__global_0_0_copy_lri_ms_local = TLRI__global_0_0;
			TAVI__global_0_0_copy_lri_ms_local = TAVI__global_0_0;
			VP__global_0_0_copy_lri_ms_local = VP__global_0_0;
			AS__global_0_0_copy_lri_ms_local = AS__global_0_0;
			VS__global_0_0_copy_lri_ms_local = VS__global_0_0;
			DDD__global_0_0_copy_lri_ms_local = DDD__global_0_0;
			VDI__global_0_0_copy_lri_ms_local = VDI__global_0_0;
			AP__global_0_0_copy_lri_ms_local.status = FOREC_SHARED_UNMODIFIED;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		AP__global_0_0_copy_lri_ms = AP__global_0_0_copy_lri_ms_local;
		VP__global_0_0_copy_lri_ms = VP__global_0_0_copy_lri_ms_local;

		// forec:scheduler:threadRemove:lri_ms:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		lri_ms__thread.nextThread -> prevThread = lri_ms__thread.prevThread;
		lri_ms__thread.prevThread -> nextThread = lri_ms__thread.nextThread;
		goto *lri_ms__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:lri_ms:end
	} // lri_ms__thread
	// forec:thread:lri_ms:end

	// forec:thread:pattern_vpAs:start
	/*--------------------------------------------------------------
	| Thread pattern_vpAs
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	enum State__pattern_vpAs_0_0 {
		Init_pattern_vpAs = 0,
		VP1
	} state_pattern_vpAs__pattern_vpAs_0_0;

	unsigned int timer_pattern_vpAs__pattern_vpAs_0_0;
	Shared_AP__global_0_0 AP__global_0_0_copy_pattern_vpAs_local;
	Shared_VP__global_0_0 VP__global_0_0_copy_pattern_vpAs_local;
	Shared_AS__global_0_0 AS__global_0_0_copy_pattern_vpAs_local;
	Shared_AR__global_0_0 AR__global_0_0_copy_pattern_vpAs_local;
	Shared_VS__global_0_0 VS__global_0_0_copy_pattern_vpAs_local;
	Shared_VP_AS__global_0_0 VP_AS__global_0_0_copy_pattern_vpAs_local;
	Shared_Reset__global_0_0 Reset__global_0_0_copy_pattern_vpAs_local;

	// Thread body -------------------------------------------------
	pattern_vpAs__thread: {
		// Initialise the local copies of shared variables.
		AP__global_0_0_copy_pattern_vpAs_local.value = AP__global_0_0_copy_main.value;
		AP__global_0_0_copy_pattern_vpAs_local.status = FOREC_SHARED_UNMODIFIED;
		VP__global_0_0_copy_pattern_vpAs_local.value = VP__global_0_0_copy_main.value;
		VP__global_0_0_copy_pattern_vpAs_local.status = FOREC_SHARED_UNMODIFIED;
		AS__global_0_0_copy_pattern_vpAs_local.value = AS__global_0_0_copy_main.value;
		AS__global_0_0_copy_pattern_vpAs_local.status = FOREC_SHARED_UNMODIFIED;
		AR__global_0_0_copy_pattern_vpAs_local.value = AR__global_0_0_copy_main.value;
		AR__global_0_0_copy_pattern_vpAs_local.status = FOREC_SHARED_UNMODIFIED;
		VS__global_0_0_copy_pattern_vpAs_local.value = VS__global_0_0_copy_main.value;
		VS__global_0_0_copy_pattern_vpAs_local.status = FOREC_SHARED_UNMODIFIED;
		VP_AS__global_0_0_copy_pattern_vpAs_local.value = VP_AS__global_0_0.value;
		VP_AS__global_0_0_copy_pattern_vpAs_local.status = FOREC_SHARED_UNMODIFIED;
		Reset__global_0_0_copy_pattern_vpAs_local.value = Reset__global_0_0.value;
		Reset__global_0_0_copy_pattern_vpAs_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		state_pattern_vpAs__pattern_vpAs_0_0 = Init_pattern_vpAs;
		timer_pattern_vpAs__pattern_vpAs_0_0 = 0;

		while (1) {
			printf("pattern_vpAs\n");
			timer_pattern_vpAs__pattern_vpAs_0_0 = timer_pattern_vpAs__pattern_vpAs_0_0 + 1;
			VP_AS__global_0_0_copy_pattern_vpAs_local.value = absent;
			VP_AS__global_0_0_copy_pattern_vpAs_local.status = FOREC_SHARED_MODIFIED;
			Reset__global_0_0_copy_pattern_vpAs_local.value = absent;
			Reset__global_0_0_copy_pattern_vpAs_local.status = FOREC_SHARED_MODIFIED;
			if (state_pattern_vpAs__pattern_vpAs_0_0 == Init_pattern_vpAs) {
				if (VP__global_0_0_copy_pattern_vpAs_local.value == present) {
					state_pattern_vpAs__pattern_vpAs_0_0 = VP1;
					timer_pattern_vpAs__pattern_vpAs_0_0 = 0;
				} else {
					// ifElse88
					
				}
			} else {
				// ifElse93
				if (state_pattern_vpAs__pattern_vpAs_0_0 == VP1) {
					if (AS__global_0_0_copy_pattern_vpAs_local.value == present) {
						if (T_150__global_0_0 <= timer_pattern_vpAs__pattern_vpAs_0_0 && timer_pattern_vpAs__pattern_vpAs_0_0 <= T_200__global_0_0) {
							VP_AS__global_0_0_copy_pattern_vpAs_local.value = present;
							VP_AS__global_0_0_copy_pattern_vpAs_local.status = FOREC_SHARED_MODIFIED;
						} else {
							// ifElse89
							
						}
					} else {
						// ifElse91
						if ((VS__global_0_0_copy_pattern_vpAs_local.value == present) || (AP__global_0_0_copy_pattern_vpAs_local.value == present) || (AR__global_0_0_copy_pattern_vpAs_local.value == present)) {
							Reset__global_0_0_copy_pattern_vpAs_local.value = present;
							Reset__global_0_0_copy_pattern_vpAs_local.status = FOREC_SHARED_MODIFIED;
						} else {
							// if90
						}
					}
					state_pattern_vpAs__pattern_vpAs_0_0 = Init_pattern_vpAs;
				} else {
					// ifElse92
					printf("pattern_vpAs: In an undefined state (%d)\n", state_pattern_vpAs__pattern_vpAs_0_0);
				}
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.

			VP_AS__global_0_0_copy_pattern_vpAs = VP_AS__global_0_0_copy_pattern_vpAs_local;
			Reset__global_0_0_copy_pattern_vpAs = Reset__global_0_0_copy_pattern_vpAs_local;			// forec:statement:pause:pause9:start
			pattern_vpAs__thread.programCounter = &&pause9;
			goto *pattern_vpAs__thread.nextThread -> programCounter;
			pause9:;
			// forec:statement:pause:pause9:end
			// Update the values of the used shared variables from their global copy.
			AP__global_0_0_copy_pattern_vpAs_local = AP__global_0_0;
			VP__global_0_0_copy_pattern_vpAs_local = VP__global_0_0;
			AS__global_0_0_copy_pattern_vpAs_local = AS__global_0_0;
			AR__global_0_0_copy_pattern_vpAs_local = AR__global_0_0;
			VS__global_0_0_copy_pattern_vpAs_local = VS__global_0_0;
			VP_AS__global_0_0_copy_pattern_vpAs_local.status = FOREC_SHARED_UNMODIFIED;
			Reset__global_0_0_copy_pattern_vpAs_local.status = FOREC_SHARED_UNMODIFIED;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		VP_AS__global_0_0_copy_pattern_vpAs = VP_AS__global_0_0_copy_pattern_vpAs_local;
		Reset__global_0_0_copy_pattern_vpAs = Reset__global_0_0_copy_pattern_vpAs_local;

		// forec:scheduler:threadRemove:pattern_vpAs:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		pattern_vpAs__thread.nextThread -> prevThread = pattern_vpAs__thread.prevThread;
		pattern_vpAs__thread.prevThread -> nextThread = pattern_vpAs__thread.nextThread;
		goto *pattern_vpAs__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:pattern_vpAs:end
	} // pattern_vpAs__thread
	// forec:thread:pattern_vpAs:end

	// forec:thread:pvarp_elt:start
	/*--------------------------------------------------------------
	| Thread pvarp_elt
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	enum State__pvarp_elt_0_0 {
		Init_pvarp_elt = 0,
		PVAB,
		PVARP
	} state_pvarp_elt__pvarp_elt_0_0;

	unsigned int timer_pvarp_elt__pvarp_elt_0_0;
	Shared_TPVARP__global_0_0 TPVARP__global_0_0_copy_pvarp_elt_local;
	Shared_A_Get__global_0_0 A_Get__global_0_0_copy_pvarp_elt_local;
	Shared_A_Act__global_0_0 A_Act__global_0_0_copy_pvarp_elt_local;
	Shared_AS__global_0_0 AS__global_0_0_copy_pvarp_elt_local;
	Shared_AR__global_0_0 AR__global_0_0_copy_pvarp_elt_local;
	Shared_VS__global_0_0 VS__global_0_0_copy_pvarp_elt_local;
	Shared_A_Block__global_0_0 A_Block__global_0_0_copy_pvarp_elt_local;

	// Thread body -------------------------------------------------
	pvarp_elt__thread: {
		// Initialise the local copies of shared variables.
		TPVARP__global_0_0_copy_pvarp_elt_local.value = TPVARP__global_0_0_copy_main.value;
		TPVARP__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_UNMODIFIED;
		A_Get__global_0_0_copy_pvarp_elt_local.value = A_Get__global_0_0_copy_main.value;
		A_Get__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_UNMODIFIED;
		A_Act__global_0_0_copy_pvarp_elt_local.value = A_Act__global_0_0_copy_main.value;
		A_Act__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_UNMODIFIED;
		VS__global_0_0_copy_pvarp_elt_local.value = VS__global_0_0_copy_main.value;
		VS__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_UNMODIFIED;
		AS__global_0_0_copy_pvarp_elt_local.value = AS__global_0_0.value;
		AS__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_UNMODIFIED;
		AR__global_0_0_copy_pvarp_elt_local.value = AR__global_0_0.value;
		AR__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_UNMODIFIED;
		A_Block__global_0_0_copy_pvarp_elt_local.value = A_Block__global_0_0.value;
		A_Block__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		state_pvarp_elt__pvarp_elt_0_0 = Init_pvarp_elt;
		timer_pvarp_elt__pvarp_elt_0_0 = 0;

		while (1) {
			printf("pvarp_elt\n");
			timer_pvarp_elt__pvarp_elt_0_0 = timer_pvarp_elt__pvarp_elt_0_0 + 1;
			AS__global_0_0_copy_pvarp_elt_local.value = absent;
			AS__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_MODIFIED;
			AR__global_0_0_copy_pvarp_elt_local.value = absent;
			AR__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_MODIFIED;
			A_Block__global_0_0_copy_pvarp_elt_local.value = absent;
			A_Block__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_MODIFIED;
			if (state_pvarp_elt__pvarp_elt_0_0 == Init_pvarp_elt) {
				if ((A_Act__global_0_0_copy_pvarp_elt_local.value == present) || (A_Get__global_0_0_copy_pvarp_elt_local.value == present)) {
					state_pvarp_elt__pvarp_elt_0_0 = Init_pvarp_elt;
					AS__global_0_0_copy_pvarp_elt_local.value = present;
					AS__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_MODIFIED;
				} else {
					// ifElse50
					if ((VS__global_0_0_copy_pvarp_elt_local.value == present) || (VS__global_0_0_copy_pvarp_elt_local.value == present)) {
						state_pvarp_elt__pvarp_elt_0_0 = PVAB;
						timer_pvarp_elt__pvarp_elt_0_0 = 0;
					} else {
						// ifElse49
						
					}
				}
			} else {
				// ifElse57
				if (state_pvarp_elt__pvarp_elt_0_0 == PVAB) {
					if ((A_Act__global_0_0_copy_pvarp_elt_local.value == present) || (A_Get__global_0_0_copy_pvarp_elt_local.value == present)) {
						state_pvarp_elt__pvarp_elt_0_0 = PVAB;
						A_Block__global_0_0_copy_pvarp_elt_local.value = present;
						A_Block__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_MODIFIED;
					} else {
						// ifElse52
						if (timer_pvarp_elt__pvarp_elt_0_0 >= TPVAB__global_0_0) {
							state_pvarp_elt__pvarp_elt_0_0 = PVARP;
						} else {
							// ifElse51
							
						}
					}
				} else {
					// ifElse56
					if (state_pvarp_elt__pvarp_elt_0_0 == PVARP) {
						if ((A_Act__global_0_0_copy_pvarp_elt_local.value == present) || (A_Get__global_0_0_copy_pvarp_elt_local.value == present)) {
							state_pvarp_elt__pvarp_elt_0_0 = PVARP;
							AR__global_0_0_copy_pvarp_elt_local.value = present;
							AR__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_MODIFIED;
						} else {
							// ifElse54
							if (timer_pvarp_elt__pvarp_elt_0_0 >= TPVARP__global_0_0_copy_pvarp_elt_local.value) {
								state_pvarp_elt__pvarp_elt_0_0 = Init_pvarp_elt;
								TPVARP__global_0_0_copy_pvarp_elt_local.value = TPVARP_100__global_0_0;
								TPVARP__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_MODIFIED;
							} else {
								// ifElse53
								
							}
						}
					} else {
						// ifElse55
						printf("pvarp_elt: In an undefined state (%d)\n", state_pvarp_elt__pvarp_elt_0_0);
					}
				}
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.

			TPVARP__global_0_0_copy_pvarp_elt = TPVARP__global_0_0_copy_pvarp_elt_local;
			AS__global_0_0_copy_pvarp_elt = AS__global_0_0_copy_pvarp_elt_local;
			AR__global_0_0_copy_pvarp_elt = AR__global_0_0_copy_pvarp_elt_local;
			A_Block__global_0_0_copy_pvarp_elt = A_Block__global_0_0_copy_pvarp_elt_local;			// forec:statement:pause:pause4:start
			pvarp_elt__thread.programCounter = &&pause4;
			goto *pvarp_elt__thread.nextThread -> programCounter;
			pause4:;
			// forec:statement:pause:pause4:end
			// Update the values of the used shared variables from their global copy.
			TPVARP__global_0_0_copy_pvarp_elt_local = TPVARP__global_0_0;
			A_Get__global_0_0_copy_pvarp_elt_local = A_Get__global_0_0;
			A_Act__global_0_0_copy_pvarp_elt_local = A_Act__global_0_0;
			VS__global_0_0_copy_pvarp_elt_local = VS__global_0_0;
			AS__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_UNMODIFIED;
			AR__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_UNMODIFIED;
			A_Block__global_0_0_copy_pvarp_elt_local.status = FOREC_SHARED_UNMODIFIED;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		TPVARP__global_0_0_copy_pvarp_elt = TPVARP__global_0_0_copy_pvarp_elt_local;
		AS__global_0_0_copy_pvarp_elt = AS__global_0_0_copy_pvarp_elt_local;
		AR__global_0_0_copy_pvarp_elt = AR__global_0_0_copy_pvarp_elt_local;
		A_Block__global_0_0_copy_pvarp_elt = A_Block__global_0_0_copy_pvarp_elt_local;

		// forec:scheduler:threadRemove:pvarp_elt:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		pvarp_elt__thread.nextThread -> prevThread = pvarp_elt__thread.prevThread;
		pvarp_elt__thread.prevThread -> nextThread = pvarp_elt__thread.nextThread;
		goto *pvarp_elt__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:pvarp_elt:end
	} // pvarp_elt__thread
	// forec:thread:pvarp_elt:end

	// forec:thread:uri:start
	/*--------------------------------------------------------------
	| Thread uri
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_timer_uri__global_0_0 timer_uri__global_0_0_copy_uri_local;
	Shared_VP__global_0_0 VP__global_0_0_copy_uri_local;
	Shared_VS__global_0_0 VS__global_0_0_copy_uri_local;

	// Thread body -------------------------------------------------
	uri__thread: {
		// Initialise the local copies of shared variables.
		timer_uri__global_0_0_copy_uri_local.value = timer_uri__global_0_0_copy_main.value;
		timer_uri__global_0_0_copy_uri_local.status = FOREC_SHARED_UNMODIFIED;
		VP__global_0_0_copy_uri_local.value = VP__global_0_0_copy_main.value;
		VP__global_0_0_copy_uri_local.status = FOREC_SHARED_UNMODIFIED;
		VS__global_0_0_copy_uri_local.value = VS__global_0_0_copy_main.value;
		VS__global_0_0_copy_uri_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		while (1) {
			printf("uri\n");
			timer_uri__global_0_0_copy_uri_local.value = timer_uri__global_0_0_copy_uri_local.value + 1;
			timer_uri__global_0_0_copy_uri_local.status = FOREC_SHARED_MODIFIED;
			if ((VP__global_0_0_copy_uri_local.value == present) || (VS__global_0_0_copy_uri_local.value == present)) {
				timer_uri__global_0_0_copy_uri_local.value = 0;
				timer_uri__global_0_0_copy_uri_local.status = FOREC_SHARED_MODIFIED;
			} else {
				// ifElse48
				
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.

			timer_uri__global_0_0_copy_uri = timer_uri__global_0_0_copy_uri_local;			// forec:statement:pause:pause3:start
			uri__thread.programCounter = &&pause3;
			goto *uri__thread.nextThread -> programCounter;
			pause3:;
			// forec:statement:pause:pause3:end
			// Update the values of the used shared variables from their global copy.
			timer_uri__global_0_0_copy_uri_local = timer_uri__global_0_0;
			VP__global_0_0_copy_uri_local = VP__global_0_0;
			VS__global_0_0_copy_uri_local = VS__global_0_0;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		timer_uri__global_0_0_copy_uri = timer_uri__global_0_0_copy_uri_local;

		// forec:scheduler:threadRemove:uri:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		uri__thread.nextThread -> prevThread = uri__thread.prevThread;
		uri__thread.prevThread -> nextThread = uri__thread.nextThread;
		goto *uri__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:uri:end
	} // uri__thread
	// forec:thread:uri:end

	// forec:thread:vrp:start
	/*--------------------------------------------------------------
	| Thread vrp
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	enum State__vrp_0_0 {
		Init_vrp = 0,
		VRP
	} state_vrp__vrp_0_0;

	unsigned int timer_vrp__vrp_0_0;
	Shared_V_Get__global_0_0 V_Get__global_0_0_copy_vrp_local;
	Shared_V_Act__global_0_0 V_Act__global_0_0_copy_vrp_local;
	Shared_VP__global_0_0 VP__global_0_0_copy_vrp_local;
	Shared_VS__global_0_0 VS__global_0_0_copy_vrp_local;
	Shared_V_Block__global_0_0 V_Block__global_0_0_copy_vrp_local;

	// Thread body -------------------------------------------------
	vrp__thread: {
		// Initialise the local copies of shared variables.
		V_Get__global_0_0_copy_vrp_local.value = V_Get__global_0_0_copy_main.value;
		V_Get__global_0_0_copy_vrp_local.status = FOREC_SHARED_UNMODIFIED;
		V_Act__global_0_0_copy_vrp_local.value = V_Act__global_0_0_copy_main.value;
		V_Act__global_0_0_copy_vrp_local.status = FOREC_SHARED_UNMODIFIED;
		VP__global_0_0_copy_vrp_local.value = VP__global_0_0_copy_main.value;
		VP__global_0_0_copy_vrp_local.status = FOREC_SHARED_UNMODIFIED;
		VS__global_0_0_copy_vrp_local.value = VS__global_0_0.value;
		VS__global_0_0_copy_vrp_local.status = FOREC_SHARED_UNMODIFIED;
		V_Block__global_0_0_copy_vrp_local.value = V_Block__global_0_0.value;
		V_Block__global_0_0_copy_vrp_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		state_vrp__vrp_0_0 = Init_vrp;
		timer_vrp__vrp_0_0 = 0;

		while (1) {
			printf("vrp\n");
			timer_vrp__vrp_0_0 = timer_vrp__vrp_0_0 + 1;
			VS__global_0_0_copy_vrp_local.value = absent;
			VS__global_0_0_copy_vrp_local.status = FOREC_SHARED_MODIFIED;
			V_Block__global_0_0_copy_vrp_local.value = absent;
			V_Block__global_0_0_copy_vrp_local.status = FOREC_SHARED_MODIFIED;
			if (state_vrp__vrp_0_0 == Init_vrp) {
				if ((V_Act__global_0_0_copy_vrp_local.value == present) || (V_Get__global_0_0_copy_vrp_local.value == present)) {
					state_vrp__vrp_0_0 = VRP;
					VS__global_0_0_copy_vrp_local.value = present;
					VS__global_0_0_copy_vrp_local.status = FOREC_SHARED_MODIFIED;
					timer_vrp__vrp_0_0 = 0;
				} else {
					// ifElse59
					if (VP__global_0_0_copy_vrp_local.value == present) {
						state_vrp__vrp_0_0 = VRP;
						timer_vrp__vrp_0_0 = 0;
					} else {
						// if58
					}
				}
			} else {
				// ifElse63
				if (state_vrp__vrp_0_0 == VRP) {
					if (timer_vrp__vrp_0_0 >= TVRP__global_0_0) {
						state_vrp__vrp_0_0 = Init_vrp;
					} else {
						// ifElse61
						if ((V_Act__global_0_0_copy_vrp_local.value == present) || (V_Get__global_0_0_copy_vrp_local.value == present)) {
							state_vrp__vrp_0_0 = VRP;
							V_Block__global_0_0_copy_vrp_local.value = present;
							V_Block__global_0_0_copy_vrp_local.status = FOREC_SHARED_MODIFIED;
						} else {
							// ifElse60
							
						}
					}
				} else {
					// ifElse62
					printf("vrp: In an undefined state (%d)\n", state_vrp__vrp_0_0);
				}
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.

			VS__global_0_0_copy_vrp = VS__global_0_0_copy_vrp_local;
			V_Block__global_0_0_copy_vrp = V_Block__global_0_0_copy_vrp_local;			// forec:statement:pause:pause5:start
			vrp__thread.programCounter = &&pause5;
			goto *vrp__thread.nextThread -> programCounter;
			pause5:;
			// forec:statement:pause:pause5:end
			// Update the values of the used shared variables from their global copy.
			V_Get__global_0_0_copy_vrp_local = V_Get__global_0_0;
			V_Act__global_0_0_copy_vrp_local = V_Act__global_0_0;
			VP__global_0_0_copy_vrp_local = VP__global_0_0;
			VS__global_0_0_copy_vrp_local.status = FOREC_SHARED_UNMODIFIED;
			V_Block__global_0_0_copy_vrp_local.status = FOREC_SHARED_UNMODIFIED;

		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		VS__global_0_0_copy_vrp = VS__global_0_0_copy_vrp_local;
		V_Block__global_0_0_copy_vrp = V_Block__global_0_0_copy_vrp_local;

		// forec:scheduler:threadRemove:vrp:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		vrp__thread.nextThread -> prevThread = vrp__thread.prevThread;
		vrp__thread.prevThread -> nextThread = vrp__thread.nextThread;
		goto *vrp__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:vrp:end
	} // vrp__thread
	// forec:thread:vrp:end


} // End of the main() function.

