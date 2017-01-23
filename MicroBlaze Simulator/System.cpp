/*
 * Scratchpad MMU - Simulated memory and IO devices
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
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include "System.hpp"
#include "Uart.hpp"
#include "PrivateMemoryBus.hpp"
#include "SharedMemoryBus.hpp"

System::MB_Memory_Page System::shared_memory_page[];

System::System ( MicroBlaze::TraceFn traceFn ) {
    this -> check = System::CHECK ;
}

System::~System ( void ) {
    unsigned i ;

    assert ( check == System::CHECK ) ;
    for ( i = 0 ; i < System::NUM_PAGES ; i ++ ) {
        unsigned * d = memory_page [ i ] . data ;

        if ( d != NULL ) {
            free ( d ) ;
        }
    }
}

// No side-effects
int System::Is_IO_Page ( System::MB_Memory_Page * p ) {
    return ( p -> io_load_fn != NULL ) ;
}

// No side-effects
System::MB_Memory_Page * System::Lookup ( const unsigned page , const int allocate ) {
    System::MB_Memory_Page * p ;

    assert ( page < System::NUM_PAGES ) ;
    
	if ( /*(0x00000000 >> System::PAGE_SHIFT) <= page &&*/ page <= (0x0007FFFF >> System::PAGE_SHIFT) ) {
		// Private on-chip memory
    	p = & memory_page [ page ] ;
    } else {
    	// Shared memory
    	p = & System::shared_memory_page [ page ] ;
    }
    
    if (( p -> data == NULL ) && ( allocate ) && ( ! System::Is_IO_Page ( p ))) {
        p -> data = (unsigned *)malloc ( System::PAGE_SIZE ) ;
        assert ( p -> data != NULL ) ;
        memset ( p -> data , (unsigned char) System::EMPTY_MEMORY_IS , System::PAGE_SIZE ) ;
    }
    return p ;
}

// Modifies page_data
void System::Page_Store ( unsigned * page_data , const unsigned address , const unsigned data , const unsigned size ) {
    unsigned within_page = address >> 2 ;
    unsigned within_word = ( address & 3 ) ;
    unsigned mask , modify , shift ; 

    if ( size == 4 ) {
        page_data [ within_page ] = htonl ( data ) ;
        return ;
    } else if ( size == 2 ) {
        mask = 0xffff ;
        shift = (( 2 - within_word ) * 8 ) ;
    } else {
        mask = 0xff ;
        shift = (( 3 - within_word ) * 8 ) ;
    }
    modify = ntohl ( page_data [ within_page ] ) ;
    modify &= ~ ( mask << shift ) ;
    modify |= ( data & mask ) << shift ;
    page_data [ within_page ] = htonl ( modify ) ;
}

// No side-effects
const unsigned System::Page_Load ( const unsigned * page_data , const unsigned address , const unsigned size ) {
    unsigned within_page = address >> 2 ;
    unsigned within_word = ( address & 3 ) ;
    unsigned data = ntohl ( page_data [ within_page ] ) ;

    if ( size == 4 ) {
        return data ;
    } else if ( size == 2 ) {
        return ( data >> (( 2 - within_word ) * 8 )) & 0xffff ;
    } else {
        return ( data >> (( 3 - within_word ) * 8 )) & 0xff ;
    }
}

const bool System::busIsBusy ( MicroBlaze * core, const unsigned address , const bool isLoad ) {
	// Refer to the Xilinx XPS project for the address ranges.
	// Check where the address points to and then return the arbitration result.
	if ( /*0x00000000 <= address &&*/ address <= 0x0007FFFF ) {
		// Private on-chip.
		// No arbitration.
		return PrivateMemoryBus::busIsBusy() ;
	} else if ( (0x80000000 <= address && address <= 0x83FFFFFF) || 
				(0x85390000 <= address && address <= 0x8548FFFF) ||
				(0x86300000 <= address && address <= 0x863FFFFF) ) {
		// DDR SDRAM, Shared on-chip, and SRAM via the same bus.
		return SharedMemoryBus::busIsBusy( core -> getId(), address, isLoad ) ;
	} else if ( 0x84400000 <= address && address <= 0x8440FFFF ) {
		// MDM UART. Assumed to be connected directly to the core.
		return Uart::busIsBusy() ;
	}
	
	return true;
}

// Modifies core -> clock_cycle
const unsigned System::load ( MicroBlaze * core, const unsigned address , const unsigned size ) {
    unsigned page = address >> System::PAGE_SHIFT ;
    System::MB_Memory_Page * p ;

    assert ( core -> system -> check == System::CHECK ) ;
    p = core -> system -> Lookup ( page , 0 ) ;
    if ( p -> data != NULL ) {
        return System::Page_Load ( p -> data , address & ( System::PAGE_SIZE - 1 ) , size ) ;
    } else if ( System::Is_IO_Page ( p ) ) {
        return p -> io_load_fn ( core, address , size ) ;
    } else {
        /* Return 0xff, 0xffff, etc. for invalid page */
        return System::EMPTY_MEMORY_IS >> (( 4UL - size ) * 8UL ) ;
    }
}

