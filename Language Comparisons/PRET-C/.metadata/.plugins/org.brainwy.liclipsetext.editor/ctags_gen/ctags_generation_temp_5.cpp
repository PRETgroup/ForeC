#include "Simulation.h"


// This stuff is just here for milestone 3
// need to add this code when testing on windows
#ifdef WIN32
#include <windows.h>
#include <time.h>
int gettimeofday(struct timeval* tp, void* tzp) 
{ 
	DWORD t; 
	t = GetTickCount(); 
	tp->tv_sec = t / 1000; 
	tp->tv_usec = (t % 1000) * 1000; 
	return 0; // 0 indicates that the call succeeded. 
} 
void timersub( const struct timeval * tvp, const struct timeval * uvp, struct timeval 
* vvp ) 
{ 
	vvp->tv_sec = tvp->tv_sec - uvp->tv_sec; 
	vvp->tv_usec = tvp->tv_usec - uvp->tv_usec; 
	if( vvp->tv_usec < 0 ) 
	{ 
	   --vvp->tv_sec; 
	   vvp->tv_usec += 1000000; 
	} 
} 
#endif

void voidToString(void* value, IEC61131Type type, int arraylen, char* result)
{

    int i;
    unsigned int ui;

    switch(type)
	{
		case IEC_INT:
		    i = *(short*)value;
			itoa(i,result,10);
			break;
		case IEC_UINT:
			ui = *(unsigned short*)value;
			itoa(ui,result,10);
			break;
		case IEC_DINT:
			itoa(*(int*)value,result,10);
			break;
		case IEC_UDINT:
			itoa(*(unsigned int*)value,result,10);
			break;
		case IEC_LINT:
			itoa(*(long*)value,result,10);
			break;
		case IEC_ULINT:
			itoa(*(unsigned long*)value,result,10);
			break;
		case IEC_BOOL:
			i = *(bool*)value;
			itoa(i,result,10);
			break;
		default:
	        printf("Unknown type: %d\n", type);
		    result = 0;
			break;
	}
}

void stringToVoid(char* value, IEC61131Type type, int arraylen, void* result)
{

    int i;
    unsigned int ui;
	long l;
	unsigned long ul;
    switch(type)
	{
		case IEC_INT:
		    i = atoi(value);
			*(short*)result = i;
			break;
		case IEC_UINT:
			i = atoi(value);
			*(unsigned short*)result = i;
			break;
		case IEC_DINT:
			i = atoi(value);
			*(int*)result = i;
			break;
		case IEC_UDINT:
			i = atoi(value);
			*(unsigned int*)result = i;
			break;
		case IEC_LINT:
			l = atol(value);
			*(long*)result = l;
			break;
		case IEC_ULINT:
			ul = atol(value);
			*(unsigned long*)result = ul;
			break;
		case IEC_BOOL:
			if( stricmp(value,"true") == 0) 
				*(char*)result = 1;
			else //if( stricmp(value,"true") == 0) 
				*(char*)result = 0;
			break;
		case IEC_STRING:
		case IEC_WSTRING:
			strcpy((char*)result,value);
			break;
		default:
	        printf("Unknown type: %d\n", type);
		    result = 0;
			break;
	}
}


void appendConnectionToXML(mxml_node_t* simdata, char* source, char* destination){
    mxml_node_t* connection = mxmlNewElement(simdata, "Connection");
	mxmlElementSetAttr(connection, "Source", source);
	mxmlElementSetAttr(connection, "Destination", destination);
}

void appendEventOutputToXML(mxml_node_t* simdata, char* eventname){
    mxml_node_t* connection = mxmlNewElement(simdata, "Event");
	mxmlElementSetAttr(connection, "Name", eventname);
}

void appendVarToXML(mxml_node_t* simdata, char* varname, void* value, IEC61131Type vartype, int arraylen){
    char valstring[32];
	mxml_node_t* var = mxmlNewElement(simdata, "Var");
	
    voidToString(value, vartype, arraylen, valstring);
	
	mxmlElementSetAttr(var, "Name", varname);
	mxmlElementSetAttr(var, "Value", valstring);

}

// TODO: HCECC parent
void appendTransitionToXML(mxml_node_t* simdata, char* srcState, char* destState, char* condition){
	mxml_node_t* transition = mxmlNewElement(simdata, "ECTransition");
	
    mxmlElementSetAttr(transition, "Source", srcState);
	mxmlElementSetAttr(transition, "Destination", destState);
	mxmlElementSetAttr(transition, "Condition", condition);

}

//Used to Remove: Events / Transitions / Connections
void clearChildren(mxml_node_t* node){
	mxml_node_t* child;
	if( node->child == NULL ) return;
	child = node->child;
	deleteNexts(child);
	mxmlDelete(child);
	
}

void deleteNexts(mxml_node_t* child)
{
	if( child == NULL ) return;

	if( child->next != NULL )
	{
	    deleteNexts(child->next);
		mxmlDelete(child->next);
	}
}

	
	// Pretty Print (ISH)
const char *   whitespace_cb(mxml_node_t *node, int where)
{
	static int indent = 0;
	switch(where)
	{
		case MXML_WS_AFTER_OPEN:
			if( node->child != NULL ) 
				return "\t";
			else
				return NULL;
		case MXML_WS_BEFORE_OPEN:
			return "\n";
		case MXML_WS_AFTER_CLOSE:
			return NULL;
		case MXML_WS_BEFORE_CLOSE:
			return NULL;
			
	}



}

