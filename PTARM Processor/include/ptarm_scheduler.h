// This file defines macros for creating and managing static and dynamic task schedules.

#ifndef PTARM_SCHEDULER_H
#define PTARM_SCHEDULER_H

#include <ptarm_types.h>
#include <ptarm_io.h>
#include <ptarm_mutex.h>
#include <ptarm_task.h>
#include <ptarm_timer.h>
#include <ptarm_hw_thread.h>


//======================================================================
// PTARM scheduler variables.
//======================================================================

// Task states.
typedef enum {
	PTARM_SCHEDULER_RELEASE			= 0,
	PTARM_SCHEDULER_STATIC			= 1,
	PTARM_SCHEDULER_DYNAMIC			= 2
} SchedulerPhase;


// Local scheduler control block.
// (For managing one hardware thread)
typedef struct _LocalScheduler {
	const char *name;										// Name of this scheduler as a string.
	const unsigned int hwThreadId;							// Hardware thread number that this scheduler manages.
	volatile unsigned int *fp;								// Last location of this scheduler's stack pointer.
	volatile unsigned int *sp;								// Last location of this scheduler's stack pointer.
	volatile unsigned int *pc;								// Last location of this scheduler's program counter.
	volatile unsigned int *preemptedSp;						// Last location of the preempted task's stack pointer.
	volatile unsigned int preemptedSpsr;					// Saved Processor Status Register at the time of preemption.

	volatile struct _Task *const *staticSchedule;			// Static schedule of tasks. Pointer to constant pointers to tasks.
	volatile struct _Task *currentTask;						// Current task to execute.
	volatile struct _Task *const *nextStaticTask;			// Next statically scheduled task to execute.

	volatile SchedulerPhase phase;							// Phase of the scheduling (static or dynamic).

	volatile Timer64Bit basePeriodStart;					// Timestamp of the start of the base period.
	volatile unsigned int basePeriodCounter;				// Number of base periods already executed.
	
	volatile Timer64Bit basePeriodStartOverhead;			// Worst-case scheduling overhead time in nanoseconds.
	volatile Timer64Bit basePeriodEndOverhead;				// Worst-case scheduling overhead time in nanoseconds.
	volatile Timer64Bit basePeriodStartAfterOverhead;		// Absolute starting time of the static scheduling phase.
	volatile Timer64Bit basePeriodMinusEndingOverhead;		// Duration of one base period minus the ending overhead in nanoseconds.

	volatile Timer64Bit currentTime;						// Variable to help compute the current physical time.
	volatile Timer64Bit elapsedTime;						// Variable to help compute the elapsed physical time.
} LocalScheduler;


// Global scheduler control block.
// (For managing all the local schedulers, i.e., hardware threads.)
typedef struct {
	volatile bool isInitialised;							// Program has been initialised for execution.

	const Timer64Bit basePeriodDuration;					// Duration of one base period in nanoseconds.
	volatile Timer64Bit basePeriodFirstStart;				// Timestamp of the start of the first base period only.

	// Pointers to the local schedulers of each hardware thread.
	volatile LocalScheduler *localScheduler0;
	volatile LocalScheduler *localScheduler1;
	volatile LocalScheduler *localScheduler2;
	volatile LocalScheduler *localScheduler3;

	// Priority queues for dynamic scheduling.
	volatile struct _Task **priorityQueueNonCritical;		// Non-critical tasks.
	volatile struct _Task **priorityQueueMission;			// Mission critical tasks.
	volatile struct _Task **priorityQueueLife;				// Life critical tasks.

	// Index of the last task of each priority queue. -1 = empty.
	volatile int counterNonCritical;						// Non-critical tasks.
	volatile int counterMission;							// Mission critical tasks.
	volatile int counterLife;								// Life critical tasks.
} GlobalScheduler;


//======================================================================
// PTARM scheduler macros.
//======================================================================

// Save the stack pointer, frame pointer, and program counter of the current scheduler.
#define PTARM_SCHEDULER_SAVE_CONTEXT(scheduler, continuation)		\
	asm volatile ("mov %[stack], sp\n"	/* Save SP */				\
				  "mov %[frame], fp"	/* Save FP */				\
		: [stack]"=r"(scheduler.sp), [frame]"=r"(scheduler.fp)		\
		: 															\
		: 															\
	);																\
	scheduler.pc = continuation


// Restore the stack and frame pointer of a scheduler.
#define PTARM_SCHEDULER_RESTORE_CONTEXT(scheduler)					\
	asm volatile ("mov sp, %[stack]\n"	/* Restore SP */			\
				  "mov fp, %[frame]"	/* Restore FP */			\
		:															\
		: [stack]"r"(scheduler->sp), [frame]"r"(scheduler->fp)		\
		:															\
	)


