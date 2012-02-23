#ifndef MOD_DATA_H_INCLUDED
#define MOD_DATA_H_INCLUDED

/*
mod_data
Do: Node registration and node handling
IS MANDATORY
*/


// MIN/MAX Values
#define MAX_PROMPT 20
#define MAX_HELP 2048

// root level names
#define ROOT_PROMPT "root"
#define ROOT_HELP "Top level"

// Data structures
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

//globals
struct nodeTree *pNodeTreeMaster;
struct nodeTree *pCurrentNode;
char sCurrentPrompt[MAX_PROMPT];

// exported functions
void dataInit(); // Initialisation
struct nodeTree* addNode(struct nodeTree*,char*,char*,void (*pFunc)(int,char**), void (*pFuncHelp)() ); //Adds a node to the tree.
void switchToNode(struct nodeTree*); // Switch to the given node
struct nodeTree* getNodeByPrompt(struct nodeTree*, char*); // Returns the nodes address of a given prompt in current level

// internal functions
void* __memNewNode(); // mallocs and init a new node
void __setPrompt(char *sPrompt);



#endif // MOD_DATA_H_INCLUDED

