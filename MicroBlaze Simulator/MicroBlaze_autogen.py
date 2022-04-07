# 
#  Scratchpad MMU - Autogenerator for some Microblaze opcodes
#  Copyright (C) Jack Whitham 2009
#  http://www.jwhitham.org.uk/c/smmu.html
# 
#  This library is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public
#  License as published by the Free Software Foundation
#  (version 2.1 of the License only).
#  
#  This library is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#  
#  You should have received a copy of the GNU Lesser General Public
#  License along with this library; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
# 

import re

DEBUG = False

def Get_Cmp(topcode):
    assert topcode == 5
    return """
\t\tswitch ( iword & 3 )
\t\t{
\t\t\tcase 1 : /* cmp */
\t\t\t\tout &= ~ ( 1 << 31 ) ;
\t\t\t\tif ( (int) a > (int) b ) out |= 1 << 31 ;
\t\t\t\tsnprintf ( name , MicroBlaze::NS , "cmp: r%u = r%u > r%u = %u\\n" , rD , rA , rB , ((unsigned) out ) >> 31 ) ;
\t\t\t\tbreak ;
\t\t\tcase 3 : /* cmpu */
\t\t\t\tmemcpy ( name , "cmpu " , 5 ) ;
\t\t\t\tout &= ~ ( 1 << 31 ) ;
\t\t\t\tif ( a > b ) out |= 1 << 31 ;
\t\t\t\tsnprintf ( name , MicroBlaze::NS , "cmpu: r%u = r%u > r%u = %u\\n" , rD , rA , rB , ((unsigned) out ) >> 31 ) ;
\t\t\t\tbreak ;
\t\t\tdefault :/* rsubk */
\t\t\t\tbreak ;
\t\t}
"""

def Get_Pcmp_Eq_Ne(topcode):
    
    if ( topcode == 0x22 ):
        function = "eq"
        function1 = "=="
    else:
        assert topcode == 0x23
        function = "ne"
        function1 = "!="

    return ("""
\t\tif ( iword & 0x400 )
\t\t{
\t\t\tout = ( a """ + function1 + """ b ) ;
\t\t\tsnprintf ( name , MicroBlaze::NS , "pcmp""" + function + ": r%u " + function1 + """ r%u = %u\\n" , rA , rB , out ) ;
\t\t}
""")

def Get_Pcmp_Bf(topcode):
    assert topcode == 0x20
    out = []
    out.append("\n\t\tif ( iword & 0x400 ) {\n\t\t\ttemp = 0 ;\n")
    for i in range(4):
        out.append("\t\t\tif ((( a >> %u ) & 0xff ) == (( b >> %u ) & 0xff ))" % (i * 8, i * 8))
        out.append(" { temp = %u ; }\n" % (4 - i))
    out.append("""
\t\t\tsnprintf ( name , MicroBlaze::NS , "pcmpbf: r%u versus r%u = %u\\n" , rA , rB , temp ) ;
\t\t\tout = temp ;
\t\t}
""")
    return ''.join(out)



