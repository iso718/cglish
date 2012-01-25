#include "mod_history.h"

t_hist *pHist;
t_hist *pCurHist;

void hist_init(){
    int i;
    pHist = (t_hist*) malloc (sizeof(t_hist)*MAX_HISTORY);
    exitOnNULLPointer(pHist);
    pCurHist=pHist;
    for (i=0;i<MAX_HISTORY;i++)
    {
            pCurHist->pNext=pCurHist;
            pCurHist->pPrev=pCurHist;
            pCurHist->sCmd[0]='\0';
    }
     //lLink start and end
    pHist->pPrev=pCurHist;
    pCurHist->pNext=pHist;
}
