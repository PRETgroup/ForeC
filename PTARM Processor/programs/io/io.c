#include <ptarm_types.h>
#include <ptarm_mutex.h>
#include <ptarm_io.h>
#include <ptarm_timer.h>
#include <ptarm_hw_thread.h>
#include <ptarm_task.h>
#include <ptarm_scheduler.h>

// Null values.
Timer64Bit nullTime = {.msb = NULL, .lsb = NULL};

volatile const bool halt = true;
volatile const bool loopForever = true;

// Tasks (structure defined in ptarm_task.h).
Task one	= {.name = "one"};
Task two	= {.name = "two"};
Task three	= {.name = "three"};
Task four	= {.name = "four"};

// Global scheduling information (structure defined in ptarm_scheduler.h).
GlobalScheduler globalScheduler = {.isInitialised = false};


// Main entry point of the program that is executed by all hardware threads.
int main(void) {
	// Create a local scheduler that uses the hardware thread's stack.
	ptarmCreateLocalScheduler(localScheduler, &&localScheduler);

	// Each hardware thread performs some type of start up work.
	switch (localScheduler.hwThreadId) {
		case (0):	// Hardware thread 0.

					safe_printf("Input/Output example.\n\n");
			
					ptarmCreateTask(&one, &&one, &localScheduler);						// Create task one.
					localScheduler.currentTask = &one;									// Assign a task to execute.
					globalScheduler.localScheduler0 = &localScheduler;					// Set the global reference to the local scheduler
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler0);	// Register the EOE handler.

					globalScheduler.isInitialised = true;								// Initialisation complete.
					break;

		case (1):	// Hardware thread 1.

					ptarmCreateTask(&two, &&two, &localScheduler);						// Create task two.
					localScheduler.currentTask = &two;									// Assign a task to execute.
					globalScheduler.localScheduler1 = &localScheduler;					// Set the global reference to the local scheduler
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler1);	// Register the EOE handler.
					break;

		case (2):	// Hardware thread 2.

					ptarmCreateTask(&three, &&three, &localScheduler);
					localScheduler.currentTask = &three;
					globalScheduler.localScheduler2 = &localScheduler;
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler2);
					break;

		case (3):	// Hardware thread 3.

					ptarmCreateTask(&four, &&four, &localScheduler);
					localScheduler.currentTask = &four;
					globalScheduler.localScheduler3 = &localScheduler;
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler3);
					break;

		default:	// Unknown hardware thread ID.

					PTARM_MUTEX_LOCK();
					printf("!! Initialisation error: Unknown hwThreadId = ");
					printf(utoa(localScheduler.hwThreadId));
					printf("\n");
					PTARM_MUTEX_UNLOCK();
					while (halt);
					break;
	}

	// All hardware threads execute this.
	while(globalScheduler.isInitialised == false);
	localScheduler.basePeriodStart = globalScheduler.basePeriodFirstStart;
	PTARM_GOTO(localScheduler);


// The registered EOE handler of each hardware thread.
// An exception can occur during the execution of any task (or scheduler). When
// an exception does occur, the registered EOE handler is called. We cannot immediately
// query what task was preempted because that will cause some registers to
// be overwritten. Hence, we save the task's context anonymously before querying
// what task was preempted so that the saved context can be assigned to the correct task.

// For hardware thread 0.
eoeHandler0: {
	// Save the context of the preempted (anonymous) task and then restore the scheduler's context
	// to query which task was preempted.
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler0);
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler0);
	PTARM_GOTO(eoeHandler);
}

// For hardware thread 1.
eoeHandler1: {
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler1);
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler1);
	PTARM_GOTO(eoeHandler);
}

// For hardware thread 2.
eoeHandler2: {
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler2);
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler2);
	PTARM_GOTO(eoeHandler);
}

// For hardware thread 3.
eoeHandler3: {
	PTARM_EOE_TASK_SAVE_CONTEXT(globalScheduler.localScheduler3);
	PTARM_SCHEDULER_RESTORE_CONTEXT(globalScheduler.localScheduler3);
	PTARM_GOTO(eoeHandler);
}

eoeHandler: {
	// Assign the saved context to the preempted task.
	localScheduler.currentTask->state = PTARM_TASK_PREEMPTED;
	localScheduler.currentTask->sp = localScheduler.preemptedSp;
	localScheduler.currentTask->spsr = localScheduler.preemptedSpsr;

	PTARM_GOTO(localScheduler);
}


// Local scheduler for each hardware thread.
localScheduler: {
	Timer64Bit delay = {.msb = 0, .lsb = 0};
	switch (localScheduler.hwThreadId) {
		case (0):	delay.lsb = 1000000000u;	// 1s.
					break;

		case (1):	delay.lsb = 2000000000u;	// 2s.
					break;

		case (2):	delay.lsb = 3000000000u;	// 3s.
					break;

		case (3):	delay.lsb = 4000000000u;	// 4s.
					break;

		default:	PTARM_MUTEX_LOCK();
					printf("!! Scheduling error: Unknown hardware thread.\n  ");
					// "Task = xxx, SP = xxx, PC = xxx, hwThreadId = xxx."
					printf("Task = "); printf(localScheduler.name);
					printf(", SP = "); printf(hex((unsigned int)localScheduler.sp));
					printf(", PC = "); printf(hex((unsigned int)localScheduler.pc));
					printf(", hwThreadId = "); printf(utoa(localScheduler.hwThreadId));
					printf("\n");
					PTARM_MUTEX_UNLOCK();
					while (halt);
					break;
	}

	PTARM_TIME_GET(localScheduler.currentTime);
	PTARM_EOE_ENABLE(delay, localScheduler.currentTime);
	PTARM_TASK_RESTORE_CONTEXT(localScheduler.currentTask);

	safe_printf("!! Scheduling error: Oops!\n");
}

// The tasks.
// Note that they are defined within the main function.
one: {
	while (loopForever) {
		int i = 1;
		if (i) {
			volatile unsigned int keys = 0;
			PTARM_READ_KEYS(keys);
			ptarmLedGreenOutput(keys);
			
			volatile unsigned int switches = 0;
			PTARM_READ_SWITCHES(switches);
			ptarmLedRedOutput(switches);
		} else {
			printf("task one\n");
		}
	}
}

two: {
	while (loopForever) {
		int i = 0;
		if (i) {
			printf("task two\n");
		}
	}
}

three: {
	ptarmSevenSegOutput(0, 0x40);
	ptarmSevenSegChar(1, 'A');
	ptarmSevenSegChar(2, 'B');
	ptarmSevenSegChar(3, 'C');
	ptarmSevenSegChar(4, 'D');
	ptarmSevenSegChar(5, 'E');
	ptarmSevenSegChar(6, 'F');
	
	unsigned int i = 0;
	while (loopForever) {
		ptarmSevenSegChar(7, utoa(i)[0]);
		i++;
		i %= 9;
		
		int j;
		for (j = 0; j < 100000; j++);
	}
}

four: {
	ptarmLcdInit();
	printfLcd("Hello World!\nPTARM\n");

	volatile unsigned int keys, lastKeys;
	PTARM_READ_KEYS(keys);
	lastKeys = keys;
	bool updated = false;
	
	while (loopForever) {
		PTARM_READ_KEYS(keys);

		if (keys != lastKeys) {
			if (keys != KEY_MASK) {
				if (!updated) {
					printfLcd(" A key is being    pressed!");
					updated = true;
				}
			} else {
				printfLcd("  Press a key!");
				updated = false;
			}
			lastKeys = keys;
		}
	}
}

	return 0;
}
