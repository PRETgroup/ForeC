#ifndef PTARM_FORECAST_H
#define PTARM_FORECAST_H

#include <ptarm_hw_thread.h>
#include <ptarm_timer.h>
#include <ptarm_task.h>
#include <ptarm_scheduler.h>


//======================================================================
// ForeCast buffers.
//======================================================================
/*
// Buffer type.
#define	FORECAST_BUFFER(size)			\
	#ifndef FORECAST_BUFFER_##size		\
	#define FORECAST_BUFFER_##size		\
	typedef struct {					\
		volatile int values[##size];	\
		volatile int lastValue;			\
		volatile int count;				\
	} ForeCastBuffer##size;				\
	#endif								\
	ForeCastBuffer##size
*/

// Swap the pointers to new and old buffers. The newBuffer is
// the buffer that will be cleared and used to buffer new data.
#define FORECAST_BUFFER_SWAP(size, newBuffer, oldBuffer)														\
	{																											\
		ForeCastBuffer##size *temp = oldBuffer;																	\
		oldBuffer = newBuffer;																					\
		newBuffer = temp;																						\
		newBuffer->count = 0;																					\
		newBuffer->lastValue = oldBuffer->values[oldBuffer->count - 1];	/* In case oversampling is required */	\
	}


// Adds a value to a buffer.
#define FORECAST_BUFFER_ADD(buffer, value)	\
	buffer.values[buffer.count] = value;	\
	buffer.count++


//======================================================================
// ForeCast macros.
//======================================================================

// Pause the task execution.
#define PAUSE(task, continuationId)											\
	PTARM_EOE_DISABLE();		/* Disable EOE. */							\
	task.state = PTARM_TASK_PAUSED;											\
																			\
	/* Context switch to the local scheduler. */							\
	PTARM_TASK_SAVE_CONTEXT(task, &&PAUSE_##task##continuationId);			\
	PTARM_SCHEDULER_RESTORE_CONTEXT(task.localScheduler);					\
	PTARM_GOTO(localScheduler);												\
	PAUSE_##task##continuationId:


// Pause the task execution and buffer the output variable.
#define PAUSE_AND_BUFFER(task, outputVar, outputVal, continuationId)		\
	PTARM_EOE_DISABLE();		/* Disable EOE. */							\
	task.state = PTARM_TASK_PAUSED;											\
																			\
	/* Buffer the output variable. */										\
	outputVar->values[outputVar->count] = outputVal;						\
	outputVar->count++;														\
																			\
	/* Context switch to the next task. */									\
	PTARM_TASK_SAVE_CONTEXT(task, &&PAUSE_##task##continuationId);			\
	PTARM_SCHEDULER_RESTORE_CONTEXT(task.localScheduler);					\
	PTARM_GOTO(localScheduler);												\
	PAUSE_ ##task##continuationId:


#endif /* PTARM_FORECAST_H */

