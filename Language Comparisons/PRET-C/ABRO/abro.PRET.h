#ifndef PRET_C_NODE
#define PRET_C_NODE
typedef struct _Node{
	void *PC;
	void *deathAddr;
	int spawnCtr;
	struct _Node *next;
	struct _Node *prev;
	struct _Node *parent;
} Node;
#endif
#define PRET_S_ABORT__abro__8_START \
asm("nop");/*asm("#@STRONG_ABORT_begin");#@PRET_NL*/\
Node PRET_Abort_Node_ID__abro__8,PRET_End_Abort_Node_ID__abro__8;\
PRET_Abort_Node_ID__abro__8.next=activeNode;\
PRET_Abort_Node_ID__abro__8.prev=activeNode->prev;\
PRET_Abort_Node_ID__abro__8.spawnCtr=0; /*self spwan*/ \
(activeNode->prev)->next=&PRET_Abort_Node_ID__abro__8;\
activeNode->prev=&PRET_Abort_Node_ID__abro__8;\
PRET_Abort_Node_ID__abro__8.parent=activeNode;\
PRET_Abort_Node_ID__abro__8.PC=&&PRET_ABORT__abro__8;\
PRET_End_Abort_Node_ID__abro__8.next=activeNode->next;\
PRET_End_Abort_Node_ID__abro__8.prev=activeNode;\
PRET_End_Abort_Node_ID__abro__8.spawnCtr=0; /*self spwan*/ \
(activeNode->next)->prev=&PRET_End_Abort_Node_ID__abro__8;\
activeNode->next=&PRET_End_Abort_Node_ID__abro__8;\
PRET_End_Abort_Node_ID__abro__8.parent=activeNode;\
PRET_End_Abort_Node_ID__abro__8.PC=&&PRET_END_ABORT__abro__8;\
activeNode->PC = &&PRET_S_ABORT__abro__8_BODY;\
activeNode = &PRET_Abort_Node_ID__abro__8;\
asm("nop");/*asm("##@PRET_ABORT_8");#@PRET_NL*/\
PRET_ABORT__abro__8:;\
if (tick == INPUT_SEQUENCE) {\
	goto PRET_S_ABORT__abro__8_KILL;\
}else{\
}\
activeNode = activeNode->next;\
goto *(activeNode->PC);\
asm("nop");/*asm("##@PRET_END_ABORT_8");#@PRET_NL*/\
PRET_END_ABORT__abro__8:\
activeNode = activeNode->next;\
goto *(activeNode->PC);\
asm("nop");/*asm("##@PRET_S_ABORT_8_BODY");#@PRET_NL*/\
PRET_S_ABORT__abro__8_BODY:\

#define PAR9 \
asm("nop");/*asm("#@PRET_PAR start");*//*asm("#@PRET_GroupID 9" );#@PRET_NL*/\
(*activeNode).PC = &&main_join9;\
(*activeNode).spawnCtr += 3;\
/*update the next pointers of parent node*/\
(*activeNode).prev->next = &PRET_Node_Inputs_ID_1;\
(*activeNode).next->prev = &PRET_Node_Results_ID_3;\
/*update next#@PRET_NL*/\
PRET_Node_Inputs_ID_1.next=&PRET_Node_abro_ID_2;\
PRET_Node_abro_ID_2.next=&PRET_Node_Results_ID_3;\
PRET_Node_Results_ID_3.next=(*activeNode).next;\
/*updade prev#@PRET_NL*/\
PRET_Node_Inputs_ID_1.prev=(*activeNode).prev;\
PRET_Node_Results_ID_3.prev=&PRET_Node_abro_ID_2;\
PRET_Node_abro_ID_2.prev=&PRET_Node_Inputs_ID_1;\
PRET_Node_Inputs_ID_1.spawnCtr=0;\
PRET_Node_abro_ID_2.spawnCtr=0;\
PRET_Node_Results_ID_3.spawnCtr=0;\
PRET_Node_Inputs_ID_1.deathAddr=&&Inputs_death;\
PRET_Node_abro_ID_2.deathAddr=&&abro_death;\
PRET_Node_Results_ID_3.deathAddr=&&Results_death;\
PRET_Node_Inputs_ID_1.parent=&(*activeNode);\
PRET_Node_abro_ID_2.parent=&(*activeNode);\
PRET_Node_Results_ID_3.parent=&(*activeNode);\
/*asm("#@PRET_Child0 address");#@PRET_NL*/PRET_Node_Inputs_ID_1.PC = &&Inputs;\
/*asm("#@PRET_Child1 address");#@PRET_NL*/PRET_Node_abro_ID_2.PC = &&abro;\
/*asm("#@PRET_Child2 address");#@PRET_NL*/PRET_Node_Results_ID_3.PC = &&Results;\
/*change active thread*/ \
activeNode=&PRET_Node_Inputs_ID_1;\
goto *PRET_Node_Inputs_ID_1.PC;\

