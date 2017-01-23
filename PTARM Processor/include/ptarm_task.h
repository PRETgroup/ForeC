// This file defines macros for creating and manipulating tasks.

#ifndef PTARM_TASK_H
#define PTARM_TASK_H

#include <ptarm_types.h>
#include <ptarm_io.h>
#include <ptarm_timer.h>
#include <ptarm_scheduler.h>
#include <ptarm_hw_thread.h>
#include <ptarm_foremc.h>


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
	const char *name;									// Name of this task as a string.
	const TaskCriticality criticality;					// Criticality of this task.
	volatile struct _LocalScheduler *localScheduler;	// Reference to the local scheduler that is currently executing this task.
	volatile TaskState state;							// Execution state of this task.
	volatile unsigned int *sp;							// Last location of its stack pointer.
	volatile unsigned int spsr;							// Saved Processor Status Register at the time of preemption.
	/*
	 ->|      |<-- allocatedTime

	   .------.----.--------.---------.
	   | task |    |        |         | slack
	   |--------------------------------------|
				   Base period					*/

	const Timer64Bit allocatedTime;						// Statically allocated execution time in each base period.
	const unsigned int basePeriodsMin;					// Minimum number of base periods between each release time.
	volatile unsigned int lastRelease;					// The base period of its last release.
	volatile unsigned int earliestRelease;				// The next earliest release time.
	
	volatile struct _ForeMc_100int *receiveBuffers[10];	// List of receive buffers.
} Task;


// Variable whose address is at the end of the program binary.
// Defined in the linker script.
extern unsigned int addr_stack_limit;


// Variable whose address is at the end of the PTARM hardware threads' stacks.
// Defined in the linker script.
extern unsigned int addr_stack_end;


// Location of the next free location to begin a new task stack.
unsigned int *ptarmPreviousTaskStackEnd = &addr_stack_end;


//======================================================================
// PTARM task macros.
//======================================================================

// Creates a stack for a task.
// A stack begins (at a higher memory address) with a stack frame followed
// by (at a lower memory address) a stack.
// Due to the way the SP is restored, the task's context is stored after
// the task's stack frame.
// frameSize: size of the task's frame to hold just its local variables.
//            (function calls use the space after the stack frame)
//
//
//                ________________  <-- End of the stack determined by the ptarmCreateTask macro.
// Lower memory  |                |
// address       |                | <-- sp2
//               |__init_context__| <-- sp1 (ptarmPreviousTaskStackEnd - frameSize)
// Higher memory |                |
// address       |__task's frame__| <-- fp1 (ptarmPreviousTaskStackEnd)
//
//                A task's stack

#define PTARM_TASK_CREATE_STACK(task, frameSize, startPc)	\
	asm volatile ("mov r8, sp\n"		/* Save SP of current task*/\
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


// Stores the value of a stack element into a variable.
// PC offset = 56
#define PTARM_TASK_GET_STACK_ELEMENT(var, task, offset)		\
	asm volatile ("ldr %[varReg], [%[stack], #"#offset"]"	\
		  :	[varReg]"=r"(var)								\
		  : [stack]"r"((task)->sp)							\
		  :													\
	)


// Stores the value of a variable into a stack element.
// PC offset = 56
#define PTARM_TASK_SET_STACK_ELEMENT(var, task, offset)		\
	asm volatile ("str %[varReg], [%[stack], #"#offset"]"	\
		  : [stack]"=r"((task)->sp)							\
		  :	[varReg]"r"(var)								\
		  :													\
	)


// Save the context of the current task.
#define PTARM_TASK_SAVE_CONTEXT(task, continuation)			\
	asm volatile ("nop\n"									\
				  "push {r0}\n"		/* PC placeholder */	\
				  "push {r0-r12}\n"							\
				  "push {r14}"								\
	);														\
	asm volatile ("mov r7, %[cont]\n"						\
				  "str r7, [sp, #56]\n"	/* Save PC */		\
				  "mov %[stack], sp"	/* Save SP */		\
		: [stack]"=r"(task.sp)								\
		: [cont]"r"(continuation)							\
		: "r7"												\
	);														\
	PTARM_THREAD_GET_SPSR(task.spsr)


// Save the context of the preempted task.
// (Only used by the exception handler)
#define PTARM_EOE_TASK_SAVE_CONTEXT(scheduler)				\
	asm volatile ("nop\n"									\
				  "pop {lr}\n"								\
				  "push {r0}\n"		/* PC placeholder */	\
				  "push {r0-r12}\n"							\
				  "push {r14}"								\
	);														\
	asm volatile ("cdp p13, 9, cr7, cr0, cr0\n"				\
				  "str r7, [sp, #56]\n"	/* Save PC */		\
				  "mov %[stack], sp"	/* Save SP */		\
		: [stack]"=r"((scheduler)->preemptedSp)				\
		:													\
		: "r7"												\
	);														\
	PTARM_THREAD_GET_SPSR((scheduler)->preemptedSpsr)


// Assign a saved context to a task.
#define PTARM_EOE_TASK_ASSIGN_CONTEXT(scheduler)			\
	scheduler.currentTask->state = PTARM_TASK_PREEMPTED;	\
	scheduler.currentTask->sp = scheduler.preemptedSp;		\
	scheduler.currentTask->spsr = scheduler.preemptedSpsr

// Restore the context of a task.
#define PTARM_TASK_RESTORE_CONTEXT(task)					\
	PTARM_THREAD_SET_CPSR((task)->spsr);					\
	asm volatile ("mov sp, %[stack]\n"	/* Restore SP */	\
				  "pop {r14}\n"								\
				  "pop {r0-r12}\n"							\
				  "pop {pc}"			/* Restore PC */	\
		:													\
		: [stack]"r"((task)->sp)							\
		:													\
	)


// Set the current scheduler to the new scheduler.
#define PTARM_TASK_SET_SCHEDULER(task, scheduler)			\
	task->localScheduler = scheduler




//======================================================================
// PTARM task function.
//======================================================================

// Create a task. Checks that there will be enough memory.
// Thread-safe function.
void ptarmCreateTask(volatile Task *task, unsigned int *startPc, volatile LocalScheduler *localScheduler) {
	PTARM_MUTEX_LOCK();
	const unsigned int frameSize = 0x0100;
	const unsigned int limit = 0x0200;		// 0x0200 * sizeof(unsigned int) byte sized stack.

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

	// Create a stack for the task.
	PTARM_TASK_CREATE_STACK(task, frameSize, startPc);

	// Update where the last stack frame ends.
	ptarmPreviousTaskStackEnd = ptarmPreviousTaskStackEnd - limit;

	// Initialise the SPSR of the task.
	task->spsr = 0;
	
	// Initialise the static and current local schedulers.
	task->localScheduler = localScheduler;

	/*
	// Task = xxx, FP = xxx, SP = xxx, PC = xxx.
	printf("Task = "); printf(task->name);
	printf(", FP = "); printf(hex(stackFrameStart));
	printf(", SP = "); printf(hex((unsigned int)(task->sp)));
	printf(", PC = "); printf(hex(task->sp[14]));
	printf(".\n");
	*/
	PTARM_MUTEX_UNLOCK();
}


#endif /* PTARM_TASK_H */

