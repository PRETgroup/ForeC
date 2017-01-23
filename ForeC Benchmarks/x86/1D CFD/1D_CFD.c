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
#include "sqrtf.h"	

/* input */ float pressureSensor__global_0_0;
/* input */ float pumpSensor__global_0_0;
/* output */ float fuelInjector__global_0_0;

typedef enum {
	PipeSegment = 0,
	Cap,
	ImposedPressure,
	ImposedFlowRate,
	PipeT,
	Valve
} ElementType__global_0_0;

typedef struct _ComputationElement__global_0_0 {
	int id;
	ElementType__global_0_0 type;
	int mechanicalId;
	int leftId;
	int rightId;
	int topId;
	float pressure;
	float flowRate;
	float newPressure;
	float newFlowRate;
	float flowRateLeft;
	float flowRateRight;
	float flowRateTop;
	float newFlowRateLeft;
	float newFlowRateRight;
	float newFlowRateTop;
} ComputationElement__global_0_0;

static const int numberOfComputationElements__global_0_0 = 8;
ComputationElement__global_0_0 pipeNetwork__global_0_0[numberOfComputationElements__global_0_0] = {{.id = 0, .type = ImposedFlowRate, .mechanicalId = 0, .leftId = -1, .rightId = 1, .topId = -1, .pressure = 0.0f, .flowRate = 0.0f, .newPressure = 0.0f, .newFlowRate = 0.0f, .flowRateLeft = 0.0f, .flowRateRight = 0.0f, .flowRateTop = 0.0f, .newFlowRateLeft = 0.0f, .newFlowRateRight = 0.0f, .newFlowRateTop = 0.0f}, {.id = 1, .type = PipeSegment, .mechanicalId = -1, .leftId = 0, .rightId = 2, .topId = -1, .pressure = 0.0f, .flowRate = 0.0f, .newPressure = 0.0f, .newFlowRate = 0.0f, .flowRateLeft = 0.0f, .flowRateRight = 0.0f, .flowRateTop = 0.0f, .newFlowRateLeft = 0.0f, .newFlowRateRight = 0.0f, .newFlowRateTop = 0.0f}, {.id = 2, .type = PipeSegment, .mechanicalId = -1, .leftId = 1, .rightId = 3, .topId = -1, .pressure = 0.0f, .flowRate = 0.0f, .newPressure = 0.0f, .newFlowRate = 0.0f, .flowRateLeft = 0.0f, .flowRateRight = 0.0f, .flowRateTop = 0.0f, .newFlowRateLeft = 0.0f, .newFlowRateRight = 0.0f, .newFlowRateTop = 0.0f}, {.id = 3, .type = PipeT, .mechanicalId = -1, .leftId = 2, .rightId = 4, .topId = 6, .pressure = 0.0f, .flowRate = 0.0f, .newPressure = 0.0f, .newFlowRate = 0.0f, .flowRateLeft = 0.0f, .flowRateRight = 0.0f, .flowRateTop = 0.0f, .newFlowRateLeft = 0.0f, .newFlowRateRight = 0.0f, .newFlowRateTop = 0.0f}, {.id = 4, .type = PipeSegment, .mechanicalId = -1, .leftId = 3, .rightId = 5, .topId = -1, .pressure = 0.0f, .flowRate = 0.0f, .newPressure = 0.0f, .newFlowRate = 0.0f, .flowRateLeft = 0.0f, .flowRateRight = 0.0f, .flowRateTop = 0.0f, .newFlowRateLeft = 0.0f, .newFlowRateRight = 0.0f, .newFlowRateTop = 0.0f}, {.id = 5, .type = Valve, .mechanicalId = 1, .leftId = 4, .rightId = -1, .topId = -1, .pressure = 0.0f, .flowRate = 0.0f, .newPressure = 0.0f, .newFlowRate = 0.0f, .flowRateLeft = 0.0f, .flowRateRight = 0.0f, .flowRateTop = 0.0f, .newFlowRateLeft = 0.0f, .newFlowRateRight = 0.0f, .newFlowRateTop = 0.0f}, {.id = 6, .type = PipeSegment, .mechanicalId = -1, .leftId = 3, .rightId = 7, .topId = -1, .pressure = 0.0f, .flowRate = 0.0f, .newPressure = 0.0f, .newFlowRate = 0.0f, .flowRateLeft = 0.0f, .flowRateRight = 0.0f, .flowRateTop = 0.0f, .newFlowRateLeft = 0.0f, .newFlowRateRight = 0.0f, .newFlowRateTop = 0.0f}, {.id = 7, .type = Cap, .mechanicalId = 1, .leftId = 6, .rightId = -1, .topId = -1, .pressure = 0.0f, .flowRate = 0.0f, .newPressure = 0.0f, .newFlowRate = 0.0f, .flowRateLeft = 0.0f, .flowRateRight = 0.0f, .flowRateTop = 0.0f, .newFlowRateLeft = 0.0f, .newFlowRateRight = 0.0f, .newFlowRateTop = 0.0f}};

typedef struct {
	/* shared */ int value;
	unsigned short int status;
} Shared_numberOfPipeSegments__global_0_0;
Shared_numberOfPipeSegments__global_0_0 numberOfPipeSegments__global_0_0 = {.value = 4, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value[4];
	unsigned short int status;
} Shared_pipeSegmentIds__global_0_0;
Shared_pipeSegmentIds__global_0_0 pipeSegmentIds__global_0_0 = {.value = {1, 2, 4, 6}, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value;
	unsigned short int status;
} Shared_numberOfCaps__global_0_0;
Shared_numberOfCaps__global_0_0 numberOfCaps__global_0_0 = {.value = 1, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value[1];
	unsigned short int status;
} Shared_capIds__global_0_0;
Shared_capIds__global_0_0 capIds__global_0_0 = {.value = {7}, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value;
	unsigned short int status;
} Shared_numberOfImposedPressures__global_0_0;
Shared_numberOfImposedPressures__global_0_0 numberOfImposedPressures__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value[0];
	unsigned short int status;
} Shared_imposedPressureIds__global_0_0;
Shared_imposedPressureIds__global_0_0 imposedPressureIds__global_0_0;
typedef struct {
	/* shared */ int value;
	unsigned short int status;
} Shared_numberOfImposedFlowRates__global_0_0;
Shared_numberOfImposedFlowRates__global_0_0 numberOfImposedFlowRates__global_0_0 = {.value = 1, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value[1];
	unsigned short int status;
} Shared_imposedFlowRateIds__global_0_0;
Shared_imposedFlowRateIds__global_0_0 imposedFlowRateIds__global_0_0 = {.value = {0}, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value;
	unsigned short int status;
} Shared_numberOfPipeTs__global_0_0;
Shared_numberOfPipeTs__global_0_0 numberOfPipeTs__global_0_0 = {.value = 1, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value[1];
	unsigned short int status;
} Shared_pipeTIds__global_0_0;
Shared_pipeTIds__global_0_0 pipeTIds__global_0_0 = {.value = {3}, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value;
	unsigned short int status;
} Shared_numberOfValves__global_0_0;
Shared_numberOfValves__global_0_0 numberOfValves__global_0_0 = {.value = 1, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value[1];
	unsigned short int status;
} Shared_valveIds__global_0_0;
Shared_valveIds__global_0_0 valveIds__global_0_0 = {.value = {5}, .status = FOREC_SHARED_UNMODIFIED};

typedef struct _FluidProperties__global_0_0 {
	float p;
	float ap;
	float newP;
	float newAp;
} FluidProperties__global_0_0;

FluidProperties__global_0_0 fluidProperties__global_0_0 = {.p = 1000.0f, .ap = 1.2E+6, .newP = 0.0f, .newAp = 0.0f};

typedef enum {
	PressureSensor = 0,
	Pump,
	ValveM
} MechanicalType__global_0_0;

typedef struct _MechanicalCalculation__global_0_0 {
	int id;
	MechanicalType__global_0_0 type;
	float pressure;
	float flowRate;
	float valvePosition;
	float newPressure;
	float newFlowRate;
	float newValvePosition;
} MechanicalCalculation__global_0_0;

