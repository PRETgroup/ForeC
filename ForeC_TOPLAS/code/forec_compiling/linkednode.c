// Node definition
typedef struct _Node { (*\label{code:forec_compiling:linkednode_Node}*)
	void *pc; 
	struct _Node *prev, *next;
} Node;
// Insert node n2 after n1
#define insert(n1,n2)          \(*\label{code:forec_compiling:linkednode_insert}*)
	n2.prev = &n1;               \
	n2.next = n1.next;           \
	n1.next->prev = &n2;         \
	n1.next = &n2
// Remove node n2 from the list
#define remove(n2)             \(*\label{code:forec_compiling:linkednode_remove}*)
	n2.prev->next = n2.next;     \
	n2.next->prev = n2.prev
