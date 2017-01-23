#include <iostream>
#include <cstdlib>
#include <fstream>

#include "SharedMemoryBus.hpp"

const std::string SharedMemoryBus::latencyFilePath = "SharedMemoryLatencies.txt";

std::map<std::string, int> SharedMemoryBus::latencies;
unsigned SharedMemoryBus::numberOfRequesters;
unsigned SharedMemoryBus::currentRequester;
bool SharedMemoryBus::isLoad;
unsigned SharedMemoryBus::remainingSlotSize;
std::vector<int> SharedMemoryBus::remainingLatency;
unsigned SharedMemoryBus::originalRemainingLatency;

void SharedMemoryBus::initialise ( const unsigned numberOfRequesters ) {
	SharedMemoryBus::remainingSlotSize = SharedMemoryBus::latencies["slotSize"] ;
	SharedMemoryBus::numberOfRequesters = numberOfRequesters ;
	SharedMemoryBus::currentRequester = 0;
	
	SharedMemoryBus::originalRemainingLatency = 0;
	for (unsigned i = 0; i < numberOfRequesters; ++i) {
		SharedMemoryBus::remainingLatency.push_back(-1) ;
	}
	
	SharedMemoryBus::latencies.clear();
	const std::string mbSimPath = getenv("MB_SIM_PATH");
	if (mbSimPath.compare("") == 0) {
		throw std::string("Check your environment for MB_SIM_PATH: \"" + mbSimPath + "\"");
	}

	std::string filePath = mbSimPath + SharedMemoryBus::latencyFilePath;
	std::ifstream inFile(filePath.c_str());
	if (!inFile.good()) {
		throw std::string("SharedMemoryBus::initialise: Unable to open file \"" + filePath + "\".");
	}

	std::string memory;
	int latency;

	while (!inFile.eof()) {
		inFile >> memory >> latency;
		if (memory.compare(0, 2, "//") != 0) {
			SharedMemoryBus::latencies[memory] = latency;
		}
	}
}

void SharedMemoryBus::step ( void ) {
	if (SharedMemoryBus::remainingLatency[SharedMemoryBus::currentRequester] > 0 ) {
		SharedMemoryBus::remainingLatency[SharedMemoryBus::currentRequester]--;
	}
	
	if ( SharedMemoryBus::remainingSlotSize == 0 ) {
		// Reset slot size.
		SharedMemoryBus::remainingSlotSize = SharedMemoryBus::latencies["slotSize"] ;
		if ( SharedMemoryBus::numberOfRequesters > 1 ) {
			// Reset remainingLatency for the current requester if its request was unfulfilled.
			if ( SharedMemoryBus::remainingLatency[SharedMemoryBus::currentRequester] != -1 ) {
				SharedMemoryBus::remainingLatency[SharedMemoryBus::currentRequester] = SharedMemoryBus::originalRemainingLatency ;
			//	std::cout << "Out of time " << SharedMemoryBus::remainingLatency[SharedMemoryBus::currentRequester] << std::endl;
			}

			// Set the next requester.
			SharedMemoryBus::currentRequester = (SharedMemoryBus::currentRequester + 1) % SharedMemoryBus::numberOfRequesters ;
		//	std::cout << "Next " << SharedMemoryBus::remainingLatency[SharedMemoryBus::currentRequester] << std::endl;
		}
	}
	
	SharedMemoryBus::remainingSlotSize-- ;
//	std::cout << "Turn " << SharedMemoryBus::currentRequester << std::endl;
}

const bool SharedMemoryBus::busIsBusy ( const unsigned requester , const unsigned address , const bool isLoad ) {
	if ( SharedMemoryBus::currentRequester == requester ) {
		// If granted requester
		
		if ( SharedMemoryBus::remainingLatency[requester] == 0 ) {
			// If previous request has completed.
			
			SharedMemoryBus::remainingLatency[requester] = -1 ;
		//	std::cout << "Success" << std::endl;
			return false;
		} else if ( SharedMemoryBus::remainingLatency[requester] == -1 ) {
			// If no request is in progress.
			if ( isLoad ) {
				if (0x80000000 <= address && address <= 0x83FFFFFF) {
					// DDR SDRAM.
					SharedMemoryBus::remainingLatency[requester] = SharedMemoryBus::latencies["loadLatencyDdrSdram"] ;
				} else if (0x85390000 <= address && address <= 0x8548FFFF) {
					// Shared on-chip.
					SharedMemoryBus::remainingLatency[requester] = SharedMemoryBus::latencies["loadLatencySharedOnChip"] ;
				} else if (0x86300000 <= address && address <= 0x863FFFFF) {
					// SRAM.
					SharedMemoryBus::remainingLatency[requester] = SharedMemoryBus::latencies["loadLatencySram"] ;
				}
			} else {
				if (0x80000000 <= address && address <= 0x83FFFFFF) {
					// DDR SDRAM.
					SharedMemoryBus::remainingLatency[requester] = SharedMemoryBus::latencies["storeLatencyDdrSdram"] ;
				} else if (0x85390000 <= address && address <= 0x8548FFFF) {
					// Shared on-chip.
					SharedMemoryBus::remainingLatency[requester] = SharedMemoryBus::latencies["storeLatencySharedOnChip"] ;
				} else if (0x86300000 <= address && address <= 0x863FFFFF) {
					// SRAM.
					SharedMemoryBus::remainingLatency[requester] = SharedMemoryBus::latencies["storeLatencySram"] ;
				}
			}
			
			SharedMemoryBus::remainingLatency[SharedMemoryBus::currentRequester]--;
			SharedMemoryBus::originalRemainingLatency = SharedMemoryBus::remainingLatency[SharedMemoryBus::currentRequester];
		//	std::cout << "Request " << SharedMemoryBus::originalRemainingLatency << std::endl;
		}
	}
	
	return true;
}



