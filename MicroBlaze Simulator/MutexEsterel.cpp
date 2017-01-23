#include "MutexEsterel.hpp"

#include <iostream>

const bool MutexEsterel::fslIsBusyKey ( void * instance, const std::string type, const unsigned * rA ) {
	MutexEsterel * mutex = (MutexEsterel *) instance ;

	// Busy if the key is not going to be free.
	return (mutex->key != MutexEsterel::FREE || mutex->nextKey != MutexEsterel::FREE) ;
}

// Not used. Return a default value of 0.
void MutexEsterel::getKey ( void * instance, unsigned * rD ) {
	*rD = 0;
}

// Set the key to use the mutex.
void MutexEsterel::putKey ( void * instance, const unsigned * rA ) {
	MutexEsterel * mutex = (MutexEsterel *) instance ;
	mutex->nextKey = *rA ;
}

const bool MutexEsterel::fslIsBusyLock ( void * instance, const std::string type, const unsigned * rA ) {
	MutexEsterel * mutex = (MutexEsterel *) instance ;
	
	// Not busy if the key does not exist, the associated value is 0 (shared variables), or the new value is 0 (signals).
	return !(mutex->data.find(mutex->key) == mutex->data.end() || mutex->data[mutex->key] == 0 || *rA == 0) ;
}

// Not used. Return a default value of 0.
void MutexEsterel::getLock ( void * instance, unsigned * rD ) {
	*rD = 0;
}

// Set the value associated with the current key. Mutex is then released.
// MutexEsterel::putKey assumed to be used beforehand.
void MutexEsterel::putLock ( void * instance, const unsigned * rA ) {
	MutexEsterel * mutex = (MutexEsterel *) instance ;
	mutex->nextData[mutex->key] = *rA ;
	mutex->nextKey = MutexEsterel::FREE ;
}

const bool MutexEsterel::fslIsBusyUnlock ( void * instance, const std::string type, const unsigned * rA ) {
	return false;
}

// Returns the value of the lock for the current key. For signal resolution only. Mutex is then released.
// MutexEsterel::putKey assumed to be used beforehand.
void MutexEsterel::getUnlock ( void * instance, unsigned * rD ) {
	MutexEsterel * mutex = (MutexEsterel *) instance ;
    *rD = mutex->data[mutex->key];
	mutex->nextKey = MutexEsterel::FREE;
}

// Decrements the value of the lock for the given key.
// Multiported design.
void MutexEsterel::putUnlock ( void * instance, const unsigned * rA ) {
	MutexEsterel * mutex = (MutexEsterel *) instance ;
	if (mutex->nextData.find(*rA) != mutex->nextData.end()) {
		if (mutex->nextData[*rA]) {
			mutex->nextData[*rA]-- ;
		}
	}
/*
	for (std::map<unsigned, unsigned>::const_iterator add = mutex->data.begin(); add != mutex->data.end(); ++add) {
		std::cout << std::hex << add->first << ":" << add->second << " ";
	}
	std::cout << std::endl;*/
}

// Constructor.
MutexEsterel::MutexEsterel ( void ) {
	this->nextData.clear();
	this->nextKey = MutexEsterel::FREE;
}

// Simulation timestep.
void MutexEsterel::step ( void ) {
	this->data = this->nextData;
	this->key = this->nextKey;
}


