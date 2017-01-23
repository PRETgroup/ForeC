# 1 "foremc.c"
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/programs/foremc//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "foremc.c"
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_types.h" 1
// This file defines some useful data types.





//======================================================================
// PTARM types.
//======================================================================

// Prototypes of data structures.
struct _Task; // Defined in ptarm_task.h
struct _LocalScheduler; // Defined in ptarm_scheduler.h
struct _Timer64Bit; // Defined in ptarm_timer.h
struct _ForeMc_100int; // Defined in ptarm_foremc.h

// Boolean
typedef enum {
 false = 0,
 true = 1
} bool;

// Null value.


// Time units.
# 2 "foremc.c" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_hw_thread.h" 1
// This file defines macros for managing the PTARM hardware threads.





//======================================================================
// PTARM hardware thread macros.
//======================================================================

// Gets the ID of the current PTARM hardware thread.
# 21 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_hw_thread.h"
// Gets the Saved Processor Status Register (SPSR) of the current PTARM hardware thread.
// 20 bits long.
# 32 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_hw_thread.h"
// Gets the Current Processor Status Register (CPSR) of the current PTARM hardware thread.
// 20 bits long.
# 43 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_hw_thread.h"
// Sets the Current Processor Status Register (CPSR) of the current PTARM hardware thread.
// 20 bits long.
# 54 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_hw_thread.h"
// Goes to a label if the PTARM hardware thread's ID matches.
# 66 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_hw_thread.h"
// Go to a label.
# 76 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_hw_thread.h"
// 32-bit unsigned integer division.
// quotient = dividend / divisor
# 3 "foremc.c" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_io.h" 1
// This file defines macros for reading and writing to registers and memory mapped IO.




# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_types.h" 1
// This file defines some useful data types.
# 7 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_io.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_mutex.h" 1
// This file defines macros for a mutex.





//======================================================================
// PTARM mutex macros.
//======================================================================

// Acquire the mutex. Only one mutex can be acquired.




// Release the mutex. Only the acquirer can release the mutex.
# 8 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_io.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_hw_thread.h" 1
// This file defines macros for managing the PTARM hardware threads.
# 9 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_io.h" 2


//======================================================================
// PTARM memory mapped I/O base addresses.
//======================================================================
# 41 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_io.h"
//======================================================================
// PTARM register macros.
//======================================================================

// Stores the value of a register into a variable.
# 54 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_io.h"
//======================================================================
// PTARM Switch and Key Input functions.
//======================================================================

// Reads the 18 switches into a variable




// Reads the 4 keys into a variable




//======================================================================
// PTARM LED functions.
//======================================================================

// Outputs bit patterns to the green or red LEDs.




// Outputs a bit pattern to an LED base address. Not a thread-safe function.
void ptarmLedOutput(const unsigned int LedBaseAddress, const unsigned int bitPattern, const unsigned int mask) {
 // Memory mapped address for the LEDs.
 register unsigned int * const ptarmLed = (unsigned int * const) LedBaseAddress;
 *ptarmLed = mask & bitPattern;
}


//======================================================================
// PTARM 7-Segment display functions.
//======================================================================

// Maps lowercase characters to their 7-Segment bit patterns.
//								 0	   1     2     3     4     5     6	   7	 8	   9	 A	   B	 C	   D	 E	   F
const unsigned char hexMap[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0E};


// Outputs a bit pattern to a 7-segment display. Not a thread-safe function.
void ptarmSevenSegOutput(const unsigned int index, const unsigned int bitPattern) {
 // Memory mapped address for the 7-Segment.
 register unsigned char * const ptarmHex = (unsigned char * const) (0xFFFFFF20 + (0x08 * index));
 *ptarmHex = 0x007F & bitPattern;
}


// Outputs a hexidecimal number to a 7-segment display. Not a thread-safe function.
void ptarmSevenSegChar(const unsigned int index, const unsigned char character) {
 register unsigned int bitPattern = 0x7F;
 if ('/' < character && character < ':') {
  // 0 - 9
  bitPattern = hexMap[character - '0' ];
 } else if ('@' < character && character < 'G') {
  // A - F
  bitPattern = hexMap[character - 0x37];
 }

 ptarmSevenSegOutput(index, bitPattern);
}


//======================================================================
// PTARM LCD display functions.
//======================================================================

// Track the number of characters that have been written to the LCD display.
unsigned short int ptarmLcdCharCount = 0;


// Output a command or datum to the LCD display.



// Useful LCD commands.







// Outputs a command or datum to the LCD display. Not a thread-safe function.
void ptarmLcdOutput(const unsigned int bitPattern, const unsigned int isData, const unsigned int delay) {
 // Memory mapped addresses for the LCD.
 register unsigned int * const ptarmLcd = (unsigned int * const) 0xFFFFFF60;
 *ptarmLcd = 0x0FFF & (0x0800 | isData | 0x0100 | bitPattern);

 int i = delay;
 while(--i);

 *ptarmLcd = 0x0FFF & (0x0100 | bitPattern);
}


// Initialises the LCD display. Not a thread-safe function.
void ptarmLcdInit(void) {
 ptarmLcdCharCount = 0;

 // Function set to 8-bits and 2 lines
 ptarmLcdOutput(0x0038, 0x0, 30000);

 // Turn on the display and turn off the cursor
 ptarmLcdOutput(0x000C, 0x0, 26000);
}


// Outputs a string to the LCD display. Not a thread-safe function.
void ptarmLcdOutputStr(const char *str) {
 while (*str != 0) {
  // Check for the newline character
  if (*str == '\n') {
   ptarmLcdCharCount = (1 + (ptarmLcdCharCount > 15)) * 15;
  } else {
   ptarmLcdOutput(*str, 0x0400, 80);
   ptarmLcdCharCount++;
  }
  str++;

  if (ptarmLcdCharCount == 15) {
   // Go to the second line.
   ptarmLcdOutput(0xC0, 0x0, 26000);
  } else if (ptarmLcdCharCount == (15 * 2)) {
   // Go back to the first line and don't output the remaining string.
   ptarmLcdOutput(0x80, 0x0, 26000);
   ptarmLcdCharCount = 0;
   break;
  }
 }
}


//======================================================================
// PTARM UART functions.
//======================================================================

// Use UART as the standard output.



// Output a character to UART. Not a thread-safe function.
void ptarmUartOutputChar(const char c) {
 // Memory mapped addresses for the UART.
 register char * const ptarUartCout = (char * const) 0xFFFF0008;
 register char * const ptarmUartDout = (char * const) 0xFFFF000C;

 while(*ptarUartCout != 0);
 *ptarmUartDout = c;
}


// Output a string to UART. Not a thread-safe function.
void ptarmUartOutputStr(const char *str) {
 while (*str != 0) {
  ptarmUartOutputChar(*str);
  str++;
 }
}


// Output a string to UART. Thread-safe function.






//======================================================================
// String functions.
//======================================================================

// String buffer to hold string representations of values.
char ptarmStringBuffer[12];


// Return a string representation of a signed integer value.
const char * itoa(const int n) {
 register int next = 0;
 register unsigned int number;

 if (n < 0) {
        ptarmStringBuffer[next++] = '-';
  number = -n;
 } else {
  number = n;
 }

 if (number == 0) {
  ptarmStringBuffer[next++] = '0';
 } else {
  register int flag = 0;
  register unsigned int k = 1000000000;
  while (k > 0) {
   register int r;
   asm volatile ("mov r7, %[dividendReg]\n" "mov r8, %[divisorReg]\n" "cdp p9, 0, cr6, cr7, cr8\n" "mov %[quotientReg], r6" : [quotientReg]"=r"(r) : [dividendReg]"r"(number), [divisorReg]"r"(k) : "r6", "r7", "r8" );
   if (flag || r > 0) {
    ptarmStringBuffer[next++] = '0' + r;
    flag = 1;
   }
   number -= r * k;
   register const unsigned int k1 = k;
   register const unsigned int ten = 10;
   asm volatile ("mov r7, %[dividendReg]\n" "mov r8, %[divisorReg]\n" "cdp p9, 0, cr6, cr7, cr8\n" "mov %[quotientReg], r6" : [quotientReg]"=r"(k) : [dividendReg]"r"(k1), [divisorReg]"r"(ten) : "r6", "r7", "r8" );
  }
 }

 ptarmStringBuffer[next] = 0;
 return ptarmStringBuffer;
}


// Return a string representation of an unsigned integer value.
const char * utoa(const unsigned int n) {
 register int next = 0;
 register unsigned int number = n;

 if (number == 0) {
  ptarmStringBuffer[next++] = '0';
 } else {
  register int flag = 0;
  register unsigned int k = 1000000000;
  while (k > 0) {
   register int r;
   asm volatile ("mov r7, %[dividendReg]\n" "mov r8, %[divisorReg]\n" "cdp p9, 0, cr6, cr7, cr8\n" "mov %[quotientReg], r6" : [quotientReg]"=r"(r) : [dividendReg]"r"(number), [divisorReg]"r"(k) : "r6", "r7", "r8" );
   if (flag || r > 0) {
    ptarmStringBuffer[next++] = '0' + r;
    flag = 1;
   }
   number -= r * k;
   register const unsigned int k1 = k;
   register const unsigned int ten = 10;
   asm volatile ("mov r7, %[dividendReg]\n" "mov r8, %[divisorReg]\n" "cdp p9, 0, cr6, cr7, cr8\n" "mov %[quotientReg], r6" : [quotientReg]"=r"(k) : [dividendReg]"r"(k1), [divisorReg]"r"(ten) : "r6", "r7", "r8" );
  }
 }

 ptarmStringBuffer[next] = 0;
 return ptarmStringBuffer;
}


