void main(void) {
	shared int x=3 combine all with plus; (*\label{fig:forec_combine:passing_x}*)
	int y=5;
	f(x,y); (*\label{fig:forec_combine:passing_f_call}*)
	g(&x); (*\label{fig:forec_combine:passing_g_call}*)
}

void f(int d, shared int e) { (*\label{fig:forec_combine:passing_f}*)
	...
}
void g(shared int* p) { (*\label{fig:forec_combine:passing_g}*)
	// p points to the shared variable x declared on line (*\ref{fig:forec_combine:passing_x}*).
	...
}