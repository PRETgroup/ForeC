PTARM Processor (Windows 10 + Quartus Prime 15.1.0 Lite Edition + Altera DE2-115 Development and Education Board + GCC 5.2.1)
Modified by Matthew Kuo and Eugene Yip
---------------------------------------------------------------

Major changes made to the original PTARM processor:

  1. Additional hardware: 
     a. A mutex for protecting shared resources (when 
        time-based mutual exclusion is not practical).
     b. Custom coprocessor for getting/setting the CPSR.
     c. Custom coprocessor for getting the SPSR.
     d. Custom coprocessor for 32-bit unsigned integer division
        (3 thread cycle latency).
     e. Timed preemptions are delayed until the current 
        multicycle load/store instruction has completed.
     
  2. Modified memory layout (such as the location of 
     the EOE handler table, bootloader return addresses,
     and stack location).
     a. The bootloader program and compiler script were 
        modified to take into account the new memory layout.
   
  3. Modified compiler script:
     a. More compilation options (clean, create, make, execute, 
        run)
     b. Supports the new memory layout (updated startup code, 
        linkerscript).
     c. Updated the makefile template to have the PTARM header
        files in the include search path.
     d. Reports the amount of memory needed to store the program
        binary and stack. Also checks that it will all fit in 
        the scratchpad memory.

  4. Increased the size of the scratchpad to 128 kilobytes.

These changes are elaborated in the document 
doc/userguide/Crash course on PTARM.docx

