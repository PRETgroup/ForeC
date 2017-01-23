/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Implementation of a pacemaker based on the UPPAAL model provided
 * by "Zhihao Jiang, Miroslav Pajic, Salar Moarref, Rajeev Alur,
 * and Rahul Mangharam. Modeling and Verification of a Dual Chamber
 * Implantable Pacemaker. Tools and Algorithms for the Construction
 * and Analysis of Systems. LNCS, vol. 7214, pp. 188-203. Springer
 * Berlin Heidelberg (2012)". UPPAAL models retrieved from
 * http://www.seas.upenn.edu/~zhihaoj/VHM/PM_verify.zip
 *
 * Author of this file: Eugene Kin Chee Yip (1 October 2013)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Abbreviations
 * -------------
 * SA: Sinoatrial
 * AV: Atrioventricular
 * AS: Atrial Sense
 * AP: Atrial Pacing
 * AR: Artrial Refractory
 * VS: Ventricular Sense
 * VP: Ventricular Pacing
 *
 * SVT: Supraventricular Tachycardia
 * PMT: Pacemaker Mediated Tachycardia
 * PVAB: Post Ventricular Atrial Blanking
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define shared
#define input
#define output
#define thread void
#define pause

//#include <stdio.h>

// Lossless buffer definition.
typedef struct {
	int values[2];
	unsigned int count;
	unsigned int size;
} Buffer;

// Pacemaker parameter definition.
typedef struct {
	// Pacing logic
	int baseRate;
	int operationalMode;
	int ekgSensitivity;
	int paceVoltage;
	
	// Rate adapter
	int sensitivityThreshold;
	int maxRate;
	int minRate;
	int maxAttackSlope;
	int maxDecaySlope;
} Param;

// Signal definition.
typedef enum {
	absent = 0,
	present = 1
} Signal;

// Event definition.
typedef struct {
	unsigned int timestamp;
	Signal AP;
	Signal VP;
	Signal DDD;
	Signal VDI;
	
	Signal lrl;
	Signal url;
	Signal pmt;
	Signal vurl;
	Signal elt;
} Event;

// Data log definition.
typedef struct {
	Event events[100];	// Used as a circular buffer.
	unsigned int tail;
	unsigned int size;
} Log;


// Arithmetic max combine function.
const unsigned int max(const unsigned int * const copy1, const unsigned int * const copy2) {
	if (*copy1 > *copy2) {
		return *copy1;
	} else {
		return *copy2;
	}
}


// Base period of the program in nanoseconds.
const unsigned int Base_Period = 1562500;

// Time periods in multiples of the Base_Period.
shared unsigned int TURI = 256;			// Upper Rate Interval
shared unsigned int TLRI = 640;			// Lowest Rate Interval
const unsigned int TAVI = 96;			// Atrio-Ventricular Interval
const unsigned int TVRP = 96;			// Ventricular Refractory Period
const unsigned int TPVAB = 32;			// Post-Ventricular Atrial Blocking
const unsigned int Threshold = 256;		// Mode-Switch Atrial Threshold

shared unsigned int TPVARP = 64;	// Post-Ventricular Atrial Refractory Period
const unsigned int TPVARP_100 = 64;		// 100 milliseconds.
const unsigned int TPVARP_500 = 320;	// 500 milliseconds.

const unsigned int T_150 = 96;			// 150 milliseconds.
const unsigned int T_200 = 128;			// 200 milliseconds.
const unsigned int T_500 = 320;			// 500 milliseconds.

const unsigned int Aminwait = 320;		// 500 milliseconds.
const unsigned int Vminwait = 320;		// 500 milliseconds.
const unsigned int Tantemin = 128;		// 200 milliseconds.
const unsigned int Tretromin = 128;		// 200 milliseconds.


// Input variables.
shared Signal A_Get = absent;
shared Signal A_Act = absent;

shared Signal V_Get = absent;
shared Signal V_Act = absent;

input unsigned int motionSensor = 0x0000;
input unsigned int rfIn = 0x0000;


// Output variables.
shared Signal AP = absent;
shared Signal VP = absent;

output unsigned int rfOut = 0x0000;


// Shared variables.
shared Signal AS = absent;
shared Signal AR = absent;

shared Signal VS = absent;

shared Signal DDD = absent;
shared Signal VDI = absent;

shared Buffer motionSensing2rateAdapter = {.values = {0, }, .count = 0, .size = 2};
shared unsigned int rate = 0;

shared Param parameters = {.baseRate = 0, .operationalMode = 0, .ekgSensitivity = 0, .paceVoltage = 0, .sensitivityThreshold = 0, .maxRate = 0, .minRate = 0, .maxAttackSlope = 0, .maxDecaySlope = 0};
shared Log log = {.events = { {0} , }, .tail = 0, .size = 100};


// Thread prototypes.
thread ekgSensing(shared Signal AP, shared Signal A_Act, shared Signal A_Get, shared Signal VP, shared Signal V_Act, shared Signal V_Get);
thread basic(shared Signal AS, shared Signal VS, shared Signal VP, shared Signal DDD, shared Signal VDI, shared Signal AP, input Signal A_Get, input Signal A_Act, shared Signal AR, shared unsigned int TPVARP, input Signal V_Get, input Signal V_Act);
thread modeSwitch(shared Signal AS, shared Signal AR, shared Signal AP, shared Signal VS, shared Signal VP, shared Signal DDD, shared Signal VDI);
thread patternVpAs(shared Signal VP, shared Signal VS, shared Signal AP, shared Signal AR, shared unsigned int TPVARP);

thread motionSensing(input unsigned int motionSensor, shared Buffer motionSensing2rateAdapter);
thread rateAdapter(shared Buffer motionSensing2rateAdapter, shared unsigned int rate);

thread logging(shared Signal AS, shared Signal AP, shared Signal AR, shared Signal VS, shared Signal VP, shared Signal VDI);
thread communication(input unsigned int rfIn, input unsigned int rfOut, shared Log log);


// Function prototypes.
double sin(double rad);
void icrc(unsigned short crc, unsigned long len, short jinit, int jrev);


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Main function of the program
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int main(int argc, char **argv) {
	//printf("Pacemaker\n");
	
	ekgSensing(AP, A_Act, A_Get, VP, V_Act, V_Get);
	basic(AS, VS, VP, DDD, VDI, AP, A_Get, A_Act, AR, TPVARP, V_Get, V_Act);
	modeSwitch(AS, AR, AP, VS, VP, DDD, VDI);
	patternVpAs(VP, VS, AP, AR, TPVARP);
	
	motionSensing(motionSensor, motionSensing2rateAdapter);
	rateAdapter(motionSensing2rateAdapter, rate);
	
	logging(AS, AP, AR, VS, VP, VDI);
	communication(rfIn, rfOut, log);
	
	return 0;
}


// ---------------------------------------------------------------
// Life critical tasks.

