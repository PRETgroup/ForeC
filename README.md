# ForeC Tool Suite

The ForeC language enables the deterministic, parallel, and reactive programming of embedded multi-cores. 
The synchronous semantics of ForeC is designed to greatly simplify the understanding and debugging of parallel programs. 
ForeC ensures that ForeC programs can be compiled efficiently for parallel execution and be amenable to static timing analysis. 
ForeC's main innovation is its shared variable semantics that provides thread isolation and deterministic thread communication. 
All ForeC programs are correct by construction and deadlock-free because no non-deterministic constructs are needed.

Relevant publications:
* E. Yip, A. Girault, P. S. Roop, and M. Biglari-Abhari. [Synchronous Deterministic Parallel Programming for Multi-Cores with ForeC](https://doi.org/10.1145/3591594). ACM Transactions on Programming Languages and Systems, 2023.
* A. Girault, N. Hili, E. Jenn, and E. Yip. [A Multi-Rate Precision Timed Programming Language for Multi-Cores](https://doi.org/10.1109/FDL.2019.8876950). Forum for Specification and Design Languages (FDL), IEEE, 2019.
* E. Yip, A. Girault, P. S. Roop, and M. Biglari-Abhari. [The ForeC Synchronous Deterministic Parallel Programming Language for Multicores](https://doi.ieeecomputersociety.org/10.1109/MCSoC.2016.13). International Symposium on Embedded Multicore/Many-core Systems-on-Chip (MCSoC), IEEE, 2016.
* E. Yip. [ForeC: Designing Cyber-Physical Systems With Foresight](https://researchspace.auckland.ac.nz/handle/2292/27863). PhD thesis, University of Auckland, New Zealand, 2015.
* E. Yip, M. M. K. Kuo, P. S. Roop, and D. Broman. [Relaxing the Synchronous Approach for Mixed-Criticality Systems](https://doi.org/10.1109/RTAS.2014.6925993). Real-Time and Embedded Technology and Applications Symposium (RTAS), IEEE, 2014.
* E. Yip, P. S. Roop, M. Biglari-Abhari, and A. Girault. [Programming and Timing Analysis of Parallel Programs on Multicores](https://doi.org/10.1109/ACSD.2013.19). International Conference on Application of Concurrency to System Design (ACSD), IEEE, 2013


## Tools

* ForeC Compiler: Prototypic compiler, based on Flex/Bison, for a practical subset of the ForeC language.
* ForeC Analyser: Static timing analyser for ForeC programs compiled for bare-metal execution on MicroBlaze and PTARM architectures.
* ForeC Benchmarks: Programs used in running examples, in performance benchmarks, and in timing analysis benchmarks.
* MicroBlaze Simulator: Cycle-accurate simulator of a Xilinx MicroBlaze processor with a configurable number of cores.
* PTARM Processor: Modified softcore [Precision Timed (PRET) processor from UC Berkeley](https://ptolemy.berkeley.edu/projects/chess/pret/)