#define PRET_S_ABORT__abro__8_END \
PRET_S_ABORT__abro__8_KILL:\
asm("nop");/*asm("##@PRET_S_ABORT_8_KILL");#@PRET_NL*/\
activeNode=PRET_Abort_Node_ID__abro__8.parent;\
activeNode->next=PRET_End_Abort_Node_ID__abro__8.next;\
activeNode->prev=PRET_Abort_Node_ID__abro__8.prev;\
(PRET_End_Abort_Node_ID__abro__8.next)->prev = activeNode;\
(PRET_Abort_Node_ID__abro__8.prev)->next = activeNode;\
activeNode->spawnCtr = 0;\

#define EOT_abro__14 \
asm("nop");/*asm("#@PRET_EOT start");#@PRET_NL*/\
activeNode->PC = &&EOT__abro__14;\
activeNode = activeNode->next;\
goto *(activeNode->PC);\

#define PRET_S_ABORT__abro__15_START \
asm("nop");/*asm("#@STRONG_ABORT_begin");#@PRET_NL*/\
Node PRET_Abort_Node_ID__abro__15,PRET_End_Abort_Node_ID__abro__15;\
PRET_Abort_Node_ID__abro__15.next=activeNode;\
PRET_Abort_Node_ID__abro__15.prev=activeNode->prev;\
PRET_Abort_Node_ID__abro__15.spawnCtr=0; /*self spwan*/ \
(activeNode->prev)->next=&PRET_Abort_Node_ID__abro__15;\
activeNode->prev=&PRET_Abort_Node_ID__abro__15;\
PRET_Abort_Node_ID__abro__15.parent=activeNode;\
PRET_Abort_Node_ID__abro__15.PC=&&PRET_ABORT__abro__15;\
PRET_End_Abort_Node_ID__abro__15.next=activeNode->next;\
PRET_End_Abort_Node_ID__abro__15.prev=activeNode;\
PRET_End_Abort_Node_ID__abro__15.spawnCtr=0; /*self spwan*/ \
(activeNode->next)->prev=&PRET_End_Abort_Node_ID__abro__15;\
activeNode->next=&PRET_End_Abort_Node_ID__abro__15;\
PRET_End_Abort_Node_ID__abro__15.parent=activeNode;\
PRET_End_Abort_Node_ID__abro__15.PC=&&PRET_END_ABORT__abro__15;\
activeNode->PC = &&PRET_S_ABORT__abro__15_BODY;\
activeNode = &PRET_Abort_Node_ID__abro__15;\
asm("nop");/*asm("##@PRET_ABORT_15");#@PRET_NL*/\
PRET_ABORT__abro__15:;\
if (R == 1) {\
	goto PRET_S_ABORT__abro__15_KILL;\
}else{\
}\
activeNode = activeNode->next;\
goto *(activeNode->PC);\
asm("nop");/*asm("##@PRET_END_ABORT_15");#@PRET_NL*/\
PRET_END_ABORT__abro__15:\
activeNode = activeNode->next;\
goto *(activeNode->PC);\
asm("nop");/*asm("##@PRET_S_ABORT_15_BODY");#@PRET_NL*/\
PRET_S_ABORT__abro__15_BODY:\

