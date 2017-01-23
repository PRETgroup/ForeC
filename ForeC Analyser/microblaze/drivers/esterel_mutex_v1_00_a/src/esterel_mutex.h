/*****************************************************************************
* Filename:          C:\Xilinx\12.1\MyProcessorIPLib\drivers/esterel_mutex_v1_00_a/src/esterel_mutex.h
* Version:           1.00.a
* Description:       esterel_mutex (Esterel Mutex) Driver Header File
* Date:              Fri Jul 02 14:27:25 2010 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#ifndef ESTEREL_MUTEX_H
#define ESTEREL_MUTEX_H

#include "fsl.h"


// Set the key to use the mutex. Blocking instruction.
#define esterel_mutex_set_key(key, input_slot0_id)		\
	putfsl(key, input_slot0_id)							\

// Set the value associated with the current key. Blocking instruction.
#define esterel_mutex_lock(value, input_slot1_id)		\
	putfsl(value, input_slot1_id)						\

// Decrements the value of the lock for the given key.
#define esterel_mutex_unlock(key, input_slot2_id)		\
	putfsl(key, input_slot2_id)							\

// Get the value of the lock with the current key. For signal resolution only.
#define esterel_mutex_unlocked(value, input_slot2_id)	\
	getfsl(value, input_slot2_id)						\


#endif

