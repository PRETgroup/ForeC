/*
 * Scratchpad MMU - Microblaze(tm)-compatible simulator
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

#ifndef MICROBLAZE_HPP
#define MICROBLAZE_HPP

#include <string>

class System;

class MicroBlaze {
	// Static
	public:
		typedef enum {
			RESET , INTERRUPT , SPR_READ , SPR_WRITE , 
			CALL , RETURN , ILLEGAL_INST ,
			DIV_BY_ZERO , EXECUTE , SIM_CMD ,
			ALIGN , STORE , LOAD , SET_D 
		} TraceName ;
		
		// Function pointers
		typedef const bool (* BusIsBusyFn) ( MicroBlaze * core, const unsigned address, const bool isLoad ) ;
		typedef const unsigned (* LoadFn) ( MicroBlaze * core, const unsigned address , const unsigned size ) ;
		typedef void (* StoreFn) ( MicroBlaze * core, const unsigned address , const unsigned data , const unsigned size ) ;
		typedef void (* TraceFn) ( TraceName traceName , const void * param ) ;
		typedef const bool (* FslIsBusyFn) ( void * instance, const std::string type, const unsigned * rA ) ;
		typedef void (* GetFn) ( void * instance, unsigned * rD ) ;
		typedef void (* PutFn) ( void * instance, const unsigned * rA ) ;
		
	private:
		static const unsigned NS = 255 ;
		static const unsigned MSR_BIP = 0x8 ;
		static const unsigned MSR_EIP = 0x200 ;
		static const unsigned MSR_EE = 0x100 ;
		static const unsigned MSR_IE = 0x2 ;
		static const unsigned MSR_C = 0x80000004 ;
		static const unsigned MB_NOP = 0x80000000 ;
		static const unsigned MB_FLUSH_NOP = 0x800007ff ;

		static void * ip ( unsigned x ) ;
		
		static const bool nullFslIsBusy ( void * instance, const std::string type, const unsigned * rA );
		static void nullGet ( void * instance, unsigned * rD );
		static void nullPut ( void * instance, const unsigned * rA );

	// Dynamic
	public:
		unsigned gpr [ 32 ] ;
		unsigned prev_pc;
		unsigned next_iword , cur_iword;
		System * system;

		// Functions
		MicroBlaze( const unsigned pvr0, System * system, TraceFn traceFn , BusIsBusyFn busIsBusyFn, LoadFn loadFn, StoreFn storeFn ) ;
		
		void reset ( void ) ;
		void step ( int interrupt_flag ) ;
		void jump ( unsigned target_pc ) ;
		
		void mapFsl ( void * instance, const unsigned fslx, GetFn getFn, PutFn putFn , FslIsBusyFn fslIsBusyFn ) ;
		
		const unsigned getId(void) ;
		const unsigned getClockCycle(void) ;
		
		const std::string toString(void) ;
		
		
	private:
	    union {
		    unsigned i;
		    float f;
		} fd, fa, fb;
		
		void * fsl_instance [ 16 ] ;
		unsigned pvr[12] ;
		unsigned fslx ;
		unsigned ea;
		unsigned pc , msr;
		unsigned immediate;
		int atomic , immediate_available ;
		unsigned clock_cycle ;
		unsigned instruction_count ;
		bool isMultiCycleInstruction ;
		unsigned remainingLatency ;

		BusIsBusyFn busIsBusyFn ;
		LoadFn loadFn ;
		StoreFn storeFn ;
		TraceFn traceFn ;
		FslIsBusyFn fslIsBusyFn[16] ;
		GetFn getFn[16] ;
		PutFn putFn[16] ;

		// Functions
		unsigned get_rD ( void ) ;
		unsigned * getD ( void ) ;
		unsigned get_rA ( void ) ;
		unsigned * getA ( void ) ;
		unsigned get_rB ( void ) ;
		
		const char * Annex_Sign_Extend_Short_Shift ( unsigned a ) ;
		const char * Annex_SPR_Ops ( unsigned a ) ;

};

#endif /* MICROBLAZE_HPP */

