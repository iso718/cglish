#ifndef CGLISH_H_INCLUDED
#define CGLISH_H_INCLUDED

/* Default Header */

/* Includes */
// Standard includes
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
/* module includes */
#include "mod_logging.h"
#include "mod_data.h"
#include "mod_console.h"
#include "mod_history.h"
#include "mod_psql.h"

/* definitions */
#define INIT_MODULES \
void (*initMod[])()=  {\
&logInit, \
&dataInit, \
&logNodeInit, \
&histInit, \
&conInit,\
&psqlInit,\
NULL \
};

/* extern functions */

/* exported control functions (init, help,..) */

/* other exported functions */
// Tests
#define exitIfNull(P) if (!P) exitOnError();
void exitOnError(); // Serious Error occoured
#define testEmptyStr(STR) STR[0]=='\0' ? true : false
// String functions
void stripStr(char*, char*); // strips the user input
int splitStrToArr(char *sSrc, char ***arr);
void freeArrFromStr(int nArr,char **sArr);

/* exported global vars */

/* internal functions */
#define __testCharStrip(C) ((C== 0x9) || (C== 0x20) || (C== 0x13)) ? true : false
/* internal global vars  */


#endif // CGLISH_H_INCLUDED