// Create a local scheduler for a hardware thread. Uses the hardware thread's stack.
#define ptarmCreateLocalScheduler(localScheduler, startPc)									\
	/* Hardware thread number. */															\
	unsigned int hwThreadId;																\
	PTARM_THREAD_GET_ID(hwThreadId);														\
																							\
	/* Empty static schedule that holds up to five tasks */									\
	volatile Task *staticSchedule[5] = { NULL };											\
																							\
	/* Set the scheduler name. */															\
	char localSchedulerName[11] = "scheduler ";												\
	localSchedulerName[9] = '0' + hwThreadId;												\
																							\
	/* Create local scheduler */															\
	LocalScheduler localScheduler =	{														\
										.name = localSchedulerName,							\
										.hwThreadId = hwThreadId,							\
										.staticSchedule = staticSchedule,					\
										.currentTask = staticSchedule[0],					\
										.nextStaticTask = staticSchedule,					\
										.phase = PTARM_SCHEDULER_RELEASE,					\
										.basePeriodCounter = 0								\
									};														\
																							\
	/* Initialise the context. */															\
	PTARM_SCHEDULER_SAVE_CONTEXT(localScheduler, startPc)

	/*
	// Scheduler = xxx, SP = xxx, PC = xxx, hwThreadId = xxx.
	PTARM_MUTEX_LOCK();
	printf("Scheduler = "); printf(localScheduler->name);
	printf(", SP = "); printf(hex((unsigned int)localScheduler->sp));
	printf(", PC = "); printf(hex((unsigned int)localScheduler->pc));
	printf(", hwThreadId = "); printf(utoa(localScheduler->hwThreadId));
	printf(".\n");
	PTARM_MUTEX_UNLOCK();
	*/

// Inserts a life or mission critical task into the global priority queue.
#define PTARM_SCHEDULER_DYNAMIC_LIST_PUSH_LIFE_MISSION(globalScheduler, task)				\
	if (task->criticality == PTARM_TASK_LIFE) {												\
		++globalScheduler.counterLife;														\
		globalScheduler.priorityQueueLife[globalScheduler.counterLife] = task;				\
	} else if (task->criticality == PTARM_TASK_MISSION) {									\
		++globalScheduler.counterMission;													\
		globalScheduler.priorityQueueMission[globalScheduler.counterMission] = task;		\
	}


// Inserts a non-critical task into the global priority queue.
#define PTARM_SCHEDULER_DYNAMIC_LIST_RELEASE_NON_CRITICAL(globalScheduler, localScheduler, task)				\
	if (((task)->state == PTARM_TASK_PAUSED) && ((task)->earliestRelease <= localScheduler.basePeriodCounter)) {\
		/* "Released xxx." */																					\
		PTARM_MUTEX_LOCK();																						\
		printf(" "); printf(itoa(localScheduler.hwThreadId)); printf(":Releasing ");							\
		printf((task)->name); printf(".\n");																	\
		PTARM_MUTEX_UNLOCK();																					\
																												\
		/* The minimum number of base periods has elapsed, so release the task. */								\
		(task)->state = PTARM_TASK_RELEASED;																	\
																												\
		/* Update its last released timestamp. */																\
		(task)->lastRelease = localScheduler.basePeriodCounter;													\
																												\
		/* Update its next earliest release timestamp. */														\
		(task)->earliestRelease = (localScheduler.basePeriodCounter + (task)->basePeriodsMin);					\
																												\
		/* Insert the non-critical task into the global priority queue. */										\
		++globalScheduler.counterNonCritical;																	\
		globalScheduler.priorityQueueNonCritical[globalScheduler.counterNonCritical] = (task);					\
	}


// Finds a task from the global priority queues.
#define PTARM_SCHEDULER_DYNAMIC_LIST_POP(globalScheduler, task)								\
	if (globalScheduler.counterNonCritical > -1) {											\
		task = globalScheduler.priorityQueueNonCritical[globalScheduler.counterNonCritical];\
		--globalScheduler.counterNonCritical;												\
	} else if (globalScheduler.counterMission > -1) {										\
		task = globalScheduler.priorityQueueMission[globalScheduler.counterMission];		\
		--globalScheduler.counterMission;													\
	} else if (globalScheduler.counterLife > -1) {											\
		task = globalScheduler.priorityQueueLife[globalScheduler.counterLife];				\
		--globalScheduler.counterLife;														\
	} else {																				\
		task = NULL;																		\
	}


// Reset the global priority queue.
#define PTARM_SCHEDULER_DYNAMIC_LIST_RESET(globalScheduler)	\
	globalScheduler.counterNonCritical = -1;				\
	globalScheduler.counterMission = -1;					\
	globalScheduler.counterLife = -1


#endif /* PTARM_SCHEDULER_H */
