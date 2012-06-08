#ifndef CGLISH_MODULES_H_INCLUDED
#define CGLISH_MODULES_H_INCLUDED

#define MAX_PROMPT 10
#define MAX_HELP 2048

typedef struct {
void (*pFunc) (int);  // 0=init, 1=clean
}t_initMod;

typedef struct {
    void *pMaster;
    void *pFirstChild;
    void *pNextNode;
    void *pPrevNode;
    void *pData;
}t_node;

typedef struct {
    char sPrompt[MAX_PROMPT];
    char sHelp[MAX_HELP];
    void (*pFunc)(char**);
}t_nodeData;

t_node* modCreateNode(t_node*); // mallocs new node and call __addchildnode
t_nodeData* modCreateNodeData(char *sPrompt, char *sHelp, void (*pFunc)()); //malloc and init new Data
void* __malloc(int size); // malloc mit Fehlerprüfung
void __addChildNode(t_node*); // Fügt child in den tree ein
/* Module registration */
#define NR_MODULES 10  //Increase on demand
// include your module here
//#include "module1.h"

//Add your init function
#define INIT_MODULES \
t_initMod initMods[NR_MODULES]={ \
{&test}, \
{NULL} \
 }

#endif // CGLISH_MODULES_H_INCLUDED