thread ekgSensing(shared Signal AP, shared Signal A_Act, shared Signal A_Get, shared Signal VP, shared Signal V_Act, shared Signal V_Get) {
	// Internal state.
	enum {
		Init_conduction = 0,
		Ante,
		Retro
	} state_conduction = Init_conduction;
	
	// Internal timers.
	unsigned int timer_rhm_a = 0;
	unsigned int timer_rhm_v = 0;
	unsigned int timer_conduction = 0;
	
	while (1) {
		// thread rhm_a(shared Signal AP, shared Signal A_Act, shared Signal A_Get);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Atrial Random Heart Model (RHM-A)
		* --------------------------------------
		* This component models the heart atrial behaviour in a random
		* manner.
		*
		* Inputs: AP, A_Act.
		* Outputs: A_Get.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("rhm_a\n");
		
		timer_rhm_a = timer_rhm_a + 1;
		
		if ((A_Act == present) || (AP == present)) {
			timer_rhm_a = 0;
		} else if (timer_rhm_a > Aminwait) {
			A_Get = present;
		} else {
			// Do nothing.
		}
		
		
		// thread rhm_v(shared Signal VP, shared Signal V_Act, shared Signal V_Get);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Ventricular Random Heart Model (RHM-V)
		* --------------------------------------
		* This component models the heart ventricle behaviour in a random
		* manner.
		*
		* Inputs: VP, V_Act.
		* Outputs: V_Get.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("rhm_v\n");
		
		timer_rhm_v = timer_rhm_v + 1;
		
		if ((V_Act == present) || (VP == present)) {
			timer_rhm_v = 0;				
		} else if (timer_rhm_v > Vminwait) {
			V_Get = present;
		} else {
			// Do nothing.
		}
		
		
		// thread conduction(shared Signal AP, shared Signal A_Act, shared Signal A_Get, shared Signal VP, shared Signal V_Act, shared Signal V_Get);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Ventricular Random Heart Model (RHM-V)
		* --------------------------------------
		* This component models the heart ventricle behaviour in a random
		* manner.
		*
		* Inputs: AP, A_Act, VP, V_Act.
		* Outputs: A_Get, V_Get.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("conduction\n");
		
		timer_conduction = timer_conduction + 1;
		
		if (state_conduction == Init_conduction) {
			if ((A_Get == present) || (AP == present)) {
				state_conduction = Ante;				// Go to state Ante.
				timer_conduction = 0;
			} else if ((V_Get == present) || (VP == present)) {
				state_conduction = Retro;				// Go to state Retro.
				timer_conduction = 0;
			} else if ((A_Get == present) || (AP == present) || (V_Get == present) || (VP == present)) {
				state_conduction = Init_conduction;		// Stay in state Init.
			} else {
				// Do nothing.
			}
		} else if (state_conduction == Ante) {
			if ((V_Get == present) || (VP == present)) {
				state_conduction = Init_conduction;		// Go to state Init.
			} else if (timer_conduction >= Tantemin) {
				state_conduction = Init_conduction;		// Go to state Init.
				V_Act = present;
			} else {
				// Do nothing.
			}
		} else if (state_conduction == Retro) {
			if ((A_Get == present) || (AP == present)) {
				state_conduction = Init_conduction;		// Go to state Init.
			} else if (timer_conduction >= Tretromin) {
				state_conduction = Init_conduction;		// Go to state Init.
				A_Act = present;
			} else {
				// Do nothing.
			}
		} else {
			// In an undefined state.
			//printf("!! conduction: In an undefined state (%d)\n", state_conduction);
		}
		
		pause;
	}
}


