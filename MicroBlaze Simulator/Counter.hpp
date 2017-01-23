#ifndef COUNTER_HPP
#define COUNTER_HPP

#include <string>

class Counter {
	// Static
	public:
		static const bool fslIsBusy ( void * instance, const std::string type, const unsigned * rA ) ;
		static void get ( void * instance, unsigned * rD ) ;
		static void put ( void * instance, const unsigned * rA ) ;

	
	// Dynamic
	public:
		Counter ( void ) ;
		void step ( void ) ;
		
	private:
		typedef enum {
			IDLE,
			COUNTING
		} State;
		
		State state;
		unsigned long long counts;

};

#endif /* COUNTER_HPP */
