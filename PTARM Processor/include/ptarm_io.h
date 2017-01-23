// This file defines macros for reading and writing to registers and memory mapped IO.

#ifndef PTARM_IO_H
#define PTARM_IO_H

#include <ptarm_types.h>
#include <ptarm_mutex.h>
#include <ptarm_hw_thread.h>


//======================================================================
// PTARM memory mapped I/O base addresses.
//======================================================================
#define LEDG		0xFFFFFF00
#define LEDG_MASK	0x01FF
#define LEDR		0xFFFFFF09
#define LEDR_MASK	0x03FFFF

#define HEX			0xFFFFFF20
#define HEX_SIZE	0x08
#define HEX_MASK	0x007F

#define LCD			0xFFFFFF60
#define LCD_MASK	0x0FFF
#define LCD_EN		0x0800
#define LCD_D		0x0400
#define LCD_R		0x0200
#define LCD_ON		0x0100
#define LCD_LEN		15

#define UART_CIN	0xFFFF0000
#define UART_DIN	0xFFFF0004
#define UART_COUT	0xFFFF0008
#define UART_DOUT	0xFFFF000C

#define SW_KEY		0xFFFFF000
#define SW_MASK		0x003FFFF0
#define KEY_MASK	0x0000000F


//======================================================================
// PTARM register macros.
//======================================================================

// Stores the value of a register into a variable.
#define PTARM_GET_REG(var, reg)			    \
   asm volatile ("mov %[varReg], "#reg""	\
		 : [varReg]"=r"(var)				\
		 : 									\
		 :									\
	)


//======================================================================
// PTARM Switch and Key Input functions.
//======================================================================

// Reads the 18 switches into a variable
#define PTARM_READ_SWITCHES(var)					\
	var = ((*(unsigned int*)SW_KEY) & SW_MASK) >> 4


// Reads the 4 keys into a variable
#define PTARM_READ_KEYS(var)						\
	var = (*(unsigned int*)SW_KEY) & KEY_MASK


//======================================================================
// PTARM LED functions.
//======================================================================

// Outputs bit patterns to the green or red LEDs.
#define ptarmLedRedOutput(bitPattern)	ptarmLedOutput(LEDR, bitPattern, LEDR_MASK)
#define ptarmLedGreenOutput(bitPattern)	ptarmLedOutput(LEDG, bitPattern, LEDG_MASK)


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
	register unsigned char * const ptarmHex = (unsigned char * const) (HEX + (HEX_SIZE * index));
	*ptarmHex = HEX_MASK & bitPattern;
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
#define ptarmLcdCommand(command)	ptarmLcdOutput(command, 0x0, 26000)
#define ptarmLcdChar(char)			ptarmLcdOutput(char, LCD_D, 80)

// Useful LCD commands.
#define ptarmLcdClear()				ptarmLcdCommand(0x00)
#define ptarmLcdGotoLineOne()		ptarmLcdCommand(0x80)
#define ptarmLcdGotoLineTwo()		ptarmLcdCommand(0xC0)

#define printfLcd(str)				ptarmLcdClear(); ptarmLcdCharCount = 0; ptarmLcdGotoLineOne(); ptarmLcdOutputStr(str)


// Outputs a command or datum to the LCD display. Not a thread-safe function.
void ptarmLcdOutput(const unsigned int bitPattern, const unsigned int isData, const unsigned int delay) {
	// Memory mapped addresses for the LCD.
	register unsigned int * const ptarmLcd = (unsigned int * const) LCD;
	*ptarmLcd = LCD_MASK & (LCD_EN | isData | LCD_ON | bitPattern);
	
	int i = delay;
	while(--i);
	
	*ptarmLcd = LCD_MASK & (LCD_ON | bitPattern);
}


// Initialises the LCD display. Not a thread-safe function.
void ptarmLcdInit(void) {
	ptarmLcdCharCount = 0;

	// Function set to 8-bits and 2 lines
	ptarmLcdOutput(0x0038, 0x0, 30000);
	
	// Turn on the display and turn off the cursor
	ptarmLcdCommand(0x000C);
}


// Outputs a string to the LCD display. Not a thread-safe function.
void ptarmLcdOutputStr(const char *str) {
	while (*str != NULL) {
		// Check for the newline character
		if (*str == '\n') {
			ptarmLcdCharCount = (1 + (ptarmLcdCharCount > LCD_LEN)) * LCD_LEN;
		} else {
			ptarmLcdChar(*str);
			ptarmLcdCharCount++;
		}
		str++;
		
		if (ptarmLcdCharCount == LCD_LEN) {
			// Go to the second line.
			ptarmLcdGotoLineTwo();
		} else if (ptarmLcdCharCount == (LCD_LEN * 2)) {
			// Go back to the first line and don't output the remaining string.
			ptarmLcdGotoLineOne();
			ptarmLcdCharCount = 0;
			break;
		}
	}
}


//======================================================================
// PTARM UART functions.
//======================================================================

// Use UART as the standard output.
#define printf(str) ptarmUartOutputStr(str)


// Output a character to UART. Not a thread-safe function.
void ptarmUartOutputChar(const char c) {
	// Memory mapped addresses for the UART.
	register char * const ptarUartCout = (char * const) UART_COUT;
	register char * const ptarmUartDout = (char * const) UART_DOUT;

	while(*ptarUartCout != NULL);
	*ptarmUartDout = c;
}


// Output a string to UART. Not a thread-safe function.
void ptarmUartOutputStr(const char *str) {
	while (*str != NULL) {
		ptarmUartOutputChar(*str);
		str++;
	}
}


// Output a string to UART. Thread-safe function.
#define safe_printf(str)	\
	PTARM_MUTEX_LOCK();		\
	printf(str);			\
	PTARM_MUTEX_UNLOCK()


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
			PTARM_UNSIGNED_DIV(r, number, k);
			if (flag || r > 0) {
				ptarmStringBuffer[next++] = '0' + r;
				flag = 1;
			}
			number -= r * k;
			register const unsigned int k1 = k;
			register const unsigned int ten = 10;
			PTARM_UNSIGNED_DIV(k, k1, ten);
		}
	}

	ptarmStringBuffer[next] = NULL;
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
			PTARM_UNSIGNED_DIV(r, number, k);
			if (flag || r > 0) {
				ptarmStringBuffer[next++] = '0' + r;
				flag = 1;
			}
			number -= r * k;
			register const unsigned int k1 = k;
			register const unsigned int ten = 10;
			PTARM_UNSIGNED_DIV(k, k1, ten);
		}
	}

	ptarmStringBuffer[next] = NULL;
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

	ptarmStringBuffer[k] = NULL;
	return ptarmStringBuffer;
}

#endif /* PTARM_IO_H */

