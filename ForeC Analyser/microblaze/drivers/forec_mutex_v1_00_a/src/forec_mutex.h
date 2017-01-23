/*****************************************************************************
* Filename:          C:\Xilinx\12.1\MyProcessorIPLib\drivers/forec_mutex_v1_00_a/src/forec_mutex.h
* Version:           1.00.a
* Description:       forec_mutex (ForeC Mutex) Driver Header File
* Date:              Fri Jul 02 14:27:25 2010 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#ifndef FOREC_MUTEX_H
#define FOREC_MUTEX_H


#include "fsl.h"


// Set the bit at the given position in the bit array.
#define forec_mutex_set(position, input_slot_id)			\
	putfsl((position << 1) + 1, input_slot_id)				\

// Resets all bits to 1. Only works on core0.
#define forec_mutex_reset(input_slot_id)					\
	putfsl(0, input_slot_id)								\

// Clear the bit at the given position in the bit array.
#define forec_mutex_clear(position, input_slot_id)			\
	putfsl(((position) << 1) + 0, input_slot_id)			\

// Read the entire bit array.
#define forec_mutex_read(bitVector, input_slot_id)			\
	getfsl(bitVector, input_slot_id)						\


#endif

