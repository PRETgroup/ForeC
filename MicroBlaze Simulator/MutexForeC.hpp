// Mutex required by ForeC. The parent threads own a 
// bit within the an array of bits (bitPattern) to 
// synchronize with its child threads. Parent threads 
// set their bit to 1 to indicate that the child threads
// should not be executing. Their bit is set to 0 if it
// is okay for the child threads to read the shared 
// control variables (e.g., parStatus).


#ifndef MUTEX_FOREC_HPP
#define MUTEX_FOREC_HPP

#include <string>

class MutexForeC {
	// Static
	public:
		static const bool fslIsBusy ( void * instance, const std::string type, const unsigned * rA ) ;
		static void get ( void * instance, unsigned * rD ) ;
		static void put ( void * instance, const unsigned * rA ) ;
		static void getReset ( void * instance, unsigned * rD ) ;
		static void putReset ( void * instance, const unsigned * rA ) ;
		
	private:
		static const unsigned CONTROL_WIDTH = 1;

		
	// Dynamic
	public:
		MutexForeC ( void ) ;
		void step ( void ) ;
	
	private:
		unsigned bitPattern;
		unsigned nextBitPattern;
	
};

#endif /* MUTEX_FOREC_HPP */
