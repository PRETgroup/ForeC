#ifndef UART_HPP
#define UART_HPP

#include <string>
#include <map>

#define XUN_LSR_TX_BUFFER_EMPTY	0x20 // Transmit holding reg empty
#define XUN_THR_OFFSET			0x04 // Transmit holding register

class MicroBlaze;

class Uart {
	// Static
	public:
		static const bool busIsBusy ( void ) ;
		static const unsigned load ( MicroBlaze * core, const unsigned address , const unsigned size ) ;
		static void store ( MicroBlaze * core, const unsigned address , const unsigned data , const unsigned size ) ;

	private:
		// Buffer the standard output from each core until a new line is encountered.
		static std::map<MicroBlaze *, std::string> buffer;
};

#endif /* UART_HPP */
