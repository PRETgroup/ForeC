// Compiler-defined
#include <pthread.h> (*\label{code:forec_compiling:example:desktop:pthread1}*)
pthread_t cores[2]; (*\label{code:forec_compiling:example:desktop:pthread2}*)
...
// Entry point
void main(int argc,char ** argv) { (*\label{code:forec_compiling:example:desktop:main}*)
	pthread_create(&cores[0],...,forecMain,...); pthread_create(&cores[1],...,forecMain,...);
	pthread_join(cores[0],NULL); pthread_join(cores[1],NULL);
}
// Original main function from Figure (*\ref{fig:forec_compiling:example:c1}*)
void *forecMain(void *args) { ... } (*\label{code:forec_compiling:example:desktop:forecmain}*)