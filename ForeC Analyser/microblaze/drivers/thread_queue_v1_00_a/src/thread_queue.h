/*****************************************************************************
* Filename:          C:\Xilinx\12.1\MyProcessorIPLib\drivers/esterel_mutex_v1_00_a/src/thread_queue.h
* Version:           1.00.a
* Description:       thread_queue (Thread Queue) Driver Header File
* Date:              Fri Jul 02 14:27:25 2010 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#ifndef THREAD_QUEUE_H
#define THREAD_QUEUE_H

#include "fsl.h"


#define thread_queue_push(address, input_slot_id)	\
	putfsl(address, input_slot_id)					\
	
#define thread_queue_pop(address, input_slot_id)	\
	getfsl(address, input_slot_id)					\


#endif

