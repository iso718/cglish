#include "cglish.h"
void dataInit(){
    // init the nodes tree
    pNodeTreeMaster=(struct nodeTree*) __memNewNode();
    strncpy(pNodeTreeMaster->sPrompt,ROOT_PROMPT,MAX_PROMPT);
    strncpy(pNodeTreeMaster->sHelp,ROOT_HELP,MAX_HELP);
    currentNode=pNodeTreeMaster;
    strncpy(sCurrentPrompt,ROOT_PROMPT,MAX_PROMPT);
    ADD_LOG_ENTRY("mod_data[init]: Node Tree initialisation done. Master node at <%p>, sCurrentPrompt at <%p>\n",pNodeTreeMaster,&sCurrentPrompt);
}


struct nodeTree* addNode(struct nodeTree *pMaster,char *sPrompt,char *sHelp  ){//Adds a node to the tree
    struct nodeTree *pNewNode = __memNewNode();
    strncpy(pNodeTreeMaster->sPrompt,sPrompt,MAX_PROMPT);
    strncpy(pNodeTreeMaster->sHelp,sHelp,MAX_HELP);
    if (!pMaster) pMaster=pNodeTreeMaster;
        if(!pMaster->pFirstChild) // No child -> first child
        {
            pMaster->pFirstChild=pNewNode;
            ADD_LOG_ENTRY("mod_data[nodeTree]: Node <%s> added at <%p> as first child of <%p>\n",sPrompt,pNewNode,pMaster);
            return pNewNode;
        }
        else // Existing child(s) -> append to the last
        {
            struct nodeTree *pTmpSearch=pMaster->pFirstChild;
            while (pTmpSearch->pNext)
                pTmpSearch=pTmpSearch->pNext;
            pNewNode->pPrev=pTmpSearch;
            pTmpSearch->pNext=pNewNode;
            ADD_LOG_ENTRY("mod_data[nodeTree]: Node  <%s> appended at <%p> as last child of <%p>\n",sPrompt,pNewNode,pMaster);
            return pNewNode;
        }
}


void* __memNewNode(){
    /* do: malloc a new node
                initialise the node with NULL;
        return: pointer to the new node
    */
    struct nodeTree *pNewNode;
    pNewNode=(struct nodeTree*) malloc (sizeof(struct nodeTree));
    EXIT_IF_NULL(pNewNode);
    pNewNode->pMaster=NULL;
    pNewNode->pFirstChild=NULL;
    pNewNode->pPrev=NULL;
    pNewNode->pNext=NULL;
    pNewNode->sPrompt[0]='\0';
    pNewNode->sHelp[0]='\0';
    return pNewNode;
}