// Return a string representation of an unsigned hexadecimal value.
const char * hex(const unsigned int number) {
 ptarmStringBuffer[0] = '0';
 ptarmStringBuffer[1] = 'x';
 register int i, k;
 for(i = 32-4, k = 2; i >= 0; i -= 4, k++) {
  register unsigned int a = (number >> i) & 0xf;
  if (a < 10) {
   ptarmStringBuffer[k] = a + '0';
  } else {
   ptarmStringBuffer[k] = a + 'a' - 10;
  }
 }

 ptarmStringBuffer[k] = 0;
 return ptarmStringBuffer;
}
# 4 "foremc.c" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_foremc.h" 1
// This file defines macros for managing the communication between multi-rate tasks.




# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_hw_thread.h" 1
// This file defines macros for managing the PTARM hardware threads.
# 7 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_foremc.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_timer.h" 1
// This file defines macros for querying the time, using timing instructions, and manipulating time values.





//======================================================================
// Timer variable.
//======================================================================

// Unsigned 64 bit timer variable.
// (in nanoseconds represented as a 64 bit value).
typedef struct {
 volatile signed int msb;
 volatile unsigned int lsb;
} Timer64Bit;


//======================================================================
// General timer macros.
//======================================================================

// Get the current platform time as a 64 bit value.
// (in nanoseconds represented as a 64 bit value).
# 35 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_timer.h"
// Unsigned subtraction between two 64 bit values, each represented as two 32 bit values.
// result = minuend - subtrahend, where minuend is assumed to be greater than subtrahend.
# 51 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_timer.h"
// Unsigned addition between two 64 bit values, each represented as two 32 bit values.
// result = addend1 + addend2.
# 67 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_timer.h"
//======================================================================
// Delay macros.
//======================================================================

// Delay execution to an absolute timestamp
// (in nanoseconds represented as a 64 bit value).
# 83 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_timer.h"
//======================================================================
// Exception on Expire macros.
//======================================================================

// Variable whose address is at start of the Expire on Exception handler table.
// Defined in the linker script.
extern unsigned int eoe_table;


// For a PTARM hardware thread, set its EOE handler address.




// For the executing PTARM hardware thread, disable its EOE.




// For the executing PTARM hardware thread, get the PC it was
// at when the EOE occured.
# 113 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_timer.h"
// Set an exception to occur at an absolute timestamp
// (in nanoseconds represented as a 64 bit value).
# 8 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_foremc.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h" 1
// This file defines macros for creating and manipulating tasks.




# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_types.h" 1
// This file defines some useful data types.
# 7 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_io.h" 1
// This file defines macros for reading and writing to registers and memory mapped IO.
# 8 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_timer.h" 1
// This file defines macros for querying the time, using timing instructions, and manipulating time values.
# 9 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h" 1
// This file defines macros for creating and managing static and dynamic task schedules.




# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_types.h" 1
// This file defines some useful data types.
# 7 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_io.h" 1
// This file defines macros for reading and writing to registers and memory mapped IO.
# 8 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_mutex.h" 1
// This file defines macros for a mutex.
# 9 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h" 1
// This file defines macros for creating and manipulating tasks.
# 10 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_timer.h" 1
// This file defines macros for querying the time, using timing instructions, and manipulating time values.
# 11 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_hw_thread.h" 1
// This file defines macros for managing the PTARM hardware threads.
# 12 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h" 2


//======================================================================
// PTARM scheduler variables.
//======================================================================

// Task states.
typedef enum {
 PTARM_SCHEDULER_RELEASE = 0,
 PTARM_SCHEDULER_STATIC = 1,
 PTARM_SCHEDULER_DYNAMIC = 2
} SchedulerPhase;


// Local scheduler control block.
// (For managing one hardware thread)
typedef struct _LocalScheduler {
 const char *name; // Name of this scheduler as a string.
 const unsigned int hwThreadId; // Hardware thread number that this scheduler manages.
 volatile unsigned int *fp; // Last location of this scheduler's stack pointer.
 volatile unsigned int *sp; // Last location of this scheduler's stack pointer.
 volatile unsigned int *pc; // Last location of this scheduler's program counter.
 volatile unsigned int *preemptedSp; // Last location of the preempted task's stack pointer.
 volatile unsigned int preemptedSpsr; // Saved Processor Status Register at the time of preemption.

 volatile struct _Task *const *staticSchedule; // Static schedule of tasks. Pointer to constant pointers to tasks.
 volatile struct _Task *currentTask; // Current task to execute.
 volatile struct _Task *const *nextStaticTask; // Next statically scheduled task to execute.

 volatile SchedulerPhase phase; // Phase of the scheduling (static or dynamic).

 volatile Timer64Bit basePeriodStart; // Timestamp of the start of the base period.
 volatile unsigned int basePeriodCounter; // Number of base periods already executed.

 volatile Timer64Bit basePeriodStartOverhead; // Worst-case scheduling overhead time in nanoseconds.
 volatile Timer64Bit basePeriodEndOverhead; // Worst-case scheduling overhead time in nanoseconds.
 volatile Timer64Bit basePeriodStartAfterOverhead; // Absolute starting time of the static scheduling phase.
 volatile Timer64Bit basePeriodMinusEndingOverhead; // Duration of one base period minus the ending overhead in nanoseconds.

 volatile Timer64Bit currentTime; // Variable to help compute the current physical time.
 volatile Timer64Bit elapsedTime; // Variable to help compute the elapsed physical time.
} LocalScheduler;


// Global scheduler control block.
// (For managing all the local schedulers, i.e., hardware threads.)
typedef struct {
 volatile bool isInitialised; // Program has been initialised for execution.

 const Timer64Bit basePeriodDuration; // Duration of one base period in nanoseconds.
 volatile Timer64Bit basePeriodFirstStart; // Timestamp of the start of the first base period only.

 // Pointers to the local schedulers of each hardware thread.
 volatile LocalScheduler *localScheduler0;
 volatile LocalScheduler *localScheduler1;
 volatile LocalScheduler *localScheduler2;
 volatile LocalScheduler *localScheduler3;

 // Priority queues for dynamic scheduling.
 volatile struct _Task **priorityQueueNonCritical; // Non-critical tasks.
 volatile struct _Task **priorityQueueMission; // Mission critical tasks.
 volatile struct _Task **priorityQueueLife; // Life critical tasks.

 // Index of the last task of each priority queue. -1 = empty.
 volatile int counterNonCritical; // Non-critical tasks.
 volatile int counterMission; // Mission critical tasks.
 volatile int counterLife; // Life critical tasks.
} GlobalScheduler;


//======================================================================
// PTARM scheduler macros.
//======================================================================

// Save the stack pointer, frame pointer, and program counter of the current scheduler.
# 97 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h"
// Restore the stack and frame pointer of a scheduler.
# 107 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h"
// Create a local scheduler for a hardware thread. Uses the hardware thread's stack.
# 134 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h"
 /*

	// Scheduler = xxx, SP = xxx, PC = xxx, hwThreadId = xxx.

	PTARM_MUTEX_LOCK();

	printf("Scheduler = "); printf(localScheduler->name);

	printf(", SP = "); printf(hex((unsigned int)localScheduler->sp));

	printf(", PC = "); printf(hex((unsigned int)localScheduler->pc));

	printf(", hwThreadId = "); printf(utoa(localScheduler->hwThreadId));

	printf(".\n");

	PTARM_MUTEX_UNLOCK();

	*/
# 145 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h"
// Inserts a life or mission critical task into the global priority queue.
# 156 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h"
// Inserts a non-critical task into the global priority queue.
# 180 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h"
// Finds a task from the global priority queues.
# 196 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h"
// Reset the global priority queue.
# 10 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_hw_thread.h" 1
// This file defines macros for managing the PTARM hardware threads.
# 11 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_foremc.h" 1
// This file defines macros for managing the communication between multi-rate tasks.
# 12 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h" 2


//======================================================================
// PTARM task variables.
//======================================================================

// Task states.
typedef enum {
 PTARM_TASK_PAUSED = 0,
 PTARM_TASK_PREEMPTED = 1,
 PTARM_TASK_RELEASED = 2
} TaskState;


// Task criticalities.
typedef enum {
 PTARM_TASK_LIFE = 0,
 PTARM_TASK_MISSION = 1,
 PTARM_TASK_NONCRITICAL = 2
} TaskCriticality;


// Task control block.
typedef struct _Task {
 const char *name; // Name of this task as a string.
 const TaskCriticality criticality; // Criticality of this task.
 volatile struct _LocalScheduler *localScheduler; // Reference to the local scheduler that is currently executing this task.
 volatile TaskState state; // Execution state of this task.
 volatile unsigned int *sp; // Last location of its stack pointer.
 volatile unsigned int spsr; // Saved Processor Status Register at the time of preemption.
 /*

	 ->|      |<-- allocatedTime



	   .------.----.--------.---------.

	   | task |    |        |         | slack

	   |--------------------------------------|

				   Base period					*/
# 50 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h"
 const Timer64Bit allocatedTime; // Statically allocated execution time in each base period.
 const unsigned int basePeriodsMin; // Minimum number of base periods between each release time.
 volatile unsigned int lastRelease; // The base period of its last release.
 volatile unsigned int earliestRelease; // The next earliest release time.

 volatile struct _ForeMc_100int *receiveBuffers[10]; // List of receive buffers.
} Task;


// Variable whose address is at the end of the program binary.
// Defined in the linker script.
extern unsigned int addr_stack_limit;


// Variable whose address is at the end of the PTARM hardware threads' stacks.
// Defined in the linker script.
extern unsigned int addr_stack_end;


// Location of the next free location to begin a new task stack.
unsigned int *ptarmPreviousTaskStackEnd = &addr_stack_end;


//======================================================================
// PTARM task macros.
//======================================================================

