#! /usr/bin/env python3
# By David Broman 2012

import argparse
import sys
import serial
import time
import binascii
import struct
import subprocess
import os
import time
import glob
import shutil

# Parse program arguments.
parser = argparse.ArgumentParser(description = 'Make generator and program execution tool. Created by David Broman 2012. Modified by Eugene Yip 2016.', usage = 'ptarm <command> [options]')
subparsers = parser.add_subparsers(dest = 'command', title = 'commands')
parser_create   = subparsers.add_parser("create", help = "create the program start up code, linker script and make file")
parser_make		= subparsers.add_parser("make", help = "make files without executing the program")
parser_execute	= subparsers.add_parser("execute", help = "execute the program on PTARM")
parser_run		= subparsers.add_parser("run", help = "clean, create, make, and execute")
parser_clean    = subparsers.add_parser("clean", help = "clean up all generated files")

args = parser.parse_args()

########################################################
# DEFINITIONS 
########################################################

stack_size			= 0x00000400	# Size of each stack. 4 kilobytes.

addr_bootloader		= 0xFFFE0000	# Boot loader starts from here.
addr_code_spm		= 0x00000000	# Data is directly after this.
addr_stack_start	= 0x0001FFDC	# Stack starts towards 0x0000 from here.
addr_eoe_table		= 0x0001FFE0	# Exception on expire handler table starts here.
addr_bootloader_lr	= 0x0001FFF0	# Boot loader PC table starts here.

# The main file name that contains the main function. 
# The string is without ".c" or ".S" suffix.
mainfile = args.command
command = args.command      
builddir = "_build/"


# Serial port identifier
comport = "/dev/tty.usbserial-AL00COK9"

# The C startup code
startup_code = r"""
        .text
start: 
		cdp		p13, 0, cr1, cr0, cr0	@ Get thread ID
		ldr     r2, =4					@ Set r2 to the value 4.
		mul 	r1, r2, r1          	@ Set r1 to thread_id * 4
		ldr     r2, =${addr_bootloader_lr} 			@ Set r2 to the first boot loader lr.
		add		r0,	r1, r2				@ Boot loader lr + thread_id * 4.
		str     lr, [r0]				@ Store lr into the address of r0.

		# Initiate bss section
		ldr     r0, =bss_start        	@ Get bss addresses from the linker script
		ldr     r1, =bss_end
		ldr     r2, =bss_size

		cmp     r2, #0
		beq     skip_bss
		mov     r4, #0					@ Set r4 to the value 0.
bss_loop:
		strb    r4, [r0], #1			@ Set the bss section to 0.
		subs    r2, r2, #1
		bne     bss_loop
skip_bss:
		# Initate the stack
		cdp		p13, 0, cr1, cr0, cr0	@ Get thread ID
		ldr     sp, =${addr_stack_start}				@ Load the address of the stack pointer.
stack_setup:
		cmp		r1, #0					@ If thread ID is now 0, go to the main function.
		beq		stack_setup_complete
		sub		sp, sp, #${stack_size}			@ Give each PTARM hardware thread 4 kilobytes of stack.
		sub		r1, r1, #1				@ Decrement the thread ID
		b		stack_setup				@ Keep decrementing the stack pointer.
		
stack_setup_complete:		
		# Jump to the C main function
		bl      main

		# Return to the bootloader
		cdp 	p13, 0, cr1, cr0, cr0	@ Get thread ID
		ldr     r2, =4					@ Set r2 to the value 4.
		mul		r1, r2, r1          	@ Set r1 to thread_id * 4
		ldr     r2, =${addr_bootloader_lr}				@ Set r2 to the first boot loader lr.
		add		r0,	r1, r2				@ Boot loader lr + thread_id * 4.
		ldr     r1, [r0]				@ Load boot loader lr from the address of r0.
		mov 	pc, r1					@ Go to r1
"""


# A generic linkscript 
linkscript = r"""
SECTIONS {
	/* Code. */
	. = ${addr_code_spm};
	.text : { * (.text); }

	/* Data directly after code. */
	.data : { * (.data); }

	bss_start = .;
	.bss : { * (.bss); }
	bss_end = .;
	bss_size = bss_end - bss_start;

	/* Stack limit */
	addr_stack_limit = .;

	/* Start of the stacks */
	addr_stack_start = ${addr_stack_start};
	
	/* End of the stacks */
	addr_stack_end = addr_stack_start - 4*${stack_size};
	
	/* Exception on Expire table */
	eoe_table = ${addr_eoe_table};
}
"""


# A generic makefile used in all projects.
makefile = r"""
# Set the tools to use.
AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump

OBJ = ${builddir}startup.o ${builddir}${name}.o 

${builddir}%.o: ${builddir}%.s 
	$(AS) -march=armv2a $< -o $@

${builddir}%.o: %.c 
	$(CC) -I"${PTARM_PATH}/include" -Wall -O0 -g -march=armv2a -mno-thumb-interwork -c $< -o $@
	$(CC) -I"${PTARM_PATH}/include" -Wall -O0 -g -E -CC -march=armv2a -mno-thumb-interwork -c $< -o $@.expanded.c

${builddir}${name}.bin: $(OBJ) 
# 	Link
	$(CC) -Wall -O0 -g -Xlinker -T -Xlinker ${builddir}${name}.lds -Xlinker --fix-v4bx -nostartfiles $^ -o ${builddir}${name}.elf
# 	Disassemble the elf 
	$(OBJDUMP) --disassemble --reloc --source --syms ${builddir}${name}.elf > ${builddir}${name}.asm
# 	Extract the binary part of the code
	$(OBJCOPY) -Obinary ${builddir}${name}.elf $@
"""