def Get_ALU():
    SPECIAL_CASE = {
            0x5 : Get_Cmp ,
            0x20 : Get_Pcmp_Bf,
            0x22 : Get_Pcmp_Eq_Ne,
            0x23 : Get_Pcmp_Eq_Ne,
            }

    REGULAR_ALU_OPS = [
        ('add', '', 0x0, (False, True, '+', False, False)),
        ('add', 'c', 0x2, (True, True, '+', False, False)),
        ('add', 'k', 0x4, (False, False, '+', False, False)),
        ('add', 'kc', 0x6, (True, False, '+', False, False)),
        ('and', '', 0x21, (False, False, '&', False, False)),
        ('andn', '', 0x23, (False, False, '&', False, True)),
        ('xor', '', 0x22, (False, False, '^', False, False)),
        ('or', '', 0x20, (False, False, '|', False, False)),
        ('rsub', '', 0x1, (False, True, '+', True, False)),
        ('rsub', 'c', 0x3, (True, True, '+', True, False)),
        ('rsub', 'k', 0x5, (False, False, '+', True, False)),
        ('rsub', 'kc', 0x7, (True, False, '+', True, False)),
        ('mul', '', 0x10, (False, False, '*', False, False)) ]

    out = []
    for (mne1, mne2, topcode0, (carry_in_enable, carry_out_enable, function, invert_a, invert_b)) in REGULAR_ALU_OPS:

        for topcode in (topcode0, topcode0 | 0x8):
            out.append('\ncase 0x%x :\n' % topcode)

            if (( topcode == 0x10 ) or ( topcode == 0x18)):
                out.append('\tif ( isMultiCycleInstruction == false ) {\n')
                out.append('\t\t// Perform the stall but maintain the state of the core.\n')
                out.append('\t\tisMultiCycleInstruction = true;\n')
                out.append('\t\tremainingLatency = 2 ;\n')
                out.append('\t\tsnprintf ( name , MicroBlaze::NS , "mul (stall)\\n" ) ;\n')
                out.append('\t} else if ( remainingLatency > 1 ) {\n')
                out.append('\t\tremainingLatency--;\n')
                out.append('\t\tsnprintf ( name , MicroBlaze::NS , "(stall)\\n" ) ;\n')
                out.append('\t} else {\n')
                out.append('\t\t// Execute the instruction.\n')
                out.append('\t\tisMultiCycleInstruction = false;\n')
            else:
                out.append('\t{\n')

            c_function = function
            subtract = invert_a and ( function == '+' )
            use_64_bit = carry_out_enable and ( function == '+' )

            cin = 0 # int(subtract)

            if ( use_64_bit ):
                out.append('\t\tuint64_t out ;\n')
                expander = '(uint64_t)'
            else:
                out.append('\t\tunsigned out ;\n')
                expander = ''

            if ( carry_in_enable ):
                out.append('\t\tcarry_in = %u ;\n' % cin)
                out.append('\t\tif (( msr & MicroBlaze::MSR_C ) != 0 ) carry_in = %u ;\n' % (1 - cin))


            out.append('\t\tout = ( %s ' % expander)
            if ( invert_b ):
                out.append('( ~ b ) ')
            else:
                out.append('b ')

            if ( invert_a ):
                out.append("%s ( ~ ( %s a )) " % (function, expander))
            else:
                out.append("%s ( %s a ) " % (function, expander))

            if ( carry_in_enable ):
                out.append(' %s carry_in' % function)
            elif ( subtract ):
                out.append(' %s 1' % function)

            if ( subtract ):
                c_function = '-'

            out.append(' ) ;\n')

            if ( carry_out_enable ):
                out.append('\t\tmsr &= ~MicroBlaze::MSR_C ;\n') # carry cleared
                out.append('\t\tif ( ')
                if ( subtract ):
                    out.append('! ')
                out.append('(( out & ( (uint64_t) 1 ' +
                        '<< (uint64_t) 32 )) != 0 )) {')
                out.append('\n\t\t\tmsr |= MicroBlaze::MSR_C ;\n')
                out.append('\t\t}\n')

            out.append('\t\tsnprintf ( name , MicroBlaze::NS , "' + mne1 + mne2 + 
                    ': r%u =')
            if ( topcode & 0x8 ):
                out.append(' 0x%x ')
            else:
                out.append(' r%u ')

            out.append(c_function + ' r%u')

            if ( carry_in_enable ):
                out.append(' (carry_in)')
                
            out.append(' = 0x%x')
            if ( carry_out_enable ):
                out.append(' (carry_out=%u)')

            out.append('\\n" , rD , ')

            if ( topcode & 0x8 ):
                out.append('b , ')
            else:
                out.append('rB , ')

            out.append('rA , (unsigned) out ')
            if ( carry_out_enable ):
                out.append(', !! ( msr & MicroBlaze::MSR_C )')

            out.append(') ;\n')

            sc = SPECIAL_CASE.get(topcode, None)
            if ( sc != None ):
                out.append(sc(topcode))


            if (( mne1 == 'or' ) and ( mne2 == '' )):
                # Special case - check for simulator command
                out.append('\t\t{\n')
                out.append('\t\t\tunsigned cmd = iword & 0x7ff ;\n')
                out.append('\n')
                out.append('\t\t\tif (( iword & ~0x7ff ) == MicroBlaze::MB_NOP )\n')
                out.append('\t\t\t{\n')
                out.append('\t\t\t\tif ( cmd != 0 )\n')
                out.append('\t\t\t\t{\n')
                out.append('\t\t\t\t\tsnprintf ( name , MicroBlaze::NS , "cmd: 0x%x\\n" , iword & 0x7ff ) ;\n')
                out.append('\t\t\t\t\ttraceFn ( MicroBlaze::SIM_CMD , MicroBlaze::ip ( cmd )) ;\n')
                out.append('\t\t\t\t} else {\n')
                out.append('\t\t\t\t\tsnprintf ( name , MicroBlaze::NS , "nop:\\n" ) ;\n')
                out.append('\t\t\t\t}\n')
                out.append('\t\t\t}\n')
                out.append('\t\t}\n')

            if ( topcode == 0x0 ):
                out.append('\n')
                out.append('\t\tif ( iword == 0 )\n')
                out.append('\t\t{\n')
                out.append('\t\t\ttraceFn ( MicroBlaze::ILLEGAL_INST , MicroBlaze::ip ( pc )) ;\n')
                out.append('\t\t\tvalid = 0 ;\n')
                out.append('\t\t}\n')			

            out.append('\t\t*MicroBlaze::getD ( ) = (unsigned) out ;\n')
            out.append('\t}\n')
            out.append('\tbreak ;\n')

    return ''.join(out)