// Creates a stack for a task.
// A stack begins (at a higher memory address) with a stack frame followed
// by (at a lower memory address) a stack.
// Due to the way the SP is restored, the task's context is stored after
// the task's stack frame.
// frameSize: size of the task's frame to hold just its local variables.
//            (function calls use the space after the stack frame)
//
//
//                ________________  <-- End of the stack determined by the ptarmCreateTask macro.
// Lower memory  |                |
// address       |                | <-- sp2
//               |__init_context__| <-- sp1 (ptarmPreviousTaskStackEnd - frameSize)
// Higher memory |                |
// address       |__task's frame__| <-- fp1 (ptarmPreviousTaskStackEnd)
//
//                A task's stack
# 129 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h"
// Stores the value of a stack element into a variable.
// PC offset = 56
# 139 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h"
// Stores the value of a variable into a stack element.
// PC offset = 56
# 149 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h"
// Save the context of the current task.
# 166 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h"
// Save the context of the preempted task.
// (Only used by the exception handler)
# 185 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h"
// Assign a saved context to a task.





// Restore the context of a task.
# 204 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h"
// Set the current scheduler to the new scheduler.






//======================================================================
// PTARM task function.
//======================================================================

// Create a task. Checks that there will be enough memory.
// Thread-safe function.
void ptarmCreateTask(volatile Task *task, unsigned int *startPc, volatile LocalScheduler *localScheduler) {
 asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
 const unsigned int frameSize = 0x0100;
 const unsigned int limit = 0x0200; // 0x0200 * sizeof(unsigned int) byte sized stack.

 // Check that there is enough memory to create a task stack.
 if ((ptarmPreviousTaskStackEnd - &addr_stack_limit) < limit) {
  ptarmUartOutputStr("PTARM_TASK_CREATE: Stack limit exceeded!\n");
  ptarmUartOutputStr("  Available amount: ");
  ptarmUartOutputStr(utoa((ptarmPreviousTaskStackEnd - &addr_stack_limit)*sizeof(unsigned int)));
  ptarmUartOutputStr(" bytes.\n");
  ptarmUartOutputStr("  Requested amount: ");
  ptarmUartOutputStr(utoa(limit*sizeof(unsigned int)));
  ptarmUartOutputStr(" bytes.\n");
  while(1);
 }

 // Create a stack for the task.
 asm volatile ("mov r8, sp\n" /* Save SP of current task*/ "mov sp, %[sp1]\n" /* Set new SP */ "mov r9, %[fp1]\n" /* Set new FP */ /* Initialise task context */ "mov r7, %[pc1] \n" "push {r7}\n" /*pc*/ "mov r7, #0\n" "push {r7}\n" /*ip*/ "push {r9}\n" /*fp*/ "push {r7}\n" /*sl*/ "push {r7}\n" /*r9*/ "push {r7}\n" /*r8*/ "push {r7}\n" /*r7*/ "push {r7}\n" /*r6*/ "push {r7}\n" /*r5*/ "push {r7}\n" /*r4*/ "push {r7}\n" /*r3*/ "push {r7}\n" /*r2*/ "push {r7}\n" /*r1*/ "push {r7}\n" /*r0*/ "push {r7}\n" /*r14*/ "mov %[sp2], sp\n" /* Save SP */ "mov sp, r8" /* Restore SP of current task */ : [sp2]"=r"((task)->sp) : [pc1]"r"(startPc), [sp1]"r"(ptarmPreviousTaskStackEnd - frameSize), [fp1]"r"(ptarmPreviousTaskStackEnd) : "r7","r8", "r9" );

 // Update where the last stack frame ends.
 ptarmPreviousTaskStackEnd = ptarmPreviousTaskStackEnd - limit;

 // Initialise the SPSR of the task.
 task->spsr = 0;

 // Initialise the static and current local schedulers.
 task->localScheduler = localScheduler;

 /*

	// Task = xxx, FP = xxx, SP = xxx, PC = xxx.

	printf("Task = "); printf(task->name);

	printf(", FP = "); printf(hex(stackFrameStart));

	printf(", SP = "); printf(hex((unsigned int)(task->sp)));

	printf(", PC = "); printf(hex(task->sp[14]));

	printf(".\n");

	*/
# 254 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h"
 asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
}
# 9 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_foremc.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h" 1
// This file defines macros for creating and managing static and dynamic task schedules.
# 10 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_foremc.h" 2


//======================================================================
// ForeMC buffers.
//======================================================================

// Buffer type.
# 32 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_foremc.h"
// Pre-defined buffer type.


typedef struct _ForeMc_100int {
 volatile int data[100];
 volatile int rFirst;
 volatile int rCount;
 volatile int wFirst;
 volatile int wCount;
 const int maxSize;
} ForeMc_100int;


// Get the number of buffered elements thta can be read.




// Read a buffer at a given index, i.e., buffer[index]






// Returns 0 <= index <= count for a given index.
// If index is -1, then the last (latest) data index is returned.
# 69 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_foremc.h"
// Maps the index of the buffer array to the index of the circular buffer.
const unsigned int foreMcGetIndex(const unsigned int indexPlusFirst, const unsigned int maxSize) {
 unsigned int quotient;
 asm volatile ("mov r7, %[dividendReg]\n" "mov r8, %[divisorReg]\n" "cdp p9, 0, cr6, cr7, cr8\n" "mov %[quotientReg], r6" : [quotientReg]"=r"(quotient) : [dividendReg]"r"(indexPlusFirst), [divisorReg]"r"(maxSize) : "r6", "r7", "r8" );
 return (indexPlusFirst) - (quotient * maxSize);
}


// Place data into the circular buffer.





// Updates the circular buffer when the receiving task is released.
# 97 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_foremc.h"
//======================================================================
// ForeMC macros.
//======================================================================

// Pause the task execution.
# 113 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_foremc.h"
// Pause the task execution and buffer the output variable.
# 5 "foremc.c" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_timer.h" 1
// This file defines macros for querying the time, using timing instructions, and manipulating time values.
# 6 "foremc.c" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h" 1
// This file defines macros for creating and manipulating tasks.
# 7 "foremc.c" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h" 1
// This file defines macros for creating and managing static and dynamic task schedules.
# 8 "foremc.c" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_mutex.h" 1
// This file defines macros for a mutex.
# 9 "foremc.c" 2


volatile const bool halt = true;
volatile const bool loopForever = true;


// Tasks (structure defined in ptarm_task.h).
// Life critical
volatile Task l1 = {.name = "l1", .receiveBuffers = { 0 }, .criticality = PTARM_TASK_LIFE, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500*1000u*1000u*1u}, .basePeriodsMin = 4, .lastRelease = 0, .earliestRelease = 0};
volatile Task l2 = {.name = "l2", .receiveBuffers = { 0 }, .criticality = PTARM_TASK_LIFE, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500*1000u*1000u*1u}, .basePeriodsMin = 4, .lastRelease = 0, .earliestRelease = 0};
volatile Task l3 = {.name = "l3", .receiveBuffers = { 0 }, .criticality = PTARM_TASK_LIFE, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500*1000u*1000u*1u}, .basePeriodsMin = 4, .lastRelease = 0, .earliestRelease = 0};
volatile Task l4 = {.name = "l4", .receiveBuffers = { 0 }, .criticality = PTARM_TASK_LIFE, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500*1000u*1000u*1u}, .basePeriodsMin = 4, .lastRelease = 0, .earliestRelease = 0};

// Mission critical
volatile Task m1 = {.name = "m1", .receiveBuffers = { 0 }, .criticality = PTARM_TASK_MISSION, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500*1000u*1000u*1u}, .basePeriodsMin = 8, .lastRelease = 0, .earliestRelease = 0};
volatile Task m2 = {.name = "m2", .receiveBuffers = { 0 }, .criticality = PTARM_TASK_MISSION, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500*1000u*1000u*1u}, .basePeriodsMin = 7, .lastRelease = 0, .earliestRelease = 0};
volatile Task m3 = {.name = "m3", .receiveBuffers = { 0 }, .criticality = PTARM_TASK_MISSION, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500*1000u*1000u*1u}, .basePeriodsMin = 8, .lastRelease = 0, .earliestRelease = 0};
volatile Task m4 = {.name = "m4", .receiveBuffers = { 0 }, .criticality = PTARM_TASK_MISSION, .state = PTARM_TASK_PAUSED, .allocatedTime = {.msb = 0, .lsb = 500*1000u*1000u*1u}, .basePeriodsMin = 8, .lastRelease = 0, .earliestRelease = 0};

// Non-critical
volatile Task n1 = {.name = "n1", .receiveBuffers = { 0 }, .criticality = PTARM_TASK_NONCRITICAL, .state = PTARM_TASK_PAUSED, .basePeriodsMin = 8, .lastRelease = 0, .earliestRelease = 0};
volatile Task n2 = {.name = "n2", .receiveBuffers = { 0 }, .criticality = PTARM_TASK_NONCRITICAL, .state = PTARM_TASK_PAUSED, .basePeriodsMin = 8, .lastRelease = 0, .earliestRelease = 0};
volatile Task n3 = {.name = "n3", .receiveBuffers = { 0 }, .criticality = PTARM_TASK_NONCRITICAL, .state = PTARM_TASK_PAUSED, .basePeriodsMin = 8, .lastRelease = 0, .earliestRelease = 0};
volatile Task n4 = {.name = "n4", .receiveBuffers = { 0 }, .criticality = PTARM_TASK_NONCRITICAL, .state = PTARM_TASK_PAUSED, .basePeriodsMin = 8, .lastRelease = 0, .earliestRelease = 0};


// Buffers for mixed-criticality task communication (structure defined in ptarm_foremc.h).
volatile struct _ForeMc_100int bufferOne;


// Global scheduling information (structure defined in ptarm_scheduler.h).
volatile Task *priorityQueueNonCritical[20] = {0};
volatile Task *priorityQueueMission[20] = {0};
volatile Task *priorityQueueLife[20] = {0};
volatile GlobalScheduler globalScheduler = {
            .isInitialised = false,
            .basePeriodDuration = {.msb = 0, .lsb = 3*1000u*1000u*1000u*1u},
            .priorityQueueNonCritical = priorityQueueNonCritical,
            .priorityQueueMission = priorityQueueMission,
            .priorityQueueLife = priorityQueueLife,
            .counterNonCritical = -1,
            .counterMission = -1,
            .counterLife = -1
           };

