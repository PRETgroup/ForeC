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
	PTARM_SCHEDULER_STATIC			= 0,
	PTARM_SCHEDULER_DYNAMIC			= 1
} SchedulerPhase;


// Local scheduler control block.
typedef struct _LocalScheduler {
	const char *name;										// Name of the scheduler as a string.
	const unsigned int hwThreadId;							// Hardware thread number.	
	volatile unsigned int *fp;								// Last location of the stack pointer.
	volatile unsigned int *sp;								// Last location of the stack pointer.
	volatile unsigned int *pc;								// Last location of the program counter.
	volatile unsigned int *preemptedSp;						// Last location of the preempted task's stack pointer.

	struct _Task *const *staticSchedule;					// Static schedule of tasks. Pointers to constant pointers to tasks.
	struct _Task *currentTask;								// Current task to execute.
	struct _Task *const *nextStaticTask;					// Next statically scheduled task to execute.

	SchedulerPhase phase;									// Phase of the scheduling (static or dynamic).

	volatile Timer64Bit basePeriodStart;					// Timestamp of the start of the base period.
	volatile unsigned int basePeriodCounter;				// Number of base periods already executed.
} LocalScheduler;


// Global scheduler control block.
typedef struct {
	const Timer64Bit overhead;								// Scheduling overhead WCE in nanoseconds.
	volatile bool isInitialised;							// Program has been initialised for execution.

	const Timer64Bit basePeriodDuration;					// Duration of one base period in nanoseconds.
	volatile Timer64Bit basePeriodDurationMinusOverhead;	// Duration of one base period in nanoseconds.
	volatile Timer64Bit basePeriodFirstStart;				// Timestamp of the start of the first base period only.
		
	// Pointers to the local schedulers on each hardware thread.
	LocalScheduler *localScheduler0;
	LocalScheduler *localScheduler1;
	LocalScheduler *localScheduler2;
	LocalScheduler *localScheduler3;
	
	// Priority queues for dynamic scheduling.
	volatile struct _Task **priorityQueueNonCritical;		// Non-critical tasks.
	volatile struct _Task **priorityQueueMission;			// Mission critical tasks.
	volatile struct _Task **priorityQueueLife;				// Life critical tasks.
} GlobalScheduler;


//======================================================================
// PTARM scheduler macros.
//======================================================================

// Save the stack and frame pointer, and program counter of the current scheduler.
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
	/* Modify scheduler name. */															\
	char localSchedulerName[10] = "scheduler ";												\
	localSchedulerName[9] = '0' + hwThreadId;												\
																							\
	/* Empty static schedule */																\
	Task *staticSchedule[5] = {NULL};														\
																							\
	/* Create local scheduler */															\
	LocalScheduler localScheduler =	{														\
										.name = localSchedulerName,							\
										.hwThreadId = hwThreadId,							\
										.staticSchedule = staticSchedule,					\
										.currentTask = staticSchedule[0],					\
										.nextStaticTask = staticSchedule,					\
										.phase = PTARM_SCHEDULER_STATIC,					\
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


// Finds the highest priority task from the global priority queue.
#define PTARM_SCHEDULER_DYNAMIC_GET_TASK(currentTask, globalScheduler)	\
	currentTask = NULL


// Reset the global priority queue.
#define PTARM_SCHEDULER_DYNAMIC_LIST_RESET(priorityQueue)	\
	priorityQueue[0] = NULL


#endif /* PTARM_SCHEDULER_H */
