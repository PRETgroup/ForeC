/* abort */ {
	@@if (x > 1) { goto abort1; }@@
	x_main=1;
	
	// pause;
	main.pc=&&pause1;
	goto *main.next->pc;
	pause1:;
	if (x > 1) { goto abort1; }
	copy(x_main,x);
	
	// par(tA,tB) with id=1
	mainState=1;
	goto *main.next->pc;
	join1:;
	copy(x_main,x);
} // when (x_main > 1);