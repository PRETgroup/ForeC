/*****************************************************************************
* Filename:          C:\Xilinx\12.1\MyProcessorIPLib\drivers/counter_dfsl_v1_00_a/src/counter_dfsl_selftest.c
* Version:           1.00.a
* Description:
* Date:              Fri Jul 02 14:27:25 2010 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#include "xparameters.h"
#include "counter_dfsl.h"

/* IMPORTANT:
*  In order to run this self test, you need to modify the value of following
*  micros according to the slot ID defined in xparameters.h file.
*/
#define input_slot_id   XPAR_FSL_COUNTER_DFSL_0_INPUT_SLOT_ID
#define output_slot_id  XPAR_FSL_COUNTER_DFSL_0_OUTPUT_SLOT_ID

XStatus COUNTER_DFSL_SelfTest() {
	 unsigned int input;
	 unsigned int output;

	 //Initialize your input data over here:
	 input = 12345;

	 //Call the macro with instance specific slot IDs
	 counter_dfsl(
		 input_slot_id,
		 output_slot_id,
		 input,
		 output
		 );

	 if (output != 12345)
		 return XST_FAILURE;

	 return XST_SUCCESS;
}
