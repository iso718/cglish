#ifndef MOD_DATA_H_INCLUDED
#define MOD_DATA_H_INCLUDED

/* Includes */
#include "cglish.h" // includes standard libs and cglish stuff
// add special libs here


/* Definitions */
#define MAX_PROMPT 20
#define MAX_HELP 2048
#define ROOT_PROMPT "root"
#define ROOT_HELP "Top level"

/* extern functions */

/* exported control functions (init, help,..)  */
void dataInit();
/* other exported functions */
struct nodeTree* dataAddNode(struct nodeTree*,char*,char*,void (*pFunc)(int,char**), void (*pFuncHelp)() ); //Adds a node to the tree.
void dataSwitchToNode(struct nodeTree*); // Switch to the given node
struct nodeTree* dataGetNodeByPrompt(struct nodeTree*, char*); // Returns the nodes address of a given prompt in current level

/* exported global vars */

/* internal functions */
void* __memNewNode(); // mallocs and init a new node
void __setPrompt(char *sPrompt);
/* internal global vars  */
struct nodeTree {
    struct nodeTree *pMaster;
    struct nodeTree *pFirstChild;
    struct nodeTree *pNext;
    struct nodeTree *pPrev;
    char sPrompt[MAX_PROMPT];
    char sHelp[MAX_HELP];
    void (*pFunc)(int,char**);
    void (*pFuncHelp)();
};
struct nodeTree *pNodeTreeMaster;
struct nodeTree *pCurrentNode;
char sCurrentPrompt[MAX_PROMPT];

#endif // MOD_DATA_H_INCLUDED

