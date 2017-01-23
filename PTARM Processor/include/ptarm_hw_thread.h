// This file defines macros for managing the PTARM hardware threads.

#ifndef PTARM_HW_THREAD_H
#define PTARM_HW_THREAD_H


//======================================================================
// PTARM hardware thread macros.
//======================================================================

// Gets the ID of the current PTARM hardware thread.
#define PTARM_THREAD_GET_ID(threadId)			\
	asm volatile ("cdp p13, 0, cr7, cr0, cr0\n"	\
				  "mov %[id], r7"				\
		: [id]"=r"(threadId)					\
		:										\
		: "r7"									\
	)


// Gets the Saved Processor Status Register (SPSR) of the current PTARM hardware thread.
// 20 bits long.
#define PTARM_THREAD_GET_SPSR(spsr)				\
	asm volatile ("cdp p12, 0, cr7, cr0, cr0\n"	\
				  "mov %[spsrReg], r7"			\
		: [spsrReg]"=r"(spsr)					\
		:										\
		: "r7"									\
	)


// Gets the Current Processor Status Register (CPSR) of the current PTARM hardware thread.
// 20 bits long.
#define PTARM_THREAD_GET_CPSR(cpsr)				\
	asm volatile ("cdp p12, 1, cr7, cr0, cr0\n"	\
				  "mov %[cpsrReg], r7"			\
		: [cpsrReg]"=r"(cpsr)					\
		:										\
		: "r7"									\
	)


// Sets the Current Processor Status Register (CPSR) of the current PTARM hardware thread.
// 20 bits long.
#define PTARM_THREAD_SET_CPSR(cpsr)				\
	asm volatile ("mov r8, %[cpsrReg]\n"		\
				  "cdp p12, 2, cr0, cr0, cr8"	\
		:										\
		: [cpsrReg]"r"(cpsr)					\
		: "r8"									\
	)
	

// Goes to a label if the PTARM hardware thread's ID matches.
#define PTARM_THREAD_COND_GOTO(threadId, label)			\
	asm volatile goto ("cdp p13, 0, cr7, cr0, cr0\n"	\
					   "cmp r7, %0 \n"					\
					   "beq %l["#label"]"				\
		:												\
		: "r"(threadId)									\
		: "r7"											\
		: label											\
	)


// Go to a label.
#define PTARM_GOTO(label)						\
	asm volatile goto ("b %l["#label"]"			\
		:										\
		:										\
		:										\
		: label									\
	)


// 32-bit unsigned integer division.
// quotient = dividend / divisor
#define PTARM_UNSIGNED_DIV(quotient, dividend, divisor)			\
	asm volatile ("mov r7, %[dividendReg]\n"					\
				  "mov r8, %[divisorReg]\n"						\
				  "cdp p9, 0, cr6, cr7, cr8\n"					\
				  "mov %[quotientReg], r6"						\
		: [quotientReg]"=r"(quotient)							\
		: [dividendReg]"r"(dividend), [divisorReg]"r"(divisor)	\
		: "r6", "r7", "r8"										\
	)


#endif /* PTARM_HW_THREAD_H */

