/*
 * Scratchpad MMU - Simulator main module
 * Copyright (C) Jack Whitham 2009
 * http://www.jwhitham.org.uk/c/smmu.html
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation
 * (version 2.1 of the License only).
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include <iomanip>
#include <iostream>
#include <vector>

#include "System.hpp"
#include "MicroBlaze.hpp"
#include "MicroBlazeElf.hpp"
#include "Counter.hpp"
#include "MutexEsterel.hpp"
#include "MutexForeC.hpp"
#include "Uart.hpp"
#include "SharedMemoryBus.hpp"
#include "ThreadQueue.hpp"

static int stop = 0 ;
bool quiet = true;
unsigned int numberOfCores;
std::vector<MicroBlaze *> cores;


static void Trace ( MicroBlaze::TraceName trace_name , const void * param ) {
    unsigned param_u = (unsigned) ( (uintptr_t) param ) ;

    /* Exit command */
    if (( trace_name == MicroBlaze::SIM_CMD ) && ( param_u == 1 )) {
        stop = 1 ;
    }
    if (quiet) {
		/* Operations that should be printed when "quiet" */
		if (( trace_name != MicroBlaze::RESET ) && ( trace_name != MicroBlaze::DIV_BY_ZERO ) && ( trace_name != MicroBlaze::ILLEGAL_INST ) && ( trace_name != MicroBlaze::ALIGN )) {
		    return ;
    	}
	}

    switch ( trace_name ) {
        case MicroBlaze::RESET :
                printf ( "       RESET" ) ;
                break ;
        case MicroBlaze::INTERRUPT :
                printf ( "       INTERRUPT" ) ;
                break ;
        case MicroBlaze::SPR_READ :
                printf ( "       SPR_READ" ) ;
                break ;
        case MicroBlaze::SPR_WRITE :
                printf ( "       SPR_WRITE, value 0x%x" , param_u ) ;
                break ;
        case MicroBlaze::CALL :
                printf ( "       CALL to pc 0x%x" , param_u ) ;
                break ;
         case MicroBlaze::RETURN :
                printf ( "       RETURN to pc 0x%x" , param_u ) ;
                break ;
        case MicroBlaze::ILLEGAL_INST :
                stop = 1 ;
                printf ( "       ILLEGAL_INST, pc 0x%x", param_u ) ;
                break ;
        case MicroBlaze::DIV_BY_ZERO :
                stop = 1 ;
                printf ( "       DIV_BY_ZERO" ) ;
                break ;
        case MicroBlaze::EXECUTE :
                printf ( "       EXECUTE %s" , (const char *) param ) ;
                return ;
        case MicroBlaze::SIM_CMD :
                printf ( "       SIM_CMD" ) ;
                break ;
        case MicroBlaze::ALIGN :
                stop = 1 ;
                printf ( "       ALIGN" ) ;
                break ;
        default :
        	//	printf ( "Unknown trace name (%d)" , (int) trace_name ) ;
                return ;
    }
    printf ( "\n" ) ;
}


static void Program_Aborted ( int signum, siginfo_t * siginfo, void * data ) {
    for ( unsigned int i = 0; i < numberOfCores; ++i) {
		if ( cores[i] != NULL ) {
		    printf ( "Core %d aborted at PC 0x%08x, instruction 0x%08x, r15 = 0x%08x\n" , i, cores[i] -> prev_pc , cores[i] -> cur_iword, cores[i] -> gpr [ 15 ] ) ;
		}
	}

    exit ( 1 );
}


