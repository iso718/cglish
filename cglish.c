#include "cglish.h"

int main(){
    __initBtree();
    __initModules();
    __mainloop();
return EXIT_SUCCESS;
}

void __mainloop(){
    char sUserInput[MAX_INPUT];
    MSG_OUT("\n");
    while(1)
    {
        MSG_OUT("%s>",dataGetPrompt(pCurNode));
        fgets(sUserInput,MAX_INPUT,stdin);
        __processUserInput(sUserInput);
    }

}

void __processUserInput(char *sUserInput){
    char **aArg=NULL;
    int nArg;
    int nTmp=0;
    t_node *pTmp;
    stripStr(sUserInput,sUserInput);
    if ((nArg=splitStrToArr(sUserInput,&aArg)) == 0) // Empty input, nothing to do
        return;
    freeArrFromStr(nArg,aArg);
}

void __initModules(){
    INIT_MODULES;
    int i=0;
    while (initMods[i].pFunc!=NULL)
        initMods[i++].pFunc(0); // 0=init
}

void __initBtree(){
    pMasterNode=nodeInit("root","Top level",NULL);
    pCurNode=pMasterNode;
}