#define PAR16 \
asm("nop");/*asm("#@PRET_PAR start");*//*asm("#@PRET_GroupID 16" );#@PRET_NL*/\
(*activeNode).PC = &&abro_join16;\
(*activeNode).spawnCtr += 2;\
/*update the next pointers of parent node*/\
(*activeNode).prev->next = &PRET_Node_tA_ID_4;\
(*activeNode).next->prev = &PRET_Node_tB_ID_5;\
/*update next#@PRET_NL*/\
PRET_Node_tA_ID_4.next=&PRET_Node_tB_ID_5;\
PRET_Node_tB_ID_5.next=(*activeNode).next;\
/*updade prev#@PRET_NL*/\
PRET_Node_tA_ID_4.prev=(*activeNode).prev;\
PRET_Node_tB_ID_5.prev=&PRET_Node_tA_ID_4;\
PRET_Node_tA_ID_4.spawnCtr=0;\
PRET_Node_tB_ID_5.spawnCtr=0;\
PRET_Node_tA_ID_4.deathAddr=&&tA_death;\
PRET_Node_tB_ID_5.deathAddr=&&tB_death;\
PRET_Node_tA_ID_4.parent=&(*activeNode);\
PRET_Node_tB_ID_5.parent=&(*activeNode);\
/*asm("#@PRET_Child0 address");#@PRET_NL*/PRET_Node_tA_ID_4.PC = &&tA;\
/*asm("#@PRET_Child1 address");#@PRET_NL*/PRET_Node_tB_ID_5.PC = &&tB;\
/*change active thread*/ \
activeNode=&PRET_Node_tA_ID_4;\
goto *PRET_Node_tA_ID_4.PC;\

#define EOT_abro__19 \
asm("nop");/*asm("#@PRET_EOT start");#@PRET_NL*/\
activeNode->PC = &&EOT__abro__19;\
activeNode = activeNode->next;\
goto *(activeNode->PC);\

#define PRET_S_ABORT__abro__15_END \
PRET_S_ABORT__abro__15_KILL:\
asm("nop");/*asm("##@PRET_S_ABORT_15_KILL");#@PRET_NL*/\
activeNode=PRET_Abort_Node_ID__abro__15.parent;\
activeNode->next=PRET_End_Abort_Node_ID__abro__15.next;\
activeNode->prev=PRET_Abort_Node_ID__abro__15.prev;\
(PRET_End_Abort_Node_ID__abro__15.next)->prev = activeNode;\
(PRET_Abort_Node_ID__abro__15.prev)->next = activeNode;\
activeNode->spawnCtr = 0;\

#define KILL_abro \
asm("nop");/*asm("#@PRET_KILL start");*//*asm("#@PRET_GroupID 9");#@PRET_NL*/\
(activeNode->parent)->spawnCtr--;\
if((activeNode->parent)->spawnCtr==0) /* means all children are dead, revive parent thread #@PRET_NL*/\
{\
	(activeNode->prev)->next = (activeNode->parent);\
	(activeNode->next)->prev = (activeNode->parent);\
	(activeNode->parent)->prev=activeNode->prev;\
	(activeNode->parent)->next=activeNode->next;\
	activeNode=activeNode->parent;\
	goto *(activeNode->PC);\
}else{\
	(activeNode->prev)->next = activeNode->next;\
	(activeNode->next)->prev = activeNode->prev;\
	activeNode=activeNode->next;\
	goto *(activeNode->PC);\
	asm("nop");/*asm("#@PRET_KILL end");#@PRET_NL*/\
}\

#define PRET_S_ABORT__abro__22_START \
asm("nop");/*asm("#@STRONG_ABORT_begin");#@PRET_NL*/\
Node PRET_Abort_Node_ID__abro__22,PRET_End_Abort_Node_ID__abro__22;\
PRET_Abort_Node_ID__abro__22.next=activeNode;\
PRET_Abort_Node_ID__abro__22.prev=activeNode->prev;\
PRET_Abort_Node_ID__abro__22.spawnCtr=0; /*self spwan*/ \
(activeNode->prev)->next=&PRET_Abort_Node_ID__abro__22;\
activeNode->prev=&PRET_Abort_Node_ID__abro__22;\
PRET_Abort_Node_ID__abro__22.parent=activeNode;\
PRET_Abort_Node_ID__abro__22.PC=&&PRET_ABORT__abro__22;\
PRET_End_Abort_Node_ID__abro__22.next=activeNode->next;\
PRET_End_Abort_Node_ID__abro__22.prev=activeNode;\
PRET_End_Abort_Node_ID__abro__22.spawnCtr=0; /*self spwan*/ \
(activeNode->next)->prev=&PRET_End_Abort_Node_ID__abro__22;\
activeNode->next=&PRET_End_Abort_Node_ID__abro__22;\
PRET_End_Abort_Node_ID__abro__22.parent=activeNode;\
PRET_End_Abort_Node_ID__abro__22.PC=&&PRET_END_ABORT__abro__22;\
activeNode->PC = &&PRET_S_ABORT__abro__22_BODY;\
activeNode = &PRET_Abort_Node_ID__abro__22;\
asm("nop");/*asm("##@PRET_ABORT_22");#@PRET_NL*/\
PRET_ABORT__abro__22:;\
if (A == 1) {\
	goto PRET_S_ABORT__abro__22_KILL;\
}else{\
}\
activeNode = activeNode->next;\
goto *(activeNode->PC);\
asm("nop");/*asm("##@PRET_END_ABORT_22");#@PRET_NL*/\
PRET_END_ABORT__abro__22:\
activeNode = activeNode->next;\
goto *(activeNode->PC);\
asm("nop");/*asm("##@PRET_S_ABORT_22_BODY");#@PRET_NL*/\
PRET_S_ABORT__abro__22_BODY:\

