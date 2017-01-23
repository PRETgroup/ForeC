#include <ptarm_types.h>
#include <ptarm_hw_thread.h>
#include <ptarm_io.h>
#include <ptarm_foremc.h>
#include <ptarm_timer.h>
#include <ptarm_task.h>
#include <ptarm_scheduler.h>
#include <ptarm_mutex.h>


volatile const bool halt = true;
volatile const bool loopForever = true;


// Tasks (structure defined in ptarm_task.h).
// Life critical
volatile Task l1 = {.name = "l1", .receiveBuffers = { NULL }, .criticality = PTARM_TASK_LIFE, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500*MILLI_SECOND}, .basePeriodsMin = 4, .lastRelease = 0, .earliestRelease = 0};
volatile Task l2 = {.name = "l2", .receiveBuffers = { NULL }, .criticality = PTARM_TASK_LIFE, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500*MILLI_SECOND}, .basePeriodsMin = 4, .lastRelease = 0, .earliestRelease = 0};
volatile Task l3 = {.name = "l3", .receiveBuffers = { NULL }, .criticality = PTARM_TASK_LIFE, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500*MILLI_SECOND}, .basePeriodsMin = 4, .lastRelease = 0, .earliestRelease = 0};
volatile Task l4 = {.name = "l4", .receiveBuffers = { NULL }, .criticality = PTARM_TASK_LIFE, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500*MILLI_SECOND}, .basePeriodsMin = 4, .lastRelease = 0, .earliestRelease = 0};

// Mission critical
volatile Task m1 = {.name = "m1", .receiveBuffers = { NULL }, .criticality = PTARM_TASK_MISSION, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500*MILLI_SECOND}, .basePeriodsMin = 8, .lastRelease = 0, .earliestRelease = 0};
volatile Task m2 = {.name = "m2", .receiveBuffers = { NULL }, .criticality = PTARM_TASK_MISSION, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500*MILLI_SECOND}, .basePeriodsMin = 7, .lastRelease = 0, .earliestRelease = 0};
volatile Task m3 = {.name = "m3", .receiveBuffers = { NULL }, .criticality = PTARM_TASK_MISSION, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500*MILLI_SECOND}, .basePeriodsMin = 8, .lastRelease = 0, .earliestRelease = 0};
volatile Task m4 = {.name = "m4", .receiveBuffers = { NULL }, .criticality = PTARM_TASK_MISSION, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500*MILLI_SECOND}, .basePeriodsMin = 8, .lastRelease = 0, .earliestRelease = 0};

// Non-critical
volatile Task n1 = {.name = "n1", .receiveBuffers = { NULL }, .criticality = PTARM_TASK_NONCRITICAL, .state = PTARM_TASK_PAUSED, .basePeriodsMin = 8, .lastRelease = 0, .earliestRelease = 0};
volatile Task n2 = {.name = "n2", .receiveBuffers = { NULL }, .criticality = PTARM_TASK_NONCRITICAL, .state = PTARM_TASK_PAUSED, .basePeriodsMin = 8, .lastRelease = 0, .earliestRelease = 0};
volatile Task n3 = {.name = "n3", .receiveBuffers = { NULL }, .criticality = PTARM_TASK_NONCRITICAL, .state = PTARM_TASK_PAUSED, .basePeriodsMin = 8, .lastRelease = 0, .earliestRelease = 0};
volatile Task n4 = {.name = "n4", .receiveBuffers = { NULL }, .criticality = PTARM_TASK_NONCRITICAL, .state = PTARM_TASK_PAUSED, .basePeriodsMin = 8, .lastRelease = 0, .earliestRelease = 0};


// Buffers for mixed-criticality task communication (structure defined in ptarm_foremc.h).
volatile struct _ForeMc_100int bufferOne;


