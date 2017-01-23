#ifndef PTARM_TASK_H
#define PTARM_TASK_H

#include <ptarm_types.h>
#include <ptarm_io.h>
#include <ptarm_timer.h>
#include <ptarm_scheduler.h>

//======================================================================
// PTARM task variables.
//======================================================================

// Task states.
typedef enum {
	PTARM_TASK_PAUSED		= 0,
	PTARM_TASK_PREEMPTED	= 1,
	PTARM_TASK_RELEASED		= 2
} TaskState;


// Task criticalities.
typedef enum {
	PTARM_TASK_LIFE			= 0,
	PTARM_TASK_MISSION		= 1,
	PTARM_TASK_NONCRITICAL	= 2
} TaskCriticality;


// Task control block.
typedef struct _Task {
	const char *name;						// Name of the task as a string.
	const TaskCriticality criticality;		// Criticality of the task.
	struct _LocalScheduler *localScheduler;	// Local scheduler that statically schedules this task.
	volatile TaskState state;				// Execution state of the task.
	volatile unsigned int *sp;				// Last location of the stack pointer.
	
	/*                                        basePeriodsMin, basePeriodsElapsed++
	 ->|      |<-- allocatedTime              |
	                                          V
	   .------.----.--------.---------.
	   | task |    |        |         | slack
	   |--------------------------------------|
	   Base period					*/
	const Timer64Bit allocatedTime;			// Statically allocated execution time in each base period.
	const unsigned int basePeriodsMin;		// Minimum number of base periods between each task release.
	volatile unsigned int lastRelease;		// The base period count of its last release.
	volatile unsigned int earliestRelease;	// The next earliest release time of the task.
} Task;


// Variable whose address is at the end of the program binary.
// Defined by the linker script.
extern unsigned int addr_stack_limit;


// Variable whose address is at the end of the PTARM hardware threads' stacks.
// Defined by the linker script.
extern unsigned int addr_stack_end;


// Location of the next free location to begin a new task stack.
unsigned int *ptarmPreviousTaskStackEnd = &addr_stack_end;


//======================================================================
// PTARM task macros.
//======================================================================

// Creates a stack for a task.
// Due to the way the SP is restored, the task's context is stored after
// the stack frames (rather than inside the task's stack frame).
// frameSize: frame size for just the task to hold local variables (excludes function calls).
// limit: stack limit for the task.
//
//  ________________  <-- ptarmPreviousTaskStackEnd - limit
// |                |
// |                | <-- sp2
// |__init_context__| <-- sp1, ptarmPreviousTaskStackEnd - frameSize
// |                |
// |__task's frame__| <-- fp1, ptarmPreviousTaskStackEnd

#define PTARM_TASK_CREATE_STACK(task, frameSize, limit, startPc)	\
	asm volatile ("mov r8, sp\n"	/* Save SP of current task */	\
				  "mov sp, %[sp1]\n"	/* Set new SP */			\
				  "mov r9, %[fp1]\n"	/* Set new FP */			\
																	\
				  /* Initialise task context */						\
				  "mov r7, %[pc1] \n"								\
				  "push {r7}\n"	/*pc*/								\
				  "mov r7, #0\n"									\
				  "push {r7}\n"	/*ip*/								\
				  "push {r9}\n"	/*fp*/								\
				  "push {r7}\n"	/*sl*/								\
				  "push {r7}\n"	/*r9*/								\
				  "push {r7}\n"	/*r8*/								\
				  "push {r7}\n"	/*r7*/								\
				  "push {r7}\n"	/*r6*/								\
				  "push {r7}\n"	/*r5*/								\
				  "push {r7}\n"	/*r4*/								\
				  "push {r7}\n"	/*r3*/								\
				  "push {r7}\n"	/*r2*/								\
				  "push {r7}\n"	/*r1*/								\
				  "push {r7}\n"	/*r0*/								\
				  "push {r7}\n"	/*r14*/								\
																	\
				  "mov %[sp2], sp\n"	/* Save SP */				\
				  "mov sp, r8"		/* Restore SP of current task */\
		: [sp2]"=r"((task)->sp)										\
		: [pc1]"r"(startPc), 										\
		  [sp1]"r"(ptarmPreviousTaskStackEnd - frameSize),			\
		  [fp1]"r"(ptarmPreviousTaskStackEnd)						\
		: "r7","r8", "r9"											\
		)


