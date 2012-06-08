#include "cglish.h"

int main(){

return EXIT_SUCCESS;
}

int initModules(){
    INIT_MODULES;
    int i=0;
    while (initMods[i].pFunc!=NULL)
        initMods[i++].pFunc(0);

    return RETURN_SUCCESS;
}

void checkPointer(void* pToCheck){
    if (!pToCheck)
        exit(EXIT_FAILURE);
}

void test(){

}
