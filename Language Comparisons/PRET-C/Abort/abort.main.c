#include "abort.PRET.h"
// line:1
int  apple=2;
 int main()
{
	#include "abort.PRET.GLBASM.h"
	//global thread state vars 
	static Node PRET_Node_main_ID_0,GlobalTick,PRET_Node_t1_ID_1,PRET_Node_t2_ID_2; static Node* activeNode = &PRET_Node_main_ID_0; 
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
	// line:4
	//weak abort
	PRET_W_ABORT__abort__2_START
	{
		// line:5
		//strong abort
		PRET_S_ABORT__abort__3_START
		{
			// line:6
			static int  i;i=9;
			// line:7
			i++;
			// line:8
			//PAR ID: 6 Threads: [t1, t2] 
			PAR6
			main_join6:;
			asm("nop");/*asm("#@PRET_PAR end");*/
			// line:9
			EOT_abort__7
			EOT__abort__7:;
			asm("nop");/*asm("#@PRET_EOT end");*/
		}
		//when strong abort{...} when(apple == 3);
		PRET_S_ABORT__abort__3_END
	}
	//when weak abort{...} when(apple == 3);
	PRET_W_ABORT__abort__2_END
	PRET_END:; 
	asm("nop");/*asm("#@PRET_EOT start");#@PRET_NL*/\
	asm("nop");/*asm("#@PRET_EOT end");#@PRET_NL*/\
	goto PRET_END;
	#include "abort.thd.h"
	GlobalTick_function:; 
	asm("nop");/*asm("#@PRET_Thread start GlobalTick_function");*/
	asm("nop");/*asm("#@PRET_Parse end");*/
	//variable map 
	//scope 6
	//scope 5
	//scope 4
	//i -> i
	//scope 3
	//scope 2
	//scope 1
	//scope 0
	//apple -> apple
		activeNode = GlobalTick.next;
		goto *(activeNode->PC);
}