// Main entry point of the program that is executed by all hardware threads.
int main(void) {
 // Create a local scheduler that uses the hardware thread's stack.
 /* Hardware thread number. */ unsigned int hwThreadId; asm volatile ("cdp p13, 0, cr7, cr0, cr0\n" "mov %[id], r7" : [id]"=r"(hwThreadId) : : "r7" ); /* Empty static schedule that holds up to five tasks */ volatile Task *staticSchedule[5] = { 0 }; /* Set the scheduler name. */ char localSchedulerName[11] = "scheduler "; localSchedulerName[9] = '0' + hwThreadId; /* Create local scheduler */ LocalScheduler localScheduler = { .name = localSchedulerName, .hwThreadId = hwThreadId, .staticSchedule = staticSchedule, .currentTask = staticSchedule[0], .nextStaticTask = staticSchedule, .phase = PTARM_SCHEDULER_RELEASE, .basePeriodCounter = 0 }; /* Initialise the context. */ asm volatile ("mov %[stack], sp\n" /* Save SP */ "mov %[frame], fp" /* Save FP */ : [stack]"=r"(localScheduler.sp), [frame]"=r"(localScheduler.fp) : : ); localScheduler.pc = &&localScheduler;

 // Each hardware thread performs some type of start up work.
 switch (localScheduler.hwThreadId) {
  case (0):; // Hardware thread 0.

     asm volatile("cdp p13, 1, cr0, cr7, cr0, 1"); ptarmUartOutputStr("ForeMC example.\n\n"); asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");

     // Create the non-critical tasks.
     ptarmCreateTask(&n1, &&n1, 0);
     ptarmCreateTask(&n2, &&n2, 0);
     ptarmCreateTask(&n3, &&n3, 0);
     ptarmCreateTask(&n4, &&n4, 0);

     // Create a static schedule for hardware thread 0.
     // [m1 -> l1]
     ptarmCreateTask(&m1, &&m1, &localScheduler);
     ptarmCreateTask(&l1, &&l1, &localScheduler);
     staticSchedule[0] = &m1;
     staticSchedule[1] = &l1;

     // Calculate the duration of the base period that can be used to execute tasks.
     localScheduler.basePeriodStartOverhead.msb = 0;
     localScheduler.basePeriodStartOverhead.lsb = 100*1000u*1000u*1u; // 0.1s
     localScheduler.basePeriodEndOverhead.msb = 0;
     localScheduler.basePeriodEndOverhead.lsb = 100*1000u*1000u*1u; // 0.1s
     asm volatile ("mov r7, %[msb1]\n" "mov r8, %[lsb1]\n" "subs r8, r8, %[lsb2]\n" "sbc r7, r7, %[msb2]\n" "mov %[msb3], r7\n" "mov %[lsb3], r8" : [msb3]"=r"(localScheduler.basePeriodMinusEndingOverhead.msb), [lsb3]"=r"(localScheduler.basePeriodMinusEndingOverhead.lsb) : [msb1]"r"(globalScheduler.basePeriodDuration.msb), [lsb1]"r"(globalScheduler.basePeriodDuration.lsb), [msb2]"r"(localScheduler.basePeriodEndOverhead.msb), [lsb2]"r"(localScheduler.basePeriodEndOverhead.lsb) : "r7", "r8" );

     globalScheduler.localScheduler0 = &localScheduler; // Set the global reference to the local scheduler.
     (&eoe_table)[localScheduler.hwThreadId] = (unsigned int)&&eoeHandler0; // Register the EOE handler.

     asm volatile ("cdp p13, 8, cr0, cr7, cr8\n" "mov %[msb], r7\n" "mov %[lsb], r8" : [msb]"=r"(globalScheduler.basePeriodFirstStart.msb), [lsb]"=r"(globalScheduler.basePeriodFirstStart.lsb) : : "r7", "r8" ); // Save the time stamp of the first base period.
     globalScheduler.isInitialised = true; // Initialisation complete.
     break;

  case (1): // Hardware thread 1.

     // Create a static schedule for hardware thread 1.
     // [m2 -> l2]
     ptarmCreateTask(&m2, &&m2, &localScheduler);
     ptarmCreateTask(&l2, &&l2, &localScheduler);
     staticSchedule[0] = &m2;
     staticSchedule[1] = &l2;

     // Associate tasks with receive buffers.
     m2.receiveBuffers[0] = &bufferOne;

     // Calculate the duration of the base period that can be used to execute tasks.
     localScheduler.basePeriodStartOverhead.msb = 0;
     localScheduler.basePeriodStartOverhead.lsb = 100*1000u*1000u*1u; // 0.1s
     localScheduler.basePeriodEndOverhead.msb = 0;
     localScheduler.basePeriodEndOverhead.lsb = 100*1000u*1000u*1u; // 0.1s
     asm volatile ("mov r7, %[msb1]\n" "mov r8, %[lsb1]\n" "subs r8, r8, %[lsb2]\n" "sbc r7, r7, %[msb2]\n" "mov %[msb3], r7\n" "mov %[lsb3], r8" : [msb3]"=r"(localScheduler.basePeriodMinusEndingOverhead.msb), [lsb3]"=r"(localScheduler.basePeriodMinusEndingOverhead.lsb) : [msb1]"r"(globalScheduler.basePeriodDuration.msb), [lsb1]"r"(globalScheduler.basePeriodDuration.lsb), [msb2]"r"(localScheduler.basePeriodEndOverhead.msb), [lsb2]"r"(localScheduler.basePeriodEndOverhead.lsb) : "r7", "r8" );

     globalScheduler.localScheduler1 = &localScheduler; // Set the global reference to the local scheduler.
     (&eoe_table)[localScheduler.hwThreadId] = (unsigned int)&&eoeHandler1; // Register the EOE handler.
     break;

  case (2): // Hardware thread 2.

     ptarmCreateTask(&l3, &&l3, &localScheduler);
     ptarmCreateTask(&l4, &&l4, &localScheduler);
     staticSchedule[0] = &l3;
     staticSchedule[1] = &l4;

     localScheduler.basePeriodStartOverhead.msb = 0;
     localScheduler.basePeriodStartOverhead.lsb = 100*1000u*1000u*1u; // 0.1s
     localScheduler.basePeriodEndOverhead.msb = 0;
     localScheduler.basePeriodEndOverhead.lsb = 100*1000u*1000u*1u; // 0.1s
     asm volatile ("mov r7, %[msb1]\n" "mov r8, %[lsb1]\n" "subs r8, r8, %[lsb2]\n" "sbc r7, r7, %[msb2]\n" "mov %[msb3], r7\n" "mov %[lsb3], r8" : [msb3]"=r"(localScheduler.basePeriodMinusEndingOverhead.msb), [lsb3]"=r"(localScheduler.basePeriodMinusEndingOverhead.lsb) : [msb1]"r"(globalScheduler.basePeriodDuration.msb), [lsb1]"r"(globalScheduler.basePeriodDuration.lsb), [msb2]"r"(localScheduler.basePeriodEndOverhead.msb), [lsb2]"r"(localScheduler.basePeriodEndOverhead.lsb) : "r7", "r8" );

     globalScheduler.localScheduler2 = &localScheduler;
     (&eoe_table)[localScheduler.hwThreadId] = (unsigned int)&&eoeHandler2;
     break;

  case (3): // Hardware thread 3.

     ptarmCreateTask(&m3, &&m3, &localScheduler);
     ptarmCreateTask(&m4, &&m4, &localScheduler);
     staticSchedule[0] = &m3;
     staticSchedule[1] = &m4;

     localScheduler.basePeriodStartOverhead.msb = 0;
     localScheduler.basePeriodStartOverhead.lsb = 100*1000u*1000u*1u; // 0.1s
     localScheduler.basePeriodEndOverhead.msb = 0;
     localScheduler.basePeriodEndOverhead.lsb = 100*1000u*1000u*1u; // 0.1s
     asm volatile ("mov r7, %[msb1]\n" "mov r8, %[lsb1]\n" "subs r8, r8, %[lsb2]\n" "sbc r7, r7, %[msb2]\n" "mov %[msb3], r7\n" "mov %[lsb3], r8" : [msb3]"=r"(localScheduler.basePeriodMinusEndingOverhead.msb), [lsb3]"=r"(localScheduler.basePeriodMinusEndingOverhead.lsb) : [msb1]"r"(globalScheduler.basePeriodDuration.msb), [lsb1]"r"(globalScheduler.basePeriodDuration.lsb), [msb2]"r"(localScheduler.basePeriodEndOverhead.msb), [lsb2]"r"(localScheduler.basePeriodEndOverhead.lsb) : "r7", "r8" );

     globalScheduler.localScheduler3 = &localScheduler;
     (&eoe_table)[localScheduler.hwThreadId] = (unsigned int)&&eoeHandler3;
     break;

  default: // Unknown hardware thread ID.

     asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
     ptarmUartOutputStr("!! Initialisation error: Unknown hwThreadId = "); ptarmUartOutputStr(utoa(localScheduler.hwThreadId)); ptarmUartOutputStr("\n");
     asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
     while (halt);
     break;
 }

 // All hardware threads execute this.
 while(globalScheduler.isInitialised == false);
 localScheduler.basePeriodStart = globalScheduler.basePeriodFirstStart;
 asm volatile goto ("b %l[""localScheduler""]" : : : : localScheduler );


// The registered EOE handler of each hardware thread.
// An exception can occur during the execution of any task (or scheduler). When
// an exception does occur, the registered EOE handler is called. We cannot immediately
// query what task was preempted because that will cause some registers to
// be overwritten. Hence, we save the task's context anonymously before querying
// what task was preempted so that the saved context can be assigned to the correct task.

// For hardware thread 0.
eoeHandler0: {
 // Save the context of the preempted (anonymous) task and then restore the scheduler's context
 // to query which task was preempted.
 asm volatile ("nop\n" "pop {lr}\n" "push {r0}\n" /* PC placeholder */ "push {r0-r12}\n" "push {r14}" ); asm volatile ("cdp p13, 9, cr7, cr0, cr0\n" "str r7, [sp, #56]\n" /* Save PC */ "mov %[stack], sp" /* Save SP */ : [stack]"=r"((globalScheduler.localScheduler0)->preemptedSp) : : "r7" ); asm volatile ("cdp p12, 0, cr7, cr0, cr0\n" "mov %[spsrReg], r7" : [spsrReg]"=r"((globalScheduler.localScheduler0)->preemptedSpsr) : : "r7" );
 asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "mov fp, %[frame]" /* Restore FP */ : : [stack]"r"(globalScheduler.localScheduler0->sp), [frame]"r"(globalScheduler.localScheduler0->fp) : );
 asm volatile goto ("b %l[""eoeHandler""]" : : : : eoeHandler );
}