// Global scheduling information (structure defined in ptarm_scheduler.h).
volatile Task *priorityQueueNonCritical[20] = {NULL};
volatile Task *priorityQueueMission[20] = {NULL};
volatile Task *priorityQueueLife[20] = {NULL};
volatile GlobalScheduler globalScheduler =	{
												.isInitialised = false,
												.basePeriodDuration = {.msb = 0, .lsb = 3*SECOND},
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

					safe_printf("ForeMC example.\n\n");

					// Create the non-critical tasks.
					ptarmCreateTask(&n1, &&n1, NULL);
					ptarmCreateTask(&n2, &&n2, NULL);
					ptarmCreateTask(&n3, &&n3, NULL);
					ptarmCreateTask(&n4, &&n4, NULL);

					// Create a static schedule for hardware thread 0.
					// [m1 -> l1]
					ptarmCreateTask(&m1, &&m1, &localScheduler);
					ptarmCreateTask(&l1, &&l1, &localScheduler);
					staticSchedule[0] = &m1;
					staticSchedule[1] = &l1;

					// Calculate the duration of the base period that can be used to execute tasks.
					localScheduler.basePeriodStartOverhead.msb = 0;
					localScheduler.basePeriodStartOverhead.lsb = 100*MILLI_SECOND;	// 0.1s
					localScheduler.basePeriodEndOverhead.msb = 0;
					localScheduler.basePeriodEndOverhead.lsb = 100*MILLI_SECOND;	// 0.1s
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);

					globalScheduler.localScheduler0 = &localScheduler;					// Set the global reference to the local scheduler.
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler0);	// Register the EOE handler.

					PTARM_TIME_GET(globalScheduler.basePeriodFirstStart);				// Save the time stamp of the first base period.
					globalScheduler.isInitialised = true;								// Initialisation complete.
					break;

		case (1):	// Hardware thread 1.

					// Create a static schedule for hardware thread 1.
					// [m2 -> l2]
					ptarmCreateTask(&m2, &&m2, &localScheduler);
					ptarmCreateTask(&l2, &&l2, &localScheduler);
					staticSchedule[0] = &m2;
					staticSchedule[1] = &l2;
			
					// Associate tasks with receive buffers.
					m2.receiveBuffers[0] = &bufferOne;

					// Calculate the duration of the base period that can be used to execute tasks.
					localScheduler.basePeriodStartOverhead.msb = 0;
					localScheduler.basePeriodStartOverhead.lsb = 100*MILLI_SECOND;	// 0.1s
					localScheduler.basePeriodEndOverhead.msb = 0;
					localScheduler.basePeriodEndOverhead.lsb = 100*MILLI_SECOND;	// 0.1s
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);

					globalScheduler.localScheduler1 = &localScheduler;					// Set the global reference to the local scheduler.
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler1);	// Register the EOE handler.
					break;

		case (2):	// Hardware thread 2.

					ptarmCreateTask(&l3, &&l3, &localScheduler);
					ptarmCreateTask(&l4, &&l4, &localScheduler);
					staticSchedule[0] = &l3;
					staticSchedule[1] = &l4;

					localScheduler.basePeriodStartOverhead.msb = 0;
					localScheduler.basePeriodStartOverhead.lsb = 100*MILLI_SECOND;	// 0.1s
					localScheduler.basePeriodEndOverhead.msb = 0;
					localScheduler.basePeriodEndOverhead.lsb = 100*MILLI_SECOND;	// 0.1s
					PTARM_MINUS(localScheduler.basePeriodMinusEndingOverhead, globalScheduler.basePeriodDuration, localScheduler.basePeriodEndOverhead);

					globalScheduler.localScheduler2 = &localScheduler;
					PTARM_EOE_SET_HANDLER(localScheduler.hwThreadId, &&eoeHandler2);
					break;

		case (3):	// Hardware thread 3.

					ptarmCreateTask(&m3, &&m3, &localScheduler);
					ptarmCreateTask(&m4, &&m4, &localScheduler);
					staticSchedule[0] = &m3;
					staticSchedule[1] = &m4;

					localScheduler.basePeriodStartOverhead.msb = 0;
					localScheduler.basePeriodStartOverhead.lsb = 100*MILLI_SECOND;	// 0.1s
					localScheduler.basePeriodEndOverhead.msb = 0;
					localScheduler.basePeriodEndOverhead.lsb = 100*MILLI_SECOND;	// 0.1s
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
		
		PTARM_EOE_TASK_ASSIGN_CONTEXT(localScheduler);
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

		// Return back to the static scheduling phase.
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
	
		// Insert the task to the dynamic scheduling list.
		PTARM_MUTEX_LOCK();
		// "Queuing xxx."
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
		
			if (localScheduler.hwThreadId == 0) {
				// Go through the non-critical tasks and release eligible tasks.
				PTARM_SCHEDULER_DYNAMIC_LIST_RELEASE_NON_CRITICAL(globalScheduler, localScheduler, &n1);
				PTARM_SCHEDULER_DYNAMIC_LIST_RELEASE_NON_CRITICAL(globalScheduler, localScheduler, &n2);
				PTARM_SCHEDULER_DYNAMIC_LIST_RELEASE_NON_CRITICAL(globalScheduler, localScheduler, &n3);
				PTARM_SCHEDULER_DYNAMIC_LIST_RELEASE_NON_CRITICAL(globalScheduler, localScheduler, &n4);
			}
			
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

					// Release all the receive buffers associated with the task.
					volatile struct _ForeMc_100int *volatile *receiveBuffer;
					for (receiveBuffer = currentTask->receiveBuffers; *receiveBuffer != NULL; receiveBuffer++) {
						FOREMC_BUFFER_RELEASE(*receiveBuffer);
					}
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

