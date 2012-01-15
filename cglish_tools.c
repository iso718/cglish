#include "cglish.h"

void exitOnNULLPointer(void* pToCheck){
    if (!pToCheck)
    {
        MSG_DBG("NULL pointer catched");
        exit(EXIT_FAILURE);
    }
}

int splitStrToArr(char *sSrc, char ***arr){
    int nTmp=0, nSrc=0, nArrCount=0;
    char sTmp[MAX_INPUT];
    char *pTmp=NULL;
    char **ppTmp=NULL;
    if (strlen(sSrc)==0) // got empty string
        return 0;
    for (nSrc=0;nSrc<=strlen(sSrc);nSrc++)
    {
        if (sSrc[nSrc]== ' ' || sSrc[nSrc]=='\0')
        {
            sTmp[nTmp]='\0';
            pTmp=(char*) malloc(sizeof(char)*(nTmp+1));
            exitOnNULLPointer(pTmp);
            MSG_DBG_MEM("splitStrToArr: *char at <%p>",pTmp);
            strcpy(pTmp,sTmp);
            ppTmp=(char**) realloc(ppTmp,sizeof(char**)*++nArrCount);
            exitOnNULLPointer(ppTmp);
            MSG_DBG_MEM("splitStrToArr: Realloced **char at <%p>",ppTmp);
            ppTmp[nArrCount-1]=pTmp;
            nTmp=0;
        }
        else
        {
            sTmp[nTmp++]=sSrc[nSrc];
        }
    }
    *arr=ppTmp;
    return nArrCount;
}

void freeArrFromStr(int nArr,char **sArr){
    int nTmp;
    for (nTmp=0;nTmp<nArr;nTmp++)
    {
        MSG_DBG_MEM("freeArrFromStr: Free *char at <%p>",sArr[nTmp]);
        free(sArr[nTmp]);
    }
    MSG_DBG_MEM("freeArrFromStr: Free **char at <%p>",sArr);
    free(sArr);
}

void stripStr(char *sDst, char *sSrc){
    int i=0,j=0;
    // Remove at beginning of string
    while (__isCharStripRelevant(sSrc[i]))
        i++;
    while (sSrc[i]!='\0' && sSrc[i]!='\n')
    {
        if (__isCharStripRelevant(sSrc[i]) && __isCharStripRelevant(sSrc[i+1])) //jump over dups
            i++;
        else if (sSrc[i]=='\t') //change tabs to space
            sDst[j++]=' ';
        else
            sDst[j++]=sSrc[i++];
    }
    if (j>0)
        while (__isCharStripRelevant(sDst[j-1]))
            j--;
    sDst[j]='\0';
    MSG_DBG("stripStr: <%s>, length: <%i>",sDst,j);
}

int __isCharStripRelevant(int c){
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