// For hardware thread 1.
eoeHandler1: {
 asm volatile ("nop\n" "pop {lr}\n" "push {r0}\n" /* PC placeholder */ "push {r0-r12}\n" "push {r14}" ); asm volatile ("cdp p13, 9, cr7, cr0, cr0\n" "str r7, [sp, #56]\n" /* Save PC */ "mov %[stack], sp" /* Save SP */ : [stack]"=r"((globalScheduler.localScheduler1)->preemptedSp) : : "r7" ); asm volatile ("cdp p12, 0, cr7, cr0, cr0\n" "mov %[spsrReg], r7" : [spsrReg]"=r"((globalScheduler.localScheduler1)->preemptedSpsr) : : "r7" );
 asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "mov fp, %[frame]" /* Restore FP */ : : [stack]"r"(globalScheduler.localScheduler1->sp), [frame]"r"(globalScheduler.localScheduler1->fp) : );
 asm volatile goto ("b %l[""eoeHandler""]" : : : : eoeHandler );
}

// For hardware thread 2.
eoeHandler2: {
 asm volatile ("nop\n" "pop {lr}\n" "push {r0}\n" /* PC placeholder */ "push {r0-r12}\n" "push {r14}" ); asm volatile ("cdp p13, 9, cr7, cr0, cr0\n" "str r7, [sp, #56]\n" /* Save PC */ "mov %[stack], sp" /* Save SP */ : [stack]"=r"((globalScheduler.localScheduler2)->preemptedSp) : : "r7" ); asm volatile ("cdp p12, 0, cr7, cr0, cr0\n" "mov %[spsrReg], r7" : [spsrReg]"=r"((globalScheduler.localScheduler2)->preemptedSpsr) : : "r7" );
 asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "mov fp, %[frame]" /* Restore FP */ : : [stack]"r"(globalScheduler.localScheduler2->sp), [frame]"r"(globalScheduler.localScheduler2->fp) : );
 asm volatile goto ("b %l[""eoeHandler""]" : : : : eoeHandler );
}

// For hardware thread 3.
eoeHandler3: {
 asm volatile ("nop\n" "pop {lr}\n" "push {r0}\n" /* PC placeholder */ "push {r0-r12}\n" "push {r14}" ); asm volatile ("cdp p13, 9, cr7, cr0, cr0\n" "str r7, [sp, #56]\n" /* Save PC */ "mov %[stack], sp" /* Save SP */ : [stack]"=r"((globalScheduler.localScheduler3)->preemptedSp) : : "r7" ); asm volatile ("cdp p12, 0, cr7, cr0, cr0\n" "mov %[spsrReg], r7" : [spsrReg]"=r"((globalScheduler.localScheduler3)->preemptedSpsr) : : "r7" );
 asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "mov fp, %[frame]" /* Restore FP */ : : [stack]"r"(globalScheduler.localScheduler3->sp), [frame]"r"(globalScheduler.localScheduler3->fp) : );
 asm volatile goto ("b %l[""eoeHandler""]" : : : : eoeHandler );
}

eoeHandler: {
 // Assign the saved context to the preempted task.
 if (localScheduler.currentTask != 0) {

  // "Preempted xxx."
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
  ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(localScheduler.hwThreadId)); ptarmUartOutputStr(":Preempted "); ptarmUartOutputStr(localScheduler.currentTask->name); ptarmUartOutputStr(".\n");
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");

  localScheduler.currentTask->state = PTARM_TASK_PREEMPTED; localScheduler.currentTask->sp = localScheduler.preemptedSp; localScheduler.currentTask->spsr = localScheduler.preemptedSpsr;
 } else {
  // A null task is only possible when the scheduler is preempted during the
  // dynamic scheduling phase.

  // "Preempted scheduler x."
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
  ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(localScheduler.hwThreadId)); ptarmUartOutputStr(":Preempted "); ptarmUartOutputStr(localScheduler.name); ptarmUartOutputStr(".\n");
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
 }

 // If the preemption occured during the dynamic scheduling phase, then we know
 // that the base period has ended.
 if (localScheduler.phase == PTARM_SCHEDULER_DYNAMIC) {
  // Prepare to resume the static scheduling phase.

  // Return back to the static scheduling phase.
  localScheduler.phase = PTARM_SCHEDULER_RELEASE;

  if (localScheduler.hwThreadId == 0) {

   // Reset the dynamic scheduling lists.
   globalScheduler.counterNonCritical = -1; globalScheduler.counterMission = -1; globalScheduler.counterLife = -1;

   // "Base period xxx ended."
   asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
   ptarmUartOutputStr("Base period "); ptarmUartOutputStr(utoa(localScheduler.basePeriodCounter)); ptarmUartOutputStr(" ended.\n");
   asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
  }

  // Update the timestamp of the start of the next base period.
  localScheduler.basePeriodCounter++;
  asm volatile ("mov r7, %[msb1]\n" "mov r8, %[lsb1]\n" "adds r8, r8, %[lsb2]\n" "adc r7, r7, %[msb2]\n" "mov %[msb3], r7\n" "mov %[lsb3], r8" : [msb3]"=r"(localScheduler.basePeriodStart.msb), [lsb3]"=r"(localScheduler.basePeriodStart.lsb) : [msb1]"r"(localScheduler.basePeriodStart.msb), [lsb1]"r"(localScheduler.basePeriodStart.lsb), [msb2]"r"(globalScheduler.basePeriodDuration.msb), [lsb2]"r"(globalScheduler.basePeriodDuration.lsb) : "r7", "r8" );

  // Wait until the next base period starts. This synchronises the start of the base period with other hardware threads to minimise jitter.
  asm volatile ("mov r7, %[msb1]\n" "mov r8, %[lsb1]\n" "cdp p13, 4, cr0, cr7, cr8" : : [msb1]"r"(localScheduler.basePeriodStart.msb), [lsb1]"r"(localScheduler.basePeriodStart.lsb) : "r7", "r8" );
 } else {

  // Insert the task to the dynamic scheduling list.
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
  // "Queuing xxx."
  ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(localScheduler.hwThreadId)); ptarmUartOutputStr(":Queuing "); ptarmUartOutputStr(localScheduler.currentTask->name); ptarmUartOutputStr(".\n");
  if (localScheduler.currentTask->criticality == PTARM_TASK_LIFE) { ++globalScheduler.counterLife; globalScheduler.priorityQueueLife[globalScheduler.counterLife] = localScheduler.currentTask; } else if (localScheduler.currentTask->criticality == PTARM_TASK_MISSION) { ++globalScheduler.counterMission; globalScheduler.priorityQueueMission[globalScheduler.counterMission] = localScheduler.currentTask; };
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
 }

 asm volatile goto ("b %l[""localScheduler""]" : : : : localScheduler );
}


