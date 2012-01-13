#include "cglish.h"

int main(){
    __initBtree();
    __initModules();
    __mainloop();
return EXIT_SUCCESS;
}

void __mainloop(){
    char sUserInput[MAX_INPUT];
    MSG_CON("\n");
    while(1)
    {
        MSG_CON("%s>",dataGetPrompt(pCurNode));
        fgets(sUserInput,MAX_INPUT,stdin);
    }

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

void exitOnNULLPointer(void* pToCheck){
    if (!pToCheck)
        exit(EXIT_FAILURE);
}

