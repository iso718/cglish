#include "cglish.h"

t_node* registerModule(t_node *pMyMaster, char *sPrompt, char *sHelp, void (*pFunc)()){
    if (!pMyMaster)
        pMyMaster=pMasterNode;
    t_nodeData *pTmpData=__nodeDataAdd(sPrompt,sHelp,pFunc);
    return (__nodeAdd(pMyMaster,pTmpData));
}

t_node* nodeInit(char *sPrompt, char *sHelp, void (*pFunc)()){
    t_nodeData *pTmpData=__nodeDataAdd(sPrompt,sHelp,pFunc);
    return (__nodeAdd(NULL,pTmpData));
}

char* dataGetPrompt(t_node *pMyNode){
    MSG_DBG_NOD("dataGetPrompt: Return prompt <%s> from node <%p>",pMyNode->pData->sPrompt, pMyNode);
    return (pMyNode->pData->sPrompt);
}

t_node* getNodeByPrompt(t_node *pMyMaster,char *myPrompt){
    t_node *pTmp=pMyMaster->pFirstChild;
    MSG_DBG_NOD("getNodeByPrompt: Looking for <%s> in <%p>",myPrompt, pMyMaster);
    if (pTmp==NULL)
    {
        MSG_DBG_NOD("getNodeByPrompt: No Child found in <%p>",pMyMaster);
        return NULL;
    }
    while (pTmp)
    {
        if (strcmp(pTmp->pData->sPrompt, myPrompt)==0)
            {
                MSG_DBG_NOD("getNodeByPrompt: Found at <%p>", pTmp);
                return pTmp;
            }
        pTmp=pTmp->pNextNode;
    }
    MSG_DBG_NOD("getNodeByPrompt: Prompt <%s> not found",myPrompt);
    return NULL;
}

t_node* __nodeAdd(t_node *pMyMaster, t_nodeData *pData){
        t_node *pTmp = (t_node*) malloc (sizeof(t_node));
        exitOnNULLPointer(pTmp);
        pTmp->pMaster=pMyMaster;
        pTmp->pFirstChild=NULL;
        pTmp->pNextNode=NULL;
        pTmp->pPrevNode=NULL;
        pTmp->pData=pData;
        if (!pMyMaster) //No master -> first node
            return pTmp;
        else if(!pMyMaster->pFirstChild) // No child -> first child
        {
            pMyMaster->pFirstChild=pTmp;
            return pTmp;
        }
        else // Existing child(s) -> append to the last
        {
            t_node *pTmpSearch=pMyMaster->pFirstChild;
            while (pTmpSearch->pNextNode)
                pTmpSearch=pTmpSearch->pNextNode;
            pTmp->pPrevNode=pTmpSearch;
            pTmpSearch->pNextNode=pTmp;
            return pTmp;
        }
}

t_nodeData* __nodeDataAdd(char *sPrompt, char *sHelp,void (*pFunc)()){
        t_nodeData *pTmp = (t_nodeData*) malloc (sizeof(t_nodeData));
        exitOnNULLPointer(pTmp);
        strcpy(pTmp->sPrompt,sPrompt);
        strcpy(pTmp->sHelp,sHelp);
        pTmp->pFunc=pFunc;
        return pTmp;
};

t_node* nodeGetParent(t_node *pNode){
    return ((t_node*) pNode->pMaster);
}


