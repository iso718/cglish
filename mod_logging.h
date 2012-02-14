#ifndef MOD_LOGGING_H_INCLUDED
#define MOD_LOGGING_H_INCLUDED

#define LOGFILE "cglish.log"
#define DEBUGFILE "cglish.dbg"
FILE *logfile;
FILE *debugfile;

void logInit(); //TODO: Unload module on file open error
void logNodeInit(); //Register node for logging
void showLogs(int nArg, char **sArr);

#define ADD_LOG_ENTRY(MSG,...) \
fprintf(logfile,MSG,##__VA_ARGS__);\
fflush(logfile);

#define ADD_DEBUG_ENTRY(MSG,...) \
fprintf(debugfile,MSG,##__VA_ARGS__);\
fflush(debugfile);

#endif // MOD_LOGGING_H_INCLUDED
