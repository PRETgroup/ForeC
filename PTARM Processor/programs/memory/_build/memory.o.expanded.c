# 1 "memory.c"
# 1 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/programs/memory//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "memory.c"
# 1 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/include/ptarm_hw_thread.h" 1
// This file defines macros for managing the PTARM hardware threads.





//======================================================================
// PTARM hardware thread macros.
//======================================================================

// Gets the ID of the current PTARM hardware thread.
# 21 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/include/ptarm_hw_thread.h"
// Gets the Saved Processor Status Register (SPSR) of the current PTARM hardware thread.
// 20 bits long.
# 32 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/include/ptarm_hw_thread.h"
// Gets the Current Processor Status Register (CPSR) of the current PTARM hardware thread.
// 20 bits long.
# 43 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/include/ptarm_hw_thread.h"
// Sets the Current Processor Status Register (CPSR) of the current PTARM hardware thread.
// 20 bits long.
# 54 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/include/ptarm_hw_thread.h"
// Goes to a label if the PTARM hardware thread's ID matches.
# 66 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/include/ptarm_hw_thread.h"
// Go to a label.
# 76 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/include/ptarm_hw_thread.h"
// 32-bit unsigned integer division.
// quotient = dividend / divisor
# 2 "memory.c" 2
# 1 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/include/ptarm_io.h" 1
// This file defines macros for reading and writing to registers and memory mapped IO.




# 1 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/include/ptarm_types.h" 1
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
# 7 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/include/ptarm_io.h" 2
# 1 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/include/ptarm_mutex.h" 1
// This file defines macros for a mutex.





//======================================================================
// PTARM mutex macros.
//======================================================================

// Acquire the mutex. Only one mutex can be acquired.




// Release the mutex. Only the acquirer can release the mutex.
# 8 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/include/ptarm_io.h" 2
# 1 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/include/ptarm_hw_thread.h" 1
// This file defines macros for managing the PTARM hardware threads.
# 9 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/include/ptarm_io.h" 2


//======================================================================
// PTARM memory mapped I/O base addresses.
//======================================================================
# 41 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/include/ptarm_io.h"
//======================================================================
// PTARM register macros.
//======================================================================

// Stores the value of a register into a variable.
# 54 "/Volumes/Data/Documents/University of Auckland/Post Doc/ForeC/PTARM Processor/include/ptarm_io.h"
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
# 3 "memory.c" 2

// Variable whose address is at the end of the program binary.
// Defined in the linker script.
extern unsigned int addr_stack_limit;

// Variable whose address is at the end of the PTARM hardware threads' stacks.
// Defined in the linker script.
extern unsigned int addr_stack_end;

int main() {
 // Only hardware thread 0 is allowed to execute this test.
 unsigned int hwThreadId;
 asm volatile ("cdp p13, 0, cr7, cr0, cr0\n" "mov %[id], r7" : [id]"=r"(hwThreadId) : : "r7" );
 if (hwThreadId != 0) {
  return 0;
 }

 ptarmUartOutputStr("Memory test\n");
 ptarmUartOutputStr("-----------\n");
 ptarmUartOutputStr("Memory range: 0x");
 ptarmUartOutputStr(hex((unsigned int)&addr_stack_limit));
 ptarmUartOutputStr(" to 0x");
 ptarmUartOutputStr(hex((unsigned int)&addr_stack_end));
 ptarmUartOutputStr(" (");
 ptarmUartOutputStr(utoa(1 + ((unsigned int)&addr_stack_end - (unsigned int)&addr_stack_limit)/sizeof(unsigned int)));
 ptarmUartOutputStr(" ");
 ptarmUartOutputStr(utoa(sizeof(unsigned int)));
 ptarmUartOutputStr(" byte memory locations).\n");

 ptarmUartOutputStr("* Writing phase ... ");
 unsigned int counter = 0;
 unsigned int *address;
 for (address = &addr_stack_limit; address <= &addr_stack_end; address++) {
  *address = counter;
  counter++;
 }
 ptarmUartOutputStr(utoa(counter));
 ptarmUartOutputStr(" ");
 ptarmUartOutputStr(utoa(sizeof(unsigned int)));
 ptarmUartOutputStr(" byte memory locations.\n");

 ptarmUartOutputStr("* Reading phase ... ");
 counter = 0;
 for (address = &addr_stack_limit; address <= &addr_stack_end; address++) {
  unsigned int value = *address;

  if (value != counter) {
   ptarmUartOutputStr("  address = ");
   ptarmUartOutputStr(hex((unsigned int)address));

   ptarmUartOutputStr(", value = ");
   ptarmUartOutputStr(utoa(value));

   ptarmUartOutputStr(", counter = ");
   ptarmUartOutputStr(utoa(counter));

   ptarmUartOutputStr(".\n");
  }

  counter++;
 }
 ptarmUartOutputStr(utoa(counter));
 ptarmUartOutputStr(" ");
 ptarmUartOutputStr(utoa(sizeof(unsigned int)));
 ptarmUartOutputStr(" byte memory locations.\n");

 ptarmUartOutputStr("Completed. ");

 return 0;
}
