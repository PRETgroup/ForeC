#include "Counter.hpp"

const bool Counter::fslIsBusy ( void * instance, const std::string type, const unsigned * rA ) {
	// No arbitration.
	return false;
}

void Counter::get ( void * instance, unsigned * rD ) {
	Counter * counter = (Counter *) instance ;
	*rD = counter -> counts;
}

void Counter::put ( void * instance, const unsigned * rA ) {
	Counter * counter = (Counter *) instance ;
	switch (counter -> state) {
		case Counter::IDLE:
			counter -> state = Counter::COUNTING;
			counter -> counts = *rA;
			break;
		case Counter::COUNTING:
			counter -> state = Counter::IDLE;
			break;
		default:
			break;
	}
}

Counter::Counter ( void ) {
	state = Counter::IDLE;
	counts = 0;
}

void Counter::step ( void ) {
	if (state == Counter::COUNTING) {
		counts++;
	}
}