def Get_LSU():
    LOAD_STORE_OPS = [
        ((True, 4), "sw", 2),
        ((True, 2), "sh", 1),
        ((True, 1), "sb", 0),
        ((False, 4), "lwu", 2),
        ((False, 2), "lhu", 1),
        ((False, 1), "lbu", 0) ]

    out = []
    for ((store, size), mne, topcode_part) in LOAD_STORE_OPS:
        topcode = topcode_part 
        if ( store ):
            topcode |= 0x34 # store code
        else:
            topcode |= 0x30 # load code

        out.append('\ncase 0x%x :\n'
                    'case 0x%x : /* LSU: %s */\n' % (topcode, topcode | 0x8, mne) )

        out.append('\tif ( isMultiCycleInstruction == false ) {\n')
        out.append('\t\t// Perform the stall but maintain the state of the core.\n')
        out.append('\t\tisMultiCycleInstruction = true;\n')
        out.append('\t\tremainingLatency = 1 ;\n')
        
        out.append('\t\tea = a + b ;\n')

        if ( store ):
            out.append('\t\tsnprintf ( name , MicroBlaze::NS , "' + mne + ' (stall): [ 0x%x ] = r%u \\n" , ea , rD ) ;\n')
        else:
            out.append('\t\tsnprintf ( name , MicroBlaze::NS , "' + mne + ' (stall): r%u = [ 0x%x ] \\n" , rD , ea ) ;\n')
        
        out.append('\t} else if ( busIsBusyFn ( this , ea , %u) ) {\n' % (not store) )
        out.append('\t\tsnprintf ( name , MicroBlaze::NS , "' + mne + ' (stall)\\n" ) ;\n')
        out.append('\t} else {\n')
        out.append('\t\t// Execute the instruction.\n')
        out.append('\t\tisMultiCycleInstruction = false;\n')
        
        if ( size == 4 ):
            out.append('\t\tif ( ea & 3 ) traceFn ( MicroBlaze::ALIGN , MicroBlaze::ip ( ea )) ;\n')
        elif ( size == 2 ):
            out.append('\t\tif ( ea & 1 ) traceFn ( MicroBlaze::ALIGN , MicroBlaze::ip ( ea )) ;\n')

        if ( store ):
            out.append('\t\ttraceFn ( MicroBlaze::STORE , MicroBlaze::ip ( ea )) ;\n')
            out.append('\t\tstoreFn ( this, ea , *MicroBlaze::getD () , %u ) ;\n' % size )
            out.append('\t\tsnprintf ( name , MicroBlaze::NS , "' + mne + ': [ 0x%x ] = r%u = 0x%x\\n" , ea , rD , *MicroBlaze::getD () ) ;\n')
        else:
            out.append('\t\ttraceFn ( MicroBlaze::LOAD , MicroBlaze::ip ( ea )) ;\n')
            out.append('\t\t*MicroBlaze::getD ( ) = loadFn ( this, ea , %u ) ;\n' % size)
            out.append('\t\tsnprintf ( name , MicroBlaze::NS , "' + mne + ': r%u = [ 0x%x ] = 0x%x\\n" , rD , ea , *MicroBlaze::getD () ) ;\n')

        out.append('\t}\n')
        out.append('\tbreak;\n')

    return ''.join(out)

