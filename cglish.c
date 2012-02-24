#include "cglish.h"

int main(){
    // init Modules
    int i=0;
    INIT_MODULES;
    while (initMod[i]!=NULL) initMod[i++]();
    conMainLoop();
    return 0;
}


/* Test and exit Functions */
void exitOnError(){// Serious Error occoured
    exit(EXIT_FAILURE);
}
void exitOnNULLPointer(void *ptr){// Test for and exit on NULL pointer
    if (!ptr) exitOnError();
}
//int testCharStrip(int c){
//    switch (c)
//    {
//        case 0x9:
//        case 0x20:
//        case 0x13:
//            return true;
//        default:
//            return false;
//    }
//}
/* End Test and exit Functions */

/* String tools */
void stripStr(char *sDst, char *sSrc){
    int i=0,j=0;
    // Remove at beginning of string
    while (__testCharStrip(sSrc[i]))
        i++;
    while (sSrc[i]!='\0' && sSrc[i]!='\n')
    {
        if (__testCharStrip(sSrc[i]) && __testCharStrip(sSrc[i+1])) //jump over dups
            i++;
        else if (sSrc[i]=='\t') //change tabs to space
            sDst[j++]=' ';
        else
            sDst[j++]=sSrc[i++];
    }
    if (j>0)
        while (__testCharStrip(sDst[j-1]))
            j--;
    sDst[j]='\0';
}

int splitStrToArr(char *sSrc, char ***arr){
    int nTmp=0, nSrc=0, nArrCount=0,i;
    char sTmp[MAX_INPUT];
    char *pTmp=NULL;
    char **ppTmp=NULL;
    for (nSrc=0;nSrc<=strlen(sSrc);nSrc++)
    {
        if (sSrc[nSrc]== ' ' || sSrc[nSrc]=='\0')
        {
            sTmp[nTmp]='\0';
            pTmp=(char*) malloc(sizeof(char)*(nTmp+1));
            exitOnNULLPointer(pTmp);
            strcpy(pTmp,sTmp);
            ppTmp=(char**) realloc(ppTmp,sizeof(char**)*++nArrCount);
            exitOnNULLPointer(ppTmp);
            ppTmp[nArrCount-1]=pTmp;
            nTmp=0;
        }
        else
        {
            sTmp[nTmp++]=sSrc[nSrc];
        }
    }
    *arr=ppTmp;
    ADD_DEBUG_ENTRY("cglish[splitStrToArr]: Processed input <%s> to arr size <%i>\n",sSrc,nArrCount);
    for (i=0;i<nArrCount;i++)
        ADD_DEBUG_ENTRY("cglish[splitStrToArr]: Arg <%i> Str <%s>\n",i,ppTmp[i]);
    return nArrCount;
}

void freeArrFromStr(int nArr,char **sArr){
    int nTmp;
    for (nTmp=0;nTmp<nArr;nTmp++)
    {
        free(sArr[nTmp]);
    }
    free(sArr);
}

/* End String tools */
