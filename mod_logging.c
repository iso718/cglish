#include "cglish.h"

void logInit(){
    logfile=fopen(LOGFILE,"w");
    ADD_LOG_ENTRY("mod_logging[logInit]: Logging initialisation done. Logfile: %s\n",LOGFILE);
}

void logNodeInit(){
    addNode(NULL,"log","show log information");
}


