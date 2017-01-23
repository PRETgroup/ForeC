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

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <math.h>

#include <iomanip>
#include <iostream>
#include <sstream>

#include "MicroBlaze.hpp"
#include "System.hpp"


/* Microblaze(tm) compatible virtual machine.
 * NOT OFFICIAL XILINX SOFTWARE - USE ENTIRELY AT YOUR OWN RISK
 * Supports barrel shift, multiply, divide, interrupts.
 * Does not support full floating point, full fast simplex link, 
 * pattern instructions, cache instructions, memory barrier
 * instructions or internal exceptions.
 */


MicroBlaze::MicroBlaze( const unsigned pvr0, System * system, MicroBlaze::TraceFn traceFn , MicroBlaze::BusIsBusyFn busIsBusyFn, MicroBlaze::LoadFn loadFn, MicroBlaze::StoreFn storeFn ) {
	this -> pvr[0] = pvr0 ;
	this -> system = system ;
	this -> busIsBusyFn = busIsBusyFn ;
    this -> loadFn = loadFn ;
    this -> storeFn = storeFn ;
    this -> traceFn = traceFn ;

    MicroBlaze::reset () ;
}

void MicroBlaze::jump ( unsigned target_pc ) {
    pc = target_pc ;
    next_iword = MicroBlaze::MB_FLUSH_NOP ;
    cur_iword = MicroBlaze::MB_FLUSH_NOP ;
    immediate = 0 ;
    atomic = 0 ;
    immediate_available = 0 ;
}

void MicroBlaze::reset ( void ) {
    unsigned i ;

    for ( i = 0 ; i < 32 ; i ++ ) {
        gpr [ i ] = 0 ;
    }

    for ( i = 0 ; i < 16 ; i ++ ) {
		fsl_instance [i] = NULL;
		fslIsBusyFn[i] = MicroBlaze::nullFslIsBusy;
		getFn[i] = MicroBlaze::nullGet;
		putFn[i] = MicroBlaze::nullPut;
	}

	ea = 0;
    pc = 0 ;
    prev_pc = 0;
    msr = 0 ;
    traceFn ( MicroBlaze::RESET , 0 ) ;
    clock_cycle = 0 ;
    instruction_count = 0 ;
    isMultiCycleInstruction = false ;
    remainingLatency = 0 ;
    MicroBlaze::jump ( 0 ) ;
}

void * MicroBlaze::ip ( unsigned x ) {
	return (void *) ( (uintptr_t) (x) );
}

unsigned MicroBlaze::get_rD ( void ) {
    return ( cur_iword >> 21 ) & 0x1f ;
}

unsigned * MicroBlaze::getD ( void ) { 
    return &gpr [ MicroBlaze::get_rD () ] ;
}

unsigned * MicroBlaze::getA ( void ) {
    return &gpr [ MicroBlaze::get_rA () ] ;
}

unsigned MicroBlaze::get_rA ( void ) {
    return ( cur_iword >> 16 ) & 0x1f ;
}

unsigned MicroBlaze::get_rB ( void ) {
    unsigned iword = cur_iword ;
    unsigned rB = ( iword >> 11 ) & 0x1f ;

    if (( iword & ( 1 << 29 ) ) != 0 )
    {
        rB = 0 ; /* immediate form */
    }
    return rB ;
}
    
/* Opcodes beginning with command 0x24.
 * These are not very common unless the code has been built
 * without barrel shifter support. */
