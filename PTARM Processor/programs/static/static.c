#include <ptarm_types.h>
#include <ptarm_mutex.h>
#include <ptarm_io.h>
#include <ptarm_timer.h>
#include <ptarm_hw_thread.h>
#include <ptarm_task.h>
#include <ptarm_scheduler.h>
#include <ptarm_foremc.h>


volatile const bool halt = true;
volatile const bool foreverTrue = true;

// Tasks (structure defined in ptarm_task.h).
Task one	= {.name = "one",   .criticality = PTARM_TASK_LIFE, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 1000000000u}, .basePeriodsMin = 3, .lastRelease = 0, .earliestRelease = 0};
Task two	= {.name = "two",   .criticality = PTARM_TASK_LIFE, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 1000000000u}, .basePeriodsMin = 5, .lastRelease = 0, .earliestRelease = 0};
Task three	= {.name = "three", .criticality = PTARM_TASK_LIFE, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 1000000000u}, .basePeriodsMin = 3, .lastRelease = 0, .earliestRelease = 0};
Task four	= {.name = "four",  .criticality = PTARM_TASK_LIFE, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 1000000000u}, .basePeriodsMin = 3, .lastRelease = 0, .earliestRelease = 0};

// Global scheduling information (structure defined in ptarm_scheduler.h).
volatile Task *priorityQueueNonCritical[5] = {NULL};
volatile Task *priorityQueueMission[5] = {NULL};
volatile Task *priorityQueueLife[5] = {NULL};
GlobalScheduler globalScheduler =	{
										.isInitialised = false,
										.basePeriodDuration = {.msb = 0, .lsb = 3000000000u},
										.priorityQueueNonCritical = priorityQueueNonCritical,
										.priorityQueueMission = priorityQueueMission,
										.priorityQueueLife = priorityQueueLife,
										.counterNonCritical = -1,
										.counterMission = -1,
										.counterLife = -1
									};

