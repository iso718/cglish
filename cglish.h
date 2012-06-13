#ifndef CGLISH_H_INCLUDED
#define CGLISH_H_INCLUDED

#define DEBUG
#define DEBUG_MEMORY
#define DEBUG_NODEMGMT

#undef FALLBACK

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_INPUT 1024
#define MSG_OUT(MSG,...) printf(MSG,##__VA_ARGS__);fflush(stdout)

#ifdef DEBUG_MEMORY
#define MSG_DBG_MEM(MSG,...) fprintf(stdout,"DEBUG MEM: (%s:%d) " MSG "\n",__FILE__,__LINE__,##__VA_ARGS__); fflush(stdout)
#else
#define MSG_DBG_MEM(MSG,...)
#endif

#ifdef DEBUG_NODEMGMT
#define MSG_DBG_NOD(MSG,...) fprintf(stdout,"DEBUG NOD: (%s:%d) " MSG "\n",__FILE__,__LINE__,##__VA_ARGS__); fflush(stdout)
#else
#define MSG_DBG_NOD(MSG,...)
#endif

#ifdef DEBUG
#define MSG_DBG(MSG,...) fprintf(stdout,"DEBUG: (%s:%d) " MSG "\n",__FILE__,__LINE__,##__VA_ARGS__); fflush(stdout)
#else
#define MSG_DBG(MSG,...)
#endif

#include "cglish_tools.h"
#include "cglish_modules.h"
#include"cglish_console.h"



// globals
enum userRetval {NORMAL,ABORT,QUIT};

t_node *pMasterNode;
t_node *pCurNode;

void __processUserInput(char*); //Process the userInput and do the module actions. It will modify char*(stripStr)
void __init();
void __quit();
void __mainloop();

#endif // CGLISH_H_INCLUDED


/*
DONE: Konzept Module einbinden
DONE: Basic Btree implementation
DONE: Interface for registering modules
DONE: Basic MSG output
DONE: Create simple module and function
DONE: Input loop
DONE: Process User Input
TODO: Console
-) Init Console
-) Special Key handling:
    -) Backspace
    -) Tab -> Auto vervollständigung
    -) Pfeil up -> History
    -) Pfeil links/Rechts -> im String wandern
    -) Enter -> Process User Args
*/
