#include "abro.PRET.h"

#include <stdio.h>

#define INPUT_SEQUENCE 7
// line:4
int  I[INPUT_SEQUENCE][3]={1,1,0,1,1,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0};
// line:15
int  tick=0;
//reactive input
int  A;
//reactive input
int  B;
//reactive input
int  R;
//reactive output
int  O=0;
 int main()
{
	#include "abro.PRET.GLBASM.h"
	//global thread state vars 
	static Node PRET_Node_main_ID_0,GlobalTick,PRET_Node_tA_ID_4,PRET_Node_tB_ID_5,PRET_Node_Inputs_ID_1,PRET_Node_abro_ID_2,PRET_Node_Results_ID_3; static Node* activeNode = &PRET_Node_main_ID_0; 
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
	// line:23
	printf("        A B R  O\n");
	// line:24
	//strong abort
	PRET_S_ABORT__abro__8_START
	{
		// line:25
		//PAR ID: 9 Threads: [Inputs, abro, Results] 
		PAR9
		main_join9:;
		asm("nop");/*asm("#@PRET_PAR end");*/
	}
	//when strong abort{...} when(tick == INPUT_SEQUENCE);
	PRET_S_ABORT__abro__8_END
	// line:28
	return  0;
	PRET_END:; 
	asm("nop");/*asm("#@PRET_EOT start");#@PRET_NL*/\
	asm("nop");/*asm("#@PRET_EOT end");#@PRET_NL*/\
	goto PRET_END;
	#include "abro.thd.h"
	GlobalTick_function:; 
	asm("nop");/*asm("#@PRET_Thread start GlobalTick_function");*/
	asm("nop");/*asm("#@PRET_Parse end");*/
	//variable map 
	//scope 17
	//scope 16
	//scope 15
	//scope 14
	//scope 13
	//scope 12
	//scope 11
	//scope 10
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
	//reactive Input
	//A -> A
	//I[INPUT_SEQUENCE] -> I[INPUT_SEQUENCE]
	//tick -> tick
	//reactive Input
	//R -> R
	//reactive Output
	//O -> O
	//reactive Input
	//B -> B
		activeNode = GlobalTick.next;
		goto *(activeNode->PC);
}