# Get the filename that contains the main function. 
# Returns a tuple containing the name with out suffix and the file suffix.
def get_code_file(path):
    cfiles = glob.glob(path + '*.c')
    fname = ""
    count = 0
    for name in cfiles:
        with open(name, "r") as f:
            if 'main(' in f.read():
                count += 1
                fname = name
            if 'main (' in f.read():
                count += 1
                fname = name
    if count == 0:
        print("There is no .c or .S file containing a 'main(...)' or 'main (...)' entry point.")
        exit()
    if count > 1:
        print("More than one code file in the directory " + path + " contains a 'main' entry point.")
        exit()
    return os.path.splitext(fname)


def clean(path):
    if os.path.exists(path+builddir):
        shutil.rmtree(path+builddir)


# Create the make file, the linker script and program startup files.
def create(mainfile):
    # Create build directory if it doesn't exist.
    if not os.path.exists(builddir):
        os.makedirs(builddir)

    # Create the make file
    with open(builddir + 'Makefile', 'w') as f:
        s = makefile.replace("${name}", mainfile) 
        s = s.replace("${builddir}", builddir) 
        f.write(s)

    # Create the link script file
    with open(builddir + mainfile + '.lds', 'w') as f:
        s = linkscript
        s = s.replace("${addr_code_spm}", hex(addr_code_spm))         
        s = s.replace("${addr_stack_start}", hex(addr_stack_start))
        s = s.replace("${stack_size}", hex(stack_size))
        s = s.replace("${addr_eoe_table}", hex(addr_eoe_table))
        f.write(s)

    # Create the startup file
    with open(builddir + 'startup.s', 'w') as f:
        s = startup_code
        s = s.replace("${addr_bootloader_lr}", hex(addr_bootloader_lr))
        s = s.replace("${addr_stack_start}", hex(addr_stack_start)) 
        s = s.replace("${stack_size}", hex(stack_size))
        f.write(s)


def make():
    command = ["make", "-f", builddir + "Makefile"] 
    output = subprocess.call(command)
    if output != 0:
        sys.exit()


def size(mainfile):
	command = ["wc", "-c", builddir + mainfile + '.bin']
	output = subprocess.check_output(command)
	programSize = int(output.split()[0])
	programEndAddress = addr_code_spm + programSize
	addr_stack_end = addr_stack_start - 4*stack_size
	print
	print("Used memory: {0:0.1f}/{1:0.1f} kilobytes ({2:0.1f}%)".format(float(programEndAddress)/1024, float(addr_stack_end)/1024, (100*float(programEndAddress)/addr_stack_end)))
	print
	if programSize > addr_stack_end:
		print("Program and stack cannot fit in memory!!")
		sys.exit()


# Execute a program using the UART
def execute(file):
    # Setup serial port
    ser = serial.Serial(comport, 115200, timeout = 1)

    # Send ready and check response.
    ser.write(b'\xff')
    b = ser.read(1)

    # Is the device working?
    if b != b'\xfe':
        print("The PTARM bootloader is not responding.")
        sys.exit()
        
    # Open binary file
    with open(builddir + file + ".bin", "rb") as f:
        data = f.read()
        size = len(data)
        # Send the size
        ser.write(struct.pack('>I', size))
        # Send the program
        ser.write(data)        

    # Wait for magic program termination
    sys.stdout.write("\n")
    sys.stdout.flush()
    while True:
        d1 = ser.read(1) 

        if d1 == b'\xff':
            d3 = ser.read(3) 
            if d3 == b'\x07\xa1\x73':
                break
            else:
                sys.stdout.write(d3.decode("utf-8"))
        sys.stdout.write(d1.decode("utf-8"))
        sys.stdout.flush()

    # Get instruction and cycle counts
    count = ser.read(8)
    inst_count, cycle_count = struct.unpack('>II',count)

    # Close the serial connection
    ser.close()

    # Print instruction and cycle counts
    print("\n---------------------------------------------")
    print("Instruction count:           ", inst_count)
    print("Thread cycle count:          ", cycle_count)
    print("Execution time at 50Mhz:     ", float(cycle_count) * 4 / 50000, "ms")
    print("Cycles per instruction (CPI):", float(cycle_count)/inst_count)

    
# ========= Main =============
if __name__ == "__main__":
	# Check which command to run
	if command == "clean":
		clean('')
	else:
		# Find the main program file.
		mainfile, suffix = get_code_file('')

		if command == "create":
			create(mainfile)
		elif command == "make":
			make()
			size(mainfile)
		elif command == "execute":
			size(mainfile)
			execute(mainfile)
		elif command == "run":
			clean('')
			create(mainfile)
			make()
			size(mainfile)
			execute(mainfile)



