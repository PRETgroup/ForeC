// Mutex required by Esterel. The mutex is used to 
// protect shared control variables (e.g., number of 
// threads alive) and to track the number of potential
// signal emitters.

#ifndef MUTEX_ESTEREL_HPP
#define MUTEX_ESTEREL_HPP

#include <map>
#include <string>

class MutexEsterel {
	// Static
	public:
		static const bool fslIsBusyKey ( void * instance, const std::string type, const unsigned * rA );
		static void getKey ( void * instance, unsigned * rD );
		static void putKey ( void * instance, const unsigned * rA );
		
		static const bool fslIsBusyLock ( void * instance, const std::string type, const unsigned * rA );
		static void getLock ( void * instance, unsigned * rD );
		static void putLock ( void * instance, const unsigned * rA );
		
		static const bool fslIsBusyUnlock ( void * instance, const std::string type, const unsigned * rA );
		static void getUnlock ( void * instance, unsigned * rD );
		static void putUnlock ( void * instance, const unsigned * rA );
		
	private:
		static const unsigned FREE = 0xFFFFFFFF;
		
		
	// Dynamic
	public:
		MutexEsterel ( void ) ;
		void step ( void ) ;
	
	private:
		// map<address, value>
		std::map<unsigned, unsigned> data;
		std::map<unsigned, unsigned> nextData;
		
		unsigned key;
		unsigned nextKey;
	
};

#endif /* MUTEX_ESTEREL_HPP */
