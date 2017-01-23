/*****************************************************************************
* Filename:          C:\Xilinx\12.1\MyProcessorIPLib\drivers/counter_dfsl_v1_00_a/src/counter_dfsl.h
* Version:           1.00.a
* Description:       counter_dfsl (Counter DFSL) Driver Header File
* Date:              Fri Jul 02 14:27:25 2010 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#ifndef COUNTER_DFSL_H
#define COUNTER_DFSL_H

#include "fsl.h"


typedef struct {
	int current;		// Current counter value measured.
	int last;			// Last value of the counter.
	int difference;		// Difference between the current and last values.
	int min;			// Minimum counter value.
	int avg;			// Average counter value.
	int max;			// Maximum counter value.
	long int total;		// Cumulative value of all differences.
	int iterations;		// Number of times values are added to the total.
} Counter;


// Initialise the current and last counter values.
#define counterInitialise(counter)							\
	counterReset(counter);									\
	counter.difference = 0;									\
	counter.min = 2147483647;								\
	counter.avg = 0;										\
	counter.max = 0;										\
	counter.total = 0;										\
	counter.iterations = 0									\

#define counterReset(counter)								\
	counter.current = 0;									\
	counter.last = 0										\

// Start the counter with the specified value.
#define counterStart(counter, input_slot_id)				\
	putfsl(counter.current, input_slot_id)					\

// Stop the counter and read the current value.
#define counterStop(input_slot_id)							\
	putfsl(0, input_slot_id)								\

// Read the current counter value.
// Subtract 3 cycles for put and addk instruction.
#define counterRead(counter, input_slot_id)					\
	getfsl(counter.current, input_slot_id);					\
	counter.current -= 3									\

// Calculate the difference between the current and last
// counter values.
#define counterDifference(counter)							\
	counter.difference = counter.current - counter.last		\

// Accumulate the counter difference.
#define counterAccumulate(counter)							\
	counter.total += counter.difference;					\
	counter.iterations++									\
	
// Calculate the average differences.
#define counterAverage(counter)								\
	counter.avg = counter.total/counter.iterations			\

// Update the maximum counter difference.
#define counterMaximum(counter)								\
	if (counter.max < counter.difference) {					\
		counter.max = counter.difference;					\
	}														\

// Update the minimum counter difference.
#define counterMinimum(counter)								\
	if (counter.min > counter.difference) {					\
		counter.min = counter.difference;					\
	}														\


#endif

