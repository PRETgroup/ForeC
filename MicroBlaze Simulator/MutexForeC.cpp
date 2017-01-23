#include "MutexForeC.hpp"

const bool MutexForeC::fslIsBusy ( void * instance, const std::string type, const unsigned * rA ) {
	// No arbitration needed; this is a multiported mutex.
	return false;
}

// Get the array of bits.
void MutexForeC::get ( void * instance, unsigned * rD ) {
	MutexForeC * mutex = (MutexForeC *) instance ;
	*rD = mutex -> bitPattern ;
}

// Set the value of a bit.
void MutexForeC::put ( void * instance, const unsigned * rA ) {
	MutexForeC * mutex = (MutexForeC *) instance ;
	const unsigned value = *rA & 0x1 ;
	const unsigned position = (*rA >> MutexForeC::CONTROL_WIDTH) ;
	
	switch (value) {
		case 0:
			mutex -> nextBitPattern &= ~( 1 << position ) ;
			break;
		case 1:
			mutex -> nextBitPattern |= ( 1 << position ) ;
			break;
		default:
			break;
	}
}

// Get the array of bits.
void MutexForeC::getReset ( void * instance, unsigned * rD ) {
	MutexForeC * mutex = (MutexForeC *) instance ;
	*rD = mutex -> bitPattern ;
}

// Reset the value of every bit to 1.
void MutexForeC::putReset ( void * instance, const unsigned * rA ) {
	MutexForeC * mutex = (MutexForeC *) instance ;
	mutex -> nextBitPattern = -1;
}

// Constructor.
MutexForeC::MutexForeC ( void ) {
	bitPattern = -1;
	nextBitPattern = -1;
}

// Simulation timestep.
void MutexForeC::step ( void ) {
	bitPattern = nextBitPattern;
}