// Save the context of the current task.
#define PTARM_TASK_SAVE_CONTEXT(task, continuation)			\
	asm volatile ("push {r0}\n"		/* PC placeholder */	\
				  "push {r0-r12}\n"							\
				  "push {r14}\n"							\
				  "mov r7, %[cont]\n"						\
				  "str r7, [sp, #56]\n"	/* Save PC */		\
				  "mov %[stack], sp"	/* Save SP */		\
		: [stack]"=r"(task.sp)								\
		: [cont]"r"(continuation)							\
		: "r7"												\
	)


// Save the context of the preempted task.
#define PTARM_EOE_TASK_SAVE_CONTEXT(scheduler)			\
	asm volatile ("pop {lr}\n"							\
				  "push {r0}\n"	/* PC placeholder */	\
				  "push {r0-r12}\n"						\
				  "push {r14}\n"						\
				  "cdp p13, 9, cr7, cr0, cr0\n"			\
				  "str r7, [sp, #56]\n"	/* Save PC */	\
				  "mov %[stack], sp"	/* Save SP */	\
		 : [stack]"=r"((scheduler)->preemptedSp)		\
		 :												\
		 : "r7"											\
	)


// Restore the context of a task.
#define PTARM_TASK_RESTORE_CONTEXT(task)				\
	asm volatile ("mov sp, %[stack]\n"	/* Restore SP */\
				  "pop {r14}\n"							\
				  "pop {r0-r12}\n"						\
				  "pop {pc}"			/* Restore PC */\
		:												\
		: [stack]"r"((task)->sp)						\
		:												\
	)


// Restore the context of a task and unlock the scheduler mutex.
//#define PTARM_TASK_RESTORE_CONTEXT_AND_UNLOCK(task)			\
//	(task)->state = PTARM_TASK_EXECUTING;						\
//	asm volatile ("mov sp, %[stack]\n"	/* Restore SP */		\
//				  "pop {r14}\n"									\
//				  "pop {r0-r12}\n"								\
//				  "cdp p13, 1, cr0, cr7, cr0, 0\n"	/* Unlock */\
//				  "pop {pc}"			/* Restore PC */		\
//		:														\
//		: [stack]"r"((task)->sp)								\
//		:														\
//	)


//======================================================================
// PTARM task function.
//======================================================================

// Create a task. Checks that there will be enough memory.
void ptarmCreateTask(Task *task, unsigned int *startPc) {
	const unsigned int frameSize = 0x0100;
	const unsigned int limit = 0x0200;
//	const unsigned int stackFrameStart = (unsigned int)ptarmPreviousTaskStackEnd;

	// Check that there is enough memory to create a task stack.
	if ((ptarmPreviousTaskStackEnd - &addr_stack_limit) < limit) {
		printf("PTARM_TASK_CREATE: Stack limit exceeded!\n");
		printf("  Available amount: ");
		printf(utoa((ptarmPreviousTaskStackEnd -  &addr_stack_limit)*sizeof(unsigned int)));
		printf(" bytes.\n");
		printf("  Requested amount: ");
		printf(utoa(limit*sizeof(unsigned int)));
		printf(" bytes.\n");
		while(1);
	}

	// Create a 0x0200 * sizeof(unsigned int) byte sized stack for the task.
	PTARM_TASK_CREATE_STACK(task, frameSize, limit, startPc);

	// Update where the last stack frame ends.
	ptarmPreviousTaskStackEnd = ptarmPreviousTaskStackEnd - limit;

	/*
	// Task = xxx, FP = xxx, SP = xxx, PC = xxx.
	PTARM_MUTEX_LOCK();
	printf("Task = "); printf(task->name);
	printf(", FP = "); printf(hex(stackFrameStart));
	printf(", SP = "); printf(hex((unsigned int)(task->sp)));
	printf(", PC = "); printf(hex(task->sp[14]));
	printf(".\n");
	PTARM_MUTEX_UNLOCK();
	*/
}


#endif /* PTARM_TASK_H */