static const int numberOfMechanicalCalculations__global_0_0 = 2;
MechanicalCalculation__global_0_0 mechanicalCalculations__global_0_0[numberOfMechanicalCalculations__global_0_0] = {{.id = 0, .type = Pump, .pressure = 0.0f, .flowRate = 0.0f, .valvePosition = 0.0f, .newPressure = 0.0f, .newFlowRate = 0.0f, .newValvePosition = 0.0f}, {.id = 1, .type = ValveM, .pressure = 0.0f, .flowRate = 0.0f, .valvePosition = 0.0f, .newPressure = 0.0f, .newFlowRate = 0.0f, .newValvePosition = 0.0f}};

typedef struct {
	/* shared */ int value;
	unsigned short int status;
} Shared_numberOfMechanicalPressureSensors__global_0_0;
Shared_numberOfMechanicalPressureSensors__global_0_0 numberOfMechanicalPressureSensors__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value[0];
	unsigned short int status;
} Shared_mechanicalPressureSensorIds__global_0_0;
Shared_mechanicalPressureSensorIds__global_0_0 mechanicalPressureSensorIds__global_0_0;
typedef struct {
	/* shared */ int value;
	unsigned short int status;
} Shared_numberOfMechanicalPumps__global_0_0;
Shared_numberOfMechanicalPumps__global_0_0 numberOfMechanicalPumps__global_0_0 = {.value = 1, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value[1];
	unsigned short int status;
} Shared_mechanicalPumpIds__global_0_0;
Shared_mechanicalPumpIds__global_0_0 mechanicalPumpIds__global_0_0 = {.value = {0}, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value;
	unsigned short int status;
} Shared_numberOfMechanicalValves__global_0_0;
Shared_numberOfMechanicalValves__global_0_0 numberOfMechanicalValves__global_0_0 = {.value = 1, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value[1];
	unsigned short int status;
} Shared_mechanicalValveIds__global_0_0;
Shared_mechanicalValveIds__global_0_0 mechanicalValveIds__global_0_0 = {.value = {1}, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value;
	unsigned short int status;
} Shared_valveIndex__global_0_0;
Shared_valveIndex__global_0_0 valveIndex__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};

void computePipeSegment(const int id, const float p, const float ap);
void computeCap(const int id, const float p, const float ap);
void computeImposedPressure(const int id, const float p, const float ap);
void computeImposedFlowRate(const int id, const float p, const float ap);
void computePipeT(const int id, const float p, const float ap);
void computeValve(const int id, const float p, const float ap);
void computeMechanicalPressureSensorCalculations(const int id);
void computeMechanicalPumpCalculations(const int id);
void computeMechanicalValveCalculations(const int id);
void computeGlobalCalculations(void);
const float interpolate(const float center, const float edge, const float slope);
const float absFloat(const float number);
void applyComputationElementNonPipeT(const int id);
void applyComputationElementPipeT(const int id);
void applyMechanicalCalculations(const int id);
void applyGlobalCalculations(void);

// thread computeNewValues__thread(void);
// thread applyNewValues__thread(void);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// applyNewValues
Shared_numberOfPipeSegments__global_0_0 numberOfPipeSegments__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_pipeSegmentIds__global_0_0 pipeSegmentIds__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_numberOfCaps__global_0_0 numberOfCaps__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_capIds__global_0_0 capIds__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_numberOfImposedPressures__global_0_0 numberOfImposedPressures__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_imposedPressureIds__global_0_0 imposedPressureIds__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_numberOfImposedFlowRates__global_0_0 numberOfImposedFlowRates__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_imposedFlowRateIds__global_0_0 imposedFlowRateIds__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_numberOfPipeTs__global_0_0 numberOfPipeTs__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_pipeTIds__global_0_0 pipeTIds__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_numberOfValves__global_0_0 numberOfValves__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_valveIds__global_0_0 valveIds__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_numberOfMechanicalPressureSensors__global_0_0 numberOfMechanicalPressureSensors__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_numberOfMechanicalPumps__global_0_0 numberOfMechanicalPumps__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_mechanicalPumpIds__global_0_0 mechanicalPumpIds__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_numberOfMechanicalValves__global_0_0 numberOfMechanicalValves__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_mechanicalValveIds__global_0_0 mechanicalValveIds__global_0_0_copy_applyNewValues = {.status = FOREC_SHARED_UNMODIFIED};
// computeNewValues
Shared_numberOfPipeSegments__global_0_0 numberOfPipeSegments__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_pipeSegmentIds__global_0_0 pipeSegmentIds__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_numberOfCaps__global_0_0 numberOfCaps__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_capIds__global_0_0 capIds__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_numberOfImposedPressures__global_0_0 numberOfImposedPressures__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_imposedPressureIds__global_0_0 imposedPressureIds__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_numberOfImposedFlowRates__global_0_0 numberOfImposedFlowRates__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_imposedFlowRateIds__global_0_0 imposedFlowRateIds__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_numberOfPipeTs__global_0_0 numberOfPipeTs__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_pipeTIds__global_0_0 pipeTIds__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_numberOfValves__global_0_0 numberOfValves__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_valveIds__global_0_0 valveIds__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_numberOfMechanicalPressureSensors__global_0_0 numberOfMechanicalPressureSensors__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_numberOfMechanicalPumps__global_0_0 numberOfMechanicalPumps__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_mechanicalPumpIds__global_0_0 mechanicalPumpIds__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_numberOfMechanicalValves__global_0_0 numberOfMechanicalValves__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_mechanicalValveIds__global_0_0 mechanicalValveIds__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
Shared_valveIndex__global_0_0 valveIndex__global_0_0_copy_computeNewValues = {.status = FOREC_SHARED_UNMODIFIED};
// main
Shared_valveIndex__global_0_0 valveIndex__global_0_0_copy_main = {.status = FOREC_SHARED_UNMODIFIED};

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
	Thread computeNewValues__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionEndMaster0;

	// par1
	Thread applyNewValues__thread;
	// Thread mainReactionStartMaster0;
	// Thread mainReactionEndMaster0;


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
	Shared_valveIndex__global_0_0 valveIndex__global_0_0_copy_main_local;

