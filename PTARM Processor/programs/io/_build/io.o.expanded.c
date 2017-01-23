# 1 "io.c"
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/programs/io//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "io.c"
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
# 2 "io.c" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_mutex.h" 1
// This file defines macros for a mutex.





//======================================================================
// PTARM mutex macros.
//======================================================================

// Acquire the mutex. Only one mutex can be acquired.




// Release the mutex. Only the acquirer can release the mutex.
# 3 "io.c" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_io.h" 1
// This file defines macros for reading and writing to registers and memory mapped IO.




# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_types.h" 1
// This file defines some useful data types.
# 7 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_io.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_mutex.h" 1
// This file defines macros for a mutex.
# 8 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_io.h" 2
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
# 4 "io.c" 2
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
# 5 "io.c" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_hw_thread.h" 1
// This file defines macros for managing the PTARM hardware threads.
# 6 "io.c" 2
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




# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_hw_thread.h" 1
// This file defines macros for managing the PTARM hardware threads.
# 7 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_foremc.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_timer.h" 1
// This file defines macros for querying the time, using timing instructions, and manipulating time values.
# 8 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_foremc.h" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_task.h" 1
// This file defines macros for creating and manipulating tasks.
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
# 7 "io.c" 2
# 1 "/Volumes/Data/Documents/Dropbox/PRET/PTARM/include/ptarm_scheduler.h" 1
// This file defines macros for creating and managing static and dynamic task schedules.
# 8 "io.c" 2

// Null values.
Timer64Bit nullTime = {.msb = 0, .lsb = 0};

volatile const bool halt = true;
volatile const bool loopForever = true;

// Tasks (structure defined in ptarm_task.h).
Task one = {.name = "one"};
Task two = {.name = "two"};
Task three = {.name = "three"};
Task four = {.name = "four"};

// Global scheduling information (structure defined in ptarm_scheduler.h).
GlobalScheduler globalScheduler = {.isInitialised = false};