// Local scheduler for each hardware thread.
// It always begins each base period with the static scheduling phase, followed by the dynamic scheduling phase.
localScheduler: {
 /*

	// "Scheduler = xxx, Current Task = xxx."

	PTARM_MUTEX_LOCK();

	printf(itoa(localScheduler.hwThreadId)); printf(":Scheduler = "); printf(localScheduler.name); printf(", Current task = "); printf(localScheduler.currentTask->name); printf(".\n");

	PTARM_MUTEX_UNLOCK();

	*/
# 270 "foremc.c"
 switch (localScheduler.phase) {

  case (PTARM_SCHEDULER_RELEASE):

   if (localScheduler.hwThreadId == 0) {
    // Go through the non-critical tasks and release eligible tasks.
    if (((&n1)->state == PTARM_TASK_PAUSED) && ((&n1)->earliestRelease <= localScheduler.basePeriodCounter)) { /* "Released xxx." */ asm volatile("cdp p13, 1, cr0, cr7, cr0, 1"); ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(localScheduler.hwThreadId)); ptarmUartOutputStr(":Releasing "); ptarmUartOutputStr((&n1)->name); ptarmUartOutputStr(".\n"); asm volatile("cdp p13, 1, cr0, cr7, cr0, 0"); /* The minimum number of base periods has elapsed, so release the task. */ (&n1)->state = PTARM_TASK_RELEASED; /* Update its last released timestamp. */ (&n1)->lastRelease = localScheduler.basePeriodCounter; /* Update its next earliest release timestamp. */ (&n1)->earliestRelease = (localScheduler.basePeriodCounter + (&n1)->basePeriodsMin); /* Insert the non-critical task into the global priority queue. */ ++globalScheduler.counterNonCritical; globalScheduler.priorityQueueNonCritical[globalScheduler.counterNonCritical] = (&n1); };
    if (((&n2)->state == PTARM_TASK_PAUSED) && ((&n2)->earliestRelease <= localScheduler.basePeriodCounter)) { /* "Released xxx." */ asm volatile("cdp p13, 1, cr0, cr7, cr0, 1"); ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(localScheduler.hwThreadId)); ptarmUartOutputStr(":Releasing "); ptarmUartOutputStr((&n2)->name); ptarmUartOutputStr(".\n"); asm volatile("cdp p13, 1, cr0, cr7, cr0, 0"); /* The minimum number of base periods has elapsed, so release the task. */ (&n2)->state = PTARM_TASK_RELEASED; /* Update its last released timestamp. */ (&n2)->lastRelease = localScheduler.basePeriodCounter; /* Update its next earliest release timestamp. */ (&n2)->earliestRelease = (localScheduler.basePeriodCounter + (&n2)->basePeriodsMin); /* Insert the non-critical task into the global priority queue. */ ++globalScheduler.counterNonCritical; globalScheduler.priorityQueueNonCritical[globalScheduler.counterNonCritical] = (&n2); };
    if (((&n3)->state == PTARM_TASK_PAUSED) && ((&n3)->earliestRelease <= localScheduler.basePeriodCounter)) { /* "Released xxx." */ asm volatile("cdp p13, 1, cr0, cr7, cr0, 1"); ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(localScheduler.hwThreadId)); ptarmUartOutputStr(":Releasing "); ptarmUartOutputStr((&n3)->name); ptarmUartOutputStr(".\n"); asm volatile("cdp p13, 1, cr0, cr7, cr0, 0"); /* The minimum number of base periods has elapsed, so release the task. */ (&n3)->state = PTARM_TASK_RELEASED; /* Update its last released timestamp. */ (&n3)->lastRelease = localScheduler.basePeriodCounter; /* Update its next earliest release timestamp. */ (&n3)->earliestRelease = (localScheduler.basePeriodCounter + (&n3)->basePeriodsMin); /* Insert the non-critical task into the global priority queue. */ ++globalScheduler.counterNonCritical; globalScheduler.priorityQueueNonCritical[globalScheduler.counterNonCritical] = (&n3); };
    if (((&n4)->state == PTARM_TASK_PAUSED) && ((&n4)->earliestRelease <= localScheduler.basePeriodCounter)) { /* "Released xxx." */ asm volatile("cdp p13, 1, cr0, cr7, cr0, 1"); ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(localScheduler.hwThreadId)); ptarmUartOutputStr(":Releasing "); ptarmUartOutputStr((&n4)->name); ptarmUartOutputStr(".\n"); asm volatile("cdp p13, 1, cr0, cr7, cr0, 0"); /* The minimum number of base periods has elapsed, so release the task. */ (&n4)->state = PTARM_TASK_RELEASED; /* Update its last released timestamp. */ (&n4)->lastRelease = localScheduler.basePeriodCounter; /* Update its next earliest release timestamp. */ (&n4)->earliestRelease = (localScheduler.basePeriodCounter + (&n4)->basePeriodsMin); /* Insert the non-critical task into the global priority queue. */ ++globalScheduler.counterNonCritical; globalScheduler.priorityQueueNonCritical[globalScheduler.counterNonCritical] = (&n4); };
   }

   // Go through the static schedule and release any eligible tasks.
   for (localScheduler.nextStaticTask = localScheduler.staticSchedule; (*localScheduler.nextStaticTask) != 0; localScheduler.nextStaticTask++) {

    volatile Task *currentTask = *localScheduler.nextStaticTask;

    // If the task is paused, check if it can be released for execution (i.e., the minimum number of base periods has elapsed).
    if (currentTask->state == PTARM_TASK_PAUSED && (currentTask->earliestRelease <= localScheduler.basePeriodCounter)) {

     // "Releasing xxx."
     asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
     ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(localScheduler.hwThreadId)); ptarmUartOutputStr(":Releasing "); ptarmUartOutputStr(currentTask->name); ptarmUartOutputStr(".\n");
     asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");

     // The minimum number of base periods has elapsed, so release the task.
     currentTask->state = PTARM_TASK_RELEASED;

     // Update its last released timestamp.
     currentTask->lastRelease = localScheduler.basePeriodCounter;

     // Update its next earliest release timestamp.
     currentTask->earliestRelease = (localScheduler.basePeriodCounter + currentTask->basePeriodsMin);

     // Release all the receive buffers associated with the task.
     volatile struct _ForeMc_100int *volatile *receiveBuffer;
     for (receiveBuffer = currentTask->receiveBuffers; *receiveBuffer != 0; receiveBuffer++) {
      /* Transfer the segment of the sending task to the receiving task.*/ (*receiveBuffer)->rFirst = (*receiveBuffer)->wFirst; (*receiveBuffer)->rCount = (*receiveBuffer)->wCount; /* Set up a new segment for the sending task.*/ (*receiveBuffer)->wFirst = foreMcGetIndex((*receiveBuffer)->wCount + (*receiveBuffer)->wFirst, (*receiveBuffer)->maxSize); (*receiveBuffer)->wCount = 0; /* Initialize the new segment with the last value sent.*/ (*receiveBuffer)->data[(*receiveBuffer)->wFirst] = (*receiveBuffer)->data[foreMcGetIndex((*receiveBuffer)->rCount - 1 + (*receiveBuffer)->rFirst, (*receiveBuffer)->maxSize)];
     }
    }
   }

   // Reset the static schedule (to the first task).
   localScheduler.nextStaticTask = localScheduler.staticSchedule;

   // Continue through to the next case statement for the static scheduling phase.
   // Start time = basePeriodStartOverhead + basePeriodStart.
   localScheduler.phase = PTARM_SCHEDULER_STATIC;
   asm volatile ("mov r7, %[msb1]\n" "mov r8, %[lsb1]\n" "adds r8, r8, %[lsb2]\n" "adc r7, r7, %[msb2]\n" "mov %[msb3], r7\n" "mov %[lsb3], r8" : [msb3]"=r"(localScheduler.basePeriodStartAfterOverhead.msb), [lsb3]"=r"(localScheduler.basePeriodStartAfterOverhead.lsb) : [msb1]"r"(localScheduler.basePeriodStartOverhead.msb), [lsb1]"r"(localScheduler.basePeriodStartOverhead.lsb), [msb2]"r"(localScheduler.basePeriodStart.msb), [lsb2]"r"(localScheduler.basePeriodStart.lsb) : "r7", "r8" );
   asm volatile ("mov r7, %[msb1]\n" "mov r8, %[lsb1]\n" "cdp p13, 4, cr0, cr7, cr8" : : [msb1]"r"(localScheduler.basePeriodStartAfterOverhead.msb), [lsb1]"r"(localScheduler.basePeriodStartAfterOverhead.lsb) : "r7", "r8" );

  case (PTARM_SCHEDULER_STATIC):;
   // Static scheduling phase.
   // Schedule all the tasks in its static schedule before going into the dynamic scheduling phase.

   // Get the next statically scheduled task.
   localScheduler.currentTask = *localScheduler.nextStaticTask;

   // Check if we have reached the end of the static schedule.
   if (localScheduler.currentTask != 0) {
    // The end of the static schedule has not been reached.

    // Update the next statically scheduled task.
    localScheduler.nextStaticTask++;

    // Execute the task if it has been preempted or released.
    if (localScheduler.currentTask->state == PTARM_TASK_PREEMPTED || localScheduler.currentTask->state == PTARM_TASK_RELEASED) {

     // "Executing xxx."
     asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
     ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(localScheduler.hwThreadId)); ptarmUartOutputStr(":Executing "); ptarmUartOutputStr(localScheduler.currentTask->name); ptarmUartOutputStr(".\n");
     asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");

     // Set the task's deadline in this base period to be the end of its statically allocated execution time.
     asm volatile ("cdp p13, 8, cr0, cr7, cr8\n" "mov %[msb], r7\n" "mov %[lsb], r8" : [msb]"=r"(localScheduler.currentTime.msb), [lsb]"=r"(localScheduler.currentTime.lsb) : : "r7", "r8" );
     asm volatile ("mov r7, %[msb1]\n" "mov r8, %[lsb1]\n" "adds r8, r8, %[lsb2]\n" "adc r7, r7, %[msb2]\n" "cdp p13, 2, cr0, cr7, cr8" : : [msb1]"r"(localScheduler.currentTime.msb), [lsb1]"r"(localScheduler.currentTime.lsb), [msb2]"r"(localScheduler.currentTask->allocatedTime.msb), [lsb2]"r"(localScheduler.currentTask->allocatedTime.lsb) : "r7", "r8" );

     // (Re)set the task's local scheduler to this static local scheduler.
     localScheduler.currentTask->localScheduler = &localScheduler;

     // Context switch to the current task.
     asm volatile ("mov r8, %[cpsrReg]\n" "cdp p12, 2, cr0, cr0, cr8" : : [cpsrReg]"r"((localScheduler.currentTask)->spsr) : "r8" ); asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "pop {r14}\n" "pop {r0-r12}\n" "pop {pc}" /* Restore PC */ : : [stack]"r"((localScheduler.currentTask)->sp) : );
    } else {
     // Pick the next task to execute instead.
     goto localScheduler;
    }
   } else {
    // The end of the static schedule has been reached. Prepare for the dynamic scheduling phase.

    // "Dynamic phase."
    asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
    ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(localScheduler.hwThreadId)); ptarmUartOutputStr(":Dynamic phase.\n");
    asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");

    // We are now entering the dynamic scheduling phase.
    localScheduler.phase = PTARM_SCHEDULER_DYNAMIC;

    // Continue through to the next case statement for the dynamic scheduling phase.
   }
  case (PTARM_SCHEDULER_DYNAMIC):;
   // Dynamic scheduling phase.

   // (Re)set the current task in case a timing exception occurs when the scheduler is executing.
   localScheduler.currentTask = 0;

   // Set the dynamic execution deadline to be the end of the base period, minus the expected scheduling overhead.
   asm volatile ("mov r7, %[msb1]\n" "mov r8, %[lsb1]\n" "adds r8, r8, %[lsb2]\n" "adc r7, r7, %[msb2]\n" "cdp p13, 2, cr0, cr7, cr8" : : [msb1]"r"(localScheduler.basePeriodStart.msb), [lsb1]"r"(localScheduler.basePeriodStart.lsb), [msb2]"r"(localScheduler.basePeriodMinusEndingOverhead.msb), [lsb2]"r"(localScheduler.basePeriodMinusEndingOverhead.lsb) : "r7", "r8" );

   // Check if there is enough time to execute a task.
   // elapsedTime = currentTime - basePeriodStart.
   asm volatile ("cdp p13, 8, cr0, cr7, cr8\n" "mov %[msb], r7\n" "mov %[lsb], r8" : [msb]"=r"(localScheduler.currentTime.msb), [lsb]"=r"(localScheduler.currentTime.lsb) : : "r7", "r8" );
   asm volatile ("mov r7, %[msb1]\n" "mov r8, %[lsb1]\n" "subs r8, r8, %[lsb2]\n" "sbc r7, r7, %[msb2]\n" "mov %[msb3], r7\n" "mov %[lsb3], r8" : [msb3]"=r"(localScheduler.elapsedTime.msb), [lsb3]"=r"(localScheduler.elapsedTime.lsb) : [msb1]"r"(localScheduler.currentTime.msb), [lsb1]"r"(localScheduler.currentTime.lsb), [msb2]"r"(localScheduler.basePeriodStart.msb), [lsb2]"r"(localScheduler.basePeriodStart.lsb) : "r7", "r8" );

   if ((localScheduler.basePeriodMinusEndingOverhead.msb > localScheduler.elapsedTime.msb) ||
    ((localScheduler.basePeriodMinusEndingOverhead.msb == localScheduler.elapsedTime.msb) && (localScheduler.basePeriodMinusEndingOverhead.lsb >= localScheduler.elapsedTime.lsb))) {
    // Enough time to execute a task. Find a task to execute.

    // Find a task from the dynamic scheduling lists to execute.
    asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
    if (globalScheduler.counterNonCritical > -1) { localScheduler.currentTask = globalScheduler.priorityQueueNonCritical[globalScheduler.counterNonCritical]; --globalScheduler.counterNonCritical; } else if (globalScheduler.counterMission > -1) { localScheduler.currentTask = globalScheduler.priorityQueueMission[globalScheduler.counterMission]; --globalScheduler.counterMission; } else if (globalScheduler.counterLife > -1) { localScheduler.currentTask = globalScheduler.priorityQueueLife[globalScheduler.counterLife]; --globalScheduler.counterLife; } else { localScheduler.currentTask = 0; };
    asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");

    // Check if it is an available task.
    if (localScheduler.currentTask != 0) {

     // "Picking xxx."
     asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
     ptarmUartOutputStr(" "); ptarmUartOutputStr(utoa(localScheduler.hwThreadId)); ptarmUartOutputStr(":Picking "); ptarmUartOutputStr(localScheduler.currentTask->name); ptarmUartOutputStr(".\n");
     asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");

     // Set the task's local scheduler to this dynamic local scheduler.
     localScheduler.currentTask->localScheduler = &localScheduler;

     // The task is available, so context switch to it.
     asm volatile ("mov r8, %[cpsrReg]\n" "cdp p12, 2, cr0, cr0, cr8" : : [cpsrReg]"r"((localScheduler.currentTask)->spsr) : "r8" ); asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "pop {r14}\n" "pop {r0-r12}\n" "pop {pc}" /* Restore PC */ : : [stack]"r"((localScheduler.currentTask)->sp) : );
    }
   }

   // Wait for a task to become available, or until the base period ends.
   goto localScheduler;
   break;

  default:;
   // Undefined scheduling phase.
   asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
   ptarmUartOutputStr("!!"); ptarmUartOutputStr(utoa(localScheduler.hwThreadId)); ptarmUartOutputStr(" Scheduling error. Phase = "); ptarmUartOutputStr(utoa(localScheduler.phase)); ptarmUartOutputStr(".\n");
   asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");

   while (halt);
   break;
 }
}