thread basic(shared Signal AS, shared Signal VS, shared Signal VP, shared Signal DDD, shared Signal VDI, shared Signal AP, input Signal A_Get, input Signal A_Act, shared Signal AR, shared unsigned int TPVARP, input Signal V_Get, input Signal V_Act) {
	// Internal states.
	enum {
		Init_avi_ms = 0,
		AVI,
		Wait_URI,
		VDI_Idle,
		VDI_AVI
	} state_avi_ms = Init_avi_ms;
	
	enum {
		Init_lri_ms = 0,	// State LRI
		Sensed,
		VDI_LRI
	} state_lri_ms = Init_lri_ms;
	
	enum {
		Init_pvarp_elt = 0,
		PVAB, PVARP
		//	Inter1, ABI, Inter2
	} state_pvarp_elt = Init_pvarp_elt;
	
	enum {
		Init_vrp = 0,	// Idle state.
		VRP
		//	Inter, VB
	} state_vrp = Init_vrp;
	
	// Internal timers.
	unsigned int timer_uri = 0;
	unsigned int timer_avi_ms = 0;
	unsigned int timer_lri_ms = 0;
	unsigned int timer_pvarp_elt = 0;
	unsigned int timer_vrp = 0;
	
	// Internal signals.
	Signal A_Block = absent;
	Signal V_Block = absent;
	Signal VP_new = absent;	// New VP.
	
	while (1) {
		// thread uri(shared Signal VP, shared Signal VS, shared unsigned int timer_uri);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Upper Rate Interval (URI)
		* -------------------------
		* This component limits the ventricular pacing rate by enforcing
		* a lower bound on the times between consecutive ventricle events.
		*
		* Inputs: VS, VP.
		* Outputs: none.
		* Side-effects: timer_uri.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("uri\n");
		
		timer_uri = timer_uri + 1;
		
		if ((VP == present) || (VS == present)) {
			timer_uri = 0;
		} else {
			// Do nothing.
		}
	
		// thread avi_ms(shared Signal AS, shared Signal VS, shared Signal VP, shared Signal DDD, shared Signal VDI, shared Signal AP, shared Signal VP, shared unsigned int timer_uri);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Atrio-Ventricular Interval (AVI) with Mode-Switch (MS)
		* ------------------------------------------------------
		* This component maintains the appropriate delay between the
		* atrial activation and the ventricular activation. Can switch
		* between DDD and VDI modes.
		*
		* Inputs: AS, VS, VP, DDD, VDI.
		* Outputs: AP, VP.
		* Side-effects: timer_uri.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("avi_ms\n");
		
		timer_avi_ms = timer_avi_ms + 1;
		
		// Reset signals.
		VP_new = absent;
		
		if (state_avi_ms == Init_avi_ms) {
			if ((AS == present) || (AP == present)) {
				state_avi_ms = AVI;				// Go to state AVI.
				timer_avi_ms = 0;
			} else if (VDI == present) {
				state_avi_ms = VDI_Idle;		// Go to state VDI_Idle.
			} else {
				// Do nothing.
			}
		} else if (state_avi_ms == AVI) {
			if (VDI == present) {
				state_avi_ms = VDI_AVI;			// Go to state VDI_AVI.
			} else if (VS == present) {
				state_avi_ms = Init_avi_ms;		// Go to state Init.
			} else if (timer_avi_ms >= TAVI) {
				if (timer_uri >= TURI) {
					state_avi_ms = Init_avi_ms;	// Go to state Init.
					VP_new = present;
				} else if (timer_uri <= TURI) {
					state_avi_ms = Wait_URI;	// Go to state Wait_URI.
				} else {
					// Do nothing.
				}
			} else {
				// Do nothing.
			}
		} else if (state_avi_ms == Wait_URI) {
			if (timer_uri >= TURI) {
				state_avi_ms = Init_avi_ms;		// Go to state Init.
				VP_new = present;
			} else if (VS == present) {
				state_avi_ms = Init_avi_ms;		// Go to state Init.
			} else if (VDI == present) {
				state_avi_ms = VDI_Idle;		// Go to state VDI_Idle.
				timer_avi_ms = 0;
			} else {
				// Do nothing.
			}
		} else if (state_avi_ms == VDI_Idle) {
			if (DDD == present) {
				state_avi_ms = Init_avi_ms;		// Go to state Init.
			} else if ((AS == present) || (AP == present)) {
				state_avi_ms = VDI_AVI;			// Go to state VDI_AVI.
				timer_avi_ms = 0;
			} else {
				// Do nothing.
			}
		} else if (state_avi_ms == VDI_AVI) {
			if (VS == present) {
				state_avi_ms = VDI_Idle;		// Go to state VDI_Idle.
			} else if (DDD == present) {
				state_avi_ms = AVI;				// Go to state AVI.
			} else if (timer_avi_ms >= TAVI) {
				state_avi_ms = VDI_Idle;		// Go to state VDI_Idle.
			} else {
				// Do nothing.
			}
		} else {
			// In an undefined state.
			//printf("!! avi_ms: In an undefined state (%d)\n", state_avi_ms);
		}
		
		
		// thread lri_ms(shared Signal AS, shared Signal VS, shared Signal VP, shared Signal DDD, shared Signal VDI, shared Signal AP, shared Signal VP);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Lower Rate Interval (LRI) with Mode-Switch (MS)
		* -----------------------------------------------
		* This component keeps the heart rate above a minimum value. Can
		* switch between DDD and VDI modes.
		*
		* Inputs: AS, VS, VP, DDD, VDI.
		* Outputs: AP, VP.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("lri_ms\n");
		
		timer_lri_ms = timer_lri_ms + 1;
		
		// Reset output signals.
		AP = absent;
		
		if (state_lri_ms == Init_lri_ms) {
			if ((VP == present) || (VS == present)) {
				state_lri_ms = Init_lri_ms; // Stay in state Init.
				timer_lri_ms = 0;
			} else if (timer_lri_ms >= (TLRI - TAVI)) {
				state_lri_ms = Init_lri_ms;	// Stay in state Init.
				AP = present;
			} else if (AS == present) {
				state_lri_ms = Sensed;		// Go to state Sensed.
			} else if (VDI == present) {
				state_lri_ms = VDI_LRI;		// Go to state VDI_LRI.
			} else {
				// Do nothing.
			}
		} else if (state_lri_ms == VDI_LRI) {
			if (VS == present) {
				state_lri_ms = VDI_LRI;		// Stay in state VDI_LRI.
				timer_lri_ms = 0;
			} else if (timer_lri_ms >= TLRI) {
				state_lri_ms = Init_lri_ms;	// Stay in state VDI_LRI.
				VP_new = present;
			} else if (DDD == present) {
				state_lri_ms = Init_lri_ms;	// Go to state Init.
				timer_lri_ms = 0;
			}
		} else if (state_lri_ms == Sensed) {
			if (VDI == present) {
				state_lri_ms = VDI_LRI;		// Go to state VDI_LRI.
			} else if ((VP == present) || (VS == present)) {
				state_lri_ms = Init_lri_ms;	// Go to state Init.
				timer_lri_ms = 0;
			} else {
				// Do nothing.
			}
		} else {
			// In an undefined state.
			//printf("!! lri_ms: In an undefined state (%d)\n", state_lri_ms);
		}
		
		
		// thread pvarp_elt(shared Signal A_Get, shared Signal VS, shared Signal VP, shared Signal A_Act, shared Signal AS, shared Signal AR, shared Signal A_Block, shared unsigned int TPVARP);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Post Ventricular Atrial Refractory Period (PVARP) with Endless
		* Loop Tachycardia (ELT) Termination
		* --------------------------------------------------------------
		* This component ignores atrial events during the PVAB period and
		* allows atrial events to trigger AR events during the PVARP. This
		* filters noisy atrial events. The PVARP is allowed to be changed
		* once by the anti-ELT algorithm.
		*
		* Inputs: A_Get, VS, VP, A_Act.
		* Outputs: AS, AR, A_Block.
		* Side-effects: TPVARP.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("pvarp_elt\n");
		
		timer_pvarp_elt = timer_pvarp_elt + 1;
		
		// Reset signals.
		AS = absent;
		AR = absent;
		A_Block = absent;
		
		if (state_pvarp_elt == Init_pvarp_elt) {
			if ((A_Act == present) || (A_Get == present)) {
				//	state_pvarp_elt = Inter1;		// Instantaneous transition.
				
				state_pvarp_elt = Init_pvarp_elt;	// Stay in state Init.
				AS = present;
			} else if ((VS == present) || (VS == present)) {
				state_pvarp_elt = PVAB;				// Go to state PVAB.
				timer_pvarp_elt = 0;
			} else {
				// Do nothing.
			}
		} else if (state_pvarp_elt == PVAB) {
			if ((A_Act == present) || (A_Get == present)) {
				//	state_pvarp_elt = ABI;			// Instantaneous transition.
				
				state_pvarp_elt = PVAB;				// Stay in state PVAB.
				A_Block = present;
			} else if (timer_pvarp_elt >= TPVAB) {
				state_pvarp_elt = PVARP;			// Go to state PVARP.
			} else {
				// Do nothing.
			}
		} else if (state_pvarp_elt == PVARP) {
			if ((A_Act == present) || (A_Get == present)) {
				// state_pvarp_elt = Inter2;		// Instantaneous transition.
				
				state_pvarp_elt = PVARP;			// Stay in state PVARP.
				AR = present;
			} else if (timer_pvarp_elt >= TPVARP) {
				state_pvarp_elt = Init_pvarp_elt;	// Go to state Init.
				TPVARP = TPVARP_100;
			} else {
				// Do nothing.
			}
		} else {
			// In an undefined state.
			//printf("!! pvarp_elt: In an undefined state (%d)\n", state_pvarp_elt);
		}
		
		
		// thread vrp(shared Signal V_Get, shared Signal VP, shared Signal V_Act, shared Signal VS, shared Signal V_Block);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Ventricular Refractory Period (VRP)
		* -----------------------------------
		* This component follows each ventricular event to filter noise
		* and early events in the ventricular channel which could
		* otherwise cause undesired pacemaker behaviour.
		*
		* Inputs: V_Get, VP, V_Act.
		* Outputs: VS, V_Block.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("vrp\n");
		
		timer_vrp = timer_vrp + 1;
		
		// Reset signals.
		VS = absent;
		V_Block = absent;
		
		if (state_vrp == Init_vrp) {
			if ((V_Act == present) || (V_Get == present)) {
				//	state_vrp = Inter;	// Instantaneous transition.
				
				state_vrp = VRP;		// Go to state VRP.
				VS = present;
				timer_vrp = 0;
			} else if (VP == present) {
				state_vrp = VRP;		// Go to state Inter.
				timer_vrp = 0;
			}
		} else if (state_vrp == VRP) {
			if (timer_vrp >= TVRP) {
				state_vrp = Init_vrp;	// Go to state Init.
			} else if ((V_Act == present) || (V_Get == present)) {
				//	state_vrp = VB;		// Instantaneous transition.
				
				state_vrp = VRP;		// Stay in state VRP.
				V_Block = present;
			} else {
				// Do nothing.
			}
		} else {
			// In an undefined state.
			//printf("!! vrp: In an undefined state (%d)\n", state_vrp);
		}
		
		VP = VP_new;
		
		pause;
	}
}


