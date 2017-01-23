#include <ptarm_types.h>
#include <ptarm_mutex.h>
#include <ptarm_io.h>
#include <ptarm_timer.h>
#include <ptarm_hw_thread.h>
#include <ptarm_task.h>
#include <ptarm_scheduler.h>
#include <ptarm_foremc.h>


volatile const bool halt = true;
volatile const bool loopForever = true;

// Tasks (structure defined in ptarm_task.h).
volatile Task one	= {.name = "one",   .criticality = PTARM_TASK_LIFE, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500000000u}, .basePeriodsMin = 3, .lastRelease = 0, .earliestRelease = 0};
volatile Task two	= {.name = "two",   .criticality = PTARM_TASK_LIFE, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500000000u}, .basePeriodsMin = 5, .lastRelease = 0, .earliestRelease = 0};
volatile Task three	= {.name = "three", .criticality = PTARM_TASK_LIFE, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500000000u}, .basePeriodsMin = 3, .lastRelease = 0, .earliestRelease = 0};
volatile Task four	= {.name = "four",  .criticality = PTARM_TASK_LIFE, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500000000u}, .basePeriodsMin = 3, .lastRelease = 0, .earliestRelease = 0};

// Global scheduling information (structure defined in ptarm_scheduler.h).
volatile Task *priorityQueueNonCritical[20] = {NULL};
volatile Task *priorityQueueMission[20] = {NULL};
volatile Task *priorityQueueLife[20] = {NULL};
volatile GlobalScheduler globalScheduler =	{
										.isInitialised = false,
										.basePeriodDuration = {.msb = 0, .lsb = 1500000000u},
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
		case (0):;	// Hardware thread 0.

					safe_printf("Dynamic scheduling example.\n\n");

					// Create a static schedule for hardware thread 0.
					// [one -> two]
					ptarmCreateTask(&one, &&one, &localScheduler);
					ptarmCreateTask(&two, &&two, &localScheduler);
					staticSchedule[0] = &one;
					staticSchedule[1] = &two;

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
					// [three -> four]
					ptarmCreateTask(&three, &&three, &localScheduler);
					ptarmCreateTask(&four, &&four, &localScheduler);
					staticSchedule[0] = &three;
					staticSchedule[1] = &four;

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

					staticSchedule[0] = NULL;

					localScheduler.basePeriodStartOverhead.msb = 0;
					localScheduler.basePeriodStartOverhead.lsb = 10000000;	// 0.1s
					localScheduler.basePeriodEndOverhead.msb = 0;
					localScheduler.basePeriodEndOverhead.lsb = 10000000;	// 0.1s
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);

					globalScheduler.localScheduler2 = &localScheduler;
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler2);
					break;

		case (3):	// Hardware thread 3.

					staticSchedule[0] = NULL;
			
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
		printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Preempted "); printf(localScheduler.currentTask->name); printf(".\n");
		PTARM_MUTEX_UNLOCK();

		localScheduler.currentTask->state = PTARM_TASK_PREEMPTED;
		localScheduler.currentTask->sp = localScheduler.preemptedSp;
		localScheduler.currentTask->spsr = localScheduler.preemptedSpsr;
	} else {
		// A null task is only possible when the scheduler is preempted during the
		// dynamic scheduling phase.
	
		// "Preempted scheduler x."
		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Preempted "); printf(localScheduler.name); printf(".\n");
		PTARM_MUTEX_UNLOCK();
	}

	// If the preemption occured during the dynamic scheduling phase, then we know
	// that the base period has ended.
	if (localScheduler.phase == PTARM_SCHEDULER_DYNAMIC) {
		// Prepare to resume the static scheduling phase.

		// Return back to the release phase.
		localScheduler.phase = PTARM_SCHEDULER_RELEASE;

		if (localScheduler.hwThreadId == 0) {
		
			// Reset the dynamic scheduling lists.
			PTARM_SCHEDULER_DYNAMIC_LIST_RESET(globalScheduler);

			// "Base period xxx ended."
			PTARM_MUTEX_LOCK();
			printf("Base period "); printf(utoa(localScheduler.basePeriodCounter)); printf(" ended.\n");
			PTARM_MUTEX_UNLOCK();
		}

		// Update the timestamp of the start of the next base period.
		localScheduler.basePeriodCounter++;
		PTARM_ADD(localScheduler.basePeriodStart, localScheduler.basePeriodStart, globalScheduler.basePeriodDuration);

		// Wait until the next base period starts. This synchronises the start of the base period with other hardware threads to minimise jitter.
		PTARM_DELAY(localScheduler.basePeriodStart);
	} else {
	
		// Add the task to the dynamic scheduling list.
		PTARM_MUTEX_LOCK();
		// "Adding xxx to dynamic queue."
		printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Queuing "); printf(localScheduler.currentTask->name); printf(".\n");
		PTARM_SCHEDULER_DYNAMIC_LIST_PUSH_LIFE_MISSION(globalScheduler, localScheduler.currentTask);
		PTARM_MUTEX_UNLOCK();
	}

	PTARM_GOTO(localScheduler);
}


