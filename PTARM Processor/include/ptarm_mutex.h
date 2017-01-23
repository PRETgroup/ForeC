// This file defines macros for a mutex.

#ifndef PTARM_MUTEX_H
#define PTARM_MUTEX_H


//======================================================================
// PTARM mutex macros.
//======================================================================

// Acquire the mutex. Only one mutex can be acquired.
#define PTARM_MUTEX_LOCK()							\
	asm volatile("cdp p13, 1, cr0, cr7, cr0, 1")


// Release the mutex. Only the acquirer can release the mutex.
#define PTARM_MUTEX_UNLOCK()						\
	asm volatile("cdp p13, 1, cr0, cr7, cr0, 0")


#endif /* PTARM_MUTEX_H */

