#ifndef MOD_HISTORY_H_INCLUDED
#define MOD_HISTORY_H_INCLUDED

#include "cglish.h"

#define HISTORY
#define MAX_HISTORY 20

typedef struct {
    void *pNext;
    void *pPrev;
    char sCmd[MAX_INPUT];
} t_hist;

t_hist *pFirstHist, *pCurHist, *pLastHist;

void hist_init();
void hist_add(char*); // add char* to history
char* hist_get(int); // get +/- int from history

#endif // MOD_HISTORY_H_INCLUDED
