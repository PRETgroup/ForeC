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
#define PTARM_GOTO(label)					\
	asm volatile goto ("b %l["#label"]"	\
		: 									\
		:									\
		:									\
		: label								\
	)

#endif /* PTARM_HW_THREAD_H */