// The tasks. Note that they are defined within the main function.

// Life critical tasks
l1: {
 int j = 0;
 while (loopForever) {
  int i;
  for (i = 0; i < 2000000u; i++);

  j++;

  asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
  ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(l1.localScheduler->hwThreadId)); ptarmUartOutputStr(":l1 pausing.\n");
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
  asm volatile ("cdp p13, 3, cr0, cr0, cr0"); /* Disable EOE. */ l1.state = PTARM_TASK_PAUSED; /* Buffer the output variable. */ bufferOne.data[foreMcGetIndex(bufferOne.wCount + bufferOne.wFirst, bufferOne.maxSize)] = j; bufferOne.wCount = bufferOne.wCount + 1; /* Context switch to the next task. */ asm volatile ("nop\n" "push {r0}\n" /* PC placeholder */ "push {r0-r12}\n" "push {r14}" ); asm volatile ("mov r7, %[cont]\n" "str r7, [sp, #56]\n" /* Save PC */ "mov %[stack], sp" /* Save SP */ : [stack]"=r"(l1.sp) : [cont]"r"(&&PAUSE_l1continuationId) : "r7" ); asm volatile ("cdp p12, 0, cr7, cr0, cr0\n" "mov %[spsrReg], r7" : [spsrReg]"=r"(l1.spsr) : : "r7" ); asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "mov fp, %[frame]" /* Restore FP */ : : [stack]"r"(l1.localScheduler->sp), [frame]"r"(l1.localScheduler->fp) : ); asm volatile goto ("b %l[""localScheduler""]" : : : : localScheduler ); PAUSE_l1continuationId:;
 }
}

l2: {
 while (loopForever) {
  int i;
  for (i = 0; i < 2000000u; i++);

  asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
  ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(l2.localScheduler->hwThreadId)); ptarmUartOutputStr(":l2 pausing.\n");
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
  asm volatile ("cdp p13, 3, cr0, cr0, cr0"); /* Disable EOE. */ l2.state = PTARM_TASK_PAUSED; /* Context switch to the local scheduler. */ asm volatile ("nop\n" "push {r0}\n" /* PC placeholder */ "push {r0-r12}\n" "push {r14}" ); asm volatile ("mov r7, %[cont]\n" "str r7, [sp, #56]\n" /* Save PC */ "mov %[stack], sp" /* Save SP */ : [stack]"=r"(l2.sp) : [cont]"r"(&&PAUSE_l21) : "r7" ); asm volatile ("cdp p12, 0, cr7, cr0, cr0\n" "mov %[spsrReg], r7" : [spsrReg]"=r"(l2.spsr) : : "r7" ); asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "mov fp, %[frame]" /* Restore FP */ : : [stack]"r"(l2.localScheduler->sp), [frame]"r"(l2.localScheduler->fp) : ); asm volatile goto ("b %l[""localScheduler""]" : : : : localScheduler ); PAUSE_l21:;
 }
}

l3: {
 while (loopForever) {
  int i;
  for (i = 0; i < 2000000u; i++);

  asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
  ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(l3.localScheduler->hwThreadId)); ptarmUartOutputStr(":l3 pausing.\n");
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
  asm volatile ("cdp p13, 3, cr0, cr0, cr0"); /* Disable EOE. */ l3.state = PTARM_TASK_PAUSED; /* Context switch to the local scheduler. */ asm volatile ("nop\n" "push {r0}\n" /* PC placeholder */ "push {r0-r12}\n" "push {r14}" ); asm volatile ("mov r7, %[cont]\n" "str r7, [sp, #56]\n" /* Save PC */ "mov %[stack], sp" /* Save SP */ : [stack]"=r"(l3.sp) : [cont]"r"(&&PAUSE_l31) : "r7" ); asm volatile ("cdp p12, 0, cr7, cr0, cr0\n" "mov %[spsrReg], r7" : [spsrReg]"=r"(l3.spsr) : : "r7" ); asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "mov fp, %[frame]" /* Restore FP */ : : [stack]"r"(l3.localScheduler->sp), [frame]"r"(l3.localScheduler->fp) : ); asm volatile goto ("b %l[""localScheduler""]" : : : : localScheduler ); PAUSE_l31:;
 }
}

l4: {
 while (loopForever) {
  int i;
  for (i = 0; i < 2000000u; i++);

  asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
  ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(l4.localScheduler->hwThreadId)); ptarmUartOutputStr(":l4 pausing.\n");
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
  asm volatile ("cdp p13, 3, cr0, cr0, cr0"); /* Disable EOE. */ l4.state = PTARM_TASK_PAUSED; /* Context switch to the local scheduler. */ asm volatile ("nop\n" "push {r0}\n" /* PC placeholder */ "push {r0-r12}\n" "push {r14}" ); asm volatile ("mov r7, %[cont]\n" "str r7, [sp, #56]\n" /* Save PC */ "mov %[stack], sp" /* Save SP */ : [stack]"=r"(l4.sp) : [cont]"r"(&&PAUSE_l41) : "r7" ); asm volatile ("cdp p12, 0, cr7, cr0, cr0\n" "mov %[spsrReg], r7" : [spsrReg]"=r"(l4.spsr) : : "r7" ); asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "mov fp, %[frame]" /* Restore FP */ : : [stack]"r"(l4.localScheduler->sp), [frame]"r"(l4.localScheduler->fp) : ); asm volatile goto ("b %l[""localScheduler""]" : : : : localScheduler ); PAUSE_l41:;
 }
}

// Mission critical
m1: {
 while (loopForever) {
  int i;
  for (i = 0; i < 2000000u; i++);

  asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
  ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(m1.localScheduler->hwThreadId)); ptarmUartOutputStr(":m1 pausing.\n");
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
  asm volatile ("cdp p13, 3, cr0, cr0, cr0"); /* Disable EOE. */ m1.state = PTARM_TASK_PAUSED; /* Context switch to the local scheduler. */ asm volatile ("nop\n" "push {r0}\n" /* PC placeholder */ "push {r0-r12}\n" "push {r14}" ); asm volatile ("mov r7, %[cont]\n" "str r7, [sp, #56]\n" /* Save PC */ "mov %[stack], sp" /* Save SP */ : [stack]"=r"(m1.sp) : [cont]"r"(&&PAUSE_m11) : "r7" ); asm volatile ("cdp p12, 0, cr7, cr0, cr0\n" "mov %[spsrReg], r7" : [spsrReg]"=r"(m1.spsr) : : "r7" ); asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "mov fp, %[frame]" /* Restore FP */ : : [stack]"r"(m1.localScheduler->sp), [frame]"r"(m1.localScheduler->fp) : ); asm volatile goto ("b %l[""localScheduler""]" : : : : localScheduler ); PAUSE_m11:;
 }
}

