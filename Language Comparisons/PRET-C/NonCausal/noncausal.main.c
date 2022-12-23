#include "noncausal.PRET.h"

#include <stdio.h>
// line:3
int  X=0;
// line:4
int  Y=0;
 int main()
{
	#include "noncausal.PRET.GLBASM.h"
	//global thread state vars 
	static Node PRET_Node_main_ID_0,GlobalTick,PRET_Node_t0_ID_1,PRET_Node_t1_ID_2; static Node* activeNode = &PRET_Node_main_ID_0; 
	//setup code 
	GlobalTick.PC = &&GlobalTick_function;
	GlobalTick.prev=&PRET_Node_main_ID_0;
	GlobalTick.next=&PRET_Node_main_ID_0;
	GlobalTick.parent=0;
	PRET_Node_main_ID_0.prev=&GlobalTick;
	PRET_Node_main_ID_0.next=&GlobalTick;
	PRET_Node_main_ID_0.parent=0; /*its parent is null*/
	PRET_Node_main_ID_0.spawnCtr=0;
	//setup code 
	asm("nop");/*asm("#@PRET_Parse start");*//*asm("#@PRET_Thread start PRET_Node_main_ID_0");*/
	PRET_Node_main_ID_0:;
	// line:7
	X = 0;
	// line:7
	Y = 0;
	// line:8
	if (X == 1)
	{
		goto PRET_IF_AFTER__noncausal__5;
	}
	// line:8
	else
	{
		// line:8
		X = 1;
	}
	PRET_IF_AFTER__noncausal__5:;asm("nop");

	// line:9
	printf("X = %d Y = %d\n", X, Y);
	// line:11
	EOT_noncausal__9
	EOT__noncausal__9:;
	asm("nop");/*asm("#@PRET_EOT end");*/
	// line:12
	X = 0;
	// line:12
	Y = 0;
	// line:13
	//PAR ID: 12 Threads: [t0, t1] 
	PAR12
	main_join12:;
	asm("nop");/*asm("#@PRET_PAR end");*/
	// line:14
	printf("X = %d Y = %d\n", X, Y);
	// line:16
	return  0;
	PRET_END:; 
	asm("nop");/*asm("#@PRET_EOT start");#@PRET_NL*/\
	asm("nop");/*asm("#@PRET_EOT end");#@PRET_NL*/\
	goto PRET_END;
	#include "noncausal.thd.h"
	GlobalTick_function:; 
	asm("nop");/*asm("#@PRET_Thread start GlobalTick_function");*/
	asm("nop");/*asm("#@PRET_Parse end");*/
	//variable map 
	//scope 9
	//scope 8
	//scope 7
	//scope 6
	//scope 5
	//scope 4
	//scope 3
	//scope 2
	//scope 1
	//scope 0
	//Y -> Y
	//X -> X
		activeNode = GlobalTick.next;
		goto *(activeNode->PC);
}

