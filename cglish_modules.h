#ifndef CGLISH_MODULES_H_INCLUDED
#define CGLISH_MODULES_H_INCLUDED

#define MAX_PROMPT 10
#define MAX_HELP 2048

typedef struct {
void (*pFunc) (int);  // 0=init, 1=clean
}t_initMod;
typedef struct {
    char sPrompt[MAX_PROMPT];
    char sHelp[MAX_HELP];
    void (*pFunc)(int,char**);
}t_nodeData;

typedef struct {
    void *pMaster;
    void *pFirstChild;
    void *pNextNode;
    void *pPrevNode;
    t_nodeData *pData;
}t_node;

// Administration
t_node* nodeInit(); //Wrapper to create a first node.
t_node* registerModule(t_node*, char*, char*, void (*)()); //Add new Module function in the tree
t_node* __nodeAdd(t_node*, t_nodeData*); // malloc and append new node
t_nodeData* __nodeDataAdd(char *sPrompt, char *sHelp, void (*pFunc)()); //malloc and init new Data

// Data Level
char* dataGetPrompt(t_node*); //Returns the prompt of a give node
t_node* getNodeByPrompt(t_node*,char*); //Returns the node which have the given prompt.


/* Module registration */
// include your module here
#include "mod_console.h"
#include "mod_history.h"
#include "mod_math.h"

//Add your init/quit function
#define INIT_MODULES \
t_initMod initMods[]={ \
{&hist_init}, \
{&math_init}, \
{NULL} \
 }

#endif // CGLISH_MODULES_H_INCLUDED
