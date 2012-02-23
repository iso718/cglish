#include "cglish.h"

struct sdPsqlSrv *pPsqlSrv=NULL;

void psqlInit()
{
    void *pPsqlNode;
    pPsqlNode=addNode(NULL,"psql","Postgres tools and functions",NULL,NULL);
    addNode(pPsqlNode,"connect","Connect to a server",&psqlConnect,&psqlConnectHelp);
    __psqlInitConfig();
    ADD_LOG_ENTRY("mod_psql[psqlInit]: Psql initialisation done. \n");
}

void __psqlInitConfig()
{
    INIT_PSQL_SRV;
}
void psqlConnect(int nArg, char **sArr)
{

}

void psqlConnectHelp()
{
    struct sdPsqlSrv *pTmp=pPsqlSrv;
    int i=0;
    OUTPUT_HELP("\nHelp for the psql connect function\n");
    OUTPUT_HELP("Usage:\n");
    OUTPUT_HELP("<nr> - The server number to connect to\n");
    OUTPUT_HELP("\n");
    OUTPUT_HELP("add - Add new server with\n");
    OUTPUT_HELP("\n");
    OUTPUT_HELP("Available server:\n");
    do
    {
        OUTPUT_HELP("<%i> - <%s> - <%s> - <%i>\n",i++,pTmp->sTitle,pTmp->sIPv4,pTmp->nPort);
        pTmp=pTmp->pNext;
    } while (pTmp->pNext);
}

void __psqlAddSrv(char *sTitle,char *sIpv4,int nPort, char *sUN, char *PWD) // Add a server to the config
{
    struct sdPsqlSrv *pTmpSrv,*pSrvSearch;
    pTmpSrv=(struct sdPsqlSrv*) malloc(sizeof (struct sdPsqlSrv));
    EXIT_IF_NULL(pTmpSrv);
    strncpy(pTmpSrv->sTitle,sTitle,MAX_PSQL_SRV_TITLE);
    strncpy(pTmpSrv->sIPv4,sIpv4,15);
    pTmpSrv->nPort=nPort;
    strncpy(pTmpSrv->sUN,sUN,MAX_PSQL_USERNAME);
    strncpy(pTmpSrv->sPWD,sUN,MAX_PSQL_USERPWD);
    pTmpSrv->pgConn=NULL;
    pTmpSrv->pNext=NULL;
    ADD_DEBUG_ENTRY("__psqlAddSrc: Added <%s> to <%p>",sTitle,pTmpSrv);
    if (!pPsqlSrv)
    {
        pPsqlSrv=pTmpSrv;
        return;
    }
    pSrvSearch=pPsqlSrv;
    while (pSrvSearch->pNext) pSrvSearch=pSrvSearch->pNext;
    pSrvSearch->pNext=pTmpSrv;
}