const char * MicroBlaze::Annex_Sign_Extend_Short_Shift ( unsigned a ) {
    unsigned x , out = 0 ;
    const char * name = "?" ;

    switch ( cur_iword & 0x7f ) {
        case 0x60 : /* sext8 (pg 136) */
            if (( a & 0x80 ) != 0 ) {
                a |= 0xffffff00 ;
            } else {
                a &= 0xff ;
            }
            out = a ;
            name = "sext8" ;
            break ;
        case 0x61 : /* sext16 (pg 135) */
            if (( a & 0x8000 ) != 0 ) {
                a |= 0xffff0000 ;
            } else {
                a &= 0xffff ;
            }
            out = a ;
            name = "sext16" ;
            break ;
        case 0x01 : /* sra (pg 139) */
            if (( a & 1 ) != 0 ) { /* get carry flag */
                msr |= MicroBlaze::MSR_C ;
            } else {
                msr &= ~MicroBlaze::MSR_C ;
            }
            out = (unsigned) ( (int) a >> 1 ) ;
            name = "sra" ;
            break ;
        case 0x21 : /* src (pg 140) */
            /* use old carry flag */
            x = ( msr & MicroBlaze::MSR_C ) ;
            if (( a & 1 ) != 0 ) { /* get new carry flag */
                msr |= MicroBlaze::MSR_C ;
            } else {
                msr &= ~MicroBlaze::MSR_C ;
            }
            a = a >> 1 ;
            a = a & 0x7fffffff ;
            if ( x != 0 ) a |= 1 << 31 ;
            out = a ;
            name = "src" ;
            break ;
        case 0x41 : /* srl (pg 141) */
            if (( a & 1 ) != 0 ) { /* get carry flag */
                msr |= MicroBlaze::MSR_C ;
            } else {
                msr &= ~MicroBlaze::MSR_C ;
            }
            out = ( a >> 1 ) & 0x7fffffff ;
            name = "srl" ;
            break ;
        case 0x68 : /* wic */
            return "wic" ;
        case 0x64 : /* wdc */
            return "wdc" ;
        default :
            return "?" ; /* unknown op */
    }

	*MicroBlaze::getD ( ) = out ;
    return name ;
}

/* Opcodes for accessing the SPRs */
const char * MicroBlaze::Annex_SPR_Ops ( unsigned a ) {
    unsigned out = msr ;
    const char * name = "?" ;

    switch ( cur_iword & 0xc000 ) {
        case 0 : /* msrset or msrclr */
            if ( 0 != ( cur_iword & 0x10000 )) { /* msrclr */
                msr &= ~ ( cur_iword & 0x3fff ) ;
                name = "msrclr" ;
            } else {
                msr |= ( cur_iword & 0x3fff ) ;
                name = "msrset" ;
            }
            break ;
        case 0x8000 : /* mfs */
            switch ( cur_iword & 0x3fff ) {
                case 0x1 :    /* MSR selected */
                    out = msr ;
                    break ;
                case 0x2000 : /* PVR0 selected */
                	out = pvr[0] ;
                	break ;
                default :
                    /* Unknown SPR read */
                    out = 0 ;
                    traceFn ( MicroBlaze::SPR_READ , 0 ) ;
                    break ;
            }
            name = "mfs" ;
            break ;
        case 0xc000 : /* mts */
            switch ( cur_iword & 0x3fff ) {
                case 1 :    /* MSR selected */
                    msr = a ;
                    break ;
                default :
                    /* Unknown SPR write */
                    traceFn ( MicroBlaze::SPR_WRITE , MicroBlaze::ip ( a ) ) ;
                    break ;
            }
            name = "mts" ;
            return name ; /* not a read operation */
        default :
            return name ; /* not a known operation */
    }
    
    *MicroBlaze::getD ( ) = out ;
    return name ;
}


