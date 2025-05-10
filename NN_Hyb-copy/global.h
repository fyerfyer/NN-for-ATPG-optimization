
/***********************************************************************

		Copyright (C) 1991,
		Virginia Polytechnic Institute & State University

		This program was originally written by Mr. Hyung K. Lee
		under the supervision of Dr. Dong S. Ha, in the Bradley
		Department of Electrical Engineering, VPI&SU, in 1991.

		This program is released for research use only. This program,
		or any derivative thereof, may not be reproduced nor used
		for any commercial product without the written permission
		of the authors.

		For detailed information, please contact to

		Dr. Dong S. Ha
		Bradley Department of Electrical Engineering
		Virginia Polytechnic Institute & State University
		Blacksburg, VA 24061

		Ph.: (540) 231-4942
		Fax: (540) 231-3362
		E-Mail: ha@vt.edu
		Web: http://www.ee.vt.edu/ha

		REFERENCE:
		   H. K. Lee and D. S. Ha, "On the Generation of Test Patterns
		   for Combinational Circuits," Technical Report No. 12_93,
		   Dep't of Electrical Eng., Virginia Polytechnic Institute
		   and State University.

***********************************************************************/

/**************************** HISTORY **********************************
 
		atalanta: version 1.0   	 H. K. Lee, 8/15/1991
		atalanta: version 1.1   	 H. K. Lee, 10/5/1992
		atalanta: version 2.0   	 H. K. Lee, 6/30/1997
 
***********************************************************************/

/*----------------------------------------------------------------------
	global.h
	Define global variables of atalanta.
-----------------------------------------------------------------------*/

#ifndef __ATALANTA_GLOBAL_D__
#define __ATALANTA_GLOBAL_D__

#include "define.h"
#include "parameter.h"
#include <cstdio>

//test for learning
extern FILE *mldb_ptr;
extern bool Apply_model;
extern char name[100];
extern bool lookup;

extern GATEPTR *g_net;		/* circuit structure */
extern int *g_PrimaryIn, *g_PrimaryOut, *g_FlipFlop, *g_iHeadGateIndex;
extern int g_iNoGate, g_iNoPI, g_iNoPO, g_iNoFF, g_iNoFault, nodummy, g_iLastGate;
extern int g_iMaxLevel, g_iPOLevel, g_iPPOLevel;

extern int *depth_array;
extern STACKPTR g_pEventListStack;		/* event list */
extern struct FAULT **g_pFaultList;	/* fault list */

#ifdef INCLUDE_HOPE
extern FAULTPTR g_pHeadFault, g_pTailFault, g_pCurrentFault;
extern EVENTPTR g_headEvent, g_tailEvent;
#endif

extern struct ROOTTREE g_tree;

/* static buffers for fan */
extern STACKTYPE g_unjustStack;		/* set of unjustified lines */
extern STACKTYPE g_initObjStack;		/* set of initial objectives */
extern STACKTYPE g_curObjStack;		/* set of current objectives */
extern STACKTYPE g_fanObjStack;		/* set of fanout objectives */
extern STACKTYPE g_headObjStack;		/* set of head objectives */
extern STACKTYPE g_finalObjStack;		/* set of final objectives */
extern STACKTYPE g_DfrontierStack;		/* set of Dfrotiers */
extern STACKTYPE g_stack;			/* stack for backtracing */

/* buffers for the fault simulator */
extern STACKTYPE g_freeGatesStack;		/* fault free simulation */
extern STACKTYPE g_faultyGatesStack;		/* list of faulty gates */
extern STACKTYPE g_evalGatesStack;		/* STEM_LIST to be simulated */
extern STACKTYPE g_activeStemStack;		/* list of active stems */
extern GATEPTR *g_dynamicStack;
extern int g_iSStack, g_iDStack;

extern FILE *g_fpCctFile, *g_fpTestFile, *g_fpLogFile;
extern int mac_i;

/* global variables for bit operations */
extern level g_iAllOne;
extern status g_iUpdateFlag, g_iUpdateFlag2; //pFault->gate->nfault == 0
extern struct STACK g_stack1, g_stack2;

/* Variables for hope */
extern char initialmode;
extern char xdetectmode;

extern level g_PIValues[MAXPI];

extern level BITMASK[32];

extern char fn_to_string[][MAXGTYPE + 3];   /* gate function to string */
extern char level_to_string[][MAXLEVEL + 1];      /* level to string */
extern char fault_to_string[][3];   /* fault type to string */
extern level parallel_to_level[2][2];		 /* parallel level types to level */

#endif /* __ATALANTA_GLOBAL_D__ */