// Main entry point of the program that is executed by all hardware threads.
int main(void) {
	// Create a local scheduler that uses the hardware thread's stack.
	ptarmCreateLocalScheduler(localScheduler, &&localScheduler);

	// Each hardware thread performs some type of start up work.
	switch (localScheduler.hwThreadId) {
		case (0):	// Hardware thread 0.

					safe_printf("Static scheduling example.\n\n");

					// Create a static schedule for hardware thread 0.
					// [one]
					ptarmCreateTask(&one, &&one, &localScheduler);
					staticSchedule[0] = &one;

					// Calculate the duration of the base period that can be used to execute tasks.
					localScheduler.basePeriodStartOverhead.msb = 0;
					localScheduler.basePeriodStartOverhead.lsb = 10000000;	// 0.1s
					localScheduler.basePeriodEndOverhead.msb = 0;
					localScheduler.basePeriodEndOverhead.lsb = 10000000;	// 0.1s
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);

					globalScheduler.localScheduler0 = &localScheduler;					// Set the global reference to the local scheduler.
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler0);	// Register the EOE handler.

					PTARM_TIME_GET(globalScheduler.basePeriodFirstStart);				// Save the time stamp of the first base period.
					globalScheduler.isInitialised = true;								// Initialisation complete.
					break;

		case (1):	// Hardware thread 1.

					// Create a static schedule for hardware thread 1.
					// [two]
					ptarmCreateTask(&two, &&two, &localScheduler);
					staticSchedule[0] = &two;

					// Calculate the duration of the base period that can be used to execute tasks.
					localScheduler.basePeriodStartOverhead.msb = 0;
					localScheduler.basePeriodStartOverhead.lsb = 10000000;	// 0.1s
					localScheduler.basePeriodEndOverhead.msb = 0;
					localScheduler.basePeriodEndOverhead.lsb = 10000000;	// 0.1s
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);

					globalScheduler.localScheduler1 = &localScheduler;					// Set the global reference to the local scheduler.
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler1);	// Register the EOE handler.
					break;

		case (2):	// Hardware thread 2.

					// Create a static schedule for hardware thread 2.
					// [three]
					ptarmCreateTask(&three, &&three, &localScheduler);
					staticSchedule[0] = &three;

					localScheduler.basePeriodStartOverhead.msb = 0;
					localScheduler.basePeriodStartOverhead.lsb = 10000000;	// 0.1s
					localScheduler.basePeriodEndOverhead.msb = 0;
					localScheduler.basePeriodEndOverhead.lsb = 10000000;	// 0.1s
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);

					globalScheduler.localScheduler2 = &localScheduler;
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler2);
					break;

		case (3):	// Hardware thread 3.

					// Create a static schedule for hardware thread 3.
					// [four]
					ptarmCreateTask(&four, &&four, &localScheduler);
					staticSchedule[0] = &four;
			
					// Calculate the duration of the base period that can be used to execute tasks.
					localScheduler.basePeriodStartOverhead.msb = 0;
					localScheduler.basePeriodStartOverhead.lsb = 10000000;	// 0.1s
					localScheduler.basePeriodEndOverhead.msb = 0;
					localScheduler.basePeriodEndOverhead.lsb = 10000000;	// 0.1s
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);

					globalScheduler.localScheduler3 = &localScheduler;
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler3);
					break;

		default:	// Unknown hardware thread ID.

					PTARM_MUTEX_LOCK();
					printf("!! Initialisation error: Unknown hwThreadId = "); printf(utoa(localScheduler.hwThreadId)); printf("\n");
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
	if (localScheduler.currentTask != NULL) {

		// "Preempted xxx."
		PTARM_MUTEX_LOCK();
		printf("  Preempted "); printf(localScheduler.currentTask->name); printf(".\n");
		PTARM_MUTEX_UNLOCK();

		localScheduler.currentTask->state = PTARM_TASK_PREEMPTED;
		localScheduler.currentTask->sp = localScheduler.preemptedSp;
		localScheduler.currentTask->spsr = localScheduler.preemptedSpsr;
	} else {
		// A null task is only possible when the scheduler is preempted during the
		// dynamic scheduling phase.

		// "Preempted scheduler x."
	//	PTARM_MUTEX_LOCK();
	//	printf("  Preempted scheduler "); printf(utoa(localScheduler.hwThreadId)); printf(".\n");
	//	PTARM_MUTEX_UNLOCK();
	}

	// If the preemption occured during the dynamic scheduling phase, then we know
	// that the base period has ended.
	if (localScheduler.phase == PTARM_SCHEDULER_DYNAMIC) {
		// Prepare to resume the static scheduling phase.

		// Return back to the release phase.
		localScheduler.phase = PTARM_SCHEDULER_RELEASE;

		if (localScheduler.hwThreadId == 0) {
			
			// "Base period xxx ended."
			PTARM_MUTEX_LOCK();
			printf("Base period "); printf(utoa(localScheduler.basePeriodCounter)); printf(" ended.\n");
			PTARM_MUTEX_UNLOCK();
		}

		// Update the timestamp of the start of the next base period.
		localScheduler.basePeriodCounter++;
		PTARM_ADD(localScheduler.basePeriodStart, localScheduler.basePeriodStart, globalScheduler.basePeriodDuration);

		// Wait until the base period ends. This synchronises the start of the base period with other hardware threads to minimise jitter.
		PTARM_DELAY(localScheduler.basePeriodStart);
	}

	PTARM_GOTO(localScheduler);
}


