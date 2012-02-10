#ifndef MOD_DATA_H_INCLUDED
#define MOD_DATA_H_INCLUDED

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
};

//globals
struct nodeTree *pNodeTreeMaster;
struct nodeTree *currentNode;
char sCurrentPrompt[MAX_PROMPT];

// exported functions
void dataInit(); // Initialisation
struct nodeTree* addNode(struct nodeTree*,char*,char*); //Adds a node to the tree.

// internal functions
void* __memNewNode(); // mallocs and init a new node



#endif // MOD_DATA_H_INCLUDED

