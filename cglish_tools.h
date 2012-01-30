#ifndef CGLISH_TOOLS_H_INCLUDED
#define CGLISH_TOOLS_H_INCLUDED

#define MAX_HISTORY 20

// Strings
void stripStr(char*, char*); // strips the user input
int __isCharStripRelevant(int);
int splitStrToArr(char*, char***); // used to split the user input
void freeArrFromStr(int,char**); // frees memory alloc'd in splitStrToArr

// Checks
void exitOnNULLPointer(void* pToCheck);  //Exit if pointer is NULL
int strIsEmpty(char*); //True if str is empty, False otherwise. Empty if [0]='\0'

#endif // CGLISH_TOOLS_H_INCLUDED
