#include <stdio.h>

#include "Uart.hpp"

#include "MicroBlaze.hpp"

std::map<MicroBlaze *, std::string> Uart::buffer;

const bool Uart::busIsBusy ( void ) {
	// No arbitration.
	return false;
}

const unsigned Uart::load ( MicroBlaze * core, unsigned address, unsigned size ) {
    return XUN_LSR_TX_BUFFER_EMPTY ; 
}

void Uart::store ( MicroBlaze * core, unsigned address, unsigned data, unsigned size ) {
    address &= 0x1f ;
    if ( address == XUN_THR_OFFSET ) {
    	Uart::buffer[core].push_back( (char) data );
    	if ( (char) data == '\n' ) {
	        fputs ( Uart::buffer[core].c_str() , stdout ) ;
    	    fflush ( stdout ) ;
    	    buffer[core].clear();
    	}
    }
}