mainParCore0: {
	// Initialise the local copies of shared variables.
	valveIndex__global_0_0_copy_main_local = valveIndex__global_0_0;
	//--------------------------------------------------------------

	while (1) {
		// par0(computeNewValues__thread);
		valveIndex__global_0_0_copy_main = valveIndex__global_0_0_copy_main_local;
		valveIndex__global_0_0.value = valveIndex__global_0_0_copy_main_local.value;
		// Set the par(...) information.
		mainParParent.parId = 0;
		mainParParent.parStatus = FOREC_PAR_ON;

		// Link the threads and handlers together.
		mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
		computeNewValues__thread.programCounter = &&computeNewValues__thread;
		mainReactionStartMaster0.nextThread = &computeNewValues__thread;
		computeNewValues__thread.prevThread = &mainReactionStartMaster0;
		mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
		computeNewValues__thread.nextThread = &mainReactionEndMaster0;
		mainReactionEndMaster0.prevThread = &computeNewValues__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
		mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

		// Set the join address.
		mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

		// Set the core information.
		mainParCore0.activeThreads = 1;
		mainParCore0.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		// forec:statement:par:par0:start
		goto computeNewValues__thread;
		par0JoinAddress_mainParCore0:;
		// forec:statement:par:par0:end
		valveIndex__global_0_0_copy_main_local = valveIndex__global_0_0;

		printf("Computed");

		// par1(applyNewValues__thread);
		// Set the par(...) information.
		mainParParent.parId = 1;
		mainParParent.parStatus = FOREC_PAR_ON;

		// Link the threads and handlers together.
		mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
		applyNewValues__thread.programCounter = &&applyNewValues__thread;
		mainReactionStartMaster0.nextThread = &applyNewValues__thread;
		applyNewValues__thread.prevThread = &mainReactionStartMaster0;
		mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
		applyNewValues__thread.nextThread = &mainReactionEndMaster0;
		mainReactionEndMaster0.prevThread = &applyNewValues__thread;

		// Link the last and first threads/handlers together.
		mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
		mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

		// Set the join address.
		mainParParent.programCounter = &&par1JoinAddress_mainParCore0;

		// Set the core information.
		mainParCore0.activeThreads = 1;
		mainParCore0.reactionCounter = mainParReactionCounter;

		// Go to the first thread.
		// forec:statement:par:par1:start
		goto applyNewValues__thread;
		par1JoinAddress_mainParCore0:;
		// forec:statement:par:par1:end

		printf(" and applied\r\n");
		printf("End of time step %d\r\n", valveIndex__global_0_0_copy_main_local.value);

		// pause;
		// forec:statement:pause:pause0:start
		// forec:statement:pause:pause0:end
		// Update the values of the used shared variables from their global copy.
		valveIndex__global_0_0_copy_main_local = valveIndex__global_0_0;


		// forec:scheduler:iterationEnd:while_0:start
		// Synchronise end of iteration
		mainParParent.parId = -2;
		mainParParent.parStatus = FOREC_PAR_ON;
		mainParParent.programCounter = &&while_0_endAddress;
		goto mainParHandlerMaster0;
		while_0_endAddress:;
		// forec:scheduler:iterationEnd:while_0:end
	}

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
	// forec:thread:applyNewValues:start
	/*--------------------------------------------------------------
	| Thread applyNewValues
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_numberOfPipeSegments__global_0_0 numberOfPipeSegments__global_0_0_copy_applyNewValues_local;
	Shared_pipeSegmentIds__global_0_0 pipeSegmentIds__global_0_0_copy_applyNewValues_local;
	Shared_numberOfCaps__global_0_0 numberOfCaps__global_0_0_copy_applyNewValues_local;
	Shared_capIds__global_0_0 capIds__global_0_0_copy_applyNewValues_local;
	Shared_numberOfImposedPressures__global_0_0 numberOfImposedPressures__global_0_0_copy_applyNewValues_local;
	Shared_imposedPressureIds__global_0_0 imposedPressureIds__global_0_0_copy_applyNewValues_local;
	Shared_numberOfImposedFlowRates__global_0_0 numberOfImposedFlowRates__global_0_0_copy_applyNewValues_local;
	Shared_imposedFlowRateIds__global_0_0 imposedFlowRateIds__global_0_0_copy_applyNewValues_local;
	Shared_numberOfPipeTs__global_0_0 numberOfPipeTs__global_0_0_copy_applyNewValues_local;
	Shared_pipeTIds__global_0_0 pipeTIds__global_0_0_copy_applyNewValues_local;
	Shared_numberOfValves__global_0_0 numberOfValves__global_0_0_copy_applyNewValues_local;
	Shared_valveIds__global_0_0 valveIds__global_0_0_copy_applyNewValues_local;
	Shared_numberOfMechanicalPressureSensors__global_0_0 numberOfMechanicalPressureSensors__global_0_0_copy_applyNewValues_local;
	Shared_numberOfMechanicalPumps__global_0_0 numberOfMechanicalPumps__global_0_0_copy_applyNewValues_local;
	Shared_mechanicalPumpIds__global_0_0 mechanicalPumpIds__global_0_0_copy_applyNewValues_local;
	Shared_numberOfMechanicalValves__global_0_0 numberOfMechanicalValves__global_0_0_copy_applyNewValues_local;
	Shared_mechanicalValveIds__global_0_0 mechanicalValveIds__global_0_0_copy_applyNewValues_local;
	int i__applyNewValues_0_0;

	// Thread body -------------------------------------------------
	applyNewValues__thread: {
		// Initialise the local copies of shared variables.
		numberOfPipeSegments__global_0_0_copy_applyNewValues_local.value = numberOfPipeSegments__global_0_0.value;
		numberOfPipeSegments__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		pipeSegmentIds__global_0_0_copy_applyNewValues_local.value = pipeSegmentIds__global_0_0.value;
		pipeSegmentIds__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		numberOfCaps__global_0_0_copy_applyNewValues_local.value = numberOfCaps__global_0_0.value;
		numberOfCaps__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		capIds__global_0_0_copy_applyNewValues_local.value = capIds__global_0_0.value;
		capIds__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		numberOfImposedPressures__global_0_0_copy_applyNewValues_local.value = numberOfImposedPressures__global_0_0.value;
		numberOfImposedPressures__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		imposedPressureIds__global_0_0_copy_applyNewValues_local.value = imposedPressureIds__global_0_0.value;
		imposedPressureIds__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		numberOfImposedFlowRates__global_0_0_copy_applyNewValues_local.value = numberOfImposedFlowRates__global_0_0.value;
		numberOfImposedFlowRates__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		imposedFlowRateIds__global_0_0_copy_applyNewValues_local.value = imposedFlowRateIds__global_0_0.value;
		imposedFlowRateIds__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		numberOfPipeTs__global_0_0_copy_applyNewValues_local.value = numberOfPipeTs__global_0_0.value;
		numberOfPipeTs__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		pipeTIds__global_0_0_copy_applyNewValues_local.value = pipeTIds__global_0_0.value;
		pipeTIds__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		numberOfValves__global_0_0_copy_applyNewValues_local.value = numberOfValves__global_0_0.value;
		numberOfValves__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		valveIds__global_0_0_copy_applyNewValues_local.value = valveIds__global_0_0.value;
		valveIds__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		numberOfMechanicalPressureSensors__global_0_0_copy_applyNewValues_local.value = numberOfMechanicalPressureSensors__global_0_0.value;
		numberOfMechanicalPressureSensors__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		numberOfMechanicalPumps__global_0_0_copy_applyNewValues_local.value = numberOfMechanicalPumps__global_0_0.value;
		numberOfMechanicalPumps__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		mechanicalPumpIds__global_0_0_copy_applyNewValues_local.value = mechanicalPumpIds__global_0_0.value;
		mechanicalPumpIds__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		numberOfMechanicalValves__global_0_0_copy_applyNewValues_local.value = numberOfMechanicalValves__global_0_0.value;
		numberOfMechanicalValves__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		mechanicalValveIds__global_0_0_copy_applyNewValues_local.value = mechanicalValveIds__global_0_0.value;
		mechanicalValveIds__global_0_0_copy_applyNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		for (i__applyNewValues_0_0 = 0; i__applyNewValues_0_0 < numberOfPipeSegments__global_0_0_copy_applyNewValues_local.value; ++i__applyNewValues_0_0) {
			applyComputationElementNonPipeT(pipeSegmentIds__global_0_0_copy_applyNewValues_local.value[i__applyNewValues_0_0]);
			// forec:iteration:for1_10:bound:4:4
		}
		for (i__applyNewValues_0_0 = 0; i__applyNewValues_0_0 < numberOfCaps__global_0_0_copy_applyNewValues_local.value; ++i__applyNewValues_0_0) {
			applyComputationElementNonPipeT(capIds__global_0_0_copy_applyNewValues_local.value[i__applyNewValues_0_0]);
			// forec:iteration:for1_11:bound:1:1
		}
		for (i__applyNewValues_0_0 = 0; i__applyNewValues_0_0 < numberOfImposedPressures__global_0_0_copy_applyNewValues_local.value; ++i__applyNewValues_0_0) {
			applyComputationElementNonPipeT(imposedPressureIds__global_0_0_copy_applyNewValues_local.value[i__applyNewValues_0_0]);
			// forec:iteration:for1_12:bound:0:0
		}
		for (i__applyNewValues_0_0 = 0; i__applyNewValues_0_0 < numberOfImposedFlowRates__global_0_0_copy_applyNewValues_local.value; ++i__applyNewValues_0_0) {
			applyComputationElementNonPipeT(imposedFlowRateIds__global_0_0_copy_applyNewValues_local.value[i__applyNewValues_0_0]);
			// forec:iteration:for1_13:bound:1:1
		}
		for (i__applyNewValues_0_0 = 0; i__applyNewValues_0_0 < numberOfPipeTs__global_0_0_copy_applyNewValues_local.value; ++i__applyNewValues_0_0) {
			applyComputationElementPipeT(pipeTIds__global_0_0_copy_applyNewValues_local.value[i__applyNewValues_0_0]);
			// forec:iteration:for1_14:bound:1:1
		}
		for (i__applyNewValues_0_0 = 0; i__applyNewValues_0_0 < numberOfValves__global_0_0_copy_applyNewValues_local.value; ++i__applyNewValues_0_0) {
			applyComputationElementNonPipeT(valveIds__global_0_0_copy_applyNewValues_local.value[i__applyNewValues_0_0]);
			// forec:iteration:for1_15:bound:1:1
		}
		for (i__applyNewValues_0_0 = 0; i__applyNewValues_0_0 < numberOfMechanicalPressureSensors__global_0_0_copy_applyNewValues_local.value; ++i__applyNewValues_0_0) {
			applyMechanicalCalculations(mechanicalPumpIds__global_0_0_copy_applyNewValues_local.value[i__applyNewValues_0_0]);
			// forec:iteration:for1_16:bound:0:0
		}
		for (i__applyNewValues_0_0 = 0; i__applyNewValues_0_0 < numberOfMechanicalPumps__global_0_0_copy_applyNewValues_local.value; ++i__applyNewValues_0_0) {
			applyMechanicalCalculations(mechanicalPumpIds__global_0_0_copy_applyNewValues_local.value[i__applyNewValues_0_0]);
			// forec:iteration:for1_17:bound:1:1
		}
		for (i__applyNewValues_0_0 = 0; i__applyNewValues_0_0 < numberOfMechanicalValves__global_0_0_copy_applyNewValues_local.value; ++i__applyNewValues_0_0) {
			applyMechanicalCalculations(mechanicalValveIds__global_0_0_copy_applyNewValues_local.value[i__applyNewValues_0_0]);
			// forec:iteration:for1_18:bound:1:1
		}
		applyGlobalCalculations();

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:applyNewValues:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		applyNewValues__thread.nextThread -> prevThread = applyNewValues__thread.prevThread;
		applyNewValues__thread.prevThread -> nextThread = applyNewValues__thread.nextThread;
		goto *applyNewValues__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:applyNewValues:end
	} // applyNewValues__thread
	// forec:thread:applyNewValues:end

	// forec:thread:computeNewValues:start
	/*--------------------------------------------------------------
	| Thread computeNewValues
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_numberOfPipeSegments__global_0_0 numberOfPipeSegments__global_0_0_copy_computeNewValues_local;
	Shared_pipeSegmentIds__global_0_0 pipeSegmentIds__global_0_0_copy_computeNewValues_local;
	Shared_numberOfCaps__global_0_0 numberOfCaps__global_0_0_copy_computeNewValues_local;
	Shared_capIds__global_0_0 capIds__global_0_0_copy_computeNewValues_local;
	Shared_numberOfImposedPressures__global_0_0 numberOfImposedPressures__global_0_0_copy_computeNewValues_local;
	Shared_imposedPressureIds__global_0_0 imposedPressureIds__global_0_0_copy_computeNewValues_local;
	Shared_numberOfImposedFlowRates__global_0_0 numberOfImposedFlowRates__global_0_0_copy_computeNewValues_local;
	Shared_imposedFlowRateIds__global_0_0 imposedFlowRateIds__global_0_0_copy_computeNewValues_local;
	Shared_numberOfPipeTs__global_0_0 numberOfPipeTs__global_0_0_copy_computeNewValues_local;
	Shared_pipeTIds__global_0_0 pipeTIds__global_0_0_copy_computeNewValues_local;
	Shared_numberOfValves__global_0_0 numberOfValves__global_0_0_copy_computeNewValues_local;
	Shared_valveIds__global_0_0 valveIds__global_0_0_copy_computeNewValues_local;
	Shared_numberOfMechanicalPressureSensors__global_0_0 numberOfMechanicalPressureSensors__global_0_0_copy_computeNewValues_local;
	Shared_numberOfMechanicalPumps__global_0_0 numberOfMechanicalPumps__global_0_0_copy_computeNewValues_local;
	Shared_mechanicalPumpIds__global_0_0 mechanicalPumpIds__global_0_0_copy_computeNewValues_local;
	Shared_numberOfMechanicalValves__global_0_0 numberOfMechanicalValves__global_0_0_copy_computeNewValues_local;
	Shared_mechanicalValveIds__global_0_0 mechanicalValveIds__global_0_0_copy_computeNewValues_local;
	Shared_valveIndex__global_0_0 valveIndex__global_0_0_copy_computeNewValues_local;
	float p__computeNewValues_0_0;
	float ap__computeNewValues_0_0;
	int i__computeNewValues_0_0;

	// Thread body -------------------------------------------------
	computeNewValues__thread: {
		// Initialise the local copies of shared variables.
		numberOfPipeSegments__global_0_0_copy_computeNewValues_local.value = numberOfPipeSegments__global_0_0.value;
		numberOfPipeSegments__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		pipeSegmentIds__global_0_0_copy_computeNewValues_local.value = pipeSegmentIds__global_0_0.value;
		pipeSegmentIds__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		numberOfCaps__global_0_0_copy_computeNewValues_local.value = numberOfCaps__global_0_0.value;
		numberOfCaps__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		capIds__global_0_0_copy_computeNewValues_local.value = capIds__global_0_0.value;
		capIds__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		numberOfImposedPressures__global_0_0_copy_computeNewValues_local.value = numberOfImposedPressures__global_0_0.value;
		numberOfImposedPressures__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		imposedPressureIds__global_0_0_copy_computeNewValues_local.value = imposedPressureIds__global_0_0.value;
		imposedPressureIds__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		numberOfImposedFlowRates__global_0_0_copy_computeNewValues_local.value = numberOfImposedFlowRates__global_0_0.value;
		numberOfImposedFlowRates__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		imposedFlowRateIds__global_0_0_copy_computeNewValues_local.value = imposedFlowRateIds__global_0_0.value;
		imposedFlowRateIds__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		numberOfPipeTs__global_0_0_copy_computeNewValues_local.value = numberOfPipeTs__global_0_0.value;
		numberOfPipeTs__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		pipeTIds__global_0_0_copy_computeNewValues_local.value = pipeTIds__global_0_0.value;
		pipeTIds__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		numberOfValves__global_0_0_copy_computeNewValues_local.value = numberOfValves__global_0_0.value;
		numberOfValves__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		valveIds__global_0_0_copy_computeNewValues_local.value = valveIds__global_0_0.value;
		valveIds__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		numberOfMechanicalPressureSensors__global_0_0_copy_computeNewValues_local.value = numberOfMechanicalPressureSensors__global_0_0.value;
		numberOfMechanicalPressureSensors__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		numberOfMechanicalPumps__global_0_0_copy_computeNewValues_local.value = numberOfMechanicalPumps__global_0_0.value;
		numberOfMechanicalPumps__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		mechanicalPumpIds__global_0_0_copy_computeNewValues_local.value = mechanicalPumpIds__global_0_0.value;
		mechanicalPumpIds__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		numberOfMechanicalValves__global_0_0_copy_computeNewValues_local.value = numberOfMechanicalValves__global_0_0.value;
		numberOfMechanicalValves__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		mechanicalValveIds__global_0_0_copy_computeNewValues_local.value = mechanicalValveIds__global_0_0.value;
		mechanicalValveIds__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		valveIndex__global_0_0_copy_computeNewValues_local.value = valveIndex__global_0_0_copy_main.value;
		valveIndex__global_0_0_copy_computeNewValues_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		p__computeNewValues_0_0 = fluidProperties__global_0_0.p;
		ap__computeNewValues_0_0 = fluidProperties__global_0_0.ap;
		for (i__computeNewValues_0_0 = 0; i__computeNewValues_0_0 < numberOfPipeSegments__global_0_0_copy_computeNewValues_local.value; ++i__computeNewValues_0_0) {
			computePipeSegment(pipeSegmentIds__global_0_0_copy_computeNewValues_local.value[i__computeNewValues_0_0], p__computeNewValues_0_0, ap__computeNewValues_0_0);
			// forec:iteration:for1_1:bound:4:4
		}
		for (i__computeNewValues_0_0 = 0; i__computeNewValues_0_0 < numberOfCaps__global_0_0_copy_computeNewValues_local.value; ++i__computeNewValues_0_0) {
			computeCap(capIds__global_0_0_copy_computeNewValues_local.value[i__computeNewValues_0_0], p__computeNewValues_0_0, ap__computeNewValues_0_0);
			// forec:iteration:for1_2:bound:1:1
		}
		for (i__computeNewValues_0_0 = 0; i__computeNewValues_0_0 < numberOfImposedPressures__global_0_0_copy_computeNewValues_local.value; ++i__computeNewValues_0_0) {
			computeImposedPressure(imposedPressureIds__global_0_0_copy_computeNewValues_local.value[i__computeNewValues_0_0], p__computeNewValues_0_0, ap__computeNewValues_0_0);
			// forec:iteration:for1_3:bound:0:0
		}
		for (i__computeNewValues_0_0 = 0; i__computeNewValues_0_0 < numberOfImposedFlowRates__global_0_0_copy_computeNewValues_local.value; ++i__computeNewValues_0_0) {
			computeImposedFlowRate(imposedFlowRateIds__global_0_0_copy_computeNewValues_local.value[i__computeNewValues_0_0], p__computeNewValues_0_0, ap__computeNewValues_0_0);
			// forec:iteration:for1_4:bound:1:1
		}
		for (i__computeNewValues_0_0 = 0; i__computeNewValues_0_0 < numberOfPipeTs__global_0_0_copy_computeNewValues_local.value; ++i__computeNewValues_0_0) {
			computePipeT(pipeTIds__global_0_0_copy_computeNewValues_local.value[i__computeNewValues_0_0], p__computeNewValues_0_0, ap__computeNewValues_0_0);
			// forec:iteration:for1_5:bound:1:1
		}
		for (i__computeNewValues_0_0 = 0; i__computeNewValues_0_0 < numberOfValves__global_0_0_copy_computeNewValues_local.value; ++i__computeNewValues_0_0) {
			computeValve(valveIds__global_0_0_copy_computeNewValues_local.value[i__computeNewValues_0_0], p__computeNewValues_0_0, ap__computeNewValues_0_0);
			// forec:iteration:for1_6:bound:1:1
		}
		for (i__computeNewValues_0_0 = 0; i__computeNewValues_0_0 < numberOfMechanicalPressureSensors__global_0_0_copy_computeNewValues_local.value; ++i__computeNewValues_0_0) {
			computeMechanicalPressureSensorCalculations(mechanicalPumpIds__global_0_0_copy_computeNewValues_local.value[i__computeNewValues_0_0]);
			// forec:iteration:for1_7:bound:0:0
		}
		for (i__computeNewValues_0_0 = 0; i__computeNewValues_0_0 < numberOfMechanicalPumps__global_0_0_copy_computeNewValues_local.value; ++i__computeNewValues_0_0) {
			computeMechanicalPumpCalculations(mechanicalPumpIds__global_0_0_copy_computeNewValues_local.value[i__computeNewValues_0_0]);
			// forec:iteration:for1_8:bound:1:1
		}
		for (i__computeNewValues_0_0 = 0; i__computeNewValues_0_0 < numberOfMechanicalValves__global_0_0_copy_computeNewValues_local.value; ++i__computeNewValues_0_0) {
			computeMechanicalValveCalculations(mechanicalValveIds__global_0_0_copy_computeNewValues_local.value[i__computeNewValues_0_0]);
			// forec:iteration:for1_9:bound:1:1
		}
		computeGlobalCalculations();
		valveIndex__global_0_0_copy_computeNewValues_local.value++;

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:computeNewValues:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		computeNewValues__thread.nextThread -> prevThread = computeNewValues__thread.prevThread;
		computeNewValues__thread.prevThread -> nextThread = computeNewValues__thread.nextThread;
		goto *computeNewValues__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:computeNewValues:end
	} // computeNewValues__thread
	// forec:thread:computeNewValues:end


} // End of the main() function.

void computePipeSegment(const int id__computePipeSegment_0_0, const float p__computePipeSegment_0_0, const float ap__computePipeSegment_0_0) {
	const float theta__computePipeSegment_0_0 = 1.0f;
	const float A__computePipeSegment_0_0 = 1.0f;
	const float E__computePipeSegment_0_0 = p__computePipeSegment_0_0*1.0f;
	const float B__computePipeSegment_0_0 = ap__computePipeSegment_0_0/A__computePipeSegment_0_0;
	const float A2__computePipeSegment_0_0 = 1.0f;
	const float A3__computePipeSegment_0_0 = 1.0f;
	float pressureLeft__computePipeSegment_0_0;
	float flowRateLeft__computePipeSegment_0_0;
	const int leftId__computePipeSegment_0_0 = pipeNetwork__global_0_0[id__computePipeSegment_0_0].leftId;
	if (leftId__computePipeSegment_0_0 != -1) {
		pressureLeft__computePipeSegment_0_0 = pipeNetwork__global_0_0[leftId__computePipeSegment_0_0].pressure;
		flowRateLeft__computePipeSegment_0_0 = pipeNetwork__global_0_0[leftId__computePipeSegment_0_0].flowRate;
	} else {
		// ifElse0
		pressureLeft__computePipeSegment_0_0 = 0.0f;
		flowRateLeft__computePipeSegment_0_0 = 0.0f;
	}
	float pressureRight__computePipeSegment_0_0;
	float flowRateRight__computePipeSegment_0_0;
	const int rightId__computePipeSegment_0_0 = pipeNetwork__global_0_0[id__computePipeSegment_0_0].rightId;
	if (rightId__computePipeSegment_0_0 != -1) {
		pressureRight__computePipeSegment_0_0 = pipeNetwork__global_0_0[rightId__computePipeSegment_0_0].pressure;
		flowRateRight__computePipeSegment_0_0 = pipeNetwork__global_0_0[rightId__computePipeSegment_0_0].flowRate;
	} else {
		// ifElse1
		pressureRight__computePipeSegment_0_0 = 0.0f;
		flowRateRight__computePipeSegment_0_0 = 0.0f;
	}
	const float pressure__computePipeSegment_0_0 = pipeNetwork__global_0_0[id__computePipeSegment_0_0].pressure;
	const float flowRate__computePipeSegment_0_0 = pipeNetwork__global_0_0[id__computePipeSegment_0_0].flowRate;
	pressureLeft__computePipeSegment_0_0 = interpolate(pressure__computePipeSegment_0_0, pressureLeft__computePipeSegment_0_0, (ap__computePipeSegment_0_0*theta__computePipeSegment_0_0));
	flowRateLeft__computePipeSegment_0_0 = interpolate(flowRate__computePipeSegment_0_0, flowRateLeft__computePipeSegment_0_0, (ap__computePipeSegment_0_0*theta__computePipeSegment_0_0));
	pressureRight__computePipeSegment_0_0 = interpolate(pressure__computePipeSegment_0_0, pressureRight__computePipeSegment_0_0, (ap__computePipeSegment_0_0*theta__computePipeSegment_0_0));
	flowRateRight__computePipeSegment_0_0 = interpolate(flowRate__computePipeSegment_0_0, flowRateRight__computePipeSegment_0_0, (ap__computePipeSegment_0_0*theta__computePipeSegment_0_0));
	const float Cp__computePipeSegment_0_0 = pressureLeft__computePipeSegment_0_0 + flowRateLeft__computePipeSegment_0_0*(B__computePipeSegment_0_0 - E__computePipeSegment_0_0*absFloat(flowRateLeft__computePipeSegment_0_0));
	const float Cm__computePipeSegment_0_0 = pressureRight__computePipeSegment_0_0 - flowRateRight__computePipeSegment_0_0*(B__computePipeSegment_0_0 - E__computePipeSegment_0_0*absFloat(flowRateRight__computePipeSegment_0_0));
	const float newPressure__computePipeSegment_0_0 = (Cp__computePipeSegment_0_0 + Cm__computePipeSegment_0_0)/2.0f;
	pipeNetwork__global_0_0[id__computePipeSegment_0_0].newPressure = newPressure__computePipeSegment_0_0;
	pipeNetwork__global_0_0[id__computePipeSegment_0_0].newFlowRate = (newPressure__computePipeSegment_0_0 - Cm__computePipeSegment_0_0)/B__computePipeSegment_0_0;
}

void computeCap(const int id__computeCap_0_0, const float p__computeCap_0_0, const float ap__computeCap_0_0) {
	const float theta__computeCap_0_0 = 1.0f;
	const float A__computeCap_0_0 = 1.0f;
	const float E__computeCap_0_0 = p__computeCap_0_0*1.0f;
	const float B__computeCap_0_0 = ap__computeCap_0_0/A__computeCap_0_0;
	const float A2__computeCap_0_0 = 1.0f;
	const float A3__computeCap_0_0 = 1.0f;
	float pressureLeft__computeCap_0_0;
	float flowRateLeft__computeCap_0_0;
	const int leftId__computeCap_0_0 = pipeNetwork__global_0_0[id__computeCap_0_0].leftId;
	if (leftId__computeCap_0_0 != -1) {
		pressureLeft__computeCap_0_0 = pipeNetwork__global_0_0[leftId__computeCap_0_0].pressure;
		flowRateLeft__computeCap_0_0 = pipeNetwork__global_0_0[leftId__computeCap_0_0].flowRate;
	} else {
		// ifElse2
		pressureLeft__computeCap_0_0 = 0.0f;
		flowRateLeft__computeCap_0_0 = 0.0f;
	}
	const float pressure__computeCap_0_0 = pipeNetwork__global_0_0[id__computeCap_0_0].pressure;
	const float flowRate__computeCap_0_0 = pipeNetwork__global_0_0[id__computeCap_0_0].flowRate;
	pressureLeft__computeCap_0_0 = interpolate(pressure__computeCap_0_0, pressureLeft__computeCap_0_0, (ap__computeCap_0_0*theta__computeCap_0_0));
	flowRateLeft__computeCap_0_0 = interpolate(flowRate__computeCap_0_0, flowRateLeft__computeCap_0_0, (ap__computeCap_0_0*theta__computeCap_0_0));
	;
	const float Cp__computeCap_0_0 = pressureLeft__computeCap_0_0 + flowRateLeft__computeCap_0_0*(B__computeCap_0_0 - E__computeCap_0_0*absFloat(flowRateLeft__computeCap_0_0));
	const float newFlowRate__computeCap_0_0 = 0.0f;
	pipeNetwork__global_0_0[id__computeCap_0_0].newFlowRate = newFlowRate__computeCap_0_0;
	pipeNetwork__global_0_0[id__computeCap_0_0].newPressure = Cp__computeCap_0_0 - B__computeCap_0_0*newFlowRate__computeCap_0_0;
}

void computeImposedPressure(const int id__computeImposedPressure_0_0, const float p__computeImposedPressure_0_0, const float ap__computeImposedPressure_0_0) {
	const float theta__computeImposedPressure_0_0 = 1.0f;
	const float A__computeImposedPressure_0_0 = 1.0f;
	const float E__computeImposedPressure_0_0 = p__computeImposedPressure_0_0*1.0f;
	const float B__computeImposedPressure_0_0 = ap__computeImposedPressure_0_0/A__computeImposedPressure_0_0;
	const float A2__computeImposedPressure_0_0 = 1.0f;
	const float A3__computeImposedPressure_0_0 = 1.0f;
	float pressureRight__computeImposedPressure_0_0;
	float flowRateRight__computeImposedPressure_0_0;
	const int rightId__computeImposedPressure_0_0 = pipeNetwork__global_0_0[id__computeImposedPressure_0_0].rightId;
	if (rightId__computeImposedPressure_0_0 != -1) {
		pressureRight__computeImposedPressure_0_0 = pipeNetwork__global_0_0[rightId__computeImposedPressure_0_0].pressure;
		flowRateRight__computeImposedPressure_0_0 = pipeNetwork__global_0_0[rightId__computeImposedPressure_0_0].flowRate;
	} else {
		// ifElse3
		pressureRight__computeImposedPressure_0_0 = 0.0f;
		flowRateRight__computeImposedPressure_0_0 = 0.0f;
	}
	const float pressure__computeImposedPressure_0_0 = pipeNetwork__global_0_0[id__computeImposedPressure_0_0].pressure;
	const float flowRate__computeImposedPressure_0_0 = pipeNetwork__global_0_0[id__computeImposedPressure_0_0].flowRate;
	pressureRight__computeImposedPressure_0_0 = interpolate(pressure__computeImposedPressure_0_0, pressureRight__computeImposedPressure_0_0, (ap__computeImposedPressure_0_0*theta__computeImposedPressure_0_0));
	flowRateRight__computeImposedPressure_0_0 = interpolate(flowRate__computeImposedPressure_0_0, flowRateRight__computeImposedPressure_0_0, (ap__computeImposedPressure_0_0*theta__computeImposedPressure_0_0));
	const float Cm__computeImposedPressure_0_0 = pressureRight__computeImposedPressure_0_0 - flowRateRight__computeImposedPressure_0_0*(B__computeImposedPressure_0_0 - E__computeImposedPressure_0_0*absFloat(flowRateRight__computeImposedPressure_0_0));
	const float newPressure__computeImposedPressure_0_0 = mechanicalCalculations__global_0_0[pipeNetwork__global_0_0[id__computeImposedPressure_0_0].mechanicalId].pressure;
	pipeNetwork__global_0_0[id__computeImposedPressure_0_0].newPressure = newPressure__computeImposedPressure_0_0;
	pipeNetwork__global_0_0[id__computeImposedPressure_0_0].newFlowRate = (newPressure__computeImposedPressure_0_0 - Cm__computeImposedPressure_0_0)/B__computeImposedPressure_0_0;
}

void computeImposedFlowRate(const int id__computeImposedFlowRate_0_0, const float p__computeImposedFlowRate_0_0, const float ap__computeImposedFlowRate_0_0) {
	const float theta__computeImposedFlowRate_0_0 = 1.0f;
	const float A__computeImposedFlowRate_0_0 = 1.0f;
	const float E__computeImposedFlowRate_0_0 = p__computeImposedFlowRate_0_0*1.0f;
	const float B__computeImposedFlowRate_0_0 = ap__computeImposedFlowRate_0_0/A__computeImposedFlowRate_0_0;
	const float A2__computeImposedFlowRate_0_0 = 1.0f;
	const float A3__computeImposedFlowRate_0_0 = 1.0f;
	float pressureRight__computeImposedFlowRate_0_0;
	float flowRateRight__computeImposedFlowRate_0_0;
	const int rightId__computeImposedFlowRate_0_0 = pipeNetwork__global_0_0[id__computeImposedFlowRate_0_0].rightId;
	if (rightId__computeImposedFlowRate_0_0 != -1) {
		pressureRight__computeImposedFlowRate_0_0 = pipeNetwork__global_0_0[rightId__computeImposedFlowRate_0_0].pressure;
		flowRateRight__computeImposedFlowRate_0_0 = pipeNetwork__global_0_0[rightId__computeImposedFlowRate_0_0].flowRate;
	} else {
		// ifElse4
		pressureRight__computeImposedFlowRate_0_0 = 0.0f;
		flowRateRight__computeImposedFlowRate_0_0 = 0.0f;
	}
	const float pressure__computeImposedFlowRate_0_0 = pipeNetwork__global_0_0[id__computeImposedFlowRate_0_0].pressure;
	const float flowRate__computeImposedFlowRate_0_0 = pipeNetwork__global_0_0[id__computeImposedFlowRate_0_0].flowRate;
	pressureRight__computeImposedFlowRate_0_0 = interpolate(pressure__computeImposedFlowRate_0_0, pressureRight__computeImposedFlowRate_0_0, (ap__computeImposedFlowRate_0_0*theta__computeImposedFlowRate_0_0));
	flowRateRight__computeImposedFlowRate_0_0 = interpolate(flowRate__computeImposedFlowRate_0_0, flowRateRight__computeImposedFlowRate_0_0, (ap__computeImposedFlowRate_0_0*theta__computeImposedFlowRate_0_0));
	const float Cm__computeImposedFlowRate_0_0 = pressureRight__computeImposedFlowRate_0_0 - flowRateRight__computeImposedFlowRate_0_0*(B__computeImposedFlowRate_0_0 - E__computeImposedFlowRate_0_0*absFloat(flowRateRight__computeImposedFlowRate_0_0));
	const float newFlowRate__computeImposedFlowRate_0_0 = mechanicalCalculations__global_0_0[pipeNetwork__global_0_0[id__computeImposedFlowRate_0_0].mechanicalId].flowRate;
	pipeNetwork__global_0_0[id__computeImposedFlowRate_0_0].newPressure = Cm__computeImposedFlowRate_0_0 - (B__computeImposedFlowRate_0_0*newFlowRate__computeImposedFlowRate_0_0);
	pipeNetwork__global_0_0[id__computeImposedFlowRate_0_0].newFlowRate = newFlowRate__computeImposedFlowRate_0_0;
}

void computePipeT(const int id__computePipeT_0_0, const float p__computePipeT_0_0, const float ap__computePipeT_0_0) {
	const float theta__computePipeT_0_0 = 1.0f;
	const float A__computePipeT_0_0 = 1.0f;
	const float E__computePipeT_0_0 = p__computePipeT_0_0*1.0f;
	const float B__computePipeT_0_0 = ap__computePipeT_0_0/A__computePipeT_0_0;
	const float A2__computePipeT_0_0 = 1.0f;
	const float A3__computePipeT_0_0 = 1.0f;
	float pressureLeft__computePipeT_0_0;
	float flowRateLeft__computePipeT_0_0;
	const int leftId__computePipeT_0_0 = pipeNetwork__global_0_0[id__computePipeT_0_0].leftId;
	if (leftId__computePipeT_0_0 != -1) {
		pressureLeft__computePipeT_0_0 = pipeNetwork__global_0_0[leftId__computePipeT_0_0].pressure;
		flowRateLeft__computePipeT_0_0 = pipeNetwork__global_0_0[leftId__computePipeT_0_0].flowRate;
	} else {
		// ifElse5
		pressureLeft__computePipeT_0_0 = 0.0f;
		flowRateLeft__computePipeT_0_0 = 0.0f;
	}
	float pressureRight__computePipeT_0_0;
	float flowRateRight__computePipeT_0_0;
	const int rightId__computePipeT_0_0 = pipeNetwork__global_0_0[id__computePipeT_0_0].rightId;
	if (rightId__computePipeT_0_0 != -1) {
		pressureRight__computePipeT_0_0 = pipeNetwork__global_0_0[rightId__computePipeT_0_0].pressure;
		flowRateRight__computePipeT_0_0 = pipeNetwork__global_0_0[rightId__computePipeT_0_0].flowRate;
	} else {
		// ifElse6
		pressureRight__computePipeT_0_0 = 0.0f;
		flowRateRight__computePipeT_0_0 = 0.0f;
	}
	float pressureTop__computePipeT_0_0;
	float flowRateTop__computePipeT_0_0;
	const int topId__computePipeT_0_0 = pipeNetwork__global_0_0[id__computePipeT_0_0].topId;
	if (topId__computePipeT_0_0 != -1) {
		pressureTop__computePipeT_0_0 = pipeNetwork__global_0_0[topId__computePipeT_0_0].pressure;
		flowRateTop__computePipeT_0_0 = pipeNetwork__global_0_0[topId__computePipeT_0_0].pressure;
	} else {
		// ifElse7
		pressureTop__computePipeT_0_0 = 0.0f;
		flowRateTop__computePipeT_0_0 = 0.0f;
	}
	const float pressure__computePipeT_0_0 = pipeNetwork__global_0_0[id__computePipeT_0_0].pressure;
	const float flowRate__computePipeT_0_0 = pipeNetwork__global_0_0[id__computePipeT_0_0].flowRate;
	pressureLeft__computePipeT_0_0 = interpolate(pressure__computePipeT_0_0, pressureLeft__computePipeT_0_0, (ap__computePipeT_0_0*theta__computePipeT_0_0));
	flowRateLeft__computePipeT_0_0 = interpolate(flowRate__computePipeT_0_0, flowRateLeft__computePipeT_0_0, (ap__computePipeT_0_0*theta__computePipeT_0_0));
	pressureRight__computePipeT_0_0 = interpolate(pressure__computePipeT_0_0, pressureRight__computePipeT_0_0, (ap__computePipeT_0_0*theta__computePipeT_0_0));
	flowRateRight__computePipeT_0_0 = interpolate(flowRate__computePipeT_0_0, flowRateRight__computePipeT_0_0, (ap__computePipeT_0_0*theta__computePipeT_0_0));
	pressureTop__computePipeT_0_0 = interpolate(pressure__computePipeT_0_0, pressureTop__computePipeT_0_0, (ap__computePipeT_0_0*theta__computePipeT_0_0));
	flowRateTop__computePipeT_0_0 = interpolate(flowRate__computePipeT_0_0, flowRateTop__computePipeT_0_0, (ap__computePipeT_0_0*theta__computePipeT_0_0));
	const float B2__computePipeT_0_0 = ap__computePipeT_0_0/A2__computePipeT_0_0;
	const float B3__computePipeT_0_0 = ap__computePipeT_0_0/A3__computePipeT_0_0;
	const float Cp1__computePipeT_0_0 = pressureLeft__computePipeT_0_0 + flowRateLeft__computePipeT_0_0*(B__computePipeT_0_0 - E__computePipeT_0_0*absFloat(flowRateLeft__computePipeT_0_0));
	const float Cm2__computePipeT_0_0 = pressureRight__computePipeT_0_0 - flowRateRight__computePipeT_0_0*(B2__computePipeT_0_0 - E__computePipeT_0_0*absFloat(flowRateRight__computePipeT_0_0));
	const float Cm3__computePipeT_0_0 = pressureTop__computePipeT_0_0 - flowRateTop__computePipeT_0_0*(B3__computePipeT_0_0 - E__computePipeT_0_0*absFloat(flowRateTop__computePipeT_0_0));
	const float newPressure__computePipeT_0_0 = (Cp1__computePipeT_0_0/B__computePipeT_0_0 + Cm2__computePipeT_0_0/B2__computePipeT_0_0 + Cm3__computePipeT_0_0/B3__computePipeT_0_0)/(1/B__computePipeT_0_0 + 1/B2__computePipeT_0_0 + 1/B3__computePipeT_0_0);
	pipeNetwork__global_0_0[id__computePipeT_0_0].newPressure = newPressure__computePipeT_0_0;
	pipeNetwork__global_0_0[id__computePipeT_0_0].newFlowRateLeft = -newPressure__computePipeT_0_0/B__computePipeT_0_0 + Cp1__computePipeT_0_0/B__computePipeT_0_0;
	pipeNetwork__global_0_0[id__computePipeT_0_0].newFlowRateRight = -newPressure__computePipeT_0_0/B2__computePipeT_0_0 + Cm2__computePipeT_0_0/B2__computePipeT_0_0;
	pipeNetwork__global_0_0[id__computePipeT_0_0].newFlowRateTop = -newPressure__computePipeT_0_0/B3__computePipeT_0_0 + Cm3__computePipeT_0_0/B3__computePipeT_0_0;
}

void computeValve(const int id__computeValve_0_0, const float p__computeValve_0_0, const float ap__computeValve_0_0) {
	const float theta__computeValve_0_0 = 1.0f;
	const float A__computeValve_0_0 = 1.0f;
	const float E__computeValve_0_0 = p__computeValve_0_0*1.0f;
	const float B__computeValve_0_0 = ap__computeValve_0_0/A__computeValve_0_0;
	const float A2__computeValve_0_0 = 1.0f;
	const float A3__computeValve_0_0 = 1.0f;
	float pressureLeft__computeValve_0_0;
	float flowRateLeft__computeValve_0_0;
	const int leftId__computeValve_0_0 = pipeNetwork__global_0_0[id__computeValve_0_0].leftId;
	if (leftId__computeValve_0_0 != -1) {
		pressureLeft__computeValve_0_0 = pipeNetwork__global_0_0[leftId__computeValve_0_0].pressure;
		flowRateLeft__computeValve_0_0 = pipeNetwork__global_0_0[leftId__computeValve_0_0].flowRate;
	} else {
		// ifElse8
		pressureLeft__computeValve_0_0 = 0.0f;
		flowRateLeft__computeValve_0_0 = 0.0f;
	}
	const float pressure__computeValve_0_0 = pipeNetwork__global_0_0[id__computeValve_0_0].pressure;
	const float flowRate__computeValve_0_0 = pipeNetwork__global_0_0[id__computeValve_0_0].flowRate;
	pressureLeft__computeValve_0_0 = interpolate(pressure__computeValve_0_0, pressureLeft__computeValve_0_0, (ap__computeValve_0_0*theta__computeValve_0_0));
	flowRateLeft__computeValve_0_0 = interpolate(flowRate__computeValve_0_0, flowRateLeft__computeValve_0_0, (ap__computeValve_0_0*theta__computeValve_0_0));
	;
	const float Cp__computeValve_0_0 = pressureLeft__computeValve_0_0 + flowRateLeft__computeValve_0_0*(B__computeValve_0_0 - E__computeValve_0_0*absFloat(flowRateLeft__computeValve_0_0));
	const float tau__computeValve_0_0 = mechanicalCalculations__global_0_0[pipeNetwork__global_0_0[id__computeValve_0_0].mechanicalId].valvePosition;
	const float Cvp__computeValve_0_0 = 1.0f;
	const float Cv__computeValve_0_0 = (tau__computeValve_0_0*tau__computeValve_0_0)*Cvp__computeValve_0_0;
	const float newFlowRate__computeValve_0_0 = -B__computeValve_0_0*Cv__computeValve_0_0 + sqrtf((B__computeValve_0_0*Cv__computeValve_0_0)*(B__computeValve_0_0*Cv__computeValve_0_0) + 2*Cv__computeValve_0_0*Cp__computeValve_0_0);
	pipeNetwork__global_0_0[id__computeValve_0_0].newFlowRate = newFlowRate__computeValve_0_0;
	pipeNetwork__global_0_0[id__computeValve_0_0].newPressure = Cp__computeValve_0_0 - B__computeValve_0_0*newFlowRate__computeValve_0_0;
}

const float interpolate(const float center__interpolate_0_0, const float edge__interpolate_0_0, const float slope__interpolate_0_0) {
	return center__interpolate_0_0 - slope__interpolate_0_0*(center__interpolate_0_0 - edge__interpolate_0_0);
}

const float absFloat(const float number__absFloat_0_0) {
	float result__absFloat_0_0;
	if (number__absFloat_0_0 > 0.0f) {
		result__absFloat_0_0 = number__absFloat_0_0;
	} else {
		// ifElse9
		result__absFloat_0_0 = -number__absFloat_0_0;
	}
	return result__absFloat_0_0;
}

void computeMechanicalPressureSensorCalculations(const int id__computeMechanicalPressureSensorCalculations_0_0) {
	mechanicalCalculations__global_0_0[id__computeMechanicalPressureSensorCalculations_0_0].newPressure = 1470900.0f;
}

void computeMechanicalPumpCalculations(const int id__computeMechanicalPumpCalculations_0_0) {
	mechanicalCalculations__global_0_0[id__computeMechanicalPumpCalculations_0_0].newFlowRate = 100.0f;
}

void computeMechanicalValveCalculations(const int id__computeMechanicalValveCalculations_0_0) {
	static const int numberOfValvePositions__computeMechanicalValveCalculations_0_0 = 27;
	const float valvePositions__computeMechanicalValveCalculations_0_0[numberOfValvePositions__computeMechanicalValveCalculations_0_0] = {1.000000f, 0.929429f, 0.860600f, 0.793560f, 0.728357f, 0.665045f, 0.603682f, 0.544331f, 0.487064f, 0.431959f, 0.379106f, 0.328603f, 0.280566f, 0.235129f, 0.192450f, 0.152721f, 0.116179f, 0.083131f, 0.053995f, 0.029391f, 0.010391f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f};
	mechanicalCalculations__global_0_0[id__computeMechanicalValveCalculations_0_0].newValvePosition = valvePositions__computeMechanicalValveCalculations_0_0[valveIndex__global_0_0_copy_computeMechanicalValveCalculations_local.value%numberOfValvePositions__computeMechanicalValveCalculations_0_0];
}

void computeGlobalCalculations(void) {
	fluidProperties__global_0_0.newP = 1000.0f;
	fluidProperties__global_0_0.newAp = 1.2E+6;
}

void applyComputationElementNonPipeT(const int id__applyComputationElementNonPipeT_0_0) {
	pipeNetwork__global_0_0[id__applyComputationElementNonPipeT_0_0].pressure = pipeNetwork__global_0_0[id__applyComputationElementNonPipeT_0_0].newPressure;
	pipeNetwork__global_0_0[id__applyComputationElementNonPipeT_0_0].flowRate = pipeNetwork__global_0_0[id__applyComputationElementNonPipeT_0_0].newFlowRate;
}

void applyComputationElementPipeT(const int id__applyComputationElementPipeT_0_0) {
	pipeNetwork__global_0_0[id__applyComputationElementPipeT_0_0].pressure = pipeNetwork__global_0_0[id__applyComputationElementPipeT_0_0].newPressure;
	pipeNetwork__global_0_0[id__applyComputationElementPipeT_0_0].flowRateLeft = pipeNetwork__global_0_0[id__applyComputationElementPipeT_0_0].newFlowRateLeft;
	pipeNetwork__global_0_0[id__applyComputationElementPipeT_0_0].flowRateRight = pipeNetwork__global_0_0[id__applyComputationElementPipeT_0_0].newFlowRateRight;
	pipeNetwork__global_0_0[id__applyComputationElementPipeT_0_0].flowRateTop = pipeNetwork__global_0_0[id__applyComputationElementPipeT_0_0].newFlowRateTop;
}

void applyMechanicalCalculations(const int id__applyMechanicalCalculations_0_0) {
	mechanicalCalculations__global_0_0[id__applyMechanicalCalculations_0_0].pressure = mechanicalCalculations__global_0_0[id__applyMechanicalCalculations_0_0].newPressure;
	mechanicalCalculations__global_0_0[id__applyMechanicalCalculations_0_0].flowRate = mechanicalCalculations__global_0_0[id__applyMechanicalCalculations_0_0].newFlowRate;
	mechanicalCalculations__global_0_0[id__applyMechanicalCalculations_0_0].valvePosition = mechanicalCalculations__global_0_0[id__applyMechanicalCalculations_0_0].newValvePosition;
}

void applyGlobalCalculations(void) {
	fluidProperties__global_0_0.p = fluidProperties__global_0_0.newP;
	fluidProperties__global_0_0.ap = fluidProperties__global_0_0.newAp;
}

