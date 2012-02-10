#ifndef MOD_HISTORY_H_INCLUDED
#define MOD_HISTORY_H_INCLUDED

#define HISTORY
#define MAX_HISTORY 20

struct sdHist {
    struct sdHist *pNext;
    struct sdHist *pPrev;
    char sCmd[MAX_INPUT];
};

struct sdHist pHist[MAX_HISTORY];
struct  sdHist *pGivenHist; // pointer of the last given hist entry
struct  sdHist *pNewHist;  // pointer where the next history entry should be added

void histInit();
void histAdd(char*); // add char* to history
char* histGetPrev();
char* histGetNext();

#endif // MOD_HISTORY_H_INCLUDED
