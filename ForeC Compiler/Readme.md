# ForeC Compiler (multicore deployment)
Compiles ForeC programs into an equivalent C program for 
multicore execution on MicroBlaze, PTARM, or desktop
environments (Pthreads).

Author: Eugene Kin Chee Yip   
Date: 26 December 2023

## Pre-requisites
* Unix compatible system
* [Flex version 2.6.4 or later]([url](https://github.com/westes/flex))
* [Bison version 3.6 or later]([url](https://www.gnu.org/software/bison/))
* C++ compiler
* GNU make and relevant dependencies
* [Graphviz 2.34 or later]([url](https://graphviz.org))


## Installing on Linux
To create the `forecc` executable, the following commands need to be executed:
```bash
 $ make clean
 $ make
```

The Makefile specifies the C++ compiler used to compile the ForeC compiler.
This can be changed by modifying `CC` in the Makefile to your liking.

The compiler uses templates to generate code and these are stored in 
`tools/template`. The compiler needs to know where this folder is located. 
This is achieved by setting the environment variable `FOREC_COMPILER_PATH` 
to the folder location. Note that the path must have a trailing slash. 
Thus, the following commands should be issued:
```bash
 $ FOREC_COMPILER_PATH="/root/path/to/the/compiler/"
 $ export FOREC_COMPILER_PATH
 ```

To execute the compiler from any directory, the root path to the compiler 
can be added to the `PATH` environment variable. Be careful of spaces in the path:
```bash
 $ PATH=$PATH:$FOREC_COMPILER_PATH
 $ export PATH
```

## Usage
* `$ forecc [options] <source filename> <header filename>`

* Options can be:
  * `-v` for version information.
  * `-d1` for including print statements that will print out
    the elapsed time after each program reaction.
  * `-i` for checking instantaneous loops.
  * `-t<clock cycles>` for creating time predictable code that
    runs each global tick for at least <clock cycles> long
    on microblaze or ptarm platforms, or at least 
    <microseconds> long on x86 platforms.
  * `-m<name>` for embedding the program with <name> for the 
    main function, with `void *` as the return type and 
    `void *_` for the function parameter.
* Expected source file extension: `*.forec`
* Expected header file extension: `*.foreh`


## ForeC Header File
The purpose of the `*.foreh` file is to specify the architecture
that the compiler should target. It is also used to specify the
thread-to-core distribution. The contents of the file follows
the following convention:
* A `key: value` format is used.
* Multiple values for the same key can be specified and separated
  by commas.
* Each `key` and `value` need to be on their own lines.
* To specify the architecture, the key `architecture` is used. 
  The value is the name of the target architecture (listed in 
  the following section in **Target Architectures**).
* To specify a thread-to-core distribution, the key is an integer
  to represent the core ID. Core IDs on MicroBlaze start from zero
  and increase monotonically. The value is the name of the thread.

An example that specifies MicroBlaze as the architecture and distributes
the threads `t0`, `t1`, and `t2` to two different cores (`0` and `1`):
```
architecture:
microblaze

0:
t0
t1

1:
t2
```

## Target Architectures
* `microblaze`: Bare-metal Xilinx multicore (custom) processors.
* `ptarm`: Bare-metal PTARM single-core multi-threaded processor.
* `x86`: General platforms supporting the POSIX threads model.

## Syntax Colouring
Syntax colouring/highlighting files are located in `./syntax colouring/` and supports:
* XCode 4.3
  * Execute the shell scripts with superuser privileges.
* Gedit
  * Go to `/usr/share/gtksourceview-X.Y/`, where `X.Y` is the latest version number.
    Place the language file into the language-specs folder.
    Place the XML style file into the styles folder.
    
## Outputs
* `<source name>.c`:
  Generated C-program that is equivalent to the original ForeC program specification.
* `information.xml`:
  Information about the program structure for use with the ForeC analyser.
* `debug.txt`:
  Debugging information for each stage of compilation.
* `<source name>.dot`:
  Graphviz (directed) diagram of the intermediate format. Convert into a PDF with the following command:   
  `$ dot -T pdf <source name>.dot -o <filename>.pdf`

## Capabilities
* Read a ForeC program from a self-contained `*.forec` file.
* Read a thread-to-core allocation `*.foreh` file.
* Handle an arbitrary number of threads and cores.
* Handle arbitrary sequences and nestings of par, abort, iteration, and selection statements.
* Check for variables used/defined by multiple threads.
* Support scalar shared variables and whether they need a combine function.
* Check for potentially instantaneous loops.

A ForeC source program is mapped directly into a graph that is 
constructed from a set of connected blocks. The 
graph represents the program's control-flow and 
concurrency. Hence, we call this graph a Concurrent Control-Flow 
Graph (CCFG). There are two classes of blocks: asynchronous and 
synchronous. Asynchronous blocks correspond to C-statements while 
synchronous blocks correspond to ForeC statements. In addition 
to forming the foundations of an intermediate format, this 
graph can be visualised to provide a graphical means for inspecting 
the program. Using this visualisation, explicit parallelism is 
made obvious and control-flow patterns can be identified and
improved.

Given the allocation of threads-to-cores, it is possible to 
take the CCFG and derive new graphs (tarots) to show each 
core's allocation of threads. For the allocation to be effective, 
it may be necessary to replicate the parallel statements in 
each graph. These new graphs make it easier to see the 
distribution of control and the relevant inter-core dependencies 
required to preserve program behaviour. During compilation, 
each core's tarot may be optimised and these are preserved during 
code generation.

The idea of distribution is to spread the workload over available 
cores for faster execution but to orchestrate the execution to 
give the illusion that the execution is on a single powerful core. 
When a core executes a parallel statement, it becomes the master 
of that parallel statement. Then, other cores involved with executing 
the child threads become slaves of the master.

Intuitively, the replicated parallel statements in each graph 
indicate when master and slave cores are involved in the execution 
of threads. If all threads of a parallel statement were allocated 
to the same core, then no replication of the parallel statement
would be required.

## Limitations
* Lexical:
  - Avoid mangling externally defined typedef names with the ForeC supported `extern typedef` combination of storage specifiers.
  - Cannot `typedef` within a storage definition.
  - Cannot declare `extern shared` variables.
  - Scoping within storage definitions is ignored.
  - Correct C-code assumed to be written.
  - User definitions for storages and types must be defined within the `*.forec` file.
  - All global variables have to be declared before the `main(...)` function.
  - The arguments of the `main(...)` function are expected to be `int argc, char **argv`.

* Multi-core:
  - All threads need to be manually allocated.
  - Undefined threads may not appear in the `*.foreh` header file.
  - Core IDs in the `*.foreh` header file must start from `0` in numerical order.
  
* Multi-threading:
  - All functions, apart from `main(...)`, cannot fork threads.
  - Only threads can fork other threads.
  - Threads can only be respawned by the same parent thread.
  - Cannot deal with recursive threads.
  - Old-style of declaring ForeC threads with `void` arguments.
  - Variables cannot be passed into a thread as an argument.
  - Only the last enclosing `par(...)` is returned for a thread if is used in multiple `par(...)`s.

* Input and Output variables:
  - Not yet implemented.

* Shared variables:
  - Very basic support for shared arrays.
  - Local shared variables not fully supported.
  - Cannot qualify elements of an array as shared.
  - Cannot use postfix or prefix assignment shorthands.
  - Does not work with `static` or `const` qualifiers.
  - Only the `mod` combine policy is implemented. `all` and `new` not yet implemented.

* Aborts:
  - Only `strong immediate` aborts are supported.
  - Conditions with side-effects are not supported.
  - When a `par(...)` is preempted, the parent thread's copies of shared variables are not updated.

* Architecture:
  - `main(...)` function must return `void`.
  
* Graphviz:
  - Does not show jumps via break and continue statements.
  - Does not show computation nodes.

## Translation Process
* Private variable declarations in threads are moved to the same scope as the thread. 
  This is to prevent stack corruption when jumping between different "threads".
* Local shared variable declarations in threads are moved to the global scope.
* Thread definitions are relocated to the end of the `main(...)` function.
* POSIX: Pthreads are used to emulate physical cores so the `main(...)` function must fork a 
  Pthread for each allocated core.  Hence, the `main(...)` function of the source file is renamed
  to `forecMain(...)`.
* Initial suffixes are determined immediately for shared variable declarations.
  If a variable is used, then we search for its corresponding declaration within 
  the current thread scope and then global scope.
* Nomenclature for shared variable names:   
  Declaring  = `variableName_scopeNameOfDeclaration_scopeLevel_scopeInstance`   
  Use or Def = `variableName_scopeNameOfDeclaration_scopeLevel_scopeInstance_copy_scopeName`

## `par(...)` ID Codes
* 0 and higher: Normal `par(...)` ID numbers.
* -1: Undefined `par(...)`.  Reserved for making sure there is a distinction between the current and next `par(...)`.
* -2: End of an iteration.  Same behaviour as an ID of -1.
* -3: End of a thread.
* default: `par(...)` IDs that the core does not participate in.

## Use-Def of Shared Variables
```
                                                        Parallel Use
                           +-----------------------------------------------+--------------+
                           |        0 threads      |       1 thread        |  2+ threads  |
                           |  (Output/Write only)  |       (Reduce)        |   (Reduce)   |  Remark:
         +-----------------+-----------------------+-----------------------+--------------+  ----------------------
Parallel |     0 threads   |                                                              |  Combine not needed.
Def      |  (Read only)    |                                                              |  Enforced by dropping
         +-----------------|                       +-----------------------+--------------+  the "combine with" 
         |     1 thread    |                       | If different threads, | Create local |  clause.
         | (Point-to-point |                       | create local copy.    | copy.        |
         |  or broadcast)  |                       |                       |              |
         +-----------------+-----------------------+-----------------------+--------------+  ----------------------
         |    2+ threads   | If output, create     |    Create local copy and combine.    |
         |      (Map)      | local copy & combine. |                                      |
         +-----------------+-----------------------+--------------------------------------+
```

Execution Scenarios

| Master Core                                  |  Slave Core(s)                                    |
| -------------------------------------------- | ------------------------------------------------- |
| Executes main thread.                        | Busy waits for a top-level par(...) to execute.   |
|                                              |                                                   |
| Executes top-level par(...). Creates thread-level par(...) handlers. Suspends execution of the parent thread. | Constructs linked-list and thread-level par handlers. If not participating in the par(...), wait for the next par(...). | 
|                                              |                                                   |
| Executes nested par(...). Suspends execution of parent thread. Executes child threads. | Extends linked list. Suspends execution of thread-level par handler. Executes child threads. |
|                                              |                                                   |
| Busy waits for reaction to finish.           | Executes reaction end. Busy wait for reaction to finish. |
|                                              |                                                   |
| Reaction finishes. Update mutex value. Go to the next thread. | Go to the next thread.           |
|                                              |                                                   |
| par(...) finishes. Delete linked list. Resume parent thread and thread-level par handler. | Delete linked list. Resume thread-level par handler. Busy wait for another par to execute. |
|                                              |                                                   |
| Thread terminates. Delete linked list and thread-level par handler. | Delete linked list and thread-level par handler. |
|                                              |                                                   |
| Abort executes without par(...) inside. Skip to the end of the abort scope. | Do nothing. |
|                                              |                                                   |
| Abort executes with par(...) inside, but par(...) is not executing. Skip to the end of the abort scope. | Busy wait for the next par or go to the next handler. |
|                                              |                                                   |
| Executes a par(...) within an abort. Check abort condition. If true, delete linked list and resume the parent thread. | Check abort condition. If true, delete linked list then busy wait for the next par(...) or go to the next handler. |
|                                              |                                                   |
| Iteration executes with at least one par(...). | Execute dummy par(...) with undefined ID to make a distinction between the last and current iteration. |
												
