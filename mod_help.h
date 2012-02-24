#ifndef MOD_HELP_H_INCLUDED
#define MOD_HELP_H_INCLUDED

/* help module
This module provide the help functionality
and export functions for  module and global help output

Basic concept:
Press ? will show the local (modules) help
help or 'h' as command will show the global help

Implementation:

*/

/* definitions */


/* Includes */
#include "cglish.h" // includes standard libs and cglish stuff

//  special libs

/* extern functions */
struct nodeTree* dataAddNode(struct nodeTree *pMaster,char *sPrompt,char *sHelp,void (*pFunc)(int,char**) , void (*pFuncHelp)() );


/* exported control functions (init, help,..) */
void helpInit();
/* other exported functions */

/* exported global vars */
helpMsg
/* internal functions */

/* internal global vars  */


#endif // MOD_HELP_H_INCLUDED
