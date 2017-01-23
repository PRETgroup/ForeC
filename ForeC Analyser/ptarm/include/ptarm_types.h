#ifndef PTARM_TYPES_H
#define PTARM_TYPES_H

//======================================================================
// PTARM types.
//======================================================================

// Prototypes of data structures.
struct _Task;				// Defined in ptarm_task.h
struct _LocalScheduler;		// Defined in ptarm_scheduler.h
struct _Timer64Bit;			// Defined in ptarm_timer.h

// Boolean
typedef enum {
	false	= 0,
	true	= 1
} bool;

// Null value.
#define NULL 0

#endif /* PTARM_TYPES_H */

