#include "global.h"
#include <cstdio>

//test for learning
FILE *mldb_ptr;
bool Apply_model = false;
char name[100]="";
bool lookup = true;

GATEPTR *g_net;		/* circuit structure */
int *g_PrimaryIn, *g_PrimaryOut, *g_FlipFlop, *g_iHeadGateIndex;
int g_iNoGate = 0, g_iNoPI = 0, g_iNoPO = 0, g_iNoFF = 0, g_iNoFault = 0, nodummy = 0, g_iLastGate;
int g_iMaxLevel, g_iPOLevel, g_iPPOLevel;

int *depth_array;
STACKPTR g_pEventListStack;		/* event list */
struct FAULT **g_pFaultList;	/* fault list */

#ifdef INCLUDE_HOPE
FAULTPTR g_pHeadFault, g_pTailFault, g_pCurrentFault;
EVENTPTR g_headEvent, g_tailEvent;
#endif

struct ROOTTREE g_tree;

/* static buffers for fan */
STACKTYPE g_unjustStack;		/* set of unjustified lines */
STACKTYPE g_initObjStack;			/* set of initial objectives */
STACKTYPE g_curObjStack;			/* set of current objectives */
STACKTYPE g_fanObjStack;			/* set of fanout objectives */
STACKTYPE g_headObjStack;			/* set of head objectives */
STACKTYPE g_finalObjStack;		/* set of final objectives */
STACKTYPE g_DfrontierStack;		/* set of Dfrotiers */
STACKTYPE g_stack;			/* stack for backtracing */

/* buffers for the fault simulator */
STACKTYPE g_freeGatesStack;		/* fault free simulation */
STACKTYPE g_faultyGatesStack;		/* list of faulty gates */
STACKTYPE g_evalGatesStack;		/* STEM_LIST to be simulated */
STACKTYPE g_activeStemStack;		/* list of active stems */
GATEPTR *g_dynamicStack;
int g_iSStack, g_iDStack;

FILE *g_fpCctFile, *g_fpTestFile, *g_fpLogFile;
int mac_i;

/* global variables for bit operations */
level g_iAllOne;
status g_iUpdateFlag, g_iUpdateFlag2; //pFault->gate->nfault == 0
struct STACK g_stack1, g_stack2;

/* Variables for hope */
char initialmode = 'x';
char xdetectmode = 'n';

level g_PIValues[MAXPI];

level BITMASK[32] =
{
    MASK0, MASK0 << 1, MASK0 << 2, MASK0 << 3, MASK0 << 4, MASK0 << 5, MASK0 << 6, MASK0 << 7, MASK0 << 8, MASK0 << 9, MASK0 << 10, MASK0 << 11, MASK0 << 12, MASK0 << 13, MASK0 << 14, MASK0 << 15, MASK0 << 16, MASK0 << 17, MASK0 << 18, MASK0 << 19, MASK0 << 20, MASK0 << 21, MASK0 << 22, MASK0 << 23, MASK0 << 24, MASK0 << 25, MASK0 << 26, MASK0 << 27, MASK0 << 28, MASK0 << 29, MASK0 << 30, MASK0 << 31
};

char fn_to_string[][MAXGTYPE + 3] =  	   /* gate function to string */
{
    "AND", "NAND", "OR", "NOR", "INPUT", "XOR", "XNOR", "DFF", "DUMMY", "BUFFER", "NOT", "", "", "", "", "", "", "", "", "", "PO",
};
char level_to_string[][MAXLEVEL + 1] =      /* level to string */
{
    "0", "1", "x", "z",
};
char fault_to_string[][3] =
{
    "/0", "/1"
};   /* fault type to string */
level parallel_to_level[2][2] = 		 /* parallel level types to level */
{
    {X,ONE}, {ZERO,Z}
};