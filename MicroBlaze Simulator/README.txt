Multicore Xilinx MicroBlaze Simulator
-------------------------------------
Simulates a multicore MicroBlaze system where
cores connect to main memory via a TDMA bus.

Based on the MicroBlaze/SMMU Simulator
** For information about the SMMU please visit
** http://www.jwhitham.org.uk/c/smmu.html

Author: Eugene Kin Chee Yip
Date: 5 October 2014


Pre-requisites:
---------------
* Unix compatible system
* Python
* libelf-dev
* C++ compiler
* GNU make and relevant dependencies


Installing:
-----------
To create the "mb-sim" executable, the following commands need to be executed:
 $ make clean
 $ make

The Makefile specifies the C++ compiler used to compile the ForeC compiler.
This can be changed by modifying "CC" in the Makefile to your liking.


Usage:
------
* $ mb-sim <cores> <name>.elf [-debug]

* cores:
  * An integer representing the number of cores in the system.
  * Each core is given a unique ID between 0 and <cores>. Thus,
    the core ID in the ForeC header file must be within the same
    range. Otherwise, the program behaviour is undefined.

* name:
  * The name of the MicroBlaze elf file to simulate.

* -debug option:
  -verbose for showing the instruction fetched in each clock cycle.

