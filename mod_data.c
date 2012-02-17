#include "cglish.h"
void dataInit(){
    // init the nodes tree
    pNodeTreeMaster=(struct nodeTree*) __memNewNode();
    strncpy(pNodeTreeMaster->sPrompt,ROOT_PROMPT,MAX_PROMPT);
    strncpy(pNodeTreeMaster->sHelp,ROOT_HELP,MAX_HELP);
    pCurrentNode=pNodeTreeMaster;
    __setPrompt(ROOT_PROMPT);
    ADD_LOG_ENTRY("mod_data[init]: Node Tree initialisation done. Master node at <%p>, sCurrentPrompt at <%p>\n",pNodeTreeMaster,&sCurrentPrompt);
}


struct nodeTree* addNode(struct nodeTree *pMaster,char *sPrompt,char *sHelp,void (*pFunc)()  ){//Adds a node to the tree
    struct nodeTree *pNewNode = __memNewNode();
    strncpy(pNewNode->sPrompt,sPrompt,MAX_PROMPT);
    strncpy(pNewNode->sHelp,sHelp,MAX_HELP);
    pNewNode->pFunc=pFunc;
    if (!pMaster) pMaster=pNodeTreeMaster;
    if(!pMaster->pFirstChild) // No child -> first child
    {
        pMaster->pFirstChild=pNewNode;
        ADD_DEBUG_ENTRY("mod_data[nodeTree]: Node <%s> added at <%p> as first child of <%p>\n",sPrompt,pNewNode,pMaster);
        return pNewNode;
    }
    else // Existing child(s) -> append to the last
    {
        struct nodeTree *pTmpSearch=pMaster->pFirstChild;
        while (pTmpSearch->pNext)
            pTmpSearch=pTmpSearch->pNext;
        pNewNode->pPrev=pTmpSearch;
        pTmpSearch->pNext=pNewNode;
        ADD_DEBUG_ENTRY("mod_data[nodeTree]: Node  <%s> appended at <%p> as last child of <%p>\n",sPrompt,pNewNode,pMaster);
        return pNewNode;
    }
}

struct nodeTree* getNodeByPrompt(struct nodeTree *pMyMaster,char *myPrompt){// Returns the nodes address of a given prompt in current level
    if (!pMyMaster)
        pMyMaster=pCurrentNode;
    struct nodeTree *pTmp=pMyMaster->pFirstChild;
    if (pTmp==NULL)
        {
            ADD_DEBUG_ENTRY("mod_data[getNodeByPrompt]: No child found for prompt <%s> at <%p>\n",myPrompt, pMyMaster);
            return NULL;
        }
    while (pTmp)
    {
        ADD_DEBUG_ENTRY("mod_data[getNodeByPrompt]: Compare prompt <%s> with node <%p> prompt <%s>\n",myPrompt,pTmp, pTmp->sPrompt);
        if (strcmp(pTmp->sPrompt, myPrompt)==0)
        {
            ADD_DEBUG_ENTRY("mod_data[getNodeByPrompt]: Found prompt <%s> at <%p>\n",pTmp->sPrompt, pTmp);
            return pTmp;
        }
        pTmp=pTmp->pNext;
    }
    ADD_DEBUG_ENTRY("mod_data[getNodeByPrompt]: No matching child found for prompt <%s> at <%p>\n",myPrompt, pMyMaster);
    return NULL;
}

void switchToNode(struct nodeTree *pNode){
    ADD_DEBUG_ENTRY("mod_data[switchToNode]: Switch to node <%s>  at <%p>\n",pNode->sPrompt, pNode);
    pCurrentNode=pNode;
    __setPrompt(pCurrentNode->sPrompt);
}

void __setPrompt(char *sPrompt){
        strncpy(sCurrentPrompt,sPrompt,MAX_PROMPT);
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
