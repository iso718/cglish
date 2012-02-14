#include "cglish.h"

void histInit(){
    int i=0;
    for (i=0;i<MAX_HISTORY;i++)
    {
            pHist[i].pNext=&pHist[i+1];
            pHist[i].pPrev=&pHist[i-1];
            pHist[i].sCmd[0]='\0';
    }
    pHist[0].pPrev=&pHist[MAX_HISTORY-1];
    pHist[MAX_HISTORY-1].pNext=&pHist[0];
    pGivenHist=&pHist[0];
    pNewHist=&pHist[0];
    ADD_LOG_ENTRY("mod_history[init]: History Initialisation done. First Element at <%p>\n",&pHist[0]);
}

void histAdd(char* str){// add char* to history
    strncpy(pNewHist->sCmd,str,MAX_INPUT);
    pNewHist=pNewHist->pNext;
    pGivenHist=pNewHist;
    ADD_DEBUG_ENTRY("mod_history[add]: Added <%s>  at <%p>\n",str, pGivenHist);
}

char* histGetPrev(){
    if (strIsEmpty(pGivenHist->pPrev->sCmd)) return NULL;
    pGivenHist=pGivenHist->pPrev;
    return pGivenHist->sCmd;
}

char* histGetNext(){
    if (strIsEmpty(pGivenHist->pNext->sCmd)) return NULL;
    pGivenHist=pGivenHist->pNext;
    return pGivenHist->sCmd;
}
