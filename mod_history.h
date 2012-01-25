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

void hist_init();

#endif // MOD_HISTORY_H_INCLUDED