void MicroBlaze::step ( int interrupt_flag ) {
    /* Instruction pipeline */
    unsigned    iword , topcode ;
    int         imm_inst = 0 ;
    int         div_zero = 0 ;
    int         valid = 1 ;
    unsigned    a , b , temp , carry_in , rA, rB, rD ;
    int         condition ;
    const char * temp_name = "?" ;
    char        name [ MicroBlaze::NS + 1 ] ;
    const int   pcoffset = -8 ;

	if ( isMultiCycleInstruction ) {		
		// Maintain the pc, prev_pc, iword, cur_iword, next_iword.
		// Continue with previous iword.
		iword = cur_iword ;

		name [ MicroBlaze::NS ] = '\0' ;
	} else {
		do {
			cur_iword = next_iword ;
		    iword = cur_iword ;
		    next_iword = loadFn ( this, pc , 4 ) ;
		    prev_pc = pc ;
		    pc += 4 ;
		    name [ MicroBlaze::NS ] = '\0' ;

		    /* Interrupt handler */
		    if ( atomic ) {
		        atomic = 0 ;
		    } else if (( interrupt_flag ) /* interrupt! */
		    && (( msr & ( MicroBlaze::MSR_IE | MicroBlaze::MSR_BIP | MicroBlaze::MSR_EIP )) == MicroBlaze::MSR_IE )) {
		        /* IE high, BIP low, EIP low */
		        /* Prevent further interrupts until reenabled by code */
		        msr &= ~ MSR_IE ;
		        /* PC copied to "return PC" GPR */
		        pc += pcoffset ;
		        gpr [ 14 ] = pc ; 
		        /* Pipeline flush */
		        iword = cur_iword = next_iword = MB_FLUSH_NOP ;
		        /* Go to vector code */
		        pc = 0x10 ;
		        traceFn ( MicroBlaze::INTERRUPT , 0 ) ;
		    }
		} while ( iword == MicroBlaze::MB_FLUSH_NOP ) ;
	}

    /* Decoding of command */
    topcode = (( iword >> 26 ) & 0x3f ) ;
    rD = ( iword >> 21 ) & 0x1f ;
    rA = ( iword >> 16 ) & 0x1f ;
    rB = ( iword >> 11 ) & 0x1f ;
    fslx = iword & 0xf ;
    
    a = gpr [ rA ] ;
    if (( iword & ( 1 << 29 ) ) != 0 ) {
        /* Get B value from immediate */
        if ( immediate_available ) {
            b = (( immediate << 16 ) | ( iword & 0xffff )) ;
        } else if (( iword & 0x8000 ) != 0 ) {
            b = iword | (int) ( 0xffff << 16 ) ;
        } else {
            b = iword & 0xffff ;
        }
    } else {
        /* Get B value from register */
        b = gpr [ rB ] ;
    }

    switch ( topcode ) {
        case 0x27 :     
        case 0x2f :
            /* beq etc.: Conditional branch 
             * (page 79 of ISA ref, onwards) */
            if ( isMultiCycleInstruction == false ) {
		        switch (( iword >> 21 ) & 7 ) {
		            case 0 :    condition = ( (int) a == 0 ) ; break ;
		            case 1 :    condition = ( (int) a != 0 ) ; break ;
		            case 2 :    condition = ( (int) a < 0 ) ; break ;
		            case 3 :    condition = ( (int) a <= 0 ) ; break ;
		            case 4 :    condition = ( (int) a > 0 ) ; break ;
		            case 5 :    condition = ( (int) a >= 0 ) ; break ;
		            default :   condition = 0 ; break ;
		        }
		        
		        temp = pc + b + pcoffset ;

		        if ( condition ) { /* conditional branch taken */
		        	// Perform the stall but maintain the state of the core.
		        	isMultiCycleInstruction = true;
		            if ( 0 == ( iword & ( 1 << 25 ) )) { /* delay bit not set */
		                remainingLatency = 2 ;
		            } else {
		                remainingLatency = 1 ;
		            }
		            atomic = 1 ;

		            static const char * b_names [ 8 ] =  { "beq" , "bne" , "blt" , "ble" , "bgt" , "bge" , "?" , "?" } ;
		            snprintf ( name , MicroBlaze::NS , "%s (stall): r%u: to 0x%x (cond:%s taken)\n" , b_names [ ( iword >> 21 ) & 7 ] , rA , temp , condition ? "" : " not" ) ;
		        } else {
		            static const char * b_names [ 8 ] =  { "beq" , "bne" , "blt" , "ble" , "bgt" , "bge" , "?" , "?" } ;
		            snprintf ( name , MicroBlaze::NS , "%s: r%u: to 0x%x (cond:%s taken)\n" , b_names [ ( iword >> 21 ) & 7 ] , rA , temp , condition ? "" : " not" ) ;
				}
            } else if ( remainingLatency > 1 ) { 
		    	remainingLatency--;
		    	snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
            } else {
	            // Execute the instruction.
		        isMultiCycleInstruction = false;

		        switch (( iword >> 21 ) & 7 ) {
		            case 0 :    condition = ( (int) a == 0 ) ; break ;
		            case 1 :    condition = ( (int) a != 0 ) ; break ;
		            case 2 :    condition = ( (int) a < 0 ) ; break ;
		            case 3 :    condition = ( (int) a <= 0 ) ; break ;
		            case 4 :    condition = ( (int) a > 0 ) ; break ;
		            case 5 :    condition = ( (int) a >= 0 ) ; break ;
		            default :   condition = 0 ; break ;
		        }

		        temp = pc + b + pcoffset ;
		        {
		            static const char * b_names [ 8 ] =  { "beq" , "bne" , "blt" , "ble" , "bgt" , "bge" , "?" , "?" } ;
		            snprintf ( name , MicroBlaze::NS , "%s: r%u: to 0x%x (cond:%s taken)\n" , b_names [ ( iword >> 21 ) & 7 ] , rA , temp , condition ? "" : " not" ) ;
		        }
		        
		        if ( condition ) { /* conditional branch taken */
		            pc = temp ;
		            if ( 0 == ( iword & ( 1 << 25 ) )) { /* delay bit not set */
		                next_iword = MicroBlaze::MB_FLUSH_NOP ;
		            }
		            atomic = 1 ;
		        }
            }
            break ;
        case 0x26 :     
        case 0x2e :
            /* brai, etc.:
             * Unconditional branch (page 91 of ISA ref manual) */
            
            if ( isMultiCycleInstruction == false ) {
		        // Perform the stall but maintain the state of the core.
		        isMultiCycleInstruction = true;
		        
		        const bool nodelay = ( 0 == ( iword & ( 1 << 20 ) )) ; /* delay bit not set */ 
		        if ( nodelay ) {
		            remainingLatency = 2 ;
		        } else {
		            remainingLatency = 1 ;
		        }
		        
		        bool sub_call = false;
		        temp_name = "bra (stall)" ;
		        if ( 0 != ( iword & ( 1 << 18 ) )) { /* link bit set */
		            temp_name = "bral (stall)" ;
		            /* *could* be a brk operation (page 95) */
		            if (( iword & 0x1f0000 ) == 0x0c0000 ) { /* brk */
		                temp_name = "brk (stall)" ;
		            } else {
		            	sub_call = true ;
		            }
		        }
		        
		        temp = pc ;
		        if ( 0 != ( iword & ( 1 << 19 ) )) { /* absolute bit set */
		            temp = b ;
		        } else {
		            temp += b + pcoffset ;
		        }
		        
                if ( sub_call ) {
		            traceFn ( MicroBlaze::CALL , MicroBlaze::ip ( temp )) ;
		        }
		        snprintf ( name , MicroBlaze::NS , "%s: to 0x%x\n" , temp_name , temp ) ;
		    } else if ( remainingLatency > 1 ) { 
		    	remainingLatency--;
		    	snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
            } else {
		        // Execute the instruction.
		        isMultiCycleInstruction = false;
		        
		        const bool nodelay = ( 0 == ( iword & ( 1 << 20 ) )) ; /* delay bit not set */ 
		        if ( nodelay ) {
		            next_iword = MicroBlaze::MB_FLUSH_NOP ;
		        }
				
				bool sub_call = false;
		        temp_name = "bra" ;
		        if ( 0 != ( iword & ( 1 << 18 ) )) { /* link bit set */
		            temp_name = "bral" ;
		            *MicroBlaze::getD ( ) = pc + pcoffset ;
		            /* *could* be a brk operation (page 95) */
		            if (( iword & 0x1f0000 ) == 0x0c0000 ) { /* brk */
		                temp_name = "brk" ;
		                msr |= MicroBlaze::MSR_BIP ;
		            } else {
		                sub_call = true ;
		            }
		        }
		        
		        if ( 0 != ( iword & ( 1 << 19 ) )) { /* absolute bit set */
		            pc = b ;
		        } else {
		            pc += b + pcoffset ;
		        }
		        
                if ( sub_call ) {
		            traceFn ( MicroBlaze::CALL , MicroBlaze::ip ( pc )) ;
		        }
		        snprintf ( name , MicroBlaze::NS , "%s: to 0x%x\n" , temp_name , pc ) ;
		    }

            atomic = 1 ; /* no interrupt in delay slot */
            
            break ;
        case 0x2c :
            /* imm: immediate load instruction */
            snprintf ( name , MicroBlaze::NS , "imm: 0x%x\n" , iword & 0xffff ) ;
            imm_inst = 1 ;
            atomic = 1 ; /* no interrupt to the next instruction */
            immediate = iword ;
            break ;
        case 0x12 :
        case 0x1a :
            /* idiv: division instruction (pg 107) */
            if ( isMultiCycleInstruction == false ) {
		        if ( 0 != ( iword & 0x2 )) { /* unsigned division */
		            if ( a == 0 ) {
			            temp_name = "idivu" ;
		                div_zero = 1 ;
		                a ++ ;
		            } else {
    		 	        // Perform the stall but maintain the state of the core.
		                temp_name = "idivu (stall)" ;
		     		    isMultiCycleInstruction = true;
		                remainingLatency = 33 ;
		            }
		            temp = b / a ;
		        } else {
		            if ( a == 0 ) {
			            temp_name = "idiv" ;
		                div_zero = 1 ;
		                a ++ ;
		            } else {
        		        // Perform the stall but maintain the state of the core.
		                temp_name = "idiv (stall)" ;
		        		isMultiCycleInstruction = true;
		                remainingLatency = 33 ;
		            }
		            temp = (unsigned) ( (int) b / (int) a ) ;
		        }
		        
		        snprintf ( name , MicroBlaze::NS , "%s: r%u = r%u / r%u = 0x%x\n" , temp_name , rD , rA , rB , temp ) ;
		    } else if ( remainingLatency > 1 ) { 
		    	remainingLatency--;
		    	snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
            } else {
		        // Execute the instruction.
		        isMultiCycleInstruction = false;

		        if ( 0 != ( iword & 0x2 )) { /* unsigned division */
		            temp_name = "idivu" ;
		            if ( a == 0 ) {
		                div_zero = 1 ;
		                a ++ ;
		            }
		            temp = b / a ;
		        } else {
		            temp_name = "idiv" ;
		            if ( a == 0 ) {
		                div_zero = 1 ;
		                a ++ ;
		            }
		            temp = (unsigned) ( (int) b / (int) a ) ;
		        }
		        
		        snprintf ( name , MicroBlaze::NS , "%s: r%u = r%u / r%u = 0x%x\n" , temp_name , rD , rA , rB , temp ) ;
		        *MicroBlaze::getD ( ) = temp ;
		    }
            break ;
        case 0x24 : 
            /* Sign extend and 1-bit shifts, also 
             * cache writers wdc and wic. */
            temp_name = MicroBlaze::Annex_Sign_Extend_Short_Shift ( a ) ;
            snprintf ( name , MicroBlaze::NS , "%s: r%u = %s r%u = 0x%x\n" , temp_name , rD , temp_name , rA , *MicroBlaze::getD () ) ;
            break ;
        case 0x2d :
            /* rtsd etc: Return operations */
            if ( isMultiCycleInstruction == false ) {
		        // Perform the stall but maintain the state of the core.
		        isMultiCycleInstruction = true;

		        remainingLatency = 1 ;
		        
				temp = a + b ;

		        switch (( iword >> 21 ) & 0x1f ) {
		            case 0x12 : 
		                temp_name = "rtbd" ;
		                break ;
		            case 0x11 : 
		                temp_name = "rtid" ;
		                break ;
		            case 0x14 : 
		                temp_name = "rted" ;
		                break ;
		            default :
		                if (( rA == 15 ) && ( b == 8 )) {
		                    /* It's being used as a RETURN. */
		                    traceFn ( MicroBlaze::RETURN , MicroBlaze::ip ( temp )) ;
		                }
		                temp_name = "rtsd" ;
		                break ;
		        }

		        snprintf ( name , MicroBlaze::NS , "%s (stall): to 0x%x\n" , temp_name , temp ) ;
		    } else if ( remainingLatency > 1 ) { 
		    	remainingLatency--;
		    	snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
            } else {
		        // Execute the instruction.
		        isMultiCycleInstruction = false;
		        
				pc = a + b ;
		        switch (( iword >> 21 ) & 0x1f ) {
		            case 0x12 : 
		                msr &= ~MicroBlaze::MSR_BIP ; 
		                temp_name = "rtbd" ;
		                break ;
		            case 0x11 : 
		                msr |= MicroBlaze::MSR_IE ; 
		                temp_name = "rtid" ;
		                break ;
		            case 0x14 : 
		                msr &= ~ MicroBlaze::MSR_EIP ;
		                msr |= MicroBlaze::MSR_EE ;
		                temp_name = "rted" ;
		                break ;
		            default :
		                if (( rA == 15 ) && ( b == 8 )) {
		                    /* It's being used as a RETURN. */
		                    traceFn ( MicroBlaze::RETURN , MicroBlaze::ip ( pc )) ;
		                }
		                temp_name = "rtsd" ;
		                break ;
		        }

		        snprintf ( name , MicroBlaze::NS , "%s: to 0x%x\n" , temp_name , pc ) ;
			}
	        atomic = 1 ; /* no interrupt in delay slot */
            break ;
        case 0x25 :
            /* mfs, mts, msrset, msrclr: Special purpose register
             * access commands. */
            temp_name = MicroBlaze::Annex_SPR_Ops ( a ) ;
            snprintf ( name , MicroBlaze::NS , "%s: %u\n" , temp_name , *MicroBlaze::getD ( ) ) ;
            break ;

        case 0x1b :
            /* get, put: Flags n c t a e currently not suported */
	        if ( rD ) {
	        	temp_name = "get" ;
				if ( isMultiCycleInstruction == false ) {
					// Perform the stall but maintain the state of the core.
					isMultiCycleInstruction = true;
					remainingLatency = 1 ;
		            snprintf ( name , NS , "%s (stall): from FSL%d\n" , temp_name , fslx ) ;
				} else if ( fslIsBusyFn [ fslx ] ( fsl_instance [ fslx ], "get", MicroBlaze::getD ( ) ) ) { 
					snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
		        } else {
				    // Execute the instruction.
				    isMultiCycleInstruction = false;
				    getFn [ fslx ] ( fsl_instance [ fslx ], MicroBlaze::getD ( ) ) ;
                    snprintf ( name , NS , "%s: %u from FSL%d\n" , "get" , *MicroBlaze::getD ( ) , fslx ) ;
                }
	        } else {
	        	temp_name = "put" ;
				if ( isMultiCycleInstruction == false ) {
					// Perform the stall but maintain the state of the core.
					isMultiCycleInstruction = true;
					remainingLatency = 1 ;
		            snprintf ( name , NS , "%s (stall): from FSL%d\n" , temp_name , fslx ) ;
				} else if ( fslIsBusyFn [ fslx ] ( fsl_instance [ fslx ], "put", MicroBlaze::getA ( ) ) ) { 
					snprintf ( name , MicroBlaze::NS , "(stall)\n" ) ;
		        } else {
				    // Execute the instruction.
				    isMultiCycleInstruction = false;
				    putFn [ fslx ] ( fsl_instance [ fslx ], MicroBlaze::getA ( ) ) ;
	                snprintf ( name , NS , "%s: %u to FSL%d\n" , "put" , *MicroBlaze::getA ( ) , fslx ) ;
		        }
		    }
            break ;
/*
		case 0x13 :
			// getd, putd: Flags n c t a e currently not suported 
			temp_name = rD ? "getd" : "putd" ;
			snprintf ( name , NS , "%s\n" , temp_name ) ;
			break;
*/

#include "MicroBlaze_autogen.cpp"

        default :
            traceFn ( MicroBlaze::ILLEGAL_INST , MicroBlaze::ip ( pc )) ;
            valid = 0 ;
            break ;
    }
    if ( div_zero ) {
        traceFn ( MicroBlaze::EXECUTE , name ) ;
        traceFn ( MicroBlaze::DIV_BY_ZERO , MicroBlaze::ip ( pc )) ;
        valid = 0 ;
    }

	if ( !isMultiCycleInstruction ) {
		if ( imm_inst ) {
		    immediate_available = 1 ;
		} else {
		    immediate_available = 0 ;
		}
	}
    clock_cycle ++ ;
    instruction_count += ( isMultiCycleInstruction == false ) ;
    if ( valid ) {
        traceFn ( MicroBlaze::EXECUTE , name ) ;
    }
}