thread modeSwitch(shared Signal AS, shared Signal AR, shared Signal AP, shared Signal VS, shared Signal VP, shared Signal DDD, shared Signal VDI) {
	// Internal states.
	enum {
		Init_interval_ms = 0,	// First Wait state.
		Wait
		//	Reset, APed
	} state_interval_ms = Init_interval_ms;

	enum State_counter {
		Init_counter_ms = 0,
		Fast1, Fast2, Fast3, Fast4, Fast5, Fast6, Fast7, Fast8
		//	Switch1, Switch2
	} state_counter_ms = Init_counter_ms;

	enum State_duration {
		Init_duration_ms = 0,
		V1, V2, V3, V4, V5, V6, V7, V8, V9
	} state_duration_ms = Init_duration_ms;
	
	// Internal timer.
	unsigned int timer_interval_ms = 0;
	
	// Internal signals.
	Signal Fast = absent;
	Signal Slow = absent;
	
	Signal D_Beg = absent;
	Signal D_Beg_new = absent;	// New D_Beg.
	Signal D_End = absent;
	
	while (1) {	
		// thread counter_ms(shared Signal Fast, shared Signal Slow, shared Signal D_End, shared Signal DDD, shared Signal VDI, shared Signal D_Beg);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Counter for Fast and Slow Intervals between Atrial Events (for
		* the Mode-Switch Algorithm)
		* --------------------------------------------------------------
		* This component counts up for "fast" events and counts down for
		* "slow" events. Switches to VDI mode when "fast" events have
		* occured and DDD otherwise.
		*
		* Inputs: Fast, Slow, D_End.
		* Outputs: DDD, VDI, D_Beg.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("counter_ms\n");
		
		// Reset signals.
		DDD = absent;
		VDI = absent;
		D_Beg_new = absent;
		
		if (state_counter_ms == Init_counter_ms) {
			if (Fast == present) {
				state_counter_ms = Fast1;					// Go to state Fast1.
			} else {
				// Do nothing.
			}
		} else if (state_counter_ms == Fast1) {
			if (Slow == present) {
				state_counter_ms = Init_counter_ms;			// Go to state Init.
				DDD = present;								// From the transition from state Switch1.
			} else if (Fast == present) {
				state_counter_ms = Fast2;					// Go to state Fast2.
			} else if (D_End == present) {
				state_counter_ms = Fast1;					// Stay in state Fast1.
				VDI = present;								// From the committed state transition.
			} else {
				// Do nothing.
			}
		} else if (state_counter_ms == Fast8) {
			if (Slow == present) {
				state_counter_ms = Fast7;					// Go back to state Fast7.
			} else if (D_End == present) {
				state_counter_ms = Fast8;					// Stay in state Fast8.
				VDI = present;								// From the transition from state Fast8.
			} else {
				// Do nothing.
			}
		} else {
			// Fast2 to Fast7.
			if (Slow == present) {
				state_counter_ms = State_counter((int)state_counter_ms - 1);	// Go back to state Fast1 to Fast6.
			} else if (Fast == present) {
				if (state_counter_ms == Fast7) {
					D_Beg_new = present;										// From the committed state transition.
				}
				state_counter_ms = State_counter((int)state_counter_ms + 1);	// Go to state Fast3 to Fast8.
			} else if (D_End == present) {
				state_counter_ms = State_counter((int)state_counter_ms + 0);	// Stay in the current state.
				VDI = present;													// From the transition from the current state.
			} else {
				// Do nothing.
			}
		}
	
	
		// thread duration_ms(shared Signal VS, shared Signal VP, shared Signal D_Beg, shared Signal D_End);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Duration of Fast Atrial Events (for the Mode-Switch Algorithm)
		* --------------------------------------------------------------
		* This component confirms SVT after a period of time.
		*
		* Inputs: VS, VP, D_Beg.
		* Outputs: D_End.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("duration_ms\n");
		
		// Reset signal.
		D_End = absent;
		
		if (state_duration_ms == Init_duration_ms) {
			if (D_Beg == present) {
				state_duration_ms = V1;											// Go to state V1.
			} else {
				// Do nothing.
			}
		} else {
			// V1 to V8.
			if ((VS == present) || (VP == present)) {
				state_duration_ms = State_duration((int)state_duration_ms + 1);	// Go to state V2 to V9.
				
				if (state_duration_ms == V9) {									// Instantaneous transition.
					state_duration_ms = Init_duration_ms;						// Go to state Init.
					D_End = present;
				} else {
					// Do nothing.
				}
			} else {
				// Do nothing.
			}
		}
		
		D_Beg = D_Beg_new;
		
		
		// thread interval_ms(shared Signal AS, shared Signal AR, shared Signal AP, shared Signal Fast, shared Signal Slow);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Interval between Atrial Events (for the Mode-Switch Algorithm)
		* --------------------------------------------------------------
		* This component measures the interval between atrial events
		* outside the blanking period (AS, AR). The interval is "fast" if
		* it is above a threshold and "slow" otherwise.
		*
		* Inputs: AS, AR, AP.
		* Outputs: Fast, Slow.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("interval_ms\n");
		
		timer_interval_ms = timer_interval_ms + 1;
		
		// Reset signals.
		Fast = absent;
		Slow = absent;
		
		if (state_interval_ms == Init_interval_ms) {
			if ((AP == present) || (AR == present) || (AS == present)) {
				state_interval_ms = Wait;		// Go to state Wait.
				timer_interval_ms = 0;
			} else {
				// Do nothing.
			}
		} else if (state_interval_ms == Wait) {
			if ((AR == present) || (AS == present)) {
				//	state_interval_ms = Reset;	// Instantaneous transiiton.
				
				if (timer_interval_ms <= Threshold) {
					state_interval_ms = Wait;	// Stay in state Wait.
					Fast = present;
					timer_interval_ms = 0;
				} else if (timer_interval_ms > Threshold) {
					state_interval_ms = Wait;	// Stay in state Wait.
					Slow = present;
					timer_interval_ms = 0;
				} else {
					// Do nothing.
				}
			} else if (AP == present) {
				//	state_interval_ms = APed;	// Instantaneous transition.
				
				state_interval_ms = Wait;		// Stay in state Wait.
				Slow = present;
				timer_interval_ms = 0;
			} else {
				// Do nothing.
			}
		} else {
			// In an undefined state.
			//printf("!! interval_ms: In an undefined state (%d)\n", state_interval_ms);
		}
		
		pause;
	}
}


