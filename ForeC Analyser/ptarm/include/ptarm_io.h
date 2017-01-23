#ifndef PTARM_IO_H
#define PTARM_IO_H

#include <ptarm_mutex.h>

//======================================================================
// PTARM register macros.
//======================================================================

// Stores the value of a register into a variable.
#define PTARM_GET_REG(var, reg)			    \
   asm volatile ("mov %[varReg], "#reg""	\
		 : [varReg]"=r"(var)				\
		 : 									\
		 :									\
		 );	


//======================================================================
// PTARM UART functions.
//======================================================================

#define printf(str) ptarmUartOutputStr(str);


// Output a character to UART. Not a thread-safe function.
void ptarmUartOutputChar(const char c) {
	// Memory mapped addresses for the UART.
	char * const ptarUartCout = (char * const) 0xFFFF0008;
	char * const ptarmUartDout = (char * const) 0xFFFF000C;

	while(*ptarUartCout != 0);
	*ptarmUartDout = c;
}


// Output a string to UART. Not a thread-safe function.
void ptarmUartOutputStr(const char * str) {
	while (*str != 0) {
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
char ptarmStringBuffer[11];


// Return a string representation of a signed integer value.
const char * itoa(const int n) {
	int next = 0;
	int number = n;
	
	if (number < 0) {
        ptarmStringBuffer[next++] = '-';
		number = -number;
	}
	
	if (number == 0) {
		ptarmStringBuffer[next++] = '0';
	} else {
		int flag = 0;
		register int k = 100000;
		while (k > 0) {
			register int r = number / k;
			if (flag || r > 0) {
				ptarmStringBuffer[next++] = '0' + r;
				flag = 1;
			}
			number -= r * k;
			k = k / 10;
		}
	}
	
	ptarmStringBuffer[next] = 0;
	return ptarmStringBuffer;
}


// Return a string representation of an unsigned integer value.
const char * utoa(const unsigned int n) {
	int next = 0;
	unsigned int number = n;

	if (number == 0) {
		ptarmStringBuffer[next++] = '0';
	} else {
		int flag = 0;
		register unsigned int k = 1000000000;
		while (k > 0) {
			register unsigned int r = number / k;
			if (flag || r > 0) {
				ptarmStringBuffer[next++] = '0' + r;
				flag = 1;
			}
			number -= r * k;
			k = k / 10;
		}
	}
	
	ptarmStringBuffer[next] = 0;
	return ptarmStringBuffer;
}


// Return a string representation of an unsigned hexadecimal value.
const char * hex(const unsigned int number) {
	ptarmStringBuffer[0] = '0';
	ptarmStringBuffer[1] = 'x';
	int i, k;
	for(i = 32-4, k = 2; i >= 0; i -= 4, k++) {
		unsigned int a = (number >> i) & 0xf;
		if (a < 10) {
			ptarmStringBuffer[k] = a + '0';
		} else {
			ptarmStringBuffer[k] = a + 'a' - 10;
		}
	}
	
	ptarmStringBuffer[k] = 0;
	return ptarmStringBuffer;
}

#endif /* PTARM_IO_H */

