// This file defines some useful data types.

#ifndef PTARM_TYPES_H
#define PTARM_TYPES_H


//======================================================================
// PTARM types.
//======================================================================

// Prototypes of data structures.
struct _Task;				// Defined in ptarm_task.h
struct _LocalScheduler;		// Defined in ptarm_scheduler.h
struct _Timer64Bit;			// Defined in ptarm_timer.h
struct _ForeMc_100int;		// Defined in ptarm_foremc.h

// Boolean
typedef enum {
	false	= 0,
	true	= 1
} bool;

// Null value.
#define NULL 0

// Time units.
#define NANO_SECOND		1u
#define MICRO_SECOND	1000u*NANO_SECOND
#define MILLI_SECOND	1000u*MICRO_SECOND
#define SECOND			1000u*MILLI_SECOND


#endif /* PTARM_TYPES_H */

