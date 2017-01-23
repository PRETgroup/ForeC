#include "oned_cfd.h"
#include <deadline.h>

//I/O memory map
//Output P
//Output Q
//Left P
//Left Q
//Right P
//Right Q
//Top P
//Top Q
//Global 1: speed of sound * density
//Global 2: density
//Global 3: 1/(a*density)

#define ABSF(y,x) asm volatile ("abss %[out], %[in]\n\t": [out]"=f"((y)): [in]"f"((x)));

#define INTERP(Center, Edge, Slope) (Center - Slope*(Center-Edge)) 

//Enable Interpolation
#define USE_INTERP 0

//enumerate elemental processor types
#define PIPE_SEGMENT 	0
#define UPSTREAM_P		1
#define UPSTREAM_Q		2
#define CAP						3
#define VALVE					4
#define PIPE_T				5

//Assuming it takes one clock to read all I/O registers then our worst case time
//to read them all is the worst case number of input registers and global registers
#define READ_COMPLETE_TIMESTEP (LOCAL_CONST_BASE - INPUT_REG_BASE)

#if defined(INIT_LP) && defined(INIT_RP) && defined(INIT_LQ) && defined(INIT_RQ) && defined(INIT_TP) && defined(INIT_TQ)
#define _INITIALIZED_ 1
#endif

#ifndef INIT_OP
#define INIT_OP (float)1.0
#endif

#ifndef INIT_OQ
#define INIT_OQ (float)1.0
#endif


#define INPUT_REG_BASE (PORTS_BASE+(CORENUM*CORE_OFFSET_SIZE))
#define LP			(*(volatile float *)(INPUT_REG_BASE  + 0x00))
#define LQ			(*(volatile float *)(INPUT_REG_BASE  + 0x04))
#define RP			(*(volatile float *)(INPUT_REG_BASE  + 0x08))
#define RQ			(*(volatile float *)(INPUT_REG_BASE  + 0x0C))
#define TP			(*(volatile float *)(INPUT_REG_BASE  + 0x10))
#define TQ			(*(volatile float *)(INPUT_REG_BASE  + 0x14))

#ifndef CONST1
#define CONST1 (float)1.0
#endif

#ifndef CONST2
#define CONST2 (float)1.0
#endif

#ifndef CONST3
#define CONST3 (float)1.0
#endif

#ifndef CONST4
#define CONST4 (float)1.0
#endif

#ifndef CONST5
#define CONST5 (float)1.0
#endif

#ifndef CONST6
#define CONST6 (float)1.0
#endif

#ifndef _FUNCNAME_
#define _FUNCNAME_ main
#endif

