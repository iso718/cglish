#ifndef MOD_PSQL_H_INCLUDED
#define MOD_PSQL_H_INCLUDED

#include <libpq-fe.h>

#define MAX_PSQL_SRV_TITLE 30
#define MAX_PSQL_USERNAME 30
#define MAX_PSQL_USERPWD 30
// Servers
struct sdPsqlSrv {
char sTitle[MAX_PSQL_SRV_TITLE];
char sIPv4[16]; // xxx.xxx.xxx.xxx\0
int nPort;
PGconn *pgConn;
char sUN[MAX_PSQL_USERNAME];
char sPWD[MAX_PSQL_USERPWD];
struct sdPsqlSrv *pNext;
};

// Hardcoded Servers
// TODO: Configfile
#define INIT_PSQL_SRV \
__psqlAddSrv("SBB_LAB_OL_AKT","10.16.240.10",5433,"postgres","postgres"); \
__psqlAddSrv("SBB_LAB_ZUE_AKT","10.16.240.10",5433,"postgres","postgres"); \
__psqlAddSrv("SBB_LAB_LS_AKT","10.16.240.10",5433,"postgres","postgres"); \
__psqlAddSrv("SBB_LAB_DB1","10.16.240.10",5433,"postgres","postgres"); \
__psqlAddSrv("SBB_LAB_OL_MGMT1_DMC","10.16.240.10",5433,"postgres","postgres"); \
__psqlAddSrv("SBB_LAB_OL_MGMT2_DMC","10.16.240.10",5433,"postgres","postgres"); \
__psqlAddSrv("SBB_LAB_OL_MGMT1_VCSRS","10.16.240.10",5432,"postgres","postgres"); \
__psqlAddSrv("SBB_LAB_OL_MGMT2_VCSRS","10.16.240.10",5432,"postgres","postgres"); \
__psqlAddSrv("SBB_LAB_ZUE_MGMT1_DMC","10.16.248.10",5433,"postgres","postgres"); \
__psqlAddSrv("SBB_LAB_ZUE_MGMT2_DMC","10.16.248.10",5433,"postgres","postgres"); \
__psqlAddSrv("SBB_LAB_ZUE_MGMT1_VCSRS","10.16.248.10",5432,"postgres","postgres"); \
__psqlAddSrv("SBB_LAB_ZUE_MGMT2_VCSRS","10.16.248.10",5432,"postgres","postgres"); \
__psqlAddSrv("SBB_LAB_LS_MGMT1_DMC","10.16.243.10",5433,"postgres","postgres"); \
__psqlAddSrv("SBB_LAB_LS_MGMT2_DMC","10.16.243.10",5433,"postgres","postgres"); \
__psqlAddSrv("SBB_LAB_LS_MGMT1_VCSRS","10.16.243.10",5432,"postgres","postgres"); \
__psqlAddSrv("SBB_LAB_LS_MGMT2_VCSRS","10.16.243.10",5432,"postgres","postgres");





void psqlInit();
void __psqlInitConfig();
void psqlConnect(int nArg, char **sArr);
void psqlConnectHelp();

void __psqlAddSrv(char*,char*, int,  char* , char*); // Add a server to the config
#endif // MOD_PSQL_H_INCLUDED
