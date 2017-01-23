#ifndef _DEADLINE_H_
#define _DEADLINE_H_


//int PTARM_DEADLINE_NSEC_REG;
//int PTARM_DEADLINE_SEC_REG;

// DEFINE DEADELINE REGISTERS TO BE R7, R8 FOR NOW
#define SET_TIME( t_ns, t_s, r_ns, r_s)			       \
   asm volatile ("mov r7, %[nsec64]\n\t"\
		 "mov r8, %[nsec]\n\t"			\
		 "cdp p13, 9, cr7, cr7, cr8, 0\n\t"	\
		 "mov %[nsec_result], r7\n\t"\
		 "mov %[nsec64_result], r8\n\t"\
		 : [nsec_result]"=l"(r_ns), [nsec64_result]"=l"(r_s)	\
		 : [nsec64]"l" (t_s), [nsec]"l" (t_ns)			\
		 : "r7", "r8"						\
		 );

#define DELAY_UNTIL( ns, s )			       \
   asm volatile ("mov r7, %[sec]\n\t"\
		 "mov r8, %[nsec]\n\t"			\
		 "cdp p13, 4, cr7, cr7, cr8, 0\n\t"	\
		 : 	\
		 : [sec]"l" (s), [nsec]"l" (ns)			\
		 : "r7", "r8"						\
		 );



// Nanoseconds deadline instructions uses r2
// Seconds deadline instruction uses r1

/* #define DEADLOAD_NSEC( nsec_reg )                        \  */
/* asm volatile (".word 0xee111d00;  \ */
/*                mov %0, %%r1;"                   \ */
/* 	      : "=r" (nsec_reg)	  \ */
/* 	      : /\* no inputs  *\/		  \ */
/* 	      : "r1"); */

/* #define DEADLOAD_SEC( sec_reg )                           \  */
/* asm volatile (".word 0xee522d00;  \ */
/*                mov %0, %%r2;"                   \ */
/* 	      : "=r" (sec_reg)	  \ */
/* 	      : /\* no inputs  *\/		  \ */
/* 	      : "r2"); */


/* #define DEAD_NSEC                           \  */
/* asm volatile (".word 0xee011d00;"  \ */
/* 	      : /\* no outputs *\/                  \ */
/* 	      : /\* no inputs  *\/		  \ */
/* 	      : "r1"); */

/* #define DEAD_SEC                           \  */
/* asm volatile (".word 0xee422d00;"  \ */
/* 	      : /\* no outputs *\/                  \ */
/* 	      : /\* no inputs  *\/		  \ */
/* 	      : "r2"); */


/* #define DEADLINE_INIT( sec_reg, nsec_reg )	\ */
/*   DEADLOAD_NSEC(nsec_reg)			\ */
/*   DEADLOAD_SEC(sec_reg) */


/* #define DEADLINE( sec_reg, nsec_reg, SECOND, NANOSEC )	\ */
/*   asm volatile ("mov %%r1, %5;        \ */
/*                 mov %%r2, %6;         \ */
/*                 add %%r2, %%r2, %2;   \ */
/* 		add %%r1, %%r1, %3;   \ */
/* 		cmp %%r1, %4;         \ */
/*                 addge %%r2, %%r2, #1; \ */
/*                 subge %%r1, %%r1, %4; \ */
/*                 .word 0xee422d00;     \ */
/*                 .word 0xee011d00;     \ */
/*                 mov %0, %%r1;     \ */
/*                 mov %1, %%r2;"     \ */
/* 		: "=r"(nsec_reg), "=r"(sec_reg)	 \ */
/* 		: "r" (SECOND), "r"(NANOSEC), "r"(1000000000), "r"(nsec_reg), "r"(sec_reg) \ */
/* 		: "r1", "r2", "r3"); */

#endif