def Get_Barrel():
    BARREL_OPS = [ 
        ('bsrl', 0, '>>', False), 
        ('bsra', 1, '>>', True), 
        ('bsll', 2, '<<', False) ]

    out = []
    for topcode in (0x11, 0x19):
        out.append("\ncase 0x%x :\n" % topcode)
        out.append("\tswitch ( iword & ( 3 << 9 )) {\n")

        for (mne, opcode, java_op, special) in BARREL_OPS:
            out.append('\t\tcase 0x%x : /* Barrel: %s */\n' % (opcode << 9, mne) )
            
            out.append('\t\t\tif ( isMultiCycleInstruction == false ) {\n')
            out.append('\t\t\t\t// Perform the stall but maintain the state of the core.\n')
            out.append('\t\t\t\tisMultiCycleInstruction = true;\n')
            out.append('\t\t\t\tremainingLatency = 1 ;\n')
            out.append('\t\t\t\tsnprintf ( name , MicroBlaze::NS , "' + mne + ' (stall)\\n" ) ;\n')
            out.append('\t\t\t} else if ( remainingLatency > 1 ) {\n')
            out.append('\t\t\t\tremainingLatency--;\n')
            out.append('\t\t\t\tsnprintf ( name , MicroBlaze::NS , "(stall)\\n" ) ;\n')
            out.append('\t\t\t} else {\n')
            out.append('\t\t\t\t// Execute the instruction.\n')
            out.append('\t\t\t\tisMultiCycleInstruction = false;\n')
            out.append('\t\t\t\tb = b & 0x1f ;\n')
            
            if ( special ):
                # special means sign extend
                out.append('\t\t\t\t*MicroBlaze::getD ( ) = ((int) a) %s b;\n' % java_op)
            else:
                out.append('\t\t\t\t*MicroBlaze::getD ( ) = a %s b;\n' % java_op)

            out.append('\t\t\t\tsnprintf ( name , MicroBlaze::NS , "' + mne + ': r%u = r%u ' + java_op)
            if ( topcode & 0x8 ):
                out.append(' 0x%x')
            else:
                out.append(' r%u')

            out.append(' = 0x%x\\n" , rD , rA ,')
            if ( topcode & 0x8 ):
                out.append(' b , ')
            else:
                out.append(' rB , ')

            out.append('*MicroBlaze::getD () ) ;\n')
            out.append('\t\t\t}\n')
            

            out.append('\t\t\tbreak ;\n')
			
        out.append('\t\tdefault : *MicroBlaze::getD ( ) = 0 ; break ;\n' )
        out.append('\t}\n')
        out.append('\tbreak;\n')

    return ''.join(out)

def Get_Float_Cmp(topcode):
    assert topcode == 0x200
    
    FLOAT_CMP_OPS = [ 
		('fcmp.un', 0, '', 2),
		('fcmp.lt', 1, '<', 2),
		('fcmp.eq', 2, "==", 2),
		('fcmp.le', 3, "<=", 2),
		('fcmp.gt', 4, '>', 2),
		('fcmp.nq', 5, "!=", 2),
		('fcmp.ge', 6, ">=", 2) ]
    
    out = []
    out.append('\t\tcase 0x%x : /* Float: cmp */\n' % topcode )
    out.append("\t\t\tswitch ( (iword >> 4) & 0x7 ) {\n")
    
    for (mne, opcode, java_op, remainingLatency) in FLOAT_CMP_OPS:
        out.append('\t\t\t\tcase 0x%x : /* Float: %s */\n' % (opcode, mne) )
        out.append('\t\t\t\t\tif ( isMultiCycleInstruction == false ) {\n')
        out.append('\t\t\t\t\t\t// Perform the stall but maintain the state of the core.\n')
        out.append('\t\t\t\t\t\tisMultiCycleInstruction = true;\n')
        out.append('\t\t\t\t\t\tremainingLatency = %d ;\n' % remainingLatency )
        out.append("\t\t\t\t\t\tfa.i = a;\n")
        out.append("\t\t\t\t\t\tfb.i = b;\n")
        out.append('\t\t\t\t\t\tsnprintf ( name , MicroBlaze::NS , "' + mne + ' (stall)\\n" ) ;\n')
        out.append('\t\t\t\t\t} else if ( remainingLatency > 1 ) {\n')
        out.append('\t\t\t\t\t\tremainingLatency--;\n')
        out.append('\t\t\t\t\t\tsnprintf ( name , MicroBlaze::NS , "(stall)\\n" ) ;\n')
        out.append('\t\t\t\t\t} else {\n')
        out.append('\t\t\t\t\t\t// Execute the instruction.\n')
        out.append('\t\t\t\t\t\tisMultiCycleInstruction = false;\n')
        if ( mne != 'fcmp.un' ):
            out.append('\t\t\t\t\t\ttemp = fb.f %s fa.f;\n' %java_op)
        else:
            out.append('\t\t\t\t\t\ttemp = 0;\n')
        out.append('\t\t\t\t\t\t*MicroBlaze::getD ( ) = temp ;\n' )
        out.append('\t\t\t\t\t\tsnprintf ( name , MicroBlaze::NS , "' + mne + ': fd.f = %f ' + java_op + ' %f = %u\\n", fb.f, fa.f, temp ) ;\n' ) ; 
        out.append('\t\t\t\t\t}\n')
        out.append('\t\t\t\t\tbreak ;\n' )
		    
    out.append('\t\t\t\tdefault : *MicroBlaze::getD ( ) = 0 ; break ;\n' )
    out.append('\t\t\t}\n')
    out.append('\t\t\tbreak;\n')

    return ''.join(out)
    
    
