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
#define PRET_W_ABORT__abort__2_START \
asm("nop");/*asm("#@WAEK_ABORT_begin");#@PRET_NL*/\
Node PRET_Abort_Node_ID__abort__2,PRET_End_Abort_Node_ID__abort__2;\
PRET_Abort_Node_ID__abort__2.next=activeNode->next;\
PRET_Abort_Node_ID__abort__2.prev=activeNode;\
PRET_Abort_Node_ID__abort__2.spawnCtr=0; /*self spwan*/ \
(activeNode->next)->prev=&PRET_Abort_Node_ID__abort__2;\
activeNode->next=&PRET_Abort_Node_ID__abort__2;\
PRET_Abort_Node_ID__abort__2.parent=activeNode;\
PRET_Abort_Node_ID__abort__2.PC=&&PRET_ABORT__abort__2;\
PRET_End_Abort_Node_ID__abort__2.next=activeNode;\
PRET_End_Abort_Node_ID__abort__2.prev=activeNode->prev;\
PRET_End_Abort_Node_ID__abort__2.spawnCtr=0; /*self spwan*/ \
(activeNode->prev)->next=&PRET_End_Abort_Node_ID__abort__2;\
activeNode->prev=&PRET_End_Abort_Node_ID__abort__2;\
PRET_End_Abort_Node_ID__abort__2.parent=activeNode;\
PRET_End_Abort_Node_ID__abort__2.PC=&&PRET_END_ABORT__abort__2;\
activeNode->PC = &&PRET_W_ABORT__abort__2_BODY;\
goto *(activeNode->PC);\
asm("nop");/*asm("##@PRET_ABORT_2");#@PRET_NL*/\
PRET_ABORT__abort__2:;\
if (apple == 3) {\
	goto PRET_W_ABORT__abort__2_KILL;\
}else{\
}\
activeNode = activeNode->next;\
goto *(activeNode->PC);\
asm("nop");/*asm("##@PRET_END_ABORT_2");#@PRET_NL*/\
PRET_END_ABORT__abort__2:\
activeNode = activeNode->next;\
goto *(activeNode->PC);\
asm("nop");/*asm("##@PRET_W_ABORT_2_BODY");#@PRET_NL*/\
PRET_W_ABORT__abort__2_BODY:\

#define PRET_S_ABORT__abort__3_START \
asm("nop");/*asm("#@STRONG_ABORT_begin");#@PRET_NL*/\
Node PRET_Abort_Node_ID__abort__3,PRET_End_Abort_Node_ID__abort__3;\
PRET_Abort_Node_ID__abort__3.next=activeNode;\
PRET_Abort_Node_ID__abort__3.prev=activeNode->prev;\
PRET_Abort_Node_ID__abort__3.spawnCtr=0; /*self spwan*/ \
(activeNode->prev)->next=&PRET_Abort_Node_ID__abort__3;\
activeNode->prev=&PRET_Abort_Node_ID__abort__3;\
PRET_Abort_Node_ID__abort__3.parent=activeNode;\
PRET_Abort_Node_ID__abort__3.PC=&&PRET_ABORT__abort__3;\
PRET_End_Abort_Node_ID__abort__3.next=activeNode->next;\
PRET_End_Abort_Node_ID__abort__3.prev=activeNode;\
PRET_End_Abort_Node_ID__abort__3.spawnCtr=0; /*self spwan*/ \
(activeNode->next)->prev=&PRET_End_Abort_Node_ID__abort__3;\
activeNode->next=&PRET_End_Abort_Node_ID__abort__3;\
PRET_End_Abort_Node_ID__abort__3.parent=activeNode;\
PRET_End_Abort_Node_ID__abort__3.PC=&&PRET_END_ABORT__abort__3;\
activeNode->PC = &&PRET_S_ABORT__abort__3_BODY;\
activeNode = &PRET_Abort_Node_ID__abort__3;\
asm("nop");/*asm("##@PRET_ABORT_3");#@PRET_NL*/\
PRET_ABORT__abort__3:;\
if (apple == 3) {\
	goto PRET_S_ABORT__abort__3_KILL;\
}else{\
}\
activeNode = activeNode->next;\
goto *(activeNode->PC);\
asm("nop");/*asm("##@PRET_END_ABORT_3");#@PRET_NL*/\
PRET_END_ABORT__abort__3:\
activeNode = activeNode->next;\
goto *(activeNode->PC);\
asm("nop");/*asm("##@PRET_S_ABORT_3_BODY");#@PRET_NL*/\
PRET_S_ABORT__abort__3_BODY:\

