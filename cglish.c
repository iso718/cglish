#include "cglish.h"

int main(){
    __init();
    __mainloop();
return EXIT_SUCCESS;
}

void __mainloop(){
    char sUserInput[MAX_INPUT];
    MSG_OUT("\n");
    while(1)
    {
        MSG_OUT("%s>",dataGetPrompt(pCurNode));
         conMainLoop(sUserInput);
        __processUserInput(sUserInput);
    }
    __quit();
}

void __processUserInput(char *sUserInput){
    char **aArg=NULL;
    int nArg, nCmd=0;
    t_node *pTmp=pCurNode;
    stripStr(sUserInput,sUserInput); // Make nice string
    if ((nArg=splitStrToArr(sUserInput,&aArg)) == 0) // Split string into arr. Empty input-> nothing to do
        return;
    while ((nCmd<nArg) && (getNodeByPrompt(pTmp,aArg[nCmd]))) // Count cmd's
        pTmp=getNodeByPrompt(pTmp,aArg[nCmd++]);
    if (nCmd==0) // Params only
    {
        MSG_DBG("Params only");
        if (pCurNode->pData->pFunc)
            pCurNode->pData->pFunc(nArg,aArg);
    }
    else if (nCmd==nArg) // Cmd only
    {
        MSG_DBG("Cmd only");
        pCurNode=pTmp;
    }
    else // Cmd and params
    {
        pTmp->pData->pFunc(nArg-nCmd,&aArg[nCmd]);  // Just execute, no level change
        MSG_DBG("CMD: nCmd: %i and Params:  nArg:%i, func: <%p>",nCmd, nArg,pTmp->pData->pFunc);
    }
    freeArrFromStr(nArg,aArg);
}
void __init(){
    //init Console
     conInit();
    // init Modules
    INIT_MODULES;
    int i=0;
    while (initMods[i].pFunc!=NULL)
        initMods[i++].pFunc(0); // 0=init

    // init Btree
    pMasterNode=nodeInit("root","Top level",NULL);
    pCurNode=pMasterNode;
}

void __quit(){
    conQuit();
}
