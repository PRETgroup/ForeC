/*****************************************************************************
* Filename:          C:\Xilinx\12.1\MyProcessorIPLib\drivers/counter_dfsl_v1_00_a/examples/counter_dfsl_v2_1_0_app.c
* Version:           1.00.a
* Description:       counter_dfsl (Counter DFSL) Driver Example File
* Date:              Fri Jul 02 14:27:25 2010 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#include "counter_dfsl.h"

#include "xparameters.h"

/*
* Follwing is an example driver function
* that is called in the main function.
*
* This example driver writes all the data in the input arguments
* into the input FSL bus through blocking writes. FSL peripheral will
* automatically read from the FSL bus. Once all the inputs
* have been written, the output from the FSL peripheral is read
* into output arguments through blocking reads.
*
* CAUTION:
*
* The sequence of writes and reads in this function should be consistent
* with the sequence of reads or writes in the HDL implementation of this
* coprocessor.
*
*/
// Instance name specific MACROs. Defined for each instance of the peripheral.
#define WRITE_COUNTER_DFSL_0(val)  write_into_fsl(val, XPAR_FSL_COUNTER_DFSL_0_INPUT_SLOT_ID)
#define READ_COUNTER_DFSL_0(val)  read_from_fsl(val, XPAR_FSL_COUNTER_DFSL_0_OUTPUT_SLOT_ID)

void counter_dfsl_app(unsigned int input, unsigned int output) {
	int i;

	//Start writing into the FSL bus
	WRITE_COUNTER_DFSL_0(input);

	//Start reading from the FSL bus
	READ_COUNTER_DFSL_0(output);
}

main() {
	 unsigned int input;
	 unsigned int output;

	 //Initialize your input data over here:
	 input = 12345;

	 //Call the macro with instance specific slot IDs
	 counter_dfsl(
		XPAR_FSL_COUNTER_DFSL_0_INPUT_SLOT_ID,
		XPAR_FSL_COUNTER_DFSL_0_OUTPUT_SLOT_ID,
		input,
		output
	);

	 // You can also define your own function to access the peripheral
	 // Here you are calling the example function defined above
	 // Note the slot ID can not be passed over as function parameters
	 counter_dfsl_app(input, output);

}