#define EOT_abro__24 \
asm("nop");/*asm("#@PRET_EOT start");#@PRET_NL*/\
activeNode->PC = &&EOT__abro__24;\
activeNode = activeNode->next;\
goto *(activeNode->PC);\

#define PRET_S_ABORT__abro__22_END \
PRET_S_ABORT__abro__22_KILL:\
asm("nop");/*asm("##@PRET_S_ABORT_22_KILL");#@PRET_NL*/\
activeNode=PRET_Abort_Node_ID__abro__22.parent;\
activeNode->next=PRET_End_Abort_Node_ID__abro__22.next;\
activeNode->prev=PRET_Abort_Node_ID__abro__22.prev;\
(PRET_End_Abort_Node_ID__abro__22.next)->prev = activeNode;\
(PRET_Abort_Node_ID__abro__22.prev)->next = activeNode;\
activeNode->spawnCtr = 0;\

#define KILL_tA \
asm("nop");/*asm("#@PRET_KILL start");*//*asm("#@PRET_GroupID 16");#@PRET_NL*/\
(activeNode->parent)->spawnCtr--;\
if((activeNode->parent)->spawnCtr==0) /* means all children are dead, revive parent thread #@PRET_NL*/\
{\
	(activeNode->prev)->next = (activeNode->parent);\
	(activeNode->next)->prev = (activeNode->parent);\
	(activeNode->parent)->prev=activeNode->prev;\
	(activeNode->parent)->next=activeNode->next;\
	activeNode=activeNode->parent;\
	goto *(activeNode->PC);\
}else{\
	(activeNode->prev)->next = activeNode->next;\
	(activeNode->next)->prev = activeNode->prev;\
	activeNode=activeNode->next;\
	goto *(activeNode->PC);\
	asm("nop");/*asm("#@PRET_KILL end");#@PRET_NL*/\
}\

#define PRET_S_ABORT__abro__26_START \
asm("nop");/*asm("#@STRONG_ABORT_begin");#@PRET_NL*/\
Node PRET_Abort_Node_ID__abro__26,PRET_End_Abort_Node_ID__abro__26;\
PRET_Abort_Node_ID__abro__26.next=activeNode;\
PRET_Abort_Node_ID__abro__26.prev=activeNode->prev;\
PRET_Abort_Node_ID__abro__26.spawnCtr=0; /*self spwan*/ \
(activeNode->prev)->next=&PRET_Abort_Node_ID__abro__26;\
activeNode->prev=&PRET_Abort_Node_ID__abro__26;\
PRET_Abort_Node_ID__abro__26.parent=activeNode;\
PRET_Abort_Node_ID__abro__26.PC=&&PRET_ABORT__abro__26;\
PRET_End_Abort_Node_ID__abro__26.next=activeNode->next;\
PRET_End_Abort_Node_ID__abro__26.prev=activeNode;\
PRET_End_Abort_Node_ID__abro__26.spawnCtr=0; /*self spwan*/ \
(activeNode->next)->prev=&PRET_End_Abort_Node_ID__abro__26;\
activeNode->next=&PRET_End_Abort_Node_ID__abro__26;\
PRET_End_Abort_Node_ID__abro__26.parent=activeNode;\
PRET_End_Abort_Node_ID__abro__26.PC=&&PRET_END_ABORT__abro__26;\
activeNode->PC = &&PRET_S_ABORT__abro__26_BODY;\
activeNode = &PRET_Abort_Node_ID__abro__26;\
asm("nop");/*asm("##@PRET_ABORT_26");#@PRET_NL*/\
PRET_ABORT__abro__26:;\
if (B == 1) {\
	goto PRET_S_ABORT__abro__26_KILL;\
}else{\
}\
activeNode = activeNode->next;\
goto *(activeNode->PC);\
asm("nop");/*asm("##@PRET_END_ABORT_26");#@PRET_NL*/\
PRET_END_ABORT__abro__26:\
activeNode = activeNode->next;\
goto *(activeNode->PC);\
asm("nop");/*asm("##@PRET_S_ABORT_26_BODY");#@PRET_NL*/\
PRET_S_ABORT__abro__26_BODY:\