def Get_Float():
    FLOAT_OPS = [ 
        ('fadd', 0x0, '+', 5),
        ('frsub', 0x80, '-', 5),
        ('fmul', 0x100, '*', 5),
        ('fdiv', 0x180, '/', 29),
        ('fcmp', 0x200, '', 2),
        ('flt', 0x280, '', 5),
        ('fint', 0x300, '', 6),
        ('fsqrt', 0x380, '', 28) ]

    out = []
    out.append("\ncase 0x16 :\n")
    out.append("\tswitch ( iword & 0x780 ) {\n")

    for (mne, opcode, java_op, remainingLatency) in FLOAT_OPS:
        if (mne == 'fcmp'):
            out.append(Get_Float_Cmp(opcode))
        else:
            out.append('\t\tcase 0x%x : /* Float: %s */\n' % (opcode, mne) )
            out.append('\t\t\tif ( isMultiCycleInstruction == false ) {\n')
            out.append('\t\t\t\t// Perform the stall but maintain the state of the core.\n')
            out.append('\t\t\t\tisMultiCycleInstruction = true;\n')
            out.append('\t\t\t\tremainingLatency = %d ;\n' % remainingLatency )
            out.append("\t\t\t\tfa.i = a;\n")
            out.append("\t\t\t\tfb.i = b;\n")
            out.append('\t\t\t\tsnprintf ( name , MicroBlaze::NS , "' + mne + ' (stall)\\n" ) ;\n')
            out.append('\t\t\t} else if ( remainingLatency > 1 ) {\n')
            out.append('\t\t\t\tremainingLatency--;\n')
            out.append('\t\t\t\tsnprintf ( name , MicroBlaze::NS , "(stall)\\n" ) ;\n')
            out.append('\t\t\t} else {\n')
            out.append('\t\t\t\t// Execute the instruction.\n')
            out.append('\t\t\t\tisMultiCycleInstruction = false;\n')
		    
            if (java_op != ''):
                out.append('\t\t\t\tfd.f = fb.f %s fa.f ;\n' % java_op )
                out.append('\t\t\t\t*MicroBlaze::getD ( ) = fd.i;\n' )
                out.append('\t\t\t\tsnprintf ( name , MicroBlaze::NS , "' + mne + ': fd.f = %f ' + java_op + ' %f = %f\\n", fb.f, fa.f, fd.f ) ;\n' ) ;

            elif (mne == 'flt'):
                out.append('\t\t\t\tfd.f = fa.i;\n')
                out.append('\t\t\t\t*MicroBlaze::getD ( ) = fd.i;\n' )
            elif (mne == 'fint'):
                out.append('\t\t\t\tfd.i = fa.f;\n')
                out.append('\t\t\t\t*MicroBlaze::getD ( ) = fd.i;\n' )
            elif (mne == 'fsqrt'):
                out.append('\t\t\t\tfd.f = sqrt(fa.f);\n')
                out.append('\t\t\t\t*MicroBlaze::getD ( ) = fd.i;\n' )
				
            out.append('\t\t\t}\n')
            out.append('\t\t\tbreak ;\n' )

    out.append('\t\tdefault : *MicroBlaze::getD ( ) = 0; break ;\n' )
    out.append('\t}\n')
    out.append('\tbreak;\n')

    return ''.join(out)

def Get_Pycode():
    out = []
    out.append(Get_ALU())
    out.append(Get_LSU())
    out.append(Get_Barrel())
    out.append(Get_Float())
    return ''.join(out)

def Main():
    fout = open('MicroBlaze_autogen.cpp', 'wt')
    fout.write(Get_Pycode())
    fout.close()

if ( __name__ == "__main__" ):
    Main()

