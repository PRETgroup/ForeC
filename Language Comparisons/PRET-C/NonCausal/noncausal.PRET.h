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
#define EOT_noncausal__9 \
asm("nop");/*asm("#@PRET_EOT start");#@PRET_NL*/\
activeNode->PC = &&EOT__noncausal__9;\
activeNode = activeNode->next;\
goto *(activeNode->PC);\

#define PAR12 \
asm("nop");/*asm("#@PRET_PAR start");*//*asm("#@PRET_GroupID 12" );#@PRET_NL*/\
(*activeNode).PC = &&main_join12;\
(*activeNode).spawnCtr += 2;\
/*update the next pointers of parent node*/\
(*activeNode).prev->next = &PRET_Node_t0_ID_1;\
(*activeNode).next->prev = &PRET_Node_t1_ID_2;\
/*update next#@PRET_NL*/\
PRET_Node_t0_ID_1.next=&PRET_Node_t1_ID_2;\
PRET_Node_t1_ID_2.next=(*activeNode).next;\
/*updade prev#@PRET_NL*/\
PRET_Node_t0_ID_1.prev=(*activeNode).prev;\
PRET_Node_t1_ID_2.prev=&PRET_Node_t0_ID_1;\
PRET_Node_t0_ID_1.spawnCtr=0;\
PRET_Node_t1_ID_2.spawnCtr=0;\
PRET_Node_t0_ID_1.deathAddr=&&t0_death;\
PRET_Node_t1_ID_2.deathAddr=&&t1_death;\
PRET_Node_t0_ID_1.parent=&(*activeNode);\
PRET_Node_t1_ID_2.parent=&(*activeNode);\
/*asm("#@PRET_Child0 address");#@PRET_NL*/PRET_Node_t0_ID_1.PC = &&t0;\
/*asm("#@PRET_Child1 address");#@PRET_NL*/PRET_Node_t1_ID_2.PC = &&t1;\
/*change active thread*/ \
activeNode=&PRET_Node_t0_ID_1;\
goto *PRET_Node_t0_ID_1.PC;\

#define KILL_t0 \
asm("nop");/*asm("#@PRET_KILL start");*//*asm("#@PRET_GroupID 12");#@PRET_NL*/\
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

#define KILL_t1 \
asm("nop");/*asm("#@PRET_KILL start");*//*asm("#@PRET_GroupID 12");#@PRET_NL*/\
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


