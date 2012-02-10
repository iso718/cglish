#include "cglish.h"

int main(){
    // init Modules
    int i=0;
    INIT_MODULES;
    while (initMod[i]!=NULL) initMod[i++]();
    MAINLOOP;
    fMainLoop();
    return 0;
}


/* Test Functions */
void abnormalAbort(){// Serious Error occoured
    exit(EXIT_FAILURE);
}

void exitOnNULLPointer(void *ptr){// Test for and exit on NULL pointer
    if (!ptr) abnormalAbort();
}
int strIsEmpty(char *str){
  return str[0]=='\0' ? true : false;
}

int isCharStripRelevant(int c){
    switch (c)
    {
        case 0x9:
        case 0x20:
        case 0x13:
            return true;
        default:
            return false;
    }
}

void stripStr(char *sDst, char *sSrc){
    int i=0,j=0;
    // Remove at beginning of string
    while (isCharStripRelevant(sSrc[i]))
        i++;
    while (sSrc[i]!='\0' && sSrc[i]!='\n')
    {
        if (isCharStripRelevant(sSrc[i]) && isCharStripRelevant(sSrc[i+1])) //jump over dups
            i++;
        else if (sSrc[i]=='\t') //change tabs to space
            sDst[j++]=' ';
        else
            sDst[j++]=sSrc[i++];
    }
    if (j>0)
        while (isCharStripRelevant(sDst[j-1]))
            j--;
    sDst[j]='\0';
}



//#include "cglish.h"
//
//int main(){
//    __init();
//    __quit();
//return EXIT_SUCCESS;
//}
//
//void processUserInput(char *sUserInput){
//    char **aArg=NULL;
//    int nArg, nCmd=0;
//    t_node *pTmp=pCurNode;
//    stripStr(sUserInput,sUserInput); // Make nice string
//    if ((nArg=splitStrToArr(sUserInput,&aArg)) == 0) // Split string into arr. Empty input-> nothing to do
//        return;
//    while ((nCmd<nArg) && (getNodeByPrompt(pTmp,aArg[nCmd]))) // Count cmd's
//        pTmp=getNodeByPrompt(pTmp,aArg[nCmd++]);
//    if (nCmd==0) // Params only
//    {
//        MSG_DBG("Params only");
//        if (pCurNode->pData->pFunc)
//            pCurNode->pData->pFunc(nArg,aArg);
//    }
//    else if (nCmd==nArg) // Cmd only
//    {
//        MSG_DBG("Cmd only");
//        pCurNode=pTmp;
//    }
//    else // Cmd and params
//    {
//        pTmp->pData->pFunc(nArg-nCmd,&aArg[nCmd]);  // Just execute, no level change
//        MSG_DBG("CMD: nCmd: %i and Params:  nArg:%i, func: <%p>",nCmd, nArg,pTmp->pData->pFunc);
//    }
//    freeArrFromStr(nArg,aArg);
//}
//void __init(){
//    //init Console
//     conInit();
//    // init Btree
//    pMasterNode=nodeInit("root","Top level",NULL);
//    pCurNode=pMasterNode;
//    // init Modules
//    INIT_MODULES;
//    int i=0;
//    while (initMods[i].pFunc!=NULL)
//        initMods[i++].pFunc(0); // 0=init
//}
//
//void __quit(){
//        // quit Modules
//    INIT_MODULES;
//    int i=0;
//    while (initMods[i].pFunc!=NULL)
//        initMods[i++].pFunc(1); // 0=init
//    exit(0);
//}