m2: {
 while (loopForever) {
  int index;
  for (index = 0; index < (bufferOne).rCount; index++) {
   asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
   ptarmUartOutputStr(utoa((bufferOne).rCount)); ptarmUartOutputStr(","); ptarmUartOutputStr(utoa(bufferOne.data[ foreMcGetIndex(index + bufferOne.rFirst, bufferOne.maxSize) ])); ptarmUartOutputStr("\n");
   asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
  }

  int i;
  for (i = 0; i < 2000000u; i++);

  asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
  ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(m2.localScheduler->hwThreadId)); ptarmUartOutputStr(":m2 pausing.\n");
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
  asm volatile ("cdp p13, 3, cr0, cr0, cr0"); /* Disable EOE. */ m2.state = PTARM_TASK_PAUSED; /* Context switch to the local scheduler. */ asm volatile ("nop\n" "push {r0}\n" /* PC placeholder */ "push {r0-r12}\n" "push {r14}" ); asm volatile ("mov r7, %[cont]\n" "str r7, [sp, #56]\n" /* Save PC */ "mov %[stack], sp" /* Save SP */ : [stack]"=r"(m2.sp) : [cont]"r"(&&PAUSE_m21) : "r7" ); asm volatile ("cdp p12, 0, cr7, cr0, cr0\n" "mov %[spsrReg], r7" : [spsrReg]"=r"(m2.spsr) : : "r7" ); asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "mov fp, %[frame]" /* Restore FP */ : : [stack]"r"(m2.localScheduler->sp), [frame]"r"(m2.localScheduler->fp) : ); asm volatile goto ("b %l[""localScheduler""]" : : : : localScheduler ); PAUSE_m21:;
 }
}

m3: {
 while (loopForever) {
  int i;
  for (i = 0; i < 2000000u; i++);

  asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
  ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(m3.localScheduler->hwThreadId)); ptarmUartOutputStr(":m3 pausing.\n");
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
  asm volatile ("cdp p13, 3, cr0, cr0, cr0"); /* Disable EOE. */ m3.state = PTARM_TASK_PAUSED; /* Context switch to the local scheduler. */ asm volatile ("nop\n" "push {r0}\n" /* PC placeholder */ "push {r0-r12}\n" "push {r14}" ); asm volatile ("mov r7, %[cont]\n" "str r7, [sp, #56]\n" /* Save PC */ "mov %[stack], sp" /* Save SP */ : [stack]"=r"(m3.sp) : [cont]"r"(&&PAUSE_m31) : "r7" ); asm volatile ("cdp p12, 0, cr7, cr0, cr0\n" "mov %[spsrReg], r7" : [spsrReg]"=r"(m3.spsr) : : "r7" ); asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "mov fp, %[frame]" /* Restore FP */ : : [stack]"r"(m3.localScheduler->sp), [frame]"r"(m3.localScheduler->fp) : ); asm volatile goto ("b %l[""localScheduler""]" : : : : localScheduler ); PAUSE_m31:;
 }
}

m4: {
 while (loopForever) {
  int i;
  for (i = 0; i < 2000000u; i++);

  asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
  ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(m4.localScheduler->hwThreadId)); ptarmUartOutputStr(":m4 pausing.\n");
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
  asm volatile ("cdp p13, 3, cr0, cr0, cr0"); /* Disable EOE. */ m4.state = PTARM_TASK_PAUSED; /* Context switch to the local scheduler. */ asm volatile ("nop\n" "push {r0}\n" /* PC placeholder */ "push {r0-r12}\n" "push {r14}" ); asm volatile ("mov r7, %[cont]\n" "str r7, [sp, #56]\n" /* Save PC */ "mov %[stack], sp" /* Save SP */ : [stack]"=r"(m4.sp) : [cont]"r"(&&PAUSE_m41) : "r7" ); asm volatile ("cdp p12, 0, cr7, cr0, cr0\n" "mov %[spsrReg], r7" : [spsrReg]"=r"(m4.spsr) : : "r7" ); asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "mov fp, %[frame]" /* Restore FP */ : : [stack]"r"(m4.localScheduler->sp), [frame]"r"(m4.localScheduler->fp) : ); asm volatile goto ("b %l[""localScheduler""]" : : : : localScheduler ); PAUSE_m41:;
 }
}

// Non-critical
n1: {
 while (loopForever) {
  int i;
  for (i = 0; i < 2000000u; i++);

  asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
  ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(n1.localScheduler->hwThreadId)); ptarmUartOutputStr(":n1 pausing.\n");
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
  asm volatile ("cdp p13, 3, cr0, cr0, cr0"); /* Disable EOE. */ n1.state = PTARM_TASK_PAUSED; /* Context switch to the local scheduler. */ asm volatile ("nop\n" "push {r0}\n" /* PC placeholder */ "push {r0-r12}\n" "push {r14}" ); asm volatile ("mov r7, %[cont]\n" "str r7, [sp, #56]\n" /* Save PC */ "mov %[stack], sp" /* Save SP */ : [stack]"=r"(n1.sp) : [cont]"r"(&&PAUSE_n11) : "r7" ); asm volatile ("cdp p12, 0, cr7, cr0, cr0\n" "mov %[spsrReg], r7" : [spsrReg]"=r"(n1.spsr) : : "r7" ); asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "mov fp, %[frame]" /* Restore FP */ : : [stack]"r"(n1.localScheduler->sp), [frame]"r"(n1.localScheduler->fp) : ); asm volatile goto ("b %l[""localScheduler""]" : : : : localScheduler ); PAUSE_n11:;
 }
}

n2: {
 while (loopForever) {
  int i;
  for (i = 0; i < 2000000u; i++);

  asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
  ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(n2.localScheduler->hwThreadId)); ptarmUartOutputStr(":n2 pausing.\n");
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
  asm volatile ("cdp p13, 3, cr0, cr0, cr0"); /* Disable EOE. */ n2.state = PTARM_TASK_PAUSED; /* Context switch to the local scheduler. */ asm volatile ("nop\n" "push {r0}\n" /* PC placeholder */ "push {r0-r12}\n" "push {r14}" ); asm volatile ("mov r7, %[cont]\n" "str r7, [sp, #56]\n" /* Save PC */ "mov %[stack], sp" /* Save SP */ : [stack]"=r"(n2.sp) : [cont]"r"(&&PAUSE_n21) : "r7" ); asm volatile ("cdp p12, 0, cr7, cr0, cr0\n" "mov %[spsrReg], r7" : [spsrReg]"=r"(n2.spsr) : : "r7" ); asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "mov fp, %[frame]" /* Restore FP */ : : [stack]"r"(n2.localScheduler->sp), [frame]"r"(n2.localScheduler->fp) : ); asm volatile goto ("b %l[""localScheduler""]" : : : : localScheduler ); PAUSE_n21:;
 }
}

n3: {
 while (loopForever) {
  int i;
  for (i = 0; i < 2000000u; i++);

  asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
  ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(n3.localScheduler->hwThreadId)); ptarmUartOutputStr(":n3 pausing.\n");
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
  asm volatile ("cdp p13, 3, cr0, cr0, cr0"); /* Disable EOE. */ n3.state = PTARM_TASK_PAUSED; /* Context switch to the local scheduler. */ asm volatile ("nop\n" "push {r0}\n" /* PC placeholder */ "push {r0-r12}\n" "push {r14}" ); asm volatile ("mov r7, %[cont]\n" "str r7, [sp, #56]\n" /* Save PC */ "mov %[stack], sp" /* Save SP */ : [stack]"=r"(n3.sp) : [cont]"r"(&&PAUSE_n31) : "r7" ); asm volatile ("cdp p12, 0, cr7, cr0, cr0\n" "mov %[spsrReg], r7" : [spsrReg]"=r"(n3.spsr) : : "r7" ); asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "mov fp, %[frame]" /* Restore FP */ : : [stack]"r"(n3.localScheduler->sp), [frame]"r"(n3.localScheduler->fp) : ); asm volatile goto ("b %l[""localScheduler""]" : : : : localScheduler ); PAUSE_n31:;
 }
}

n4: {
 while (loopForever) {
  int i;
  for (i = 0; i < 2000000u; i++);

  asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
  ptarmUartOutputStr(" "); ptarmUartOutputStr(itoa(n4.localScheduler->hwThreadId)); ptarmUartOutputStr(":n4 pausing.\n");
  asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
  asm volatile ("cdp p13, 3, cr0, cr0, cr0"); /* Disable EOE. */ n4.state = PTARM_TASK_PAUSED; /* Context switch to the local scheduler. */ asm volatile ("nop\n" "push {r0}\n" /* PC placeholder */ "push {r0-r12}\n" "push {r14}" ); asm volatile ("mov r7, %[cont]\n" "str r7, [sp, #56]\n" /* Save PC */ "mov %[stack], sp" /* Save SP */ : [stack]"=r"(n4.sp) : [cont]"r"(&&PAUSE_n41) : "r7" ); asm volatile ("cdp p12, 0, cr7, cr0, cr0\n" "mov %[spsrReg], r7" : [spsrReg]"=r"(n4.spsr) : : "r7" ); asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "mov fp, %[frame]" /* Restore FP */ : : [stack]"r"(n4.localScheduler->sp), [frame]"r"(n4.localScheduler->fp) : ); asm volatile goto ("b %l[""localScheduler""]" : : : : localScheduler ); PAUSE_n41:;
 }
}

 return 0;
}
