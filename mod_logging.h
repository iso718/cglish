#ifndef MOD_LOGGING_H_INCLUDED
#define MOD_LOGGING_H_INCLUDED

#define LOGFILE "cglish.log"
FILE *logfile;

void logInit(); //TODO: Unload module on file open error
void logNodeInit(); //Register node for logging

#define ADD_LOG_ENTRY(MSG,...) \
fprintf(logfile,MSG,##__VA_ARGS__);\
fflush(logfile);


#endif // MOD_LOGGING_H_INCLUDED
