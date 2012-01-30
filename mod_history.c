#include "mod_history.h"

void hist_init(){
    int i;
    pFirstHist = (t_hist*) malloc (sizeof(t_hist)*MAX_HISTORY);
    exitOnNULLPointer(pFirstHist);
    pCurHist=(t_hist*) pFirstHist;
    for (i=0;i<MAX_HISTORY;i++)
    {
            pCurHist->pNext=pCurHist;
            pCurHist->pPrev=pCurHist;
            pCurHist->sCmd[0]='\0';
    }
     //lLink start and end
    pFirstHist->pPrev=pCurHist;
    pCurHist->pNext=pFirstHist;
    // Set pointers to first el
    pCurHist=pFirstHist;
    pLastHist=pFirstHist;
}

void hist_add(char* str){// add char* to history
    strncpy(pLastHist->sCmd,str,MAX_INPUT);
    pLastHist=(t_hist*) pLastHist->pNext;
    pCurHist=pLastHist;
}

char* hist_get(int n){// get +/- int from history
    int i;
    t_hist *pTmp=NULL;
    if (n<0)
    {
        for (i=1;i<=n;i++)
        {
            pTmp=(t_hist*) pCurHist->pPrev;  // Maybe there is a better way to derefer void pointer?
            if (!strIsEmpty(pTmp->sCmd))
                pCurHist=pCurHist->pPrev;
        }
    }
    if (n>0)
    {
        for (i=1;i<=n;i++)
        {
            pTmp=(t_hist*) pCurHist->pNext; // Maybe there is a better way to derefer void pointer?
             if (!strIsEmpty(pCurHist->sCmd))
                pCurHist=pCurHist->pNext;
        }
    }
    return pCurHist->sCmd;
}