// Main entry point of the program that is executed by all hardware threads.
int main(void) {
 // Create a local scheduler that uses the hardware thread's stack.
 /* Hardware thread number. */ unsigned int hwThreadId; asm volatile ("cdp p13, 0, cr7, cr0, cr0\n" "mov %[id], r7" : [id]"=r"(hwThreadId) : : "r7" ); /* Empty static schedule that holds up to five tasks */ volatile Task *staticSchedule[5] = { 0 }; /* Set the scheduler name. */ char localSchedulerName[11] = "scheduler "; localSchedulerName[9] = '0' + hwThreadId; /* Create local scheduler */ LocalScheduler localScheduler = { .name = localSchedulerName, .hwThreadId = hwThreadId, .staticSchedule = staticSchedule, .currentTask = staticSchedule[0], .nextStaticTask = staticSchedule, .phase = PTARM_SCHEDULER_RELEASE, .basePeriodCounter = 0 }; /* Initialise the context. */ asm volatile ("mov %[stack], sp\n" /* Save SP */ "mov %[frame], fp" /* Save FP */ : [stack]"=r"(localScheduler.sp), [frame]"=r"(localScheduler.fp) : : ); localScheduler.pc = &&localScheduler;

 // Each hardware thread performs some type of start up work.
 switch (localScheduler.hwThreadId) {
  case (0): // Hardware thread 0.

     asm volatile("cdp p13, 1, cr0, cr7, cr0, 1"); ptarmUartOutputStr("Input/Output example.\n\n"); asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");

     ptarmCreateTask(&one, &&one, &localScheduler); // Create task one.
     localScheduler.currentTask = &one; // Assign a task to execute.
     globalScheduler.localScheduler0 = &localScheduler; // Set the global reference to the local scheduler
     (&eoe_table)[localScheduler.hwThreadId] = (unsigned int)&&eoeHandler0; // Register the EOE handler.

     globalScheduler.isInitialised = true; // Initialisation complete.
     break;

  case (1): // Hardware thread 1.

     ptarmCreateTask(&two, &&two, &localScheduler); // Create task two.
     localScheduler.currentTask = &two; // Assign a task to execute.
     globalScheduler.localScheduler1 = &localScheduler; // Set the global reference to the local scheduler
     (&eoe_table)[localScheduler.hwThreadId] = (unsigned int)&&eoeHandler1; // Register the EOE handler.
     break;

  case (2): // Hardware thread 2.

     ptarmCreateTask(&three, &&three, &localScheduler);
     localScheduler.currentTask = &three;
     globalScheduler.localScheduler2 = &localScheduler;
     (&eoe_table)[localScheduler.hwThreadId] = (unsigned int)&&eoeHandler2;
     break;

  case (3): // Hardware thread 3.

     ptarmCreateTask(&four, &&four, &localScheduler);
     localScheduler.currentTask = &four;
     globalScheduler.localScheduler3 = &localScheduler;
     (&eoe_table)[localScheduler.hwThreadId] = (unsigned int)&&eoeHandler3;
     break;

  default: // Unknown hardware thread ID.

     asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
     ptarmUartOutputStr("!! Initialisation error: Unknown hwThreadId = ");
     ptarmUartOutputStr(utoa(localScheduler.hwThreadId));
     ptarmUartOutputStr("\n");
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
 localScheduler.currentTask->state = PTARM_TASK_PREEMPTED;
 localScheduler.currentTask->sp = localScheduler.preemptedSp;
 localScheduler.currentTask->spsr = localScheduler.preemptedSpsr;

 asm volatile goto ("b %l[""localScheduler""]" : : : : localScheduler );
}


// Local scheduler for each hardware thread.
localScheduler: {
 Timer64Bit delay = {.msb = 0, .lsb = 0};
 switch (localScheduler.hwThreadId) {
  case (0): delay.lsb = 1000000000u; // 1s.
     break;

  case (1): delay.lsb = 2000000000u; // 2s.
     break;

  case (2): delay.lsb = 3000000000u; // 3s.
     break;

  case (3): delay.lsb = 4000000000u; // 4s.
     break;

  default: asm volatile("cdp p13, 1, cr0, cr7, cr0, 1");
     ptarmUartOutputStr("!! Scheduling error: Unknown hardware thread.\n  ");
     // "Task = xxx, SP = xxx, PC = xxx, hwThreadId = xxx."
     ptarmUartOutputStr("Task = "); ptarmUartOutputStr(localScheduler.name);
     ptarmUartOutputStr(", SP = "); ptarmUartOutputStr(hex((unsigned int)localScheduler.sp));
     ptarmUartOutputStr(", PC = "); ptarmUartOutputStr(hex((unsigned int)localScheduler.pc));
     ptarmUartOutputStr(", hwThreadId = "); ptarmUartOutputStr(utoa(localScheduler.hwThreadId));
     ptarmUartOutputStr("\n");
     asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
     while (halt);
     break;
 }

 asm volatile ("cdp p13, 8, cr0, cr7, cr8\n" "mov %[msb], r7\n" "mov %[lsb], r8" : [msb]"=r"(localScheduler.currentTime.msb), [lsb]"=r"(localScheduler.currentTime.lsb) : : "r7", "r8" );
 asm volatile ("mov r7, %[msb1]\n" "mov r8, %[lsb1]\n" "adds r8, r8, %[lsb2]\n" "adc r7, r7, %[msb2]\n" "cdp p13, 2, cr0, cr7, cr8" : : [msb1]"r"(localScheduler.currentTime.msb), [lsb1]"r"(localScheduler.currentTime.lsb), [msb2]"r"(delay.msb), [lsb2]"r"(delay.lsb) : "r7", "r8" );
 asm volatile ("mov r8, %[cpsrReg]\n" "cdp p12, 2, cr0, cr0, cr8" : : [cpsrReg]"r"((localScheduler.currentTask)->spsr) : "r8" ); asm volatile ("mov sp, %[stack]\n" /* Restore SP */ "pop {r14}\n" "pop {r0-r12}\n" "pop {pc}" /* Restore PC */ : : [stack]"r"((localScheduler.currentTask)->sp) : );

 asm volatile("cdp p13, 1, cr0, cr7, cr0, 1"); ptarmUartOutputStr("!! Scheduling error: Oops!\n"); asm volatile("cdp p13, 1, cr0, cr7, cr0, 0");
}

// The tasks.
// Note that they are defined within the main function.
one: {
 while (loopForever) {
  int i = 1;
  if (i) {
   volatile unsigned int keys = 0;
   keys = (*(unsigned int*)0xFFFFF000) & 0x0000000F;
   ptarmLedOutput(0xFFFFFF00, keys, 0x01FF);

   volatile unsigned int switches = 0;
   switches = ((*(unsigned int*)0xFFFFF000) & 0x003FFFF0) >> 4;
   ptarmLedOutput(0xFFFFFF09, switches, 0x03FFFF);
  } else {
   ptarmUartOutputStr("task one\n");
  }
 }
}

two: {
 while (loopForever) {
  int i = 0;
  if (i) {
   ptarmUartOutputStr("task two\n");
  }
 }
}

three: {
 ptarmSevenSegOutput(0, 0x40);
 ptarmSevenSegChar(1, 'A');
 ptarmSevenSegChar(2, 'B');
 ptarmSevenSegChar(3, 'C');
 ptarmSevenSegChar(4, 'D');
 ptarmSevenSegChar(5, 'E');
 ptarmSevenSegChar(6, 'F');

 unsigned int i = 0;
 while (loopForever) {
  ptarmSevenSegChar(7, utoa(i)[0]);
  i++;
  i %= 9;

  int j;
  for (j = 0; j < 100000; j++);
 }
}

four: {
 ptarmLcdInit();
 ptarmLcdOutput(0x00, 0x0, 26000); ptarmLcdCharCount = 0; ptarmLcdOutput(0x80, 0x0, 26000); ptarmLcdOutputStr("Hello World!\nPTARM\n");

 volatile unsigned int keys, lastKeys;
 keys = (*(unsigned int*)0xFFFFF000) & 0x0000000F;
 lastKeys = keys;
 bool updated = false;

 while (loopForever) {
  keys = (*(unsigned int*)0xFFFFF000) & 0x0000000F;

  if (keys != lastKeys) {
   if (keys != 0x0000000F) {
    if (!updated) {
     ptarmLcdOutput(0x00, 0x0, 26000); ptarmLcdCharCount = 0; ptarmLcdOutput(0x80, 0x0, 26000); ptarmLcdOutputStr(" A key is being    pressed!");
     updated = true;
    }
   } else {
    ptarmLcdOutput(0x00, 0x0, 26000); ptarmLcdCharCount = 0; ptarmLcdOutput(0x80, 0x0, 26000); ptarmLcdOutputStr("  Press a key!");
    updated = false;
   }
   lastKeys = keys;
  }
 }
}

 return 0;
}