// Modifies p, sc -> mb_context -> clock_cycle
void System::store ( MicroBlaze * core, const unsigned address , const unsigned data , const unsigned size ) {
    unsigned page = address >> System::PAGE_SHIFT ;
    System::MB_Memory_Page * p ;

    assert ( core -> system -> check == System::CHECK ) ;
    p = core -> system -> Lookup ( page , 1 ) ;
    if ( System::Is_IO_Page ( p ) ) {
        p -> io_store_fn ( core, address , data , size ) ;
    } else {
        assert ( p -> data != NULL ) ;
        System::Page_Store ( p -> data , address & ( System::PAGE_SIZE - 1 ) , data , size ) ;
    }
}

// Modifies p
void System::mapIo ( const unsigned page , const MicroBlaze::LoadFn loadFn , const MicroBlaze::StoreFn storeFn , void * io_user ) {
    System::MB_Memory_Page * p ;

    assert ( check == System::CHECK ) ;
    p = Lookup ( page , 0 ) ;
    if ( p -> data != NULL ) {
        free ( p -> data ) ;
        p -> data = NULL ;
    }
    p -> io_load_fn = loadFn ;
    p -> io_store_fn = storeFn ;
}

// Modifies p
void System::unmapIo ( const unsigned page ) {
    System::MB_Memory_Page * p ;

    assert ( check == System::CHECK ) ;
    p = Lookup ( page , 0 ) ;
    p -> io_load_fn = NULL ;
    p -> io_store_fn = NULL ;
}

// Modifies p
unsigned System::MB_Access ( unsigned address , char * data , unsigned size , const int write_flag , const int fd ) {
    unsigned total_bytes = 0 ;

    assert ( check == System::CHECK ) ;
    while ( size != 0 ) {
        unsigned page = address >> System::PAGE_SHIFT ;
        unsigned within_page = ( address & ( System::PAGE_SIZE - 1 )) ;
        unsigned space = System::PAGE_SIZE - within_page ;
        System::MB_Memory_Page * p = Lookup ( page , write_flag ) ;
        char * ptr = NULL ;

        
        if ( space > size ) space = size ;

        assert ( ! System::Is_IO_Page ( p ) ) ; /* No access to IO pages */

        if ( p -> data != NULL ) {
            ptr = & (( (char *) p -> data ) [ within_page ] ) ;
        }

        if ( write_flag ) {
            assert ( ptr != NULL ) ;
            if ( fd >= 0 ) {
                ssize_t s = read ( fd , ptr , space ) ;
                assert( s > -1 );
                if ( (unsigned)s != space ) {
                    if ( s > 0 ) {
                        total_bytes += space ;
                    }
                    return total_bytes ;
                }
            } else {
                memcpy ( ptr , data , space ) ;
            }
        } else if ( ptr == NULL ) {
            if ( fd >= 0 ) {
                char blank [ BUFSIZ ] ;
                ssize_t s ;

                if ( space >= BUFSIZ ) space = BUFSIZ ;
                memset ( blank , (unsigned char) System::EMPTY_MEMORY_IS , space ) ;
                s = write ( fd , blank , space ) ;
                assert( s > -1 );
                assert ( (unsigned)s == space ) ;
            } else {
                memset ( data , (unsigned char) System::EMPTY_MEMORY_IS , space ) ;
            }
        } else {
            if ( fd >= 0 ) {
                ssize_t s = write ( fd , ptr , space ) ;
                assert( s > -1 );
                assert ( (unsigned)s == space ) ;
            } else {
                memcpy ( data , ptr , space ) ;
            }
        }
        size -= space ;
        data += space ;
        address += space ;
        total_bytes += space ;
    }
    return total_bytes ;
}

// Modifies p
void System::MB_Write ( unsigned address , const char * data , unsigned size ) {
    System::MB_Access ( address , (char *) data , size , 1 , -1 ) ;
}

// Modifies p
void System::MB_Read ( unsigned address , char * data , unsigned size ) {
    System::MB_Access ( address , data , size , 0 , -1 ) ;
}

// Modifies p
unsigned System::MB_Write_From_File ( unsigned address , const int fd , unsigned size ) {
    return System::MB_Access ( address , NULL , size , 1 , fd ) ;
}

// Modifies p
unsigned System::MB_Read_To_File ( unsigned address , const int fd , unsigned size ) {
    return System::MB_Access ( address , NULL , size , 0 , fd ) ;
}