// Life critical tasks
l1: {
	int j = 0;
	while (loopForever) {
		int i;
		for (i = 0; i < 2000000u; i++);
		
		j++;

		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(l1.localScheduler->hwThreadId)); printf(":l1 pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE_AND_BUFFER(l1, continuationId, bufferOne, j);
	}
}

l2: {
	while (loopForever) {
		int i;
		for (i = 0; i < 2000000u; i++);

		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(l2.localScheduler->hwThreadId)); printf(":l2 pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(l2, 1);
	}
}

l3: {
	while (loopForever) {
		int i;
		for (i = 0; i < 2000000u; i++);

		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(l3.localScheduler->hwThreadId)); printf(":l3 pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(l3, 1);
	}
}

l4: {
	while (loopForever) {
		int i;
		for (i = 0; i < 2000000u; i++);

		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(l4.localScheduler->hwThreadId)); printf(":l4 pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(l4, 1);
	}
}

// Mission critical
m1: {
	while (loopForever) {
		int i;
		for (i = 0; i < 2000000u; i++);
		
		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(m1.localScheduler->hwThreadId)); printf(":m1 pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(m1, 1);
	}
}
	
m2: {
	while (loopForever) {
		int index;
		for (index = 0; index < FOREMC_BUFFER_READ_COUNT(bufferOne); index++) {
			PTARM_MUTEX_LOCK();
			printf(utoa(FOREMC_BUFFER_READ_COUNT(bufferOne))); printf(","); printf(utoa(FOREMC_BUFFER_AT_INDEX(bufferOne, index))); printf("\n");
			PTARM_MUTEX_UNLOCK();
		}
		
		int i;
		for (i = 0; i < 2000000u; i++);
		
		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(m2.localScheduler->hwThreadId)); printf(":m2 pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(m2, 1);
	}
}
	
m3: {
	while (loopForever) {
		int i;
		for (i = 0; i < 2000000u; i++);
		
		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(m3.localScheduler->hwThreadId)); printf(":m3 pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(m3, 1);
	}
}
	
m4: {
	while (loopForever) {
		int i;
		for (i = 0; i < 2000000u; i++);
		
		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(m4.localScheduler->hwThreadId)); printf(":m4 pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(m4, 1);
	}
}

// Non-critical
n1: {
	while (loopForever) {
		int i;
		for (i = 0; i < 2000000u; i++);
		
		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(n1.localScheduler->hwThreadId)); printf(":n1 pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(n1, 1);
	}
}
	
n2: {
	while (loopForever) {
		int i;
		for (i = 0; i < 2000000u; i++);
		
		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(n2.localScheduler->hwThreadId)); printf(":n2 pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(n2, 1);
	}
}
	
n3: {
	while (loopForever) {
		int i;
		for (i = 0; i < 2000000u; i++);
		
		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(n3.localScheduler->hwThreadId)); printf(":n3 pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(n3, 1);
	}
}
	
n4: {
	while (loopForever) {
		int i;
		for (i = 0; i < 2000000u; i++);
		
		PTARM_MUTEX_LOCK();
		printf(" "); printf(itoa(n4.localScheduler->hwThreadId)); printf(":n4 pausing.\n");
		PTARM_MUTEX_UNLOCK();
		PAUSE(n4, 1);
	}
}

	return 0;
}

