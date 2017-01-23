#ifndef THREAD_QUEUE_HPP
#define THREAD_QUEUE_HPP

#include <queue>
#include <string>

class ThreadQueue {
	// Static
	public:
		static const bool fslIsBusy ( void * instance, const std::string type, const unsigned * rA ) ;
		static void get ( void * instance, unsigned * rD ) ;
		static void put ( void * instance, const unsigned * rA ) ;
		
		
	// Dynamic
	public:
		ThreadQueue ( void ) ;
		void step ( void ) ;
	
	private:
		std::queue<int> threads;
		bool queueModified;
	
};

#endif /* THREAD_QUEUE_HPP */
