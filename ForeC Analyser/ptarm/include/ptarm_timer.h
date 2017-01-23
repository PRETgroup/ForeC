#ifndef PTARM_TIMER_H
#define PTARM_TIMER_H

//======================================================================
// Timer variable.
//======================================================================

// Unsigned 64 bit timer variable.
typedef struct {
	unsigned int msb;
	unsigned int lsb;
} Timer64Bit;


//======================================================================
// General timer macros.
//======================================================================

// Get the current platform time as a 64 bit value.
#define PTARM_TIME_GET(time)							\
	asm volatile ("cdp p13, 8, cr0, cr7, cr8\n"			\
				  "mov %[msb], r7\n"					\
				  "mov %[lsb], r8"						\
		 : [msb]"=r"(time.msb), [lsb]"=r"(time.lsb)		\
		 : 												\
		 : "r7", "r8"									\
	)


// Unsigned subtraction between two 64 bit values, each represented as two 32 bit values.
// result = minuend - subtrahend, where minuend is assumed to be greater than subtrahend.
#define PTARM_DIFF(result, minuend, subtrahend)	\
	result.lsb = minuend.lsb - subtrahend.lsb;	\
	result.msb = minuend.msb - subtrahend.msb;	\
	if (minuend.lsb < subtrahend.lsb) {			\
		result.msb = result.msb - 1;			\
	}


// Unsigned addition between two 64 bit values, each represented as two 32 bit values.
// result = addend1 + addend2.
#define PTARM_ADD(result, addend1, addend2)						\
	asm volatile ("mov r7, %[msb1]\n"							\
				  "mov r8, %[lsb1]\n"							\
				  "adds r8, r8, %[lsb2]\n"						\
				  "adc r7, r7, %[msb2]\n"						\
				  "mov %[msb3], r7\n"							\
				  "mov %[lsb3], r8"								\
		: [msb3]"=r"(result.msb), [lsb3]"=r"(result.lsb)		\
		: [msb1]"r"(addend1.msb), [lsb1]"r"(addend1.lsb),		\
		  [msb2]"r"(addend2.msb), [lsb2]"r"(addend2.lsb)		\
		: "r7", "r8"											\
	)


//======================================================================
// Delay macros.
//======================================================================

// Delay execution to an absolute timestamp
// (in nanoseconds represented as a 64 bit value).
#define PTARM_DELAY(timestamp)									\
	asm volatile ("mov r7, %[msb1]\n"							\
				  "mov r8, %[lsb1]\n"							\
				  "cdp p13, 4, cr7, cr7, cr8"					\
		:														\
		: [msb1]"r"(timestamp.msb), [lsb1]"r"(timestamp.lsb)	\
		: "r7", "r8"											\
	)


//======================================================================
// Exception on Expire macros.
//======================================================================

// Variable whose address is at start of the Expire on Exception handler table.
// Defined by the linker script.
extern unsigned int eoe_table;

#define PTARM_EOE_SET_HANDLER(ptarmThreadId, address)	\
	(&eoe_table)[ptarmThreadId] = (unsigned int)address


#define PTARM_EOE_DISABLE()								\
	asm volatile ("cdp p13, 3, cr0, cr0, cr0")


// Set an exception to occur at an absolute timestamp
// (in nanoseconds represented as a 64 bit value).
#define PTARM_EOE_ENABLE(duration, start)						\
	asm volatile ("mov r7, %[msb1]\n"							\
				  "mov r8, %[lsb1]\n"							\
				  "adds r8, r8, %[lsb2]\n"						\
				  "adc r7, r7, %[msb2]\n"						\
				  "cdp p13, 2, cr7, cr7, cr8"					\
		:														\
		: [msb1]"r"(start.msb), [lsb1]"r"(start.lsb),			\
		  [msb2]"r"(duration.msb), [lsb2]"r"(duration.lsb)		\
		: "r7", "r8"											\
	)


#endif /* PTARM_TIMER_H */

