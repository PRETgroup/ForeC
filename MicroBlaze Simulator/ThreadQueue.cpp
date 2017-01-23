#include "ThreadQueue.hpp"

#include <iostream>

const bool ThreadQueue::fslIsBusy ( void * instance, const std::string type, const unsigned * rA ) {
	ThreadQueue * threadQueue = (ThreadQueue *) instance ;

	if (type.compare("put") == 0) {
		// Busy if the queue has been modified.
		return threadQueue->queueModified;
	} else if (type.compare("get") == 0) {
		// Busy if the queue is empty or has been modified.
		return (threadQueue->threads.empty() || threadQueue->queueModified);
	}

	return true;
}

void ThreadQueue::get ( void * instance, unsigned * rD ) {
	ThreadQueue * threadQueue = (ThreadQueue *) instance ;
	*rD = threadQueue->threads.front();
	threadQueue->threads.pop();
	threadQueue->queueModified = true;
}

void ThreadQueue::put ( void * instance, const unsigned * rA ) {
	ThreadQueue * threadQueue = (ThreadQueue *) instance ;
	threadQueue->threads.push(*rA);
	threadQueue->queueModified = true;
}

ThreadQueue::ThreadQueue ( void ) {
	queueModified = false;
}

void ThreadQueue::step ( void ) {
/*	if (queueModified) {
		std::cout << "size: " << threads.size() << std::hex << " last: " << threads.back() << std::endl;
	}*/
	
	queueModified = false;
}


