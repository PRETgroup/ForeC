/*****************************************************************************
* Filename:          C:\qmb\drivers/forec_mutex_v1_00_a/examples/forec_mutex_v2_1_0_app.c
* Version:           1.00.a
* Description:       forec_mutex (new FSL core) Driver Example File
* Date:              Fri Jul 02 15:14:50 2010 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#include "forec_mutex.h"

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
#define WRITE_FOREC_MUTEX_0(val)  write_into_fsl(val, XPAR_FSL_FOREC_MUTEX_0_INPUT_SLOT_ID)
#define READ_FOREC_MUTEX_0(val)  read_from_fsl(val, XPAR_FSL_FOREC_MUTEX_0_OUTPUT_SLOT_ID)

void forec_mutex_app(
       unsigned int* input_0,      /* Array size = 4 */
       unsigned int* output_0       /* Array size = 1 */
       )
{
   int i;

   //Start writing into the FSL bus
   for (i = 0; i < 4; i++) {
      WRITE_FOREC_MUTEX_0(input_0[i]);
   }

   //Start reading from the FSL bus
   for (i = 0; i < 1; i++) {
      READ_FOREC_MUTEX_0(output_0[i]);
   }
}

main() {
	 unsigned int input_0[4];     
	 unsigned int output_0[1];     


#ifdef __PPC__
	 // Enable APU for PowerPC.
	 unsigned int msr_i;
	 msr_i = mfmsr();
	 msr_i = (msr_i | XREG_MSR_APU_AVAILABLE | XREG_MSR_APU_ENABLE) & ~XREG_MSR_USER_MODE;
	 mtmsr(msr_i);
#endif

	 //Initialize your input data over here: 
	 input_0[0] = 12345;     
	 input_0[1] = 24690;     
	 input_0[2] = 37035;     
	 input_0[3] = 49380;     

	 //Call the macro with instance specific slot IDs
	 forec_mutex(
		 XPAR_FSL_FOREC_MUTEX_0_INPUT_SLOT_ID,
		 XPAR_FSL_FOREC_MUTEX_0_OUTPUT_SLOT_ID,
		 input_0,      
		 output_0       
		 );

	 // You can also define your own function to access the peripheral
	 // Here you are calling the example function defined above
	 // Note the slot ID can not be passed over as function parameters
	 forec_mutex_app(
		 input_0,      
		 output_0       
		 );

}