#define PAR6 \
asm("nop");/*asm("#@PRET_PAR start");*//*asm("#@PRET_GroupID 6" );#@PRET_NL*/\
(*activeNode).PC = &&main_join6;\
(*activeNode).spawnCtr += 2;\
/*update the next pointers of parent node*/\
(*activeNode).prev->next = &PRET_Node_t1_ID_1;\
(*activeNode).next->prev = &PRET_Node_t2_ID_2;\
/*update next#@PRET_NL*/\
PRET_Node_t1_ID_1.next=&PRET_Node_t2_ID_2;\
PRET_Node_t2_ID_2.next=(*activeNode).next;\
/*updade prev#@PRET_NL*/\
PRET_Node_t1_ID_1.prev=(*activeNode).prev;\
PRET_Node_t2_ID_2.prev=&PRET_Node_t1_ID_1;\
PRET_Node_t1_ID_1.spawnCtr=0;\
PRET_Node_t2_ID_2.spawnCtr=0;\
PRET_Node_t1_ID_1.deathAddr=&&t1_death;\
PRET_Node_t2_ID_2.deathAddr=&&t2_death;\
PRET_Node_t1_ID_1.parent=&(*activeNode);\
PRET_Node_t2_ID_2.parent=&(*activeNode);\
/*asm("#@PRET_Child0 address");#@PRET_NL*/PRET_Node_t1_ID_1.PC = &&t1;\
/*asm("#@PRET_Child1 address");#@PRET_NL*/PRET_Node_t2_ID_2.PC = &&t2;\
/*change active thread*/ \
activeNode=&PRET_Node_t1_ID_1;\
goto *PRET_Node_t1_ID_1.PC;\

#define EOT_abort__7 \
asm("nop");/*asm("#@PRET_EOT start");#@PRET_NL*/\
activeNode->PC = &&EOT__abort__7;\
activeNode = activeNode->next;\
goto *(activeNode->PC);\

#define PRET_S_ABORT__abort__3_END \
PRET_S_ABORT__abort__3_KILL:\
asm("nop");/*asm("##@PRET_S_ABORT_3_KILL");#@PRET_NL*/\
activeNode=PRET_Abort_Node_ID__abort__3.parent;\
activeNode->next=PRET_End_Abort_Node_ID__abort__3.next;\
activeNode->prev=PRET_Abort_Node_ID__abort__3.prev;\
(PRET_End_Abort_Node_ID__abort__3.next)->prev = activeNode;\
(PRET_Abort_Node_ID__abort__3.prev)->next = activeNode;\
activeNode->spawnCtr = 0;\

#define PRET_W_ABORT__abort__2_END \
PRET_W_ABORT__abort__2_KILL:\
asm("nop");/*asm("##@PRET_W_ABORT_2_KILL");#@PRET_NL*/\
activeNode=PRET_Abort_Node_ID__abort__2.parent;\
activeNode->next=PRET_Abort_Node_ID__abort__2.next;\
activeNode->prev=PRET_End_Abort_Node_ID__abort__2.prev;\
(PRET_Abort_Node_ID__abort__2.next)->prev = activeNode;\
(PRET_End_Abort_Node_ID__abort__2.prev)->next = activeNode;\
activeNode->spawnCtr = 0;\

#define EOT_abort__10 \
asm("nop");/*asm("#@PRET_EOT start");#@PRET_NL*/\
activeNode->PC = &&EOT__abort__10;\
activeNode = activeNode->next;\
goto *(activeNode->PC);\

#define KILL_t1 \
asm("nop");/*asm("#@PRET_KILL start");*//*asm("#@PRET_GroupID 6");#@PRET_NL*/\
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

#define EOT_abort__13 \
asm("nop");/*asm("#@PRET_EOT start");#@PRET_NL*/\
activeNode->PC = &&EOT__abort__13;\
activeNode = activeNode->next;\
goto *(activeNode->PC);\

#define EOT_abort__15 \
asm("nop");/*asm("#@PRET_EOT start");#@PRET_NL*/\
activeNode->PC = &&EOT__abort__15;\
activeNode = activeNode->next;\
goto *(activeNode->PC);\

#define KILL_t2 \
asm("nop");/*asm("#@PRET_KILL start");*//*asm("#@PRET_GroupID 6");#@PRET_NL*/\
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


