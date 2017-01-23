/*
// Memory map of each PRET core going out for the 1d CFD
// 0xFFFF8000 ------------------------
//                TOP CORE SPACE
// 0xFFFF9000 ------------------------
//                BOTTOM CORE SPACE
// 0xFFFFA000 ------------------------
//                RIGHT CORE SPACE
// 0xFFFFB000 ------------------------
//                LEFT CORE SPACE
// 0xFFFFC000 ------------------------
//                GLOBAL SPACE
// 0xFFFFD000 ------------------------
*/
/* Within each space
--------------------
       TQ
       TP
       RQ 
       RP
       LQ
       LP
--------------------
*/

// start of PRET shared memory address
#define SHARED_BASE		(0xFFFF8000)

#define GLOBAL_REG_BASE             (0xFFFFC000)
#define AD_REG			(*(volatile float *)(GLOBAL_REG_BASE + 0x00))
#define D_REG				(*(volatile float *)(GLOBAL_REG_BASE + 0x04))
#define INV_AD_REG	(*(volatile float *)(GLOBAL_REG_BASE + 0x08))


#define PORTS_BASE              SHARED_BASE + 0x100
// LP, LQ, RP, RQ, TP, TQ - 6 memory locations 
#define CORE_OFFSET_SIZE        6*4

//CONVENTIONAL OUTPUT DEFINITIONS
#ifdef OUTPUT_LCORENUM
#define OUTPUT_LREG_BASE (PORTS_BASE+(OUTPUT_LCORENUM*CORE_OFFSET_SIZE)+0x8)
/* Outputs */
#define OLP			(*(volatile float *)(OUTPUT_LREG_BASE + 0x00))
#define OLQ			(*(volatile float *)(OUTPUT_LREG_BASE + 0x04))
#endif

#ifdef OUTPUT_RCORENUM
#define OUTPUT_RREG_BASE (PORTS_BASE+(OUTPUT_RCORENUM*CORE_OFFSET_SIZE))
#define ORP			(*(volatile float *)(OUTPUT_RREG_BASE + 0x00))
#define ORQ			(*(volatile float *)(OUTPUT_RREG_BASE + 0x04))
#endif

#ifdef OUTPUT_TCORENUM
#define OUTPUT_TREG_BASE (PORTS_BASE+(OUTPUT_TCORENUM*CORE_OFFSET_SIZE)+0x10)
/* Outputs */
#define OTP			(*(volatile float *)(OUTPUT_TREG_BASE + 0x00))
#define OTQ			(*(volatile float *)(OUTPUT_TREG_BASE + 0x04))
#endif

#define CYCLE_PERIOD 15000 //in nano seconds
#define READ_IN_TIME 3000
#define COMPUTE_TIME 10000