// Local scheduler for each hardware thread.
// It always begins each base period with the static scheduling phase, followed by the dynamic scheduling phase.
localScheduler: {
	/*
	// "Scheduler = xxx, Current Task = xxx."
	PTARM_MUTEX_LOCK();
	printf("Scheduler = "); printf(localScheduler.name); printf(", Current task = "); printf(localScheduler.currentTask->name); printf(".\n");
	PTARM_MUTEX_UNLOCK();
	*/

	switch (localScheduler.phase) {
		case (PTARM_SCHEDULER_RELEASE):
		
			// Go through the static schedule and release any eligible tasks.
			for (localScheduler.nextStaticTask = localScheduler.staticSchedule; (*localScheduler.nextStaticTask) != NULL; localScheduler.nextStaticTask++) {
				
				volatile Task *currentTask = *localScheduler.nextStaticTask;
				
				// If the task is paused, check if it can be released for execution (i.e., the minimum number of base periods has elapsed).
				if (currentTask->state == PTARM_TASK_PAUSED && (currentTask->earliestRelease <= localScheduler.basePeriodCounter)) {
					
					// "Released xxx."
					PTARM_MUTEX_LOCK();
					printf("  Releasing "); printf(currentTask->name); printf(".\n");
					PTARM_MUTEX_UNLOCK();
					
					// The minimum number of base periods has elapsed, so release the task.
					currentTask->state = PTARM_TASK_RELEASED;
					
					// Update its last released timestamp.
					currentTask->lastRelease = localScheduler.basePeriodCounter;
					
					// Update its next earliest release timestamp.
					currentTask->earliestRelease = (localScheduler.basePeriodCounter + currentTask->basePeriodsMin);
				}
			}
		
			// Reset the static schedule (to the first task).
			localScheduler.nextStaticTask = localScheduler.staticSchedule;
			
			// Continue through to the next case statement for the static scheduling phase.
			localScheduler.phase = PTARM_SCHEDULER_STATIC;
			
			PTARM_ADD(localScheduler.basePeriodStartAfterOverhead, localScheduler.basePeriodStartOverhead, localScheduler.basePeriodStart);
			PTARM_DELAY(localScheduler.basePeriodStartAfterOverhead);
	
		case (PTARM_SCHEDULER_STATIC):
			// Static scheduling phase.
			// Schedule all the tasks in its static schedule before going into the dynamic scheduling phase.

			// Get the next statically scheduled task.
			localScheduler.currentTask = *localScheduler.nextStaticTask;

			// Check if we have reached the end of the static schedule.
			if (localScheduler.currentTask != NULL) {
				// The end of the static schedule has not been reached.

				// Update the next statically scheduled task.
				localScheduler.nextStaticTask++;

				// Execute the task if it has been preempted or released.
				if (localScheduler.currentTask->state == PTARM_TASK_PREEMPTED || localScheduler.currentTask->state == PTARM_TASK_RELEASED) {

					// Set the task's deadline in this base period to be the end of its statically allocated execution time.
					PTARM_TIME_GET(localScheduler.currentTime);
					PTARM_EOE_ENABLE(localScheduler.currentTask->allocatedTime, localScheduler.currentTime);

					// (Re)set the task's local scheduler to this static local scheduler.
					PTARM_TASK_SET_SCHEDULER(localScheduler.currentTask, &localScheduler);

					// Context switch to the current task.
					PTARM_TASK_RESTORE_CONTEXT(localScheduler.currentTask);
				} else {
					// Pick the next task to execute instead.
					goto localScheduler;
				}
			} else {
				// The end of the static schedule has been reached. Prepare for the dynamic scheduling phase.

				// We are now entering the dynamic scheduling phase.
				localScheduler.phase = PTARM_SCHEDULER_DYNAMIC;

				// Continue through to the next case statement for the dynamic scheduling phase.
			}
			
		case (PTARM_SCHEDULER_DYNAMIC):;
			// Dynamic scheduling phase.
			
			// (Re)set the current task in case a timing exception occurs when the scheduler is executing.
			localScheduler.currentTask = NULL;

			// Set the dynamic execution deadline to be the end of the base period, minus the expected scheduling overhead.
			PTARM_EOE_ENABLE(localScheduler.basePeriodMinusEndingOverhead, localScheduler.basePeriodStart);

			// Wait for the base period to end.
			goto localScheduler;
			break;

		default:
			// Undefined scheduling phase.

			safe_printf("!! Scheduling error: Oops!\n");
			while (halt);
			break;
	}
}

// The tasks.
// Note that they are defined within the main function.

one: {
	while (foreverTrue) {
		int i;
		for (i = 0; i < 2500000u; i++);

		PTARM_MUTEX_LOCK();
		printf("  one pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(one, 1);
	}
}

two: {
	while (foreverTrue) {
		int i;
		for (i = 0; i < 3000000u; i++);

		PTARM_MUTEX_LOCK();
		printf("  two pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(two, 1);
	}
}

three: {
	while (foreverTrue) {
		int i;
		for (i = 0; i < 2500000u; i++);

		PTARM_MUTEX_LOCK();
		printf("  three pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(three, 1);
	}
}

four: {
	while (foreverTrue) {
		int i;
		for (i = 0; i < 2500000u; i++);

		PTARM_MUTEX_LOCK();
		printf("  four pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(four, 1);
	}
}

	return 0;
}

