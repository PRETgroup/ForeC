ForeC Benchmarks (Desktop versions)
-----------------------------------
ForeC benchmark programs that are designed
for execution on multicore desktop computers.

Pre-requisites:
---------------
* Pthread support
* forecc (ForeC compiler)
* GNU make

Benchmarks:
-----------
The benchmarks are contained in each folder.
Each benchmark comes with a Makefile to help automate
the compilation process. The following is the 
general procedure to compile the benchmarks for 
execution:

Compile the ForeC program into C:
$ make forec

Compile the generated C program into an executable binary:
$ make c

Specific make commands for each benchmark can be 
seen by looking at its Makefile.


