# 1 "test.c"
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/programs/test//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "test.c"
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
# 2 "test.c" 2
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
# 3 "test.c" 2
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
# 4 "test.c" 2
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
# 5 "test.c" 2

Task one = {.receiveBuffers = { 0 }};


int main() {
 // Only hardware thread 0 is allowed to execute this test.
 unsigned int hwThreadId;
 asm volatile ("cdp p13, 0, cr7, cr0, cr0\n" "mov %[id], r7" : [id]"=r"(hwThreadId) : : "r7" );
 if (hwThreadId != 0) {
  return 0;
 }

 ptarmUartOutputStr("ForeMC buffer test\n");

 // Define and declare the buffer.
 typedef struct _ForeMc_buffer4int { volatile int data[4]; volatile int rFirst; volatile int rCount; volatile int wFirst; volatile int wCount; const int maxSize; } ForeMc_buffer4int; ForeMc_buffer4int buffer = { .wFirst = 1, .maxSize = 4 };

 // Read the last buffered data for the receiver.
 ptarmUartOutputStr(utoa((buffer).rCount)); ptarmUartOutputStr(":"); ptarmUartOutputStr(utoa(buffer.data[ foreMcGetIndex((buffer).rCount + buffer.rFirst, buffer.maxSize) ])); ptarmUartOutputStr("\n");

 // Write data into the buffer
 buffer.data[foreMcGetIndex(buffer.wCount + buffer.wFirst, buffer.maxSize)] = 10; buffer.wCount = buffer.wCount + 1;
 buffer.data[foreMcGetIndex(buffer.wCount + buffer.wFirst, buffer.maxSize)] = 20; buffer.wCount = buffer.wCount + 1;

 // Read the last buffered data for the receiver.
 ptarmUartOutputStr(utoa((buffer).rCount)); ptarmUartOutputStr(":"); ptarmUartOutputStr(utoa(buffer.data[ foreMcGetIndex((buffer).rCount + buffer.rFirst, buffer.maxSize) ])); ptarmUartOutputStr("\n");

 // Swap the buffers.
 /* Transfer the segment of the sending task to the receiving task.*/ (&buffer)->rFirst = (&buffer)->wFirst; (&buffer)->rCount = (&buffer)->wCount; /* Set up a new segment for the sending task.*/ (&buffer)->wFirst = foreMcGetIndex((&buffer)->wCount + (&buffer)->wFirst, (&buffer)->maxSize); (&buffer)->wCount = 0; /* Initialize the new segment with the last value sent.*/ (&buffer)->data[(&buffer)->wFirst] = (&buffer)->data[foreMcGetIndex((&buffer)->rCount - 1 + (&buffer)->rFirst, (&buffer)->maxSize)];

 // Read the last (latest) buffered data for the receiver.
 ptarmUartOutputStr(utoa(buffer.data[ foreMcGetIndex(( (buffer.rCount == 0) ? 0 : ((-1 > (buffer.rCount - 1) || -1 == -1) ? (buffer.rCount - 1) : -1) ) + buffer.rFirst, buffer.maxSize) ])); ptarmUartOutputStr("\n");

 int i;
 for (i = 0; i < (buffer).rCount; i++) {
  ptarmUartOutputStr(utoa((buffer).rCount)); ptarmUartOutputStr(":"); ptarmUartOutputStr(utoa(buffer.data[ foreMcGetIndex(i + buffer.rFirst, buffer.maxSize) ])); ptarmUartOutputStr("\n");
 }

 return 0;
}