// Local scheduler for each hardware thread.
// It always begins each base period with the static scheduling phase, followed by the dynamic scheduling phase.
localScheduler: {
	/*
	// "Scheduler = xxx, Current Task = xxx."
	PTARM_MUTEX_LOCK();
	printf(itoa(localScheduler.hwThreadId)); printf(":Scheduler = "); printf(localScheduler.name); printf(", Current task = "); printf(localScheduler.currentTask->name); printf(".\n");
	PTARM_MUTEX_UNLOCK();
	*/

	switch (localScheduler.phase) {
		case (PTARM_SCHEDULER_RELEASE):
			
			// Go through the static schedule and release any eligible tasks.
			for (localScheduler.nextStaticTask = localScheduler.staticSchedule; (*localScheduler.nextStaticTask) != NULL; localScheduler.nextStaticTask++) {
				
				volatile Task *currentTask = *localScheduler.nextStaticTask;
				
				// If the task is paused, check if it can be released for execution (i.e., the minimum number of base periods has elapsed).
				if (currentTask->state == PTARM_TASK_PAUSED && (currentTask->earliestRelease <= localScheduler.basePeriodCounter)) {
					
					// "Releasing xxx."
					PTARM_MUTEX_LOCK();
					printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Releasing "); printf(currentTask->name); printf(".\n");
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
			// Start time = basePeriodStartOverhead + basePeriodStart.
			localScheduler.phase = PTARM_SCHEDULER_STATIC;
			PTARM_ADD(localScheduler.basePeriodStartAfterOverhead, localScheduler.basePeriodStartOverhead, localScheduler.basePeriodStart);
			PTARM_DELAY(localScheduler.basePeriodStartAfterOverhead);
	
		case (PTARM_SCHEDULER_STATIC):;
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
					
					// "Executing xxx."
					PTARM_MUTEX_LOCK();
					printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Executing "); printf(localScheduler.currentTask->name); printf(".\n");
					PTARM_MUTEX_UNLOCK();

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
				
				// "Dynamic phase."
				PTARM_MUTEX_LOCK();
				printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Dynamic phase.\n");
				PTARM_MUTEX_UNLOCK();

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

			// Check if there is enough time to execute a task.
			// elapsedTime = currentTime - basePeriodStart.
			PTARM_TIME_GET(localScheduler.currentTime);
			PTARM_MINUS(localScheduler.elapsedTime, localScheduler.currentTime, localScheduler.basePeriodStart);

			if ((localScheduler.basePeriodMinusEndingOverhead.msb > localScheduler.elapsedTime.msb) ||
			   ((localScheduler.basePeriodMinusEndingOverhead.msb == localScheduler.elapsedTime.msb) && (localScheduler.basePeriodMinusEndingOverhead.lsb >= localScheduler.elapsedTime.lsb))) {
				// Enough time to execute a task. Find a task to execute.

				// Find a task from the dynamic scheduling lists to execute.
				PTARM_MUTEX_LOCK();
				PTARM_SCHEDULER_DYNAMIC_LIST_POP(globalScheduler, localScheduler.currentTask);
				PTARM_MUTEX_UNLOCK();

				// Check if it is an available task.
				if (localScheduler.currentTask != NULL) {

					// "Picking xxx."
					PTARM_MUTEX_LOCK();
					printf(" "); printf(utoa(localScheduler.hwThreadId)); printf(":Picking "); printf(localScheduler.currentTask->name); printf(".\n");
					PTARM_MUTEX_UNLOCK();

					// Set the task's local scheduler to this dynamic local scheduler.
					PTARM_TASK_SET_SCHEDULER(localScheduler.currentTask, &localScheduler);

					// The task is available, so context switch to it.
					PTARM_TASK_RESTORE_CONTEXT(localScheduler.currentTask);
				}
			}

			// Wait for a task to become available, or until the base period ends.
			goto localScheduler;
			break;

		default:;
			// Undefined scheduling phase.
			PTARM_MUTEX_LOCK();
			printf("!!"); printf(utoa(localScheduler.hwThreadId)); printf(" Scheduling error. Phase = "); printf(utoa(localScheduler.phase)); printf(".\n");
			PTARM_MUTEX_UNLOCK();

			while (halt);
			break;
	}
}

// The tasks. Note that they are defined within the main function.

one: {
	while (loopForever) {
		int i;
		for (i = 0; i < 2000000u; i++);

		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(one.localScheduler->hwThreadId)); printf(":one pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(one, 1);
	}
}

two: {
	while (loopForever) {
		int i;
		for (i = 0; i < 2000000u; i++);

		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(two.localScheduler->hwThreadId)); printf(":two pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(two, 1);
	}
}

three: {
	while (loopForever) {
		int i;
		for (i = 0; i < 2000000u; i++);

		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(three.localScheduler->hwThreadId)); printf(":three pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(three, 1);
	}
}

four: {
	while (loopForever) {
		int i;
		for (i = 0; i < 2000000u; i++);

		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(four.localScheduler->hwThreadId)); printf(":four pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(four, 1);
	}
}

	return 0;
}

