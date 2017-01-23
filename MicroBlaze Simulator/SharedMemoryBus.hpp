#ifndef SHARED_MEMORY_BUS_HPP
#define SHARED_MEMORY_BUS_HPP

#include <vector>
#include <map>

class SharedMemoryBus {
	// Static
	public:
		static void initialise ( const unsigned numberOfRequesters ) ;
		
		static void step ( void ) ;
		static const bool busIsBusy ( const unsigned requester , const unsigned address , const bool isLoad ) ;
		
	private:
		static const std::string latencyFilePath ;
		
		// map<memoryName, latency>
		static std::map<std::string, int> latencies;

		static unsigned numberOfRequesters;
		
		static unsigned currentRequester;
		static bool isLoad;
		static unsigned remainingSlotSize;
		static unsigned originalRemainingLatency;
		
		// vector<remainingLatency>
		static std::vector<int> remainingLatency;

};

#endif /* SHARED_MEMORY_BUS_HPP */