void MicroBlaze::mapFsl ( void * instance, const unsigned fslx, MicroBlaze::GetFn getFn, MicroBlaze::PutFn putFn, MicroBlaze::FslIsBusyFn fslIsBusyFn ) {
	this -> fsl_instance[fslx] = instance;
	this -> getFn[fslx] = getFn;
	this -> putFn[fslx] = putFn;
	this -> fslIsBusyFn[fslx] = fslIsBusyFn;
}

const unsigned MicroBlaze::getId(void) {
	return (pvr[0] & 0xff);
}

const unsigned MicroBlaze::getClockCycle(void) {
	return clock_cycle;
}

const bool MicroBlaze::nullFslIsBusy ( void * instance, const std::string type, const unsigned * rA ) {
	return false;
}

void MicroBlaze::nullGet ( void * instance, unsigned * rD ) {
	*rD = 0;
}

void MicroBlaze::nullPut ( void * instance, const unsigned * rA ) {
	// Nothing to do
}

const std::string MicroBlaze::toString(void) {
	std::ostringstream output;
	
	output << "core" << std::setw(2) << std::left << getId() << std::right
		   << " pc = 0x" << std::hex << std::setfill('0') << std::setw(8) << pc 
		   << " cur_iword = 0x" << std::hex << std::setfill('0') << std::setw(8) << cur_iword 
		   << " next_iword = 0x" << std::hex << std::setfill('0') << std::setw(8) << next_iword;
	return output.str();
}

