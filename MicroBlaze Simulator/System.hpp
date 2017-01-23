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
 
#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#ifdef __MICROBLAZE__
	#define htonl(x) (x)
	#define ntohl(x) (x)
	#define uintptr_t unsigned
#else
	#include <arpa/inet.h>
	#undef PAGE_SIZE
#endif

#include "MicroBlaze.hpp"

class System {
	// Static
	public:
		static const unsigned PAGE_SHIFT = 16 ;
	
		static const bool busIsBusy ( MicroBlaze * core, unsigned address , const bool isLoad ) ;
		static const unsigned load ( MicroBlaze * core, unsigned address , unsigned size ) ;
		static void store ( MicroBlaze * core, unsigned address , unsigned data , unsigned size ) ;
		
	private:
		static const unsigned PAGE_SIZE = 0x10000 ;
		static const unsigned NUM_PAGES = 0x10000 ;
		static const unsigned EMPTY_MEMORY_IS = 0 ;
		static const unsigned CHECK = 0xc8f3680a ;

		typedef struct MB_Memory_Page_struct {
			unsigned *          data ;
			MicroBlaze::LoadFn          io_load_fn ;
			MicroBlaze::StoreFn         io_store_fn ;
		} MB_Memory_Page ;
		
		static MB_Memory_Page shared_memory_page [ NUM_PAGES ] ;

		static int Is_IO_Page ( MB_Memory_Page * p );
		static void Page_Store ( unsigned * page_data , const unsigned address , const unsigned data , const unsigned size ) ;
		static const unsigned Page_Load ( const unsigned * page_data , const unsigned address , const unsigned size ) ;

		
	// Dynamic
	public:
		System ( MicroBlaze::TraceFn traceFn ) ;
		~System ( void ) ;
		
		void mapIo ( const unsigned page , const MicroBlaze::LoadFn loadFn , const MicroBlaze::StoreFn storeFn , void * io_user ) ;
		void unmapIo ( unsigned page ) ;

		void MB_Write ( unsigned address , const char * data , unsigned size ) ;
		void MB_Read ( unsigned address , char * data , unsigned size ) ;
		unsigned MB_Write_From_File ( unsigned address , const int fd , unsigned size ) ;
		unsigned MB_Read_To_File ( unsigned address , const int fd , unsigned size ) ;
	
	private:
		unsigned check ;
		MB_Memory_Page memory_page [ NUM_PAGES ] ;

		MB_Memory_Page * Lookup ( const unsigned page , const int allocate ) ;
		unsigned MB_Access ( unsigned address , char * data , unsigned size , const int write_flag , const int fd ) ;
	
};

#endif /* SYSTEM_HPP */