int main ( const int argc , const char * argv[] ) {
    if ( argc < 3 ) {
        printf ( "Usage: %s <no. of cores> <elf binary> [-verbose]\n" , argv [ 0 ] ) ;
        return 1 ;
    }

    if (argc == 4 ) {
    	if (strcmp(argv[3], "-verbose") == 0) {
    		quiet = false;
    	}
    }
    
    numberOfCores = atoi(argv [ 1 ]) ;
	{
		char numberOfCoresChar[256];
		sprintf(numberOfCoresChar, "%d", numberOfCores);
		if (strcmp(argv[1], numberOfCoresChar)) {
			printf ( "Usage: %s <no. of cores> <elf binary> [-verbose]\n" , argv [ 0 ] ) ;
			printf ( "<no. of cores> must be a number!\n" ) ;
			return 1;
		}
	}
	
    SharedMemoryBus::initialise(numberOfCores);
    
	// Mutexes
	MutexEsterel * mutexEsterel = new MutexEsterel () ;
	MutexForeC * mutexForeC = new MutexForeC () ;
	
	// Thread queue
	ThreadQueue * threadQueue = new ThreadQueue () ;
	
	std::vector<System *> systems;
    for ( unsigned int i = 0; i < numberOfCores; ++i) {
		// Create a system.
        systems.push_back( new System ( Trace ) ) ;
        systems[i] -> mapIo ( 0x84400000 >> System::PAGE_SHIFT , Uart::load , Uart::store , NULL ) ;
		
		// Create a core.
		cores.push_back( new MicroBlaze ( i , systems[i], Trace , System::busIsBusy, System::load, System::store ) ) ;
		cores[i] -> mapFsl ( (void *) mutexForeC, 0 , MutexForeC::get, MutexForeC::put, MutexForeC::fslIsBusy ) ;
		cores[i] -> mapFsl ( (void *) mutexEsterel, 3 , MutexEsterel::getKey, MutexEsterel::putKey, MutexEsterel::fslIsBusyKey ) ;
		cores[i] -> mapFsl ( (void *) mutexEsterel, 4 , MutexEsterel::getLock, MutexEsterel::putLock, MutexEsterel::fslIsBusyLock ) ;
		cores[i] -> mapFsl ( (void *) mutexEsterel, 5 , MutexEsterel::getUnlock, MutexEsterel::putUnlock, MutexEsterel::fslIsBusyUnlock ) ;
		cores[i] -> mapFsl ( (void *) threadQueue, 6 , ThreadQueue::get, ThreadQueue::put, ThreadQueue::fslIsBusy ) ;
		
		// Load the program.
		const char * out = MicroBlazeElf::readElf ( cores[i], argv [ 2 ] ) ;
		if ( out != NULL ) {
		    printf ( "ELF read error: %s\n" , out ) ;
		    return 1 ;
		}
    }

    // Mutexes reset
	cores[0] -> mapFsl ( (void *) mutexForeC, 1, MutexForeC::getReset, MutexForeC::putReset, MutexForeC::fslIsBusy ) ;

    // Counter
	Counter * counter = new Counter () ;
	cores[0] -> mapFsl ( (void *) counter, 2, Counter::get, Counter::put, Counter::fslIsBusy ) ;

    /* SIGABRT is raised by assertion failure */
    {
        struct sigaction sa;
        sa.sa_sigaction = Program_Aborted;
        sa.sa_flags = SA_SIGINFO;
        sigemptyset(&sa.sa_mask);
        sigaction(SIGABRT, &sa, NULL);
        sigaction(SIGINT, &sa, NULL);
    }

    /* Simulate */
    unsigned clockCycles = 1;
    while ( ! stop ) {
		if (!quiet) {
			std::cout << std::setfill('-') << std::setw(80) << std::left << clockCycles << std::endl;
		}
		
    	SharedMemoryBus::step();
    	counter -> step();
    	mutexForeC -> step();
    	mutexEsterel -> step();
    	threadQueue -> step();

		for ( unsigned int i = 0; i < numberOfCores; ++i) {
        	cores[i] -> step(0);
			if (!quiet) {
				std::cout << cores[i] -> toString() << std::endl;
			}
        }
        
        clockCycles++;
    }

	for ( unsigned int i = 0; i < numberOfCores; ++i) {
    	delete systems[i] ;
    	delete cores[i] ;
    }
    
    return 0 ;
}


