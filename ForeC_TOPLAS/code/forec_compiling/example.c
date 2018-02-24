#include "node.h"	// Figure (*\ref{fig:forec_compiling:linkednode}*)

// Programmer-defined
int x=0;	// Shared variable (*\label{code:forec_compiling:example_user1}*)
int a_tC;	// tC's local variable (*\label{code:forec_compiling:example_a}*)
int plus(int th1,int th2) {return th1+th2;}(*\label{code:forec_compiling:example_user2}*)

// Compiler-defined
enum State {OTHER=-1,TERM=0}; (*\label{code:forec_compiling:example_scheduling1}*)
int mainState=OTHER, tAState=OTHER, (*\label{code:forec_compiling:example_states}*)
		tBState=OTHER, tCState=OTHER,
		tDState=OTHER;
int x_main, x_tA, x_tB, x_tC, x_tD; (*\label{code:forec_compiling:example_copies}*)

// Entry point
void main(void) { (*\label{code:forec_compiling:example_forecmain}*)
	// Nodes for the linked lists
	Node main={.pc=&&main}, (*\label{code:forec_compiling:example_scheduling3}*)
				tA={.pc=&&tA}, tB={.pc=&&tB},
				tC={.pc=&&tC}, tD={.pc=&&tD};
	Node mFork1={.pc=&&mFork1},
				sFork1={.pc=&&sFork1},
				mJoin1={.pc=&&mJoin1},
				sJoin1={.pc=&&sJoin1};
	Node mFork2={.pc=&&mFork2},
				sFork2={.pc=&&sFork2},
				mJoin2={.pc=&&mJoin2},
				sJoin2={.pc=&&sJoin2};
	Node mAbort1={.pc=&&mAbort1},
				sAbort1={.pc=&&sAbort1};
	Node mSync={.pc=&&mSync},
				sSync={.pc=&&sSync}; (*\label{code:forec_compiling:example_scheduling4}*)
	// Create initial linked lists
	if (core == 1) { (*\label{code:forec_compiling:example_scheduler1}\label{code:forec_compiling:example_direct1}*)
		main.prev=main.next=&main;
		insert(main,mFork1); insert(mFork1,mSync);
		goto *main.pc;
	} else if (core == 2) {
		sFork1.prev=sFork1.next=&sFork1;
		insert(sFork1,sSync); goto *sFork1.pc;
	} else { while(1); } (*\label{code:forec_compiling:example_direct2}*)

// Forking
mFork1: { (*\label{code:forec_compiling:example_mFork1}*)
	send(mainState); (*\label{code:forec_compiling:example_send1}*)
	if (mainState == 1) {
		Insert the nodes mAbort1,tA,sFork2, and mJoin1 (*\label{code:forec_compiling:example_mAbort1_insert}*)
		after mFork1.
		remove(main); remove(mFork1); goto *tA.pc; (*\label{code:forec_compiling:example_mFork1_goto1}*)
	} else { goto *mFork1.next->pc; } (*\label{code:forec_compiling:example_mFork1_goto2}*)
} (*\label{code:forec_compiling:example_mFork1_end}*)
sFork1: { (*\label{code:forec_compiling:example_sFork1}*)
	receive(mainState); (*\label{code:forec_compiling:example_receive1}*)
	if (mainState == 1) {
		Insert the nodes sAbort1,tB,mFork2, and sJoin1 (*\label{code:forec_compiling:example_sAbort1_insert}*)
		after sFork1.
		remove(sFork1); goto *sFork2.pc; (*\label{code:forec_compiling:example_sFork1_goto1}*)
	} else { goto *sFork1.next->pc; } (*\label{code:forec_compiling:example_sFork1_goto2}*)
} (*\label{code:forec_compiling:example_sFork1_end}*)

mFork2: {
	send(tBState);
	if (tBState == 2) {
		Insert the nodes tD and mJoin2 after mFork2.
		remove(tB); remove(mFork2); goto *tD.pc;
	} else { goto *mFork2.next->pc; }
}
sFork2: {
	receive(tBState);
	if (tBState == 2) {
		Insert the nodes tC and sJoin2 after sFork2.
		remove(sFork2); goto *tC.pc;
	} else { goto *sFork2.next->pc; }
}

// Joining
mJoin2: {
	receive(tCState);
	x_tB=plus(x_tC,x_tD,x); // Combine (*\label{code:forec_compiling:example_combine1}*)
	if (tCState == TERM 
			&& tDState == TERM) {
		tBState=OTHER; send(tBState);
		insert(mJoin2,tB); remove(mJoin2);
		goto *tB.pc;
	} else { 
		send(tBState); goto *mJoin2.next->pc;
	}
}
sJoin2: {
	send(tCState); receive(tBState);
	if (tBState == OTHER) { remove(sJoin2); }
	goto *sJoin2.next->pc;
}
mJoin1: { (*\label{code:forec_compiling:example_mJoin1}*)
	receive(tBState); (*\label{code:forec_compiling:example_receive2}*)
	x_main=plus(x_tA,x_tB,x); // Combine (*\label{code:forec_compiling:example_combine2}*)
	if (tAState == TERM
			&& tBState == TERM) {
		mainState=OTHER; send(mainState); (*\label{code:forec_compiling:example_receive2_term1}*)
		insert(mJoin1,main); remove(mAbort1); (*\label{code:forec_compiling:example_receive2_term2}*)
		remove(mJoin1); goto *main.pc; (*\label{code:forec_compiling:example_receive2_term3}*)
	} else { 
		send(mainState); goto *mJoin1.next->pc; (*\label{code:forec_compiling:example_receive2_term4}*)
	}
} (*\label{code:forec_compiling:example_mJoin1_end}*)
sJoin1: { (*\label{code:forec_compiling:example_sJoin1}*)
	send(tBState); (*\label{code:forec_compiling:example_send2}*)
	receive(mainState); (*\label{code:forec_compiling:example_sJoin1_receive}*)
	if (mainState == OTHER) { remove(sJoin1); }(*\label{code:forec_compiling:example_sJoin1_term}*)
	goto *sJoin1.next->pc; (*\label{code:forec_compiling:example_sJoin1_goto}*)
} (*\label{code:forec_compiling:example_sJoin1_end}*)

// Preempting
mAbort1: { (*\label{code:forec_compiling:example_mAbort1}*)
	if (x > 1) { (*\label{code:forec_compiling:example_mAbort1_1}*)
		Remove the linked nodes between mAbort1 (*\label{code:forec_compiling:example_mAbort1_2}*)
		and mJoin1 inclusive.
		main.pc = &&abort1; goto *main.pc; (*\label{code:forec_compiling:example_mAbort1_3}*)
	} else { goto *mAbort1.next->pc; } (*\label{code:forec_compiling:example_mAbort1_4}*)
} (*\label{code:forec_compiling:example_mAbort1_end}*)
sAbort1: { (*\label{code:forec_compiling:example_sAbort1}*)
	if (x > 1) { (*\label{code:forec_compiling:example_sAbort1_1}*)
		Remove the linked nodes between sAbort1 (*\label{code:forec_compiling:example_sAbort1_2}*)
		and sJoin1 inclusive.
		goto *sAbort1.next->pc; (*\label{code:forec_compiling:example_sAbort1_3}*)
	} else { goto *sAbort1.next->pc; } (*\label{code:forec_compiling:example_sAbort1_4}*)
} (*\label{code:forec_compiling:example_sAbort1_end}*)

// Synchronizing
mSync: { (*\label{code:forec_compiling:example_mSync}*)
	barrier(); (*\label{code:forec_compiling:example_mSync_1}*)
	x=x_main; emitOutputs(); sampleInputs(); (*\label{code:forec_compiling:example_mSync_2}*)
	barrier(); (*\label{code:forec_compiling:example_mSync_3}*)
	goto *mSync.next->pc; (*\label{code:forec_compiling:example_mSync_4}*)
} (*\label{code:forec_compiling:example_mSync_end}*)
sSync: { (*\label{code:forec_compiling:example_sSync}*)
	barrier(); barrier(); goto *sSync.next->pc; (*\label{code:forec_compiling:example_sSync_1}*)
} (*\label{code:forec_compiling:example_scheduler2}*)

// Threads
main: { (*\label{code:forec_compiling:example_threads1}*)
	copy(x_main,x); (*\label{code:forec_compiling:example_copy1}*)
	/* abort */ { (*\label{code:forec_compiling:example_abort1}*)
		x_main=1; (*\label{code:forec_compiling:example_x_main}*)
		
		// pause; (*\label{code:forec_compiling:example_pause1}*)
		main.pc=&&pause1; (*\label{code:forec_compiling:example_pause2}*)
		goto *main.next->pc; (*\label{code:forec_compiling:example_pause3}*)
		pause1:; (*\label{code:forec_compiling:example_pause1_end}*)
		if (x > 1) { goto abort1; } (*\label{code:forec_compiling:example_abort2}*)
		copy(x_main,x); (*\label{code:forec_compiling:example_copy2}*)
		
		// par(tA(),tB()); with id=1 (*\label{code:forec_compiling:example_par1}*)
		mainState=1; main.pc=&&join1; (*\label{code:forec_compiling:example_state}*)
		goto *main.next->pc; (*\label{code:forec_compiling:example_switch}*)
		join1:; (*\label{code:forec_compiling:example_join1}*)
		copy(x_main,x); (*\label{code:forec_compiling:example_copy3}*)
	} // when (x_main > 1); (*\label{code:forec_compiling:example_abort3}*)
	abort1: exit(0); (*\label{code:forec_compiling:example_abort4}*)
}
tA: {
	copy(x_tA,x_main);
	
	x_tA=x_tA+1; (*\label{code:forec_compiling:example_x_tA}*)
	
	// pause;
	tA.pc=&&pause2; goto *tA.next->pc;
	pause2:	copy(x_tA,x);
	
	x_tA=x_tA+1;
	
	// Termination.
	tAState=TERM; remove(tA);
	goto *tA.next->pc;
}
tB: {
	// par(tC(),tD()); with id=2 (*\label{code:forec_compiling:example_par2}*)
	tBState=2; tB.pc=&&join2; goto mFork2;
	join2:;
	// Termination. (*\label{code:forec_compiling:example_term1}*)
	tBState=TERM; (*\label{code:forec_compiling:example_term2}*)
	remove(tB); (*\label{code:forec_compiling:example_term3}*)
	goto *tB.next->pc; (*\label{code:forec_compiling:example_term4}*)
}
tC: { a_tC=1; ... }
tD: { ... } (*\label{code:forec_compiling:example_threads2}*)
}	// End of main()