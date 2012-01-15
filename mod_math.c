#include "mod_math.h"

void math_init(){
    t_node *pMaster;
    MSG_DBG("Init module math");
    pMaster=registerModule(NULL,"math","Basic math tools",&math_default);
    registerModule(pMaster,"add","Add given numbers",&math_add);
}

void math_add(int nArg,char** sArg){
    int i;
    MSG_DBG("Got: nArg: <%i>, sArg at <%p>",nArg, sArg);
}

void math_default(int nArg,char** sArg){

}
