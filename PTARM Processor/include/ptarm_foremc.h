// This file defines macros for managing the communication between multi-rate tasks.

#ifndef PTARM_FOREMC_H
#define PTARM_FOREMC_H

#include <ptarm_hw_thread.h>
#include <ptarm_timer.h>
#include <ptarm_task.h>
#include <ptarm_scheduler.h>


//======================================================================
// ForeMC buffers.
//======================================================================

// Buffer type.
#define	FORECMC_BUFFER(type, maxsize, var)						\
	typedef struct _ForeMc_##var##maxsize##type {				\
		volatile type data[maxsize];							\
		volatile int rFirst;									\
		volatile int rCount;									\
		volatile int wFirst;									\
		volatile int wCount;									\
		const int maxSize;										\
	} ForeMc_##var##maxsize##type;								\
	ForeMc_##var##maxsize##type var = {							\
										.wFirst = 1,			\
										.maxSize = maxsize		\
									  }


// Pre-defined buffer type.
#ifndef FOREMC_100_INT
#define FOREMC_100_INT
typedef struct _ForeMc_100int {
	volatile int data[100];
	volatile int rFirst;
	volatile int rCount;
	volatile int wFirst;
	volatile int wCount;
	const int maxSize;
} ForeMc_100int;
#endif

// Get the number of buffered elements thta can be read.
#define FOREMC_BUFFER_READ_COUNT(buffer)						\
	(buffer).rCount


// Read a buffer at a given index, i.e., buffer[index]
#define FOREMC_BUFFER_AT_INDEX(buffer, index)					\
	buffer.data[												\
		foreMcGetIndex(index + buffer.rFirst, buffer.maxSize)	\
	]


// Returns 0 <= index <= count for a given index.
// If index is -1, then the last (latest) data index is returned.
#define FOREMC_BUFFER_BOUND(index, buffer)						\
	(															\
		(buffer.rCount == 0)									\
		? 0														\
		: ((index > (buffer.rCount - 1) || index == -1)			\
		   ? (buffer.rCount - 1)								\
		   : index)												\
	)


// Maps the index of the buffer array to the index of the circular buffer.
const unsigned int foreMcGetIndex(const unsigned int indexPlusFirst, const unsigned int maxSize) {
	unsigned int quotient;
	PTARM_UNSIGNED_DIV(quotient, indexPlusFirst, maxSize);
	return (indexPlusFirst) - (quotient * maxSize);
}


// Place data into the circular buffer.
#define FOREMC_BUFFER_SEND(buffer, value)												\
	buffer.data[foreMcGetIndex(buffer.wCount + buffer.wFirst, buffer.maxSize)] = value;	\
	buffer.wCount = buffer.wCount + 1


// Updates the circular buffer when the receiving task is released.
#define FOREMC_BUFFER_RELEASE(buffer)																								\
	/* Transfer the segment of the sending task to the receiving task.*/															\
	(buffer)->rFirst = (buffer)->wFirst;																							\
	(buffer)->rCount = (buffer)->wCount;																							\
																																	\
	/* Set up a new segment for the sending task.*/																					\
	(buffer)->wFirst = foreMcGetIndex((buffer)->wCount + (buffer)->wFirst, (buffer)->maxSize);										\
	(buffer)->wCount = 0;																											\
																																	\
	/* Initialize the new segment with the last value sent.*/																		\
	(buffer)->data[(buffer)->wFirst] = (buffer)->data[foreMcGetIndex((buffer)->rCount - 1 + (buffer)->rFirst, (buffer)->maxSize)]


//======================================================================
// ForeMC macros.
//======================================================================

// Pause the task execution.
#define PAUSE(task, continuationId)										\
	PTARM_EOE_DISABLE();		/* Disable EOE. */						\
	task.state = PTARM_TASK_PAUSED;										\
																		\
	/* Context switch to the local scheduler. */						\
	PTARM_TASK_SAVE_CONTEXT(task, &&PAUSE_##task##continuationId);		\
	PTARM_SCHEDULER_RESTORE_CONTEXT(task.localScheduler);				\
	PTARM_GOTO(localScheduler);											\
	PAUSE_##task##continuationId:


// Pause the task execution and buffer the output variable.
#define PAUSE_AND_BUFFER(task, continuationId, buffer, value)			\
	PTARM_EOE_DISABLE();		/* Disable EOE. */						\
	task.state = PTARM_TASK_PAUSED;										\
																		\
	/* Buffer the output variable. */									\
	FOREMC_BUFFER_SEND(buffer, value);									\
																		\
	/* Context switch to the next task. */								\
	PTARM_TASK_SAVE_CONTEXT(task, &&PAUSE_##task##continuationId);		\
	PTARM_SCHEDULER_RESTORE_CONTEXT(task.localScheduler);				\
	PTARM_GOTO(localScheduler);											\
	PAUSE_##task##continuationId:


#endif /* PTARM_FOREMC_H */

