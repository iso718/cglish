#include "cglish.h"

t_node* modCreateNode(t_node *pMaster){
        t_node *pTmp = (t_node*) __malloc (sizeof(t_node));
        pTmp->pMaster=pMaster;
        return pTmp;
}

t_nodeData* modCreateNodeData(char *sPrompt, char *sHelp,void (*pFunc)()){
        t_nodeData *pTmp = (t_nodeData*) __malloc (sizeof(t_nodeData));
        strcpy(pTmp->sPrompt,sPrompt);
        strcpy(pTmp->sHelp,sHelp);
        pTmp->pFunc=pFunc;
        return pTmp;
};

void* __malloc(int mySize){
        t_nodeData *pTmp = (t_nodeData*) malloc (sizeof(t_nodeData));
        checkPointer(pTmp);
        return pTmp;
}

void __addChildNode(t_node *pMaster){
        if (!pMaster)
            return;
        // Erstes child wenn !firstchild
        // Neues letztes child wenn firstchild vorhanden.
}