#define EOT_abro__28 \
asm("nop");/*asm("#@PRET_EOT start");#@PRET_NL*/\
activeNode->PC = &&EOT__abro__28;\
activeNode = activeNode->next;\
goto *(activeNode->PC);\

#define PRET_S_ABORT__abro__26_END \
PRET_S_ABORT__abro__26_KILL:\
asm("nop");/*asm("##@PRET_S_ABORT_26_KILL");#@PRET_NL*/\
activeNode=PRET_Abort_Node_ID__abro__26.parent;\
activeNode->next=PRET_End_Abort_Node_ID__abro__26.next;\
activeNode->prev=PRET_Abort_Node_ID__abro__26.prev;\
(PRET_End_Abort_Node_ID__abro__26.next)->prev = activeNode;\
(PRET_Abort_Node_ID__abro__26.prev)->next = activeNode;\
activeNode->spawnCtr = 0;\

#define KILL_tB \
asm("nop");/*asm("#@PRET_KILL start");*//*asm("#@PRET_GroupID 16");#@PRET_NL*/\
(activeNode->parent)->spawnCtr--;\
if((activeNode->parent)->spawnCtr==0) /* means all children are dead, revive parent thread #@PRET_NL*/\
{\
	(activeNode->prev)->next = (activeNode->parent);\
	(activeNode->next)->prev = (activeNode->parent);\
	(activeNode->parent)->prev=activeNode->prev;\
	(activeNode->parent)->next=activeNode->next;\
	activeNode=activeNode->parent;\
	goto *(activeNode->PC);\
}else{\
	(activeNode->prev)->next = activeNode->next;\
	(activeNode->next)->prev = activeNode->prev;\
	activeNode=activeNode->next;\
	goto *(activeNode->PC);\
	asm("nop");/*asm("#@PRET_KILL end");#@PRET_NL*/\
}\

#define EOT_abro__34 \
asm("nop");/*asm("#@PRET_EOT start");#@PRET_NL*/\
activeNode->PC = &&EOT__abro__34;\
activeNode = activeNode->next;\
goto *(activeNode->PC);\

#define KILL_Inputs \
asm("nop");/*asm("#@PRET_KILL start");*//*asm("#@PRET_GroupID 9");#@PRET_NL*/\
(activeNode->parent)->spawnCtr--;\
if((activeNode->parent)->spawnCtr==0) /* means all children are dead, revive parent thread #@PRET_NL*/\
{\
	(activeNode->prev)->next = (activeNode->parent);\
	(activeNode->next)->prev = (activeNode->parent);\
	(activeNode->parent)->prev=activeNode->prev;\
	(activeNode->parent)->next=activeNode->next;\
	activeNode=activeNode->parent;\
	goto *(activeNode->PC);\
}else{\
	(activeNode->prev)->next = activeNode->next;\
	(activeNode->next)->prev = activeNode->prev;\
	activeNode=activeNode->next;\
	goto *(activeNode->PC);\
	asm("nop");/*asm("#@PRET_KILL end");#@PRET_NL*/\
}\

#define EOT_abro__39 \
asm("nop");/*asm("#@PRET_EOT start");#@PRET_NL*/\
activeNode->PC = &&EOT__abro__39;\
activeNode = activeNode->next;\
goto *(activeNode->PC);\

#define KILL_Results \
asm("nop");/*asm("#@PRET_KILL start");*//*asm("#@PRET_GroupID 9");#@PRET_NL*/\
(activeNode->parent)->spawnCtr--;\
if((activeNode->parent)->spawnCtr==0) /* means all children are dead, revive parent thread #@PRET_NL*/\
{\
	(activeNode->prev)->next = (activeNode->parent);\
	(activeNode->next)->prev = (activeNode->parent);\
	(activeNode->parent)->prev=activeNode->prev;\
	(activeNode->parent)->next=activeNode->next;\
	activeNode=activeNode->parent;\
	goto *(activeNode->PC);\
}else{\
	(activeNode->prev)->next = activeNode->next;\
	(activeNode->next)->prev = activeNode->prev;\
	activeNode=activeNode->next;\
	goto *(activeNode->PC);\
	asm("nop");/*asm("#@PRET_KILL end");#@PRET_NL*/\
}\