thread patternVpAs(shared Signal VP, shared Signal VS, shared Signal AP, shared Signal AR, shared unsigned int TPVARP) {
	// Internal states.
	enum {
		Init_pattern_vpAs = 0,
		VP1
		//	AS1,
		//	Cancel
	} state_pattern_vpAs = Init_pattern_vpAs;
	
	enum State_counter {
		Init_counter_vpAs = 0,
		E1, E2, E3, E4, E5, E6, E7, E8
	} state_counter_vpAs = Init_counter_vpAs;
	
	// Internal timer.
	unsigned int timer_pattern_vpAs = 0;
	
	// Internal signals.
	Signal VP_AS = absent;
	Signal Reset = absent;
	
	while (1) {
		// thread pattern_vpAs(shared Signal VP, shared Signal VS, shared Signal AP, shared Signal AR, shared Signal VP_AS, shared Signal Reset);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Ventricular Pacing - Atrial Pacing (VP-AS) Pattern Detector
		* (for ELT-Termination Algorithm)
		* -----------------------------------------------------------
		* This component detects the VP-AS pattern with ventricular rate
		* at the upper rate limit and sends out VP_AS event if the
		* interval qualifies.
		*
		* Inputs: VP, VS, AP, AR.
		* Outputs: VP_AS, Reset.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("pattern_vpAs\n");
		
		timer_pattern_vpAs = timer_pattern_vpAs + 1;
		
		// Reset signals.
		VP_AS = absent;
		Reset = absent;
		
		if (state_pattern_vpAs == Init_pattern_vpAs) {
			if (VP == present) {
				state_pattern_vpAs = VP1;			// Go to state VP1.
				timer_pattern_vpAs = 0;
			} else {
				// Do nothing.
			}
		} else if (state_pattern_vpAs == VP1) {
			if (AS == present) {
				//	state_pattern_vpAs = AS1;		// Instantaneous transition.
				
				if (T_150 <= timer_pattern_vpAs && timer_pattern_vpAs <= T_200) {
					VP_AS = present;
				} else {
					// Do nothing.
				}
			} else if ((VS == present) || (AP == present) || (AR == present)) {
				//	state_pattern_vpAs = Cancel;	// Instantaneous transition.
				
				Reset = present;
			}
			state_pattern_vpAs = Init_pattern_vpAs;	// Go to state Init.
		} else {
			// In an undefined state.
			//printf("!! pattern_vpAs: In an undefined state (%d)\n", state_pattern_vpAs);
		}
	
	
		// thread counter_vpAs(shared Signal VP_AS, shared Signal Reset, shared unsigned int TPVARP);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Counter for Ventricular Pacing - Atrial Pacing (VP-AS) Patterns
		* (for ELT-Termination Algorithm)
		* ---------------------------------------------------------------
		* This component counts the number of qualified VP-AS patterns.
		*
		* Inputs: VP_AS, Reset.
		* Outputs: none.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("counter_vpAs\n");
		
		if (state_counter_vpAs == Init_counter_vpAs) {
			if (VP_AS == present) {
				state_counter_vpAs = E1;										// Go to state E1.
			} else {
				// Do nothing.
			}
		} else {
			// E1 to E7.
			if (Reset == present) {
				state_counter_vpAs = Init_counter_vpAs;							// Go to state Init.
			} else if (VP_AS == present) {
				state_counter_vpAs = State_counter((int)state_counter_vpAs + 1);// Go to state E2 to E8.
				
				if (state_counter_vpAs == E8) {	// Instantaneous transition.
					state_counter_vpAs = Init_counter_vpAs;	// Go to state Init.
					TPVARP = T_500;
				} else {
					// Do nothing.
				}
			} else {
				// Do nothing.
			}
		}
		
		pause;
	}
}


// ---------------------------------------------------------------
// Mission critical tasks.

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Motion sensing
 * --------------
 * This component determines the patient's level of physical 
 * activity. This is simply implemented as a Fast Fourier Transform
 * from the fft1.c Malardalen WCET Benchmark.
 *
 * Inputs: motionSensor.
 * Outputs: motionSensing2rateAdapter.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
thread motionSensing(input unsigned int motionSensor, shared Buffer motionSensing2rateAdapter) {
	// Internal variables.
	double PI = 3.14159;
	double PI_half = 1.570795;
	double PI_twice = 6.28318;
	
	double ar[8];
	ar[0] = 1.0;
	ar[1] = 0.70711;
	ar[2] = 0.0;
	ar[3] = -0.70711;
	ar[4] = -1.0;
	ar[5] = -0.70711;
	ar[6] = 0.0;
	ar[7] = 0.70711;
	
	double ai[8];
	ai[0] = 0.0;
	ai[1] = 0.0;
	ai[2] = 0.0;
	ai[3] = 0.0;
	ai[4] = 0.0;
	ai[5] = 0.0;
	ai[6] = 0.0;
	ai[7] = 0.0;

	int n = 8, o = 0;
	int i, j, k, it, xp, xp2, j1, j2;
	double w, wr, wi, dr1, dr2, di1, di2, tr, ti, arg;
	
	while (1) {
		//printf("motionSensing\n");

		// Perform Fast Fourier Transform.
		// fft1.c from the Malardalen WCET Benchmark.
		j = 2;
		
		/*  Main FFT Loops  */
		xp2 = n;
		for (it = 0; it < 1; it = it + 1) {
			xp = xp2;
			xp2 = xp2/2;
			w = PI / xp2;
			
			for (k = 0; k < xp2; k = k + 1) {
				arg = k * w;	// 0 to PI
				wr = sin(PI_half - arg);
				wi = -sin(arg);
				i = k - xp;
				
				for (j = xp; j <= n; j = j + xp) {
					j1 = j + i;
					j2 = j1 + xp2;
					dr1 = ar[j1];
					dr2 = ar[j2];
					di1 = ai[j1];
					di2 = ai[j2];
					tr = dr1 - dr2;
					ti = di1 - di2;
					ar[j1] = dr1 + dr2;
					ai[j1] = di1 + di2;
					ar[j2] = tr * wr - ti * wi;
					ai[j2] = ti * wr + tr * wi;
				}
			}
		}
		
		/*  Digit Reverse Counter  */
		j1 = n / 2;		// 4
		j2 = n - 1;		// 7
		j = 1;
		
		for (i = 1; i <= j2; i = i + 1) {
			if (i < j) {
				tr = ar[j-1];
				ti = ai[j-1];
				ar[j-1] = ar[i-1];
				ai[j-1] = ai[i-1];
				ar[i-1] = tr;
				ai[i-1] = ti;
			}
			
			k = j1;
			while (k < j && k > 0) {
				j = j - k;
				k = k / 2;	// If k = 1/2 = 0 and j > 0, then the while condition cannot terminate.
			}
			j = j + k;
		}
		
		o = (o + 1) % 8;
		if (motionSensing2rateAdapter.count == motionSensing2rateAdapter.size) {
			//printf("!! motionSensing2rateAdapter overflow\n");
			motionSensing2rateAdapter.count = 0;
		}
		motionSensing2rateAdapter.values[motionSensing2rateAdapter.count] = ai[o];
		motionSensing2rateAdapter.count = motionSensing2rateAdapter.count + 1;
		
		pause;
	}
}