int _FUNCNAME_(void)
{
  register float lp, rp, lq, rq;  //adjacent processor data
  //The top data type is not used in all cases, count on the compiler to remove
  register float tp, tq;  //top data just for pipe T
  register float ad, d, inv_ad;  //globals
  register float Cv;
  const float Inv_area = CONST1;
  const float FFact = CONST2;
#if EP_TYPE != VALVE
  const float area = CONST3;
#else //EP_TYPE == VALVE
  const float Cvp = CONST3;
#endif //EP_TYPE != VALVE
#if USE_INTERP == 1
	const float Theta = CONST4;
#endif //USE_INTERP == 1

#if EP_TYPE == PIPE_T
	const float Inv_area2 = CONST5;
	const float Inv_area3 = CONST6;
	register float Br, Bt, abs_lt, abs_tq, Cmr, Cmt, Inv_Bl, Inv_Bt, Inv_Br, CpInv_Bl, CmrInv_Br, CmrInv_Bt, CmtInv_Bt;
#endif //EP_TYPE == PIPE_T

  register float B, InvB, R, Cp, Cm, op, oq;
  float abs_lq, abs_rq;

  int initial = 1;
  int nsec, sec;
  int read_nsec, read_sec;

  SET_TIME(CYCLE_PERIOD, 0, nsec, sec);

  while(1)
    {
      SET_TIME(READ_IN_TIME, 0, read_nsec, read_sec);

#if _INITIALIZED_ == 1
      if (initial == 1){
	//Begin external read at start of timestep
	//Read from adjacent processors
	lp = (float)INIT_LP; //Left (upstream) pressure
	rp = (float)INIT_RP; //Right (downstream) pressure
	lq = (float)INIT_LQ; //Left (upstream) input flow
	rq = (float)INIT_RQ; //Right (downstream) output flow
	//The top input is not used in all cases, count on the compiler to remove
	tp = (float)INIT_TP; //Top pressure
	tq = (float)INIT_TQ; //Top flow
#if USE_INTERP == 1
	op = (float)INIT_OP; //Initial Value, used in interpolated mode
	oq = (float)INIT_OQ; //Initial Value, used in interpolated mode
#endif //USE_INTERP == 1
	initial = 0;
      }
      else {
#endif
	//Begin external read at start of timestep
	//Read from adjacent processors
	lp = LP; //Left (upstream) pressure
	rp = RP; //Right (downstream) pressure
	lq = LQ; //Left (upstream) input flow
	rq = RQ; //Right (downstream) output flow
	//The top input is not used in all cases, count on the compiler to remove
	tp = TP; //Top pressure
	tq = TQ; //Top flow
#if _INITIALIZED_ == 1
      }
#endif

      //ReadGlobals
      //a is speed of sound (wavespeed)
			//d is density
      //Pre compute as much as possible
      ad = AD_REG;
      d = D_REG;
      inv_ad = INV_AD_REG;

      DELAY_UNTIL(read_nsec, read_sec);

      SET_TIME(COMPUTE_TIME, 0, read_nsec, read_sec);

      //Complete external read by clock number READ_COMPLETE_TIMESTEP

      /* Interpolate 
			 * Different elements require different number of interpolations depending on
			 * the number of fluid inputs.  
			 * 1 Interpolation, downstream - UPSTREAM_P, UPSTREAM_Q
			 * 1 Interpolation, upstream - VALVE, CAP
			 * 2 Interpolations - PIPE_SEGMENT
			 * 3 Interpolations - PIPE_T
			 * */

#if EP_TYPE == PIPE_SEGMENT
#if USE_INTERP == 1
			lp = INTERP(op, lp,(ad*Theta));
			lq = INTERP(oq, lq,(ad*Theta));	
			rp = INTERP(op, rp,(ad*Theta));
			rq = INTERP(oq, rq,(ad*Theta));
			//Note that Theta is the ratio of timestep to length and divided by d
			//The only reason we have the d term is that we already have the global ad so it by modifying Theta
			//we can save a global.
#endif //USE_INTERP
      B = ad*Inv_area;
      InvB = inv_ad*area;
      R = d*FFact;
      ABSF(abs_lq, lq);
      ABSF(abs_rq, rq);
      Cp = lp+lq*(B-R*abs_lq);
      Cm = rp-rq*(B-R*abs_rq);
      op = (Cm+Cp)*0.5f;
      oq = (op-Cm)*InvB;
#endif //EP_TYPE == PIPE_SEGMENT

#if EP_TYPE == UPSTREAM_P
#if USE_INTERP == 1
			rp = INTERP(op, rp,(ad*Theta));
			rq = INTERP(oq, rq,(ad*Theta));
#endif //USE_INTERP
      B = ad*Inv_area;
      InvB = inv_ad*area;
      R = d*FFact;
      ABSF(abs_rq, rq);

      Cm = rp-rq*(B-R*abs_rq);
      op = tp;//Get imposed pressure from top
      oq = (op-Cm)*InvB;
#endif //EP_TYPE == UPSTREAM_P

#if EP_TYPE == UPSTREAM_Q
#if USE_INTERP == 1
			rp = INTERP(op, rp,(ad*Theta));
			rq = INTERP(oq, rq,(ad*Theta));

#endif //USE_INTERP
      B = ad*Inv_area;

      R = d*FFact;

      ABSF(abs_rq, rq);
      Cm = rp-rq*(B-R*abs_rq);
      op = Cm-(B*tq);//Get imposed flow from top
      oq = tq;
#endif //EP_TYPE == UPSTREAM_Q

#if EP_TYPE == CAP
#if USE_INTERP == 1
			lp = INTERP(op, lp,(ad*Theta));
			lq = INTERP(oq, lq,(ad*Theta));	

#endif //USE_INTERP
      B = ad*Inv_area;

      R = d*FFact;
      ABSF(abs_lq, lq);

      Cp = lp+lq*(B-R*abs_lq);

      op = Cp;
      oq = 0.0f;
#endif //EP_TYPE == CAP

#if EP_TYPE == VALVE
#if USE_INTERP == 1
			lp = INTERP(op, lp,(ad*Theta));
			lq = INTERP(oq, lq,(ad*Theta));	

#endif //USE_INTERP
#define Tau (tp)
      B = ad*Inv_area;

      R = d*FFact;

      ABSF(abs_lq, lq);
      Cp = lp+lq*(B-R*abs_lq);
      Cv = (Tau*Tau)*Cvp;//Use tp for valve position
		
      asm volatile ("sqts %[out], %[in]\n\t": [out]"=f"(oq): [in]"f"((Cv*Cv*B*B)+(2*Cp*Cv)));
      oq = oq-Cv*B;
      op = Cp-oq*B;
#endif //EP_TYPE == VALVE

#if EP_TYPE == PIPE_T
#if USE_INTERP == 1
			lp = INTERP(op, lp,(ad*Theta));
			lq = INTERP(oq, lq,(ad*Theta));	
			rp = INTERP(op, rp,(ad*Theta));
			rq = INTERP(oq, rq,(ad*Theta));
			tp = INTERP(op, tp,(ad*Theta));
			tq = INTERP(oq, tq,(ad*Theta));
#endif //USE_INTERP
			B = ad*Inv_area;
			Br = ad*Inv_area2;
			Bt = ad*Inv_area3;
			R = d*FFact;
			ABSF(abs_lq,lq);
			ABSF(abs_rq,rq);
			ABSF(abs_tq,tq);
			Cp = lp+lq*(B-R*abs_lq);
			Cmr = rp-rq*(Br-R*abs_rq);
			Cmt = tp-tq*(Bt-R*abs_tq);
			Inv_Bl = 1/B;
			Inv_Br = 1/Br;
			Inv_Bt = 1/Bt;
			CpInv_Bl = Cp*Inv_Bl;
			CmrInv_Br = Cmr*Inv_Br;
			CmtInv_Bt = Cmr*Inv_Bt;
			op = (CpInv_Bl + CmrInv_Br + CmtInv_Bt)/(Inv_Bl + Inv_Br + Inv_Bt);
			lq = CpInv_Bl - op*Inv_Bl;
			rq = CmrInv_Br - op*Inv_Br;
			tq = CmrInv_Bt - op*Inv_Bt;
#endif //EP_TYPE == PIPE_T

      DELAY_UNTIL(read_nsec, read_sec);
      //Delay until WRITE_COMPLETE_TIMESTEP clocks before the end of this timestep before 
      //writing outputs

      //Publish Data
#ifdef OUTPUT_LCORENUM
      OLP  = op;
      OLQ  = oq;
#endif
#ifdef OUTPUT_RCORENUM
      ORP  = op;
      ORQ  = oq;
#endif

#ifdef OUTPUT_TCORENUM
      OTP  = op;
      OTQ  = oq;
#endif
    DELAY_UNTIL(nsec, sec);
    SET_TIME(CYCLE_PERIOD, 0, nsec, sec);

    }
}


