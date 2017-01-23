/* Custom implementation of barriers using
 * a mutex, condition variable, and two integers to
 * track how many threads are in the barrier.
 *
 * Based on http://www.howforge.com/implementing-barrier-in-pthreads
 */

#ifndef BARRIER_H
#define BARRIER_H

#include <pthread.h>

// Barrier data type
typedef struct {
	unsigned int count;		// Number of threads that need to be in the barrier.
	unsigned int reached;	// Number of threads that have reached the barrier.
	unsigned int event;		// Each barrier synchronisation is given a unique event ID.
	pthread_mutex_t mutex;
	pthread_cond_t cond;
} barrier_t;

typedef struct {
	// We do not support barrier attributes, yet.	
} barrierattr_t;

// -1 is distinct from all other error values.
#define BARRIER_SERIAL_THREAD	-1

// Function to initialise a barrier object.
// We do not support barrier attributes, yet.
int barrier_init(barrier_t *barrier, const barrierattr_t *attr, unsigned int count) {
	barrier->count = count;
	barrier->reached = 0;
	barrier->event = 0;
	pthread_mutex_init(&barrier->mutex, NULL);
	pthread_cond_init(&barrier->cond, NULL);
	return 0;
}

// Function to change the value of count. Not atomic!
int barrier_count(barrier_t *barrier, unsigned int count) {
	barrier->count = count;
	return 0;
}

// Function to destroy a barrier object.
int barrier_destroy(barrier_t *barrier) {
	pthread_mutex_destroy(&barrier->mutex);
	pthread_cond_destroy(&barrier->cond);
	barrier->count = -1;
	barrier->reached = -1;
	barrier->event = 0;
	return 0;
}

// Function to wait until all participating threads are in the barrier.
int barrier_wait(barrier_t *barrier) {
	int result = 0;

	// Obtain a lock on the barrier object before we modify it.
	pthread_mutex_lock(&barrier->mutex);

	// Decrement the number of threads that are not in the barrier.
	++barrier->reached;

	// Check if all threads are in the barrier.
	if (barrier->reached == barrier->count) {
		// All threads are in the barrier.
		
		// Increment the event ID.
		++barrier->event;
		
		// Reset the number that need to be in the barrier.
		barrier->reached = 0;
		
		// Allow all threads to go through the barrier.
		pthread_cond_broadcast(&barrier->cond);
		
		// This is the thread which finished the serialisation.
		result = BARRIER_SERIAL_THREAD;
	} else {
		// Some threads are not in the barrier.
		
		// Make a copy of the current event ID.
		int event = barrier->event;
		
		// Sleep the calling thread until all threads are in the barrier.
		// The while loop is to make the waiting robust to suprious wakeups.
		do {
			// The cond_wait function automatically releases the mutex when it busy waits.
			pthread_cond_wait(&barrier->cond, &barrier->mutex);
		} while (event == barrier->event);
	}

	// Unlock the mutex.
	pthread_mutex_unlock(&barrier->mutex);
	return result;
}

/*
// Function to change the value of count atomically.
// Unfortunately, we the lowlevellock.h file is not part of the Linux distribution.
int pthread_barrier_count(pthread_barrier_t *barrier, unsigned int count) {
	struct pthread_barrier *ibarrier = (struct pthread_barrier *)barrier;
	
	// Make sure we are alone.
	lll_lock (ibarrier->lock, ibarrier->private ^ FUTEX_PRIVATE_FLAG);

	ibarrier->left = count - ibarrier->init_count + ibarrier->left;	// Someone could be changing this.
	ibarrier->init_count = count;

	// We are done.
	lll_unlock (ibarrier->lock, ibarrier->private ^ FUTEX_PRIVATE_FLAG);
	
	return 0;
}
*/

#endif // BARRIER_H