double sin(double rad) {
	double PI_twice = 6.28318;
	double app;
	double diff;
	int inc;
	
	while (rad > PI_twice) {
		rad = rad - PI_twice;
	}
	
	while (rad < -PI_twice) {
		rad = rad + PI_twice;
	}
	
										// rad  = -PI_twice                  to  PI_twice
	diff = (rad * (-(rad*rad))) / 6.0;	// diff =  PI_twice^3/6              to -PI_twice^3/6
    app = rad + diff;					// app  = (-PI_twice + PI_twice^3/6) to (PI_twice - PI_twice^3/6)
    inc = 2;
	
	while ((diff >= 0.00001 && diff >= 0) || (-diff >= 0.00001 && diff < 0)) {
		diff = (diff * (-(rad*rad))) / ((2.0 * inc) * (2.0 * inc + 1.0));
		app = app + diff;
		inc = inc + 1;
	}
	
	return(app);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Rate adapter
 * ------------
 * This component changes the pacing rate depending on the patient's
 * level of physical activity. This is simply implemented as a 
 * statistical analyser from the st.c Malardalen WCET Benchmark.
 *
 * Inputs: motionSensing2rateAdapter.
 * Outputs: rate.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
thread rateAdapter(shared Buffer motionSensing2rateAdapter, shared unsigned int rate) {
	int MAX = 1000;
	int i;
	int Seed = 0;
	double ArrayA[1000], ArrayB[1000];
	double MeanA, MeanB, VarA, VarB, StddevA, StddevB;
	double SumA, SumB;
	double numerator;
	double diffsA, diffsB;
	double Aterm, Bterm, Aterm_sqrt, Bterm_sqrt;
	double Coef;

	while (1) {
		//printf("rateAdapter\n");

		// Perform Statistical analysis.
		// st.c from the Malardalen WCET Benchmark.
		
		// Initialise.
		for (i=0; i < MAX; i = i + 1) {
			ArrayA[i] = i + (((Seed * 133) + 81) % 8095)/8095.0;
			ArrayB[i] = i + (((Seed * 133) + 81) % 8095)/8095.0;
		}
		
		// Mean.
		SumA = 0;
		SumB = 0;
		for (i = 0; i < MAX; i = i + 1) {
			SumA = SumA + ArrayA[i];
			SumB = SumB + ArrayB[i];
		}
		MeanA = SumA / MAX;
		MeanB = SumB / MAX;
		
		// Standard deviation.
		diffsA = 0.0;
		diffsB = 0.0;
		for (i = 0; i < MAX; i = i + 1) {
			diffsA = diffsA + (ArrayA[i] - MeanA) * (ArrayA[i] - MeanA);
			diffsB = diffsB + (ArrayB[i] - MeanB) * (ArrayB[i] - MeanB);
		}
		VarA = diffsA/MAX;
		VarB = diffsB/MAX;
		
		StddevA = VarA;
		StddevB = VarB;
		for (i = 0; i < 10; i = i + 1) {
			StddevA = 0.5 * (StddevA + VarA/StddevA);
			StddevB = 0.5 * (StddevB + VarB/StddevB);
		}
		
		// Correlation.
		numerator = 0.0;
		Aterm = Bterm = 0.0;
		for (i = 0; i < MAX; i = i + 1) {
			numerator = numerator + (ArrayA[i] - MeanA) * (ArrayB[i] - MeanB);
			Aterm = Aterm + (ArrayA[i] - MeanA) * (ArrayA[i] - MeanA);
			Bterm = Bterm + (ArrayB[i] - MeanB) * (ArrayB[i] - MeanB);
		}
		
		for (i = 0; i < 10; i = i + 1) {
			Aterm_sqrt = 0.5 * (Aterm_sqrt + Aterm/Aterm_sqrt);
			Bterm_sqrt = 0.5 * (Bterm_sqrt + Bterm/Bterm_sqrt);
		}
		
		Coef = numerator / (Aterm_sqrt * Bterm_sqrt);
		
		pause;
	}
}


// ---------------------------------------------------------------
// Non-critical tasks.

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Logging of state violations
* ---------------------------
* This component monitors the pacemaker and logs any state
* violations.
*
* Inputs: AS, AP, AR, A_Block, VS, VP, V_Block, VDI.
* Outputs: none.
* Side-effects: log.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

thread logging(shared Signal AS, shared Signal AP, shared Signal AR, shared Signal A_Block, shared Signal VS, shared Signal VP, shared Signal V_Block, shared Signal VDI) {
	// Internal states.
	enum {
		Init_lrl = 0,
		Wait_lrl
	} state_lrl = Init_lrl;
	
	enum {
		Init_url = 0,
		Wait_url
	} state_url = Init_url;
	
	enum {
		Init_pmt = 0,
		Wait_pmt,
		Error_pmt
	} state_pmt = Init_pmt;
	
	enum {
		Init_vurl = 0,
		V_vurl,
		Error_vurl
	} state_vurl = Init_vurl;
	
	enum {
		Init_elt = 0,
		AS_elt, VP_elt,
		Error_elt
	} state_elt = Init_elt;
	
	// Internal timers.
	unsigned int timer_lrl = 0;
	unsigned int timer_url = 0;
	unsigned int timer_pmt = 0;
	unsigned int timer_vurl = 0;
	
	// Internal signals.
	Signal violated = absent;
	Event event;
	
	while (1) {
		violated = absent;
		
		event.timestamp = 0;
		event.AP = absent;
		event.VP = absent;
		event.DDD = absent;
		event.VDI = absent;
		event.lrl = absent;
		event.url = absent;
		event.pmt = absent;
		event.vurl = absent;
		event.elt = absent;
		
		// lrl(shared Signal VP, shared Signal VS);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Monitor for Lower Rate Limit (LRL)
		* ----------------------------------
		* This component monitors the ventricular rate. The interval
		* between two ventricle events should be less than TLRI.
		*
		* Inputs: VP, VS.
		* Outputs: none.
		* Side-effects: log.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("lrl\n");
		
		timer_lrl = timer_lrl + 1;
		
		if (state_lrl == Init_lrl) {
			if ((VS == present) || (VP == present)) {
				state_lrl = Wait_lrl;	// Go to state Wait.
				timer_lrl = 0;
			} else {
				// Do nothing.
			}
		} else if (state_lrl == Wait_lrl) {
			if ((VS == present) || (VP == present)) {
				state_lrl = Wait_lrl;	// Stay in state Wait.
				if (timer_lrl > TLRI) {
					// Timing violation.
					violated = present;
					event.lrl = present;
				}
				timer_lrl = 0;
			} else {
				// Do nothing.
			}
		} else {
			// In an undefined state.
			//printf("!! lrl: In an undefined state (%d)\n", state_lrl);
		}
		
		
		// url(shared Signal VP, shared Signal VS);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Monitor for Upper Rate Limit (URL)
		* ----------------------------------
		* This component monitors the ventricular rate. The interval
		* between a ventricle event and pacing should be longer than
		* TLRI.
		*
		* Inputs: VP, VS.
		* Outputs: none.
		* Side-effects: log.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("url\n");
		
		timer_url = timer_url + 1;
		
		if (state_url == Init_url) {
			if ((VS == present) || (VP == present)) {
				state_url = Wait_url;	// Go to state Wait.
				timer_url = 0;
			} else {
				// Do nothing.
			}
		} else if (state_url == Wait_url) {
			if (VS == present) {
				state_url = Wait_url;	// Stay in state Wait.
				timer_url = 0;
			} else if (VP == present) {
				state_url = Wait_url;	// Stay in state Wait.
				if (timer_url < TLRI) {
					// Timing violation.
					violated = present;
					event.url = present;
				}
				timer_url = 0;
			} else {
				// Do nothing.
			}
		} else {
			// In an undefined state.
			//printf("!! url: In an undefined state (%d)\n", state_url);
		}
		
		
		// pmt(shared Signal VP, shared Signal VS);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Monitor for Pacemaker Mediated Tachycardia (PMT)
		* ------------------------------------------------
		* This component monitors for tachycardia caused by the pacemaker.
		*
		* Inputs: VP, VS.
		* Outputs: none.
		* Side-effects: log.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("pmt\n");
		
		timer_pmt = timer_pmt + 1;
		
		if (state_pmt == Init_pmt) {
			if ((VS == present) || (VP == present)) {
				state_pmt = Wait_pmt;	// Go to state Wait.
				timer_pmt = 0;
			} else {
				// Do nothing.
			}
		} else if (state_pmt == Wait_pmt) {
			if ((VS == present) || (VP == present)) {
				state_pmt = Wait_pmt;	// Stay in state Wait.
				if (timer_pmt > TLRI) {
					// Timing violation.
					violated = present;
					event.pmt = present;
				}
				timer_pmt = 0;
			} else {
				// Do nothing.
			}
		} else {
			// In an undefined state.
			//printf("!! pmt: In an undefined state (%d)\n", state_pmt);
		}
		
		
		// ms(shared Signal VDI);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Monitor for Mode-Switch (MS)
		* ----------------------------
		* This component monitors the pacing mode (DDD or VDI).
		*
		* Inputs: VDI.
		* Outputs: none.
		* Side-effects: log.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("ms\n");
		
		if (VDI == present) {
			violated = present;
		} else {
			// Do nothing.
		}
		
		
		// vurl(shared Signal VP);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Monitor for Ventricle Upper Rate Limit (VURL)
		* ---------------------------------------------
		* This component monitors the upper rate limit of ventricular
		* pacing.
		*
		* Inputs: VP.
		* Outputs: none.
		* Side-effects: log.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("vurl\n");
		
		timer_vurl = timer_vurl + 1;
		
		if (state_vurl == Init_vurl) {
			if (VP == present) {
				state_vurl = V_vurl;	// Go to state V.
				timer_vurl = 0;
			} else {
				// Do nothing.
			}
		} else if (state_vurl == V_vurl) {
			if (VP == present) {
				if (timer_vurl <= TURI) {
					state_vurl = V_vurl;	// Stay in state V.
				} else {
					state_vurl = Error_vurl;// Go to state Error.
					violated = present;
					event.vurl = present;
				}
				
				timer_vurl = 0;
			} else {
				// Do nothing.
			}
		} else if (state_vurl == Error_vurl) {
			state_vurl = Error_vurl;	// Stay in state Error.
			violated = present;
			event.vurl = present;
			timer_vurl = 0;
		} else {
			// In an undefined state.
			//printf("!! vurl: In an undefined state (%d)\n", state_vurl);
		}
		
		
		// elt(shared Signal AS, shared Signal AP, shared Signal AR, shared Signal VS, shared Signal VP);
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		* Monitor for Endless Loop Tachycardia (ELT)
		* ------------------------------------------
		* This component monitors the existence of endless loop tachycardia.
		*
		* Inputs: AS, AP, AR, VS, VP.
		* Outputs: none.
		* Side-effects: log.
		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		
		//printf("elt\n");
		
		if (state_elt == Init_elt) {
			if (AS == present) {
				state_elt = AS_elt;		// Go to state AS.
			} else if ((AP == present) || (AR == present)) {
				state_elt = Error_elt;	// Go to state Error.
			} else if (VP == present) {
				state_elt = VP_elt;		// Go to state VP.
			} else {
				// Do nothing.
			}
		} else if (state_elt == AS_elt) {
			if ((AS == present) || (AP == present) || (AR == present) || (VS == present)) {
				state_elt = Error_elt;	// Go to state Error.
			} else if (VP == present) {
				state_elt = VP_elt;		// Go to state VP.
			} else {
				// Do nothing.
			}
		} else if (state_elt == VP_elt) {
			if ((VS == present) || (VP == present) || (AP == present) || (AR == present)) {
				state_elt = Error_elt;	// Go to state Error.
			} else if (AS == present) {
				state_elt = AS_elt;		// Go to state AS.
			} else {
				// Do nothing.
			}
		} else if (state_elt == Error_elt) {
			state_elt = Error_elt;		// Stay in state Error.
			violated = present;
			event.elt = present;
		} else {
			// In an undefined state.
			//printf("!! elt: In an undefined state (%d)\n", state_elt);
		}
		
		
		// Log the violations.
		if (violated == present) {
			//	event.timestamp = getTime();
			event.AP = AP;
			event.VP = VP;
			event.DDD = DDD;
			event.VDI = VDI;
			
			log.events[log.tail] = event;
			log.tail = (log.tail + 1) % log.size;
		}
		
		pause;
	}
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Communication
* -------------
* This component communicates the data log and pacemaker parameters
* to the outside world. Communication is asynchronous with two-way 
* handshaking. Performes Cyclic Redundancy Check using crc.c from
* the Malardalen WCET Benchmark.
*
* Inputs: rfIn, log.
* Outputs: rfOut.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

thread communication(input unsigned int rfIn, input unsigned int rfOut, shared Log log) {
	// Internal codes.
	enum Code {
		Nothing = 0,
		Acknowledge,
		Complete,
		Receive,
		Send
	};

	// Internal variables.
	unsigned int state_rf = 0;
	unsigned int subState = 0;
	unsigned int data = 0;

	Log logCopy;
	unsigned int i = 0;
	
	while (1) {
		//printf("communication\n");

		// Wait for a command.
	//	while (rfIn == Nothing);
		
		// Perform Cyclic Redundancy Check.
		// crc.c from the Malardalen WCET Benchmark.
		icrc(0, 40, (short)0, 1);
		
		// rfIn = [state_rf, subState, data];
		unsigned int state_rf = (rfIn >> 30);
		unsigned int subState = (rfIn >> 28) & 0x03;
		unsigned int data = (rfIn & 0x0FFF);
		
		if (state_rf == Receive) {
			// Acknowledge new parameter received.
			rfOut = Acknowledge;
			
			// Update the specified parameter.
			if (subState == 0) {
				parameters.baseRate = data;
			} else if (subState == 1) {
				parameters.operationalMode = data;
			} else if (subState == 2) {
				parameters.ekgSensitivity = data;
			} else if (subState == 3) {
				parameters.paceVoltage = data;
			} else if (subState == 4) {
				parameters.sensitivityThreshold = data;
			} else if (subState == 5) {
				parameters.maxRate = data;
			} else if (subState == 6) {
				parameters.minRate = data;
			} else if (subState == 7) {
				parameters.maxAttackSlope = data;
			} else if (subState == 8) {
				parameters.maxDecaySlope = data;
			} else {
				// Do nothing.
			}
		} else if (state_rf == Send) {
			if (i == 0) {
				// Copy log.
				logCopy = log;
			}
			
			// Send log.
			if (i < logCopy.size) {
				// Send each event.
				if (subState == 0) {
					rfOut = logCopy.events[i].AP;
				} else if (subState == 1) {
					rfOut = logCopy.events[i].VP;
				} else if (subState == 2) {
					rfOut = logCopy.events[i].DDD;
				} else if (subState == 3) {
					rfOut = logCopy.events[i].VDI;
				} else if (subState == 4) {
					rfOut = logCopy.events[i].lrl;
				} else if (subState == 5) {
					rfOut = logCopy.events[i].url;
				} else if (subState == 6) {
					rfOut = logCopy.events[i].pmt;
				} else if (subState == 7) {
					rfOut = logCopy.events[i].vurl;
				} else if (subState == 8) {
					rfOut = logCopy.events[i].elt;
				} else {
					i = i + 1;
				}
			} else {
				rfOut = Complete;
				i = 0;
			}
		} else {
			// Do nothing.
		}
		
		// Wait for the command to complete.
	//	while (rfIn != Nothing);
				
		pause;
	}
}


/* $Id: crc.c,v 1.2 2005/04/04 11:34:58 csg Exp $ */

//************************************************************************/
/*                                                                       */
/*   SNU-RT Benchmark Suite for Worst Case Timing Analysis               */
/*   =====================================================               */
/*                              Collected and Modified by S.-S. Lim      */
/*                                            sslim@archi.snu.ac.kr      */
/*                                         Real-Time Research Group      */
/*                                        Seoul National University      */
/*                                                                       */
/*                                                                       */
/*        < Features > - restrictions for our experimental environment   */
/*                                                                       */
/*          1. Completely structured.                                    */
/*               - There are no unconditional jumps.                     */
/*               - There are no exit from loop bodies.                   */
/*                 (There are no 'break' or 'return' in loop bodies)     */
/*          2. No 'switch' statements.                                   */
/*          3. No 'do..while' statements.                                */
/*          4. Expressions are restricted.                               */
/*               - There are no multiple expressions joined by 'or',     */
/*                'and' operations.                                      */
/*          5. No library calls.                                         */
/*               - All the functions needed are implemented in the       */
/*                 source file.                                          */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*  FILE: crc.c                                                          */
/*  SOURCE : Numerical Recipes in C - The Second Edition                 */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     A demonstration for CRC (Cyclic Redundancy Check) operation.      */
/*     The CRC is manipulated as two functions, icrc1 and icrc.          */
/*     icrc1 is for one character and icrc uses icrc1 for a string.      */
/*     The input string is stored in array lin[].                        */
/*     icrc is called two times, one for X-Modem string CRC and the      */
/*     other for X-Modem packet CRC.                                     */
/*                                                                       */
//************************************************************************/

void icrc(unsigned short crc, unsigned long len, short jinit, int jrev) {
	unsigned char lin[40] = "asdffeagewaHAFEFaeDsFEawFdsFaefaeerdjgp";
	unsigned short icrctb[40];
	unsigned char rchr[40];
	unsigned short tmp1;
	unsigned short tmp2;
	unsigned short j;
	unsigned short cword = crc;
	unsigned char it[16] = {0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};

	for (j = 0; j < len; j = j + 1) {
		unsigned char onech = (unsigned char)0;
		unsigned short ans=((j << 8) ^ onech << 8);
		
		unsigned short int i;
		for (i = 0; i < 8; i = i + 1) {
			if (ans & 0x8000) {
				ans = (ans << 1);
				ans = (ans ^ 4129);
			} else {
				ans = (ans << 1);
			}
		}
		icrctb[j] = ans;
		
		rchr[j]=(unsigned char)(it[j & 0xF] << 4 | it[j >> 4]);
	}
	
	if (jinit > -1) {
		cword = ((unsigned char) jinit) | (((unsigned char) jinit) << 8);
	} else if (jrev < 0) {
		cword = rchr[((unsigned char)((cword) >> 8))] | rchr[((unsigned char)((cword) & 0xFF))] << 8;
	}

	for (j = 1; j <= len; j = j + 1) {
		if (jrev < 0) {
			tmp1 = rchr[lin[j]] ^ ((unsigned char)((cword) >> 8));
		} else {
			tmp1 = lin[j] ^ ((unsigned char)((cword) >> 8));
		}
		cword = icrctb[tmp1] ^ ((unsigned char)((cword) & 0xFF)) << 8;
	}
	if (jrev > -1) {
		tmp2 = cword;
	} else {
		tmp2 = rchr[((unsigned char)((cword) >> 8))] | rchr[((unsigned char)((cword) & 0xFF))] << 8;
	}
	
//	return tmp2;
}

