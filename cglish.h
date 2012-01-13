#ifndef CGLISH_H_INCLUDED
#define CGLISH_H_INCLUDED

#define DEBUG

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_INPUT 1024

#define MSG_CON(MSG,...) printf(MSG,##__VA_ARGS__);

#ifdef DEBUG
#define MSG_DBG(MSG,...) fprintf(stdout,"DEBUG: (%s:%d) " MSG "\n",__FILE__,__LINE__,##__VA_ARGS__)
#else
#define MSG_DBG(MSG,...)
#endif

#include "cglish_modules.h"

t_node *pMasterNode;
t_node *pCurNode;

void exitOnNULLPointer(void* pToCheck);  //Exit if pointer is NULL

// Init Functions
void __initModules();
void __initBtree();
void __mainloop();
#endif // CGLISH_H_INCLUDED


/*
DONE: Konzept Module einbinden
DONE: Basic Btree implementation
DONE: Interface for registering modules
DONE: Basic MSG output
TODO:
+) Create simple module and function
-) Input loop
*/
